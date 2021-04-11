

#include <stdio.h>
#include <stdlib.h>

#include "dap.h"
#include "app.h"

#include <nidonehsp.h>
#include <SDL.h>

#define N2RI_DEBUG			(1)

enum
{
	MODE_PREVIEW = 0,
	MODE_BUILD,
	MODE_EXPORT,
	MODE_PACK,
	MODE_COMPILE,
	MODE_DEBUGADAPTER,
};

enum
{
	PLATFORM_NATIVE = 0,
	PLATFORM_HTML,
};

typedef struct n2a_options_t n2a_options_t;
struct n2a_options_t
{
	int mode_;
	const char* output_root_;
	const char* output_path_;
	const char* startup_script_;
	const char* startup_binary_;
	size_t include_paths_count_;
	const char** include_paths_;
	size_t define_macros_count_;
	const char** define_macros_;
	n2_bool_t error_dialog_;
	n2_bool_t success_dialog_;
	n2_bool_t formatted_output_;
	n2_bool_t pack_compress_;
	int export_platform_;
	n2_bool_t export_allow_directory_;
	const char* export_runtime_root_;
	int da_port_;
	int da_timeout_msec_;
	int da_logging_;
	int use_inspector_;
	int passthrough_begin_;
	int verbose_;
};

static void n2a_options_init(n2a_options_t* opts)
{
	opts->mode_ = MODE_PREVIEW;
	opts->output_root_ = NULL;
	opts->output_path_ = NULL;
	opts->include_paths_count_ = 0;
	opts->include_paths_ = NULL;
	opts->define_macros_count_ = 0;
	opts->define_macros_ = NULL;
	opts->startup_script_ = "main.nhsp";
	opts->startup_binary_ = NULL;
	opts->error_dialog_ = N2_TRUE;
	opts->success_dialog_ = N2_FALSE;
	opts->formatted_output_ = N2_FALSE;
	opts->pack_compress_ = N2_TRUE;
	opts->export_platform_ = PLATFORM_NATIVE;
	opts->export_allow_directory_ = N2_FALSE;
	opts->export_runtime_root_ = "runtime";
	opts->da_port_ = 9022;
	opts->da_timeout_msec_ = 10 * 1000;
	opts->da_logging_ = N2_FALSE;
	opts->use_inspector_ = 1;
	opts->passthrough_begin_ = -1;
	opts->verbose_ = 0;
}

typedef struct n2a_dap_user_t n2a_dap_user_t;
struct n2a_dap_user_t
{
	const n2a_options_t* opts_;
};

static void n2ai_apply_opts_to_state_bindings(n2_state_t* state, const n2a_options_t* opts)
{
	// 追加パス
	for (size_t i = 0; i < opts->include_paths_count_; ++i)
	{
		n2_plstrarray_pushv(state, state->pp_context_->searchpaths_, n2_plstr_clone(state, opts->include_paths_[i]));
	}

	// マクロ
	for (size_t i = 0; i < opts->define_macros_count_; ++i)
	{
		const char* macro = opts->define_macros_[i];
		const char* sephead = strchr(macro, '=');
		if (sephead)
		{
			const int separator = (int)((sephead - macro) / sizeof(char));
			n2_str_t tmacro;
			n2_str_init(&tmacro);
			n2_str_set(state, &tmacro, macro, SIZE_MAX);
			tmacro.str_[separator] = '\0';
			n2_pp_context_register_macro(state, state->pp_context_, tmacro.str_, tmacro.str_ + separator + 1);
			n2_str_teardown(state, &tmacro);
		}
		else
		{
			n2_pp_context_register_macro(state, state->pp_context_, macro, "");
		}
	}
}

static void n2ai_show_success(const n2a_options_t* opts, const char* fmt, ...)
{
	const n2_bool_t is_dialog = opts->success_dialog_;
	va_list args;
	va_start(args, fmt);
	const int required = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (required > 0)
	{
		char* mem = malloc((size_t)required + 4);
		va_start(args, fmt);
		vsnprintf(mem, (size_t)required + 4, fmt, args);
		va_end(args);

		fprintf(stdout, "%s\n", mem);
		if (is_dialog)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "n2studio > 成功", mem, NULL);
		}

		free(mem);
	}
}

static void n2ai_show_error(const n2a_options_t* opts, const char* fmt, ...)
{
	const n2_bool_t is_dialog = opts->error_dialog_;
	va_list args;
	va_start(args, fmt);
	const int required = vsnprintf(NULL, 0, fmt, args);
	va_end(args);

	if (required > 0)
	{
		char* mem = malloc((size_t)required + 4);
		va_start(args, fmt);
		vsnprintf(mem, (size_t)required + 4, fmt, args);
		va_end(args);

		fprintf(stderr, "%s\n", mem);
		if (is_dialog)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "n2studio > エラー", mem, NULL);
		}

		free(mem);
	}
}

// エラー
static n2_plstrarray_t* n2ai_state_print_errors = NULL;
static n2_str_t n2ai_state_print_error_merged;

static void n2ai_print_error_func(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	if (!n2ai_state_print_errors) { return; }
	n2_plstrarray_pushv(state, n2ai_state_print_errors, n2_plstr_clone(state, str));
}

static void n2ai_print_error_merge_and_clear(n2_state_t* state, const char* separator)
{
	n2_str_clear(&n2ai_state_print_error_merged);
	if (n2ai_state_print_errors)
	{
		for (size_t i = 0, l = n2_plstrarray_size(n2ai_state_print_errors); i < l; ++i)
		{
			const char* message = n2_plstrarray_peekv(n2ai_state_print_errors, N2_SCAST(int, i), NULL);
			if (i > 0 && separator) { n2_str_append(state, &n2ai_state_print_error_merged, separator, SIZE_MAX); }
			n2_str_append(state, &n2ai_state_print_error_merged, message, SIZE_MAX);
		}
		n2_plstrarray_clear(state, n2ai_state_print_errors);
	}
}

static void n2ai_print_error_reset(n2_state_t* state)
{
	n2_plstrarray_free(state, n2ai_state_print_errors);
	n2ai_state_print_errors = NULL;
	n2_str_teardown(state, &n2ai_state_print_error_merged);
}

typedef struct n2a_error_data_t n2a_error_data_t;
struct n2a_error_data_t
{
	n2_error_param_t e_;
	char* sourcefile_;
};

#define N2AI_MAX_STATE_ERROR (128)
static size_t n2ai_state_error_num = 0;
static size_t n2ai_state_error_reported = 0;
static n2a_error_data_t n2ai_state_errors[N2AI_MAX_STATE_ERROR];

static void n2ai_error_param_copy_to(n2_state_t* state, n2a_error_data_t* to, const n2_error_param_t* from)
{
	n2_error_param_t* toe = &to->e_;
	toe->state_ = from->state_;
	toe->error_ = from->error_;
	toe->sourcecode_ = from->sourcecode_;
	toe->package_ = from->package_ ? n2_plstr_clone(state, from->package_) : NULL;
	toe->raw_message_ = from->raw_message_ ? n2_plstr_clone(state, from->raw_message_) : NULL;
	toe->message_ = from->message_ ? n2_plstr_clone(state, from->message_) : NULL;
	toe->subdescription_ = from->subdescription_ ? n2_plstr_clone(state, from->subdescription_) : NULL;
	toe->line_ = from->line_;
	toe->fiber_ = from->fiber_;
	to->sourcefile_ = from->sourcecode_ ? n2_plstr_clone(state, from->sourcecode_->sourcefile_ ? from->sourcecode_->sourcefile_->src_resolved_filepath_.str_ : from->sourcecode_->src_filepath_.str_) : NULL;
}
static void n2ai_error_param_teardown(n2a_error_data_t* ed)
{
	n2_state_t* state = ed->e_.state_;
	n2_error_param_t* ep = &ed->e_;
	if (ep->package_) { n2_free(state, N2_RCAST(char*, ep->package_)); }
	if (ep->raw_message_) { n2_free(state, N2_RCAST(char*, ep->raw_message_)); }
	if (ep->message_) { n2_free(state, N2_RCAST(char*, ep->message_)); }
	if (ep->subdescription_) { n2_free(state, N2_RCAST(char*, ep->subdescription_)); }
	if (ed->sourcefile_) { n2_free(state, ed->sourcefile_); }
}

static void n2ai_error_func(void* error_user, const n2_error_param_t* param)
{
	N2_UNUSE(error_user);
	n2_state_t* state = param->state_;
	if (n2ai_state_error_num < N2AI_MAX_STATE_ERROR)
	{
		n2a_error_data_t* toed = &n2ai_state_errors[n2ai_state_error_num];
		n2ai_error_param_copy_to(state, toed, param);
		++n2ai_state_error_num;
	}
	++n2ai_state_error_reported;
}

static void n2ai_error_reset()
{
	for (size_t i = 0; i < n2ai_state_error_num; ++i)
	{
		n2ai_error_param_teardown(&n2ai_state_errors[i]);
	}
	n2ai_state_error_num = 0;
	n2ai_state_error_reported = 0;
}

static void n2ai_error_dump(const n2a_options_t* opts)
{
	N2_UNUSE(opts);

	//FILE* out = stdout;
	FILE* out = stderr;

	for (size_t i = 0; i < n2ai_state_error_num; ++i)
	{
		n2a_error_data_t* ed = &n2ai_state_errors[i];
		n2_error_param_t* e = &ed->e_;
		fprintf(out, "type(error)");
		fprintf(out, " file(%s)", ed->sourcefile_ ? ed->sourcefile_ : "");
		fprintf(out, " line(%d)", e->line_ + N2_LINE_BASE);
		fprintf(out, " column(%d)", e->column_ + N2_COLUMN_BASE);
		fprintf(out, " message{{%s}}", e->raw_message_);
		fprintf(out, "\n");
	}

	if (n2ai_state_error_reported > N2AI_MAX_STATE_ERROR)
	{
		fprintf(out, "type(info) file() line(-1) column(-1) message{{... too many errros[%zu] detected.}}\n", n2ai_state_error_reported);
	}
}

// バイナリビルド
static n2_bool_t n2ai_build_ebinary(n2_state_t* state, n2_buffer_t* dst, const n2a_options_t* opts)
{
	n2_buffer_clear(dst);

	// ヘッダー用のバッファを先に書いておく
	n2_buffer_append_values(state, dst, 0, n2h_binseq_signature_size());

	// データツリーを形成
	n2h_datatree_t* datatree = n2h_datatree_allocmap(state);

	// スクリプト
	{
		n2_str_t script_merged;
		n2_str_init(&script_merged);

		if (!n2_state_export_as_script(state, &script_merged))
		{
			n2ai_show_error(opts, "スクリプトのエクスポートに失敗しました。");
			return N2_FALSE;
		}

		n2h_datatree_t* scripttree = n2h_datatree_allocmap(state);

		n2_buffer_t scriptbin;
		n2_buffer_init(&scriptbin);
		if (!n2h_aes_encrypt(state, &scriptbin, script_merged.str_, script_merged.size_, n2ri_script_aes_key, sizeof(n2ri_script_aes_key), n2ri_script_aes_iv, sizeof(n2ri_script_aes_iv)))
		{
			n2ai_show_error(opts, "スクリプトのエクスポートに失敗しました。");
			return N2_FALSE;
		}

		n2h_datatree_set_bystr(state, scripttree, "b", SIZE_MAX, n2h_datatree_allocbin(state, scriptbin.data_, scriptbin.size_));
		n2h_datatree_set_bystr(state, scripttree, "l", SIZE_MAX, n2h_datatree_alloci(state, N2_SCAST(n2_valint_t, script_merged.size_)));
		n2h_datatree_set_bystr(state, scripttree, "c", SIZE_MAX, n2h_datatree_alloci(state, N2_SCAST(n2_valint_t, n2h_crc32(script_merged.str_, script_merged.size_))));
		n2h_datatree_set_bystr(state, datatree, "s", SIZE_MAX, scripttree);
		scripttree = NULL;

		n2_buffer_teardown(state, &scriptbin);

		n2_str_teardown(state, &script_merged);
	}

	// ファイルシステム
	{
		n2h_datatree_t* fstree = n2h_datatree_allocmap(state);

		for (size_t i = 0, l = n2_pppackfilearray_size(state->pp_context_->packfiles_); i < l; ++i)
		{
			const n2_pp_packfile_t* packfile = n2_pppackfilearray_peekc(state->pp_context_->packfiles_, N2_SCAST(int, i));
			N2_ASSERT(packfile);
			if (!packfile) { continue; }

			fprintf(stdout, "packファイル（%s）\n", packfile->filepath_.str_);
			fprintf(stdout, "  ファイル読み込み中…\n");

			n2_buffer_t filecontent = n2ri_load_raw_file(state, &packfile->filepath_);
			if (filecontent.size_ <= 0)
			{
				n2ai_show_error(opts, "packファイル（%s）が読み込めません。", packfile->filepath_.str_);
				return N2_FALSE;
			}

			n2_buffer_t filecompressed;
			n2_buffer_init(&filecompressed);

			const char* compressformat = "none";
			const n2_buffer_t* usefilebin = &filecontent;

			if (opts->pack_compress_)
			{
				// @todo compress format
				fprintf(stdout, "  ファイル圧縮中…（入力サイズ＝%zu[byte]）\n", filecontent.size_);

				if (n2h_z_compress(state, &filecompressed, filecontent.data_, filecontent.size_, N2_Z_COMPRESS_SPEED))
				{
					compressformat = "z";
					usefilebin = &filecompressed;
					fprintf(stdout, "  ファイル圧縮成功　フォーマット（%s）、圧縮後（%zu[byte]＝%.2lf%%に圧縮）\n", compressformat, filecompressed.size_, N2_SCAST(double, filecompressed.size_) / N2_SCAST(double, filecontent.size_) * 100.0);
				}
				else
				{
					fprintf(stdout, "  ファイル圧縮に失敗、元のファイルをそのまま使います\n");
				}
			}

			n2_str_t filepath;
			n2_str_init(&filepath);
			n2_str_copy_to(state, &filepath, &packfile->filepath_);
			n2_path_normalize(state, &filepath, N2_PATH_SEPARATOR_SLASH);

			fprintf(stdout, "  ファイルパス解決（%s） -> （%s）\n", packfile->filepath_.str_, filepath.str_);

			n2h_datatree_t* filetree = n2h_datatree_allocmap(state);
			n2h_datatree_set_bystr(state, filetree, "compress", SIZE_MAX, n2h_datatree_allocstr(state, compressformat, SIZE_MAX));
			n2h_datatree_set_bystr(state, filetree, "size", SIZE_MAX, n2h_datatree_alloci(state, N2_SCAST(int64_t, filecontent.size_)));
			n2h_datatree_set_bystr(state, filetree, "bin", SIZE_MAX, n2h_datatree_allocbin(state, usefilebin->data_, usefilebin->size_));
			n2h_datatree_set_bystr(state, fstree, filepath.str_, filepath.size_, filetree);

			n2_str_teardown(state, &filepath);

			n2_buffer_teardown(state, &filecompressed);
			n2_buffer_teardown(state, &filecontent);
		}

		n2h_datatree_set_bystr(state, datatree, "fs", SIZE_MAX, fstree);
		fstree = NULL;
	}

	// パックオプション
	{
		n2h_datatree_t* packoptstree = n2h_datatree_allocmap(state);

		const n2c_pp_packopt_t* packopts = &state->pp_context_->packopt_;
		n2h_datatree_set_bystr(state, packoptstree, "xsize", SIZE_MAX, n2h_datatree_alloci(state, N2_SCAST(n2_valint_t, packopts->xsize_)));
		n2h_datatree_set_bystr(state, packoptstree, "ysize", SIZE_MAX, n2h_datatree_alloci(state, N2_SCAST(n2_valint_t, packopts->ysize_)));
		n2h_datatree_set_bystr(state, packoptstree, "hide", SIZE_MAX, n2h_datatree_allocb(state, packopts->hide_));
		n2h_datatree_set_bystr(state, datatree, "packopts", SIZE_MAX, packoptstree);
		packoptstree = NULL;
	}

	// バイナリ化
	{
		// データツリーのバイナリ化
		n2_buffer_t databin;
		n2_buffer_init(&databin);
		if (!n2h_datatree_write_as_msgpack_to(state, &databin, datatree))
		{
			n2ai_show_error(opts, "スクリプトのバイナリエクスポートに失敗しました。");
			return N2_FALSE;
		}

		const uint32_t original_data_crc = n2h_crc32(databin.data_, databin.size_);

		// スクラッチ
		const n2_bool_t is_scratch = N2_TRUE;
		const uint64_t scratch_key = n2ri_ebin_scratch_key;
		if (is_scratch)
		{
			n2h_random_scratch(databin.data_, databin.size_, scratch_key);
		}

		// データを追加
		n2_buffer_append(state, dst, databin.data_, databin.size_);

		// ヘッダを書き込み
		n2h_binseq_header_t ebinheader;
		ebinheader.size_ = databin.size_;
		ebinheader.flags_ = 0 | (is_scratch ? N2H_BINSEQ_FLAG_SCRATCHED : 0);
		ebinheader.scratch_key_ = scratch_key;
		ebinheader.check_ = original_data_crc;
		n2h_binseq_write_signature(dst->data_, &ebinheader);

		n2_buffer_teardown(state, &databin);
	}

	return N2_TRUE;
}

// DAP用
static n2_bool_t n2ai_dap_staging_cwd_setfunc(n2r_dap_t* dap, const n2_str_t* cwd)
{
	return n2ri_change_cwd(dap->estate_, cwd);
}

static void n2ai_dap_staging_state_setupfunc(n2r_dap_t* dap, n2_state_config_t* state_config, const n2r_dap_launch_param_t* launch_param)
{
	N2_UNUSE(dap);
	N2_UNUSE(state_config);
	N2_UNUSE(launch_param);
}

static void n2ai_dap_staging_state_preloadfunc(n2r_dap_t* dap, n2_state_t* state, const n2r_dap_launch_param_t* launch_param)
{
	N2_UNUSE(launch_param);
	const n2a_dap_user_t* dapuser = N2_RCAST(const n2a_dap_user_t*, dap->user_);
	n2ai_apply_opts_to_state_bindings(state, dapuser->opts_);
}

// エントリーポイント
#define N2AI_BUILD_DEFAULT_FILENAME		"n2bin"
#define N2AI_EXPORT_DEFAULT_FILENAME	"nhsptmp"
#define N2AI_PACK_DEFAULT_FILENAME		"n2pack"

#define N2AI_MAX_INCLUDE_PATHS		(128)
static const char* n2ai_include_paths[N2AI_MAX_INCLUDE_PATHS] = {NULL};

#define N2AI_MAX_DEFINE_MACROS		(256)
static const char* n2ai_define_macros[N2AI_MAX_DEFINE_MACROS] = {NULL};

int main(int argc, char* argv[])
{
	n2ri_app_startup_console();

	n2a_options_t opts;
	n2a_options_init(&opts);

	// 容量が心配なのでstatic変数を使う
	opts.include_paths_ = n2ai_include_paths;
	opts.define_macros_ = n2ai_define_macros;

	// テスト用
#if N2RI_DEBUG
	{
		//opts.startup_script_ = "../demo/main.nhsp";

		//opts.mode_ = MODE_BUILD;
		//opts.mode_ = MODE_EXPORT;
		//opts.export_platform_ = PLATFORM_HTML;

		//opts.mode_ = MODE_COMPILE;
		//opts.success_dialog_ = N2_FALSE;
		//opts.error_dialog_ = N2_FALSE;
		//opts.formatted_output_ = N2_TRUE;

		//opts.mode_ = MODE_DEBUGADAPTER;
		//opts.da_timeout_msec_ = -1;
		//opts.da_logging_ = 1;

		//opts.include_paths_[opts.include_paths_count_++] = "./ipath";
		//opts.define_macros_[opts.define_macros_count_++] = "TESTDEF=12";
	}
#endif

	// コマンド引数
	{
		int parse_error = 0;
		const char* error_str = NULL;
		const char* error_subdesc = NULL;
		int print_help = 0;

		for (int a = 1; a < argc; ++a)
		{
			const char* label = argv[a];
			if (strcmp(label, "-D") == 0 || strcmp(label, "--define-macro") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for -D/--define-macro";
					parse_error = 1;
					break;
				}
				else
				{
					if (opts.define_macros_count_ < N2AI_MAX_INCLUDE_PATHS)
					{
						opts.define_macros_[opts.define_macros_count_++] = argv[a + 1];
					}
					else
					{
						error_str = "too many macros specified";
						parse_error = 1;
					}
					++a;
				}
			}
			else if (strcmp(label, "--da-logging") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --da-logging";
					parse_error = 1;
					break;
				}
				else
				{
					opts.da_logging_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--da-port") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --da-port";
					parse_error = 1;
					break;
				}
				else
				{
					opts.da_port_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--da-timeout") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --da-timeout";
					parse_error = 1;
					break;
				}
				else
				{
					opts.da_timeout_msec_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--error-dialog") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --error-dialog";
					parse_error = 1;
					break;
				}
				else
				{
					opts.error_dialog_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--export-allow-directory") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --export-allow-directory";
					parse_error = 1;
					break;
				}
				else
				{
					opts.export_allow_directory_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--export-platform") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --export-platform";
					parse_error = 1;
					break;
				}
				else
				{
					const char* arg = argv[a + 1];
					if (strcmp(arg, "native") == 0)
					{
						opts.export_platform_ = PLATFORM_NATIVE;
					}
					else if (strcmp(arg, "html") == 0)
					{
						opts.export_platform_ = PLATFORM_HTML;
					}
					else
					{
						error_str = "invalid argument for --export-platform";
						parse_error = 1;
						break;
					}
					++a;
				}
			}
			else if (strcmp(label, "--export-runtime-root") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --export-runtime-root";
					parse_error = 1;
					break;
				}
				else
				{
					opts.export_runtime_root_ = argv[a + 1];
					++a;
				}
			}
			else if (strcmp(label, "--formatted-output") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --formatted-output";
					parse_error = 1;
					break;
				}
				else
				{
					opts.formatted_output_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "-h") == 0 || strcmp(label, "--help") == 0)
			{
				print_help = 1;
			}
			else if (strcmp(label, "-i") == 0 || strcmp(label, "--startup-script") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for -i/--startup-script";
					parse_error = 1;
					break;
				}
				else
				{
					opts.startup_script_ = argv[a + 1];
					++a;
				}
			}
			else if (strcmp(label, "-I") == 0 || strcmp(label, "--include-path") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for -I/--include-path";
					parse_error = 1;
					break;
				}
				else
				{
					if (opts.include_paths_count_ < N2AI_MAX_INCLUDE_PATHS)
					{
						opts.include_paths_[opts.include_paths_count_++] = argv[a + 1];
					}
					else
					{
						error_str = "too many include paths specified";
						parse_error = 1;
					}
					++a;
				}
			}
			else if (strcmp(label, "-m") == 0 || strcmp(label, "--mode") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for -m/--mode";
					parse_error = 1;
					break;
				}
				else
				{
					const char* arg = argv[a + 1];
					if (strcmp(arg, "preview") == 0)
					{
						opts.mode_ = MODE_PREVIEW;
					}
					else if (strcmp(arg, "build") == 0)
					{
						opts.mode_ = MODE_BUILD;
					}
					else if (strcmp(arg, "export") == 0)
					{
						opts.mode_ = MODE_EXPORT;
					}
					else if (strcmp(arg, "pack") == 0)
					{
						opts.mode_ = MODE_PACK;
					}
					else if (strcmp(arg, "compile") == 0)
					{
						opts.mode_ = MODE_COMPILE;
					}
					else if (strcmp(arg, "debugadapter") == 0)
					{
						opts.mode_ = MODE_DEBUGADAPTER;
					}
					else
					{
						error_str = "invalid argument for -m/--mode";
						parse_error = 1;
						break;
					}
					++a;
				}
			}
			else if (strcmp(label, "-o") == 0 || strcmp(label, "--output-path") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for -o/--output-path";
					parse_error = 1;
					break;
				}
				else
				{
					opts.output_path_ = argv[a + 1];
					++a;
				}
			}
			else if (strcmp(label, "--output-root") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --output-root";
					parse_error = 1;
					break;
				}
				else
				{
					opts.output_root_ = argv[a + 1];
					++a;
				}
			}
			else if (strcmp(label, "--startup-binary") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --startup-binary";
					parse_error = 1;
					break;
				}
				else
				{
					opts.startup_binary_ = argv[a + 1];
					++a;
				}
			}
			else if (strcmp(label, "--success-dialog") == 0)
			{
				if (a + 1 >= argc)
				{
					error_str = "no argument for --success-dialog";
					parse_error = 1;
					break;
				}
				else
				{
					opts.success_dialog_ = strtol(argv[a + 1], NULL, 0);
					++a;
				}
			}
			else if (strcmp(label, "--use-inspector") == 0)
			{
			if (a + 1 >= argc)
			{
				error_str = "no argument for --use-inspector";
				parse_error = 1;
				break;
			}
			else
			{
				opts.use_inspector_ = strtol(argv[a + 1], NULL, 0);
				++a;
			}
			}
			else if (strcmp(label, "--verbose") == 0)
			{
			opts.verbose_ = 1;
			}
			else if (strcmp(label, "--") == 0)
			{
				opts.passthrough_begin_ = a + 1;
				break;
			}
			else
			{
				error_str = "unknown argument detected";
				error_subdesc = argv[a];
				parse_error = 1;
				break;
			}
		}

		if (parse_error)
		{
			fprintf(stderr, "%s\n", error_str ? error_str : "error detected");
			if (error_subdesc)
			{
				fprintf(stderr, "    %s\n", error_subdesc);
			}
			fflush(stderr);
		}

		if (parse_error || print_help)
		{
			fprintf(stdout,
				"USAGE: \n"
				"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
				"  -m/--mode <mode>\n"
				"    specify command mode\n"
				"    <mode> must be one of the followings\n"
				"      - preview       : execute input script\n"
				"      - build         : build script binary\n"
				"      - export        : build and export as native executable file or HTML\n"
				"      - pack          : pack files\n"
				"      - compile       : compile script to check errors\n"
				"      - debugadapter  : debugadapter mode\n"
				"  -i/--startup-script <filepath>\n"
				"    script file for preview mode\n"
				"    default startup script filepath is \"main.nhsp\"\n"
				"  --output-root <outputroot>\n"
				"    output root directory path for build/export/pack mode\n"
				"    this option is inferior to the -o/--output-path option\n"
				"  -o/--output-path <outputpath>\n"
				"    output file path for build/export/pack mode\n"
				"      export mode only) if this option is specified, output filename which script specified with #cmpopt will be ignored\n"
				"    if both --output-root and this option are unspecified, the actual output path will be as followings\n"
				"      \"" N2AI_BUILD_DEFAULT_FILENAME "\" for build\n"
				"      \"" N2AI_EXPORT_DEFAULT_FILENAME "[.exe]\" for export\n"
				"      \"" N2AI_PACK_DEFAULT_FILENAME "\" for pack"
				"  --error-dialog <1 or 0>\n"
				"    enable/disable show dialog on error\n"
				"    when disabled, print error message to stderr instead\n"
				"    default value is 1(enabled)\n"
				"  --success-dialog <1 or 0>\n"
				"    enable/disable show dialog on success\n"
				"    when disabled, print message to stdout instead\n"
				"    default value is 0(disabled)\n"
				"  -I/--include-path <include_path>\n"
				"    add include path\n"
				"  -D/--define-macro <macroName[=macroContent]>\n"
				"    add macro to be used in preprocessor\n"
				"  -h/--help\n"
				"    show this help\n"
				"  --verbose\n"
				"    verbose logging mode\n"
				"  -- [arguments ...]\n"
				"    pass through all following arguments\n"
				"    to latter command(such as preview script)\n"
				"  --formatted-output <1 or 0>\n"
				"    for internal use\n"
				"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
				"  --startup-binary <filepath>\n"
				"    prebuilt-binary file for preview mode\n"
				"    when this parameter specified, --startup-script argument\n"
				"    will be ignored\n"
				"    * NOT SUPPORTED YET\n"
				"  --preview-error-dialog <1 or 0>\n"
				"    enable/disable error dialog on preview\n"
				"  --use-inspector <1 or 0>\n"
				"    enable/disable inspector on preview\n"
				"    default value is 1\n"
				"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
				"  --export-platform <platform>\n"
				"    platform for export mode\n"
				"    <platform> must be one of the followings\n"
				"      - native : export as native platform executable file\n"
				"      - html   : export as HTML\n"
				"    default platform is \"native\"\n"
				"  --export-runtime-root <path>\n"
				"    runtime file root directory path\n"
				"    default value is \"runtime\"\n"
				"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
				"  --da-port <port>\n"
				"    TCP port for debugadapter mode\n"
				"    debugadapter will listen specified port\n"
				"    default value is 9022\n"
				"  --da-timeout <timeout in milliseconds>\n"
				"    timeout for debugadapter mode\n"
				"    default value is 10 * 1000\n"
				"    specify -1 to wait inifinitely\n"
				"  --da-logging <1 or 0>\n"
				"    enable/disable output all send/receive messages over DAP to stdout\n"
				"    default value is 0\n"
			);
			fflush(stdout);
			return parse_error ? n2ri_error_exit_code : 0;
		}
	}

	// 一部補正

	// 空なら指定なしと同じ
	if (opts.output_root_ && opts.output_root_[0] == '\0') { opts.output_root_ = NULL; }
	if (opts.output_path_ && opts.output_path_[0] == '\0') { opts.output_path_ = NULL; }

	// モード別
	int exit_code = 0;
	switch (opts.mode_)
	{
	case MODE_PREVIEW:
	case MODE_BUILD:
	case MODE_EXPORT:
		{
			n2_state_config_t config;
			n2_state_config_init(&config);

			{
				// エラーを全て吸収
				config.print_error_ = n2ai_print_error_func;
				config.error_ = n2ai_error_func;
				config.standard_use_inspector_ = opts.use_inspector_ ? N2_TRUE : N2_FALSE;
			}

			n2_state_t* state = n2_state_alloc(&config);

#if N2RI_DEBUG && 1
			{
				n2_str_t relpath;
				n2_str_init(&relpath);
				n2_str_set(state, &relpath, "../demo", SIZE_MAX);
				n2ri_change_cwd(state, &relpath);
				n2_str_teardown(state, &relpath);
			}
#endif

			n2_state_bind_basics(state);
			n2_state_bind_standards(state);
			n2ai_apply_opts_to_state_bindings(state, &opts);

			n2_str_t script;
			n2_str_init(&script);
			if (opts.startup_binary_)
			{
				n2_str_t startup_binary_str;
				n2_str_init(&startup_binary_str);
				n2_str_set(state, &startup_binary_str, opts.startup_binary_, SIZE_MAX);
				n2_buffer_t ebin = n2ri_load_raw_file(state, &startup_binary_str);
				n2_str_teardown(state, &startup_binary_str);

				n2h_msgpack_element_t* ebinsys = n2h_msgpack_parse(state, ebin.data_, ebin.size_);
				if (!ebinsys || ebinsys->type_ != N2H_MSGPACK_TYPE_MAP)
				{
					n2ai_show_error(&opts, "スタートアップバイナリ（%s）が読み込めません。", opts.startup_binary_);
					exit(n2ri_error_exit_code);
				}

				if (!n2ri_extract_script_from_ebinsys(state, &script, ebinsys))
				{
					n2ai_show_error(&opts, "不正なスタートアップバイナリ（%s）です。", opts.startup_binary_);
					exit(n2ri_error_exit_code);
				}
			}
			else
			{
				FILE* scriptfile = fopen(opts.startup_script_, "rt");
				if (!scriptfile)
				{
					n2ai_show_error(&opts, "スクリプトファイル（%s）が読み込めません。", opts.startup_script_);
					exit(n2ri_error_exit_code);
				}

				n2_str_t tmpbuf;
				n2_str_init(&tmpbuf);
				n2_str_reserve(state, &tmpbuf, 16 * 1024);
				for (;;)
				{
					if (!fgets(tmpbuf.str_, N2_SCAST(int, tmpbuf.buffer_size_), scriptfile)) { break; }
					n2_str_append(state, &script, tmpbuf.str_, SIZE_MAX);
					if (feof(scriptfile) || ferror(scriptfile)) { break; }
				}
				fclose(scriptfile);
			}

			// エラーをバッファ
			n2_str_init(&n2ai_state_print_error_merged);
			n2ai_state_print_errors = n2_plstrarray_alloc(state, 16, 16);

			const n2_bool_t load_succeeded = n2_state_load_str(state, NULL, script.str_, n2_str_compute_size(&script), opts.startup_binary_ ? NULL : opts.startup_script_);

			if (!load_succeeded)
			{
				if (opts.formatted_output_)
				{
					n2ai_error_dump(&opts);
				}
				else
				{
					n2ai_print_error_merge_and_clear(state, NULL);
					n2ai_show_error(&opts, "スクリプトのロードに失敗しました。\n################################\n%s", n2ai_state_print_error_merged.str_);
				}
				exit(n2ri_error_exit_code);
			}

			switch (opts.mode_)
			{
			case MODE_PREVIEW:
				{
					// プレビュー実行
#if N2RI_DEBUG
					//n2_codeimage_dump(state, state->environment_->codeimage_, state->environment_, N2_CODEIMAGE_DUMP_DEFAULT);
#endif

					n2ri_apply_packopt_from_ppc(state);// プリプロセス結果から適用できるオプションを適用

					for (;;)
					{
						n2_fiber_t* f = state->main_fiber_;

						// スクリプトの初回起動または中断
						if (f->fiber_state_ == N2_FIBER_STATE_INITIALIZED || f->fiber_state_ == N2_FIBER_STATE_YIELD_AWAIT)
						{
							if (!n2_state_execute(state))
							{
								n2ai_print_error_merge_and_clear(state, NULL);
								n2ai_show_error(&opts, "スクリプト実行中にエラーが発生しました。\n################################\n%s", n2ai_state_print_error_merged.str_);
								exit_code = n2ri_error_exit_code;
								break;
							}
						}

						if (!n2_state_loop_frame(state) || n2_state_is_quit_requested(state) || n2_fiber_is_finished(f))
						{
							exit_code = f->exit_code_;
							break;
						}

						// await状態の待ち
						if (!n2_state_do_frame_loop_yield_wait(state, f))
						{
							// 待ちが存在しないので適当な待ちを入れる
							SDL_Delay(n2ri_default_frame_delay);
						}
					}
				}
				break;
			case MODE_BUILD:
				{
					// ビルド
					n2_buffer_t ebin;
					n2_buffer_init(&ebin);
					if (!n2ai_build_ebinary(state, &ebin, &opts)) { exit(n2ri_error_exit_code); }

					// 埋め込みバイナリヘッダ
					n2_buffer_insert(state, &ebin, 0, n2ri_embed_binary_head, sizeof(n2ri_embed_binary_head));

					{
						n2_str_t output_path;
						n2_str_init(&output_path);
						if (opts.output_path_)
						{
							n2_str_set(state, &output_path, opts.output_path_, SIZE_MAX);
						}
						else if (opts.output_root_)
						{
							n2_path_join(state, &output_path, opts.output_root_, SIZE_MAX, N2AI_BUILD_DEFAULT_FILENAME, SIZE_MAX);
						}
						else
						{
							n2_str_set(state, &output_path, N2AI_BUILD_DEFAULT_FILENAME, SIZE_MAX);
						}

						FILE* outfile = fopen(output_path.str_, "wb");
						if (!outfile)
						{
							n2ai_show_error(&opts, "出力先ファイル（%s）のオープンに失敗しました。", output_path.str_);
							exit(n2ri_error_exit_code);
						}

						fwrite(ebin.data_, 1, ebin.size_, outfile);

						fclose(outfile);

						n2ai_show_success(&opts, "バイナリファイル（%s）をエクスポートしました", output_path.str_);

						n2_str_teardown(state, &output_path);
					}
				}
				break;
			case MODE_EXPORT:
				{
					// エクスポート
					n2_buffer_t ebin;
					n2_buffer_init(&ebin);
					if (!n2ai_build_ebinary(state, &ebin, &opts)) { exit(n2ri_error_exit_code); }

					// 出力パス
					n2_str_t output_path;
					n2_str_init(&output_path);
					n2_str_t output_filename;
					n2_str_init(&output_filename);

					if (opts.output_path_)
					{
						n2_str_set(state, &output_path, opts.output_path_, SIZE_MAX);
					}
					else
					{
						if (opts.verbose_)
						{
							fprintf(stdout, "出力先フルパスが指定されていなかったため、出力先ルート等から自動計算\n");
						}

						// ファイル名
						if (state->pp_context_->packopt_.name_.size_ > 0)
						{
							n2_str_copy_to(state, &output_filename, &state->pp_context_->packopt_.name_);
						}
						else
						{
							n2_str_set(state, &output_filename, N2AI_EXPORT_DEFAULT_FILENAME, SIZE_MAX);
						}

						if (opts.verbose_)
						{
							fprintf(stdout, "出力先ファイル名＝%s\n", output_filename.str_);
						}

						// フルパス
						if (opts.output_root_)
						{
							n2_path_join(state, &output_path, opts.output_root_, SIZE_MAX, output_filename.str_, SIZE_MAX);
						}
						else
						{
							n2_str_copy_to(state, &output_path, &output_filename);
						}

						if (opts.verbose_)
						{
							fprintf(stdout, "出力先パス＝%s\n", output_path.str_);
						}

						// 拡張子
						if (n2_str_find(&output_filename, ".", 1, 0) < 0)
						{
							switch (opts.export_platform_)
							{
							case PLATFORM_NATIVE:
								n2_str_append(state, &output_path, N2RI_PLATFORM_EXE_SUFFIX, SIZE_MAX);
								break;
							case PLATFORM_HTML:
								if (opts.export_allow_directory_)
								{
									n2_str_append(state, &output_path, "/", SIZE_MAX);
								}
								else
								{
									n2_str_append(state, &output_path, ".zip", SIZE_MAX);
								}
								break;
							default:
								break;
							}

							if (opts.verbose_)
							{
								fprintf(stdout, "出力先パス拡張子付加＝%s\n", output_path.str_);
							}
						}
					}

					//if (opts.verbose_)
					{
						fprintf(stdout, "出力先パス＝%s\n", output_path.str_);
					}

					// 埋め込みバイナリヘッダ
					n2_buffer_insert(state, &ebin, 0, n2ri_embed_binary_head, sizeof(n2ri_embed_binary_head));

					// どの形式でエクスポートするか
					n2_str_t runtime_path;
					n2_str_init(&runtime_path);

					n2_buffer_t tmpbuf;
					n2_buffer_init(&tmpbuf);
					n2_buffer_reserve(state, &tmpbuf, 1 * 1024 * 1024);

					switch (opts.export_platform_)
					{
					case PLATFORM_NATIVE:
						{
							n2_str_fmt_to(state, &runtime_path, "%s/%s", opts.export_runtime_root_, "n2r_std" N2RI_PLATFORM_EXE_SUFFIX);

							// 書き込み
							{
								FILE* runtimefile = fopen(runtime_path.str_, "rb");
								if (!runtimefile)
								{
									n2ai_show_error(&opts, "ランタイムファイル（%s）のオープンに失敗しました。", runtime_path.str_);
									exit(n2ri_error_exit_code);
								}

								FILE* outfile = fopen(output_path.str_, "wb");
								if (!outfile)
								{
									n2ai_show_error(&opts, "出力先ファイル（%s）のオープンに失敗しました。", output_path.str_);
									exit(n2ri_error_exit_code);
								}

								while (!feof(runtimefile))
								{
									const size_t read = fread(tmpbuf.data_, 1, tmpbuf.buffer_size_, runtimefile);
									if (read <= 0) { break; }
									fwrite(tmpbuf.data_, 1, read, outfile);
								}

								fwrite(ebin.data_, 1, ebin.size_, outfile);

								fclose(runtimefile);
								fclose(outfile);
							}

							// アイコン
							if (state->pp_context_->packopt_.icon_.size_ > 0)
							{
								n2_buffer_t iconfile = n2ri_load_raw_file(state, &state->pp_context_->packopt_.icon_);

								if (iconfile.size_ > 0)
								{
#if N2_PLATFORM_IS_WINDOWS && 0
									// @todo
									n2_bool_t icon_rewrite_success = N2_FALSE;
									n2_str_t outsys;
									n2_str_init(&outsys);
									if (n2ri_win_to_system_string(state, &outsys, &output_path))
									{
										HANDLE reshandle = BeginUpdateResourceW(N2_RCAST(LPCWSTR, outsys.str_), FALSE);
										if (reshandle != NULL)
										{
											icon_rewrite_success = N2_TRUE;
											if (!UpdateResourceW(reshandle, N2_RCAST(LPCWSTR, RT_GROUP_ICON), L"MAINICON", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), iconfile.data_, N2_SCAST(DWORD, iconfile.size_)))
											{
												icon_rewrite_success = N2_FALSE;
											}
											if (!EndUpdateResourceW(reshandle, FALSE))
											{
												icon_rewrite_success = N2_FALSE;
											}
										}

										icon_rewrite_success = N2_TRUE;
									}

									if (icon_rewrite_success)
									{
										fprintf(stdout, "アイコンファイルの書き換えに成功。\n");
									}
									else
									{
										fprintf(stdout, "アイコンファイルの書き換えに失敗、アイコン書き換えをスキップ。\n");
									}
#else
									fprintf(stdout, "アイコンファイルの書き換えに対応していないプラットフォームのため、アイコン書き換えをスキップ。\n");
#endif
								}
								else
								{
									fprintf(stderr, "アイコンファイルの書き換えに失敗：アイコンファイル（%s）が読み込めません。\n", state->pp_context_->packopt_.icon_.str_);
								}
							}

							{
								n2ai_show_success(&opts, "ネイティブファイル（%s）へエクスポートしました", output_path.str_);
							}
						}
						break;

					case PLATFORM_HTML:
						{
							n2_str_fmt_to(state, &runtime_path, "%s/html", opts.export_runtime_root_);

							const n2_bool_t export_as_dir = n2_str_ends_with(&output_path, "/", 1) || n2_str_ends_with(&output_path, "\\", 1);

							//if (opts.verbose_)
							{
								fprintf(stdout, "HTMLエクスポート：%s として出力します\n", export_as_dir ? "ディレクトリ" : "ZIPファイル");
							}

							// zip化
							n2h_zip_t* zip = NULL;
							if (!export_as_dir) { zip = n2h_zip_alloc(state); }

							if (zip) { n2h_zip_openw_to(state, zip); }

							// 必要なファイルを詰める
							n2_bool_t file_pack_ok = N2_TRUE;

							{
								const char* required_files[] = {
									"n2r_std.html",
									"n2r_std.js",
									"n2r_std.wasm",
									NULL
								};
								n2_str_t input_path;
								n2_str_init(&input_path);
								for (size_t i = 0; required_files[i]; ++i)
								{
									const char* filepath = required_files[i];
									n2_str_fmt_to(state, &input_path, "%s/%s", runtime_path.str_, filepath);

									n2_buffer_t inputfilebuf = n2ri_load_raw_file(state, &input_path);
									if (inputfilebuf.size_ <= 0)
									{
										n2ai_show_error(&opts, "ランタイムの入力ファイル（%s）が読み込めません", input_path.str_);
										exit(n2ri_error_exit_code);
									}

									if (zip)
									{
										if (!n2h_zip_add_to(state, zip, filepath, inputfilebuf.data_, inputfilebuf.size_, N2_ZIP_COMPRESS_SPEED))
										{
											file_pack_ok = N2_FALSE;
											break;
										}
									}
									else
									{
										// ファイル出力
										n2_str_t outfile_path;
										n2_str_init(&outfile_path);
										n2_path_join(state, &outfile_path, output_path.str_, SIZE_MAX, filepath, SIZE_MAX);

										FILE* outfile = fopen(output_path.str_, "wb");
										if (!outfile)
										{
											n2ai_show_error(&opts, "出力先ファイル（%s）のオープンに失敗しました。", outfile_path.str_);
											exit(n2ri_error_exit_code);
										}

										fwrite(inputfilebuf.data_, 1, inputfilebuf.size_, outfile);
										fclose(outfile);

										n2_str_teardown(state, &outfile_path);
									}

									n2_buffer_teardown(state, &inputfilebuf);
								}
							}

							// 埋め込みバイナリ
							if (zip)
							{
								if (!n2h_zip_add_to(state, zip, n2ri_embed_binary_name, ebin.data_, ebin.size_, N2_ZIP_COMPRESS_SPEED))
								{
									file_pack_ok = N2_FALSE;
								}
							}
							else
							{
								// ファイル出力
								n2_str_t outfile_path;
								n2_str_init(&outfile_path);
								n2_path_join(state, &outfile_path, output_path.str_, SIZE_MAX, n2ri_embed_binary_name, SIZE_MAX);

								FILE* outfile = fopen(outfile_path.str_, "wb");
								if (!outfile)
								{
									n2ai_show_error(&opts, "出力先ファイル（%s）のオープンに失敗しました。", outfile_path.str_);
									exit(n2ri_error_exit_code);
								}

								fwrite(ebin.data_, 1, ebin.size_, outfile);
								fclose(outfile);

								n2_str_teardown(state, &outfile_path);
							}

							if (zip && !file_pack_ok)
							{
								n2ai_show_error(&opts, "ランタイムバイナリのZIPパッキングに失敗");
								exit(n2ri_error_exit_code);
							}

							// ZIP出力
							if (zip)
							{
								n2_buffer_t zip_out_buf;
								n2_buffer_init(&zip_out_buf);
								n2h_zip_writedown_and_close(state, zip, &zip_out_buf);
								n2h_zip_free(state, zip);

								if (zip_out_buf.size_ <= 0)
								{
									n2ai_show_error(&opts, "ランタイムバイナリのZIP生成に失敗");
									exit(n2ri_error_exit_code);
								}

								// ファイルへ出力
								{
									FILE* outfile = fopen(output_path.str_, "wb");
									if (!outfile)
									{
										n2ai_show_error(&opts, "出力先ファイル（%s）のオープンに失敗しました。", output_path.str_);
										exit(n2ri_error_exit_code);
									}

									fwrite(zip_out_buf.data_, 1, zip_out_buf.size_, outfile);
									fclose(outfile);
								}
							}

							{
								n2ai_show_success(&opts, "HTMLファイル（%s）へエクスポートしました", output_path.str_);
							}
						}
						break;

					default:
						N2_ASSERT(0);
						break;
					}

					n2_buffer_teardown(state, &tmpbuf);

					n2_str_teardown(state, &output_filename);
					n2_str_teardown(state, &output_path);
					n2_str_teardown(state, &runtime_path);

					n2_buffer_teardown(state, &ebin);
				}
				break;
			default:
				break;
			}

			n2_str_teardown(state, &script);

			n2ai_print_error_reset(state);
			n2ai_error_reset();

			n2_state_free(state);
		}
		break;

	case MODE_PACK:
		// パック
		n2ai_show_error(&opts, "PACK mode is not supported yet...");
		exit_code = n2ri_error_exit_code;
		break;

	case MODE_COMPILE:
		// コンパイルチェック
		{
			n2_state_config_t config;
			n2_state_config_init(&config);

			{
				// エラーを全て吸収
				config.print_error_ = n2ai_print_error_func;
				config.error_ = n2ai_error_func;
				config.standard_use_inspector_ = opts.use_inspector_ ? N2_TRUE : N2_FALSE;
			}

			n2_state_t* state = n2_state_alloc(&config);

			n2_state_bind_basics(state);
			n2_state_bind_standards(state);
			n2ai_apply_opts_to_state_bindings(state, &opts);

			n2_str_t script;
			n2_str_init(&script);
			{
				FILE* scriptfile = fopen(opts.startup_script_, "rt");
				if (!scriptfile)
				{
					n2ai_show_error(&opts, "スクリプトファイル（%s）が読み込めません。", opts.startup_script_);
					exit(n2ri_error_exit_code);
				}

				n2_str_t tmpbuf;
				n2_str_init(&tmpbuf);
				n2_str_reserve(state, &tmpbuf, 16 * 1024);
				for (;;)
				{
					if (!fgets(tmpbuf.str_, N2_SCAST(int, tmpbuf.buffer_size_), scriptfile)) { break; }
					n2_str_append(state, &script, tmpbuf.str_, SIZE_MAX);
					if (feof(scriptfile) || ferror(scriptfile)) { break; }
				}
				fclose(scriptfile);
			}

			// エラーをバッファ
			n2_str_init(&n2ai_state_print_error_merged);
			n2ai_state_print_errors = n2_plstrarray_alloc(state, 16, 16);

			const n2_bool_t load_succeeded = n2_state_load_str(state, NULL, script.str_, n2_str_compute_size(&script), opts.startup_binary_ ? NULL : opts.startup_script_);

			if (load_succeeded)
			{
				fprintf(stdout, "コンパイル成功\n");
			}
			else
			{
				fprintf(stderr, "コンパイル失敗\n");

				if (opts.formatted_output_)
				{
					n2ai_error_dump(&opts);
				}
				else
				{
					n2ai_print_error_merge_and_clear(state, NULL);
					n2ai_show_error(&opts, "スクリプトのロードに失敗しました。\n################################\n%s", n2ai_state_print_error_merged.str_);
				}
				exit_code = n2ri_error_exit_code;
			}

			n2_str_teardown(state, &script);

			n2ai_print_error_reset(state);
			n2ai_error_reset();

			n2_state_free(state);
		}
		break;

	case MODE_DEBUGADAPTER:
		// デバッグアダプター
		{
			// 開始
			n2_state_config_t econfig;
			n2_state_config_init(&econfig);
			{
				// 外側はエラー等プリントは握り潰し
				econfig.print_ = NULL;
				econfig.print_log_ = NULL;
				econfig.print_error_ = NULL;
			}

			n2_state_t* estate = n2_state_alloc(&econfig);
			n2r_dap_t* dap = n2r_dap_alloc(estate);

			// dapのコンフィグ
			dap->enable_dap_logging_ = opts.da_logging_ ? N2_TRUE : N2_FALSE;
			dap->staging_cwd_setfunc_ = n2ai_dap_staging_cwd_setfunc;
			dap->staging_state_setupfunc_ = n2ai_dap_staging_state_setupfunc;
			dap->staging_state_preloadfunc_ = n2ai_dap_staging_state_preloadfunc;

			n2a_dap_user_t dapuser;
			dapuser.opts_ = &opts;
			dap->user_ = &dapuser;

			const Uint64 launched_counter = SDL_GetPerformanceCounter();

			// dap待ち受け
			if (n2r_dap_open(dap, opts.da_port_))
			{
				for (;;)
				{
					// ステージング更新
					if (dap->staging_state_)
					{
						// 更新処理
						if (dap->staging_configuration_done_)
						{
							n2_state_t* state = dap->staging_state_;
							n2_fiber_t* f = state->main_fiber_;

							// スクリプトの初回起動または中断
							if (f->fiber_state_ == N2_FIBER_STATE_INITIALIZED || f->fiber_state_ == N2_FIBER_STATE_YIELD_AWAIT)
							{
								if (!n2_state_execute(state))
								{
									n2ai_print_error_merge_and_clear(state, NULL);
									// dapでハンドリングされているならスルー
									if (!dap->staging_state_launched_by_dap_ || dap->staging_state_launch_param_.no_debug_)
									{
										n2ai_show_error(&opts, "スクリプト実行中にエラーが発生しました。\n################################\n%s", n2ai_state_print_error_merged.str_);
									}
									// 終了へ
									dap->servertoclose_ = N2_TRUE;
									exit_code = n2ri_error_exit_code;
								}
							}

							if (!n2_state_loop_frame(state) || n2_state_is_quit_requested(state) || n2_fiber_is_finished(f))
							{
								// 終了へ
								dap->servertoclose_ = N2_TRUE;
								exit_code = f->exit_code_;
							}

							// await状態の待ち
							if (!n2_state_do_frame_loop_yield_wait(state, f))
							{
								// 待ちが存在しないので適当な待ちを入れる
								SDL_Delay(n2ri_default_frame_delay);
							}
						}

						// 既に接続がきれているなら
						if (!dap->serveropen_)
						{
							// ステージングも解放（これがループ終了条件）
							n2r_dap_reset_staging_state(dap);
						}
					}

					// 接続待ち？
					if (opts.da_timeout_msec_ >= 0 && dap->accepted_count_ <= 0/*一回も接続されてないなら*/)
					{
						// タイムアウトでサーバークローズ
						const Uint64 elapsed_msec_from_launched = (SDL_GetPerformanceCounter() - launched_counter) * 1000/*ms*/ / SDL_GetPerformanceFrequency();
						if (elapsed_msec_from_launched > N2_SCAST(Uint64, opts.da_timeout_msec_))
						{
							fprintf(stdout, "server accept TIMEOUT, closing listen port ...\n");
							dap->servertoclose_ = N2_TRUE;
						}
					}

					// サーバー更新
					{
						n2ri_dap_poll_once(dap);
						n2r_dap_updatable(dap, N2_TRUE);
					}

					// サーバーが閉じられていて、ステージングもないなら抜ける
					if (!dap->serveropen_ && !dap->staging_state_) { break; }
				}
			}
			else
			{
				fprintf(stderr, "failed opening TCP port(%d) to listen.", opts.da_port_);
			}

			// 終了
			n2r_dap_free(dap);
			n2_state_free(estate);
		}
		break;

	default:
		break;
	}

	return exit_code;
}

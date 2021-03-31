
#include <nidonehsp.h>
#include "app.h"

#include <stdio.h>
#include <stdarg.h>

#if N2R_CONFIG_RUNTIME_STANDARD
#include <SDL.h>
#endif

#define N2RI_DEBUG			(0)

#if N2RI_DEBUG && 0
#define N2RI_DPRINT(...) \
	printf(__VA_ARGS__)
#else
#define N2RI_DPRINT(...)
#endif

static void show_error_simple(n2_state_t* state, const char* fmt, ...)
{
	n2_str_t message;
	n2_str_init(&message);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &message, fmt, args);
	va_end(args);
#if N2R_CONFIG_RUNTIME_STANDARD
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", message.str_, NULL);
#else
	fprintf(stderr, "%s\n", message.str_);
#endif
	n2_str_teardown(state, &message);
}

static n2_str_t get_app_path(n2_state_t* state)
{
	n2_str_t app_path;
	n2_str_init(&app_path);
#if N2RI_DEBUG && 0
	{
		n2_str_set(state, &app_path, "n2bin", SIZE_MAX);
	}
#elif N2_PLATFORM_IS_WINDOWS
	{
		wchar_t wapp_path[MAX_PATH * 4];// これぐらいはスタックあるだろう
		if (GetModuleFileNameW(NULL, wapp_path, sizeof(wapp_path)) > 0)
		{
			const int required = WideCharToMultiByte(CP_UTF8, 0, wapp_path, -1, NULL, 0, NULL, NULL);
			if (required > 0)
			{
				n2_str_reserve(state, &app_path, N2_SCAST(size_t, required) + 4);
				WideCharToMultiByte(CP_UTF8, 0, wapp_path, -1, app_path.str_, N2_SCAST(int, app_path.buffer_size_), NULL, NULL);
				n2_str_update_size(&app_path);
			}
		}
	}
#elif N2_PLATFORM_IS_EMSCRIPTEN
	{
		n2_str_set(state, &app_path, n2ri_em_ebin_path, SIZE_MAX);
	}
#elif N2_PLATFORM_IS_UNIX
	{
		n2_str_set(state, &app_path, "/proc/self/exe", SIZE_MAX);
	}
#else
	N2_UNUSE(state);
#endif
	return app_path;
}

static n2_buffer_t extract_embed_binary(n2_state_t* state, void** embed_base, size_t* embed_size)
{
	n2_buffer_t ebin_holder;
	n2_buffer_init(&ebin_holder);

	n2_str_t app_path = get_app_path(state);
	N2RI_DPRINT("app_path=%s\n", app_path.str_);
	if (app_path.size_ > 0)
	{
		n2_buffer_t app_image = n2ri_load_raw_file(state, &app_path);
		N2RI_DPRINT("app_image=%zu\n", app_image.size_);

		size_t magic_size = 0;
		const uint8_t* magic = n2h_binseq_magic(&magic_size);
		if (magic && magic_size > 0)
		{
			size_t search_offset = 0;
			while (search_offset < app_image.size_)
			{
				N2RI_DPRINT("searching...=%zu\n", search_offset);
				void* found = memchr(n2_cptr_offset(app_image.data_, search_offset), n2ri_embed_binary_head[0], app_image.size_ - search_offset);
				if (!found) { break; }

				const size_t found_offset = N2_SCAST(size_t, n2_ptr_diff(found, app_image.data_));
				N2_ASSERT(found_offset < app_image.size_);
				N2RI_DPRINT("found_offset=%zu\n", found_offset);

				search_offset = found_offset + 1;

				const size_t remain_size = app_image.size_ - found_offset;
				if (remain_size <= sizeof(n2ri_embed_binary_head) || memcmp(found, n2ri_embed_binary_head, sizeof(n2ri_embed_binary_head))) { continue; }

				// and is it header of binseq ?
				const size_t remain_binseq_size = remain_size - sizeof(n2ri_embed_binary_head);
				const size_t binsigsize = n2h_binseq_signature_size();

				if (remain_binseq_size < binsigsize) { continue; }
				N2RI_DPRINT("passed binseq size=%zu\n", remain_binseq_size);

				void* binseq_head = n2_ptr_offset(found, sizeof(n2ri_embed_binary_head));
				if (!n2h_binseq_verify(binseq_head, remain_binseq_size)) { continue; }
				N2RI_DPRINT("passed binseq_verify\n");

				n2h_binseq_header_t binheader;
				if (!n2h_binseq_get_header(&binheader, binseq_head, remain_binseq_size)) { continue; }
				N2RI_DPRINT("got binseq size=%llu\n", binheader.size_);

				if (remain_binseq_size < binsigsize + binheader.size_) { continue; }

				void* payload = n2_ptr_offset(binseq_head, binsigsize);
				const size_t payload_size = binheader.size_;

				// unscratch
				if (binheader.flags_ & N2H_BINSEQ_FLAG_SCRATCHED)
				{
					N2RI_DPRINT("unscratch=%lld\n", binheader.scratch_key_);
					n2h_random_scratch(payload, payload_size, binheader.scratch_key_);
				}

				// crc check
				const uint32_t check = n2h_crc32(payload, payload_size);
				if (check != binheader.check_) { continue; }
				N2RI_DPRINT("passed crc check=%u\n", binheader.check_);

				// OK
				*embed_base = payload;
				*embed_size = payload_size;
				n2_buffer_swap(&app_image, &ebin_holder);
				break;
			}
		}

		n2_buffer_teardown(state, &app_image);
	}

	n2_str_teardown(state, &app_path);
	return ebin_holder;
}

// メインループ
typedef struct n2ri_mainloop_context_t n2ri_mainloop_context_t;
struct n2ri_mainloop_context_t
{
	n2_state_t* state_;
	int exit_code_;
};

static void n2ri_mainloop_shutdown()
{
#if N2_PLATFORM_IS_EMSCRIPTEN
	// main_loopをキャンセル（もういらない）
	emscripten_cancel_main_loop();
#endif
}

static void n2ri_mainloop(void* user)
{
	n2ri_mainloop_context_t* context = N2_RCAST(n2ri_mainloop_context_t*, user);
	n2_state_t* state = context->state_;
	n2_fiber_t* f = context->state_->main_fiber_;

	// 既に終了しているなら何もしない
	if (n2_fiber_is_finished(f)) { return; }

	// スクリプトの初回起動または中断
	if (f->fiber_state_ == N2_FIBER_STATE_INITIALIZED || f->fiber_state_ == N2_FIBER_STATE_YIELD_AWAIT)
	{
		if (!n2_state_execute(state))
		{
			show_error_simple(state, "スクリプト実行中にエラーが発生しました。");
			context->exit_code_ = n2ri_error_exit_code;
			n2ri_mainloop_shutdown();
		}
	}

	// フレーム更新
	if (!n2_state_loop_frame(context->state_)) { return; }

	// await状態の待ち
	n2ri_do_frame_loop_yield_wait(state, f);
}

// スタートアップ
static void n2ri_startup()
{
#if N2_PLATFORM_IS_EMSCRIPTEN
	// IDBFSをマウント
	EM_ASM_
	(
		{
			var idbfsroot = UTF8ToString($0);
			FS.mkdirTree(idbfsroot);
			FS.mount(IDBFS, {}, idbfsroot);
			FS.syncfs(true, function(e) {});
		}, n2ri_em_idbfs_root
	);

	// 埋め込みバイナリをマウント…は既にprejsでされてる筈
#endif
}

// エントリーポイント
int main(int argc, char* argv[])
{
	N2_UNUSE(argc);
	N2_UNUSE(argv);

	// スタートアップ
	n2ri_startup();

	// コンフィグ
	n2_state_config_t config;
#if N2RI_DEBUG && 0
	n2_state_config_init_ex(&config, N2_STATE_CONFIG_FLAG_NO_RPMALLOC);
#else
	n2_state_config_init_ex(&config, N2_STATE_CONFIG_FLAG_DEFAULT);
#endif

	// ランタイム用コンフィグ
	{
#if !N2RI_DEBUG || 0
		config.error_is_print_ = N2_FALSE;
		config.print_ = NULL;
		config.print_log_ = NULL;
		config.print_error_ = NULL;
#endif
		config.generate_codelines_ = N2_FALSE;// ソースコードデバッグ情報を生成しない
		config.generate_debugvars_ = N2_FALSE;// DebugVarも同様（元々無効化されているが）
		config.max_message_log_ = 0;// logmes無効化
		config.enable_error_include_push_ = N2_FALSE;// プリプロセス済みのファイルを扱うのでエラーなし
	}

	// デバッグ用
#if N2RI_DEBUG && 0
	{
		config.standard_statup_window_shown_ = N2_TRUE;
	}
#endif

	// ステート
	n2_state_t* state = n2_state_alloc(&config);

	// 埋め込みバイナリ
	void* ebin = NULL;
	size_t ebin_size = 0;
	n2_buffer_t ebin_hold = extract_embed_binary(state, &ebin, &ebin_size);
	if (ebin_hold.size_ <= 0 || !ebin || ebin_size <= 0)
	{
		show_error_simple(state, "スタートアップバイナリの読み込みに失敗しました。");
		return -1;
	}

	// 埋め込みバイナリの解釈
	n2h_msgpack_element_t* ebinsys = n2h_msgpack_parse(state, ebin, ebin_size);
	if (!ebinsys || ebinsys->type_ != N2H_MSGPACK_TYPE_MAP)
	{
		show_error_simple(state, "不正なスタートアップバイナリです。");
		return -1;
	}

	// 基本的なデータのロード
	n2_str_t script;
	n2_str_init(&script);

	if (!n2ri_extract_script_from_ebinsys(state, &script, ebinsys) || script.size_ <= 0)
	{
		show_error_simple(state, "スタートアップバイナリが不正です。");
		return -1;
	}

	n2h_filesystem_t* fs = n2h_filesystem_alloc_array(state);

	{
		n2h_filesystem_t* efs = n2ri_create_filesystem_from_ebinsys(state, ebinsys);

		if (!efs)
		{
			show_error_simple(state, "スタートアップバイナリのFileSystemが不正です。");
			return -1;
		}

		n2h_filesystem_array_insert(state, fs, efs);
	}

	// ファイルシステムのバインド
	n2_state_set_filesystem(state, fs);
	fs = NULL;

	// packoptの適用
	{
		n2ri_apply_packopt_from_ebinsys(state, ebinsys);
	}

	// 機能バインド
	n2_state_bind_basics(state);
#if N2R_CONFIG_RUNTIME_STANDARD
	n2_state_bind_standards(state);
#else
	n2_state_bind_consoles(state);
#endif

	// スクリプトロード
	if (!n2_state_load_str(state, "main", script.str_, script.size_, NULL))
	{
		show_error_simple(state, "スクリプトのロードに失敗しました。");
		return -1;
	}

	// スクリプトロードから実行へ
	n2ri_mainloop_context_t context;
	context.exit_code_ = 0;
	context.state_ = state;

#if N2_PLATFORM_IS_EMSCRIPTEN
	emscripten_set_main_loop_arg(n2ri_mainloop, &context, 0, 1);
#else
	for (;;)
	{
		n2ri_mainloop(&context);
		if (n2_state_is_quit_requested(context.state_) || n2_fiber_is_finished(context.state_->main_fiber_)) { break; }

		// 待ち状態なら適当に待つ
		if (state->main_fiber_->fiber_state_ == N2_FIBER_STATE_YIELD || state->main_fiber_->fiber_state_ == N2_FIBER_STATE_STOPPED)
		{
			SDL_Delay(N2_SCAST(Uint32, n2ri_default_frame_delay));
		}
	}
#endif

	// 終了処理
	n2_str_teardown(state, &script);
	if (ebinsys) { n2h_msgpack_free(state, ebinsys); }
	n2_buffer_teardown(state, &ebin_hold);
	n2_state_free(state);

	return context.exit_code_;
}


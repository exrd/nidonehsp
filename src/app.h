
#ifndef N2R_APP_INCLUDED
#define N2R_APP_INCLUDED

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <nidonehsp.h>

#if N2_PLATFORM_IS_EMSCRIPTEN
#include <emscripten.h>
#endif

#if N2_PLATFORM_IS_WINDOWS
#undef APIENTRY
#include <Windows.h>
#endif

#if N2_PLATFORM_IS_WINDOWS
#define N2RI_PLATFORM_EXE_SUFFIX	".exe"
#else
#define N2RI_PLATFORM_EXE_SUFFIX	""
#endif

#include <SDL.h>

static uint8_t n2ri_embed_binary_head[] = {
	0x4e, // N
	0x32, // 2
	0x52, // R
	0x21, // !
	0x00, // <NULL>
	0x45, // E
	0x42, // B
	0x49, // I
	0x4e, // N
	0x48, // H
	0x45, // E
	0x41, // A
	0x44, // D
	0x5f, // _
	0x5f  // _
};

static const char* n2ri_embed_binary_name = "n2r_ebin";

static const char* n2ri_em_ebin_path = "/nidonehsp/res/n2r_ebin";
static const char* n2ri_em_idbfs_root = "/nidonehsp/pmem";

static const uint8_t n2ri_script_aes_key[] = {
	0xb2, 0x88, 0xd7, 0x25, 0xbe, 0xc4, 0x31, 0xbe, 0xcc, 0x00, 0xa6, 0x18, 0x04, 0x75, 0xf6, 0xe3,
	0x24, 0xed, 0x85, 0x2f, 0xee, 0x78, 0x70, 0xf9, 0x34, 0xf2, 0x54, 0x91, 0x48, 0x77, 0x01, 0x44
};

static const uint8_t n2ri_script_aes_iv[] = {
	0x56, 0x26, 0x66, 0x5b, 0x28, 0x0c, 0xc1, 0x55, 0x2b, 0x42, 0xcb, 0xb4, 0xed, 0xb3, 0xe3, 0xe5
};

static const uint64_t n2ri_ebin_scratch_key = 0xfbdeddf3b58bbc68ULL;

static unsigned int n2ri_default_frame_delay = 20;

static const int n2ri_error_exit_code = 1;

#if N2_PLATFORM_IS_WINDOWS
static n2_bool_t n2ri_win_to_system_string(n2_state_t* state, n2_str_t* dst, const n2_str_t* src)
{
	const int required = MultiByteToWideChar(CP_UTF8, 0, src->str_, N2_SCAST(int, src->size_), NULL, 0);
	if (required < 0) { return N2_FALSE; }

	if (required > 0)
	{
		n2_str_reserve(state, dst, N2_SCAST(size_t, required) * sizeof(wchar_t) + 4);
		N2_MEMSET(dst->str_, 0, dst->buffer_size_);
		const int pathwritten = MultiByteToWideChar(CP_UTF8, 0, src->str_, N2_SCAST(int, src->size_), N2_RCAST(wchar_t*, dst->str_), N2_SCAST(int, dst->buffer_size_));
		if (pathwritten > 0)
		{
			dst->size_ = N2_SCAST(size_t, pathwritten) * sizeof(wchar_t);
		}
	}
	else
	{
		n2_str_clear(dst);
	}
	return N2_TRUE;
}
#endif

static n2_buffer_t n2ri_load_raw_file(n2_state_t* state, const n2_str_t* filepath)
{
	n2_buffer_t filebuf;
	n2_buffer_init(&filebuf);

#if N2_PLATFORM_IS_WINDOWS
	{
		n2_str_t ufilepath;
		n2_str_init(&ufilepath);

		if (n2ri_win_to_system_string(state, &ufilepath, filepath) && ufilepath.size_ > 0)
		{
			const wchar_t* ufilepath_cstr = N2_RCAST(wchar_t*, ufilepath.str_);
			HANDLE hfile = CreateFileW(ufilepath_cstr, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hfile != INVALID_HANDLE_VALUE)
			{
				const DWORD filesize = GetFileSize(hfile, NULL);
				if (filesize > 0)
				{
					n2_buffer_reserve(state, &filebuf, N2_SCAST(size_t, filesize) + 1);
					DWORD fileread = 0;
					if (ReadFile(hfile, filebuf.data_, filesize, &fileread, NULL))
					{
						filebuf.size_ = N2_SCAST(size_t, fileread);
					}
				}
				CloseHandle(hfile);
			}
		}

		n2_str_teardown(state, &ufilepath);
	}
#else
	{
		FILE* file = fopen(filepath->str_, "rb");
		if (file)
		{
			fseek(file, 0, SEEK_END);
			long size = ftell(file);
			if (size > 0)
			{
				n2_buffer_reserve(state, &filebuf, N2_SCAST(size_t, size));
				fseek(file, 0, SEEK_SET);
				size_t written = fread(filebuf.data_, 1, filebuf.buffer_size_, file);
				filebuf.size_ = written;
			}
			fclose(file);
		}
	}
#endif

	return filebuf;
}

static n2_bool_t n2ri_extract_script_from_ebinsys(n2_state_t* state, n2_str_t* dst_script, const n2h_msgpack_element_t* ebinsys)
{
	const n2h_msgpack_element_t* selem = n2h_msgpack_find_bystr(ebinsys, "s", SIZE_MAX);
	if (!selem || selem->type_ != N2H_MSGPACK_TYPE_MAP) { return N2_FALSE; }

	n2_bool_t res = N2_FALSE;

	const n2h_msgpack_element_t* sbelem = n2h_msgpack_find_bystr(selem, "b", SIZE_MAX);
	const n2h_msgpack_element_t* scelem = n2h_msgpack_find_bystr(selem, "c", SIZE_MAX);
	const n2h_msgpack_element_t* slelem = n2h_msgpack_find_bystr(selem, "l", SIZE_MAX);

	if (sbelem && sbelem->type_ == N2H_MSGPACK_TYPE_BINARY
		&& scelem && (scelem->type_ == N2H_MSGPACK_TYPE_UINT || scelem->type_ == N2H_MSGPACK_TYPE_INT)
		&& slelem && (slelem->type_ == N2H_MSGPACK_TYPE_UINT || slelem->type_ == N2H_MSGPACK_TYPE_INT))
	{
		const size_t scriptlength = slelem->type_ == N2H_MSGPACK_TYPE_UINT ? N2_SCAST(size_t, slelem->content_.uintval_) : N2_SCAST(size_t, slelem->content_.intval_);
		const uint32_t scriptcheck = scelem->type_ == N2H_MSGPACK_TYPE_UINT ? N2_SCAST(uint32_t, scelem->content_.uintval_) : N2_SCAST(uint32_t, scelem->content_.intval_);

		n2_buffer_t readscript;
		n2_buffer_init(&readscript);
		const n2_bool_t decrypted = n2h_aes_decrypt(state, &readscript, sbelem->content_.binval_.bin_, sbelem->content_.binval_.length_, n2ri_script_aes_key, sizeof(n2ri_script_aes_key), n2ri_script_aes_iv, sizeof(n2ri_script_aes_iv));
		if (decrypted && readscript.size_ > 0 && readscript.size_ >= scriptlength)
		{
			const uint32_t scriptcrc = n2h_crc32(readscript.data_, scriptlength);
			if (scriptcrc == scriptcheck)
			{
				n2_str_set(state, dst_script, N2_RCAST(const char*, readscript.data_), scriptlength);
				res = N2_TRUE;
			}
		}
		n2_buffer_teardown(state, &readscript);
	}

	return res;
}

static n2h_filesystem_t* n2ri_create_filesystem_from_ebinsys(n2_state_t* state, const n2h_msgpack_element_t* ebinsys)
{
	const n2h_msgpack_element_t* fselem = n2h_msgpack_find_bystr(ebinsys, "fs", SIZE_MAX);
	if (!fselem) { return NULL; }

	n2h_filesystem_t* efs = n2h_filesystem_alloc_msgpack(state, fselem);
	return efs;
}

static void n2ri_apply_packopt_from_ppc(n2_state_t* state)
{
	if (!state || !state->pp_context_) { return; }
	const n2c_pp_packopt_t* packopts = &state->pp_context_->packopt_;

	{
		if (packopts->xsize_ > 0)
		{
			state->config_.standard_startup_window_width_ = packopts->xsize_;
		}
		if (packopts->ysize_ > 0)
		{
			state->config_.standard_startup_window_height_ = packopts->ysize_;
		}
		{
			state->config_.standard_statup_window_shown_ = !packopts->hide_;
		}
	}
}

static void n2ri_apply_packopt_from_ebinsys(n2_state_t* state, const n2h_msgpack_element_t* ebinsys)
{
	const n2h_msgpack_element_t* poelem = n2h_msgpack_find_bystr(ebinsys, "packopts", SIZE_MAX);
	if (!poelem || poelem->type_ != N2H_MSGPACK_TYPE_MAP) { return; }

	{
		uint64_t xsize = 0, ysize = 0;
		if (n2h_msgpack_get_asuint(&xsize, n2h_msgpack_find_bystr(poelem, "xsize", SIZE_MAX), N2_FALSE) && xsize > 0)
		{
			state->config_.standard_startup_window_width_ = N2_SCAST(size_t, xsize);
		}
		if (n2h_msgpack_get_asuint(&ysize, n2h_msgpack_find_bystr(poelem, "ysize", SIZE_MAX), N2_FALSE) && ysize > 0)
		{
			state->config_.standard_startup_window_height_ = N2_SCAST(size_t, ysize);
		}
	}
	{
		n2_bool_t hide = N2_FALSE;
		if (n2h_msgpack_get_asbool(&hide, n2h_msgpack_find_bystr(poelem, "hide", SIZE_MAX), N2_FALSE))
		{
			state->config_.standard_statup_window_shown_ = !hide;
		}
	}
}

// memory leak check
typedef struct n2t_leakcheck_context_t n2t_leakcheck_context_t;
struct n2t_leakcheck_context_t
{
	n2_list_t list_;
	n2_bool_t print_;
};

static void n2t_leakcheck_list_freefunc(n2_state_t* state, n2_list_t* list, n2_list_node_t* node)
{
	N2_UNUSE(state);
	N2_UNUSE(list);
	free(node);
}

static void n2t_leakcheck_context_init(n2t_leakcheck_context_t* ctx)
{
	n2_list_init(&ctx->list_);
	ctx->print_ = N2_FALSE;
}

static void n2t_leakcheck_context_teardown(n2t_leakcheck_context_t* ctx)
{
	N2_LIST_FOREACH_INLINE(
		&ctx->list_,
		n2t_leakcheck_list_freefunc(NULL, &ctx->list_, node);
	);
	n2_list_init(&ctx->list_);
}

static size_t n2t_leakcheck_context_report(n2t_leakcheck_context_t* ctx)
{
	if (ctx->list_.size_ > 0)
	{
		printf("detected memory leaks(%zu)\n", ctx->list_.size_);
		N2_LIST_FOREACH_INLINE(
			&ctx->list_,
			printf("  %p\n", n2_ptr_offset(node, sizeof(n2_list_node_t)));
		);
	}
	return ctx->list_.size_;
}

static void* n2t_leakcheck_allocfunc(void* alloc_user, size_t new_size, void* old_ptr, size_t old_size)
{
	n2t_leakcheck_context_t* ac = N2_RCAST(n2t_leakcheck_context_t*, alloc_user);

	void* nptr = malloc(new_size + sizeof(n2_list_node_t));
	n2_list_node_init(nptr);
	n2_list_append(&ac->list_, N2_RCAST(n2_list_node_t*, nptr));
	void* npayload = n2_ptr_offset(nptr, sizeof(n2_list_node_t));
	if (old_ptr)
	{
		memcpy(npayload, old_ptr, old_size);
		void* old_master = n2_ptr_offset(old_ptr, -N2_SCAST(ptrdiff_t, sizeof(n2_list_node_t)));
		n2_list_erase(&ac->list_, N2_RCAST(n2_list_node_t*, old_master));
		free(old_master);
	}
	if (ac->print_) { printf("alloc:%p < %p\n", npayload, old_ptr); }
	return npayload;
}

static void n2t_leakcheck_freefunc(void* alloc_user, void* ptr)
{
	n2t_leakcheck_context_t* ac = N2_RCAST(n2t_leakcheck_context_t*, alloc_user);
	void* master = n2_ptr_offset(ptr, -N2_SCAST(ptrdiff_t, sizeof(n2_list_node_t)));
	if (!n2_list_erase(&ac->list_, N2_RCAST(n2_list_node_t*, master)))
	{
		N2_ASSERT(0);// unallocated ptr
	}
	free(master);
	if (ac->print_) { printf("free:%p\n", ptr); }
}

// app
static void n2ri_app_startup_console()
{
#if N2_PLATFORM_IS_WINDOWS
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif
}

#endif // N2R_APP_INCLUDED

﻿
#include "nidonehsp.h"

#define N2_MPI	(3.141592653589793238)
#define N2_ME	(2.718281828459045235)

// ヘッダ群
#if N2_COMPILER_IS_MSVC
#pragma warning(push, 0)// disable all
#endif

//=============================================================================
// stb_sprintf
#if N2_CONFIG_USE_SPRINTF_LIB
#define STB_SPRINTF_STATIC
#define STB_SPRINTF_IMPLEMENTATION
#include "embed/stb_sprintf.h"
#endif

//=============================================================================
// rpmalloc
#if N2_CONFIG_USE_RPMALLOC_LIB
#include "embed/rpmalloc.h"
#include "embed/rpmalloc.c"
#endif

//=============================================================================
// stb_image
#if N2_CONFIG_USE_IMAGE_READ_LIB
#define STBI_NO_STDIO
#define STB_IMAGE_STATIC
#define STBI_WINDOWS_UTF8
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT		N2_ASSERT
#define STBI_MALLOC(sz)	n2g_malloc(sz)
#define STBI_REALLOC(p,newsz)	
#define STBI_FREE(p)	n2g_free(p)
#define STBI_REALLOC_SIZED(p,oldsz,newsz)	n2g_realloc(newsz, p, oldsz)
#include "embed/stb_image.h"
#endif

//=============================================================================
// stb_image_write
#if N2_CONFIG_USE_IMAGE_WRITE_LIB
#define STBI_WRITE_NO_STDIO
#define STB_IMAGE_WRITE_STATIC
#define STBI_WINDOWS_UTF8
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT	N2_ASSERT
#define STBIW_MALLOC(sz)	n2g_malloc(sz)
#define STBIW_REALLOC(p,newsz)	
#define STBIW_FREE(p)	n2g_free(p)
#define STBIW_REALLOC_SIZED(p,oldsz,newsz)	n2g_realloc(newsz, p, oldsz)
#define STBIW_MEMMOVE	N2_MEMMOVE
#include "embed/stb_image_write.h"
#endif

//=============================================================================
// cute_aseprite.h
#if N2_CONFIG_USE_ASEPRITE_LIB
#define CUTE_ASEPRITE_ALLOC(size, ctx)	n2_malloc(N2_RCAST(n2_state_t*, ctx), size)
#define CUTE_ASEPRITE_FREE(mem, ctx)	n2_free(N2_RCAST(n2_state_t*, ctx), mem)
#define CUTE_ASEPRITE_MEMCPY	N2_MEMCPY
#define CUTE_ASEPRITE_MEMSET	N2_MEMSET
#define CUTE_ASEPRITE_ASSERT	N2_ASSERT
#define CUTE_ASEPRITE_IMPLEMENTATION
#include "embed/cute_aseprite.h"
#endif

//=============================================================================
// dr_wav.h
#if N2_CONFIG_USE_AUDIO_WAV_LIB
#define DRWAV_API	static
#define DRWAV_PRIVATE	static
#define DRWAV_IMPLEMENTATION
#define DRWAV_ASSERT	N2_ASSERT
#define DRWAV_MALLOC(sz)	n2g_xmalloc(sz)
#define DRWAV_REALLOC(p, sz)	n2g_xrealloc((sz), (p))
#define DRWAV_FREE(p)		n2g_xfree((p))
#define DRWAV_COPY_MEMORY	N2_MEMCPY
#define DRWAV_ZERO_MEMORY(p, sz)	N2_MEMSET((p), 0, (sz))
#define DR_WAV_NO_STDIO
#include "embed/dr_wav.h"
#endif

//=============================================================================
// dr_mp3.h
#if N2_CONFIG_USE_AUDIO_MP3_LIB
#define DRMP3_API	static
#define DRMP3_PRIVATE	static
#define DRMP3_IMPLEMENTATION
#define DRMP3_ASSERT	N2_ASSERT
#define DRMP3_MALLOC(sz)	n2g_xmalloc(sz)
#define DRMP3_REALLOC(p, sz)	n2g_xrealloc((sz), (p))
#define DRMP3_FREE(p)		n2g_xfree((p))
#define DRMP3_COPY_MEMORY	N2_MEMCPY
#define DRMP3_ZERO_MEMORY(p, sz)	N2_MEMSET((p), 0, (sz))
#define DR_MP3_NO_STDIO
#include "embed/dr_mp3.h"
#endif

//=============================================================================
// stb_vorbis.h
#if N2_CONFIG_USE_AUDIO_OGG_LIB
#define STB_VORBIS_NO_STDIO
//#define STB_VORBIS_NO_CRT
#include "embed/stb_vorbis.h"
// undef evil macros
#undef L
#undef C
#undef R
#endif

//=============================================================================
// dr_flac.h
#if N2_CONFIG_USE_AUDIO_FLAC_LIB
#define DRFLAC_API	static
#define DRFLAC_PRIVATE	static
#define DRFLAC_IMPLEMENTATION
#define DRFLAC_ASSERT	N2_ASSERT
#define DRFLAC_MALLOC(sz)	n2g_xmalloc(sz)
#define DRFLAC_REALLOC(p, sz)	n2g_xrealloc((sz), (p))
#define DRFLAC_FREE(p)		n2g_xfree((p))
#define DRFLAC_COPY_MEMORY	N2_MEMCPY
#define DRFLAC_ZERO_MEMORY(p, sz)	N2_MEMSET((p), 0, (sz))
#define DR_FLAC_NO_STDIO
#include "embed/dr_flac.h"
#endif

//=============================================================================
// stb_truetype.h
#if N2_CONFIG_USE_FONT_LIB
#define STBRP_STATIC
#define STB_RECT_PACK_IMPLEMENTATION
#define STBRP_ASSERT	N2_ASSERT
#include "embed/stb_rect_pack.h"

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_sqrt	N2_SQRT
#define STBTT_pow	N2_POW
#define STBTT_fmod	N2_FMOD
#define STBTT_cos	N2_COS
#define STBTT_acos	N2_ACOS
#define STBTT_assert	N2_ASSERT
#define STBTT_malloc(sz, user)	n2_malloc(N2_RCAST(n2_state_t*, user), sz)
#define STBTT_free(p, user)	n2_free(N2_RCAST(n2_state_t*, user), p)
#define STBTT_strlen	N2_STRLEN
#define STBTT_memcpy	N2_MEMCPY
#define STBTT_memset	N2_MEMSET
#include "embed/stb_truetype.h"
#endif

//=============================================================================
// miniz.h
#if N2_CONFIG_USE_Z_LIB
#define MINIZ_NO_STDIO
//#define MINIZ_NO_MALLOC
//#define MZ_ASSERT N2_ASSERT
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES
#include "embed/miniz.h"
#endif

//=============================================================================
#if N2_CONFIG_USE_ULZ_LIB
#define CULZ_STATIC
#define CULZ_IMPLEMENTATION
#include "embed/culz.h"
#endif

//=============================================================================
// json.h
#if N2_CONFIG_USE_JSON_LIB
#include "embed/json.h"
#endif

//=============================================================================
// zed_net.h
#if N2_CONFIG_USE_NET_SOCKET_LIB
#undef APIENTRY// for msvc workaround
#define ZED_NET_STATIC
#define ZED_NET_IMPLEMENTATION
#include "embed/zed_net.h"
#endif

//=============================================================================
// SDL
#if N2_CONFIG_USE_SDL_LIB
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_opengles2_khrplatform.h>
#include "embed/glad_gles3.h"
#include "embed/glad_gles3.c"

// shader
#include "inline/shader.h"
#endif

//=============================================================================
// picomsgpack.h
#if N2_CONFIG_USE_MSGPACK_LIB
#define PMSGP_STATIC
#define PMSGP_MALLOC(size, user)	n2_malloc(N2_RCAST(n2_state_t*, user), size)
#define PMSGP_FREE(ptr, user)	n2_free(N2_RCAST(n2_state_t*, user), ptr)
#define PMSGP_REALLOC_SIZED(oldptr, newsize, oldsize, user)	n2_realloc(N2_RCAST(n2_state_t*, user), newsize, oldptr, oldsize)
#define PMSGP_NO_STDIO_FILE_API
#define PMSGP_IMPLEMENTATION
#include "embed/picomsgpack.h"
#endif

//=============================================================================
// md5.h
#if N2_CONFIG_USE_MD5_LIB
#define MD5_API static
#define MD5_MEMCPY N2_MEMCPY
#define MD5_MEMSET N2_MEMSET
#define MD5_IMPLEMENTATION
#include "embed/md5.h"
#endif

//=============================================================================
// aes.h
#if N2_CONFIG_USE_AES_LIB
#define CBC 1
#define CTR 1
#define ECB 1
#include "embed/aes.h"
#include "embed/aes.c"
#endif

//=============================================================================
// embedded font
#if N2_CONFIG_USE_EMBED_FONT
#include "inline/mplus_2m_regular_generalj.h"
//#include "inline/mplus_2m_medium_generalj.h"
#if N2I_CONFIG_USE_EMBED_FONT_FA_REGULAR
#include "inline/fa_regular_400.h"
#include "inline/fa_regular_mapping.h"
#else
#include "inline/fa_regular_mapping_none.h"
#endif
#if N2I_CONFIG_USE_EMBED_FONT_FA_SOLID
#include "inline/fa_solid_900.h"
#include "inline/fa_solid_mapping.h"
#else
#include "inline/fa_solid_mapping_none.h"
#endif
#endif

//=============================================================================
// nuklear.h
#if N2_CONFIG_USE_GUI_LIB
#define NK_PRIVATE
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO// include stdio.h but not used in nidonehsp
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
//#define NK_INCLUDE_FONT_BAKING
//#define NK_BUTTON_TRIGGER_ON_RELEASE
//#define NK_KEYSTATE_BASED_INPUT
#define NK_ASSERT	N2_ASSERT
#define NK_MEMSET	N2_MEMSET
#define NK_MEMCPY	N2_MEMCPY
#define NK_SQRT		N2_SQRT
#define NK_SIN		N2_SIN
#define NK_COS		N2_COS
#define NK_STRTOD(str, endptr)	N2_STRTOD(str, (char**)(endptr))
#define NK_VSNPRINTF	n2_vsnprintf
#define NK_IMPLEMENTATION
#include "embed/nuklear.h"
#endif

//=============================================================================
// プラットフォーム固有
#if N2_PLATFORM_IS_WINDOWS
#undef APIENTRY
#include <Windows.h>
#endif

#if N2_PLATFORM_IS_EMSCRIPTEN
#include <emscripten.h>
#endif

// ヘッダ群
#if N2_COMPILER_IS_MSVC
#pragma warning(pop)
#endif

// その他
#define N2SI_SDL_INIT_SYSTEM_FLAGS \
	(SDL_INIT_TIMER/* | SDL_INIT_AUDIO*/ | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS)

//=============================================================================
//=============================================================================
//=============================================================================
// 内部リンケージの人たち、ここから

static size_t n2i_roundup_sz(size_t val, size_t mul)
{
	if (mul <= 0) { return val; }
	const size_t rem = val % mul;
	return val + (rem ? (mul - rem) : 0);
}

static void n2i_printf(n2_state_t* state, const char* fmt, ...)
{
	if (!state->config_.print_) { return; }
	n2_str_t str;
	n2_str_init(&str);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &str, fmt, args);
	va_end(args);
	state->config_.print_(state->config_.print_user_, state, str.str_);
	n2_str_teardown(state, &str);
}

static void n2i_lprintf(n2_state_t* state, n2_fiber_t* fiber, n2_log_level_e log_level, const char* fmt, ...)
{
	if (!state->config_.print_log_) { return; }
	n2_str_t str;
	n2_str_init(&str);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &str, fmt, args);
	va_end(args);
	state->config_.print_log_(state->config_.print_user_, state, fiber, log_level, str.str_);
	n2_str_teardown(state, &str);
}

static void n2i_eprintf(n2_state_t* state, const char* fmt, ...)
{
	if (!state->config_.print_error_) { return; }
	n2_str_t str;
	n2_str_init(&str);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &str, fmt, args);
	va_end(args);
	state->config_.print_error_(state->config_.print_user_, state, str.str_);
	n2_str_teardown(state, &str);
}

#if N2_CONFIG_USE_STD_MALLOC
static void* n2i_default_allocate(void* alloc_user, size_t new_size, void* old_ptr, size_t old_size)
{
	N2_UNUSE(alloc_user);
	N2_UNUSE(old_size);
	if (old_ptr)
	{
		return realloc(old_ptr, new_size);
	}
	return malloc(new_size);
}

static void n2i_default_free(void* alloc_user, void* ptr)
{
	N2_UNUSE(alloc_user);
	free(ptr);
}
#endif

#if N2_CONFIG_USE_STD_PRINT
static void n2i_default_print(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	printf("%s", str);
}

static void n2i_default_print_log(void* print_user, n2_state_t* state, n2_fiber_t* fiber, n2_log_level_e log_level, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	N2_UNUSE(fiber);
	N2_UNUSE(log_level);
	fprintf(stdout, "%s", str);
}

static void n2i_default_print_error(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	fprintf(stderr, "%s", str);
}
#endif

#if N2_CONFIG_USE_SDL_LIB && 0
static void n2i_sdl_print(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	SDL_Log("%s", str);
}

static void n2i_sdl_print_error(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", str);
}
#endif

static void* n2i_zmalloc(const n2_allocator_t* allocator, size_t size)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->allocate_);
	return allocator->allocate_(allocator->alloc_user_, size, NULL, 0);
}

static void* n2i_zrealloc(const n2_allocator_t* allocator, size_t new_size, void* old_ptr, size_t old_size)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->allocate_);
	return allocator->allocate_(allocator->alloc_user_, new_size, old_ptr, old_size);
}

static void n2i_zfree(const n2_allocator_t* allocator, void* ptr)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->free_);
	allocator->free_(allocator->alloc_user_, ptr);
}

static void* n2i_xmalloc(const n2_allocator_t* allocator, size_t size)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->allocate_);
	void* p = allocator->allocate_(allocator->alloc_user_, size + N2_MAXALIGN_SIZE, NULL, 0);
	if (!p) { return NULL; }
	N2_MEMCPY(p, &size, sizeof(size_t));
	return n2_ptr_offset(p, N2_MAXALIGN_SIZE);
}

static void* n2i_xrealloc(const n2_allocator_t* allocator, size_t new_size, void* old_ptr)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->allocate_);
	if (!old_ptr) { return n2i_xmalloc(allocator, new_size); }// just same as new alloc
	void* old_ptr_master = n2_ptr_offset(old_ptr, -N2_SCAST(ptrdiff_t, N2_MAXALIGN_SIZE));
	size_t old_size = 0;
	N2_MEMCPY(&old_size, old_ptr_master, sizeof(size_t));
	void* new_ptr = allocator->allocate_(allocator->alloc_user_, new_size + N2_MAXALIGN_SIZE, old_ptr_master, old_size + N2_MAXALIGN_SIZE);
	N2_MEMCPY(new_ptr, &new_size, sizeof(size_t));
	return n2_ptr_offset(new_ptr, N2_MAXALIGN_SIZE);
}

static void n2i_xfree(const n2_allocator_t* allocator, void* ptr)
{
	N2_ASSERT(allocator);
	N2_ASSERT(allocator->free_);
	if (!ptr) { return; }// null free
	allocator->free_(allocator->alloc_user_, n2_ptr_offset(ptr, -N2_SCAST(ptrdiff_t, N2_MAXALIGN_SIZE)));
}

#if N2_CONFIG_USE_STD_FILEIO
static n2_bool_t n2i_default_file_read(void* file_user, const n2_fileread_param_t* param)
{
	N2_UNUSE(file_user);
	FILE* file = fopen(param->filepath_, param->binary_ ? "rb" : "rt");
	if (!file) { return N2_FALSE; }
	n2_buffer_t tmpbuffer;
	n2_buffer_init(&tmpbuffer);
	N2_ASSERT(param->state_->config_.file_read_tmp_buffer_size_ > 0);
	n2_buffer_reserve(param->state_, &tmpbuffer, N2_MAX(param->state_->config_.file_read_tmp_buffer_size_, 1));
	size_t preread = param->readoffset_;
	while (preread > 0)
	{
		const size_t read = fread(tmpbuffer.data_, 1, N2_MIN(preread, tmpbuffer.buffer_size_), file);
		preread -= read;
		if (feof(file)) { break; }
	}
	if (!feof(file))
	{
		size_t actualread = param->readsize_;
		while (actualread > 0)
		{
			if (param->binary_)
			{
				const size_t read = fread(tmpbuffer.data_, 1, N2_MIN(actualread, tmpbuffer.buffer_size_), file);
				n2_buffer_append(param->state_, param->dst_, tmpbuffer.data_, read);
			}
			else
			{
				if (!fgets(N2_RCAST(char*, tmpbuffer.data_), N2_SCAST(int, tmpbuffer.buffer_size_ / sizeof(char)), file)) { break; }
				n2_buffer_append(param->state_, param->dst_, tmpbuffer.data_, N2_STRNLEN(N2_RCAST(const char*, tmpbuffer.data_), tmpbuffer.buffer_size_));
			}
			if (feof(file)) { break; }
		}
	}
	fclose(file);
	n2_buffer_teardown(param->state_, &tmpbuffer);
	n2_buffer_append_values_transparent(param->state_, param->dst_, 0, 1);
	return N2_TRUE;
}

static n2_bool_t n2i_default_file_write(void*file_user, const n2_filewrite_param_t* param)
{
	N2_UNUSE(file_user);
	FILE* file = fopen(param->filepath_, param->writeoffset_ == SIZE_MAX ? (param->binary_ ? "wb" : "wt") : (param->binary_ ? "wb+" : "wt+"));
	if (!file) { return N2_FALSE; }
	if (param->writeoffset_ > 0 && param->writeoffset_ != SIZE_MAX) { fseek(file, N2_SCAST(long, param->writeoffset_), SEEK_SET); }
	n2_bool_t res = N2_TRUE;
	if (!ferror(file))
	{
		const size_t written = fwrite(param->writedata_, 1, param->writesize_, file);
		if (written < param->writesize_) { res = N2_FALSE; }
		if (param->dst_writtensize_) { *param->dst_writtensize_ = written; }
	}
	if (ferror(file)) { res = N2_FALSE; }
	fclose(file);
	return res;
}
#endif

static void n2i_setupfunc_nothing(n2_state_t* state, void* container)
{
	N2_UNUSE(state);
	N2_UNUSE(container);
}

static void n2i_freefunc_nothing(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(state);
	N2_UNUSE(a);
	N2_UNUSE(element);
}

static int n2i_matchfunc_bitperfect(const n2_array_t* a, const void* element, const void* key)
{
	N2_UNUSE(key);
	return N2_MEMCMP(element, key, a->element_size_);
}

static int n2i_cmpfunc_bitperfect(const n2_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(key);
	return N2_MEMCMP(lkey, rkey, a->element_size_);
}

static int n2i_mem_ncmp_sized(const void* lhs, size_t lhs_length, const void* rhs, size_t rhs_length)
{
	if (lhs_length != rhs_length) { return lhs_length < rhs_length ? -1 : 1; }
	return N2_MEMCMP(lhs, rhs, lhs_length);
}

static N2_INLINE char n2i_char_tolower(char c) { return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c; }
static N2_INLINE n2_bool_t n2i_char_is_ctrl(char c) { return N2_SCAST(uint8_t, c) < 0x20; }
static N2_INLINE n2_bool_t n2i_char_is_space(char c) { return c == ' ' || c == '\t'; };
static N2_INLINE n2_bool_t n2i_char_is_number(char c) { return c >= '0' && c <='9'; };
static N2_INLINE n2_bool_t n2i_char_is_hexnumber(char c) { return (c >= '0' && c<='9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); };
static N2_INLINE n2_bool_t n2i_char_is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z'); };
static N2_INLINE n2_bool_t n2i_char_is_multibyte(char c) { return N2_SCAST(uint8_t, c) > 0x80; }// assuming utf8
static N2_INLINE n2_bool_t n2i_char_is_lead_ident(char c) { return n2i_char_is_alpha(c) || c == '_' || n2i_char_is_multibyte(c); }
static N2_INLINE n2_bool_t n2i_char_is_rest_ident(char c) { return n2i_char_is_number(c) || n2i_char_is_alpha(c) || c == '_' || n2i_char_is_multibyte(c); };

static void n2i_do_error(n2_state_t* state, n2_error_e e, const n2_sourcecode_t* sourcecode, const char* rawmessage, const char* message, int line, const char* subdesc, n2_fiber_t* fiber)
{
	if (state->config_.error_is_print_)
	{
		n2i_eprintf(state, "%s\n", message);
		if (subdesc) { n2i_eprintf(state, "%s\n", subdesc); }
	}
	if (state->config_.error_)
	{
		n2_error_param_t error_param;
		n2_error_param_init(&error_param);
		error_param.state_ = state;
		error_param.error_ = e;
		error_param.sourcecode_ = sourcecode;
		if (sourcecode) { error_param.package_ = sourcecode->package_.str_; }
		error_param.raw_message_ = rawmessage;
		error_param.message_ = message;
		error_param.subdescription_ = subdesc;
		error_param.line_ = line;
		error_param.column_ = 0;
		error_param.fiber_ = fiber;
		state->config_.error_(state->config_.error_user_, &error_param);
	}
	return;
}

//=============================================================================
//=============================================================================
//=============================================================================
// 外部リンケージを持つ人たち、ここから

//=============================================================================
// メモリユーティリティ
N2_API void n2_swap(void* l, void* r, size_t size)
{
	uint8_t* u = N2_RCAST(uint8_t*, l);
	uint8_t* v = N2_RCAST(uint8_t*, r);
	for (size_t i = 0; i < size; ++i, ++u, ++v)
	{
		const uint8_t t = *u;
		*u = *v;
		*v = t;
	}
}

N2_API void* n2_ptr_offset(void* p, ptrdiff_t offset)
{
	return N2_RCAST(void*, N2_RCAST(uint8_t*, p) + offset);
}

N2_API const void* n2_cptr_offset(const void* p, ptrdiff_t offset)
{
	return N2_RCAST(const void*, N2_RCAST(uint8_t*, p) + offset);
}

N2_API ptrdiff_t n2_ptr_diff(const void* lhs, const void* rhs)
{
	return N2_RCAST(intptr_t, lhs) - N2_RCAST(intptr_t, rhs);
}

N2_API uint8_t n2_ptr_read8(const void* ptr)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, ptr);
	return p[0];
}

N2_API uint16_t n2_ptr_read16(const void* ptr)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, ptr);
	return p[0] | (p[1] << 8);
}

N2_API uint32_t n2_ptr_read32(const void* ptr)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, ptr);
	return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}

N2_API uint64_t n2_ptr_read64(const void* ptr)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, ptr);
	return N2_SCAST(uint64_t, p[0]) | (N2_SCAST(uint64_t, p[1]) << 8) | (N2_SCAST(uint64_t, p[2]) << 16) | (N2_SCAST(uint64_t, p[3]) << 24)
		| (N2_SCAST(uint64_t, p[4]) << 32) | (N2_SCAST(uint64_t, p[5]) << 40) | (N2_SCAST(uint64_t, p[6]) << 48) | (N2_SCAST(uint64_t, p[7]) << 56);
}

N2_API void n2_ptr_write8(void* ptr, uint8_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, ptr);
	p[0] = v;
}

N2_API void n2_ptr_write16(void* ptr, uint16_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, ptr);
	p[0] = v & 0xff;
	p[1] = (v >> 8) & 0xff;
}

N2_API void n2_ptr_write32(void* ptr, uint32_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, ptr);
	p[0] = v & 0xff;
	p[1] = (v >> 8) & 0xff;
	p[2] = (v >> 16) & 0xff;
	p[3] = (v >> 24) & 0xff;
}

N2_API void n2_ptr_write64(void* ptr, uint64_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, ptr);
	p[0] = v & 0xff;
	p[1] = (v >> 8) & 0xff;
	p[2] = (v >> 16) & 0xff;
	p[3] = (v >> 24) & 0xff;
	p[4] = (v >> 32) & 0xff;
	p[5] = (v >> 40) & 0xff;
	p[6] = (v >> 48) & 0xff;
	p[7] = (v >> 56) & 0xff;
}

N2_API void* n2_malloc(n2_state_t* state, size_t size)
{
	N2_ASSERT(state);
	return n2i_zmalloc(&state->config_.allocator_, size);
}

N2_API void* n2_realloc(n2_state_t* state, size_t new_size, void* old_ptr, size_t old_size)
{
	N2_ASSERT(state);
	return n2i_zrealloc(&state->config_.allocator_, new_size, old_ptr, old_size);
}

N2_API void n2_free(n2_state_t* state, void* ptr)
{
	N2_ASSERT(state);
	n2i_zfree(&state->config_.allocator_, ptr);
}

N2_API void* n2_xmalloc(n2_state_t* state, size_t size)
{
	N2_ASSERT(state);
	return n2i_xmalloc(&state->config_.allocator_, size);
}

N2_API void* n2_xrealloc(n2_state_t* state, size_t new_size, void* old_ptr)
{
	N2_ASSERT(state);
	return n2i_xrealloc(&state->config_.allocator_, new_size, old_ptr);
}

N2_API void n2_xfree(n2_state_t* state, void* ptr)
{
	N2_ASSERT(state);
	n2i_xfree(&state->config_.allocator_, ptr);
}

static N2_THREAD_LOCAL n2_state_t* n2gi_global_state_ = NULL;

N2_API void n2g_set_state(n2_state_t* state)
{
	n2gi_global_state_ = state;
}

N2_API n2_state_t* n2g_get_state()
{
	return n2gi_global_state_;
}

N2_API void* n2g_malloc(size_t size)
{
	return n2_malloc(n2gi_global_state_, size);
}

N2_API void* n2g_realloc(size_t new_size, void* old_ptr, size_t old_size)
{
	return n2_realloc(n2gi_global_state_, new_size, old_ptr, old_size);
}

N2_API void n2g_free(void* ptr)
{
	n2_free(n2gi_global_state_, ptr);
}

N2_API void* n2g_xmalloc(size_t size)
{
	return n2_xmalloc(n2gi_global_state_, size);
}

N2_API void* n2g_xrealloc(size_t new_size, void* old_ptr)
{
	return n2_xrealloc(n2gi_global_state_, new_size, old_ptr);
}

N2_API void n2g_xfree(void* ptr)
{
	n2_xfree(n2gi_global_state_, ptr);
}

// メモリプール
N2_API n2_mempool_t* n2_mempool_alloc(n2_state_t* state, size_t blocksize, size_t blocknum)
{
	blocksize = n2i_roundup_sz(blocksize, sizeof(void*));
	blocknum = N2_MAX(1, blocknum);
	n2_mempool_t* mempool = N2_TMALLOC(n2_mempool_t, state);
	if (!mempool) { return NULL; }
	mempool->arena_size_ = blocksize * blocknum;
	mempool->arena_ = n2_malloc(state, mempool->arena_size_);
	if (!mempool->arena_) { n2_free(state, mempool); return NULL; }
	mempool->blocksize_ = blocksize;
	mempool->blocknum_ = blocknum;
	mempool->head_ = mempool->arena_;
	for (size_t i = 0; i < mempool->blocknum_; ++i)
	{
		*N2_RCAST(void**, n2_ptr_offset(mempool->arena_, mempool->blocksize_ * i)) = i == mempool->blocknum_ - 1 ? NULL : n2_ptr_offset(mempool->arena_, mempool->blocksize_ * (i + 1));
	}
	return mempool;
}

N2_API void n2_mempool_free(n2_state_t* state, n2_mempool_t* mempool)
{
	n2_free(state, mempool->arena_);
	n2_free(state, mempool);
}

N2_API void* n2_mempool_try_alloc(n2_mempool_t* mempool, size_t size)
{
	if (size > mempool->blocksize_) { return NULL; }
	if (!mempool->head_) { return NULL; }
	void* res = mempool->head_;
	mempool->head_ = *N2_RCAST(void**, mempool->head_);
	return res;
}

N2_API n2_bool_t n2_mempool_test_include(const n2_mempool_t* mempool, void* ptr)
{
	const ptrdiff_t diff = n2_ptr_diff(mempool->arena_, ptr);
	if (diff < 0 || diff >= N2_SCAST(ptrdiff_t, mempool->arena_size_)) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2_mempool_try_free(n2_mempool_t* mempool, void* ptr)
{
	if (!n2_mempool_test_include(mempool, ptr)) { return N2_FALSE; }
	*N2_RCAST(void**, ptr) = mempool->head_;
	mempool->head_ = ptr;
	return N2_TRUE;
}

//=============================================================================
// バッファユーティリティ
N2_API void n2_buffer_init(n2_buffer_t* buffer)
{
	buffer->data_ = NULL;
	buffer->size_ = 0;
	buffer->buffer_size_ = 0;
	buffer->expand_step_ = 64;
}

N2_API void n2_buffer_teardown(n2_state_t* state, n2_buffer_t* buffer)
{
	N2_ASSERT(state);
	if (buffer->data_)
	{
		n2_free(state, buffer->data_);
		buffer->data_ = NULL;
	}
	buffer->size_ = 0;
	buffer->buffer_size_ = 0;
}

N2_API void n2_buffer_set_expand_step(n2_buffer_t* buffer, size_t expand_step)
{
	buffer->expand_step_ = expand_step;
}

N2_API void n2_buffer_copy_to(n2_state_t* state, n2_buffer_t* buffer, const n2_buffer_t* rbuffer)
{
	N2_ASSERT(buffer);
	if (rbuffer->data_)
	{
		n2_buffer_reserve(state, buffer, rbuffer->size_);
		N2_MEMCPY(buffer->data_, rbuffer->data_, rbuffer->size_);
		buffer->size_ = rbuffer->size_;
		buffer->buffer_size_ = rbuffer->size_;
	}
	else
	{
		n2_buffer_clear(buffer);
	}
}

N2_API void n2_buffer_swap(n2_buffer_t* buffer, n2_buffer_t* rbuffer)
{
	n2_buffer_t t = *buffer;
	*buffer = *rbuffer;
	*rbuffer = t;
}

N2_API void n2_buffer_clear(n2_buffer_t* buffer)
{
	buffer->size_ = 0;
}

N2_API n2_bool_t n2_buffer_reserve(n2_state_t* state, n2_buffer_t* buffer, size_t size)
{
	N2_ASSERT(buffer);
	if (!buffer->data_)
	{
		if (size > 0)
		{
			const size_t next_size = N2_MAX(size, buffer->expand_step_);
			buffer->data_ = n2_malloc(state, next_size);
			if (!buffer->data_) { return N2_FALSE; }
			buffer->buffer_size_ = next_size;
		}
	}
	else if (buffer->buffer_size_ < size)
	{
		const size_t next_size = N2_MAX(size, buffer->buffer_size_ + (buffer->expand_step_ == 0 ? buffer->buffer_size_ : buffer->expand_step_));
		void* next_data = n2_realloc(state, next_size, buffer->data_, buffer->buffer_size_);
		if (!next_data) { return N2_FALSE; }
		buffer->data_ = next_data;
		buffer->buffer_size_ = next_size;
	}
	return N2_TRUE;
}

N2_API void n2_buffer_set(n2_state_t* state, n2_buffer_t* buffer, const void* cbuffer, size_t length)
{
	N2_ASSERT(buffer);
	N2_ASSERT(cbuffer);

	n2_buffer_reserve(state, buffer, length);

	N2_MEMCPY(buffer->data_, cbuffer, length);
	buffer->size_ = length;
}

N2_API void n2_buffer_append(n2_state_t* state, n2_buffer_t* buffer, const void* append_buffer, size_t append_length)
{
	N2_ASSERT(buffer);
	N2_ASSERT(append_buffer);

	if (append_length <= 0) { return; }
	n2_buffer_reserve(state, buffer, buffer->size_ + append_length);

	N2_MEMCPY(n2_ptr_offset(buffer->data_, buffer->size_), append_buffer, append_length);
	buffer->size_ += append_length;
}

N2_API void n2_buffer_append_values(n2_state_t* state, n2_buffer_t* buffer, uint8_t value, size_t append_length)
{
	n2_buffer_append_values_transparent(state, buffer, value, append_length);
	buffer->size_ += append_length;
}

N2_API void n2_buffer_append_values_transparent(n2_state_t* state, n2_buffer_t* buffer, uint8_t value, size_t append_length)
{
	N2_ASSERT(buffer);

	if (append_length <= 0) { return; }
	n2_buffer_reserve(state, buffer, buffer->size_ + append_length);

	N2_MEMSET(n2_ptr_offset(buffer->data_, buffer->size_), value, append_length);
}

N2_API n2_bool_t n2_buffer_insert(n2_state_t* state, n2_buffer_t* buffer, size_t offset, const void* data, size_t length)
{
	if (offset > buffer->size_) { return N2_FALSE; }
	if (length <= 0) { return N2_TRUE; }
	if (!n2_buffer_reserve(state, buffer, buffer->size_ + length)) { return N2_FALSE; }
	const size_t tail_size = buffer->size_ - offset;
	if (tail_size > 0) { N2_MEMMOVE(n2_ptr_offset(buffer->data_, offset + length), n2_ptr_offset(buffer->data_, offset), tail_size); }
	N2_MEMCPY(n2_ptr_offset(buffer->data_, offset), data, length);
	buffer->size_ += length;
	return N2_TRUE;
}

N2_API size_t n2_buffer_erase(n2_buffer_t* buffer, size_t offset, size_t length)
{
	if (length <= 0) { return 0; }
	if (offset >= buffer->size_) { return 0; }
	length = N2_MIN(length, buffer->size_ - offset);
	N2_MEMMOVE(n2_ptr_offset(buffer->data_, offset), n2_ptr_offset(buffer->data_, offset + length), buffer->size_ + 1 - offset - length);
	buffer->size_ -= length;
	return length;
}

N2_API size_t n2_buffer_replace_pattern(n2_state_t* state, n2_buffer_t* buffer, const void* src, size_t src_length, const void* to, size_t to_length)
{
	if (src_length <= 0) { return 0; }
	if (buffer->size_ < src_length) { return 0; }
	size_t replace_count = 0;
	for (int i = N2_SCAST(int, buffer->size_ - src_length); i >= 0; --i)
	{
		if (N2_MEMCMP(n2_ptr_offset(buffer->data_, i), src, src_length) == 0)
		{
			if (src_length != to_length)
			{
				int diff = N2_SCAST(int, to_length - src_length);
				if (src_length < to_length) { n2_buffer_reserve(state, buffer, buffer->size_ + to_length - src_length + 1); }
				N2_MEMMOVE(n2_ptr_offset(buffer->data_, i + N2_SCAST(int, to_length)), n2_ptr_offset(buffer->data_, i + N2_SCAST(int, src_length)), N2_SCAST(int, buffer->size_ + 1) - i - N2_SCAST(int, src_length));
				(diff < 0 ? (buffer->size_ -= N2_SCAST(size_t, -diff)) : (buffer->size_ += N2_SCAST(size_t, diff)));
			}
			if (to_length > 0) { N2_MEMCPY(n2_ptr_offset(buffer->data_, i), to, to_length); }
			i -= N2_SCAST(int, src_length) - 1;
			++replace_count;
			continue;
		}
	}
	return replace_count;
}

N2_API n2_buffer_t* n2_buffer_alloc(n2_state_t* state, size_t initial_buffer_size)
{
	n2_buffer_t* buffer = N2_TMALLOC(n2_buffer_t, state);
	if (!buffer) { return buffer; }
	n2_buffer_init(buffer);
	n2_buffer_reserve(state, buffer, initial_buffer_size);
	return buffer;
}

N2_API n2_buffer_t* n2_buffer_clone(n2_state_t* state, const n2_buffer_t* rbuffer)
{
	n2_buffer_t* buffer = n2_buffer_alloc(state, 0);
	if (!buffer) { return NULL; }
	n2_buffer_init(buffer);
	n2_buffer_copy_to(state, buffer, rbuffer);
	return buffer;
}

N2_API void n2_buffer_free(n2_state_t* state, n2_buffer_t* buffer)
{
	N2_ASSERT(state);
	n2_buffer_teardown(state, buffer);
	n2_free(state, buffer);
}

//=============================================================================
// エンコーディングユーティリティ
static n2_codepoint_t n2i_encoding_fetch_table(n2_codepoint_t codepoint, n2_codepoint_t fallback, const int32_t* table, size_t tablesize)
{
	int l = 0, r = N2_SCAST(int, tablesize / 2);
	while (l < r)
	{
		const int m = (l + r) / 2;
		const int from = table[m * 2 + 0];
		const int to = table[m * 2 + 1];
		const int c = codepoint - from;
		if (c == 0) { return to; }
		else if (c > 0) { r = m; }
		else { l = m + 1; }
	}
	return fallback;
}

static n2_unicp_t n2i_unicode_latin_tolower(n2_unicp_t unicp)
{
	if (unicp >= 0x41 && unicp <= 0x5a) { return unicp + 0x20; }
	return unicp;
}

static n2_unicp_t n2i_unicode_latin_toupper(n2_unicp_t unicp)
{
	if (unicp >= 0x61 && unicp <= 0x7a) { return unicp - 0x20; }
	return unicp;
}

static const struct
{
	n2_encoding_e encoding_;
	const char* name_;
} n2i_encoding_table[] =
{
	{N2_ENCODING_UTF8,		"utf8"},
	{N2_ENCODING_UTF16LE,	"utf16le"},
	{N2_ENCODING_UTF16BE,	"utf16be"},
	{N2_ENCODING_CP932,		"cp932"},
	{N2_ENCODING_UNKNOWN,	NULL}
};

N2_API n2_encoding_e n2_encoding_find(const char* name, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(name); }

	// 全探索
	for (size_t i = 0; n2i_encoding_table[i].name_; ++i)
	{
		const size_t name_length = N2_STRLEN(n2i_encoding_table[i].name_);
		if (length == name_length && N2_STRNCMP(name, n2i_encoding_table[i].name_, name_length) == 0)
		{
			return n2i_encoding_table[i].encoding_;
		}
	}
	return N2_ENCODING_UNKNOWN;
}

N2_API const char* n2_encoding_name(n2_encoding_e encoding, const char* on_not_found)
{
	if (encoding < 0 || encoding >= N2_MAX_ENCODING) { return on_not_found; }
	return n2i_encoding_table[encoding].name_;
}

N2_API n2_bool_t n2_unicode_is_newline(n2_unicp_t unicp)
{
	return unicp == 0x0d/*CR*/ || unicp == 0x0a/*LF*/ || unicp == 0x85/*NEL*/ || unicp == 0x2028/*LS*/ || unicp == 0x2029/*PS*/;
}

N2_API const char* n2_encoding_utf8_fetch(const char* str, n2_unicp_t* dst)
{
	const unsigned char* p = N2_RCAST(const unsigned char*, str);
	if ((p[0] & 0xf8) == 0xf0)
	{
		if (dst) { *dst = ((p[0] & 0x07) << 18) | ((p[1] & 0x3f) << 12) | ((p[2] & 0x3f) << 6) | (p[3] & 0x3f); }
		p += 4;
	}
	else if ((p[0] & 0xf0) == 0xe0)
	{
		if (dst) { *dst = ((p[0] & 0x0f) << 12) | ((p[1] & 0x3f) << 6) | (p[2] & 0x3f); }
		p += 3;
	}
	else if ((p[0] & 0xe0) == 0xc0)
	{
		if (dst) { *dst = ((p[0] & 0x1f) << 6) | (p[1] & 0x3f); };
		p += 2;
	}
	else
	{
		if (dst) { *dst = p[0]; }
		p += 1;
	}

	return N2_RCAST(const char*, p);
}

N2_API size_t n2_encoding_utf8_bytesize(n2_unicp_t unicp)
{
	if ((unicp & 0xffffff80)== 0) { return 1; }
	else if ((unicp & 0xfffff800) == 0) { return 2; }
	else if ((unicp & 0xffff0000) == 0) { return 3; }
	return 4;
}

N2_API char* n2_encoding_utf8_print(char* dst, size_t dst_size, n2_unicp_t unicp)
{
	N2_ASSERT(dst);
	unsigned char* p = N2_RCAST(unsigned char*, dst);

	const size_t size = n2_encoding_utf8_bytesize(unicp);
	if (dst_size < size) { return NULL; }

	switch (size)
	{
	case 1:
		p[0] = N2_SCAST(unsigned char, unicp);
		break;
	case 2:
		p[0] = N2_SCAST(unsigned char, 0xc0 | (unicp >> 6));
		p[1] = N2_SCAST(unsigned char, 0x80 | (unicp & 0x3f));
		break;
	case 3:
		p[0] = N2_SCAST(unsigned char, 0xe0 | (unicp >> 12));
		p[1] = N2_SCAST(unsigned char, 0x80| ((unicp >> 6) & 0x3f));
		p[2] = N2_SCAST(unsigned char, 0x80| (unicp & 0x3f));
		break;
	case 4:
		p[0] = N2_SCAST(unsigned char, 0xf0 | (unicp >> 18));
		p[1] = N2_SCAST(unsigned char, 0x80| ((unicp >> 12) & 0x3f));
		p[2] = N2_SCAST(unsigned char, 0x80| ((unicp >> 6) & 0x3f));
		p[3] = N2_SCAST(unsigned char, 0x80| (unicp & 0x3f));
		break;
	default:
		N2_ASSERT(0);
		return NULL;
	}
	return N2_RCAST(char*, p + size);
}

N2_API int n2_encoding_utf8_verify(const char* str, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(str); }
	const unsigned char* s = N2_RCAST(const unsigned char*, str);
	const unsigned char* e = s + length;
	const unsigned char* p = s;

	while (p < e)
	{
		if ((p[0] & 0xf8) == 0xf0)
		{
			if (((p[1] & 0xc0) != 0x80) || ((p[2] & 0xc0) != 0x80) || ((p[3] & 0xc0) != 0x80)) { return N2_SCAST(int, p - s); }// invalid codeunit sequence
			if ((p[4] & 0xc0) == 0x80) { return N2_SCAST(int, p - s); }// isolated trailing sequential codeunit
			if (((p[0] & 0x07) == 0x00) && ((p[1] & 0x30) == 0x00)) { return N2_SCAST(int, p - s); }// redundunt encoding
			p += 4;
		}
		else if ((p[0] & 0xf0) == 0xe0)
		{
			if (((p[1] & 0xc0) != 0x80) || ((p[2] & 0xc0) != 0x80)) { return N2_SCAST(int, p - s); }// invalid codeunit sequence
			if ((p[3] & 0xc0) == 0x80) { return N2_SCAST(int, p - s); }// isolated trailing sequential codeunit
			if (((p[0] & 0x0f) == 0x00) && ((p[1] & 0x20) == 0x00)) { return N2_SCAST(int, p - s); }// redundunt encoding
			p += 3;
		}
		else if ((p[0] & 0xe0) == 0xc0)
		{
			if ((p[1] & 0xc0) != 0x80) { return N2_SCAST(int, p - s); }// invalid codeunit sequence
			if ((p[2] & 0xc0) == 0x80) { return N2_SCAST(int, p - s); }// isolated trailing sequential codeunit
			if ((p[0] & 0x1e) == 0x00) { return N2_SCAST(int, p - s); }// redundunt encoding
			p += 2;
		}
		else if ((p[0] & 0x80) == 0x00)
		{
			// ok, valid codeunit sequence
			p += 1;
		}
		else
		{
			// invalid codeunit sequence
			return N2_SCAST(int, p - s);
		}
	}

	return -1;
}

typedef uint16_t (*n2i_encoding_fetch16_t)(const char* str);
typedef void (*n2i_encoding_print16_t)(char* dst, uint16_t v);

static const char* n2i_encoding_utf16_fetch(const char* str, n2_unicp_t* dst, n2i_encoding_fetch16_t fetch)
{
	const char* p = str;
	if ((fetch(p + 0) & 0xfc00) == 0xd800)
	{
		if (dst) { *dst = (((fetch(p + 0) & 0x03ff) << 10) | (fetch(p + 2) & 0x03ff)) + 0x10000; }
		p += 4;
	}
	else
	{
		if (dst) { *dst = fetch(p + 0); }
		p += 2;
	}

	return p;
}

static char* n2i_encoding_utf16_print(char* dst, size_t dst_size, n2_unicp_t unicp, n2i_encoding_print16_t print)
{
	N2_ASSERT(dst);

	const size_t size = n2_encoding_utf16_bytesize(unicp);
	if (dst_size < size) { return NULL; }

	switch (size)
	{
	case 2:
		print(dst + 0, N2_SCAST(uint16_t, unicp & 0xffff));
		break;
	case 4:
		unicp -= 0x10000;
		print(dst + 0, N2_SCAST(uint16_t, 0xd800 | ((unicp >> 10) & 0x03ff)));
		print(dst + 2, N2_SCAST(uint16_t, 0xdc00 | (unicp & 0x03ff)));
		break;
	default:
		N2_ASSERT(0);
		return NULL;
	}
	return dst + size;
}

static size_t n2i_encoding_utf16_length(const char* str, size_t length)
{
	size_t compute = 0;
	const unsigned char* s = N2_RCAST(const unsigned char*, str);
	const unsigned char* e = s + length;
	while (s < e)
	{
		if (s[0] == 0 && s[1] == 0) { break; }
		s += 2; compute += 2;
	}
	return N2_MIN(compute, length);
}

static int n2i_encoding_utf16_verify(const char* str, size_t length, n2i_encoding_fetch16_t fetch)
{
	if (length == SIZE_MAX) { length = n2i_encoding_utf16_length(str, SIZE_MAX); }

	const char* s = str;
	const char* e = n2_cptr_offset(s, length);
	const char* p = s;

	while (p < e)
	{
		if ((fetch(p + 0) & 0xfc00) == 0xd800)
		{
			if ((fetch(p + 2) & 0xfc00) != 0xdc00) { return N2_SCAST(int, p - s); }// invalid codeunit sequence
			if ((fetch(p + 0) & 0x03fc) == 0x0000) { return N2_SCAST(int, p - s); }// redundunt encoding
			p += 4;
		}
		else if (fetch(p + 0) < 0xd800 || fetch(p + 0) >= 0xe000)
		{
			// ok, valid codeunit sequence
			p += 2;
		}
		else
		{
			// invalid codeunit sequence
			return N2_SCAST(int, p - s);
		}
	}

	return -1;
}

static n2_bool_t n2i_encoding_utf16_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback, n2i_encoding_print16_t print)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	const char* src_end = src + src_length;
	n2_unicp_t unicp = 0;
	n2_bool_t res = N2_TRUE;
	while (src < src_end)
	{
		src = n2_encoding_utf8_fetch(src, &unicp);
		if (unicp < 0) { res = N2_FALSE; unicp = fallback; }
		const size_t bytesize = n2_encoding_utf16_bytesize(unicp);
		n2_str_reserve(state, dst, dst->size_ + bytesize);
		const char* nstr = n2i_encoding_utf16_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, unicp, print);
		dst->size_ += bytesize;
		N2_ASSERT(N2_SCAST(size_t, nstr - dst->str_) == dst->size_);
		N2_UNUSE(nstr);
	}
	// null
	{
		unicp = 0;
		const size_t bytesize = n2_encoding_utf16_bytesize(unicp);
		n2_str_reserve(state, dst, dst->size_ + bytesize);
		n2i_encoding_utf16_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, unicp, print);
		dst->size_ += bytesize;
	}
	return res;
}

static n2_bool_t n2i_encoding_utf16_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback, n2i_encoding_fetch16_t fetch)
{
	if (src_length == SIZE_MAX) { src_length = n2_encoding_utf16ne_length(src, SIZE_MAX); }
	const char* src_end = src + src_length;
	n2_unicp_t unicp = 0;
	n2_bool_t res = N2_TRUE;
	while (src < src_end)
	{
		src = n2i_encoding_utf16_fetch(src, &unicp, fetch);
		if (unicp < 0) { res = N2_FALSE; unicp = fallback; }
		n2_str_reserve(state, dst, dst->size_ + N2_CODEPOINT_MAX_BUFFER_SIZE);
		const char* nstr = n2_encoding_utf8_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, unicp);
		dst->size_ = nstr - dst->str_;
	}
	n2_str_append(state, dst, "\0", SIZE_MAX);
	return res;
}

N2_API size_t n2_encoding_utf16_bytesize(n2_unicp_t unicp)
{
	if (unicp < 0xd800 || (unicp >= 0xe000 && unicp < 0x10000)) { return 2; }
	return 4;
}

static uint16_t n2i_encoding_fetch16ne(const char* str)
{
	uint16_t res = 0;
	N2_MEMCPY(&res, str, 2);
	return res;
}

static void n2i_encoding_print16ne(char* dst, uint16_t v)
{
	N2_MEMCPY(dst, &v, 2);
}

N2_API const char* n2_encoding_utf16ne_fetch(const char* str, n2_unicp_t* dst)
{
	return n2i_encoding_utf16_fetch(str, dst, n2i_encoding_fetch16ne);
}

N2_API char* n2_encoding_utf16ne_print(char* dst, size_t dst_size, n2_unicp_t unicp)
{
	return n2i_encoding_utf16_print(dst, dst_size, unicp, n2i_encoding_print16ne);
}

N2_API size_t n2_encoding_utf16ne_length(const char* str, size_t length)
{
	return n2i_encoding_utf16_length(str, length);
}

N2_API int n2_encoding_utf16ne_verify(const char* str, size_t length)
{
	return n2i_encoding_utf16_verify(str, length, n2i_encoding_fetch16ne);
}

N2_API n2_bool_t n2_encoding_utf16ne_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_from_utf8(state, dst, src, src_length, fallback, n2i_encoding_print16ne);
}

N2_API n2_bool_t n2_encoding_utf16ne_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_to_utf8(state, dst, src, src_length, fallback, n2i_encoding_fetch16ne);
}

static uint16_t n2i_encoding_fetch16le(const char* str)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, str);
	return p[0] | (p[1] << 8);
}

static void n2i_encoding_print16le(char* dst, uint16_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, dst);
	p[0] = v & 0xff;
	p[1] = (v >> 8) & 0xff;
}

N2_API const char* n2_encoding_utf16le_fetch(const char* str, n2_unicp_t* dst)
{
	return n2i_encoding_utf16_fetch(str, dst, n2i_encoding_fetch16le);
}

N2_API char* n2_encoding_utf16le_print(char* dst, size_t dst_size, n2_unicp_t unicp)
{
	return n2i_encoding_utf16_print(dst, dst_size, unicp, n2i_encoding_print16le);
}

N2_API size_t n2_encoding_utf16le_length(const char* str, size_t length)
{
	return n2i_encoding_utf16_length(str, length);
}

N2_API int n2_encoding_utf16le_verify(const char* str, size_t length)
{
	return n2i_encoding_utf16_verify(str, length, n2i_encoding_fetch16le);
}

N2_API n2_bool_t n2_encoding_utf16le_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_from_utf8(state, dst, src, src_length, fallback, n2i_encoding_print16le);
}

N2_API n2_bool_t n2_encoding_utf16le_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_to_utf8(state, dst, src, src_length, fallback, n2i_encoding_fetch16le);
}

static uint16_t n2i_encoding_fetch16be(const char* str)
{
	const uint8_t* p = N2_RCAST(const uint8_t*, str);
	return (p[0] << 8) | p[1];
}

static void n2i_encoding_print16be(char* dst, uint16_t v)
{
	uint8_t* p = N2_RCAST(uint8_t*, dst);
	p[0] = (v >> 8) & 0xff;
	p[1] = v & 0xff;
}

N2_API const char* n2_encoding_utf16be_fetch(const char* str, n2_unicp_t* dst)
{
	return n2i_encoding_utf16_fetch(str, dst, n2i_encoding_fetch16be);
}

N2_API char* n2_encoding_utf16be_print(char* dst, size_t dst_size, n2_unicp_t unicp)
{
	return n2i_encoding_utf16_print(dst, dst_size, unicp, n2i_encoding_print16be);
}

N2_API size_t n2_encoding_utf16be_length(const char* str, size_t length)
{
	return n2i_encoding_utf16_length(str, length);
}

N2_API int n2_encoding_utf16be_verify(const char* str, size_t length)
{
	return n2i_encoding_utf16_verify(str, length, n2i_encoding_fetch16be);
}

N2_API n2_bool_t n2_encoding_utf16be_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_from_utf8(state, dst, src, src_length, fallback, n2i_encoding_print16be);
}

N2_API n2_bool_t n2_encoding_utf16be_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	return n2i_encoding_utf16_convert_to_utf8(state, dst, src, src_length, fallback, n2i_encoding_fetch16be);
}

#if N2_CONFIG_USE_ENCODING_CP932
#include "inline/cp932.h"

N2_API n2_unicp_t n2_encoding_cp932_to_unicode(n2_codepoint_t codepoint, n2_unicp_t fallback)
{
	return N2_SCAST(n2_unicp_t, n2i_encoding_fetch_table(codepoint, N2_SCAST(n2_codepoint_t, fallback), n2i_cp932_to_unicode, N2_ARRAYDIM(n2i_cp932_to_unicode)));
}

N2_API n2_codepoint_t n2_encoding_cp932_from_unicode(n2_unicp_t unicp, n2_codepoint_t fallback)
{
	return n2i_encoding_fetch_table(N2_SCAST(n2_codepoint_t, unicp), fallback, n2i_unicode_to_cp932, N2_ARRAYDIM(n2i_unicode_to_cp932));
}

N2_API const char* n2_encoding_cp932_fetch(const char* str, n2_codepoint_t* dst)
{
	const unsigned char* p = N2_RCAST(const unsigned char*, str);
	if ((p[0] >= 0x81 && p[0] <= 0x9f) || (p[0] >= 0xe0 && p[0] <= 0xfc))
	{
		if (dst) { *dst = (p[0] << 8) | (p[1] & 0xff); }
		p += 2;
	}
	else
	{
		if (dst) { *dst = p[0]; }
		++p;
	}
	return N2_RCAST(const char*, p);
}

N2_API size_t n2_encoding_cp932_bytesize(n2_codepoint_t codepoint)
{
	if ((codepoint > 0xff)== 0) { return 2; }
	return 1;
}

N2_API char* n2_encoding_cp932_print(char* dst, size_t dst_size, n2_codepoint_t codepoint)
{
	N2_ASSERT(dst);
	unsigned char* p = N2_RCAST(unsigned char*, dst);

	const size_t size = n2_encoding_utf8_bytesize(codepoint);
	if (dst_size < size) { return NULL; }

	switch (size)
	{
	case 1:
		p[0] = N2_SCAST(unsigned char, codepoint & 0xff);
		break;
	case 2:
		p[0] = N2_SCAST(unsigned char, (codepoint >> 8) & 0xff);
		p[1] = N2_SCAST(unsigned char, (codepoint & 0xff));
		break;
	default:
		N2_ASSERT(0);
		return NULL;
	}
	return N2_RCAST(char*, p + size);
}

N2_API int n2_encoding_cp932_verify(const char* str, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(str); }
	const unsigned char* s = N2_RCAST(const unsigned char*, str);
	const unsigned char* e = s + length;
	const unsigned char* p = s;

	while (p < e)
	{
		if ((p[0] >= 0x81 && p[0] <= 0x9f) || (p[0] >= 0xe0 && p[0] <= 0xfc))
		{
			if ((p[1] < 0x40) || (p[1] == 0x7f) || (p[1] > 0xfc)) { return N2_SCAST(int, p - s); }// invalid codeunit sequence
			p += 2;
		}
		else
		{
			if ((p[0] == 0x80) || (p[0] == 0xa0) || (p[0] > 0xfc)) { return N2_SCAST(int, p - s); }// invalid codepoint
			p += 1;
		}
	}

	return -1;
}

N2_API n2_bool_t n2_encoding_cp932_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_codepoint_t fallback)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	const char* src_end = src + src_length;
	n2_codepoint_t cp = 0;
	n2_unicp_t unicp = 0;
	n2_bool_t res = N2_TRUE;
	while (src < src_end)
	{
		src = n2_encoding_utf8_fetch(src, &unicp);
		if (unicp < 0) { res = N2_FALSE; unicp = fallback; }
		n2_str_reserve(state, dst, dst->size_ + N2_CODEPOINT_MAX_BUFFER_SIZE);
		cp = n2_encoding_cp932_from_unicode(unicp, fallback);
		const char* nstr = n2_encoding_cp932_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, cp);
		dst->size_ = nstr - dst->str_;
	}
	// null
	{
		unicp = 0;
		n2_str_reserve(state, dst, dst->size_ + N2_CODEPOINT_MAX_BUFFER_SIZE);
		cp = n2_encoding_cp932_from_unicode(unicp, fallback);
		const char* nstr = n2_encoding_cp932_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, cp);
		dst->size_ = nstr - dst->str_;
	}
	return res;
}

N2_API n2_bool_t n2_encoding_cp932_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	const char* src_end = src + src_length;
	n2_codepoint_t cp = 0;
	n2_unicp_t unicp = 0;
	n2_bool_t res = N2_TRUE;
	while (src < src_end)
	{
		cp = 0;
		src = n2_encoding_cp932_fetch(src, &cp);
		unicp = n2_encoding_cp932_to_unicode(cp, -1);
		if (unicp < 0) { res = N2_FALSE; unicp = fallback; }
		n2_str_reserve(state, dst, dst->size_ + N2_CODEPOINT_MAX_BUFFER_SIZE);
		const char* nstr = n2_encoding_utf8_print(dst->str_ + dst->size_, dst->buffer_size_ - dst->size_, unicp);
		dst->size_ = nstr - dst->str_;
	}
	n2_str_append(state, dst, "\0", SIZE_MAX);
	return res;
}
#endif

//=============================================================================
// 文字列ユーティリティ
N2_API int n2_snprintf(char* buf, size_t bufsize, const char* fmt, ...)
{
	int res;
	va_list args;
	va_start(args, fmt);
	res = n2_vsnprintf(buf, bufsize, fmt, args);
	va_end(args);
	return res;
}

N2_API int n2_vsnprintf(char* buf, size_t bufsize, const char* fmt, va_list args)
{
	int res;
#if N2_CONFIG_USE_SPRINTF_LIB
	res = stbsp_vsnprintf(buf, N2_SCAST(int, bufsize), fmt, args);
#else
	res = N2_VSNPRINTF(buf, bufsize, fmt, args);
#endif
	return res;
}

N2_API char* n2_plstr_clone_size(n2_state_t* state, const char* s, size_t l)
{
	char* const a = N2_TMALLOCA(char, state, l + 1);
	if (!a) { return NULL; }
	N2_MEMCPY(a, s, sizeof(char) * l);
	a[l] = '\0';
	return a;
}

N2_API char* n2_plstr_clone(n2_state_t* state, const char* s)
{
	return n2_plstr_clone_size(state, s, N2_STRLEN(s));
}

N2_API int n2_plstr_ncmp_sized(const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length)
{
	for (size_t i = 0, l = N2_MIN(lhs_length, rhs_length); i < l; ++i)
	{
		if (lhs[i] != rhs[i]) { return lhs[i] < rhs[i] ? -1 : 1; }
	}
	if (lhs_length != rhs_length) { return lhs_length < rhs_length ? -1 : 1; }
	return 0;
}

N2_API int n2_plstr_ncmp_sized_fast(const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length)
{
	if (lhs_length != rhs_length) { return lhs_length < rhs_length ? -1 : 1; }
	return N2_STRNCMP(lhs, rhs, lhs_length);
}

N2_API int n2_plstr_cmp_case(const char* lhs, const char* rhs)
{
	char lc, rc; size_t i;
	for (i = 0; lhs[i] != '\0'; ++i)
	{
		lc = n2i_char_tolower(lhs[i]); rc = n2i_char_tolower(rhs[i]);
		if (lc != rc) { return lc < rc ? -1 : 1; }
	}
	if (rhs[i] != '\0') { return -1; }
	return 0;
}

N2_API int n2_plstr_ncmp_case(const char* lhs, const char* rhs, size_t size)
{
	char lc, rc;
	for (size_t i = 0; i < size; ++i)
	{
		lc = n2i_char_tolower(lhs[i]); rc = n2i_char_tolower(rhs[i]);
		if (lc != rc) { return lc < rc ? -1 : 1; }
	}
	return 0;
}

N2_API int n2_plstr_search(const char* str, size_t str_len, const char* pattern, size_t pattern_len)
{
	if (str_len == SIZE_MAX) { str_len = N2_STRLEN(str); }
	if (pattern_len == SIZE_MAX) { pattern_len = N2_STRLEN(pattern); }
	if (str_len < pattern_len) { return -1; }
	for (size_t i = 0, l = (str_len - pattern_len); i <= l; ++i)
	{
		if (N2_STRNCMP(str + i, pattern, pattern_len) == 0) { return N2_SCAST(int, i); }
	}
	return -1;
}

static void n2i_str_cutoff_append(n2_state_t* state, n2_str_t* str, const char* head, size_t max_char_num, char delimiter, const char* cutoff_tail)
{
	n2_bool_t append_tail; const char* tail;
	append_tail = N2_TRUE; tail = head;
	for (size_t i = 0; i < max_char_num + 1; ++i) { if (*tail == '\0' || *tail == delimiter) { append_tail = N2_FALSE; break; } ++tail; }
	n2_str_append(state, str, head, N2_SCAST(size_t, tail - head));
	if (append_tail) { n2_str_append(state, str, cutoff_tail, SIZE_MAX); }
}

static void n2i_str_convert_to_lower(n2_str_t* str)
{
	for (size_t i = 0; i < str->size_; ++i) { str->str_[i] = n2i_char_tolower(str->str_[i]); }
}

N2_API void n2_str_init(n2_str_t* str)
{
	str->str_ = NULL;
	str->size_ = 0;
	str->buffer_size_ = 0;
	str->expand_step_ = 16;
}

N2_API void n2_str_teardown(n2_state_t* state, n2_str_t* str)
{
	N2_ASSERT(state);
	if (str->str_)
	{
		n2_free(state, str->str_);
		str->str_ = NULL;
	}
	str->size_ = 0;
	str->buffer_size_ = 0;
}

N2_API const char* n2_str_cstr(const n2_str_t* str)
{
	return N2_SCAST(const char*, str->str_);
}

N2_API void n2_str_set_expand_step(n2_str_t* str, size_t expand_step)
{
	str->expand_step_ = expand_step;
}

N2_API void n2_str_vfmt_to(n2_state_t* state, n2_str_t* str, const char* fmt, va_list args)
{
	va_list targs;
	va_copy(targs, args);
	int required_size = n2_vsnprintf(NULL, 0, fmt, targs);
	va_end(targs);

	if (required_size < 0) { N2_ASSERT(0); n2_str_clear(str); return; }

	n2_str_reserve(state, str, N2_SCAST(size_t, required_size + 1));

	va_copy(targs, args);
	int written_size = n2_vsnprintf(str->str_, str->buffer_size_, fmt, targs);
	va_end(targs);

	const size_t final_size = N2_MIN(N2_SCAST(size_t, written_size), str->buffer_size_ - 1);
	str->str_[final_size] = '\0';
	str->size_ = written_size;
}

N2_API void n2_str_fmt_to(n2_state_t* state, n2_str_t* str, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, str, fmt, args);
	va_end(args);
}

N2_API void n2_str_copy_to(n2_state_t* state, n2_str_t* str, const n2_str_t* rstr)
{
	N2_ASSERT(str);
	if (rstr->str_)
	{
		n2_str_reserve(state, str, rstr->size_ + 1);
		N2_MEMCPY(str->str_, rstr->str_, sizeof(char) * rstr->size_);
		str->size_ = rstr->size_;
		str->str_[str->size_] = '\0';
		str->buffer_size_ = rstr->size_ + 1;
	}
	else
	{
		n2_str_clear(str);
	}
}

N2_API void n2_str_swap(n2_str_t* str, n2_str_t* rstr)
{
	n2_str_t t = *str;
	*str = *rstr;
	*rstr = t;
}

N2_API void n2_str_clear(n2_str_t* str)
{
	if (str->str_ && str->buffer_size_ > 0) { str->str_[0] = '\0'; }
	str->size_ = 0;
}

N2_API n2_bool_t n2_str_reserve(n2_state_t* state, n2_str_t* str, size_t size)
{
	N2_ASSERT(str);
	if (!str->str_)
	{
		if (size > 0)
		{
			const size_t next_size = N2_MAX(size + 1, str->expand_step_);
			str->str_ = n2_malloc(state, next_size);
			if (!str->str_) { return N2_FALSE; }
			str->str_[0] = '\0';
			str->buffer_size_ = next_size;
		}
	}
	else if (str->buffer_size_ < size)
	{
		const size_t next_size = N2_MAX(size + 1, str->buffer_size_ + (str->expand_step_ == 0 ? str->buffer_size_ : str->expand_step_));
		char* next_str = N2_RCAST(char*, n2_realloc(state, next_size, str->str_, str->buffer_size_));
		if (!next_str) { return N2_FALSE; }
		str->str_ = next_str;
		str->buffer_size_ = next_size;
	}
	return N2_TRUE;
}

N2_API size_t n2_str_compute_size(const n2_str_t* str)
{
	N2_ASSERT(str);
	return N2_STRNLEN(str->str_, str->buffer_size_);
}

N2_API size_t n2_str_compute_ut16ne_size(const n2_str_t* str)
{
	N2_ASSERT(str);
	return N2_STRNLEN(str->str_, str->buffer_size_);
}

N2_API void n2_str_update_size(n2_str_t* str)
{
	N2_ASSERT(str);
	str->size_ = n2_str_compute_size(str);
}

N2_API int n2_str_compare(const n2_str_t* lhs, const n2_str_t* rhs)
{
	if (!lhs || !rhs) { return lhs == rhs ? 0 : lhs ? 1 : -1; }
	return n2_plstr_ncmp_sized(lhs->str_, lhs->size_, rhs->str_, rhs->size_);
}

N2_API void n2_str_set(n2_state_t* state, n2_str_t* str, const char* cstr, size_t length)
{
	N2_ASSERT(str);
	N2_ASSERT(cstr);

	if (length == SIZE_MAX) { length = N2_STRLEN(cstr); }
	n2_str_reserve(state, str, length + 1);

	N2_MEMCPY(str->str_, cstr, sizeof(char) * length);
	str->str_[length] = '\0';
	str->size_ = length;
}

N2_API n2_bool_t n2_str_insert(n2_state_t* state, n2_str_t* str, size_t offset, const char* add_str, size_t add_length)
{
	N2_ASSERT(str);
	N2_ASSERT(add_str);

	if (add_length == SIZE_MAX) { add_length = N2_STRLEN(add_str); }
	if (add_length <= 0) { return N2_TRUE; }

	if (offset > str->size_) { return N2_FALSE; }

	const size_t left = str->buffer_size_ - str->size_;
	const size_t required = add_length + 1;
	if (left < required) { n2_str_reserve(state, str, str->buffer_size_ + (required - left)); }

	if (offset < str->size_) { N2_MEMMOVE(str->str_ + offset + add_length, str->str_ + offset, str->size_); }
	N2_MEMCPY(str->str_ + offset, add_str, add_length);
	str->size_ += add_length;
	str->str_[str->size_] = '\0';
	return N2_TRUE;
}

N2_API void n2_str_prepend(n2_state_t* state, n2_str_t* str, const char* add_str, size_t add_length)
{
	n2_str_insert(state, str, 0, add_str, add_length);
}

N2_API void n2_str_appendv(n2_state_t* state, n2_str_t* str, char c)
{
	n2_str_append(state, str, &c, 1);
}

N2_API void n2_str_append(n2_state_t* state, n2_str_t* str, const char* append_str, size_t append_length)
{
	N2_ASSERT(str);
	N2_ASSERT(append_str);

	if (append_length >= SIZE_MAX) { append_length = N2_STRLEN(append_str); }
	if (append_length <= 0) { return; }

	const size_t left = str->buffer_size_ - str->size_;
	const size_t required = append_length + 1;
	if (left < required) { n2_str_reserve(state, str, str->buffer_size_ + (required - left)); }

	N2_MEMCPY(str->str_ + str->size_, append_str, append_length);
	str->size_ += append_length;
	str->str_[str->size_] = '\0';
}

N2_API void n2_str_append_fmt(n2_state_t* state, n2_str_t* str, const char* fmt, ...)
{
	n2_str_t tstr;
	n2_str_init(&tstr);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &tstr, fmt, args);
	va_end(args);
	n2_str_append(state, str, tstr.str_, tstr.size_);
	n2_str_teardown(state, &tstr);
}

N2_API int n2_str_find(const n2_str_t* str, const char* pattern, size_t pattern_length, size_t offset)
{
	if (pattern_length == SIZE_MAX) { pattern_length = N2_STRLEN(pattern); }
	if (str->size_ < pattern_length + offset) { return -1; }
	for (size_t i = offset, l = str->size_ - pattern_length; i <= l; ++i)
	{
		if (str->str_[i] == pattern[0] && N2_STRNCMP(str->str_ + i, pattern, pattern_length) == 0) { return N2_SCAST(int, i); }
	}
	return -1;
}

N2_API int n2_str_rfind(const n2_str_t* str, const char* pattern, size_t pattern_length, size_t offset)
{
	if (pattern_length == SIZE_MAX) { pattern_length = N2_STRLEN(pattern); }
	if (str->size_ < pattern_length + offset) { return -1; }
	for (size_t i = offset, l = str->size_ - pattern_length; i <= l; ++i)
	{
		const size_t index = str->size_ - i - 1;
		if (str->str_[index] == pattern[0] && N2_STRNCMP(str->str_ + index, pattern, pattern_length) == 0) { return N2_SCAST(int, index); }
	}
	return -1;
}

N2_API n2_bool_t n2_str_starts_with(const n2_str_t* str, const char* pattern, size_t pattern_length)
{
	if (pattern_length == SIZE_MAX) { pattern_length = N2_STRLEN(pattern); }
	if (str->size_ < pattern_length) { return N2_FALSE; }
	return N2_MEMCMP(str->str_, pattern, pattern_length) == 0;
}

N2_API n2_bool_t n2_str_ends_with(const n2_str_t* str, const char* pattern, size_t pattern_length)
{
	if (pattern_length == SIZE_MAX) { pattern_length = N2_STRLEN(pattern); }
	if (str->size_ < pattern_length) { return N2_FALSE; }
	return N2_MEMCMP(str->str_ + str->size_ - pattern_length, pattern, pattern_length) == 0;
}

N2_API size_t n2_str_erase(n2_str_t* str, size_t offset, size_t length)
{
	if (length <= 0) { return 0; }
	if (offset >= str->size_) { return 0; }
	length = N2_MIN(length, str->size_ - offset);
	N2_MEMMOVE(str->str_ + offset, str->str_ + offset + length, str->size_ + 1 - offset - length);
	str->size_ -= length;
	return length;
}

N2_API n2_bool_t n2_str_replace_range(n2_state_t* state, n2_str_t* str, size_t offset, size_t size, const char* to, size_t to_length)
{
	if (offset > str->size_) { return N2_FALSE; }
	if (to_length == SIZE_MAX) { to_length = N2_STRLEN(to); }
	if (offset + size > str->size_) { size = str->size_ - offset; }
	int diff = N2_SCAST(int, to_length) - N2_SCAST(int, size);
	if (size < to_length) { n2_str_reserve(state, str, str->size_ + to_length - size + 1); }
	N2_MEMMOVE(str->str_ + offset + N2_SCAST(int, to_length), str->str_ + offset + N2_SCAST(int, size), N2_SCAST(int, str->size_ + 1) - offset - N2_SCAST(int, size));
	(diff < 0 ? (str->size_ -= N2_SCAST(size_t, -diff)) : (str->size_ += N2_SCAST(size_t, diff)));
	if (to_length > 0) { N2_MEMCPY(str->str_ + offset, to, to_length); }
	return N2_TRUE;
}

N2_API size_t n2_str_replace_pattern(n2_state_t* state, n2_str_t* str, const char* src, size_t src_length, const char* to, size_t to_length)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	if (to_length == SIZE_MAX) { to_length = N2_STRLEN(to); }
	if (src_length <= 0) { return 0; }
	if (str->size_ < src_length) { return 0; }
	size_t replace_count = 0;
	for (int i = N2_SCAST(int, str->size_ - src_length); i >= 0; --i)
	{
		if (str->str_[i] == src[0] && N2_STRNCMP(str->str_ + i, src, src_length) == 0)
		{
			if (src_length != to_length)
			{
				int diff = N2_SCAST(int, to_length) - N2_SCAST(int, src_length);
				if (src_length < to_length) { n2_str_reserve(state, str, str->size_ + to_length - src_length + 1); }
				N2_MEMMOVE(str->str_ + i + N2_SCAST(int, to_length), str->str_ + i + N2_SCAST(int, src_length), N2_SCAST(int, str->size_ + 1) - i - N2_SCAST(int, src_length));
				(diff < 0 ? (str->size_ -= N2_SCAST(size_t, -diff)) : (str->size_ += N2_SCAST(size_t, diff)));
			}
			if (to_length > 0) { N2_MEMCPY(str->str_ + i, to, to_length); }
			i -= N2_SCAST(int, src_length) - 1;
			++replace_count;
			continue;
		}
	}
	n2_str_update_size(str);
	return replace_count;
}

N2_API size_t n2_str_trim(n2_str_t* str, const char* src, size_t src_length, n2_bool_t left)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	size_t erased_count = 0;
	if (left)
	{
		size_t p = 0;
		while (p + src_length < str->size_)
		{
			if (str->str_[p] == src[0] && N2_STRNCMP(str->str_ + p, src, src_length)) { break; }
			p += src_length;
		}
		if (p > 0) { n2_str_erase(str, 0, p); }
		erased_count = p;
	}
	else
	{
		size_t p = 0;
		while (p + src_length < str->size_)
		{
			if (str->str_[str->size_ - p] == src[0] && N2_STRNCMP(str->str_ + str->size_ - p, src, src_length)) { break; }
			p += src_length;
		}
		if (p > 0) { n2_str_erase(str, str->size_ - p, p); }
		erased_count = p;
	}
	return erased_count;
}

N2_API n2_bool_t n2_str_trim_utf8_bom(n2_str_t* str)
{
	if (str->size_ < 3) { return N2_FALSE; }
	const unsigned char* p = N2_RCAST(const unsigned char*, str->str_);
	if (p[0] != 0xfe && p[1] != 0xbb && p[2] != 0xbf) { return N2_FALSE; }
	n2_str_erase(str, 0, 3);
	return N2_TRUE;
}

static n2_bool_t n2i_str_trim_utf16_bom(n2_str_t* str, n2i_encoding_fetch16_t fetch)
{
	if (str->size_ < 2) { return N2_FALSE; }
	const uint16_t sig = fetch(str->str_);
	if (sig != 0xfeff) { return N2_FALSE; }
	n2_str_erase(str, 0, 2);
	return N2_TRUE;
}

N2_API n2_bool_t n2_str_trim_utf16ne_bom(n2_str_t* str)
{
	return n2i_str_trim_utf16_bom(str, n2i_encoding_fetch16ne);
}

N2_API n2_bool_t n2_str_trim_utf16le_bom(n2_str_t* str)
{
	return n2i_str_trim_utf16_bom(str, n2i_encoding_fetch16le);
}

N2_API n2_bool_t n2_str_trim_utf16be_bom(n2_str_t* str)
{
	return n2i_str_trim_utf16_bom(str, n2i_encoding_fetch16be);
}

N2_API n2_bool_t n2_str_escaped_to(n2_state_t* state, n2_str_t* str, const char* src, size_t length, size_t flags)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(src); }
	n2_str_reserve(state, str, length + 1);
	n2_str_clear(str);

	n2_bool_t res = N2_TRUE;
	for (size_t i = 0; i < length && res; ++i)
	{
		switch (src[i])
		{
		case '\0':	n2_str_append(state, str, "\\0", 2); break;
		case '\t':	n2_str_append(state, str, "\\t", 2); break;
		case '\n':	n2_str_append(state, str, "\\n", 2);; break;
		case '\'':	if (flags & N2_STR_ESCAPE_FLAG_NO_SINGLEQUOTE) { n2_str_append(state, str, "\'", 1); } else { n2_str_append(state, str, "\\\'", 2); } break;
		case '"':	if (flags & N2_STR_ESCAPE_FLAG_NO_DOUBLEQUOTE) { { n2_str_append(state, str, "\"", 1); } } else { n2_str_append(state, str, "\\\"", 2); } break;
		case '`':	if (flags & N2_STR_ESCAPE_FLAG_NO_BACKQUOTE) { { n2_str_append(state, str, "`", 1); } } else { n2_str_append(state, str, "\\`", 2); } break;
		case '\\':	n2_str_append(state, str, "\\\\", 2); break;
		default:
			if ((flags & N2_STR_ESCAPE_FLAG_NO_CONTROLS) == 0 && n2i_char_is_ctrl(src[i]))
			{
				// escape conrols
				n2_str_append_fmt(state, str, "\\u%04x", N2_SCAST(uint8_t, src[i]));
			}
			else
			{
				// output raw chars
				n2_str_append(state, str, src + i, 1);
			}
			break;
		}
	}
	//n2_str_update_size(str);
	return res;
}

N2_API n2_bool_t n2_str_unescaped_to(n2_state_t* state, n2_str_t* str, const char* src, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(src); }
	n2_str_reserve(state, str, length + 1);

	n2_bool_t res = N2_TRUE;
	for (size_t i = 0; i < length && res; ++i)
	{
		if (src[i] == '\\' && (i + 1) < length)
		{
			switch (src[i + 1])
			{
			case '0':	n2_str_appendv(state, str, '\0'); break;
			case 't':	n2_str_appendv(state, str, '\t'); break;
			case 'n':	n2_str_appendv(state, str, '\n'); break;
			case '\'':	n2_str_appendv(state, str, '\''); break;
			case '\"':	n2_str_appendv(state, str, '\"'); break;
			case '`':	n2_str_appendv(state, str, '`'); break;
			case '\\':	n2_str_appendv(state, str, '\\'); break;
			case 'x':
				{
					if ((i + 3) >= length) { res = N2_FALSE; break; }
					if (!n2i_char_is_hexnumber(src[i + 2]) || !n2i_char_is_hexnumber(src[i + 3])) { res = N2_FALSE; break; }
					char tmp[4];
					tmp[0] = src[i + 2]; tmp[1] = src[i + 3]; tmp[2] = '\0';
					const int64_t ll = N2_STRTOLL(tmp, NULL, 16);
					n2_str_appendv(state, str, N2_SCAST(char, ll & 0xff));
					i += 2;
				}
				break;
			case 'u':
			case 'U':
				{
					const size_t ulength = src[i + 1] == 'u' ? 4 : 8;
					if ((i + 1 + ulength) >= length) { res = N2_FALSE; break; }
					char tmp[10];
					N2_MEMSET(tmp, 0, sizeof(tmp));
					for (size_t ai = 0; ai < ulength; ++ai)
					{
						if (!n2i_char_is_hexnumber(src[i + 2 + ai])) { res = N2_FALSE; break; }
						tmp[ai] = src[i + 2 + ai];
					}
					if (!res) { break; }
					const int64_t ll = N2_STRTOLL(tmp, NULL, 16);
					if (ll < N2_UNICODE_MIN || ll > N2_UNICODE_MAX) { res = N2_FALSE; break; }
					char out[N2_CODEPOINT_MAX_BUFFER_SIZE];
					*n2_encoding_utf8_print(out, N2_ARRAYDIM(out), N2_SCAST(n2_unicp_t, ll)) = '\0';
					n2_str_append(state, str, out, SIZE_MAX);
					i += ulength;
				}
				break;
			default:	res = N2_FALSE; break;
			}
			++i;
		}
		else
		{
			n2_str_appendv(state, str, src[i]);
		}
	}
	n2_str_update_size(str);
	return res;
}

N2_API n2_str_t* n2_str_alloc(n2_state_t* state, size_t initial_buffer_size)
{
	n2_str_t* str = N2_TMALLOC(n2_str_t, state);
	if (!str) { return str; }
	n2_str_init(str);
	n2_str_reserve(state, str, initial_buffer_size);
	return str;
}

N2_API n2_str_t* n2_str_alloc_fmt(n2_state_t* state, const char* fmt, ...)
{
	n2_str_t* str = n2_str_alloc(state, 0);
	if (!str) { return NULL; }

	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, str, fmt, args);
	va_end(args);
	return str;
}

N2_API n2_str_t* n2_str_clone(n2_state_t* state, const n2_str_t* rstr)
{
	n2_str_t* str = n2_str_alloc(state, 0);
	if (!str) { return NULL; }
	n2_str_init(str);
	n2_str_copy_to(state, str, rstr);
	return str;
}

N2_API void n2_str_free(n2_state_t* state, n2_str_t* str)
{
	N2_ASSERT(state);
	n2_str_teardown(state, str);
	n2_free(state, str);
}

N2_API void n2_str_buffer_mutate(n2_str_t* lhs, n2_buffer_t* rhs)
{
	n2_swap(&lhs->str_, &rhs->data_, sizeof(void*));
	n2_swap(&lhs->size_, &rhs->size_, sizeof(size_t));
	n2_swap(&lhs->buffer_size_, &rhs->buffer_size_, sizeof(size_t));
}

// 文字列パス
static const char n2i_path_drive_delimiter = ':';
static const char n2i_path_separator = '/';
static const char n2i_path_separator_alt = '\\';
#if N2_PLATFORM_IS_WINDOWS
static const char n2i_path_separator_native = '\\';
#else
static const char n2i_path_separator_native = '/';
#endif

N2_API char n2_path_separator(n2_path_separator_e separator)
{
	switch (separator)
	{
	case N2_PATH_SEPARATOR_SLASH:		return n2i_path_separator;
	case N2_PATH_SEPARATOR_BACKSLASH:	return n2i_path_separator_alt;
	case N2_PATH_SEPARATOR_NATIVE:		return n2i_path_separator_native;
	default:							break;
	}
	return n2i_path_separator;
}

N2_API n2_bool_t n2_path_normalize(n2_state_t* state, n2_str_t* path, n2_path_separator_e separator)
{
#define N2I_MAX_PATH_DIR_NORMALIZE_DEPTH	(64)
	size_t dir_count = 0;
	size_t dir_max = 0;
	size_t* dir_offsets = NULL;
	size_t* dir_lengths = NULL;

	size_t sdir_offsets[N2I_MAX_PATH_DIR_NORMALIZE_DEPTH];
	size_t sdir_lengths[N2I_MAX_PATH_DIR_NORMALIZE_DEPTH];
	n2_szarray_t* adir_offsets = NULL;
	n2_szarray_t* adir_lengths = NULL;

	dir_max = N2I_MAX_PATH_DIR_NORMALIZE_DEPTH;
	dir_offsets = sdir_offsets;
	dir_lengths = sdir_lengths;

	const char to_separator = n2_path_separator(separator);

	size_t ioffset = 0;

	n2_bool_t res = N2_TRUE;

	// ドライブ
	const int drive_delimiter_pos = n2_str_find(path, &n2i_path_drive_delimiter, 1, ioffset);
	if (drive_delimiter_pos >= 0)
	{
		ioffset = N2_SCAST(size_t, drive_delimiter_pos) + 1;// ここはスキップ
	}

	// 各パス
	while (ioffset < path->size_)
	{
		const int nsep_pos_normal = n2_str_find(path, &n2i_path_separator, 1, ioffset);
		const int nsep_pos_alt = n2_str_find(path, &n2i_path_separator_alt, 1, ioffset);
		const int nsep_pos = nsep_pos_normal >= 0 ? (nsep_pos_alt >= 0 ? N2_MIN(nsep_pos_normal, nsep_pos_alt) : nsep_pos_normal) : nsep_pos_alt;
		if (nsep_pos < 0) { break; }// もうない

		const char* cdir = path->str_ + ioffset;
		const size_t cdir_length = N2_SCAST(size_t, nsep_pos) - ioffset;
		if (cdir_length > 0)
		{
			if (cdir_length == 1 && N2_STRNCMP(cdir, ".", 1) == 0)
			{
				// "./"を消す
				n2_str_erase(path, ioffset, 2);
				continue;
			}
			else if (cdir_length == 2 && N2_STRNCMP(cdir, "..", 2) == 0)
			{
				// 1個前と"../"を消す（ないなら残す）
				if (dir_count > 0)
				{
					--dir_count;
					n2_str_erase(path, ioffset, 3);// "../"を消す
					n2_str_erase(path, dir_offsets[dir_count], dir_lengths[dir_count] + 1);// セパレータも巻き込んで消す
					ioffset -= dir_lengths[dir_count] + 1;// その分戻す
					continue;
				}
				// 消せないならパスが間違ってる
				res = N2_FALSE;
			}
			else
			{
				// ディレクトリをプッシュ
				if (dir_count >= dir_max)
				{
					// 足りないので可変配列を動的に確保
					if (!adir_offsets)
					{
						N2_ASSERT(!adir_lengths);
						adir_offsets = n2_szarray_alloc(state, dir_count, 32);
						adir_lengths = n2_szarray_alloc(state, dir_count, 32);
						for (size_t i = 0; i < dir_count; ++i)
						{
							n2_szarray_pushv(state, adir_offsets, dir_offsets[i]);
							n2_szarray_pushv(state, adir_lengths, dir_lengths[i]);
						}
					}
					// 伸長
					n2_szarray_reserve(state, adir_offsets, dir_count + 1);
					n2_szarray_reserve(state, adir_lengths, dir_count + 1);
					dir_offsets = N2_RCAST(size_t*, adir_offsets->elements_);
					dir_lengths = N2_RCAST(size_t*, adir_lengths->elements_);
					dir_max = n2_szarray_size(adir_offsets);
					N2_ASSERT(n2_szarray_size(adir_offsets) == n2_szarray_size(adir_lengths));
				}
				// そして入れる
				N2_ASSERT(dir_count < dir_max);
				dir_offsets[dir_count] = ioffset;
				dir_lengths[dir_count] = cdir_length;
				++dir_count;
			}
		}

		path->str_[nsep_pos] = to_separator;// パスの統一
		ioffset = N2_SCAST(size_t, nsep_pos) + 1;// 次へ
	}

	if (adir_offsets) { n2_szarray_free(state, adir_offsets); }
	if (adir_lengths) { n2_szarray_free(state, adir_lengths); }
	return res;
}

N2_API void n2_path_join(n2_state_t* state, n2_str_t* path, const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length)
{
	n2_str_set(state, path, lhs, lhs_length);
	n2_path_append(state, path, rhs, rhs_length);
}

N2_API void n2_path_append(n2_state_t* state, n2_str_t* path, const char* append, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(append); }
	if (length <= 0) { return; }

	// 足す側の最初のセパレータは消す
	if (append[0] == n2i_path_separator || append[0] == n2i_path_separator_alt)
	{
		++append;
		--length;
	}
	if (length <= 0) { return; }

	// 最後にセパレータがないなら付ける
	if (path->size_ > 0 && (path->str_[path->size_ - 1] != n2i_path_separator && path->str_[path->size_ - 1] != n2i_path_separator_alt))
	{
		n2_str_append(state, path, &n2i_path_separator_native, 1);
	}

	// 実際に足す
	n2_str_append(state, path, append, length);
}

N2_API void n2_path_split(n2_state_t* state, n2_str_t* dst_dir, n2_str_t* dst_filename, n2_str_t* dst_ext, const n2_str_t* path)
{
	const int dsep_pos = n2_str_rfind(path, &n2i_path_separator, 1, 0);
	const int dsepa_pos = n2_str_rfind(path, &n2i_path_separator_alt, 1, 0);
	const int dir_separator_pos = dsep_pos >= 0 ? (dsepa_pos >= 0 ? N2_MAX(dsep_pos, dsepa_pos) : dsep_pos) : dsepa_pos;
	if (dir_separator_pos < 0)
	{
		if (dst_dir) { n2_str_clear(dst_dir); }
	}
	else
	{
		if (dst_dir) { n2_str_set(state, dst_dir, path->str_, N2_SCAST(size_t, dir_separator_pos)); }
	}

	const int filename_offset = N2_MAX(dir_separator_pos + 1, 0);
	const int dot_pos = n2_str_find(path, ".", 1, N2_SCAST(size_t, filename_offset));
	if (dot_pos < 0)
	{
		if (dst_filename) { n2_str_copy_to(state, dst_filename, path); }
		if (dst_ext) { n2_str_clear(dst_ext); }
	}
	else
	{
		if (dst_filename) { n2_str_set(state, dst_filename, path->str_ + filename_offset, N2_SCAST(size_t, dot_pos) - filename_offset); }

		const int ext_size = N2_SCAST(int, path->size_) - dot_pos - 1;/*without dot*/
		if (ext_size > 0)
		{
			if (dst_ext) { n2_str_set(state, dst_ext, path->str_ + dot_pos + 1, ext_size); }
		}
		else
		{
			if (dst_ext) { n2_str_clear(dst_ext); }
		}
	}
}

N2_API void n2_path_basename(n2_state_t* state, n2_str_t* dst, const n2_str_t* path, const char* suffix, size_t suffix_length)
{
	n2_str_t ext;
	n2_str_init(&ext);
	n2_path_split(state, NULL, dst, &ext, path);
	if (ext.size_ > 0) { n2_str_append_fmt(state, dst, ".%s", ext.str_); }
	if (suffix)
	{
		if (suffix_length == SIZE_MAX) { suffix_length = N2_STRLEN(suffix); }
		if (n2_str_ends_with(dst, suffix, suffix_length)) { n2_str_erase(dst, dst->size_ - suffix_length, suffix_length); }
	}
	n2_str_teardown(state, &ext);
}

N2_API int n2_path_compare(const n2_str_t* lhs, const n2_str_t* rhs)
{
	for (size_t i = 0, l = N2_MIN(lhs->size_, rhs->size_); i < l; ++i)
	{
		if (lhs->str_[i] != rhs->str_[i])
		{
			if ((lhs->str_[i] == n2i_path_separator || lhs->str_[i] == n2i_path_separator_alt) != (rhs->str_[i] == n2i_path_separator || rhs->str_[i] == n2i_path_separator_alt))
			{
				return lhs->str_[i] < rhs->str_[i] ? -1 : 1;
			}
		}
	}
	if (lhs->size_ != rhs->size_) { return lhs->size_ < rhs->size_ ? -1 : 1; }
	return 0;
}

//=============================================================================
// リストユーティリティ
N2_API void n2_list_node_init(n2_list_node_t* node)
{
	node->prev_ = node->next_ = NULL;
}

N2_API void n2_list_node_link_prev(n2_list_node_t* to, n2_list_node_t* node)
{
	N2_ASSERT(to);
	N2_ASSERT(node);
	N2_ASSERT(!node->prev_ && !node->next_);
	node->prev_ = to->prev_;
	node->next_ = to;
	if (to->prev_) { to->prev_->next_ = node; }
	to->prev_ = node;
}

void n2_list_node_link_next(n2_list_node_t* to, n2_list_node_t* node)
{
	N2_ASSERT(to);
	N2_ASSERT(node);
	N2_ASSERT(!node->prev_ && !node->next_);
	node->prev_ = to;
	node->next_ = to->next_;
	if (to->next_) { to->next_->prev_ = node; }
	to->next_ = node;
}

N2_API n2_bool_t n2_list_node_islinked(const n2_list_node_t* node)
{
	if (!node->prev_ && !node->next_)
	{
		return N2_FALSE;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_list_node_unlink(n2_list_node_t* node)
{
	if (!node->prev_ && !node->next_)
	{ 
		return N2_FALSE;
	}
	if (node->prev_)
	{
		node->prev_->next_ = node->next_;
	}
	if (node->next_)
	{
		node->next_->prev_ = node->prev_;
	}
	node->prev_ = node->next_ = NULL;
	return N2_TRUE;
}

N2_API void n2_list_init(n2_list_t* list)
{
	n2_list_node_init(&list->head_);
	n2_list_node_init(&list->tail_);
	list->head_.next_ = &list->tail_;
	list->tail_.prev_ = &list->head_;
	list->size_ = 0;
	list->user_ = NULL;
}

N2_API n2_list_t* n2_list_alloc(n2_state_t* state)
{
	n2_list_t* list = N2_TMALLOC(n2_list_t, state);
	n2_list_init(list);
	return list;
}

N2_API void n2_list_free(n2_state_t* state, n2_list_t* list)
{
	n2_list_clear(state, list);
	n2_free(state, list);
}

N2_API void n2_list_clear_free(n2_state_t* state, n2_list_t* list, n2_list_node_free_func freefunc)
{
	N2_ASSERT(list);
	N2_LIST_FOREACH_INLINE(
		list,
		if (freefunc) { freefunc(state, list, node); }
	);
	list->head_.next_ = &list->tail_;
	list->tail_.prev_ = &list->head_;
	list->size_ = 0;
}

N2_API void n2_list_clear(n2_state_t* state, n2_list_t* list)
{
	N2_ASSERT(list);
	N2_LIST_FOREACH_INLINE(
		list,
		n2_free(state, node);
	);
	list->head_.next_ = &list->tail_;
	list->tail_.prev_ = &list->head_;
	list->size_ = 0;
}

N2_API void n2_list_prepend(n2_list_t* list, n2_list_node_t* node)
{
	N2_ASSERT(list);
	N2_ASSERT(!n2_list_node_islinked(node));
	n2_list_node_link_next(&list->head_, node);
	++list->size_;
}

N2_API void n2_list_append(n2_list_t* list, n2_list_node_t* node)
{
	N2_ASSERT(list);
	N2_ASSERT(!n2_list_node_islinked(node));
	n2_list_node_link_prev(&list->tail_, node);
	++list->size_;
}

N2_API n2_list_node_t* n2_list_shift(n2_list_t* list)
{
	N2_ASSERT(list);
	n2_list_node_t* node = list->head_.next_;
	if (node == &list->tail_) { return NULL; }
	n2_list_erase(list, node);
	return node;
}

N2_API n2_list_node_t* n2_list_pop(n2_list_t* list)
{
	N2_ASSERT(list);
	n2_list_node_t* node = list->tail_.prev_;
	if (node == &list->head_) { return NULL; }
	n2_list_erase(list, node);
	return node;
}

N2_API n2_bool_t n2_list_erase(n2_list_t* list, n2_list_node_t* node)
{
	N2_ASSERT(list);
	if (!n2_list_node_islinked(node)) { return N2_FALSE; }
	n2_list_node_unlink(node);
	--list->size_;
	N2_ASSERT(list->size_ > 0 ? (list->head_.next_ != &list->tail_ && list->tail_.prev_ != &list->head_) : (list->head_.next_ == &list->tail_ && list->tail_.prev_ == &list->head_));
	return N2_TRUE;
}

N2_API size_t n2_list_update(n2_list_t* list)
{
	size_t size = 0;
	N2_ASSERT(list);
	N2_LIST_FOREACH_INLINE(
		list,
		++size;
	);
	list->size_ = size;
	return size;
}

//=============================================================================
// 配列ユーティリティ

static void n2i_array_heapify(n2_array_t* a, n2_array_element_cmp_func cmp, const void* key, int i, int n)
{
	do
	{
		const int l = i * 2 + 1;
		const int r = i * 2 + 2;

		int root = i;
		if (l < n && cmp(a, n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, root)), n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, l)), key) < 0) { root = l; }
		if (r < n && cmp(a, n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, root)), n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, r)), key) < 0) { root = r; }
		if (root == i) { break; }
		n2_swap(n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, i)), n2_ptr_offset(a->elements_, a->element_size_ * N2_SCAST(size_t, root)), a->element_size_);
		i = root;
	} while (i < n);
}

static void n2i_array_heapsort(n2_array_t* a, n2_array_element_cmp_func cmp, const void* key)
{
	if (a->size_ < 2) { return; }

	for (size_t i = 0, l = a->size_ / 2; i < l; ++i)
	{
		n2i_array_heapify(a, cmp, key, N2_SCAST(int, l - i - 1), N2_SCAST(int, a->size_));
	}
	for (size_t i = a->size_ - 1; i > 0; --i)
	{
		n2_swap(a->elements_, n2_ptr_offset(a->elements_, a->element_size_ * i), a->element_size_);
		n2i_array_heapify(a, cmp, key, 0, N2_SCAST(int, i));
	}
}

N2_API void n2_array_setup(n2_state_t* state, n2_array_t* a, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc)
{
	a->element_size_ = N2_MAX(element_size, 1);
	a->buffer_size_ = initial_buffer_size;
	if (a->buffer_size_ > 0)
	{
		a->elements_ = n2_malloc(state, a->element_size_ * a->buffer_size_);
	}
	else
	{
		a->elements_ = NULL;
	}
	a->size_ = 0;
	a->expand_step_ = expand_step;
	a->freefunc_ = freefunc;
	a->user_ = NULL;
}

N2_API void n2_array_teardown(n2_state_t* state, n2_array_t* a)
{
	n2_array_clear(state, a);
	if (a->elements_) { n2_free(state, a->elements_); a->elements_ = NULL; }
	a->element_size_ = 0;
	a->buffer_size_ = 0;
	a->freefunc_ = NULL;
	a->user_ = NULL;
}

N2_API n2_array_t* n2_array_alloc(n2_state_t* state, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc)
{
	N2_ASSERT(element_size > 0);
	n2_array_t* a = N2_TMALLOC(n2_array_t, state);
	n2_array_setup(state, a, element_size, initial_buffer_size, expand_step, freefunc);
	return a;
}

N2_API void n2_array_free(n2_state_t* state, n2_array_t* a)
{
	n2_array_teardown(state, a);
	n2_free(state, a);
}

N2_API void n2_array_clear_free(n2_state_t* state, n2_array_t* a, n2_array_element_free_func freefunc)
{
	if (freefunc)
	{
		for (size_t i = 0; i < a->size_; ++i)
		{
			void* element = n2_ptr_offset(a->elements_, i * a->element_size_);
			freefunc(state, a, element);
		}
	}
	a->size_ = 0;
}

N2_API void n2_array_clear(n2_state_t* state, n2_array_t* a)
{
	n2_array_clear_free(state, a, a->freefunc_);
}

N2_API void n2_array_reserve(n2_state_t* state, n2_array_t* a, size_t size)
{
	if (a->buffer_size_ >= size) { return; }

	const size_t expand_step = (a->expand_step_ == 0 ? a->buffer_size_ : a->expand_step_);
	const size_t next_buffer_size = N2_MAX(a->buffer_size_ + expand_step, size);

	if (a->elements_)
	{
		a->elements_ = n2_realloc(state, a->element_size_ * next_buffer_size, a->elements_, a->element_size_ * a->buffer_size_);
	}
	else
	{
		a->elements_ = n2_malloc(state, a->element_size_ * next_buffer_size);
	}
	a->buffer_size_ = next_buffer_size;
}

N2_API n2_bool_t n2_array_resize(n2_state_t* state, n2_array_t* a, size_t size, const void* fill_element)
{
	if (size > a->buffer_size_) { return N2_FALSE; }
	if (size < a->size_)
	{
		// 多いので消す
		n2_array_erase_num(state, a, N2_SCAST(int, size), a->size_ - size);
	}
	else if (size > a->size_)
	{
		// 少ないので追加
		n2_array_reserve(state, a, size);
		if (fill_element)
		{
			while (a->size_ < size)
			{
				n2_array_push(state, a, fill_element);
			}
		}
		else
		{
			a->size_ = size;
		}
	}
	return N2_TRUE;
}

N2_API size_t n2_array_size(const n2_array_t* a)
{
	return a->size_;
}

N2_API size_t n2_array_buffer_size(const n2_array_t* a)
{
	return a->buffer_size_;
}

N2_API int n2_array_compute_index(const n2_array_t* a, const void* element)
{
	if (!element || a->element_size_ <= 0) { return -1; }
	const ptrdiff_t diff = n2_ptr_diff(element, a->elements_);
	if (diff < 0) { return -1; }
	const int index = N2_SCAST(int, diff / N2_SCAST(ptrdiff_t, a->element_size_));
	if (index < 0 || index >= N2_SCAST(int, a->size_)) { return -1; }
	return index;
}

N2_API void* n2_array_peek(n2_array_t* a, int index)
{
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n >= N2_SCAST(int, a->size_)) { return NULL; }
	return n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
}

N2_API const void* n2_array_peekc(const n2_array_t* a, int index)
{
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n >= N2_SCAST(int, a->size_)) { return NULL; }
	return n2_cptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
}

N2_API void* n2_array_insert(n2_state_t* state, n2_array_t* a, int index, const void* element)
{
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n > N2_SCAST(int, a->size_)) { return NULL; }
	if (n == N2_SCAST(int, a->size_)) { return n2_array_push(state, a, element); }
	n2_array_reserve(state, a, a->size_ + 1);
	void* to_element = n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
	N2_MEMMOVE(n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * (n + 1)), to_element, a->element_size_ * (a->size_ - n));
	if (element) { N2_MEMCPY(to_element, element, a->element_size_); }
	++a->size_;
	return to_element;
}

N2_API int n2_array_find(const n2_array_t* a, n2_array_element_match_func match, const void* key)
{
	for (size_t i = 0; i < a->size_; ++i)
	{
		const void* element = n2_cptr_offset(a->elements_, a->element_size_ * i);
		if (match(a, element, key) == 0) { return N2_SCAST(int, i); }
	}
	return -1;
}

N2_API void* n2_array_findp(n2_array_t* a, n2_array_element_match_func match, const void* key)
{
	const int index = n2_array_find(a, match, key);
	if (index < 0) { return NULL; }
	return n2_array_peek(a, index);
}

N2_API const void* n2_array_findcp(const n2_array_t* a, n2_array_element_match_func match, const void* key)
{
	const int index = n2_array_find(a, match, key);
	if (index < 0) { return NULL; }
	return n2_array_peekc(a, index);
}

N2_API n2_bool_t n2_array_erase(n2_state_t* state, n2_array_t* a, int index)
{
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n >= N2_SCAST(int, a->size_)) { return N2_FALSE; }
	void* to_element = n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
	if (a->freefunc_) { a->freefunc_(state, a, to_element); }
	N2_MEMMOVE(to_element, n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * (n + 1)), a->element_size_ * (a->size_ - n - 1));
	--a->size_;
	return N2_TRUE;
}

N2_API size_t n2_array_erase_num(n2_state_t* state, n2_array_t* a, int index, size_t num)
{
	if (num <= 0) { return 0; }
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n >= N2_SCAST(int, a->size_)) { return N2_FALSE; }
	if (N2_SCAST(int, num) > N2_SCAST(int, a->size_) - n) { num = N2_SCAST(size_t, N2_SCAST(int, a->size_) - n); }
	void* to_element = n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
	if (a->freefunc_) { for (size_t i = 0; i < num; ++i) { a->freefunc_(state, a, n2_ptr_offset(to_element, a->element_size_ * i)); } }
	N2_MEMMOVE(to_element, n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * (n + N2_SCAST(int, num))), a->element_size_ * (N2_SCAST(int, a->size_) - n - num));
	a->size_ -= num;
	return num;
}

N2_API void* n2_array_replace(n2_state_t* state, n2_array_t* a, int index, const void* element)
{
	const int n = (index < 0 ? N2_SCAST(int, a->size_) + index : index);
	if (n < 0 || n >= N2_SCAST(int, a->size_)) { return NULL; }
	void* to_element = n2_ptr_offset(a->elements_, N2_SCAST(int, a->element_size_) * n);
	if (a->freefunc_) { a->freefunc_(state, a, to_element); }
	if (element) { N2_MEMCPY(to_element, element, a->element_size_); }
	return to_element;
}

N2_API void n2_array_sort(n2_array_t* a, n2_array_element_cmp_func cmp, const void* key)
{
	n2i_array_heapsort(a, cmp, key);
}

N2_API void* n2_array_push(n2_state_t* state, n2_array_t* a, const void* element)
{
	n2_array_reserve(state, a, a->size_ + 1);
	void* new_element = n2_ptr_offset(a->elements_, a->element_size_ * a->size_);
	if (element) { N2_MEMCPY(new_element, element, a->element_size_); }
	++a->size_;
	return new_element;
}

N2_API size_t n2_array_pop(n2_state_t* state, n2_array_t* a, size_t num)
{
	num = N2_MIN(num, a->size_);
	if (a->freefunc_)
	{
		for (size_t i = 0; i < num; ++i)
		{
			a->freefunc_(state, a, n2_ptr_offset(a->elements_, a->element_size_ * (a->size_ - i - 1)));
		}
	}
	a->size_ -= num;
	return num;
}

N2_API void* n2_array_enqueue(n2_state_t* state, n2_array_t* a, const void* element)
{
	n2_array_reserve(state, a, a->size_ + 1);
	N2_MEMMOVE(n2_ptr_offset(a->elements_, a->element_size_), a->elements_, a->element_size_ * a->size_);
	if (element) { N2_MEMCPY(a->elements_, element, a->element_size_); }
	++a->size_;
	return a->elements_;
}

N2_API size_t n2_array_dequeue(n2_state_t* state, n2_array_t* a, size_t num)
{
	num = N2_MIN(num, a->size_);
	if (num > 0)
	{
		if (a->freefunc_)
		{
			for (size_t i = 0; i < num; ++i)
			{
				a->freefunc_(state, a, n2_ptr_offset(a->elements_, a->element_size_ * i));
			}
		}
		N2_MEMMOVE(a->elements_, n2_ptr_offset(a->elements_, a->element_size_ * num), a->element_size_ * (a->size_ - num));
		a->size_ -= num;
	}
	return num;
}

// ソート済み
N2_API void n2_sorted_array_setup(n2_state_t* state, n2_sorted_array_t* a, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc)
{
	n2_array_setup(state, &a->a_, element_size, initial_buffer_size, expand_step, freefunc);
	a->cmp_ = NULL;
	a->cmp_key_ = NULL;
	a->match_ = NULL;
	a->match_key_ = NULL;
}

N2_API void n2_sorted_array_teardown(n2_state_t* state, n2_sorted_array_t* a)
{
	n2_sorted_array_clear(state, a);
	n2_array_teardown(state, &a->a_);
	a->cmp_ = NULL;
	a->cmp_key_ = NULL;
	a->match_ = NULL;
	a->match_key_ = NULL;
}

N2_API n2_sorted_array_t* n2_sorted_array_alloc(n2_state_t* state, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc)
{
	N2_ASSERT(element_size > 0);
	n2_sorted_array_t* a = N2_TMALLOC(n2_sorted_array_t, state);
	n2_sorted_array_setup(state, a, element_size, initial_buffer_size, expand_step, freefunc);
	return a;
}

N2_API void n2_sorted_array_free(n2_state_t* state, n2_sorted_array_t* a)
{
	n2_sorted_array_teardown(state, a);
	n2_free(state, a);
}

N2_API void n2_sorted_array_clear(n2_state_t* state, n2_sorted_array_t* a)
{
	n2_array_clear(state, &a->a_);
}

N2_API void n2_sorted_array_reserve(n2_state_t* state, n2_sorted_array_t* a, size_t size)
{
	n2_array_reserve(state, &a->a_, size);
}

N2_API size_t n2_sorted_array_size(const n2_sorted_array_t* a)
{
	return n2_array_size(N2_RCAST(const n2_array_t*, a));
}

N2_API int n2_sorted_array_compute_index(const n2_sorted_array_t* a, const void* element)
{
	return n2_array_compute_index(N2_RCAST(const n2_array_t*, a), element);
}

N2_API void* n2_sorted_array_peek(n2_sorted_array_t* a, int index)
{
	return n2_array_peek(N2_RCAST(n2_array_t*, a), index);
}

N2_API const void* n2_sorted_array_peekc(const n2_sorted_array_t* a, int index)
{
	return n2_array_peekc(N2_RCAST(const n2_array_t*, a), index);
}

N2_API void* n2_sorted_array_find_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key)
{
	N2_ASSERT(match);
	int l = 0, r = N2_SCAST(int, a->a_.size_);
	while (l < r)
	{
		const int m = (l + r) / 2;
		void* element = n2_array_peek(&a->a_, m);
		const int c = match(a, element, key);
		if (c == 0) { return element; }
		else if (c > 0) { r = m; }
		else { l = m + 1; }
	}
	return NULL;
}

N2_API void* n2_sorted_array_lowerbound_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key)
{
	N2_ASSERT(match);
	if (a->a_.size_ <= 0) { return NULL; }

	int l = 0, r = N2_SCAST(int, a->a_.size_);
	while (l < r)
	{
		const int m = (l + r) / 2;
		const void* element = n2_array_peek(&a->a_, m);
		const int c = match(a, element, key);
		if (c >= 0) { r = m; }
		else { l = m + 1; }
	}
	if (l >= N2_SCAST(int, a->a_.size_)) { return NULL; }
	return n2_array_peek(&a->a_, l);
}

N2_API void* n2_sorted_array_upperbound_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key, n2_bool_t allow_outrange)
{
	N2_ASSERT(match);
	if (a->a_.size_ <= 0) { return NULL; }

	int l = 0, r = N2_SCAST(int, a->a_.size_);
	while (l < r)
	{
		const int m = (l + r) / 2;
		const void* element = n2_array_peek(&a->a_, m);
		const int c = match(a, element, key);
		if (c > 0) { r = m; }
		else { l = m + 1; }
	}
	if (l >= N2_SCAST(int, a->a_.size_)) { return allow_outrange ? n2_ptr_offset(a->a_.elements_, a->a_.element_size_ * a->a_.size_) : NULL; }
	return n2_array_peek(&a->a_, l);
}

N2_API void* n2_sorted_array_insert_cmp(n2_state_t* state, n2_sorted_array_t* a, const void* element, n2_sorted_array_element_cmp_func cmp, const void* key)
{
	N2_ASSERT(cmp);
	n2_array_element_free_func freefunc = a->a_.freefunc_;
	int l = 0, r = N2_SCAST(int, a->a_.size_);
	while (l < r)
	{
		const int m = (l + r) / 2;
		void* to_element = n2_array_peek(&a->a_, m);
		const int c = cmp(a, element, to_element, key);
		if (c == 0)
		{
			if (freefunc) { freefunc(state, N2_RCAST(n2_array_t*, a), to_element); }
			if (element) { N2_MEMCPY(to_element, element, a->a_.element_size_); }
			return to_element;
		}
		else if (c < 0) { r = m; }
		else { l = m + 1; }
	}
	return n2_array_insert(state, &a->a_, l, element);
}

N2_API size_t n2_sorted_array_erase_match(n2_state_t* state, n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key)
{
	N2_ASSERT(match);
	void* element = n2_sorted_array_find_match(a, match, key);
	if (!element) { return 0; }
	const int n = N2_SCAST(int, N2_SCAST(intptr_t, element) - N2_SCAST(intptr_t, a->a_.elements_)) / N2_SCAST(int, a->a_.element_size_);
	n2_array_erase(state, &a->a_, n);
	return 1;
}

N2_API n2_bool_t n2_sorted_array_erase_at(n2_state_t* state, n2_sorted_array_t* a, int index)
{
	return n2_array_erase(state, &a->a_, index);
}

N2_API void* n2_sorted_array_find(n2_sorted_array_t* a, const void* key)
{
	return n2_sorted_array_find_match(a, a->match_, key);
}

N2_API void* n2_sorted_array_lowerbound(n2_sorted_array_t* a, const void* key)
{
	return n2_sorted_array_lowerbound_match(a, a->match_, key);
}

N2_API void* n2_sorted_array_upperbound(n2_sorted_array_t* a, const void* key, n2_bool_t allow_outrange)
{
	return n2_sorted_array_upperbound_match(a, a->match_, key, allow_outrange);
}

N2_API void* n2_sorted_array_insert(n2_state_t* state, n2_sorted_array_t* a, const void* element, const void* key)
{
	return n2_sorted_array_insert_cmp(state, a, element, a->cmp_, key);
}

N2_API size_t n2_sorted_array_erase(n2_state_t* state, n2_sorted_array_t* a, const void* key)
{
	return n2_sorted_array_erase_match(state, a, a->match_, key);
}

N2_DEFINE_TARRAY(int, n2_intarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

static int n2i_intset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return N2_THREE_WAY_CMP(*N2_RCAST(const int*, lkey), *N2_RCAST(const int*, rkey));
}
static int n2i_intset_matchfunc(const n2_sorted_array_t* a, const void* ikey, const void* key)
{
	N2_UNUSE(a);
	return N2_THREE_WAY_CMP(*N2_RCAST(const int*, ikey), *N2_RCAST(const int*, key));
}
static void n2i_intset_setupfunc(n2_state_t* state, n2_plstrset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2i_intset_cmpfunc;
	a->match_ = n2i_intset_matchfunc;
}
N2_DEFINE_TSORTED_ARRAY(int, void, int, n2_intset, N2_API, n2i_intset_setupfunc, n2i_freefunc_nothing);

N2_DEFINE_TARRAY(uint8_t, n2_u8array, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);
N2_DEFINE_TARRAY(uint16_t, n2_u16array, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);
N2_DEFINE_TARRAY(uint32_t, n2_u32array, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);
N2_DEFINE_TARRAY(size_t, n2_szarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

static void n2i_plstr_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_free(state, *N2_RCAST(char**, element));
}
static int n2i_plstarray_matchfunc(const n2_array_t* a, const void* strkey, const void* key)
{
	N2_UNUSE(a);
	return N2_STRCMP(*N2_RCAST(const char**, strkey), N2_RCAST(const char*, key));
}
N2_DEFINE_TARRAY(char*, n2_plstrarray, N2_API, n2i_setupfunc_nothing, n2i_plstr_freefunc);
N2_DEFINE_TARRAY(char*, n2_cstrarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

static int n2i_plstrset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return N2_STRCMP(*N2_RCAST(const char**, lkey), *N2_RCAST(const char**, rkey));
}
static int n2i_plstrset_matchfunc(const n2_sorted_array_t* a, const void* strkey, const void* key)
{
	N2_UNUSE(a);
	return N2_STRCMP(*N2_RCAST(const char**, strkey), N2_RCAST(const char*, key));
}
static void n2i_plstrset_setupfunc(n2_state_t* state, n2_plstrset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2i_plstrset_cmpfunc;
	a->match_ = n2i_plstrset_matchfunc;
}
N2_DEFINE_TSORTED_ARRAY(char*, void, char, n2_plstrset, N2_API, n2i_plstrset_setupfunc, n2i_plstr_freefunc);

static int n2i_ptrset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	uintptr_t l, r;
	N2_UNUSE(a);
	N2_UNUSE(key);
	l = N2_RCAST(uintptr_t, *N2_RCAST(const void**, lkey));
	r = N2_RCAST(uintptr_t, *N2_RCAST(const void**, rkey));
	return l == r ? 0 : l < r ? -1 : 1;
}

static int n2i_ptrset_matchfunc(const n2_sorted_array_t* a, const void* pkey, const void* key)
{
	uintptr_t l, r;
	N2_UNUSE(a);
	l = N2_RCAST(uintptr_t, *N2_RCAST(const void**, pkey));
	r = N2_RCAST(uintptr_t, key);
	return l == r ? 0 : l < r ? -1 : 1;
}

static void n2i_ptrset_setupfunc(n2_state_t* state, n2_ptrset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2i_ptrset_cmpfunc;
	a->match_ = n2i_ptrset_matchfunc;
}

static void n2i_ptrset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_free(state, *N2_RCAST(void**, element));
}

N2_DEFINE_TSORTED_ARRAY(void*, void, void*, n2_ptrset, N2_API, n2i_ptrset_setupfunc, n2i_ptrset_freefunc);

//=============================================================================
// ベクトル

static N2_INLINE float n2_float_saturate(float v)
{
	return (v < 0.f ? 0.f : v > 1.f ? 1.f : v);
}

N2_API n2_fvec2_t n2_fvec2(float x, float y)
{
	n2_fvec2_t res;
	res.x_ = x; res.y_ = y;
	return res;
}

N2_API n2_fvec2_t n2_fvec2_add(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return n2_fvec2(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

N2_API n2_fvec2_t n2_fvec2_sub(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return n2_fvec2(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}

N2_API n2_fvec2_t n2_fvec2_mul(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return n2_fvec2(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
}

N2_API n2_fvec2_t n2_fvec2_scale(const n2_fvec2_t lhs, float s)
{
	return n2_fvec2(lhs.x_ * s, lhs.y_ * s);
}

N2_API float n2_fvec2_cross(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
}

N2_API float n2_fvec2_normalize_to(n2_fvec2_t* lhs)
{
	float l = lhs->x_ * lhs->x_ + lhs->y_ * lhs->y_;
	if (l > 0.f) { l = N2_SCAST(float, N2_SQRT(l)); const float r = 1.f / l; lhs->x_ *= r; lhs->y_ *= r; }
	return l;
}

N2_API n2_fvec2_t n2_fvec2_min(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return n2_fvec2(N2_MIN(lhs.x_, rhs.x_), N2_MIN(lhs.y_, rhs.y_));
}

N2_API n2_fvec2_t n2_fvec2_max(const n2_fvec2_t lhs, const n2_fvec2_t rhs)
{
	return n2_fvec2(N2_MAX(lhs.x_, rhs.x_), N2_MAX(lhs.y_, rhs.y_));
}

N2_API n2_fvec3_t n2_fvec3(float x, float y, float z)
{
	n2_fvec3_t res;
	res.x_ = x; res.y_ = y; res.z_ = z;
	return res;
}

N2_API n2_fvec3_t n2_fvec3_add(const n2_fvec3_t lhs, const n2_fvec3_t rhs)
{
	return n2_fvec3(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
}

N2_API n2_fvec3_t n2_fvec3_sub(const n2_fvec3_t lhs, const n2_fvec3_t rhs)
{
	return n2_fvec3(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
}

N2_API n2_fvec3_t n2_fvec3_scale(const n2_fvec3_t lhs, float s)
{
	return n2_fvec3(lhs.x_ * s, lhs.y_ * s, lhs.z_ * s);
}

N2_API float n2_fvec3_normalize_to(n2_fvec3_t* lhs)
{
	float l = lhs->x_ * lhs->x_ + lhs->y_ * lhs->y_ + lhs->z_ * lhs->z_;
	if (l > 0.f) { l = N2_SCAST(float, N2_SQRT(l)); const float r = 1.f / l; lhs->x_ *= r; lhs->y_ *= r; lhs->z_ *= r; }
	return l;
}

N2_API n2_fvec4_t n2_fvec4(float x, float y, float z, float w)
{
	n2_fvec4_t res;
	res.x_ = x; res.y_ = y; res.z_ = z; res.w_ = w;
	return res;
}

N2_API n2_fvec4_t n2_fvec4_add(const n2_fvec4_t lhs, const n2_fvec4_t rhs)
{
	return n2_fvec4(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_, lhs.w_ + rhs.w_);
}

N2_API n2_fvec4_t n2_fvec4_sub(const n2_fvec4_t lhs, const n2_fvec4_t rhs)
{
	return n2_fvec4(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_, lhs.w_ - rhs.w_);
}

N2_API n2_fvec4_t n2_fvec4_scale(const n2_fvec4_t lhs, float s)
{
	return n2_fvec4(lhs.x_ * s, lhs.y_ * s, lhs.z_ * s, lhs.w_ * s);
}

N2_API void n2_fmat4_zero_to(n2_fmat4_t* to)
{
	to->m_[0][0] = 0; to->m_[0][1] = 0; to->m_[0][2] = 0; to->m_[0][3] = 0;
	to->m_[1][0] = 0; to->m_[1][1] = 0; to->m_[1][2] = 0; to->m_[1][3] = 0;
	to->m_[2][0] = 0; to->m_[2][1] = 0; to->m_[2][2] = 0; to->m_[2][3] = 0;
	to->m_[3][0] = 0; to->m_[3][1] = 0; to->m_[3][2] = 0; to->m_[3][3] = 0;
}

N2_API void n2_fmat4_identity_to(n2_fmat4_t* to)
{
	to->m_[0][0] = 1; to->m_[0][1] = 0; to->m_[0][2] = 0; to->m_[0][3] = 0;
	to->m_[1][0] = 0; to->m_[1][1] = 1; to->m_[1][2] = 0; to->m_[1][3] = 0;
	to->m_[2][0] = 0; to->m_[2][1] = 0; to->m_[2][2] = 1; to->m_[2][3] = 0;
	to->m_[3][0] = 0; to->m_[3][1] = 0; to->m_[3][2] = 0; to->m_[3][3] = 1;
}

N2_API n2_fmat4_t n2_fmat4_identity()
{
	n2_fmat4_t res;
	n2_fmat4_identity_to(&res);
	return res;
}

N2_API void n2_fmat4_copy_to(n2_fmat4_t* to, const n2_fmat4_t* from)
{
	N2_MEMCPY(to, from, sizeof(n2_fmat4_t));
}

N2_API void n2_fmat4_ortho2d_to(n2_fmat4_t* to, float left, float right, float top, float bottom, float z_near, float z_far)
{
	n2_fmat4_identity_to(to);
	to->m_[0][0] =  2.f / (right - left);
	to->m_[1][1] =  2.f / (top - bottom);
	to->m_[2][2] = -2.f / (z_far - z_near);
	to->m_[3][0] = -(right + left) / (right - left);
	to->m_[3][1] = -(top + bottom) / (top - bottom);
	to->m_[3][2] = -(z_far + z_near) / (z_far - z_near);
}

N2_API void n2_fmat4_ortho3d_to(n2_fmat4_t* to, float left, float right, float bottom, float top, float z_near, float z_far)
{
	n2_fmat4_identity_to(to);
	to->m_[0][0] =  2.f / (right - left);
	to->m_[1][1] =  2.f / (top - bottom);
	to->m_[2][2] = -2.f / (z_far - z_near);
	to->m_[3][0] = -(right + left) / (right - left);
	to->m_[3][1] = -(top   + bottom) / (top   - bottom);
	to->m_[3][2] = -(z_far + z_near) / (z_far - z_near);
}

N2_API void n2_fmat4_perspective_to(n2_fmat4_t* to, float fovy, float aspect, float z_near, float z_far)
{
	n2_fmat4_zero_to(to);
	const float tan_half_fovy = N2_SCAST(float, N2_TAN(0.5f * fovy));
	to->m_[0][0] = 1.f / (aspect * tan_half_fovy);
	to->m_[1][1] = 1.f / (tan_half_fovy);
	to->m_[2][2] = -(z_far + z_near) / (z_far - z_near);
	to->m_[2][3] = -1.f;
	to->m_[3][2] = -2.f*z_far*z_near / (z_far - z_near);
}

//=============================================================================
// 内部ヘルパー

#if N2_CONFIG_USE_RPMALLOC_LIB
static void* n2i_rpmalloc_allocate(void* alloc_user, size_t new_size, void* old_ptr, size_t old_size)
{
	N2_UNUSE(alloc_user);
	N2_UNUSE(old_size);
	if (old_ptr)
	{
		return n2h_rpmalloc_realloc(new_size, old_ptr);
	}
	return n2h_rpmalloc_alloc(new_size);
}

static void n2i_rpmalloc_free(void* alloc_user, void* ptr)
{
	N2_UNUSE(alloc_user);
	n2h_rpmalloc_free(ptr);
}

static void n2i_rpmalloc_close(void* alloc_user)
{
	N2_UNUSE(alloc_user);
	n2h_rpmalloc_teardown();
}

static int n2h_rpmalloc_initialized = 0;

N2_API void n2h_rpmalloc_init()
{
	if (!n2h_rpmalloc_initialized)
	{
		rpmalloc_initialize();
	}
	++n2h_rpmalloc_initialized;
}

N2_API void n2h_rpmalloc_teardown()
{
	if (!n2h_rpmalloc_initialized) { return; }
	if (!--n2h_rpmalloc_initialized)
	{
		rpmalloc_finalize();
	}
}

N2_API int n2h_rpmalloc_initialized_count()
{
	return n2h_rpmalloc_initialized;
}

N2_API void* n2h_rpmalloc_alloc(size_t size)
{
	return rpmalloc(size);
}

N2_API void* n2h_rpmalloc_realloc(size_t size, void* old_ptr)
{
	return rprealloc(old_ptr, size);
}

N2_API void n2h_rpmalloc_free(void* ptr)
{
	rpfree(ptr);
}
#endif

#if N2_PLATFORM_IS_WINDOWS
static n2_bool_t n2hi_to_system_string(n2_state_t* state, n2_str_t* dst, const n2_str_t* src)
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

// 動的ライブラリ
N2_API n2_bool_t n2h_dynlib_supported_platform(int platform)
{
	switch (platform)
	{
	case N2_PLATFORM_WINDOWS:
	case N2_PLATFORM_UNIX:
		return N2_TRUE;
	default:
		break;
	}
	return N2_FALSE;
}

N2_API n2_bool_t n2h_dynlib_supported()
{
	return n2h_dynlib_supported_platform(N2_PLATFORM);
}

N2_API n2h_dynlib_t* n2h_dynlib_alloc(n2_state_t* state, const char* path, size_t path_length)
{
	if (!path || path_length <= 0) { return NULL; }
	if (path_length == SIZE_MAX) { path_length = N2_STRLEN(path); }
#if N2_PLATFORM_IS_WINDOWS
	n2_str_t syspath;
	n2_str_init(&syspath);
	n2_str_t pathstr; pathstr.str_ = N2_CCAST(char*, path); pathstr.size_ = path_length;
	if (!n2hi_to_system_string(state, &syspath, &pathstr)) { return NULL; }
	const UINT errmode = GetErrorMode();
	SetErrorMode(errmode | SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX);
	HMODULE hmodule = LoadLibraryW(N2_RCAST(LPCWSTR, syspath.str_));
	SetErrorMode(errmode);
	if (!hmodule) { return NULL; }
	n2h_dynlib_t* dynlib = N2_TMALLOC(n2h_dynlib_t, state);
	n2_str_init(&dynlib->path_);
	n2_str_set(state, &dynlib->path_, path, path_length);
	dynlib->native_handle_ = hmodule;
	dynlib->native_data_ = NULL;
	n2_str_teardown(state, &syspath);
	return dynlib;
#else
	N2_UNUSE(state);
	return NULL;
#endif
}

N2_API void n2h_dynlib_free(n2_state_t* state, n2h_dynlib_t* dynlib)
{
	if (!dynlib) { return; }
#if N2_PLATFORM_IS_WINDOWS
	if (dynlib->native_handle_) { FreeLibrary(dynlib->native_handle_); dynlib->native_handle_ = NULL; }
#endif
	N2_ASSERT(!dynlib->native_handle_);
	N2_ASSERT(!dynlib->native_data_);
	n2_str_teardown(state, &dynlib->path_);
	n2_free(state, dynlib);
}

N2_API void* n2h_dynlib_find_function(n2_state_t* state, n2h_dynlib_t* dynlib, const char* name)
{
	if (!dynlib || !name) { return NULL; }
#if N2_PLATFORM_IS_WINDOWS
	N2_UNUSE(state);
	if (!dynlib->native_handle_) { return NULL; }
	return N2_RCAST(void*, GetProcAddress(dynlib->native_handle_, name));
#else
	N2_UNUSE(state);
	return NULL;
#endif
}

// @todo Too straitforward and negligent way to call signature missing functions. should use ffi library to do so.
// @warning Currently this code works ONLY on Windows OS.
#if N2_PLATFORM_IS_WINDOWS && N2_COMPILER_IS_MSVC && defined(_WIN32) && !defined(_WIN64)
#define N2HI_DYNLIB_PROC_CC __stdcall
#else
#define N2HI_DYNLIB_PROC_CC
#endif

#if N2_ARCHBIT_IS_64BIT
typedef double n2h_dynlib_arg_real_t;// to fill xmm registers
#else
//typedef float n2h_dynlib_arg_real_t;
typedef n2h_dynlib_arg_t n2h_dynlib_arg_real_t;
#endif

#define N2HI_DR n2h_dynlib_result_t
#define N2HI_DA n2h_dynlib_arg_t
#define N2HI_DAR n2h_dynlib_arg_real_t
#if N2_ARCHBIT_IS_64BIT
#define N2HI_DT , ...
#else
#define N2HI_DT
#endif
#define N2HI_CC N2HI_DYNLIB_PROC_CC

typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_n)(N2HI_DAR, ...);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_0)();
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_1)(N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_2)(N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_3)(N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_4)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_5)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_6)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_7)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_8)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_9)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_10)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_11)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_12)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_13)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_14)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_15)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_16)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);
typedef N2HI_DR (N2HI_CC *n2hi_dynlib_proc_17)(N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR, N2HI_DAR N2HI_DT);

#if N2_ARCHBIT_IS_64BIT
#define N2HI_DP0 n2hi_dynlib_proc_0
// to fill both int registers and floating point registers
#define N2HI_DPN(n) n2hi_dynlib_proc_n
#else
#define N2HI_DP0 n2hi_dynlib_proc_0
#define N2HI_DPN(n) n2hi_dynlib_proc_##n
#endif

N2_API n2_bool_t n2h_dynlib_call_single(n2_state_t* state, n2h_dynlib_t* dynlib, void* proc, intptr_t* dst, const n2h_dynlib_arg_t* args, size_t arg_num)
{
	N2_UNUSE(state);
	if (!dynlib || !proc) { return N2_FALSE; }
	if (!args && arg_num > 0) { return N2_FALSE; }
	N2_ASSERT(sizeof(N2HI_DA) == sizeof(N2HI_DAR));
	n2h_dynlib_result_t result = 0;
	const n2h_dynlib_arg_real_t* rargs = N2_RCAST(const n2h_dynlib_arg_real_t*, args);
	switch (arg_num)
	{
	case 0:		result = N2_RCAST(N2HI_DP0, proc)(); break;
	case 1:		result = N2_RCAST(N2HI_DPN(1), proc)(rargs[0]); break;
	case 2:		result = N2_RCAST(N2HI_DPN(2), proc)(rargs[0], rargs[1]); break;
	case 3:		result = N2_RCAST(N2HI_DPN(3), proc)(rargs[0], rargs[1], rargs[2]); break;
	case 4:		result = N2_RCAST(N2HI_DPN(4), proc)(rargs[0], rargs[1], rargs[2], rargs[3]); break;
	case 5:		result = N2_RCAST(N2HI_DPN(5), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4]); break;
	case 6:		result = N2_RCAST(N2HI_DPN(6), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5]); break;
	case 7:		result = N2_RCAST(N2HI_DPN(7), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6]); break;
	case 8:		result = N2_RCAST(N2HI_DPN(8), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7]); break;
	case 9:		result = N2_RCAST(N2HI_DPN(9), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8]); break;
	case 10:	result = N2_RCAST(N2HI_DPN(10), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9]); break;
	case 11:	result = N2_RCAST(N2HI_DPN(11), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10]); break;
	case 12:	result = N2_RCAST(N2HI_DPN(12), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11]); break;
	case 13:	result = N2_RCAST(N2HI_DPN(13), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11], rargs[12]); break;
	case 14:	result = N2_RCAST(N2HI_DPN(14), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11], rargs[12], rargs[13]); break;
	case 15:	result = N2_RCAST(N2HI_DPN(15), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11], rargs[12], rargs[13], rargs[14]); break;
	case 16:	result = N2_RCAST(N2HI_DPN(16), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11], rargs[12], rargs[13], rargs[14], rargs[15]); break;
	case 17:	result = N2_RCAST(N2HI_DPN(17), proc)(rargs[0], rargs[1], rargs[2], rargs[3], rargs[4], rargs[5], rargs[6], rargs[7], rargs[8], rargs[9], rargs[10], rargs[11], rargs[12], rargs[13], rargs[14], rargs[15], args[16]); break;
	default:	return N2_FALSE;
	}
	if (dst) { *dst = result; }
	return N2_TRUE;
}

#undef N2HI_DR
#undef N2HI_DA
#undef N2HI_DAR
#undef N2HI_DT
#undef N2HI_CC

#undef N2HI_DP0
#undef N2HI_DPN

/* CRC32 implemetation from <https://github.com/panzi/CRC-and-checksum-functions> */

/* Copyright (C) 1986 Gary S. Brown.  You may use this program, or
code or tables extracted from it, as desired without restriction.*/

#define N2HI_CRC32_UPDATE(octet, crc) (n2hi_crc_32_tab[((crc)^ ((uint8_t)(octet))) & 0xff] ^ ((crc) >> 8))

static uint32_t n2hi_crc_32_tab[] = /* CRC polynomial 0xedb88320 */
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

N2_API uint32_t n2h_crc32(const void* src, size_t src_size)
{
	uint32_t oldcrc32;
	const uint8_t* buf = N2_RCAST(const uint8_t*, src);

	oldcrc32 = 0xffffffff;

	while (src_size > 0)
	{
		oldcrc32 = N2HI_CRC32_UPDATE(*buf, oldcrc32);
		--src_size; ++buf;
	}

	return ~oldcrc32;
}

#if N2_CONFIG_USE_MD5_LIB
// md5
N2_API void n2h_md5(n2_md5_digest_t* dst, const void* src, size_t src_size)
{
	MD5_CTX ctx;
	MD5Init(&ctx);
	MD5Update(&ctx, N2_RCAST(const unsigned char*, src), N2_SCAST(unsigned int, src_size));
	MD5Final(N2_RCAST(unsigned char*, dst->digest_), &ctx);
}
#endif

// rfc1924
static const char n2hi_base85_encode_table[] = 
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'!', '#', '$', '%', '&', '(', ')', '*', '+', '-', ';', '<', '=', '>', '?', '@', '^', '_', '`', '{', '|', '}', '~'
};

static uint8_t n2hi_base85_decode_table[255] = {0};
static n2_bool_t n2hi_base85_decode_table_initialized = N2_FALSE;

static void n2hi_base85_initialize()
{
	if (n2hi_base85_decode_table_initialized) { return; }
	N2_MEMSET(n2hi_base85_decode_table, 0xff, sizeof(n2hi_base85_decode_table));
	for (size_t i = 0; i < N2_ARRAYDIM(n2hi_base85_encode_table); ++i)
	{
		const uint8_t c = N2_SCAST(uint8_t, N2_SCAST(unsigned char, n2hi_base85_encode_table[i]));
		n2hi_base85_decode_table[c] = N2_SCAST(uint8_t, i);
	}
	n2hi_base85_decode_table_initialized = N2_TRUE;
}

N2_API void n2h_base85_encode_to(n2_state_t* state, n2_str_t* dst, const void* src, size_t src_size)
{
	n2hi_base85_initialize();
	n2_str_clear(dst);
	n2_str_reserve(state, dst, src_size * 5 / 4 + 4 + 1);

	char* w = dst->str_;
	const uint8_t* r = N2_RCAST(const uint8_t*, src);
	while (src_size > 0)
	{
		uint32_t v = 0;
		for (size_t i = 0; i < 4; ++i)
		{
			v |= *r << (8 * i);
			++r;
			--src_size;
			if (!src_size) { break; }
		}
		// to make it easier to decode
		for (int i = 4; i >= 0; --i)
		{
			const uint8_t c = v % 85;
			w[i] = n2hi_base85_encode_table[c];
			v /= 85;
		}
		w += 5;
	}
	*w = '\0';
	dst->size_ = N2_SCAST(size_t, n2_ptr_diff(w, dst->str_));
}

N2_API n2_bool_t n2h_base85_decode_to(n2_state_t* state, n2_buffer_t* dst, const char* src, size_t src_size)
{
	n2hi_base85_initialize();
	n2_buffer_clear(dst);
	n2_buffer_reserve(state, dst, ((src_size + 4) / 5) * 4 + 1);

	uint8_t* w = N2_RCAST(uint8_t*, dst->data_);
	const char* r = src;
	while (src_size > 0)
	{
		uint32_t v = 0;
		for (size_t i = 0; i < 5; ++i)
		{
			const unsigned char c = n2hi_base85_decode_table[N2_SCAST(unsigned char, *r)];
			if (c >= 85) { return N2_FALSE; }
			v *= 85;
			v += c;
			++r;
			--src_size;
			if (!src_size) { break; }
		}
		for (size_t i = 0; i < 4; ++i)
		{
			*w = (v >> (8 * i)) & 0xff;
			++w;
		}
	}
	dst->size_ = N2_SCAST(size_t, n2_ptr_diff(w, dst->data_));
	return N2_TRUE;
}

// easing
N2_API double n2h_easing_linear(double v) { return v; }
N2_API double n2h_easing_quadratic_in(double v) { return v * v; }
N2_API double n2h_easing_quadratic_out(double v) { return -(v * (v - 2)); }
N2_API double n2h_easing_quadratic_inout(double v) { return (v < 0.5) ? 2 * v * v : (-2 * v * v) + (4 * v) - 1; }
N2_API double n2h_easing_cubic_in(double v) { return v * v * v; }
N2_API double n2h_easing_cubic_out(double v) { const double r = v - 1; return r * r * r + 1; }
N2_API double n2h_easing_cubic_inout(double v) { if (v < 0.5) { return 4 * v * v * v; } const double r = ( 2 * v ) - 2; return 0.5 * r * r * r + 1; }
N2_API double n2h_easing_quartic_in(double v) { return v * v * v * v; }
N2_API double n2h_easing_quartic_out(double v) { const double r = v - 1; return r * r * r * (1 - v) + 1; }
N2_API double n2h_easing_quartic_inout(double v) { if (v < 0.5) { return 8 * v * v * v * v; } const double r = v - 1; return -8 * r * r * r * r + 1; }
N2_API double n2h_easing_quintic_in(double v) { return v * v * v * v * v; }
N2_API double n2h_easing_quintic_out(double v) { const double r = v - 1; return r * r * r * r * r + 1; }
N2_API double n2h_easing_quintic_inout(double v) { if (v < 0.5) { return 16 * v * v * v * v * v; } const double r = (2 * v) - 2; return 0.5 * r * r * r * r * r + 1; }
N2_API double n2h_easing_sine_in(double v) { return 1 + N2_SIN(v - 1) * (N2_MPI * 0.5); }
N2_API double n2h_easing_sine_out(double v) { return N2_SIN(v * (N2_MPI * 0.5)); }
N2_API double n2h_easing_sine_inout(double v) { return 0.5 * (1 - N2_COS(v * N2_MPI)); }
N2_API double n2h_easing_circular_in(double v) { return 1 - N2_SQRT(1 - (v * v)); }
N2_API double n2h_easing_circular_out(double v) { return N2_SQRT((2 - v) * v); }
N2_API double n2h_easing_circular_inout(double v) { return v < 0.5 ? 0.5 * (1 - N2_SQRT(1 - 4 * (v * v))) : 0.5 * N2_SQRT(-((2 * v) - 3) * ((2 * v) - 1)) + 1; }
N2_API double n2h_easing_exponential_in(double v) { return (v <= 0) ? v : N2_POW(2, 10 * (v - 1)); }
N2_API double n2h_easing_exponential_out(double v) { return (v >= 1) ? v : 1 - N2_POW(2, -10 * v); }
N2_API double n2h_easing_exponential_inout(double v) { return (v <= 0 || v >= 1) ? v : v < 0.5 ? 0.5 * N2_POW(2, (20 * v) - 10) : -0.5 * N2_POW(2, (-20 * v) + 10) + 1; }
N2_API double n2h_easing_elastic_in(double v) { return N2_SIN(13 * (N2_MPI * 0.5) * v) * N2_POW(2, 10 * (v - 1)); }
N2_API double n2h_easing_elastic_out(double v) { return N2_SIN(-13 * (N2_MPI * 0.5) * (v + 1)) * N2_POW(2, -10 * v) + 1; }
N2_API double n2h_easing_elastic_inout(double v) { return v < 0.5 ? 0.5 * N2_SIN(13 * (N2_MPI * 0.5) * (2 * v)) * N2_POW(2, 10 * ((2 * v) - 1)) : 0.5 * (N2_SIN(-13 * (N2_MPI * 0.5) * ((2 * v - 1) + 1)) * N2_POW(2, -10 * (2 * v - 1)) + 2); }
N2_API double n2h_easing_back_in(double v) { return v * v * v - v * N2_SIN(v * N2_MPI); }
N2_API double n2h_easing_back_out(double v) { const double r = 1 - v; return 1 - (r * r * r - r * N2_SIN(r * N2_MPI)); }
N2_API double n2h_easing_back_inout(double v) { if (v < 0.5) { const double r = 2 * v; return 0.5 * (r * r * r - r * N2_SIN(r * N2_MPI)); } const double r = (1 - (2 * v - 1)); return 0.5 * (1 - (r * r * r - r * N2_SIN(r * N2_MPI))) + 0.5; }
N2_API double n2h_easing_bounce_out(double v) { return (v < 4.0 / 11.0) ? (121.0 * v * v) / 16.0 : (v < 8.0 / 11.0) ? (363.0 / 40 * v * v) - (99.0 / 10.0 * v) + 17.0 / 5.0 : (v < 9.0 / 10.0) ? (4356.0 / 361.0 * v * v) - (35442.0 / 1805.0 * v) + 16061.0 / 1805.0 : (54.0 / 5.0 * v * v) - (513.0 / 25.0 * v) + 268.0/25.0; }
N2_API double n2h_easing_bounce_in(double v) { return 1 - n2h_easing_bounce_out(1 - v); }
N2_API double n2h_easing_bounce_inout(double v) { return v < 0.5 ? 0.5 * n2h_easing_bounce_in(v * 2) : 0.5 * n2h_easing_bounce_out(v * 2 - 1) + 0.5; }

// ランダム

// [0, 1)
static double n2hi_translate_as_normalized_float(uint64_t v)
{
	uint64_t f = (1023ULL << 52ULL) | (v >> 12ULL);
	return *N2_RCAST(double*, &f) - 1.0;
}

// [0, range)
static uint64_t n2hi_fold_range_hard(uint64_t val, uint64_t range)
{
	const uint64_t ur = (val >> 32ULL);
	const uint64_t lr = (val & 0xffffffffULL);
	const uint64_t ud = (range >> 32ULL);
	const uint64_t ld = (range & 0xffffffffULL);
	return (ur * ud) + (((ur * ld) + (lr * ud)) >> 32ULL)/* + ((lr * ld) >> 64ULL)*/;
}

static uint64_t n2hi_mmh3_avalanche(uint64_t v)
{
	v ^= v >> 33; v *= 0xff51afd7ed558ccd;
	v ^= v >> 33; v *= 0xc4ceb9fe1a85ec53;
	v ^= v >> 33;
	return v;
}

N2_API void n2h_random_init(n2h_random_t* rd, uint64_t s)
{
	s = n2hi_mmh3_avalanche(s | 1);
	rd->state_[0] = s;
	s = n2hi_mmh3_avalanche(s);
	rd->state_[1] = s;
}

N2_API uint64_t n2h_random_next(n2h_random_t* rd)
{
	uint64_t x = rd->state_[0];
	const uint64_t y = rd->state_[1];
	rd->state_[0] = y;
	x ^= x << 23; x ^= x >> 17; x ^= y ^ ( y >> 26 );
	rd->state_[1] = x;
	return x + y;
}

N2_API uint64_t n2h_random_next_range(n2h_random_t* rd, uint64_t range)
{
	uint64_t r = n2h_random_next(rd);
	return n2hi_fold_range_hard(r, range);
}

N2_API double n2h_random_next_float(n2h_random_t* rd)
{
	uint64_t r = n2h_random_next(rd);
	return n2hi_translate_as_normalized_float(r);
}

N2_API void n2h_random_scratch(void* data, size_t data_size, uint64_t seed)
{
	uint8_t* p = N2_RCAST(uint8_t*, data);
	n2h_random_t r;
	n2h_random_init(&r, seed);
	uint64_t v = 0;
	while (data_size > sizeof(uint64_t))
	{
		v = n2h_random_next(&r);
		// unrolled
		p[0] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[1] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[2] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[3] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[4] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[5] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[6] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		p[7] ^= N2_SCAST(uint8_t, v & 0xff);/* v >>= 8; */
		p += sizeof(uint64_t);
		data_size -= sizeof(uint64_t);
	}
	v = n2h_random_next(&r);
	while (data_size > 0)
	{
		p[0] ^= N2_SCAST(uint8_t, v & 0xff); v >>= 8;
		++p; --data_size;
	}
}

// バイナリシーケンス
static const uint8_t n2hi_binseq_magic[] = {0x4e, 0x32, 0x21, 0x00};// N2!0

N2_API size_t n2h_binseq_signature_size()
{
	return sizeof(n2hi_binseq_magic) + sizeof(n2h_binseq_header_t);
}

N2_API const uint8_t* n2h_binseq_magic(size_t* dst_size)
{
	if (dst_size) { *dst_size = sizeof(n2hi_binseq_magic); }
	return n2hi_binseq_magic;
}

N2_API n2_bool_t n2h_binseq_verify(const void* src, size_t src_size)
{
	if (src_size < n2h_binseq_signature_size()) { return N2_FALSE; }
	return N2_MEMCMP(src, n2hi_binseq_magic, sizeof(n2hi_binseq_magic)) == 0 ? N2_TRUE : N2_FALSE;
}

N2_API n2_bool_t n2h_binseq_get_header(n2h_binseq_header_t* dst, const void* src, size_t src_size)
{
	if (src_size < n2h_binseq_signature_size()) { return N2_FALSE; }
	if (dst)
	{
		const void* header_base = n2_cptr_offset(src, sizeof(n2hi_binseq_magic));
		dst->size_ = n2_ptr_read64(n2_cptr_offset(header_base, offsetof(n2h_binseq_header_t, size_)));
		dst->flags_ = n2_ptr_read64(n2_cptr_offset(header_base, offsetof(n2h_binseq_header_t, flags_)));
		dst->scratch_key_ = n2_ptr_read64(n2_cptr_offset(header_base, offsetof(n2h_binseq_header_t, scratch_key_)));
		dst->check_ = n2_ptr_read32(n2_cptr_offset(header_base, offsetof(n2h_binseq_header_t, check_)));
	}
	return N2_TRUE;
}

N2_API size_t n2h_binseq_write_signature(void* dst, const n2h_binseq_header_t* header)
{
	N2_MEMCPY(dst, n2hi_binseq_magic, sizeof(n2hi_binseq_magic));
	{
		void* header_base = n2_ptr_offset(dst, sizeof(n2hi_binseq_magic));
		n2_ptr_write64(n2_ptr_offset(header_base, offsetof(n2h_binseq_header_t, size_)), header->size_);
		n2_ptr_write64(n2_ptr_offset(header_base, offsetof(n2h_binseq_header_t, flags_)), header->flags_);
		n2_ptr_write64(n2_ptr_offset(header_base, offsetof(n2h_binseq_header_t, scratch_key_)), header->scratch_key_);
		n2_ptr_write32(n2_ptr_offset(header_base, offsetof(n2h_binseq_header_t, check_)), header->check_);
	}
	return n2h_binseq_signature_size();
}

// イメージ
#if N2_CONFIG_USE_IMAGE_READ_LIB
N2_API n2_bool_t n2h_image_read(n2_state_t* state, n2_buffer_t* dst, size_t* dst_width, size_t* dst_height, const void* src, size_t src_size)
{
	if (!src || src_size <= 0) { return N2_FALSE; }
	if (src_size > N2_SCAST(size_t, INT_MAX)) { return N2_FALSE; }
	n2_state_t* old_state = n2g_get_state();
	n2g_set_state(state);

	stbi_set_flip_vertically_on_load(1);// flip

	int x = 0, y = 0, cmp = 0;
	stbi_uc* l = stbi_load_from_memory(N2_RCAST(const stbi_uc*, src), N2_SCAST(int, src_size), &x, &y, &cmp, 4);
	n2_bool_t res = N2_FALSE;
	if (!l) { goto exit; }
	if (x <= 0 || y <= 0) { goto exit; }

	const size_t image_size = N2_SCAST(size_t, x) * N2_SCAST(size_t, y) * N2_SCAST(size_t, cmp);
	n2_buffer_reserve(state, dst, image_size);
	N2_MEMCPY(dst->data_, l, image_size);
	dst->size_ = image_size;

	*dst_width = N2_SCAST(size_t, x);
	*dst_height = N2_SCAST(size_t, y);

	res = N2_TRUE;
	goto exit;
exit:
	stbi_image_free(l);
	n2g_set_state(old_state);
	return N2_TRUE;
}
#endif

#if N2_CONFIG_USE_IMAGE_WRITE_LIB
typedef struct n2hi_stbi_write_context_t n2hi_stbi_write_context_t;
struct n2hi_stbi_write_context_t
{
	n2_state_t* state_;
	n2_buffer_t* dst_buffer_;
};

static void n2hi_stbi_write_func(void* context, void* data, int size)
{
	n2hi_stbi_write_context_t* c = N2_RCAST(n2hi_stbi_write_context_t*, context);
	n2_buffer_append(c->state_, c->dst_buffer_, data, N2_SCAST(size_t, size));
}

N2_API n2_bool_t n2h_image_write(n2_state_t* state, n2_buffer_t* dst, n2_image_file_e image_file, const void* src, size_t src_size, size_t width, size_t height, int quality)
{
	if (!src || src_size <= 0 || !dst) { return N2_FALSE; }
	if (src_size < (width * height * 4)) { return N2_FALSE; }

	n2hi_stbi_write_context_t context;
	context.state_ = state;
	context.dst_buffer_ = dst;

	n2_buffer_clear(dst);

	n2_state_t* old_state = n2g_get_state();
	n2g_set_state(state);

	stbi_flip_vertically_on_write(1);// flip

	n2_bool_t res = N2_TRUE;
	switch (image_file)
	{
	case N2_IMAGE_FILE_BMP:		if (!stbi_write_bmp_to_func(n2hi_stbi_write_func, &context, N2_SCAST(int, width), N2_SCAST(int, height), 4, src)) { res = N2_FALSE; } break;
	case N2_IMAGE_FILE_JPG:		if (!stbi_write_jpg_to_func(n2hi_stbi_write_func, &context, N2_SCAST(int, width), N2_SCAST(int, height), 4, src, quality)) { res = N2_FALSE; } break;
	case N2_IMAGE_FILE_PNG:		if (!stbi_write_png_to_func(n2hi_stbi_write_func, &context, N2_SCAST(int, width), N2_SCAST(int, height), 4, src, N2_SCAST(int, width) * 4)) { res = N2_FALSE; } break;
	case N2_IMAGE_FILE_TGA:		if (!stbi_write_tga_to_func(n2hi_stbi_write_func, &context, N2_SCAST(int, width), N2_SCAST(int, height), 4, src)) { res = N2_FALSE; } break;
	default:					res = N2_FALSE; break;
	}

	n2g_set_state(old_state);
	return res;
}
#endif

// 暗号化
#if N2_CONFIG_USE_AES_LIB
N2_API size_t n2h_aes_blocksize()
{
	return AES_BLOCKLEN;
}

N2_API size_t n2h_aes_keysize()
{
#if defined(AES256) && (AES256 == 1)
	return 256 / 8;
#elif defined(AES192) && (AES192 == 1)
	return 192 / 8;
#else
	return 128 / 8;
#endif
}

N2_API size_t n2h_aes_ivsize()
{
	return AES_BLOCKLEN;
}

N2_API n2_bool_t n2h_aes_encrypt(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, const uint8_t* key, size_t keysize, const uint8_t* iv, size_t ivsize)
{
	if (keysize < n2h_aes_keysize() || ivsize < n2h_aes_ivsize()) { return N2_FALSE; }

	const size_t dst_size = n2i_roundup_sz(src_size, AES_BLOCKLEN);
	if (!n2_buffer_reserve(state, dst, dst_size)) { return N2_FALSE; }
	dst->size_ = dst->buffer_size_;
	N2_MEMSET(dst->data_, 0x00, dst->size_);
	N2_MEMCPY(dst->data_, src, src_size);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, dst->data_, dst->size_);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_aes_decrypt(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, const uint8_t* key, size_t keysize, const uint8_t* iv, size_t ivsize)
{
	if (keysize < n2h_aes_keysize() || ivsize < n2h_aes_ivsize()) { return N2_FALSE; }
	if (src_size % AES_BLOCKLEN) { return N2_FALSE; }

	const size_t dst_size = src_size;
	if (!n2_buffer_reserve(state, dst, dst_size)) { return N2_FALSE; }
	dst->size_ = dst->buffer_size_;
	N2_MEMSET(dst->data_, 0x00, dst->size_);
	N2_MEMCPY(dst->data_, src, src_size);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, dst->data_, dst->size_);
	return N2_TRUE;
}
#endif

// MessagePack
#if N2_CONFIG_USE_MSGPACK_LIB

static void n2hi_msgpack_teardown(n2_state_t* state, n2h_msgpack_element_t* element)
{
	N2_ASSERT(element);
	switch (element->type_)
	{
	case N2H_MSGPACK_TYPE_ARRAY:
		n2h_msgpack_elementarray_free(state, element->content_.arrayval_.array_);
		break;
	case N2H_MSGPACK_TYPE_MAP:
		n2h_msgpack_elementpairarray_free(state, element->content_.mapval_.pairarray_);
		break;
	default: break;
	}
}

static void n2hi_msgpack_elementarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2hi_msgpack_teardown(state, N2_RCAST(n2h_msgpack_element_t*, element));
}
N2_DEFINE_TARRAY(n2h_msgpack_element_t, n2h_msgpack_elementarray, N2_API, n2i_setupfunc_nothing, n2hi_msgpack_elementarray_freefunc);

static int n2hi_msgpack_elementpairarray_cmpfunc(const n2_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	const n2h_msgpack_element_pair_t* lhs = N2_RCAST(const n2h_msgpack_element_pair_t*, lkey);
	const n2h_msgpack_element_pair_t* rhs = N2_RCAST(const n2h_msgpack_element_pair_t*, rkey);
	const int cmp = n2h_msgpack_element_cmp(&lhs->key_, &rhs->key_);
	if (cmp) { return cmp; }
	return lhs->original_order_ == rhs->original_order_ ? 0 : lhs->original_order_ < rhs->original_order_ ? -1 : 1;
}
static int n2hi_msgpack_elementpairarray_matchfunc(const n2_array_t* a, const void* lkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	const n2h_msgpack_element_pair_t* lhs = N2_RCAST(const n2h_msgpack_element_pair_t*, lkey);
	const n2h_msgpack_element_t* rhs = N2_RCAST(const n2h_msgpack_element_t*, key);
	const int cmp = n2h_msgpack_element_cmp(&lhs->key_, rhs);
	return cmp;
}
static void n2hi_msgpack_elementpairarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2h_msgpack_element_pair_t* pairelement = N2_RCAST(n2h_msgpack_element_pair_t*, element);
	n2hi_msgpack_teardown(state, &pairelement->key_);
	n2hi_msgpack_teardown(state, &pairelement->value_);
}
N2_DEFINE_TARRAY(n2h_msgpack_element_pair_t, n2h_msgpack_elementpairarray, N2_API, n2i_setupfunc_nothing, n2hi_msgpack_elementpairarray_freefunc);

static n2_bool_t n2hi_msgpack_parse_to(n2_state_t* state, n2h_msgpack_element_t* nelement, pmsgp_unpack_t* unpack)
{
	pmsgp_element_t element;
	if (!pmsgp_unpack_get_element(unpack, &element)) { return N2_FALSE; }
	pmsgp_unpack_next(unpack);

	switch (element.type)
	{
	case PMSGP_TYPE_NIL:	nelement->type_ = N2H_MSGPACK_TYPE_NIL; break;
	case PMSGP_TYPE_BOOL:	nelement->type_ = N2H_MSGPACK_TYPE_BOOL; nelement->content_.boolval_ = element.content.boolval ? N2_TRUE : N2_FALSE; break;
	case PMSGP_TYPE_UINT:	nelement->type_ = N2H_MSGPACK_TYPE_UINT; nelement->content_.uintval_ = element.content.uintval; break;
	case PMSGP_TYPE_INT:	nelement->type_ = N2H_MSGPACK_TYPE_INT; nelement->content_.intval_ = element.content.intval; break;
	case PMSGP_TYPE_FLOAT:	nelement->type_ = N2H_MSGPACK_TYPE_FLOAT; nelement->content_.floatval_ = element.content.floatval; break;
	case PMSGP_TYPE_DOUBLE:	nelement->type_ = N2H_MSGPACK_TYPE_DOUBLE; nelement->content_.doubleval_ = element.content.doubleval; break;
	case PMSGP_TYPE_STRING:	nelement->type_ = N2H_MSGPACK_TYPE_STRING; nelement->content_.strval_.str_ = element.content.strval.str; nelement->content_.strval_.length_ = element.content.strval.length; break;
	case PMSGP_TYPE_BINARY:	nelement->type_ = N2H_MSGPACK_TYPE_BINARY; nelement->content_.binval_.bin_ = element.content.binval.bin; nelement->content_.binval_.length_ = element.content.binval.length; break;
	case PMSGP_TYPE_ARRAY:
		{
			nelement->type_ = N2H_MSGPACK_TYPE_ARRAY;
			const size_t length = element.content.arrayval.length;
			nelement->content_.arrayval_.array_ = n2h_msgpack_elementarray_alloc(state, length, 0);
			for (size_t i = 0; i < length; ++i)
			{
				n2h_msgpack_element_t* value = n2h_msgpack_elementarray_push(state, nelement->content_.arrayval_.array_, NULL);
				if (!n2hi_msgpack_parse_to(state, value, unpack)) { return N2_FALSE; }
			}
		}
		break;
	case PMSGP_TYPE_MAP:
		{
			nelement->type_ = N2H_MSGPACK_TYPE_MAP;
			const size_t length = element.content.mapval.length;
			nelement->content_.mapval_.pairarray_ = n2h_msgpack_elementpairarray_alloc(state, length, 0);
			for (size_t i = 0; i < length; ++i)
			{
				n2h_msgpack_element_pair_t* pairvalue = n2h_msgpack_elementpairarray_push(state, nelement->content_.mapval_.pairarray_, NULL);
				pairvalue->key_.type_ = N2H_MSGPACK_TYPE_NIL;
				pairvalue->value_.type_ = N2H_MSGPACK_TYPE_NIL;
				pairvalue->original_order_ = i;
				if (!n2hi_msgpack_parse_to(state, &pairvalue->key_, unpack)) { return N2_FALSE; }
				if (!n2hi_msgpack_parse_to(state, &pairvalue->value_, unpack)) { return N2_FALSE; }
			}
			n2h_msgpack_elementpairarray_sort(nelement->content_.mapval_.pairarray_, n2hi_msgpack_elementpairarray_cmpfunc, NULL);
		}
		break;
	case PMSGP_TYPE_EXTENSION:	nelement->type_ = N2H_MSGPACK_TYPE_EXTENSION; nelement->content_.extval_.subtype_ = element.content.extval.subtype; nelement->content_.extval_.data_ = element.content.extval.data; nelement->content_.extval_.length_ = element.content.extval.length; break;
	default:				return N2_FALSE;
	}
	return N2_TRUE;;
}

static n2h_msgpack_element_t* n2hi_msgpack_parse(n2_state_t* state, pmsgp_unpack_t* unpack)
{
	n2h_msgpack_element_t* nelement = N2_TMALLOC(n2h_msgpack_element_t, state);
	if (!n2hi_msgpack_parse_to(state, nelement, unpack)) { goto fail_exit; }
	return nelement;

fail_exit:
	if (nelement) { n2h_msgpack_free(state, nelement); }
	return NULL;
}

N2_API int n2h_msgpack_element_cmp(const n2h_msgpack_element_t* lhs, const n2h_msgpack_element_t* rhs)
{
	if (lhs->type_ != rhs->type_) { return lhs->type_ - rhs->type_; }
	switch (lhs->type_)
	{
	case N2H_MSGPACK_TYPE_NIL:		return 0;
	case N2H_MSGPACK_TYPE_BOOL:		return N2_THREE_WAY_CMP(lhs->content_.boolval_, rhs->content_.boolval_);
	case N2H_MSGPACK_TYPE_UINT:		return N2_THREE_WAY_CMP(lhs->content_.uintval_, rhs->content_.uintval_);
	case N2H_MSGPACK_TYPE_INT:		return N2_THREE_WAY_CMP(lhs->content_.intval_, rhs->content_.intval_);
	case N2H_MSGPACK_TYPE_FLOAT:	return N2_THREE_WAY_CMP(lhs->content_.floatval_, rhs->content_.floatval_);
	case N2H_MSGPACK_TYPE_DOUBLE:	return N2_THREE_WAY_CMP(lhs->content_.doubleval_, rhs->content_.doubleval_);
	case N2H_MSGPACK_TYPE_STRING:	return n2_plstr_ncmp_sized(lhs->content_.strval_.str_, lhs->content_.strval_.length_, rhs->content_.strval_.str_, rhs->content_.strval_.length_);
	case N2H_MSGPACK_TYPE_BINARY:	return n2i_mem_ncmp_sized(lhs->content_.binval_.bin_, lhs->content_.binval_.length_, rhs->content_.binval_.bin_, rhs->content_.binval_.length_);
	case N2H_MSGPACK_TYPE_ARRAY:
		{
			const size_t lsize = n2h_msgpack_elementarray_size(lhs->content_.arrayval_.array_);
			const size_t rsize = n2h_msgpack_elementarray_size(rhs->content_.arrayval_.array_);
			if (lsize != rsize) { return N2_SCAST(int, lsize) - N2_SCAST(int, rsize); }
			for (size_t i = 0; i < lsize; ++i)
			{
				const n2h_msgpack_element_t* lelem =  n2h_msgpack_elementarray_peekc(lhs->content_.arrayval_.array_, N2_SCAST(int, i));
				const n2h_msgpack_element_t* relem =  n2h_msgpack_elementarray_peekc(rhs->content_.arrayval_.array_, N2_SCAST(int, i));
				const int cmp = n2h_msgpack_element_cmp(lelem, relem);
				if (!cmp) { return cmp; }
			}
			return 0;
		}
		break;
	case N2H_MSGPACK_TYPE_MAP:
		{
			const size_t lsize = n2h_msgpack_elementpairarray_size(lhs->content_.mapval_.pairarray_);
			const size_t rsize = n2h_msgpack_elementpairarray_size(rhs->content_.mapval_.pairarray_);
			if (lsize != rsize) { return N2_SCAST(int, lsize) - N2_SCAST(int, rsize); }
			for (size_t i = 0; i < lsize; ++i)
			{
				const n2h_msgpack_element_pair_t* lelem =  n2h_msgpack_elementpairarray_peekc(lhs->content_.mapval_.pairarray_, N2_SCAST(int, i));
				const n2h_msgpack_element_pair_t* relem =  n2h_msgpack_elementpairarray_peekc(rhs->content_.mapval_.pairarray_, N2_SCAST(int, i));
				int cmp = n2h_msgpack_element_cmp(&lelem->key_, &relem->key_);
				if (!cmp) { return cmp; }
				cmp = n2h_msgpack_element_cmp(&lelem->value_, &relem->value_);
				if (!cmp) { return cmp; }
			}
			return 0;
		}
		break;
	default:					N2_ASSERT(0); break;
	}
	return 0;
}

N2_API n2h_msgpack_element_t* n2h_msgpack_parse(n2_state_t* state, const void* msgpack, size_t msgpack_size)
{
	if (!msgpack || msgpack_size <= 0) { return NULL; }
	pmsgp_unpack_t unpack;
	pmsgp_unpack_init(&unpack, msgpack, msgpack_size);
	n2h_msgpack_element_t* element = n2hi_msgpack_parse(state, &unpack);
	pmsgp_unpack_fin(&unpack);
	return element;
}

N2_API void n2h_msgpack_free(n2_state_t* state, n2h_msgpack_element_t* element)
{
	n2hi_msgpack_teardown(state, element);
	n2_free(state, element);
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_at(const n2h_msgpack_element_t* ar, int index)
{
	if (!ar || ar->type_ != N2H_MSGPACK_TYPE_ARRAY) { return NULL; }
	return n2h_msgpack_elementarray_peekc(ar->content_.arrayval_.array_, index);
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_find(const n2h_msgpack_element_t* map, const n2h_msgpack_element_t* key)
{
	if (!map || map->type_ != N2H_MSGPACK_TYPE_MAP) { return NULL; }
	const n2h_msgpack_element_pair_t* epair = n2h_msgpack_elementpairarray_findcp(map->content_.mapval_.pairarray_, n2hi_msgpack_elementpairarray_matchfunc, key);
	if (!epair) { return NULL; }
	return &epair->value_;
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byuint_strict(const n2h_msgpack_element_t* map, uint64_t keyval)
{
	n2h_msgpack_element_t tmpe;
	tmpe.type_ = N2H_MSGPACK_TYPE_UINT;
	tmpe.content_.uintval_ = keyval;
	return n2h_msgpack_find(map, &tmpe);
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byint_strict(const n2h_msgpack_element_t* map, int64_t keyval)
{
	n2h_msgpack_element_t tmpe;
	tmpe.type_ = N2H_MSGPACK_TYPE_INT;
	tmpe.content_.intval_ = keyval;
	return n2h_msgpack_find(map, &tmpe);
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byint(const n2h_msgpack_element_t* map, int64_t keyval)
{
	const n2h_msgpack_element_t* e = n2h_msgpack_find_byint_strict(map, keyval);
	if (e) { return e; }
	if (keyval >= 0) { return n2h_msgpack_find_byuint_strict(map, N2_SCAST(uint64_t, keyval)); }
	return NULL;
}

N2_API const n2h_msgpack_element_t* n2h_msgpack_find_bystr(const n2h_msgpack_element_t* map, const char* name, size_t name_length)
{
	n2h_msgpack_element_t tmpe;
	tmpe.type_ = N2H_MSGPACK_TYPE_STRING;
	tmpe.content_.strval_.str_ = name;
	tmpe.content_.strval_.length_ = (uint32_t)(name_length == SIZE_MAX ? N2_STRLEN(name) : name_length);
	return n2h_msgpack_find(map, &tmpe);
}

N2_API n2_bool_t n2h_msgpack_get_asbool(n2_bool_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict)
{
	if (!o) { return N2_FALSE; }
	switch (o->type_)
	{
	case N2H_MSGPACK_TYPE_NIL:	*dst = N2_TRUE; return N2_TRUE;
	case N2H_MSGPACK_TYPE_BOOL:	*dst = o->content_.boolval_; return N2_TRUE;
	case N2H_MSGPACK_TYPE_INT:	if (strict) { break; } *dst = o->content_.intval_ ? N2_TRUE : N2_FALSE; return N2_TRUE;
	case N2H_MSGPACK_TYPE_UINT:	if (strict) { break; } *dst = o->content_.uintval_ ? N2_TRUE : N2_FALSE; return N2_TRUE;
	default:					break;
	}
	return N2_FALSE;
}

N2_API n2_bool_t n2h_msgpack_get_asint(int64_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict)
{
	if (!o) { return N2_FALSE; }
	switch (o->type_)
	{
	case N2H_MSGPACK_TYPE_NIL:	if (strict) { break; } *dst = 0; return N2_TRUE;
	case N2H_MSGPACK_TYPE_BOOL:	if (strict) { break; } *dst = o->content_.boolval_ ? 1 : 0; return N2_TRUE;
	case N2H_MSGPACK_TYPE_INT:	*dst = o->content_.intval_; return N2_TRUE;
	case N2H_MSGPACK_TYPE_UINT:	if (o->content_.uintval_ > INT64_MAX) { break; } *dst = N2_SCAST(int64_t, o->content_.uintval_); return N2_TRUE;
	default:					break;
	}
	return N2_FALSE;
}

N2_API n2_bool_t n2h_msgpack_get_asuint(uint64_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict)
{
	if (!o) { return N2_FALSE; }
	switch (o->type_)
	{
	case N2H_MSGPACK_TYPE_NIL:	if (strict) { break; } *dst = 0; return N2_TRUE;
	case N2H_MSGPACK_TYPE_BOOL:	if (strict) { break; } *dst = o->content_.boolval_ ? 1 : 0; return N2_TRUE;
	case N2H_MSGPACK_TYPE_INT:	if (o->content_.intval_ < 0) { break; } *dst = N2_SCAST(uint64_t, o->content_.intval_); return N2_TRUE;
	case N2H_MSGPACK_TYPE_UINT:	*dst = o->content_.uintval_; return N2_TRUE;
	default:					break;
	}
	return N2_FALSE;
}

N2_API n2_bool_t n2h_msgpack_get_asstr(n2_state_t* state, n2_str_t* dst, const n2h_msgpack_element_t* o)
{
	if (!o) { return N2_FALSE; }
	switch (o->type_)
	{
	case N2H_MSGPACK_TYPE_STRING:	n2_str_set(state, dst, o->content_.strval_.str_, o->content_.strval_.length_); return N2_TRUE;
	default:						break;
	}
	return N2_FALSE;
}

#endif

// データツリー
typedef struct n2h_datatree_arrayelement_t n2h_datatree_arrayelement_t;
struct n2h_datatree_arrayelement_t
{
	n2h_datatree_t* tree_;
};
N2_DECLARE_TARRAY(n2h_datatree_arrayelement_t, n2h_datatree_array, static);
static void n2hi_datatree_arrayelement_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2h_datatree_free(state, N2_RCAST(n2h_datatree_arrayelement_t*, element)->tree_);
}
N2_DEFINE_TARRAY(n2h_datatree_arrayelement_t, n2h_datatree_array, static, n2i_setupfunc_nothing, n2hi_datatree_arrayelement_freefunc);

typedef struct n2h_datatree_mapelement_t n2h_datatree_mapelement_t;
struct n2h_datatree_mapelement_t
{
	n2h_datatree_t* key_;
	n2h_datatree_t* tree_;
};
N2_DECLARE_TSORTED_ARRAY(n2h_datatree_mapelement_t, void, n2h_datatree_t, n2h_datatree_map, static);

typedef union n2h_datatree_field_t n2h_datatree_field_t;
union n2h_datatree_field_t
{
	n2_bool_t bvalue_;
	int64_t ivalue_;
	double fvalue_;
	n2_str_t strvalue_;
	n2_buffer_t binvalue_;
	n2h_datatree_array_t* arrayvalue_;
	n2h_datatree_map_t* mapvalue_;
};

struct n2h_datatree_t
{
	n2h_datatree_e type_;
	n2h_datatree_field_t field_;
};

static int n2hi_datatree_mapelement_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	const n2h_datatree_mapelement_t* lelem = N2_RCAST(const n2h_datatree_mapelement_t*, lkey);
	const n2h_datatree_mapelement_t* relem = N2_RCAST(const n2h_datatree_mapelement_t*, rkey);
	const int cmp = n2h_datatree_cmp(lelem->key_, relem->key_);
	if (cmp) { return cmp; }
	return n2h_datatree_cmp(lelem->tree_, relem->tree_);
}
static int n2hi_datatree_mapelement_matchfunc(const n2_sorted_array_t* a, const void* mapkey, const void* key)
{
	N2_UNUSE(a);
	return n2h_datatree_cmp(N2_RCAST(const n2h_datatree_mapelement_t*, mapkey)->key_, N2_RCAST(const n2h_datatree_t*, key));
}
static void n2hi_datatree_mapelement_setup(n2_state_t* state, n2h_datatree_map_t* map)
{
	N2_UNUSE(state);
	map->cmp_ = n2hi_datatree_mapelement_cmpfunc;
	map->match_ = n2hi_datatree_mapelement_matchfunc;
}
static void n2hi_datatree_mapelement_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2h_datatree_mapelement_t* mapelement = N2_RCAST(n2h_datatree_mapelement_t*, element);
	n2h_datatree_free(state, mapelement->key_);
	n2h_datatree_free(state, mapelement->tree_);
}
N2_DEFINE_TSORTED_ARRAY(n2h_datatree_mapelement_t, void, n2h_datatree_t, n2h_datatree_map, static, n2hi_datatree_mapelement_setup, n2hi_datatree_mapelement_freefunc);

static void n2hi_datatree_settmp_int(n2h_datatree_t* tmptree, int64_t ival)
{
	tmptree->type_ = N2H_DATATREE_INT;
	tmptree->field_.ivalue_ = ival;
}

static void n2hi_datatree_settmp_str(n2h_datatree_t* tmptree, const char* name, size_t name_size)
{
	tmptree->type_ = N2H_DATATREE_STRING;
	tmptree->field_.strvalue_.str_ = N2_CCAST(char*, name);
	tmptree->field_.strvalue_.size_ = name_size == SIZE_MAX ? N2_STRLEN(name) : name_size;
	tmptree->field_.strvalue_.buffer_size_ = tmptree->field_.strvalue_.size_;
}

static void n2h_datatree_teardown(n2_state_t* state, n2h_datatree_t* tree)
{
	switch (tree->type_)
	{
	case N2H_DATATREE_STRING:	n2_str_teardown(state, &tree->field_.strvalue_); break;
	case N2H_DATATREE_BINARY:	n2_buffer_teardown(state, &tree->field_.binvalue_); break;
	case N2H_DATATREE_ARRAY:	n2h_datatree_array_free(state, tree->field_.arrayvalue_); break;
	case N2H_DATATREE_MAP:		n2h_datatree_map_free(state, tree->field_.mapvalue_); break;
	default:					break;
	}
	tree->type_ = N2H_DATATREE_NULL;
}

N2_API n2h_datatree_t* n2h_datatree_allocnull(n2_state_t* state)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_NULL;
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocb(n2_state_t* state, n2_bool_t v)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_BOOL;
	tree->field_.bvalue_ = v;
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_alloci(n2_state_t* state, int64_t v)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_INT;
	tree->field_.ivalue_ = v;
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocf(n2_state_t* state, double v)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_FLOAT;
	tree->field_.fvalue_ = v;
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocstr(n2_state_t* state, const char* str, size_t str_size)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_STRING;
	n2_str_init(&tree->field_.strvalue_);
	n2_str_set(state, &tree->field_.strvalue_, str, str_size);
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocbin(n2_state_t* state, const void* bin, size_t bin_size)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_BINARY;
	n2_buffer_init(&tree->field_.binvalue_);
	n2_buffer_append(state, &tree->field_.binvalue_, bin, bin_size);
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocarray(n2_state_t* state)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_ARRAY;
	tree->field_.arrayvalue_ = n2h_datatree_array_alloc(state, 0, 0);
	return tree;
}

N2_API n2h_datatree_t* n2h_datatree_allocmap(n2_state_t* state)
{
	n2h_datatree_t* tree = N2_TMALLOC(n2h_datatree_t, state);
	tree->type_ = N2H_DATATREE_MAP;
	tree->field_.mapvalue_ = n2h_datatree_map_alloc(state, 0, 0);
	return tree;
}

N2_API void n2h_datatree_free(n2_state_t* state, n2h_datatree_t* tree)
{
	n2h_datatree_teardown(state, tree);
	n2_free(state, tree);
}

N2_API n2h_datatree_e n2h_datatree_type(const n2h_datatree_t* datatree)
{
	return datatree->type_;
}

N2_API int n2h_datatree_cmp(const n2h_datatree_t* ltree, const n2h_datatree_t* rtree)
{
	if (!ltree || !rtree) { return ltree == rtree ? 0 : ltree ? 1 : -1; }
	if (ltree->type_ != rtree->type_) { return ltree->type_ - rtree->type_; }
	switch (ltree->type_)
	{
	case N2H_DATATREE_NULL:		return 0;
	case N2H_DATATREE_BOOL:		return N2_THREE_WAY_CMP( ltree->field_.bvalue_, rtree->field_.bvalue_);
	case N2H_DATATREE_INT:		return N2_THREE_WAY_CMP( ltree->field_.ivalue_, rtree->field_.ivalue_);
	case N2H_DATATREE_FLOAT:	return N2_THREE_WAY_CMP( ltree->field_.fvalue_, rtree->field_.fvalue_);
	case N2H_DATATREE_STRING:	return N2_STRCMP(ltree->field_.strvalue_.str_, rtree->field_.strvalue_.str_);
	case N2H_DATATREE_BINARY:	return n2i_mem_ncmp_sized(ltree->field_.binvalue_.data_, ltree->field_.binvalue_.size_, rtree->field_.binvalue_.data_, rtree->field_.binvalue_.size_);
	case N2H_DATATREE_ARRAY:
		{
			if (ltree->field_.arrayvalue_->size_ != rtree->field_.arrayvalue_->size_) { return N2_SCAST(int, ltree->field_.arrayvalue_->size_) - N2_SCAST(int, rtree->field_.arrayvalue_->size_); }
			for (size_t i = 0; i < ltree->field_.arrayvalue_->size_; ++i)
			{
				const n2h_datatree_arrayelement_t* lelem =  n2h_datatree_array_peekc(ltree->field_.arrayvalue_, N2_SCAST(int, i));
				const n2h_datatree_arrayelement_t* relem =  n2h_datatree_array_peekc(rtree->field_.arrayvalue_, N2_SCAST(int, i));
				const int cmp = n2h_datatree_cmp(lelem->tree_, relem->tree_);
				if (!cmp) { return cmp; }
			}
			return 0;
		}
		break;
	case N2H_DATATREE_MAP:
		{
			if (ltree->field_.mapvalue_->a_.size_ != rtree->field_.mapvalue_->a_.size_) { return N2_SCAST(int, ltree->field_.mapvalue_->a_.size_) - N2_SCAST(int, rtree->field_.mapvalue_->a_.size_); }
			for (size_t i = 0; i < ltree->field_.mapvalue_->a_.size_; ++i)
			{
				const n2h_datatree_mapelement_t* lelem =  n2h_datatree_map_peekc(ltree->field_.mapvalue_, N2_SCAST(int, i));
				const n2h_datatree_mapelement_t* relem =  n2h_datatree_map_peekc(rtree->field_.mapvalue_, N2_SCAST(int, i));
				int cmp = n2h_datatree_cmp(lelem->key_, relem->key_);
				if (!cmp) { return cmp; }
				cmp = n2h_datatree_cmp(lelem->tree_, relem->tree_);
				if (!cmp) { return cmp; }
			}
			return 0;
		}
		break;
	default:					N2_ASSERT(0); break;
	}
	return 0;
}

N2_API n2_bool_t n2h_datatree_asbool(const n2h_datatree_t* datatree, n2_bool_t orval)
{
	if (!datatree) { return orval; }
	switch (datatree->type_)
	{
	case N2H_DATATREE_BOOL:		return datatree->field_.bvalue_;
	case N2H_DATATREE_INT:		return datatree->field_.ivalue_ ? N2_TRUE : N2_FALSE;
	case N2H_DATATREE_FLOAT:	return datatree->field_.fvalue_ ? N2_TRUE : N2_FALSE;
	case N2H_DATATREE_STRING:	return datatree->field_.strvalue_.size_ > 0 && n2_plstr_cmp_case(datatree->field_.strvalue_.str_, "false") != 0 ? N2_TRUE : N2_FALSE;
	default:					break;
	}
	return orval;
}

N2_API int64_t n2h_datatree_asint(const n2h_datatree_t* datatree, int64_t orval)
{
	if (!datatree) { return orval; }
	switch (datatree->type_)
	{
	case N2H_DATATREE_BOOL:		return datatree->field_.bvalue_ ? 1 : 0;
	case N2H_DATATREE_INT:		return datatree->field_.ivalue_;
	case N2H_DATATREE_FLOAT:	return N2_SCAST(int64_t, datatree->field_.fvalue_);
	case N2H_DATATREE_STRING:	return N2_SCAST(int64_t, N2_STRTOLL(datatree->field_.strvalue_.str_, NULL, 0));
	default:					break;
	}
	return orval;
}

N2_API double n2h_datatree_asfloat(const n2h_datatree_t* datatree, double orval)
{
	if (!datatree) { return orval; }
	switch (datatree->type_)
	{
	case N2H_DATATREE_BOOL:		return datatree->field_.bvalue_ ? 1 : 0;
	case N2H_DATATREE_INT:		return N2_SCAST(double, datatree->field_.ivalue_);
	case N2H_DATATREE_FLOAT:	return datatree->field_.fvalue_;
	case N2H_DATATREE_STRING:	return N2_SCAST(double, N2_STRTOD(datatree->field_.strvalue_.str_, NULL));
	default:					break;
	}
	return orval;
}

N2_API n2_str_t* n2h_datatree_asstr(n2_state_t* state, const n2h_datatree_t* datatree, const char* orval)
{
	if (datatree)
	{
		switch (datatree->type_)
		{
		case N2H_DATATREE_BOOL:		return n2_str_alloc_fmt(state, "%s", datatree->field_.bvalue_ ? "true" : "false");
		case N2H_DATATREE_INT:		return n2_str_alloc_fmt(state, "%" N2_VALINT_PRI, datatree->field_.ivalue_);
		case N2H_DATATREE_FLOAT:	return n2_str_alloc_fmt(state, "%" N2_VALINT_PRI, datatree->field_.fvalue_);
		case N2H_DATATREE_STRING:	return n2_str_clone(state, &datatree->field_.strvalue_);
		default:					break;
		}
	}
	return n2_str_alloc_fmt(state, "%s", orval);
}

N2_API const n2_str_t* n2h_datatree_peekstr(const n2h_datatree_t* datatree)
{
	if (datatree)
	{
		switch (datatree->type_)
		{
		case N2H_DATATREE_STRING:	return &datatree->field_.strvalue_;
		default:					break;
		}
	}
	return NULL;
}

N2_API size_t n2h_datatree_arraysize(const n2h_datatree_t* datatree)
{
	return datatree && datatree->type_ == N2H_DATATREE_ARRAY ? n2h_datatree_array_size(datatree->field_.arrayvalue_) : 0;
}

N2_API size_t n2h_datatree_mapsize(const n2h_datatree_t* datatree)
{
	return datatree && datatree->type_ == N2H_DATATREE_MAP ? n2h_datatree_map_size(datatree->field_.mapvalue_) : 0;
}

N2_API size_t n2h_datatree_size(const n2h_datatree_t* datatree)
{
	return N2_MAX(n2h_datatree_arraysize(datatree), n2h_datatree_mapsize(datatree));
}

N2_API const n2h_datatree_t* n2h_datatree_at(const n2h_datatree_t* datatree, int index)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_ARRAY) { return NULL; }
	const n2h_datatree_arrayelement_t* elem = n2h_datatree_array_peek(datatree->field_.arrayvalue_, index);
	return elem ? elem->tree_ : NULL;
}

N2_API const n2h_datatree_t* n2h_datatree_find(const n2h_datatree_t* datatree, const n2h_datatree_t* key)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return NULL; }
	const n2h_datatree_mapelement_t* elem = n2h_datatree_map_find(datatree->field_.mapvalue_, key);
	return elem ? elem->tree_ : NULL;
}

N2_API const n2h_datatree_t* n2h_datatree_find_byint(const n2h_datatree_t* datatree, int64_t keyval)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return NULL; }
	n2h_datatree_t tmptree;
	n2hi_datatree_settmp_int(&tmptree, keyval);
	return n2h_datatree_find(datatree, &tmptree);
}

N2_API const n2h_datatree_t* n2h_datatree_find_bystr(const n2h_datatree_t* datatree, const char* name)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return NULL; }
	n2h_datatree_t tmptree;
	n2hi_datatree_settmp_str(&tmptree, name, SIZE_MAX);
	return n2h_datatree_find(datatree, &tmptree);
}

N2_API const n2h_datatree_t* n2h_datatree_get_key(const n2h_datatree_t* datatree, int index)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return NULL; }
	const n2h_datatree_mapelement_t* elem = n2h_datatree_map_peek(datatree->field_.mapvalue_, index);
	return elem ? elem->key_ : NULL;
}

N2_API const n2h_datatree_t* n2h_datatree_get_value(const n2h_datatree_t* datatree, int index)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return NULL; }
	const n2h_datatree_mapelement_t* elem = n2h_datatree_map_peek(datatree->field_.mapvalue_, index);
	return elem ? elem->tree_ : NULL;
}

N2_API n2_bool_t n2h_datatree_set_at(n2_state_t* state, n2h_datatree_t* datatree, int index, n2h_datatree_t* val)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_ARRAY) { return N2_FALSE; }
	n2h_datatree_arrayelement_t* elem = n2h_datatree_array_peek(datatree->field_.arrayvalue_, index);
	if (!elem) { return N2_FALSE; }
	n2h_datatree_free(state, elem->tree_);
	elem->tree_ = val;
	return N2_TRUE;
}

N2_API n2_bool_t n2h_datatree_append(n2_state_t* state, n2h_datatree_t* datatree, n2h_datatree_t* val)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_ARRAY) { return N2_FALSE; }
	n2h_datatree_arrayelement_t* elem = n2h_datatree_array_push(state, datatree->field_.arrayvalue_, NULL);
	elem->tree_ = val;
	return N2_TRUE;
}

N2_API n2_bool_t n2h_datatree_set(n2_state_t* state, n2h_datatree_t* datatree, n2h_datatree_t* key, n2h_datatree_t* val)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return N2_FALSE; }
	n2h_datatree_mapelement_t elem;
	elem.key_ = key;
	elem.tree_ = val;
	n2h_datatree_map_insert(state, datatree->field_.mapvalue_, &elem, NULL);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_datatree_set_byint(n2_state_t* state, n2h_datatree_t* datatree, int64_t keyval, n2h_datatree_t* val)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return N2_FALSE; }
	n2h_datatree_t* key = n2h_datatree_alloci(state, keyval);
	return n2h_datatree_set(state, datatree, key, val);
}

N2_API n2_bool_t n2h_datatree_set_bystr(n2_state_t* state, n2h_datatree_t* datatree, const char* name, size_t name_size, n2h_datatree_t* val)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return N2_FALSE; }
	n2h_datatree_t* key = n2h_datatree_allocstr(state, name, name_size);
	return n2h_datatree_set(state, datatree, key, val);
}

N2_API n2_bool_t n2h_datatree_erase_at(n2_state_t* state, n2h_datatree_t* datatree, int index)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_ARRAY) { return N2_FALSE; }
	return n2h_datatree_array_erase(state, datatree->field_.arrayvalue_, index);
}

N2_API n2_bool_t n2h_datatree_erase(n2_state_t* state, n2h_datatree_t* datatree, const n2h_datatree_t* key)
{
	if (!datatree || datatree->type_ != N2H_DATATREE_MAP) { return N2_FALSE; }
	return n2h_datatree_map_erase(state, datatree->field_.mapvalue_, key) > 0;
}

N2_API n2_bool_t n2h_datatree_erase_byint(n2_state_t* state, n2h_datatree_t* datatree, int64_t keyval)
{
	n2h_datatree_t tmptree;
	n2hi_datatree_settmp_int(&tmptree, keyval);
	return n2h_datatree_erase(state, datatree, &tmptree);
}

N2_API n2_bool_t n2h_datatree_erase_bystr(n2_state_t* state, n2h_datatree_t* datatree, const char* name)
{
	n2h_datatree_t tmptree;
	n2hi_datatree_settmp_str(&tmptree, name, SIZE_MAX);
	return n2h_datatree_erase(state, datatree, &tmptree);
}

#if N2_CONFIG_USE_MSGPACK_LIB
static n2h_datatree_t* n2hi_datatree_msgpack_import(n2_state_t* state, pmsgp_unpack_t* unpack)
{
	n2h_datatree_t* tree = NULL;
	pmsgp_element_t element;
	if (!pmsgp_unpack_get_element(unpack, &element)) { goto fail_exit; }
	switch (element.type)
	{
	case PMSGP_TYPE_NIL:	tree = n2h_datatree_allocnull(state); break;
	case PMSGP_TYPE_BOOL:	tree = n2h_datatree_allocb(state, element.content.boolval ? N2_TRUE : N2_FALSE); break;
	case PMSGP_TYPE_UINT:	tree = n2h_datatree_alloci(state, N2_BCAST(int64_t, element.content.uintval)); break;
	case PMSGP_TYPE_INT:	tree = n2h_datatree_alloci(state, N2_SCAST(int64_t, element.content.intval)); break;
	case PMSGP_TYPE_FLOAT:	tree = n2h_datatree_allocf(state, N2_SCAST(double, element.content.floatval)); break;
	case PMSGP_TYPE_DOUBLE:	tree = n2h_datatree_allocf(state, N2_SCAST(double, element.content.doubleval)); break;
	case PMSGP_TYPE_STRING:	tree = n2h_datatree_allocstr(state, element.content.strval.str, element.content.strval.length); break;
	case PMSGP_TYPE_BINARY:	tree = n2h_datatree_allocbin(state, element.content.binval.bin, element.content.binval.length); break;
	case PMSGP_TYPE_ARRAY:
		{
			tree = n2h_datatree_allocarray(state);
			const size_t length = element.content.arrayval.length;
			n2h_datatree_array_reserve(state, tree->field_.arrayvalue_, length);
			for (size_t i = 0; i < length; ++i)
			{
				n2h_datatree_t* value = n2hi_datatree_msgpack_import(state, unpack);
				if (!value) { goto fail_exit; }
				n2h_datatree_arrayelement_t ae;
				ae.tree_ = value;
				n2h_datatree_array_push(state, tree->field_.arrayvalue_, &ae);
			}
		}
		break;
	case PMSGP_TYPE_MAP:
		{
			tree = n2h_datatree_allocmap(state);
			const size_t length = element.content.mapval.length;
			n2h_datatree_map_reserve(state, tree->field_.mapvalue_, length);
			for (size_t i = 0; i < length; ++i)
			{
				n2h_datatree_t* key = n2hi_datatree_msgpack_import(state, unpack);
				if (!key) { goto fail_exit; }
				n2h_datatree_t* value = n2hi_datatree_msgpack_import(state, unpack);
				if (!value) { n2h_datatree_free(state, key); goto fail_exit; }
				n2h_datatree_mapelement_t me;
				me.key_ = key;
				me.tree_ = value;
				n2h_datatree_map_insert(state, tree->field_.mapvalue_, &me, NULL);
			}
		}
		break;
	case PMSGP_TYPE_EXTENSION:	tree = n2h_datatree_allocbin(state, element.content.extval.data, element.content.extval.length); break;
	default:				goto fail_exit;
	}
	return tree;

fail_exit:
	if (tree) { n2h_datatree_free(state, tree); }
	return NULL;
}

typedef struct n2hi_datatree_msgpack_context_t n2hi_datatree_msgpack_context_t;
struct n2hi_datatree_msgpack_context_t
{
	n2_state_t* state_;
	n2_buffer_t* dst_;
};

static pmsgp_bool_t n2hi_datatree_msgpack_write_func(void* user, const void* data, size_t length)
{
	n2hi_datatree_msgpack_context_t* context = N2_RCAST(n2hi_datatree_msgpack_context_t*, user);
	n2_buffer_append(context->state_, context->dst_, data, length);
	return PMSGP_TRUE;
}

static n2_bool_t n2hi_datatree_msgpack_export(n2_state_t* state, pmsgp_pack_t* pack, const n2h_datatree_t* tree)
{
	switch (tree->type_)
	{
	case N2H_DATATREE_NULL:		if (!pmsgp_pack_put_nil(pack)) { return N2_FALSE; } break;
	case N2H_DATATREE_BOOL:		if (!pmsgp_pack_put_bool(pack, tree->field_.bvalue_ ? PMSGP_TRUE : PMSGP_FALSE)) { return N2_FALSE; } break;
	case N2H_DATATREE_INT:		if (!pmsgp_pack_put_int(pack, tree->field_.ivalue_)) { return N2_FALSE; } break;
	case N2H_DATATREE_FLOAT:	if (!pmsgp_pack_put_double(pack, tree->field_.fvalue_)) { return N2_FALSE; } break;
	case N2H_DATATREE_STRING:	if (!pmsgp_pack_put_str(pack, tree->field_.strvalue_.str_, (uint32_t)(tree->field_.strvalue_.size_))) { return N2_FALSE; } break;
	case N2H_DATATREE_BINARY:	if (!pmsgp_pack_put_bin(pack, tree->field_.binvalue_.data_, (uint32_t)(tree->field_.binvalue_.size_))) { return N2_FALSE; } break;
	case N2H_DATATREE_ARRAY:
		{
			const size_t length = n2h_datatree_array_size(tree->field_.arrayvalue_);
			if (!pmsgp_pack_put_array_size(pack, (uint32_t)length)) { return N2_FALSE; }
			for (size_t i = 0; i < length; ++i)
			{
				const n2h_datatree_arrayelement_t* ae = n2h_datatree_array_peek(tree->field_.arrayvalue_, N2_SCAST(int, i));
				if (!n2hi_datatree_msgpack_export(state, pack, ae->tree_)) { return N2_FALSE; }
			}
		}
		break;
	case N2H_DATATREE_MAP:
		{
			const size_t length = n2h_datatree_map_size(tree->field_.mapvalue_);
			if (!pmsgp_pack_put_map_size(pack, (uint32_t)length)) { return N2_FALSE; }
			for (size_t i = 0; i < length; ++i)
			{
				const n2h_datatree_mapelement_t* me = n2h_datatree_map_peek(tree->field_.mapvalue_, N2_SCAST(int, i));
				if (!n2hi_datatree_msgpack_export(state, pack, me->key_)) { return N2_FALSE; }
				if (!n2hi_datatree_msgpack_export(state, pack, me->tree_)) { return N2_FALSE; }
			}
		}
		break;
	default:					return N2_FALSE;
	}
	return N2_TRUE;
}

N2_API n2h_datatree_t* n2h_datatree_read_from_msgpack(n2_state_t* state, const void* msgpack, size_t msgpack_size)
{
	if (!msgpack || msgpack_size <= 0) { return NULL; }
	pmsgp_unpack_t unpack;
	pmsgp_unpack_init(&unpack, msgpack, msgpack_size);
	n2h_datatree_t* tree = n2hi_datatree_msgpack_import(state, &unpack);
	pmsgp_unpack_fin(&unpack);
	return tree;
}

N2_API n2_bool_t n2h_datatree_write_as_msgpack_to(n2_state_t* state, n2_buffer_t* write_to, const n2h_datatree_t* tree)
{
	if (!tree) { N2_FALSE; }
	n2_buffer_clear(write_to);
	n2hi_datatree_msgpack_context_t context;
	context.state_ = state;
	context.dst_ = write_to;
	pmsgp_pack_t pack;
	pmsgp_pack_init(&pack, &n2hi_datatree_msgpack_write_func, NULL, &context);
	n2_bool_t res = N2_TRUE;
	if (!n2hi_datatree_msgpack_export(state, &pack, tree)) { res = N2_FALSE; }
	if (pmsgp_pack_get_error(&pack) != PMSGP_ERROR_NONE) { res = N2_FALSE; }
	pmsgp_pack_fin(&pack);
	return res;
}
#endif

#if N2_CONFIG_USE_JSON_LIB
static void* n2hi_json_alloc(void* user_data, size_t size)
{
	return n2_malloc(N2_RCAST(n2_state_t*, user_data), size);
}

static n2h_datatree_t* n2hi_datatree_json_import(n2_state_t* state, struct json_value_s* json)
{
	n2h_datatree_t* tree = NULL;
	switch (json->type)
	{
	case json_type_null:	tree = n2h_datatree_allocnull(state); break;
	case json_type_false:	tree = n2h_datatree_allocb(state, N2_FALSE); break;
	case json_type_true:	tree = n2h_datatree_allocb(state, N2_TRUE); break;
	case json_type_number:
		{
			struct json_number_s* njson = json_value_as_number(json);
			N2_ASSERT(njson);
			n2_str_t tstr; n2_str_init(&tstr); n2_str_set(state, &tstr, njson->number, njson->number_size);
			n2_bool_t is_float = N2_FALSE;
			if (n2_plstr_search(tstr.str_, tstr.size_, ".", 1) >= 0 ||
				n2_plstr_search(tstr.str_, tstr.size_, "E", 1) >= 0 ||
				n2_plstr_search(tstr.str_, tstr.size_, "e", 1) >= 0)
			{
				is_float = N2_TRUE;
			}
			if (is_float) { tree = n2h_datatree_alloci(state, N2_SCAST(int64_t, N2_STRTOLL(tstr.str_, NULL, 0))); }
			else { tree = n2h_datatree_allocf(state, N2_SCAST(double, N2_STRTOD(tstr.str_, NULL))); }
			n2_str_teardown(state, &tstr);
		}
		break;
	case json_type_string:
		{
			struct json_string_s* sjson = json_value_as_string(json);
			N2_ASSERT(sjson);
			tree = n2h_datatree_allocstr(state, sjson->string, sjson->string_size);
		}
		break;
	case json_type_array:
		{
			tree = n2h_datatree_allocarray(state);
			struct json_array_s* ajson = json_value_as_array(json);
			N2_ASSERT(ajson);
			struct json_array_element_s* ejson = ajson->start;
			for (size_t i = 0; i < ajson->length; ++i)
			{
				n2h_datatree_t* child = n2hi_datatree_json_import(state, ejson->value);
				if (!child) { goto fail_exit; }
				if (!n2h_datatree_append(state, tree, child)) { goto fail_exit; }
				ejson = ejson->next;
			}
		}
		break;
	case json_type_object:
		{
			tree = n2h_datatree_allocmap(state);
			struct json_object_s* ojson = json_value_as_object(json);
			N2_ASSERT(ojson);
			struct json_object_element_s* ejson = ojson->start;
			for (size_t i = 0; i < ojson->length; ++i)
			{
				n2h_datatree_t* child = n2hi_datatree_json_import(state, ejson->value);
				if (!child) { n2h_datatree_free(state, tree); return NULL; }
				n2h_datatree_set_bystr(state, tree, ejson->name->string, ejson->name->string_size, child);
				ejson = ejson->next;
			}
		}
		break;
	default:				N2_ASSERT(0); break;
	}
	return tree;

fail_exit:
	if (tree) { n2h_datatree_free(state, tree); }
	return NULL;
}

static size_t n2hi_datatree_json_export_value(void* dst, const n2h_datatree_t* tree)
{
	N2_ASSERT(tree);
	size_t res = 0;
	switch (tree->type_)
	{
	case N2H_DATATREE_NULL:
		{
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				w->payload = NULL; w->type = json_type_null;
			}
			res += sizeof(struct json_value_s);
		}
		break;
	case N2H_DATATREE_BOOL:
		{
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				w->payload = NULL; w->type = tree->field_.bvalue_ ? json_type_true : json_type_false;
			}
			res += sizeof(struct json_value_s);
		}
		break;
	case N2H_DATATREE_INT:
		{
			int ssize = n2_snprintf(NULL, 0, "%I64d", tree->field_.ivalue_);
			if (ssize < 0) { return 0; }
			res += N2_SCAST(size_t, ssize + 1);
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				struct json_number_s* p = N2_RCAST(struct json_number_s*, n2_ptr_offset(w, sizeof(struct json_value_s)));
				char* n = N2_RCAST(char*, n2_ptr_offset(p, sizeof(struct json_number_s)));
				w->payload = p; w->type = json_type_number;
				int wsize = n2_snprintf(n, ssize, "%64d", tree->field_.ivalue_); p->number = n; p->number_size = wsize;
			}
			res += sizeof(struct json_value_s) + sizeof(struct json_number_s);
		}
		break;
	case N2H_DATATREE_FLOAT:
		{
			int ssize = n2_snprintf(NULL, 0, "%lf", tree->field_.fvalue_);
			if (ssize < 0) { return 0; }
			res += N2_SCAST(size_t, ssize + 1);
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				struct json_number_s* p = N2_RCAST(struct json_number_s*, n2_ptr_offset(w, sizeof(struct json_value_s)));
				char* n = N2_RCAST(char*, n2_ptr_offset(p, sizeof(struct json_number_s)));
				w->payload = p; w->type = json_type_number;
				int wsize = n2_snprintf(n, ssize, "%lf", tree->field_.fvalue_); p->number = n; p->number_size = wsize;
			}
			res += sizeof(struct json_value_s) + sizeof(struct json_number_s);
		}
		break;
	case N2H_DATATREE_STRING:
		{
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				struct json_string_s* s = N2_RCAST(struct json_string_s*, n2_ptr_offset(w, sizeof(struct json_value_s)));
				w->payload = s; w->type = json_type_string;
				s->string = tree->field_.strvalue_.str_; s->string_size = tree->field_.strvalue_.size_;/*use external memory*/
			}
			res += sizeof(struct json_value_s) + sizeof(struct json_string_s);
		}
		break;
	case N2H_DATATREE_ARRAY:
		{
			const size_t num = n2h_datatree_array_size(tree->field_.arrayvalue_);
			res += sizeof(struct json_array_element_s) * num;
			for (size_t i = 0; i < num; ++i)
			{
				const n2h_datatree_t* child = n2h_datatree_at(tree, N2_SCAST(int, i));
				N2_ASSERT(child);
				const size_t childsize = n2hi_datatree_json_export_value(NULL, child);
				if (!childsize) { return 0; }
				res += childsize;
			}
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				struct json_array_s* a = N2_RCAST(struct json_array_s*, n2_ptr_offset(w, sizeof(struct json_value_s)));
				struct json_array_element_s* e = N2_RCAST(struct json_array_element_s*, n2_ptr_offset(a, sizeof(struct json_array_s)));
				void* edata = n2_ptr_offset(e, sizeof(struct json_array_element_s) * num);
				w->payload = a; w->type = json_type_array;
				a->length = num; a->start = e; e->next = NULL;
				for (size_t i = 0; i < num; ++i)
				{
					const n2h_datatree_t* child = n2h_datatree_at(tree, N2_SCAST(int, i));
					N2_ASSERT(child);
					const size_t childsize = n2hi_datatree_json_export_value(edata, child);
					e->value = edata;
					edata = n2_ptr_offset(edata, childsize);
					e->next = (i < (num - 1)) ? e + 1 : NULL;
					e = e->next;
				}
			}
			res += sizeof(struct json_value_s) + sizeof(struct json_array_s);
		}
		break;
	case N2H_DATATREE_MAP:
		{
			const size_t num = n2h_datatree_map_size(tree->field_.mapvalue_);
			res += (sizeof(struct json_object_element_s) + sizeof(struct json_string_s)) * num;
			for (size_t i = 0; i < num; ++i)
			{
				const n2h_datatree_mapelement_t* child = n2h_datatree_map_peekc(tree->field_.mapvalue_, N2_SCAST(int, i));
				N2_ASSERT(child);
				const size_t childsize = n2hi_datatree_json_export_value(NULL, child->tree_);
				if (!childsize) { return 0; }
				res += childsize;
			}
			if (dst)
			{
				struct json_value_s* w = N2_RCAST(struct json_value_s*, dst);
				struct json_object_s* o = N2_RCAST(struct json_object_s*, n2_ptr_offset(w, sizeof(struct json_value_s)));
				struct json_object_element_s* e = N2_RCAST(struct json_object_element_s*, n2_ptr_offset(o, sizeof(struct json_object_s)));
				struct json_string_s* es = N2_RCAST(struct json_string_s*, n2_ptr_offset(e, sizeof(struct json_object_element_s) * num));
				void* edata = n2_ptr_offset(es, sizeof(struct json_string_s) * num);
				w->payload = o; w->type = json_type_object;
				o->length = num; o->start = e; e->next = NULL;
				for (size_t i = 0; i < num; ++i)
				{
					const n2h_datatree_mapelement_t* child = n2h_datatree_map_peekc(tree->field_.mapvalue_, N2_SCAST(int, i));
					N2_ASSERT(child);
					const size_t childsize = n2hi_datatree_json_export_value(edata, child->tree_);
					if (child->key_->type_ != N2H_DATATREE_STRING) { return 0; }// invalid for json key
					e->name = es; es->string = child->key_->field_.strvalue_.str_; es->string_size = child->key_->field_.strvalue_.size_; ++es;/*use external memory*/
					e->value = edata;
					edata = n2_ptr_offset(edata, childsize);
					e->next = (i < (num - 1)) ? e + 1 : NULL;
					e = e->next;
				}
			}
			res += sizeof(struct json_value_s) + sizeof(struct json_object_s);
		}
		break;
	default:
		N2_ASSERT(0);
		break;
	}
	return res;
}

static struct json_value_s* n2hi_datatree_export(n2_state_t* state, const n2h_datatree_t* tree)
{
	if (!tree) { return NULL; }
	const size_t valsize = n2hi_datatree_json_export_value(NULL, tree);
	if (!valsize) { return NULL; }
	void* data = n2_malloc(state, valsize);
	const size_t wsize = n2hi_datatree_json_export_value(data, tree);
	N2_ASSERT(wsize > 0);
	N2_UNUSE(wsize);
	return N2_RCAST(struct json_value_s*, data);
}

N2_API n2h_datatree_t* n2h_datatree_read_from_json(n2_state_t* state, const char* json, size_t json_size)
{
	if (json_size == SIZE_MAX) { json_size = N2_STRLEN(json); }
	struct json_parse_result_s result;
	struct json_value_s* jsonval = json_parse_ex(json, json_size, json_parse_flags_allow_json5, n2hi_json_alloc, state, &result);
	n2h_datatree_t* tree = NULL;
	if (jsonval && result.error == json_parse_error_none) { tree = n2hi_datatree_json_import(state, jsonval); }
	return tree;
}

N2_API n2_bool_t n2h_datatree_is_writable_as_json(const n2h_datatree_t* tree)
{
	if (!tree) { return N2_FALSE; }
	const size_t valsize = n2hi_datatree_json_export_value(NULL, tree);
	if (!valsize) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_datatree_write_as_json_to(n2_state_t* state, n2_str_t* write_to, const n2h_datatree_t* tree, n2_bool_t pretty)
{
	struct json_value_s* json = n2hi_datatree_export(state, tree);
	if (!json) { n2_str_clear(write_to); return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	size_t required = 0;
	if (pretty)
	{
		if (json_write_minified_get_value_size(json, &required)) { res = N2_FALSE; }
		if (res)
		{
			n2_str_reserve(state, write_to, required + 4);
			char* endptr = json_write_minified_value(json, write_to->str_);
			if (endptr) { *endptr = '\0'; n2_str_update_size(write_to); } else { res = N2_FALSE; }
		}
	}
	else
	{
		static const char* indent = "  "; const size_t indent_size = N2_STRLEN(indent);
		static const char* newline = "\n"; const size_t newline_size = N2_STRLEN(newline);
		if (json_write_pretty_get_value_size(json, 0, indent_size, newline_size, &required)) { res = N2_FALSE; }
		if (res)
		{
			n2_str_reserve(state, write_to, required + 4);
			char* endptr = json_write_pretty_value(json, 0, indent, newline, write_to->str_);
			if (endptr) { *endptr = '\0'; n2_str_update_size(write_to); } else { res = N2_FALSE; }
		}
	}
	n2_free(state, json);
	return res;
}
#endif

// 圧縮
static const struct {
	const char* name_;
	n2h_compress_e compress_;
} n2hi_compress_table[] = 
{
	{"none",		N2H_COMPRESS_NULL},
	{"z",			N2H_COMPRESS_Z},
	{"ulz",			N2H_COMPRESS_ULZ},
	{NULL,			N2H_COMPRESS_NULL}
};

N2_API const char* n2h_compress_name(n2h_compress_e compress, const char* on_failed)
{
	for (size_t i = 0; n2hi_compress_table[i].name_; ++i)
	{
		if (n2hi_compress_table[i].compress_ == compress)
		{
			return n2hi_compress_table[i].name_;
		}
	}
	return on_failed;
}

N2_API n2h_compress_e n2h_compress_find(const char* name, size_t name_length, n2h_compress_e on_failed)
{
	if (name_length == SIZE_MAX) { name_length = N2_STRLEN(name); }
	for (size_t i = 0; n2hi_compress_table[i].name_; ++i)
	{
		if (N2_STRLEN(n2hi_compress_table[i].name_) == name_length && N2_STRNCMP(n2hi_compress_table[i].name_, name, name_length) == 0)
		{
			return n2hi_compress_table[i].compress_;
		}
	}
	return on_failed;
}

// Z圧縮
#if N2_CONFIG_USE_Z_LIB
static void* n2hi_z_alloc(void* opaque, size_t items, size_t size)
{
	return n2_malloc(N2_RCAST(n2_state_t*, opaque), items * size);
}

static void n2hi_z_free(void* opaque, void* address)
{
	n2_free(N2_RCAST(n2_state_t*, opaque), address);
}

N2_API n2_bool_t n2h_z_compress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, int level)
{
	int status;
	mz_stream stream;

	N2_ASSERT(dst);
	N2_ASSERT(src);

	if (level < MZ_NO_COMPRESSION || level > MZ_BEST_COMPRESSION) { return N2_FALSE; }

	N2_MEMSET(&stream, 0, sizeof(stream));

	const mz_ulong bound_size = mz_compressBound(N2_SCAST(mz_ulong, src_size));
	n2_buffer_reserve(state, dst, bound_size + 4);

	stream.zalloc = n2hi_z_alloc;
	stream.zfree = n2hi_z_free;
	stream.opaque = state;
	stream.next_in = N2_RCAST(const unsigned char*, src);
	stream.avail_in = N2_SCAST(mz_uint32, src_size);
	stream.next_out = N2_RCAST(unsigned char*, dst->data_);
	stream.avail_out = N2_SCAST(mz_uint32, dst->buffer_size_);

	status = mz_deflateInit(&stream, level);
	if (status != MZ_OK) { return N2_FALSE; }

	status = mz_deflate(&stream, MZ_FINISH);
	if (status != MZ_STREAM_END)
	{
		mz_deflateEnd(&stream);
		return N2_FALSE;
	}

	dst->size_ = N2_SCAST(size_t, stream.total_out);
	mz_deflateEnd(&stream);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_z_decompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size)
{
	mz_stream stream;
	int status;

	N2_ASSERT(dst);
	N2_ASSERT(src);

	N2_MEMSET(&stream, 0, sizeof(stream));

	stream.zalloc = n2hi_z_alloc;
	stream.zfree = n2hi_z_free;
	stream.opaque = state;
	stream.next_in = N2_RCAST(const unsigned char*, src);
	stream.avail_in = N2_SCAST(mz_uint32, src_size);
	stream.next_out = N2_RCAST(unsigned char*, dst);
	stream.avail_out = N2_RCAST(mz_uint32, dst_size);

	status = mz_inflateInit(&stream);
	if (status != MZ_OK) { return N2_FALSE; }

	status = mz_inflate(&stream, MZ_FINISH);
	if (status != MZ_STREAM_END)
	{
		mz_inflateEnd(&stream);
		return N2_FALSE;
	}

	if (dst_written) { *dst_written = N2_SCAST(size_t, stream.total_out); }
	mz_inflateEnd(&stream);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_z_decompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size)
{
	mz_stream stream;
	int status;
	n2_buffer_t tbuf;

	N2_ASSERT(dst);
	N2_ASSERT(src);

	N2_MEMSET(&stream, 0, sizeof(stream));

	n2_buffer_init(&tbuf);
	n2_buffer_reserve(state, &tbuf, N2_MAX(1024, state->config_.z_decompress_tmp_buffer_size_));

	stream.zalloc = n2hi_z_alloc;
	stream.zfree = n2hi_z_free;
	stream.opaque = state;
	stream.next_in = N2_RCAST(const unsigned char*, src);
	stream.avail_in = N2_SCAST(mz_uint32, src_size);
	stream.next_out = N2_RCAST(unsigned char*, tbuf.data_);
	stream.avail_out = N2_SCAST(mz_uint32, tbuf.buffer_size_);

	status = mz_inflateInit(&stream);
	if (status != MZ_OK) { goto fail_exit; }

	for (;;)
	{
		status = mz_inflate(&stream, MZ_NO_FLUSH);
		n2_buffer_append(state, dst, tbuf.data_, tbuf.buffer_size_ - N2_SCAST(size_t, stream.avail_out));
		if (status == MZ_STREAM_END) { break; }
		if (status != MZ_OK) { mz_inflateEnd(&stream); goto fail_exit; }
		stream.next_out = N2_RCAST(unsigned char*, tbuf.data_);
		stream.avail_out = N2_SCAST(mz_uint32, tbuf.buffer_size_);
	}

	dst->size_ = N2_SCAST(size_t, stream.total_out);

	mz_inflateEnd(&stream);
	n2_buffer_teardown(state, &tbuf);
	return N2_TRUE;

fail_exit:
	n2_buffer_teardown(state, &tbuf);
	return N2_FALSE;
}
#endif

// uzl圧縮
#if N2_CONFIG_USE_ULZ_LIB
static const uint8_t n2hi_ulz_wrap_magic[] = {0x55, 0x4c, 0x5a, 0x21};// ULZ!

static n2_bool_t n2hi_ulz_compress_offset(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, size_t offset)
{
	const int bound = CulzCompressBound(N2_SCAST(int, src_size));
	if (bound < 0) { return N2_FALSE; }
	if (!n2_buffer_reserve(state, dst, N2_SCAST(size_t, bound) + offset)) { return N2_FALSE; }
	void* hash_table_work = n2_malloc(state, CulzHashTableWorkSize());
	void* prev_work = n2_malloc(state, CulzPrevWorkSize());
	const int written = CulzCompressFastNoAlloc(src, N2_SCAST(int, src_size), n2_ptr_offset(dst->data_, offset), hash_table_work, prev_work);
	if (hash_table_work) { n2_free(state, hash_table_work); }
	if (prev_work) { n2_free(state, prev_work); }
	if (written > 0) { dst->size_ = N2_SCAST(size_t, written) + offset; }
	return written > 0;
}

N2_API n2_bool_t n2h_ulz_compress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size)
{
	return n2hi_ulz_compress_offset(state, dst, src, src_size, 0);
}

N2_API n2_bool_t n2h_ulz_decompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size)
{
	N2_UNUSE(state);
	const int res = CulzDecompress(N2_RCAST(const uint8_t*, src), N2_SCAST(int, src_size), N2_RCAST(uint8_t*, dst), N2_SCAST(int, dst_size));
	if (res < 0) { return N2_FALSE; }
	if (dst_written) { *dst_written = N2_SCAST(size_t, res); }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_ulz_wverify(const void* src, size_t src_size)
{
	if (src_size < sizeof(n2hi_ulz_wrap_magic)) { return N2_FALSE; }
	return N2_MEMCMP(src, n2hi_ulz_wrap_magic, sizeof(n2hi_ulz_wrap_magic)) == 0;
}

N2_API n2_bool_t n2h_ulz_wget(n2h_ulz_wrap_t* dst, const void* src, size_t src_size)
{
	if (!n2h_ulz_wverify(src, src_size)) { return 0; }
	if (src_size < sizeof(n2hi_ulz_wrap_magic) + sizeof(n2h_ulz_wrap_t)) { return 0; }
	if (dst)
	{
		const void* wrap_base = n2_cptr_offset(src, sizeof(n2hi_ulz_wrap_magic));
#if 0
		N2_MEMCPY(dst, wrap_base, sizeof(n2h_ulz_wrap_t));
#else
		dst->compressed_size_ = n2_ptr_read64(n2_cptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, compressed_size_)));
		dst->decompressed_size_ = n2_ptr_read64(n2_cptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, decompressed_size_)));
		dst->check_ = n2_ptr_read32(n2_cptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, check_)));
		dst->payload_offset_ = n2_ptr_read32(n2_cptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, payload_offset_)));
#endif
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2h_ulz_wcompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size)
{
	const size_t header_size = sizeof(n2hi_ulz_wrap_magic) + sizeof(n2h_ulz_wrap_t);
	if (!n2hi_ulz_compress_offset(state, dst, src, src_size, header_size)) { return N2_FALSE; }
	n2h_ulz_wrap_t wrap;
	N2_MEMSET(&wrap, 0, sizeof(wrap));
	wrap.compressed_size_ = dst->size_;
	wrap.decompressed_size_ = src_size;
	wrap.check_ = n2h_crc32(src, src_size);
	wrap.payload_offset_ = 0;
	N2_MEMCPY(dst->data_, n2hi_ulz_wrap_magic, sizeof(n2hi_ulz_wrap_magic));
#if 0
	N2_MEMCPY(n2_ptr_offset(dst->data_, sizeof(n2hi_ulz_wrap_magic)), &wrap, sizeof(wrap));
#else
	{
		void* wrap_base = n2_ptr_offset(dst->data_, sizeof(n2hi_ulz_wrap_magic));
		n2_ptr_write64(n2_ptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, compressed_size_)), wrap.compressed_size_);
		n2_ptr_write64(n2_ptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, decompressed_size_)), wrap.decompressed_size_);
		n2_ptr_write32(n2_ptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, check_)), wrap.check_);
		n2_ptr_write32(n2_ptr_offset(wrap_base, offsetof(n2h_ulz_wrap_t, payload_offset_)), wrap.payload_offset_);
	}
#endif
	return N2_TRUE;
}

N2_API n2_bool_t n2h_ulz_wdecompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size)
{
	if (!n2h_ulz_wverify(src, src_size)) { return N2_FALSE; }
	n2h_ulz_wrap_t wrap;
	if (!n2h_ulz_wget(&wrap, src, src_size)) { return N2_FALSE; }
	if (dst_size < wrap.decompressed_size_) { return N2_FALSE; }
	const size_t header_size = sizeof(n2hi_ulz_wrap_magic) + sizeof(wrap);
	const size_t payload_offset = header_size + wrap.payload_offset_;
	if (payload_offset >= src_size) { return N2_FALSE; }
	const void* payload = n2_cptr_offset(src, payload_offset);
	size_t payload_size = src_size - payload_offset;
	if (payload_size < wrap.compressed_size_) { return N2_FALSE; }
	if (!n2h_ulz_decompress_to(state, dst, dst_size, dst_written, payload, payload_size)) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_ulz_wdecompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size)
{
	if (!n2h_ulz_wverify(src, src_size)) { return 0; }
	n2h_ulz_wrap_t wrap;
	if (!n2h_ulz_wget(&wrap, src, src_size)) { return N2_FALSE; }
	if (!n2_buffer_reserve(state, dst, N2_SCAST(size_t, wrap.decompressed_size_))) { return N2_FALSE; }
	size_t written = 0;
	if (!n2h_ulz_wdecompress_to(state, dst->data_, dst->buffer_size_, &written, src, src_size)) { return N2_FALSE; }
	dst->size_ = written;
	return N2_TRUE;
}
#endif

// zip
#if N2_CONFIG_USE_Z_LIB
static void* n2hi_mz_alloc_func(void* opaque, size_t items, size_t size)
{
	return n2_xmalloc(N2_RCAST(n2_state_t* ,opaque), items * size);
}

static void n2hi_mz_free_func(void* opaque, void* address)
{
	n2_xfree(N2_RCAST(n2_state_t*, opaque), address);
}

static void* n2hi_mz_realloc_func(void* opaque, void* address, size_t items, size_t size)
{
	return n2_xrealloc(N2_RCAST(n2_state_t*, opaque), items * size, address);
}

static void n2hi_zip_init(n2h_zip_t* zip)
{
	zip->zip_archive_ = NULL;
	zip->src_ = NULL;
	zip->src_size_ = 0;
	n2_buffer_init(&zip->own_buffer_);
}

N2_API void n2h_zip_setup(n2_state_t* state, n2h_zip_t* zip)
{
	n2hi_zip_init(zip);
	if (!zip->zip_archive_) { zip->zip_archive_ = N2_TMALLOC(mz_zip_archive, state); }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	N2_MEMSET(a, 0, sizeof(*a));
	a->m_pAlloc = n2hi_mz_alloc_func;
	a->m_pFree = n2hi_mz_free_func;
	a->m_pRealloc = n2hi_mz_realloc_func;
	a->m_pAlloc_opaque = state;
}

N2_API void n2h_zip_teardown(n2_state_t* state, n2h_zip_t* zip)
{
	if (zip->zip_archive_)
	{
		n2h_zip_close(state, zip);
		n2_free(state, zip->zip_archive_);
		zip->zip_archive_ = NULL;
	}
}

N2_API n2h_zip_t* n2h_zip_alloc(n2_state_t* state)
{
	n2h_zip_t* zip = N2_TMALLOC(n2h_zip_t, state);
	n2h_zip_setup(state, zip);
	return zip;
}

N2_API void n2h_zip_free(n2_state_t* state, n2h_zip_t* zip)
{
	n2h_zip_teardown(state, zip);
	n2_free(state, zip);
}

N2_API n2_bool_t n2h_zip_is_setup_done(const n2h_zip_t* zip)
{
	if (!zip->zip_archive_) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_is_read_mode(const n2h_zip_t* zip)
{
	if (!zip->zip_archive_) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (a->m_zip_mode != MZ_ZIP_MODE_READING) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_is_write_mode(const n2h_zip_t* zip)
{
	if (!zip->zip_archive_) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (a->m_zip_mode != MZ_ZIP_MODE_WRITING) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_close(n2_state_t* state, n2h_zip_t* zip)
{
	N2_UNUSE(state);
	if (!n2h_zip_is_setup_done(zip)) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	mz_zip_writer_finalize_archive(a);
	mz_zip_writer_end(a);
	mz_zip_reader_end(a);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_openr_to(n2_state_t* state, n2h_zip_t* zip, const void* src, size_t src_size)
{
	if (!n2h_zip_is_setup_done(zip)) { return N2_FALSE; }
	n2h_zip_close(state, zip);
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (mz_zip_reader_init_mem(a, src, src_size, 0) == MZ_FALSE) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API size_t n2h_zip_filenum(const n2h_zip_t* zip)
{
	if (!n2h_zip_is_read_mode(zip)) { return 0; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	return mz_zip_reader_get_num_files(a);
}

N2_API int n2h_zip_find(const n2h_zip_t* zip, const char* name)
{
	if (!n2h_zip_is_read_mode(zip)) { return -1; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	return mz_zip_reader_locate_file(a, name, NULL, 0);
}

N2_API n2_bool_t n2h_zip_filestat_to(const n2h_zip_t* zip, n2h_zip_filestat_t* dst, int index)
{
	if (!dst) { return N2_FALSE; }
	if (!n2h_zip_is_read_mode(zip)) { return N2_FALSE; }
	if (index < 0 || index > N2_SCAST(int, n2h_zip_filenum(zip))) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	mz_zip_archive_file_stat filestat;
	if (mz_zip_reader_file_stat(a, N2_SCAST(mz_uint, index), &filestat) == MZ_FALSE) { return N2_FALSE; }
	N2_MEMCPY(dst->filename_, filestat.m_filename, sizeof(filestat.m_filename));
	dst->fileindex_ = N2_SCAST(int, filestat.m_file_index);
	dst->is_directory_ = mz_zip_reader_is_file_a_directory(a, N2_SCAST(mz_uint, index)) == MZ_FALSE ? N2_FALSE : N2_TRUE;
	dst->comp_size_ = N2_SCAST(size_t, filestat.m_comp_size);
	dst->decomp_size_ = N2_SCAST(size_t, filestat.m_uncomp_size);
	dst->decomp_crc32_ = N2_SCAST(size_t, filestat.m_crc32);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_read_to(n2_state_t* state, const n2h_zip_t* zip, n2_buffer_t* dst, int index)
{
	if (!dst) { return N2_FALSE; }
	if (!n2h_zip_is_read_mode(zip)) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	n2h_zip_filestat_t filestat;
	if (!n2h_zip_filestat_to(zip, &filestat, index)) { return N2_FALSE; }
	if (filestat.is_directory_) { return N2_FALSE; }
	n2_buffer_reserve(state, dst, filestat.decomp_size_ + 1);
	if (mz_zip_reader_extract_to_mem_no_alloc(a, N2_SCAST(mz_uint, index), dst->data_, dst->buffer_size_, 0, NULL, 0) == MZ_FALSE) { return N2_FALSE; }
	dst->size_ = filestat.decomp_size_;
	n2_buffer_append_values_transparent(state, dst, 0, 1);
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_openw_to(n2_state_t* state, n2h_zip_t* zip)
{
	N2_UNUSE(state);
	if (!n2h_zip_is_setup_done(zip)) { return N2_FALSE; }
	n2h_zip_close(state, zip);
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (mz_zip_writer_init_heap(a, 0, 0) == MZ_FALSE) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_openwa_to(n2_state_t* state, n2h_zip_t* zip, const void* src, size_t src_size)
{
	N2_UNUSE(state);
	if (!n2h_zip_openr_to(state, zip, src, src_size)) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (mz_zip_writer_init_from_reader(a, NULL) == MZ_FALSE) { n2h_zip_close(state, zip); return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_add_to(n2_state_t* state, n2h_zip_t* zip, const char* filename, const void* src, size_t src_size, int level)
{
	N2_UNUSE(state);
	if (!n2h_zip_is_write_mode(zip)) { return N2_FALSE; }
	if (level < N2_ZIP_COMPRESS_NO_COMPRESS || level > N2_ZIP_COMPRESS_BEST) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	if (mz_zip_writer_add_mem(a, filename, src, src_size, level) == MZ_FALSE) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2h_zip_writedown_and_close(n2_state_t* state, n2h_zip_t* zip, n2_buffer_t* dst)
{
	if (!n2h_zip_is_write_mode(zip)) { return N2_FALSE; }
	mz_zip_archive* a = N2_RCAST(mz_zip_archive*, zip->zip_archive_);
	void* archbuf = NULL;
	size_t archsize = 0;
	if (mz_zip_writer_finalize_heap_archive(a, &archbuf, &archsize) == MZ_FALSE) { return N2_FALSE; }
	if (!n2_buffer_reserve(state, dst, archsize + 1)) { return N2_FALSE; }
	N2_MEMCPY(dst->data_, archbuf, archsize);
	dst->size_ = archsize;
	n2_buffer_append_values_transparent(state, dst, 0, 1);
	n2_xfree(state, archbuf);
	mz_zip_writer_end(a);
	return N2_TRUE;
}
#endif

// ファイルシステム
static void n2hi_filesystem_init(n2h_filesystem_t* fs)
{
	fs->type_ = N2H_FILESYSTEM_NULL;
	n2_str_init(&fs->name_);
	fs->priority_ = 0;
	fs->id_ = -1;
	fs->read_func_ = NULL;
	fs->write_func_ = NULL;
	fs->close_func_ = NULL;
	fs->fin_func_ = NULL;
	fs->user_ = NULL;
}

static void n2hi_filesystem_handle_init(n2h_filesystem_handle_t* dst, n2h_filesystem_t* fs, n2_bool_t is_read)
{
	dst->filesystem_ = fs;
	dst->is_read_ = is_read;
	dst->error_hint_ = NULL;
	dst->user_ = NULL;
}

N2_API void n2h_filesystem_handle_teardown(n2_state_t* state, n2h_filesystem_handle_t* handle)
{
	if (handle->is_read_)
	{
		n2h_filesystem_readhandle_t* readhandle = N2_RCAST(n2h_filesystem_readhandle_t*, handle);
		n2_buffer_teardown(state, &readhandle->data_mut_);
	}
	else
	{
		n2h_filesystem_writehandle_t* writehandle = N2_RCAST(n2h_filesystem_writehandle_t*, handle);
		N2_UNUSE(writehandle);
	}
}

N2_API void n2h_filesystem_readhandle_init(n2h_filesystem_readhandle_t* dst, n2h_filesystem_t* fs)
{
	n2hi_filesystem_handle_init(&dst->handle_, fs, N2_TRUE);
	dst->data_ = NULL;
	dst->data_size_ = 0;
	n2_buffer_init(&dst->data_mut_);
}

N2_API void n2h_filesystem_writehandle_init(n2h_filesystem_writehandle_t* dst, n2h_filesystem_t* fs)
{
	n2hi_filesystem_handle_init(&dst->handle_, fs, N2_FALSE);
	dst->written_succeeded_ = N2_FALSE;
	dst->written_size_ = 0;
}

static void n2hi_filesystemarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2h_filesystem_free(state, *N2_RCAST(n2h_filesystem_t**, element));
}

static int n2hi_filesystemarray_cmpfunc(const n2_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	const n2h_filesystem_t* lhs = *N2_RCAST(const n2h_filesystem_t**, lkey);
	const n2h_filesystem_t* rhs = *N2_RCAST(const n2h_filesystem_t**, rkey);
	if (lhs->priority_ != rhs->priority_) { return lhs->priority_ - rhs->priority_; }
	return lhs->id_ - rhs->id_;
}

N2_DEFINE_TARRAY(n2h_filesystem_t*, n2h_filesystemarray, N2_API, n2i_setupfunc_nothing, n2hi_filesystemarray_freefunc);

N2_API n2h_filesystem_t* n2h_filesystem_alloc_null(n2_state_t* state)
{
	n2h_filesystem_t* fs = N2_TMALLOC(n2h_filesystem_t, state);
	n2hi_filesystem_init(fs);
	return fs;
}

static n2h_filesystem_readhandle_t* n2hi_filesystem_read_func_system(const n2h_filesystem_readparam_t* readparam)
{
	n2h_filesystem_readhandle_t* handle = NULL;
	n2_state_t* state = N2_RCAST(n2_state_t*, readparam->filesystem_->user_);
	if (state->config_.file_read_)
	{
		handle = N2_TMALLOC(n2h_filesystem_readhandle_t, readparam->state_);
		n2h_filesystem_readhandle_init(handle, readparam->filesystem_);
		n2_bool_t succeed = N2_FALSE;

		n2_fileread_param_t fparam;
		fparam.state_ = readparam->state_;
		fparam.filepath_ = readparam->filepath_;
		fparam.binary_ = readparam->binary_;
		fparam.readsize_ = readparam->readsize_;
		fparam.readoffset_ = readparam->readoffset_;
		fparam.dst_ = &handle->data_mut_;
		succeed = state->config_.file_read_(state->config_.file_user_, &fparam);
		handle->data_ = handle->data_mut_.data_;
		handle->data_size_ = handle->data_mut_.size_;

		if (!succeed)
		{
			n2h_filesystem_close(state, N2_RCAST(n2h_filesystem_handle_t*, handle));
			handle = NULL;
		}
	}
	return handle;
}

static n2h_filesystem_writehandle_t* n2hi_filesystem_write_func_system(const n2h_filesystem_writeparam_t* writeparam)
{
	n2h_filesystem_writehandle_t* handle = N2_TMALLOC(n2h_filesystem_writehandle_t, writeparam->state_);
	n2h_filesystem_writehandle_init(handle, writeparam->filesystem_);
	n2_state_t* state = N2_RCAST(n2_state_t*, writeparam->filesystem_->user_);
	if (state->config_.file_write_)
	{
		n2_filewrite_param_t fparam;
		fparam.state_ = writeparam->state_;
		fparam.filepath_ = writeparam->filepath_;
		fparam.binary_ = writeparam->binary_;
		fparam.writedata_ = writeparam->writedata_;
		fparam.writesize_ = writeparam->writesize_;
		fparam.writeoffset_ = writeparam->writeoffset_;
		fparam.dst_writtensize_ = &handle->written_size_;
		handle->written_succeeded_ = state->config_.file_write_(state->config_.file_user_, &fparam);
	}
	return handle;
}

static void n2hi_filesystem_close_func_system(n2_state_t* state, n2h_filesystem_handle_t* handle)
{
	n2h_filesystem_handle_teardown(state, handle);
	n2_free(state, handle);
}

N2_API n2h_filesystem_t* n2h_filesystem_alloc_system(n2_state_t* state)
{
	n2h_filesystem_t* fs = N2_TMALLOC(n2h_filesystem_t, state);
	n2hi_filesystem_init(fs);
	fs->type_ = N2H_FILESYSTEM_SYSTEM;
	fs->read_func_ = n2hi_filesystem_read_func_system;
	fs->write_func_ = n2hi_filesystem_write_func_system;
	fs->close_func_ = n2hi_filesystem_close_func_system;
	fs->user_ = state;
	return fs;
}

N2_API void n2h_filesystem_free(n2_state_t* state, n2h_filesystem_t* fs)
{
	if (fs->fin_func_) { fs->fin_func_(state, fs); }
	n2_free(state, fs);
}

N2_API void n2h_filesystem_set_name(n2_state_t* state, n2h_filesystem_t* fs, const char* name, size_t name_length)
{
	n2_str_set(state, &fs->name_, name, name_length);
}

N2_API const n2_str_t* n2h_filesystem_get_name(const n2h_filesystem_t* fs)
{
	return &fs->name_;
}

N2_API void n2h_filesystem_set_priority(n2_state_t* state, n2h_filesystem_t* fs, int priority)
{
	N2_UNUSE(state);
	fs->priority_ = priority;
}

N2_API int n2h_filesystem_get_priority(const n2h_filesystem_t* fs)
{
	return fs->priority_;
}

N2_API n2h_filesystem_readhandle_t* n2h_filesystem_read(n2_state_t* state, n2h_filesystem_t* fs, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset, n2h_filesystem_read_e read)
{
	if (!fs) { return N2_FALSE; }
	if (!fs->read_func_) { return N2_FALSE; }
	n2h_filesystem_readparam_t frparam;
	frparam.state_ = state;
	frparam.filepath_ = filepath;
	frparam.binary_ = is_binary;
	frparam.readsize_ = readsize;
	frparam.readoffset_ = readoffset;
	frparam.read_ = read;
	frparam.filesystem_ = fs;
	n2h_filesystem_readhandle_t* readhandle = fs->read_func_(&frparam);
	return readhandle;
}

N2_API n2h_filesystem_writehandle_t* n2h_filesystem_write(n2_state_t* state, n2h_filesystem_t* fs, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset)
{
	if (!fs) { return N2_FALSE; }
	if (!fs->write_func_) { return N2_FALSE; }
	n2h_filesystem_writeparam_t fwparam;
	fwparam.state_ = state;
	fwparam.filepath_ = filepath;
	fwparam.binary_ = is_binary;
	fwparam.writedata_ = writedata;
	fwparam.writesize_ = writesize;
	fwparam.writeoffset_ = writeoffset;
	fwparam.filesystem_ = fs;
	n2h_filesystem_writehandle_t* writehandle = fs->write_func_(&fwparam);
	return writehandle;
}

N2_API void n2h_filesystem_close(n2_state_t* state, n2h_filesystem_handle_t* handle)
{
	if (!handle) { return; }
	if (handle->filesystem_ && handle->filesystem_->close_func_)
	{
		handle->filesystem_->close_func_(state, handle);
	}
}

N2_API n2_bool_t n2h_filesystem_load(n2_state_t* state, n2h_filesystem_t* fs, n2_buffer_t* dst, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset)
{
	n2h_filesystem_readhandle_t* readhandle = n2h_filesystem_read(state, fs, filepath, is_binary, readsize, readoffset, N2H_FILESYSTEM_READ_MUTABLE);
	if (!readhandle) { return N2_FALSE; }
	n2_buffer_swap(dst, &readhandle->data_mut_);
	n2h_filesystem_close(state, N2_RCAST(n2h_filesystem_handle_t*, readhandle));
	return N2_TRUE;
}

N2_API n2_bool_t n2h_filesystem_save(n2_state_t* state, n2h_filesystem_t* fs, size_t* dst_writtensize, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset)
{
	n2h_filesystem_writehandle_t* writehandle = n2h_filesystem_write(state, fs, filepath, is_binary, writedata, writesize, writeoffset);
	if (!writehandle) { return N2_FALSE; }
	const n2_bool_t written_succeeded = writehandle->written_succeeded_;
	if (written_succeeded && dst_writtensize) { *dst_writtensize = writehandle->written_size_; }
	n2h_filesystem_close(state, N2_RCAST(n2h_filesystem_handle_t*, writehandle));
	return written_succeeded;
}

static n2h_filesystem_readhandle_t* n2hi_filesystem_read_func_array(const n2h_filesystem_readparam_t* readparam)
{
	N2_ASSERT(readparam->filesystem_->type_ == N2H_FILESYSTEM_ARRAY);
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, readparam->filesystem_->user_);
	for (size_t i = 0, l = n2h_filesystemarray_size(context->filesystem_array_); i < l; ++i)
	{
		n2h_filesystem_t* fs = n2h_filesystemarray_peekv(context->filesystem_array_, N2_SCAST(int, i), NULL);
		if (!fs->read_func_) { continue; }
		n2h_filesystem_readparam_t elementreadparam = *readparam;
		elementreadparam.filesystem_ = fs;
		n2h_filesystem_readhandle_t* handle = fs->read_func_(&elementreadparam);
		if (handle) { return handle; }
	}
	return NULL;
}

static n2h_filesystem_writehandle_t* n2hi_filesystem_write_func_array(const n2h_filesystem_writeparam_t* writeparam)
{
	N2_ASSERT(writeparam->filesystem_->type_ == N2H_FILESYSTEM_ARRAY);
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, writeparam->filesystem_->user_);
	for (size_t i = 0, l = n2h_filesystemarray_size(context->filesystem_array_); i < l; ++i)
	{
		n2h_filesystem_t* fs = n2h_filesystemarray_peekv(context->filesystem_array_, N2_SCAST(int, i), NULL);
		if (!fs->write_func_) { continue; }
		n2h_filesystem_writeparam_t elementwriteparam = *writeparam;
		elementwriteparam.filesystem_ = fs;
		n2h_filesystem_writehandle_t* handle = fs->write_func_(&elementwriteparam);
		if (handle) { return handle; }
	}
	return NULL;
}

static void n2hi_filesystem_close_func_array(n2_state_t* state, n2h_filesystem_handle_t* handle)
{
	n2h_filesystem_handle_teardown(state, handle);
	n2_free(state, handle);
}

static void n2hi_filesystem_fin_func_array(n2_state_t* state, n2h_filesystem_t* fs)
{
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, fs->user_);
	n2h_filesystemarray_free(state, context->filesystem_array_);
	n2_free(state, context);
}

N2_API n2h_filesystem_t* n2h_filesystem_alloc_array(n2_state_t* state)
{
	n2h_filesystem_t* fs = N2_TMALLOC(n2h_filesystem_t, state);
	n2hi_filesystem_init(fs);
	fs->type_ = N2H_FILESYSTEM_ARRAY;
	fs->read_func_ = n2hi_filesystem_read_func_array;
	fs->write_func_ = n2hi_filesystem_write_func_array;
	fs->close_func_ = n2hi_filesystem_close_func_array;
	fs->fin_func_ = n2hi_filesystem_fin_func_array;
	n2h_filesystem_array_context_t* context = N2_TMALLOC(n2h_filesystem_array_context_t, state);
	context->next_id_ = 0;
	context->filesystem_array_ = n2h_filesystemarray_alloc(state, 0, 4);
	fs->user_ = context;
	return fs;
}

N2_API size_t n2h_filesystem_array_size(const n2h_filesystem_t* fs)
{
	if (!fs || fs->type_ != N2H_FILESYSTEM_ARRAY) { return 0; }
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, fs->user_);
	return n2h_filesystemarray_size(context->filesystem_array_);
}

N2_API n2h_filesystem_t* n2h_filesystem_array_at(n2h_filesystem_t* fs, int index)
{
	if (!fs || fs->type_ != N2H_FILESYSTEM_ARRAY) { return NULL; }
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, fs->user_);
	return n2h_filesystemarray_peekv(context->filesystem_array_, index, NULL);
}

N2_API void n2h_filesystem_array_priority_updated(n2h_filesystem_t* fs)
{
	if (!fs || fs->type_ != N2H_FILESYSTEM_ARRAY) { return; }
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, fs->user_);
	n2h_filesystemarray_sort(context->filesystem_array_, n2hi_filesystemarray_cmpfunc, NULL);
}

N2_API void n2h_filesystem_array_insert(n2_state_t* state, n2h_filesystem_t* fs, n2h_filesystem_t* add_fs)
{
	if (!fs || fs->type_ != N2H_FILESYSTEM_ARRAY) { return; }
	n2h_filesystem_array_context_t* context = N2_RCAST(n2h_filesystem_array_context_t*, fs->user_);
	n2h_filesystemarray_pushv(state, context->filesystem_array_, add_fs);
}

#if N2_CONFIG_USE_MSGPACK_LIB
static n2h_filesystem_readhandle_t* n2hi_filesystem_read_func_msgpack(const n2h_filesystem_readparam_t* readparam)
{
	n2h_filesystem_readhandle_t* handle = N2_TMALLOC(n2h_filesystem_readhandle_t, readparam->state_);
	n2h_filesystem_readhandle_init(handle, readparam->filesystem_);
	n2h_filesystem_msgpack_context_t* context = N2_RCAST(n2h_filesystem_msgpack_context_t*, readparam->filesystem_->user_);
	n2_bool_t succeeded = N2_FALSE;
	if (context && context->msgpack_)
	{
		n2_str_t filepath;
		n2_str_init(&filepath);
		n2_str_set(readparam->state_, &filepath, readparam->filepath_, SIZE_MAX);
		n2_path_normalize(readparam->state_, &filepath, N2_PATH_SEPARATOR_SLASH);

		const n2h_msgpack_element_t* file = n2h_msgpack_find_bystr(context->msgpack_, filepath.str_, SIZE_MAX);
		if (file)
		{
			size_t filesize = 0;
			n2h_compress_e compress = N2H_COMPRESS_NULL;
			const void* filedata = NULL;
			size_t filedatasize = 0;
			{
				const n2h_msgpack_element_t* compress_element = n2h_msgpack_find_bystr(file, "compress", SIZE_MAX);
				if (compress_element && compress_element->type_ == N2H_MSGPACK_TYPE_STRING)
				{
					compress = n2h_compress_find(compress_element->content_.strval_.str_, compress_element->content_.strval_.length_, N2H_COMPRESS_NULL);
				}
			}
			{
				const n2h_msgpack_element_t* filesize_element = n2h_msgpack_find_bystr(file, "size", SIZE_MAX);
				if (filesize_element && (filesize_element->type_ == N2H_MSGPACK_TYPE_UINT || filesize_element->type_ == N2H_MSGPACK_TYPE_INT))
				{
					filesize = filesize_element->type_ == N2H_MSGPACK_TYPE_UINT ? N2_SCAST(size_t, filesize_element->content_.uintval_) : N2_SCAST(size_t, filesize_element->content_.intval_);
				}
			}
			{
				const n2h_msgpack_element_t* filedata_element = n2h_msgpack_find_bystr(file, "bin", SIZE_MAX);
				if (filedata_element && filedata_element->type_ == N2H_MSGPACK_TYPE_BINARY)
				{
					filedata = filedata_element->content_.binval_.bin_;
					filedatasize = filedata_element->content_.binval_.length_;
				}
			}

			if (filesize > 0 && filedata && filedatasize > 0)
			{
				if (readparam->read_ == N2H_FILESYSTEM_READ_REFERENCE && compress == N2H_COMPRESS_NULL)
				{
					size_t readoffset = N2_MIN(readparam->readoffset_, filedatasize);
					size_t readsize = N2_MIN(readparam->readsize_, filedatasize - readoffset);
					handle->data_ = n2_cptr_offset(filedata, readoffset);
					handle->data_size_ = readsize;
				}
				else
				{
					switch (compress)
					{
					case N2H_COMPRESS_NULL:
						n2_buffer_set(readparam->state_, &handle->data_mut_, filedata, filedatasize);
						break;
					case N2H_COMPRESS_Z:
#if N2_CONFIG_USE_Z_LIB
						if (!n2h_z_decompress(readparam->state_, &handle->data_mut_, filedata, filedatasize))
						{
							n2_buffer_teardown(readparam->state_, &handle->data_mut_);
						}
#endif
						break;
					case N2H_COMPRESS_ULZ:
#if N2_CONFIG_USE_ULZ_LIB
						if (!n2h_ulz_wdecompress(readparam->state_, &handle->data_mut_, filedata, filedatasize))
						{
							n2_buffer_teardown(readparam->state_, &handle->data_mut_);
						}
#endif
						break;
					default:
						n2_buffer_set(readparam->state_, &handle->data_mut_, filedata, filedatasize);
						break;
					}

					size_t readoffset = N2_MIN(readparam->readoffset_, handle->data_mut_.size_);
					size_t readsize = N2_MIN(readparam->readsize_, handle->data_mut_.size_ - readoffset);
					if (readoffset > 0) { n2_buffer_erase(&handle->data_mut_, 0, readoffset); }
					N2_ASSERT(handle->data_mut_.size_ >= readsize);// check cap
					handle->data_mut_.size_ = readsize;
					n2_buffer_append_values_transparent(readparam->state_, &handle->data_mut_, 0, 4);// trailing zeros

					if (!readparam->binary_)
					{
						// make crlf -> lf
						n2_buffer_replace_pattern(readparam->state_, &handle->data_mut_, "\r", 1, "", 0);
					}

					handle->data_ = handle->data_mut_.data_;
					handle->data_size_ = handle->data_mut_.size_;
				}

				succeeded = N2_TRUE;
			}
		}
		n2_str_teardown(readparam->state_, &filepath);
	}
	if (!succeeded)
	{
		n2h_filesystem_close(readparam->state_, N2_RCAST(n2h_filesystem_handle_t*, handle));
		handle = NULL;
	}
	return handle;
}

static void n2hi_filesystem_close_func_msgpack(n2_state_t* state, n2h_filesystem_handle_t* handle)
{
	n2h_filesystem_handle_teardown(state, handle);
	n2_free(state, handle);
}

N2_API n2h_filesystem_t* n2h_filesystem_alloc_msgpack(n2_state_t* state, const n2h_msgpack_element_t* msgpack)
{
	// 検証
	if (!msgpack || msgpack->type_ != N2H_MSGPACK_TYPE_MAP) { return NULL; }

	// 生成
	n2h_filesystem_t* fs = N2_TMALLOC(n2h_filesystem_t, state);
	n2hi_filesystem_init(fs);
	fs->type_ = N2H_FILESYSTEM_MSGPACK;
	fs->read_func_ = n2hi_filesystem_read_func_msgpack;
	fs->close_func_ = n2hi_filesystem_close_func_msgpack;
	n2h_filesystem_msgpack_context_t* context = N2_TMALLOC(n2h_filesystem_msgpack_context_t, state);
	context->msgpack_ = msgpack;
	fs->user_ = context;
	return fs;
}
#endif

// ネットワーク
#if N2_CONFIG_USE_NET_SOCKET_LIB
static n2_bool_t n2hi_socketsys_is_initialized = N2_FALSE;
static size_t n2hi_socketsys_open_channels = 0;

static n2_bool_t n2hi_socketsys_init()
{
	if (!n2hi_socketsys_is_initialized)
	{
		if (!zed_net_init()) { return N2_FALSE; }
		n2hi_socketsys_is_initialized = N2_TRUE;
	}
	return N2_TRUE;
}
static void n2hi_socketsys_teardown()
{
	if (!n2hi_socketsys_is_initialized) { return; }
	zed_net_shutdown();
	n2hi_socketsys_is_initialized = N2_FALSE;
}

static void n2hi_socket_init(n2h_socket_t* socket)
{
	socket->port_ = 0;
	socket->socket_ = NULL;
	n2_str_init(&socket->host_);
	n2_str_init(&socket->service_);
}

static void n2hi_socket_teardown(n2_state_t* state, n2h_socket_t* socket)
{
	zed_net_socket_t* nsocket = N2_RCAST(zed_net_socket_t*, socket->socket_);
	if (nsocket)
	{
		zed_net_socket_close(nsocket);
		n2_free(state, nsocket);
	}

	socket->port_ = 0;
	socket->socket_ = NULL;
	n2_str_teardown(state, &socket->host_);
	n2_str_teardown(state, &socket->service_);

	if (nsocket && --n2hi_socketsys_open_channels == 0)
	{
		n2hi_socketsys_teardown();
	}
}

N2_API n2h_socket_t* n2h_socket_server_alloc(n2_state_t* state, int port)
{
	if (port <= 0) { return NULL; }

	n2h_socket_t* socket = N2_TMALLOC(n2h_socket_t, state);
	if (!socket) { return NULL; }
	n2hi_socket_init(socket);

	zed_net_socket_t* nsocket = N2_TMALLOC(zed_net_socket_t, state);
	if (!nsocket) { n2_free(state, socket); return NULL; }

	socket->port_ = port;

	if (!n2hi_socketsys_init()) { return NULL; }
	if (!zed_net_tcp_socket_open(nsocket, N2_SCAST(unsigned int, socket->port_), 0, 1)) { n2_free(state, nsocket); n2h_socket_free(state, socket); return NULL; }

	socket->socket_ = nsocket;
	++n2hi_socketsys_open_channels;
	return socket;
}
N2_API void n2h_socket_free(n2_state_t* state, n2h_socket_t* socket)
{
	n2hi_socket_teardown(state, socket);
	n2_free(state, socket);
}
#endif

// 組み込み用リソース
static n2_buffer_t n2hi_resource_load_bin(n2_state_t* state, const void* src, size_t src_size, uint64_t scratch_key, size_t dst_size)
{
	n2_buffer_t cmpbuf;
	n2_buffer_init(&cmpbuf);
	n2_buffer_append(state, &cmpbuf, src, src_size);
	n2h_random_scratch(cmpbuf.data_, cmpbuf.size_, scratch_key);
	n2_buffer_t resbuf;
	n2_buffer_init(&resbuf);
#if N2_CONFIG_USE_Z_LIB
	n2_buffer_reserve(state, &resbuf, dst_size);
	size_t written_size = 0;
	if (!n2h_z_decompress_to(state, resbuf.data_, resbuf.buffer_size_, &written_size, cmpbuf.data_, cmpbuf.size_) || written_size != dst_size)
	{
		n2_buffer_teardown(state, &resbuf);
	}
	else
	{
		resbuf.size_ = written_size;
	}
#else
	N2_UNUSE(state);
	N2_UNUSE(src);
	N2_UNUSE(src_size);
	N2_UNUSE(scratch_key);
	N2_UNUSE(dst_size);
#endif
	n2_buffer_teardown(state, &cmpbuf);
	return resbuf;
}

static n2_buffer_t n2hi_resource_load_str(n2_state_t* state, const char* src, size_t src_size, uint64_t scratch_key, size_t cmp_size, size_t dst_size)
{
	n2_buffer_t cmpbuf;
	n2_buffer_init(&cmpbuf);
	n2_buffer_t resbuf;
	n2_buffer_init(&resbuf);
	if (n2h_base85_decode_to(state, &cmpbuf, src, src_size) && cmpbuf.size_ >= src_size)
	{
		resbuf = n2hi_resource_load_bin(state, cmpbuf.data_, cmp_size, scratch_key, dst_size);
	}
	n2_buffer_teardown(state, &cmpbuf);
	return resbuf;
}

//=============================================================================
// 特殊
static void n2i_errorinfo_append(n2_state_t* state, n2_str_t* str, const char* package,  const char* line_head, int line)
{
	n2_str_append_fmt(state, str, "@@ (%s:%d)", package ? package : "-", line + N2_LINE_BASE);
	if (line_head) { n2_str_append(state, str, " << ", SIZE_MAX); n2i_str_cutoff_append(state, str, line_head, 64, '\n', "..."); }
}

static void n2i_vraise_as(n2_state_t* state, n2_error_e e, const n2_sourcecode_t* sourcecode, const char* package, const char* line_head, int line, const char* fmt, va_list args)
{
	n2_str_t tstr; n2_str_init(&tstr); n2_str_vfmt_to(state, &tstr, fmt, args);
	n2_str_t tmstr; n2_str_init(&tmstr); n2_str_copy_to(state, &tmstr, &tstr);
	n2i_errorinfo_append(state, &tmstr, package, line_head, line);
	n2i_do_error(state, e, sourcecode, tstr.str_, tmstr.str_, line, NULL, NULL);
	n2_str_teardown(state, &tstr); n2_str_teardown(state, &tmstr);
}

static void n2i_raise_as(n2_state_t* state, n2_error_e e, const n2_sourcecode_t* sourcecode, const char* package, const char* line_head, int line, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	n2i_vraise_as(state, e, sourcecode, package, line_head, line, fmt, args);
	va_end(args);
}

static const n2_codeline_t* n2i_codelinetable_find_from_pc(const n2_codelinetable_t* codelinetable, n2_pc_t pc);

static void n2i_vraise_fiber_exception(n2_state_t* state, n2_fiber_t* f, n2_error_e e, const char* fmt, va_list args)
{
	// AST評価時はエラー文字列だけだす
	if (f->ast_evaluate_context_)
	{
		n2_str_vfmt_to(state, &f->ast_evaluate_context_->error_, fmt, args);
		goto protected_exit;
	}

	// そうでない時の対処
	n2_str_t tstr;
	n2_str_init(&tstr);

	const n2_codelinetable_t* codelines = f && f->environment_ && f->environment_->codeimage_ && f->environment_->codeimage_->codelinetable_ ? f->environment_->codeimage_->codelinetable_ : NULL;

	n2_str_t subdescstr;
	n2_str_init(&subdescstr);
	if (state->config_.error_is_print_ && state->config_.error_print_callstack_)
	{
		if (n2_callframearray_size(f->callframes_) > 0)
		{
			n2_str_append(state, &subdescstr, "コールスタック：\n", SIZE_MAX);
			for (size_t i = 0, l = n2_callframearray_size(f->callframes_); i < l; ++i)
			{
				const n2_callframe_t* cf = n2_callframearray_peek(f->callframes_, N2_SCAST(int, i));
				N2_ASSERT(cf);
				const n2_codeline_t* codeline = NULL;
				if (i > 0) { n2_str_append_fmt(state, &subdescstr, "\n"); }
				n2_str_append_fmt(state, &subdescstr, "  ");
				if (codelines)
				{
					if (cf->caller_pc_ >= 0)
					{
						codeline = n2i_codelinetable_find_from_pc(codelines, cf->caller_pc_);
						if (codeline && codeline->line_head_)
						{
							n2_str_clear(&tstr);
							n2i_str_cutoff_append(state, &tstr, codeline->line_head_, 64, '\n', "...");
							n2_str_append_fmt(state, &subdescstr, "(%s:%d) %s", codeline->package_, codeline->line_, tstr.str_);
						}
						else
						{
							n2_str_append_fmt(state, &subdescstr, "(unresolved...)");
						}
					}
					else
					{
						n2_str_append_fmt(state, &subdescstr, "(out of script : such as builtin functions...)");
					}
				}
				else
				{
					n2_str_append_fmt(state, &subdescstr, "(unresolved...)");
				}
			}
		}
	}

	n2_str_t rawmessagestr;
	n2_str_init(&rawmessagestr);
	n2_str_vfmt_to(state, &rawmessagestr, fmt, args);

	const n2_sourcecode_t* sourcecode = NULL;
	const char* package = NULL;
	const char* line_head = NULL;
	int line = -1;
	if (codelines && f->op_pc_ >= 0)
	{
		const n2_codeline_t* codeline = n2i_codelinetable_find_from_pc(codelines, f->op_pc_);
		if (codeline)
		{
			sourcecode = codeline->sourcecode_;
			package = codeline->package_;
			line_head = codeline->line_head_;
			line = codeline->line_;
		}
	}
	else if (f->op_pc_ < 0)
	{
		package = "(out of script)";
	}

	n2_str_t messagestr;
	n2_str_init(&messagestr);
	n2_str_copy_to(state, &messagestr, &rawmessagestr);
	n2i_errorinfo_append(state, &messagestr, package, line_head, line);

	n2i_do_error(state, e, sourcecode, rawmessagestr.str_, messagestr.str_, line, subdescstr.str_, f);

#if N2_CONFIG_USE_DEBUGGING
	// デバッガー
	if (f)
	{
		n2_debughook_t* debughook = n2_environment_get_debughook(f->environment_);
		if (debughook && debughook->errorstopfunc_)
		{
			n2_error_param_t error_param;
			n2_error_param_init(&error_param);
			error_param.state_ = state;
			error_param.error_ = e;
			error_param.sourcecode_ = sourcecode;
			error_param.package_ = package;
			error_param.raw_message_ = rawmessagestr.str_;
			error_param.message_ = messagestr.str_;
			error_param.subdescription_ = subdescstr.str_;
			error_param.line_ = line;
			error_param.column_ = 0;
			error_param.fiber_ = f;
			debughook->errorstopfunc_(state, debughook, &error_param);
		}
	}
#endif

	n2_str_teardown(state, &subdescstr);
	n2_str_teardown(state, &messagestr);
	n2_str_teardown(state, &rawmessagestr);
	n2_str_teardown(state, &tstr);

protected_exit:
	if (f->protectframe_) { longjmp(f->protectframe_->jmp_, 1); }

	// @todo まだ想定してない
	N2_ASSERT(0);

	// ここまで来たら基本abort()しかない
	if (state->config_.abort_on_unprotected_error_)
	{
		abort();
	}

	// 危険なリターン
	return;
}

static void n2i_raise_fiber_exception(n2_state_t* state, n2_fiber_t* f, n2_error_e e, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	n2i_vraise_fiber_exception(state, f, e, fmt, args);
	va_end(args);
}

//=============================================================================
// 論理ソースコード

// n2_sourcecode_tじゃないけど似たようなものなので
static n2_bool_t n2i_sourcecode_autoencode_src(n2_state_t* state, n2_str_t* script)
{
	n2_bool_t is_valid_encoding = N2_FALSE;

	// UTF8？
	if (!is_valid_encoding)
	{
		if (n2_str_trim_utf8_bom(script)) { is_valid_encoding = N2_TRUE; }
		else
		{
			const int utf8_invalid_pos = n2_encoding_utf8_verify(script->str_, script->size_);
			if (utf8_invalid_pos < 0) { is_valid_encoding = N2_TRUE; }
		}
	}

	// UTF16LE？
	if (!is_valid_encoding && state->config_.enable_script_auto_decode_utf16_)
	{
		n2_bool_t accepted = N2_FALSE;
		if (n2_str_trim_utf16le_bom(script))
		{
			accepted = N2_TRUE;
		}
		else
		{
			const int utf16le_invalid_pos = n2_encoding_utf16le_verify(script->str_, script->size_);
			if (utf16le_invalid_pos < 0) { accepted = N2_TRUE; }
		}
		if (accepted)
		{
			is_valid_encoding = N2_TRUE;
			n2_str_t cnvscriptstr;
			n2_str_init(&cnvscriptstr);
			n2_str_reserve(state, &cnvscriptstr, script->buffer_size_);
			n2_encoding_utf16le_convert_to_utf8(state, &cnvscriptstr, script->str_, script->size_, '?');
			n2_str_swap(script, &cnvscriptstr);
			n2_str_teardown(state, &cnvscriptstr);
		}
	}

	// UTF16BE？
	if (!is_valid_encoding && state->config_.enable_script_auto_decode_utf16_)
	{
		n2_bool_t accepted = N2_FALSE;
		if (n2_str_trim_utf16be_bom(script))
		{
			accepted = N2_TRUE;
		}
		else
		{
			const int utf16be_invalid_pos = n2_encoding_utf16be_verify(script->str_, script->size_);
			if (utf16be_invalid_pos < 0) { accepted = N2_TRUE; }
		}
		if (accepted)
		{
			is_valid_encoding = N2_TRUE;
			n2_str_t cnvscriptstr;
			n2_str_init(&cnvscriptstr);
			n2_str_reserve(state, &cnvscriptstr, script->buffer_size_);
			n2_encoding_utf16be_convert_to_utf8(state, &cnvscriptstr, script->str_, script->size_, '?');
			n2_str_swap(script, &cnvscriptstr);
			n2_str_teardown(state, &cnvscriptstr);
		}
	}

#if N2_CONFIG_USE_ENCODING_CP932
	// cp932？
	if (!is_valid_encoding && state->config_.enable_script_auto_decode_cp932_)
	{
		const int cp932_invalid_pos = n2_encoding_cp932_verify(script->str_, script->size_);
		if (cp932_invalid_pos < 0)
		{
			is_valid_encoding = N2_TRUE;
			n2_str_t cnvscriptstr;
			n2_str_init(&cnvscriptstr);
			n2_str_reserve(state, &cnvscriptstr, script->buffer_size_);
			n2_encoding_cp932_convert_to_utf8(state, &cnvscriptstr, script->str_, script->size_, '?');
			n2_str_swap(script, &cnvscriptstr);
			n2_str_teardown(state, &cnvscriptstr);
		}
	}
#endif

	return is_valid_encoding;
}

static int n2i_sourcefilearray_matchfunc(const n2_array_t* a, const void* element, const void* key)
{
	N2_UNUSE(a);
	n2_sourcefile_t* sourcefile = *N2_RCAST(n2_sourcefile_t**, element);
	const n2_str_t* skey = N2_RCAST(const n2_str_t*, key);
	return n2_str_compare(&sourcefile->src_resolved_filepath_, skey);
}
static void n2i_sourcefilearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_sourcefile_t* sourcefile = *N2_RCAST(n2_sourcefile_t**, element);
	n2_sourcefile_free(state, sourcefile);
}
N2_DEFINE_TARRAY(n2_sourcefile_t*, n2_sourcefilearray, N2_API, n2i_setupfunc_nothing, n2i_sourcefilearray_freefunc);

static void n2i_sourcefile_setup(n2_state_t* state, n2_sourcefile_t* sourcefile)
{
	sourcefile->id_ = -1;
	n2_str_init(&sourcefile->src_resolved_filepath_);
	n2_str_init(&sourcefile->src_resolved_filepath_escaped_);
	n2_sourcecodeptrarray_setup(state, &sourcefile->sourcecodeptrs_, 0, 4);
}

static void n2i_sourcefile_teardown(n2_state_t* state, n2_sourcefile_t* sourcefile)
{
	n2_str_teardown(state, &sourcefile->src_resolved_filepath_);
	n2_str_teardown(state, &sourcefile->src_resolved_filepath_escaped_);
	n2_sourcecodeptrarray_teardown(state, &sourcefile->sourcecodeptrs_);
}

N2_API n2_sourcefile_t* n2_sourcefile_alloc(n2_state_t* state)
{
	n2_sourcefile_t* sourcefile = N2_TMALLOC(n2_sourcefile_t, state);
	n2i_sourcefile_setup(state, sourcefile);
	return sourcefile;
}

N2_API void n2_sourcefile_free(n2_state_t* state, n2_sourcefile_t* sourcefile)
{
	n2i_sourcefile_teardown(state, sourcefile);
	n2_free(state, sourcefile);
}

N2_API n2_sourcefile_t* n2_sourcefilearray_register_sourcecode(n2_state_t* state, n2_sourcefilearray_t* sourcefiles, n2_sourcecode_t* sourcecode)
{
	if (!sourcefiles) { return NULL; }
	if (sourcecode->sourcefile_) { return sourcecode->sourcefile_; }
	// 解決済みパス
	n2_str_t resolved_filepath;
	n2_str_init(&resolved_filepath);
	n2_str_copy_to(state, &resolved_filepath, &sourcecode->src_loaded_filepath_);
	n2_path_normalize(state, &resolved_filepath, N2_PATH_SEPARATOR_NATIVE);
	// 検索
	const int index = n2_sourcefilearray_find(sourcefiles, n2i_sourcefilearray_matchfunc, &resolved_filepath);
	n2_sourcefile_t* sourcefile = NULL;
	if (index < 0)
	{
		// 新規作成
		sourcefile = n2_sourcefile_alloc(state);
		sourcefile->id_ = N2_SCAST(int, n2_sourcefilearray_size(sourcefiles));
		n2_str_copy_to(state, &sourcefile->src_resolved_filepath_, &resolved_filepath);
		n2_str_escaped_to(state, &sourcefile->src_resolved_filepath_escaped_, sourcefile->src_resolved_filepath_.str_, sourcefile->src_resolved_filepath_.size_, N2_STR_ESCAPE_FLAG_JSON);
		n2_sourcefilearray_pushv(state, sourcefiles, sourcefile);
	}
	else
	{
		// 既存
		sourcefile = n2_sourcefilearray_peekv(sourcefiles, index, NULL);
		N2_ASSERT(sourcefile);
	}
	// に追加
	n2_sourcecodeptrarray_pushv(state, &sourcefile->sourcecodeptrs_, sourcecode);
	// 逆参照
	sourcecode->sourcefile_ = sourcefile;
	// 解決済みパスは使わない
	n2_str_teardown(state, &resolved_filepath);
	return sourcefile;
}

static void n2i_sourcecode_setup(n2_state_t* state, n2_sourcecode_t* sourcecode)
{
	n2_str_init(&sourcecode->package_);
	n2_str_init(&sourcecode->src_filepath_);
	n2_str_init(&sourcecode->src_filename_);
	n2_str_init(&sourcecode->src_loaded_filepath_);
	n2_str_init(&sourcecode->searchpath_);
	n2_str_init(&sourcecode->src_script_);
	n2_cstrarray_setup(state, &sourcecode->script_lines_, 0, 16);
	n2_str_init(&sourcecode->src_ppscript_);
	n2_cstrarray_setup(state, &sourcecode->ppscript_lines_, 0, 16);
	n2_szarray_setup(state, &sourcecode->codeline_indices_, 0, 256);
	sourcecode->sourcecodes_ = n2_sourcecodearray_alloc(state, 0, 4);
	sourcecode->parent_sourcecode_ = NULL;
	sourcecode->parent_line_ = -1;
	sourcecode->sourcefile_ = NULL;
}

static void n2i_sourcecode_teardown(n2_state_t* state, n2_sourcecode_t* sourcecode)
{
	if (sourcecode->sourcecodes_)
	{
		n2_sourcecodearray_free(state, sourcecode->sourcecodes_);
		sourcecode->sourcecodes_ = NULL;
	}
	n2_szarray_teardown(state, &sourcecode->codeline_indices_);
	n2_cstrarray_teardown(state, &sourcecode->script_lines_);
	n2_cstrarray_teardown(state, &sourcecode->ppscript_lines_);
	n2_str_teardown(state, &sourcecode->package_);
	n2_str_teardown(state, &sourcecode->src_filepath_);
	n2_str_teardown(state, &sourcecode->src_filename_);
	n2_str_teardown(state, &sourcecode->src_loaded_filepath_);
	n2_str_teardown(state, &sourcecode->searchpath_);
	n2_str_teardown(state, &sourcecode->src_script_);
	n2_str_teardown(state, &sourcecode->src_ppscript_);
}

N2_API n2_sourcecode_t* n2_sourcecode_alloc(n2_state_t* state)
{
	n2_sourcecode_t* sourcecode = N2_TMALLOC(n2_sourcecode_t, state);
	n2i_sourcecode_setup(state, sourcecode);
	return sourcecode;
}

N2_API void n2_sourcecode_free(n2_state_t* state, n2_sourcecode_t* sourcecode)
{
	n2i_sourcecode_teardown(state, sourcecode);
	n2_free(state, sourcecode);
}

static void n2i_sourcecode_split_lines(n2_state_t* state, const n2_str_t* script, n2_cstrarray_t* lines)
{
	n2_cstrarray_clear(state, lines);
	n2_bool_t prev_linebreak = N2_TRUE;
	for (size_t i = 0; i < script->size_; ++i)
	{
		if (prev_linebreak)
		{
			n2_cstrarray_pushv(state, lines, script->str_ + i);
			prev_linebreak = N2_FALSE;
		}
		if (script->str_[i] == '\n') { prev_linebreak = N2_TRUE; }
	}
}

N2_API n2_bool_t n2_sourcecode_split_script_lines(n2_state_t* state, n2_sourcecode_t* sourcecode)
{
	n2i_sourcecode_split_lines(state, &sourcecode->src_script_, &sourcecode->script_lines_);
	return N2_TRUE;
}

N2_API n2_bool_t n2_sourcecode_split_ppscript_lines(n2_state_t* state, n2_sourcecode_t* sourcecode)
{
	n2i_sourcecode_split_lines(state, &sourcecode->src_ppscript_, &sourcecode->ppscript_lines_);
	return N2_TRUE;
}

static void n2i_sourcecodearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_sourcecode_t* sourcecode = *N2_RCAST(n2_sourcecode_t**, element);
	n2_sourcecode_free(state, sourcecode);
}
N2_DEFINE_TARRAY(n2_sourcecode_t*, n2_sourcecodearray, N2_API, n2i_setupfunc_nothing, n2i_sourcecodearray_freefunc);

N2_DEFINE_TARRAY(n2_sourcecode_t*, n2_sourcecodeptrarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

//=============================================================================
// キーワード
N2_API n2_keyword_e n2_keyword_find(const char* s)
{
	static const struct
	{
		n2_keyword_e keyword_;
		const char* word_;
	} table[] =
	{
		{N2_KEYWORD_GLOBAL,		"global"},
		{N2_KEYWORD_LOCAL,		"local"},
		{N2_KEYWORD_CTYPE,		"ctype"},
		{N2_KEYWORD_END,		"end"},
		{N2_KEYWORD_RETURN,		"return"},
		{N2_KEYWORD_GOTO,		"goto"},
		{N2_KEYWORD_GOSUB,		"gosub"},
		{N2_KEYWORD_REPEAT,		"repeat"},
		{N2_KEYWORD_FOREACH,	"foreach"},
		{N2_KEYWORD_LOOP,		"loop"},
		{N2_KEYWORD_CONTINUE,	"continue"},
		{N2_KEYWORD_BREAK,		"break"},
		{N2_KEYWORD_IF,			"if"},
		{N2_KEYWORD_ELSE,		"else"},
		{N2_KEYWORD_THEN,		"then"},
		{N2_KEYWORD_SWITCH,		"switch"},
		{N2_KEYWORD_CASE,		"case"},
		{N2_KEYWORD_DEFAULT,	"default"},
		{N2_KEYWORD_SWBREAK,	"swbreak"},
		{N2_KEYWORD_SWEND,		"swend"},
		{N2_KEYWORD_INT,		"int"},
		{N2_KEYWORD_DOUBLE,		"double"},
		{N2_KEYWORD_STR,		"str"},
		{N2_KEYWORD_LABEL,		"label"},
		{N2_KEYWORD_VAR,		"var"},
		{N2_KEYWORD_ARRAY,		"array"},
		{N2_KEYWORD_MODVAR,		"modvar"},
		{N2_KEYWORD_THISMOD,	"thismod"},
		{N2_KEYWORD_UNDEF,		NULL}
	};

	// 全探索
	for (size_t i = 0; table[i].word_; ++i)
	{
		if (N2_STRCMP(s, table[i].word_) == 0)
		{
			return table[i].keyword_;
		}
	}
	return N2_KEYWORD_UNDEF;
}

//=============================================================================
// トークナイザ
static n2_bool_t n2i_token_is_keyword(const n2_token_t* token, n2_keyword_e keyword)
{
	return token->token_ == N2_TOKEN_IDENTIFIER && n2_keyword_find(token->content_) == keyword;
}

N2_API n2_bool_t n2_token_is_eos_like(n2_token_e tag)
{
	return tag == N2_TOKEN_EOF ||
		tag == N2_TOKEN_EOL ||
		tag == N2_TOKEN_EOS ||
		tag == N2_TOKEN_RBRACE;
}

N2_API n2_token_e n2_token_shadow_find(const char* ident, size_t len)
{
	static const struct
	{
		n2_token_e token_;
		const char* word_;
		size_t word_len_;
	}
	shadows[] =
	{
		{N2_TOKEN_NIL,			"nil",		3},
		{N2_TOKEN_OP_NEQ,		"not",		3},
		{N2_TOKEN_OP_BAND,		"and",		3},
		{N2_TOKEN_OP_BOR,		"or",		2},
		{N2_TOKEN_OP_BXOR,		"xor",		3},
		{N2_TOKEN_UNKNOWN,		NULL,		0}
	};

	for (size_t i = 0; shadows[i].word_; ++i)
	{
		if (shadows[i].word_len_ == len && N2_STRNCMP(shadows[i].word_, ident, len) == 0)
		{
			return shadows[i].token_;
		}
	}
	return N2_TOKEN_UNKNOWN;
}

N2_API n2_source_order_e n2_source_order_find(const char* s)
{
	static const struct
	{
		n2_source_order_e order_;
		const char* word_;
	}
	orders[] =
	{
		{N2_SOURCE_ORDER_INCLUDE_PUSH,	"include_push"},
		{N2_SOURCE_ORDER_INCLUDE_POP,	"include_pop"},
		{N2_SOURCE_ORDER_UNKNOWN,		NULL}
	};

	for (size_t i = 0; orders[i].word_; ++i)
	{
		if (N2_STRCMP(orders[i].word_, s) == 0)
		{
			return orders[i].order_;
		}
	}
	return N2_SOURCE_ORDER_UNKNOWN;
}

static void n2i_tokenize_context_init(n2_tokenize_context_t* c)
{
	c->sourcecode_ = NULL;
	c->package_ = NULL;
	c->script_ = NULL;
	c->cursor_ = 0;
	c->line_ = 0;
	c->line_head_ = NULL;
}

N2_API void n2_tokenize_context_init(n2_state_t* state, n2_tokenize_context_t* c, n2_sourcecode_t* sourcecode)
{
	N2_UNUSE(state);
	n2i_tokenize_context_init(c);
	c->sourcecode_ = sourcecode;
	c->package_ = sourcecode->package_.str_;
	c->script_ = sourcecode->src_ppscript_.str_;
	c->template_str_depth_ = 0;
	for (size_t i = 0; i < N2_MAX_TEMPLATE_STRING_DEPTH; ++i)
	{
		c->template_str_levels_[i] = 0;
		c->template_str_token_[i] = NULL;
	}
	c->line_head_ = c->script_;
}

N2_API void n2_tokenize_context_init_raw(n2_state_t* state, n2_tokenize_context_t* c, const char* package, const char* script)
{
	N2_UNUSE(state);
	n2i_tokenize_context_init(c);
	c->package_ = package;
	c->script_ = script;
	c->line_head_ = c->script_;
}

N2_API void n2_tokenize_context_fin(n2_state_t* state, n2_tokenize_context_t* c)
{
	N2_UNUSE(state);
	c->package_ = NULL;
	c->script_ = NULL;
	c->template_str_depth_ = 0;
	c->cursor_ = 0;
	c->line_ = 0;
	c->line_head_ = NULL;
}

#define N2I_TK_RAISE(state, fmt, ...) \
	n2i_raise_as(state, N2_ERROR_TOKENIZE, c->sourcecode_, c->package_, c->line_head_, c->line_, fmt, ## __VA_ARGS__)

#define N2I_TK_NEXT_LINE() \
	do { \
		++c->line_; \
		c->line_head_ = p; \
	} while(0)

enum
{
	N2I_TK_STR_SINGLE,
	N2I_TK_STR_DOUBLE,
	N2I_TK_STR_TEMPLATE,
	N2I_TK_STR_TEMPLATE_CONTINUE,
	N2I_TK_STR_MULTI
};

static n2_bool_t n2i_tokenize_context_next_string(n2_state_t* state, n2_token_t* token, n2_tokenize_context_t* c, const char** pp, int tkstr)
{
	n2_bool_t res = N2_TRUE;
	const char* p = *pp;

	char beginchar = '\0';
	switch (tkstr)
	{
	case N2I_TK_STR_SINGLE:					beginchar = '\''; ++p; break;
	case N2I_TK_STR_DOUBLE:					beginchar = '\"'; ++p; break;
	case N2I_TK_STR_TEMPLATE:				beginchar = '`'; ++p; break;
	case N2I_TK_STR_TEMPLATE_CONTINUE:		beginchar = '`'; break;
	case N2I_TK_STR_MULTI:					p += 2; break;
	default:								N2_ASSERT(0); break;
	}

	n2_bool_t has_template = N2_FALSE;
	const char* s = p;
	for (;;)
	{
		if (p[0] == '\0')
		{
			N2I_TK_RAISE(state, "文字列の読み取り中にEOFが検出されました。");
			res = N2_FALSE;
			goto to_exit;
		}
		if (p[0] == '\n')
		{
			if (tkstr != N2I_TK_STR_TEMPLATE && tkstr != N2I_TK_STR_TEMPLATE_CONTINUE && tkstr != N2I_TK_STR_MULTI)
			{
				N2I_TK_RAISE(state, "文字列の読み取り中に行末が検出されました。文字列が閉じられていません");
				res = N2_FALSE;
				goto to_exit;
			}
			++p;
			N2I_TK_NEXT_LINE();
			continue;
		}
		if ((tkstr == N2I_TK_STR_TEMPLATE || tkstr == N2I_TK_STR_TEMPLATE_CONTINUE) && p[0] == '$' && p[1] == '{')
		{
			if (c->template_str_depth_ >= N2_MAX_TEMPLATE_STRING_DEPTH)
			{
				N2I_TK_RAISE(state, "テンプレート文字列のネストレベルが最大（%d）を超えました。", N2_MAX_TEMPLATE_STRING_DEPTH);
				res = N2_FALSE;
				goto to_exit;
			}
			c->template_str_levels_[c->template_str_depth_] = 1;
			c->template_str_token_[c->template_str_depth_] = token;
			++c->template_str_depth_;
			has_template = N2_TRUE;
			break;
		}
		if (tkstr == N2I_TK_STR_MULTI ? (p[0] == '\"' && p[1] == '}') : p[0] == beginchar) { break; }
		if (p[0] == '\\' && p[1] != '\0') { ++p; }
		++p;
	}

	const char* e = p;
	n2_str_t tstr; n2_str_init(&tstr);
	if (!n2_str_unescaped_to(state, &tstr, s, N2_SCAST(size_t, e - s)))
	{
		N2I_TK_RAISE(state, "文字列中に解決できないエスケープシーケンスを発見しました");
		n2_str_teardown(state, &tstr);
		return N2_FALSE;
	}
	token->content_ = n2_plstr_clone(state, tstr.str_);
	token->token_ = tkstr == N2I_TK_STR_SINGLE ? N2_TOKEN_CHAR : has_template ? N2_TOKEN_TEMPLATE_STRING : N2_TOKEN_STRING;
	n2_str_teardown(state, &tstr);

	if (token->token_ == N2_TOKEN_CHAR)
	{
		const char* cpe = n2_encoding_utf8_fetch(token->content_, NULL);
		if (*cpe != '\0')
		{
			N2I_TK_RAISE(state, "文字リテラルに複数のコードポイントが含まれています");
			res = N2_FALSE;
			goto to_exit;
		}
	}

	++p;
	if (tkstr == N2I_TK_STR_MULTI) { ++p; }
	if (has_template) { ++p; }

to_exit:
	*pp = p;
	return res;
}

N2_API n2_bool_t n2_tokenize_context_next(n2_state_t* state, n2_token_t* to, n2_tokenize_context_t* c)
{
	n2_token_t* token = to;
	N2_ASSERT(token);

	token->token_ = N2_TOKEN_UNKNOWN;
	token->sourcecode_ = c->sourcecode_;
	token->package_ = c->package_;
	token->content_ = NULL;
	token->cursor_begin_ = token->cursor_end_ = c->cursor_;
	token->left_space_ = N2_FALSE;
	token->right_space_ =N2_FALSE;

	const char* pp = c->script_ + c->cursor_;
	const char* p = c->script_ + c->cursor_;

	const char* prev_p;
	int prev_cursor;

restart:
	prev_p = p;
	prev_cursor = N2_SCAST(int, p - c->script_);

	token->appear_line_head_ = c->line_head_;
	token->appear_line_ = c->line_;
	switch (p[0])
	{
		// EOF
	case '\0':
		token->token_ = N2_TOKEN_EOF;
		break;

		// 行終わり（無視）
	case '\r':
	case '\f':
		++p;
		goto restart;

		// 行終わり
	case '\n':
		// この位置はマーキング
		++p;
		N2I_TK_NEXT_LINE();
		token->token_ = N2_TOKEN_EOL;
		break;

		// ステートメント終わり
	case ':': ++p; token->token_ = N2_TOKEN_EOS; break;

		// 主にプリプロセッサで使う
	case '#':	++p; token->token_ = N2_TOKEN_PP_INDICATOR; break;
	case '%':	++p; token->token_ = N2_TOKEN_PP_ARG_INDICATOR; break;

		// 微妙な文字
	case '{':
		++p;
		if (p[0] == '\"')
		{
			--p;
			if (!n2i_tokenize_context_next_string(state, token, c, &p, N2I_TK_STR_MULTI)) { return N2_FALSE; }
		}
		else
		{
			token->token_ = N2_TOKEN_LBRACE;
			if (c->template_str_depth_ > 0) { ++c->template_str_levels_[c->template_str_depth_ - 1]; }
		}
		break;
	case '}':
		++p;
		token->token_ = N2_TOKEN_RBRACE;
		if (c->template_str_depth_ > 0)
		{
			if (--c->template_str_levels_[c->template_str_depth_ - 1] == 0)
			{
				--c->template_str_depth_;
				if (!n2i_tokenize_context_next_string(state, token, c, &p, N2I_TK_STR_TEMPLATE_CONTINUE)) { return N2_FALSE; }
			}
		}
		break;
	case '(':	++p; token->token_ = N2_TOKEN_LPARENTHESIS; break;
	case ')':	++p; token->token_ = N2_TOKEN_RPARENTHESIS; break;
	case ',':	++p; token->token_ = N2_TOKEN_COMMA; break;

		// 演算子
	case '|':
		++p;
		if (p[0] == '|')
		{
			++p;
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_LOR_ASSIGN; } else { token->token_ = N2_TOKEN_OP_LOR; }
		}
		else
		{
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_BOR_ASSIGN; } else { token->token_ = N2_TOKEN_OP_BOR; }
		}
		break;
	case '&':
		++p;
		if (p[0] == '&')
		{
			++p;
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_LAND_ASSIGN; } else { token->token_ = N2_TOKEN_OP_LAND; }
		}
		else
		{
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_BAND_ASSIGN; } else { token->token_ = N2_TOKEN_OP_BAND; }
		}
		break;
	case '^':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_BXOR_ASSIGN; } else { token->token_ = N2_TOKEN_OP_BXOR; } break;
	case '!':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_OP_NEQ; } else { token->token_ = N2_TOKEN_OP_NOT; } break;
	case '>':
		++p;
		if (p[0] == '>')
		{
			++p; token->token_ = N2_TOKEN_OP_BRSHIFT;
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_BRSHIFT_ASSIGN; }
		}
		else
		{
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_OP_GTOE; }
			else { token->token_ = N2_TOKEN_OP_GT; }
		}
		break;
	case '<':
		++p;
		if (p[0] == '<')
		{
			++p; token->token_ = N2_TOKEN_OP_BLSHIFT;
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_BLSHIFT_ASSIGN; }
		}
		else
		{
			if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_OP_LTOE; }
			else { token->token_ = N2_TOKEN_OP_LT; }
		}
		break;
	case '+':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_ADD_ASSIGN; } else if (p[0] == '+') { ++p; token->token_ = N2_TOKEN_INCREMENT; } else { token->token_ = N2_TOKEN_OP_ADD; } break;
	case '-':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_SUB_ASSIGN; } else if (p[0] == '-') { ++p; token->token_ = N2_TOKEN_DECREMENT; } else { token->token_ = N2_TOKEN_OP_SUB; } break;
	case '*':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_MUL_ASSIGN; } else { token->token_ = N2_TOKEN_OP_MUL; } break;
	case '/':
		++p;
		if (p[0] == '/')// 一行コメント
		{
			++p;
			while (p[0] != '\n' && p[0] != '\0') { ++p; }
			goto restart;
		}
		if (p[0] == '*')// 複数行コメント
		{
			++p;
			for (;;)
			{
				if (p[0] == '\0')
				{
					N2I_TK_RAISE(state, "複数行コメントの読み取り中にEOFが検出されました");
					return N2_FALSE;
				}
				if (p[0] == '\n')
				{
					++p;
					N2I_TK_NEXT_LINE();
					continue;
				}
				if (p[0] == '*' && p[1] == '/')
				{
					p += 2;
					break;
				}
				++p;
			}
			goto restart;
		}
		if (p[0] == '=')
		{
			++p;
			token->token_ = N2_TOKEN_DIV_ASSIGN;
		}
		else
		{ 
			token->token_ = N2_TOKEN_OP_DIV;
		}
		break;
	case '\\':	++p; if (p[0] == '=') { ++p; token->token_ = N2_TOKEN_MOD_ASSIGN; } else { token->token_ = N2_TOKEN_OP_MOD; } break;

		// 代入
	case '=':
		++p;
		if (p[0] == '=')
		{
			++p;
			token->token_ = N2_TOKEN_OP_EQ;
		}
		else
		{
			token->token_ = N2_TOKEN_ASSIGN;
		}
		break;

		// 文字列
	case '\'':
	case '\"':
	case '`':
		{
			const int tkstr = p[0] == '\'' ? N2I_TK_STR_SINGLE : p[0] == '\"' ? N2I_TK_STR_DOUBLE : N2I_TK_STR_TEMPLATE;
			if (!n2i_tokenize_context_next_string(state, token, c, &p, tkstr)) { return N2_FALSE; }
		}
		break;

		// 16進
	case '$': ++p; while (n2i_char_is_hexnumber(p[0])) { ++p; } token->token_ = N2_TOKEN_HEXINT; break;

		// コメント
	case ';':
		++p;
		while (p[0] != '\n' && p[0] != '\0')
		{
			++p;
		}
		goto restart;

	default:
		if (n2i_char_is_space(p[0]))
		{
			// スペース
			++p;
			token->left_space_ = N2_TRUE;
			while (n2i_char_is_space(p[0])) { ++p; }
			goto restart;
		}
		else if (n2i_char_is_number(p[0]))
		{
			// 数値
			n2_bool_t is_hex = p[0] == '0' && (p[1] == 'x' || p[1] == 'X');
			if (is_hex)
			{
				p += 2;
				while (n2i_char_is_hexnumber(p[0])) { ++p; }
				token->token_ = N2_TOKEN_HEXINT;
			}
			else
			{
				if (p[0] == '0')
				{
					++p;
				}
				else
				{
					while (n2i_char_is_number(p[0])) { ++p; }
				}
				if (p[0] == '.')
				{
					++p;
					while (n2i_char_is_number(p[0])) { ++p; }
					token->token_ = N2_TOKEN_FLOAT;
				}
				else
				{
					token->token_ = N2_TOKEN_INT;
				}
			}
		}
		else if (n2i_char_is_lead_ident(p[0]))
		{
			// 何らかの識別子
			++p;
			while (n2i_char_is_rest_ident(p[0])) { ++p; }
			token->token_ = N2_TOKEN_IDENTIFIER;
			// 名前空間修飾付き
			if (*p == '@')
			{
				++p;
				if (n2i_char_is_lead_ident(p[0]))
				{
					++p;
					while (n2i_char_is_rest_ident(p[0])) { ++p; }
				}
				token->token_ = N2_TOKEN_IDENTIFIER_FQ;
			}
			if (token->token_ == N2_TOKEN_IDENTIFIER)
			{
				const n2_token_e shadow = n2_token_shadow_find(c->script_ + prev_cursor, N2_SCAST(size_t, p - prev_p));
				if (shadow != N2_TOKEN_UNKNOWN) { token->token_ = shadow; }
			}
		}
		else
		{
			// もう読めない
			N2I_TK_RAISE(state, "読み取れない文字[%c]", *p);
			return N2_FALSE;
		}
		break;
	}

	if (n2i_char_is_space(p[0]))
	{
		token->right_space_ = N2_TRUE;
	}

	c->cursor_ += N2_SCAST(int, p - pp);
	token->cursor_begin_ = prev_cursor;
	token->cursor_end_ = c->cursor_;

	// contentが埋まってないなら埋める
	if (!token->content_)
	{
		const int len = token->cursor_end_ - token->cursor_begin_;
		token->content_ = n2_plstr_clone_size(state, c->script_ + token->cursor_begin_, N2_SCAST(size_t, len));
	}
	return N2_TRUE;
}
#undef N2I_TK_RAISE

N2_API void n2_token_free(n2_state_t* state, n2_token_t* t)
{
	if (t->content_) { n2_free(state, t->content_); }
	n2_free(state, t);
}

static void n2i_tokenarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_token_t** token = N2_RCAST(n2_token_t**, element);
	n2_token_free(state, *token);
}
N2_DEFINE_TARRAY(n2_token_t*, n2_tokenarray, N2_API, n2i_setupfunc_nothing, n2i_tokenarray_freefunc);

//=============================================================================
// 名前規則
static const char* n2i_modulename_default = "hsp";

N2_API n2_bool_t n2_naming_compute(n2_state_t* state, const char* src, size_t src_length, const char* modulename, n2_str_t* dst_shortname, n2_str_t* dst_fullname, n2_str_t* dst_modulename)
{
	if (!modulename) { modulename = n2i_modulename_default; }

	n2_str_t tstr;
	n2_str_init(&tstr);
	n2_str_set(state, &tstr, src, src_length);

	const int at_pos = n2_str_find(&tstr, "@", 1, 0);
	if (at_pos >= 0 && at_pos != n2_str_rfind(&tstr, "@", 1, 0)) { return N2_FALSE; }// @が2個以上

	const n2_bool_t is_at_last = at_pos >= 0 && N2_SCAST(size_t, at_pos + 1) >= tstr.size_;
	if (is_at_last) { modulename = n2i_modulename_default; }// @が最後ならデフォルト名が入っていると考える

	if (dst_shortname)
	{
		n2_str_set(state, dst_shortname, tstr.str_, at_pos < 0 ? SIZE_MAX : N2_SCAST(size_t, at_pos));
	}
	if (dst_fullname)
	{
		n2_str_set(state, dst_fullname, tstr.str_, at_pos < 0 ? SIZE_MAX : N2_SCAST(size_t, at_pos));
		n2_str_append_fmt(state, dst_fullname, "@%s", (at_pos < 0 || is_at_last) ? modulename : (tstr.str_ + at_pos + 1));
	}
	if (dst_modulename)
	{
		n2_str_set(state, dst_modulename, (at_pos < 0 || is_at_last) ? modulename : (tstr.str_ + at_pos + 1), SIZE_MAX);
	}

	n2_str_teardown(state, &tstr);
	return N2_TRUE;
}

N2_API n2_bool_t n2_naming_replace_modulename(n2_state_t* state, const char* src, size_t src_length, const char* modulename, n2_str_t* dst)
{
	if (!modulename) { modulename = n2i_modulename_default; }

	n2_str_t tstr;
	n2_str_init(&tstr);
	n2_str_set(state, &tstr, src, src_length);

	n2_bool_t is_replaced = N2_FALSE;
	const int at_pos = n2_str_find(&tstr, "@", 1, 0);
	if (at_pos >= 0)
	{
		n2_str_erase(&tstr, at_pos + 1, SIZE_MAX);
		n2_str_append(state, &tstr, modulename, SIZE_MAX);
		is_replaced = N2_TRUE;
	}

	n2_str_swap(&tstr, dst);
	n2_str_teardown(state, &tstr);
	return is_replaced;
}

N2_API n2_bool_t n2_naming_verify_modulename(const char* src, size_t src_length)
{
	if (src_length == SIZE_MAX) { src_length = N2_STRLEN(src); }
	if (src_length <= 0) { return N2_FALSE; }
	for (size_t i = 0; i < src_length; ++i) { if (!((i == 0 ? n2i_char_is_lead_ident : n2i_char_is_rest_ident)(src[i]))) { return N2_FALSE; } }
	return N2_TRUE;
}

//=============================================================================
// 抽象構文木
static void n2i_ast_node_teardown(n2_state_t* state, n2_ast_node_t* node)
{
	if (node->left_) { n2_ast_node_free(state, node->left_); }
	if (node->right_) { n2_ast_node_free(state, node->right_); }
}

N2_API n2_ast_node_t* n2_ast_node_alloc(n2_state_t* state, n2_ast_node_e tag, n2_ast_node_t* left, n2_ast_node_t* right)
{
	n2_ast_node_t* node = N2_TMALLOC(n2_ast_node_t, state);
	node->node_ = tag;
	node->token_ = NULL;
	node->left_ = left;
	node->right_ = right;
	node->exflags_ = 0;
	return node;
}

N2_API n2_ast_node_t* n2_ast_node_alloc_token(n2_state_t* state, n2_ast_node_e tag, const n2_token_t* token, n2_ast_node_t* left)
{
	n2_ast_node_t* node = N2_TMALLOC(n2_ast_node_t, state);
	node->node_ = tag;
	node->token_ = token;
	node->left_ = left;
	node->right_ = NULL;
	node->exflags_ = 0;
	return node;
}

N2_API void n2_ast_node_free_unit(n2_state_t* state, n2_ast_node_t* node)
{
	n2_free(state, node);
}

N2_API void n2_ast_node_free(n2_state_t* state, n2_ast_node_t* node)
{
	n2i_ast_node_teardown(state, node);
	n2_ast_node_free_unit(state, node);
}

static void n2i_ast_node_dump(n2_state_t* state, int indent, const n2_ast_node_t* node, n2_bool_t is_detail)
{
	static const char* nodenames[] =
	{
		"EMPTY",
		"ROOT",
		"ROOT_PARTS",
		"LINE",
		"STATEMENT",
		"MODULE",
		"MODULE_LOCALVAR",
		"GLOBAL",
		"USELIB",
		"DEFFUNC",
		"DEFCFUNC",
		"MODINIT",
		"MODTERM",
		"MODFUNC",
		"MODCFUNC",
		"FUNC",
		"CFUNC",
		"DEFFUNC_PARTS",
		"DECLARE_PARAM",
		"DECLARE_PARAM_PARTS",
		"LABEL",
		"BLOCK_STATEMENTS",
		"COMMAND",
		"ARGUMENTS",
		"ARGUMENTS_PARTS",
		"ARGUMENTS_EMPTY_ARG",
		"ASSIGN",
		"LOR_ASSIGN",
		"LAND_ASSIGN",
		"BOR_ASSIGN",
		"BAND_ASSIGN",
		"BXOR_ASSIGN",
		"BLSHIFT_ASSIGN",
		"BRSHIFT_ASSIGN",
		"ADD_ASSIGN",
		"SUB_ASSIGN",
		"MUL_ASSIGN",
		"DIV_ASSIGN",
		"MOD_ASSIGN",
		"VARIABLE",
		"EXPRESSION",
		"CONDITIONAL",
		"CONDITIONAL_PARTS",
		"LOR",
		"LAND",
		"BOR",
		"BAND",
		"BXOR",
		"EQ",
		"NEQ",
		"GT",
		"GTOE",
		"LT",
		"LTOE",
		"BLSHIFT",
		"BRSHIFT",
		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"MOD",
		"INCREMENT",
		"DECREMENT",
		"UNARY_NOT",
		"UNARY_MINUS",
		"PRIMITIVE_VALUE",
		"TEMPLATE_STRING",
		"TEMPLATE_STRING_PARTS",
		"LABEL_VALUE",
		"IDENTIFIER_EXPR",
		"END",
		"RETURN",
		"GOTO",
		"GOSUB",
		"REPEAT",
		"FOREACH",
		"LOOP",
		"CONTINUE",
		"BREAK",
		"IF",
		"IF_DISPATCHER",
		"SWITCH",
		"CASE",
		"DEFAULT",
		"SWBREAK",
		"SWEND",
		"<END>"
	};
	N2_ASSERT(node->node_ >= 0 && node->node_ < N2_MAX_AST_NODE);

	while (node)
	{
		n2_bool_t noprint = N2_FALSE;
		switch (node->node_)
		{
		case N2_AST_NODE_ROOT:
		case N2_AST_NODE_ROOT_PARTS:
		case N2_AST_NODE_DEFFUNC_PARTS:
		case N2_AST_NODE_DECLARE_PARAM_PARTS:
		case N2_AST_NODE_BLOCK_STATEMENTS:
		case N2_AST_NODE_ARGUMENTS_PARTS:
			noprint = N2_TRUE;
			break;
		default:
			break;
		}

		if (is_detail || !noprint)
		{
			for (int i = 0; i < indent; ++i) { n2i_printf(state, "  "); }
			n2i_printf(state, "%s", nodenames[node->node_]);
			if (is_detail) { n2i_printf(state, " :%p", node); }
			if (node->token_) { n2i_printf(state, "[%s]", node->token_->content_); }
			n2i_printf(state, "\n");
		}

		n2_bool_t noindent = N2_FALSE;
		switch (node->node_)
		{
		case N2_AST_NODE_ROOT:
		case N2_AST_NODE_ROOT_PARTS:
		case N2_AST_NODE_LINE:
		case N2_AST_NODE_DEFFUNC_PARTS:
		case N2_AST_NODE_DECLARE_PARAM:
		case N2_AST_NODE_DECLARE_PARAM_PARTS:
		case N2_AST_NODE_BLOCK_STATEMENTS:
		case N2_AST_NODE_ARGUMENTS_PARTS:
		case N2_AST_NODE_TEMPLATE_STRING_PARTS:
			noindent = N2_TRUE;
			break;
		default:
			break;
		}
		if (!noindent) { ++indent; }

		if (node->left_) { n2i_ast_node_dump(state, indent, node->left_, is_detail); }

		// tail recursion
		node = node->right_;
	}
}

N2_API void n2_ast_node_dump(n2_state_t* state, const n2_ast_node_t* ast, n2_bool_t is_detail)
{
	n2i_printf(state, "====ast[%p]====\n", ast);
	n2i_ast_node_dump(state, 1, ast, is_detail);
	n2i_printf(state, "--------\n");
}

static void n2i_astarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_ast_node_free(state, *N2_RCAST(n2_ast_node_t**, element));
}

N2_DEFINE_TARRAY(n2_ast_node_t*, n2_astarray, N2_API, n2i_setupfunc_nothing, n2i_astarray_freefunc);

//=============================================================================
// パーサー
typedef struct n2i_parse_context_t n2i_parse_context_t;
struct n2i_parse_context_t
{
	n2_bool_t error_;
};

static void n2i_parse_context_init(n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
}

static n2_ast_node_t* n2i_parser_parse_statement_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_bool_t n2i_parser_parse_statement_post(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc, n2_ast_node_t* statement, n2_ast_node_t* root_parts);
static n2_ast_node_t* n2i_parser_parse_source_order_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_declare_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_func_declare_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_label_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc, n2_bool_t as_value);
static n2_ast_node_t* n2i_parser_parse_control_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_command_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_arguments(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_incdec_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_assign_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_variable_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);
static n2_ast_node_t* n2i_parser_parse_thenelse(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_lorand(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_borand(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_eqneq(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_gtlt(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_bshift(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_addsub(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_muldivmod(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_term(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_primitive(n2_state_t* state, n2_parser_t* p);
static n2_ast_node_t* n2i_parser_parse_identifier_expression_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc);

static void n2i_raise_parser_exception(n2_state_t* state, n2_error_e e, const n2_token_t* token, const char* package, const char* line_head, int line, const char* fmt, ...)
{
	va_list args;

	n2_str_t tstr;
	n2_str_init(&tstr);

	n2_str_t subdescstr;
	n2_str_init(&subdescstr);

	const n2_sourcecode_t* sourcecode = NULL;
	if (token && token->sourcecode_)
	{
		int depth = 0;
		sourcecode = token->sourcecode_;
		const n2_sourcecode_t* cur = sourcecode;
		while (cur)
		{
			const n2_sourcecode_t* parent = cur->parent_sourcecode_;
			if (!parent) { break; }

			if (depth > 0) { n2_str_append(state, &subdescstr, "\n", SIZE_MAX); }
			n2_str_append_fmt(state, &subdescstr, "インクルード元 @@ %s(%s):%d", parent->package_.str_, parent->src_loaded_filepath_.str_, cur->parent_line_ + N2_LINE_BASE);
			cur = parent;
			++depth;
		}
	}

	n2_str_t rawmessagestr;
	n2_str_init(&rawmessagestr);
	va_start(args, fmt); n2_str_vfmt_to(state, &rawmessagestr, fmt, args); va_end(args);

	n2_str_t messagestr;
	n2_str_init(&messagestr);
	n2_str_copy_to(state, &messagestr, &rawmessagestr);
	n2i_errorinfo_append(state, &messagestr, package, line_head, line);

	n2i_do_error(state, e, sourcecode, rawmessagestr.str_, messagestr.str_, line, subdescstr.str_, NULL);

	n2_str_teardown(state, &subdescstr);
	n2_str_teardown(state, &messagestr);
	n2_str_teardown(state, &rawmessagestr);
	n2_str_teardown(state, &tstr);
}

#define N2I_PS_RAISE(state, t, fmt, ...) \
	n2i_raise_parser_exception(state, N2_ERROR_PARSE, t, t->package_, t->appear_line_head_, t->appear_line_, fmt, ## __VA_ARGS__)

N2_API void n2i_parser_teardown(n2_state_t* state, n2_parser_t* p)
{
	n2_tokenarray_free(state, p->tokens_);
	n2_tokenize_context_fin(state, &p->tokenize_context_);
}

N2_API n2_parser_t* n2_parser_alloc(n2_state_t* state)
{
	n2_parser_t* p = N2_TMALLOC(n2_parser_t, state);
	p->tokens_ = n2_tokenarray_alloc(state, 128, 128);
	p->token_cursor_ = 0;
	n2_tokenize_context_init_raw(state, &p->tokenize_context_, NULL, NULL);
	return p;
}

N2_API void n2_parser_free(n2_state_t* state, n2_parser_t* p)
{
	n2i_parser_teardown(state, p);
	n2_free(state, p);
}

static void n2i_parser_rewind(n2_state_t* state, n2_parser_t* p)
{
	if (p->tokens_) { n2_tokenarray_free(state, p->tokens_); }
	p->tokens_ = n2_tokenarray_alloc(state, 1, 0);
	p->token_cursor_ = 0;
	n2_tokenize_context_fin(state, &p->tokenize_context_);
}

N2_API void n2_parser_rewind(n2_state_t* state, n2_parser_t* p, n2_sourcecode_t* sourcecode)
{
	n2i_parser_rewind(state, p);
	n2_tokenize_context_init(state, &p->tokenize_context_, sourcecode);
}

N2_API void n2_parser_rewind_raw(n2_state_t* state, n2_parser_t* p, const char* package, const char* script)
{
	n2i_parser_rewind(state, p);
	n2_tokenize_context_init_raw(state, &p->tokenize_context_, package, script);
}

N2_API const n2_token_t* n2_parser_read_token(n2_state_t* state, n2_parser_t* p)
{
	if (p->token_cursor_ < N2_SCAST(int, n2_tokenarray_size(p->tokens_)))
	{
		n2_token_t* token = *n2_tokenarray_peek(p->tokens_, p->token_cursor_);
		++p->token_cursor_;
		return token;
	}

	n2_token_t* token = N2_TMALLOC(n2_token_t, state);
	if (!n2_tokenize_context_next(state, token, &p->tokenize_context_))
	{
		token->token_ = N2_TOKEN_ERROR;
	}
	n2_tokenarray_pushv(state, p->tokens_, token);
	++p->token_cursor_;
	return token;
}

N2_API void n2_parser_unread_token(n2_parser_t* p, size_t num)
{
	if (num <= 0) { return; }
	N2_ASSERT(N2_SCAST(int, num) <= p->token_cursor_);
	p->token_cursor_ -= N2_SCAST(int, num);
}

N2_API const n2_token_t* n2_parser_prev_token(const n2_parser_t* p, size_t num)
{
	if (N2_SCAST(int, num) > p->token_cursor_) { return NULL; }
	const int token_cursor = p->token_cursor_ - N2_SCAST(int, num);
	return *n2_tokenarray_peek(p->tokens_, token_cursor);
}

N2_API n2_ast_node_t* n2_parser_parse(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* root = n2_ast_node_alloc(state, N2_AST_NODE_ROOT, NULL, NULL);
	n2_ast_node_t* root_parts = root;

	n2i_parse_context_t pc;
	n2i_parse_context_init(&pc);

	for (;;)
	{
		if (root_parts->left_)
		{
			n2_ast_node_t* nparts = n2_ast_node_alloc(state, N2_AST_NODE_ROOT_PARTS, NULL, NULL);
			root_parts->right_ = nparts;
			root_parts = nparts;
		}

		n2_ast_node_t* statement = n2i_parser_parse_statement_safe(state, p, &pc);
		if (!statement) { break; }

		root_parts->left_ = statement;
	}

	// エラー？
	if (pc.error_)
	{
		n2_ast_node_free(state, root);
		return NULL;
	}

	{
		const n2_token_t* token = n2_parser_read_token(state, p);
		if (token->token_ != N2_TOKEN_EOF)
		{
			n2i_raise_as(state, N2_ERROR_PARSE, p->tokenize_context_.sourcecode_, p->tokenize_context_.package_, token->appear_line_head_, token->appear_line_, "パースできないトークンです");
			n2_ast_node_free(state, root);
			return NULL;
		}
	}

	return root;
}

N2_API n2_ast_node_t* n2_parser_parse_expression(n2_state_t* state, n2_parser_t* p)
{
	// ただの関数転送
	return n2i_parser_parse_thenelse(state, p);
}

static n2_ast_node_t* n2i_parser_parse_statement_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;

	// 行頭？
	n2_bool_t is_line_head = N2_FALSE;
	{
		const n2_token_t* prev_token = n2_parser_prev_token(p, 1);
		if (!prev_token || prev_token->token_ == N2_TOKEN_EOL)
		{
			is_line_head = N2_TRUE;
		}
	}

	// 何もない？
	{
		const n2_token_t* token = n2_parser_read_token(state, p);
		if (token->token_ == N2_TOKEN_ERROR) { pc->error_ = N2_TRUE; return NULL; }
		if (token->token_ == N2_TOKEN_EOF) { return NULL; }
		if (n2_token_is_eos_like(token->token_)) { return n2_ast_node_alloc(state, N2_AST_NODE_EMPTY, NULL, NULL); }
		n2_parser_unread_token(p, 1);
	}

	n2_ast_node_t* statement = NULL;

	// オーダーを試す
	if (!statement)
	{
		statement = n2i_parser_parse_source_order_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// 宣言を試す
	if (!statement)
	{
		statement = n2i_parser_parse_declare_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// 関宣言を試す
	if (!statement)
	{
		statement = n2i_parser_parse_func_declare_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// ラベルを試す
	if (!statement)
	{
		statement = n2i_parser_parse_label_safe(state, p, pc, N2_FALSE);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// 制御構文を試す
	if (!statement)
	{
		statement = n2i_parser_parse_control_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// コマンドを試す
	if (!statement)
	{
		statement = n2i_parser_parse_command_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// インクリメントデクリメント
	if (!statement)
	{
		statement = n2i_parser_parse_incdec_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// それ以外は全て代入
	if (!statement)
	{
		statement = n2i_parser_parse_assign_safe(state, p, pc);
		if (pc->error_) { N2_ASSERT(!statement); return NULL; }
	}

	// ここまで来て何もないなら、パース不能
	if (!statement)
	{
		const n2_token_t* token = n2_parser_read_token(state, p);
		N2I_PS_RAISE(state, token, "解析不能なステートメントです");
		pc->error_ = N2_TRUE;
		return NULL;
	}

	// 最後の改行チェック
	{
		const n2_token_t* token = n2_parser_read_token(state, p);
		if (!n2_token_is_eos_like(token->token_))
		{
			N2I_PS_RAISE(state, token, "ステートメントを最後まで正しく解析できませんでした（不明なトークン＝%s）", token->content_);
			n2_ast_node_free(state, statement);
			pc->error_ = N2_TRUE;
			return NULL;
		}
	}

	// ステートメントとしてラッピング
	statement = n2_ast_node_alloc(state, N2_AST_NODE_STATEMENT, statement, NULL);

	// 行ステートメントとする
	if (is_line_head)
	{
		statement = n2_ast_node_alloc(state, N2_AST_NODE_LINE, statement, NULL);
	}

	return statement;
}

static n2_ast_node_t* n2i_parser_parse_source_order_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;

	{
		const n2_token_t* indicator = n2_parser_read_token(state, p);
		if (indicator->token_ != N2_TOKEN_PP_INDICATOR)
		{
			n2_parser_unread_token(p, 1);
			return NULL;
		}

		const n2_token_t* nindicator = n2_parser_read_token(state, p);
		if (nindicator->token_ != N2_TOKEN_OP_LT || nindicator->left_space_)
		{
			n2_parser_unread_token(p, 2);
			return NULL;
		}
	}

	const n2_token_t* order = n2_parser_read_token(state, p);
	const n2_source_order_e sorder = order->token_ == N2_TOKEN_IDENTIFIER ? n2_source_order_find(order->content_) : N2_SOURCE_ORDER_UNKNOWN;

	switch (sorder)
	{
	case N2_SOURCE_ORDER_INCLUDE_PUSH:
		{
			const n2_token_t* nt = n2_parser_read_token(state, p);
			const n2_token_t* ft = n2_parser_read_token(state, p);

			if (nt->token_ != N2_TOKEN_INT || ft->token_ != N2_TOKEN_STRING)
			{
				N2I_PS_RAISE(state, order, "include_push：引数のトークン解析に失敗（index=%s, filepath=%s）", nt->content_, ft->content_);
				pc->error_ = N2_TRUE;
				return NULL;
			}

			const int index = N2_SCAST(int, N2_STRTOLL(nt->content_, NULL, 0));
			//const char* filepath = ft->content_;

			// include関係をpush
			n2_sourcecode_t* sourcecode = p->tokenize_context_.sourcecode_;
			if (sourcecode && index >= 0)
			{
				n2_sourcecode_t* next_sourcecode = n2_sourcecodearray_peekv(sourcecode->sourcecodes_, index, NULL);
				if (next_sourcecode)
				{
					p->tokenize_context_.sourcecode_ = next_sourcecode;
					p->tokenize_context_.package_ = next_sourcecode->package_.str_;
					p->tokenize_context_.line_ = -1;// 次の行
				}
				else if (state->config_.enable_error_include_push_)
				{
					N2I_PS_RAISE(state, order, "include_push：該当のincludeが見つかりませんでした、プリプロセスミス（index=%d, filepath=%s）", index, ft->content_);
					pc->error_ = N2_TRUE;
					return NULL;
				}
			}

			// empty
			return n2_ast_node_alloc_token(state, N2_AST_NODE_EMPTY, order, NULL);
		}
		break;
	case N2_SOURCE_ORDER_INCLUDE_POP:
		{
			const n2_token_t* it = n2_parser_read_token(state, p);
			if (it->token_ != N2_TOKEN_INT)
			{
				N2I_PS_RAISE(state, order, "include_pop：引数のトークン解析に失敗（index=%s）", it->content_);
				pc->error_ = N2_TRUE;
				return NULL;
			}

			const int line_index = N2_SCAST(int, N2_STRTOLL(it->content_, NULL, 0));

			// include関係をpop
			n2_sourcecode_t* sourcecode = p->tokenize_context_.sourcecode_;
			if (sourcecode)
			{
				p->tokenize_context_.line_ = sourcecode->parent_line_;// lineを修復
				p->tokenize_context_.sourcecode_ = sourcecode->parent_sourcecode_;
				if (p->tokenize_context_.sourcecode_)
				{
					p->tokenize_context_.package_ = p->tokenize_context_.sourcecode_->package_.str_;
				}
			}
			else
			{
				p->tokenize_context_.line_ = line_index;
			}

			// empty
			return n2_ast_node_alloc_token(state, N2_AST_NODE_EMPTY, order, NULL);
		}
		break;
	default:
		N2I_PS_RAISE(state, order, "識別できないオーダー（%s）です", order->content_);
		break;
	}

	pc->error_ = N2_TRUE;
	return NULL;
}

static n2_ast_node_t* n2i_parser_parse_declare_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* token = n2_parser_read_token(state, p);
	if (token->token_ != N2_TOKEN_PP_INDICATOR)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_token_t* directive = n2_parser_read_token(state, p);
	if (directive->token_ != N2_TOKEN_IDENTIFIER)
	{
		n2_parser_unread_token(p, 2);
		return NULL;
	}

	const n2_pp_directive_e pp_directive = n2_pp_directive_find(directive->content_);
	const char* directive_name = directive->content_;

	switch (pp_directive)
	{
	case N2_PP_DIRECTIVE_MODULE:
		{
			const n2_token_t* ident = n2_parser_read_token(state, p);
			if (ident->token_ != N2_TOKEN_IDENTIFIER)
			{
				N2I_PS_RAISE(state, ident, "%s のモジュール名が識別子ではありませんでした（%s）", directive_name, ident->content_);
				pc->error_ = N2_TRUE;
				return NULL;
			}

			if (n2_keyword_find(ident->content_) >= 0)
			{
				N2I_PS_RAISE(state, ident, "%s のモジュール名にキーワードを用いることはできません（%s）", directive_name, ident->content_);
				pc->error_ = N2_TRUE;
				return NULL;
			}

			n2_ast_node_t* localvars = NULL;

			for (;;)
			{
				const n2_token_t* lt = n2_parser_read_token(state, p);
				if (n2_token_is_eos_like(lt->token_)) { n2_parser_unread_token(p, 1); break; }
				if (!n2i_token_is_keyword(lt, N2_KEYWORD_LOCAL)) { n2_parser_unread_token(p, 1); }

				const n2_token_t* lvt = n2_parser_read_token(state, p);
				if (lvt->token_ != N2_TOKEN_IDENTIFIER)
				{
					N2I_PS_RAISE(state, ident, "%s のモジュール（%s）のローカル変数定義が不正です（%s）", directive_name, ident->content_, lvt->content_);
					pc->error_ = N2_TRUE;
					n2_ast_node_free(state, localvars);
					return NULL;
				}

				n2_ast_node_t* lvn = n2_ast_node_alloc_token(state, N2_AST_NODE_MODULE_LOCALVAR, lvt, NULL);
				if (localvars) { localvars->left_ = lvn; }
				localvars = lvn;
			}

			return n2_ast_node_alloc_token(state, N2_AST_NODE_MODULE, ident, localvars);
		}
	case N2_PP_DIRECTIVE_GLOBAL:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_GLOBAL, directive, NULL);

	case N2_PP_DIRECTIVE_USELIB:
		{
			const n2_token_t* path = n2_parser_read_token(state, p);
			if (path->token_ != N2_TOKEN_STRING)
			{
				N2I_PS_RAISE(state, path, "%s のライブラリパスが文字列ではありませんでした（%s）", directive_name, path->content_);
				pc->error_ = N2_TRUE;
				return NULL;
			}
			return n2_ast_node_alloc_token(state, N2_AST_NODE_USELIB, path, NULL);
		}

	default:
		break;
	}

	n2_parser_unread_token(p, 2);
	return NULL;
}

static n2_ast_node_t* n2i_parser_parse_func_declare_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* token = n2_parser_read_token(state, p);
	if (token->token_ != N2_TOKEN_PP_INDICATOR)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_token_t* directive = n2_parser_read_token(state, p);
	if (directive->token_ != N2_TOKEN_IDENTIFIER)
	{
		n2_parser_unread_token(p, 2);
		return NULL;
	}

	const n2_pp_directive_e pp_directive = n2_pp_directive_find(directive->content_);

	n2_ast_node_e node = N2_AST_NODE_UNDEF;
	n2_bool_t is_modfunc = N2_FALSE;
	n2_bool_t is_dlfunc = N2_FALSE;
	n2_bool_t is_noname = N2_FALSE;

	switch (pp_directive)
	{
	case N2_PP_DIRECTIVE_DEFFUNC:
		node = N2_AST_NODE_DEFFUNC;
		break;
	case N2_PP_DIRECTIVE_DEFCFUNC:
		node = N2_AST_NODE_DEFCFUNC;
		break;
	case N2_PP_DIRECTIVE_MODINIT:
		node = N2_AST_NODE_MODINIT;
		is_modfunc = N2_TRUE;
		is_noname = N2_TRUE;
		break;
	case N2_PP_DIRECTIVE_MODTERM:
		node = N2_AST_NODE_MODTERM;
		is_modfunc = N2_TRUE;
		is_noname = N2_TRUE;
		break;
	case N2_PP_DIRECTIVE_MODFUNC:
		node = N2_AST_NODE_MODFUNC;
		is_modfunc = N2_TRUE;
		break;
	case N2_PP_DIRECTIVE_MODCFUNC:
		node = N2_AST_NODE_MODCFUNC;
		is_modfunc = N2_TRUE;
		break;
	case N2_PP_DIRECTIVE_FUNC:
		node = N2_AST_NODE_FUNC;
		is_dlfunc = N2_TRUE;
		break;
	case N2_PP_DIRECTIVE_CFUNC:
		node = N2_AST_NODE_CFUNC;
		is_dlfunc = N2_TRUE;
		break;
	default:
		n2_parser_unread_token(p, 2);
		return NULL;
	}

	const char* directive_name = directive->content_;

	const n2_token_t* lgt = n2_parser_read_token(state, p);
	if (n2i_token_is_keyword(lgt, N2_KEYWORD_LOCAL) || n2i_token_is_keyword(lgt, N2_KEYWORD_GLOBAL))
	{
		// lgtをそのまま使う
	}
	else
	{
		lgt = NULL;
		n2_parser_unread_token(p, 1);
	}

	if (is_noname && lgt)
	{
		N2I_PS_RAISE(state, directive, "無名関数に local や global はつけられません");
		pc->error_ = N2_TRUE;
		return NULL;
	}

	// 関数名
	const n2_token_t* ident = NULL;
	
	if (!is_noname)
	{
		ident = n2_parser_read_token(state, p);
		if (ident->token_ != N2_TOKEN_IDENTIFIER)
		{
			N2I_PS_RAISE(state, ident, "%s の関数名が識別子ではありませんでした（%s）", directive_name, ident->content_);
			pc->error_ = N2_TRUE;
			return NULL;
		}

		if (n2_keyword_find(ident->content_) >= 0)
		{
			N2I_PS_RAISE(state, ident, "%s の関数名にキーワードを用いることはできません（%s）", directive_name, ident->content_);
			pc->error_ = N2_TRUE;
			return NULL;
		}
	}

	// 関数パス
	const n2_token_t* lib_proc_name = NULL;
	if (is_dlfunc)
	{
		lib_proc_name = n2_parser_read_token(state, p);
		if (lib_proc_name->token_ != N2_TOKEN_STRING)
		{
			N2I_PS_RAISE(state, lib_proc_name, "%s のライブラリ関数名が文字列ではありませんでした（%s）", directive_name, lib_proc_name->content_);
			pc->error_ = N2_TRUE;
			return NULL;
		}
	}

	// パラメータ
	n2_ast_node_t* params = NULL;

	const n2_token_t* nt = n2_parser_read_token(state, p);
	if (n2_token_is_eos_like(nt->token_))
	{
		n2_parser_unread_token(p, 1);
	}
	else
	{
		// 左括弧チェック
		const n2_bool_t has_parenthesis = is_dlfunc ? N2_FALSE : nt->token_ == N2_TOKEN_LPARENTHESIS;// 動的ライブラリ宣言時は括弧は絶対つかない
		if (!has_parenthesis) { n2_parser_unread_token(p, 1); }

		const n2_token_t* preread_e = n2_parser_read_token(state, p);
		n2_parser_unread_token(p, 1);
		if ((!has_parenthesis || preread_e->token_ != N2_TOKEN_RPARENTHESIS) && !n2_token_is_eos_like(preread_e->token_))
		{
			// 各パラメータ
			n2_ast_node_t* cur_param = NULL;
			for (;;)
			{
				// 型名
				const n2_token_t* type = n2_parser_read_token(state, p);
				const n2_func_param_e paramtype = n2_func_param_from_token(type, is_dlfunc);
				if (paramtype == N2_FUNC_PARAM_UNKNOWN)
				{
					N2I_PS_RAISE(state, type, "%s：関数（%s）パラメータ定義で認識できない型名です（%s）", directive_name, ident->content_, type->content_);
					if (params) { n2_ast_node_free(state, params); }
					pc->error_ = N2_TRUE;
					return NULL;
				}

				// 名前
				const n2_token_t* param_name = param_name = n2_parser_read_token(state, p);
				if (param_name->token_ != N2_TOKEN_IDENTIFIER)
				{
					// パラメータ省略OK？
					if (!is_dlfunc)
					{
						N2I_PS_RAISE(state, param_name, "%s：関数（%s）パラメータ名を認識できません（%s）", directive_name, ident->content_, param_name->content_);
						if (params) { n2_ast_node_free(state, params); }
						pc->error_ = N2_TRUE;
						return NULL;
					}
					n2_parser_unread_token(p, 1);
					param_name = NULL;
				}

				// デフォルト値
				n2_ast_node_t* this_param_defval = NULL;
				if (!is_dlfunc)
				{
					const n2_token_t* at = n2_parser_read_token(state, p);
					if (at->token_ == N2_TOKEN_ASSIGN)
					{
						this_param_defval = n2_parser_parse_expression(state, p);
						if (!this_param_defval)
						{
							if (params) { n2_ast_node_free(state, params); }
							pc->error_ = N2_TRUE;
							return NULL;
						}
					}
					else
					{
						n2_parser_unread_token(p, 1);
					}
				}

				n2_ast_node_t* this_param_type = n2_ast_node_alloc_token(state, N2_AST_NODE_DECLARE_PARAM_PARTS, type, this_param_defval);
				n2_ast_node_t* this_param_name = n2_ast_node_alloc_token(state, N2_AST_NODE_DECLARE_PARAM_PARTS, param_name, NULL);
				n2_ast_node_t* this_param_parts = n2_ast_node_alloc(state, N2_AST_NODE_DECLARE_PARAM_PARTS, this_param_type, this_param_name);
				n2_ast_node_t* this_param = n2_ast_node_alloc(state, N2_AST_NODE_DECLARE_PARAM, this_param_parts, NULL);

				if (!params)
				{
					params = this_param;
					cur_param = this_param;
				}
				else
				{
					N2_ASSERT(cur_param);
					N2_ASSERT(!cur_param->right_);
					cur_param->right_ = this_param;
					cur_param = this_param;
				}

				const n2_token_t* nn = n2_parser_read_token(state, p);
				if (n2_token_is_eos_like(nn->token_)) { n2_parser_unread_token(p, 1); break; }
				if (has_parenthesis && nn->token_ == N2_TOKEN_RPARENTHESIS) { n2_parser_unread_token(p, 1); break; }
				if (nn->token_ != N2_TOKEN_COMMA)
				{
					N2I_PS_RAISE(state, nn, "%s：関数（%s）定義を再度まで正しく解釈できませんでした（トークン＝%s）", directive_name, ident->content_, nn->content_);
					if (params) { n2_ast_node_free(state, params); }
					pc->error_ = N2_TRUE;
					return NULL;
				}
			}
		}

		// 右括弧チェック
		if (has_parenthesis)
		{
			const n2_token_t* rp = n2_parser_read_token(state, p);
			if (rp->token_ != N2_TOKEN_RPARENTHESIS)
			{
				N2I_PS_RAISE(state, rp, "%s：パラメータ定義が括弧で閉じられていません", directive_name, ident->content_);
				if (params) { n2_ast_node_free(state, params); }
				pc->error_ = N2_TRUE;
				return NULL;
			}
		}
	}

	n2_ast_node_t* res = n2_ast_node_alloc_token(state, node, ident, params);
	n2_ast_node_t* curres = res;
	if (is_dlfunc) { N2_ASSERT(!curres->right_); curres->right_ = n2_ast_node_alloc_token(state, N2_AST_NODE_DEFFUNC_PARTS, lib_proc_name, NULL); curres = curres->right_; }
	if (lgt) { N2_ASSERT(!curres->right_); curres->right_ = n2_ast_node_alloc_token(state, N2_AST_NODE_DEFFUNC_PARTS, lgt, NULL); curres = curres->right_; }
	return res;
}

static n2_ast_node_t* n2i_parser_parse_label_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc, n2_bool_t as_value)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* token = n2_parser_read_token(state, p);
	if (token->token_ != N2_TOKEN_OP_MUL)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_token_t* ident = n2_parser_read_token(state, p);
	if (ident->token_ != N2_TOKEN_IDENTIFIER && ident->token_ != N2_TOKEN_IDENTIFIER_FQ)
	{
		n2_parser_unread_token(p, 2);
		return NULL;
	}

	return n2_ast_node_alloc_token(state, as_value ? N2_AST_NODE_LABEL_VALUE : N2_AST_NODE_LABEL, ident, NULL);
}

static n2_ast_node_t* n2i_parser_parse_control_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* ident = n2_parser_read_token(state, p);
	if (ident->token_ != N2_TOKEN_IDENTIFIER)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_keyword_e keyword = n2_keyword_find(ident->content_);
	switch (keyword)
	{
	case N2_KEYWORD_RETURN:
		{
			const n2_token_t* next = n2_parser_read_token(state, p);
			n2_parser_unread_token(p, 1);

			n2_ast_node_t* expr = NULL;
			if (!n2_token_is_eos_like(next->token_))
			{
				expr = n2_parser_parse_expression(state, p);
			}
			return n2_ast_node_alloc_token(state, N2_AST_NODE_RETURN, ident, expr);
		}
	case N2_KEYWORD_GOTO:
	case N2_KEYWORD_GOSUB:
		{

			n2_ast_node_t* expr = n2_parser_parse_expression(state, p);
			if (!expr) { return NULL; }
			return n2_ast_node_alloc_token(state, keyword == N2_KEYWORD_GOTO ? N2_AST_NODE_GOTO : N2_AST_NODE_GOSUB, ident, expr);
		}
	case N2_KEYWORD_REPEAT:
		{
			const n2_token_t* next = n2_parser_read_token(state, p);
			n2_parser_unread_token(p, 1);

			n2_ast_node_t* expr = NULL;
			if (!n2_token_is_eos_like(next->token_))
			{
				expr = n2_parser_parse_expression(state, p);
				if (!expr) { pc->error_ = N2_TRUE; return NULL; }
			}
			return n2_ast_node_alloc_token(state, N2_AST_NODE_REPEAT, ident, expr);
		}
	case N2_KEYWORD_FOREACH:
		{
			n2_ast_node_t* var = n2i_parser_parse_variable_safe(state, p, pc);
			if (pc->error_) { N2_ASSERT(!var); return NULL; }
			return n2_ast_node_alloc_token(state, N2_AST_NODE_FOREACH, ident, var);
		}
	case N2_KEYWORD_LOOP:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_LOOP, ident, NULL);
	case N2_KEYWORD_CONTINUE:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_CONTINUE, ident, NULL);
	case N2_KEYWORD_BREAK:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_BREAK, ident, NULL);
	case N2_KEYWORD_IF:
		{
			n2_ast_node_t* expr = n2_parser_parse_expression(state, p);
			if (!expr) { return NULL; }
			const n2_token_t* next = n2_parser_read_token(state, p);

			n2_ast_node_t* true_statements = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);
			n2_ast_node_t* false_statements = NULL;
			n2_ast_node_t* tfs_cur = NULL;
			if (next->token_ == N2_TOKEN_LBRACE)
			{
				tfs_cur = true_statements;
				for (;;)
				{
					const n2_token_t* pp = n2_parser_prev_token(p, 1);
					if (pp->token_ == N2_TOKEN_RBRACE)
					{
						// RBRACEは食われてた
						break;
					}
					n2_ast_node_t* statement = n2i_parser_parse_statement_safe(state, p, pc);
					if (!statement)
					{
						if (!(pc->error_))
						{
							N2I_PS_RAISE(state, pp, "if文の解析中、解析できないステートメントに到達しました");
							pc->error_ = N2_TRUE;
						}
						n2_ast_node_free(state, expr);
						n2_ast_node_free(state, true_statements);
						return NULL;
					}
					N2_ASSERT(!tfs_cur->left_);
					tfs_cur->left_ = statement;
					tfs_cur->right_ = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);
					tfs_cur = tfs_cur->right_;
				}
			}
			else
			{
				n2_parser_unread_token(p, 1);
				{
					const n2_token_t* nn = n2_parser_read_token(state, p);
					if (nn->token_ != N2_TOKEN_EOS)
					{
						N2I_PS_RAISE(state, nn, "if文の解析中：ifの条件式の後は { か : しか置けません");
						n2_ast_node_free(state, expr);
						n2_ast_node_free(state, true_statements);
						pc->error_ = N2_TRUE;
						return NULL;
					}
				}

				tfs_cur = true_statements;
				for (;;)
				{
					const n2_token_t* pp = n2_parser_prev_token(p, 1);
					if (pp->token_ == N2_TOKEN_EOL || pp->token_ == N2_TOKEN_EOF)
					{
						// EOLまたはEOFは食われてた
						n2_parser_unread_token(p, 1);
						break;
					}

					const n2_token_t* nn = n2_parser_read_token(state, p);
					n2_parser_unread_token(p, 1);
					if (n2i_token_is_keyword(nn, N2_KEYWORD_ELSE))
					{ break; }

					n2_ast_node_t* statement = n2i_parser_parse_statement_safe(state, p, pc);
					if (!statement)
					{
						if (!(pc->error_))
						{
							N2I_PS_RAISE(state, nn, "if文の解析中、解析できないステートメントに到達しました");
							pc->error_ = N2_TRUE;
						}
						n2_ast_node_free(state, expr);
						n2_ast_node_free(state, true_statements);
						return NULL;
					}
					N2_ASSERT(!tfs_cur->left_);
					tfs_cur->left_ = statement;
					tfs_cur->right_ = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);
					tfs_cur = tfs_cur->right_;
				}
			}

			// elseはあるか？（行スキップ）
			size_t nnread = 1;
			const n2_token_t* nn = n2_parser_read_token(state, p);
			while (nn->token_ == N2_TOKEN_EOL || nn->token_ == N2_TOKEN_EOS)
			{
				nn = n2_parser_read_token(state, p);
				++nnread;
			}

			if (n2i_token_is_keyword(nn, N2_KEYWORD_ELSE))
			{
				false_statements = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);

				const n2_token_t* nextf = n2_parser_read_token(state, p);
				if (nextf->token_ == N2_TOKEN_LBRACE)
				{
					tfs_cur = false_statements;
					for (;;)
					{
						const n2_token_t* ppf = n2_parser_prev_token(p, 1);
						if (ppf->token_ == N2_TOKEN_RBRACE)
						{
							// RBRACEは食われてた
							break;
						}
						n2_ast_node_t* statement = n2i_parser_parse_statement_safe(state, p, pc);
						if (!statement)
						{
							if (!(pc->error_))
							{
								N2I_PS_RAISE(state, nn, "ifのelse文の解析中、解析できないステートメントに到達しました");
								pc->error_ = N2_TRUE;
							}
							n2_ast_node_free(state, expr);
							n2_ast_node_free(state, true_statements);
							n2_ast_node_free(state, false_statements);
							return NULL;
						}
						N2_ASSERT(!tfs_cur->left_);
						tfs_cur->left_ = statement;
						tfs_cur->right_ = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);
						tfs_cur = tfs_cur->right_;
					}
				}
				else
				{
					n2_parser_unread_token(p, 1);
					{
						const n2_token_t* nnf = n2_parser_read_token(state, p);
						if (nnf->token_ != N2_TOKEN_EOS)
						{
							N2I_PS_RAISE(state, nnf, "ifのelse文の解析中：elseの後は { か : しか置けません");
							n2_ast_node_free(state, true_statements);
							n2_ast_node_free(state, false_statements);
							pc->error_ = N2_TRUE;
							return NULL;
						}
					}

					tfs_cur = false_statements;
					for (;;)
					{
						const n2_token_t* pp = n2_parser_prev_token(p, 1);
						if (pp->token_ == N2_TOKEN_EOL || pp->token_ == N2_TOKEN_EOF)
						{
							// EOLまたはEOFは食われてた
							n2_parser_unread_token(p, 1);
							break;
						}

						const n2_token_t* nnf = n2_parser_read_token(state, p);
						n2_parser_unread_token(p, 1);
						if (n2i_token_is_keyword(nnf, N2_KEYWORD_ELSE)) { break; }

						n2_ast_node_t* statement = n2i_parser_parse_statement_safe(state, p, pc);
						if (!statement)
						{
							if (!(pc->error_))
							{
								N2I_PS_RAISE(state, nnf, "ifのelse文の解析中、解析できないステートメントに到達しました");
								pc->error_ = N2_TRUE;
							}
							n2_ast_node_free(state, expr);
							n2_ast_node_free(state, true_statements);
							n2_ast_node_free(state, false_statements);
							return NULL;
						}
						N2_ASSERT(!tfs_cur->left_);
						tfs_cur->left_ = statement;
						tfs_cur->right_ = n2_ast_node_alloc(state, N2_AST_NODE_BLOCK_STATEMENTS, NULL, NULL);
						tfs_cur = tfs_cur->right_;
					}
				}
			}
			else
			{
				n2_parser_unread_token(p, nnread);
			}

			n2_ast_node_t* dispatcher = n2_ast_node_alloc(state, N2_AST_NODE_IF_DISPATCHER, true_statements, false_statements);
			return n2_ast_node_alloc(state, N2_AST_NODE_IF, expr, dispatcher);
		}
	case N2_KEYWORD_ELSE:
		N2I_PS_RAISE(state, ident, "パースされてないelseを検出しました");
		pc->error_ = N2_TRUE;
		return NULL;
	case N2_KEYWORD_SWITCH:
		{
			n2_ast_node_t* expr = n2_parser_parse_expression(state, p);
			if (!expr) { pc->error_ = N2_TRUE; return NULL; }
			return n2_ast_node_alloc_token(state, N2_AST_NODE_SWITCH, ident, expr);
		}
	case N2_KEYWORD_CASE:
		{
			n2_ast_node_t* expr = n2_parser_parse_expression(state, p);
			if (!expr) { pc->error_ = N2_TRUE; return NULL; }
			return n2_ast_node_alloc_token(state, N2_AST_NODE_CASE, ident, expr);
		}
	case N2_KEYWORD_DEFAULT:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_DEFAULT, ident, NULL);
	case N2_KEYWORD_SWBREAK:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_SWBREAK, ident, NULL);
	case N2_KEYWORD_SWEND:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_SWEND, ident, NULL);

	default:
		break;
	}

	n2_parser_unread_token(p, 1);
	return NULL;
}

static n2_ast_node_t* n2i_parser_parse_command_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* ident = n2_parser_read_token(state, p);
	if (ident->token_ != N2_TOKEN_IDENTIFIER && ident->token_ != N2_TOKEN_IDENTIFIER_FQ)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_token_t* next = n2_parser_read_token(state, p);

	n2_bool_t is_command = N2_TRUE;
	switch (next->token_)
	{
	case N2_TOKEN_ASSIGN:
	case N2_TOKEN_LOR_ASSIGN:
	case N2_TOKEN_LAND_ASSIGN:
	case N2_TOKEN_BOR_ASSIGN:
	case N2_TOKEN_BAND_ASSIGN:
	case N2_TOKEN_BXOR_ASSIGN:
	case N2_TOKEN_BLSHIFT_ASSIGN:
	case N2_TOKEN_BRSHIFT_ASSIGN:
	case N2_TOKEN_ADD_ASSIGN:
	case N2_TOKEN_SUB_ASSIGN:
	case N2_TOKEN_MUL_ASSIGN:
	case N2_TOKEN_DIV_ASSIGN:
	case N2_TOKEN_MOD_ASSIGN:
	case N2_TOKEN_INCREMENT:
	case N2_TOKEN_DECREMENT:
		is_command = N2_FALSE;
		break;
	default:
		break;
	}

	// "("チェック
	if (!ident->right_space_ && next->token_ == N2_TOKEN_LPARENTHESIS) { is_command = N2_FALSE; }

	if (!is_command)
	{
		n2_parser_unread_token(p, 2);
		return NULL;
	}

	size_t exflags = 0;

	// goto/gosubチェック
	if (n2i_token_is_keyword(next, N2_KEYWORD_GOTO) || n2i_token_is_keyword(next, N2_KEYWORD_GOSUB))
	{
		if (n2i_token_is_keyword(next, N2_KEYWORD_GOSUB)) { exflags |= N2_CALLSTATEFLAG_QUAL_GOSUB; }
		next = n2_parser_read_token(state, p);
	}

	// あるなら引数の解析
	n2_ast_node_t* args = NULL;
	if (!n2_token_is_eos_like(next->token_))
	{
		n2_parser_unread_token(p, 1);
		args = n2i_parser_parse_arguments(state, p);
		if (!args) { pc->error_ = N2_TRUE; return NULL; }
	}
	else
	{
		n2_parser_unread_token(p, 1);
	}

	n2_ast_node_t* res = n2_ast_node_alloc_token(state, N2_AST_NODE_COMMAND, ident, args);
	res->exflags_ = exflags;
	return res;
}

static n2_ast_node_t* n2i_parser_parse_arguments(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* res = n2_ast_node_alloc(state, N2_AST_NODE_ARGUMENTS, NULL, NULL);
	n2_ast_node_t* args = res;

	for (;;)
	{
		// 既に終わっている？
		const n2_token_t* token = n2_parser_read_token(state, p);
		if (token->token_ == N2_TOKEN_RPARENTHESIS || n2_token_is_eos_like(token->token_))
		{
			n2_parser_unread_token(p, 1);
			break;
		}

		// 引数省略
		if (token->token_ == N2_TOKEN_COMMA)
		{
			n2_ast_node_t* nextarg = n2_ast_node_alloc(state, N2_AST_NODE_ARGUMENTS_EMPTY_ARG, NULL, NULL);
			args->right_ = n2_ast_node_alloc(state, N2_AST_NODE_ARGUMENTS_PARTS, nextarg, NULL);
			args = args->right_;
			continue;
		}

		n2_parser_unread_token(p, 1);

		// 実際に値を取得
		n2_ast_node_t* nextarg = n2_parser_parse_expression(state, p);
		if (!nextarg) { n2_ast_node_free(state, args); return NULL; }
		args->right_ = n2_ast_node_alloc(state, N2_AST_NODE_ARGUMENTS_PARTS, nextarg, NULL);
		args = args->right_;

		// 一個先読みでカンマを取り除く
		const n2_token_t* ntoken = n2_parser_read_token(state, p);
		if (ntoken->token_ != N2_TOKEN_COMMA) { n2_parser_unread_token(p, 1); }
	}
	return res;
}

static n2_ast_node_t* n2i_parser_parse_incdec_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;

	const n2_token_t* nt = n2_parser_read_token(state, p);
	if (nt->token_ != N2_TOKEN_INCREMENT && nt->token_ != N2_TOKEN_DECREMENT)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	n2_ast_node_t* variable = n2i_parser_parse_variable_safe(state, p, pc);
	if (!variable)
	{
		N2I_PS_RAISE(state, nt, "++/--のあとに変数が必要です");
		pc->error_ = N2_TRUE;
		return NULL;
	}

	return n2_ast_node_alloc(state, nt->token_ == N2_TOKEN_INCREMENT ? N2_AST_NODE_INCREMENT : N2_AST_NODE_DECREMENT, variable, NULL);
}

static n2_ast_node_t* n2i_parser_parse_assign_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	n2_ast_node_t* variable = n2i_parser_parse_variable_safe(state, p, pc);
	if (!variable) { return NULL; }

	N2_ASSERT(variable->node_ == N2_AST_NODE_VARIABLE);
	const char* var_name = variable->token_->content_;

	const n2_token_t* next = n2_parser_read_token(state, p);

	n2_ast_node_e node = N2_AST_NODE_UNDEF;
	n2_bool_t can_bulk = N2_FALSE;
	n2_bool_t has_expr = N2_TRUE;
	switch (next->token_)
	{
	case N2_TOKEN_ASSIGN:			node = N2_AST_NODE_ASSIGN; can_bulk = N2_TRUE; break;
	case N2_TOKEN_LOR_ASSIGN:		node = N2_AST_NODE_LOR_ASSIGN; break;
	case N2_TOKEN_LAND_ASSIGN:		node = N2_AST_NODE_LAND_ASSIGN; break;
	case N2_TOKEN_BOR_ASSIGN:		node = N2_AST_NODE_BOR_ASSIGN; break;
	case N2_TOKEN_BAND_ASSIGN:		node = N2_AST_NODE_BAND_ASSIGN; break;
	case N2_TOKEN_BXOR_ASSIGN:		node = N2_AST_NODE_BXOR_ASSIGN; break;
	case N2_TOKEN_BLSHIFT_ASSIGN:	node = N2_AST_NODE_BLSHIFT_ASSIGN; break;
	case N2_TOKEN_BRSHIFT_ASSIGN:	node = N2_AST_NODE_BRSHIFT_ASSIGN; break;
	case N2_TOKEN_ADD_ASSIGN:		node = N2_AST_NODE_ADD_ASSIGN; break;
	case N2_TOKEN_SUB_ASSIGN:		node = N2_AST_NODE_SUB_ASSIGN; break;
	case N2_TOKEN_MUL_ASSIGN:		node = N2_AST_NODE_MUL_ASSIGN; break;
	case N2_TOKEN_DIV_ASSIGN:		node = N2_AST_NODE_DIV_ASSIGN; break;
	case N2_TOKEN_MOD_ASSIGN:		node = N2_AST_NODE_MOD_ASSIGN; break;
	case N2_TOKEN_INCREMENT:		node = N2_AST_NODE_INCREMENT; has_expr = N2_FALSE; break;
	case N2_TOKEN_DECREMENT:		node = N2_AST_NODE_DECREMENT; has_expr = N2_FALSE; break;
	default:
		N2I_PS_RAISE(state, next, "変数（%s）への代入では = が必要です ※関数呼び出しのみのステートメントは不正です", var_name);
		n2_ast_node_free(state, variable);
		pc->error_ = N2_TRUE;
		return NULL;
	}
	N2_ASSERT(node != N2_AST_NODE_UNDEF);

	n2_ast_node_t* expr = NULL;
	if (has_expr)
	{
		if (can_bulk)
		{
			expr = n2i_parser_parse_arguments(state, p);
		}
		else
		{
			expr = n2_parser_parse_expression(state, p);
		}
		if (!expr) { n2_ast_node_free(state, variable); pc->error_ = N2_TRUE; return NULL; }
	}
	n2_ast_node_t* assign = n2_ast_node_alloc(state, node, variable, expr);
	assign->token_ = next;
	return assign;
}

static n2_ast_node_t* n2i_parser_parse_variable_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;

	const n2_token_t* ident = n2_parser_read_token(state, p);
	if (ident->token_ != N2_TOKEN_IDENTIFIER && ident->token_ != N2_TOKEN_IDENTIFIER_FQ)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	// 変数そのまま
	const n2_token_t* next = n2_parser_read_token(state, p);
	if (next->token_ != N2_TOKEN_LPARENTHESIS)
	{
		n2_parser_unread_token(p, 1);
		return n2_ast_node_alloc_token(state, N2_AST_NODE_VARIABLE, ident, NULL);
	}

	n2_ast_node_t* index_args = NULL;

	const n2_token_t* nn = n2_parser_read_token(state, p);
	n2_parser_unread_token(p, 1);
	if (nn->token_ != N2_TOKEN_RPARENTHESIS)
	{
		// 引数を取得
		index_args = n2i_parser_parse_arguments(state, p);
		if (!index_args) { pc->error_ = N2_TRUE; return NULL; }
	}

	const n2_token_t* nnf = n2_parser_read_token(state, p);
	if (nnf->token_ != N2_TOKEN_RPARENTHESIS)
	{
		N2I_PS_RAISE(state, nnf, "配列変数 : 括弧が正しく閉じられていません");
		n2_ast_node_free(state, index_args);
		pc->error_ = N2_TRUE;
		return NULL;
	}

	return n2_ast_node_alloc_token(state, N2_AST_NODE_VARIABLE, ident, index_args);
}

static n2_ast_node_t* n2i_parser_parse_thenelse(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = NULL;
	n2_ast_node_t* cur = NULL;

	for (;;)
	{
		n2_ast_node_t* cond = n2i_parser_parse_lorand(state, p);
		if (!cond) { goto fail_exit; }

		if (cur)
		{
			N2_ASSERT(cur->node_ == N2_AST_NODE_CONDITIONAL);
			N2_ASSERT(cur->right_ && cur->right_->node_ == N2_AST_NODE_CONDITIONAL_PARTS);
			N2_ASSERT(cur->right_->left_ && !cur->right_->right_);
			cur->right_->right_ = cond;
		}

		const n2_token_t* token = n2_parser_read_token(state, p);
		if (!n2i_token_is_keyword(token, N2_KEYWORD_THEN))
		{
			if (!node) { node = cond; }
			n2_parser_unread_token(p, 1);
			break;
		}

		n2_ast_node_t* ncur = n2_ast_node_alloc(state, N2_AST_NODE_CONDITIONAL, cond, n2_ast_node_alloc(state, N2_AST_NODE_CONDITIONAL_PARTS, NULL, NULL));
		if (cur)
		{
			N2_ASSERT(cur->right_->right_ == cond);
			cur->right_->right_ = ncur;
			cur = ncur;
		}
		else
		{
			N2_ASSERT(!node);
			node = cur = ncur;
		}

		n2_ast_node_t* l = n2i_parser_parse_lorand(state, p);
		if (!l)
		{
			N2I_PS_RAISE(state, token, "then の次項の解析が出来ません");
			goto fail_exit;
		}

		N2_ASSERT(cur->right_ && !cur->right_->left_);
		cur->right_->left_ = l;

		const n2_token_t* elsetoken = n2_parser_read_token(state, p);
		if (!n2i_token_is_keyword(elsetoken, N2_KEYWORD_ELSE))
		{
			N2I_PS_RAISE(state, elsetoken, "then の後に else がありません。");
			goto fail_exit;
		}

		// 末尾再起と同じ感じでループさせる。左結合じゃなくて右結合なので、ちょっと複雑だがこうする
	}
	goto do_exit;

fail_exit:
	if (node) { n2_ast_node_free(state, node); node = NULL; }
do_exit:
	return node;
}

static n2_ast_node_t* n2i_parser_parse_lorand(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_borand(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_LOR:
		case N2_TOKEN_OP_LAND:
			{
				n2_ast_node_t* r = n2i_parser_parse_borand(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "||,&&の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_LOR:	node = n2_ast_node_alloc(state, N2_AST_NODE_LOR, node, r); break;
				case N2_TOKEN_OP_LAND:	node = n2_ast_node_alloc(state, N2_AST_NODE_LAND, node, r); break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_borand(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_eqneq(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_BOR:
		case N2_TOKEN_OP_BAND:
		case N2_TOKEN_OP_BXOR:
			{
				n2_ast_node_t* r = n2i_parser_parse_eqneq(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "|,&の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_BOR:	node = n2_ast_node_alloc(state, N2_AST_NODE_BOR, node, r); break;
				case N2_TOKEN_OP_BAND:	node = n2_ast_node_alloc(state, N2_AST_NODE_BAND, node, r); break;
				case N2_TOKEN_OP_BXOR:	node = n2_ast_node_alloc(state, N2_AST_NODE_BXOR, node, r); break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_eqneq(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_gtlt(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_EQ:
		case N2_TOKEN_OP_NEQ:
		case N2_TOKEN_OP_NOT:
		case N2_TOKEN_ASSIGN:
			{
				n2_ast_node_t* r = n2i_parser_parse_gtlt(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "==,!=の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_EQ:
				case N2_TOKEN_ASSIGN:
					node = n2_ast_node_alloc(state, N2_AST_NODE_EQ, node, r);
					break;
				case N2_TOKEN_OP_NEQ:
				case N2_TOKEN_OP_NOT:
					node = n2_ast_node_alloc(state, N2_AST_NODE_NEQ, node, r);
					break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_gtlt(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_bshift(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_GT:
		case N2_TOKEN_OP_GTOE:
		case N2_TOKEN_OP_LT:
		case N2_TOKEN_OP_LTOE:
			{
				n2_ast_node_t* r = n2i_parser_parse_bshift(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, ">,>=,<,<=の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_GT:	node = n2_ast_node_alloc(state, N2_AST_NODE_GT, node, r); break;
				case N2_TOKEN_OP_GTOE:	node = n2_ast_node_alloc(state, N2_AST_NODE_GTOE, node, r); break;
				case N2_TOKEN_OP_LT:	node = n2_ast_node_alloc(state, N2_AST_NODE_LT, node, r); break;
				case N2_TOKEN_OP_LTOE:	node = n2_ast_node_alloc(state, N2_AST_NODE_LTOE, node, r); break;
				default: N2_ASSERT(0); break;
				}
				break;
			}
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_bshift(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_addsub(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_BLSHIFT:
		case N2_TOKEN_OP_BRSHIFT:
			{
				n2_ast_node_t* r = n2i_parser_parse_addsub(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "<<,>>の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_BLSHIFT:	node = n2_ast_node_alloc(state, N2_AST_NODE_BLSHIFT, node, r); break;
				case N2_TOKEN_OP_BRSHIFT:	node = n2_ast_node_alloc(state, N2_AST_NODE_BRSHIFT, node, r); break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_addsub(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_muldivmod(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_ADD:
		case N2_TOKEN_OP_SUB:
			{
				n2_ast_node_t* r = n2i_parser_parse_muldivmod(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "+,-の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_ADD:	node = n2_ast_node_alloc(state, N2_AST_NODE_ADD, node, r); break;
				case N2_TOKEN_OP_SUB:	node = n2_ast_node_alloc(state, N2_AST_NODE_SUB, node, r); break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_muldivmod(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = n2i_parser_parse_term(state, p);
	if (!node) { return NULL; }

	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_MUL:
		case N2_TOKEN_OP_DIV:
		case N2_TOKEN_OP_MOD:
			{
				n2_ast_node_t* r = n2i_parser_parse_term(state, p);
				if (!r)
				{
					N2I_PS_RAISE(state, token, "*,/,\\の演算子で、右項の解析が出来ません");
					n2_ast_node_free(state, node);
					return NULL;
				}

				switch (token->token_)
				{
				case N2_TOKEN_OP_MUL:	node = n2_ast_node_alloc(state, N2_AST_NODE_MUL, node, r); break;
				case N2_TOKEN_OP_DIV:	node = n2_ast_node_alloc(state, N2_AST_NODE_DIV, node, r); break;
				case N2_TOKEN_OP_MOD:	node = n2_ast_node_alloc(state, N2_AST_NODE_MOD, node, r); break;
				default: N2_ASSERT(0); break;
				}
			}
			break;
		default:
			is_continue = N2_FALSE;
			break;
		}
		if (!is_continue)
		{
			n2_parser_unread_token(p, 1);
			break;
		}
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_term(n2_state_t* state, n2_parser_t* p)
{
	n2_ast_node_t* node = NULL;
	n2_ast_node_t* cur = NULL;
	for (;;)
	{
		n2_bool_t is_continue = N2_TRUE;
		const n2_token_t* token = n2_parser_read_token(state, p);
		switch (token->token_)
		{
		case N2_TOKEN_OP_NOT:
		case N2_TOKEN_OP_SUB:
			{
				n2_ast_node_t* next = NULL;
				switch (token->token_)
				{
				case N2_TOKEN_OP_NOT: next = n2_ast_node_alloc_token(state, N2_AST_NODE_UNARY_NOT, token, NULL); break;
				case N2_TOKEN_OP_SUB: next = n2_ast_node_alloc_token(state, N2_AST_NODE_UNARY_MINUS, token, NULL); break;
				default: N2_ASSERT(0); break;
				}
				N2_ASSERT(next);
				if (cur) { N2_ASSERT(node); cur->left_ = next; cur = next; }
				else { N2_ASSERT(!node); node = cur = next; }
			}
			break;
		default:
			is_continue = N2_FALSE;
			n2_parser_unread_token(p, 1);
			break;
		}
		if (!is_continue) { break; }
	}

	n2_ast_node_t* prim = n2i_parser_parse_primitive(state, p);
	if (prim)
	{
		if (cur) { N2_ASSERT(node); cur->left_ = prim; }
		else { node = prim; }
	}
	else
	{
		n2_ast_node_free(state, node);
		node = NULL;
	}
	return node;
}

static n2_ast_node_t* n2i_parser_parse_primitive(n2_state_t* state, n2_parser_t* p)
{
	const n2_token_t* token = n2_parser_read_token(state, p);
	switch (token->token_)
	{
	case N2_TOKEN_LPARENTHESIS:
		{
			n2_ast_node_t* node = n2_parser_parse_expression(state, p);
			if (!node) { return NULL; }
			const n2_token_t* next = n2_parser_read_token(state, p);
			if (next->token_ != N2_TOKEN_RPARENTHESIS)
			{
				N2I_PS_RAISE(state, token, "括弧が閉じられていません");
				return NULL;
			}
			return n2_ast_node_alloc(state, N2_AST_NODE_EXPRESSION, node, NULL);
		}

	case N2_TOKEN_NIL:
	case N2_TOKEN_INT:
	case N2_TOKEN_HEXINT:
	case N2_TOKEN_FLOAT:
	case N2_TOKEN_STRING:
	case N2_TOKEN_CHAR:
		return n2_ast_node_alloc_token(state, N2_AST_NODE_PRIMITIVE_VALUE, token, NULL);

	case N2_TOKEN_TEMPLATE_STRING:
		{
			n2_ast_node_t* node = n2_ast_node_alloc_token(state, N2_AST_NODE_TEMPLATE_STRING, token, NULL);
			n2_ast_node_t* ncur = node;
			for (;;)
			{
				n2_ast_node_t* exp = n2_parser_parse_expression(state, p);
				if (!exp) { n2_ast_node_free(state, node); return NULL; }
				const n2_token_t* next = n2_parser_read_token(state, p);
				N2_ASSERT(!ncur->left_);
				ncur->left_ = exp;
				if (next->token_ == N2_TOKEN_STRING) { ncur->right_ = n2_ast_node_alloc_token(state, N2_AST_NODE_TEMPLATE_STRING_PARTS, next, NULL); break; }
				if (next->token_ != N2_TOKEN_TEMPLATE_STRING)
				{
					N2I_PS_RAISE(state, next, "テンプレート文字列の組み込み式を正しく解釈できません");
					n2_ast_node_free(state, node);
					return NULL;
				}
				N2_ASSERT(!ncur->right_);
				ncur->right_ = n2_ast_node_alloc_token(state, N2_AST_NODE_TEMPLATE_STRING_PARTS, next, NULL);
				ncur = ncur->right_;
			}
			return node;
		}

	case N2_TOKEN_OP_MUL:
		{
			n2_parser_unread_token(p, 1);
			n2i_parse_context_t pc;
			n2i_parse_context_init(&pc);
			n2_ast_node_t* label = n2i_parser_parse_label_safe(state, p, &pc, N2_TRUE);
			if (!label || pc.error_)
			{
				N2I_PS_RAISE(state, token, "ラベルが正しく解析できませんでした");
				return NULL;
			}
			return label;
		}

	case N2_TOKEN_IDENTIFIER:
	case N2_TOKEN_IDENTIFIER_FQ:
		{
			n2_parser_unread_token(p, 1);
			n2i_parse_context_t pc;
			n2i_parse_context_init(&pc);
			n2_ast_node_t* expr = n2i_parser_parse_identifier_expression_safe(state, p, &pc);
			if (!expr)
			{
				if (!pc.error_) { N2I_PS_RAISE(state, token, "関数または変数を正しく解析できませんでした"); }
				return NULL;
			}
			return expr;
		}
	default: break;
	}

	N2I_PS_RAISE(state, token, "プリミティブな値を取得できません");
	return NULL;
}

static n2_ast_node_t* n2i_parser_parse_identifier_expression_safe(n2_state_t* state, n2_parser_t* p, n2i_parse_context_t* pc)
{
	pc->error_ = N2_FALSE;
	const n2_token_t* ident = n2_parser_read_token(state, p);
	if (ident->token_ != N2_TOKEN_IDENTIFIER && ident->token_ != N2_TOKEN_IDENTIFIER_FQ)
	{
		n2_parser_unread_token(p, 1);
		return NULL;
	}

	const n2_token_t* next = n2_parser_read_token(state, p);
	if (next->token_ != N2_TOKEN_LPARENTHESIS)
	{
		n2_parser_unread_token(p, 1);
		return n2_ast_node_alloc_token(state, N2_AST_NODE_IDENTIFIER_EXPR, ident, NULL);
	}

	// 引数なしの即閉じ？
	{
		const n2_token_t* nn = n2_parser_read_token(state, p);
		if (nn->token_ == N2_TOKEN_RPARENTHESIS)
		{
			return n2_ast_node_alloc_token(state, N2_AST_NODE_IDENTIFIER_EXPR, ident, n2_ast_node_alloc(state, N2_AST_NODE_ARGUMENTS, NULL, NULL) );
		}
		n2_parser_unread_token(p, 1);
	}

	// 引数あり
	n2_ast_node_t* index = n2i_parser_parse_arguments(state, p);
	if (!index) { pc->error_ = N2_TRUE; return NULL; }

	const n2_token_t* nn = n2_parser_read_token(state, p);
	if (nn->token_ != N2_TOKEN_RPARENTHESIS)
	{
		N2I_PS_RAISE(state, nn, "関数または配列変数 : 括弧が正しく閉じられていません");
		n2_ast_node_free(state, index);
		pc->error_ = N2_TRUE;
		return NULL;
	}

	return n2_ast_node_alloc_token(state, N2_AST_NODE_IDENTIFIER_EXPR, ident, index);
}

static void n2i_parserarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_parser_free(state, *N2_RCAST(n2_parser_t**, element));
}
N2_DEFINE_TARRAY(n2_parser_t*, n2_parserarray, N2_API, n2i_setupfunc_nothing, n2i_parserarray_freefunc);

//=============================================================================
// シンボル

static void n2i_symbol_init(n2_symbol_t* symbol)
{
	symbol->id_ = SIZE_MAX;
	n2_str_init(&symbol->name_);
}

static void n2i_symbol_teardown(n2_state_t* state, n2_symbol_t* symbol)
{
	n2_str_teardown(state, &symbol->name_);
}

static void n2i_symbolarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_symbol_t* symbol = N2_RCAST(n2_symbol_t*, element);
	n2i_symbol_teardown(state, symbol);
}
N2_DEFINE_TARRAY(n2_symbol_t, n2_symbolarray, N2_API, n2i_setupfunc_nothing, n2i_symbolarray_freefunc);

static int n2i_symbolindexmap_name_cmpfunc(const n2_sorted_array_t* a, const void* lsymbolkey, const void* rsymbolkey, const void* key)
{
	N2_UNUSE(key);
	n2_symboltable_t* symboltable = N2_RCAST(n2_symboltable_t*, a->a_.user_);
	N2_ASSERT(symboltable);
	const int* lindex = N2_RCAST(const int*, lsymbolkey);
	const int* rindex = N2_RCAST(const int*, rsymbolkey);
	n2_symbol_t* lsymbol = n2_symbolarray_peek(symboltable->symbolarray_, *lindex);
	n2_symbol_t* rsymbol = n2_symbolarray_peek(symboltable->symbolarray_, *rindex);
	if (!lsymbol->name_.str_ || !rsymbol->name_.str_) { return (lsymbol->name_.str_ == rsymbol->name_.str_ ? 0 : lsymbol->name_.str_ ? 1 : -1); }
	return n2_plstr_cmp_case(lsymbol->name_.str_, rsymbol->name_.str_);
}

static int n2i_symbolindexmap_name_matchfunc(const n2_sorted_array_t* a, const void* symbolkey, const void* key)
{
	n2_symboltable_t* symboltable = N2_RCAST(n2_symboltable_t*, a->a_.user_);
	N2_ASSERT(symboltable);
	const int* symbolindex = N2_RCAST(const int*, symbolkey);
	n2_symbol_t* symbol = n2_symbolarray_peek(symboltable->symbolarray_, *symbolindex);
	const char* name = N2_RCAST(const char*, key);
	if (!symbol->name_.str_ || !name) { return -1; }
	return n2_plstr_cmp_case(symbol->name_.str_, name);
}

static void n2i_symbolindexmap_setupfunc(n2_state_t* state, n2_symbolindexmap_t* symbolindexmap)
{
	N2_UNUSE(state);
	symbolindexmap->cmp_ = n2i_symbolindexmap_name_cmpfunc;
	symbolindexmap->match_ = n2i_symbolindexmap_name_matchfunc;
}

static void n2i_symbolindexmap_postalloc(n2_state_t* state, n2_symboltable_t* symboltable)
{
	N2_UNUSE(state);
	symboltable->symbolindexmap_->a_.user_ = symboltable;
}
N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_symbolindexmap, N2_API, n2i_symbolindexmap_setupfunc, n2i_freefunc_nothing);

N2_API n2_symboltable_t* n2_symboltable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step)
{
	n2_symboltable_t* symboltable = N2_TMALLOC(n2_symboltable_t, state);
	if (!symboltable) { return NULL; }
	symboltable->symbolarray_ = n2_symbolarray_alloc(state, initial_buffer_size, expand_step);
	symboltable->symbolindexmap_ = n2_symbolindexmap_alloc(state, initial_buffer_size, expand_step);
	n2i_symbolindexmap_postalloc(state, symboltable);
	return symboltable;
}

N2_API void n2_symboltable_free(n2_state_t* state, n2_symboltable_t* symboltable)
{
	n2_symbolindexmap_free(state, symboltable->symbolindexmap_);
	n2_symbolarray_free(state, symboltable->symbolarray_);
	n2_free(state, symboltable);
}

N2_API n2_symbol_t* n2_symboltable_peek(n2_symboltable_t* symboltable, int index)
{
	return n2_symbolarray_peek(symboltable->symbolarray_, index);
}

N2_API n2_symbol_t* n2_symboltable_find(n2_symboltable_t* symboltable, const char* name)
{
	if (!name) { return NULL; }
	int* index = n2_symbolindexmap_find(symboltable->symbolindexmap_, name);
	if (!index) { return NULL; }
	return n2_symbolarray_peek(symboltable->symbolarray_, *index);
}

N2_API int n2_symboltable_register(n2_state_t* state, n2_symboltable_t* symboltable, const char* name)
{
	n2_symbol_t* symbol = NULL;
	if (name) { symbol = n2_symboltable_find(symboltable, name); }
	if (!symbol)
	{
		n2_symbol_t tsymbol;
		n2i_symbol_init(&tsymbol);
		if (name) { n2_str_set(state, &tsymbol.name_, name, SIZE_MAX); }
		int symbolindex = N2_SCAST(int, n2_symbolarray_size(symboltable->symbolarray_));
		symbol = n2_symbolarray_push(state, symboltable->symbolarray_, &tsymbol);
		if (name) { n2_symbolindexmap_insert(state, symboltable->symbolindexmap_, &symbolindex, symbol->name_.str_); }
	}

	return n2_symbolarray_compute_index(symboltable->symbolarray_, symbol);
}

//=============================================================================
// ハンドリング
N2_API void n2_error_param_init(n2_error_param_t* error_param)
{
	error_param->state_ = NULL;
	error_param->error_ = N2_ERROR_NONE;
	error_param->sourcecode_ = NULL;
	error_param->package_ = NULL;
	error_param->message_ = NULL;
	error_param->subdescription_ = NULL;
	error_param->line_ = -1;
	error_param->column_ = -1;
	error_param->fiber_ = NULL;
}

//=============================================================================
// デバッガーフック
static void n2i_debughook_init(n2_debughook_t* debughook, n2_environment_t* e)
{
	debughook->pollfunc_ = NULL;
	debughook->breakstopfunc_ = NULL;
	debughook->errorstopfunc_ = NULL;
	debughook->finfunc_ = NULL;
	debughook->user_ = NULL;

	debughook->poll_per_operation_ = 100;

	debughook->attached_environment_ = e;

	debughook->icounter_poll_operation_ = 0;
}

N2_API void n2_debughook_free(n2_state_t* state, n2_debughook_t* debughook)
{
	if (debughook->finfunc_) { debughook->finfunc_(state, debughook); }
	n2_free(state, debughook);
}

static void n2i_debugvariable_init(n2_debugvariable_t* debugvar)
{
	n2_list_node_init(&debugvar->entry_);
	debugvar->id_ = 0;
	debugvar->type_ = N2_DEBUGVARIABLE_NONE;
}

static void n2i_debugvariable_teardown(n2_state_t* state, n2_debugvariable_t* debugvar)
{
	N2_UNUSE(state);
	n2_list_node_unlink(&debugvar->entry_);
}

N2_API n2_debugvariable_t* n2_debugvariable_alloc(n2_state_t* state)
{
	n2_debugvariable_t* debugvar = N2_TMALLOC(n2_debugvariable_t, state);
	if (!debugvar) { return NULL; }
	n2i_debugvariable_init(debugvar);
	return debugvar;
}

N2_API void n2_debugvariable_free(n2_state_t* state, n2_debugvariable_t* debugvar)
{
	n2i_debugvariable_teardown(state, debugvar);
	n2_free(state, debugvar);
}

static void n2i_debugvararray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	n2_debugvariable_t* debugvar = *N2_RCAST(n2_debugvariable_t**, element);
	// ユーザーポインタが設定されているなら
	if (a->user_)
	{
		// この配列の要素はそのpoolへ返却
		n2_debugvarpool_t* pool = N2_RCAST(n2_debugvarpool_t*, a->user_);
		n2_debugvarpool_push(state, pool, debugvar);
		return;
	}
	// 直接破棄
	n2i_debugvariable_teardown(state, debugvar);
}
N2_DEFINE_TARRAY(n2_debugvariable_t*, n2_debugvararray, N2_API, n2i_setupfunc_nothing, n2i_debugvararray_freefunc);

N2_API void n2_debugvararray_autoresize(n2_state_t* state, n2_debugvararray_t* a, size_t size)
{
	n2_debugvararray_reserve(state, a, size);
	n2_debugvarpool_t* debugvarpool = N2_RCAST(n2_debugvarpool_t*, a->user_);
	if (a->size_ < size)
	{
		while (a->size_ < size)
		{
			n2_debugvariable_t* debugvar = NULL;
			if (debugvarpool) { debugvar = n2_debugvarpool_pop_or_alloc(state, debugvarpool); }
			else { debugvar = n2_debugvariable_alloc(state); }
			n2_debugvararray_pushv(state, a, debugvar);
		}
	}
	else if (a->size_ > size)
	{
		n2_debugvararray_resize(state, a, size, NULL);
	}
}

static int n2i_debugvarset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	const n2_debugvariable_t* lvar = *N2_RCAST(const n2_debugvariable_t**, lkey);
	const n2_debugvariable_t* rvar = *N2_RCAST(const n2_debugvariable_t**, rkey);
	return N2_THREE_WAY_CMP(lvar->id_, rvar->id_);
}
static int n2i_debugvarset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	const n2_debugvariable_t* var = *N2_RCAST(const n2_debugvariable_t**, ekey);
	const size_t* idkey = N2_RCAST(const size_t*, key);
	return N2_THREE_WAY_CMP(var->id_, *idkey);
}
static void n2i_debugvarset_setupfunc(n2_state_t* state, n2_modfuncindexset_t* modfuncs)
{
	N2_UNUSE(state);
	modfuncs->cmp_ = n2i_debugvarset_cmpfunc;
	modfuncs->match_ = n2i_debugvarset_matchfunc;
}
static void n2i_debugvarset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	// 何もしない（これはただのポインタ）
	N2_UNUSE(state);
	N2_UNUSE(a);
	N2_UNUSE(element);
	//n2i_debugvararray_freefunc(state, a, element);
}
N2_DEFINE_TSORTED_ARRAY(n2_debugvariable_t*, void, size_t, n2_debugvarset, N2_API, n2i_debugvarset_setupfunc, n2i_debugvarset_freefunc);

static void n2i_debugvarpool_list_node_free_func(n2_state_t* state, n2_list_t* l, n2_list_node_t* node)
{
	N2_UNUSE(l);
	n2_debugvariable_t* debugvar = N2_RCAST(n2_debugvariable_t*, node);
	n2_debugvariable_free(state, debugvar);
}

N2_API n2_debugvarpool_t* n2_debugvarpool_alloc(n2_state_t* state, size_t initial_pool_size)
{
	n2_debugvarpool_t* debugvarpool = N2_TMALLOC(n2_debugvarpool_t, state);
	debugvarpool->debugvars_ = n2_debugvarset_alloc(state, 0, 256);
	n2_list_init(&debugvarpool->debugvar_pool_);
	debugvarpool->next_id_ = 0;
	// 初期個数
	for (size_t i = 0; i < initial_pool_size; ++i)
	{
		n2_debugvariable_t* debugvar = n2_debugvariable_alloc(state);
		debugvar->id_ = debugvarpool->next_id_++;
		n2_list_append(&debugvarpool->debugvar_pool_, &debugvar->entry_);
	}
	return debugvarpool;
}

N2_API void n2_debugvarpool_free(n2_state_t* state, n2_debugvarpool_t* debugvarpool)
{
	n2_debugvarset_free(state, debugvarpool->debugvars_);
	n2_list_clear_free(state, &debugvarpool->debugvar_pool_, n2i_debugvarpool_list_node_free_func);
	n2_free(state, debugvarpool);
}

N2_API n2_debugvariable_t* n2_debugvarpool_pop_or_alloc(n2_state_t* state, n2_debugvarpool_t* debugvarpool)
{
	// キャッシュ（先頭から）
	n2_debugvariable_t* debugvar = N2_RCAST(n2_debugvariable_t*, n2_list_shift(&debugvarpool->debugvar_pool_));
	if (!debugvar)
	{
		// 無いなら作る
		debugvar = n2_debugvariable_alloc(state);
		debugvar->id_ = debugvarpool->next_id_++;
	}
	// 使用リストへ
	n2_debugvarset_insert(state, debugvarpool->debugvars_, N2_RCAST(const n2_debugvariable_t**, &debugvar), NULL);
	return debugvar;
}

N2_API void n2_debugvarpool_push(n2_state_t* state, n2_debugvarpool_t* debugvarpool, n2_debugvariable_t* debugvar)
{
	N2_UNUSE(state);
	// 未使用タイプへ
	debugvar->type_ = N2_DEBUGVARIABLE_NONE;
	// 使用リストから外す
	n2_debugvarset_erase(state, debugvarpool->debugvars_, &debugvar->id_);
	// キャッシュ（末尾へ）
	n2_list_append(&debugvarpool->debugvar_pool_, &debugvar->entry_);
}

//=============================================================================
// 変数
static const size_t n2i_variable_nlength[N2_VARIABLE_DIM] = {0};
static const size_t n2i_variable_onelength[N2_VARIABLE_DIM] = {1, 0, 0, 0};

static size_t n2i_variable_compute_element_num(const size_t length[N2_VARIABLE_DIM])
{
	if (length[0] <= 0) { return 0; }
	size_t num = 1;
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i)
	{
		if (length[i] <= 0) { break; }
		num *= length[i];
	}
	return num;
}

static size_t n2i_variable_compute_element_num_indim(const size_t length[N2_VARIABLE_DIM], size_t indim)
{
	if (length[0] <= 0) { return 0; }
	N2_ASSERT(indim <= N2_VARIABLE_DIM);
	size_t num = 1;
	for (size_t i = 0; i < indim; ++i)
	{
		if (length[i] <= 0) { break; }
		num *= length[i];
	}
	return num;
}

static void n2i_variable_setup(n2_state_t* state, n2_environment_t* e, n2_variable_t* var, const char* name)
{
	N2_UNUSE(e);
	var->name_ = NULL;
	if (name) { var->name_ = n2_plstr_clone(state, name); }
	var->type_ = N2_VALUE_NIL;
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { var->length_[i] = 0; }
	var->data_ = NULL;
	var->data_buffer_size_ = 0;
	var->element_num_ = 0;
	var->element_size_ = 0;
	var->granule_size_ = 0;
	var->module_id_ = -1;
#if N2_CONFIG_USE_DEBUGGING
	var->debugvarpool_ = NULL;
	var->debugvarroot_ = NULL;
	if (state->config_.generate_debugvars_)
	{
		var->debugvarpool_ = e->debugvarpool_;
		var->debugvarroot_ = n2_debugvarpool_pop_or_alloc(state, e->debugvarpool_);
		var->debugvarroot_->type_ = N2_DEBUGVARIABLE_VARIABLE_ROOT;
		var->debugvarroot_->v_.var_root_ = var;
	}
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { n2_debugvararray_setup_user(state, &var->debugvardims_[i], 0, 0, e->debugvarpool_); }
	n2_debugvararray_setup_user(state, &var->debugvarelements_, 0, 0, e->debugvarpool_);
#endif
}

static void n2i_variable_clean(n2_state_t* state, n2_variable_t* var)
{
	switch (var->type_)
	{
	case N2_VALUE_STRING:
		for (size_t i = 0; i < var->element_num_; ++i)
		{
			n2_valstr_t* s = N2_RCAST(n2_valstr_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
			n2_str_teardown(state, s);
		}
		break;
	case N2_VALUE_MODINST:
		for (size_t i = 0; i < var->element_num_; ++i)
		{
			n2_valmodinst_t* instance = N2_RCAST(n2_valmodinst_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
			if (instance->instance_) { n2_modinstance_decref(state, instance->instance_); }
			instance->instance_ = NULL;
		}
		break;
	default:
		break;
	}
}

static void n2i_variable_teardown(n2_state_t* state, n2_variable_t* var)
{
#if N2_CONFIG_USE_DEBUGGING
	if (var->debugvarroot_) { n2_debugvarpool_push(state, var->debugvarpool_, var->debugvarroot_); var->debugvarroot_ = NULL; }
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { n2_debugvararray_teardown(state, &var->debugvardims_[i]); }
	n2_debugvararray_teardown(state, &var->debugvarelements_);
	var->debugvarroot_ = NULL;
#endif
	n2_variable_clear(state, var);
	if (var->name_) { n2_free(state, var->name_); }
}

static uint8_t n2i_variable_init_value(n2_value_e type)
{
	uint8_t init = 0;
	switch(type)
	{
	case N2_VALUE_LABEL:	init = 0xff; break;
	default:				break;
	}
	return init;
}

N2_API n2_variable_t* n2_variable_alloc(n2_state_t* state, n2_environment_t* e, const char* name)
{
	n2_variable_t* const var = N2_TMALLOC(n2_variable_t, state);
	if (!var) { return NULL; }

	n2i_variable_setup(state, e, var, name);
	n2_variable_prepare(state, var, N2_VALUE_INT, state->config_.variable_granule_size_, n2i_variable_nlength);
	return var;
}

N2_API void n2_variable_free(n2_state_t* state, n2_variable_t* var)
{
	N2_ASSERT(var);
	n2i_variable_teardown(state, var);
	n2_free(state, var);
}

N2_API void n2_variable_prepare(n2_state_t* state, n2_variable_t* var, n2_value_e type, size_t granule_size, const size_t length[N2_VARIABLE_DIM])
{
	N2_ASSERT(var);

	// @todo reuse data memory

	n2_variable_clear(state, var);

	var->type_ = type;

	// ストライドの決定
	switch(var->type_)
	{
	case N2_VALUE_NIL:
		var->element_size_ = 0;
		granule_size = 0;
		break;
	case N2_VALUE_INT:
		var->element_size_ = sizeof(n2_valint_t);
		granule_size = 0;
		break;
	case N2_VALUE_FLOAT:
		var->element_size_ = sizeof(n2_valfloat_t);
		granule_size = 0;
		break;
	case N2_VALUE_STRING:
		var->element_size_ = sizeof(n2_valstr_t);
		break;
	case N2_VALUE_LABEL:
		var->element_size_ = sizeof(n2_vallabel_t);
		break;
	case N2_VALUE_MODINST:
		var->element_size_ = sizeof(n2_valmodinst_t);
		break;
	case N2_VALUE_VARIABLE:
		var->element_size_ = sizeof(n2_valvar_t);
		granule_size = 0;
		break;
	default:
		N2_ASSERT(0);
		break;
	}
	N2_ASSERT(var->element_size_ <= N2_MAX_VARIABLE_ELEMENT_SIZE);

	const uint8_t init = n2i_variable_init_value(var->type_);

	// 最終粒度確保
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { var->length_[i] = (i == 0 || length[i - 1] > 0/*0は伝搬*/) ? length[i] : 0; };
	if (var->length_[0] <= 0 && var->element_size_ > 0)
	{
		for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { var->length_[i] = 0; };
		var->length_[0] = var->type_ == N2_VALUE_STRING ? state->config_.variable_str_element_min_num_ : state->config_.variable_element_min_num_;
	}
	var->element_num_ = n2i_variable_compute_element_num(var->length_);

	// 確保データサイズが決まったので色々する
	const size_t areasize = var->element_size_ * var->element_num_;
	if (areasize > 0)
	{
		var->data_ = n2_malloc(state, areasize);
	}
	var->data_buffer_size_ = areasize;

	// 初期化
	if (var->data_)
	{
		N2_MEMSET(var->data_, init, var->data_buffer_size_);
	}

	// 更に追加で確保する分
	var->granule_size_ = granule_size;
	if (var->granule_size_ > 0)
	{
		switch (var->type_)
		{
		case N2_VALUE_STRING:
			for (size_t i = 0; i < var->element_num_; ++i)
			{
				n2_valstr_t* s = N2_RCAST(n2_valstr_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
				n2_str_reserve(state, s, var->granule_size_);
			}
			break;
		default:
			break;
		}
	}

	// デバッグ用変数の確保
	n2_variable_ensure_debugvariables(state, var, 0);
}

N2_API void n2_variable_redim(n2_state_t* state, n2_variable_t* var, const size_t length[N2_VARIABLE_DIM])
{
	N2_ASSERT(var);

	const size_t nelement_num = n2i_variable_compute_element_num(length);

	// 再配置
	if (nelement_num == var->element_num_)
	{
		for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { var->length_[i] = length[i]; }
		return;
	}

	const size_t oldareasize = var->element_size_ * var->element_num_;
	const size_t nareasize = var->element_size_ * nelement_num;
	const uint8_t init = n2i_variable_init_value(var->type_);

	if (nelement_num > var->element_num_)
	{
		// 拡大
		var->data_ = n2_realloc(state, nareasize, var->data_, var->data_buffer_size_);

		// 初期化
		N2_MEMSET(n2_ptr_offset(var->data_, oldareasize), init,  nareasize - oldareasize);

		if (var->granule_size_ > 0)
		{
			switch (var->type_)
			{
			case N2_VALUE_STRING:
				for (size_t i = var->element_num_; i < nelement_num; ++i)
				{
					n2_valstr_t* s = N2_RCAST(n2_valstr_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
					n2_str_reserve(state, s, var->granule_size_);
				}
				break;
			default:
				break;
			}
		}

		var->data_buffer_size_ = nareasize;
	}
	else
	{
		// 縮小
		switch (var->type_)
		{
		case N2_VALUE_STRING:
			for (size_t i = nelement_num; i < var->element_num_; ++i)
			{
				n2_valstr_t* s = N2_RCAST(n2_valstr_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
				n2_str_teardown(state, s);
			}
			break;
		case N2_VALUE_MODINST:
			for (size_t i = nelement_num; i < var->element_num_; ++i)
			{
				n2_valmodinst_t* instance = N2_RCAST(n2_valmodinst_t*, n2_ptr_offset(var->data_, var->element_size_ * i));
				if (instance->instance_) { n2_modinstance_decref(state, instance->instance_); }
				instance->instance_ = NULL;
			}
			break;
		default:
			break;
		}
	}
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { var->length_[i] = length[i]; }
	var->element_num_ = nelement_num;

	// デバッグ用変数の確保
	n2_variable_ensure_debugvariables(state, var, 0);
}

N2_API void n2_variable_clear(n2_state_t* state, n2_variable_t* var)
{
	N2_ASSERT(var);

	n2i_variable_clean(state, var);

	var->type_ = N2_VALUE_NIL;
	for (size_t i = 0, l = N2_ARRAYDIM(var->length_); i < l; ++i) { var->length_[i] = 0; }
	var->element_num_ = 0;
	var->element_size_ = 0;
	var->granule_size_ = 0;
	if (var->data_) { n2_free(state, var->data_); }
	var->data_ = NULL;
	var->data_buffer_size_ = 0;
}

N2_API n2_bool_t n2_variable_set(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	N2_ASSERT(val);
	if (var->type_ != val->type_)
	{
		if (aptr > 0)
		{
			n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への代入< %s(%d)", var->name_, aptr);
			return N2_FALSE;
		}
		n2_variable_prepare(state, var, val->type_, state->config_.variable_granule_size_, n2i_variable_nlength);
	}

	n2_bool_t init_required = N2_FALSE;

	size_t granule_size = 0;
	if (val->type_ == N2_VALUE_STRING)
	{
		granule_size = N2_MAX(state->config_.variable_granule_size_, val->field_.svalue_.size_ + 1);
	}

	if (aptr == -1) { aptr = 0; }
	if (aptr < 0)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数の配列で負の添え字は無効です< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}
	// 自動拡張を試す
	if (N2_SCAST(size_t, aptr) == var->element_num_ && var->length_[1] == 0)// 1次元のみ
	{
		size_t length[N2_VARIABLE_DIM];
		for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { length[i] = var->length_[i]; }
		++length[0];
		n2_variable_redim(state, var, length);
	}
	if (N2_SCAST(size_t, aptr) >= var->element_num_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数の配列範囲外への代入です< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	if (init_required)
	{
		n2_variable_prepare(state, var, val->type_, granule_size, var->length_);
	}

	N2_ASSERT(var->type_ == val->type_);

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) = val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		*N2_RCAST(n2_valfloat_t*, data_ptr) = val->field_.fvalue_;
		break;
	case N2_VALUE_STRING:
		n2_str_set(state, N2_RCAST(n2_valstr_t*, data_ptr), val->field_.svalue_.str_, val->field_.svalue_.size_);
		break;
	case N2_VALUE_LABEL:
		*N2_RCAST(n2_vallabel_t*, data_ptr) = val->field_.labelvalue_;
		break;
	case N2_VALUE_MODINST:
		*N2_RCAST(n2_valmodinst_t*, data_ptr) = val->field_.modvalue_;
		break;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_bor(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数へのOR代入（|=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) |= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に対するOR代入（|=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するOR代入（|=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するOR代入（|=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するOR代入（|=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_band(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数へのAND代入（&=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) &= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に対するAND代入（&=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するAND代入（&=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するAND代入（&=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するAND代入（&=）操作は定義されてません< %s(%d)", var->name_, aptr);
		break;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_bxor(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数へのXOR代入（^=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) ^= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に対するXOR代入（^=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するXOR代入（^=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するXOR代入（^=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するXOR代入（^=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_blshift(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数へのLSHIFT代入（<<=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) <<= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に対するLSHIFT代入（<<=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するLSHIFT代入（<<=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するLSHIFT代入（<<=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するLSHIFT代入（<<=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_brshift(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数へのRSHIFT代入（>>=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) >>= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に対するRSHIFT代入（>>=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するRSHIFT代入（>>=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するRSHIFT代入（>>=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するRSHIFT代入（>>=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_add(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への加算代入（+=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) += val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		*N2_RCAST(n2_valfloat_t*, data_ptr) += val->field_.fvalue_;
		break;
	case N2_VALUE_STRING:
		{
			n2_valstr_t* varstr = N2_RCAST(n2_valstr_t*, data_ptr);
			n2_str_update_size(varstr);
			n2_str_append(state, varstr, val->field_.svalue_.str_, SIZE_MAX);
		}
		break;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対する加算代入（+=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対する加算代入（+=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_sub(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への減算代入（-=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) -= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		*N2_RCAST(n2_valfloat_t*, data_ptr) -= val->field_.fvalue_;
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対する減算代入（-=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対する減算代入（-=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対する減算代入（-=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_mul(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への乗算代入（*=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		*N2_RCAST(n2_valint_t*, data_ptr) *= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		*N2_RCAST(n2_valfloat_t*, data_ptr) *= val->field_.fvalue_;
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対する乗算代入（*=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対する乗算代入（*=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対する乗算代入（*=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_div(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への除算代入（/=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		if (val->field_.ivalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0除算が行われました< %s(%d)", var->name_, aptr); return N2_FALSE; }
		*N2_RCAST(n2_valint_t*, data_ptr) /= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		if (val->field_.fvalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0除算が行われました< %s(%d)", var->name_, aptr); return N2_FALSE; }
		*N2_RCAST(n2_valfloat_t*, data_ptr) /= val->field_.fvalue_;
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_mod(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val)
{
	N2_ASSERT(var);
	if (var->type_ != val->type_)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "型の異なる変数への剰余代入（\\=）操作< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	}

	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:
		if (val->field_.ivalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0剰余が行われました< %s(%d)", var->name_, aptr); return N2_FALSE; }
		*N2_RCAST(n2_valint_t*, data_ptr) %= val->field_.ivalue_;
		break;
	case N2_VALUE_FLOAT:
		if (val->field_.fvalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0剰余が行われました< %s(%d)", var->name_, aptr); return N2_FALSE; }
		*N2_RCAST(n2_valfloat_t*, data_ptr) = N2_FMOD(*N2_RCAST(n2_valfloat_t*, data_ptr), val->field_.fvalue_);
		break;
	case N2_VALUE_STRING:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対する除算代入（/=）操作は定義されてません< %s(%d)", var->name_, aptr);
		return N2_FALSE;
	default:
		N2_ASSERT(0);
		break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_increment(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr)
{
	N2_ASSERT(var);
	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:		++(*N2_RCAST(n2_valint_t*, data_ptr)); break;
	case N2_VALUE_FLOAT:	(*N2_RCAST(n2_valfloat_t*, data_ptr)) += N2_SCAST(n2_valfloat_t, 1); break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するインクリメント（++）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するインクリメント（++）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するインクリメント（++）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	default:				N2_ASSERT(0); break;
	}
	return N2_TRUE;
}

N2_API n2_bool_t n2_variable_decrement(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr)
{
	N2_ASSERT(var);
	void* data_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_INT:		--(*N2_RCAST(n2_valint_t*, data_ptr)); break;
	case N2_VALUE_FLOAT:	(*N2_RCAST(n2_valfloat_t*, data_ptr)) -= N2_SCAST(n2_valfloat_t, 1); break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に対するデクリメント（--）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに対するデクリメント（--）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール変数に対するデクリメント（--）操作は定義されてません< %s(%d)", var->name_, aptr); return N2_FALSE;
	default:				N2_ASSERT(0); break;
	}
	return N2_TRUE;
}

N2_API size_t n2_variable_compute_dimension_num(const size_t length[N2_VARIABLE_DIM])
{
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i)
	{
		if (length[i] <= 0) { return i; }
	}
	return N2_VARIABLE_DIM;
}

N2_API int n2_variable_compute_aptr_indim(const n2_variable_t* var, const size_t indices[N2_VARIABLE_DIM], size_t indim)
{
	N2_ASSERT(indim <= N2_VARIABLE_DIM);
	int aptr = 0;
	for (size_t i = 0, l = N2_MIN(indim, N2_VARIABLE_DIM); i < l; ++i)
	{
		if (var->length_[i] <= 0) { break; }
		if (i > 0) { aptr *= N2_SCAST(int, var->length_[i]); }
		aptr += N2_SCAST(int, indices[i]);
	}
	return aptr;
}

N2_API int n2_variable_compute_aptr(const n2_variable_t* var, const size_t indices[N2_VARIABLE_DIM])
{
	return n2_variable_compute_aptr_indim(var, indices, N2_VARIABLE_DIM);
}

N2_API void n2_variable_compute_dimension_indices_indim(size_t dst_length[N2_VARIABLE_DIM], size_t element_index, const size_t length[N2_VARIABLE_DIM], size_t indim)
{
	N2_ASSERT(indim <= N2_VARIABLE_DIM);
	for (size_t i = 0; i < N2_VARIABLE_DIM; ++i) { dst_length[i] = 0; }
	if (indim <= 0) { return; }
	int i = N2_SCAST(int, indim) - 1;
	for (; i >= 0; --i)
	{
		if (length[i] <= 0) { dst_length[i] = 0; continue; }
		dst_length[i] = element_index % length[i];
		element_index /= length[i];
	}
}

N2_API void n2_variable_compute_dimension_indices(size_t dst_length[N2_VARIABLE_DIM], size_t element_index, const size_t length[N2_VARIABLE_DIM])
{
	n2_variable_compute_dimension_indices_indim(dst_length, element_index, length, N2_VARIABLE_DIM);
}

N2_API void* n2_variable_element_ptr(const n2_variable_t* var, int aptr)
{
	if (!var || !var->data_) { return NULL; }
	N2_ASSERT(aptr >= -1 && aptr < N2_SCAST(int, var->element_num_));
	aptr = N2_MAX(0, aptr);
	const int offset = N2_SCAST(int, var->element_size_) * aptr;
	N2_ASSERT(offset >= 0 && offset < N2_SCAST(int, var->data_buffer_size_));
	return n2_ptr_offset(var->data_, offset);
}

N2_API size_t n2_variable_element_size(const n2_variable_t* var, int aptr)
{
	const void* element = n2_variable_element_ptr(var, aptr);
	if (!element) { return 0; }

	size_t data_size = 0;
	switch (var->type_)
	{
	case N2_VALUE_STRING:	data_size = N2_RCAST(const n2_valstr_t*, element)->buffer_size_; break;
	default:				data_size = var->element_size_; break;
	}
	return data_size;
}

N2_API size_t n2_variable_left_buffer_size(const n2_variable_t* var, int aptr)
{
	const void* element = n2_variable_element_ptr(var, aptr);
	if (!element) { return 0; }

	size_t data_size = 0;
	switch (var->type_)
	{
	case N2_VALUE_INT:
	case N2_VALUE_FLOAT:
		// opaque types
		data_size = var->data_buffer_size_ - N2_SCAST(size_t, n2_ptr_diff(element, var->data_));
		break;
	case N2_VALUE_STRING:	data_size = N2_MAX(N2_RCAST(const n2_valstr_t*, element)->buffer_size_, 1) - 1/*without null temrmination*/; break;
	default:				break;
	}
	return data_size;
}

N2_API void* n2_variable_map_data(size_t* data_size, const n2_variable_t* var, int aptr)
{
	void* element = n2_variable_element_ptr(var, aptr);
	if (!element) { return NULL; }

	void* data = NULL;
	switch (var->type_)
	{
	case N2_VALUE_INT:
	case N2_VALUE_FLOAT:
		data = element;
		break;
	case N2_VALUE_STRING:
		{
			n2_valstr_t* str = N2_RCAST(n2_valstr_t*, element);
			data = str->str_;
		}
		break;
	default:
		break;
	}
	if (data_size) { *data_size = n2_variable_left_buffer_size(var, aptr); }
	return data;
}

N2_API void n2_variable_unmap_data(const n2_variable_t* var, int aptr)
{
#if 0
	if (!var->data_) { return; }
	void* element = n2_variable_element_ptr(var, aptr);
	if (!element) { return; }
	switch (var->type_)
	{
	case N2_VALUE_STRING:
		{
			n2_valstr_t* str = N2_RCAST(n2_valstr_t*, element);
			n2_str_update_size(str);
		}
		break;
	default:
		break;
	}
#else
	N2_UNUSE(var);
	N2_UNUSE(aptr);
#endif
}

N2_API n2_valint_t n2_variable_eval_int(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr)
{
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_NIL:		return 0;
	case N2_VALUE_INT:		return *N2_RCAST(const n2_valint_t*, element_ptr);
	case N2_VALUE_FLOAT:	return N2_SCAST(int, *N2_RCAST(const n2_valfloat_t*, element_ptr));
	case N2_VALUE_STRING:	return N2_SCAST(n2_valint_t, N2_STRTOLL(N2_RCAST(const n2_valstr_t*, element_ptr)->str_, NULL, 0));
	default:				if (f) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "整数に変換できない型です"); } break;
	}
	return 0;
}

N2_API n2_valfloat_t n2_variable_eval_float(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr)
{
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_NIL:		return 0;
	case N2_VALUE_INT:		return N2_SCAST(n2_valfloat_t, *N2_RCAST(const n2_valint_t*, element_ptr));
	case N2_VALUE_FLOAT:	return *N2_RCAST(const n2_valfloat_t*, element_ptr);
	case N2_VALUE_STRING:	return N2_SCAST(n2_valfloat_t, N2_STRTOD(N2_RCAST(const n2_valstr_t*, element_ptr)->str_, NULL));
	default:				if (f) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "実数に変換できない型です"); } break;
	}
	return 0;
}

N2_API const char* n2_variable_get_plstr(const n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_STRING) { return NULL; }
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(const n2_valstr_t*, element_ptr)->str_;
}

N2_API n2_valstr_t* n2_variable_get_str(n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_STRING) { return NULL; }
	void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(n2_valstr_t*, element_ptr);
}

N2_API const n2_valstr_t* n2_variable_get_strc(const n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_STRING) { return NULL; }
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(const n2_valstr_t*, element_ptr);
}

N2_API n2_valstr_t* n2_variable_eval_str(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr)
{
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	switch (var->type_)
	{
	case N2_VALUE_NIL:		return n2_str_alloc_fmt(state, "nil");
	case N2_VALUE_INT:		return n2_str_alloc_fmt(state, "%" N2_VALINT_PRI, *N2_RCAST(const n2_valint_t*, element_ptr));
	case N2_VALUE_FLOAT:	return n2_str_alloc_fmt(state, "%" N2_VALFLOAT_PRI, *N2_RCAST(const n2_valfloat_t*, element_ptr));
	case N2_VALUE_STRING:	return n2_str_clone(state, N2_RCAST(const n2_valstr_t*, element_ptr));
	default:				if (f) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に変換できない型です"); } break;
	}
	return n2_str_alloc_fmt(state, "");
}

N2_API const n2_vallabel_t* n2_variable_get_label(const n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_LABEL) { return NULL; }
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(const n2_vallabel_t*, element_ptr);
}

N2_API n2_valmodinst_t* n2_variable_get_modinst(n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_MODINST) { return NULL; }
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(n2_valmodinst_t*, element_ptr);
}

N2_API const n2_valmodinst_t* n2_variable_get_modinstc(const n2_variable_t* var, int aptr)
{
	if (var->type_ != N2_VALUE_MODINST) { return NULL; }
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	return N2_RCAST(const n2_valmodinst_t*, element_ptr);
}

N2_API void n2_variable_inspect(n2_state_t* state, n2_environment_t* e, n2_str_t* dst, const n2_variable_t* var, int aptr)
{
	const void* element_ptr = n2_variable_element_ptr(var, aptr);
	if (!element_ptr) { n2_str_set(state, dst, "(out of boundary)", SIZE_MAX); return; }
	switch (var->type_)
	{
	case N2_VALUE_NIL:		n2_str_set(state, dst, "nil", SIZE_MAX); return;
	case N2_VALUE_INT:		n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, *N2_RCAST(const n2_valint_t*, element_ptr)); return;
	case N2_VALUE_FLOAT:	n2_str_fmt_to(state, dst, "%" N2_VALFLOAT_PRI, *N2_RCAST(const n2_valfloat_t*, element_ptr)); return;
	case N2_VALUE_STRING:
		{
			const n2_valstr_t* str = N2_RCAST(const n2_valstr_t*, element_ptr);
			n2_str_fmt_to(state, dst, "\"%.*s\"", str->size_, str->str_);
		}
		return;
	case N2_VALUE_LABEL:
		{
			const n2_vallabel_t* vallabel = N2_RCAST(const n2_vallabel_t*, element_ptr);
			const n2_label_t* label = vallabel->label_index_ >= 0 ? n2_labelarray_peek(e->labels_, vallabel->label_index_) : NULL;
			n2_str_fmt_to(state, dst, "(label *%s)", label ? label->name_ : "<unknown>");
		}
		return;
	case N2_VALUE_MODINST:
		{
			const n2_valmodinst_t* valmodinst = N2_RCAST(const n2_valmodinst_t*, element_ptr);
			if (valmodinst->instance_)
			{
				const n2_module_t* emodule = valmodinst->instance_ && valmodinst->instance_->module_id_ >= 0 ? n2_moduletable_peek(e->moduletable_, valmodinst->instance_->module_id_) : NULL;
				n2_str_fmt_to(state, dst, "(mod %s:%p)", emodule ? emodule->name_ : "<unknown>", valmodinst->instance_);
			}
			else
			{
				n2_str_fmt_to(state, dst, "(mod <null>)");
			}
		}
		return;
	default:				break;
	}
	n2_str_set(state, dst, "(unknown)", SIZE_MAX);
}

N2_API void n2_variable_ensure_debugvariables(n2_state_t* state, n2_variable_t* var, size_t dim)
{
#if N2_CONFIG_USE_DEBUGGING
	if (!state->config_.generate_debugvars_) { return; }

	const size_t using_dims = n2_variable_compute_dimension_num(var->length_);
	const size_t ensure_dim = N2_MIN(dim, using_dims);
	if (ensure_dim > 0)
	{
		for (size_t i = 0, l = N2_MIN(ensure_dim, using_dims - 1/*最後の次元用のは要らない*/); i < l; ++i)
		{
			n2_debugvararray_t* debugvararray = &var->debugvardims_[i];
			if (var->length_[i] > 0)
			{
				const size_t elements_indim = n2i_variable_compute_element_num_indim(var->length_, i + 1);
				const size_t curr_element_num = n2_debugvararray_size(debugvararray);
				if (curr_element_num != elements_indim)
				{
					n2_debugvararray_autoresize(state, debugvararray, elements_indim);
					for (size_t j = 0; j < elements_indim; ++j)
					{
						n2_debugvariable_t* debugvar = n2_debugvararray_peekv(debugvararray, N2_SCAST(int, j), NULL);
						debugvar->type_ = N2_DEBUGVARIABLE_VARIABLE_DIMENSION;
						debugvar->v_.var_dimension_.var_ = var;
						debugvar->v_.var_dimension_.dimension_index_ = i;
						n2_variable_compute_dimension_indices_indim(debugvar->v_.var_dimension_.dimension_, j, var->length_, i + 1);
					}
				}
			}
			else
			{
				n2_debugvararray_clear(state, debugvararray);
			}
		}

		{
			const size_t elements_indim = n2i_variable_compute_element_num_indim(var->length_, ensure_dim);
			const size_t curr_element_num = n2_debugvararray_size(&var->debugvarelements_);
			if (curr_element_num < elements_indim)
			{
				n2_debugvararray_autoresize(state, &var->debugvarelements_, elements_indim);
				for (size_t i = curr_element_num; i < elements_indim; ++i)
				{
					n2_debugvariable_t* debugvar = n2_debugvararray_peekv(&var->debugvarelements_, N2_SCAST(int, i), NULL);
					debugvar->type_ = N2_DEBUGVARIABLE_VARIABLE_ELEMENT;
					debugvar->v_.var_element_.var_ = var;
					debugvar->v_.var_element_.element_index_ = i;
				}
			}
		}
	}
#else
	N2_UNUSE(state);
	N2_UNUSE(var);
	N2_UNUSE(dim);
#endif
}

static void n2i_vararray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_variable_t* var = *N2_RCAST(n2_variable_t**, element);
	n2_variable_free(state, var);
}

static int n2i_varindexmap_name_cmpfunc(const n2_sorted_array_t* a, const void* lvarkey, const void* rvarkey, const void* key)
{
	N2_UNUSE(key);
	n2_vartable_t* vartable = N2_RCAST(n2_vartable_t*, a->a_.user_);
	N2_ASSERT(vartable);
	const int* lindex = N2_RCAST(const int*, lvarkey);
	const int* rindex = N2_RCAST(const int*, rvarkey);
	n2_variable_t* lvar = n2_vararray_peekv(&vartable->vararray_, *lindex, NULL);
	n2_variable_t* rvar = n2_vararray_peekv(&vartable->vararray_, *rindex, NULL);
	if (!lvar->name_ || !rvar->name_) { return (lvar->name_ == rvar->name_ ? 0 : lvar->name_ ? 1 : -1); }
	return N2_STRCMP(lvar->name_, rvar->name_);
}

static int n2i_varindexmap_name_matchfunc(const n2_sorted_array_t* a, const void* varkey, const void* key)
{
	n2_vartable_t* vartable = N2_RCAST(n2_vartable_t*, a->a_.user_);
	N2_ASSERT(vartable);
	const int* varindex = N2_RCAST(const int*, varkey);
	n2_variable_t* var = n2_vararray_peekv(&vartable->vararray_, *varindex, NULL);
	const char* name = N2_RCAST(const char*, key);
	if (!var->name_ || !name) { return -1; }
	return N2_STRCMP(var->name_, name);
}

static void n2i_varindexmap_setupfunc(n2_state_t* state, n2_varindexmap_t* varindexmap)
{
	N2_UNUSE(state);
	varindexmap->cmp_ = n2i_varindexmap_name_cmpfunc;
	varindexmap->match_ = n2i_varindexmap_name_matchfunc;
}

static void n2i_varindexmap_postalloc(n2_state_t* state, n2_vartable_t* vartable)
{
	N2_UNUSE(state);
	vartable->varindexmap_->a_.user_ = vartable;
}

N2_DEFINE_TARRAY(n2_variable_t*, n2_vararray, N2_API, n2i_setupfunc_nothing, n2i_vararray_freefunc);
N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_varindexmap, N2_API, n2i_varindexmap_setupfunc, n2i_freefunc_nothing);

static n2_variable_t** n2i_vartable_findp(n2_vartable_t* vartable, const char* name)
{
	if (!name) { return NULL; }
	int* index = n2_varindexmap_find(vartable->varindexmap_, name);
	if (!index) { return NULL; }
	return n2_vararray_peek(&vartable->vararray_, *index);
}

N2_API n2_vartable_t* n2_vartable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step)
{
	n2_vartable_t* vartable = N2_TMALLOC(n2_vartable_t, state);
	if (!vartable) { return vartable; }
	n2_vararray_setup(state, &vartable->vararray_, initial_buffer_size, expand_step);
	vartable->varindexmap_ = n2_varindexmap_alloc(state, initial_buffer_size, expand_step);
	n2i_varindexmap_postalloc(state, vartable);
	return vartable;
}

N2_API void n2_vartable_free(n2_state_t* state, n2_vartable_t* vartable)
{
	n2_varindexmap_free(state, vartable->varindexmap_);
	n2_vararray_teardown(state, &vartable->vararray_);
	n2_free(state, vartable);
}

N2_API n2_variable_t* n2_vartable_peek(n2_vartable_t* vartable, int index)
{
	return n2_vararray_peekv(&vartable->vararray_, index, NULL);
}

N2_API n2_variable_t* n2_vartable_find(n2_vartable_t* vartable, const char* name)
{
	n2_variable_t** pvar = n2i_vartable_findp(vartable, name);
	return pvar ? *pvar : NULL;
}

N2_API int n2_vartable_register(n2_state_t* state, n2_environment_t* e, n2_vartable_t* vartable, const char* name)
{
	n2_variable_t** pvar = NULL;
	if (name) { pvar = n2i_vartable_findp(vartable, name); }
	if (!pvar)
	{
		const int varindex = N2_SCAST(int, n2_vararray_size(&vartable->vararray_));
		pvar = n2_vararray_push(state, &vartable->vararray_, NULL);
		*pvar = n2_variable_alloc(state, e, name);
		if (name) { n2_varindexmap_insert(state, vartable->varindexmap_, &varindex, (*pvar)->name_); }
	}

	return n2_vararray_compute_index(&vartable->vararray_, pvar);
}

N2_API size_t n2_vartable_size_named(const n2_vartable_t* vartable)
{
	return n2_varindexmap_size(vartable->varindexmap_);
}

N2_API n2_variable_t* n2_vartable_peek_named(n2_vartable_t* vartable, int index)
{
	const int* arrayindex = n2_varindexmap_peekc(vartable->varindexmap_, index);
	if (!arrayindex) { return NULL; }
	return n2_vartable_peek(vartable, *arrayindex);
}

//=============================================================================
// 値

static const struct
{
	n2_value_e type_;
	const char* name_;
}
n2i_value_type_table[] = {
	{N2_VALUE_NIL,		"nil"},
	{N2_VALUE_LABEL,	"label"},
	{N2_VALUE_STRING,	"str"},
	{N2_VALUE_FLOAT,	"double"},
	{N2_VALUE_INT,		"int"},
	{N2_VALUE_MODINST,	"modinst"},
	{N2_VALUE_VARIABLE,	"variable"},
	{-1,				NULL}
};

static const struct
{
	n2_value_e type_;
	const char* name_;
}
n2i_value_type_table_ex[] = {
	{N2_VALUE_MODINST,	"struct"},
	{-1,				NULL}
};

N2_API const char* n2_valuetype_name(const n2_value_e value, const char* on_failed)
{
	if (value >= 0 && value < N2_MAX_VALUE) { return n2i_value_type_table[value].name_; }
	return on_failed;
}

N2_API int n2_valuetype_find(const char* name, n2_bool_t include_ex)
{
	for (size_t i = 0; n2i_value_type_table[i].name_; ++i)
	{
		if (N2_STRCMP(name, n2i_value_type_table[i].name_) == 0) { return n2i_value_type_table[i].type_; }
	}
	if (include_ex)
	{
		for (size_t i = 0; n2i_value_type_table_ex[i].name_; ++i)
		{
			if (N2_STRCMP(name, n2i_value_type_table_ex[i].name_) == 0) { return n2i_value_type_table_ex[i].type_; }
		}
	}
	return -1;
}

static n2_value_t* n2i_value_alloc(n2_state_t* state)
{
	if (state->value_cache_ && state->value_cache_left_ > 0)
	{
		return state->value_cache_[--state->value_cache_left_];
	}
	return N2_TMALLOC(n2_value_t, state);
}

static void n2i_value_free(n2_state_t* state, n2_value_t* val)
{
	if (state->value_cache_ && state->value_cache_left_ < state->config_.value_cache_size_)
	{
		state->value_cache_[state->value_cache_left_++] = val;
		return;
	}
	n2_free(state, val);
}

static void n2i_value_init(n2_value_t* val)
{
	val->type_ = N2_VALUE_NIL;
}

static void n2i_value_teardown(n2_state_t* state, n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_STRING:
		n2_str_teardown(state, &val->field_.svalue_);
		break;
	case N2_VALUE_MODINST:
		if (val->field_.modvalue_.instance_)
		{
			n2_modinstance_decref(state, val->field_.modvalue_.instance_);
		}
		break;
	default:
		break;
	}

	val->type_ = N2_VALUE_NIL;
}

N2_API n2_value_t* n2_value_allocnil(n2_state_t* state)
{
	n2_value_t* val = n2i_value_alloc(state);
	n2i_value_init(val);
	return val;
}

N2_API n2_value_t* n2_value_alloci(n2_state_t* state, n2_valint_t v)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_INT;
	val->field_.ivalue_ = v;
	return val;
}

N2_API n2_value_t* n2_value_allocf(n2_state_t* state, n2_valfloat_t v)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_FLOAT;
	val->field_.fvalue_ = v;
	return val;
}

N2_API n2_value_t* n2_value_allocs(n2_state_t* state, n2_valstr_t* v)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_STRING;
	val->field_.svalue_ = *v;
	n2_str_init(v);
	return val;
}

N2_API n2_value_t* n2_value_allocl(n2_state_t* state, int labelindex)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_LABEL;
	val->field_.labelvalue_.label_index_ = labelindex;
	return val;
}

N2_API n2_value_t* n2_value_allocvar(n2_state_t* state, n2_variable_t* var, int aptr)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_VARIABLE;
	val->field_.varvalue_.var_ = var;
	val->field_.varvalue_.aptr_ = aptr;
	return val;
}

N2_API n2_value_t* n2_value_allocmodinst(n2_state_t* state, n2_modinstance_t* instance)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = N2_VALUE_MODINST;
	val->field_.modvalue_.instance_ = instance;
	return val;
}

N2_API n2_value_t* n2_value_clone(n2_state_t* state, const n2_value_t* rval)
{
	n2_value_t* val = n2i_value_alloc(state);
	val->type_ = rval->type_;
	switch (rval->type_)
	{
	case N2_VALUE_NIL:			break;
	case N2_VALUE_INT:			val->field_.ivalue_ = rval->field_.ivalue_; break;
	case N2_VALUE_FLOAT:		val->field_.fvalue_ = rval->field_.fvalue_; break;
	case N2_VALUE_STRING:		n2_str_init(&val->field_.svalue_); n2_str_copy_to(state, &val->field_.svalue_, &rval->field_.svalue_); break;
	case N2_VALUE_LABEL:		val->field_.labelvalue_ = rval->field_.labelvalue_; break;
	case N2_VALUE_MODINST:		val->field_.modvalue_ = rval->field_.modvalue_; if (val->field_.modvalue_.instance_) { n2_modinstance_incref(state, val->field_.modvalue_.instance_); } break;
	case N2_VALUE_VARIABLE:		val->field_.varvalue_ = rval->field_.varvalue_; break;
	default:					N2_ASSERT(0); val->type_ = N2_VALUE_NIL; break;
	}
	return val;
}

N2_API void n2_value_free(n2_state_t* state, n2_value_t* val)
{
	n2i_value_teardown(state, val);
	n2i_value_free(state, val);
}

N2_API void n2_value_swap(n2_value_t* lhs, n2_value_t* rhs)
{
	const n2_value_t t = *lhs;
	*lhs = *rhs;
	*rhs = t;
}

N2_API void n2_value_seti(n2_state_t* state, n2_value_t* val, n2_valint_t v)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_INT;
	val->field_.ivalue_ = v;
}

N2_API void n2_value_setf(n2_state_t* state, n2_value_t* val, n2_valfloat_t v)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_FLOAT;
	val->field_.fvalue_ = v;
}

N2_API void n2_value_sets(n2_state_t* state, n2_value_t* val, const char* v, size_t length)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_STRING;
	n2_str_init(&val->field_.svalue_);
	n2_str_set(state, &val->field_.svalue_, v, length);
}

N2_API void n2_value_replaces(n2_state_t* state, n2_value_t* val, n2_valstr_t* v)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_STRING;
	val->field_.svalue_ = *v;
	n2_str_init(v);
}

N2_API void n2_value_setl(n2_state_t* state, n2_value_t* val, const n2_vallabel_t* v)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_LABEL;
	val->field_.labelvalue_ = *v;
}

N2_API void n2_value_setvar(n2_state_t* state, n2_value_t* val, n2_variable_t* var, int aptr)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_VARIABLE;
	val->field_.varvalue_.var_ = var;
	val->field_.varvalue_.aptr_ = aptr;
}

N2_API void n2_value_setmodinstance(n2_state_t* state, n2_value_t* val, n2_modinstance_t* instance)
{
	n2i_value_teardown(state, val);
	val->type_ = N2_VALUE_MODINST;
	val->field_.modvalue_.instance_ = instance;
}

N2_API n2_value_e n2_value_get_type(const n2_value_t* val)
{
	if (val->type_ == N2_VALUE_VARIABLE) { return val->field_.varvalue_.var_->type_; }
	return val->type_;
}

N2_API n2_bool_t n2_value_eval_bool(n2_state_t* state, n2_fiber_t* f,const n2_value_t* val)
{
	switch (n2_value_get_type(val))
	{
	case N2_VALUE_NIL:			return N2_FALSE;
	case N2_VALUE_INT:			return n2_value_eval_int(state, f, val) != 0;
	case N2_VALUE_FLOAT:		return n2_value_eval_float(state, f, val) != 0;
	case N2_VALUE_STRING:		return n2_value_eval_int(state, f, val) != 0;
	case N2_VALUE_LABEL:		return n2_value_get_label(val)->label_index_ >= 0;
	case N2_VALUE_MODINST:		return n2_value_get_modinstc(val)->instance_ != NULL;
	default:					N2_ASSERT(0); break;
	}
	return N2_FALSE;
}

N2_API n2_valint_t n2_value_eval_int(n2_state_t* state, n2_fiber_t* f,const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_NIL:			return 0;
	case N2_VALUE_INT:			return val->field_.ivalue_;
	case N2_VALUE_FLOAT:		return N2_SCAST(n2_valint_t, val->field_.fvalue_);
	case N2_VALUE_STRING:		return N2_SCAST(n2_valint_t, N2_STRTOLL(val->field_.svalue_.str_, NULL, 0));
	case N2_VALUE_VARIABLE:		return n2_variable_eval_int(state, f, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	case N2_VALUE_LABEL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル型は整数へ変換できません"); break;
	case N2_VALUE_MODINST:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール型は整数へ変換できません"); break;
	default:					N2_ASSERT(0); break;
	}
	return 0;
}

N2_API n2_valfloat_t n2_value_eval_float(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_NIL:			return 0;
	case N2_VALUE_INT:			return N2_SCAST(n2_valfloat_t, val->field_.ivalue_);
	case N2_VALUE_FLOAT:		return val->field_.fvalue_;
	case N2_VALUE_STRING:		return N2_SCAST(n2_valfloat_t, N2_STRTOD(val->field_.svalue_.str_, NULL));
	case N2_VALUE_VARIABLE:		return n2_variable_eval_float(state, f, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	case N2_VALUE_LABEL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル型は実数へ変換できません"); break;
	case N2_VALUE_MODINST:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール型は実数へ変換できません"); break;
	default:					N2_ASSERT(0); break;
	}
	return 0;
}

N2_API const char* n2_value_get_plstr(const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_STRING:		return val->field_.svalue_.str_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_plstr(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API n2_valstr_t* n2_value_get_str(n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_STRING:		return &val->field_.svalue_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_str(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API const n2_valstr_t* n2_value_get_strc(const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_STRING:		return &val->field_.svalue_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_strc(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API n2_valstr_t* n2_value_eval_str(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_NIL:			return n2_str_alloc_fmt(state, "nil");
	case N2_VALUE_INT:			return n2_str_alloc_fmt(state, "%" N2_VALINT_PRI, val->field_.ivalue_);
	case N2_VALUE_FLOAT:		return n2_str_alloc_fmt(state, "%" N2_VALFLOAT_PRI, val->field_.fvalue_);
	case N2_VALUE_STRING:		return n2_str_clone(state, &val->field_.svalue_);
	case N2_VALUE_VARIABLE:		return n2_variable_eval_str(state, f, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	case N2_VALUE_LABEL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル型は文字列へ変換できません"); break;
	case N2_VALUE_MODINST:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール型は文字列へ変換できません"); break;
	default:					N2_ASSERT(0); break;
	}
	return NULL;
}

N2_API const n2_vallabel_t* n2_value_get_label(const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_LABEL:		return &val->field_.labelvalue_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_label(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API n2_valmodinst_t* n2_value_get_modinst(n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_MODINST:		return &val->field_.modvalue_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_modinst(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API const n2_valmodinst_t* n2_value_get_modinstc(const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_MODINST:		return &val->field_.modvalue_;
	case N2_VALUE_VARIABLE:		return n2_variable_get_modinstc(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	default:					break;
	}
	return NULL;
}

N2_API const n2_value_t* n2_value_eval_as(n2_state_t* state, n2_fiber_t* f, n2_value_e to, const n2_value_t* src, n2_value_t** will_free)
{
	N2_ASSERT(will_free);

	if (to == src->type_)
	{
		*will_free = NULL;
		return src;
	}

	n2_value_t* val = NULL;
	switch (to)
	{
	case N2_VALUE_NIL:		n2i_value_teardown(state, val); break;
	case N2_VALUE_INT:		val = n2_value_alloci(state, n2_value_eval_int(state, f, src)); break;
	case N2_VALUE_FLOAT:	val = n2_value_allocf(state, n2_value_eval_float(state, f, src)); break;
	case N2_VALUE_STRING:
		{
			n2_valstr_t* s = n2_value_eval_str(state, f, src);
			val = n2_value_allocs(state, s);
			n2_free(state, s);
		}
		break;
	case N2_VALUE_LABEL:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル型へ変換できません");
		break;
	case N2_VALUE_MODINST:
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール型へ変換できません");
		break;
	default:				N2_ASSERT(0); break;
	}
	*will_free = val;
	return val;
}

N2_API void n2_value_isolate(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, n2_bool_t nil_to_int)
{
	if (val->type_ != N2_VALUE_VARIABLE)
	{
		if (nil_to_int && val->type_ == N2_VALUE_NIL) { n2_value_seti(state, val, 0); }
		return;
	}

	switch (val->field_.varvalue_.var_->type_)
	{
	case N2_VALUE_NIL:
		if (nil_to_int) { n2_value_seti(state, val, 0); }
		break;
	case N2_VALUE_INT:
		n2_value_seti(state, val, n2_variable_eval_int(state, f, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_));
		break;
	case N2_VALUE_FLOAT:
		n2_value_setf(state, val, n2_variable_eval_float(state, f, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_));
		break;
	case N2_VALUE_STRING:
		n2_value_sets(state, val, n2_variable_get_str(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_)->str_, SIZE_MAX);
		break;
	case N2_VALUE_LABEL:
		n2_value_setl(state, val, n2_variable_get_label(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_));
		break;
	case N2_VALUE_MODINST:
		{
			n2_modinstance_t* instance = n2_variable_get_modinst(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_)->instance_;
			if (instance) { n2_modinstance_incref(state, instance); }
			n2_value_setmodinstance(state, val, instance);
		}
		break;
	default:
		N2_ASSERT(0);
		break;
	}
}

N2_API n2_bool_t n2_value_bor(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の|演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ | trhs->field_.ivalue_); break;
	case N2_VALUE_FLOAT:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "浮動小数点同士の|演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の|演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の|演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の|演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_band(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の&演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ & trhs->field_.ivalue_); break;
	case N2_VALUE_FLOAT:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "浮動小数点同士の&演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の&演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の&演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の&演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_bxor(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の^演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ ^ trhs->field_.ivalue_); break;
	case N2_VALUE_FLOAT:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "浮動小数点同士の^演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の^演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の^演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の^演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_eq(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2_value_seti(state, val, 1); break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ == trhs->field_.ivalue_ ? 1 : 0); break;
	case N2_VALUE_FLOAT:	n2_value_seti(state, val, val->field_.fvalue_ == trhs->field_.fvalue_ ? 1 : 0); break;
	case N2_VALUE_STRING:	n2_value_seti(state, val, N2_STRCMP(val->field_.svalue_.str_, trhs->field_.svalue_.str_) == 0 ? 1 : 0); break;
	case N2_VALUE_LABEL:	n2_value_seti(state, val, val->field_.labelvalue_.label_index_ == trhs->field_.labelvalue_.label_index_ ? 1 : 0); break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の等号関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_neq(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	if (!n2_value_eq(state, f, val, rhs)) { return N2_FALSE; }
	N2_ASSERT(val->type_ == N2_VALUE_INT);
	val->field_.ivalue_ = (val->field_.ivalue_ ? 0 : 1);
	return N2_TRUE;
}

N2_API n2_bool_t n2_value_gt(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ > trhs->field_.ivalue_ ? 1 : 0); break;
	case N2_VALUE_FLOAT:	n2_value_seti(state, val, val->field_.fvalue_ > trhs->field_.fvalue_ ? 1 : 0); break;
	case N2_VALUE_STRING:	n2_value_seti(state, val, N2_STRCMP(val->field_.svalue_.str_, trhs->field_.svalue_.str_) > 0 ? 1 : 0); break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_gtoe(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ >= trhs->field_.ivalue_ ? 1 : 0); break;
	case N2_VALUE_FLOAT:	n2_value_seti(state, val, val->field_.fvalue_ >= trhs->field_.fvalue_ ? 1 : 0); break;
	case N2_VALUE_STRING:	n2_value_seti(state, val, N2_STRCMP(val->field_.svalue_.str_, trhs->field_.svalue_.str_) >= 0 ? 1 : 0); break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の大小関係演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_lt(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	if (!n2_value_gtoe(state, f, val, rhs)) { return N2_FALSE; }
	N2_ASSERT(val->type_ == N2_VALUE_INT);
	val->field_.ivalue_ = (val->field_.ivalue_ ? 0 : 1);
	return N2_TRUE;
}

N2_API n2_bool_t n2_value_ltoe(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	if (!n2_value_gt(state, f, val, rhs)) { return N2_FALSE; }
	N2_ASSERT(val->type_ == N2_VALUE_INT);
	val->field_.ivalue_ = (val->field_.ivalue_ ? 0 : 1);
	return N2_TRUE;
}

N2_API n2_bool_t n2_value_blshift(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の<<演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ << trhs->field_.ivalue_); break;
	case N2_VALUE_FLOAT:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "浮動小数点同士の<<演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の<<演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の<<演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の<<演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_brshift(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の>>演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		n2_value_seti(state, val, val->field_.ivalue_ >> trhs->field_.ivalue_); break;
	case N2_VALUE_FLOAT:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "浮動小数点同士の>>演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の>>演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の>>演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の>>演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_add(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の+演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		val->field_.ivalue_ += trhs->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	val->field_.fvalue_ += trhs->field_.fvalue_; break;
	case N2_VALUE_STRING:	n2_str_append(state, &val->field_.svalue_, trhs->field_.svalue_.str_, SIZE_MAX); break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の+演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の+演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_sub(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の-演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		val->field_.ivalue_ -= trhs->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	val->field_.fvalue_ -= trhs->field_.fvalue_; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の-演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の-演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の-演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_mul(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の*演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		val->field_.ivalue_ *= trhs->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	val->field_.fvalue_ *= trhs->field_.fvalue_; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の*演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の*演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の*演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_div(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の/演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		if (trhs->field_.ivalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0除算が行われました"); res = N2_FALSE; break; } val->field_.ivalue_ /= trhs->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	if (trhs->field_.fvalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0除算が行われました"); res = N2_FALSE; break; } val->field_.fvalue_ /= trhs->field_.fvalue_; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の/演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベル同士の/演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール同士の/演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_mod(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs)
{
	n2_value_t* talloc = NULL;
	const n2_value_t* trhs = n2_value_eval_as(state, f, val->type_, rhs, &talloc);
	if (!trhs) { return N2_FALSE; }
	n2_bool_t res = N2_TRUE;
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nil同士の\\演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_INT:		if (trhs->field_.ivalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0剰余が行われました"); res = N2_FALSE; break; } val->field_.ivalue_ %= trhs->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	if (trhs->field_.fvalue_ == 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "0剰余が行われました"); res = N2_FALSE; break; } val->field_.fvalue_ = N2_FMOD(val->field_.fvalue_, trhs->field_.fvalue_); break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列同士の\\演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに\\演算子は挙動が定義されていません"); res = N2_FALSE; break;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュールに\\演算子は挙動が定義されていません"); res = N2_FALSE; break;
	default:				N2_ASSERT(0); break;
	}
	if (talloc) { n2_value_free(state, talloc); }
	return res;
}

N2_API n2_bool_t n2_value_unary_not(n2_state_t* state, n2_fiber_t* f, n2_value_t* val)
{
	n2_value_seti(state, val, !n2_value_eval_bool(state, f, val));
	return N2_TRUE;
}

N2_API n2_bool_t n2_value_unary_minus(n2_state_t* state, n2_fiber_t* f, n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "nilに負の値は定義されていません"); return N2_FALSE;
	case N2_VALUE_INT:		val->field_.ivalue_ = -val->field_.ivalue_; break;
	case N2_VALUE_FLOAT:	val->field_.fvalue_ = -val->field_.fvalue_; break;
	case N2_VALUE_STRING:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "文字列に負の値は定義されていません"); return N2_FALSE;
	case N2_VALUE_LABEL:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "ラベルに負の値は定義されていません"); return N2_FALSE;
	case N2_VALUE_MODINST:	n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュールに負値のは定義されていません"); return N2_FALSE;
	default:				N2_ASSERT(0); break;
	}
	return N2_TRUE;
}

N2_API void n2_value_inspect(n2_state_t* state, n2_environment_t* e, n2_str_t* dst, const n2_value_t* val)
{
	switch (val->type_)
	{
	case N2_VALUE_NIL:		n2_str_set(state, dst, "nil", SIZE_MAX); return;
	case N2_VALUE_INT:		n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, val->field_.ivalue_); return;
	case N2_VALUE_FLOAT:	n2_str_fmt_to(state, dst, "%" N2_VALFLOAT_PRI, val->field_.fvalue_); return;
	case N2_VALUE_STRING:	n2_str_fmt_to(state, dst, "\"%.*s\"", val->field_.svalue_.size_, val->field_.svalue_.str_); return;
	case N2_VALUE_LABEL:
		{
			const n2_vallabel_t* vallabel = &val->field_.labelvalue_;
			const n2_label_t* label = vallabel->label_index_ >= 0 ? n2_labelarray_peek(e->labels_, vallabel->label_index_) : NULL;
			n2_str_fmt_to(state, dst, "(label *%s)", label ? label->name_ : "<unknown>");
		}
		return;
	case N2_VALUE_MODINST:
		{
			const n2_valmodinst_t* valmodinst = &val->field_.modvalue_;
			if (valmodinst->instance_)
			{
				const n2_module_t* emodule = valmodinst->instance_ && valmodinst->instance_->module_id_ >= 0 ? n2_moduletable_peek(e->moduletable_, valmodinst->instance_->module_id_) : NULL;
				n2_str_fmt_to(state, dst, "(mod %s:%p)", emodule ? emodule->name_ : "<unknown>", valmodinst->instance_);
			}
			else
			{
				n2_str_fmt_to(state, dst, "(mod <null>)");
			}
		}
		return;
	case N2_VALUE_VARIABLE:	n2_variable_inspect(state, e, dst, val->field_.varvalue_.var_, val->field_.varvalue_.aptr_); return;
	default:				break;
	}
	n2_str_set(state, dst, "(unknown)", SIZE_MAX);
}

static void n2i_valuearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_value_free(state, *N2_RCAST(n2_value_t**, element));
}
N2_DEFINE_TARRAY(n2_value_t*, n2_valuearray, N2_API, n2i_setupfunc_nothing, n2i_valuearray_freefunc);

static void n2i_flatvaluearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2i_value_teardown(state, N2_RCAST(n2_value_t*, element));
}
N2_DEFINE_TARRAY(n2_value_t, n2_flatvaluearray, N2_API, n2i_setupfunc_nothing, n2i_flatvaluearray_freefunc);

//=============================================================================
// 実行コード

static int n2i_labelarray_matchfunc(const n2_array_t* a, const void* element, const void* key)
{
	N2_UNUSE(a);
	return n2_plstr_cmp_case(N2_RCAST(const n2_label_t*, element)->name_, N2_RCAST(const char*, key));
}

static void n2i_label_teardown(n2_state_t* state, n2_label_t* label)
{
	n2_free(state, label->name_);
}

static void n2i_labelarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_label_t* label = N2_RCAST(n2_label_t*, element);
	n2i_label_teardown(state, label);
}

N2_DEFINE_TARRAY(n2_label_t, n2_labelarray, N2_API, n2i_setupfunc_nothing, n2i_labelarray_freefunc);

N2_DEFINE_TARRAY(n2_opcode_t, n2_opcodearray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

static int n2i_codelinetable_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	n2_pc_t l, r;
	N2_UNUSE(a);
	N2_UNUSE(key);
	l = N2_RCAST(const n2_codeline_t*, lkey)->pc_;
	r = N2_RCAST(const n2_codeline_t*, rkey)->pc_;
	return l == r ? 0 : l < r ? -1 : 1;
}

static int n2i_codelinetable_matchfunc(const n2_sorted_array_t* a, const void* ckey, const void* key)
{
	n2_pc_t l, r;
	N2_UNUSE(a);
	l = N2_RCAST(const n2_codeline_t*, ckey)->pc_;
	r = *N2_RCAST(const n2_pc_t*, key);
	return l == r ? 0 : l < r ? -1 : 1;
}

static void n2i_codelinetable_setupfunc(n2_state_t* state, n2_codelinetable_t* codelinetable)
{
	N2_UNUSE(state);
	codelinetable->cmp_ = n2i_codelinetable_cmpfunc;
	codelinetable->match_ = n2i_codelinetable_matchfunc;
}
N2_DEFINE_TSORTED_ARRAY(n2_codeline_t, void, n2_pc_t, n2_codelinetable, N2_API, n2i_codelinetable_setupfunc, n2i_freefunc_nothing);

static const n2_codeline_t* n2i_codelinetable_find_from_pc(const n2_codelinetable_t* codelinetable, n2_pc_t pc)
{
	if (!codelinetable || pc < 0) { return NULL; }
	const n2_codeline_t* codeline = n2_codelinetable_upperbound(N2_CCAST(n2_codelinetable_t*, codelinetable), &pc, N2_TRUE);
	if (!codeline) { return NULL; }
	--codeline;
	if (n2_codelinetable_compute_index(codelinetable, codeline) < 0) { return NULL; }
	if (!codeline->line_head_) { return NULL; }// no corresponding codeline
	return codeline;
}

N2_API n2_codeimage_t* n2_codeimage_alloc(n2_state_t* state)
{
	n2_codeimage_t* codeimage = N2_TMALLOC(n2_codeimage_t, state);
	codeimage->opcodes_ = n2_opcodearray_alloc(state, 1024, 1024);
	codeimage->opcodeflags_ = NULL;
	codeimage->val_literals_ = n2_flatvaluearray_alloc(state, 0, 16);
	codeimage->str_literals_ = n2_plstrarray_alloc(state, 0, 16);
	codeimage->sourcefiles_ = n2_sourcefilearray_alloc(state, 0, 4);
	codeimage->sourcecodes_ = n2_sourcecodearray_alloc(state, 0, 4);
	codeimage->codelinetable_ = NULL;
#if N2_CONFIG_USE_DEBUGGING
	if (state->config_.generate_opcodeflags_) { codeimage->opcodeflags_ = n2_u8array_alloc(state, 1024, 1024); }
	codeimage->codelinetable_ = n2_codelinetable_alloc(state, 0, 1024);
#endif
	return codeimage;
}

N2_API void n2_codeimage_free(n2_state_t* state, n2_codeimage_t* codeimage)
{
	n2_opcodearray_free(state, codeimage->opcodes_);
	if (codeimage->opcodeflags_) { n2_u8array_free(state, codeimage->opcodeflags_); }
	n2_flatvaluearray_free(state, codeimage->val_literals_);
	n2_plstrarray_free(state, codeimage->str_literals_);
	if (codeimage->sourcefiles_) { n2_sourcefilearray_free(state, codeimage->sourcefiles_); }
	if (codeimage->sourcecodes_) { n2_sourcecodearray_free(state, codeimage->sourcecodes_); }
	if (codeimage->codelinetable_) { n2_codelinetable_free(state, codeimage->codelinetable_); }
	n2_free(state, codeimage);
}

N2_API const n2_codeline_t* n2_codeimage_find_codeline_from_pc(const n2_codeimage_t* codeimage, n2_pc_t pc)
{
	return n2i_codelinetable_find_from_pc(codeimage->codelinetable_, pc);
}

static int n2i_opcode_put_block(n2_state_t* state, n2_opcodearray_t* opcodes, const void* src, size_t src_size)
{
	if (src_size <= 0) { return 0; }
	int stride = N2_SCAST(int, src_size / sizeof(n2_opcode_t));
	if ((src_size % sizeof(n2_opcode_t)) > 0) { ++stride; }
	for (int i = 0; i < stride; ++i)
	{
		n2_opcode_t w = 0;
		const size_t wsize = N2_MIN(src_size - sizeof(n2_opcode_t) * N2_SCAST(size_t, i), sizeof(n2_opcode_t));
		N2_MEMCPY(&w, n2_cptr_offset(src, sizeof(n2_opcode_t) * N2_SCAST(size_t, i)), wsize);
		n2_opcodearray_push(state, opcodes, &w);
	}
	return stride;
}

static int n2i_opcode_get_block(void* dst, size_t dst_size, const n2_opcode_t* opcodes, int pc)
{
	N2_MEMCPY(dst, opcodes + pc, dst_size);
	int stride = N2_SCAST(int, dst_size / sizeof(n2_opcode_t));
	if ((dst_size % sizeof(n2_opcode_t)) > 0) { ++stride; }
	return stride;
}

static void n2i_opcode_put_pushvalliteral(n2_state_t* state, n2_codeimage_t* codeimage, n2_opcodearray_t* opcodes, n2_value_t* val)
{
	int valindex = n2_flatvaluearray_find(codeimage->val_literals_, n2i_matchfunc_bitperfect, val);
	if (valindex < 0)
	{
		valindex = N2_SCAST(int, n2_flatvaluearray_size(codeimage->val_literals_));
		n2_flatvaluearray_push(state, codeimage->val_literals_, val);
	}
	else
	{
		n2i_value_teardown(state, val);
	}
	n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_VAL_LITERAL);
	n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, valindex));
}

static void n2i_opcode_put_pushintop(n2_state_t* state, n2_codeimage_t* codeimage, n2_opcodearray_t* opcodes, n2_valint_t val)
{
	N2_ASSERT(sizeof(n2_opcode_t) == sizeof(int32_t));
	if (val >= INT32_MIN && val <= INT32_MAX)
	{
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_SINT);
		n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, val));
	}
	else
	{
		n2_value_t tval;
		n2i_value_init(&tval);
		n2_value_seti(state, &tval, val);
		n2i_opcode_put_pushvalliteral(state, codeimage, opcodes, &tval);
	}
}

static void n2i_opcode_put_pushfloatop(n2_state_t* state, n2_codeimage_t* codeimage, n2_opcodearray_t* opcodes, n2_valfloat_t val)
{
	n2_value_t tval;
	n2i_value_init(&tval);
	n2_value_setf(state, &tval, val);
	n2i_opcode_put_pushvalliteral(state, codeimage, opcodes, &tval);
}

static n2_pc_t n2i_opcode_dump(n2_state_t* state, int indent, const n2_codeimage_t* codeimage, int pc, const n2_environment_t* e, size_t flags)
{
	N2_UNUSE(flags);

	const n2_opcode_t* opcodes = N2_RCAST(const n2_opcode_t*, codeimage->opcodes_->elements_);
	const n2_u8array_t* opcodeflags = codeimage->opcodeflags_;

	for (int i = 0; i < indent; ++i) { n2i_printf(state, "  "); }

	static const char* opnames[] =
	{
		"NOP",

		"POP",
		"PUSH_NIL",
		"PUSH_SINT",
		"PUSH_VAL_LITERAL",
		"PUSH_STRING",
		"PUSH_TEMPLATE_STRING",
		"PUSH_LABEL",
		"PUSH_VARIABLE",
		"PUSH_SYSVAR",
		"PUSH_SYSVAR_EX",
		"PUSH_MODULE",
		"PUSH_MODULE_LOCALVAR",
		"PUSH_STACK",
		"PUSH_STACK_REL",
		"STORE_STACK",
		"SET_VARIABLE_APTR",

		"ASSIGN",
		"ASSIGN_BULK",
		"BOR_ASSIGN",
		"BAND_ASSIGN",
		"BXOR_ASSIGN",
		"BLSHIFT_ASSIGN",
		"BLSHIFT_ASSIGN",
		"ADD_ASSIGN",
		"SUB_ASSIGN",
		"MUL_ASSIGN",
		"DIV_ASSIGN",
		"MOD_ASSIGN",
		"INCREMENT",
		"DECREMENT",

		"BOR",
		"BAND",
		"BXOR",

		"EQ",
		"NEQ",
		"GT",
		"GTOE",
		"LT",
		"LTOE",
		"BLSHIFT",
		"BRSHIFT",

		"ADD",
		"SUB",
		"MUL",
		"DIV",
		"MOD",

		"UNARY_NOT",
		"UNARY_MINUS",

		"TEST_NIL",
		"TEST_ORIGINAL_ARG_NUM",

		"IF",
		"IFNOT",

		"REPEAT",
		"FOREACH",
		"REPEAT_CHECK",
		"LOOP",
		"CONTINUE",
		"BREAK",

		"SWITCH",
		"SWCASE",
		"SWDEFAULT",
		"SWBREAK",
		"SWEND",

		"MODULE",
		"GLOBAL",

		"DEFFUNC",
		"ENTER_FUNCTION",

		"LABEL",

		"GOSUB",
		"GOTO",

		"COMMAND",
		"FUNCTION",

		"JUMP",
		"JUMP_RELATIVE",
		"RETURN",
		"END",

		"<END>"
	};

	const n2_opcode_t op = opcodes[pc];
	N2_ASSERT(op >= 0 && op < N2_MAX_OPECODE);

	const uint8_t opf = opcodeflags ? n2_u8array_peekcv(opcodeflags, N2_SCAST(int, pc), 0) : 0;

	n2i_printf(state, "%s%s %04d: %s[%d] ", (opf & N2_OPCODEFLAG_LINE_STATEMENTS_HEAD) ? "L" : " ", (opf & N2_OPCODEFLAG_STATEMENT_HEAD) ? "S" : " ", pc, opnames[op], op);

	n2_pc_t offset = 0;
	switch (op)
	{
	case N2_OPCODE_NOP:
		break;

	case N2_OPCODE_POP:
		{
			const n2_opcode_t num = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": NUM[%d]", N2_SCAST(int, num));
		}
		break;
	case N2_OPCODE_PUSH_SINT:
		{
			n2_valint_t v = N2_SCAST(n2_valint_t, opcodes[pc + 1]);
			++offset;
			n2i_printf(state, ": VAL[%" N2_VALINT_PRI "]", v);
		}
		break;
	case N2_OPCODE_PUSH_VAL_LITERAL:
		{
			const n2_opcode_t valindex = opcodes[pc + 1];
			++offset;
			const n2_value_t* val = n2_flatvaluearray_peek(codeimage->val_literals_, valindex);
			N2_ASSERT(val);
			switch (val->type_)
			{
			case N2_VALUE_INT:		n2i_printf(state, ": VAL[%" N2_VALINT_PRI " <= %d]", val->field_.ivalue_, N2_SCAST(int, valindex)); break;
			case N2_VALUE_FLOAT:	n2i_printf(state, ": VAL[%" N2_VALFLOAT_PRI " <= %d]", val->field_.fvalue_, N2_SCAST(int, valindex)); break;
			default:				n2i_printf(state, ": VAL[UNKNOWN <= %d]", N2_SCAST(int, valindex)); break;
			}
		}
		break;
	case N2_OPCODE_PUSH_STRING:
		{
			const n2_opcode_t strindex = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": VAL[%s]", *N2_SCAST(char**, n2_array_peek(codeimage->str_literals_, strindex)));
		}
		break;
	case N2_OPCODE_PUSH_TEMPLATE_STRING:
		{
			const n2_opcode_t arg_num = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": NUM[%d]", N2_SCAST(int, arg_num));
		}
		break;
	case N2_OPCODE_PUSH_LABEL:
		{
			const n2_opcode_t labelindex = opcodes[pc + 1];
			const n2_label_t* label = NULL;
			if (e) { label = n2_labelarray_peek(e->labels_, labelindex); }
			++offset;
			n2i_printf(state, ": VAL[%d=%s]", N2_SCAST(int, labelindex), label ? label->name_ : "-");
		}
		break;
	case N2_OPCODE_PUSH_VARIABLE:
		{
			const n2_opcode_t varindex = opcodes[pc + 1];
			++offset;
			const n2_variable_t* var = NULL;
			if (e) { var = n2_vartable_peek(e->vartable_, varindex); }
			n2i_printf(state, ": VAR[%d=%s]", N2_SCAST(int, varindex), var ? var->name_ : "-");
		}
		break;
	case N2_OPCODE_PUSH_SYSVAR:
		{
			const n2_opcode_t sysvar = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": VAL[%d]", N2_SCAST(int, sysvar));
		}
		break;
	case N2_OPCODE_PUSH_SYSVAR_EX:
		{
			const n2_opcode_t sysvarexindex = opcodes[pc + 1];
			++offset;
			const n2_sysvar_ex_t* sysvarex = NULL;
			if (e) { sysvarex = n2_sysvarexarray_peek(e->sysvar_ex_, sysvarexindex); }
			n2i_printf(state, ": VAL[%d=%s]", N2_SCAST(int, sysvarexindex), sysvarex ? sysvarex->name_ : "-");
		}
		break;
	case N2_OPCODE_PUSH_MODULE:
		{
			const n2_opcode_t modindex = opcodes[pc + 1];
			N2_ASSERT(modindex >= 0);
			n2_module_t* emodule = NULL;
			if (e) { emodule = n2_moduletable_peek(e->moduletable_, modindex); }
			n2i_printf(state, ": MODULE[%i=%s]", modindex, emodule ? emodule->name_ : "-");
			++offset;
		}
		break;
	case N2_OPCODE_PUSH_MODULE_LOCALVAR:
		{
			const n2_opcode_t modvarindex = opcodes[pc + 1];
			N2_ASSERT(modvarindex >= 0);
			n2i_printf(state, ": MODULE_LOCALVAR[%i]", modvarindex);
			++offset;
		}
		break;
	case N2_OPCODE_PUSH_STACK:
	case N2_OPCODE_PUSH_STACK_REL:
		{
			const n2_opcode_t stack = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": VAL[%d]", N2_SCAST(int, stack));
		}
		break;

	case N2_OPCODE_STORE_STACK:
		{
			const n2_opcode_t stack = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": VAL[%d]", N2_SCAST(int, stack));
		}
		break;

	case N2_OPCODE_SET_VARIABLE_APTR:
		{
			const n2_opcode_t arg_num = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": ARG[%d]", N2_SCAST(int, arg_num));
		}
		break;

	case N2_OPCODE_ASSIGN:
	case N2_OPCODE_BOR_ASSIGN:
	case N2_OPCODE_BAND_ASSIGN:
	case N2_OPCODE_BXOR_ASSIGN:
	case N2_OPCODE_BLSHIFT_ASSIGN:
	case N2_OPCODE_BRSHIFT_ASSIGN:
	case N2_OPCODE_ADD_ASSIGN:
	case N2_OPCODE_SUB_ASSIGN:
	case N2_OPCODE_MUL_ASSIGN:
	case N2_OPCODE_DIV_ASSIGN:
	case N2_OPCODE_MOD_ASSIGN:
	case N2_OPCODE_INCREMENT:
	case N2_OPCODE_DECREMENT:
		break;
	case N2_OPCODE_ASSIGN_BULK:
		{
			const n2_opcode_t arg_num = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": ARG[%d]", N2_SCAST(int, arg_num));
		}
		break;

	case N2_OPCODE_BOR:
	case N2_OPCODE_BAND:
	case N2_OPCODE_BXOR:
	case N2_OPCODE_EQ:
	case N2_OPCODE_NEQ:
	case N2_OPCODE_GT:
	case N2_OPCODE_GTOE:
	case N2_OPCODE_LT:
	case N2_OPCODE_LTOE:
	case N2_OPCODE_BLSHIFT:
	case N2_OPCODE_BRSHIFT:
	case N2_OPCODE_ADD:
	case N2_OPCODE_SUB:
	case N2_OPCODE_MUL:
	case N2_OPCODE_DIV:
	case N2_OPCODE_MOD:
		break;

	case N2_OPCODE_UNARY_NOT:
	case N2_OPCODE_UNARY_MINUS:
		break;

	case N2_OPCODE_TEST_ORIGINAL_ARG_NUM:
		{
			const n2_opcode_t stackindex = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": STACK[%d]", N2_SCAST(int, stackindex));
		}
		break;

	case N2_OPCODE_IF:
	case N2_OPCODE_IFNOT:
		{
			const n2_opcode_t to_head = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": %s[%d>%d]", op == N2_OPCODE_IF ? "FALSE" : "TRUE", N2_SCAST(int, to_head), N2_SCAST(int, pc + to_head));
		}
		break;

	case N2_OPCODE_REPEAT:
	case N2_OPCODE_FOREACH:
		{
			const n2_opcode_t end_position = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": END[%d]", N2_SCAST(int, end_position));
		}
		break;
	case N2_OPCODE_REPEAT_CHECK:
		break;

	case N2_OPCODE_LOOP:
	case N2_OPCODE_CONTINUE:
	case N2_OPCODE_BREAK:
		break;

	case N2_OPCODE_SWITCH:
		{
			const n2_opcode_t end_position = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": END[>%d]", N2_SCAST(int, end_position));
		}
		break;
	case N2_OPCODE_SWCASE:
		{
			const n2_opcode_t end_position = opcodes[pc + 1];
			++offset;
			n2i_printf(state, ": END_CASE[>%d]", N2_SCAST(int, end_position));
		}
		break;

	case N2_OPCODE_SWDEFAULT:
	case N2_OPCODE_SWBREAK:
	case N2_OPCODE_SWEND:
		break;

	case N2_OPCODE_MODULE:
		{
			const n2_opcode_t modindex = opcodes[pc + 1];
			const n2_opcode_t endoffset = opcodes[pc + 2];
			N2_ASSERT(modindex >= 0);
			n2_module_t* emodule = NULL;
			if (e) { emodule = n2_moduletable_peek(e->moduletable_, modindex); }
			n2i_printf(state, ": MODULE[%i=%s] END[%d>%d]", modindex, emodule ? emodule->name_ : "-", N2_SCAST(int, endoffset), N2_SCAST(int, pc + endoffset));
			offset += 2;
		}
		break;
	case N2_OPCODE_GLOBAL:
		{
			const n2_opcode_t modindex = opcodes[pc + 1];
			N2_ASSERT(modindex >= 0);
			n2_module_t* emodule = NULL;
			if (e) { emodule = n2_moduletable_peek(e->moduletable_, modindex); }
			n2i_printf(state, ": MODULE[%i=%s]", modindex, emodule ? emodule->name_ : "-");
			++offset;
		}
		break;

	case N2_OPCODE_DEFFUNC:
	case N2_OPCODE_ENTER_FUNCTION:
		{
			const n2_opcode_t funcindex = opcodes[pc + 1];
			N2_ASSERT(funcindex >= 0);
			n2_func_t* func = NULL;
			if (e) { func = n2_functable_peek(e->functable_, funcindex); }
			n2i_printf(state, ": FUNC[%i=%s]", funcindex, func ? func->name_ : "-");
			++offset;
		}
		break;

	case N2_OPCODE_LABEL:
		{
			const n2_opcode_t labelindex = opcodes[pc + 1];
			N2_ASSERT(labelindex >= 0);
			n2_label_t* label = NULL;
			if (e) { label = n2_labelarray_peek(e->labels_, labelindex); }
			n2i_printf(state, ": LABEL[%i=%s] POS[%d]", labelindex, label ? label->name_ : "-", label ? label->pc_ : -1);
			++offset;
		}
		break;

	case N2_OPCODE_GOSUB:
	case N2_OPCODE_GOTO:
		break;

	case N2_OPCODE_COMMAND:
	case N2_OPCODE_FUNCTION:
		{
			const n2_opcode_t funcindex = opcodes[pc + 1];
			N2_ASSERT(funcindex >= 0);
			const n2_opcode_t arg_num_flags = opcodes[pc + 2];
			n2_func_t* func = NULL;
			if (e) { func = n2_functable_peek(e->functable_, funcindex); }
			const int arg_num = N2_SCAST(int, arg_num_flags & 0xffff);
			const size_t exflags = N2_SCAST(size_t, (arg_num_flags >> 16) & 0xffff);
			n2i_printf(state, ": %s[%d=%s] ARG[%d] F[%zx]", op == N2_OPCODE_COMMAND ? "COMMAND" : "FUNCTION", funcindex, func ? func->name_ : "-", arg_num, exflags);
			offset += 2;
		}
		break;

	case N2_OPCODE_JUMP:
		n2i_printf(state, ": POS[%d]", N2_SCAST(int, opcodes[pc + 1]));
		++offset;
		break;
	case N2_OPCODE_JUMP_RELATIVE:
		n2i_printf(state, ": OFFSET[%d>%d]", N2_SCAST(int, opcodes[pc + 1]), N2_SCAST(int, pc + opcodes[pc + 1]));
		++offset;
		break;
	case N2_OPCODE_RETURN:
		n2i_printf(state, ": ARG[%d]", N2_SCAST(int, opcodes[pc + 1]));
		++offset;
		break;

	case N2_OPCODE_END:
		break;

	default:
		break;
	}
	n2i_printf(state, "\n");
	return offset;
}

N2_API void n2_codeimage_dump(n2_state_t* state, const n2_codeimage_t* codeimage, const n2_environment_t* e, size_t flags)
{
	const n2_pc_t l = N2_SCAST(n2_pc_t, n2_array_size(codeimage->opcodes_));
	n2i_printf(state, "====code[%p] %d[words]====\n", codeimage->opcodes_, l);
	n2_str_t tstr; n2_str_init(&tstr);
	const char* line_head = NULL;
	for (n2_pc_t i = 0; i < l; ++i )
	{
		if ((flags & N2_CODEIMAGE_DUMP_CODELINES) && codeimage->codelinetable_)
		{
			const n2_codeline_t* codeline = n2i_codelinetable_find_from_pc(codeimage->codelinetable_, i);
			if (codeline && codeline->line_head_ != line_head)
			{
				line_head = codeline->line_head_;
				n2_str_clear(&tstr);
				n2i_str_cutoff_append(state, &tstr, line_head, 64, '\n', "...");
				n2i_printf(state, "    >> %s\n", tstr.str_);
			}
		}

		i += n2i_opcode_dump(state, 1, codeimage, i, e, flags);
	}
	n2_str_teardown(state, &tstr);
	n2i_printf(state, "  %04d: EOC\n", l);
	n2i_printf(state, "--------\n");
}

//=============================================================================
// 関数

static void n2i_func_init(n2_state_t* state, n2_func_t* dst, const char* name)
{
	dst->func_ = N2_FUNC_UNKNOWN;
	dst->name_ = NULL;
	dst->short_name_ = NULL;
	if (name)
	{
		n2_str_t sname;
		n2_str_init(&sname);
		n2_naming_compute(state, name, SIZE_MAX, NULL, &sname, NULL, NULL);
		dst->name_ = n2_plstr_clone(state, name);
		dst->short_name_ = n2_plstr_clone(state, sname.str_);
		n2_str_teardown(state, &sname);
	}
	dst->flags_ = 0;
	dst->callback_ = NULL;
	dst->user_ = NULL;
	dst->pc_ = -1;
	dst->params_ = NULL;
	dst->alias_func_ = NULL;
	dst->module_id_ = -1;
	n2_str_init(&dst->libprocname_);
	dst->lib_ = NULL;
	dst->libproc_ = NULL;
}

static void n2i_func_setas_callback(n2_state_t* state, n2_func_t* dst, n2_func_e funce, n2_func_callback_t callback, void* funcuser)
{
	N2_UNUSE(state);
	dst->func_ = funce;
	dst->flags_ |= N2_FUNCFLAG_DEFINED;
	dst->callback_ = callback;
	dst->user_ = funcuser;
	dst->module_id_ = -1;
}

static void n2i_func_setas_alias(n2_state_t* state, n2_func_t* dst, n2_func_t* to)
{
	N2_UNUSE(state);
	dst->func_ = N2_FUNC_ALIAS;
	dst->flags_ |= N2_FUNCFLAG_DEFINED;
	dst->alias_func_ = to;
	dst->module_id_ = -1;
}

static void n2i_func_teardown(n2_state_t* state, n2_func_t* func)
{
	if (func->name_) { n2_free(state, func->name_); func->name_ = NULL; }
	if (func->short_name_) { n2_free(state, func->short_name_); func->short_name_ = NULL; }
	if (func->params_) { n2_funcparamarray_free(state, func->params_); func->params_ = NULL; }
	n2_str_teardown(state, &func->libprocname_);
	func->lib_ = NULL;
	func->libproc_ = NULL;
}

static void n2i_funcarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_func_t* func = N2_RCAST(n2_func_t*, element);
	n2i_func_teardown(state, func);
}

static int n2i_funcindexmap_name_cmpfunc(const n2_sorted_array_t* a, const void* lfunckey, const void* rfunckey, const void* key)
{
	N2_UNUSE(key);
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int* lindex = N2_RCAST(const int*, lfunckey);
	const int* rindex = N2_RCAST(const int*, rfunckey);
	n2_func_t* lfunc = n2_funcarray_peek(functable->funcarray_, *lindex);
	n2_func_t* rfunc = n2_funcarray_peek(functable->funcarray_, *rindex);
	if (!lfunc->name_ || !rfunc->name_) { return (lfunc->name_ == rfunc->name_ ? 0 : lfunc->name_ ? 1 : -1); }
	return n2_plstr_cmp_case(lfunc->name_, rfunc->name_);
}

static int n2i_funcindexmap_name_matchfunc(const n2_sorted_array_t* a, const void* funckey, const void* key)
{
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int* funcindex = N2_RCAST(const int*, funckey);
	n2_func_t* func = n2_funcarray_peek(functable->funcarray_, *funcindex);
	const char* name = N2_RCAST(const char*, key);
	if (!func->name_ || !name) { return -1; }
	return n2_plstr_cmp_case(func->name_, name);
}

static void n2i_funcindexmap_setupfunc(n2_state_t* state, n2_funcindexmap_t* funcindexmap)
{
	N2_UNUSE(state);
	funcindexmap->cmp_ = n2i_funcindexmap_name_cmpfunc;
	funcindexmap->match_ = n2i_funcindexmap_name_matchfunc;
}

static void n2i_funcindexmap_postalloc(n2_state_t* state, n2_functable_t* functable)
{
	N2_UNUSE(state);
	functable->funcindexmap_->a_.user_ = functable;
}

N2_DEFINE_TARRAY(n2_func_t, n2_funcarray, N2_API, n2i_setupfunc_nothing, n2i_funcarray_freefunc);
N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_funcindexmap, N2_API, n2i_funcindexmap_setupfunc, n2i_freefunc_nothing);

static void n2i_func_param_teardown(n2_state_t* state, n2_func_param_t* func_param)
{
	if (func_param->name_) { n2_free(state, func_param->name_); }
}

static const struct
{
	n2_func_param_e type_;
	const char* word_;
}
n2i_func_param_type_extable[] =
{
	{N2_FUNC_PARAM_WSTR,			"wstr"},
	{N2_FUNC_PARAM_SPTR,			"sptr"},
	{N2_FUNC_PARAM_WPTR,			"wptr"},
	{N2_FUNC_PARAM_SINGLEFLOAT,		"float"},
	{N2_FUNC_PARAM_NULLPTR,			"nullptr"},
	{N2_FUNC_PARAM_INT64,			"int64"},
	{N2_FUNC_PARAM_U8STR,			"u8str"},
	{N2_FUNC_PARAM_U8PTR,			"u8ptr"},
	{N2_FUNC_PARAM_UNKNOWN,			NULL}
};

N2_API n2_func_param_e n2_func_param_from_token(const n2_token_t* token, n2_bool_t allow_dltype)
{
	N2_ASSERT(token);
	if (token->token_ != N2_TOKEN_IDENTIFIER) { return N2_FUNC_PARAM_UNKNOWN; }
	n2_func_param_e paramtype = N2_FUNC_PARAM_UNKNOWN;
	// 通常型
	const n2_keyword_e typekeyword = n2_keyword_find(token->content_);
	switch (typekeyword)
	{
	case N2_KEYWORD_INT:		paramtype = N2_FUNC_PARAM_INT; break;
	case N2_KEYWORD_DOUBLE:		paramtype = N2_FUNC_PARAM_FLOAT; break;
	case N2_KEYWORD_STR:		paramtype = N2_FUNC_PARAM_STR; break;
	case N2_KEYWORD_LABEL:		paramtype = N2_FUNC_PARAM_LABEL; break;
	case N2_KEYWORD_VAR:		paramtype = N2_FUNC_PARAM_VAR; break;
	case N2_KEYWORD_ARRAY:		paramtype = N2_FUNC_PARAM_ARRAY; break;
	case N2_KEYWORD_LOCAL:		paramtype = N2_FUNC_PARAM_LOCAL; break;
	case N2_KEYWORD_MODVAR:		paramtype = N2_FUNC_PARAM_MODVAR; break;
	default:					break;
	}
	// 拡張型の検索
	if (paramtype == N2_FUNC_PARAM_UNKNOWN && allow_dltype)
	{
		for (size_t i = 0; n2i_func_param_type_extable[i].word_; ++i)
		{
			if (N2_STRCMP(token->content_, n2i_func_param_type_extable[i].word_) == 0) { paramtype = n2i_func_param_type_extable[i].type_; break; }
		}
	}
	return paramtype;
}

static void n2i_funcparamarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_func_param_t* func_param = N2_RCAST(n2_func_param_t*, element);
	n2i_func_param_teardown(state, func_param);
}
static int n2i_funcparamarray_matchfunc(const n2_array_t* a, const void* pkey, const void* key)
{
	N2_UNUSE(a);
	const n2_func_param_t* param = N2_RCAST(const n2_func_param_t*, pkey);
	if (!param->name_) { return key ? -1 : 0; }
	return n2_plstr_cmp_case(param->name_, N2_RCAST(const char*, key));
}
N2_DEFINE_TARRAY(n2_func_param_t, n2_funcparamarray, N2_API, n2i_setupfunc_nothing, n2i_funcparamarray_freefunc);

N2_API n2_functable_t* n2_functable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step)
{
	n2_functable_t* functable = N2_TMALLOC(n2_functable_t, state);
	if (!functable) { return NULL; }
	functable->funcarray_ = n2_funcarray_alloc(state, initial_buffer_size, expand_step);
	functable->funcindexmap_ = n2_funcindexmap_alloc(state, initial_buffer_size, expand_step);
	n2i_funcindexmap_postalloc(state, functable);
	return functable;
}

N2_API void n2_functable_free(n2_state_t* state, n2_functable_t* functable)
{
	n2_funcindexmap_free(state, functable->funcindexmap_);
	n2_funcarray_free(state, functable->funcarray_);
	n2_free(state, functable);
}

N2_API n2_func_t* n2_functable_peek(n2_functable_t* functable, int index)
{
	return n2_funcarray_peek(functable->funcarray_, index);
}

N2_API n2_func_t* n2_functable_find(n2_functable_t* functable, const char* name)
{
	if (!name) { return NULL; }
	int* index = n2_funcindexmap_find(functable->funcindexmap_, name);
	if (!index) { return NULL; }
	return n2_funcarray_peek(functable->funcarray_, *index);
}

N2_API int n2_functable_register(n2_state_t* state, n2_functable_t* functable, const char* name)
{
	n2_func_t* func = NULL;
	if (name) { func = n2_functable_find(functable, name); }
	if (!func)
	{
		n2_func_t tfunc;
		n2i_func_init(state, &tfunc, name);
		int funcindex = N2_SCAST(int, n2_funcarray_size(functable->funcarray_));
		func = n2_funcarray_push(state, functable->funcarray_, &tfunc);
		if (name) { n2_funcindexmap_insert(state, functable->funcindexmap_, &funcindex, func->name_); }
	}

	return n2_funcarray_compute_index(functable->funcarray_, func);
}

//=============================================================================
// システム変数
static const struct
{
	n2_sysvar_e sysvar_;
	const char* word_;
}
n2i_sysvar_table[] =
{
	{N2_SYSVAR_HSPVER,		"hspver"},
	{N2_SYSVAR_CNT,			"cnt"},
	{N2_SYSVAR_STAT,		"stat"},
	{N2_SYSVAR_REFDVAL,		"refdval"},
	{N2_SYSVAR_REFSTR,		"refstr"},
	{N2_SYSVAR_STRSIZE,		"strsize"},
	{N2_SYSVAR_LOOPLEV,		"looplev"},
	{N2_SYSVAR_SUBLEV,		"sublev"},
	{N2_SYSVAR_NOTEMAX,		"notemax"},
	{N2_SYSVAR_NOTESIZE,	"notesize"},
	{N2_SYSVAR_UNDEF,		NULL}
};

static size_t n2i_sysvar_notelinenum(const n2_valstr_t* str)
{
	size_t line = 0;
	size_t line_head_offset = 0;
	size_t offset = 0;
	while (offset < str->buffer_size_)
	{
		const char c = str->str_[offset];
		if (c == '\0') { break; }
		if (c == '\n') { line_head_offset = offset; ++line; }
		++offset;
	}
	return line + (offset > line_head_offset + 1 ? 1 : 0);
}

static int n2i_sysvar_notelinehead(const n2_valstr_t* str, int line)
{
	if (line == 0) { return 0; }
	size_t offset = 0;
	while (offset < str->buffer_size_)
	{
		const char c = str->str_[offset];
		if (c == '\0') { break; }
		if (c == '\n' && !--line) { return N2_SCAST(int, offset + 1); }
		++offset;
	}
	return -1;
}

N2_API const char* n2_sysvar_name(n2_sysvar_e sysvar, const char* on_failed)
{
	// 全探索
	for (size_t i = 0; n2i_sysvar_table[i].word_; ++i)
	{
		if (n2i_sysvar_table[i].sysvar_ == sysvar) { return n2i_sysvar_table[i].word_; }
	}
	return on_failed;
}

N2_API n2_sysvar_e n2_sysvar_find(const char* s)
{
	// 全探索
	for (size_t i = 0; n2i_sysvar_table[i].word_; ++i)
	{
		if (N2_STRCMP(s, n2i_sysvar_table[i].word_) == 0) { return n2i_sysvar_table[i].sysvar_; }
	}
	return N2_SYSVAR_UNDEF;
}

N2_API n2_bool_t n2_sysvar_inspect(n2_state_t* state, n2_str_t* dst, n2_str_t* dst_type, n2_sysvar_e sysvar, const n2_fiber_t* f)
{
	switch (sysvar)
	{
	case N2_SYSVAR_HSPVER:	{ n2_str_fmt_to(state, dst, "%d", state->config_.reference_hspver_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_CNT:		{ n2_str_fmt_to(state, dst, "%d", f->cnt_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_STAT:	{ n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, f->stat_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_REFDVAL:	{ n2_str_fmt_to(state, dst, "%" N2_VALFLOAT_PRI, f->refdval_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_FLOAT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_REFSTR:	{ n2_str_fmt_to(state, dst, "\"%.*s\"", f->refstr_->size_, f->refstr_->str_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_STRING, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_STRSIZE:	{ n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, f->strsize_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_LOOPLEV:	{ n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, f->looplev_); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_SUBLEV:	{ n2_str_fmt_to(state, dst, "%zu", n2_callframearray_size(f->callframes_)); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); } return N2_TRUE;
	case N2_SYSVAR_NOTEMAX:
		{
			n2_valint_t size = 0;
			if (f->notevar_ && f->notevar_->type_ == N2_VALUE_STRING)
			{
				const n2_valstr_t* notestr = n2_variable_get_strc(f->notevar_, f->noteaptr_);
				if (notestr) { size = n2i_sysvar_notelinenum(notestr); }
			}
			n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, size); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX);
		}
		return N2_TRUE;
	case N2_SYSVAR_NOTESIZE:
		{
			n2_valint_t size = 0;
			if (f->notevar_ && f->notevar_->type_ == N2_VALUE_STRING)
			{
				const n2_valstr_t* notestr = n2_variable_get_strc(f->notevar_, f->noteaptr_);
				if (notestr) { size = N2_SCAST(n2_valint_t, n2_str_compute_size(notestr)); }
			}
			n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, size); n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX);
		}
		return N2_TRUE;
	default:				break;
	}
	n2_str_set(state, dst, "<unknown>", SIZE_MAX);
	n2_str_set(state, dst_type, "<unknown type>", SIZE_MAX);
	return N2_FALSE;
}

static void n2i_sysvarex_teardown(n2_state_t* state, n2_sysvar_ex_t* sysvarex)
{
	n2_free(state, sysvarex->name_);
#if N2_CONFIG_USE_DEBUGGING
	if (sysvarex->debugvarroot_) { n2_debugvarpool_push(state, sysvarex->debugvarpool_, sysvarex->debugvarroot_); sysvarex->debugvarroot_ = NULL; }
	sysvarex->debugvarpool_ = NULL;
#endif
}

static void n2i_sysvarexarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_sysvar_ex_t* sysvarex = N2_RCAST(n2_sysvar_ex_t*, element);
	n2i_sysvarex_teardown(state, sysvarex);
}
static int n2i_sysvarexarray_matchfunc(const n2_array_t* a, const void* mkey, const void* key)
{
	N2_UNUSE(a);
	return n2_plstr_cmp_case(N2_RCAST(const n2_sysvar_ex_t*, mkey)->name_, N2_RCAST(const char*, key));
}
N2_DEFINE_TARRAY(n2_sysvar_ex_t, n2_sysvarexarray, N2_API, n2i_setupfunc_nothing, n2i_sysvarexarray_freefunc);

//=============================================================================
// モジュール

static void n2i_modvararray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_modlocalvar_t* modvar = N2_RCAST(n2_modlocalvar_t*, element);
	n2_free(state, modvar->name_);
}

static int n2i_modvararray_matchfunc(const n2_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	n2_modlocalvar_t* modvar = N2_RCAST(n2_modlocalvar_t*, ekey);
	return n2_plstr_cmp_case(modvar->name_, N2_RCAST(const char*, key));
}

N2_DEFINE_TARRAY(n2_modlocalvar_t, n2_modlocalvararray, N2_API, n2i_setupfunc_nothing, n2i_modvararray_freefunc);

static int n2i_modfuncindexset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(key);
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int lindex = *N2_RCAST(const int*, lkey);
	const int rindex = *N2_RCAST(const int*, rkey);
	const n2_func_t* lfunc = n2_functable_peek(functable, lindex);
	const n2_func_t* rfunc = n2_functable_peek(functable, rindex);
	if (!lfunc->name_ || !rfunc->name_) { return (lfunc->name_ == rfunc->name_ ? 0 : lfunc->name_ ? 1 : -1); }
	return n2_plstr_cmp_case(lfunc->name_, rfunc->name_);
}

static int n2i_modfuncindexset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int modfuncindex = *N2_RCAST(const int*, ekey);
	const n2_func_t* func = n2_functable_peek(functable, modfuncindex);
	const char* name = N2_RCAST(const char*, key);
	if (!func->name_ || !name) { return -1; }
	return n2_plstr_cmp_case(func->name_, name);
}

static void n2i_modfuncindexset_setupfunc(n2_state_t* state, n2_modfuncindexset_t* modfuncs)
{
	N2_UNUSE(state);
	modfuncs->cmp_ = n2i_modfuncindexset_cmpfunc;
	modfuncs->match_ = n2i_modfuncindexset_matchfunc;
}

N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_modfuncindexset, N2_API, n2i_modfuncindexset_setupfunc, n2i_freefunc_nothing);

static int n2i_modfuncsnameindexset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(key);
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int lindex = *N2_RCAST(const int*, lkey);
	const int rindex = *N2_RCAST(const int*, rkey);
	const n2_func_t* lfunc = n2_functable_peek(functable, lindex);
	const n2_func_t* rfunc = n2_functable_peek(functable, rindex);
	if (!lfunc->short_name_ || !rfunc->short_name_) { return (lfunc->short_name_ == rfunc->short_name_ ? 0 : lfunc->short_name_ ? 1 : -1); }
	return n2_plstr_cmp_case(lfunc->short_name_, rfunc->short_name_);
}

static int n2i_modfuncsnameindexset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	n2_functable_t* functable = N2_RCAST(n2_functable_t*, a->a_.user_);
	N2_ASSERT(functable);
	const int modfuncindex = *N2_RCAST(const int*, ekey);
	const n2_func_t* func = n2_functable_peek(functable, modfuncindex);
	const char* short_name = N2_RCAST(const char*, key);
	if (!func->short_name_ || !short_name) { return -1; }
	return n2_plstr_cmp_case(func->short_name_, short_name);
}

static void n2i_modfuncsnameindexset_setupfunc(n2_state_t* state, n2_modfuncindexset_t* modfuncs)
{
	N2_UNUSE(state);
	modfuncs->cmp_ = n2i_modfuncsnameindexset_cmpfunc;
	modfuncs->match_ = n2i_modfuncsnameindexset_matchfunc;
}

N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_modfuncsnameindexset, N2_API, n2i_modfuncsnameindexset_setupfunc, n2i_freefunc_nothing);

static void n2i_module_init(n2_state_t* state, n2_module_t* dst, const char* name)
{
	dst->name_ = NULL;
	if (name) { dst->name_ = n2_plstr_clone(state, name); }
	dst->module_id_ = -1;
	dst->pc_begin_ = -1;
	dst->modlocalvars_ = n2_modlocalvararray_alloc(state, 0, 4);
	dst->modfuncs_ = n2_modfuncindexset_alloc_user(state, 0, 4, state->environment_->functable_);// @todo isolate e
	dst->modfuncsnames_ = n2_modfuncsnameindexset_alloc_user(state, 0, 4, state->environment_->functable_);// @todo isolate e
	dst->modinit_funcindex_ = -1;
	dst->modterm_funcindex_ = -1;
	dst->alloc_callback_ = NULL;
	dst->free_callback_ = NULL;
	dst->mod_user_ = NULL;
}

static void n2i_module_teardown(n2_state_t* state, n2_module_t* emodule)
{
	if (emodule->name_) { n2_free(state, emodule->name_); emodule->name_ = NULL; }
	if (emodule->modlocalvars_) { n2_modlocalvararray_free(state, emodule->modlocalvars_); emodule->modlocalvars_ = NULL; }
	if (emodule->modfuncsnames_) { n2_modfuncsnameindexset_free(state, emodule->modfuncsnames_); emodule->modfuncsnames_ = NULL; }
	if (emodule->modfuncs_) { n2_modfuncindexset_free(state, emodule->modfuncs_); emodule->modfuncs_ = NULL; }
}

static void n2i_modulearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_module_t* emodule = N2_RCAST(n2_module_t*, element);
	n2i_module_teardown(state, emodule);
}

static int n2i_moduleindexmap_name_cmpfunc(const n2_sorted_array_t* a, const void* lmodulekey, const void* rmodulekey, const void* key)
{
	N2_UNUSE(key);
	n2_moduletable_t* moduletable = N2_RCAST(n2_moduletable_t*, a->a_.user_);
	N2_ASSERT(moduletable);
	const int* lindex = N2_RCAST(const int*, lmodulekey);
	const int* rindex = N2_RCAST(const int*, rmodulekey);
	n2_module_t* lmodule = n2_modulearray_peek(moduletable->modulearray_, *lindex);
	n2_module_t* rmodule = n2_modulearray_peek(moduletable->modulearray_, *rindex);
	if (!lmodule->name_ || !rmodule->name_) { return (lmodule->name_ == rmodule->name_ ? 0 : lmodule->name_ ? 1 : -1); }
	return n2_plstr_cmp_case(lmodule->name_, rmodule->name_);
}

static int n2i_moduleindexmap_name_matchfunc(const n2_sorted_array_t* a, const void* modulekey, const void* key)
{
	n2_moduletable_t* moduletable = N2_RCAST(n2_moduletable_t*, a->a_.user_);
	N2_ASSERT(moduletable);
	const int* moduleindex = N2_RCAST(const int*, modulekey);
	n2_module_t* emodule = n2_modulearray_peek(moduletable->modulearray_, *moduleindex);
	const char* name = N2_RCAST(const char*, key);
	if (!emodule->name_ || !name) { return -1; }
	return n2_plstr_cmp_case(emodule->name_, name);
}

static void n2i_moduleindexmap_setupfunc(n2_state_t* state, n2_moduleindexmap_t* moduleindexmap)
{
	N2_UNUSE(state);
	moduleindexmap->cmp_ = n2i_moduleindexmap_name_cmpfunc;
	moduleindexmap->match_ = n2i_moduleindexmap_name_matchfunc;
}

static void n2i_moduleindexmap_postalloc(n2_state_t* state, n2_moduletable_t* moduletable)
{
	N2_UNUSE(state);
	moduletable->moduleindexmap_->a_.user_ = moduletable;
}

N2_DEFINE_TARRAY(n2_module_t, n2_modulearray, N2_API, n2i_setupfunc_nothing, n2i_modulearray_freefunc);
N2_DEFINE_TSORTED_ARRAY(int, void, char, n2_moduleindexmap, N2_API, n2i_moduleindexmap_setupfunc, n2i_freefunc_nothing);

N2_API n2_moduletable_t* n2_moduletable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step)
{
	n2_moduletable_t* moduletable = N2_TMALLOC(n2_moduletable_t, state);
	if (!moduletable) { return NULL; }
	moduletable->modulearray_ = n2_modulearray_alloc(state, initial_buffer_size, expand_step);
	moduletable->moduleindexmap_ = n2_moduleindexmap_alloc(state, initial_buffer_size, expand_step);
	n2i_moduleindexmap_postalloc(state, moduletable);
	return moduletable;
}

N2_API void n2_moduletable_free(n2_state_t* state, n2_moduletable_t* moduletable)
{
	n2_moduleindexmap_free(state, moduletable->moduleindexmap_);
	n2_modulearray_free(state, moduletable->modulearray_);
	n2_free(state, moduletable);
}

N2_API n2_module_t* n2_moduletable_peek(n2_moduletable_t* moduletable, int index)
{
	return n2_modulearray_peek(moduletable->modulearray_, index);
}

N2_API n2_module_t* n2_moduletable_find(n2_moduletable_t* moduletable, const char* name)
{
	if (!name) { return NULL; }
	int* index = n2_moduleindexmap_find(moduletable->moduleindexmap_, name);
	if (!index) { return NULL; }
	return n2_modulearray_peek(moduletable->modulearray_, *index);
}

N2_API n2_module_t* n2_moduletable_register(n2_state_t* state, n2_moduletable_t* moduletable, const char* name)
{
	n2_module_t* emodule = NULL;
	if (name) { emodule = n2_moduletable_find(moduletable, name); }
	if (!emodule)
	{
		n2_module_t tmodule;
		n2i_module_init(state, &tmodule, name);
		int moduleindex = N2_SCAST(int, n2_modulearray_size(moduletable->modulearray_));
		emodule = n2_modulearray_push(state, moduletable->modulearray_, &tmodule);
		emodule->module_id_ = moduleindex;
		if (name) { n2_moduleindexmap_insert(state, moduletable->moduleindexmap_, &moduleindex, emodule->name_); }
	}

	return emodule;
}

N2_API void n2_modinstance_init(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule, n2_modinstance_t* instance)
{
	instance->module_id_ = emodule->module_id_;
	instance->fiber_ = f;
	instance->localvars_ = n2_vartable_alloc(state, n2_modlocalvararray_size(emodule->modlocalvars_), 1);
	for (size_t i = 0; i < n2_modlocalvararray_size(emodule->modlocalvars_); ++i)
	{
		const n2_modlocalvar_t* modvar = n2_modlocalvararray_peek(emodule->modlocalvars_, N2_SCAST(int, i));
		n2_vartable_register(state, f->environment_, instance->localvars_, modvar->name_);
	}
	instance->reference_count_ = 1;
	instance->flags_ = 0;
}

N2_API void n2_modinstance_teardown(n2_state_t* state, n2_modinstance_t* instance)
{
	//instance->fiber_ = f;// @todo modterm呼ぶ？　仕様的にmodtermはdelmod時限定のようなのでスルー
	n2_vartable_free(state, instance->localvars_);
}

static n2_modinstance_t* n2i_modinstance_create(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule)
{
	n2_modinstance_t* instance = NULL;
	if (emodule->alloc_callback_)
	{
		instance = emodule->alloc_callback_(state, f, emodule);
	}
	else
	{
		instance = N2_TMALLOC(n2_modinstance_t, state);
		n2_modinstance_init(state, f, emodule, instance);
	}
	return instance;
}

static void n2i_modinstance_destroy(n2_state_t* state, n2_modinstance_t* instance)
{
	n2_fiber_t* f = instance->fiber_;
	n2_environment_t* e = f->environment_;
	n2_module_t* emodule = n2_modulearray_peek(e->moduletable_->modulearray_, instance->module_id_);
	N2_ASSERT(emodule);
	if (emodule->free_callback_)
	{
		emodule->free_callback_(state, f, emodule, instance);
	}
	n2_modinstance_teardown(state, instance);
	n2_free(state, instance);
}

N2_API void n2_modinstance_incref(n2_state_t* state, n2_modinstance_t* instance)
{
	N2_UNUSE(state);
	N2_ASSERT(instance);
	N2_ASSERT(instance->reference_count_ >= 0);
	++instance->reference_count_;
}

N2_API void n2_modinstance_decref(n2_state_t* state, n2_modinstance_t* instance)
{
	N2_ASSERT(instance);
	--instance->reference_count_;
	N2_ASSERT(instance->reference_count_ >= 0);
	if (instance->reference_count_ == 0)
	{
		n2i_modinstance_destroy(state, instance);
	}
}

static int n2i_modinstance_term(const n2_funcarg_t* arg, n2_modinstance_t* instance)
{
	if (instance->flags_ & N2_MODINSTANCE_FLAG_TERMINATED) { n2e_funcarg_raise(arg, "モジュール変数は既に破棄されているのに再び破棄しようとしました");
return -1; }

	n2_module_t* emodule = n2_moduletable_peek(arg->fiber_->environment_->moduletable_, instance->module_id_);
	if (instance->module_id_ < 0 || !emodule) { n2e_funcarg_raise(arg, "モジュール変数を破棄しようとしましたが、モジュール変数の元モジュールを特定できません"); return -1; }

	instance->flags_ |= N2_MODINSTANCE_FLAG_TERMINATED;// ここで破棄フラグを立てる

	if (emodule->modterm_funcindex_ < 0) { return 0; }// なにも処理なし

	// 関数呼び出し
	n2_func_t* func = n2_functable_peek(arg->fiber_->environment_->functable_, emodule->modterm_funcindex_);
	N2_ASSERT(func);
	n2_modinstance_incref(arg->state_, instance);
	n2e_funcarg_pushmodinst(arg, instance);
	const size_t call_arg_num = 1;// instance分
	return n2e_funcarg_callfunc(arg, func, call_arg_num);
}

// コアモジュール
typedef struct n2i_crmodclass_instance_t n2i_crmodclass_instance_t;
struct n2i_crmodclass_instance_t
{
	n2_modinstance_t instance_;
	int refer_module_id_;
};

static n2_modinstance_t* n2i_crmodule_modclass_alloc(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule)
{
	n2i_crmodclass_instance_t* crinstance = N2_TMALLOC(n2i_crmodclass_instance_t, state);
	crinstance->refer_module_id_ = -1;
	n2_modinstance_t* instance = N2_RCAST(n2_modinstance_t*, crinstance);
	n2_modinstance_init(state, f, emodule, instance);
	return instance;
}

static void n2i_crmodule_modclass_free(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule, n2_modinstance_t* instance)
{
	N2_UNUSE(state);
	N2_UNUSE(f);
	N2_UNUSE(emodule);
	N2_UNUSE(instance);
}

//=============================================================================
// プリプロセッサ

N2_DEFINE_TARRAY(n2_pp_region_t, n2_ppregionarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

static void n2i_ppmacroparamarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_str_teardown(state, &N2_RCAST(n2_pp_macro_param_t*, element)->default_param_);
}
N2_DEFINE_TARRAY(n2_pp_macro_param_t, n2_ppmacroparamarray, N2_API, n2i_setupfunc_nothing, n2i_ppmacroparamarray_freefunc);

static void n2i_ppmacroargarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_str_teardown(state, &N2_RCAST(n2_pp_macro_arg_t*, element)->content_);
}
N2_DEFINE_TARRAY(n2_pp_macro_arg_t, n2_ppmacroargarray, N2_API, n2i_setupfunc_nothing, n2i_ppmacroargarray_freefunc);

static void n2i_ppmacroarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_pp_macro_t* macro = N2_RCAST(n2_pp_macro_t*, element);
	n2_ppmacroparamarray_free(state, macro->params_);
	n2_str_teardown(state, &macro->replacing_);
	n2_free(state, macro->name_);
}
static int n2i_ppmacroarray_matchfunc(const n2_array_t* a, const void* mkey, const void* key)
{
	N2_UNUSE(a);
	return n2_plstr_cmp_case(N2_RCAST(const n2_pp_macro_t*, mkey)->name_, N2_RCAST(const char*, key));
}
N2_DEFINE_TARRAY(n2_pp_macro_t, n2_ppmacroarray, N2_API, n2i_setupfunc_nothing, n2i_ppmacroarray_freefunc);

static int n2i_ppmoddeclareset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return n2_plstr_cmp_case(N2_RCAST(const n2_pp_module_declare_t*, lkey)->name_, N2_RCAST(const n2_pp_module_declare_t*, rkey)->name_);
}

static int n2i_ppmoddeclareset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	return n2_plstr_cmp_case(N2_RCAST(const n2_pp_module_declare_t*, ekey)->name_, N2_RCAST(const char*, key));
}

static void n2i_ppmoddeclareset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_free(state, N2_RCAST(n2_pp_module_declare_t*, element)->name_);
}

static void n2i_ppmoddeclareset_setupfunc(n2_state_t* state, n2_ppfuncdeclareset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2i_ppmoddeclareset_cmpfunc;
	a->match_ = n2i_ppmoddeclareset_matchfunc;
}

N2_DEFINE_TSORTED_ARRAY(n2_pp_module_declare_t, void, char*, n2_ppmoddeclareset, N2_API, n2i_ppmoddeclareset_setupfunc, n2i_ppmoddeclareset_freefunc);

static int n2i_ppfuncdeclareset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return n2_plstr_cmp_case(N2_RCAST(const n2_pp_func_declare_t*, lkey)->name_, N2_RCAST(const n2_pp_func_declare_t*, rkey)->name_);
}

static int n2i_ppfuncdeclareset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	return n2_plstr_cmp_case(N2_RCAST(const n2_pp_func_declare_t*, ekey)->name_, N2_RCAST(const char*, key));
}

static void n2i_ppfuncdeclareset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_free(state, N2_RCAST(n2_pp_func_declare_t*, element)->name_);
}

static void n2i_ppfuncdeclareset_setupfunc(n2_state_t* state, n2_ppfuncdeclareset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2i_ppfuncdeclareset_cmpfunc;
	a->match_ = n2i_ppfuncdeclareset_matchfunc;
}

N2_DEFINE_TSORTED_ARRAY(n2_pp_func_declare_t, void, char*, n2_ppfuncdeclareset, N2_API, n2i_ppfuncdeclareset_setupfunc, n2i_ppfuncdeclareset_freefunc);

static void n2_pp_packfile_init(n2_pp_packfile_t* packfile)
{
	packfile->sourcecode_ = NULL;
	n2_str_init(&packfile->filepath_);
	packfile->epack_ = N2_FALSE;
}

static void n2_pp_packfile_teardown(n2_state_t* state, n2_pp_packfile_t* packfile)
{
	n2_str_teardown(state, &packfile->filepath_);
}

static void n2i_pppackfilearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_pp_packfile_t* packfile = N2_RCAST(n2_pp_packfile_t*, element);
	n2_pp_packfile_teardown(state, packfile);
}

N2_DEFINE_TARRAY(n2_pp_packfile_t, n2_pppackfilearray, N2_API, n2i_setupfunc_nothing, n2i_pppackfilearray_freefunc);

static n2_pp_macro_t* n2i_pp_context_register_macro_raw(n2_state_t* state, n2_pp_context_t* ppc, const char* name, const char* replacing)
{
	n2_pp_macro_t nm;
	n2_str_t namestr;
	n2_str_init(&namestr);
	n2_naming_compute(state, name, SIZE_MAX, n2i_modulename_default, NULL, &namestr, NULL);
	nm.name_ = namestr.str_;
	n2_str_init(&nm.replacing_);
	n2_str_set(state, &nm.replacing_, replacing, SIZE_MAX);
	nm.is_ctype_ = N2_FALSE;
	nm.params_ = n2_ppmacroparamarray_alloc(state, 0, 4);

	const int emindex = n2_ppmacroarray_find(ppc->macros_, n2i_ppmacroarray_matchfunc, nm.name_);
	return emindex < 0 ? n2_ppmacroarray_push(state, ppc->macros_, &nm) : n2_ppmacroarray_replace(state, ppc->macros_, emindex, &nm);
}

static n2_pp_macro_t* n2i_pp_context_register_macro_rawfmt(n2_state_t* state, n2_pp_context_t* ppc, const char* name, const char* fmt, ...)
{
	n2_str_t replacing;
	n2_str_init(&replacing);
	va_list args;
	va_start(args, fmt);
	n2_str_vfmt_to(state, &replacing, fmt, args);
	va_end(args);
	n2_pp_macro_t* macro = n2i_pp_context_register_macro_raw(state, ppc, name, replacing.str_);
	n2_str_teardown(state, &replacing);
	return macro;
}

static n2_pp_macro_t* n2i_pp_context_register_macro_rawi(n2_state_t* state, n2_pp_context_t* ppc, const char* name, int i)
{
	return n2i_pp_context_register_macro_rawfmt(state, ppc, name, "%d", i);
}

N2_API n2_pp_directive_e n2_pp_directive_find(const char* s)
{
	static const struct
	{
		n2_pp_directive_e directive_;
		const char* word_;
	} table[] =
	{
		{N2_PP_DIRECTIVE_ERROR,		"error"},
		{N2_PP_DIRECTIVE_DEFINE,	"define"},
		{N2_PP_DIRECTIVE_UNDEF,		"undef"},
		{N2_PP_DIRECTIVE_IF,		"if"},
		{N2_PP_DIRECTIVE_IFDEF,		"ifdef"},
		{N2_PP_DIRECTIVE_IFNDEF,	"ifndef"},
		{N2_PP_DIRECTIVE_ELIF,		"elif"},
		{N2_PP_DIRECTIVE_ELSE,		"else"},
		{N2_PP_DIRECTIVE_ENDIF,		"endif"},
		{N2_PP_DIRECTIVE_ENUM,		"enum"},
		{N2_PP_DIRECTIVE_CONST,		"const"},
		{N2_PP_DIRECTIVE_ADDITION,	"addition"},
		{N2_PP_DIRECTIVE_INCLUDE,	"include"},
		{N2_PP_DIRECTIVE_DEFFUNC,	"deffunc"},
		{N2_PP_DIRECTIVE_DEFCFUNC,	"defcfunc"},
		{N2_PP_DIRECTIVE_MODULE,	"module"},
		{N2_PP_DIRECTIVE_GLOBAL,	"global"},
		{N2_PP_DIRECTIVE_MODINIT,	"modinit"},
		{N2_PP_DIRECTIVE_MODTERM,	"modterm"},
		{N2_PP_DIRECTIVE_MODFUNC,	"modfunc"},
		{N2_PP_DIRECTIVE_MODCFUNC,	"modfcunf"},
		{N2_PP_DIRECTIVE_USELIB,	"uselib"},
		{N2_PP_DIRECTIVE_FUNC,		"func"},
		{N2_PP_DIRECTIVE_CFUNC,		"cfunc"},

		{N2_PP_DIRECTIVE_BOOTOPT,	"bootopt"},
		{N2_PP_DIRECTIVE_CMPOPT,	"cmpopt"},
		{N2_PP_DIRECTIVE_PACKOPT,	"packopt"},
		{N2_PP_DIRECTIVE_PACK,		"pack"},
		{N2_PP_DIRECTIVE_EPACK,		"epack"},
		{N2_PP_DIRECTIVE_N2PACK,	"n2pack"},

		{N2_PP_DIRECTIVE_UNKNOWN,	NULL},
	};

	// 全探索
	for (size_t i = 0; table[i].word_; ++i)
	{
		if (n2_plstr_cmp_case(s, table[i].word_) == 0) { return table[i].directive_; }
	}
	return N2_PP_DIRECTIVE_UNKNOWN;
}

static const struct
{
	n2c_pp_packopt_e packopt_;
	const char* word_;
} n2ci_pp_packopt_table[] =
{
	{N2C_PP_PACKOPT_NAME,		"name"},
	{N2C_PP_PACKOPT_TYPE,		"type"},
	{N2C_PP_PACKOPT_XSIZE,		"xsize"},
	{N2C_PP_PACKOPT_YSIZE,		"ysize"},
	{N2C_PP_PACKOPT_HIDE,		"hide"},
	{N2C_PP_PACKOPT_ORGPATH,	"orgpath"},
	{N2C_PP_PACKOPT_ICON,		"icon"},
	{N2C_PP_PACKOPT_VERSION,	"version"},
	{N2C_PP_PACKOPT_MANIFEST,	"manifest"},
	{N2C_PP_PACKOPT_LANG,		"lang"},
	{N2C_PP_PACKOPT_UPX,		"upx"},
	{N2C_PP_PACKOPT_UNKNOWN,	NULL},
};

N2_API n2c_pp_packopt_e n2c_pp_packopt_find(const char* s)
{
	// 全探索
	for (size_t i = 0; n2ci_pp_packopt_table[i].word_; ++i)
	{
		if (n2_plstr_cmp_case(s, n2ci_pp_packopt_table[i].word_) == 0) { return n2ci_pp_packopt_table[i].packopt_; }
	}
	return N2C_PP_PACKOPT_UNKNOWN;
}

N2_API const char* n2c_pp_packopt_name(n2c_pp_packopt_e packopt, const char* on_not_found)
{
	// 全探索
	for (size_t i = 0; n2ci_pp_packopt_table[i].word_; ++i)
	{
		if (n2ci_pp_packopt_table[i].packopt_ == packopt) { return n2ci_pp_packopt_table[i].word_; }
	}
	return on_not_found;
}

static void n2ci_pp_packopt_init(n2c_pp_packopt_t* packopt)
{
	n2_str_init(&packopt->name_);
	packopt->type_ = 0;
	packopt->xsize_ = 640;
	packopt->ysize_ = 480;
	packopt->hide_ = N2_FALSE;
	packopt->orgpath_ = N2_FALSE;
	n2_str_init(&packopt->icon_);
	n2_str_init(&packopt->version_);
	n2_str_init(&packopt->manifest_);
	packopt->langcode_ = 1041;
	packopt->upx_ = N2_FALSE;
}

N2_API void n2c_pp_packopt_setup(n2_state_t* state, n2c_pp_packopt_t* packopt)
{
	N2_UNUSE(state);
	n2ci_pp_packopt_init(packopt);
	packopt->xsize_ = 0;
	packopt->ysize_ = 0;
}

N2_API void n2c_pp_packopt_teardown(n2_state_t* state, n2c_pp_packopt_t* packopt)
{
	n2_str_teardown(state, &packopt->name_);
	n2_str_teardown(state, &packopt->icon_);
	n2_str_teardown(state, &packopt->version_);
	n2_str_teardown(state, &packopt->manifest_);
}

N2_API n2_pp_context_t* n2_pp_context_alloc(n2_state_t* state)
{
	n2_pp_context_t* ppc = N2_TMALLOC(n2_pp_context_t, state);
	ppc->searchpaths_ = n2_plstrarray_alloc(state, 0, 4);
	ppc->macros_ = n2_ppmacroarray_alloc(state, 64, 64);
	ppc->line_ = 0;
	ppc->current_region_valid_ = N2_TRUE;
	ppc->regions_ = n2_ppregionarray_alloc(state, 8, 8);
	ppc->auto_module_next_ = 0;
	ppc->enum_next_ = 0;
	ppc->mod_decls_ = n2_ppmoddeclareset_alloc(state, 0, 16);
	ppc->current_sourcefiles_ = NULL;
	ppc->current_rootsourcecode_ = NULL;
	ppc->current_sourcecode_ = NULL;
	ppc->current_mod_decl_ = NULL;
	ppc->staging_func_decls_ = n2_ppfuncdeclareset_alloc(state, 64, 64);
	n2c_pp_packopt_setup(state, &ppc->packopt_);
	ppc->packfiles_ = n2_pppackfilearray_alloc(state, 0, 8);
	return ppc;
}

N2_API void n2_pp_context_free(n2_state_t* state, n2_pp_context_t* ppc)
{
	N2_ASSERT(ppc);
	n2_plstrarray_free(state, ppc->searchpaths_);
	n2_ppmacroarray_free(state, ppc->macros_);
	n2_ppregionarray_free(state, ppc->regions_);
	n2_ppfuncdeclareset_free(state, ppc->staging_func_decls_);
	n2_ppmoddeclareset_free(state, ppc->mod_decls_);
	ppc->current_mod_decl_ = NULL;
	n2c_pp_packopt_teardown(state, &ppc->packopt_);
	n2_pppackfilearray_free(state, ppc->packfiles_);
	n2_free(state, ppc);
}

N2_API n2_bool_t n2_pp_context_load_src_file(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* filepath, n2_str_t* dst_resolved_filepath)
{
	const size_t loadflags = N2_STATE_FSFLAG_USE_SYSTEM_FS;
	n2_bool_t res = N2_FALSE;
	n2_str_t tfilepath;
	n2_str_init(&tfilepath);
	const char* used_filepath = NULL;
	if (ppc->current_sourcecode_ && ppc->current_sourcecode_->searchpath_.size_ > 0)
	{
		n2_path_join(state, &tfilepath, ppc->current_sourcecode_->searchpath_.str_, SIZE_MAX, filepath, SIZE_MAX);
		if (n2_state_fs_load_str(state, dst, loadflags, tfilepath.str_, SIZE_MAX, 0)) { used_filepath = tfilepath.str_; res = N2_TRUE; goto exit; }
	}
	for (size_t i = 0, l = n2_plstrarray_size(ppc->searchpaths_); i < l; ++i)
	{
		const char* searchpath = n2_plstrarray_peekv(ppc->searchpaths_, N2_SCAST(int, i), NULL);
		if (!searchpath) { continue; }
		n2_path_join(state, &tfilepath, searchpath, SIZE_MAX, filepath, SIZE_MAX);
		if (n2_state_fs_load_str(state, dst, loadflags, tfilepath.str_, SIZE_MAX, 0)) { used_filepath = tfilepath.str_; res = N2_TRUE; goto exit; }
	}
	if (n2_state_fs_load_str(state, dst, loadflags, filepath, SIZE_MAX, 0)) { used_filepath = filepath; res = N2_TRUE; goto exit; }
exit:
	if (res && dst_resolved_filepath && used_filepath) { n2_str_set(state, dst_resolved_filepath, used_filepath, SIZE_MAX); }
	n2_str_teardown(state, &tfilepath);
	return res;
}

N2_API void n2_pp_context_register_default_macros(n2_state_t* state, n2_pp_context_t* ppc)
{
	n2_str_t tstr;
	n2_str_init(&tstr);

	if (state->config_.reference_hspver_ >= 0)
	{
		n2_str_fmt_to(state, &tstr, "0x%" N2_VALINT_PRI_PF "x", state->config_.reference_hspver_);
		n2i_pp_context_register_macro_raw(state, ppc, "__hspver__", tstr.str_);
	}
	if (state->config_.define_hsp30_)
	{
		n2i_pp_context_register_macro_raw(state, ppc, "__hsp30__", "");
	}
	if (state->config_.define_debug_)
	{
		n2i_pp_context_register_macro_raw(state, ppc, "__debug__", "");
	}
	{
		n2_str_fmt_to(state, &tstr, "0x%x", N2_VERSION);
		n2i_pp_context_register_macro_raw(state, ppc, "__nhspver__", tstr.str_);
	}

	n2i_pp_context_register_macro_raw(state, ppc, "M_PI", N2_STRINGIZE(N2_MPI));
	n2i_pp_context_register_macro_raw(state, ppc, "M_E", N2_STRINGIZE(N2_ME));

	{
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_nil", N2_VALUE_NIL);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_label", N2_VALUE_LABEL);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_str", N2_VALUE_STRING);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_double", N2_VALUE_FLOAT);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_int", N2_VALUE_INT);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_modinst", N2_VALUE_MODINST);
		n2i_pp_context_register_macro_rawi(state, ppc, "typeid_var", N2_VALUE_VARIABLE);
	}

	{
		n2i_pp_context_register_macro_rawi(state, ppc, "imgfile_bmp@n2", N2_IMAGE_FILE_BMP);
		n2i_pp_context_register_macro_rawi(state, ppc, "imgfile_jpg@n2", N2_IMAGE_FILE_JPG);
		n2i_pp_context_register_macro_rawi(state, ppc, "imgfile_png@n2", N2_IMAGE_FILE_PNG);
		n2i_pp_context_register_macro_rawi(state, ppc, "imgfile_tga@n2", N2_IMAGE_FILE_TGA);
	}

	{
		n2i_pp_context_register_macro_rawi(state, ppc, "texfilter_none@n2", N2S_SAMPLERFILTER_NONE);
		n2i_pp_context_register_macro_rawi(state, ppc, "texfilter_nearest@n2", N2S_SAMPLERFILTER_NEAREST);
		n2i_pp_context_register_macro_rawi(state, ppc, "texfilter_bilinear@n2", N2S_SAMPLERFILTER_BILINEAR);
		n2i_pp_context_register_macro_rawi(state, ppc, "texfilter_trilinear@n2", N2S_SAMPLERFILTER_TRILINEAR);
	}

	{
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_linear", N2_EASE_LINEAR);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quad_in", N2_EASE_QUAD_IN);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quad_out", N2_EASE_QUAD_OUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quad_inout", N2_EASE_QUAD_INOUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_cubic_in", N2_EASE_CUBIC_IN);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_cubic_out", N2_EASE_CUBIC_OUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_cubic_inout", N2_EASE_CUBIC_INOUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quartic_in", N2_EASE_QUARTIC_IN);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quartic_out", N2_EASE_QUARTIC_OUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_quartic_inout", N2_EASE_QUARTIC_INOUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_bounce_in", N2_EASE_BOUNCE_IN);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_bounce_out", N2_EASE_BOUNCE_OUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_bounce_inout", N2_EASE_BOUNCE_INOUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_shake_in", N2_EASE_SHAKE_IN);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_shake_out", N2_EASE_SHAKE_OUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_shake_inout", N2_EASE_SHAKE_INOUT);
		n2i_pp_context_register_macro_rawi(state, ppc, "ease_loop", N2_EASE_OPT_LOOP);
	}

	n2_str_teardown(state, &tstr);
}

enum n2i_pp_expand_line_flag
{
	N2I_PP_EXPAND_LINE_ENABLE_DIRECTIVES = 0x01,
	N2I_PP_EXPAND_LINE_CHECK_INLINE_DIRECTIVE = 0x02,
	N2I_PP_EXPAND_LINE_ENABLE_SPECIAL_MACROS = 0x04,
	N2I_PP_EXPAND_LINE_NO_REGION_CHECK = 0x08,

	N2I_PP_EXPAND_DEFAULT = (N2I_PP_EXPAND_LINE_ENABLE_DIRECTIVES | N2I_PP_EXPAND_LINE_CHECK_INLINE_DIRECTIVE),
	N2I_PP_EXPAND_EXPAND_ONLY = (N2I_PP_EXPAND_LINE_CHECK_INLINE_DIRECTIVE),
	N2I_PP_EXPAND_PPEXPRESSION = (N2I_PP_EXPAND_LINE_CHECK_INLINE_DIRECTIVE | N2I_PP_EXPAND_LINE_ENABLE_SPECIAL_MACROS | N2I_PP_EXPAND_LINE_NO_REGION_CHECK),
	N2I_PP_EXPAND_EXPAND_ONLY_WITHOUT_CHECK = (0)
};

static n2_bool_t n2i_pp_preprocess_line_to(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* line, int line_index, size_t flags);
static n2_bool_t n2i_pp_preprocess_line_expand_to(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* original_line, const char* line, int line_index, n2_bool_t* dst_is_replaced, size_t flags);

static void n2i_pp_context_preprocess_sync_sourcecode(n2_state_t* state, n2_pp_context_t* ppc)
{
	if (ppc->current_sourcecode_)
	{
		n2i_pp_context_register_macro_raw(state, ppc, "__file__", ppc->current_sourcecode_->package_.str_);
	}
}

static void n2i_raise_pp_exception(n2_state_t* state, n2_error_e e, n2_pp_context_t* ppc, const char* package, const char* line_head, int line, const char* fmt, ...)
{
	va_list args;

	n2_str_t tstr;
	n2_str_init(&tstr);

	n2_str_t subdescstr;
	n2_str_init(&subdescstr);

	const n2_sourcecode_t* sourcecode = NULL;
	if (ppc && ppc->current_sourcecode_)
	{
		int depth = 0;
		sourcecode = ppc->current_sourcecode_;
		const n2_sourcecode_t* cur = sourcecode;
		while (cur)
		{
			const n2_sourcecode_t* parent = cur->parent_sourcecode_;
			if (!parent) { break; }

			if (depth > 0) { n2_str_append(state, &subdescstr, "\n", SIZE_MAX); }
			n2_str_append_fmt(state, &subdescstr, "インクルード元 @@ %s(%s):%d", parent->package_.str_, parent->src_loaded_filepath_.str_, cur->parent_line_ + N2_LINE_BASE);
			cur = parent;
			++depth;
		}
	}

	n2_str_t rawmessagestr;
	n2_str_init(&rawmessagestr);
	va_start(args, fmt); n2_str_vfmt_to(state, &rawmessagestr, fmt, args); va_end(args);

	n2_str_t messagestr;
	n2_str_init(&messagestr);
	n2_str_copy_to(state, &messagestr, &rawmessagestr);
	n2i_errorinfo_append(state, &messagestr, package, line_head, line);

	n2i_do_error(state, e, sourcecode, rawmessagestr.str_, messagestr.str_, line, subdescstr.str_, NULL);

	n2_str_teardown(state, &subdescstr);
	n2_str_teardown(state, &messagestr);
	n2_str_teardown(state, &rawmessagestr);
	n2_str_teardown(state, &tstr);
}

#define N2I_PP_RAISE(state, fmt, ...) \
	n2i_raise_pp_exception(state, N2_ERROR_PREPROCESS, ppc, package, original_line, line_index, fmt, ## __VA_ARGS__)

N2_API n2_bool_t n2_pp_context_preprocess_raw(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* src)
{
	n2_str_reserve(state, dst, N2_STRLEN(src) + 1);
	n2_str_clear(dst);
	n2_str_set_expand_step(dst, 16 * 1024);

	n2_str_t line;
	n2_str_init(&line);
	n2_str_reserve(state, &line, 16 * 1024);
	n2_str_set_expand_step(&line, 1024);

	n2_str_t out_line;
	n2_str_init(&out_line);
	n2_str_reserve(state, &out_line, 16 * 1024);
	n2_str_set_expand_step(&out_line, 1024);

	n2_bool_t res = N2_TRUE;

	const char* p = src;
	for (;;)
	{
		const char* const s = p;
		const int line_index = ppc->line_;
		n2_str_clear(&line);
		const char* original_line = s;
		if (ppc->current_region_valid_)
		{
			// 論理一行を抽出する処理：かなり複雑になってきてるのでそのうちちゃんと直す
			n2_bool_t is_in_multi_line_comment = N2_FALSE;
			n2_bool_t is_in_single_string = N2_FALSE;
			n2_bool_t is_in_double_string = N2_FALSE;
			n2_bool_t is_in_multi_line_string = N2_FALSE;
			n2_bool_t is_in_string_template = N2_FALSE;
			size_t str_template_depth = 0;
			size_t str_template_levels[N2_MAX_TEMPLATE_STRING_DEPTH] = {0};
			for (;;)
			{
				if (!is_in_multi_line_string && !is_in_string_template && p[0] == '/' && p[1] == '/')
				{
					p += 2;
					while (p[0] != '\0' && p[0] != '\n') { ++p; }
					continue;
				}
				else if (!is_in_single_string && !is_in_double_string && !is_in_multi_line_string && !is_in_string_template && p[0] == '/' && p[1] == '*')
				{
					is_in_multi_line_comment = N2_TRUE;
					p += 2;
					continue;
				}
				else if (is_in_multi_line_comment && !is_in_single_string && !is_in_double_string && !is_in_multi_line_string && !is_in_string_template && p[0] == '*' && p[1] == '/')
				{
					is_in_multi_line_comment = N2_FALSE;
					p += 2;
					continue;
				}
				else if (p[0] == '\\' && p[1] == '\n')
				{
					n2_str_append(state, &line, p, 2);
					p += 2;
					++ppc->line_;
					continue;
				}
				else if (p[0] == '\n')
				{
					if (!is_in_multi_line_comment && !is_in_multi_line_string && !is_in_string_template && str_template_depth <= 0) { break; }
					++ppc->line_;
				}
				else if (!is_in_multi_line_comment && !is_in_double_string && !is_in_multi_line_string && !is_in_string_template && p[0] == '\'')
				{
					is_in_single_string = !is_in_single_string;
				}
				else if (!is_in_multi_line_comment && !is_in_single_string && !is_in_multi_line_string && !is_in_string_template && p[0] == '\"')
				{
					is_in_double_string = !is_in_double_string;
				}
				else if (!is_in_multi_line_comment && !is_in_single_string && !is_in_double_string && !is_in_string_template && p[0] == '{' && p[1] == '\"')
				{
					is_in_multi_line_string = N2_TRUE;
					n2_str_append(state, &line, p, 2);
					p += 2;
					continue;
				}
				else if (!is_in_multi_line_comment && !is_in_single_string && !is_in_double_string && is_in_multi_line_string && !is_in_string_template && p[0] == '\"' && p[1] == '}')
				{
					is_in_multi_line_string = N2_FALSE;
					n2_str_append(state, &line, p, 2);
					p += 2;
					continue;
				}
				else if (!is_in_multi_line_comment && !is_in_single_string && !is_in_double_string && !is_in_multi_line_string && p[0] == '`')
				{
					is_in_string_template = !is_in_string_template;
				}
				else if (!is_in_multi_line_comment && !is_in_single_string && !is_in_double_string && !is_in_multi_line_string && is_in_string_template && p[0] == '$' && p[1] == '{')
				{
					if (str_template_depth >= N2_MAX_TEMPLATE_STRING_DEPTH)
					{
						N2I_PP_RAISE(state, "テンプレート文字列のネストが深すぎます");
						res = N2_FALSE;
						break;
					}
					str_template_levels[str_template_depth] = 1;
					++str_template_depth;
					is_in_string_template = N2_FALSE;
					n2_str_append(state, &line, p, 2);
					p += 2;
					continue;
				}
				else if (!is_in_single_string && !is_in_double_string && !is_in_multi_line_comment && !is_in_multi_line_string && !is_in_string_template && p[0] == '}')
				{
					if (str_template_depth > 0)
					{
						if (--str_template_levels[str_template_depth - 1] == 0)
						{
							--str_template_depth;
							is_in_string_template = N2_TRUE;
						}
					}
				}
				else if (p[0] == '\0')
				{
					break;
				}

				if (!is_in_multi_line_comment) { n2_str_append(state, &line, p, 1); }
				++p;
			}
		}
		else
		{
			// 中身に意味がない可能性が高いので適当に行末まで読み流す
			while (p[0] != '\n' && p[0] != '\0') { ++p; }
			n2_str_append(state, &line, s, N2_SCAST(size_t, p - s));
		}

		if (!res) { break; }

		const char* const e = p;

		if (e > s)
		{
			n2_str_clear(&out_line);
			if (!n2i_pp_preprocess_line_to(state, ppc, &out_line, package, line.str_, line_index, N2I_PP_EXPAND_DEFAULT))
			{
				res = N2_FALSE;
				break;
			}
			n2_str_append(state, dst, out_line.str_, out_line.size_);
		}

		if (p[0] == '\0') { break; }

		n2_str_append(state, dst, "\n", SIZE_MAX);
		++p;
		++ppc->line_;
	}

	n2_str_teardown(state, &line);
	n2_str_teardown(state, &out_line);

	if (!res) { return N2_FALSE; }

	return N2_TRUE;
}

N2_API n2_bool_t n2_pp_context_preprocess_root(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, n2_sourcecode_t* rootsourcecode)
{
	N2_ASSERT(rootsourcecode);

	ppc->current_rootsourcecode_ = rootsourcecode;
	ppc->current_sourcecode_ = rootsourcecode;

	n2i_pp_context_preprocess_sync_sourcecode(state, ppc);

	if (!n2_pp_context_preprocess_raw(state, ppc, dst, rootsourcecode->package_.str_, rootsourcecode->src_script_.str_)) { return N2_FALSE; }

	// 検証
	{
		const char* package = rootsourcecode->package_.str_;

		if (n2_ppregionarray_size(ppc->regions_) > 0)
		{
			n2i_raise_as(state, N2_ERROR_PREPROCESS, rootsourcecode, package, NULL, -1, "プリプロセス：#if-#endifリージョンが正しく閉じられていません：閉じられていないリージョンの始まり（%d行目）", n2_ppregionarray_peek(ppc->regions_, -1)->begin_line_ + 1);
			return N2_FALSE;
		}

		if (ppc->current_mod_decl_)
		{
			n2i_raise_as(state, N2_ERROR_PREPROCESS, rootsourcecode, package, NULL, -1, "プリプロセス：#module で始まったモジュール（%s）定義が #gobal によって閉じられていません", ppc->current_mod_decl_->name_);
			return N2_FALSE;
		}
	}

	return N2_TRUE;
}

static n2_bool_t n2i_pp_preprocess_line_to(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* line, int line_index, size_t flags)
{
	const char* original_line = line;

	// この行番号をマクロとして登録
	{
		n2i_pp_context_register_macro_rawi(state, ppc, "__line__", line_index);
	}

	// 最初の空白をスキップ
	while (line[0] == ' ' || line[0] == '\t') { ++line; }

	// 普通の行なら展開
	if (((flags & N2I_PP_EXPAND_LINE_ENABLE_DIRECTIVES) == 0) || (line[0] != '#' || line[1] == '<')/*source orderは無視*/)
	{
		int replaced_loop = 0;

		n2_bool_t res = N2_TRUE;

		n2_str_t hold;
		n2_str_init(&hold);
		n2_str_set(state, &hold, original_line, SIZE_MAX);

		n2_str_clear(dst);

		// 展開があるならずっとループ
		for (;;)
		{
			n2_bool_t is_replaced = N2_FALSE;
			if (!n2i_pp_preprocess_line_expand_to(state, ppc, dst, package, original_line, hold.str_, line_index, &is_replaced, flags))
			{
				res = N2_FALSE;
				break;
			}
			if (!is_replaced) { break; }

			n2_str_set(state, &hold, dst->str_, dst->size_);
			n2_str_clear(dst);

			++replaced_loop;
			if (replaced_loop > 256)
			{
				N2I_PP_RAISE(state, "マクロの再起展開が上限数（%d）を突破しました、マクロが無限ループしてる可能性があります", replaced_loop);
				res = N2_FALSE;
				break;
			}

			// ループ毎に揮発するフラグ
			flags &= ~(N2I_PP_EXPAND_LINE_ENABLE_SPECIAL_MACROS);
		}

		n2_str_teardown(state, &hold);
		return res;
	}

	// 最初の#はスキップ
	++line;

	n2_bool_t res = N2_TRUE;

	n2_parser_t* p = n2_parser_alloc(state);
	n2_parser_rewind_raw(state, p, package, line);

	n2_parser_t* inner_p = NULL;

	n2_str_t inner_eval_exp;
	n2_str_init(&inner_eval_exp);
	n2_str_set_expand_step(&inner_eval_exp, 1024);

	n2_str_t inner_str;
	n2_str_init(&inner_str);

	n2_str_t inner_str_general;
	n2_str_init(&inner_str_general);

	n2_value_t* inner_ev = NULL;
	n2_ast_node_t* inner_ast = NULL;
	n2_ast_evaluate_context_t inner_ast_context;
	n2_ast_evaluate_context_init(&inner_ast_context);

	{
		const n2_token_t* st = n2_parser_read_token(state, p);
		if (st->token_ != N2_TOKEN_IDENTIFIER)
		{
			if (ppc->current_region_valid_)
			{
				N2I_PP_RAISE(state, "プリプロセス：# の後に識別子でないトークンが検出されました");
				goto fail_exit;
			}

			// 有効でないリージョンなら無効なプリプロセッサは無視
			goto exit;
		}

		const n2_pp_directive_e ppdirective = n2_pp_directive_find(st->content_);
		if (ppdirective == N2_PP_DIRECTIVE_UNKNOWN)
		{
			if (ppc->current_region_valid_)
			{
				N2I_PP_RAISE(state, "プリプロセス：想定外のプリプロセッサ（%s）", st->content_);
				goto fail_exit;
			}

			// 有効でないリージョンなら無効なプリプロセッサは無視
			goto exit;
		}

		switch (ppdirective)
		{
		case N2_PP_DIRECTIVE_ERROR:
			if (ppc->current_region_valid_)
			{
				const n2_token_t* nt = n2_parser_read_token(state, p);
				if (nt->token_ != N2_TOKEN_STRING)
				{
					N2I_PP_RAISE(state, "プリプロセス：error に失敗：error の後は文字列が必要です");
					goto fail_exit;
				}
				N2I_PP_RAISE(state, "プリプロセス：error：%s", nt->content_);
				goto fail_exit;
			}
			break;
		case N2_PP_DIRECTIVE_DEFINE:
			{
				if (ppc->current_region_valid_)
				{
					// 修飾子
					n2_bool_t is_ctype = N2_FALSE;
					n2_bool_t is_global = N2_FALSE;
					for (;;)
					{
						const n2_token_t* it = n2_parser_read_token(state, p);
						if (n2i_token_is_keyword(it, N2_KEYWORD_CTYPE))
						{
							if (is_ctype)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：ctypeが重複して指定されています");
								goto fail_exit;
							}
							is_ctype = N2_TRUE;
						}
						else if (n2i_token_is_keyword(it, N2_KEYWORD_GLOBAL))
						{
							if (is_global)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：globalが重複して指定されています");
								goto fail_exit;
							}
							is_global = N2_TRUE;
						}
						else
						{
							n2_parser_unread_token(p, 1);
							break;
						}
					}

					// 識別子
					const n2_token_t* ident = n2_parser_read_token(state, p);
					if (ident->token_ != N2_TOKEN_IDENTIFIER)
					{
						N2I_PP_RAISE(state, "プリプロセス：define に失敗：識別子名が見つかりません");
						goto fail_exit;
					}

					n2_str_t fullname;
					n2_str_init(&fullname);
					n2_naming_compute(state, ident->content_, SIZE_MAX, ppc->current_mod_decl_ && !is_global ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &fullname, NULL);

					n2_pp_macro_t* nmacro = n2i_pp_context_register_macro_raw(state, ppc, fullname.str_, "");
					nmacro->is_ctype_ = is_ctype;

					n2_str_teardown(state, &fullname);

					// パラメータあり？
					const n2_token_t* lt = n2_parser_read_token(state, p);
					if (lt->token_ == N2_TOKEN_LPARENTHESIS && !lt->left_space_)
					{
						n2_bool_t is_break = N2_FALSE;

						for (;;)
						{
							// パラメータ名チェック
							const n2_token_t* ct = n2_parser_read_token(state, p);
							if (ct->token_ == N2_TOKEN_EOF)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータのパース中に行末に到達しました");
								goto fail_exit;
							}
							if (ct->token_ == N2_TOKEN_RPARENTHESIS)
							{
								// 何もパラメータがない、おわり
								n2_parser_unread_token(p, 1);
								break;
							}
							if (ct->token_ != N2_TOKEN_PP_ARG_INDICATOR)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータは%%から始まる必要があります@@ %d行目");
								goto fail_exit;
							}

							const n2_token_t* it = n2_parser_read_token(state, p);
							if (it->token_ != N2_TOKEN_INT || it->left_space_)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータ%%のあと、スペースなしで数値を入れる必要があります");
								goto fail_exit;
							}

							const int itindex = N2_SCAST(int, N2_STRTOLL(it->content_, NULL, 0));
							if (itindex != N2_SCAST(int, n2_ppmacroparamarray_size(nmacro->params_)) + 1)
							{
								N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータ%%は順番に定義する必要があります");
								goto fail_exit;
							}

							// パラメータ生成
							n2_pp_macro_param_t* nparam = n2_ppmacroparamarray_push(state, nmacro->params_, NULL);
							n2_str_init(&nparam->default_param_);

							// デフォルトパラメータ？
							const n2_token_t* at = n2_parser_read_token(state, p);
							if (at->token_ == N2_TOKEN_ASSIGN)
							{
								// デフォルト値あり
								int parenthesis_depth = 0;
								for (;;)
								{
									const n2_token_t* nt = n2_parser_read_token(state, p);
									if (parenthesis_depth == 0 && (nt->token_ == N2_TOKEN_RPARENTHESIS || nt->token_ == N2_TOKEN_COMMA))
									{
										// ここまで食って終わり
										n2_str_set(state, &nparam->default_param_, p->tokenize_context_.script_ + at->cursor_end_, nt->cursor_begin_ - at->cursor_end_);

										if (nt->token_ == N2_TOKEN_RPARENTHESIS)
										{
											is_break = N2_TRUE;
											n2_parser_unread_token(p, 1);
										}
										break;
									}
									if (nt->token_ == N2_TOKEN_LPARENTHESIS) { ++parenthesis_depth; }
									if (nt->token_ == N2_TOKEN_RPARENTHESIS) { --parenthesis_depth; }
									if (nt->token_ == N2_TOKEN_EOF)
									{
										N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータ%%のデフォルト値を取得中、文末まで到達しました");
										goto fail_exit;
									}
								}
							}
							else
							{
								// デフォルト値なし
								if (at->token_ == N2_TOKEN_RPARENTHESIS)
								{
									n2_parser_unread_token(p, 1);
									break;
								}
								if (at->token_ != N2_TOKEN_COMMA)
								{
									N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータ%%の定義の後に不明なトークンを読み込みました（%s）", at->content_);
									goto fail_exit;
								}
							}

							if (is_break) { break; }
						}

						// 残り
						const n2_token_t* lrt = n2_parser_read_token(state, p);
						if (lrt->token_ != N2_TOKEN_RPARENTHESIS)
						{
							N2I_PP_RAISE(state, "プリプロセス：define に失敗：パラメータ%%の定義の後に不明なトークンを読み込みました（%s）。括弧が閉じられていません", lrt->content_);
							goto fail_exit;
						}

						n2_str_set(state, &nmacro->replacing_, p->tokenize_context_.script_ + lrt->cursor_end_, SIZE_MAX);
					}
					else
					{
						// パラメータなし
						n2_str_set(state, &nmacro->replacing_, p->tokenize_context_.script_ + lt->cursor_begin_, SIZE_MAX);
					}

					// 改行削除
					n2_str_replace_pattern(state, &nmacro->replacing_, "\\\n", SIZE_MAX, "\n", SIZE_MAX);
				}
			}
			break;
		case N2_PP_DIRECTIVE_UNDEF:
			if (ppc->current_region_valid_)
			{
				const n2_token_t* it = n2_parser_read_token(state, p);
				const n2_token_t* et = n2_parser_read_token(state, p);
				if ((it->token_ != N2_TOKEN_IDENTIFIER && it->token_ != N2_TOKEN_IDENTIFIER_FQ) || et->token_ != N2_TOKEN_EOF)
				{
					N2I_PP_RAISE(state, "プリプロセス：undef に失敗：構文が間違っています");
					goto fail_exit;
				}

				n2_bool_t is_erased = N2_FALSE;

				n2_naming_compute(state, it->content_, SIZE_MAX, ppc->current_mod_decl_ ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_str, NULL);
				if (n2_pp_context_erase_macro(state, ppc, inner_str.str_)) { is_erased = N2_TRUE; }

				// ローカルで見つからないならグローバルを消しにいく
				if (!is_erased && it->token_ != N2_TOKEN_IDENTIFIER_FQ && ppc->current_mod_decl_)
				{
					n2_naming_compute(state, it->content_, SIZE_MAX, n2i_modulename_default, NULL, &inner_str, NULL);
					if (n2_pp_context_erase_macro(state, ppc, inner_str.str_)) { is_erased = N2_TRUE; }
				}

#if 0
				if (!is_erased)
				{
					N2I_PP_RAISE(state, "プリプロセス：undef に失敗：（%s：フル名＝%s）が見つかりません", it->content_, inner_str.str_);
					goto fail_exit;
				}
#endif

				n2_str_clear(&inner_str);
			}
			break;
		case N2_PP_DIRECTIVE_IF:
			{
				n2_bool_t is_valid = N2_FALSE;
				if (ppc->current_region_valid_)
				{
					const char* rest_top = line + st->cursor_end_;
					n2_str_clear(&inner_eval_exp);
					if (!n2i_pp_preprocess_line_to(state, ppc, &inner_eval_exp, package, rest_top, line_index, N2I_PP_EXPAND_PPEXPRESSION))
					{
						N2I_PP_RAISE(state, "プリプロセス：if に失敗：式のプリプロセスに失敗");
						goto fail_exit;
					}

					inner_p = n2_parser_alloc(state);
					n2_parser_rewind_raw(state, inner_p, package, inner_eval_exp.str_);

					inner_p->tokenize_context_.line_ = ppc->line_;// ラインを強制的に同期

					inner_ast = n2_parser_parse_expression(state, inner_p);
					if (!inner_ast)
					{
						N2I_PP_RAISE(state, "プリプロセス：if に失敗：式のパースに失敗");
						goto fail_exit;
					}

					inner_ev = n2_ast_evaluate_immediate(state, &inner_ast_context, inner_ast);
					if (!inner_ev)
					{
						N2I_PP_RAISE(state, "プリプロセス：if に失敗：式の評価に失敗（%s）", inner_ast_context.error_.str_);
						goto fail_exit;
					}

					is_valid = n2_value_eval_bool(state, NULL, inner_ev);

					n2_value_free(state, inner_ev);
					inner_ev = NULL;

					n2_ast_node_free(state, inner_ast);
					inner_ast = NULL;

					n2_parser_free(state, inner_p);
					inner_p = NULL;
				}
				else
				{
					// 何も食わずに判断
					is_valid = N2_FALSE;
				}

				// リージョン追加
				n2_pp_region_t* region = n2_ppregionarray_push(state, ppc->regions_, NULL);
				region->is_valid_ = ppc->current_region_valid_;
				region->begin_line_ = line_index;
				region->valid_region_count_ = ppc->valid_region_count_;
				ppc->current_region_valid_ = region->is_valid_ && is_valid;
				ppc->valid_region_count_ = 0;
				if (ppc->current_region_valid_) { ++ppc->valid_region_count_; }
			}
			break;
		case N2_PP_DIRECTIVE_IFDEF:
		case N2_PP_DIRECTIVE_IFNDEF:
			{
				n2_bool_t is_valid = N2_FALSE;
				if (ppc->current_region_valid_)
				{
					const n2_token_t* it = n2_parser_read_token(state, p);
					const n2_token_t* et = n2_parser_read_token(state, p);
					if ((it->token_ != N2_TOKEN_IDENTIFIER && it->token_ != N2_TOKEN_IDENTIFIER_FQ) || et->token_ != N2_TOKEN_EOF)
					{
						N2I_PP_RAISE(state, "プリプロセス：ifdef/ifndef に失敗：構文が間違っています");
						goto fail_exit;
					}

					n2_naming_compute(state, it->content_, SIZE_MAX, ppc->current_mod_decl_ ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_str, NULL);
					if (!is_valid && n2_pp_context_find_macro(ppc, inner_str.str_)) { is_valid = N2_TRUE; }
					if (!is_valid && it->token_ != N2_TOKEN_IDENTIFIER_FQ && ppc->current_mod_decl_)
					{
						// グローバルも探しにいく
						n2_naming_compute(state, it->content_, SIZE_MAX, n2i_modulename_default, NULL, &inner_str, NULL);
						if (n2_pp_context_find_macro(ppc, inner_str.str_)) { is_valid = N2_TRUE; }
					}
					if (ppdirective == N2_PP_DIRECTIVE_IFNDEF) { is_valid = !is_valid; }
				}
				else
				{
					// 何も食わずに判断
					is_valid = N2_FALSE;
				}

				// リージョン追加
				n2_pp_region_t* region = n2_ppregionarray_push(state, ppc->regions_, NULL);
				region->is_valid_ = ppc->current_region_valid_;
				region->begin_line_ = line_index;
				region->valid_region_count_ = ppc->valid_region_count_;
				ppc->current_region_valid_ = region->is_valid_ && is_valid;
				ppc->valid_region_count_ = 0;
				if (ppc->current_region_valid_) { ++ppc->valid_region_count_; }
			}
			break;
		case N2_PP_DIRECTIVE_ELIF:
			{
				if (n2_ppregionarray_size(ppc->regions_) < 0)
				{
					N2I_PP_RAISE(state, "プリプロセス：elif に失敗：if/ifdef等で始まっていません");
					goto fail_exit;
				}

				n2_bool_t is_valid = N2_FALSE;
				if (ppc->valid_region_count_ <= 0)
				{
					const char* rest_top = line + st->cursor_end_;
					n2_str_clear(&inner_eval_exp);
					if (!n2i_pp_preprocess_line_to(state, ppc, &inner_eval_exp, package, rest_top, line_index, N2I_PP_EXPAND_PPEXPRESSION))
					{
						N2I_PP_RAISE(state, "プリプロセス：elif に失敗：式のプリプロセスに失敗");
						goto fail_exit;
					}

					inner_p = n2_parser_alloc(state);
					n2_parser_rewind_raw(state, inner_p, package, inner_eval_exp.str_);

					inner_p->tokenize_context_.line_ = ppc->line_;// ラインを強制的に同期

					inner_ast = n2_parser_parse_expression(state, inner_p);
					if (!inner_ast)
					{
						N2I_PP_RAISE(state, "プリプロセス：elif に失敗：式のパースに失敗");
						goto fail_exit;
					}

					inner_ev = n2_ast_evaluate_immediate(state, &inner_ast_context, inner_ast);
					if (!inner_ev)
					{
						N2I_PP_RAISE(state, "プリプロセス：elif に失敗：式の評価に失敗（%s）", inner_ast_context.error_.str_);
						goto fail_exit;
					}

					is_valid = n2_value_eval_bool(state, NULL, inner_ev);

					n2_value_free(state, inner_ev);
					inner_ev = NULL;

					n2_ast_node_free(state, inner_ast);
					inner_ast = NULL;

					n2_parser_free(state, inner_p);
					inner_p = NULL;
				}
				else
				{
					// 何も食わずに判断
					is_valid = N2_FALSE;
				}

				// リージョン反転
				const n2_bool_t is_prev_valid = n2_ppregionarray_size(ppc->regions_) > 0 ? n2_ppregionarray_peekc(ppc->regions_, -1)->is_valid_ : N2_TRUE;
				ppc->current_region_valid_ = is_prev_valid && is_valid;
				if (ppc->current_region_valid_) { ++ppc->valid_region_count_; }
			}
			break;
		case N2_PP_DIRECTIVE_ELSE:
			{
				const n2_token_t* et = n2_parser_read_token(state, p);
				if (et->token_ != N2_TOKEN_EOF)
				{
					N2I_PP_RAISE(state, "プリプロセス：else に失敗：else後に解析できないトークンを検出");
					goto fail_exit;
				}
				if (n2_ppregionarray_size(ppc->regions_) < 0)
				{
					N2I_PP_RAISE(state, "プリプロセス：else に失敗：if/ifdef等で始まっていません");
					goto fail_exit;
				}

				// リージョン反転
				const n2_bool_t is_prev_valid = n2_ppregionarray_peekc(ppc->regions_, -1)->is_valid_;
				ppc->current_region_valid_ = is_prev_valid && (ppc->valid_region_count_ <= 0);
				if (ppc->current_region_valid_) { ++ppc->valid_region_count_; }
			}
			break;
		case N2_PP_DIRECTIVE_ENDIF:
			{
				const n2_token_t* et = n2_parser_read_token(state, p);
				if (et->token_ != N2_TOKEN_EOF)
				{
					N2I_PP_RAISE(state, "プリプロセス：endif に失敗：endif後に解析できないトークンを検出");
					goto fail_exit;
				}
				if (n2_ppregionarray_size(ppc->regions_) <= 0)
				{
					N2I_PP_RAISE(state, "プリプロセス：endif に失敗：if ネストがされいてません");
					goto fail_exit;
				}

				// リージョン削除
				const n2_pp_region_t* prev_region = n2_ppregionarray_peek(ppc->regions_, -1);
				ppc->current_region_valid_ = prev_region->is_valid_;
				ppc->valid_region_count_ = prev_region->valid_region_count_;
				n2_ppregionarray_pop(state, ppc->regions_, 1);
			}
			break;
		case N2_PP_DIRECTIVE_ENUM:
			if (ppc->current_region_valid_)
			{
				n2_bool_t is_global = N2_FALSE;

				// globalか
				{
					const n2_token_t* rt = n2_parser_read_token(state, p);
					if (n2i_token_is_keyword(rt, N2_KEYWORD_GLOBAL))
					{
						is_global = N2_TRUE;
					}
					else
					{
						n2_parser_unread_token(p, 1);
					}
				}

				const n2_token_t* it = n2_parser_read_token(state, p);
				if (it->token_ != N2_TOKEN_IDENTIFIER)
				{
					N2I_PP_RAISE(state, "プリプロセス：enum に失敗：構文が間違っています");
					goto fail_exit;
				}
				const n2_token_t* at = n2_parser_read_token(state, p);
				if (at->token_ == N2_TOKEN_ASSIGN)
				{
					const char* rest_top = line + at->cursor_end_;
					n2_str_clear(&inner_eval_exp);
					if (!n2i_pp_preprocess_line_to(state, ppc, &inner_eval_exp, package, rest_top, line_index, N2I_PP_EXPAND_PPEXPRESSION))
					{
						N2I_PP_RAISE(state, "プリプロセス：enum に失敗：式のプリプロセスに失敗");
						goto fail_exit;
					}

					inner_p = n2_parser_alloc(state);
					n2_parser_rewind_raw(state, inner_p, package, inner_eval_exp.str_);

					inner_p->tokenize_context_.line_ = ppc->line_;// ラインを強制的に同期

					inner_ast = n2_parser_parse_expression(state, inner_p);
					if (!inner_ast)
					{
						N2I_PP_RAISE(state, "プリプロセス：enum に失敗：式のパースに失敗");
						goto fail_exit;
					}

					inner_ev = n2_ast_evaluate_immediate(state, &inner_ast_context, inner_ast);
					if (!inner_ev)
					{
						N2I_PP_RAISE(state, "プリプロセス：enum に失敗：式の評価に失敗（%s）", inner_ast_context.error_.str_);
						goto fail_exit;
					}

					ppc->enum_next_ = n2_value_eval_int(state, NULL, inner_ev);

					n2_value_free(state, inner_ev);
					inner_ev = NULL;

					n2_ast_node_free(state, inner_ast);
					inner_ast = NULL;

					n2_parser_free(state, inner_p);
					inner_p = NULL;
				}
				else
				{
					if (at->token_ != N2_TOKEN_EOF)
					{
						N2I_PP_RAISE(state, "プリプロセス：enum に失敗：enum後に解析できないトークンを検出");
						goto fail_exit;
					}
				}

				// 登録
				n2_naming_compute(state, it->content_, SIZE_MAX, ppc->current_mod_decl_ && !is_global ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_str, NULL);

				n2_pp_macro_t* nm = n2i_pp_context_register_macro_raw(state, ppc, inner_str.str_, "");
				n2_str_append_fmt(state, &nm->replacing_, "%" N2_VALINT_PRI, ppc->enum_next_);
				++ppc->enum_next_;

				n2_str_clear(&inner_str);
			}
			break;
		case N2_PP_DIRECTIVE_CONST:
			if (ppc->current_region_valid_)
			{
				// globalなどのトークン
				n2_bool_t is_global = N2_FALSE;
				n2_bool_t is_double = N2_FALSE;

				for (;;)
				{
					const n2_token_t* rt = n2_parser_read_token(state, p);
					if (n2i_token_is_keyword(rt, N2_KEYWORD_GLOBAL))
					{
						if (is_global)
						{
							N2I_PP_RAISE(state, "プリプロセス：const に失敗：globalが重複して指定されています");
							goto fail_exit;
						}
						is_global = N2_TRUE;
					}
					else if (n2i_token_is_keyword(rt, N2_KEYWORD_DOUBLE))
					{
						if (is_double)
						{
							N2I_PP_RAISE(state, "プリプロセス：const に失敗：doubleが重複して指定されています");
							goto fail_exit;
						}
						is_double = N2_TRUE;
					}
					else
					{
						n2_parser_unread_token(p, 1);
						break;
					}
				}

				const n2_token_t* it = n2_parser_read_token(state, p);
				if (it->token_ != N2_TOKEN_IDENTIFIER)
				{
					N2I_PP_RAISE(state, "プリプロセス：const に失敗：構文が間違っています、constの後には識別子が必要です");
					goto fail_exit;
				}

				const n2_token_t* nt = n2_parser_read_token(state, p);
				const char* rest_top = line + nt->cursor_begin_;
				n2_str_clear(&inner_eval_exp);
				if (!n2i_pp_preprocess_line_to(state, ppc, &inner_eval_exp, package, rest_top, line_index, N2I_PP_EXPAND_PPEXPRESSION))
				{
					N2I_PP_RAISE(state, "プリプロセス：const に失敗：式のプリプロセスに失敗");
					goto fail_exit;
				}

				inner_p = n2_parser_alloc(state);
				n2_parser_rewind_raw(state, inner_p, package, inner_eval_exp.str_);

				inner_p->tokenize_context_.line_ = ppc->line_;// ラインを強制的に同期

				inner_ast = n2_parser_parse_expression(state, inner_p);
				if (!inner_ast)
				{
					N2I_PP_RAISE(state, "プリプロセス：const に失敗：式のパースに失敗");
					goto fail_exit;
				}

				inner_ev = n2_ast_evaluate_immediate(state, &inner_ast_context, inner_ast);
				if (!inner_ev)
				{
					N2I_PP_RAISE(state, "プリプロセス：const に失敗：式の評価に失敗（%s）", inner_ast_context.error_.str_);
					goto fail_exit;
				}

				if (inner_ev->type_ == N2_VALUE_FLOAT || is_double)
				{
					n2_value_setf(state, inner_ev, n2_value_eval_float(state, NULL, inner_ev));
				}
				else
				{
					n2_value_seti(state, inner_ev, n2_value_eval_int(state, NULL, inner_ev));
				}

				// 登録
				n2_naming_compute(state, it->content_, SIZE_MAX, ppc->current_mod_decl_ && !is_global ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_str, NULL);

				n2_pp_macro_t* nm = n2i_pp_context_register_macro_raw(state, ppc, inner_str.str_, "");
				if (inner_ev->type_ == N2_VALUE_INT)
				{
					n2_str_append_fmt(state, &nm->replacing_, "%" N2_VALINT_PRI, inner_ev->field_.ivalue_);
				}
				else if (inner_ev->type_ == N2_VALUE_FLOAT)
				{
					n2_str_append_fmt(state, &nm->replacing_, "%+.18f" N2_VALFLOAT_PRI, inner_ev->field_.fvalue_);
				}
				else
				{
					N2I_PP_RAISE(state, "プリプロセス：const に失敗：マクロとして登録できない型です");
					goto fail_exit;
				}

				n2_str_clear(&inner_str);

				n2_value_free(state, inner_ev);
				inner_ev = NULL;

				n2_ast_node_free(state, inner_ast);
				inner_ast = NULL;

				n2_parser_free(state, inner_p);
				inner_p = NULL;
			}
			break;
		case N2_PP_DIRECTIVE_ADDITION:
		case N2_PP_DIRECTIVE_INCLUDE:
			if (ppc->current_region_valid_)
			{
				const n2_bool_t addition = ppdirective == N2_PP_DIRECTIVE_ADDITION;

				const n2_token_t* file = n2_parser_read_token(state, p);
				if (file->token_ != N2_TOKEN_STRING)
				{
					N2I_PP_RAISE(state, "プリプロセス：include/addition に失敗：対象が文字列ではありません");
					goto fail_exit;
				}

				const n2_token_t* et = n2_parser_read_token(state, p);
				if (et->token_ != N2_TOKEN_EOF)
				{
					N2I_PP_RAISE(state, "プリプロセス：include/addition に失敗：include後に解析できないトークンを検出");
					goto fail_exit;
				}

				// ファイルを取得
				const char* filepackage = file->content_;
				const char* filesrc = NULL;

				if (n2_pp_context_load_src_file(state, ppc, &inner_eval_exp, filepackage, &inner_str_general))
				{
					// 自動エンコード
					if (!n2i_sourcecode_autoencode_src(state, &inner_eval_exp))
					{
						N2I_PP_RAISE(state, "プリプロセス：include/addition したファイル（%s）をutf8として読み取れません（自動エンコードも失敗）", file->content_);
						goto fail_exit;
					}

					filesrc = inner_eval_exp.str_;
				}

				if (!filesrc && !addition)
				{
					N2I_PP_RAISE(state, "プリプロセス：include/addition に失敗：ファイル（%s）が見つかりません", file->content_);
					goto fail_exit;
				}

				// 読み込まれていたら
				if (filesrc)
				{
					// include関係をpush
					int include_index = 0;
					if (ppc->current_sourcecode_)
					{
						n2_sourcecode_t* parent_sourcecode = ppc->current_sourcecode_;
						include_index = N2_SCAST(int, n2_sourcecodearray_size(parent_sourcecode->sourcecodes_));
						n2_sourcecode_t* next_sourcecode = n2_sourcecode_alloc(state);
						next_sourcecode->parent_sourcecode_ = parent_sourcecode;
						next_sourcecode->parent_line_ = line_index;
						n2_sourcecodearray_pushv(state, parent_sourcecode->sourcecodes_, next_sourcecode);
						ppc->current_sourcecode_ = next_sourcecode;
						// パス情報を解析
						n2_str_set(state, &next_sourcecode->src_filepath_, filepackage, SIZE_MAX);
						n2_str_copy_to(state, &next_sourcecode->src_loaded_filepath_, &inner_str_general);
						n2_path_split(state, &next_sourcecode->searchpath_, NULL, NULL, &next_sourcecode->src_loaded_filepath_);// inner_strは後でも使うので短期的にのみ使う
						n2_path_basename(state, &next_sourcecode->src_filename_, &next_sourcecode->src_filepath_, NULL, 0);
						n2_str_copy_to(state, &next_sourcecode->package_, &next_sourcecode->src_filename_);
						n2_str_clear(&inner_str);
						filepackage = next_sourcecode->package_.str_;// パッケージはファイル名のみ
						// ソースファイルへ追加
						if (ppc->current_sourcefiles_)
						{
							n2_sourcefilearray_register_sourcecode(state, ppc->current_sourcefiles_, next_sourcecode);
						}
						// 次の解析のため
						n2i_pp_context_preprocess_sync_sourcecode(state, ppc);
					}

					// ファイルの先を展開
					const int prev_line_indx = ppc->line_;
					ppc->line_ = 0;
					if (!n2_pp_context_preprocess_raw(state, ppc, &inner_str, filepackage, filesrc))
					{
						// 既にエラーは送出されているのでスルー
						ppc->line_ = prev_line_indx;
						goto fail_exit;
					}
					ppc->line_ = prev_line_indx;

					// くっつける
					n2_str_append_fmt(state, dst, "#<include_push %d \"%s\"\n", include_index, filepackage);// ファイルの先端
					n2_str_append(state, dst, inner_str.str_, inner_str.size_);
					n2_str_append_fmt(state, dst, "\n");
					n2_str_append_fmt(state, dst, "#<include_pop %d", line_index);// 最後に改行は要らない（勝手につく）

					// pop
					if (ppc->current_sourcecode_)
					{
						ppc->current_sourcecode_ = ppc->current_sourcecode_->parent_sourcecode_;
						N2_ASSERT(ppc->current_sourcecode_);
						// 解析終わったがもう一度同期
						n2i_pp_context_preprocess_sync_sourcecode(state, ppc);
					}
				}

				// 後片付け
				n2_str_clear(&inner_eval_exp);
				n2_str_clear(&inner_str);
				n2_str_clear(&inner_str_general);
			}
			break;
		case N2_PP_DIRECTIVE_DEFFUNC:
		case N2_PP_DIRECTIVE_DEFCFUNC:
		case N2_PP_DIRECTIVE_MODINIT:
		case N2_PP_DIRECTIVE_MODTERM:
		case N2_PP_DIRECTIVE_MODFUNC:
		case N2_PP_DIRECTIVE_MODCFUNC:
		case N2_PP_DIRECTIVE_FUNC:
		case N2_PP_DIRECTIVE_CFUNC:
			if (ppc->current_region_valid_)
			{
				const char* directivename = st->content_;

				n2_bool_t is_modfunc = N2_FALSE;
				n2_bool_t is_dlfunc = N2_FALSE;
				n2_bool_t is_noname = N2_FALSE;

				switch (ppdirective)
				{
				case N2_PP_DIRECTIVE_DEFFUNC:
				case N2_PP_DIRECTIVE_DEFCFUNC:
					break;
				case N2_PP_DIRECTIVE_MODINIT:
				case N2_PP_DIRECTIVE_MODTERM:
					is_modfunc = N2_TRUE;
					is_noname = N2_TRUE;
					break;
				case N2_PP_DIRECTIVE_MODFUNC:
				case N2_PP_DIRECTIVE_MODCFUNC:
					is_modfunc = N2_TRUE;
					break;
				case N2_PP_DIRECTIVE_FUNC:
				case N2_PP_DIRECTIVE_CFUNC:
					is_dlfunc = N2_TRUE;
					break;
				default:
					N2_ASSERT(0);
					break;
				}

				// globalかlocal
				const n2_token_t* lgt = n2_parser_read_token(state, p);
				if (n2i_token_is_keyword(lgt, N2_KEYWORD_LOCAL) || n2i_token_is_keyword(lgt, N2_KEYWORD_GLOBAL))
				{
				}
				else
				{
					n2_parser_unread_token(p, 1);
					lgt = NULL;
				}

				n2_str_t fullname;
				n2_str_init(&fullname);

				if (!is_noname)
				{
					// 先読みで関数名をとるだけ
					const n2_token_t* it = n2_parser_read_token(state, p);
					if (it->token_ != N2_TOKEN_IDENTIFIER)
					{
						N2I_PP_RAISE(state, "プリプロセス：%s に失敗：関数名が識別子ではありません", directivename);
						n2_str_teardown(state, &fullname);
						goto fail_exit;
					}

					const char* func_name = it->content_;

					n2_naming_compute(state, func_name, SIZE_MAX, ppc->current_mod_decl_ ? ppc->current_mod_decl_->name_ : NULL, NULL, &fullname, NULL);

					const char* fullname_cstr = fullname.str_;
					if (n2_ppfuncdeclareset_find(ppc->staging_func_decls_, &fullname_cstr))
					{
						N2I_PP_RAISE(state, "プリプロセス：%s しようとした関数（%s）が既に定義されています", directivename, fullname.str_);
						n2_str_teardown(state, &fullname);
						goto fail_exit;
					}

					{
						n2_pp_func_declare_t func_decl;
						func_decl.name_ = n2_plstr_clone(state, fullname.str_);
						n2_ppfuncdeclareset_insert(state, ppc->staging_func_decls_, &func_decl, NULL);
					}

					// global ならエイリアス関数も作成
					if (lgt && n2i_token_is_keyword(lgt, N2_KEYWORD_GLOBAL) && ppc->current_mod_decl_)
					{
						n2_naming_compute(state, func_name, SIZE_MAX, NULL, NULL, &fullname, NULL);

						fullname_cstr = fullname.str_;
						if (n2_ppfuncdeclareset_find(ppc->staging_func_decls_, &fullname_cstr))
						{
							N2I_PP_RAISE(state, "プリプロセス：%s しようとした関数（%s）が既に定義されています", directivename, fullname.str_);
							n2_str_teardown(state, &fullname);
							goto fail_exit;
						}

						{
							n2_pp_func_declare_t func_decl;
							func_decl.name_ = n2_plstr_clone(state, fullname.str_);
							n2_ppfuncdeclareset_insert(state, ppc->staging_func_decls_, &func_decl, NULL);
						}
					}
				}

				// プリプロセスなしで展開させる
				if (!n2i_pp_preprocess_line_to(state, ppc, dst, package, original_line, line_index, N2I_PP_EXPAND_EXPAND_ONLY_WITHOUT_CHECK))
				{
					n2_str_teardown(state, &fullname);
					goto fail_exit;
				}

				n2_str_teardown(state, &fullname);
			}
			break;
		case N2_PP_DIRECTIVE_MODULE:
			if (ppc->current_region_valid_)
			{
				if (ppc->current_mod_decl_)
				{
					N2I_PP_RAISE(state, "プリプロセス：#module でモジュールを定義しようとしましたがまだ直前のモジュール（%s）が閉じられていません", ppc->current_mod_decl_->name_);
					goto fail_exit;
				}

				const n2_token_t* ident = n2_parser_read_token(state, p);

				n2_str_clear(&inner_str);

				if (ident->token_ == N2_TOKEN_EOF)
				{
					// 省略
					n2_str_fmt_to(state, &inner_str, "_m%d", ppc->auto_module_next_);
					++ppc->auto_module_next_;
					n2_parser_unread_token(p, 1);
				}
				else if (ident->token_ == N2_TOKEN_IDENTIFIER || ident->token_ == N2_TOKEN_STRING)
				{
					n2_str_set(state, &inner_str, ident->content_, SIZE_MAX);
				}
				else
				{
					N2I_PP_RAISE(state, "プリプロセス：#module モジュール名が認識できません");
					goto fail_exit;
				}

				const char* inner_str_cstr = inner_str.str_;
				if (n2_ppmoddeclareset_find(ppc->mod_decls_, &inner_str_cstr))
				{
					N2I_PP_RAISE(state, "プリプロセス：#module モジュール（%s）は既に定義されています", inner_str.str_);
					goto fail_exit;
				}

				if (!n2_naming_verify_modulename(inner_str.str_, SIZE_MAX))
				{
					N2I_PP_RAISE(state, "プリプロセス：#module モジュール（%s）はモジュール名として不適切です", inner_str.str_);
					goto fail_exit;
				}

				{
					n2_pp_module_declare_t mod_decl;
					mod_decl.name_ = n2_plstr_clone(state, inner_str.str_);
					ppc->current_mod_decl_ = n2_ppmoddeclareset_insert(state, ppc->mod_decls_, &mod_decl, NULL);
				}

				// 名前まではこの形でくっつける
				n2_str_fmt_to(state, dst, "#module %s ", inner_str.str_);

				// この後をプリプロセスなしで展開させる
				if (ident->token_ != N2_TOKEN_EOF)
				{
					n2_str_clear(&inner_eval_exp);
					if (!n2i_pp_preprocess_line_expand_to(state, ppc, &inner_eval_exp, package, original_line, line + ident->cursor_end_, line_index, NULL, N2I_PP_EXPAND_EXPAND_ONLY))
					{
						goto fail_exit;
					}
					if (inner_eval_exp.size_ > 0)
					{
						n2_str_append(state, dst, inner_eval_exp.str_, SIZE_MAX);
					}
				}
			}
			break;
		case N2_PP_DIRECTIVE_GLOBAL:
			if (ppc->current_region_valid_)
			{
				if (!ppc->current_mod_decl_)
				{
					N2I_PP_RAISE(state, "プリプロセス：#global でモジュールを閉じようとしましたが、まだモジュール定義が始まっていません");
					goto fail_exit;
				}
				ppc->current_mod_decl_ = NULL;

				// プリプロセスなしで展開させる
				if (!n2i_pp_preprocess_line_to(state, ppc, dst, package, original_line, line_index, N2I_PP_EXPAND_EXPAND_ONLY_WITHOUT_CHECK))
				{
					goto fail_exit;
				}
			}
			break;

		case N2_PP_DIRECTIVE_USELIB:
			if (ppc->current_region_valid_)
			{
				const n2_token_t* path = n2_parser_read_token(state, p);
				if (path->token_ != N2_TOKEN_STRING)
				{
					N2I_PP_RAISE(state, "プリプロセス：uselib の後には動的ライブラリのパスが必要です");
					goto fail_exit;
				}

				const n2_token_t* et = n2_parser_read_token(state, p);
				if (et->token_ != N2_TOKEN_EOF)
				{
					N2I_PP_RAISE(state, "プリプロセス：uselib に失敗：uselib後に解析できないトークンを検出");
					goto fail_exit;
				}

				// プリプロセスなしで展開させる
				if (!n2i_pp_preprocess_line_to(state, ppc, dst, package, original_line, line_index, N2I_PP_EXPAND_EXPAND_ONLY_WITHOUT_CHECK))
				{
					goto fail_exit;
				}
			}
			break;

		case N2_PP_DIRECTIVE_BOOTOPT:
			if (ppc->current_region_valid_)
			{
				N2I_PP_RAISE(state, "プリプロセス：#bootopt は未サポートです");
				goto fail_exit;
			}
			break;
		case N2_PP_DIRECTIVE_CMPOPT:
			if (ppc->current_region_valid_)
			{
				N2I_PP_RAISE(state, "プリプロセス：#cmpopt は未サポートです");
				goto fail_exit;
			}
			break;
		case N2_PP_DIRECTIVE_PACKOPT:
			if (ppc->current_region_valid_)
			{
				// 対象
				const n2_token_t* label = n2_parser_read_token(state, p);
				const n2c_pp_packopt_e packopt = n2c_pp_packopt_find(label->content_);
				if (packopt == N2C_PP_PACKOPT_UNKNOWN)
				{
					N2I_PP_RAISE(state, "プリプロセス：#packopt に不明なキーワード（%s）が指定されました", label->content_ ? "<NULL>" : label->content_);
					goto fail_exit;
				}

				// パラメータ
				const n2_token_t* packarg = n2_parser_read_token(state, p);

				switch (packopt)
				{
				case N2C_PP_PACKOPT_NAME:
					if (packarg->token_ != N2_TOKEN_STRING)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード name には文字列のみ指定できます（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					n2_str_set(state, &ppc->packopt_.name_, packarg->content_, SIZE_MAX);
					break;
				case N2C_PP_PACKOPT_TYPE:
					if (packarg->token_ != N2_TOKEN_INT)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード type には数値のみ指定できます（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					ppc->packopt_.type_ = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
					if (ppc->packopt_.type_ < N2C_PP_PACKOPT_TYPE_MIN || ppc->packopt_.type_ > N2C_PP_PACKOPT_TYPE_MAX)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード type の数値が不正です（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					break;
				case N2C_PP_PACKOPT_XSIZE:
				case N2C_PP_PACKOPT_YSIZE:
					{
						if (packarg->token_ != N2_TOKEN_INT)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード xsize/ysize には数値のみ指定できます（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						const int val = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
						if (val < N2S_WINDOW_SIZE_MIN || val > N2S_WINDOW_SIZE_MAX)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード xsize/ysize の数値が不正です（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						if (ppdirective == N2C_PP_PACKOPT_XSIZE) { ppc->packopt_.xsize_ = N2_SCAST(size_t, val); }
						else { ppc->packopt_.ysize_ = N2_SCAST(size_t, val); }
					}
					break;
				case N2C_PP_PACKOPT_HIDE:
					{
						if (packarg->token_ != N2_TOKEN_INT)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード hide には数値のみ指定できます（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						const int val = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
						ppc->packopt_.hide_ = val == 0 ? N2_FALSE : N2_TRUE;
					}
					break;
				case N2C_PP_PACKOPT_ORGPATH:
					{
						if (packarg->token_ != N2_TOKEN_INT)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード orgpath には数値のみ指定できます（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						const int val = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
						ppc->packopt_.orgpath_ = val == 0 ? N2_FALSE : N2_TRUE;
					}
					break;
				case N2C_PP_PACKOPT_ICON:
					if (packarg->token_ != N2_TOKEN_STRING)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード icon には文字列のみ指定できます（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					n2_str_set(state, &ppc->packopt_.icon_, packarg->content_, SIZE_MAX);
					break;
				case N2C_PP_PACKOPT_VERSION:
					if (packarg->token_ != N2_TOKEN_STRING)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード version には文字列のみ指定できます（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					n2_str_set(state, &ppc->packopt_.version_, packarg->content_, SIZE_MAX);
					break;
				case N2C_PP_PACKOPT_MANIFEST:
					if (packarg->token_ != N2_TOKEN_STRING)
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード manifest には文字列のみ指定できます（%sが指定されました）", packarg->content_);
						goto fail_exit;
					}
					{
						N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード manifest は未サポートです");
						goto fail_exit;
					}
					//n2_str_set(state, &ppc->packopt_.manifest_, packarg->content_, SIZE_MAX);
					break;
				case N2C_PP_PACKOPT_LANG:
					{
						if (packarg->token_ != N2_TOKEN_INT)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード lang には数値のみ指定できます（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						const int val = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
						if (val < 0)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード lang の数値が不正です（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						ppc->packopt_.langcode_ = N2_SCAST(size_t, val);
					}
					break;
				case N2C_PP_PACKOPT_UPX:
					{
						if (packarg->token_ != N2_TOKEN_INT)
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード upx には数値のみ指定できます（%sが指定されました）", packarg->content_);
							goto fail_exit;
						}
						{
							N2I_PP_RAISE(state, "プリプロセス：#packopt のキーワード upx は未サポートです");
							goto fail_exit;
						}
						//const int val = N2_SCAST(int, N2_STRTOLL(packarg->content_, NULL, 0));
						//ppc->packopt_.upx_ = val == 0 ? N2_FALSE : N2_TRUE;
					}
					break;
				default:
					N2_ASSERT(0);
					break;
				}
			}
			break;
		case N2_PP_DIRECTIVE_PACK:
		case N2_PP_DIRECTIVE_EPACK:
			if (ppc->current_region_valid_)
			{
				const n2_bool_t is_epack = ppdirective == N2_PP_DIRECTIVE_EPACK;

				const n2_token_t* file = n2_parser_read_token(state, p);
				if (file->token_ != N2_TOKEN_STRING)
				{
					N2I_PP_RAISE(state, "プリプロセス：#pack/#epack の後は文字列でファイルを指定する必要があります");
					goto fail_exit;
				}

				n2_pp_packfile_t packfile;
				n2_pp_packfile_init(&packfile);
				packfile.sourcecode_ = ppc->current_sourcecode_;
				n2_str_set(state, &packfile.filepath_, file->content_, SIZE_MAX);
				packfile.epack_ = is_epack;

				n2_pppackfilearray_push(state, ppc->packfiles_, &packfile);
			}
			break;

		case N2_PP_DIRECTIVE_N2PACK:
			if (ppc->current_region_valid_)
			{
				N2I_PP_RAISE(state, "プリプロセス：#n2pack は未実装です");
				goto fail_exit;
			}
			break;

		default:
			N2_ASSERT(0);
			break;
		}
	}

	goto exit;

fail_exit:
	res = N2_FALSE;

exit:
	n2_ast_evaluate_context_teardown(state, &inner_ast_context);
	if (inner_ast) { n2_ast_node_free(state, inner_ast); inner_ast = NULL; }
	if (inner_ev) { n2_value_free(state, inner_ev); inner_ev = NULL; }
	n2_str_teardown(state, &inner_str);
	n2_str_teardown(state, &inner_str_general);
	n2_str_teardown(state, &inner_eval_exp);
	if (inner_p) { n2_parser_free(state, inner_p); inner_p = NULL; }

	n2_parser_free(state, p);

	return res;
}

static n2_bool_t n2i_pp_preprocess_line_expand_to(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* original_line, const char* line, int line_index, n2_bool_t* dst_is_replaced, size_t flags)
{
	// このディレクティブが無効なら何もしない
	if (!ppc->current_region_valid_ && (flags & N2I_PP_EXPAND_LINE_NO_REGION_CHECK) == 0)
	{
		if (dst_is_replaced) { *dst_is_replaced = N2_FALSE; }
		return N2_TRUE;
	}

	// マクロ展開
	n2_parser_t* p = n2_parser_alloc(state);
	n2_parser_rewind_raw(state, p, package, line);
	p->tokenize_context_.line_ = line_index;
	int prev_line_index = p->tokenize_context_.line_;

	n2_str_clear(dst);

	n2_ppmacroargarray_t* macroargs = NULL;
	n2_parser_t* inner_p = NULL;
	n2_str_t inner_identname;
	n2_str_init(&inner_identname);

	n2_bool_t is_replaced = N2_FALSE;
	{
		const n2_token_t* prev = NULL;

		for (;;)
		{
			const n2_token_t* st = n2_parser_read_token(state, p);
			if (st->token_ == N2_TOKEN_ERROR) { goto fail_exit; }

			// 行違いなのでマクロ再定義
			if (st->appear_line_ != prev_line_index)
			{
				n2i_pp_context_register_macro_rawi(state, ppc, "__line__", p->tokenize_context_.line_);
			}

			// このトークンより前の雑多なものをコピー
			if (prev)
			{
				const int len = st->cursor_begin_ - prev->cursor_end_;
				if (len > 0)
				{
					n2_str_append(state, dst, line + prev->cursor_end_, N2_SCAST(size_t, len));
				}
			}

			prev = st;

			// もう終わった？
			if (st->token_ == N2_TOKEN_EOF) { break; }

			// 特殊マクロ
			if (flags & N2I_PP_EXPAND_LINE_ENABLE_SPECIAL_MACROS && st->token_ == N2_TOKEN_IDENTIFIER)
			{
				const char* ident = st->content_;
				if (n2_plstr_cmp_case(ident, "defined") == 0)
				{
					const n2_token_t* lp = n2_parser_read_token(state, p);
					if (lp->token_ != N2_TOKEN_LPARENTHESIS) { lp = NULL; n2_parser_unread_token(p, 1); }

					const n2_token_t* macroname = n2_parser_read_token(state, p);
					if (macroname->token_ != N2_TOKEN_IDENTIFIER && macroname->token_ != N2_TOKEN_IDENTIFIER_FQ)
					{
						N2I_PP_RAISE(state, "プリプロセス：マクロ展開（defined）：対象のマクロ名（%s）が不正です", macroname->content_);
						goto fail_exit;
					}

					// マクロ検索
					const n2_pp_macro_t* macro = NULL;

					n2_naming_compute(state, macroname->content_, SIZE_MAX, ppc->current_mod_decl_ ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_identname, NULL);
					macro = n2_pp_context_find_macro(ppc, inner_identname.str_);

					if (!macro && macroname->token_ != N2_TOKEN_IDENTIFIER_FQ && ppc->current_mod_decl_)
					{
						n2_naming_compute(state, macroname->content_, SIZE_MAX, n2i_modulename_default, NULL, &inner_identname, NULL);
						macro = n2_pp_context_find_macro(ppc, inner_identname.str_);
					}

					if (lp)
					{
						const n2_token_t* rp = n2_parser_read_token(state, p);
						if (rp->token_ != N2_TOKEN_RPARENTHESIS)
						{
							N2I_PP_RAISE(state, "プリプロセス：マクロ展開（defined）：丸括弧が閉じられていません");
							goto fail_exit;
						}
					}

					// 結果に応じて0/1
					n2_str_append_fmt(state, dst, " %d ", macro ? 1 : 0);

					// 次の取得用にずらしておく
					prev = n2_parser_read_token(state, p);
					n2_parser_unread_token(p, 1);

					is_replaced = N2_TRUE;
					continue;
				}
			}

			// Identifierなら置き換えの余地あり
			if (st->token_ == N2_TOKEN_IDENTIFIER || st->token_ == N2_TOKEN_IDENTIFIER_FQ)
			{
				// マクロ検索
				const n2_pp_macro_t* macro = NULL;

				n2_naming_compute(state, st->content_, SIZE_MAX, ppc->current_mod_decl_ ? ppc->current_mod_decl_->name_ : n2i_modulename_default, NULL, &inner_identname, NULL);
				macro = n2_pp_context_find_macro(ppc, inner_identname.str_);

				if (!macro && st->token_ != N2_TOKEN_IDENTIFIER_FQ && ppc->current_mod_decl_)
				{
					n2_naming_compute(state, st->content_, SIZE_MAX, n2i_modulename_default, NULL, &inner_identname, NULL);
					macro = n2_pp_context_find_macro(ppc, inner_identname.str_);
				}

				// マクロ置き換え？
				if (macro)
				{
					// パラメータあり？
					if (n2_ppmacroparamarray_size(macro->params_) > 0)
					{
						// パラメータ取得
						macroargs = n2_ppmacroargarray_alloc(state, 4, 8);

						// パラメータ取得検証
						if (macro->is_ctype_)
						{
							const n2_token_t* lt = n2_parser_read_token(state, p);
							if (lt->token_ != N2_TOKEN_LPARENTHESIS)
							{
								N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）：ctypeと定義されていますが、引数が括弧で始まっていません", macro->name_);
								goto fail_exit;
							}
						}
						else
						{
							const n2_token_t* nst = n2_parser_read_token(state, p);
							n2_parser_unread_token(p, 1);

							if (!nst->left_space_ && (nst->token_ != N2_TOKEN_EOS && nst->token_ != N2_TOKEN_EOF))
							{
								N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）：ctypeと定義されていないマクロ展開において、マクロの後にスペースが存在しません", macro->name_);
								goto fail_exit;
							}
						}

						// 実際の取得ここから
						for (;;)
						{
							const n2_token_t* nst = n2_parser_read_token(state, p);
							n2_parser_unread_token(p, 1);

							n2_bool_t is_break = N2_FALSE;
							int parenthesis_depth = 0;

							for (;;)
							{
								const n2_token_t* nt = n2_parser_read_token(state, p);
								if (nt->token_ == N2_TOKEN_EOS || nt->token_ == N2_TOKEN_EOF )
								{
									if (parenthesis_depth > 0 || macro->is_ctype_)
									{
										N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：パラメータ読み取り中に、予期しないステートメントの終わり（:）か行末に到達しました", macro->name_);
										goto fail_exit;
									}

									// ここまで食う
									n2_pp_macro_arg_t* ma = n2_ppmacroargarray_push(state, macroargs, NULL);
									n2_str_init(&ma->content_);

									// 引数省略
									if (nst != nt)
									{
										n2_str_set(state, &ma->content_, line + nst->cursor_begin_, nt->cursor_begin_ - nst->cursor_begin_);
									}

									n2_parser_unread_token(p, 1);
									is_break = N2_TRUE;
									break;
								}

								const n2_bool_t is_rp_end = (macro->is_ctype_ && nt->token_ == N2_TOKEN_RPARENTHESIS);
								if (parenthesis_depth == 0 && (is_rp_end || nt->token_ == N2_TOKEN_COMMA))
								{
									// ここまで食う
									n2_pp_macro_arg_t* ma = n2_ppmacroargarray_push(state, macroargs, NULL);
									n2_str_init(&ma->content_);

									// 引数省略
									if (nst != nt)
									{
										n2_str_set(state, &ma->content_, line + nst->cursor_begin_, nt->cursor_begin_ - nst->cursor_begin_);
									}

									if (is_rp_end)
									{
										n2_parser_unread_token(p, 1);// 食いすぎなので戻す
										is_break = N2_TRUE;
									}
									break;
								}

								if (nt->token_ == N2_TOKEN_LPARENTHESIS) { ++parenthesis_depth; }
								if (nt->token_ == N2_TOKEN_RPARENTHESIS) { --parenthesis_depth; }

								if (nt->token_ == N2_TOKEN_EOF)
								{
									if (macro->is_ctype_)
									{
										N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：ctypeで定義されていますが、括弧の終わりがみつかりません", macro->name_);
										goto fail_exit;
									}

									// ここまで食う
									n2_pp_macro_arg_t* ma = n2_ppmacroargarray_push(state, macroargs, NULL);
									n2_str_init(&ma->content_);

									// 引数省略
									if (nst != nt)
									{
										n2_str_set(state, &ma->content_, line + nst->cursor_begin_, SIZE_MAX);
									}

									is_break = N2_TRUE;
									break;
								}
							}

							if (is_break) { break; }
						}

						// 引数閉じ終わり？
						if (macro->is_ctype_)
						{
							const n2_token_t* rt = n2_parser_read_token(state, p);
							if (rt->token_ != N2_TOKEN_RPARENTHESIS)
							{
								N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：ctypeと定義されていますが、引数が括弧で終わっていません", macro->name_);
								goto fail_exit;
							}
						}

						// 次の取得用にずらしておく
						prev = n2_parser_read_token(state, p);
						n2_parser_unread_token(p, 1);

						// 省略チェック
						for (size_t i = 0, l = n2_ppmacroparamarray_size(macro->params_); i <l; ++i)
						{
							const n2_pp_macro_param_t* mp = n2_ppmacroparamarray_peek(macro->params_, N2_SCAST(int, i));
							const n2_pp_macro_arg_t* ma = n2_ppmacroargarray_peek(macroargs, N2_SCAST(int, i));
							if ((!ma || ma->content_.size_ <= 0) && mp->default_param_.size_ <= 0)
							{
								N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：%zu番目の引数は省略できません", macro->name_, i + 1);
								goto fail_exit;
							}
						}

						// 置き換え
						{
							inner_p = n2_parser_alloc(state);
							n2_parser_rewind_raw(state, inner_p, package, macro->replacing_.str_);

							const n2_token_t* iprev = NULL;
							for (;;)
							{
								const n2_token_t* ist = n2_parser_read_token(state, inner_p);
								if (ist->token_ == N2_TOKEN_EOF) { break; }

								if (ist->token_ == N2_TOKEN_PP_ARG_INDICATOR)
								{
									const n2_token_t* it = n2_parser_read_token(state, inner_p);
									if (it->token_ != N2_TOKEN_INT || it->left_space_)
									{
										N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：展開後のパラメータ%%のあと、スペースなしで数値を入れる必要があります", macro->name_);
										goto fail_exit;
									}

									const n2_valint_t itindex = N2_SCAST(n2_valint_t, N2_STRTOLL(it->content_, NULL, 0) - 1);
									if (itindex < 0 || itindex > N2_SCAST(n2_valint_t, n2_ppmacroparamarray_size(macro->params_)))
									{
										N2I_PP_RAISE(state, "プリプロセス：マクロ展開（%s）に失敗：パラメータ%が存在しません", macro->name_);
										goto fail_exit;
									}
									const n2_pp_macro_param_t* mp = n2_ppmacroparamarray_peek(macro->params_, N2_SCAST(int, itindex));
									N2_ASSERT(mp);
									const n2_pp_macro_arg_t* ma = n2_ppmacroargarray_peek(macroargs, N2_SCAST(int, itindex));

									n2_str_append(state, dst, ma && ma->content_.size_ > 0 ? ma->content_.str_ : mp->default_param_.str_, SIZE_MAX);
									iprev = it;
								}
								else
								{
									if (iprev)
									{
										n2_str_append(state, dst, macro->replacing_.str_ + iprev->cursor_end_, ist->cursor_begin_ - iprev->cursor_end_);
									}
									n2_str_append(state, dst, macro->replacing_.str_ + ist->cursor_begin_, ist->cursor_end_ - ist->cursor_begin_);
									iprev = ist;
								}
							}

							if (iprev)
							{
								n2_str_append(state, dst, macro->replacing_.str_ + iprev->cursor_end_, SIZE_MAX);
							}

							n2_parser_free(state, inner_p);
							inner_p = NULL;
						}

						n2_ppmacroargarray_free(state, macroargs);
						macroargs = NULL;
					}
					else
					{
						// 単純置き換え
						n2_str_append(state, dst, macro->replacing_.str_, SIZE_MAX);
					}

					is_replaced = N2_TRUE;
					continue;
				}
			}

			// 行頭にないプリプロセッサの検出
			if (flags & N2I_PP_EXPAND_LINE_CHECK_INLINE_DIRECTIVE)
			{
				if (st->token_ == N2_TOKEN_PP_INDICATOR)
				{
					const n2_token_t* nt = n2_parser_read_token(state, p);
					if (n2_pp_directive_find(nt->content_) != N2_PP_DIRECTIVE_UNKNOWN)
					{
						N2I_PP_RAISE(state, "行頭にないプリプロセッサ（%s）は不正です", nt->content_);
						goto fail_exit;
					}

					// そうでないものは一旦無視（将来の拡張性に残しておく、stringizeなど）
					n2_parser_unread_token(p, 1);
				}
			}

			// このトークンの中身をそのままコピー
			n2_str_append(state, dst, line + st->cursor_begin_, st->cursor_end_ - st->cursor_begin_);
			continue;
		}
	}

	n2_str_teardown(state, &inner_identname);
	if (inner_p) { n2_parser_free(state, inner_p); inner_p = NULL; }
	if (macroargs) { n2_ppmacroargarray_free(state, macroargs); }
	n2_parser_free(state, p);

	if (dst_is_replaced) { *dst_is_replaced = is_replaced; }
	return N2_TRUE;

fail_exit:
	n2_str_teardown(state, &inner_identname);
	if (inner_p) { n2_parser_free(state, inner_p); inner_p = NULL; }
	if (macroargs) { n2_ppmacroargarray_free(state, macroargs); }
	n2_parser_free(state, p);
	return N2_FALSE;
}

#undef N2_PP_RAISE

N2_API const n2_pp_macro_t* n2_pp_context_find_macro(n2_pp_context_t* ppc, const char* name)
{
	const int emindex = n2_ppmacroarray_find(ppc->macros_, n2i_ppmacroarray_matchfunc, name);
	return emindex < 0 ? NULL : n2_ppmacroarray_peek(ppc->macros_, emindex);
}

N2_API n2_bool_t n2_pp_context_register_macro(n2_state_t* state, n2_pp_context_t* ppc, const char* name, const char* replacing)
{
	n2i_pp_context_register_macro_raw(state, ppc, name, replacing);
	return N2_TRUE;
}

N2_API n2_bool_t n2_pp_context_erase_macro(n2_state_t* state, n2_pp_context_t* ppc, const char* name)
{
	const int emindex = n2_ppmacroarray_find(ppc->macros_, n2i_ppmacroarray_matchfunc, name);
	if (emindex < 0) { return N2_FALSE; }
	n2_ppmacroarray_erase(state, ppc->macros_, emindex);
	return N2_TRUE;
}

N2_API void n2_pp_context_clear_staging(n2_state_t* state, n2_pp_context_t* ppc)
{
	n2_ppfuncdeclareset_clear(state, ppc->staging_func_decls_);

	ppc->current_rootsourcecode_ = NULL;
	ppc->current_sourcecode_ = NULL;
	ppc->current_mod_decl_ = NULL;
}

//=============================================================================
// 動的ライブラリ
static void n2i_uselib_setup(n2_state_t* state, n2_uselib_t* uselib, const char* path)
{
	uselib->path_ = n2_plstr_clone(state, path);
	n2_intarray_setup(state, &uselib->func_indices_, 0, 8);
	uselib->dynlib_ = NULL;
}

static void n2i_uselib_teardown(n2_state_t* state, n2_uselib_t* uselib)
{
	if (uselib->path_) { n2_free(state, uselib->path_); uselib->path_ = NULL; }
	n2_intarray_teardown(state, &uselib->func_indices_);
	if (uselib->dynlib_) { n2h_dynlib_free(state, uselib->dynlib_); uselib->dynlib_ = NULL; }
}

static void n2i_uselibarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_uselib_t* uselib = N2_RCAST(n2_uselib_t*, element);
	n2i_uselib_teardown(state, uselib);
}
N2_DEFINE_TARRAY(n2_uselib_t, n2_uselibarray, N2_API, n2i_setupfunc_nothing, n2i_uselibarray_freefunc);

//=============================================================================
// n2標準機能
#if 1
#define N2SI_IS_FLIP_V			(1)
#define N2SI_FLIP_V_OR(v, or)	(v)
#define N2SI_FLIP_VS(v, s)		((s) - (v))
#define N2SI_FLIP_V(v)			(1.f - (v))
#else
#define N2SI_IS_FLIP_V			(0)
#define N2SI_FLIP_V_OR(v, or)	(or)
#define N2SI_FLIP_VS(v, s)		(v)
#define N2SI_FLIP_V(v)			(v)
#endif

#if N2_CONFIG_USE_SDL_LIB
static const char* n2si_glerror_str(GLenum err_id)
{
	switch (err_id)
	{
	case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
	case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
	case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
	case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
	}
	return "<unknown error>";
}

static n2_bool_t n2si_glerror_check(n2_state_t* state)
{
	if (!state->config_.enable_graphics_assert_) { return N2_TRUE; }
	const GLenum glerr = glGetError();
	if (glerr == GL_NO_ERROR) { return N2_TRUE; }
	n2i_lprintf(state, NULL, N2_LOG_LEVEL_CRITICAL, "glError : %s\n", n2si_glerror_str(glerr));
	return N2_FALSE;
}

static n2_bool_t n2si_glerror_clear(n2_state_t* state)
{
	if (!state->config_.enable_graphics_assert_) { return N2_FALSE; }
	n2_bool_t has_error = N2_FALSE;
	for (;;)
	{
		const GLenum glerr = glGetError();
		if (glerr == GL_NO_ERROR) { break; }
		has_error = N2_TRUE;
	}
	return has_error;
}

#define N2SI_ASSERT_GL(state) \
	N2_ASSERT(n2si_glerror_check(state))

#define N2SI_GL_CLEAR_ERRORS(state) \
	n2si_glerror_clear(state)
#endif

static n2s_u8color_t N2S_COLOR_WHITE = {{255, 255, 255, 255}};
static n2s_u8color_t N2S_COLOR_BLACK = {{0, 0, 0, 255}};
//static n2s_u8color_t N2S_COLOR_ZERO = {{0, 0, 0, 0}};

N2_API n2s_u8color_t n2s_u8color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	n2s_u8color_t res;
	res.r_ = r; res.g_ = g; res.b_ = b; res.a_ = a;
	return res;
}

static N2_INLINE uint8_t n2si_u8channel_clamp(int v)
{
	return N2_SCAST(uint8_t, v < 0 ? 0 : v > 255 ? 255 : v);
}

N2_API n2s_u8color_t n2s_u8color_clamp(int r, int g, int b, int a)
{
	return n2s_u8color(n2si_u8channel_clamp(r), n2si_u8channel_clamp(g), n2si_u8channel_clamp(b), n2si_u8channel_clamp(a));
}

N2_API n2s_fcolor_t n2s_fcolor(float r, float g, float b, float a)
{
	n2s_fcolor_t res;
	res.r_ = r; res.g_ = g; res.b_ = b; res.a_ = a;
	return res;
}

static N2_INLINE float n2si_fchannel_clamp(float v)
{
	return n2_float_saturate(v);
}

N2_API n2s_fcolor_t n2s_fcolor_clamp(float r, float g, float b, float a)
{
	return n2s_fcolor(n2si_fchannel_clamp(r), n2si_fchannel_clamp(g), n2si_fchannel_clamp(b), n2si_fchannel_clamp(a));
}

static N2_INLINE uint8_t n2si_fchannel_to_u8channel(float v)
{
	return n2si_u8channel_clamp(N2_SCAST(int, N2_ROUND(N2_SCAST(double, v) * 255.0)));
}

static N2_INLINE float n2si_u8channel_to_fchannel(uint8_t v)
{
	return N2_SCAST(float, v) / 255.f;
}

N2_API n2s_u8color_t n2s_fcolor_to_u8color(n2s_fcolor_t fcolor)
{
	return n2s_u8color(n2si_fchannel_to_u8channel(fcolor.r_), n2si_fchannel_to_u8channel(fcolor.g_), n2si_fchannel_to_u8channel(fcolor.b_), n2si_fchannel_to_u8channel(fcolor.a_));
}

N2_API n2s_fcolor_t n2s_u8color_to_fcolor(n2s_u8color_t u8color)
{
	return n2s_fcolor(n2si_u8channel_to_fchannel(u8color.r_), n2si_u8channel_to_fchannel(u8color.g_), n2si_u8channel_to_fchannel(u8color.b_), n2si_u8channel_to_fchannel(u8color.a_));
}

N2_API n2s_fcolor_t n2s_hsv_to_fcolor(n2_fvec3_t hsv, float a)
{
	const float h = n2_float_saturate(hsv.x_);
	const float s = n2_float_saturate(hsv.y_);
	const float v = n2_float_saturate(hsv.z_);

	const float h6 = h * 6;
	const int h6i = N2_SCAST(int, h6);
	const float h6f = h6 - N2_SCAST(float, h6i);
	const float h6fr = 1.f - h6f;

	float r, g, b;
	switch (h6i)
	{
	case 1:	r = v * (1 - s * h6f), g = v, b = v * (1 - s); break;
	case 2:	r = v * (1 - s), g = v, b = v * (1 - s * h6fr); break;
	case 3:	r = v * (1 - s), g = v * (1 - s * h6f), b = v; break;
	case 4:	r = v * (1 - s * h6fr), g = v * (1 - s), b = v; break;
	case 5:	r = v, g = v * (1 - s), b = v * (1 - s * h6f); break;
	case 0: default:	r = v, g = v * (1 - s * h6fr), b = v * (1 - s); break;
	}

	return n2s_fcolor(r, g, b, a);
}

N2_API n2_fvec3_t n2s_fcolor_to_hsv(n2s_fcolor_t fcolor)
{
	const float r = n2_float_saturate(fcolor.r_);
	const float g = n2_float_saturate(fcolor.g_);
	const float b = n2_float_saturate(fcolor.b_);
	const float cmax = r > g ? (r > b ? r : b) : (g > b ? g : b);
	const float cmin = r < g ? (r < b ? r : b) : (g < b ? g : b);
	const float d = cmax - cmin;
	const float d6 = d * 6;

	float h;
	if (d <= 0.f) { h = 0.f; }
	else if (cmax == r) { h = (g - b) / d6; if (h < 0) { h += 1; } }
	else if (cmax == g) { h = 1.f / 3.f + (b - r) / d6; }
	else { h = 2.f / 3.f + (r - g) / d6; }

	float s = cmax <= 0 ? 0 : d / cmax;
	float v = cmax;

	return n2_fvec3(h, s, v);
}

N2_API n2_bool_t n2s_uv_clamp_pixel(n2_fvec2_t* uv0, n2_fvec2_t* uv1, size_t w, size_t h)
{
	if (w <= 0 || h <= 0) { return N2_FALSE; }
	const n2_fvec2_t pixel_uv_half = n2_fvec2(0.5f / N2_SCAST(float, w), 0.5f / N2_SCAST(float, h));
	n2_fvec2_t iuv0 = n2_fvec2_min(*uv0, *uv1);
	n2_fvec2_t iuv1 = n2_fvec2_max(*uv0, *uv1);
	*uv0 = n2_fvec2_add(iuv0, pixel_uv_half);
	*uv1 = n2_fvec2_sub(iuv1, pixel_uv_half);
	return N2_TRUE;
}

N2_API void n2s_vertex_uv_clamp_to(n2s_vertex_t* dst, n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color, n2_fvec2_t uvc0, n2_fvec2_t uvc1)
{
	dst->position_ = position;
	dst->uv_ = uv;
	dst->color_ = color;
	dst->uv_clamp_ = n2_fvec4(uvc0.x_, uvc0.y_, uvc1.x_, uvc1.y_);
}

N2_API void n2s_vertex_to(n2s_vertex_t* dst, n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color)
{
	n2s_vertex_uv_clamp_to(dst, position, uv, color, n2_fvec2(0, 0), n2_fvec2(1, 1));
}

N2_API n2s_vertex_t n2s_vertex(n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color)
{
	n2s_vertex_t res;
	n2s_vertex_to(&res, position, uv, color);
	return res;
}

N2_API void n2s_vertex_set_uv_clamp_direct_to(n2s_vertex_t* dst, n2_fvec2_t uv0, n2_fvec2_t uv1)
{
	dst->uv_clamp_.xy_ = uv0;
	dst->uv_clamp_.zw_ = uv1;
}

N2_API void n2s_vertex_set_uv_clamp_pixel(n2s_vertex_t* dst, n2_fvec2_t uv0, n2_fvec2_t uv1, size_t w, size_t h)
{
	n2s_uv_clamp_pixel(&uv0, &uv1, w, h);
	n2s_vertex_set_uv_clamp_direct_to(dst, uv0, uv1);
}

N2_DEFINE_TARRAY(n2s_vertex_t, n2s_vertexarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

N2_DEFINE_TARRAY(n2s_index_t, n2s_indexarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

#if N2_CONFIG_USE_GUI_LIB
static void* n2si_nk_plugin_alloc(nk_handle user, void* old, nk_size size)
{
	n2_state_t* state = N2_RCAST(n2_state_t*, user.ptr);
	N2_UNUSE(old);
	//if (old) { return n2_xrealloc(state, size, old); }
	return n2_xmalloc(state, size);
}

static void n2si_nk_plugin_free(nk_handle user, void* old)
{
	n2_state_t* state = N2_RCAST(n2_state_t*, user.ptr);
	n2_xfree(state, old);
}
#endif

static void n2si_texture_apply_samplerfilter(n2_state_t* state, n2s_texture_t* tx, n2s_samplerfilter_e samplerfilter)
{
	N2_UNUSE(state);
#if N2_CONFIG_USE_SDL_LIB
	glBindTexture(GL_TEXTURE_2D, tx->gl_texture_);
	switch (samplerfilter)
	{
	case N2S_SAMPLERFILTER_NEAREST:
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case N2S_SAMPLERFILTER_BILINEAR:
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case N2S_SAMPLERFILTER_TRILINEAR:
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case N2S_SAMPLERFILTER_NONE:
	default:
		break;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	N2SI_ASSERT_GL(state);
#else
	N2_UNUSE(tx);
	N2_UNUSE(samplerfilter);
#endif
}

static void n2si_texture_reinstantinate(n2_state_t* state, n2s_texture_t* tx)
{
#if N2_CONFIG_USE_SDL_LIB
	glBindTexture(GL_TEXTURE_2D, tx->gl_texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, N2_SCAST(GLsizei, tx->width_), N2_SCAST(GLsizei, tx->height_), 0, GL_RGBA, GL_UNSIGNED_BYTE, tx->imagebuf_.data_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	N2SI_ASSERT_GL(state);
#endif
	n2si_texture_apply_samplerfilter(state, tx, tx->samplerfilter_);
}

static void n2si_texture_init(n2_state_t* state, n2s_texture_t* tx, size_t width, size_t height, const void* data)
{
	n2_str_init(&tx->name_);
	tx->width_ = width;
	tx->height_ = height;
	n2_buffer_init(&tx->imagebuf_);
	tx->samplerfilter_ = N2S_SAMPLERFILTER_BILINEAR;

	const size_t bytesize = width * height * 4;
	n2_buffer_reserve(state, &tx->imagebuf_, bytesize);
	if (data)
	{
		n2_buffer_append(state, &tx->imagebuf_, data, bytesize);
	}
	else
	{
		n2_buffer_append_values(state, &tx->imagebuf_, 0xff, bytesize);
	}

	n2s_texture_dirty_clear(tx);

#if N2_CONFIG_USE_SDL_LIB
	glGenTextures(1, &tx->gl_texture_);
	n2si_texture_reinstantinate(state, tx);
#endif
}

static void n2si_texture_teardown(n2_state_t* state, n2s_texture_t* tx)
{
#if N2_CONFIG_USE_SDL_LIB
	glDeleteTextures(1, &tx->gl_texture_);
	N2SI_ASSERT_GL(state);
#endif

	n2_buffer_teardown(state, &tx->imagebuf_);
	n2_str_teardown(state, &tx->name_);
}

static n2s_texture_t* n2si_texture_alloc(n2_state_t* state, size_t width, size_t height, const void* data)
{
	n2s_texture_t* tx = N2_TMALLOC(n2s_texture_t, state);
	n2si_texture_init(state, tx, width, height, data);
	return tx;
}

static void n2si_texture_free(n2_state_t* state, n2s_texture_t* tx)
{
	n2si_texture_teardown(state, tx);
	n2_free(state, tx);
}

N2_API n2_bool_t n2s_texture_set_samplerfilter(n2_state_t* state, n2s_texture_t* tx, n2s_samplerfilter_e samplerfilter)
{
	if (tx->samplerfilter_ == samplerfilter) { return N2_FALSE; }
	tx->samplerfilter_ = samplerfilter;
	n2si_texture_apply_samplerfilter(state, tx, tx->samplerfilter_);
	return N2_TRUE;
}

N2_API void n2s_texture_dirty_clear(n2s_texture_t* tx)
{
	tx->dirty_begin_y_ = SIZE_MAX;
	tx->dirty_end_y_ = 0;
}

N2_API void n2s_texture_dirty_all(n2s_texture_t* tx)
{
	tx->dirty_begin_y_ = 0;
	tx->dirty_end_y_ = tx->height_;
}

N2_API void n2s_texture_dirty_range(n2s_texture_t* tx, size_t begin_y, size_t end_y)
{
	if (begin_y < tx->dirty_begin_y_) { tx->dirty_begin_y_ = begin_y; }
	if (end_y > tx->dirty_end_y_) { tx->dirty_end_y_ = end_y; }
}

N2_API void n2s_texture_fill_color(n2s_texture_t* tx, n2s_u8color_t color)
{
	if (tx->width_ <= 0 || tx->height_ <= 0) { return; }
	// fill first line
	for (size_t x = 0; x < tx->width_; ++x) { N2_MEMCPY(n2_ptr_offset(tx->imagebuf_.data_, x * 4), color.e_, 4); }
	// copy to all other line
	for (size_t y = 1; y < tx->height_; ++y) { N2_MEMCPY(n2_ptr_offset(tx->imagebuf_.data_, tx->width_ * 4), tx->imagebuf_.data_, tx->width_ * 4); }
	n2s_texture_dirty_all(tx);
}

N2_API void n2s_texture_render_buffer(n2s_texture_t* tx, const n2_buffer_t* rendertxbuf, size_t rendertxwidth, size_t rendertxheight, int renderx, int rendery, n2s_u8color_t mulcolor)
{
	if (tx->width_ <= 0 || tx->height_ <= 0) { return; }
	if (rendertxwidth <= 0 || rendertxheight <= 0) { return; }
	const int render_endx = renderx + N2_SCAST(int, rendertxwidth);
	const int render_endy = rendery + N2_SCAST(int, rendertxheight);
	if (renderx >= N2_SCAST(int, tx->width_) || rendery >= N2_SCAST(int, tx->height_) || render_endx < 0 || render_endy < 0) { return; }
	const int beginx = N2_MAX(renderx, 0), beginy = N2_MAX(rendery, 0), endx = N2_MIN(render_endx, N2_SCAST(int, tx->width_)), endy = N2_MIN(render_endy, N2_SCAST(int, tx->height_));
	const int render_offsetx = beginx - renderx, render_offsety = beginy - rendery;
	for (int y = beginy; y < endy; ++y)
	{
		for (int x = beginx; x < endx; ++x)
		{
			const uint8_t* src = n2_ptr_offset(rendertxbuf->data_, (((render_offsety + (y - beginy)) * N2_SCAST(int, rendertxwidth)) + (render_offsetx + (x - beginx))) * 4);
			uint8_t* dst = n2_ptr_offset(tx->imagebuf_.data_, (y * N2_SCAST(int, tx->width_) + x) * 4);
			const uint8_t srca = src[3] * mulcolor.a_ / 255;
			const uint8_t invsrca = 255 - srca;
			dst[0] = src[0] * srca * mulcolor.r_ / 255 / 255 + dst[0] * invsrca / 255;
			dst[1] = src[1] * srca * mulcolor.g_ / 255 / 255 + dst[1] * invsrca / 255;
			dst[2] = src[2] * srca * mulcolor.b_ / 255 / 255 + dst[2] * invsrca / 255;
			dst[3] = srca + dst[3] * invsrca / 255;
		}
	}
	n2s_texture_dirty_range(tx, N2_SCAST(size_t, beginy), N2_SCAST(size_t, endy));
}

N2_API void n2s_texture_render(n2s_texture_t* tx, const n2s_texture_t* rendertx, int renderx, int rendery, n2s_u8color_t mulcolor)
{
	if (!rendertx) { return; }
	n2s_texture_render_buffer(tx, &rendertx->imagebuf_, rendertx->width_, rendertx->height_, renderx, rendery, mulcolor);
}

N2_API void n2s_texture_copy_buffer(n2s_texture_t* tx, const n2_buffer_t* srctxbuf, size_t srctxwidth, size_t srctxheight, int renderx, int rendery)
{
	if (tx->width_ <= 0 || tx->height_ <= 0) { return; }
	if (srctxwidth <= 0 || srctxheight <= 0) { return; }
	const int render_endx = renderx + N2_SCAST(int, srctxwidth);
	const int render_endy = rendery + N2_SCAST(int, srctxheight);
	if (renderx >= N2_SCAST(int, tx->width_) || rendery >= N2_SCAST(int, tx->height_) || render_endx < 0 || render_endy < 0) { return; }
	const int beginx = N2_MAX(renderx, 0), beginy = N2_MAX(rendery, 0), endx = N2_MIN(render_endx, N2_SCAST(int, tx->width_)), endy = N2_MIN(render_endy, N2_SCAST(int, tx->height_));
	const int render_offsetx = beginx - renderx, render_offsety = beginy - rendery;
	for (int y = beginy; y < endy; ++y)
	{
		for (int x = beginx; x < endx; ++x)
		{
			const uint8_t* src = n2_ptr_offset(srctxbuf->data_, (((render_offsety + (y - beginy)) * N2_SCAST(int, srctxwidth)) + (render_offsetx + (x - beginx))) * 4);
			uint8_t* dst = n2_ptr_offset(tx->imagebuf_.data_, (y * N2_SCAST(int, tx->width_) + x) * 4);
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
		}
	}
	n2s_texture_dirty_range(tx, N2_SCAST(size_t, beginy), N2_SCAST(size_t, endy));
}

N2_API n2_bool_t n2s_texture_submit(n2_state_t* state, n2s_texture_t* tx, n2_bool_t force_submit_all)
{
	N2_UNUSE(state);
	n2_bool_t res = N2_FALSE;
	if (force_submit_all)
	{
		tx->dirty_begin_y_ = 0;
		tx->dirty_end_y_ = tx->height_;
	}
	if (tx->dirty_begin_y_ < tx->dirty_end_y_)
	{
#if N2_CONFIG_USE_SDL_LIB
		glBindTexture(GL_TEXTURE_2D, tx->gl_texture_);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, N2_SCAST(GLint, tx->dirty_begin_y_), N2_SCAST(GLsizei, tx->width_), N2_SCAST(GLsizei, tx->dirty_end_y_ - tx->dirty_begin_y_), GL_RGBA, GL_UNSIGNED_BYTE, n2_ptr_offset(tx->imagebuf_.data_, tx->dirty_begin_y_ * tx->width_ * 4));
		glBindTexture(GL_TEXTURE_2D, 0);
		N2SI_ASSERT_GL(state);
#endif
		res = N2_TRUE;
	}
	tx->dirty_begin_y_ = SIZE_MAX;
	tx->dirty_end_y_ = 0;
	return res;
}

N2_API n2_bool_t n2s_texture_resize(n2_state_t* state, n2s_texture_t* tx, size_t width, size_t height, n2_bool_t keep_content)
{
	if (tx->width_ == width && tx->height_ == height) { return N2_TRUE; }
	if (width <= 0 || height <= 0 || width >= N2S_WINDOW_SIZE_MAX || height >= N2S_WINDOW_SIZE_MAX) { return N2_FALSE; }
	n2_buffer_t nimagebuf;
	n2_buffer_init(&nimagebuf);
	const size_t bytesize = width * height * 4;
	if (!n2_buffer_reserve(state, &nimagebuf, bytesize)) { return N2_FALSE; }
	n2_buffer_append_values(state, &nimagebuf, 0xff, bytesize);
	if (keep_content)
	{
		for (size_t y = 0; y < tx->height_; ++y)
		{
			N2_MEMCPY(n2_ptr_offset(nimagebuf.data_, y * width * 4), n2_cptr_offset(tx->imagebuf_.data_, y * tx->width_ * 4), tx->width_ * 4);
		}
	}
	tx->width_ = width;
	tx->height_ = height;
	n2_buffer_swap(&tx->imagebuf_, &nimagebuf);
	n2si_texture_reinstantinate(state, tx);
	n2s_texture_dirty_clear(tx);
	n2_buffer_teardown(state, &nimagebuf);
	return N2_TRUE;
}

N2_API n2_bool_t n2s_texture_save_to(n2_state_t* state, n2_buffer_t* dst, const n2s_texture_t* texture, n2_image_file_e imagefile)
{
	if (texture->width_ <= 0 || texture->height_ <= 0) { return N2_FALSE; }
#if N2_CONFIG_USE_IMAGE_WRITE_LIB
	return n2h_image_write(state, dst, imagefile, texture->imagebuf_.data_, texture->imagebuf_.size_, texture->width_, texture->height_, 100);
#else
	N2_UNUSE(state);
	N2_UNUSE(dst);
	N2_UNUSE(imagefile);
	return N2_FALSE;
#endif
}

static n2s_texturebuffer_t* n2si_texturebuffer_alloc(n2_state_t* state, size_t width, size_t height)
{
	n2s_texturebuffer_t* tb = N2_TMALLOC(n2s_texturebuffer_t, state);

#if N2_CONFIG_USE_SDL_LIB
	glGenFramebuffers(1, &tb->gl_framebuffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, tb->gl_framebuffer_);
#endif

	n2si_texture_init(state, &tb->texture_, width, height, NULL);

#if N2_CONFIG_USE_SDL_LIB
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, tb->texture_.gl_texture_);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tb->texture_.gl_texture_, 0);
	N2_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	N2SI_ASSERT_GL(state);
#endif
	return tb;
}

static void n2si_texturebuffer_free(n2_state_t* state, n2s_texturebuffer_t* tb)
{
#if N2_CONFIG_USE_SDL_LIB
	glDeleteFramebuffers(1, &tb->gl_framebuffer_);
	N2SI_ASSERT_GL(state);
#endif

	n2si_texture_teardown(state, &tb->texture_);
	n2_free(state, tb);
}

static n2_bool_t n2si_texturebuffer_resize(n2_state_t* state, n2s_texturebuffer_t* tb, size_t width, size_t height, n2_bool_t keep_content)
{
	return n2s_texture_resize(state, &tb->texture_, width, height, keep_content);
}

static n2_bool_t n2si_texturebuffer_clear(n2_state_t* state, n2s_texturebuffer_t* tb, n2s_u8color_t color)
{
	N2_UNUSE(state);
#if N2_CONFIG_USE_SDL_LIB
	glBindFramebuffer(GL_FRAMEBUFFER, tb->gl_framebuffer_);
	const n2s_fcolor_t fcolor = n2s_u8color_to_fcolor(color);
	glClearColor(fcolor.r_, fcolor.g_, fcolor.b_, fcolor.a_);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	N2SI_ASSERT_GL(state);
	return N2_TRUE;
#else
	N2_UNUSE(tb);
	N2_UNUSE(color);
	return N2_FALSE;
#endif
}

N2_API n2_bool_t n2s_texturebuffer_read(n2_state_t* state, n2s_texturebuffer_t* tb)
{
	N2_UNUSE(state);
#if N2_CONFIG_USE_SDL_LIB
	glBindFramebuffer(GL_FRAMEBUFFER, tb->gl_framebuffer_);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glReadPixels(0, 0, N2_SCAST(GLsizei, tb->texture_.width_), N2_SCAST(GLsizei, tb->texture_.height_), GL_RGBA, GL_UNSIGNED_BYTE, tb->texture_.imagebuf_.data_);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	N2SI_ASSERT_GL(state);
	return N2_TRUE;
#else
	return N2_FALSE;
#endif
}

static int n2si_glyphset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	if (lkey && rkey) { return N2_RCAST(const n2s_glyph_t*, lkey)->codepoint_ - N2_RCAST(const n2s_glyph_t*, rkey)->codepoint_; }
	N2_ASSERT(key);
	const void* ekey = lkey ? lkey : rkey;
	return N2_SCAST(int, N2_RCAST(const n2s_glyph_t*, ekey)->codepoint_ - *N2_RCAST(const n2_codepoint_t*, key)) * (lkey ? 1: -1);
}

static int n2si_glyphset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	return N2_RCAST(const n2s_glyph_t*, ekey)->codepoint_ - *N2_RCAST(const n2_codepoint_t*, key);
}

static void n2si_glyphset_setupfunc(n2_state_t* state, n2s_fontset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2si_glyphset_cmpfunc;
	a->match_ = n2si_glyphset_matchfunc;
}

N2_DEFINE_TSORTED_ARRAY(n2s_glyph_t, n2_codepoint_t, n2_codepoint_t, n2s_glyphset, N2_API, n2si_glyphset_setupfunc, n2i_freefunc_nothing);

static void n2si_fontdata_init(n2s_fontdata_t* fontdata)
{
	n2_buffer_init(&fontdata->fontbinary_);
	fontdata->pixel_scaling_ = 0;
	fontdata->pixel_ascent_ = 0;
	fontdata->pixel_descent_ = 0;
	fontdata->pixel_linegap_ = 0;
	fontdata->pixel_strict_lineheight_ = 0;
#if N2_CONFIG_USE_FONT_LIB
	fontdata->fontinfo_ = NULL;
#endif
}

static void n2si_fontdata_teardown(n2_state_t* state, n2s_fontdata_t* fontdata)
{
#if N2_CONFIG_USE_FONT_LIB
	if (fontdata->fontinfo_) { n2_free(state, fontdata->fontinfo_); fontdata->fontinfo_ = NULL; }
#endif
	fontdata->pixel_scaling_ = 0.f;
	fontdata->pixel_ascent_ = 0.f;
	fontdata->pixel_descent_ = 0.f;
	fontdata->pixel_linegap_ = 0.f;
	fontdata->pixel_strict_lineheight_ = 0.f;
	n2_buffer_teardown(state, &fontdata->fontbinary_);
}

static n2_bool_t n2si_fontdata_load_to(n2_state_t* state, n2s_fontdata_t* fontdata, n2_buffer_t* fontbinary)
{
	n2si_fontdata_teardown(state, fontdata);
#if N2_CONFIG_USE_FONT_LIB
	struct stbtt_fontinfo* fontinfo = N2_TMALLOC(struct stbtt_fontinfo, state);
	if (!stbtt_InitFont(fontinfo, fontbinary->data_, 0))
	{
		n2_free(state, fontinfo);
		return N2_FALSE;
	}
	fontinfo->userdata = state;
	n2_buffer_swap(&fontdata->fontbinary_, fontbinary);
	fontdata->fontinfo_ = fontinfo;
	fontdata->pixel_scaling_ = stbtt_ScaleForPixelHeight(fontdata->fontinfo_, 1.f);
	int ascent = 0, descent = 0, line_gap = 0;
	stbtt_GetFontVMetrics(fontdata->fontinfo_, &ascent, &descent, &line_gap);
	fontdata->pixel_ascent_ = N2_SCAST(float, ascent) * fontdata->pixel_scaling_;
	fontdata->pixel_descent_ = N2_SCAST(float, descent) * fontdata->pixel_scaling_;
	fontdata->pixel_linegap_ = N2_SCAST(float, line_gap) * fontdata->pixel_scaling_;
	fontdata->pixel_strict_lineheight_ = N2_SCAST(float, ascent - descent + line_gap) * fontdata->pixel_scaling_;
	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(fontdata);
	N2_UNUSE(fontbinary);
	return N2_FALSE;
#endif
}

static void n2si_fontdataarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2s_fontdata_t* fontdata = N2_RCAST(n2s_fontdata_t*, element);
	n2si_fontdata_teardown(state, fontdata);
}

N2_DEFINE_TARRAY(n2s_fontdata_t, n2s_fontdataarray, N2_API, n2i_setupfunc_nothing, n2si_fontdataarray_freefunc);

static void n2si_font_teardown(n2_state_t* state, n2s_font_t* font)
{
	n2s_font_clear(state, font);
	n2s_fontdataarray_free(state, font->fontdata_);
	n2_buffer_teardown(state, &font->glyph_staging_alpha_);
	if (font->texture_) { n2si_texture_free(state, font->texture_); }
	n2s_glyphset_free(state, font->glyphset_);
	n2_str_teardown(state, &font->filepath_);
	n2_str_teardown(state, &font->name_);
}

static int n2si_font_find_glyph_raw(n2s_fontdata_t** dst_fontdata, const n2s_font_t* font, n2_codepoint_t codepoint)
{
#if N2_CONFIG_USE_FONT_LIB
	for (size_t i = 0, l = n2s_fontdataarray_size(font->fontdata_); i < l; ++i)
	{
		n2s_fontdata_t* fontdata = n2s_fontdataarray_peek(font->fontdata_, N2_SCAST(int, i));
		if (!fontdata->fontinfo_) { continue; }
		const int glyph_index = stbtt_FindGlyphIndex(fontdata->fontinfo_, codepoint);
		if (!glyph_index) { continue; }
		if (dst_fontdata) { *dst_fontdata = fontdata; }
		return glyph_index;
	}
	return 0;
#else
	N2_UNUSE(dst_fontdata);
	N2_UNUSE(font);
	return 0;
#endif
}

static const n2s_glyph_t* n2si_font_find_glyph_or_fallback(const n2s_font_t* font, n2_codepoint_t codepoint)
{
	const n2s_glyph_t* glyph = n2s_glyphset_find(font->glyphset_, &codepoint);
	if (!glyph && font->fallback_codepoint_ > 0) { glyph = n2s_glyphset_find(font->glyphset_, &font->fallback_codepoint_); }
	return glyph;
}

#if N2_CONFIG_USE_FONT_LIB && N2_CONFIG_USE_GUI_LIB
static float n2si_font_nk_text_width_f(nk_handle userdata, float h, const char* str, int len)
{
	n2s_font_t* font = N2_RCAST(n2s_font_t*, userdata.ptr);
	N2_ASSERT(font);
	if (!font) { return 0.f; }
	const char* e = str + len;
	const char* p = str;
	float width = 0.f;
	if (font->birth_state_ && font->fallback_codepoint_ > 0) { n2s_font_bake_codepoint(font->birth_state_, font, font->fallback_codepoint_, -1); }
	while (p < e)
	{
		n2_unicp_t unicp = 0;
		p = n2_encoding_utf8_fetch(p, &unicp);
		if (font->birth_state_) { n2s_font_bake_codepoint(font->birth_state_, font, unicp, -1); }
		const n2s_glyph_t* glyph = n2si_font_find_glyph_or_fallback(font, N2_SCAST(n2_codepoint_t, unicp));
		if (glyph) { width += glyph->pixel_xadvance_ * h; }
	}
	return width;
}

static void n2si_font_nk_query_font_glyph_f(nk_handle userdata, float font_height, struct nk_user_font_glyph *glyph, nk_rune codepoint, nk_rune next_codepoint)
{
	// @todo kerning support
	N2_UNUSE(next_codepoint);

	const n2s_font_t* font = N2_RCAST(const n2s_font_t*, userdata.ptr);
	N2_ASSERT(font);
	n2_bool_t fill_zero = N2_TRUE;
	if (font)
	{
		const n2s_glyph_t* fglyph = n2si_font_find_glyph_or_fallback(font, N2_SCAST(n2_codepoint_t, codepoint));
		if (fglyph)
		{
			fill_zero = N2_FALSE;
			glyph->offset.x = fglyph->pixel_offset_x_ * font_height;
			glyph->offset.y = (fglyph->pixel_ascent_ + fglyph->pixel_offset_y_) * font_height;
			glyph->width = fglyph->pixel_width_ * font_height;
			glyph->height = fglyph->pixel_height_ * font_height;
			glyph->uv[0].x = fglyph->uv_ltx_;
			glyph->uv[0].y = fglyph->uv_lty_;
			glyph->uv[1].x = fglyph->uv_rbx_;
			glyph->uv[1].y = fglyph->uv_rby_;
			glyph->xadvance = fglyph->pixel_xadvance_ * font_height;
		}
	}
	if (fill_zero)
	{
		glyph->offset.x = 0.f;
		glyph->offset.y = 0.f;
		glyph->width = 0.f;
		glyph->height = 0.f;
		glyph->uv[0].x = 0.f;
		glyph->uv[0].y = 0.f;
		glyph->uv[1].x = 0.f;
		glyph->uv[1].y = 0.f;
		glyph->xadvance = 0.f;
	}
}
#endif

N2_API n2s_font_t* n2s_font_alloc(n2_state_t* state, const char* name, size_t name_size, size_t atlas_width, size_t atlas_height)
{
	n2s_font_t* font = N2_TMALLOC(n2s_font_t, state);
	font->birth_state_ = state;
	n2_str_init(&font->name_);
	n2_str_set(state, &font->name_, name, name_size);
	n2_str_init(&font->filepath_);
	font->fontdata_ = n2s_fontdataarray_alloc(state, 0, 0);
	font->fallback_codepoint_ = state->config_.standard_font_fallback_codepoint_;
	font->ignore_complex_c0_control_codepoints_ = N2_TRUE;
	font->glyphset_ = n2s_glyphset_alloc(state, 256, 0);
	font->texture_ = n2si_texture_alloc(state, atlas_width, atlas_height, NULL);
	n2_buffer_init(&font->glyph_staging_alpha_);
	font->texture_cursor_x_ = font->texture_cursor_y_ = 0;
	font->texture_next_y_ = 0;
	font->bake_padding_ = 1;
	font->bake_height_ = state->config_.standard_font_default_bake_height_;
	font->bake_oversample_ = 1.f;
#if N2_CONFIG_USE_GUI_LIB
	font->nk_font_ = NULL;
#endif
	return font;
}

N2_API void n2s_font_free(n2_state_t* state, n2s_font_t* font)
{
	n2si_font_teardown(state, font);
	n2_free(state, font);
}

N2_API n2_bool_t n2s_font_load_to(n2_state_t* state, n2s_font_t* font, n2_buffer_t* fontbinary, n2_bool_t append)
{
	N2_ASSERT(fontbinary);
	if (fontbinary->size_ <= 0) { return N2_FALSE; }
	n2s_fontdata_t fontdata;
	n2si_fontdata_init(&fontdata);
	if (!n2si_fontdata_load_to(state, &fontdata, fontbinary)) { return N2_FALSE; }
	if (!append) { n2s_font_clear(state, font); }
	n2s_fontdataarray_push(state, font->fontdata_, &fontdata);
	font->pixel_lineheight_ = 1.f;
#if N2_CONFIG_USE_FONT_LIB && N2_CONFIG_USE_GUI_LIB
	if (!font->nk_font_)
	{
		struct nk_user_font* nk_font = N2_TMALLOC(struct nk_user_font, state);
		nk_font->userdata.ptr = font;
		nk_font->height = font->bake_height_;
		nk_font->width = n2si_font_nk_text_width_f;
		nk_font->query = n2si_font_nk_query_font_glyph_f;
		nk_font->texture.ptr = font->texture_;
		font->nk_font_ = nk_font;
	}
#endif
	return N2_TRUE;
}

N2_API void n2s_font_clear(n2_state_t* state, n2s_font_t* font)
{
	n2s_glyphset_clear(state, font->glyphset_);
	font->texture_cursor_x_ = font->texture_cursor_y_ = 0;
	font->texture_next_y_ = 0;
	N2_MEMSET(font->texture_->imagebuf_.data_, 0x00, font->texture_->imagebuf_.size_);
	n2s_texture_dirty_all(font->texture_);
	n2_buffer_teardown(state, &font->glyph_staging_alpha_);
	font->pixel_lineheight_ = 0.f;
#if N2_CONFIG_USE_FONT_LIB && N2_CONFIG_USE_GUI_LIB
	if (font->nk_font_) { n2_free(state, font->nk_font_); font->nk_font_ = NULL; }
#endif
}

N2_API void n2s_font_swap(n2s_font_t* lhs, n2s_font_t* rhs)
{
	n2_swap(lhs, rhs, sizeof(n2s_font_t));
#if N2_CONFIG_USE_FONT_LIB && N2_CONFIG_USE_GUI_LIB
	// ポインタは戻す
	n2_swap(&lhs->nk_font_, &rhs->nk_font_, sizeof(struct nk_user_font*));
	// 参照先のテクスチャは変える
	if (lhs->nk_font_) { lhs->nk_font_->texture.ptr = lhs->texture_; }
	if (rhs->nk_font_) { rhs->nk_font_->texture.ptr = rhs->texture_; }
#endif
}

N2_API n2_bool_t n2s_font_bake_codepoint(n2_state_t* state, n2s_font_t* font, n2_codepoint_t codepoint, float height)
{
	if (height <= 0.f) { height = font->bake_height_; }
#if N2_CONFIG_USE_FONT_LIB
	// @todo support over samping
	// check is codepoint already registered
	const n2s_glyph_t* glyph = n2s_glyphset_find(font->glyphset_, &codepoint);
	if (glyph) { return N2_TRUE; }
	// check glyph
	n2s_fontdata_t* fontdata = NULL;
	const int glyph_index = n2si_font_find_glyph_raw(&fontdata, font, codepoint);
	if (!fontdata || !glyph_index) { return N2_FALSE; }
	// determin glyph bounding box
	const float pixel_scaling = fontdata->pixel_scaling_;
	const float scaling = pixel_scaling * height;
	int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
	stbtt_GetCodepointBitmapBox(fontdata->fontinfo_, codepoint, scaling, scaling, &x0, &y0, &x1, &y1);
	// determin bake region
	const size_t pd = font->bake_padding_;
	const size_t w = N2_SCAST(size_t, x1 - x0);
	const size_t h = N2_SCAST(size_t, y1 - y0);
	const size_t pw = w + pd * 2;
	const size_t ph = h + pd * 2;
	size_t stx = font->texture_cursor_x_, sty = font->texture_cursor_y_;
	if (stx + pw > font->texture_->width_) { stx = 0; sty = font->texture_next_y_; }
	if (stx + pw > font->texture_->width_) { return N2_FALSE; }
	if (sty + ph > font->texture_->height_) { return N2_FALSE; }
	// bake to alpha
	n2_buffer_reserve(state, &font->glyph_staging_alpha_, w * h);
	const int line_stride = N2_SCAST(int, w);
	stbtt_MakeCodepointBitmapSubpixel(fontdata->fontinfo_, N2_RCAST(unsigned char*, font->glyph_staging_alpha_.data_), N2_SCAST(int, w), N2_SCAST(int, h), line_stride, scaling, scaling, 0.f, 0.f, codepoint);
	//stbtt_MakeCodepointBitmap(fontdata->fontinfo_, N2_RCAST(unsigned char*, font->glyph_staging_alpha_.data_), N2_SCAST(int, w), N2_SCAST(int, h), line_stride, scaling, scaling, codepoint);
	// copy to region
	uint8_t* pixel_head = N2_RCAST(uint8_t*, n2_ptr_offset(font->texture_->imagebuf_.data_, ((sty + pd) * font->texture_->width_ + (stx + pd)) * 4));
	const uint8_t* read_head = N2_RCAST(const uint8_t*, font->glyph_staging_alpha_.data_);
	for (size_t y = 0; y < h; ++y)
	{
		uint8_t* line_head = pixel_head;
		for (size_t x = 0; x < w; ++x)
		{
			const uint8_t alpha = *read_head;
			line_head[0] = line_head[1] = line_head[2] = 255;// rgb
			line_head[3] = alpha;// alpha
			line_head += 4;
			++read_head;
		}
		pixel_head += font->texture_->width_ * 4;
	}
	// step cursor
	font->texture_cursor_x_ = stx; font->texture_cursor_y_ = sty;
	font->texture_cursor_x_ += pw;
	font->texture_next_y_ = N2_MAX(font->texture_next_y_, font->texture_cursor_y_ + ph);
	// dirty texture
	n2s_texture_dirty_range(font->texture_, font->texture_cursor_y_, font->texture_next_y_);
	// register glyph
	int xadvance = 0; int lsb = 0;
	stbtt_GetCodepointHMetrics(fontdata->fontinfo_, codepoint, &xadvance, &lsb);
	n2s_glyph_t* rglyph = n2s_glyphset_insert(state, font->glyphset_, NULL, &codepoint);
	rglyph->codepoint_ = codepoint;
	rglyph->glyph_index_ = glyph_index;
	rglyph->bb_x_ = stx + pd; rglyph->bb_y_ = sty + pd;
	rglyph->bb_width_ = w; rglyph->bb_height_ = h;
	rglyph->uv_ltx_ = N2_SCAST(float, rglyph->bb_x_) / N2_SCAST(float, font->texture_->width_);
	rglyph->uv_lty_ = N2_SCAST(float, rglyph->bb_y_) / N2_SCAST(float, font->texture_->height_);
	rglyph->uv_rbx_ = N2_SCAST(float, rglyph->bb_x_ + rglyph->bb_width_) / N2_SCAST(float, font->texture_->width_);
	rglyph->uv_rby_ = N2_SCAST(float, rglyph->bb_y_ + rglyph->bb_height_) / N2_SCAST(float, font->texture_->height_);
	rglyph->bake_height_ = height;
	rglyph->pixel_offset_x_ = N2_SCAST(float, x0) / height; rglyph->pixel_offset_y_ = N2_SCAST(float, y0) / height;
	rglyph->pixel_width_ = N2_SCAST(float, x1 - x0) / height; rglyph->pixel_height_ = N2_SCAST(float, y1 - y0) / height;
	rglyph->pixel_xadvance_ = N2_SCAST(float, xadvance) * pixel_scaling;
	rglyph->pixel_ascent_ = fontdata->pixel_ascent_;
	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(font);
	return N2_FALSE;
#endif
}

N2_API void n2s_font_text(n2_state_t* state, n2s_font_t* font, const char* str, size_t str_length, n2s_font_text_callback_t callback, void* user)
{
	N2_ASSERT(font);
	if (str_length == SIZE_MAX) { str_length = N2_STRLEN(str); }
	const char* e = str + str_length;
	const char* p = str;
	n2s_font_text_callback_param_t param;
	param.font_ = font;
	param.prev_codepoint_ = 0;
	if (state && font->fallback_codepoint_ > 0) { n2s_font_bake_codepoint(state, font, font->fallback_codepoint_, -1); }// bake fallback font
	while (p < e)
	{
		n2_unicp_t unicp = 0;
		p = n2_encoding_utf8_fetch(p, &unicp);
		if (font->ignore_complex_c0_control_codepoints_ && (unicp < 0x20 && unicp != 0x0a/*lf*/)) { continue; }
		if (state) { n2s_font_bake_codepoint(state, font, unicp, -1); }
		const n2s_glyph_t* glyph = n2si_font_find_glyph_or_fallback(font, N2_SCAST(n2_codepoint_t, unicp));
		param.codepoint_ = N2_SCAST(n2_codepoint_t, unicp);
		param.glyph_ = glyph;
		callback(&param, user);
		param.prev_codepoint_ = param.codepoint_;
	}
}

typedef struct n2si_font_text_bb_context_t n2si_font_text_bb_context_t;
struct n2si_font_text_bb_context_t
{
	n2_fvec2_t cursor_;
	n2_fvec2_t bb_;
	n2_fvec2_t draw_cursor_;
	float height_;
	float wrap_width_;
};

static void n2si_font_text_bb_context_init(n2si_font_text_bb_context_t* dst, float height, float wrap_width)
{
	dst->cursor_ = n2_fvec2(0, 0);
	dst->bb_ = n2_fvec2(0, 0);
	dst->draw_cursor_ = n2_fvec2(0, 0);
	dst->height_ = height;
	dst->wrap_width_ = wrap_width;
}

static void n2si_font_text_bb_callback(const n2s_font_text_callback_param_t* param, void* user)
{
	n2si_font_text_bb_context_t* context = N2_RCAST(n2si_font_text_bb_context_t*, user);
	const float line_height = param->font_->pixel_lineheight_ * context->height_;
	if (n2_unicode_is_newline(param->codepoint_))
	{
		context->draw_cursor_ = context->cursor_;
		context->cursor_ = n2_fvec2(0, context->cursor_.y_ + line_height);
	}
	else
	{
		if (param->glyph_)
		{
			const float xadvance = param->glyph_->pixel_xadvance_ * context->height_;
			if (context->wrap_width_ > 0 && context->cursor_.x_ + xadvance > context->wrap_width_)
			{
				context->cursor_ = n2_fvec2(0, context->cursor_.y_ + line_height);
			}
			context->draw_cursor_ = context->cursor_;
			context->cursor_.x_ += xadvance;
			//context->bb_ = n2_fvec2_max(context->bb_, n2_fvec2_add(context->cursor_, n2_fvec2(0, (param->font_->pixel_ascent_ + param->glyph_->pixel_offset_y_ + param->glyph_->pixel_height_) * context->height_)));// strict
			context->bb_ = n2_fvec2_max(context->bb_, n2_fvec2_add(context->cursor_, n2_fvec2(0, line_height)));
		}
	}
}

N2_API n2_bool_t n2s_font_text_bb(n2_state_t* state, n2_fvec2_t* dst_bb, n2s_font_t* font, const char* str, size_t str_length, float height, float wrap_width)
{
	if (dst_bb) { *dst_bb = n2_fvec2(0, 0); }
	if (!font) { return N2_FALSE; }
	if (!str || str_length <= 0 || height <= 0.f) { return N2_TRUE; }
	n2si_font_text_bb_context_t context;
	n2si_font_text_bb_context_init(&context, height, wrap_width);
	n2s_font_text(state, font, str, str_length, n2si_font_text_bb_callback, &context);
	if (dst_bb) { *dst_bb = context.bb_; }
	return N2_TRUE;
}

N2_API void n2s_font_render_config_init(n2s_font_render_config_t* render_config, const n2s_font_t* font, float height, n2_buffer_t* staging_alpha)
{
	render_config->font_ = font;
	render_config->render_flags_ = N2S_FONT_RENDER_FLAG_DEFAULT;
	render_config->fallback_codepoint_ = font->fallback_codepoint_;
	render_config->height_ = height;
	render_config->wrap_width_ = -1;
	render_config->color_ = n2s_u8color(255, 255, 255, 255);
	render_config->cursor_offsetx_ = 0;
	render_config->cursor_offsety_ = 0;
	render_config->staging_alpha_ = staging_alpha;
}

N2_API n2_bool_t n2s_font_render_buffer(n2_state_t* state, n2_buffer_t* dst, size_t dst_width, size_t dst_height, const char* str, size_t str_length, const n2s_font_render_config_t* render_config)
{
	if (str_length == SIZE_MAX && str) { str_length = N2_STRLEN(str); }
	if (!render_config) { return N2_FALSE; }
	if (!str || str_length <= 0 || render_config->height_ <= 0) { return N2_TRUE; }
	const n2s_font_t* font = render_config->font_;
	if (!font) { return N2_FALSE; }
	n2_buffer_t* staging_alpha = render_config->staging_alpha_;
	if (!staging_alpha) { return N2_FALSE; }
#if N2_CONFIG_USE_FONT_LIB
	if (n2s_fontdataarray_size(font->fontdata_) <= 0) { return N2_FALSE; }
	const float height = render_config->height_;
	const n2s_u8color_t color = render_config->color_;
	const n2_bool_t vflip = (render_config->render_flags_ & N2S_FONT_RENDER_FLAG_VFLIP) ? N2_TRUE : N2_FALSE;
	// 各文字
	const char* e = str + str_length;
	const char* p = str;
	const float line_height = font->pixel_lineheight_ * height;
	float cursor_x = N2_SCAST(float, render_config->cursor_offsetx_), cursor_y = N2_SCAST(float, render_config->cursor_offsety_);
	while (p < e)
	{
		// コードポイント取り出し
		n2_unicp_t unicp = 0;
		p = n2_encoding_utf8_fetch(p, &unicp);

		n2_codepoint_t codepoint = N2_SCAST(n2_codepoint_t, unicp);
		n2s_fontdata_t* fontdata = NULL;
		int glyph_index = n2si_font_find_glyph_raw(&fontdata, font, codepoint);
		if (!glyph_index)
		{
			codepoint = render_config->fallback_codepoint_;
			glyph_index = n2si_font_find_glyph_raw(&fontdata, font, codepoint);
		}

		// 無いなら、ベイクはしない
		if (!codepoint || !fontdata) { continue; }

		// determin glyph bounding box
		const float pixel_scaling = fontdata->pixel_scaling_;
		const float scaling = pixel_scaling * height;
		int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
		stbtt_GetCodepointBitmapBox(fontdata->fontinfo_, codepoint, scaling, scaling, &x0, &y0, &x1, &y1);
		// determin bake region
		const size_t pd = 0;
		const size_t w = N2_SCAST(size_t, x1 - x0);
		const size_t h = N2_SCAST(size_t, y1 - y0);
		// determin advance
		int xadvance = 0; int lsb = 0;
		stbtt_GetCodepointHMetrics(fontdata->fontinfo_, codepoint, &xadvance, &lsb);
		float bake_x = cursor_x, bake_y = cursor_y;
		cursor_x += N2_SCAST(float, xadvance) * pixel_scaling * height;
		if (render_config->wrap_width_ > 0 && cursor_x > render_config->wrap_width_)
		{
			cursor_x = N2_SCAST(float, render_config->cursor_offsetx_);
			bake_x = cursor_x;
			cursor_y += line_height;
			bake_y = cursor_y;
		}
		// check region
		const size_t baseline = N2_SCAST(size_t, fontdata->pixel_ascent_ * height + N2_SCAST(float, y0));
		const size_t rw = w + pd * 2 + x0;
		const size_t rh = h + pd * 2 + baseline;
		const size_t bake_sx = N2_SCAST(size_t, bake_x);
		const size_t bake_sy = N2_SCAST(size_t, bake_y);
#if 0
		const float bake_subx = bake_x - N2_SCAST(float, bake_sx);
		const float bake_suby = bake_y - N2_SCAST(float, bake_sy);
#else
		const float bake_subx = 0;
		const float bake_suby = 0;
#endif
		if (bake_sx + rw > dst_width) { return N2_FALSE; }// out of range
		if (bake_sy + rh > dst_height) { return N2_FALSE; }// out of range
		// bake to alpha
		n2_buffer_reserve(state, staging_alpha, w * h);
		const int line_stride = N2_SCAST(int, w);
		stbtt_MakeCodepointBitmapSubpixel(fontdata->fontinfo_, N2_RCAST(unsigned char*, staging_alpha->data_), N2_SCAST(int, w), N2_SCAST(int, h), line_stride, scaling, scaling, bake_subx, bake_suby, codepoint);
		// copy to region
		size_t hx = bake_sx + x0;
		size_t hy = bake_sy + baseline;
		if (vflip) { hy = dst_height - hy; }
		uint8_t* pixel_head = N2_RCAST(uint8_t*, n2_ptr_offset(dst->data_, (hy * dst_width + hx) * 4));
		const uint8_t* read_head = N2_RCAST(const uint8_t*, staging_alpha->data_);
		for (size_t y = 0; y < h; ++y)
		{
			uint8_t* line_head = pixel_head;
			for (size_t x = 0; x < w; ++x)
			{
				const uint8_t alpha = *read_head;
				if (render_config->render_flags_ & N2S_FONT_RENDER_FLAG_ALPHA_BLEND)
				{
					const int malpha = color.a_ * alpha;
					const int imalpha = 255 * 255 - malpha;
					const int dalpha = 255 * 255;
					// rgb
					line_head[0] = N2_SCAST(uint8_t, (line_head[0] * imalpha + color.r_ * malpha) / dalpha);
					line_head[1] = N2_SCAST(uint8_t, (line_head[1] * imalpha + color.g_ * malpha) / dalpha);
					line_head[2] = N2_SCAST(uint8_t, (line_head[2] * imalpha + color.b_ * malpha) / dalpha);
					// alpha
					line_head[3] = N2_SCAST(uint8_t, (line_head[3] * imalpha + 255 * malpha) / dalpha);
				}
				else
				{
					// rgb
					line_head[0] = color.r_;
					line_head[1] = color.g_;
					line_head[2] = color.b_;
					// alpha
					line_head[3] = N2_SCAST(uint8_t, color.a_ * alpha / 255);
				}
				line_head += 4;
				++read_head;
			}
			pixel_head += N2_SCAST(int, dst_width) * 4 * (vflip ? -1 : 1);
		}
	}
	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(dst);
	N2_UNUSE(dst_width);
	N2_UNUSE(dst_height);
	N2_UNUSE(str);
	N2_UNUSE(str_length);
	N2_UNUSE(render_config);
	return N2_FALSE;
#endif
}

static int n2si_fontset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return N2_STRCMP((*N2_RCAST(const n2s_font_t**, lkey))->name_.str_, (*N2_RCAST(const n2s_font_t**, rkey))->name_.str_);
}

static int n2si_fontset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	return N2_STRCMP((*N2_RCAST(const n2s_font_t**, ekey))->name_.str_, N2_RCAST(const char*, key));
}

static void n2si_fontset_setupfunc(n2_state_t* state, n2s_fontset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2si_fontset_cmpfunc;
	a->match_ = n2si_fontset_matchfunc;
}

static void n2si_fontset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2s_font_t* font = *N2_RCAST(n2s_font_t**, element);
	n2si_font_teardown(state, font);
	n2_free(state, font);
}

N2_DEFINE_TSORTED_ARRAY(n2s_font_t*, void, char, n2s_fontset, N2_API, n2si_fontset_setupfunc, n2si_fontset_freefunc);

static const struct
{
	n2s_gprogram_uniform_e uniform_;
	const char* name_;
	size_t name_length_;
} n2si_gprogram_uniform_table[] =
{
	{N2S_GPROGRAM_UNIFORM_TEXTURE,		"uTexture",		8},
	{N2S_GPROGRAM_UNIFORM_TRANSCOLOR,	"uTransColor",	11},
};

N2_API n2s_gprogram_uniform_e n2s_gprogram_uniform_find(const char* name, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(name); }

	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_uniform_table); i < l; ++i)
	{
		if (n2si_gprogram_uniform_table[i].name_length_ == length && N2_STRNCMP(name, n2si_gprogram_uniform_table[i].name_, length) == 0) { return n2si_gprogram_uniform_table[i].uniform_; }
	}
	return N2S_GPROGRAM_UNIFORM_UNKNOWN;
}

N2_API const char* n2s_gprogram_uniform_name(n2s_gprogram_uniform_e un, const char* on_failed)
{
	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_uniform_table); i < l; ++i)
	{
		if (n2si_gprogram_uniform_table[i].uniform_ == un) { return n2si_gprogram_uniform_table[i].name_; }
	}
	return on_failed;
}

N2_API void n2s_gprogram_uniform_data_init(n2s_gprogram_uniform_data_t* uniform_data)
{
	uniform_data->data_type_ = N2S_GPROGRAM_DATA_UNKNOWN;
	uniform_data->data_element_num_ = 0;
	uniform_data->data_ = NULL;
}

static const struct
{
	n2s_gprogram_uniform_block_e uniform_block_;
	const char* name_;
	size_t name_length_;
} n2si_gprogram_uniform_block_table[] =
{
	{N2S_GPROGRAM_UNIFORM_BLOCK_DRAWENV,		"ubDrawEnv",		9},
	{N2S_GPROGRAM_UNIFORM_BLOCK_D3ENV,			"ubD3Env",			7},
};

N2_API n2s_gprogram_uniform_block_e n2s_gprogram_uniform_block_find(const char* name, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(name); }

	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_uniform_block_table); i < l; ++i)
	{
		if (n2si_gprogram_uniform_block_table[i].name_length_ == length && N2_STRNCMP(name, n2si_gprogram_uniform_block_table[i].name_, length) == 0) { return n2si_gprogram_uniform_block_table[i].uniform_block_; }
	}
	return N2S_GPROGRAM_UNIFORM_BLOCK_UNKNOWN;
}

N2_API const char* n2s_gprogram_uniform_block_name(n2s_gprogram_uniform_block_e ubn, const char* on_failed)
{
	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_uniform_block_table); i < l; ++i)
	{
		if (n2si_gprogram_uniform_block_table[i].uniform_block_ == ubn) { return n2si_gprogram_uniform_block_table[i].name_; }
	}
	return on_failed;
}

N2_API void n2s_guniform_block_drawenv_init(n2s_guniform_block_drawenv_t* drawenv)
{
	n2_fmat4_identity_to(&drawenv->v_mtx_);
	n2_fmat4_identity_to(&drawenv->p_mtx_);
	n2_fmat4_identity_to(&drawenv->pv_mtx_);
	drawenv->screen_param_ = n2_fvec4(0, 0, 0, 0);
}

N2_API void n2s_guniform_block_drawenv_set_screen_param(n2s_guniform_block_drawenv_t* drawenv, size_t width, size_t height)
{
	drawenv->screen_param_ = n2_fvec4(N2_SCAST(float, width), N2_SCAST(float, height), width <= 0 ? 0 : 1.f / N2_SCAST(float, width), height <= 0 ? 0 : 1.f / N2_SCAST(float, height));
}

static const struct
{
	n2s_gprogram_attribute_e attribute_;
	const char* name_;
	size_t name_length_;
} n2si_gprogram_attribute_table[] =
{
	{N2S_GPROGRAM_ATTRIBUTE_POSITION,			"aPosition",		9},
	{N2S_GPROGRAM_ATTRIBUTE_TEXCOORD,			"aTexCoord",		9},
	{N2S_GPROGRAM_ATTRIBUTE_COLOR,				"aColor",			6},
	{N2S_GPROGRAM_ATTRIBUTE_TEXCOORD_CLAMP,		"aTexCoordClamp",	13}
};

N2_API n2s_gprogram_attribute_e n2s_gprogram_attribute_find(const char* name, size_t length)
{
	if (length == SIZE_MAX) { length = N2_STRLEN(name); }

	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_attribute_table); i < l; ++i)
	{
		if (n2si_gprogram_attribute_table[i].name_length_ == length && N2_STRNCMP(name, n2si_gprogram_attribute_table[i].name_, length) == 0) { return n2si_gprogram_attribute_table[i].attribute_; }
	}
	return N2S_GPROGRAM_ATTRIBUTE_UNKNOWN;
}

N2_API const char* n2s_gprogram_attribute_name(n2s_gprogram_attribute_e attr, const char* on_failed)
{
	for (size_t i = 0, l = N2_ARRAYDIM(n2si_gprogram_attribute_table); i < l; ++i)
	{
		if (n2si_gprogram_attribute_table[i].attribute_ == attr) { return n2si_gprogram_attribute_table[i].name_; }
	}
	return on_failed;
}

#if N2_CONFIG_USE_SDL_LIB
static n2_bool_t n2si_gprogram_shader_log(n2_state_t* state, n2_str_t* dst, GLuint shader)
{
	GLint log_length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
	if (log_length <= 0) { return N2_FALSE; }

	n2_str_reserve(state, dst, N2_SCAST(size_t, log_length + 1));

	GLsizei written = 0;
	glGetShaderInfoLog(shader, N2_SCAST(GLsizei, dst->buffer_size_ - 1), &written, N2_SCAST(GLchar*, dst->str_));

	dst->size_ = N2_SCAST(size_t, written);
	dst->str_[written] = '\0';
	return N2_TRUE;
}
#endif

N2_API void n2s_gprogram_init(n2s_gprogram_t* program)
{
	n2_str_init(&program->name_);
	n2_str_init(&program->last_error_);
#if N2_CONFIG_USE_SDL_LIB
	program->gl_vsh_ = 0;
	program->gl_fsh_ = 0;
	program->gl_program_ = 0;
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM; ++i) { program->gl_ulocation_[i] = -1; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { program->gl_ublocation_[i] = -1; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_ATTRIBUTE; ++i) { program->gl_alocation_[i] = -1; }
#endif
}

N2_API void n2s_gprogram_teardown(n2_state_t* state, n2s_gprogram_t* program)
{
	n2s_gprogram_clear(state, program);
	n2_str_teardown(state, &program->name_);
	n2_str_teardown(state, &program->last_error_);
}

N2_API void n2s_gprogram_clear(n2_state_t* state, n2s_gprogram_t* program)
{
#if N2_CONFIG_USE_SDL_LIB
	if (program->gl_program_)
	{
		N2SI_ASSERT_GL(state);
		if (program->gl_vsh_) { glDetachShader(program->gl_program_, program->gl_vsh_); }
		if (program->gl_fsh_) { glDetachShader(program->gl_program_, program->gl_fsh_); }
		N2SI_GL_CLEAR_ERRORS(state);
		glDeleteProgram(program->gl_program_);
		program->gl_program_ = 0;
	}
	if (program->gl_vsh_) { glDeleteShader(program->gl_vsh_); program->gl_vsh_ = 0; }
	if (program->gl_fsh_) { glDeleteShader(program->gl_fsh_); program->gl_fsh_ = 0; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM; ++i) { program->gl_ulocation_[i] = -1; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { program->gl_ublocation_[i] = -1; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_ATTRIBUTE; ++i) { program->gl_alocation_[i] = -1; }
	N2SI_ASSERT_GL(state);
#endif
}

N2_API n2_bool_t n2s_gprogram_load_to(n2_state_t* state, n2s_gprogram_t* program, const char* vsh_src, const char* fsh_src)
{
	n2s_gprogram_teardown(state, program);
#if N2_CONFIG_USE_SDL_LIB
	program->gl_vsh_ = glCreateShader(GL_VERTEX_SHADER);
	program->gl_fsh_ = glCreateShader(GL_FRAGMENT_SHADER);
	program->gl_program_ = glCreateProgram();
	N2SI_ASSERT_GL(state);
	if (!program->gl_vsh_ || !program->gl_fsh_ || !program->gl_program_) { goto fail_exit; }

	glShaderSource(program->gl_vsh_, 1, &vsh_src, NULL);
	glCompileShader(program->gl_vsh_);
	{
		GLint status = GL_TRUE;
		glGetShaderiv(program->gl_vsh_, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) { n2si_gprogram_shader_log(state, &program->last_error_, program->gl_vsh_); goto fail_exit; }
	}
	N2SI_ASSERT_GL(state);

	glShaderSource(program->gl_fsh_, 1, &fsh_src, NULL);
	glCompileShader(program->gl_fsh_);
	{
		GLint status = GL_TRUE;
		glGetShaderiv(program->gl_fsh_, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) { n2si_gprogram_shader_log(state, &program->last_error_, program->gl_fsh_); goto fail_exit; }
	}
	N2SI_ASSERT_GL(state);

	glAttachShader(program->gl_program_, program->gl_vsh_);
	glAttachShader(program->gl_program_, program->gl_fsh_);
	glLinkProgram(program->gl_program_);
	{
		GLint status = GL_TRUE;
		glGetProgramiv(program->gl_program_, GL_LINK_STATUS, &status);
		if (status != GL_TRUE) { goto fail_exit; }
	}
	N2SI_ASSERT_GL(state);

	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM; ++i)
	{
		program->gl_ulocation_[i] = glGetUniformLocation(program->gl_program_, n2s_gprogram_uniform_name(N2_SCAST(n2s_gprogram_uniform_e, i), NULL));
	}
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i)
	{
		const GLuint ub_index = glGetUniformBlockIndex(program->gl_program_, n2s_gprogram_uniform_block_name(N2_SCAST(n2s_gprogram_uniform_block_e, i), NULL));
		if (ub_index != GL_INVALID_INDEX)
		{
			program->gl_ublocation_[i] = N2_SCAST(GLint, ub_index);
			glUniformBlockBinding(program->gl_program_, ub_index, N2_SCAST(GLuint, i));
			N2SI_ASSERT_GL(state);
		}
	}
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_ATTRIBUTE; ++i)
	{
		program->gl_alocation_[i] = glGetAttribLocation(program->gl_program_, n2s_gprogram_attribute_name(N2_SCAST(n2s_gprogram_attribute_e, i), NULL));;
	}
	N2SI_ASSERT_GL(state);

	return N2_TRUE;

fail_exit:
	N2SI_ASSERT_GL(state);
	n2s_gprogram_clear(state, program);
	return N2_FALSE;
#else
	N2_UNUSE(vsh_src);
	N2_UNUSE(fsh_src);
	return N2_FALSE;
#endif
}

N2_API n2_bool_t n2s_gprogram_is_loaded(const n2s_gprogram_t* program)
{
#if N2_CONFIG_USE_SDL_LIB
	if (!program->gl_vsh_ || !program->gl_fsh_ || !program->gl_program_) { return N2_FALSE; }
	return N2_TRUE;
#else
	N2_UNUSE(program);
	return N2_FALSE;
#endif
}

N2_API void n2s_gprogram_draw_cache_reset(n2s_gprogram_draw_cache_t* pdc)
{
	pdc->u_cached_ = (1 << N2S_MAX_GPROGRAM_UNIFORM) - 1;
	pdc->ub_cached_ = (1 << N2S_MAX_GPROGRAM_UNIFORM_BLOCK) - 1;
}

N2_API void n2s_command_draw_to(n2s_command_t* c, size_t vertex, size_t index, const n2s_texture_t* texture)
{
	c->type_ = N2S_COMMAND_DRAW;
	c->draw_.vertex_count_ = vertex;
	c->draw_.index_count_ = index;
	c->draw_.texture_ = texture;
}

N2_DEFINE_TARRAY(n2s_command_t, n2s_commandarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

N2_API void n2s_commandbuffer_staging_state_reset(n2s_commandbuffer_staging_state_t* cbss)
{
	cbss->draw_.vertex_count_ = 0;
	cbss->draw_.index_count_ = 0;
	cbss->draw_.texture_ = NULL;
	cbss->program_ = -1;
	cbss->renderstate_ = -1;
	cbss->samplerfilter_ = -1;
	cbss->transcolor_ = N2S_COLOR_BLACK;
}

N2_API n2s_commandbuffer_t* n2s_commandbuffer_alloc(n2_state_t* state, size_t max_command_num, size_t max_vertex_num, size_t max_index_num, size_t max_data_num)
{
	n2s_commandbuffer_t* cb = N2_TMALLOC(n2s_commandbuffer_t, state);
	cb->vertexarray_ = n2s_vertexarray_alloc(state, max_vertex_num, 256);
	cb->indexarray_ = n2s_indexarray_alloc(state, max_index_num, 256);
	cb->commandarray_ = n2s_commandarray_alloc(state, max_command_num, 128);
	cb->commanddataarray_ = n2_u32array_alloc(state, max_data_num, 256);
	n2s_commandbuffer_staging_state_reset(&cb->staging_);
	return cb;
}

N2_API void n2s_commandbuffer_free(n2_state_t* state, n2s_commandbuffer_t* cb)
{
	n2s_commandbuffer_clear(state, cb);
	n2s_vertexarray_free(state, cb->vertexarray_);
	n2s_indexarray_free(state, cb->indexarray_);
	n2s_commandarray_free(state, cb->commandarray_);
	n2_u32array_free(state, cb->commanddataarray_);
	n2_free(state, cb);
}

N2_API void n2s_commandbuffer_clear(n2_state_t* state, n2s_commandbuffer_t* cb)
{
	n2s_vertexarray_clear(state, cb->vertexarray_);
	n2s_indexarray_clear(state, cb->indexarray_);
	n2s_commandarray_clear(state, cb->commandarray_);
	n2_u32array_clear(state, cb->commanddataarray_);
	n2s_commandbuffer_staging_state_reset(&cb->staging_);
}

N2_API size_t n2s_commandbuffer_command_size(const n2s_commandbuffer_t* cb)
{
	return n2s_commandarray_size(cb->commandarray_);
}

N2_API size_t n2s_commandbuffer_vertex_size(const n2s_commandbuffer_t* cb)
{
	return n2s_vertexarray_size(cb->vertexarray_);
}

N2_API size_t n2s_commandbuffer_index_size(const n2s_commandbuffer_t* cb)
{
	return n2s_indexarray_size(cb->indexarray_);
}

N2_API n2s_command_t* n2s_commandbuffer_add_command(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num)
{
	n2s_commandarray_reserve(state, cb->commandarray_, cb->commandarray_->size_ + num);
	n2s_command_t* res = N2_RCAST(n2s_command_t*, cb->commandarray_->elements_) + cb->commandarray_->size_;
	cb->commandarray_->size_ += num;
	return res;
}

N2_API n2_bool_t n2s_commandbuffer_flush_staging(n2_state_t* state, n2s_commandbuffer_t* cb)
{
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	if (cbss->draw_.vertex_count_ <= 0 && cbss->draw_.index_count_ <= 0) { return N2_FALSE; }
	n2s_command_t* c = n2s_commandbuffer_add_command(state, cb, 1);
	c->type_ = N2S_COMMAND_DRAW;
	c->draw_ = cbss->draw_;
	cbss->draw_.vertex_count_ = 0;
	cbss->draw_.index_count_ = 0;
	cbss->draw_.texture_ = NULL;
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_add_command_draw(n2_state_t* state, n2s_commandbuffer_t* cb, size_t vertex_num, size_t index_num)
{
	N2_UNUSE(state);
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	cbss->draw_.vertex_count_ += vertex_num;
	cbss->draw_.index_count_ += index_num;
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_add_command_program(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_e program)
{
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	if (cbss->program_ == program) { return N2_FALSE; }
	n2s_commandbuffer_flush_staging(state, cb);
	n2s_command_t* c = n2s_commandbuffer_add_command(state, cb, 1);
	c->type_ = N2S_COMMAND_PROGRAM;
	c->program_.program_ = program;
	cbss->program_ = program;
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_add_command_renderstate(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_renderstate_e renderstate)
{
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	if (cbss->renderstate_ == renderstate) { return N2_FALSE; }
	n2s_commandbuffer_flush_staging(state, cb);
	n2s_command_t* c = n2s_commandbuffer_add_command(state, cb, 1);
	c->type_ = N2S_COMMAND_RENDERSTATE;
	c->renderstate_.renderstate_ = renderstate;
	cbss->renderstate_ = renderstate;
	return N2_TRUE;
}

N2_API n2s_vertex_t* n2s_commandbuffer_alloc_vertex(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num)
{
	n2s_vertexarray_reserve(state, cb->vertexarray_, cb->vertexarray_->size_ + num);
	n2s_vertex_t* res = N2_RCAST(n2s_vertex_t*, cb->vertexarray_->elements_) + cb->vertexarray_->size_;
	cb->vertexarray_->size_ += num;
	return res;
}

N2_API n2s_index_t* n2s_commandbuffer_alloc_index(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num)
{
	n2s_indexarray_reserve(state, cb->indexarray_, cb->indexarray_->size_ + num);
	n2s_index_t* res = N2_RCAST(n2s_index_t*, cb->indexarray_->elements_) + cb->indexarray_->size_;
	cb->indexarray_->size_ += num;
	return res;
}

N2_API uint32_t* n2s_commandbuffer_alloc_commanddata(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num)
{
	n2_u32array_reserve(state, cb->commanddataarray_, cb->commanddataarray_->size_ + num);
	uint32_t* res = N2_RCAST(uint32_t*, cb->commanddataarray_->elements_) + cb->commanddataarray_->size_;
	cb->commanddataarray_->size_ += num;
	return res;
}

N2_API size_t n2s_commandbuffer_add_commanddata(n2_state_t* state, n2s_commandbuffer_t* cb, const void* data, size_t bytesize)
{
	const size_t pushbytesize = n2i_roundup_sz(bytesize, sizeof(uint32_t));
	const size_t pushsize = pushbytesize / sizeof(uint32_t);
	const size_t offset = n2_u32array_size(cb->commanddataarray_);
	uint32_t* todata = n2s_commandbuffer_alloc_commanddata(state, cb, pushsize);
	N2_MEMCPY(todata, data, bytesize);
	return offset;
}

N2_API n2_bool_t n2s_commandbuffer_add_uniform(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_uniform_e u, n2s_gprogram_data_e data_type, size_t element_num, const void* data, size_t data_size)
{
	if (element_num <= 0 || !data || data_size <= 0) { return N2_FALSE; }
	n2s_commandbuffer_flush_staging(state, cb);
	n2s_command_t* c = n2s_commandbuffer_add_command(state, cb, 1);
	const size_t offset = n2s_commandbuffer_add_commanddata(state, cb, data, data_size);
	c->type_ = N2S_COMMAND_UNIFORM;
	c->uniform_.uniform_ = u;
	c->uniform_.data_type_ = data_type;
	c->uniform_.data_element_num_ = element_num;
	c->uniform_.data_offset_ = offset;
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_set_program(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_e program)
{
	return n2s_commandbuffer_add_command_program(state, cb, program);
}

N2_API n2_bool_t n2s_commandbuffer_set_renderstate(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_renderstate_e renderstate)
{
	return n2s_commandbuffer_add_command_renderstate(state, cb, renderstate);
}

N2_API n2_bool_t n2s_commandbuffer_set_texture(n2_state_t* state, n2s_commandbuffer_t* cb, const n2s_texture_t* texture)
{
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	if (cbss->draw_.texture_ == texture) { return N2_FALSE; }
	n2s_commandbuffer_flush_staging(state, cb);
	cbss->draw_.texture_ = texture;
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_set_transcolor(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_u8color_t transcolor)
{
	n2s_commandbuffer_staging_state_t* cbss = &cb->staging_;
	if (cbss->transcolor_.r_ == transcolor.r_ && cbss->transcolor_.g_ == transcolor.g_ && cbss->transcolor_.b_ == transcolor.b_) { return N2_FALSE; }
	cbss->transcolor_ = transcolor; cbss->transcolor_.a_ = 0;
	const n2s_fcolor_t ftranscolor = n2s_u8color_to_fcolor(cbss->transcolor_);
	n2s_commandbuffer_add_uniform(state, cb, N2S_GPROGRAM_UNIFORM_TRANSCOLOR, N2S_GPROGRAM_DATA_FVEC4, 1, &ftranscolor, sizeof(ftranscolor));
	return N2_TRUE;
}

N2_API void n2s_commandbuffer_triangle_textured_colored(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, const n2s_texture_t* texture, n2_fvec2_t uv0, n2_fvec2_t uv1, n2_fvec2_t uv2, n2s_u8color_t c0, n2s_u8color_t c1, n2s_u8color_t c2)
{
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, texture);
	n2s_commandbuffer_add_command_draw(state, cb, 3, 3);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, 3);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, 3);
	//if (n2_fvec2_cross(v0.xy_, v1.xy_) < 0.f) { const n2_fvec3_t t = v0; v0 = v1; v1 = t; }
	n2s_vertex_to(v + 0, v0, uv0, c0);
	n2s_vertex_to(v + 1, v1, uv1, c1);
	n2s_vertex_to(v + 2, v2, uv2, c2);
	i[0] = top_index + 0; i[1] = top_index + 2; i[2] = top_index + 1;
}

N2_API void n2s_commandbuffer_triangle_textured(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, const n2s_texture_t* texture, n2_fvec2_t uv0, n2_fvec2_t uv1, n2_fvec2_t uv2, n2s_u8color_t color)
{
	n2s_commandbuffer_triangle_textured_colored(state, cb, v0, v1, v2, texture, uv0, uv1, uv2, color, color, color);
}

N2_API void n2s_commandbuffer_triangle_colored(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, n2s_u8color_t c0, n2s_u8color_t c1, n2s_u8color_t c2)
{
	n2s_commandbuffer_triangle_textured_colored(state, cb, v0, v1, v2, NULL, n2_fvec2(0, 0), n2_fvec2(0, 0), n2_fvec2(0, 0), c0, c1, c2);
}

N2_API void n2s_commandbuffer_triangle(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, n2s_u8color_t color)
{
	n2s_commandbuffer_triangle_textured_colored(state, cb, v0, v1, v2, NULL, n2_fvec2(0, 0), n2_fvec2(0, 0), n2_fvec2(0, 0), color, color, color);
}

N2_API void n2s_commandbuffer_line(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t start, n2_fvec3_t end, n2s_u8color_t color, float thickness)
{
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, NULL);
	n2s_commandbuffer_add_command_draw(state, cb, 4, 6);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, 4);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, 6);
	start = n2_fvec3_sub(start, n2_fvec3(-0.5f, -0.5f, -0.5f));
	end = n2_fvec3_sub(end, n2_fvec3(-0.5f, -0.5f, -0.5f));
	n2_fvec3_t diff = n2_fvec3_sub(end, start);
	if (n2_fvec3_normalize_to(&diff) <= 0.f) { diff.x_ = 1.f; diff.y_ = 0.f; diff.z_ = 0.f; }
	const n2_fvec3_t hd = n2_fvec3_scale(diff, thickness * 0.5f);
	n2s_vertex_to(v + 0, n2_fvec3_add(start, n2_fvec3( hd.y_, -hd.x_, -hd.z_)), n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 1, n2_fvec3_add(end, n2_fvec3( hd.y_, -hd.x_,  hd.z_)), n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 2, n2_fvec3_add(end, n2_fvec3(-hd.y_,  hd.x_,  hd.z_)), n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 3, n2_fvec3_add(start, n2_fvec3(-hd.y_,  hd.x_, -hd.z_)), n2_fvec2(0, 0), color);
	i[0] = top_index + 0; i[1] = top_index + 2; i[2] = top_index + 1; i[3] = top_index + 0; i[4] = top_index + 3; i[5] = top_index + 2;
}

N2_API void n2s_commandbuffer_rect(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t left_top, n2_fvec3_t right_bottom, n2s_u8color_t color)
{
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, NULL);
	n2s_commandbuffer_add_command_draw(state, cb, 4, 6);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, 4);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, 6);
	n2s_vertex_to(v + 0, left_top, n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 1, n2_fvec3(right_bottom.x_, left_top.y_, (left_top.z_ + right_bottom.z_) * 0.5f), n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 2, right_bottom, n2_fvec2(0, 0), color);
	n2s_vertex_to(v + 3, n2_fvec3(left_top.x_, right_bottom.y_, (left_top.z_ + right_bottom.z_) * 0.5f), n2_fvec2(0, 0), color);
	i[0] = top_index + 0; i[1] = top_index + 2; i[2] = top_index + 1; i[3] = top_index + 0; i[4] = top_index + 3; i[5] = top_index + 2;
}

#if 0
N2_API void n2s_commandbuffer_roundrect_ex(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, float rad, float rounding, size_t rounding_corners, size_t rounding_division)
{
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, NULL);
	n2s_commandbuffer_add_command_draw(state, cb, 4, 6);
	if (rounding > scale.x_ * 0.5f) { rounding = scale.x_ * 0.5f; }
	if (rounding > scale.y_ * 0.5f) { rounding = scale.y_ * 0.5f; }
	if (rounding <= 0) { rounding_corners = 0; }
	if (rounding_division < 2) { rounding_division = 1; rounding_corners = 0; }
	size_t rounding_corner_num = 0;
	for (size_t i = 0; i < 4; ++i) { if (rounding_corners & (1 << i)) { ++rounding_corner_num; } }
	const size_t vnum = rounding_division * rounding_corner_num + 1 * (4 - rounding_corner_num) + 1;// + center
	const size_t inum = (vnum - 1) * 3;
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, vnum);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, inum);
	const n2_fvec2_t pivot_diff = n2_fvec2_mul(scale, n2_fvec2_sub(n2_fvec2(0.5f, 0.5f), pivot));
	const n2_fvec3_t center = n2_fvec3_add(position, n2_fvec3(pivot_diff.x_, pivot_diff.y_, 0));
	const n2_fvec2_t cs = n2_fvec2(N2_SCAST(float, N2_COS(rad)), N2_SCAST(float, N2_SIN(rad)));
	const n2_fvec2_t hcs = n2_fvec2_scale(cs, 0.5f);
	const n2_fvec2_t diff = n2_fvec2(hcs.x_ * scale.x_ + hcs.y_ * scale.y_, -hcs.y_ * scale.x_ + hcs.x_ * scale.y_);
	size_t vi = 0;
	n2s_vertex_to(vi++, center, n2_fvec2(0, 0), color);// center
	if (rounding_corners & 1)
	{
	}
	else
	{
		n2s_vertex_to(vi++, n2_fvec3_add(center, n2_fvec3(-diff.x_, -diff.y_, 0)), n2_fvec2(0, 0), color);
	}
	if (rounding_corners & 2)
	{
	}
	else
	{
		n2s_vertex_to(vi++, n2_fvec3_add(center, n2_fvec3( diff.x_, -diff.y_, 0)), n2_fvec2(0, 0), color);
	}
	if (rounding_corners & 4)
	{
	}
	else
	{
		n2s_vertex_to(vi++, n2_fvec3_add(center, n2_fvec3( diff.x_,  diff.y_, 0)), n2_fvec2(0, 0), color);
	}
	if (rounding_corners & 8)
	{
	}
	else
	{
		n2s_vertex_to(vi++, n2_fvec3_add(center, n2_fvec3(-diff.x_,  diff.y_, 0)), n2_fvec2(0, 0), color);
	}
	for (size_t j = 0; j < vnum - 1; ++j)
	{
		i[j * 3 + 0] = top_index + 0;
		i[j * 3 + 1] = top_index + (j + 1);
		i[j * 3 + 2] = top_index + ((j + 2) % (vnum - 1));
	}
}
#endif

N2_API void n2s_commandbuffer_rect_textured_rot(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, const n2s_texture_t* texture, n2_fvec2_t left_top_uv, n2_fvec2_t right_bottom_uv, float rad, size_t w, size_t h)
{
	n2s_commandbuffer_rect_textured_rotskew(state, cb, position, pivot, scale, color, texture, left_top_uv, right_bottom_uv, rad, n2_fvec2(0, 0), n2_fvec2(0, 0), w, h);
}

N2_API void n2s_commandbuffer_rect_textured_rotskew(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, const n2s_texture_t* texture, n2_fvec2_t left_top_uv, n2_fvec2_t right_bottom_uv, float rad, n2_fvec2_t topskew, n2_fvec2_t bottomskew, size_t w, size_t h)
{
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, texture);
	n2s_commandbuffer_add_command_draw(state, cb, 4, 6);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, 4);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, 6);
	const n2_fvec2_t pivot_diff = n2_fvec2_mul(scale, n2_fvec2_sub(n2_fvec2(0.5f, 0.5f), pivot));
	const n2_fvec3_t center = n2_fvec3_add(position, n2_fvec3(pivot_diff.x_, pivot_diff.y_, 0));
	const n2_fvec2_t cs = n2_fvec2(N2_SCAST(float, N2_COS(rad)), N2_SCAST(float, N2_SIN(rad)));
	const n2_fvec2_t hcs = n2_fvec2_scale(cs, 0.5f);
	const n2_fvec2_t fqdiff = n2_fvec2( hcs.x_ * scale.x_ + hcs.y_ * scale.y_,  hcs.y_ * scale.x_ - hcs.x_ * scale.y_);
	const n2_fvec2_t sqdiff = n2_fvec2(-hcs.x_ * scale.x_ + hcs.y_ * scale.y_, -hcs.y_ * scale.x_ - hcs.x_ * scale.y_);
	const n2_fvec2_t tskdiff = n2_fvec2( cs.x_ * topskew.x_ + cs.y_ * topskew.y_,  cs.y_ * topskew.x_ - cs.x_ * topskew.y_);
	const n2_fvec2_t bskdiff = n2_fvec2( cs.x_ * bottomskew.x_ + cs.y_ * bottomskew.y_,  cs.y_ * bottomskew.x_ - cs.x_ * bottomskew.y_);
	n2_fvec2_t uvc0 = left_top_uv, uvc1 = right_bottom_uv;
	n2s_uv_clamp_pixel(&uvc0, &uvc1, w, h);
	n2s_vertex_uv_clamp_to(v + 0, n2_fvec3_add(center, n2_fvec3( sqdiff.x_ + tskdiff.x_,  sqdiff.y_ + tskdiff.y_, 0)), left_top_uv, color, uvc0, uvc1);
	n2s_vertex_uv_clamp_to(v + 1, n2_fvec3_add(center, n2_fvec3( fqdiff.x_ + tskdiff.x_,  fqdiff.y_ + tskdiff.y_, 0)), n2_fvec2(right_bottom_uv.x_, left_top_uv.y_), color, uvc0, uvc1);
	n2s_vertex_uv_clamp_to(v + 2, n2_fvec3_add(center, n2_fvec3(-sqdiff.x_ + bskdiff.x_, -sqdiff.y_ + bskdiff.y_, 0)), right_bottom_uv, color, uvc0, uvc1);
	n2s_vertex_uv_clamp_to(v + 3, n2_fvec3_add(center, n2_fvec3(-fqdiff.x_ + bskdiff.x_, -fqdiff.y_ + bskdiff.y_, 0)), n2_fvec2(left_top_uv.x_, right_bottom_uv.y_), color, uvc0, uvc1);
	i[0] = top_index + 0; i[1] = top_index + 2; i[2] = top_index + 1; i[3] = top_index + 0; i[4] = top_index + 3; i[5] = top_index + 2;
}

N2_API void n2s_commandbuffer_circle_wire(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t center, n2_fvec2_t scale, n2s_u8color_t color, float thickness, size_t div)
{
	if (div < 3) { return; }
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, NULL);
	const size_t vertex_num = div * 2;
	const size_t index_num = div * 6;
	n2s_commandbuffer_add_command_draw(state, cb, vertex_num, index_num);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, vertex_num);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, index_num);
	const float ht = thickness * 0.5f;
	for (size_t r = 0; r < div; ++r)
	{
		const float rad = N2_SCAST(float, r) / N2_SCAST(float, div) * N2_SCAST(float, N2_MPI) * 2.f;
		const float c = N2_SCAST(float, N2_COS(rad)); const float s = N2_SCAST(float, N2_SIN(rad));
		n2s_vertex_to(v + r * 2 + 0, n2_fvec3_add(center, n2_fvec3(c * (scale.x_ + ht), s * (scale.y_ + ht), 0)), n2_fvec2(0, 0), color);
		n2s_vertex_to(v + r * 2 + 1, n2_fvec3_add(center, n2_fvec3(c * (scale.x_ - ht), s * (scale.y_ - ht), 0)), n2_fvec2(0, 0), color);
		const n2s_index_t ri = N2_SCAST(n2s_index_t, r);
		const n2s_index_t rni = N2_SCAST(n2s_index_t, r == div - 1 ? 0 : r + 1);
		i[r * 6 + 0] = top_index + ri * 2 + 0; i[r * 6 + 1] = top_index + rni * 2 + 1; i[r * 6 + 2] = top_index + rni * 2 + 0;
		i[r * 6 + 3] = top_index + ri * 2 + 0; i[r * 6 + 4] = top_index + ri * 2 + 1; i[r * 6 + 5] = top_index + rni * 2 + 1;
	}
}

N2_API void n2s_commandbuffer_circle(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t center, n2_fvec2_t scale, n2s_u8color_t color, size_t div)
{
	if (div < 3) { return; }
	const n2s_index_t top_index = N2_SCAST(n2s_index_t, n2s_commandbuffer_vertex_size(cb));
	n2s_commandbuffer_set_texture(state, cb, NULL);
	const size_t vertex_num = div + 1;
	const size_t index_num = div * 3;
	n2s_commandbuffer_add_command_draw(state, cb, vertex_num, index_num);
	n2s_vertex_t* v = n2s_commandbuffer_alloc_vertex(state, cb, vertex_num);
	n2s_index_t* i = n2s_commandbuffer_alloc_index(state, cb, index_num);
	n2s_vertex_to(v + 0, center, n2_fvec2(0, 0), color);
	for (size_t r = 0; r < div; ++r)
	{
		const float rad = N2_SCAST(float, r) / N2_SCAST(float, div) * N2_SCAST(float, N2_MPI) * 2.f;
		const float c = N2_SCAST(float, N2_COS(rad)); const float s = N2_SCAST(float, N2_SIN(rad));
		n2s_vertex_to(v + r + 1, n2_fvec3_add(center, n2_fvec3(c * scale.x_ * 0.5f, s * scale.y_ * 0.5f, 0)), n2_fvec2(0, 0), color);
		i[r * 3 + 0] = top_index + 0; i[r * 3 + 1] = top_index + N2_SCAST(n2s_index_t, r); i[r * 3 + 2] = top_index + N2_SCAST(n2s_index_t, r == div - 1 ? 1 : r + 1);
	}
}

typedef struct n2si_commandbuffer_text_context_t n2si_commandbuffer_text_context_t;
struct n2si_commandbuffer_text_context_t
{
	n2si_font_text_bb_context_t bb_context_;
	n2_state_t* state_;
	n2s_commandbuffer_t* cb_;
	size_t flags_;
	n2_fvec3_t begin_;
	const n2s_text_render_unit_t* units_;
	size_t unit_num_;
};

static void n2si_commandbuffer_text_callback(const n2s_font_text_callback_param_t* param, void* user)
{
	n2si_commandbuffer_text_context_t* context = N2_RCAST(n2si_commandbuffer_text_context_t*, user);
	n2si_font_text_bb_callback(param, &context->bb_context_);
	const float s = context->bb_context_.height_;
	const n2s_glyph_t* g = param->glyph_;
	if (g && (param->codepoint_ != 0x0a/*lf*/))
	{
		n2_fvec3_t position = n2_fvec3(context->begin_.x_ + context->bb_context_.draw_cursor_.x_ + g->pixel_offset_x_ * s, context->begin_.y_ + context->bb_context_.draw_cursor_.y_ + (g->pixel_ascent_ + g->pixel_offset_y_) * s, context->begin_.z_);
		if (context->flags_ & N2S_TEXT_RENDER_FLAG_PIXEL_PERFECT)
		{
			// make it pixel perfect
			position.x_ = N2_SCAST(float, N2_FLOOR(position.x_));
			position.y_ = N2_SCAST(float, N2_FLOOR(position.y_));
		}
		for (size_t i = 0; i < context->unit_num_; ++i)
		{
			const n2s_text_render_unit_t* unit = context->units_ + i;
			if (!unit->enable_ || unit->scale_.x_ <= 0.f || unit->scale_.y_ <= 0.f) { continue; }

			const n2_fvec2_t gs = n2_fvec2(g->pixel_width_ * s * unit->scale_.x_, g->pixel_height_ * s * unit->scale_.y_);
			const n2_fvec2_t gsdiff = n2_fvec2(s * (unit->scale_.x_ - 1.f), s * (unit->scale_.y_ - 1.f));
			n2_fvec3_t uposition = position;
			uposition.x_ += unit->offset_.x_ + gsdiff.x_ * 0.5f;
			uposition.y_ += unit->offset_.y_ + gsdiff.y_ * 0.5f;

			n2s_commandbuffer_rect_textured_rotskew(
				context->state_,
				context->cb_,
				uposition,
				n2_fvec2(0, 0),
				gs,
				unit->color_,
				param->font_->texture_,
				n2_fvec2(g->uv_ltx_, g->uv_lty_),
				n2_fvec2(g->uv_rbx_, g->uv_rby_),
				0,
				n2_fvec2(unit->topskew_, 0),
				n2_fvec2(0, 0),
				0, 0
			);
		}
	}
}

N2_API n2_bool_t n2s_commandbuffer_text_units(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, const n2s_text_render_unit_t* units, size_t unit_num, float wrap_width, size_t flags, n2_fvec2_t* dst_bb)
{
	if (!font) { return N2_FALSE; }
	n2si_commandbuffer_text_context_t context;
	n2si_font_text_bb_context_init(&context.bb_context_, height, wrap_width);
	context.state_ = state;
	context.cb_ = cb;
	context.flags_ = flags;
	context.begin_ = begin;
	context.units_ = units;
	context.unit_num_ = unit_num;
	n2s_font_text(state, font, str, str_length, n2si_commandbuffer_text_callback, &context);
	n2s_texture_submit(state, font->texture_, N2_FALSE);
	if (dst_bb) { *dst_bb = context.bb_context_.bb_; }
	return N2_TRUE;
}

N2_API n2_bool_t n2s_commandbuffer_text(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, n2s_u8color_t color, float wrap_width, size_t flags, n2_fvec2_t* dst_bb)
{
	n2s_text_render_unit_t unit;
	unit.enable_ = N2_TRUE;
	unit.color_ = color;
	unit.scale_ = n2_fvec2(1, 1);
	unit.offset_ = n2_fvec2(0, 0);
	unit.topskew_ = 0.f;
	return n2s_commandbuffer_text_units(state, cb, begin, font, str, str_length, height, &unit, 1, wrap_width, flags, dst_bb);
}

N2_API n2_bool_t n2s_commandbuffer_text_ex(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, n2s_u8color_t color, float wrap_width, size_t flags, n2_fvec2_t* dst_bb, float topskew, n2_bool_t dropshadow, n2s_u8color_t dscolor, n2_fvec2_t dsscale, n2_fvec2_t dsoffset, n2_bool_t outline, n2s_u8color_t olcolor, n2_fvec2_t olscale, n2_fvec2_t oloffset)
{
	n2s_text_render_unit_t units[3];
	size_t unit_num = 0;
	// dropshadow
	if (dropshadow)
	{
		units[unit_num].enable_ = N2_TRUE;
		units[unit_num].color_ = dscolor;
		units[unit_num].scale_ = dsscale;
		units[unit_num].offset_ = dsoffset;
		units[unit_num].topskew_ = topskew;
		++unit_num;
	}
	// outline
	if (outline)
	{
		units[unit_num].enable_ = N2_TRUE;
		units[unit_num].color_ = olcolor;
		units[unit_num].scale_ = olscale;
		units[unit_num].offset_ = oloffset;
		units[unit_num].topskew_ = topskew;
		++unit_num;
	}
	// foreground
	{
		units[unit_num].enable_ = N2_TRUE;
		units[unit_num].color_ = color;
		units[unit_num].scale_ = n2_fvec2(1, 1);
		units[unit_num].offset_ = n2_fvec2(0, 0);
		units[unit_num].topskew_ = topskew;
		++unit_num;
	}
	return n2s_commandbuffer_text_units(state, cb, begin, font, str, str_length, height, units, unit_num, wrap_width, flags, dst_bb);
}

N2_API void n2s_commandbuffer_draw_cache_init(n2s_commandbuffer_draw_cache_t* cbdc)
{
	cbdc->drawenv_ = NULL;
	cbdc->d3env_ = NULL;

	cbdc->program_ = -1;
	cbdc->texture_ = NULL;
	cbdc->renderstate_ = -1;
	cbdc->samplerfilter_ = -1;
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM; ++i) { n2s_gprogram_uniform_data_init(&cbdc->uniforms_[i]); }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM; ++i) { n2s_gprogram_draw_cache_reset(&cbdc->program_cache_[i]); }

#if N2_CONFIG_USE_SDL_LIB
	cbdc->use_vao_ = GL_INVALID_INDEX;
	cbdc->use_vbo_ = GL_INVALID_INDEX;
	cbdc->use_ebo_ = GL_INVALID_INDEX;
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { cbdc->use_ubo_[i] = GL_INVALID_INDEX; }
#endif
}

static void n2si_renderstate_apply(n2_state_t* state, n2s_renderstate_e renderstate)
{
	N2_UNUSE(state);
#if N2_CONFIG_USE_SDL_LIB
	N2SI_ASSERT_GL(state);

	glEnable(GL_STENCIL_TEST);// stenciltest
	glFrontFace(GL_CCW);// frontface
	glCullFace(GL_BACK);// cullface
	glEnable(GL_SCISSOR_TEST);// scissortest
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// polygonmode
	N2SI_ASSERT_GL(state);

	n2_bool_t is_cull = N2_FALSE;
	n2_bool_t is_depth_test = N2_FALSE;
	n2_bool_t is_depth_write = N2_FALSE;

	switch (renderstate)
	{
	case N2S_RENDERSTATE_2D_NOBLEND:
		glDisable(GL_BLEND);
		break;
	case N2S_RENDERSTATE_2D_BLEND_ALPHA:
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case N2S_RENDERSTATE_2D_BLEND_ADD:
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_SRC_ALPHA, GL_ONE);
		break;
	case N2S_RENDERSTATE_2D_BLEND_SUB:
		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE, GL_SRC_ALPHA, GL_ONE);
		break;
	default:
		glDisable(GL_BLEND);
		break;
	}
	N2SI_ASSERT_GL(state);

	if (is_cull)
	{
		glEnable(GL_CULL_FACE);// culling
	}
	else
	{
		glDisable(GL_CULL_FACE);// culling
	}
	if (is_depth_test)
	{
		glEnable(GL_DEPTH_TEST);// depthtest
	}
	else
	{
		glDisable(GL_DEPTH_TEST);// depthtest
	}

	if (is_depth_write)
	{
		glDepthMask(GL_TRUE);// depthwrite
	}
	else
	{
		glDepthMask(GL_FALSE);// depthwrite
	}

	N2SI_ASSERT_GL(state);
#else
	N2_UNUSE(gmode);
#endif
}

static n2s_gprogram_e n2si_gmode_to_program(n2s_gmode_e gmode)
{
	switch (gmode)
	{
	case N2S_GMODE_COPY:				return N2S_GPROGRAM_2D;
	case N2S_GMODE_MEMCOPY:				return N2S_GPROGRAM_2D;
	case N2S_GMODE_COPY_BLACKTRANS:		return N2S_GPROGRAM_2D_TRANSCOLOR;
	case N2S_GMODE_BLEND:				return N2S_GPROGRAM_2D;
	case N2S_GMODE_BLEND_COLTRANS:		return N2S_GPROGRAM_2D_TRANSCOLOR;
	case N2S_GMODE_BLEND_ADD:			return N2S_GPROGRAM_2D;
	case N2S_GMODE_BLEND_SUB:			return N2S_GPROGRAM_2D;
	case N2S_GMODE_BLEND_RALPHA:		return N2S_GPROGRAM_2D;
	default:							break;
	}
	return N2S_GPROGRAM_2D;
}

static n2s_renderstate_e n2si_gmode_to_renderstate(n2s_gmode_e gmode)
{
	switch (gmode)
	{
	case N2S_GMODE_COPY:				return N2S_RENDERSTATE_2D_NOBLEND;
	case N2S_GMODE_MEMCOPY:				return N2S_RENDERSTATE_2D_NOBLEND;
	case N2S_GMODE_COPY_BLACKTRANS:		return N2S_RENDERSTATE_2D_BLEND_ALPHA;
	case N2S_GMODE_BLEND:				return N2S_RENDERSTATE_2D_BLEND_ALPHA;
	case N2S_GMODE_BLEND_COLTRANS:		return N2S_RENDERSTATE_2D_BLEND_ALPHA;
	case N2S_GMODE_BLEND_ADD:			return N2S_RENDERSTATE_2D_BLEND_ADD;
	case N2S_GMODE_BLEND_SUB:			return N2S_RENDERSTATE_2D_BLEND_SUB;
	case N2S_GMODE_BLEND_RALPHA:		return N2S_RENDERSTATE_2D_BLEND_ALPHA;// サポートされてない
	default:							break;
	}
	return N2S_RENDERSTATE_2D_NOBLEND;
}

N2_API void n2s_widget_init(n2s_widget_t* widget)
{
	widget->id_ = 0;
	widget->type_ = N2S_WIDGET_BUTTON;
	widget->position_ = n2_fvec2(0, 0);
	widget->size_ = n2_fvec2(0, 0);
	n2_str_init(&widget->label_);
	widget->enable_ = N2_TRUE;
	widget->value_dirty_count_ = 0;
	widget->ivalue_ = 0;
	n2_str_init(&widget->strvalue_);
	widget->lvalue_.label_index_ = -1;
	widget->lgosub_ = N2_FALSE;
	widget->capture_ = NULL;
	widget->capture_aptr_ = 0;
}

N2_API void n2s_widget_teardown(n2_state_t* state, n2s_widget_t* widget)
{
	n2_str_teardown(state, &widget->label_);
	n2_str_teardown(state, &widget->strvalue_);
}

static int n2si_widgetset_cmpfunc(const n2_sorted_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	if (lkey && rkey) { return N2_THREE_WAY_CMP(N2_RCAST(const n2s_widget_t*, lkey)->id_, N2_RCAST(const n2s_widget_t*, rkey)->id_); }
	N2_ASSERT(key);
	const void* ekey = lkey ? lkey : rkey;
	return N2_THREE_WAY_CMP(N2_RCAST(const n2s_widget_t*, ekey)->id_, *N2_RCAST(const size_t*, key));
}

static int n2si_widgetset_matchfunc(const n2_sorted_array_t* a, const void* ekey, const void* key)
{
	N2_UNUSE(a);
	return N2_THREE_WAY_CMP(N2_RCAST(const n2s_widget_t*, ekey)->id_, *N2_RCAST(const size_t*, key));
}

static void n2si_widgetset_setupfunc(n2_state_t* state, n2s_widgetset_t* a)
{
	N2_UNUSE(state);
	a->cmp_ = n2si_widgetset_cmpfunc;
	a->match_ = n2si_widgetset_matchfunc;
}

static void n2si_widgetset_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2s_widget_t* widget = N2_RCAST(n2s_widget_t*, element);
	n2s_widget_teardown(state, widget);
}

N2_DEFINE_TSORTED_ARRAY(n2s_widget_t, void, size_t, n2s_widgetset, N2_API, n2si_widgetset_setupfunc, n2si_widgetset_freefunc);

N2_DEFINE_TARRAY(n2s_window_event_t, n2s_windoweventarray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

#if N2_CONFIG_USE_GUI_LIB
static void n2si_gui_clipboard_paste(nk_handle user, struct nk_text_edit* edit)
{
	N2_UNUSE(user);
	char* cliptext = SDL_GetClipboardText();
	if (cliptext)
	{
		nk_textedit_paste(edit, cliptext, N2_SCAST(int, N2_STRLEN(cliptext)));
		SDL_free(cliptext);
	}
}

static void n2si_gui_clipboard_copy(nk_handle user, const char* text, int len)
{
	N2_UNUSE(user);
	if (len <= 0) { return; }
	char* str = N2_RCAST(char*, SDL_malloc(N2_SCAST(size_t, len + 1)));
	if (!str) { return; }
	N2_MEMCPY(str, text, N2_SCAST(size_t, len));
	str[len] = '\0';
	SDL_SetClipboardText(str);
	SDL_free(str);
}
#endif

static void n2si_window_reset_state(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w)
{
	w->mousex_ = w->mousey_ = 0;
	w->prev_mousex_ = w->prev_mousey_ = 0;
	w->mousew_ = 0;
	w->mousebuttons_ = 0;
	w->ginfo_r_ = w->ginfo_g_ = w->ginfo_b_ = 0;
	w->ginfo_a_ = 255;

	w->ginfo_mulr_ = w->ginfo_mulg_ = w->ginfo_mulb_ = 255;

	w->objcolor_r_ = w->objcolor_g_ = w->objcolor_b_ = 0;

	w->posx_ = w->posy_ = 0;
	w->objx_ = 64; w->objy_ = 24;
	w->objminheight_ = 0;
	w->mesx_ = w->mesy_ = 0;

	w->gmode_ = N2S_GMODE_COPY;
	w->gfilter_ = N2S_GFILTER_NONE;
	w->gmode_copy_width_ = 32; w->gmode_copy_height_ = 32;

	w->draw_font_ = se->default_font_;
	w->draw_font_height_ = state->config_.standard_font_default_draw_height_;
	w->draw_font_style_ = 0;

	w->celdiv_sizex_ = w->celdiv_sizey_ = 0;
	w->cel_offset_ = n2_fvec2(0, 0);

	if (w->widgets_) { n2s_widgetset_clear(state, w->widgets_); }
	w->next_widget_id_ = 0;
}

static n2s_window_t* n2si_window_alloc(n2_state_t* state, n2s_environment_t* se, n2s_window_e type, size_t width, size_t height, size_t flags, n2_bool_t startup)
{
	n2s_window_t* w = N2_TMALLOC(n2s_window_t, state);

	w->type_ = type;
	n2_str_init(&w->name_);
	n2_str_init(&w->title_);

	w->width_ = width;
	w->height_ = height;

	w->dpiscale_x_ = 1.0;
	w->dpiscale_x_ = 1.0;

	w->redraw_ = N2_TRUE;

	w->texturebuffer_ = NULL;
	w->drawcachebuffer_ = NULL;

	w->events_ = n2s_windoweventarray_alloc(state, 256, 256);
	n2_str_init(&w->textinput_);

	w->draw_font_ = se->default_font_;
	w->draw_font_height_ = state->config_.standard_font_default_draw_height_;
	w->draw_font_style_ = 0;

	w->widgets_ = NULL;
	w->next_widget_id_ = 0;

	w->hwnd_ = 0;
	w->hdc_ = 0;
	w->hinstance_ = 0;

#if N2_CONFIG_USE_SDL_LIB
	w->window_ = NULL;
	w->gl_context_ = NULL;
	w->gl_framebuffer_ = 0;
#if N2I_ENABLE_SDL_RENDERER
	w->renderer_ = NULL;
#endif
#endif

#if N2_CONFIG_USE_GUI_LIB
	w->nk_context_ = NULL;
	w->nk_cmd_buf_ = NULL;
#endif

#if N2_CONFIG_USE_SDL_LIB
	if (w->type_ == N2S_WINDOW_SCREEN)
	{
		flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

		// 作るときのサイズ
		const size_t create_sizex = width;
		const size_t create_sizey = height;

		w->window_ = SDL_CreateWindow(state->config_.standard_window_default_title_, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, N2_SCAST(int, create_sizex), N2_SCAST(int, create_sizey), N2_SCAST(Uint32, flags));

		// @todo error handling

		SDL_SetWindowMinimumSize(w->window_, 1, 1);// N2S_WINDOW_SIZE_MIN 以下の値も使用するので、最小サイズはこれに設定しておく
		SDL_SetWindowMaximumSize(w->window_, N2S_WINDOW_SIZE_MAX, N2S_WINDOW_SIZE_MAX);

		int draw_width = 0, draw_height = 0;
		SDL_GL_GetDrawableSize(w->window_, &draw_width, &draw_height);
		w->dpiscale_x_ = N2_SCAST(double, N2_MAX(draw_width, 1)) / N2_SCAST(double, create_sizex);
		w->dpiscale_y_ = N2_SCAST(double, N2_MAX(draw_height, 1)) / N2_SCAST(double, create_sizey);
		//printf("wh(%zu, %zu) draw wh(%d, %d) dpiscale(%lf, %lf)\n", w->width_, w->height_, draw_width, draw_height, w->dpiscale_x_, w->dpiscale_y_);
#if N2_PLATFORM_IS_EMSCRIPTEN
		//printf("devicePixelRatio=%lf\n", emscripten_get_device_pixel_ratio());
#endif

		w->gl_context_ = SDL_GL_CreateContext(w->window_);

		if (startup)
		{
			N2_ASSERT(!se->gl_context_);
			se->gl_context_ = w->gl_context_;

			// load all opengl functions
			gladLoadGLES2Loader(&SDL_GL_GetProcAddress);
		}

		SDL_GL_MakeCurrent(w->window_, se->gl_context_);
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &w->gl_framebuffer_);
		N2SI_ASSERT_GL(state);

		SDL_SetWindowData(w->window_, "n2hsp.window_", w);

		// @todo
		// 最終的に同じサイズに設定しているだけなのだが、
		// これでWin環境のwgl初期化時のフレームバッファのカラースペース（srgb）誤認問題が治るコトがあるので、
		// ワークアラウンドとして入れておく。（WinというかOpenGLドライバーの問題）
		// 最初の初期化時と、次の初期化時とでフレームバッファの初期化コンテキストがたぶん違うのだろう
#if N2_PLATFORM_IS_WINDOWS
		if (startup && state->config_.standard_window_resize_on_creation_workaround_)
		{
			SDL_SetWindowSize(w->window_, N2_SCAST(int, N2S_WINDOW_SIZE_MIN - 1), N2_SCAST(int, N2S_WINDOW_SIZE_MIN - 1));
			SDL_SetWindowSize(w->window_, N2_SCAST(int, w->width_), N2_SCAST(int, w->height_));
		}
#endif

		SDL_SysWMinfo wminfo;
		SDL_VERSION(&wminfo.version);
		if (SDL_GetWindowWMInfo(w->window_, &wminfo))
		{
#if N2_PLATFORM_IS_WINDOWS
			w->hwnd_ =  N2_SCAST(n2_valint_t, N2_RCAST(intptr_t, wminfo.info.win.window));
			w->hdc_ = N2_SCAST(n2_valint_t, N2_RCAST(intptr_t, wminfo.info.win.hdc));
			w->hinstance_ = N2_SCAST(n2_valint_t, N2_RCAST(intptr_t, wminfo.info.win.hinstance));
#else
			N2_UNUSE(wminfo);
#endif
		}

#if N2I_ENABLE_SDL_RENDERER
		{
			int driver_index = -1;
			for (int it = 0; it < SDL_GetNumRenderDrivers(); ++it)
			{
				SDL_RendererInfo rinfo;
				SDL_GetRenderDriverInfo(it, &rinfo);

				n2i_printf(state, "%s\n", rinfo.name);
				if (N2_STRCMP(rinfo.name, "opengles2") == 0)
				{
					driver_index = it;
					break;
				}
			}

			w->renderer_ = SDL_CreateRenderer(w->window_, driver_index, SDL_RENDERER_ACCELERATED);
		}
#endif
	}

	N2_ASSERT(!startup || w->window_);
#endif

	w->texturebuffer_ = n2si_texturebuffer_alloc(state, width, height);
	if (w->type_ == N2S_WINDOW_SCREEN)
	{
		w->drawcachebuffer_ = n2si_texturebuffer_alloc(state, width, height);
	}

#if N2_CONFIG_USE_GUI_LIB
	w->nk_context_ = N2_TMALLOC(struct nk_context, state);
	struct nk_allocator nk_alloc;
	nk_alloc.alloc = n2si_nk_plugin_alloc;
	nk_alloc.free = n2si_nk_plugin_free;
	nk_alloc.userdata.ptr = state;
	nk_init(w->nk_context_, &nk_alloc, w->draw_font_ ? w->draw_font_->nk_font_ : NULL);

	w->nk_context_->clip.paste = n2si_gui_clipboard_paste;
	w->nk_context_->clip.copy = n2si_gui_clipboard_copy;
	w->nk_context_->clip.userdata.ptr = w;

	w->nk_cmd_buf_ = N2_TMALLOC(struct nk_buffer, state);
	nk_buffer_init(w->nk_cmd_buf_, &nk_alloc, 1024);

	{
		struct nk_color coltable[NK_COLOR_COUNT];
		coltable[NK_COLOR_TEXT] = nk_rgba(0, 0, 0, 255);
		coltable[NK_COLOR_WINDOW] = nk_rgba(202, 212, 214, 215);
		coltable[NK_COLOR_HEADER] = nk_rgba(137, 182, 224, 220);
		coltable[NK_COLOR_BORDER] = nk_rgba(140, 159, 173, 255);
		coltable[NK_COLOR_BUTTON] = nk_rgba(215, 215, 215, 255);
		coltable[NK_COLOR_BUTTON_HOVER] = nk_rgba(229, 241, 251, 255);
		coltable[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(204, 228, 247, 255);
		coltable[NK_COLOR_TOGGLE] = nk_rgba(115, 115, 115, 255);
		coltable[NK_COLOR_TOGGLE_HOVER] = nk_rgba(181, 181, 181, 255);
		coltable[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(204, 228, 474, 255);
		coltable[NK_COLOR_SELECT] = nk_rgba(177, 210, 210, 255);
		coltable[NK_COLOR_SELECT_ACTIVE] = nk_rgba(137, 182, 224, 255);
		coltable[NK_COLOR_SLIDER] = nk_rgba(177, 210, 210, 255);
		coltable[NK_COLOR_SLIDER_CURSOR] = nk_rgba(137, 182, 224, 245);
		coltable[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(142, 188, 229, 255);
		coltable[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(147, 193, 234, 255);
		coltable[NK_COLOR_PROPERTY] = nk_rgba(210, 210, 210, 255);
		coltable[NK_COLOR_EDIT] = nk_rgba(210, 210, 210, 225);
		coltable[NK_COLOR_EDIT_CURSOR] = nk_rgba(20, 20, 20, 255);
		coltable[NK_COLOR_COMBO] = nk_rgba(210, 210, 210, 255);
		coltable[NK_COLOR_CHART] = nk_rgba(210, 210, 210, 255);
		coltable[NK_COLOR_CHART_COLOR] = nk_rgba(137, 182, 224, 255);
		coltable[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba( 255, 0, 0, 255);
		coltable[NK_COLOR_SCROLLBAR] = nk_rgba(241, 241, 241, 255);
		coltable[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(215, 215, 215, 255);
		coltable[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(250, 250, 250, 255);
		coltable[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(204, 204, 204, 255);
		coltable[NK_COLOR_TAB_HEADER] = nk_rgba(156, 193, 220, 255);
		nk_style_from_table(w->nk_context_, coltable);

		struct nk_style* style = &w->nk_context_->style;
		style->button.rounding = 0.f;
	}

	w->widgets_ = n2s_widgetset_alloc(state, 0, 8);
#endif

	n2si_window_reset_state(state, se, w);

	return w;
}

static void n2si_window_free(n2_state_t* state, n2s_window_t* w)
{
	n2_str_teardown(state, &w->name_);
	n2_str_teardown(state, &w->title_);

	n2s_windoweventarray_free(state, w->events_);
	n2_str_teardown(state, &w->textinput_);

	if (w->widgets_) { n2s_widgetset_free(state, w->widgets_); w->widgets_ = NULL; }

#if N2_CONFIG_USE_GUI_LIB
	if (w->nk_cmd_buf_)
	{
		nk_buffer_free(w->nk_cmd_buf_);
		n2_free(state, w->nk_cmd_buf_);
		w->nk_cmd_buf_ = NULL;
	}
	if (w->nk_context_)
	{
		nk_free(w->nk_context_);
		n2_free(state, w->nk_context_);
		w->nk_context_ = NULL;
	}
#endif

	if (w->texturebuffer_)
	{
		n2si_texturebuffer_free(state, w->texturebuffer_);
		w->texturebuffer_ = NULL;
	}
	if (w->drawcachebuffer_)
	{
		n2si_texturebuffer_free(state, w->drawcachebuffer_);
		w->drawcachebuffer_ = NULL;
	}

#if N2_CONFIG_USE_SDL_LIB
#if N2I_ENABLE_SDL_RENDERER
	if (w->renderer_)
	{
		SDL_DestroyRenderer(w->renderer_);
		w->renderer_ = NULL;
	}
#endif
	if (w->window_)
	{
		SDL_DestroyWindow(w->window_);
		w->window_ = NULL;
	}
#endif

	n2_free(state, w);
}

static n2_bool_t n2si_window_is_keyboard_focus(const n2s_window_t* w)
{
#if N2_CONFIG_USE_SDL_LIB
	if (w->window_)
	{
		if (w->window_ == SDL_GetKeyboardFocus()) { return N2_TRUE; }
	}
#else
	N2_UNUSE(w);
#endif
	return N2_FALSE;
}

static n2_bool_t n2si_window_is_mouse_focus(const n2s_window_t* w)
{
#if N2_CONFIG_USE_SDL_LIB
	if (w->window_)
	{
		if (w->window_ == SDL_GetMouseFocus()) { return N2_TRUE; }
	}
#else
	N2_UNUSE(w);
#endif
	return N2_FALSE;
}

static void n2si_window_set_title(n2_state_t* state, n2s_window_t* w, const char* str)
{
	n2_str_set(state, &w->title_, str, SIZE_MAX);

#if N2_CONFIG_USE_SDL_LIB
	if (w->window_) { SDL_SetWindowTitle(w->window_, w->title_.str_); }
#endif
}

static n2_bool_t n2si_window_sync_drawbuffer_from_texturebuffer(n2_state_t* state, n2s_window_t* w)
{
	if (!w->drawcachebuffer_) { return N2_FALSE; }
	n2si_texturebuffer_resize(state, w->drawcachebuffer_, w->width_, w->height_, N2_FALSE);
	N2_ASSERT(w->drawcachebuffer_->texture_.imagebuf_.size_ == w->texturebuffer_->texture_.imagebuf_.size_);
	N2_MEMCPY(w->drawcachebuffer_->texture_.imagebuf_.data_, w->texturebuffer_->texture_.imagebuf_.data_, w->drawcachebuffer_->texture_.imagebuf_.size_);
	n2s_texture_submit(state, &w->drawcachebuffer_->texture_, N2_TRUE);
	return N2_TRUE;
}

static void n2si_windowarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2s_window_t* w = *N2_RCAST(n2s_window_t**, element);
	if (w) { n2si_window_free(state, w); }
}

N2_DEFINE_TARRAY(n2s_window_t*, n2s_windowarray, N2_API, n2i_setupfunc_nothing, n2si_windowarray_freefunc);

static n2_bool_t n2si_window_register(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w, int index)
{
	n2s_window_t** pw = n2s_windowarray_peek(se->windows_, index);

	if (!pw)
	{
		n2si_window_free(state, w);
		return N2_FALSE;
	}

	if (*pw) { n2si_window_free(state, *pw); }
	*pw = w;
	return N2_TRUE;
}

static n2s_window_t* n2si_window_find_by_iid(n2s_windowarray_t* ws, size_t iid)
{
#if N2_CONFIG_USE_SDL_LIB
	N2_UNUSE(ws);
	SDL_Window* sw = SDL_GetWindowFromID(N2_SCAST(Uint32, iid));
	if (!sw) { return NULL; }
	void* data = SDL_GetWindowData(sw, "n2hsp.window_");
	if (!data) { return NULL; }
	n2s_window_t* w = N2_RCAST(n2s_window_t*, data);
	return w;
#else
	N2_UNUSE(ws);
	N2_UNUSE(iid);
	return NULL;
#endif
}

static n2s_environment_t* n2si_environment_alloc(n2_state_t* state, const char** pe)
{
#if N2_CONFIG_USE_SDL_LIB
	//SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");// 既にビルド設定でしてるから必要ない
	SDL_SetHint(SDL_HINT_TIMER_RESOLUTION, "1");

	SDL_ClearError();

	n2_bool_t init_success = N2_FALSE;
	if (state->config_.standard_init_sdl_with_subsystem_)
	{
		if (SDL_InitSubSystem(N2SI_SDL_INIT_SYSTEM_FLAGS) == 0)
		{
			init_success = N2_TRUE;
		}
	}
	else
	{
		if (SDL_Init(N2SI_SDL_INIT_SYSTEM_FLAGS) == 0)
		{
			init_success = N2_TRUE;
		}
	}

	if (!init_success)
	{
		if (pe) { *pe = SDL_GetError(); }
		return NULL;
	}

	// set attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
	//SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

	// gles3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	// immediate context
	SDL_GL_SetSwapInterval(0);
#endif

	n2s_environment_t* se = N2_TMALLOC(n2s_environment_t, state);

	se->environment_spec_.max_texture_width_ = 4096;
	se->environment_spec_.max_texture_height_ = 4096;

	for (size_t i = 0; i < N2S_MAX_GPROGRAM; ++i) { n2s_gprogram_init(&se->gprograms_[i]); }

	se->is_quit_requested_ = N2_FALSE;

	se->last_async_time_ = 0;
	se->ginfo_accx_ = se->ginfo_accy_ = se->ginfo_accz_ = 0;

	se->selected_window_index_ = 0;

	const size_t window_num = state->config_.standard_window_num_;
	se->windows_ = n2s_windowarray_alloc(state, window_num, 0);
	for (size_t i = 0, l = window_num; i < l; ++i)
	{
		const n2s_window_t* wnull = NULL;
		n2s_windowarray_push(state, se->windows_, &wnull);
	}

	se->commandbuffer_ = n2s_commandbuffer_alloc(state, state->config_.standard_command_num_, state->config_.standard_vertex_num_, state->config_.standard_index_num_, state->config_.standard_command_data_num_);
	se->syscommandbuffer_ = n2s_commandbuffer_alloc(state, 16, 256, 256, 256);

	se->default_font_ = NULL;
	se->fontset_ = n2s_fontset_alloc(state, 4, 16);
	se->font_atlas_width_ = state->config_.standard_font_atlas_width_;
	se->font_atlas_height_ = state->config_.standard_font_atlas_height_;

	se->stick_last_ = 0;

	se->imgunpackw_ = 0;
	se->imgunpackh_ = 0;

#if N2_CONFIG_USE_SDL_LIB
	se->gl_context_ = NULL;
	se->last_async_time_ = SDL_GetPerformanceCounter();
#endif

	// 0番のウィンドウを作る
	const n2_state_config_t* c = &state->config_;
	const size_t flags = N2_SDL_OR(
		(c->standard_statup_window_shown_ ? SDL_WINDOW_SHOWN : SDL_WINDOW_HIDDEN),
		0
	);
	n2s_window_t* main_window = n2si_window_alloc(state, se, N2S_WINDOW_SCREEN, c->standard_startup_window_width_, c->standard_startup_window_height_, flags, N2_TRUE);
	n2si_window_register(state, se, main_window, 0);

#if N2_CONFIG_USE_SDL_LIB
	// GLコンテキスト作ったので必要なリソースを作る
	N2_ASSERT(se->gl_context_);
	N2SI_ASSERT_GL(state);

	{
		GLint val = 0;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &val);
		se->environment_spec_.max_texture_width_ = N2_SCAST(size_t, val);
		se->environment_spec_.max_texture_height_ = N2_SCAST(size_t, val);
		N2SI_ASSERT_GL(state);
	}

	{
		const char* vsh_src = 
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UB_DRAWENV()
			N2I_GL_SHADER_DEF_ATTR_POSITION()
			N2I_GL_SHADER_DEF_ATTR_TEXCOORD()
			N2I_GL_SHADER_DEF_ATTR_COLOR()
			N2I_GL_SHADER_DEF_ATTR_TEXCOORD_CLAMP()
			"out vec2 vUV;\n"
			"out vec4 vColor;\n"
			"out vec4 vUVClamp;\n"
			"void main()\n"
			"{\n"
			"	vUV = N2_ATTR_TEXCOORD;\n"
			"	vColor = N2_ATTR_COLOR;\n"
			"	vUVClamp = vec4(min(N2_ATTR_TEXCOORD_CLAMP.xy, N2_ATTR_TEXCOORD_CLAMP.zw), max(N2_ATTR_TEXCOORD_CLAMP.xy, N2_ATTR_TEXCOORD_CLAMP.zw));\n"
			"	gl_Position = N2_PVMTX * vec4(N2_ATTR_POSITION.xyz, 1.0);\n"
			"}\n";
		const char* fsh_src =
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UNIFORM_TEXTURE()
			"in vec2 vUV;\n"
			"in vec4 vColor;\n"
			"in vec4 vUVClamp;\n"
			"out vec4 oColor;\n"
			"void main()\n"
			"{\n"
			"	vec2 uv = clamp(vUV, vUVClamp.xy, vUVClamp.zw);\n"
			"	vec4 color = vColor * texture(N2_UTEXTURE, uv);\n"
			"	oColor = color;\n"
			"}\n";
		const n2_bool_t load_succeeded = n2s_gprogram_load_to(state, &se->gprograms_[N2S_GPROGRAM_2D], vsh_src, fsh_src);
		N2_ASSERT(load_succeeded);
		N2_UNUSE(load_succeeded);
	}
	{
		const char* vsh_src = 
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UB_DRAWENV()
			N2I_GL_SHADER_DEF_ATTR_POSITION()
			N2I_GL_SHADER_DEF_ATTR_TEXCOORD()
			N2I_GL_SHADER_DEF_ATTR_COLOR()
			N2I_GL_SHADER_DEF_ATTR_TEXCOORD_CLAMP()
			"out vec2 vUV;\n"
			"out vec4 vColor;\n"
			"out vec4 vUVClamp;\n"
			"void main()\n"
			"{\n"
			"	vUV = N2_ATTR_TEXCOORD;\n"
			"	vColor = N2_ATTR_COLOR;\n"
			"	vUVClamp = vec4(min(N2_ATTR_TEXCOORD_CLAMP.xy, N2_ATTR_TEXCOORD_CLAMP.zw), max(N2_ATTR_TEXCOORD_CLAMP.xy, N2_ATTR_TEXCOORD_CLAMP.zw));\n"
			"	gl_Position = N2_PVMTX * vec4(N2_ATTR_POSITION.xyz, 1.0);\n"
			"}\n";
		const char* fsh_src =
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UNIFORM_TEXTURE()
			N2I_GL_SHADER_DEF_UNIFORM_TRANS_COLOR()
			"in vec2 vUV;\n"
			"in vec4 vColor;\n"
			"in vec4 vUVClamp;\n"
			"out vec4 oColor;\n"
			"void main()\n"
			"{\n"
			"	vec2 uv = clamp(vUV, vUVClamp.xy, vUVClamp.zw);\n"
			"	vec4 texcolor = texture(N2_UTEXTURE, uv);\n"
			"	vec4 diffcolor = abs(N2_UTRANSCOLOR - texcolor);\n"
			"	if (dot(diffcolor.xyz, vec3(1, 1, 1)) < (1.5 / 255.0)) { discard; }\n"
			"	vec4 color = vColor * texcolor;\n"
			"	oColor = color;\n"
			"}\n";
		const n2_bool_t load_succeeded = n2s_gprogram_load_to(state, &se->gprograms_[N2S_GPROGRAM_2D_TRANSCOLOR], vsh_src, fsh_src);
		N2_ASSERT(load_succeeded);
		N2_UNUSE(load_succeeded);
	}
	{
		const char* vsh_src = 
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UB_DRAWENV()
			N2I_GL_SHADER_DEF_ATTR_POSITION()
			N2I_GL_SHADER_DEF_ATTR_TEXCOORD()
			N2I_GL_SHADER_DEF_ATTR_COLOR()
			"out vec2 vUV;\n"
			"out vec4 vColor;\n"
			"void main()\n"
			"{\n"
			"	vUV = N2_ATTR_TEXCOORD;\n"
			"	vColor = N2_ATTR_COLOR;\n"
			"	gl_Position = N2_PVMTX * vec4(N2_ATTR_POSITION.xy, 0.0, 1.0);\n"
			"}\n";
		const char* fsh_src =
			N2I_GL_SHADER_HEADER()
			N2I_GL_SHADER_DEF_UNIFORM_TEXTURE()
			"in vec2 vUV;\n"
			"in vec4 vColor;\n"
			"out vec4 oColor;\n"
			"void main()\n"
			"{\n"
			"	vec2 uv = vUV;\n"
			"	vec4 color = vColor * texture(N2_UTEXTURE, uv);\n"
			"	oColor = color;\n"
			"}\n";
		const n2_bool_t load_succeeded = n2s_gprogram_load_to(state, &se->gprograms_[N2S_GPROGRAM_GUI], vsh_src, fsh_src);
		N2_ASSERT(load_succeeded);
		N2_UNUSE(load_succeeded);
	}

	glGenBuffers(1, &se->gl_cb_vbo_);
	glGenVertexArrays(1, &se->gl_cb_vao_);
	glGenBuffers(1, &se->gl_cb_ebo_);
	glGenBuffers(N2_ARRAYDIM(se->gl_cb_ubo_), se->gl_cb_ubo_);
	glGenVertexArrays(1, &se->gl_gui_vao_);
	glGenBuffers(1, &se->gl_gui_vbo_);
	glGenBuffers(1, &se->gl_gui_ebo_);
	glGenBuffers(N2_ARRAYDIM(se->gl_gui_ubo_), se->gl_gui_ubo_);
	N2SI_ASSERT_GL(state);

	n2_buffer_init(&se->gui_cmd_buf_);
	n2_buffer_reserve(state, &se->gui_cmd_buf_, 1024);
	n2_buffer_init(&se->gui_vbo_buf_);
	n2_buffer_reserve(state, &se->gui_vbo_buf_, state->config_.standard_gui_vertex_num_);
	n2_buffer_set_expand_step(&se->gui_vbo_buf_, state->config_.standard_gui_vertex_expand_step_);
	n2_buffer_init(&se->gui_ebo_buf_);
	n2_buffer_reserve(state, &se->gui_ebo_buf_, state->config_.standard_gui_index_num_);
	n2_buffer_set_expand_step(&se->gui_ebo_buf_, state->config_.standard_gui_index_expand_step_);

	{
		uint8_t cols[4];
		cols[0] = cols[1] = cols[2] = cols[3] = 255;
		se->white_texture_ = n2si_texture_alloc(state, 1, 1, cols);
		cols[0] = cols[1] = cols[2] = 0; cols[3] = 255;
		se->black_texture_ = n2si_texture_alloc(state, 1, 1, cols);
		cols[0] = cols[1] = cols[2] = cols[3] = 0;
		se->zero_texture_ = n2si_texture_alloc(state, 1, 1, cols);
		N2SI_ASSERT_GL(state);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	N2SI_ASSERT_GL(state);
#endif

#if N2_CONFIG_USE_EMBED_FONT
	{
		// decode
		n2_buffer_t fontbuf = n2hi_resource_load_bin(state, n2_ettf_mplus_generalj_cmp, n2_ettf_mplus_generalj_cmp_size, n2_ettf_mplus_generalj_scratch_key, n2_ettf_mplus_generalj_src_size);
		if (fontbuf.size_ > 0)
		{
			// load as font and register
			n2s_font_t* font = n2s_font_alloc(state, "n2default", SIZE_MAX, state->config_.standard_font_atlas_width_, state->config_.standard_font_atlas_height_);
			if (n2s_font_load_to(state, font, &fontbuf, N2_FALSE))
			{
				se->default_font_ = font;
				n2s_fontset_insertv(state, se->fontset_, font, NULL);
#if N2_CONFIG_USE_GUI_LIB
				font->nk_font_->height = state->config_.standard_font_default_draw_height_;
#endif
			}
			else
			{
				n2s_font_free(state, font);
				n2i_lprintf(state, NULL, N2_LOG_LEVEL_CRITICAL, "failed loading default font");
			}
		}
		n2_buffer_teardown(state, &fontbuf);
	}

#if N2I_CONFIG_USE_EMBED_FONT_FA_REGULAR
	if (se->default_font_)
	{
		n2_buffer_t fontbuf = n2hi_resource_load_bin(state, n2_ettf_fa_regular_400_cmp, n2_ettf_fa_regular_400_cmp_size, n2_ettf_fa_regular_400_scratch_key, n2_ettf_fa_regular_400_src_size);
		if (fontbuf.size_ > 0)
		{
			// load as font and merge
			if (!n2s_font_load_to(state, se->default_font_, &fontbuf, N2_TRUE))
			{
				n2i_lprintf(state, NULL, N2_LOG_LEVEL_CRITICAL, "failed loading default font(fa_regular_400)");
			}
		}
		n2_buffer_teardown(state, &fontbuf);
	}
#endif

#if N2I_CONFIG_USE_EMBED_FONT_FA_SOLID
	if (se->default_font_)
	{
		n2_buffer_t fontbuf = n2hi_resource_load_bin(state, n2_ettf_fa_solid_900_cmp, n2_ettf_fa_solid_900_cmp_size, n2_ettf_fa_solid_900_scratch_key, n2_ettf_fa_solid_900_src_size);
		if (fontbuf.size_ > 0)
		{
			// load as font and merge
			if (!n2s_font_load_to(state, se->default_font_, &fontbuf, N2_TRUE))
			{
				n2i_lprintf(state, NULL, N2_LOG_LEVEL_CRITICAL, "failed loading default font(fa_solid_900)");
			}
		}
		n2_buffer_teardown(state, &fontbuf);
	}
#endif

	if (se->default_font_)
	{
		// replace draw font
		for (size_t i = 0, l = n2s_windowarray_size(se->windows_); i < l; ++i)
		{
			n2s_window_t* w = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, i), NULL);
			if (!w) { continue; }
			w->draw_font_ = se->default_font_;
#if N2_CONFIG_USE_GUI_LIB
			if (w->nk_context_)
			{
				nk_style_set_font(w->nk_context_, se->default_font_->nk_font_);
			}
#endif
		}
	}
#endif

#if N2_CONFIG_USE_INSPECTOR
	se->inspector_ = NULL;
	if (state->config_.standard_use_inspector_)
	{
		se->inspector_ = n2si_window_alloc(state, se, N2S_WINDOW_SCREEN, 800, 600, SDL_WINDOW_SHOWN, N2_FALSE);
		n2si_window_set_title(state, se->inspector_, "n2_inspector");
		SDL_SetWindowPosition(se->inspector_->window_, 0, 0);
	}
#endif

	if (main_window && c->standard_statup_window_shown_)
	{
#if N2_CONFIG_USE_SDL_LIB
		if (main_window->window_) { SDL_RaiseWindow(main_window->window_); }
#endif
	}
	return se;
}

static void n2si_environment_free(n2_state_t* state, n2s_environment_t* se)
{
	n2s_commandbuffer_free(state, se->commandbuffer_);
	n2s_commandbuffer_free(state, se->syscommandbuffer_);

	n2s_fontset_free(state, se->fontset_);

	for (size_t i = 0; i < N2S_MAX_GPROGRAM; ++i) { n2s_gprogram_teardown(state, &se->gprograms_[i]); }

#if N2_CONFIG_USE_INSPECTOR
	if (se->inspector_)
	{
		n2si_window_free(state, se->inspector_);
		se->inspector_ = NULL;
	}
#endif

#if N2_CONFIG_USE_SDL_LIB
	n2si_texture_free(state, se->zero_texture_);
	n2si_texture_free(state, se->black_texture_);
	n2si_texture_free(state, se->white_texture_);
	N2SI_ASSERT_GL(state);

	n2_buffer_teardown(state, &se->gui_cmd_buf_);
	n2_buffer_teardown(state, &se->gui_vbo_buf_);
	n2_buffer_teardown(state, &se->gui_ebo_buf_);

	glDeleteVertexArrays(1, &se->gl_cb_vao_);
	glDeleteBuffers(1, &se->gl_cb_vbo_);
	glDeleteBuffers(1, &se->gl_cb_ebo_);
	glDeleteBuffers(N2_ARRAYDIM(se->gl_cb_ubo_), se->gl_cb_ubo_);
	glDeleteVertexArrays(1, &se->gl_gui_vao_);
	glDeleteBuffers(1, &se->gl_gui_vbo_);
	glDeleteBuffers(1, &se->gl_gui_ebo_);
	glDeleteBuffers(N2_ARRAYDIM(se->gl_gui_ubo_), se->gl_gui_ubo_);
	N2SI_ASSERT_GL(state);

	//if (se->gl_context_) { SDL_GL_DeleteContext(se->gl_context_); }
#endif

	// 0以外を先に解放（0がGLContextと同一のため）
	for (size_t i = 0, l = n2s_windowarray_size(se->windows_); i < l; ++i)
	{
		n2s_windowarray_erase(state, se->windows_, N2_SCAST(int, l - i - 1));
	}
	n2s_windowarray_free(state, se->windows_);

#if N2_CONFIG_USE_SDL_LIB
	if (state->config_.standard_init_sdl_with_subsystem_)
	{
		SDL_QuitSubSystem(N2SI_SDL_INIT_SYSTEM_FLAGS);
	}
	else
	{
		SDL_Quit();
	}
#endif

	n2_free(state, se);
}

#if N2_CONFIG_USE_SDL_LIB
static void n2si_gprogram_attribute_apply(n2_state_t* state, n2s_gprogram_t* p)
{
	N2_UNUSE(state);
	const size_t vstride = sizeof(n2s_vertex_t);

	for (size_t i = 0; i < N2S_MAX_GPROGRAM_ATTRIBUTE; ++i)
	{
		const int aloc = p->gl_alocation_[i];
		if (aloc >= 0)
		{
			switch (i)
			{
			case N2S_GPROGRAM_ATTRIBUTE_POSITION:
				glEnableVertexAttribArray(N2_SCAST(GLuint, aloc));
				glVertexAttribPointer(N2_SCAST(GLuint, aloc), 3, GL_FLOAT, GL_FALSE, N2_SCAST(GLsizei, vstride), N2_RCAST(void*, offsetof(n2s_vertex_t, position_)));
				break;
			case N2S_GPROGRAM_ATTRIBUTE_TEXCOORD:
				glEnableVertexAttribArray(N2_SCAST(GLuint, aloc));
				glVertexAttribPointer(N2_SCAST(GLuint, aloc), 2, GL_FLOAT, GL_FALSE, N2_SCAST(GLsizei, vstride), N2_RCAST(void*, offsetof(n2s_vertex_t, uv_)));
				break;
			case N2S_GPROGRAM_ATTRIBUTE_COLOR:
				glEnableVertexAttribArray(N2_SCAST(GLuint, aloc));
				glVertexAttribPointer(N2_SCAST(GLuint, aloc), 4, GL_UNSIGNED_BYTE, GL_TRUE, N2_SCAST(GLsizei, vstride), N2_RCAST(void*, offsetof(n2s_vertex_t, color_)));
				break;
			case N2S_GPROGRAM_ATTRIBUTE_TEXCOORD_CLAMP:
				glEnableVertexAttribArray(N2_SCAST(GLuint, aloc));
				glVertexAttribPointer(N2_SCAST(GLuint, aloc), 4, GL_FLOAT, GL_FALSE, N2_SCAST(GLsizei, vstride), N2_RCAST(void*, offsetof(n2s_vertex_t, uv_clamp_)));
				break;
			default:
				break;
			}
			N2SI_ASSERT_GL(state);
		}
	}
	N2SI_ASSERT_GL(state);
}

static n2_bool_t n2si_gprogram_uniform_apply(n2_state_t* state, n2s_gprogram_t* p, GLint location, const n2s_gprogram_uniform_data_t* data)
{
	if (!p || !data) { return N2_FALSE; }
	if (location < 0) { return N2_FALSE; }
	if (data->data_element_num_ <= 0 || !data->data_) { return N2_FALSE; }

	switch (data->data_type_)
	{
	case N2S_GPROGRAM_DATA_INT:			glUniform1iv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_IVEC2:		glUniform2iv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_IVEC3:		glUniform3iv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_IVEC4:		glUniform4iv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_UINT:		glUniform1uiv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLuint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_UVEC2:		glUniform2uiv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLuint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_UVEC3:		glUniform3uiv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLuint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_UVEC4:		glUniform4uiv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLuint*, data->data_)); break;
	case N2S_GPROGRAM_DATA_FLOAT:		glUniform1fv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLfloat*, data->data_)); break;
	case N2S_GPROGRAM_DATA_FVEC2:		glUniform2fv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLfloat*, data->data_)); break;
	case N2S_GPROGRAM_DATA_FVEC3:		glUniform3fv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLfloat*, data->data_)); break;
	case N2S_GPROGRAM_DATA_FVEC4:		glUniform4fv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_RCAST(const GLfloat*, data->data_)); break;
	case N2S_GPROGRAM_DATA_FMAT4:		glUniformMatrix4fv(location, N2_SCAST(GLsizei, data->data_element_num_), N2_FALSE, N2_RCAST(const GLfloat*, data->data_)); break;
	default:							N2_ASSERT(0); break;
	}

	return N2SI_GL_CLEAR_ERRORS(state);
}

static void n2si_gprogram_uniform_block_update(n2_state_t* state, GLuint ubo, const void* data, size_t data_size, GLenum usage)
{
	N2_UNUSE(state);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, data_size, data, usage);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	N2SI_ASSERT_GL(state);
}

static n2_bool_t n2si_gprogram_uniform_block_apply(n2_state_t* state, n2s_gprogram_t* p, GLuint binding_point, GLuint ubo)
{
	N2_UNUSE(state);
	N2_UNUSE(p);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, ubo);
	return N2SI_GL_CLEAR_ERRORS(state);
}

static void n2si_environment_draw_commandbuffer(n2_state_t* state, n2s_environment_t* se, n2s_commandbuffer_t* cb, n2s_commandbuffer_draw_cache_t* dc)
{
	const size_t vstride = sizeof(n2s_vertex_t);
	const size_t istride = sizeof(n2s_index_t);

	// 毎回適用する（効率悪いしVAOの概念を割と無視してるが）
	if (dc->use_vao_ == GL_INVALID_INDEX) { dc->use_vao_ = se->gl_cb_vao_; }
	if (dc->use_vbo_ == GL_INVALID_INDEX) { dc->use_vbo_ = se->gl_cb_vbo_; }
	if (dc->use_ebo_ == GL_INVALID_INDEX) { dc->use_ebo_ = se->gl_cb_ebo_; }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { if (dc->use_ubo_[i] == GL_INVALID_INDEX) { dc->use_ubo_[i] = se->gl_cb_ubo_[i]; } }
	glBindVertexArray(dc->use_vao_);
	glBindBuffer(GL_ARRAY_BUFFER, dc->use_vbo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dc->use_ebo_);
	N2SI_ASSERT_GL(state);

	glBufferData(GL_ARRAY_BUFFER, N2_SCAST(GLsizeiptr, n2s_commandbuffer_vertex_size(cb) * vstride), cb->vertexarray_->elements_, GL_STREAM_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, N2_SCAST(GLsizeiptr, n2s_commandbuffer_index_size(cb) * istride), cb->indexarray_->elements_, GL_STREAM_DRAW);
	N2SI_ASSERT_GL(state);

	if (dc->drawenv_) { n2si_gprogram_uniform_block_update(state, dc->use_ubo_[N2S_GPROGRAM_UNIFORM_BLOCK_DRAWENV], dc->drawenv_, sizeof(*dc->drawenv_), GL_STREAM_DRAW); }
	if (dc->d3env_) { n2si_gprogram_uniform_block_update(state, dc->use_ubo_[N2S_GPROGRAM_UNIFORM_BLOCK_D3ENV], dc->d3env_, sizeof(*dc->d3env_), GL_STREAM_DRAW); }
	for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { glBindBufferBase(GL_UNIFORM_BUFFER, N2_SCAST(GLuint, i), dc->use_ubo_[i]); }
	N2SI_ASSERT_GL(state);

	if (dc->program_ < 0) { dc->program_ = N2S_GPROGRAM_2D; }
	n2s_gprogram_t* p = &se->gprograms_[dc->program_];
	glUseProgram(p->gl_program_);
	N2SI_ASSERT_GL(state);
	n2si_gprogram_attribute_apply(state, p);

	if (!dc->texture_) { dc->texture_ = se->white_texture_; }
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dc->texture_->gl_texture_);
	N2SI_ASSERT_GL(state);

	if (dc->renderstate_ < 0) { dc->renderstate_ = N2S_RENDERSTATE_2D_NOBLEND; }
	n2si_renderstate_apply(state, dc->renderstate_);

	if (dc->samplerfilter_ < 0) { dc->samplerfilter_ = N2S_SAMPLERFILTER_NONE; }

	const n2s_command_t* commands = N2_RCAST(const n2s_command_t*, cb->commandarray_->elements_);
	n2s_index_t* ioffset = 0;
	for (size_t i = 0, l = n2s_commandbuffer_command_size(cb); i < l; ++i)
	{
		switch (commands[i].type_)
		{
		case N2S_COMMAND_DRAW:
			{
				// uniform
				n2s_gprogram_draw_cache_t* pdc = &dc->program_cache_[dc->program_];
				if (pdc->u_cached_)
				{
					for (size_t u = 0; u < N2S_MAX_GPROGRAM_UNIFORM; ++u)
					{
						const size_t uf = N2_SCAST(size_t, 1) << u;
						if (pdc->u_cached_ & uf)
						{
							n2si_gprogram_uniform_apply(state, p, p->gl_ulocation_[u], &dc->uniforms_[u]);
							pdc->u_cached_ &= ~uf;
						}
					}
				}
				if (pdc->ub_cached_)
				{
					for (size_t ub = 0; ub < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++ub)
					{
						const size_t ubf = N2_SCAST(size_t, 1) << ub;
						if (pdc->ub_cached_ & ubf)
						{
							//n2si_gprogram_uniform_block_apply(state, p, N2_SCAST(GLuint, ub), dc->use_ubo_[ub]);// プログラム毎にする必要はない
							pdc->ub_cached_ &= ~ubf;
						}
					}
				}

				// draw elements
				const n2s_command_draw_t* draw = &commands[i].draw_;
				const n2s_texture_t* draw_texture = draw->texture_;
				if (!draw_texture) { draw_texture = se->white_texture_; }
				if (dc->texture_ != draw_texture)
				{
					dc->texture_ = draw_texture;
					glBindTexture(GL_TEXTURE_2D, dc->texture_->gl_texture_);
				}
				glDrawElements(GL_TRIANGLES, N2_SCAST(GLsizei, draw->index_count_), GL_UNSIGNED_INT, ioffset);
				ioffset += draw->index_count_;
			}
			break;
		case N2S_COMMAND_PROGRAM:
			{
				const n2s_command_program_t* pg = &commands[i].program_;
				if (dc->program_ != pg->program_)
				{
					dc->program_ = pg->program_;
					p = &se->gprograms_[dc->program_];
					N2_ASSERT(p);
					glUseProgram(p->gl_program_);
					N2SI_ASSERT_GL(state);
					n2si_gprogram_attribute_apply(state, p);
				}
			}
			break;
		case N2S_COMMAND_RENDERSTATE:
			{
				const n2s_command_renderstate_t* rs = &commands[i].renderstate_;
				if (dc->renderstate_ != rs->renderstate_)
				{
					dc->renderstate_ = rs->renderstate_;
					n2si_renderstate_apply(state, dc->renderstate_);
				}
			}
			break;
		case N2S_COMMAND_SAMPLERFILTER:
			{
				const n2s_command_samplerfilter_t* sf = &commands[i].samplerfilter_;
				if (dc->samplerfilter_ != sf->samplerfilter_)
				{
					dc->samplerfilter_ = sf->samplerfilter_;
				}
			}
			break;
		case N2S_COMMAND_UNIFORM:
			{
				const n2s_command_uniform_t* u = &commands[i].uniform_;
				n2s_gprogram_uniform_data_t* ud = &dc->uniforms_[u->uniform_];
				ud->data_type_ = u->data_type_;
				ud->data_element_num_ = u->data_element_num_;
				ud->data_ = n2_u32array_peek(cb->commanddataarray_, N2_SCAST(int, u->data_offset_));
				const size_t uf = N2_SCAST(size_t, 1) << u->uniform_;
				for (size_t pi = 0; pi < N2S_MAX_GPROGRAM; ++pi) { dc->program_cache_[pi].u_cached_ |= uf; }
			}
			break;
		case N2S_COMMAND_UNIFORM_BLOCK:
			{
				const n2s_command_uniform_block_t* ub = &commands[i].uniform_block_;
				const GLuint ubo = dc->use_ubo_[ub->uniform_block_];
				if (ubo != GL_INVALID_INDEX)
				{
					const void* data = n2_u32array_peek(cb->commanddataarray_, N2_SCAST(int, ub->data_offset_));
					n2si_gprogram_uniform_block_update(state, ubo, data, ub->data_size_, GL_STREAM_DRAW);
					const size_t ubf = N2_SCAST(size_t, 1) << ub->uniform_block_;
					for (size_t pi = 0; pi < N2S_MAX_GPROGRAM; ++pi) { dc->program_cache_[pi].ub_cached_ |= ubf; }
				}
			}
			break;
		default:
			N2_ASSERT(0);
			break;
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//for (size_t i = 0; i < N2S_MAX_GPROGRAM_UNIFORM_BLOCK; ++i) { glBindBufferBase(GL_UNIFORM_BUFFER, N2_SCAST(GLuint, i), 0); }// unbindはない
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}
#endif

static void n2si_environment_flush_commandbuffer_to_window(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w)
{
	if (!w) { return; }
	n2s_commandbuffer_flush_staging(state, se->commandbuffer_);

	n2_bool_t draw_content = N2_TRUE;
	if (n2s_commandbuffer_command_size(se->commandbuffer_) <= 0) { draw_content = N2_FALSE; }
	if (n2s_commandbuffer_vertex_size(se->commandbuffer_) <= 0) { draw_content = N2_FALSE; }
	if (n2s_commandbuffer_index_size(se->commandbuffer_) <= 0) { draw_content = N2_FALSE; }

	if (w->draw_font_) { n2s_texture_submit(state, w->draw_font_->texture_, N2_FALSE); }

	if (draw_content)
	{
#if N2_CONFIG_USE_SDL_LIB
		if (w->window_) { SDL_GL_MakeCurrent(w->window_, w->gl_context_); }

		{
			//glBindFramebuffer(GL_FRAMEBUFFER, w->gl_framebuffer_);
			glBindFramebuffer(GL_FRAMEBUFFER, w->texturebuffer_->gl_framebuffer_);

			//const GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
			//glDrawBuffers(1, buffers);

			//glClearColor(0.f, 0.f, 1.f, 1.f);
			//glClear(GL_COLOR_BUFFER_BIT);

			const size_t framew = w->texturebuffer_->texture_.width_;
			const size_t frameh = w->texturebuffer_->texture_.height_;

			glViewport(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
			glScissor(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
			N2SI_ASSERT_GL(state);

			n2s_commandbuffer_draw_cache_t dc;
			n2s_commandbuffer_draw_cache_init(&dc);

			const GLint uniform_texture = 0;
			{
				n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TEXTURE];
				ud->data_type_ = N2S_GPROGRAM_DATA_INT;
				ud->data_element_num_ = 1;
				ud->data_ = &uniform_texture;
			}
			const n2s_fcolor_t uniform_transcolor = n2s_fcolor(-1, -1, -1, -1);
			{
				n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TRANSCOLOR];
				ud->data_type_ = N2S_GPROGRAM_DATA_FVEC4;
				ud->data_element_num_ = 1;
				ud->data_ = &uniform_transcolor;
			}

			n2s_guniform_block_drawenv_t drawenv;
			n2s_guniform_block_drawenv_init(&drawenv);
			n2_fmat4_ortho2d_to(&drawenv.p_mtx_, 0, N2_SCAST(float, framew), 0, N2_SCAST(float, frameh), -1, 1);
			n2_fmat4_copy_to(&drawenv.pv_mtx_, &drawenv.p_mtx_);
			n2s_guniform_block_drawenv_set_screen_param(&drawenv, framew, frameh);
			dc.drawenv_ = &drawenv;

			n2si_environment_draw_commandbuffer(state, se, se->commandbuffer_, &dc);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//glDrawBuffer(GL_FRONT);
			N2SI_ASSERT_GL(state);
		}
#else
		N2_UNUSE(state);
#endif
	}

	n2s_commandbuffer_clear(state, se->commandbuffer_);
}

static void n2si_environment_flush_commandbuffer(n2_state_t* state, n2s_environment_t* se)
{
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	n2si_environment_flush_commandbuffer_to_window(state, se, nw);
}

static n2_bool_t n2si_environment_sync_gmode_transcolor_commandbuffer(n2_state_t* state, n2s_environment_t* se, n2s_commandbuffer_t* cb)
{
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	switch (nw->gmode_)
	{
	case N2S_GMODE_COPY_BLACKTRANS:
	case N2S_GMODE_BLEND_COLTRANS:
		break;
	default:
		return N2_FALSE;
	}
	const n2s_u8color_t transcolor = nw->gmode_ == N2S_GMODE_COPY_BLACKTRANS ? N2S_COLOR_BLACK : n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, 0);
	return n2s_commandbuffer_set_transcolor(state, cb, transcolor);
}

static void n2si_environment_fullsync_gmode_commandbuffer(n2_state_t* state, n2s_environment_t* se, n2s_commandbuffer_t* cb)
{
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	n2s_commandbuffer_set_program(state, cb, n2si_gmode_to_program(nw->gmode_));
	n2s_commandbuffer_set_renderstate(state, cb, n2si_gmode_to_renderstate(nw->gmode_));
	n2si_environment_sync_gmode_transcolor_commandbuffer(state, se, cb);
}

static void n2si_environment_checkout_gmode_commandbuffer(n2_state_t* state, n2s_environment_t* se, n2s_commandbuffer_t* cb)
{
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	n2s_commandbuffer_add_command_renderstate(state, cb, n2si_gmode_to_renderstate(nw->gmode_));
	n2si_environment_sync_gmode_transcolor_commandbuffer(state, se, cb);
}

static n2_bool_t n2si_environment_check_and_flush_commandbuffer(n2_state_t* state, n2s_environment_t* se)
{
	n2_bool_t is_flush = N2_FALSE;
	if (n2s_commandbuffer_command_size(se->commandbuffer_) > state->config_.standard_command_num_) { is_flush = N2_TRUE; }
	if (n2s_commandbuffer_vertex_size(se->commandbuffer_) > state->config_.standard_vertex_num_) { is_flush = N2_TRUE; }
	if (n2s_commandbuffer_index_size(se->commandbuffer_) > state->config_.standard_index_num_) { is_flush = N2_TRUE; }
	if (!is_flush) { return N2_FALSE; }
	n2si_environment_flush_commandbuffer(state, se);
	n2si_environment_fullsync_gmode_commandbuffer(state, se, se->commandbuffer_);
	return N2_TRUE;
}

static void n2si_environment_checkout_draw_commandbuffer(n2_state_t* state, n2s_environment_t* se)
{
	n2si_environment_check_and_flush_commandbuffer(state, se);
	n2si_environment_fullsync_gmode_commandbuffer(state, se, se->commandbuffer_);
}

static n2_bool_t n2si_environemnt_input_gui(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w)
{
	N2_UNUSE(state);
	N2_UNUSE(se);
	if (!w) { return N2_FALSE; }

#if N2_CONFIG_USE_GUI_LIB
	struct nk_context* c = w->nk_context_;
	if (!c) { return N2_FALSE; }

	nk_input_begin(c);
	{
		// mouse
		nk_input_motion(c, N2_SCAST(int, w->mousex_), N2_SCAST(int, w->mousey_));
		nk_input_scroll(c, nk_vec2(0, N2_SCAST(float, w->mousew_)));

		// keys
		for (size_t i = 0, l = n2s_windoweventarray_size(w->events_); i < l; ++i)
		{
			const n2s_window_event_t* wevt = n2s_windoweventarray_peekc(w->events_, N2_SCAST(int, i));
			switch (wevt->type_)
			{
			case N2S_WINDOW_EVENT_KEY:
				switch (wevt->content_.key_.key_)
				{
				case SDLK_LSHIFT: case SDLK_RSHIFT:	nk_input_key(c, NK_KEY_SHIFT, wevt->content_.key_.is_down_); break;
				case SDLK_LCTRL: case SDLK_RCTRL:	nk_input_key(c, NK_KEY_CTRL, wevt->content_.key_.is_down_); break;
				case SDLK_DELETE:		nk_input_key(c, NK_KEY_DEL, wevt->content_.key_.is_down_); break;
				case SDLK_RETURN:		nk_input_key(c, NK_KEY_ENTER, wevt->content_.key_.is_down_); break;
				case SDLK_TAB:			nk_input_key(c, NK_KEY_TAB, wevt->content_.key_.is_down_); break;
				case SDLK_BACKSPACE:	nk_input_key(c, NK_KEY_BACKSPACE, wevt->content_.key_.is_down_); break;
				case SDLK_UP:			nk_input_key(c, NK_KEY_UP, wevt->content_.key_.is_down_); break;
				case SDLK_DOWN:			nk_input_key(c, NK_KEY_DOWN, wevt->content_.key_.is_down_); break;
				case SDLK_LEFT:			nk_input_key(c, NK_KEY_LEFT, wevt->content_.key_.is_down_); break;
				case SDLK_RIGHT:		nk_input_key(c, NK_KEY_RIGHT, wevt->content_.key_.is_down_); break;
				default:				break;
				}
				break;
			case N2S_WINDOW_EVENT_SPECIALKEY:
				switch (wevt->content_.specialkey_.key_)
				{
				case N2S_SPECIAL_KEY_UNDO:	nk_input_key(c, NK_KEY_TEXT_UNDO, wevt->content_.specialkey_.is_down_); break;
				case N2S_SPECIAL_KEY_REDO:	nk_input_key(c, NK_KEY_TEXT_REDO, wevt->content_.specialkey_.is_down_); break;
				case N2S_SPECIAL_KEY_COPY:	nk_input_key(c, NK_KEY_COPY, wevt->content_.specialkey_.is_down_); break;
				case N2S_SPECIAL_KEY_CUT:	nk_input_key(c, NK_KEY_CUT, wevt->content_.specialkey_.is_down_); break;
				case N2S_SPECIAL_KEY_PASTE:	nk_input_key(c, NK_KEY_PASTE, wevt->content_.specialkey_.is_down_); break;
				default:					break;
				}
				break;
			case N2S_WINDOW_EVENT_MOUSEBUTTON:
				{
					enum nk_buttons button = NK_BUTTON_LEFT;
					switch (wevt->content_.mousebutton_.button_)
					{
					case N2S_MOUSE_BUTTON_LEFT:		button = wevt->content_.mousebutton_.is_dclick_ ? NK_BUTTON_DOUBLE : NK_BUTTON_LEFT; break;
					case N2S_MOUSE_BUTTON_RIGHT:	button = NK_BUTTON_RIGHT; break;
					case N2S_MOUSE_BUTTON_MIDDLE:	button = NK_BUTTON_MIDDLE; break;
					default:						break;
					}
					nk_input_button(
						c,
						button,
						N2_SCAST(int, wevt->content_.mousebutton_.position_.x_),
						N2_SCAST(int, wevt->content_.mousebutton_.position_.y_),
						wevt->content_.mousebutton_.is_down_
					);
				}
				break;
			default:
				break;
			}
		}

		// text input
		{
			n2_unicp_t unicp;
			const char* p = w->textinput_.str_;
			const char* e = p + w->textinput_.size_;
			while (p < e)
			{
				unicp = 0;
				p = n2_encoding_utf8_fetch(p, &unicp);
				nk_input_unicode(c, N2_SCAST(nk_rune, unicp));
			}
		}
}
	nk_input_end(c);
	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(se);
	N2_UNUSE(w);
	return N2_FALSE;
#endif
}

static n2_bool_t n2si_environemnt_draw_gui(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w, size_t framew, size_t frameh)
{
	if (!w) { return N2_FALSE; }

#if N2_CONFIG_USE_GUI_LIB
	struct nk_context* c = w->nk_context_;
	if (!c) { return N2_FALSE; }

	{
		n2s_gprogram_t* p = &se->gprograms_[N2S_GPROGRAM_GUI];
		if (!n2s_gprogram_is_loaded(p)) { return N2_FALSE; }
	}

	static const struct nk_draw_vertex_layout_element vertex_layout_conf[] = {
		{NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(n2s_vertex_t, position_)},
		{NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(n2s_vertex_t, uv_)},
		{NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(n2s_vertex_t, color_)},
		{NK_VERTEX_LAYOUT_END}
	};

	struct nk_convert_config cnvconf;
	N2_MEMSET(&cnvconf, 0x00, sizeof(cnvconf));
	cnvconf.vertex_layout = vertex_layout_conf;
	cnvconf.vertex_size = sizeof(n2s_vertex_t);
	cnvconf.vertex_alignment = NK_ALIGNOF(n2s_vertex_t);
	cnvconf.null.texture.ptr = NULL;
	cnvconf.null.uv = nk_vec2(0, 0);
	cnvconf.circle_segment_count = 22;
	cnvconf.curve_segment_count = 22;
	cnvconf.arc_segment_count = 22;
	cnvconf.global_alpha = 1.f;
	cnvconf.shape_AA = NK_ANTI_ALIASING_ON;
	cnvconf.line_AA = NK_ANTI_ALIASING_ON;

	n2_buffer_t* cnvcbuf = &se->gui_cmd_buf_;
	n2_buffer_t* cnvvbuf = &se->gui_vbo_buf_;
	n2_buffer_t* cnvebuf = &se->gui_ebo_buf_;

	cnvcbuf->size_ = 0;
	cnvvbuf->size_ = 0;
	cnvebuf->size_ = 0;

	struct nk_buffer cbuf;
	struct nk_buffer* usecbuf = w->nk_cmd_buf_ ? w->nk_cmd_buf_ : &cbuf;

	for (size_t ci = 0; ci < 2; ++ci)
	{
		struct nk_buffer vbuf, ebuf;
		nk_buffer_init_fixed(&cbuf, cnvcbuf->data_, cnvcbuf->buffer_size_);
		nk_buffer_init_fixed(&vbuf, cnvvbuf->data_, cnvvbuf->buffer_size_);
		nk_buffer_init_fixed(&ebuf, cnvebuf->data_, cnvebuf->buffer_size_);
		nk_buffer_clear(usecbuf);
		const nk_flags cnvflags = nk_convert(c, usecbuf, &vbuf, &ebuf, &cnvconf);
		if (cnvflags == NK_CONVERT_SUCCESS)
		{
			if (usecbuf == &cbuf) { cnvcbuf->size_ = cbuf.needed; }
			cnvvbuf->size_ = vbuf.needed;
			cnvebuf->size_ = ebuf.needed;
			break;
		}
		if (ci == 0)
		{
			n2_buffer_reserve(state, cnvcbuf, cbuf.needed + 64);
			n2_buffer_reserve(state, cnvvbuf, vbuf.needed + 64);
			n2_buffer_reserve(state, cnvebuf, ebuf.needed + 64);
		}
		else
		{
			n2i_lprintf(state, NULL, N2_LOG_LEVEL_WARNING, "failed buffer reserve\n");
		}
	}

	if (usecbuf->needed > 0 && cnvvbuf->size_ > 0 && cnvebuf->size_ > 0)
	{
		n2s_font_t* font = N2_RCAST(n2s_font_t*, c->style.font->userdata.ptr);
		if (font) { n2s_texture_submit(state, font->texture_, N2_FALSE); }

		// この辺はべた書き
		n2s_gprogram_t* p = &se->gprograms_[N2S_GPROGRAM_GUI];
		N2_ASSERT(p && n2s_gprogram_is_loaded(p));

		glUseProgram(p->gl_program_);
		N2SI_ASSERT_GL(state);

		glViewport(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
		glScissor(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
		N2SI_ASSERT_GL(state);

		const float winx = N2_SCAST(float, w->width_);
		const float winy = N2_SCAST(float, w->height_);

		const float scalex = N2_SCAST(float, framew) / winx;
		const float scaley = N2_SCAST(float, frameh) / winy;

		if (p->gl_ulocation_[N2S_GPROGRAM_UNIFORM_TEXTURE] >= 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(p->gl_ulocation_[N2S_GPROGRAM_UNIFORM_TEXTURE], 0);
		}

		n2s_guniform_block_drawenv_t drawenv;
		n2s_guniform_block_drawenv_init(&drawenv);
		n2_fmat4_ortho2d_to(&drawenv.p_mtx_, 0, winx, 0, winy, -1, 1);
		n2_fmat4_copy_to(&drawenv.pv_mtx_, &drawenv.p_mtx_);
		GLuint drawenv_ubo = se->gl_gui_ubo_[N2S_GPROGRAM_UNIFORM_BLOCK_DRAWENV];
		n2si_gprogram_uniform_block_update(state, drawenv_ubo, &drawenv, sizeof(drawenv), GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, N2S_GPROGRAM_UNIFORM_BLOCK_DRAWENV, drawenv_ubo);

		N2SI_ASSERT_GL(state);

		glBindVertexArray(se->gl_gui_vao_);
		glBindBuffer(GL_ARRAY_BUFFER, se->gl_gui_vbo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, se->gl_gui_ebo_);
		N2SI_ASSERT_GL(state);

		n2si_gprogram_attribute_apply(state, p);

		glBufferData(GL_ARRAY_BUFFER, cnvvbuf->size_, cnvvbuf->data_, GL_STREAM_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, cnvebuf->size_, cnvebuf->data_, GL_STREAM_DRAW);
		N2SI_ASSERT_GL(state);

		n2si_renderstate_apply(state, N2S_RENDERSTATE_2D_BLEND_ALPHA);

		const struct nk_draw_command* cmd = NULL;
		const nk_draw_index* offset = NULL;
		nk_draw_foreach(cmd, c, usecbuf)
		{
			if (!cmd->elem_count) { continue; }
			const n2s_texture_t* texture = N2_RCAST(const n2s_texture_t*, cmd->texture.ptr);
			if (!texture) { texture = se->white_texture_; }
			glBindTexture(GL_TEXTURE_2D, texture->gl_texture_);
			glScissor(
				N2_SCAST(GLint, cmd->clip_rect.x * scalex),
				N2_SCAST(GLint, N2_SCAST(float, frameh) - (cmd->clip_rect.y + cmd->clip_rect.h) * scaley),
				N2_SCAST(GLint, cmd->clip_rect.w * scalex),
				N2_SCAST(GLint, cmd->clip_rect.h * scaley)
			);
			glDrawElements(GL_TRIANGLES, N2_SCAST(GLsizei, cmd->elem_count), sizeof(nk_draw_index) == sizeof(nk_ushort) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, offset);
			offset += cmd->elem_count;
		}

		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		N2SI_ASSERT_GL(state);
	}

	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(se);
	N2_UNUSE(w);
	N2_UNUSE(framew);
	N2_UNUSE(frameh);
	return N2_FALSE;
#endif
}

static n2_bool_t n2si_environment_present_widgets(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w, size_t framew, size_t frameh)
{
	if (!w->widgets_) { return N2_FALSE; }
	if (framew <= 0 || frameh <= 0) { return N2_FALSE; }

	n2_bool_t res = N2_FALSE;
#if N2_CONFIG_USE_GUI_LIB
	struct nk_context* c = w->nk_context_;
	if (!c) { return N2_FALSE; }
	if (!c->style.font) { return N2_FALSE; }
	if (!n2s_gprogram_is_loaded(&se->gprograms_[N2S_GPROGRAM_GUI])) { return N2_FALSE; }

	// 入力処理
	n2si_environemnt_input_gui(state, se, w);

	// キャンバスとして使う
	{
		const float width = N2_SCAST(float, w->width_);
		const float height = N2_SCAST(float, w->height_);

		const struct nk_vec2 panel_padding = c->style.window.padding;
		const struct nk_vec2 item_spacing = c->style.window.spacing;
		const struct nk_style_item window_background = c->style.window.fixed_background;

		// 前準備
		{
			c->style.window.spacing = nk_vec2(0,0);
			c->style.window.padding = nk_vec2(0,0);
			c->style.window.fixed_background = nk_style_item_color(nk_rgba(0, 0, 0, 0));

			nk_window_set_bounds(c, "MainWindow", nk_rect(0, 0, width, height));
			nk_begin(c, "MainWindow", nk_rect(0, 0, width, height), NK_WINDOW_BACKGROUND | NK_WINDOW_NO_SCROLLBAR/* | NK_WINDOW_NO_INPUT*/);

			struct nk_rect total_space;
			total_space = nk_window_get_content_region(c);
			nk_layout_space_begin(c, NK_STATIC, height, INT_MAX);
		}

		// 各ウィジェット
		n2_str_t widgetlabel;
		n2_str_init(&widgetlabel);
		for (size_t wi = 0, wl = n2s_widgetset_size(w->widgets_); wi < wl; ++wi)
		{
			n2s_widget_t* widget = n2s_widgetset_peek(w->widgets_, N2_SCAST(int, wi));

			switch (widget->type_)
			{
			case N2S_WIDGET_BUTTON:
				nk_layout_space_push(c, nk_rect(widget->position_.x_, widget->position_.y_, widget->size_.x_, widget->size_.y_));
				n2_str_fmt_to(state, &widgetlabel, "%s", widget->label_.str_);
				if (nk_button_label(c, widgetlabel.str_)) { ++widget->value_dirty_count_; }
				break;
			case N2S_WIDGET_CHECKBOX:
				{
					nk_layout_space_push(c, nk_rect(widget->position_.x_, widget->position_.y_, widget->size_.x_, widget->size_.y_));
					n2_str_fmt_to(state, &widgetlabel, "%s", widget->label_.str_);
					nk_bool active = widget->ivalue_ ? nk_true : nk_false;
					if (nk_checkbox_label(c, widgetlabel.str_, &active)) { ++widget->value_dirty_count_; widget->ivalue_ = !widget->ivalue_; }
				}
				break;
			case N2S_WIDGET_INPUT:
			case N2S_WIDGET_TEXTBOX:
				{
					const n2_bool_t is_multiline = widget->type_ == N2S_WIDGET_TEXTBOX;
					nk_layout_space_push(c, nk_rect(widget->position_.x_, widget->position_.y_, widget->size_.x_, widget->size_.y_));
					n2_str_fmt_to(state, &widgetlabel, "%s", widget->label_.str_);
					int len = N2_SCAST(int, widget->strvalue_.size_);
					const nk_flags action = nk_edit_string(c, (is_multiline ? NK_EDIT_EDITOR : NK_EDIT_FIELD), widget->strvalue_.str_, &len, N2_SCAST(int, widget->strvalue_.buffer_size_), NULL);
					widget->strvalue_.size_ = N2_SCAST(size_t, len);
					widget->strvalue_.str_[widget->strvalue_.size_] = '\0';
					const nk_flags comit_flags = NK_EDIT_DEACTIVATED;
					if (action & comit_flags) { ++widget->value_dirty_count_; }
				}
				break;
			default:
				break;
			}
		}
		n2_str_teardown(state, &widgetlabel);

		// 後処理
		{
			nk_layout_space_end(c);
			nk_end(c);
			c->style.window.spacing = panel_padding;
			c->style.window.padding = item_spacing;
			c->style.window.fixed_background = window_background;
		}
	}

	// 実際の描画
	n2si_environemnt_draw_gui(state, se, w, framew, frameh);

	// クリア
	nk_clear(c);
#else
	N2_UNUSE(state);
	N2_UNUSE(se);
	N2_UNUSE(w);
#endif
	return res;
}

static void n2si_environment_present_window(n2_state_t* state, n2s_environment_t* se, n2s_window_t* w)
{
#if N2_CONFIG_USE_SDL_LIB
	if (!w->window_) { return; }
	SDL_GL_MakeCurrent(w->window_, w->gl_context_);
	{
		int drawx = 0, drawy = 0;
		SDL_GL_GetDrawableSize(w->window_, &drawx, &drawy);
		const size_t framew = N2_SCAST(size_t, drawx);
		const size_t frameh = N2_SCAST(size_t, drawy);

		const float winx = N2_SCAST(float, w->texturebuffer_->texture_.width_);
		const float winy = N2_SCAST(float, w->texturebuffer_->texture_.height_);

		n2s_commandbuffer_t* cb = se->syscommandbuffer_;

		n2s_commandbuffer_draw_cache_t dc;
		n2s_guniform_block_drawenv_t drawenv;
		const GLint uniform_texture = 0;
		const n2s_fcolor_t uniform_transcolor = n2s_fcolor(-1, -1, -1, -1);

		if (w->redraw_ && w->drawcachebuffer_)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, w->drawcachebuffer_->gl_framebuffer_);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glViewport(0, 0, N2_SCAST(GLsizei, winx), N2_SCAST(GLsizei, winy));
			glScissor(0, 0, N2_SCAST(GLsizei, winx), N2_SCAST(GLsizei, winy));
			N2SI_ASSERT_GL(state);

			{
				n2s_commandbuffer_draw_cache_init(&dc);
				dc.program_ = N2S_GPROGRAM_2D;
				dc.renderstate_ = N2S_RENDERSTATE_2D_NOBLEND;
				{
					n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TEXTURE];
					ud->data_type_ = N2S_GPROGRAM_DATA_INT;
					ud->data_element_num_ = 1;
					ud->data_ = &uniform_texture;
				}
				{
					n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TRANSCOLOR];
					ud->data_type_ = N2S_GPROGRAM_DATA_FVEC4;
					ud->data_element_num_ = 1;
					ud->data_ = &uniform_transcolor;
				}
				n2s_guniform_block_drawenv_init(&drawenv);
				n2_fmat4_ortho2d_to(&drawenv.p_mtx_, 0, 1, 0, 1, -1, 1);
				n2_fmat4_copy_to(&drawenv.pv_mtx_, &drawenv.p_mtx_);
				dc.drawenv_ = &drawenv;
			}

			n2s_commandbuffer_rect_textured_rot(state, cb, n2_fvec3(0, 0, 0), n2_fvec2(0, 0), n2_fvec2(1, 1), N2S_COLOR_WHITE, &w->texturebuffer_->texture_, n2_fvec2(0, N2SI_FLIP_V(0)), n2_fvec2(1, N2SI_FLIP_V(1)), 0, 0, 0);
			n2s_commandbuffer_flush_staging(state, cb);
			n2si_environment_draw_commandbuffer(state, se, cb, &dc);
			n2s_commandbuffer_clear(state, cb);
		}

		{
			const n2s_texturebuffer_t* wtexturebuffer = w->drawcachebuffer_ ? w->drawcachebuffer_ : w->texturebuffer_;
			N2_ASSERT(wtexturebuffer);

			glBindFramebuffer(GL_FRAMEBUFFER, w->gl_framebuffer_);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glViewport(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
			glScissor(0, 0, N2_SCAST(GLsizei, framew), N2_SCAST(GLsizei, frameh));
			N2SI_ASSERT_GL(state);

			{
				n2s_commandbuffer_draw_cache_init(&dc);
				dc.program_ = N2S_GPROGRAM_2D;
				dc.renderstate_ = N2S_RENDERSTATE_2D_NOBLEND;
				{
					n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TEXTURE];
					ud->data_type_ = N2S_GPROGRAM_DATA_INT;
					ud->data_element_num_ = 1;
					ud->data_ = &uniform_texture;
				}
				{
					n2s_gprogram_uniform_data_t* ud = &dc.uniforms_[N2S_GPROGRAM_UNIFORM_TRANSCOLOR];
					ud->data_type_ = N2S_GPROGRAM_DATA_FVEC4;
					ud->data_element_num_ = 1;
					ud->data_ = &uniform_transcolor;
				}
				n2s_guniform_block_drawenv_init(&drawenv);
				n2_fmat4_ortho2d_to(&drawenv.p_mtx_, 0, 1, 0, 1, -1, 1);
				n2_fmat4_copy_to(&drawenv.pv_mtx_, &drawenv.p_mtx_);
				dc.drawenv_ = &drawenv;
			}

			n2s_commandbuffer_rect_textured_rot(state, cb, n2_fvec3(0, 0, 0), n2_fvec2(0, 0), n2_fvec2(1, 1), N2S_COLOR_WHITE, &wtexturebuffer->texture_, n2_fvec2(0, N2SI_FLIP_V(0)), n2_fvec2(1, N2SI_FLIP_V(1)), 0, 0, 0);
			n2s_commandbuffer_flush_staging(state, cb);
			n2si_environment_draw_commandbuffer(state, se, cb, &dc);
			n2s_commandbuffer_clear(state, cb);
		}

		{
			n2si_environment_present_widgets(state, se, w, framew, frameh);
		}

		// clear alpha as 1
		//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		N2SI_ASSERT_GL(state);
	}
#if N2I_ENABLE_SDL_RENDERER && 0// test code
	if (w->renderer_)
	{
		SDL_SetRenderDrawBlendMode(w->renderer_, SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(w->renderer_, 128, 128, 128, 255);
		SDL_Rect rect;
		rect.x = 150; rect.y = 150; rect.w = 100; rect.h = 100;
		SDL_RenderFillRect(w->renderer_, &rect);
		SDL_RenderPresent(w->renderer_);
	}
#endif
	SDL_GL_SwapWindow(w->window_);
#else
	N2_UNUSE(state);
	N2_UNUSE(se);
	N2_UNUSE(w);
#endif
}

static n2_bool_t n2si_environment_update_widget_dirty(n2_state_t* state, n2_fiber_t* f, n2s_window_t* w);

static void n2si_environment_frame_update(n2_state_t* state, n2s_environment_t* se)
{
#if N2_CONFIG_USE_SDL_LIB
	// flush all command
	n2si_environment_flush_commandbuffer(state, se);
	n2si_environment_fullsync_gmode_commandbuffer(state, se, se->commandbuffer_);

	// clear per frame window data
	for (size_t i = 0, l = n2s_windowarray_size(se->windows_); i < l; ++i)
	{
		n2s_window_t* w = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, i), NULL);
		if (!w) { continue; }

		w->prev_mousex_ = w->mousex_;
		w->prev_mousey_ = w->mousey_;
		w->mousew_ = 0;
		n2s_windoweventarray_clear(state, w->events_);
		n2_str_clear(&w->textinput_);
	}

	// poll all events
	SDL_Event evt;

	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT:
			se->is_quit_requested_ = N2_TRUE;
			break;
		case SDL_WINDOWEVENT:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.motion.windowID);
				if (w)
				{
					switch (evt.window.event)
					{
					case SDL_WINDOWEVENT_CLOSE:
						se->is_quit_requested_ = N2_TRUE;
						break;
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					//case SDL_WINDOWEVENT_RESIZED:
						if (evt.window.data1 >= N2S_WINDOW_SIZE_MIN && evt.window.data2 >= N2S_WINDOW_SIZE_MIN/* これらのサイズは特殊用途 */)
						{
							if (w->width_ != N2_SCAST(size_t, evt.window.data1) || w->height_ != N2_SCAST(size_t, evt.window.data2))
							{
								w->width_ = N2_SCAST(size_t, evt.window.data1);
								w->height_ = N2_SCAST(size_t, evt.window.data2);
								n2si_texturebuffer_resize(state, w->texturebuffer_, w->width_, w->height_, N2_TRUE);
								n2si_texturebuffer_resize(state, w->drawcachebuffer_, w->width_, w->height_, N2_TRUE);
							}
							// dpiスケールは毎回更新
							int draw_width = 0, draw_height = 0;
							SDL_GL_GetDrawableSize(w->window_, &draw_width, &draw_height);
							w->dpiscale_x_ = N2_SCAST(double, N2_MAX(draw_width, 1)) / N2_SCAST(double, w->width_);
							w->dpiscale_y_ = N2_SCAST(double, N2_MAX(draw_height, 1)) / N2_SCAST(double, w->height_);
						}
						break;
					default:
						break;
					}
				}
			}
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.motion.windowID);
				if (w)
				{
					const n2_bool_t is_down_src = evt.type == SDL_KEYDOWN;
					const Uint8* keystates = SDL_GetKeyboardState(NULL);
					n2_bool_t tohandle = N2_FALSE;
					n2s_window_event_t wevt;

					// as normal key
					wevt.type_ = N2S_WINDOW_EVENT_KEY;
					wevt.content_.key_.key_ = evt.key.keysym.sym;
					wevt.content_.key_.is_down_ = is_down_src;
					n2s_windoweventarray_push(state, w->events_, &wevt);

					// as specialkey
					n2_bool_t is_down = is_down_src;
					wevt.type_ = N2S_WINDOW_EVENT_SPECIALKEY;
					switch (evt.key.keysym.sym)
					{
					case SDLK_LSHIFT: case SDLK_RSHIFT:	wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_SHIFT; tohandle = N2_TRUE; break;
					case SDLK_LCTRL: case SDLK_RCTRL:	wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_CTRL; tohandle = N2_TRUE; break;
					case SDLK_LALT: case SDLK_RALT:		wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_ALT; tohandle = N2_TRUE; break;
					case SDLK_c:	is_down = (is_down && keystates[SDL_SCANCODE_LCTRL]); wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_COPY; tohandle = N2_TRUE; break;
					case SDLK_v:	is_down = (is_down && keystates[SDL_SCANCODE_LCTRL]); wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_PASTE; tohandle = N2_TRUE; break;
					case SDLK_x:	is_down = (is_down && keystates[SDL_SCANCODE_LCTRL]); wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_CUT; tohandle = N2_TRUE; break;
					case SDLK_y:	is_down = (is_down && keystates[SDL_SCANCODE_LCTRL]); wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_REDO; tohandle = N2_TRUE; break;
					case SDLK_z:	is_down = (is_down && keystates[SDL_SCANCODE_LCTRL]); wevt.content_.specialkey_.key_ = N2S_SPECIAL_KEY_UNDO; tohandle = N2_TRUE; break;
					default:		break;
					}
					if (tohandle)
					{
						wevt.content_.specialkey_.is_down_ = is_down;
						n2s_windoweventarray_push(state, w->events_, &wevt);
					}
				}
			}
			break;
		case SDL_MOUSEMOTION:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.motion.windowID);
				if (w)
				{
#if 0
					w->mousex_ = N2_SCAST(n2_valint_t, N2_SCAST(double, evt.motion.x) * w->dpiscale_x_);
					w->mousey_ = N2_SCAST(n2_valint_t, N2_SCAST(double, evt.motion.y) * w->dpiscale_y_);
#else
					w->mousex_ = N2_SCAST(n2_valint_t, evt.motion.x);
					w->mousey_ = N2_SCAST(n2_valint_t, evt.motion.y);
#endif
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.motion.windowID);
				//printf("mousebutton w(%p) down(%d) lr(%d)\n", w, evt.type == SDL_MOUSEBUTTONDOWN, (evt.button.button == SDL_BUTTON_LEFT ? N2S_MOUSE_BUTTON_LEFT : evt.button.button == SDL_BUTTON_RIGHT ? N2S_MOUSE_BUTTON_RIGHT : N2S_MOUSE_BUTTON_MIDDLE));
				if (w)
				{
					n2s_window_event_t wevt;
					wevt.type_ = N2S_WINDOW_EVENT_MOUSEBUTTON;
					wevt.content_.mousebutton_.button_ = (evt.button.button == SDL_BUTTON_LEFT ? N2S_MOUSE_BUTTON_LEFT : evt.button.button == SDL_BUTTON_RIGHT ? N2S_MOUSE_BUTTON_RIGHT : N2S_MOUSE_BUTTON_MIDDLE);
					wevt.content_.mousebutton_.is_down_ = evt.type == SDL_MOUSEBUTTONDOWN;
					wevt.content_.mousebutton_.is_dclick_ = evt.button.clicks > 1;
					wevt.content_.mousebutton_.position_ = n2_fvec2(N2_SCAST(float, evt.button.x), N2_SCAST(float, evt.button.y));
					n2s_windoweventarray_push(state, w->events_, &wevt);
					if (wevt.content_.mousebutton_.is_down_) { w->mousebuttons_ |= N2_SCAST(size_t, 1 << wevt.content_.mousebutton_.button_); }
					else { w->mousebuttons_ &= ~N2_SCAST(size_t, 1 << wevt.content_.mousebutton_.button_); }
				}
			}
			break;
		case SDL_MOUSEWHEEL:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.wheel.windowID);
				if (w) { w->mousew_ += evt.wheel.y; }
			}
			break;
		case SDL_TEXTINPUT:
			{
				n2s_window_t* w = n2si_window_find_by_iid(se->windows_, evt.text.windowID);
				if (w) { n2_str_append(state, &w->textinput_, evt.text.text, SIZE_MAX); }
			}
			break;
		default:
			break;
		}
	}

	// present
	for (size_t i = 0, l = n2s_windowarray_size(se->windows_); i < l; ++i)
	{
		n2s_window_t* w = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, i), NULL);
		if (!w) { continue; }

		if (w->window_) { n2si_environment_present_window(state, se, w); }
	}

#if N2_CONFIG_USE_INSPECTOR
	// inspector
	if (se->inspector_)
	{
		n2si_environment_present_window(state, se, se->inspector_);
	}
#endif

#endif

	// update widget dirty
	for (size_t i = 0, l = n2s_windowarray_size(se->windows_); i < l; ++i)
	{
		n2s_window_t* w = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, i), NULL);
		if (!w) { continue; }

		n2si_environment_update_widget_dirty(state, state->main_fiber_, w);
	}
}

//=============================================================================
// 実行環境

static void n2i_environment_bind_core_builtins(n2_state_t* state, n2_environment_t* e);
static void n2i_environment_bind_basic_builtins(n2_state_t* state, n2_environment_t* e);
static void n2i_environment_bind_console_builtins(n2_state_t* state, n2_environment_t* e);
static void n2i_environment_bind_standards_builtins(n2_state_t* state, n2_pp_context_t* ppc, n2_environment_t* e);

static void n2i_callframe_init(n2_callframe_t* cf)
{
	cf->caller_ = N2_CALLER_EXTERNAL;
	cf->caller_pc_ = -1;
	cf->caller_function_ = NULL;
	cf->caller_label_ = NULL;
	cf->next_pc_ = -1;
	cf->shortframe_cursor_ = 0;
	cf->csflags_ = 0;
	cf->base_ = 0;
	cf->arg_num_ = 0;
	cf->original_arg_num_ = 0;
	cf->local_vars_ = NULL;
#if N2_CONFIG_USE_DEBUGGING
	cf->debugvarpool_ = NULL;
	cf->debugvarroot_ = NULL;
	cf->debugvarargs_ = NULL;
#endif
#if N2_CONFIG_USE_PROFILING
	cf->call_timestamp_ = 0;
#endif
}
static void n2i_callframe_teardown(n2_state_t* state, n2_callframe_t* cf)
{
	N2_UNUSE(state);
	N2_UNUSE(cf);
#if N2_CONFIG_USE_DEBUGGING
	if (cf->debugvarargs_) { n2_debugvararray_free(state, cf->debugvarargs_); cf->debugvarargs_ = NULL; }
	if (cf->debugvarroot_) { n2_debugvarpool_push(state, cf->debugvarpool_, cf->debugvarroot_); cf->debugvarroot_ = NULL; }
	cf->debugvarpool_ = NULL;
#endif
}

static void n2i_callframearray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2_callframe_t* cf = N2_RCAST(n2_callframe_t*, element);
	n2i_callframe_teardown(state, cf);
}
N2_DEFINE_TARRAY(n2_callframe_t, n2_callframearray, N2_API, n2i_setupfunc_nothing, n2i_callframearray_freefunc);

N2_DEFINE_TARRAY(n2_shortframe_t, n2_shortframearray, N2_API, n2i_setupfunc_nothing, n2i_freefunc_nothing);

N2_API n2_shortframe_t* n2_shortframearray_find_last_typed(n2_shortframearray_t* shortframes, n2_shortframe_e type)
{
	for (size_t i = 0, l = n2_shortframearray_size(shortframes); i < l; ++i)
	{
		n2_shortframe_t* sf = n2_shortframearray_peek(shortframes, -N2_SCAST(int, i) - 1);
		if (sf->type_ == type) { return sf; }
	}
	return NULL;
}

static size_t n2i_shortframearray_compute_popnum_to(const n2_shortframearray_t* shortframes, const n2_shortframe_t* sf)
{
	const int index = n2_shortframearray_compute_index(shortframes, sf);
	if (index < 0) { return 0; }
	const size_t size = n2_shortframearray_size(shortframes);
	if (size <= 0) { return 0; }
	const size_t lindex = N2_MIN(N2_SCAST(size_t, index), size - 1);
	const size_t pop_num = size - lindex;
	return pop_num;
}

N2_API size_t n2_shortframearray_pop_to(n2_state_t* state, n2_shortframearray_t* shortframes, n2_shortframe_t* sf)
{
	const size_t pop_num = n2i_shortframearray_compute_popnum_to(shortframes, sf);
	if (pop_num > 0) { n2_shortframearray_pop(state, shortframes, pop_num); }
	return pop_num;
}

static size_t n2i_fiber_shortframearray_pop_to(n2_state_t* state, n2_fiber_t* f, n2_shortframe_t* sf)
{
	const size_t pop_num = n2i_shortframearray_compute_popnum_to(f->shortframes_, sf);
	if (pop_num > 0)
	{
		for(size_t i = 0; i < pop_num; ++i)
		{
			const n2_shortframe_t* csf = n2_shortframearray_peekc(f->shortframes_, -N2_SCAST(int, i) - 1);
			N2_ASSERT(csf);
			if (csf->type_ == N2_SHORTFRAME_LOOP) { --f->looplev_; }
		}
		n2_shortframearray_pop(state, f->shortframes_, pop_num);
	}
	return pop_num;
}

static void n2i_fiber_logmes(n2_state_t* state, n2_fiber_t* fiber, n2_str_t* message)
{
	n2_environment_t* e = fiber->environment_;
	if (!e || !e->messagelogs_) { return; }
	if (state->config_.max_message_log_ <= 0) { return; }
	n2i_lprintf(state, fiber, N2_LOG_LEVEL_LOGMES, "%s", message->str_);
	while (n2_plstrarray_size(e->messagelogs_) >= state->config_.max_message_log_) { n2_plstrarray_erase(state, e->messagelogs_, 0); }
	n2_plstrarray_pushv(state, e->messagelogs_, message->str_ ? message->str_ : "");
	n2_str_init(message);
}

N2_API n2_fiber_t* n2_fiber_alloc(n2_state_t* state, n2_environment_t* e, int id, const char* name, size_t name_length)
{
	n2_fiber_t* fiber = N2_TMALLOC(n2_fiber_t, state);
	fiber->id_ = id;
	n2_str_init(&fiber->name_);
	n2_str_set(state, &fiber->name_, name, name_length);
	fiber->fiber_state_ = N2_FIBER_STATE_INITIALIZED;
	fiber->exit_code_ = 0;
	fiber->has_error_ = N2_FALSE;
	fiber->ast_evaluate_context_ = NULL;
	fiber->yield_await_duration_ms_ = 0;
	fiber->environment_ = e;
	fiber->values_ = n2_valuearray_alloc(state, 64, 64);
	fiber->callstate_.flags_ = 0;
	fiber->callstate_.base_ = 0;
	fiber->callstate_.arg_num_ = 0;
	fiber->callstate_.original_arg_num_ = 0;
	fiber->callstate_.func_ = NULL;
	fiber->callstate_.label_ = NULL;
#if N2_CONFIG_USE_DEBUGGING
	fiber->callstate_.debugvarargs_ = NULL;
#endif
	fiber->pc_ = -1;
	fiber->op_pc_ = -1;
	fiber->protectframe_ = NULL;
	fiber->callframes_ = n2_callframearray_alloc(state, 16, 16);
	fiber->shortframes_ = n2_shortframearray_alloc(state, 16, 16);
	fiber->curscope_local_vars_ = NULL;
	fiber->notevar_ = NULL;
	fiber->noteaptr_ = -1;
	fiber->cnt_ = 0;
	fiber->stat_ = 0;
	fiber->refdval_ = 0;
	fiber->refstr_ = n2_str_alloc(state, 1024);
	fiber->strsize_ = 0;
	fiber->looplev_ = 0;
	fiber->sort_indices_ = n2_intarray_alloc(state, 0, 0);
	fiber->sort_fill_ = n2_intarray_alloc(state, 0, 0);
	fiber->ease_type_ = N2_EASE_LINEAR;
	fiber->ease_start_ = 0;
	fiber->ease_end_ = 1;
#if N2_CONFIG_USE_DEBUGGING
	fiber->debugint_type_ = N2_DEBUGINT_NONE;
	fiber->debugint_granularity_ = N2_DEBUGINT_GRANULARITY_LINE;
	fiber->debugint_granule_size_ = 0;
	fiber->debugint_call_depth_ = 0;
	fiber->debugvarpool_ = NULL;
	fiber->debugvarroot_ = NULL;
	fiber->debugvarsysvar_ = NULL;
	for (size_t i = 0; i < N2_ARRAYDIM(fiber->debugvarsysvarelements_); ++i) { fiber->debugvarsysvarelements_[i] = NULL; }
	if (state->config_.generate_debugvars_)
	{
		fiber->debugvarpool_ = e->debugvarpool_;
		fiber->debugvarroot_ = n2_debugvarpool_pop_or_alloc(state, e->debugvarpool_);
		fiber->debugvarroot_->type_ = N2_DEBUGVARIABLE_FIBER;
		fiber->debugvarroot_->v_.fiber_ = fiber;
		fiber->debugvarsysvar_ = n2_debugvarpool_pop_or_alloc(state, e->debugvarpool_);;
		fiber->debugvarsysvar_->type_ = N2_DEBUGVARIABLE_SYSVAR;
		fiber->debugvarsysvar_->v_.sysvar_.fiber_ = fiber;
		for (size_t i = 0; i < N2_ARRAYDIM(fiber->debugvarsysvarelements_); ++i)
		{
			fiber->debugvarsysvarelements_[i] = n2_debugvarpool_pop_or_alloc(state, e->debugvarpool_);
			fiber->debugvarsysvarelements_[i]->type_ = N2_DEBUGVARIABLE_SYSVAR_ELEMENT;
			fiber->debugvarsysvarelements_[i]->v_.sysvar_element_.fiber_ = fiber;
			fiber->debugvarsysvarelements_[i]->v_.sysvar_element_.sysvar_index_ = N2_SCAST(int, i);
		}
	}
#endif
	return fiber;
}

N2_API void n2_fiber_free(n2_state_t* state, n2_fiber_t* fiber)
{
#if N2_CONFIG_USE_DEBUGGING
	if (fiber->debugvarroot_) { n2_debugvarpool_push(state, fiber->debugvarpool_, fiber->debugvarroot_); fiber->debugvarroot_ = NULL; }
	if (fiber->debugvarsysvar_) { n2_debugvarpool_push(state, fiber->debugvarpool_, fiber->debugvarsysvar_); fiber->debugvarsysvar_ = NULL; }
	for (size_t i = 0; i < N2_ARRAYDIM(fiber->debugvarsysvarelements_); ++i) { if (fiber->debugvarsysvarelements_[i]) { n2_debugvarpool_push(state, fiber->debugvarpool_, fiber->debugvarsysvarelements_[i]); fiber->debugvarsysvarelements_[i] = NULL; } }
	fiber->debugvarpool_ = NULL;
#endif
	n2_intarray_free(state, fiber->sort_fill_);
	n2_intarray_free(state, fiber->sort_indices_);
	n2_str_free(state, fiber->refstr_);
	n2_shortframearray_free(state, fiber->shortframes_);
	n2_callframearray_free(state, fiber->callframes_);
	if (fiber->curscope_local_vars_) { n2_vararray_free(state, fiber->curscope_local_vars_); }
	n2_valuearray_free(state, fiber->values_);
	n2_str_teardown(state, &fiber->name_);
	n2_free(state, fiber);
}

N2_API n2_bool_t n2_fiber_is_finished(const n2_fiber_t* fiber)
{
	switch (fiber->fiber_state_)
	{
	case N2_FIBER_STATE_END:
	//case N2_FIBER_STATE_FINISHED:
	case N2_FIBER_STATE_ERROR:
		return N2_TRUE;
	default:
		break;
	}
	return N2_FALSE;
}

N2_API n2_environment_t* n2_environment_alloc(n2_state_t* state)
{
	n2_environment_t* e = N2_TMALLOC(n2_environment_t, state);
	e->parsers_ = n2_parserarray_alloc(state, 0, 128);
	e->asts_ = n2_astarray_alloc(state, 0, 128);
	e->codeimage_ = n2_codeimage_alloc(state);
	e->vartable_ = n2_vartable_alloc(state, 128, 128);
	e->functable_ = n2_functable_alloc(state, 128, 128);
	e->labels_ = n2_labelarray_alloc(state, 0, 64);
	e->moduletable_ = n2_moduletable_alloc(state, 0, 16);
	e->uselibs_dirty_ = N2_TRUE;
	e->uselibs_ = n2_uselibarray_alloc(state, 0, 4);
	e->sysvar_ex_ = n2_sysvarexarray_alloc(state, 0, 8);
	e->load_error_ = N2_FALSE;
	e->last_error_ = n2_str_alloc(state, 0);
	e->is_core_bounded_ = N2_FALSE;
	e->module_core_modclass_id_ = -1;
	e->is_basics_bounded_ = N2_FALSE;
	e->is_consoles_bounded_ = N2_FALSE;
	e->is_standards_bounded_ = N2_FALSE;
	e->standard_environment_ = NULL;
	n2h_random_init(&e->random_, 0x0123456789abcdefULL);// 固定値
	e->messagelogs_ = n2_plstrarray_alloc(state, state->config_.max_message_log_ , 4);
#if N2_CONFIG_USE_DEBUGGING
	e->debughook_ = NULL;
	e->debugvarpool_ = NULL;
	e->debugvarroot_ = NULL;
	if (state->config_.generate_debugvars_)
	{
		e->debugvarpool_ = n2_debugvarpool_alloc(state, 256);
		e->debugvarroot_ = n2_debugvarpool_pop_or_alloc(state, e->debugvarpool_);
		e->debugvarroot_->type_ = N2_DEBUGVARIABLE_ENVIRONMENT;
		e->debugvarroot_->v_.environment_ = e;
	}
#endif
#if N2_CONFIG_USE_PROFILING
	e->is_profiling_ = N2_FALSE;
#endif
	return e;
}

N2_API void n2_environment_free(n2_state_t* state, n2_environment_t* e)
{
	n2_plstrarray_free(state, e->messagelogs_);
	if (e->standard_environment_) { n2si_environment_free(state, e->standard_environment_); }
	n2_str_free(state, e->last_error_);
	n2_sysvarexarray_free(state, e->sysvar_ex_);
	n2_uselibarray_free(state, e->uselibs_);
	n2_moduletable_free(state, e->moduletable_);
	n2_labelarray_free(state, e->labels_);
	n2_functable_free(state, e->functable_);
	n2_vartable_free(state, e->vartable_);
	n2_codeimage_free(state, e->codeimage_);
	n2_astarray_free(state, e->asts_);
	n2_parserarray_free(state, e->parsers_);
#if N2_CONFIG_USE_DEBUGGING
	if (e->debugvarroot_) { n2_debugvarpool_push(state, e->debugvarpool_, e->debugvarroot_); e->debugvarroot_ = NULL; }
	if (e->debugvarpool_) { n2_debugvarpool_free(state, e->debugvarpool_); e->debugvarpool_ = NULL; }
	n2_environment_detach_debughook(state, e);
#endif
	n2_free(state, e);
}

static n2_bool_t n2i_environment_generate(n2_state_t* state, n2_environment_t* e, n2_ast_node_t* ast, const n2_sourcecode_t* sourcecode);

N2_API n2_bool_t n2_environment_load_str(n2_state_t* state, n2_pp_context_t* ppc, n2_environment_t* e, const char* package, const char* script, size_t script_size, const char* src_filepath_hint)
{
	if ((!package && !src_filepath_hint) || !script) { return N2_FALSE; }

	n2_parser_t* p = NULL;
	n2_ast_node_t* staging_ast = NULL;

	n2_sourcecode_t* rootsourcecode = n2_sourcecode_alloc(state);
	n2_sourcecode_t* usesourcecode = rootsourcecode;

	n2_str_t* filepathstr = &rootsourcecode->src_filepath_;
	n2_str_t* packagestr = &rootsourcecode->package_;

	if (src_filepath_hint)
	{
		n2_str_set(state, filepathstr, src_filepath_hint, SIZE_MAX);
		n2_str_set(state, &rootsourcecode->src_loaded_filepath_, src_filepath_hint, SIZE_MAX);

		// searchpathやpackageの抜き出し
		n2_path_split(state, &rootsourcecode->searchpath_, NULL, NULL, filepathstr);
		n2_path_basename(state, &rootsourcecode->src_filename_, filepathstr, NULL, 0);
		n2_str_copy_to(state, packagestr, &rootsourcecode->src_filename_);

		// commonのsearchpathに追加
		if (rootsourcecode->searchpath_.size_ > 0)
		{
			n2_plstrarray_pushv(state, ppc->searchpaths_, n2_plstr_clone(state, rootsourcecode->searchpath_.str_));
		}
	}

	if (package) { n2_str_set(state, packagestr, package, SIZE_MAX); }
	else { package = packagestr->str_; }// ないならsrc_filepathから同期

	n2_str_t* scriptstr = &rootsourcecode->src_script_;
	n2_str_set(state, scriptstr, script, script_size);

	n2_str_t* ppscriptstr = &rootsourcecode->src_ppscript_;

	// 既にエラー？
	if (e->load_error_)
	{
		n2i_raise_as(state, N2_ERROR_COMPILE, rootsourcecode, package, NULL, -1, "既にloadがエラーになっているため、更にloadすることが出来ません");
		goto fail_exit;
	}

	n2_bool_t is_valid_encoding = n2i_sourcecode_autoencode_src(state, scriptstr);

	// 最後にもう一回チェック
	if (!is_valid_encoding)
	{
		// UTF8での不正位置を報告
		const int utf8_invalid_pos = n2_encoding_utf8_verify(scriptstr->str_, scriptstr->size_);
		int invalid_line_head = utf8_invalid_pos;
		while (invalid_line_head > 0) { --invalid_line_head; if (scriptstr->str_[invalid_line_head] == '\n') { ++invalid_line_head; break; } }
		n2i_raise_as(state, N2_ERROR_COMPILE, rootsourcecode, package, scriptstr->str_ + invalid_line_head, -1, "スクリプトは有効なUTF8文字列ではありません");
		goto fail_exit;
	}

	// 行ごとにばらす
	n2_sourcecode_split_script_lines(state, rootsourcecode);

	// プリプロセス
	ppc->current_sourcefiles_ = e->codeimage_->sourcefiles_;
	if (!n2_pp_context_preprocess_root(state, ppc, ppscriptstr, rootsourcecode)) { goto fail_exit; }

	// プリプロセスで定義されたモジュールをインポート
	for (size_t i = 0, l = n2_ppmoddeclareset_size(ppc->mod_decls_); i < l; ++i)
	{
		const n2_pp_module_declare_t* decl = n2_ppmoddeclareset_peek(ppc->mod_decls_, N2_SCAST(int, i));
		N2_ASSERT(decl && decl->name_);
		n2_moduletable_register(state, e->moduletable_, decl->name_);
	}

	// プリプロセスで定義された関数をインポート
	for (size_t i = 0, l = n2_ppfuncdeclareset_size(ppc->staging_func_decls_); i < l; ++i)
	{
		const n2_pp_func_declare_t* decl = n2_ppfuncdeclareset_peek(ppc->staging_func_decls_, N2_SCAST(int, i));
		N2_ASSERT(decl && decl->name_);
		n2_functable_register(state, e->functable_, decl->name_);
	}

	// ステージングをクリア
	n2_pp_context_clear_staging(state, ppc);

	// デバッグ用
	//n2i_printf(state, "PP:\n%s\n", ppscriptstr->str_);

	// プリプロセスされたものを行ごとにばらす
	n2_sourcecode_split_ppscript_lines(state, rootsourcecode);

	// パース
	p = n2_parser_alloc(state);
	n2_parser_rewind(state, p, rootsourcecode);

	staging_ast = n2_parser_parse(state, p);
	if (!staging_ast) { goto fail_exit; }

	// ここまできてて正しいならもう保存しておく
	{
		const n2_parser_t* pc = p;// to avoid warning...
		n2_parserarray_push(state, e->parsers_, &pc);
		p = NULL;
	}
	n2_astarray_pushv(state, e->asts_, staging_ast);
	n2_ast_node_t* load_ast = staging_ast;
	staging_ast = NULL;

	n2_sourcefilearray_register_sourcecode(state, e->codeimage_->sourcefiles_, rootsourcecode);
	n2_sourcecodearray_pushv(state, e->codeimage_->sourcecodes_, rootsourcecode);
	rootsourcecode = NULL;

	// コード生成
	if (!n2i_environment_generate(state, e, load_ast, usesourcecode)) { goto fail_exit; }

	return N2_TRUE;

fail_exit:
	e->load_error_ = N2_TRUE;
	if (rootsourcecode) { n2_sourcecode_free(state, rootsourcecode); }
	if (staging_ast) { n2_ast_node_free(state, staging_ast); }
	if (p) { n2_parser_free(state, p); }
	return N2_FALSE;
}

N2_API n2_debughook_t* n2_environment_get_debughook(n2_environment_t* e)
{
#if N2_CONFIG_USE_DEBUGGING
	return e->debughook_;
#else
	N2_UNUSE(e);
	return NULL;
#endif
}

N2_API n2_debughook_t* n2_environment_attach_debughook(n2_state_t* state, n2_environment_t* e)
{
#if N2_CONFIG_USE_DEBUGGING
	if (e->debughook_) { n2_environment_detach_debughook(state, e); }
	e->debughook_ = N2_TMALLOC(n2_debughook_t, state);
	n2i_debughook_init(e->debughook_, e);
	return e->debughook_;
#else
	N2_UNUSE(state);
	N2_UNUSE(e);
	return NULL;
#endif
}

N2_API n2_bool_t n2_environment_detach_debughook(n2_state_t* state, n2_environment_t* e)
{
#if N2_CONFIG_USE_DEBUGGING
	if (!e->debughook_) { return N2_FALSE; }
	n2_debughook_free(state, e->debughook_);
	e->debughook_ = NULL;
	return N2_TRUE;
#else
	N2_UNUSE(state);
	N2_UNUSE(e);
	return N2_FALSE;
#endif
}

N2_DECLARE_ENUM(n2i_codegen_shortblock_e);
enum n2i_codegen_shortblock_e
{
	N2I_CODEGEN_SHORTBLOCK_REPEAT,
	N2I_CODEGEN_SHORTBLOCK_SWITCH
};

typedef struct n2i_codegen_shortblock_t n2i_codegen_shortblock_t;
struct n2i_codegen_shortblock_t
{
	n2i_codegen_shortblock_e type_;
	n2_pc_t begin_pc_;
	n2_intarray_t* swcase_prologue_pcs_;
	n2_intarray_t* swcase_head_pcs_;
	int swdefault_pc_;
};

static void n2i_codegen_shortblock_init(n2i_codegen_shortblock_t* sblock)
{
	sblock->type_ = N2I_CODEGEN_SHORTBLOCK_REPEAT;
	sblock->begin_pc_ = 0;
	sblock->swcase_prologue_pcs_ = NULL;
	sblock->swcase_head_pcs_ = NULL;
	sblock->swdefault_pc_ = -1;
}
static void n2i_codegen_shortblock_teardown(n2_state_t* state, n2i_codegen_shortblock_t* sblock)
{
	if (sblock->swcase_prologue_pcs_) { n2_intarray_free(state, sblock->swcase_prologue_pcs_); }
	if (sblock->swcase_head_pcs_) { n2_intarray_free(state, sblock->swcase_head_pcs_); }
}

N2_DECLARE_TARRAY(n2i_codegen_shortblock_t, n2i_codegen_shortblockarray, static);

static void n2i_codegen_shortblockarray_freefunc(n2_state_t* state, n2_array_t* a, void* element)
{
	N2_UNUSE(a);
	n2i_codegen_shortblock_t* sblock = N2_RCAST(n2i_codegen_shortblock_t*, element);
	n2i_codegen_shortblock_teardown(state, sblock);
}
N2_DEFINE_TARRAY(n2i_codegen_shortblock_t, n2i_codegen_shortblockarray, static, n2i_setupfunc_nothing, n2i_codegen_shortblockarray_freefunc);

static n2i_codegen_shortblock_t* n2i_codegen_shortblock_find_last_typed(n2i_codegen_shortblockarray_t* shortblocks, n2i_codegen_shortblock_e type)
{
	for (size_t i = 0, l = n2i_codegen_shortblockarray_size(shortblocks); i < l; ++i)
	{
		n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblockarray_peek(shortblocks, -N2_SCAST(int, i) - 1);
		if (sblock->type_ == type) { return sblock; }
	}
	return NULL;
}

static size_t n2i_codegen_shortblock_pop_to_typed(n2_state_t* state, n2i_codegen_shortblockarray_t* shortblocks, n2i_codegen_shortblock_e type)
{
	size_t poped = 0;
	while (n2i_codegen_shortblockarray_size(shortblocks) > 0)
	{
		n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblockarray_peek(shortblocks, -1);
		const n2_bool_t found = sblock->type_ == type;
		n2i_codegen_shortblockarray_pop(state, shortblocks, 1);
		++poped;
		if (found) { break; }
	}
	return poped;
}

typedef struct n2i_codegen_context_t n2i_codegen_context_t;
struct n2i_codegen_context_t
{
	int stack_;
	const n2_sourcecode_t* sourcecode_;
	n2i_codegen_shortblockarray_t* shortblocks_;
	n2_bool_t generate_codelines_;
	n2_func_t* func_;
	n2_uselib_t* uselib_;
	n2_module_t* module_;
};

static void n2i_environment_generate_raise_token(n2_state_t* state, const n2_token_t* token, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	n2i_vraise_as(state, N2_ERROR_COMPILE, token ? token->sourcecode_ : NULL, token ? token->package_ : NULL, token ? token->appear_line_head_ : NULL, token ? token->appear_line_ : -1, fmt, args);
	va_end(args);
}

static void n2i_environment_generate_raise(n2_state_t* state, const n2_ast_node_t* node, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	n2i_vraise_as(state, N2_ERROR_COMPILE, node->token_ ? node->token_->sourcecode_ : NULL, node->token_ ? node->token_->package_ : NULL, node->token_ ? node->token_->appear_line_head_ : NULL, node->token_ ? node->token_->appear_line_ : -1, fmt, args);
	va_end(args);
}

static void n2i_environment_generate_register_codeline(n2_state_t* state, n2_environment_t* e, n2i_codegen_context_t* c, n2_pc_t pc, const n2_token_t* token)
{
	if (!e->codeimage_ || !e->codeimage_->codelinetable_) { return; }
	if (!c->generate_codelines_) { return; }
	if (!token) { return; }

	if (pc < 0) { pc = N2_SCAST(n2_pc_t, n2_opcodearray_size(e->codeimage_->opcodes_)); }

	// 同じものは書き換えない @todo 適当な処理なので後で真面目に考える、column追加した時とか
	const n2_codeline_t* ecodeline = n2i_codelinetable_find_from_pc(e->codeimage_->codelinetable_, pc);
	if (ecodeline && ecodeline->line_head_ == token->appear_line_head_) { return; }

	// 新しく追加
	n2_codeline_t codeline;
	codeline.pc_ = pc;
	codeline.sourcecode_ = token->sourcecode_;
	codeline.package_ = token->package_;
	codeline.line_head_ = token->appear_line_head_;
	codeline.line_ = token->appear_line_;
	codeline.column_ = -1;// @todo
	n2_codeline_t* inserted = n2_codelinetable_insert(state, e->codeimage_->codelinetable_, &codeline, NULL);
	const int inserted_index = n2_codelinetable_compute_index(e->codeimage_->codelinetable_, inserted);

	if (inserted->sourcecode_ && inserted_index >= 0)
	{
		n2_szarray_pushv(state, &N2_CCAST(n2_sourcecode_t*, inserted->sourcecode_)->codeline_indices_, N2_SCAST(size_t, inserted_index));
	}
}

static void n2i_environment_generate_sync_opcodeflags(n2_state_t* state, n2_environment_t* e, n2i_codegen_context_t* c, size_t opcode_cursor)
{
	N2_UNUSE(c);
	n2_codeimage_t* codeimage = e->codeimage_;
	n2_u8array_t* opcodeflags = codeimage->opcodeflags_;
	if (!opcodeflags) { return; }
	const size_t size = n2_u8array_size(opcodeflags);
	if (opcode_cursor < size) { return; }
	const uint8_t zero = 0;
	n2_u8array_reserve(state, opcodeflags, opcode_cursor + 1);
	n2_u8array_resize(state, opcodeflags, opcode_cursor + 1, &zero);
}

static void n2i_environment_generate_set_opcodeflag(n2_state_t* state, n2_environment_t* e, n2i_codegen_context_t* c, size_t opcode_cursor, uint8_t flags)
{
	n2_codeimage_t* codeimage = e->codeimage_;
	n2_u8array_t* opcodeflags = codeimage->opcodeflags_;
	if (!opcodeflags) { return; }
	n2i_environment_generate_sync_opcodeflags(state, e, c, opcode_cursor);
	*n2_u8array_peek(opcodeflags, N2_SCAST(int ,opcode_cursor)) = flags;
}

static void n2i_environment_generate_add_opcodeflag(n2_state_t* state, n2_environment_t* e, n2i_codegen_context_t* c, size_t opcode_cursor, uint8_t flags)
{
	n2_codeimage_t* codeimage = e->codeimage_;
	n2_u8array_t* opcodeflags = codeimage->opcodeflags_;
	if (!opcodeflags) { return; }
	n2i_environment_generate_sync_opcodeflags(state, e, c, opcode_cursor);
	*n2_u8array_peek(opcodeflags, N2_SCAST(int ,opcode_cursor)) |= flags;
}

static void n2i_environment_generate_erase_opcodeflag(n2_state_t* state, n2_environment_t* e, n2i_codegen_context_t* c, size_t opcode_cursor, uint8_t flags)
{
	n2_codeimage_t* codeimage = e->codeimage_;
	n2_u8array_t* opcodeflags = codeimage->opcodeflags_;
	if (!opcodeflags) { return; }
	n2i_environment_generate_sync_opcodeflags(state, e, c, opcode_cursor);
	*n2_u8array_peek(opcodeflags, N2_SCAST(int ,opcode_cursor)) &= ~flags;
}

static int n2i_environment_find_sysvar(const n2_environment_t* e, const char* name, n2_bool_t* dst_is_ex)
{
	const int exindex = n2_sysvarexarray_find(e->sysvar_ex_, n2i_sysvarexarray_matchfunc, name);
	if (exindex >= 0) { *dst_is_ex = N2_TRUE; return exindex; }
	*dst_is_ex = N2_FALSE;
	return n2_sysvar_find(name);
}

static int n2i_environment_register_label(n2_state_t* state, n2_environment_t* e, const char* name)
{
	int index = n2_labelarray_find(e->labels_, n2i_labelarray_matchfunc, name);
	if (index < 0)
	{
		index = N2_SCAST(int, n2_labelarray_size(e->labels_));
		n2_label_t* label = n2_labelarray_push(state, e->labels_, NULL);
		label->name_ = n2_plstr_clone(state, name);
		label->pc_ = -1;
	}
	return index;
}

static n2_bool_t n2i_environment_generate_walk(n2_state_t* state, n2_environment_t* e, n2_ast_node_t* n, n2i_codegen_context_t* c)
{
	n2_opcodearray_t* opcodes = e->codeimage_->opcodes_;
	const size_t node_opcode_cursor = n2_opcodearray_size(opcodes);

	n2i_environment_generate_register_codeline(state, e, c, -1, n->token_);

	N2_ASSERT(c->stack_ >= 0);

	switch (n->node_)
	{
	case N2_AST_NODE_EMPTY:
		break;

	case N2_AST_NODE_LINE:
		if (n->left_ && !n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		n2i_environment_generate_add_opcodeflag(state, e, c, node_opcode_cursor, N2_OPCODEFLAG_LINE_STATEMENTS_HEAD);
		break;

	case N2_AST_NODE_STATEMENT:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		n2i_environment_generate_add_opcodeflag(state, e, c, node_opcode_cursor, N2_OPCODEFLAG_STATEMENT_HEAD);
		break;

	case N2_AST_NODE_MODULE:
		{
			if (c->module_)
			{
				n2i_environment_generate_raise(state, n, "#module の始まりで前のモジュール（%s）定義が終わっていません", c->module_->name_);
				return N2_FALSE;
			}

			N2_ASSERT(n->token_);
			N2_ASSERT(n->token_->token_ == N2_TOKEN_IDENTIFIER);
			const char* modulename = n->token_->content_;

			n2_module_t* emodule = n2_moduletable_find(e->moduletable_, modulename);
			if (!emodule)
			{
				n2i_environment_generate_raise(state, n, "モジュール（%s）が宣言されていません、プリプロセスに失敗しています ※#moduleは行頭にくる必要があります", modulename);
				return N2_FALSE;
			}

			const int modindex = n2_modulearray_compute_index(e->moduletable_->modulearray_, emodule);
			N2_ASSERT(modindex >= 0);

			// 宣言
			emodule->pc_begin_ = N2_SCAST(n2_pc_t, n2_opcodearray_size(opcodes));
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_MODULE);
			n2_opcodearray_pushv(state, opcodes, modindex);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy

			c->module_ = emodule;

			if (n->left_) { if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; } }
		}
		break;
	case N2_AST_NODE_MODULE_LOCALVAR:
		{
			N2_ASSERT(c->module_);
			n2_module_t* emodule = c->module_;

			N2_ASSERT(n->token_);
			N2_ASSERT(n->token_->token_ == N2_TOKEN_IDENTIFIER);
			const char* varname = n->token_->content_;

			if (n2_modlocalvararray_find(emodule->modlocalvars_, n2i_modvararray_matchfunc, varname) >= 0)
			{
				n2i_environment_generate_raise(state, n, "#module のモジュール（%s）で同名のモジュールローカル変数（%s）が宣言されました", emodule->name_, varname);
				return N2_FALSE;
			}

			n2_modlocalvar_t* modvar = n2_modlocalvararray_push(state, emodule->modlocalvars_, NULL);
			modvar->name_ = n2_plstr_clone(state, varname);
		}
		break;
	case N2_AST_NODE_GLOBAL:
		{
			if (!c->module_)
			{
				n2i_environment_generate_raise(state, n, "#module で始まってない #globalです");
				return N2_FALSE;
			}

			const int modindex = n2_modulearray_compute_index(e->moduletable_->modulearray_, c->module_);
			N2_ASSERT(modindex >= 0);

			// 本終了コード
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_GLOBAL);
			n2_opcodearray_pushv(state, opcodes, modindex);

			// 開始からのジャンプ
			const n2_pc_t pc_end = N2_SCAST(n2_pc_t, n2_opcodearray_size(opcodes));
			*n2_opcodearray_peek(opcodes, c->module_->pc_begin_ + 2) = N2_SCAST(n2_opcode_t, pc_end - c->module_->pc_begin_);

			// モジュールも関数も終了
			c->module_ = NULL;
			c->func_ = NULL;
		}
		break;

	case N2_AST_NODE_USELIB:
		{
			const n2_token_t* path = n->token_;
			N2_ASSERT(path && path->token_ == N2_TOKEN_STRING);

			n2_uselib_t* uselib = n2_uselibarray_push(state, e->uselibs_, NULL);
			n2i_uselib_setup(state, uselib, path->content_);

			e->uselibs_dirty_ = N2_TRUE;

			c->uselib_ = uselib;
		}
		break;

	case N2_AST_NODE_DEFFUNC:
	case N2_AST_NODE_DEFCFUNC:
	case N2_AST_NODE_MODINIT:
	case N2_AST_NODE_MODTERM:
	case N2_AST_NODE_MODFUNC:
	case N2_AST_NODE_MODCFUNC:
	case N2_AST_NODE_FUNC:
	case N2_AST_NODE_CFUNC:
		{
			n2_bool_t is_modfunc = N2_FALSE;
			n2_bool_t is_dlfunc = N2_FALSE;
			n2_bool_t is_noname = N2_FALSE;
			n2_bool_t is_noparam = N2_FALSE;

			switch (n->node_)
			{
			case N2_AST_NODE_DEFFUNC:
				break;
			case N2_AST_NODE_DEFCFUNC:
				break;
			case N2_AST_NODE_MODINIT:
				is_modfunc = N2_TRUE;
				is_noname = N2_TRUE;
				break;
			case N2_AST_NODE_MODTERM:
				is_modfunc = N2_TRUE;
				is_noname = N2_TRUE;
				is_noparam = N2_TRUE;
				break;
			case N2_AST_NODE_MODFUNC:
				is_modfunc = N2_TRUE;
				break;
			case N2_AST_NODE_MODCFUNC:
				is_modfunc = N2_TRUE;
				break;
			case N2_AST_NODE_FUNC:
				is_dlfunc = N2_TRUE;
				break;
			case N2_AST_NODE_CFUNC:
				is_dlfunc = N2_TRUE;
				break;
			default:
				N2_ASSERT(0);
				return N2_FALSE;
			}

			// モジュール変数なら場所チェック
			if (is_modfunc)
			{
				if (!c->module_)
				{
					n2i_environment_generate_raise(state, n, "モジュール関数宣言が #module-#global で囲まれていません");
					return N2_FALSE;
				}
			}

			// 動的ライブラリならuselibチェック
			if (is_dlfunc)
			{
				if (!c->uselib_)
				{
					n2i_environment_generate_raise(state, n, "ライブラリ関数宣言が #uselib 前に使われています");
					return N2_FALSE;
				}
			}

			const char* func_name = NULL;
			const char* lib_proc_name = NULL;

			const n2_ast_node_t* curn = n;

			// 名前
			if (is_noname)
			{
				// 名前なしは自動
				switch (n->node_)
				{
				case N2_AST_NODE_MODINIT:	func_name = "#_modinit"; break;
				case N2_AST_NODE_MODTERM:	func_name = "#_modterm"; break;
				default:					N2_ASSERT(0); return N2_FALSE;
				}
			}
			else
			{
				N2_ASSERT(n->token_);
				N2_ASSERT(n->token_->token_ == N2_TOKEN_IDENTIFIER);
				func_name = n->token_->content_;
			}

			// 動的ライブラリ
			if (is_dlfunc)
			{
				if (curn->right_)
				{
					N2_ASSERT(curn->right_->node_ == N2_AST_NODE_DEFFUNC_PARTS);
					N2_ASSERT(curn->right_->token_);
					lib_proc_name = curn->right_->token_->content_;
					curn = curn->right_;
				}
				if (!lib_proc_name)
				{
					n2i_environment_generate_raise(state, n, "ライブラリ関数名の取得に失敗：内部エラー");
					return N2_FALSE;
				}
			}

			// local - global
			n2_bool_t is_global = N2_TRUE;
			if (curn->right_)
			{
				N2_ASSERT(curn->right_->node_ == N2_AST_NODE_DEFFUNC_PARTS);
				N2_ASSERT(curn->right_->token_);
				const n2_token_t* lgt = curn->right_->token_;
				if (n2i_token_is_keyword(lgt, N2_KEYWORD_LOCAL)) { is_global = N2_FALSE; }
				curn = curn->right_;
			}
			if (is_noname)
			{
				is_global = N2_FALSE;
			}

			n2_str_t func_fullname;
			n2_str_init(&func_fullname);
			n2_naming_compute(state, func_name, SIZE_MAX, c->module_ ? c->module_->name_ : NULL, NULL, &func_fullname, NULL);

			if (is_noname)
			{
				n2_functable_register(state, e->functable_, func_fullname.str_);
			}

			n2_func_t* func = n2_functable_find(e->functable_, func_fullname.str_);
			if (!func)
			{
				n2i_environment_generate_raise(state, n, "関数（%s：フル名＝%s）が宣言されていません、プリプロセスに失敗しています ※#deffunc/#defcfuncは行頭にくる必要があります", func_name, func_fullname.str_);
				n2_str_teardown(state, &func_fullname);
				return N2_FALSE;
			}

			if (func->func_ != N2_FUNC_UNKNOWN)
			{
				n2i_environment_generate_raise(state, n, "関数（%s：フル名＝%s）を定義しようとしましたが既に別の箇所で定義されています", func_name, func_fullname.str_);
				n2_str_teardown(state, &func_fullname);
				return N2_FALSE;
			}

			const int funcindex = n2_funcarray_compute_index(e->functable_->funcarray_, func);
			N2_ASSERT(funcindex >= 0);

			// モジュール関数なら関連づける
			if (is_modfunc)
			{
				N2_ASSERT(c->module_);
				func->module_id_ = c->module_->module_id_;

				switch (n->node_)
				{
				case N2_AST_NODE_MODINIT:
					if (c->module_->modinit_funcindex_ >= 0)
					{
						n2i_environment_generate_raise(state, n, "モジュール（%s）の #modinit を再定義しようとしました", c->module_->name_);
						return N2_FALSE;
					}
					c->module_->modinit_funcindex_ = funcindex;
					break;
				case N2_AST_NODE_MODTERM:
					if (c->module_->modterm_funcindex_ >= 0)
					{
						n2i_environment_generate_raise(state, n, "モジュール（%s）の #modterm を再定義しようとしました", c->module_->name_);
						return N2_FALSE;
					}
					c->module_->modterm_funcindex_ = funcindex;
					break;
				default:
					break;
				}

				n2_modfuncindexset_insertv(state, c->module_->modfuncs_, funcindex, NULL);
				n2_modfuncindexset_insertv(state, c->module_->modfuncsnames_, funcindex, NULL);
			}

			// エイリアス
			if (is_global)
			{
				n2_str_t func_globalname;
				n2_str_init(&func_globalname);
				n2_naming_replace_modulename(state, func_fullname.str_, SIZE_MAX, n2i_modulename_default, &func_globalname);
				if (N2_STRCMP(func_fullname.str_, func_globalname.str_))
				{
					n2_func_t* func_global = n2_functable_find(e->functable_, func_globalname.str_);
					if (func_global && (func_global->flags_ & N2_FUNCFLAG_DEFINED))
					{
						n2i_environment_generate_raise(state, n, "関数（%s：フル名＝%s）の定義中、グローバル空間に関数エイリアス（%s）も定義しようとしましたが既に別の箇所で定義されています", func_name, func_fullname.str_, func_globalname.str_);
						n2_str_teardown(state, &func_fullname);
						n2_str_teardown(state, &func_globalname);
						return N2_FALSE;
					}

					const int func_global_index = n2_functable_register(state, e->functable_, func_globalname.str_);
					N2_ASSERT(func_global_index >= 0);
					func_global = n2_functable_peek(e->functable_, func_global_index);
					N2_ASSERT(func_global);
					n2i_func_setas_alias(state, func_global, func);
				}
				n2_str_teardown(state, &func_globalname);
			}
			n2_str_teardown(state, &func_fullname);

			// パラメータ準備
			N2_ASSERT(!func->params_);
			func->params_ = n2_funcparamarray_alloc(state, 0, 4);

			// 動的ライブラリ
			if (is_dlfunc)
			{
				// func情報を埋める
				func->func_ = N2_FUNC_DLFUNC;
				func->flags_ |= N2_FUNCFLAG_DEFINED;

				// ライブラリの関数名を保存
				n2_str_set(state, &func->libprocname_, lib_proc_name, SIZE_MAX);

				// uselibのテーブルへ追加
				n2_intarray_pushv(state, &c->uselib_->func_indices_, funcindex);
			}
			else
			{
				// モジュール変数なら勝手に入れる
				if (is_modfunc)
				{
					n2_func_param_t* param = n2_funcparamarray_push(state, func->params_, NULL);
					param->name_ = n2_plstr_clone(state, "thismod");
					param->type_ = N2_FUNC_PARAM_MODVAR;
					param->omittable_ = N2_FALSE;
				}

				// 関数ガード
				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_DEFFUNC);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, funcindex));

				// ここのPCを記録
				func->func_ = N2_FUNC_SCRIPT;
				func->flags_ |= N2_FUNCFLAG_DEFINED;
				func->pc_ = N2_SCAST(n2_pc_t, n2_opcodearray_size(e->codeimage_->opcodes_));

				// 実際の関数処理はここから
				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ENTER_FUNCTION);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, funcindex));
			}

			c->func_ = func;// 現在のスコープをこの関数に切り替え

			// 各パラメータの処理に移る
			if (n->left_)
			{
				if (is_noparam)
				{
					n2i_environment_generate_raise(state, n, "関数はパラメータを受け取れないため、パラメータ定義もできません");
					return N2_FALSE;
				}
				if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
			}
		}
		break;

	case N2_AST_NODE_DECLARE_PARAM:
		{
			n2_func_t* func = c->func_;
			N2_ASSERT(func);
			N2_ASSERT(func->params_);

			const n2_bool_t is_dlfunc = func->func_ == N2_FUNC_DLFUNC;

			const n2_ast_node_t* prop = n->left_;
			N2_ASSERT(prop);
			N2_ASSERT(prop->left_ && prop->right_);

			const n2_ast_node_t* typedefval = prop->left_;
			N2_ASSERT(typedefval && typedefval->token_ && typedefval->token_->token_ == N2_TOKEN_IDENTIFIER);
			const n2_ast_node_t* ident = prop->right_;
			N2_ASSERT(ident);
			N2_ASSERT(!ident->token_ || ident->token_->token_ == N2_TOKEN_IDENTIFIER);

			const n2_func_param_e paramtype = n2_func_param_from_token(typedefval->token_, is_dlfunc);
			N2_ASSERT(paramtype != N2_FUNC_PARAM_UNKNOWN);
			n2_func_param_t* param = n2_funcparamarray_push(state, func->params_, NULL);
			const int paramindex = n2_funcparamarray_compute_index(func->params_, param);
			param->name_ = ident->token_ ? n2_plstr_clone(state, ident->token_->content_) : NULL;
			param->type_ = paramtype;
			param->omittable_ = (paramtype == N2_FUNC_PARAM_LOCAL || typedefval->left_);// 省略できる基本条件
			if (paramtype == N2_FUNC_PARAM_VAR || paramtype == N2_FUNC_PARAM_ARRAY) { param->omittable_ = N2_FALSE; }// 一部の省略できない型

			// スクリプト関数なら引数処理を書いていく
			if (func->func_ == N2_FUNC_SCRIPT)
			{
				// デフォルト値
				if (param->omittable_ && typedefval->left_)
				{
					const int prev_stack_top = c->stack_;
					const n2_bool_t local_variable = paramtype == N2_FUNC_PARAM_LOCAL;// この場合はデフォルト値を強制的に入れる

					size_t pos_root = SIZE_MAX;
					// 分岐
					if (local_variable)
					{
						// オリジナル引数の数
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_TEST_ORIGINAL_ARG_NUM);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
						++c->stack_;
					}
					else
					{
						// スタック値のnilチェック
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
						++c->stack_;
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_TEST_NIL);
					}
					// 分岐点
					pos_root = n2_opcodearray_size(opcodes);
					n2_opcodearray_pushv(state, opcodes, local_variable ? N2_OPCODE_IFNOT : N2_OPCODE_IF);// @todo ここの分岐OPをそろえてもいいかも、TEST_ORIGINAL_ARG_NUMを修正？
					n2_opcodearray_pushv(state, opcodes, 0);// dummy
					--c->stack_;
					// デフォルト値を入れる
					if (local_variable)
					{
						// 変数代入のための仕込み
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
						++c->stack_;
					}
					// 値を取得
					if (!n2i_environment_generate_walk(state, e, typedefval->left_, c)) { return N2_FALSE; }
					// 代入
					if (local_variable)
					{
						// 変数へ保存
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ASSIGN);
						c->stack_ -= 2;
					}
					else
					{
						// スタックへ保存
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_STORE_STACK);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
						--c->stack_;
					}
					// ifの辻褄合わせ
					if (pos_root != SIZE_MAX)
					{
						const size_t pos_tail = n2_opcodearray_size(opcodes);
						*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_root + 1)) = N2_SCAST(n2_opcode_t, pos_tail - pos_root);
					}
					// スタックチェック
					N2_ASSERT(c->stack_ == prev_stack_top);
					N2_UNUSE(prev_stack_top);
				}
			}

			// 次のパラメータへリレー
			if (n->right_) { if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; } }
		}
		break;

	case N2_AST_NODE_LABEL:
		{
			const char* label_name = n->token_->content_;
			const int label_index = n2i_environment_register_label(state, e, label_name);
			N2_ASSERT(label_index >= 0);
			n2_label_t* label = n2_labelarray_peek(e->labels_, label_index);
			if (label->pc_ >= 0)
			{
				n2i_environment_generate_raise(state, n, "ラベル（*%s）を定義しようとしましたが既に別の箇所で定義されています", label_name);
				return N2_FALSE;
			}
			label->pc_ = N2_SCAST(n2_pc_t, n2_opcodearray_size(opcodes));
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_LABEL);
			n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, label_index));
		}
		break;

	case N2_AST_NODE_BLOCK_STATEMENTS:
		{
			n2_ast_node_t* ncur = n;
			while (ncur)
			{
				if (ncur->left_) { if (!n2i_environment_generate_walk(state, e, ncur->left_, c)) { return N2_FALSE; } }
				ncur = ncur->right_;// 末尾再起
			}
		}
		break;

	case N2_AST_NODE_COMMAND:
		{
			const int top = c->stack_;
			if (n->left_) { if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; } }
			const int arg_num = c->stack_ - top;
			N2_ASSERT(arg_num >= 0);

			N2_ASSERT(n->token_->token_ == N2_TOKEN_IDENTIFIER || n->token_->token_ == N2_TOKEN_IDENTIFIER_FQ);
			const char* command_name = n->token_->content_;

			n2_str_t fullname, fullname_global;
			n2_str_init(&fullname); n2_str_init(&fullname_global);
			n2_naming_compute(state, command_name, SIZE_MAX, c->module_ ? c->module_->name_ : NULL, NULL, &fullname, NULL);
			n2_naming_replace_modulename(state, fullname.str_, SIZE_MAX, n2i_modulename_default, &fullname_global);

			n2_func_t* func = n2_functable_find(e->functable_, fullname.str_);
			if (!func && n->token_->token_ != N2_TOKEN_IDENTIFIER_FQ)
			{
				func = n2_functable_find(e->functable_, fullname_global.str_);
			}
			if (!func)
			{
				n2i_environment_generate_raise(state, n, "コマンドが見つかりません：%s（フル名=%s、グローバル名=%s）", command_name, fullname.str_, fullname_global.str_);
				n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
				return N2_FALSE;
			}
			const int funcindex = n2_funcarray_compute_index(e->functable_->funcarray_, func);

			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_COMMAND);
			n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, funcindex));
			n2_opcodearray_pushv(state, opcodes, (arg_num & 0xffff) | N2_SCAST(n2_opcode_t, (n->exflags_ & 0xffff) << 16));

			n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
			c->stack_ = top;
		}
		break;

	case N2_AST_NODE_ARGUMENTS:
	case N2_AST_NODE_ARGUMENTS_PARTS:
		if (n->left_) { if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; } }
		if (n->right_) { if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; } }
		break;
	case N2_AST_NODE_ARGUMENTS_EMPTY_ARG:
		// nilを入れる
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_NIL);
		++c->stack_;
		break;

	case N2_AST_NODE_LOR_ASSIGN:
	case N2_AST_NODE_LAND_ASSIGN:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			const n2_bool_t is_lor = n->node_ == N2_AST_NODE_LOR_ASSIGN;

			// 特殊な動作（短絡評価）
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK_REL);
			n2_opcodearray_pushv(state, opcodes, -1);
			++c->stack_;

			const size_t pos_root = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, is_lor ? N2_OPCODE_IFNOT : N2_OPCODE_IF);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy FALSE
			--c->stack_;

			// 代入処理
			N2_ASSERT(n->right_);
			if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; }
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ASSIGN);
			const size_t pos_true_tail = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_JUMP_RELATIVE);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL
			--c->stack_;

			// 何もしないのでpop
			const size_t pos_false_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_POP);
			n2_opcodearray_pushv(state, opcodes, 1);
			--c->stack_;

			// マージ
			const size_t pos_tail = n2_opcodearray_size(opcodes);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_root + 1)) = N2_SCAST(n2_opcode_t, pos_false_head - pos_root);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_true_tail + 1)) = N2_SCAST(n2_opcode_t, pos_tail - pos_true_tail);
		}
		break;

	case N2_AST_NODE_ASSIGN:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
			N2_ASSERT(n->right_);
			const int top = c->stack_;
			if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; }
			const int arg_num = c->stack_ - top;
			if (arg_num > 1)
			{
				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ASSIGN_BULK);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, arg_num));
			}
			else if (arg_num == 1)
			{
				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ASSIGN);
			}
			else
			{
				// 0以下
				n2i_environment_generate_raise(state, n, "変数へ代入する値がありません");
				return N2_FALSE;
			}
			c->stack_ -= arg_num + 1; 
		}
		break;
	case N2_AST_NODE_BOR_ASSIGN:
	case N2_AST_NODE_BAND_ASSIGN:
	case N2_AST_NODE_BXOR_ASSIGN:
	case N2_AST_NODE_BLSHIFT_ASSIGN:
	case N2_AST_NODE_BRSHIFT_ASSIGN:
	case N2_AST_NODE_ADD_ASSIGN:
	case N2_AST_NODE_SUB_ASSIGN:
	case N2_AST_NODE_MUL_ASSIGN:
	case N2_AST_NODE_DIV_ASSIGN:
	case N2_AST_NODE_MOD_ASSIGN:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		N2_ASSERT(n->right_);
		if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; }
		switch (n->node_)
		{
		case N2_AST_NODE_BOR_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BOR_ASSIGN); break;
		case N2_AST_NODE_BAND_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BAND_ASSIGN); break;
		case N2_AST_NODE_BXOR_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BXOR_ASSIGN); break;
		case N2_AST_NODE_BLSHIFT_ASSIGN:	n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BRSHIFT_ASSIGN); break;
		case N2_AST_NODE_BRSHIFT_ASSIGN:	n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BLSHIFT_ASSIGN); break;
		case N2_AST_NODE_ADD_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ADD_ASSIGN); break;
		case N2_AST_NODE_SUB_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SUB_ASSIGN); break;
		case N2_AST_NODE_MUL_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_MUL_ASSIGN); break;
		case N2_AST_NODE_DIV_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_DIV_ASSIGN); break;
		case N2_AST_NODE_MOD_ASSIGN:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_MOD_ASSIGN); break;
		default:							N2_ASSERT(0); break;
		}
		c->stack_ -= 2; 
		break;

	case N2_AST_NODE_INCREMENT:
	case N2_AST_NODE_DECREMENT:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		switch (n->node_)
		{
		case N2_AST_NODE_INCREMENT:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_INCREMENT); break;
		case N2_AST_NODE_DECREMENT:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_DECREMENT); break;
		default:						N2_ASSERT(0); break;
		}
		c->stack_ -= 1;
		break;

	case N2_AST_NODE_VARIABLE:
		{
			const int top = c->stack_;
			if (n->left_) { if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; } }
			const int arg_num = c->stack_ - top;

			const char* ident = n->token_->content_;

			n2_str_t fullname, fullname_global;
			n2_str_init(&fullname); n2_str_init(&fullname_global);
			n2_naming_compute(state, ident, SIZE_MAX, c->module_ ? c->module_->name_ : NULL, NULL, &fullname, NULL);
			n2_naming_replace_modulename(state, fullname.str_, SIZE_MAX, n2i_modulename_default, &fullname_global);

			n2_bool_t accepted = N2_FALSE;

			// ローカル変数
			if (!accepted)
			{
				const int paramindex = (c->func_ && c->func_->params_ ? n2_funcparamarray_find(c->func_->params_, n2i_funcparamarray_matchfunc, ident) : -1);
				if (paramindex >= 0)
				{
					const n2_func_param_t* param = n2_funcparamarray_peek(c->func_->params_, paramindex);
					N2_ASSERT(param);
					if (arg_num > 0 && param->type_ != N2_FUNC_PARAM_LOCAL && param->type_ != N2_FUNC_PARAM_ARRAY)
					{
						n2i_environment_generate_raise(state, n, "関数の引数（%s）は次元を持たない値のため括弧によるアクセスはできません", ident);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}
					if (arg_num > N2_VARIABLE_DIM)
					{
						n2i_environment_generate_raise(state, n, "ローカル変数（%s）の添え字は%d次元までです", ident, N2_VARIABLE_DIM);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
					accepted = N2_TRUE;
				}
			}

			// モジュールローカル変数
			if (!accepted)
			{
				if (c->module_)
				{
					const int modvarindex = n2_modlocalvararray_find(c->module_->modlocalvars_, n2i_modvararray_matchfunc, ident);
					if (modvarindex >= 0)
					{
						if (arg_num > N2_VARIABLE_DIM)
						{
							n2i_environment_generate_raise(state, n, "モジュールローカル変数（%s）の添え字は%d次元までです", ident, N2_VARIABLE_DIM);
							n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
							return N2_FALSE;
						}
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_MODULE_LOCALVAR);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, modvarindex));
						accepted = N2_TRUE;
					}
				}
			}

			// モジュール
			if (!accepted)
			{
				n2_module_t* emodule = n2_moduletable_find(e->moduletable_, ident);
				if (emodule)
				{
					if (arg_num > 0)
					{
						n2i_environment_generate_raise(state, n, "モジュール（%s）は次元を持たない値のため括弧によるアクセスはできません", ident);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}

					const int modindex = n2_modulearray_compute_index(e->moduletable_->modulearray_, emodule);
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_MODULE);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, modindex));
					accepted = N2_TRUE;
				}
			}

			// グローバル変数
			if (!accepted)
			{
				if (arg_num > N2_VARIABLE_DIM)
				{
					n2i_environment_generate_raise(state, n, "配列変数（%s）の添え字は%d次元までです", N2_VARIABLE_DIM, fullname.str_);
					n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
					return N2_FALSE;
				}

				const int varindex = n2_vartable_register(state, e, e->vartable_, fullname.str_);
				N2_ASSERT(varindex >= 0);

				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_VARIABLE);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, varindex));
				if (arg_num > 0)
				{
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SET_VARIABLE_APTR);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, arg_num));
				}
				accepted = N2_TRUE;
			}
			n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
			c->stack_ = top + 1;
		}
		break;

	case N2_AST_NODE_EXPRESSION:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		break;

	case N2_AST_NODE_CONDITIONAL:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			N2_ASSERT(n->right_ && n->right_->node_ == N2_AST_NODE_CONDITIONAL_PARTS);
			N2_ASSERT(n->right_->left_ && n->right_->right_);

			// 特殊な動作（短絡評価）
			const size_t pos_root = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_IF);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy FALSE
			--c->stack_;

			// 左項を使う
			if (!n2i_environment_generate_walk(state, e, n->right_->left_, c)) { return N2_FALSE; }
			--c->stack_;// 辻褄合わせでこのタイミング

			const size_t pos_mid = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_JUMP_RELATIVE);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy FALSE

			// 右項を使う
			if (!n2i_environment_generate_walk(state, e, n->right_->right_, c)) { return N2_FALSE; }

			// マージ
			const size_t pos_tail = n2_opcodearray_size(opcodes);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_root + 1)) = N2_SCAST(n2_opcode_t, pos_mid + 2 - pos_root);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_mid + 1)) = N2_SCAST(n2_opcode_t, pos_tail - pos_mid);
		}
		break;

	case N2_AST_NODE_LOR:
	case N2_AST_NODE_LAND:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			const n2_bool_t is_lor = n->node_ == N2_AST_NODE_LOR;

			// 特殊な動作（短絡評価）
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK_REL);
			n2_opcodearray_pushv(state, opcodes, -1);
			++c->stack_;

			const size_t pos_root = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, is_lor ? N2_OPCODE_IFNOT : N2_OPCODE_IF);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy FALSE
			--c->stack_;

			// 右項を使う
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_POP);
			n2_opcodearray_pushv(state, opcodes, 1);

			N2_ASSERT(n->right_);
			if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; }

			--c->stack_;// 辻褄合わせでこのタイミング

			// マージ
			const size_t pos_tail = n2_opcodearray_size(opcodes);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_root + 1)) = N2_SCAST(n2_opcode_t, pos_tail - pos_root);
		}
		break;

	case N2_AST_NODE_BOR:
	case N2_AST_NODE_BAND:
	case N2_AST_NODE_BXOR:
	case N2_AST_NODE_EQ:
	case N2_AST_NODE_NEQ:
	case N2_AST_NODE_GT:
	case N2_AST_NODE_GTOE:
	case N2_AST_NODE_LT:
	case N2_AST_NODE_LTOE:
	case N2_AST_NODE_BLSHIFT:
	case N2_AST_NODE_BRSHIFT:
	case N2_AST_NODE_ADD:
	case N2_AST_NODE_SUB:
	case N2_AST_NODE_MUL:
	case N2_AST_NODE_DIV:
	case N2_AST_NODE_MOD:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		N2_ASSERT(n->right_);
		if (!n2i_environment_generate_walk(state, e, n->right_, c)) { return N2_FALSE; }
		switch (n->node_)
		{
		case N2_AST_NODE_BOR:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BOR); break;
		case N2_AST_NODE_BAND:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BAND); break;
		case N2_AST_NODE_BXOR:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BXOR); break;
		case N2_AST_NODE_EQ:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_EQ); break;
		case N2_AST_NODE_NEQ:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_NEQ); break;
		case N2_AST_NODE_GT:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_GT); break;
		case N2_AST_NODE_GTOE:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_GTOE); break;
		case N2_AST_NODE_LT:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_LT); break;
		case N2_AST_NODE_LTOE:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_LTOE); break;
		case N2_AST_NODE_BLSHIFT:	n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BLSHIFT); break;
		case N2_AST_NODE_BRSHIFT:	n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BRSHIFT); break;
		case N2_AST_NODE_ADD:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_ADD); break;
		case N2_AST_NODE_SUB:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SUB); break;
		case N2_AST_NODE_MUL:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_MUL); break;
		case N2_AST_NODE_DIV:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_DIV); break;
		case N2_AST_NODE_MOD:		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_MOD); break;
		default:					N2_ASSERT(0); break;
		}
		--c->stack_;
		break;

	case N2_AST_NODE_UNARY_NOT:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_UNARY_NOT);
		break;

	case N2_AST_NODE_UNARY_MINUS:
		N2_ASSERT(n->left_);
		if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_UNARY_MINUS);
		break;

	case N2_AST_NODE_LABEL_VALUE:
		{
			const char* label_name = n->token_->content_;
			const int label_index = n2i_environment_register_label(state, e, label_name);
			N2_ASSERT(label_index >= 0);

			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_LABEL);
			n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, label_index));
			++c->stack_;
		}
		break;
	case N2_AST_NODE_PRIMITIVE_VALUE:
		switch (n->token_->token_)
		{
		case N2_TOKEN_NIL:
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_NIL);
			break;
		case N2_TOKEN_INT:
			{
				const n2_valint_t vali = N2_SCAST(n2_valint_t, N2_STRTOLL(n->token_->content_, NULL, 0));
				n2i_opcode_put_pushintop(state, e->codeimage_, opcodes, vali);
			}
			break;
		case N2_TOKEN_HEXINT:
			{
				const char* chex = n->token_->content_;
				if (chex[0] == '$') { ++chex; } else if (chex[0] == '0' && (chex[1] == 'x' || chex[1] == 'X')) { chex += 2; }
				const n2_valint_t vali = N2_SCAST(n2_valint_t, N2_STRTOLL(chex, NULL, 16));
				n2i_opcode_put_pushintop(state, e->codeimage_, opcodes, vali);
			}
			break;
		case N2_TOKEN_FLOAT:
			{
				const n2_valfloat_t valf = N2_SCAST(n2_valfloat_t, N2_STRTOD(n->token_->content_, NULL));
				n2i_opcode_put_pushfloatop(state, e->codeimage_, opcodes, valf);
			}
			break;
		case N2_TOKEN_STRING:
			{
				int strindex = n2_plstrarray_find(e->codeimage_->str_literals_, n2i_plstarray_matchfunc, n->token_->content_);
				if (strindex < 0)
				{
					strindex = N2_SCAST(int, n2_plstrarray_size(e->codeimage_->str_literals_));
					char* str = n2_plstr_clone(state, n->token_->content_);
					n2_plstrarray_pushv(state, e->codeimage_->str_literals_, str);
				}
				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STRING);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, strindex));
			}
			break;
		case N2_TOKEN_CHAR:
			{
				n2_codepoint_t codepoint = 0;
				n2_encoding_utf8_fetch(n->token_->content_, &codepoint);
				const n2_valint_t vali = N2_SCAST(n2_valint_t, codepoint);
				n2i_opcode_put_pushintop(state, e->codeimage_, opcodes, vali);
			}
			break;
		default:
			N2_ASSERT(0);
			break;
		}
		++c->stack_;
		break;
	case N2_AST_NODE_TEMPLATE_STRING:
		{
			const int top = c->stack_;
			const n2_ast_node_t* ncur = n;
			while (ncur)
			{
				N2_ASSERT(ncur->node_ == N2_AST_NODE_TEMPLATE_STRING || ncur->node_ == N2_AST_NODE_TEMPLATE_STRING_PARTS);
				{
					const char* ncurstr = ncur->token_->content_;
					int strindex = n2_plstrarray_find(e->codeimage_->str_literals_, n2i_plstarray_matchfunc, ncurstr);
					if (strindex < 0)
					{
						strindex = N2_SCAST(int, n2_plstrarray_size(e->codeimage_->str_literals_));
						char* str = n2_plstr_clone(state, ncurstr);
						n2_plstrarray_pushv(state, e->codeimage_->str_literals_, str);
					}
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STRING);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, strindex));
					++c->stack_;
				}
				if (ncur->left_ && !n2i_environment_generate_walk(state, e, ncur->left_, c)) { return N2_FALSE; }
				ncur = ncur->right_;
			}
			const int arg_num = c->stack_ - top;
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_TEMPLATE_STRING);
			n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, arg_num));
			c->stack_ = top + 1;
		}
		break;
	case N2_AST_NODE_IDENTIFIER_EXPR:
		{
			const int top = c->stack_;
			if (n->left_) { if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; } }
			const int arg_num = c->stack_ - top;

			N2_ASSERT(n->token_->token_ == N2_TOKEN_IDENTIFIER || n->token_->token_ == N2_TOKEN_IDENTIFIER_FQ);
			const char* ident = n->token_->content_;

			n2_str_t fullname, fullname_global;
			n2_str_init(&fullname); n2_str_init(&fullname_global);
			n2_naming_compute(state, ident, SIZE_MAX, c->module_ ? c->module_->name_ : NULL, NULL, &fullname, NULL);
			n2_naming_replace_modulename(state, fullname.str_, SIZE_MAX, n2i_modulename_default, &fullname_global);

			n2_bool_t accepted = N2_FALSE;

			// ローカル変数
			if (!accepted)
			{
				const int paramindex = (c->func_ && c->func_->params_ ? n2_funcparamarray_find(c->func_->params_, n2i_funcparamarray_matchfunc, ident) : -1);
				if (paramindex >= 0)
				{
					const n2_func_param_t* param = n2_funcparamarray_peek(c->func_->params_, paramindex);
					N2_ASSERT(param);
					if (arg_num > 0 && param->type_ != N2_FUNC_PARAM_LOCAL && param->type_ != N2_FUNC_PARAM_ARRAY)
					{
						n2i_environment_generate_raise(state, n, "関数の引数（%s）は次元を持たない値のため括弧によるアクセスはできません", ident);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}
					if (arg_num > N2_VARIABLE_DIM)
					{
						n2i_environment_generate_raise(state, n, "ローカル変数（%s）の添え字は%d次元までです", ident, N2_VARIABLE_DIM);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_STACK);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, paramindex));
					accepted = N2_TRUE;
				}
			}

			// モジュールローカル変数
			if (!accepted)
			{
				if (c->module_)
				{
					const int modvarindex = n2_modlocalvararray_find(c->module_->modlocalvars_, n2i_modvararray_matchfunc, ident);
					if (modvarindex >= 0)
					{
						if (arg_num > N2_VARIABLE_DIM)
						{
							n2i_environment_generate_raise(state, n, "モジュールローカル変数（%s）の添え字は%d次元までです", ident, N2_VARIABLE_DIM);
							n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
							return N2_FALSE;
						}
						n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_MODULE_LOCALVAR);
						n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, modvarindex));
						accepted = N2_TRUE;
					}
				}
			}

			// モジュール
			if (!accepted)
			{
				n2_module_t* emodule = n2_moduletable_find(e->moduletable_, ident);
				if (emodule)
				{
					if (arg_num > 0)
					{
						n2i_environment_generate_raise(state, n, "モジュール（%s）は次元を持たない値のため括弧によるアクセスはできません", ident);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}

					const int modindex = n2_modulearray_compute_index(e->moduletable_->modulearray_, emodule);
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_MODULE);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, modindex));
					accepted = N2_TRUE;
				}
			}

			// 関数
			if (!accepted)
			{
				n2_func_t* func = n2_functable_find(e->functable_, fullname.str_);
				if (!func && n->token_->token_ != N2_TOKEN_IDENTIFIER_FQ) { func = n2_functable_find(e->functable_, fullname_global.str_); }
				if (func)
				{
					const int funcindex = n2_funcarray_compute_index(e->functable_->funcarray_, func);
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_FUNCTION);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, funcindex));
					n2_opcodearray_pushv(state, opcodes, (arg_num & 0xffff) | (0));
					accepted = N2_TRUE;
				}
			}

			// システム変数
			if (!accepted)
			{
				n2_bool_t is_ex = N2_FALSE;
				const int sysvar = n2i_environment_find_sysvar(e, ident, &is_ex);
				if (sysvar >= 0)
				{
					if (arg_num > 0)
					{
						n2i_environment_generate_raise(state, n, "システム変数（%s）に添え字はありません", ident);
						n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
						return N2_FALSE;
					}

					n2_opcodearray_pushv(state, opcodes, is_ex ? N2_OPCODE_PUSH_SYSVAR_EX : N2_OPCODE_PUSH_SYSVAR);
					n2_opcodearray_pushv(state, opcodes, sysvar);
					accepted = N2_TRUE;
				}
			}

			// 配列変数
			if (!accepted)
			{
				if (arg_num > N2_VARIABLE_DIM)
				{
					n2i_environment_generate_raise(state, n, "配列変数（%s）の添え字は%d次元までです", fullname.str_, N2_VARIABLE_DIM);
					n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
					return N2_FALSE;
				}

				const int varindex = n2_vartable_register(state, e, e->vartable_, fullname.str_);
				N2_ASSERT(varindex >= 0);

				n2_opcodearray_pushv(state, opcodes, N2_OPCODE_PUSH_VARIABLE);
				n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, varindex));
				if (arg_num > 0)
				{
					n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SET_VARIABLE_APTR);
					n2_opcodearray_pushv(state, opcodes, N2_SCAST(n2_opcode_t, arg_num));
				}
				accepted = N2_TRUE;
			}

			n2_str_teardown(state, &fullname); n2_str_teardown(state, &fullname_global);
			c->stack_ = top + 1;
		}
		break;

	case N2_AST_NODE_END:
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_END);
		break;

	case N2_AST_NODE_RETURN:
		if (n->left_)
		{
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
			--c->stack_;
		}
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_RETURN);
		n2_opcodearray_pushv(state, opcodes, n->left_ ? 1 : 0);
		break;

	case N2_AST_NODE_GOTO:
	case N2_AST_NODE_GOSUB:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			n2_opcodearray_pushv(state, opcodes, n->node_ == N2_AST_NODE_GOTO ? N2_OPCODE_GOTO : N2_OPCODE_GOSUB);
			--c->stack_;
		}
		break;

	case N2_AST_NODE_REPEAT:
		{
			if (n->left_)
			{
				if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
				--c->stack_;
			}
			else
			{
				const n2_valint_t vali = -1;
				n2i_opcode_put_pushintop(state, e->codeimage_, opcodes, vali);
			}

			const size_t pos_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_REPEAT);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL

			n2i_codegen_shortblock_t sblock;
			n2i_codegen_shortblock_init(&sblock);
			sblock.type_ = N2I_CODEGEN_SHORTBLOCK_REPEAT;
			sblock.begin_pc_ = N2_SCAST(n2_pc_t, pos_head);
			n2i_codegen_shortblockarray_push(state, c->shortblocks_, &sblock);

			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_REPEAT_CHECK);
		}
		break;
	case N2_AST_NODE_FOREACH:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
			--c->stack_;

			const size_t pos_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_FOREACH);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL

			n2i_codegen_shortblock_t sblock;
			n2i_codegen_shortblock_init(&sblock);
			sblock.type_ = N2I_CODEGEN_SHORTBLOCK_REPEAT;
			sblock.begin_pc_ = N2_SCAST(n2_pc_t, pos_head);
			n2i_codegen_shortblockarray_push(state, c->shortblocks_, &sblock);

			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_REPEAT_CHECK);
		}
		break;
	case N2_AST_NODE_LOOP:
		{
			n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_REPEAT);
			if (!sblock)
			{
				n2i_environment_generate_raise(state, n, "repeat-loop: repeatがないのにloopを検出しました");
				return N2_FALSE;
			}
			if (n2i_codegen_shortblockarray_peek(c->shortblocks_, -1) != sblock)
			{
				n2i_environment_generate_raise(state, n, "repeat-loop: repeat内部でrepeat以外のブロック（switchなど）が閉じられていないのにloopでrepeatを閉じようとしました");
				return N2_FALSE;
			}

			const size_t loop_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_LOOP);

			const n2_opcode_t write_offset = N2_SCAST(n2_opcode_t, sblock->begin_pc_) + 1;
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, write_offset)) = N2_SCAST(n2_opcode_t, loop_head);
			n2i_codegen_shortblock_pop_to_typed(state, c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_REPEAT);
		}
		break;
	case N2_AST_NODE_CONTINUE:
		if (!n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_REPEAT))
		{
			n2i_environment_generate_raise(state, n, "repeat-loop: repeatがないのにcontinueを検出しました");
			return N2_FALSE;
		}
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_CONTINUE);
		break;
	case N2_AST_NODE_BREAK:
		if (!n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_REPEAT))
		{
			n2i_environment_generate_raise(state, n, "repeat-loop: repeatがないのにbreakを検出しました");
			return N2_FALSE;
		}
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_BREAK);
		break;

	case N2_AST_NODE_IF:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			N2_ASSERT(n->right_);
			const n2_ast_node_t* dispatcher = n->right_;
			N2_ASSERT(dispatcher->node_ == N2_AST_NODE_IF_DISPATCHER);

			const size_t pos_root = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_IF);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy FALSE

			N2_ASSERT(dispatcher->left_);
			if (!n2i_environment_generate_walk(state, e, dispatcher->left_, c)) { return N2_FALSE; }
			const size_t pos_true_tail = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_JUMP_RELATIVE);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL

			const size_t pos_false_head = n2_opcodearray_size(opcodes);
			if (dispatcher->right_) { if (!n2i_environment_generate_walk(state, e, dispatcher->right_, c)) { return N2_FALSE; } }

			const size_t pos_tail = n2_opcodearray_size(opcodes);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_root + 1)) = N2_SCAST(n2_opcode_t, pos_false_head - pos_root);
			*n2_opcodearray_peek(opcodes, N2_SCAST(int, pos_true_tail + 1)) = N2_SCAST(n2_opcode_t, pos_tail - pos_true_tail);
		}
		break;
	case N2_AST_NODE_IF_DISPATCHER:
		N2_ASSERT(0);
		break;

	case N2_AST_NODE_SWITCH:
		{
			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }

			const size_t pos_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SWITCH);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL

			n2i_codegen_shortblock_t sblock;
			n2i_codegen_shortblock_init(&sblock);
			sblock.type_ = N2I_CODEGEN_SHORTBLOCK_SWITCH;
			sblock.begin_pc_ = N2_SCAST(n2_pc_t, pos_head);
			sblock.swcase_prologue_pcs_ = n2_intarray_alloc(state, 8, 8);
			sblock.swcase_head_pcs_ = n2_intarray_alloc(state, 8, 8);
			n2i_codegen_shortblockarray_push(state, c->shortblocks_, &sblock);
		}
		break;
	case N2_AST_NODE_CASE:
		{
			n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_SWITCH);
			if (!sblock)
			{
				n2i_environment_generate_raise(state, n, "switch-swend: switchがないのにcaseを検出しました");
				return N2_FALSE;
			}

			const size_t case_prologue = n2_opcodearray_size(opcodes);

			N2_ASSERT(n->left_);
			if (!n2i_environment_generate_walk(state, e, n->left_, c)) { return N2_FALSE; }
			--c->stack_;

			const size_t case_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SWCASE);
			n2_opcodearray_pushv(state, opcodes, 0);// dummy TAIL of case

			n2_intarray_pushv(state, sblock->swcase_prologue_pcs_, N2_SCAST(int, case_prologue));
			n2_intarray_pushv(state, sblock->swcase_head_pcs_, N2_SCAST(int, case_head));
		}
		break;
	case N2_AST_NODE_DEFAULT:
		{
			n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_SWITCH);
			if (!sblock)
			{
				n2i_environment_generate_raise(state, n, "switch-swend: switchがないのにdefaultを検出しました");
				return N2_FALSE;
			}
			if (sblock->swdefault_pc_ >= 0)
			{
				n2i_environment_generate_raise(state, n, "switch-swend: 重複したdefaultを検出しました");
				return N2_FALSE;
			}
			sblock->swdefault_pc_ = N2_SCAST(int, n2_opcodearray_size(opcodes));
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SWDEFAULT);
		}
		break;
	case N2_AST_NODE_SWBREAK:
		if (!n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_SWITCH))
		{
			n2i_environment_generate_raise(state, n, "switch-swend: switchがないのにswbreakを検出しました");
			return N2_FALSE;
		}
		n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SWBREAK);
		break;
	case N2_AST_NODE_SWEND:
		{
			n2i_codegen_shortblock_t* sblock = n2i_codegen_shortblock_find_last_typed(c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_SWITCH);
			if (!sblock)
			{
				n2i_environment_generate_raise(state, n, "switch-swend: switchがないのにswendを検出しました");
				return N2_FALSE;
			}
			if (n2i_codegen_shortblockarray_peek(c->shortblocks_, -1) != sblock)
			{
				n2i_environment_generate_raise(state, n, "switch-swend: switch内部でswitch以外のブロック（repeatなど）が閉じられていないのにswendでswitchを閉じようとしました");
				return N2_FALSE;
			}

			// pop value for switch
			--c->stack_;

			const size_t swend_head = n2_opcodearray_size(opcodes);
			n2_opcodearray_pushv(state, opcodes, N2_OPCODE_SWEND);

			// コードブランチを書き込み
			{
				const n2_opcode_t write_offset = N2_SCAST(n2_opcode_t, sblock->begin_pc_) + 1;
				*n2_opcodearray_peek(opcodes, N2_SCAST(int, write_offset)) = N2_SCAST(n2_opcode_t, swend_head);
			}
			for (size_t ci = 0, cl = n2_intarray_size(sblock->swcase_head_pcs_); ci < cl; ++ci)
			{
				const int* this_head = n2_intarray_peekc(sblock->swcase_head_pcs_, N2_SCAST(int, ci));
				const int* next_prologue = n2_intarray_peekc(sblock->swcase_prologue_pcs_, N2_SCAST(int, ci + 1));
				const size_t next_pos = next_prologue ? N2_SCAST(size_t, *next_prologue) : sblock->swdefault_pc_ >= 0 ? sblock->swdefault_pc_ : swend_head;
				*n2_opcodearray_peek(opcodes, N2_SCAST(int, *this_head + 1)) = N2_SCAST(n2_opcode_t, next_pos);
			}

			n2i_codegen_shortblock_pop_to_typed(state, c->shortblocks_, N2I_CODEGEN_SHORTBLOCK_SWITCH);
		}
		break;

	default:
		N2_ASSERT(0);
		n2i_environment_generate_raise(state, n, "処理できないASTノードが見つかりました");
		return N2_FALSE;
	}
	return N2_TRUE;
}

static n2_bool_t n2i_environment_generate(n2_state_t* state, n2_environment_t* e, n2_ast_node_t* ast, const n2_sourcecode_t* sourcecode)
{
	const char* package = sourcecode->package_.str_;

	n2i_codegen_context_t c;
	c.sourcecode_ = sourcecode;
	c.stack_ = 0;
	c.shortblocks_ = n2i_codegen_shortblockarray_alloc(state, 16, 4);
	c.generate_codelines_ = state->config_.generate_codelines_;
	c.uselib_ = NULL;
	c.func_ = NULL;
	c.module_ = NULL;

	n2_bool_t res = N2_TRUE;

	n2_ast_node_t* node = ast;
	while (node)
	{
		// 末尾再起
		if (node->node_ != N2_AST_NODE_ROOT && node->node_ != N2_AST_NODE_ROOT_PARTS) { break; }
		if (node->left_) { if (!n2i_environment_generate_walk(state, e, node->left_, &c)) { res = N2_FALSE; break; } }
		node = node->right_;
	}

	// 追加検証
	if (res)
	{
		if (c.module_)
		{
			n2i_raise_as(state, N2_ERROR_COMPILE, sourcecode, package, NULL, -1, "#module-#global: 閉じられていないモジュール（%s）が存在します", c.module_->name_);
			res = N2_FALSE;
		}
		if (n2i_codegen_shortblockarray_size(c.shortblocks_) > 0)
		{
			const n2i_codegen_shortblock_t* last_sblock = n2i_codegen_shortblockarray_peek(c.shortblocks_, -1);
			switch (last_sblock->type_)
			{
			case N2I_CODEGEN_SHORTBLOCK_REPEAT:
				n2i_raise_as(state, N2_ERROR_COMPILE, sourcecode, package, NULL, -1, "repeat-loop: 閉じられていないブロックが存在します");
				break;
			case N2I_CODEGEN_SHORTBLOCK_SWITCH:
				n2i_raise_as(state, N2_ERROR_COMPILE, sourcecode, package, NULL, -1, "switch-swend: 閉じられていないブロックが存在します");
				break;
			default:
				N2_ASSERT(0);
				break;
			}
			res = N2_FALSE;
		}
	}

	// 何もないなら 0 だと都合悪いのでとりあえず書いておく
	if (n2_opcodearray_size(e->codeimage_->opcodes_) <= 0)
	{
		n2_opcodearray_pushv(state, e->codeimage_->opcodes_, N2_OPCODE_NOP);
	}

#if N2_CONFIG_USE_DEBUGGING
	// 足りてないならopcodesと同じだけの数のフラグを用意しておく
	if (e->codeimage_->opcodeflags_)
	{
		const size_t opcodelen = n2_opcodearray_size(e->codeimage_->opcodes_);
		n2_u8array_reserve(state, e->codeimage_->opcodeflags_, opcodelen);
		while (n2_u8array_size(e->codeimage_->opcodeflags_) < opcodelen)
		{
			n2_u8array_pushv(state, e->codeimage_->opcodeflags_, 0x00);
		}
	}
#endif

	// 確保したデータの破棄
	n2i_codegen_shortblockarray_free(state, c.shortblocks_);

	return res;
}

//=============================================================================
// 即席実行
N2_API void n2_ast_evaluate_context_init(n2_ast_evaluate_context_t* context)
{
	n2_str_init(&context->error_);
}

N2_API void n2_ast_evaluate_context_teardown(n2_state_t* state, n2_ast_evaluate_context_t* context)
{
	n2_str_teardown(state, &context->error_);
}

N2_API n2_value_t* n2_ast_evaluate_immediate(n2_state_t* state, n2_ast_evaluate_context_t* context, const n2_ast_node_t* ast)
{
	n2_fiber_t* fiber = n2_fiber_alloc(state, state->environment_, -1, "immeval", SIZE_MAX);
	fiber->ast_evaluate_context_ = context;

	const n2_bool_t is_succeeded = n2_ast_node_evaluate(state, fiber, ast);

	// 戻り値
	n2_value_t* res = NULL;
	if (is_succeeded && n2_valuearray_size(fiber->values_) > 0)
	{
		res = n2_value_clone(state, n2_valuearray_peekv(fiber->values_, -1, NULL));
		N2_ASSERT(res);
		n2_value_isolate(state, fiber, res, N2_TRUE);
	}

	n2_fiber_free(state, fiber);
	return res;
}

N2_API n2_bool_t n2_ast_node_evaluate(n2_state_t* state, n2_fiber_t* f, const n2_ast_node_t* node)
{
	switch (node->node_)
	{
	case N2_AST_NODE_EMPTY: break;

	case N2_AST_NODE_EXPRESSION:
		N2_ASSERT(node->left_);
		return n2_ast_node_evaluate(state, f, node->left_);

	case N2_AST_NODE_CONDITIONAL:
		{
			N2_ASSERT(node->left_);
			if (!n2_ast_node_evaluate(state, f, node->left_) ) { return N2_FALSE; }

			n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
			const n2_bool_t is = n2_value_eval_bool(state, f, lhs);
			n2_valuearray_pop(state, f->values_, 1);

			N2_ASSERT(node->right_);
			N2_ASSERT(node->right_->node_ == N2_AST_NODE_CONDITIONAL);

			if (!n2_ast_node_evaluate(state, f, is ? node->right_->left_ : node->right_->right_)) { return N2_FALSE; }
		}
		break;

	case N2_AST_NODE_LOR:
	case N2_AST_NODE_LAND:
		{
			N2_ASSERT(node->left_);
			if (!n2_ast_node_evaluate(state, f, node->left_) ) { return N2_FALSE; }

			n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
			const n2_bool_t is = n2_value_eval_bool(state, f, lhs);
			if ((is ? N2_TRUE : N2_FALSE) != (node->node_ == N2_AST_NODE_LOR ? N2_TRUE : N2_FALSE))
			{
				n2_valuearray_pop(state, f->values_, 1);
				N2_ASSERT(node->right_);
				if (!n2_ast_node_evaluate(state, f, node->right_)) { return N2_FALSE; }
			}
		}
		break;

	case N2_AST_NODE_BOR:
	case N2_AST_NODE_BAND:
	case N2_AST_NODE_BXOR:
	case N2_AST_NODE_EQ:
	case N2_AST_NODE_NEQ:
	case N2_AST_NODE_GT:
	case N2_AST_NODE_GTOE:
	case N2_AST_NODE_LT:
	case N2_AST_NODE_LTOE:
	case N2_AST_NODE_BLSHIFT:
	case N2_AST_NODE_BRSHIFT:
	case N2_AST_NODE_ADD:
	case N2_AST_NODE_SUB:
	case N2_AST_NODE_MUL:
	case N2_AST_NODE_DIV:
	case N2_AST_NODE_MOD:
		{
			N2_ASSERT(node->left_);
			if (!n2_ast_node_evaluate(state, f, node->left_) ) { return N2_FALSE; }
			N2_ASSERT(node->right_);
			if (!n2_ast_node_evaluate(state, f, node->right_) ) { return N2_FALSE; }

			if (n2_valuearray_size(f->values_) < 2)
			{
				if (f->ast_evaluate_context_) { n2_str_fmt_to(state, &f->ast_evaluate_context_->error_, "二項演算時に対象の値が存在してません"); }
				return N2_FALSE;
			}

			n2_value_t* lhs = n2_valuearray_peekv(f->values_, -2, NULL);
			n2_value_t* rhs = n2_valuearray_peekv(f->values_, -1, NULL);
			n2_value_isolate(state, f, lhs, N2_TRUE);

			switch (node->node_)
			{
			case N2_AST_NODE_BOR:		n2_value_bor(state, f, lhs, rhs); break;
			case N2_AST_NODE_BAND:		n2_value_band(state, f, lhs, rhs); break;
			case N2_AST_NODE_BXOR:		n2_value_bxor(state, f, lhs, rhs); break;
			case N2_AST_NODE_EQ:		n2_value_eq(state, f, lhs, rhs); break;
			case N2_AST_NODE_NEQ:		n2_value_neq(state, f, lhs, rhs); break;
			case N2_AST_NODE_GT:		n2_value_gt(state, f, lhs, rhs); break;
			case N2_AST_NODE_GTOE:		n2_value_gtoe(state, f, lhs, rhs); break;
			case N2_AST_NODE_LT:		n2_value_lt(state, f, lhs, rhs); break;
			case N2_AST_NODE_LTOE:		n2_value_ltoe(state, f, lhs, rhs); break;
			case N2_AST_NODE_BLSHIFT:	n2_value_blshift(state, f, lhs, rhs); break;
			case N2_AST_NODE_BRSHIFT:	n2_value_brshift(state, f, lhs, rhs); break;
			case N2_AST_NODE_ADD:		n2_value_add(state, f, lhs, rhs); break;
			case N2_AST_NODE_SUB:		n2_value_sub(state, f, lhs, rhs); break;
			case N2_AST_NODE_MUL:		n2_value_mul(state, f, lhs, rhs); break;
			case N2_AST_NODE_DIV:		n2_value_div(state, f, lhs, rhs); break;
			case N2_AST_NODE_MOD:		n2_value_mod(state, f, lhs, rhs); break;
			default:					N2_ASSERT(0); break;
			}
			n2_valuearray_pop(state, f->values_, 1);
		}
		break;

	case N2_AST_NODE_UNARY_NOT:
		{
			N2_ASSERT(node->left_);
			if (!n2_ast_node_evaluate(state, f, node->left_)) { return N2_FALSE; }
			if (n2_valuearray_size(f->values_) < 1)
			{
				if (f->ast_evaluate_context_) { n2_str_fmt_to(state, &f->ast_evaluate_context_->error_, "単項演算時に対象の値が存在してません"); }
				return N2_FALSE;
			}
			n2_value_t* val = n2_valuearray_peekv(f->values_, -1, NULL);
			n2_value_isolate(state, f, val, N2_TRUE);
			n2_value_unary_not(state, f, val);
		}
		break;

	case N2_AST_NODE_UNARY_MINUS:
		{
			N2_ASSERT(node->left_);
			if (!n2_ast_node_evaluate(state, f, node->left_)) { return N2_FALSE; }
			if (n2_valuearray_size(f->values_) < 1)
			{
				if (f->ast_evaluate_context_) { n2_str_fmt_to(state, &f->ast_evaluate_context_->error_, "単項演算時に対象の値が存在してません"); }
				return N2_FALSE;
			}
			n2_value_t* val = n2_valuearray_peekv(f->values_, -1, NULL);
			n2_value_isolate(state, f, val, N2_TRUE);
			n2_value_unary_minus(state, f, val);
		}
		break;

	case N2_AST_NODE_PRIMITIVE_VALUE:
		switch (node->token_->token_)
		{
		case N2_TOKEN_NIL:		n2_valuearray_pushv(state, f->values_, n2_value_allocnil(state)); break;
		case N2_TOKEN_INT:		n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, N2_SCAST(n2_valint_t, N2_STRTOLL(node->token_->content_, NULL, 0)))); break;
		case N2_TOKEN_FLOAT:	n2_valuearray_pushv(state, f->values_, n2_value_allocf(state, N2_STRTOD(node->token_->content_, NULL))); break;
		case N2_TOKEN_STRING:
			{
				n2_valstr_t s; n2_str_init(&s); n2_str_set(state, &s, node->token_->content_, SIZE_MAX);
				n2_valuearray_pushv(state, f->values_, n2_value_allocs(state, &s));
				n2_str_teardown(state, &s);
			}
			break;
		default:				N2_ASSERT(0); break;
		}
		break;

	//case N2_AST_NODE_IDENTIFIER_EXPR:
		// @todo constexpr function call
		//break;

	default:
		if (f->ast_evaluate_context_) { n2_str_fmt_to(state, &f->ast_evaluate_context_->error_, "AST評価ではサポートされてないノード（%s）", node->token_->content_); }
		return N2_FALSE;
	}
	return N2_TRUE;
}

//=============================================================================
// 全体（ステート）
static void n2i_execute_fill_to_callframe(n2_state_t* state, n2_callframe_t* cf, n2_fiber_t* f)
{
	N2_UNUSE(state);
	cf->caller_function_ = f->callstate_.func_;
	cf->caller_label_ = f->callstate_.label_;
	cf->csflags_ = f->callstate_.flags_;
	cf->base_ = f->callstate_.base_;
	cf->arg_num_ = f->callstate_.arg_num_;
	cf->original_arg_num_ = f->callstate_.arg_num_;
	cf->shortframe_cursor_ = n2_shortframearray_size(f->shortframes_);
	// 変数領域を委譲
	cf->local_vars_ = f->curscope_local_vars_; f->curscope_local_vars_ = NULL;
#if N2_CONFIG_USE_DEBUGGING
	// デバッグ変数
	if (state->config_.generate_debugvars_ && !cf->debugvarroot_)
	{
		cf->debugvarpool_ = f->environment_->debugvarpool_;
		cf->debugvarroot_ = n2_debugvarpool_pop_or_alloc(state, cf->debugvarpool_);
		cf->debugvarroot_->type_ = N2_DEBUGVARIABLE_FIBER_CALLFRAME;
		cf->debugvarroot_->v_.fiber_cf_.fiber_ = f;
		cf->debugvarroot_->v_.fiber_cf_.callframe_index_ = n2_callframearray_compute_index(f->callframes_, cf);
		cf->debugvarargs_ = f->callstate_.debugvarargs_; f->callstate_.debugvarargs_ = NULL;
		// 所属するcallframeが変わったので再設定
		if (cf->debugvarargs_)
		{
			const int callframe_index = n2_callframearray_compute_index(f->callframes_, cf);
			for (size_t i = 0, l = n2_debugvararray_size(cf->debugvarargs_); i < l; ++i)
			{
				n2_debugvariable_t* debugvar = n2_debugvararray_peekv(cf->debugvarargs_, N2_SCAST(int, i), NULL);
				N2_ASSERT(debugvar->type_ == N2_DEBUGVARIABLE_FUNCTIONARG);
				debugvar->v_.funcarg_.callframe_index_ = callframe_index;
			}
		}
	}
#endif
}

static void n2i_execute_post_setup_callframe(n2_state_t* state, n2_callframe_t* cf, n2_fiber_t* f)
{
	N2_UNUSE(state);
	N2_UNUSE(cf);
	N2_UNUSE(f);
#if N2_CONFIG_USE_DEBUGGING
	// デバッグ変数
	if (state->config_.generate_debugvars_ && f->callstate_.func_)
	{
		const n2_func_t* func = f->callstate_.func_;
		const size_t func_param_num = func->params_ ? n2_funcparamarray_size(func->params_) : f->callstate_.arg_num_;
		if (func_param_num > 0)
		{
			f->callstate_.debugvarargs_ = n2_debugvararray_alloc_user(state, func_param_num, 0, f->environment_->debugvarpool_);
			for (size_t i = 0; i < func_param_num; ++i)
			{
				n2_debugvariable_t* debugvar = n2_debugvarpool_pop_or_alloc(state, f->environment_->debugvarpool_);
				debugvar->type_ = N2_DEBUGVARIABLE_FUNCTIONARG;
				debugvar->v_.funcarg_.fiber_ = f;
				debugvar->v_.funcarg_.callframe_index_ = -1;
				debugvar->v_.funcarg_.arg_index_ = N2_SCAST(int, i);
				n2_debugvararray_pushv(state, f->callstate_.debugvarargs_, debugvar);
			}
		}
	}
#endif
}

static n2_bool_t n2i_fiber_sync_shortframes(n2_fiber_t* f)
{
	for (size_t si = 0, sl = n2_shortframearray_size(f->shortframes_); si < sl; ++si)
	{
		const n2_shortframe_t* sf = n2_shortframearray_peek(f->shortframes_, -N2_SCAST(int, si) - 1);
		if (sf && sf->type_ == N2_SHORTFRAME_LOOP)
		{
			f->cnt_ = sf->content_.loop_.cnt_;
			return N2_TRUE;
		}
	}
	return N2_FALSE;
}

static n2_bool_t n2i_execute_rewind_to_callframe(n2_state_t* state, n2_fiber_t* f, n2_callframe_t* cf)
{
#if N2_CONFIG_USE_DEBUGGING
	if (f->callstate_.debugvarargs_) { n2_debugvararray_free(state, f->callstate_.debugvarargs_); f->callstate_.debugvarargs_ = NULL; }
	f->callstate_.debugvarargs_ = cf->debugvarargs_;
	cf->debugvarargs_ = NULL;
	// 所属するcallframeが変わったので再設定
	if (f->callstate_.debugvarargs_)
	{
		for (size_t i = 0, l = n2_debugvararray_size(f->callstate_.debugvarargs_); i < l; ++i)
		{
			n2_debugvariable_t* debugvar = n2_debugvararray_peekv(f->callstate_.debugvarargs_, N2_SCAST(int, i), NULL);
			N2_ASSERT(debugvar->type_ == N2_DEBUGVARIABLE_FUNCTIONARG);
			debugvar->v_.funcarg_.callframe_index_ = -1;
		}
	}
#endif

	// shortframeを同期
	if (cf->shortframe_cursor_ != n2_shortframearray_size(f->shortframes_))
	{
		if (cf->shortframe_cursor_ > n2_shortframearray_size(f->shortframes_))
		{
			n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "gosub/関数呼び出しから戻った際、repeat-loop/switch-swendの階層が減少したのを検知");
			return N2_FALSE;
		}
		n2_shortframearray_pop(state, f->shortframes_, n2_shortframearray_size(f->shortframes_) - cf->shortframe_cursor_);

		n2i_fiber_sync_shortframes(f);
	}
	// 変数を解放
	if (f->curscope_local_vars_)
	{
		// キャプチャチェック
		for (size_t i = 0, l = n2_vararray_size(f->curscope_local_vars_); i < l; ++i)
		{
			n2_variable_t* var = n2_vararray_peekv(f->curscope_local_vars_, N2_SCAST(int, i), NULL);
			if (f->notevar_ == var) { f->notevar_ = NULL; f->noteaptr_ = -1; }
		}
		// 解放
		n2_vararray_free(state, f->curscope_local_vars_);
	}
	f->curscope_local_vars_ = cf->local_vars_; cf->local_vars_ = NULL;
	// その他の情報の同期
	f->callstate_.func_ = cf->caller_function_;
	f->callstate_.label_ = cf->caller_label_;
	f->callstate_.flags_ = cf->csflags_;
	f->callstate_.base_ = cf->base_;
	f->callstate_.arg_num_ = cf->arg_num_;
	f->callstate_.original_arg_num_ = cf->arg_num_;
	if (cf->next_pc_ >= 0) { f->pc_ = cf->next_pc_; }
	f->op_pc_ = f->pc_;// op_pcは即同期しておく
	return N2_TRUE;
}

static void n2_state_reset_fiber(n2_state_t* state, n2_fiber_t* f)
{
	while (n2_callframearray_size(f->callframes_))
	{
		n2_callframe_t* lcf = n2_callframearray_peek(f->callframes_, -1);
		n2i_execute_rewind_to_callframe(state, f, lcf);
		n2_callframearray_pop(state, f->callframes_, 1);
	}
	n2_callframearray_clear(state, f->callframes_);
	n2_shortframearray_clear(state, f->shortframes_);
	N2_ASSERT(!f->curscope_local_vars_);

	n2_valuearray_clear(state, f->values_);
	f->pc_ = -1;
	f->op_pc_ = -1;
	f->fiber_state_ = N2_FIBER_STATE_INITIALIZED;
}

static void n2_state_shutdown(n2_state_t* state)
{
	n2_fiber_t* f = state->main_fiber_;
	n2_state_reset_fiber(state, f);

	n2_environment_t* e = state->environment_;
	for (size_t i = 0, l = n2_vararray_size(&e->vartable_->vararray_); i < l; ++i)
	{
		n2_variable_t* var = n2_vararray_peekv(&e->vartable_->vararray_, N2_SCAST(int, i), NULL);
		N2_ASSERT(var);
		if (var->type_ == N2_VALUE_MODINST)
		{
			n2_variable_clear(state, var);
		}
	}
}

N2_API void n2_state_config_init(n2_state_config_t* dst_config)
{
	n2_state_config_init_ex(dst_config, N2_STATE_CONFIG_FLAG_DEFAULT);
}

N2_API void n2_state_config_init_ex(n2_state_config_t* dst_config, size_t flags)
{
	N2_UNUSE(flags);

	dst_config->allocator_.allocate_ = NULL;
	dst_config->allocator_.free_ = NULL;
#if N2_CONFIG_USE_STD_MALLOC
	dst_config->allocator_.allocate_ = &n2i_default_allocate;
	dst_config->allocator_.free_ = &n2i_default_free;
#endif
	dst_config->allocator_.alloc_user_ = NULL;
	dst_config->allocator_close_ = NULL;

#if N2_CONFIG_USE_RPMALLOC_LIB
	if ((flags & N2_STATE_CONFIG_FLAG_NO_RPMALLOC) == 0)
	{
		n2h_rpmalloc_init();
		dst_config->allocator_.allocate_ = &n2i_rpmalloc_allocate;
		dst_config->allocator_.free_ = &n2i_rpmalloc_free;
		dst_config->allocator_close_ = &n2i_rpmalloc_close;
	}
#endif

	dst_config->print_ = NULL;
	dst_config->print_log_ = NULL;
	dst_config->print_error_ = NULL;
#if N2_CONFIG_USE_STD_PRINT
	dst_config->print_ = &n2i_default_print;
	dst_config->print_log_ = &n2i_default_print_log;
	dst_config->print_error_ = &n2i_default_print_error;
#endif
	dst_config->print_user_ = NULL;

#if N2_CONFIG_USE_STD_FILEIO
	dst_config->file_read_ = &n2i_default_file_read;
	dst_config->file_write_ = &n2i_default_file_write;
#else
	dst_config->file_read_ = NULL;
	dst_config->file_write_ = NULL;
#endif
	dst_config->file_user_ = NULL;
	dst_config->file_read_tmp_buffer_size_ = N2_DEFAULT_FILE_READ_TMP_BUFFER_SIZE;

	dst_config->z_decompress_tmp_buffer_size_ = N2_DEFAULT_Z_DECOMP_READ_TMP_BUFFER_SIZE;

	dst_config->error_is_print_ = N2_TRUE;
	dst_config->error_print_callstack_ = N2_TRUE;
	dst_config->error_ = NULL;
	dst_config->error_user_ = NULL;

	dst_config->abort_on_unprotected_error_ = N2_TRUE;

	dst_config->value_cache_size_ = N2_DEFAULT_VALUE_CACHE_NUM;

	dst_config->variable_element_min_num_ = N2_DEFAULT_VARIABLE_ELEMENT_MIN_NUM;
	dst_config->variable_str_element_min_num_ = N2_DEFAULT_VARIABLE_STR_ELEMENT_MIN_NUM;
	dst_config->variable_granule_size_ = N2_DEFAULT_VARIABLE_GRANULE_SIZE;

	dst_config->max_shortframe_nest_ = N2_DEFAULT_MAX_SHORTFRAME_NEST;
	dst_config->max_call_nest_ = N2_DEFAULT_MAX_CALL_NEST;

	dst_config->generate_opcodeflags_ = N2_FALSE;
	dst_config->generate_codelines_ = N2_TRUE;
	dst_config->generate_debugvars_ = N2_FALSE;
	dst_config->enable_graphics_assert_ = N2_FALSE;

	dst_config->max_message_log_ = N2_DEFAULT_MESSAGE_LOG_MAX;

	dst_config->reference_hspver_ = N2_DEFAULT_REFERRENCE_HSPVER;
	dst_config->define_hsp30_ = N2_TRUE;
	dst_config->define_debug_ = N2_FALSE;

	dst_config->enable_error_include_push_ = N2_TRUE;

	dst_config->enable_script_auto_decode_utf16_ = N2_TRUE;
	dst_config->enable_script_auto_decode_cp932_ = N2_TRUE;

	dst_config->standard_init_sdl_with_subsystem_ = N2_FALSE;

	dst_config->standard_window_num_ = N2S_DEFAULT_WINDOW_NUM;

	dst_config->standard_await_exit_margin_ = N2S_DEFAULT_AWAIT_EXIT_MARGIN;

	dst_config->standard_window_default_width_ = N2S_DEFAULT_WINDOW_WIDTH;
	dst_config->standard_window_default_height_ = N2S_DEFAULT_WINDOW_HEIGHT;
	dst_config->standard_window_default_title_ = "nidonehsp";

	dst_config->standard_startup_window_width_ = dst_config->standard_window_default_width_;
	dst_config->standard_startup_window_height_ = dst_config->standard_window_default_height_;
	dst_config->standard_startup_window_title_ = dst_config->standard_window_default_title_;
	dst_config->standard_statup_window_shown_ = N2_TRUE;
	dst_config->standard_window_resize_on_creation_workaround_ = N2_TRUE;

	dst_config->standard_vertex_num_ = N2S_DEFAULT_STANDARD_VERTEX_NUM;
	dst_config->standard_index_num_ = N2S_DEFAULT_STANDARD_INDEX_NUM;
	dst_config->standard_command_num_ = N2S_DEFAULT_STANDARD_COMMAND_NUM;
	dst_config->standard_command_data_num_ = N2S_DEFAULT_STANDARD_COMMAND_DATA_NUM;

	dst_config->standard_gui_vertex_num_ = N2S_DEFAULT_STANDARD_GUI_VERTEX_NUM;
	dst_config->standard_gui_index_num_ = N2S_DEFAULT_STANDARD_GUI_INDEX_NUM;
	dst_config->standard_gui_vertex_expand_step_ = N2S_DEFAULT_STANDARD_GUI_VERTEX_EXSTEP;
	dst_config->standard_gui_index_expand_step_ = N2S_DEFAULT_STANDARD_GUI_INDEX_EXSTEP;

	dst_config->standard_font_fallback_codepoint_ = N2S_DEFAULT_FONT_FALLBACK_CODEPOINT;
	dst_config->standard_font_atlas_width_ = N2S_DEFAULT_FONT_ATLAS_WIDTH;
	dst_config->standard_font_atlas_height_ = N2S_DEFAULT_FONT_ATLAS_HEIGHT;
	dst_config->standard_font_default_bake_height_ = N2S_DEFAULT_FONT_BAKE_HEIGHT;
	dst_config->standard_font_default_draw_height_ = N2S_DEFAULT_FONT_DRAW_HEIGHT;
	dst_config->standard_font_draw_pixel_perfect_ = N2_TRUE;

	dst_config->standard_widget_input_default_max_buffer_size_ = N2S_DEFAULT_WIDGET_INPUT_MAX_BUFFER_SIZE;

	dst_config->standard_use_inspector_ = N2_FALSE;

	dst_config->user_ = NULL;
}

N2_API n2_state_t* n2_state_alloc(const n2_state_config_t* config)
{
	// コンフィグの決定
	n2_state_config_t sconfig;
	if (!config)
	{
		n2_state_config_init(&sconfig);
	}
	else
	{
		sconfig = *config;
	}

	n2_state_t* state = n2i_zmalloc(&sconfig.allocator_, sizeof(n2_state_t));
	if (!state) { return NULL; }
	state->config_ = sconfig;

	// 値キャッシュの確保
	if (state->config_.value_cache_size_ > 0)
	{
		state->value_cache_ = N2_TMALLOCA(n2_value_t*, state, state->config_.value_cache_size_);
		state->value_cache_left_ = 0;
	}
	else
	{
		state->value_cache_ = NULL;
		state->value_cache_left_ = 0;
	}

	// プリプロセッサ
	state->pp_context_ = n2_pp_context_alloc(state);

	// 環境構築
	state->environment_ = n2_environment_alloc(state);

	// ファイバーの構築
	state->next_fiber_id_ = 0;
	state->main_fiber_ = n2_fiber_alloc(state, state->environment_, state->next_fiber_id_++, "main", SIZE_MAX);

	// ファイルシステム
	state->filesystem_ = NULL;
	state->filesystem_system_ = n2h_filesystem_alloc_system(state);

	// その他の初期化
	state->internal_user_ = NULL;

	// 基底機能のバインド
	n2i_environment_bind_core_builtins(state, state->environment_);

	return state;
}

N2_API void n2_state_free(n2_state_t* state)
{
	N2_ASSERT(state);
	if (!state) { return; }

	// 雑多なものの破棄
	n2_state_shutdown(state);

	// ファイバーの破棄
	n2_fiber_free(state, state->main_fiber_);

	// 環境の破棄
	n2_environment_free(state, state->environment_);

	// プリプロセッサ
	n2_pp_context_free(state, state->pp_context_);

	// 値の破棄（teardown済みなので、メモリを解放するだけ）
	if (state->value_cache_)
	{
		for (size_t i = 0; i < state->value_cache_left_; ++i)
		{
			n2_free(state, state->value_cache_[i]);
		}
		n2_free(state, state->value_cache_);
	}

	// ファイルシステム
	if (state->filesystem_)
	{
		n2h_filesystem_free(state, state->filesystem_);
		state->filesystem_ = NULL;
	}
	if (state->filesystem_system_)
	{
		n2h_filesystem_free(state, state->filesystem_system_);
		state->filesystem_system_ = NULL;
	}

	const n2_allocator_t allocator = state->config_.allocator_;
	n2_allocator_close_func_t allocator_close = state->config_.allocator_close_;

	// 環境自体の破棄
	{
		n2i_zfree(&allocator, state);
	}

	// 最終破棄（アロケータ）
	if (allocator_close)
	{
		allocator_close(allocator.alloc_user_);
	}
}

N2_API void n2_state_bind_basics(n2_state_t* state)
{
	n2_pp_context_register_default_macros(state, state->pp_context_);
	n2i_environment_bind_basic_builtins(state, state->environment_);
}

N2_API void n2_state_bind_consoles(n2_state_t* state)
{
	n2i_environment_bind_console_builtins(state, state->environment_);
}

N2_API void n2_state_bind_standards(n2_state_t* state)
{
	n2i_environment_bind_standards_builtins(state, state->pp_context_, state->environment_);
}

N2_API n2_bool_t n2_state_load_str(n2_state_t* state, const char* package, const char* script, size_t script_size, const char* src_filepath_hint)
{
	if (!n2_environment_load_str(state, state->pp_context_, state->environment_, package, script, script_size, src_filepath_hint)) { return N2_FALSE; }
	return N2_TRUE;
}

N2_API n2_bool_t n2_state_load_file(n2_state_t* state, const char* src_filepath)
{
	n2_str_t file;
	n2_str_init(&file);
	n2_bool_t succeeded = n2_state_fs_load_str(state, &file, N2_STATE_FSFLAG_USE_SYSTEM_FS, src_filepath, SIZE_MAX, 0);
	if (succeeded) { succeeded = n2_state_load_str(state, NULL, file.str_, file.size_, src_filepath); }
	n2_str_teardown(state, &file);
	if (!succeeded) { return N2_FALSE; }
	return N2_TRUE;
}

static n2_bool_t n2i_execute_substitute_to_sysvar(n2_state_t* state, n2_fiber_t* f, n2_value_t* v)
{
	switch (n2_value_get_type(v))
	{
	case N2_VALUE_INT:		f->stat_ = n2_value_eval_int(state, f, v); return N2_TRUE;
	case N2_VALUE_FLOAT:	f->refdval_ = n2_value_eval_float(state, f, v); return N2_TRUE;
	case N2_VALUE_STRING:	n2_str_set(state, f->refstr_, n2_value_get_plstr(v), SIZE_MAX); return N2_TRUE;
	default:				break;
	}
	return N2_FALSE;
}

static int n2i_execute_dynlib_call(const n2_funcarg_t* arg)
{
	const n2_func_t* func = arg->func_;
	N2_ASSERT(func);
	if (!func->lib_ || !func->libproc_)
	{
		n2e_funcarg_raise(arg, "関数（%s）を呼び出そうとしましたが読み込まれていません。動的ライブラリ（%s）から関数名（%s）の検索に失敗しています。", func->name_, func->lib_ ? func->lib_->path_.str_ : "(unknown)", func->libprocname_.str_);
		return -1;
	}

	const size_t arg_num = n2e_funcarg_argnum(arg);
	if (arg_num != n2_funcparamarray_size(func->params_))
	{
		n2e_funcarg_raise(arg, "%s：引数の数（%zu）が期待（%zu）と違います。", func->name_, arg_num, n2_funcparamarray_size(func->params_));
		return -1;
	}

	// 引数をintptr_tにパッキングしていく
	n2h_dynlib_result_t dlresult = 0;
	n2h_dynlib_arg_t dlargs[N2H_DYNLIB_ARG_MAX] = {0};
	size_t dlargnum = 0;

	n2h_dynlib_arg_t dltmp[4];
	size_t dltmpsize = 0;

	for (size_t i = 0; i < arg_num; ++i)
	{
		const n2_func_param_t* param = n2_funcparamarray_peek(func->params_, N2_SCAST(int, i));
		const n2_value_t* argval = n2e_funcarg_getarg(arg, N2_SCAST(int, i));
		switch (param->type_)
		{
		case N2_FUNC_PARAM_INT:
			{
				// 32bitでも64bitでもネイティブのintとして扱う
				dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, n2e_funcarg_eval_int(arg, argval));
				dltmpsize = sizeof(n2h_dynlib_arg_t);
			}
			break;
		case N2_FUNC_PARAM_FLOAT:
			{
				// 奇妙に見えるかもしれないがdoubleは32bit系においても値渡しであることを利用する（想定するCCでは）
				const double v = N2_SCAST(double, n2e_funcarg_eval_float(arg, argval));
				N2_MEMCPY(dltmp, &v, sizeof(double));
				dltmpsize = sizeof(double);
			}
			break;
#if N2_CONFIG_USE_ENCODING_CP932
		case N2_FUNC_PARAM_STR:
#endif
		case N2_FUNC_PARAM_WSTR:
		case N2_FUNC_PARAM_U8STR:
			{
				if (!argval || argval->type_ != N2_VALUE_STRING)
				{
					n2e_funcarg_raise(arg, "%s：引数（%zu番目＝%s）が文字列ではありません。", func->name_, i, param->name_ ? param->name_ : "(unnamed)");
					return -1;
				}
				const n2_str_t* argstr = n2_value_get_strc(argval);
				const n2_str_t* usestr = NULL;
				if (param->type_ == N2_FUNC_PARAM_STR)
				{
#if N2_CONFIG_USE_ENCODING_CP932
					n2_str_t* astr = n2e_funcarg_pushs(arg, "");
					n2_encoding_cp932_convert_from_utf8(arg->state_, astr, argstr->str_, n2_str_compute_size(argstr), '?');
					usestr = astr;
#else
					N2_ASSERT(0);
					return -1;
#endif
				}
				else if (param->type_ == N2_FUNC_PARAM_WSTR)
				{
					n2_str_t* wstr = n2e_funcarg_pushs(arg, "");
					n2_encoding_utf16ne_convert_from_utf8(arg->state_, wstr, argstr->str_, n2_str_compute_size(argstr), '?');
					usestr = wstr;
				}
				else
				{
					usestr = argstr;
				}
				dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, usestr->str_);
				dltmpsize = sizeof(n2h_dynlib_arg_t);
			}
			break;
		case N2_FUNC_PARAM_VAR:
		case N2_FUNC_PARAM_ARRAY:
			{
				if (!argval || argval->type_ != N2_VALUE_VARIABLE)
				{
					n2e_funcarg_raise(arg, "%s：引数（%zu番目＝%s）が変数ではありません。", func->name_, i, param->name_ ? param->name_ : "(unnamed)");
					return -1;
				}
				void* element_ptr = n2_variable_element_ptr(argval->field_.varvalue_.var_, argval->field_.varvalue_.aptr_);
				dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, element_ptr);
				dltmpsize = sizeof(n2h_dynlib_arg_t);
			}
			break;
		case N2_FUNC_PARAM_INT64:
			{
				const int64_t v = N2_SCAST(int64_t, n2e_funcarg_eval_int(arg, argval));
				N2_MEMCPY(dltmp, &v, sizeof(int64_t));
				dltmpsize = sizeof(int64_t);
			}
			break;
#if N2_CONFIG_USE_ENCODING_CP932
		case N2_FUNC_PARAM_SPTR:
#endif
		case N2_FUNC_PARAM_WPTR:
		case N2_FUNC_PARAM_U8PTR:
			{
				if (argval && argval->type_ == N2_VALUE_STRING)
				{
					const n2_str_t* argstr = n2_value_get_strc(argval);
					const n2_str_t* usestr = NULL;
					if (param->type_ == N2_FUNC_PARAM_SPTR)
					{
#if N2_CONFIG_USE_ENCODING_CP932
						n2_str_t* astr = n2e_funcarg_pushs(arg, "");
						n2_encoding_cp932_convert_from_utf8(arg->state_, astr, argstr->str_, n2_str_compute_size(argstr), '?');
						usestr = astr;
#else
						N2_ASSERT(0);
						return -1;
#endif
					}
					else if (param->type_ == N2_FUNC_PARAM_WPTR)
					{
						n2_str_t* wstr = n2e_funcarg_pushs(arg, "");
						n2_encoding_utf16ne_convert_from_utf8(arg->state_, wstr, argstr->str_, n2_str_compute_size(argstr), '?');
						usestr = wstr;
					}
					else
					{
						usestr = argstr;
					}
					dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, usestr->str_);
					dltmpsize = sizeof(n2h_dynlib_arg_t);
				}
				else
				{
					dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, n2e_funcarg_eval_int(arg, argval));
					dltmpsize = sizeof(n2h_dynlib_arg_t);
				}
			}
			break;
		case N2_FUNC_PARAM_SINGLEFLOAT:
			{
				// 値として扱う
				const float v = N2_SCAST(float, n2e_funcarg_eval_float(arg, argval));
				int32_t vi = 0;
				N2_ASSERT(sizeof(v) == sizeof(vi));
				N2_MEMCPY(&vi, &v, sizeof(float));
				dltmp[0] = N2_RCAST(n2h_dynlib_arg_t, vi);
				dltmpsize = sizeof(n2h_dynlib_arg_t);
			}
			break;
		case N2_FUNC_PARAM_NULLPTR:
			dltmp[0] = 0;
			dltmpsize = sizeof(n2h_dynlib_arg_t);
			break;

		case N2_FUNC_PARAM_LABEL:
		case N2_FUNC_PARAM_LOCAL:
		case N2_FUNC_PARAM_MODVAR:
		default:
			n2e_funcarg_raise(arg, "%s：引数（%zu番目＝%s）を評価できません。対応していない型です", func->name_, i, param->name_ ? param->name_ : "(unnamed)");
			return -1;
		}

		size_t pushed = 0;
		while (pushed < dltmpsize)
		{
			if (pushed >= N2H_DYNLIB_ARG_MAX)
			{
				n2e_funcarg_raise(arg, "動的ライブラリの関数（%s）呼び出しに失敗：引数の数が多すぎます、多すぎる引数を持つ関数呼び出しはサポートされていません", func->name_);
				return -1;
			}
			N2_MEMCPY(dlargs + dlargnum, n2_ptr_offset(dltmp, pushed), sizeof(n2h_dynlib_arg_t));
			pushed += sizeof(n2h_dynlib_arg_t);
			++dlargnum;
		}
	}

	if (!n2h_dynlib_call_single(arg->state_, func->lib_, func->libproc_, &dlresult, dlargs, dlargnum))
	{
		n2e_funcarg_raise(arg, "動的ライブラリ（%s）の関数（%s）の呼び出しに失敗。", func->lib_ ? func->lib_->path_.str_ : "(unknown)", func->libprocname_.str_);
		return -1;
	}

	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, dlresult));
	return 1;
}

static n2_bool_t n2i_execute_inner(n2_state_t* state, n2_fiber_t* f)
{
	N2_ASSERT(f->protectframe_);

	n2_environment_t* e = f->environment_;
	N2_ASSERT(e);

	// ここでオペコードはフリーズされている想定
	const n2_opcode_t* c = N2_RCAST(const n2_opcode_t*, e->codeimage_->opcodes_->elements_);
	const n2_pc_t code_size = N2_SCAST(n2_pc_t, n2_opcodearray_size(e->codeimage_->opcodes_));

#define N2_EI_ENSURE_VS_FNUM(num) \
	N2_ASSERT((num) <= (N2_SCAST(int, n2_valuearray_size(f->values_)) - f->callstate_.base_ - f->callstate_.arg_num_))

	for (;;)
	{
		// もう実行おわってる
		n2_bool_t is_execute_continue = N2_TRUE;
		switch (f->fiber_state_)
		{
		case N2_FIBER_STATE_YIELD:
		case N2_FIBER_STATE_YIELD_AWAIT:
		case N2_FIBER_STATE_STOPPED:
		case N2_FIBER_STATE_END:
		case N2_FIBER_STATE_FINISHED:
			is_execute_continue = N2_FALSE;
			break;
		default:
			break;
		}

		if (!is_execute_continue) { break; }

		// 末尾に到達した
		if (f->pc_ >= code_size) { f->pc_ = code_size; f->fiber_state_ = N2_FIBER_STATE_FINISHED; break; }

		n2_pc_t* pc = &f->pc_;
		f->op_pc_ = f->pc_;

		const n2_opcode_t op = c[*pc];

#if N2_CONFIG_USE_DEBUGGING
		// ポーリング
		if (e->debughook_ && e->debughook_->pollfunc_)
		{
			if (++e->debughook_->icounter_poll_operation_ >= e->debughook_->poll_per_operation_)
			{
				e->debughook_->pollfunc_(state, e->debughook_, N2_DEBUGHOOK_POLLFLAG_BUSY);
				e->debughook_->icounter_poll_operation_ = 0;
			}
		}

		n2_debughook_stop_reason_e breakstop_reason = N2_DEBUGHOOK_STOP_REASON_NONE;

		// オペフラグ
		uint8_t opf = 0x00;
		if (e->codeimage_->opcodeflags_)
		{
			opf = n2_u8array_peekv(e->codeimage_->opcodeflags_, N2_SCAST(int, *pc), 0x00);
		}

		// ブレークポイント張られてる？
		if (opf & N2_OPCODEFLAG_BREAKPOINT)
		{
			breakstop_reason = N2_DEBUGHOOK_STOP_REASON_BREAKPOINT;
		}

		// step等によるブレークポイント
		if (f->debugint_type_ != N2_DEBUGINT_NONE)
		{
			switch (f->debugint_type_)
			{
			case N2_DEBUGINT_PAUSE:
				f->debugint_type_ = N2_DEBUGINT_NONE;
				breakstop_reason = N2_DEBUGHOOK_STOP_REASON_PAUSE;
				break;
			case N2_DEBUGINT_NEXT:
			case N2_DEBUGINT_STEPIN:
				if (f->debugint_call_depth_ == 0)
				{
					n2_bool_t valid_step = N2_FALSE;
					switch (f->debugint_granularity_)
					{
					case N2_DEBUGINT_GRANULARITY_INSTRUCTION:
						valid_step = N2_TRUE;
						break;
					case N2_DEBUGINT_GRANULARITY_STATEMENT:
						if (opf & N2_OPCODEFLAG_STATEMENT_HEAD) { valid_step = N2_TRUE; }
						break;
					case N2_DEBUGINT_GRANULARITY_LINE:
						if (opf & N2_OPCODEFLAG_LINE_STATEMENTS_HEAD) { valid_step = N2_TRUE; }
						break;
					case N2_DEBUGINT_GRANULARITY_FUNCTION:
						valid_step = N2_FALSE;
						break;
					default:
						// STATEMENTと同じ
						if (opf & N2_OPCODEFLAG_STATEMENT_HEAD) { valid_step = N2_TRUE; }
						break;
					}
					if (valid_step && --f->debugint_granule_size_ <= 0)
					{
						f->debugint_type_ = N2_DEBUGINT_NONE;
						breakstop_reason = N2_DEBUGHOOK_STOP_REASON_STEP;
					}
				}
				break;
			default:
				break;
			}
		}

		// ブレークストップ実行
		if (breakstop_reason != N2_DEBUGHOOK_STOP_REASON_NONE && e->debughook_ && e->debughook_->breakstopfunc_)
		{
			e->debughook_->breakstopfunc_(state, e->debughook_, f, breakstop_reason);
		}

#define N2I_DEBUGGING_STEPIN() \
		do { \
			/*stepInの対応*/ \
			if (f->debugint_type_ == N2_DEBUGINT_STEPIN) \
			{ \
				if (--f->debugint_granule_size_ <= 0)/*強制的にカウントを減らす*/ \
				{ \
					f->debugint_type_ = N2_DEBUGINT_NONE; \
					if (e->debughook_ && e->debughook_->breakstopfunc_) \
					{ \
						e->debughook_->breakstopfunc_(state, e->debughook_, f, N2_DEBUGHOOK_STOP_REASON_STEP); \
					} \
				} \
			} \
		} while (0)

#define N2I_DEBUGGING_STEPOUT() \
		do { \
			/*stepOutの対応*/ \
			if (f->debugint_type_ == N2_DEBUGINT_STEPOUT) \
			{ \
				if (--f->debugint_granule_size_ <= 0)/*強制的にカウントを減らす*/ \
				{ \
					f->debugint_type_ = N2_DEBUGINT_NONE; \
					if (e->debughook_ && e->debughook_->breakstopfunc_) \
					{ \
						e->debughook_->breakstopfunc_(state, e->debughook_, f, N2_DEBUGHOOK_STOP_REASON_STEP); \
					} \
				} \
			} \
		} while (0)

#endif

		// オペレーション実行
		switch (op)
		{
		case N2_OPCODE_NOP:
			break;

		case N2_OPCODE_POP:
			{
				const n2_opcode_t num = c[*pc + 1];
				++(*pc);
				N2_ASSERT(num >= 0);
				N2_EI_ENSURE_VS_FNUM(num);
				if (num > 0)
				{
					n2_valuearray_pop(state, f->values_, N2_SCAST(size_t, num));
				}
			}
			break;

		case N2_OPCODE_PUSH_NIL:
			n2_valuearray_pushv(state, f->values_, n2_value_allocnil(state));
			break;
		case N2_OPCODE_PUSH_SINT:
			{
				n2_valint_t vali = N2_SCAST(n2_valint_t, c[*pc + 1]);
				++(*pc);
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, vali));
			}
			break;

		case N2_OPCODE_PUSH_VAL_LITERAL:
			{
				const n2_opcode_t valindex = c[*pc + 1];
				++(*pc);
				const n2_value_t* val = n2_flatvaluearray_peek(e->codeimage_->val_literals_, N2_SCAST(int, valindex));
				N2_ASSERT(val);
				n2_valuearray_pushv(state, f->values_, n2_value_clone(state, val));
			}
			break;

		case N2_OPCODE_PUSH_STRING:
			{
				const n2_opcode_t strindex = c[*pc + 1];
				++(*pc);
				const char* s = n2_plstrarray_peekv(e->codeimage_->str_literals_, N2_SCAST(int, strindex), NULL);
				N2_ASSERT(s);
				n2_str_t tstr; n2_str_init(&tstr); n2_str_set(state, &tstr, s, SIZE_MAX);
				n2_valuearray_pushv(state, f->values_, n2_value_allocs(state, &tstr));
				n2_str_teardown(state, &tstr);
			}
			break;

		case N2_OPCODE_PUSH_TEMPLATE_STRING:
			{
				const n2_opcode_t arg_num = c[*pc + 1];
				++(*pc);
				N2_ASSERT(arg_num > 0);
				N2_EI_ENSURE_VS_FNUM(arg_num);
				const int base = N2_SCAST(int, n2_valuearray_size(f->values_)) - arg_num;
				n2_value_t* basestr = n2_valuearray_peekv(f->values_, base, NULL);
				N2_ASSERT(basestr);
				if (basestr->type_ != N2_VALUE_STRING) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "テンプレート文字列の評価に失敗しました：内部エラー"); return N2_FALSE; }
				for (int i = 1; i < arg_num; ++i)
				{
					n2_value_t* argval = n2_valuearray_peekv(f->values_, base + i, NULL);
					n2_str_t* argstr = n2_value_eval_str(state, f, argval);
					n2_str_append(state, &basestr->field_.svalue_, argstr->str_, argstr->size_);
					n2_str_free(state, argstr);
				}
				n2_valuearray_pop(state, f->values_, arg_num - 1);
			}
			break;

		case N2_OPCODE_PUSH_LABEL:
			{
				const n2_opcode_t labelindex = c[*pc + 1];
				++(*pc);
				n2_valuearray_pushv(state, f->values_, n2_value_allocl(state, N2_SCAST(int, labelindex)));
			}
			break;

		case N2_OPCODE_PUSH_VARIABLE:
			{
				const n2_opcode_t varindex = c[*pc + 1];
				n2_variable_t* var = n2_vartable_peek(e->vartable_, N2_SCAST(int, varindex));
				N2_ASSERT(var);
				n2_valuearray_pushv(state, f->values_, n2_value_allocvar(state, var, -1));
				++(*pc);
			}
			break;

		case N2_OPCODE_PUSH_SYSVAR:
			switch (c[*pc + 1])
			{
			case N2_SYSVAR_HSPVER:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, state->config_.reference_hspver_));
				break;
			case N2_SYSVAR_CNT:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, f->cnt_));
				break;
			case N2_SYSVAR_STAT:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, f->stat_));
				break;
			case N2_SYSVAR_REFDVAL:
				n2_valuearray_pushv(state, f->values_, n2_value_allocf(state, f->refdval_));
				break;
			case N2_SYSVAR_REFSTR:
				{
					n2_str_t tstr; n2_str_init(&tstr); n2_str_copy_to(state, &tstr, f->refstr_);
					n2_valuearray_pushv(state, f->values_, n2_value_allocs(state, &tstr));
					n2_str_teardown(state, &tstr);
				}
				break;
			case N2_SYSVAR_STRSIZE:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, f->strsize_));
				break;
			case N2_SYSVAR_LOOPLEV:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, f->looplev_));
				break;
			case N2_SYSVAR_SUBLEV:
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, N2_SCAST(n2_valint_t, n2_callframearray_size(f->callframes_))));
				break;
			case N2_SYSVAR_NOTEMAX:
				{
					n2_valint_t size = 0;
					if (f->notevar_ && f->notevar_->type_ == N2_VALUE_STRING)
					{
						const n2_valstr_t* notestr = n2_variable_get_strc(f->notevar_, f->noteaptr_);
						if (notestr) { size = n2i_sysvar_notelinenum(notestr); }
					}
					n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, size));
				}
				break;
			case N2_SYSVAR_NOTESIZE:
				{
					n2_valint_t size = 0;
					if (f->notevar_ && f->notevar_->type_ == N2_VALUE_STRING)
					{
						const n2_valstr_t* notestr = n2_variable_get_strc(f->notevar_, f->noteaptr_);
						if (notestr) { size = N2_SCAST(n2_valint_t, n2_str_compute_size(notestr)); }
					}
					n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, size));
				}
				break;
			default:
				N2_ASSERT(0);
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, 0));
				break;
			}
			++(*pc);
			break;

		case N2_OPCODE_PUSH_SYSVAR_EX:
			{
				// 値フェッチ
				const n2_opcode_t sysvarexindex = c[*pc + 1];
				++(*pc);
				const n2_sysvar_ex_t* sysvarex = n2_sysvarexarray_peekc(e->sysvar_ex_, sysvarexindex);
				N2_ASSERT(sysvarex);
				N2_ASSERT(sysvarex->callback_);

				// コールフレーム準備
				n2_callframe_t* lcf = n2_callframearray_push(state, f->callframes_, NULL);
				n2i_callframe_init(lcf);
				n2i_execute_fill_to_callframe(state, lcf, f);
				lcf->caller_ = N2_CALLER_SYSVAR_EX;
				lcf->caller_pc_ = f->op_pc_;
				lcf->next_pc_ = *pc;

				f->callstate_.func_ = NULL;
				f->callstate_.label_ = NULL;
				f->callstate_.flags_ = 0;
				f->callstate_.base_ = N2_SCAST(int, n2_valuearray_size(f->values_));
				f->callstate_.arg_num_ = f->callstate_.original_arg_num_ = 0;

				n2i_execute_post_setup_callframe(state, lcf, f);

				// 呼び出し
				n2_funcarg_t funcarg;
				funcarg.state_ = state;
				funcarg.fiber_ = f;
				funcarg.func_ = NULL;
				funcarg.funcuser_ = sysvarex->user_;
				int res_num = sysvarex->callback_(&funcarg);

				if (res_num < 0) { n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "システム変数（%s）評価でエラーが発生しました", sysvarex->name_); return N2_FALSE; }

				// ないならnilにする
				if (res_num <= 0) { res_num = 1; n2_valuearray_pushv(state, f->values_, n2_value_allocnil(state)); }

				// 戻り値をそのまま返却
				const int top = N2_SCAST(int, n2_valuearray_size(f->values_));
				const int res_max = top - f->callstate_.base_;
				if (res_num > 1) { res_num = 1; }
				const int pop_res_num = res_max - res_num;
				N2_ASSERT(pop_res_num >= 0);
				n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, N2_SCAST(size_t, pop_res_num));

				// 即rewind
				if (!n2i_execute_rewind_to_callframe(state, f, lcf)) { return N2_FALSE; }
				n2_callframearray_pop(state, f->callframes_, 1);
			}
			break;

		case N2_OPCODE_PUSH_MODULE:
			{
				const n2_opcode_t modindex = c[*pc + 1];
				++(*pc);
				const n2_module_t* emodule = n2_moduletable_peek(e->moduletable_, modindex);
				N2_ASSERT(emodule);
				n2_module_t* crmodule = n2_moduletable_peek(e->moduletable_, e->module_core_modclass_id_);
				N2_ASSERT(crmodule);
				n2_modinstance_t* instance = n2i_modinstance_create(state, f, crmodule);
				N2_RCAST(n2i_crmodclass_instance_t*, instance)->refer_module_id_ = emodule->module_id_;
				n2_valuearray_pushv(state, f->values_, n2_value_allocmodinst(state, instance));
			}
			break;

		case N2_OPCODE_PUSH_MODULE_LOCALVAR:
			{
				const n2_opcode_t modvarindex = c[*pc + 1];
				++(*pc);
				n2_value_t* instval = n2_valuearray_peekv(f->values_, f->callstate_.base_, NULL);
				N2_ASSERT(instval);
				if (n2_value_get_type(instval) != N2_VALUE_MODINST)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "thismod がモジュール変数ではありませんでした、想定外の挙動です");
					return N2_FALSE;
				}
				n2_valmodinst_t* valmodinst = n2_value_get_modinst(instval);
				if (!valmodinst->instance_)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "thismod のモジュール変数が NULL でした。モジュールローカル変数も取得できません");
					return N2_FALSE;
				}
				n2_variable_t* modlocalvar = n2_vartable_peek(valmodinst->instance_->localvars_, N2_SCAST(int, modvarindex));
				if (!modlocalvar)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "thismod のモジュール変数に該当のモジュールローカル変数（%d-th）が存在しません", N2_SCAST(int, modvarindex));
					return N2_FALSE;
				}
				n2_valuearray_pushv(state, f->values_, n2_value_allocvar(state, modlocalvar, -1));
			}
			break;

		case N2_OPCODE_PUSH_STACK:
			{
				const n2_opcode_t stackindex = c[*pc + 1];
				N2_ASSERT(stackindex >= 0);
				n2_value_t* stackval = n2_valuearray_peekv(f->values_, f->callstate_.base_ + stackindex, NULL);
				if (!stackval)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "存在しないスタックを評価しようとしてエラーが発生しました ※gotoなどで別関数内へ移りその引数を参照した時などによく起こります");
					return N2_FALSE;
				}
				n2_valuearray_pushv(state, f->values_, n2_value_clone(state, stackval));
				++(*pc);
			}
			break;

		case N2_OPCODE_PUSH_STACK_REL:
			{
				const n2_opcode_t stackindex = c[*pc + 1];
				N2_ASSERT(stackindex < 0);
				N2_EI_ENSURE_VS_FNUM(-stackindex);
				n2_value_t* stackval = n2_valuearray_peekv(f->values_, stackindex, NULL);
				if (!stackval)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "存在しないスタックを評価しようとしてエラーが発生しました ※gotoなどで別関数内へ移りその引数を参照した時などによく起こります");
					return N2_FALSE;
				}
				n2_valuearray_pushv(state, f->values_, n2_value_clone(state, stackval));
				++(*pc);
			}
			break;

		case N2_OPCODE_STORE_STACK:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				const n2_opcode_t stackindex = c[*pc + 1];
				N2_ASSERT(stackindex >= 0);
				n2_value_t* stackval = n2_valuearray_peekv(f->values_, f->callstate_.base_ + stackindex, NULL);
				if (!stackval)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "存在しないスタックに保存しようとしてエラーが発生しました ※gotoなどで別関数内へ移りその引数を参照した時などによく起こります");
					return N2_FALSE;
				}
				n2_value_t* val = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_swap(stackval, val);
				n2_valuearray_pop(state, f->values_, 1);
				++(*pc);
			}
			break;

		case N2_OPCODE_SET_VARIABLE_APTR:
			{
				const n2_opcode_t arg_num = c[*pc + 1];
				N2_ASSERT(arg_num >= 0 && arg_num < N2_VARIABLE_DIM);
				int aptr = -1;
				if (arg_num > 0)
				{
					N2_EI_ENSURE_VS_FNUM(arg_num + 1);
					n2_value_t* varval = n2_valuearray_peekv(f->values_, -1, NULL);
					N2_ASSERT(varval);
					if (varval->type_ != N2_VALUE_VARIABLE)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数のAPTR指定時、対象が変数ではありませんでした");
						return N2_FALSE;
					}
					if (varval->field_.varvalue_.aptr_ >= 0)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数のAPTR指定時、対象の変数（%s）が配列要素指定可能な状態ではありませんでした（配列要素の配列要素は無効です）", varval->field_.varvalue_.var_->name_);
						return N2_FALSE;
					}
					N2_ASSERT(arg_num <= N2_VARIABLE_DIM);
					n2_variable_t* var = varval->field_.varvalue_.var_;
					aptr = 0;
					const int base = N2_SCAST(int, n2_valuearray_size(f->values_)) - arg_num - 1;
					for (int i = 0; i < arg_num; ++i)
					{
						const n2_value_t* valindex = n2_valuearray_peekv(f->values_, base + i, NULL);
						const n2_valint_t arg_index = n2_value_eval_int(state, f, valindex);
						if (arg_index < 0 || arg_index >= N2_SCAST(n2_valint_t, var->length_[i]))
						{
							n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "配列変数（%s）の%d次元目の添え字（%d）がその次元の最大長（%zu）を超えています", var->name_, i + 1, N2_SCAST(int, arg_index), var->length_[i]);
							return N2_FALSE;
						}
						if (i > 0) { aptr *= N2_SCAST(int, var->length_[i]); };
						aptr += N2_SCAST(int, arg_index);
					}
					n2_valuearray_pop(state, f->values_, N2_SCAST(size_t, arg_num + 1));
					n2_valuearray_pushv(state, f->values_, n2_value_allocvar(state, var, aptr));
				}
				++(*pc);
			}
			break;

		case N2_OPCODE_ASSIGN:
		case N2_OPCODE_ASSIGN_BULK:
			{
				const n2_bool_t bulk_assign = op == N2_OPCODE_ASSIGN_BULK;
				int arg_num = 1;
				if (bulk_assign)
				{
					arg_num = N2_SCAST(int, c[*pc + 1]);
					++(*pc);
				}

				N2_EI_ENSURE_VS_FNUM(1 + arg_num);

				const n2_value_t* varval = n2_valuearray_peekv(f->values_, -arg_num - 1, NULL);
				if (varval->type_ != N2_VALUE_VARIABLE)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数代入：代入先が変数ではありませんでした");
					return N2_FALSE;
				}

				const int aptr_base = N2_MAX(varval->field_.varvalue_.aptr_, 0);
				for (int i = 0; i < arg_num; ++i)
				{
					n2_value_t* rhs = n2_valuearray_peekv(f->values_, -arg_num + i, NULL);
					n2_value_isolate(state, f, rhs, N2_FALSE);
					n2_variable_set(state, f, varval->field_.varvalue_.var_, aptr_base + i, rhs);
				}

				n2_valuearray_pop(state, f->values_, N2_SCAST(size_t, arg_num + 1));
			}
			break;


		case N2_OPCODE_BOR_ASSIGN:
		case N2_OPCODE_BAND_ASSIGN:
		case N2_OPCODE_BXOR_ASSIGN:
		case N2_OPCODE_BLSHIFT_ASSIGN:
		case N2_OPCODE_BRSHIFT_ASSIGN:
		case N2_OPCODE_ADD_ASSIGN:
		case N2_OPCODE_SUB_ASSIGN:
		case N2_OPCODE_MUL_ASSIGN:
		case N2_OPCODE_DIV_ASSIGN:
		case N2_OPCODE_MOD_ASSIGN:
			{
				N2_EI_ENSURE_VS_FNUM(2);

				const n2_value_t* varval = n2_valuearray_peekv(f->values_, -2, NULL);
				if (varval->type_ != N2_VALUE_VARIABLE)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数代入：代入先が変数ではありませんでした");
					return N2_FALSE;
				}

				n2_value_t* rhs = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_isolate(state, f, rhs, N2_FALSE);

				n2_value_t* talloc = NULL;
				const n2_value_t* trhs = n2_value_eval_as(state, f, n2_value_get_type(varval), rhs, &talloc);
				if (!trhs) { return N2_FALSE; }
				switch (op)
				{
				case N2_OPCODE_BOR_ASSIGN:		n2_variable_bor(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_BAND_ASSIGN:		n2_variable_band(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_BXOR_ASSIGN:		n2_variable_bxor(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_BLSHIFT_ASSIGN:	n2_variable_blshift(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_BRSHIFT_ASSIGN:	n2_variable_brshift(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_ADD_ASSIGN:		n2_variable_add(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_SUB_ASSIGN:		n2_variable_sub(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_MUL_ASSIGN:		n2_variable_mul(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_DIV_ASSIGN:		n2_variable_div(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				case N2_OPCODE_MOD_ASSIGN:		n2_variable_mod(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, trhs); break;
				default:						N2_ASSERT(0); break;
				}
				if (talloc) { n2_value_free(state, talloc); talloc = NULL; }
				n2_valuearray_pop(state, f->values_, 2);
			}
			break;

		case N2_OPCODE_INCREMENT:
		case N2_OPCODE_DECREMENT:
			{
				N2_EI_ENSURE_VS_FNUM(1);

				const n2_value_t* varval = n2_valuearray_peekv(f->values_, -1, NULL);
				if (varval->type_ != N2_VALUE_VARIABLE)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "変数インクリメント・デクリメント：操作先が変数ではありませんでした");
					return N2_FALSE;
				}

				switch (op)
				{
				case N2_OPCODE_INCREMENT:	n2_variable_increment(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_); break;
				case N2_OPCODE_DECREMENT:	n2_variable_decrement(state, f, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_); break;
				default:					N2_ASSERT(0); break;
				}
				n2_valuearray_pop(state, f->values_, 1);
			}
			break;

		case N2_OPCODE_BOR:
		case N2_OPCODE_BAND:
		case N2_OPCODE_BXOR:
		case N2_OPCODE_EQ:
		case N2_OPCODE_NEQ:
		case N2_OPCODE_GT:
		case N2_OPCODE_GTOE:
		case N2_OPCODE_LT:
		case N2_OPCODE_LTOE:
		case N2_OPCODE_BLSHIFT:
		case N2_OPCODE_BRSHIFT:
		case N2_OPCODE_ADD:
		case N2_OPCODE_SUB:
		case N2_OPCODE_MUL:
		case N2_OPCODE_DIV:
		case N2_OPCODE_MOD:
			{
				N2_EI_ENSURE_VS_FNUM(2);
				n2_value_t* lhs = n2_valuearray_peekv(f->values_, -2, NULL);
				n2_value_t* rhs = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_isolate(state, f, lhs, N2_TRUE);

				switch (op)
				{
				case N2_OPCODE_BOR:		n2_value_bor(state, f, lhs, rhs); break;
				case N2_OPCODE_BAND:	n2_value_band(state, f, lhs, rhs); break;
				case N2_OPCODE_BXOR:	n2_value_bxor(state, f, lhs, rhs); break;
				case N2_OPCODE_EQ:		n2_value_eq(state, f, lhs, rhs); break;
				case N2_OPCODE_NEQ:		n2_value_neq(state, f, lhs, rhs); break;
				case N2_OPCODE_GT:		n2_value_gt(state, f, lhs, rhs); break;
				case N2_OPCODE_GTOE:	n2_value_gtoe(state, f, lhs, rhs); break;
				case N2_OPCODE_LT:		n2_value_lt(state, f, lhs, rhs); break;
				case N2_OPCODE_LTOE:	n2_value_ltoe(state, f, lhs, rhs); break;
				case N2_OPCODE_BLSHIFT:	n2_value_blshift(state, f, lhs, rhs); break;
				case N2_OPCODE_BRSHIFT:	n2_value_brshift(state, f, lhs, rhs); break;
				case N2_OPCODE_ADD:		n2_value_add(state, f, lhs, rhs); break;
				case N2_OPCODE_SUB:		n2_value_sub(state, f, lhs, rhs); break;
				case N2_OPCODE_MUL:		n2_value_mul(state, f, lhs, rhs); break;
				case N2_OPCODE_DIV:		n2_value_div(state, f, lhs, rhs); break;
				case N2_OPCODE_MOD:		n2_value_mod(state, f, lhs, rhs); break;
				default:				N2_ASSERT(0); break;
				}
				n2_valuearray_pop(state, f->values_, 1);
			}
			break;

		case N2_OPCODE_UNARY_NOT:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_isolate(state, f, lhs, N2_TRUE);
				n2_value_unary_not(state, f, lhs);
			}
			break;

		case N2_OPCODE_UNARY_MINUS:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_isolate(state, f, lhs, N2_TRUE);
				n2_value_unary_minus(state, f, lhs);
			}
			break;

		case N2_OPCODE_TEST_NIL:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
				const n2_bool_t is_nil = n2_value_get_type(lhs) == N2_VALUE_NIL;
				n2_value_seti(state, lhs, is_nil ? 1 : 0);
			}
			break;
		case N2_OPCODE_TEST_ORIGINAL_ARG_NUM:
			{
				const n2_opcode_t stackindex = c[*pc + 1];
				++(*pc);
				const n2_bool_t test_result = f->callstate_.original_arg_num_ > stackindex;
				n2_valuearray_pushv(state, f->values_, n2_value_alloci(state, test_result ? 1 : 0));
			}
			break;

		case N2_OPCODE_IF:
		case N2_OPCODE_IFNOT:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				const n2_value_t* cond = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_bool_t is_cond = n2_value_eval_bool(state, f, cond);
				if (op == N2_OPCODE_IFNOT) { is_cond = !is_cond; }
				n2_valuearray_pop(state, f->values_, 1);
				if (is_cond)
				{
					++(*pc);
				}
				else
				{
					*pc += c[*pc + 1] - 1;
				}
			}
			break;

		case N2_OPCODE_REPEAT:
		case N2_OPCODE_FOREACH:
			{
				N2_EI_ENSURE_VS_FNUM(1);

				const n2_bool_t is_foreach = op == N2_OPCODE_FOREACH;

				if (state->config_.max_shortframe_nest_ > 0 && n2_shortframearray_size(f->shortframes_) >= state->config_.max_shortframe_nest_)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "repeat-loopのネストサイズが最大（%zu）を超えました", state->config_.max_shortframe_nest_);
					return N2_FALSE;
				}

				const n2_opcode_t end_pc = c[*pc + 1];
				++(*pc);

				n2_shortframe_t* llf = n2_shortframearray_push(state, f->shortframes_, NULL);
				llf->type_ = N2_SHORTFRAME_LOOP;
				llf->start_pc_ = *pc + 1;
				llf->end_pc_ = end_pc;
				llf->content_.loop_.cnt_ = 0;
				llf->content_.loop_.counter_ = 0;
				llf->content_.loop_.max_ = 0;
				llf->content_.loop_.foreach_capture_ = NULL;
				++f->looplev_;

				const n2_value_t* loop_num_val = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_valint_t loop_num = 0;
				if (is_foreach)
				{
					if (loop_num_val->type_ != N2_VALUE_VARIABLE)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "foreachの対象が変数ではありません");
						return N2_FALSE;
					}
					loop_num = N2_SCAST(n2_valint_t, loop_num_val->field_.varvalue_.var_->length_[0]);
					llf->content_.loop_.foreach_capture_ = loop_num_val->field_.varvalue_.var_->type_ == N2_VALUE_MODINST ? loop_num_val->field_.varvalue_.var_ : NULL;// モジュール変数ならこの変数をキャプチャ @todo このコードちょっと雑すぎるな
				}
				else
				{
					loop_num = n2_value_eval_int(state, f, loop_num_val);
				}

				n2_valuearray_pop(state, f->values_, 1);
				llf->content_.loop_.max_ = loop_num;
			}
			break;
		case N2_OPCODE_REPEAT_CHECK:
			{
				N2_ASSERT(n2_shortframearray_size(f->shortframes_) > 0);
				n2_shortframe_t* llf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_LOOP);
				if (!llf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "repeat：repeat-loopの中にありません");
					return N2_FALSE;
				}

				// foreachの場合
				if (llf->content_.loop_.foreach_capture_)
				{
					// カレントの変数が生きているかをチェック
					n2_variable_t* var = llf->content_.loop_.foreach_capture_;
					if (var->type_ != N2_VALUE_MODINST)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "foreach：foreach中に対象の変数（%s）の型がモジュール変数から変更されました", var->name_);
						return N2_FALSE;
					}

					while (llf->content_.loop_.counter_ < llf->content_.loop_.max_)
					{
						n2_valmodinst_t* modinst = n2_variable_get_modinst(var, N2_SCAST(int, llf->content_.loop_.counter_));
						if (modinst && modinst->instance_) { break; }
						++llf->content_.loop_.counter_;
						++llf->content_.loop_.cnt_;
					}
				}

				// ここでシステム変数を同期
				f->cnt_ = llf->content_.loop_.cnt_;

				// 終了することもある
				if (llf->content_.loop_.max_ >= 0 && llf->content_.loop_.counter_ >= llf->content_.loop_.max_)
				{
					*pc = llf->end_pc_;
					n2i_fiber_shortframearray_pop_to(state, f, llf);

					n2i_fiber_sync_shortframes(f);
				}
			}
			break;

		case N2_OPCODE_LOOP:
		case N2_OPCODE_CONTINUE:
			{
				n2_shortframe_t* llf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_LOOP);
				if (!llf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "loop, continue：repeat-loopの中にありません");
					return N2_FALSE;
				}
				if (n2_callframearray_size(f->callframes_) > 0)
				{
					const n2_callframe_t* lcf = n2_callframearray_peekc(f->callframes_, -1);
					const int llfindex = n2_shortframearray_compute_index(f->shortframes_, llf);
					N2_ASSERT(llfindex >= 0);
					if (N2_SCAST(size_t, llfindex) < lcf->shortframe_cursor_)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "loop, continue：gosub/関数コールなどで外部から呼び出された際にloop/continueしようとしました");
						return N2_FALSE;
					}
				}

				++llf->content_.loop_.counter_;
				++llf->content_.loop_.cnt_;
				*pc = llf->start_pc_ - 1;
			}
			break;
		case N2_OPCODE_BREAK:
			{
				n2_shortframe_t* llf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_LOOP);
				if (!llf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "break：repeat-loopの中にありません");
					return N2_FALSE;
				}
				if (n2_callframearray_size(f->callframes_) > 0)
				{
					const n2_callframe_t* lcf = n2_callframearray_peekc(f->callframes_, -1);
					const int llfindex = n2_shortframearray_compute_index(f->shortframes_, llf);
					N2_ASSERT(llfindex >= 0);
					if (N2_SCAST(size_t, llfindex) < lcf->shortframe_cursor_)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "loop, continue：gosub/関数コールなどで外部から呼び出された際にbreakしようとしました");
						return N2_FALSE;
					}
				}

				*pc = llf->end_pc_;
				n2i_fiber_shortframearray_pop_to(state, f, llf);
			}
			break;

		case N2_OPCODE_SWITCH:
			{
				N2_EI_ENSURE_VS_FNUM(1);

				if (state->config_.max_shortframe_nest_ > 0 && n2_shortframearray_size(f->shortframes_) >= state->config_.max_shortframe_nest_)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "switch-swendのネストサイズが最大（%zu）を超えました", state->config_.max_shortframe_nest_);
					return N2_FALSE;
				}

				// 今のうちに孤立化させておく
				n2_value_t* lhs = n2_valuearray_peekv(f->values_, -1, NULL);
				n2_value_isolate(state, f, lhs, N2_TRUE);

				const n2_opcode_t end_pc = c[*pc + 1];
				++(*pc);

				n2_shortframe_t* lsf = n2_shortframearray_push(state, f->shortframes_, NULL);
				lsf->type_ = N2_SHORTFRAME_SWITCH;
				lsf->start_pc_ = *pc + 1;
				lsf->end_pc_ = end_pc;
				lsf->content_.switch_.case_hit_ = N2_FALSE;
			}
			break;
		case N2_OPCODE_SWCASE:
			{
				N2_EI_ENSURE_VS_FNUM(2);// value for switch + value for case

				n2_shortframe_t* lsf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_SWITCH);
				if (!lsf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "case：switch-swendの中にありません");
					return N2_FALSE;
				}

				const n2_opcode_t end_case_pc = c[*pc + 1];
				++(*pc);

				if (!lsf->content_.switch_.case_hit_)
				{
					n2_value_t* lhs = n2_valuearray_peekv(f->values_, -2, NULL);
					n2_value_t* rhs = n2_valuearray_peekv(f->values_, -1, NULL);
					n2_value_t* lhsmut = n2_value_clone(state, lhs);

					if (!n2_value_eq(state, f, lhsmut, rhs)) { return N2_FALSE; }
					N2_ASSERT(lhsmut->type_ == N2_VALUE_INT);
					if (lhsmut->field_.ivalue_) { lsf->content_.switch_.case_hit_ = N2_TRUE; }
					n2_value_free(state, lhsmut);
				}

				if (!lsf->content_.switch_.case_hit_)
				{
					// ヒットしてないなら次のcaseへ
					*pc = end_case_pc - 1;
				}

				n2_valuearray_pop(state, f->values_, 1);// value for case
			}
			break;
		case N2_OPCODE_SWDEFAULT:
			{
				N2_EI_ENSURE_VS_FNUM(1);// value for switch

				n2_shortframe_t* lsf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_SWITCH);
				if (!lsf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "default：switch-swendの中にありません");
					return N2_FALSE;
				}
				// do nothing
			}
			break;

		case N2_OPCODE_SWBREAK:
			{
				N2_EI_ENSURE_VS_FNUM(1);// value for switch

				n2_shortframe_t* lsf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_SWITCH);
				if (!lsf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "swbreak：switch-swendの中にありません");
					return N2_FALSE;
				}

				*pc = lsf->end_pc_ - 1;
			}
			break;
		case N2_OPCODE_SWEND:
			{
				N2_EI_ENSURE_VS_FNUM(1);// value for switch

				n2_shortframe_t* lsf = n2_shortframearray_find_last_typed(f->shortframes_, N2_SHORTFRAME_SWITCH);
				if (!lsf)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "swend：switch-swendの中にありません");
					return N2_FALSE;
				}
				if (n2_callframearray_size(f->callframes_) > 0)
				{
					const n2_callframe_t* lcf = n2_callframearray_peekc(f->callframes_, -1);
					const int lsfindex = n2_shortframearray_compute_index(f->shortframes_, lsf);
					N2_ASSERT(lsfindex >= 0);
					if (N2_SCAST(size_t, lsfindex) < lcf->shortframe_cursor_)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "swend：gosub/関数コールなどで外部から呼び出された際にswendしようとしました");
						return N2_FALSE;
					}
				}

				n2i_fiber_shortframearray_pop_to(state, f, lsf);

				n2i_fiber_sync_shortframes(f);

				// pop value for switch
				n2_valuearray_pop(state, f->values_, 1);
			}
			break;

		case N2_OPCODE_MODULE:
			{
				//const n2_opcode_t modindex = c[*pc + 1];
				const n2_opcode_t offset = c[*pc + 2];
				*pc += N2_SCAST(n2_pc_t, offset - 1);
			}
			break;
		case N2_OPCODE_GLOBAL:
			{
				const n2_opcode_t modindex = c[*pc + 1];
				++(*pc);
				const n2_module_t* emodule = n2_moduletable_peek(e->moduletable_, modindex);
				N2_ASSERT(emodule);
				n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "モジュール（%s）の終了（#global）に到達しました。このままモジュール外へ処理を継続できません ※直前の関数の return が実行されていない時によく起こります", emodule->name_);
				return N2_FALSE;
			}
			break;

		case N2_OPCODE_DEFFUNC:
			{
				const n2_opcode_t funcindex = c[*pc + 1];
				++(*pc);
				const n2_func_t* func = n2_functable_peek(e->functable_, N2_SCAST(int, funcindex));
				N2_ASSERT(func);
				n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の定義に到達しました。関数呼び出し以外で関数内部を実行することはできません ※直前の関数の return が実行されていない時によく起こります", func->name_);
				return N2_FALSE;
			}
			break;
		case N2_OPCODE_ENTER_FUNCTION:
			{
				const n2_opcode_t funcindex = c[*pc + 1];
				++(*pc);
				const n2_func_t* func = n2_functable_peek(e->functable_, N2_SCAST(int, funcindex));
				N2_ASSERT(func);
				if (func->func_ != N2_FUNC_SCRIPT)
				{
					// なることはないと思うが
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）がスクリプトで定義後、外部から再度定義されています。この状態でのスクリプトの関数実行はできません", func->name_);
					return N2_FALSE;
				}
				// 変数領域を確保
				if (!f->curscope_local_vars_) { f->curscope_local_vars_ = n2_vararray_alloc(state, 0, 4); }
				// arityチェック
				const int arg_num = f->callstate_.original_arg_num_;
				const int func_arity = N2_SCAST(int, n2_funcparamarray_size(func->params_));
				if (arg_num > func_arity)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）呼び出しの引数の数（%d）が想定（%d）より多いです", func->name_, arg_num, func_arity);
					return N2_FALSE;
				}
				// modfunc系？
				const n2_module_t* funcmod = NULL;
				if (func->module_id_ >= 0)
				{
					//funcmod = n2_modulearray_peek(e->functable_->funcarray_, func->module_id_);
					//N2_ASSERT(funcmod);
				}
				// type/omitチェック
				for (int i = 0; i < func_arity; ++i)
				{
					const n2_func_param_t* func_param = n2_funcparamarray_peekc(func->params_, i);
					N2_ASSERT(func_param);
					n2_value_t* arg_val = n2_valuearray_peekv(f->values_, f->callstate_.base_ + i, NULL);
					const n2_bool_t arg_omitted = !arg_val || arg_val->type_ == N2_VALUE_NIL;
					if (!func_param->omittable_ && arg_omitted)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）は省略できません", func->name_, i, func_param->name_);
						return N2_FALSE;
					}
					if (arg_omitted)
					{
						// そもそも引数として渡ってきてないなら生成する
						if (!arg_val)
						{
							switch (func_param->type_)
							{
								// 変数新規確保
							case N2_FUNC_PARAM_LOCAL:
								{
									n2_variable_t* var = n2_variable_alloc(state, f->environment_, func_param->name_);
									n2_vararray_pushv(state, f->curscope_local_vars_, var);
									n2_valuearray_pushv(state, f->values_, n2_value_allocvar(state, var, -1));
								}
								break;
							default:
								// nil を入れる
								n2_valuearray_pushv(state, f->values_, n2_value_allocnil(state));
								break;
							}

							// こっそり足す
							++f->callstate_.arg_num_;
						}
					}
					else
					{
						switch (func_param->type_)
						{
							// 自動変換
						case N2_FUNC_PARAM_INT:
							n2_value_seti(state, arg_val, n2_value_eval_int(state, f, arg_val));
							break;
						case N2_FUNC_PARAM_FLOAT:
							n2_value_setf(state, arg_val, n2_value_eval_float(state, f, arg_val));
							break;
							// 自動変換しない
						case N2_FUNC_PARAM_STR:
							if (n2_value_get_type(arg_val) != N2_VALUE_STRING)
							{
								n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）が文字列型ではありません", func->name_, i, func_param->name_);
								return N2_FALSE;
							}
							n2_value_isolate(state, f, arg_val, N2_TRUE);
							break;
						case N2_FUNC_PARAM_LABEL:
							if (n2_value_get_type(arg_val) != N2_VALUE_LABEL)
							{
								n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）がラベル型ではありません", func->name_, i, func_param->name_);
								return N2_FALSE;
							}
							n2_value_isolate(state, f, arg_val, N2_TRUE);
							break;
							// 変数束縛
						case N2_FUNC_PARAM_VAR:
						case N2_FUNC_PARAM_ARRAY:
							if (arg_val->type_ != N2_VALUE_VARIABLE)
							{
								n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）が変数ではありません", func->name_, i, func_param->name_);
								return N2_FALSE;
							}
							if (func_param->type_ == N2_FUNC_PARAM_ARRAY && arg_val->field_.varvalue_.aptr_ >= 0)
							{
								n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）がarrayを期待しましたが変数の1要素が渡されました", func->name_, i, func_param->name_);
								return N2_FALSE;
							}
							break;
							// 別途変数確保
						case N2_FUNC_PARAM_LOCAL:
							{
								n2_variable_t* var = n2_variable_alloc(state, f->environment_, func_param->name_);
								n2_vararray_pushv(state, f->curscope_local_vars_, var);
								if (!n2_variable_set(state, f, var, -1, arg_val)) { return N2_FALSE; }
								n2_value_setvar(state, arg_val, var, -1);
							}
							break;
							// チェック
						case N2_FUNC_PARAM_MODVAR:
							{
								n2_value_isolate(state, f, arg_val, N2_TRUE);
								if (arg_val->type_ != N2_VALUE_MODINST)
								{
									n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）がモジュール変数型ではありませんでした", func->name_, i, func_param->name_);
									return N2_FALSE;
								}
								n2_valmodinst_t* modinst = n2_value_get_modinst(arg_val);
								if (!modinst->instance_)
								{
									n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）の引数（%d＝%s）のモジュール変数がNULLでした。既にdelmod等で削除されています", func->name_, i, func_param->name_);
									return N2_FALSE;
								}

								// modfunc系ならチェック
								if (i == 0 && funcmod)
								{
									if (modinst->instance_->module_id_ != funcmod->module_id_)
									{
										n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）のthismodのモジュール変数が異なるモジュールで作られたものです", func->name_);
										return N2_FALSE;
									}
								}
							}
							break;
						default:
							N2_ASSERT(0);
							n2_value_seti(state, arg_val, n2_value_eval_int(state, f, arg_val));// intにしておく
							break;
						}
					}
				}

#if N2_CONFIG_USE_DEBUGGING
				++f->debugint_call_depth_;
				N2I_DEBUGGING_STEPIN();
#endif
			}
			break;

		case N2_OPCODE_LABEL:
			++(*pc);
			break;

		case N2_OPCODE_GOSUB:
		case N2_OPCODE_GOTO:
			{
				N2_EI_ENSURE_VS_FNUM(1);
				const n2_value_t* labelval = n2_valuearray_peekv(f->values_, -1, NULL);
				if (n2_value_get_type(labelval) != N2_VALUE_LABEL)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "goto/gosubで対象がラベルではありません");
					return N2_FALSE;
				}
				const n2_vallabel_t* vallabel = n2_value_get_label(labelval);
				N2_ASSERT(vallabel);

				const int labelindex = vallabel->label_index_;
				const n2_label_t* label = n2_labelarray_peek(e->labels_, labelindex);
				N2_ASSERT(label);

				if (label->pc_ < 0)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "goto/gosubの対象ラベル（*%s）がまだ定義されていません", label->name_);
					return N2_FALSE;
				}

				// 取得したのでもういらない
				n2_valuearray_pop(state, f->values_, 1);

				// 実際に飛ぶ処理
				if (op == N2_OPCODE_GOSUB)
				{
					if (state->config_.max_call_nest_ > 0 && n2_callframearray_size(f->callframes_) >= state->config_.max_call_nest_)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "gosub/関数呼び出しのネストサイズが最大（%zu）を超えました", state->config_.max_call_nest_);
						return N2_FALSE;
					}

					// gosubならコールスタック積む
					n2_callframe_t* lcf = n2_callframearray_push(state, f->callframes_, NULL);
					n2i_callframe_init(lcf);
					n2i_execute_fill_to_callframe(state, lcf, f);
					lcf->caller_ = N2_CALLER_GOSUB;
					lcf->caller_pc_ = f->op_pc_;
					lcf->next_pc_ = f->op_pc_ + 1 - 1;

					f->callstate_.func_ = NULL;
					f->callstate_.label_ = label;
					f->callstate_.flags_ = 0;
					f->callstate_.base_ = N2_SCAST(int, n2_valuearray_size(f->values_));
					f->callstate_.arg_num_ = f->callstate_.original_arg_num_ = 0;

					n2i_execute_post_setup_callframe(state, lcf, f);

					*pc = label->pc_ - 1;
				}
				else
				{
					// gotoなら直接ジャンプ
					*pc = label->pc_ - 1;
				}
			}
			break;

		case N2_OPCODE_COMMAND:
		case N2_OPCODE_FUNCTION:
			{
				const n2_bool_t is_command = (op == N2_OPCODE_COMMAND);

				if (state->config_.max_call_nest_ > 0 && n2_callframearray_size(f->callframes_) >= state->config_.max_call_nest_)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "goto/gosub/コマンド/関数呼び出しのネストサイズが最大（%zu）を超えました", state->config_.max_call_nest_);
					return N2_FALSE;
				}

				const n2_opcode_t funcindex = c[*pc + 1];
				const n2_opcode_t arg_num_flags = c[*pc + 2];
				const int arg_num = N2_SCAST(int, arg_num_flags & 0xffff);
				const size_t exflags = N2_SCAST(size_t, (arg_num_flags >> 16) & 0xffff);

				// コマンド/関数呼び出し
				const n2_func_t* original_func = n2_functable_peek(e->functable_, funcindex);
				N2_ASSERT(original_func);
				const n2_func_t* func = original_func;

				// エイリアス解決
				for (size_t i = 0; i < N2_MAX_FUNC_ALIAS_LOOP; ++i)
				{
					if (func->func_ != N2_FUNC_ALIAS) { break; }
					func = func->alias_func_;
				}
				if (func->func_ == N2_FUNC_ALIAS)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）呼び出しのエイリアスを解決しようとしましたが、エイリアスが深すぎます", original_func->name_);
					return N2_FALSE;
				}

				// コールフレーム準備
				N2_EI_ENSURE_VS_FNUM(arg_num);
				n2_callframe_t* lcf = n2_callframearray_push(state, f->callframes_, NULL);
				n2i_callframe_init(lcf);
				n2i_execute_fill_to_callframe(state, lcf, f);
				lcf->caller_ = (is_command ? N2_CALLER_COMMAND : N2_CALLER_FUNCTION);
				lcf->caller_pc_ = f->op_pc_;
				lcf->next_pc_ = *pc + 2;

				f->callstate_.func_ = original_func;
				f->callstate_.label_ = NULL;
				f->callstate_.flags_ = exflags;
				f->callstate_.base_ = N2_SCAST(int, n2_valuearray_size(f->values_)) - N2_SCAST(int, arg_num);
				f->callstate_.arg_num_ = f->callstate_.original_arg_num_ = N2_SCAST(int, arg_num);

				n2i_execute_post_setup_callframe(state, lcf, f);

				int res_num = 0;
				switch (func->func_)
				{
				case N2_FUNC_INTERNAL:
				case N2_FUNC_EXTERNAL:
				case N2_FUNC_DLFUNC:
					{
						if (!func->callback_)
						{
							n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）を呼び出そうとしましたがまだ定義されていません", func->name_);
							return N2_FALSE;
						}
						// 外部関数呼び出し用の処理
						f->op_pc_ = -1;// 実行されているPCをクリア（コールスタックのみでる）

						// funcargの準備
						n2_funcarg_t funcarg;
						funcarg.state_ = state;
						funcarg.fiber_ = f;
						funcarg.func_ = func;
						funcarg.funcuser_ = func->user_;

						// 呼び出し
						res_num = func->callback_(&funcarg);
					}
					break;
				case N2_FUNC_SCRIPT:
					if (func->pc_ < 0)
					{
						n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）を呼び出そうとしましたがまだ定義されていません", func->name_);
						return N2_FALSE;
					}
					*pc = func->pc_;
					continue;// 次の命令へ
				default:
					N2_ASSERT(0);
					return N2_FALSE;
				}

				if (res_num < 0)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）呼び出しでエラーが発生しました", func->name_);
					return N2_FALSE;
				}

				// 戻り値保証
				if (!is_command && res_num <= 0)
				{
					/*戻り値がないならnilにする*/
					res_num = 1;
					n2_valuearray_pushv(state, f->values_, n2_value_allocnil(state));
				}

				const int top = N2_SCAST(int, n2_valuearray_size(f->values_));
				const int res_max = top - f->callstate_.base_;
				if (res_num > res_max) { res_num = res_max; }

				if (is_command)
				{
					if (res_num > 0)
					{
						// 戻り値をシステム変数へ
						n2_value_t* resval = n2_valuearray_peekv(f->values_, -1, NULL);
						n2i_execute_substitute_to_sysvar(state, f, resval);
					}
					// あとは全てポップ
					n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, res_max);
					N2_ASSERT(N2_SCAST(int, n2_valuearray_size(f->values_)) == f->callstate_.base_);
				}
				else
				{
					// 戻り値をそのまま返却
					if (res_num > 1) { res_num = 1;/*@todo 戻り値の数は最大一つ*/ }
					const int pop_res_num = res_max - res_num;
					N2_ASSERT(pop_res_num >= 0);
					n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, N2_SCAST(size_t, pop_res_num));
				}

				// 即rewind
				if (!n2i_execute_rewind_to_callframe(state, f, lcf)) { return N2_FALSE; }
				n2_callframearray_pop(state, f->callframes_, 1);
			}
			break;

		case N2_OPCODE_JUMP:
			*pc = c[*pc + 1] - 1;
			break;
		case N2_OPCODE_JUMP_RELATIVE:
			*pc += c[*pc + 1] - 1;
			break;
		case N2_OPCODE_RETURN:
			{
				if (n2_callframearray_size(f->callframes_) <= 0)
				{
					n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "サブルーチン外からのreturnは無効です");
					return N2_FALSE;
				}

				n2_callframe_t* lcf = n2_callframearray_peek(f->callframes_, -1);

				n2_opcode_t res_num = c[*pc + 1];
				if (res_num > 0)
				{
					// 戻り値は一つに限定
					N2_ASSERT(res_num <= 1);

					if (lcf->caller_ == N2_CALLER_GOSUB || lcf->caller_ == N2_CALLER_COMMAND)
					{
						// システム変数へ
						n2_value_t* resval = n2_valuearray_peekv(f->values_, -1, NULL);
						n2i_execute_substitute_to_sysvar(state, f, resval);
						// 全部ポップ
						const int pop_num = N2_SCAST(int, n2_valuearray_size(f->values_)) - f->callstate_.base_;
						n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, N2_SCAST(size_t, pop_num));
					}
					else
					{
						// 一つだけ残して戻す
						const int pop_num = N2_SCAST(int, n2_valuearray_size(f->values_)) - f->callstate_.base_ - 1/*res_num*/;
						n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, N2_SCAST(size_t, pop_num));
						// isolateする（戻り値がローカル変数だった時用）
						n2_value_t* resval = n2_valuearray_peekv(f->values_, -1, NULL);
						n2_value_isolate(state, f, resval, N2_FALSE);
					}

					res_num = 1;
				}

				const n2_bool_t is_external = (lcf->caller_ == N2_CALLER_EXTERNAL);

				if (!n2i_execute_rewind_to_callframe(state, f, lcf)) { return N2_FALSE; }
				n2_callframearray_pop(state, f->callframes_, 1);

				if (is_external) { return N2_TRUE; }

#if N2_CONFIG_USE_DEBUGGING
				--f->debugint_call_depth_;
				N2I_DEBUGGING_STEPOUT();
#endif
			}
			break;

		case N2_OPCODE_END:
			f->fiber_state_ = N2_FIBER_STATE_END;
			break;

		default:
			N2_ASSERT(0);
			break;
		}

		++(*pc);
	}

	return N2_TRUE;
}

static n2_bool_t n2i_state_execute_startup(n2_state_t* state)
{
	// 全体のスタートアップ処理
	n2_environment_t* e = state->environment_;

	// uselib
	if (e->uselibs_dirty_)
	{
		for (size_t li = 0, ll = n2_uselibarray_size(e->uselibs_); li < ll; ++li)
		{
			n2_uselib_t* uselib = n2_uselibarray_peek(e->uselibs_, N2_SCAST(int, li));
			if (!uselib->dynlib_)
			{
				if (!n2h_dynlib_supported())
				{
					n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "動的ライブラリ（%s）の読み込みに失敗しました：動的ライブラリがサポートされてないプラットフォームです", uselib->path_);
					return N2_FALSE;
				}
				uselib->dynlib_ = n2h_dynlib_alloc(state, uselib->path_, SIZE_MAX);
				if (!uselib->dynlib_)
				{
					n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "動的ライブラリ（%s）の読み込みに失敗しました", uselib->path_);
					return N2_FALSE;
				}
			}

			for (size_t fi = 0, fl = n2_intarray_size(&uselib->func_indices_); fi < fl; ++fi)
			{
				const int funcindex = n2_intarray_peekv(&uselib->func_indices_, N2_SCAST(int, fi), -1);
				n2_func_t* func = funcindex >= 0 ? n2_functable_peek(e->functable_, funcindex) : NULL;
				if (!func || func->func_ != N2_FUNC_DLFUNC) { continue; }
				if (func->libproc_) { continue; }
				func->libproc_ = n2h_dynlib_find_function(state, uselib->dynlib_, func->libprocname_.str_);
				func->lib_ = uselib->dynlib_;
				func->callback_ = n2i_execute_dynlib_call;
				// 読み込み失敗はここではノーカウント
			}
		}

		e->uselibs_dirty_ = N2_FALSE;
	}

	// standard
	if (e->is_standards_bounded_)
	{
		if (!e->standard_environment_)
		{
			const char* pe = NULL;
			e->standard_environment_ = n2si_environment_alloc(state, &pe);
			if (!e->standard_environment_)
			{
				n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "バックエンドの初期化に失敗しました。OpenGL ES3が対応してないなど、動作要件を満たしていません。（%s）", pe ? pe : "不明なエラー");
				return N2_FALSE;
			}
		}
	}

	return N2_TRUE;
}

static void n2i_state_execute_fiber_startup(n2_state_t* state, n2_fiber_t* f)
{
	N2_UNUSE(state);

	// ファイバー毎
	f->pc_ = 0;
	f->op_pc_ = 0;
}

static n2_bool_t n2i_state_execute_protected(n2_state_t* state, n2_fiber_t* f)
{
	n2_environment_t* e = state->environment_;

	if (n2_opcodearray_size(e->codeimage_->opcodes_) <= 0)
	{
		n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "実行できるコードが読み込まれていません");
		return N2_FALSE;
	}

	// @todo 毎回は要らないが重い処理でもないのでそのまま、そのうちキャッシュ
	if (!n2i_state_execute_startup(state))
	{
		n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "実行のスタートアップに失敗");
		return N2_FALSE;
	}

	switch (f->fiber_state_)
	{
	case N2_FIBER_STATE_INITIALIZED:
		n2i_state_execute_fiber_startup(state, f);
	case N2_FIBER_STATE_YIELD:
	case N2_FIBER_STATE_YIELD_AWAIT:
		f->fiber_state_ = N2_FIBER_STATE_RUNNING;
		break;
	case N2_FIBER_STATE_RUNNING:
		break;
	default:
		n2i_raise_as(state, N2_ERROR_RUNTIME, NULL, NULL, NULL, -1, "既に実行が終了しているか、エラーになっています");
		return N2_FALSE;
	}

	if (!n2i_execute_inner(state, f))
	{
		f->fiber_state_ = N2_FIBER_STATE_ERROR;
		return N2_FALSE;
	}

	return N2_TRUE;
}

N2_API n2_fiber_t* n2_state_find_fiber(n2_state_t* state, int fiber_id)
{
	// @todo multi fiber
	{
		if (state->main_fiber_ && state->main_fiber_->id_ == fiber_id) { return state->main_fiber_; }
	}
	return NULL;
}

N2_API n2_bool_t n2_state_execute_fiber(n2_state_t* state, n2_fiber_t* f)
{
	N2_PROTECT_ENTER(protectframe, f);

	n2_bool_t res = N2_FALSE;
	if (N2_PROTECT_DISPATCH(protectframe, f))
	{
		f->fiber_state_ = N2_FIBER_STATE_ERROR;
		res = N2_FALSE;
	}
	else
	{
		res = n2i_state_execute_protected(state, f);
	}

	N2_PROTECT_LEAVE(protectframe, f);
	return res;
}

N2_API n2_bool_t n2_state_execute(n2_state_t* state)
{
	n2_fiber_t* f = state->main_fiber_;
	return n2_state_execute_fiber(state, f);
}

N2_API n2_bool_t n2_state_loop_frame(n2_state_t* state)
{
	n2s_environment_t* se = state->environment_->standard_environment_;
	if (!se) { return N2_FALSE; }

	n2_bool_t res = N2_TRUE;

	n2si_environment_frame_update(state, se);

	if (se->is_quit_requested_)
	{
		res = N2_FALSE;
	}

	return res;
}

N2_API n2_bool_t n2_state_is_quit_requested(const n2_state_t* state)
{
	if (state->environment_)
	{
		n2s_environment_t* se = state->environment_->standard_environment_;
		if (se && se->is_quit_requested_) { return N2_TRUE; }
	}
	return N2_FALSE;
}

N2_API void n2_state_set_filesystem(n2_state_t* state, n2h_filesystem_t* fs)
{
	if (state->filesystem_) { n2h_filesystem_free(state, state->filesystem_); }
	state->filesystem_ = fs;
}

N2_API n2h_filesystem_t* n2_state_get_filesystem(n2_state_t* state)
{
	return state->filesystem_;
}

N2_API n2_bool_t n2_state_fs_load(n2_state_t* state, n2_buffer_t* dst, size_t fsflags, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset)
{
	if ((fsflags & N2_STATE_FSFLAG_USE_PRIMARY_FS) && state->filesystem_) { if (n2h_filesystem_load(state, state->filesystem_, dst, filepath, is_binary, readsize, readoffset)) { return N2_TRUE; } }
	if ((fsflags & N2_STATE_FSFLAG_USE_SYSTEM_FS) && state->filesystem_system_) { if (n2h_filesystem_load(state, state->filesystem_system_, dst, filepath, is_binary, readsize, readoffset)) { return N2_TRUE; } }
	return N2_FALSE;
}

N2_API n2_bool_t n2_state_fs_load_str(n2_state_t* state, n2_str_t* dst, size_t fsflags, const char* filepath, size_t readsize, size_t readoffset)
{
	n2_buffer_t buf;
	n2_buffer_init(&buf);
	if (!n2_state_fs_load(state, &buf, fsflags, filepath, N2_FALSE, readsize, readoffset))
	{
		n2_buffer_teardown(state, &buf);
		return N2_FALSE;
	}
	n2_str_buffer_mutate(dst, &buf);
	n2_buffer_teardown(state, &buf);
	return N2_TRUE;
}

N2_API n2_bool_t n2_state_fs_save(n2_state_t* state, size_t* dst_writtensize, size_t fsflags, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset)
{
	if ((fsflags & N2_STATE_FSFLAG_USE_PRIMARY_FS) && state->filesystem_) { if (n2h_filesystem_save(state, state->filesystem_, dst_writtensize, filepath, is_binary, writedata, writesize, writeoffset)) { return N2_TRUE; } }
	if ((fsflags & N2_STATE_FSFLAG_USE_SYSTEM_FS) && state->filesystem_system_) { if (n2h_filesystem_save(state, state->filesystem_system_, dst_writtensize, filepath, is_binary, writedata, writesize, writeoffset)) { return N2_TRUE; } }
	return N2_FALSE;
}

N2_API n2_bool_t n2_state_export_as_script(n2_state_t* state, n2_str_t* dst)
{
	n2_str_clear(dst);
	if (!state->environment_ || !state->environment_->codeimage_) { return N2_FALSE; }
	const n2_sourcecodearray_t* sourcecodes = state->environment_->codeimage_->sourcecodes_;
	if (!sourcecodes || n2_sourcecodearray_size(sourcecodes) <= 0) { return N2_FALSE; }
	for (size_t i = 0, l = n2_sourcecodearray_size(sourcecodes); i < l; ++i)
	{
		if (i > 0) { n2_str_append(state, dst, "\n", SIZE_MAX); }
		const n2_sourcecode_t* sourcecode = n2_sourcecodearray_peekcv(sourcecodes, N2_SCAST(int, i), NULL);
		N2_ASSERT(sourcecode);
		n2_str_append(state, dst, sourcecode->src_ppscript_.str_, SIZE_MAX);
	}
	return N2_TRUE;
}

// あまりにも特殊なので位置的にここに定義する
static n2_bool_t n2si_environment_update_widget_dirty(n2_state_t* state, n2_fiber_t* f, n2s_window_t* w)
{
	if (!w) { return N2_FALSE; }
	if (!w->widgets_) { return N2_TRUE; }

	N2_PROTECT_ENTER(protectframe, f);

	const n2_fiber_state_e prev_fiber_state = f->fiber_state_;

	n2_bool_t res = N2_FALSE;
	if (N2_PROTECT_DISPATCH(protectframe, f))
	{
		f->fiber_state_ = N2_FIBER_STATE_ERROR;
		res = N2_FALSE;
	}
	else
	{
		for (size_t wi = 0, wl = n2s_widgetset_size(w->widgets_); wi < wl; ++wi)
		{
			n2s_widget_t* widget = n2s_widgetset_peek(w->widgets_, N2_SCAST(int, wi));
			if (!widget) { continue; }// ウィジェット処理の副作用があるので、チェック

			switch (widget->type_)
			{
			case N2S_WIDGET_BUTTON:
				while (widget->value_dirty_count_ > 0)
				{
					if (widget->lvalue_.label_index_ >= 0)
					{
						const int labelindex = widget->lvalue_.label_index_;
						const n2_label_t* label = n2_labelarray_peek(f->environment_->labels_, labelindex);

						if (!label || label->pc_ < 0)
						{
							n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "goto/gosubの対象ラベル（*%s）がまだ定義されていません", label->name_);
							return N2_FALSE;
						}

						// 実際に飛ぶ処理
						if (widget->lgosub_)
						{
							if (state->config_.max_call_nest_ > 0 && n2_callframearray_size(f->callframes_) >= state->config_.max_call_nest_)
							{
								n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "gosub/関数呼び出しのネストサイズが最大（%zu）を超えました", state->config_.max_call_nest_);
								return N2_FALSE;
							}

							// gosubならコールスタック積む
							n2_callframe_t* lcf = n2_callframearray_push(state, f->callframes_, NULL);
							n2i_callframe_init(lcf);
							n2i_execute_fill_to_callframe(state, lcf, f);
							lcf->caller_ = N2_CALLER_EXTERNAL;
							lcf->caller_pc_ = f->op_pc_;// await命令などが入っているので入れておく
							lcf->next_pc_ = f->pc_;// 戻ってくる

							f->callstate_.func_ = NULL;
							f->callstate_.label_ = label;
							f->callstate_.flags_ = 0;
							f->callstate_.base_ = N2_SCAST(int, n2_valuearray_size(f->values_));
							f->callstate_.arg_num_ = f->callstate_.original_arg_num_ = 0;

							n2i_execute_post_setup_callframe(state, lcf, f);

							f->pc_ = label->pc_;

							// direct call
							if (!n2i_state_execute_protected(state, f)) { return N2_FALSE; }

							// コールスタック巻き戻し
							if (!n2i_execute_rewind_to_callframe(state, f, lcf)) { return N2_FALSE; }
							n2_callframearray_pop(state, f->callframes_, 1);
						}
						else
						{
							// スケジューリングだけして次の実行タイミングに実行してもらう＋ステートをクリア
							// @todo ファイバーのスタック状態をクリアしないとダメ？
							f->pc_ = label->pc_;
							widget->value_dirty_count_ = 0;
							break;
						}
					}
					--widget->value_dirty_count_;
				}
				break;
			case N2S_WIDGET_CHECKBOX:
				if (widget->value_dirty_count_ > 0 && widget->capture_)
				{
					n2_value_t tvalue;
					n2i_value_init(&tvalue); n2_value_seti(state, &tvalue, widget->ivalue_);
					n2_variable_set(state, f, widget->capture_, widget->capture_aptr_, &tvalue);
					n2i_value_teardown(state, &tvalue);
					widget->value_dirty_count_ = 0;
				}
				break;
			case N2S_WIDGET_INPUT:
			case N2S_WIDGET_TEXTBOX:
				if (widget->value_dirty_count_ > 0 && widget->capture_)
				{
					n2_value_t tvalue;
					n2i_value_init(&tvalue); n2_value_sets(state, &tvalue, widget->strvalue_.str_, widget->strvalue_.size_);
					n2_variable_set(state, f, widget->capture_, widget->capture_aptr_, &tvalue);
					n2i_value_teardown(state, &tvalue);
					widget->value_dirty_count_ = 0;
				}
				break;
			default:
				break;
			}
		}

		// 元の状態を復元
		f->fiber_state_ = prev_fiber_state;
		res = N2_TRUE;
	}

	N2_PROTECT_LEAVE(protectframe, f);
	return res;
}

//=============================================================================
// 外部用
N2_API n2_bool_t n2e_register_func(n2_state_t* state, const char* name, n2_func_callback_t callback, void* funcuser)
{
	n2_str_t fullname;
	n2_str_init(&fullname);
	if (!name || !callback) { goto fail_exit; }
	if (!n2_naming_compute(state, name, SIZE_MAX, NULL, NULL, &fullname, NULL)) { goto fail_exit; }
	const int funcindex = n2_functable_register(state, state->environment_->functable_, name);
	n2_func_t* func = n2_functable_peek(state->environment_->functable_, funcindex);
	if (!func) { goto fail_exit; }
	n2i_func_setas_callback(state, func, N2_FUNC_EXTERNAL, callback, funcuser);
	n2_str_teardown(state, &fullname);
	return N2_TRUE;
fail_exit:
	n2_str_teardown(state, &fullname);
	return N2_FALSE;
}

N2_API n2_bool_t n2e_register_sysvar_ex(n2_state_t* state, const char* name, n2_sysvar_ex_callback_t callback, n2_sysvar_ex_inspect_t inspect, void* sysvaruser)
{
	if (n2_sysvarexarray_find(state->environment_->sysvar_ex_, n2i_sysvarexarray_matchfunc, name) >= 0) { return N2_FALSE; }
	n2_sysvar_ex_t* sysvarex = n2_sysvarexarray_push(state, state->environment_->sysvar_ex_, NULL);
	sysvarex->name_ = n2_plstr_clone(state, name);
	sysvarex->callback_ = callback;
	sysvarex->inspect_ = inspect;
	sysvarex->user_ = sysvaruser;
#if N2_CONFIG_USE_DEBUGGING
	sysvarex->debugvarpool_ = NULL;
	sysvarex->debugvarroot_ = NULL;
	if (state->config_.generate_debugvars_)
	{
		sysvarex->debugvarpool_ = state->environment_->debugvarpool_;
		sysvarex->debugvarroot_ = n2_debugvarpool_pop_or_alloc(state, sysvarex->debugvarpool_);
		sysvarex->debugvarroot_->type_ = N2_DEBUGVARIABLE_SYSVAR_ELEMENT;
		sysvarex->debugvarroot_->v_.sysvar_element_.fiber_ = state->main_fiber_;
		sysvarex->debugvarroot_->v_.sysvar_element_.sysvar_index_ = N2_SCAST(int, n2_sysvarexarray_size(state->environment_->sysvar_ex_)) - 1 + N2_MAX_SYSVAR;
	}
#endif
	return N2_TRUE;
}


N2_API n2_module_t* n2e_register_module(n2_state_t* state, const char* name)
{
	return n2_moduletable_register(state, state->environment_->moduletable_, name);
}

N2_API n2_bool_t n2e_register_modcallbacks(n2_module_t* mod, n2_modinstance_alloc_callback_t alloccallback, n2_modinstance_free_callback_t freecallback, void* moduser)
{
	if (mod->alloc_callback_ || mod->free_callback_) { return N2_FALSE; }
	mod->alloc_callback_ = alloccallback;
	mod->free_callback_ = freecallback;
	mod->mod_user_ = moduser;
	return N2_TRUE;
}

N2_API n2_bool_t n2e_register_modfunc(n2_state_t* state, n2_module_t* mod, const char* name, n2_func_callback_t callback, void* funcuser)
{
	if (n2_functable_find(state->environment_->functable_, name)) { return N2_FALSE; }
	const int funcindex = n2_functable_register(state, state->environment_->functable_, name);
	n2_func_t* func = n2_functable_peek(state->environment_->functable_, funcindex);
	n2i_func_setas_callback(state, func, N2_FUNC_EXTERNAL, callback, funcuser);
	n2_modfuncindexset_insertv(state, mod->modfuncs_, funcindex, NULL);
	n2_modfuncindexset_insertv(state, mod->modfuncsnames_, funcindex, NULL);
	return N2_TRUE;
}

static int n2ei_funcarg_compute_stackindex(const n2_funcarg_t* arg, int index)
{
	const int stack_num = N2_SCAST(int, n2_valuearray_size(arg->fiber_->values_)) - arg->fiber_->callstate_.base_;
	if (index > stack_num || index < -stack_num) { return -1; }
	if (index < 0) { index += stack_num; }
	return index;
}

static n2_value_t* n2e_funcarg_getraw(const n2_funcarg_t* arg, int index)
{
	index = n2ei_funcarg_compute_stackindex(arg, index);
	if (index < 0) { return NULL; }
	return n2_valuearray_peekv(arg->fiber_->values_, arg->fiber_->callstate_.base_ + index, NULL);
}

N2_API void n2e_funcarg_raise(const n2_funcarg_t* arg, const char* message, ...)
{
	va_list args;
	va_start(args, message);
	n2i_vraise_fiber_exception(arg->state_, arg->fiber_, N2_ERROR_RUNTIME, message, args);
	va_end(args);
}

N2_API n2_bool_t n2e_funcarg_haserror(const n2_funcarg_t* arg)
{
	return arg->fiber_->has_error_;
}

N2_API size_t n2e_funcarg_csflags(const n2_funcarg_t* arg)
{
	return arg->fiber_->callstate_.flags_;
}

N2_API size_t n2e_funcarg_argnum(const n2_funcarg_t* arg)
{
	return N2_SCAST(size_t, arg->fiber_->callstate_.arg_num_);
}

N2_API size_t n2e_funcarg_stacktop(const n2_funcarg_t* arg)
{
	const int top = N2_SCAST(int, n2_valuearray_size(arg->fiber_->values_)) - arg->fiber_->callstate_.base_;
	return top <= 0 ? 0 : N2_SCAST(size_t, top);
}

N2_API n2_value_t* n2e_funcarg_get(const n2_funcarg_t* arg, int index)
{
	return n2e_funcarg_getraw(arg, index);
}

N2_API n2_value_t* n2e_funcarg_getarg(const n2_funcarg_t* arg, int index)
{
	const int arg_num = arg->fiber_->callstate_.arg_num_;
	if (index >= arg_num || index < -arg_num) { return NULL; }
	if (index < 0) { index += arg_num; }
	return n2_valuearray_peekv(arg->fiber_->values_, arg->fiber_->callstate_.base_ + index, NULL);
}

N2_API n2_valint_t n2e_funcarg_eval_int(const n2_funcarg_t* arg, const n2_value_t* val)
{
	if (!val) { return 0; }
	return n2_value_eval_int(arg->state_, arg->fiber_, val);
}

N2_API n2_valfloat_t n2e_funcarg_eval_float(const n2_funcarg_t* arg, const n2_value_t* val)
{
	if (!val) { return 0; }
	return n2_value_eval_float(arg->state_, arg->fiber_, val);
}

N2_API n2_valstr_t* n2e_funcarg_eval_str(const n2_funcarg_t* arg, const n2_value_t* val)
{
	return n2_value_eval_str(arg->state_, arg->fiber_, val);
}

N2_API n2_valstr_t* n2e_funcarg_eval_str_and_push(const n2_funcarg_t* arg, const n2_value_t* val)
{
	n2_valstr_t* s = n2_value_eval_str(arg->state_, arg->fiber_, val);
	n2_value_t** psval = n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_allocs(arg->state_, s));
	n2_str_free(arg->state_, s);
	N2_ASSERT((*psval)->type_ == N2_VALUE_STRING);
	return &(*psval)->field_.svalue_;
}

N2_API n2_bool_t n2e_funcarg_pushstack(const n2_funcarg_t* arg, int index)
{
	n2_value_t* v = n2e_funcarg_get(arg, index);
	if (!v) { return N2_FALSE; }
	n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_clone(arg->state_, v));
	return N2_TRUE;
}

N2_API void n2e_funcarg_pushi(const n2_funcarg_t* arg, n2_valint_t v)
{
	n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_alloci(arg->state_, v));
}

N2_API void n2e_funcarg_pushf(const n2_funcarg_t* arg, n2_valfloat_t v)
{
	n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_allocf(arg->state_, v));
}

N2_API n2_valstr_t* n2e_funcarg_pushs(const n2_funcarg_t* arg, const char* s)
{
	n2_str_t tstr; n2_str_init(&tstr); n2_str_set(arg->state_, &tstr, s, SIZE_MAX);
	n2_value_t** val = n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_allocs(arg->state_, &tstr));
	n2_str_teardown(arg->state_, &tstr);
	N2_ASSERT((*val)->type_ == N2_VALUE_STRING);
	return &(*val)->field_.svalue_;
}

N2_API void n2e_funcarg_pushmodinst(const n2_funcarg_t* arg, n2_modinstance_t* instance)
{
	n2_valuearray_pushv(arg->state_, arg->fiber_->values_, n2_value_allocmodinst(arg->state_, instance));
}

N2_API int n2e_funcarg_callfunc(const n2_funcarg_t* arg, const n2_func_t* func, size_t arg_num)
{
	if (arg_num > n2e_funcarg_stacktop(arg))
	{
		n2i_raise_fiber_exception(arg->state_, arg->fiber_, N2_ERROR_RUNTIME, "関数呼び出しの引数の数がたりません（内部エラー）");
		return -1;
	}

	N2_ASSERT(func);
	const n2_func_t* original_func = func;
	for (size_t i = 0; i < N2_MAX_FUNC_ALIAS_LOOP; ++i)
	{
		if (func->func_ != N2_FUNC_ALIAS) { break; }
		func = func->alias_func_;
	}
	if (func->func_ == N2_FUNC_ALIAS)
	{
		n2i_raise_fiber_exception(arg->state_, arg->fiber_, N2_ERROR_RUNTIME, "関数（%s）呼び出しのエイリアスを解決しようとしましたが、エイリアスが深すぎます", original_func->name_);
		return -1;
	}

	n2_state_t* state = arg->state_;
	n2_fiber_t* f = arg->fiber_;

	n2_callframe_t* lcf = n2_callframearray_push(state, f->callframes_, NULL);
	n2i_callframe_init(lcf);
	n2i_execute_fill_to_callframe(state, lcf, f);
	lcf->caller_ = N2_CALLER_EXTERNAL;

	f->callstate_.func_ = func;
	f->callstate_.label_ = NULL;
	f->callstate_.base_ = N2_SCAST(int, n2_valuearray_size(f->values_)) - N2_SCAST(int, arg_num);
	f->callstate_.arg_num_ = f->callstate_.original_arg_num_ = N2_SCAST(int, arg_num);

	n2i_execute_post_setup_callframe(state, lcf, f);

	int res_num = 0;
	switch (func->func_)
	{
	case N2_FUNC_INTERNAL:
	case N2_FUNC_EXTERNAL:
		{
			if (!func->callback_)
			{
				n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）を呼び出そうとしましたがまだ定義されていません", func->name_);
				return N2_FALSE;
			}
			// 外部関数呼び出し用の処理
			f->op_pc_ = -1;// 実行されているPCをクリア（コールスタックのみでる）

			// funcargの準備
			n2_funcarg_t funcarg;
			funcarg.state_ = state;
			funcarg.fiber_ = f;
			funcarg.func_ = func;
			funcarg.funcuser_ = func->user_;

			// 呼び出し
			res_num = func->callback_(&funcarg);
		}
		break;
	case N2_FUNC_SCRIPT:
		if (func->pc_ < 0)
		{
			n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）を呼び出そうとしましたがまだ定義されていません", func->name_);
			return N2_FALSE;
		}
		f->pc_ = func->pc_;
		if (!n2_state_execute_fiber(state, f)) { return -1; }
		break;
	default:
		N2_ASSERT(0);
		return -1;
	}

	if (res_num < 0)
	{
		n2i_raise_fiber_exception(state, f, N2_ERROR_RUNTIME, "関数（%s）呼び出しでエラーが発生しました", func->name_);
		return -1;
	}

	// 戻り値保証
	const int top = N2_SCAST(int, n2_valuearray_size(f->values_));
	const int res_max = top - f->callstate_.base_;
	if (res_num > res_max) { res_num = res_max; }

	if (res_num > 1) { res_num = 1;/*@todo 戻り値の数は最大一つ*/ }
	const int pop_res_num = res_max - res_num;
	N2_ASSERT(pop_res_num >= 0);
	n2_valuearray_erase_num(state, f->values_, f->callstate_.base_, N2_SCAST(size_t, pop_res_num));

	// 即rewind
	if (!n2i_execute_rewind_to_callframe(state, f, lcf)) { return -1; }
	n2_callframearray_pop(state, f->callframes_, 1);

	return res_num;
}

//=============================================================================
// 基底組み込み機能

static void n2i_environment_bind_core_builtins(n2_state_t* state, n2_environment_t* e)
{
	if (e->is_core_bounded_) { return; }

	{
		N2_ASSERT(e->module_core_modclass_id_ < 0);
		n2_module_t* emodule = n2_moduletable_register(state, e->moduletable_, "$_modclass");
		e->module_core_modclass_id_ = emodule->module_id_;
		N2_ASSERT(e->module_core_modclass_id_ >= 0);
		emodule->alloc_callback_ = n2i_crmodule_modclass_alloc;
		emodule->free_callback_ = n2i_crmodule_modclass_free;
	}

	e->is_core_bounded_ = N2_TRUE;
}

//=============================================================================
// 基本組み込み機能

static int n2i_bifunc_end(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "end：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t ex = exval ? n2e_funcarg_eval_int(arg, exval) : 0;
	arg->fiber_->fiber_state_ = N2_FIBER_STATE_END;
	arg->fiber_->exit_code_ = N2_SCAST(int, ex);
	return 0;
}

static int n2i_bifunc_stop(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 0) { n2e_funcarg_raise(arg, "stop：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	arg->fiber_->fiber_state_ = N2_FIBER_STATE_STOPPED;
	return 0;
}

static int n2i_bifunc_raise(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "raise：引数の数（%d）が多すぎます", arg_num); return -1; }
	const n2_value_t* mesval = n2e_funcarg_getarg(arg, 0);
	// 一度確保してから、自動でメモリ回収されるようにスタックに積む
	n2_valstr_t* mes = mesval ? n2e_funcarg_eval_str(arg, mesval) : n2_str_alloc_fmt(arg->state_, "raiseによる例外が発生しました");
	n2_valstr_t* stackmes = n2e_funcarg_pushs(arg, mes->str_);
	n2_str_free(arg->state_, mes);
	n2i_raise_fiber_exception(arg->state_, arg->fiber_, N2_ERROR_RUNTIME, "%s", stackmes->str_);
	return 0;
}

static int n2i_bifunc_exit(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "exit：引数の数（%d）が多すぎます", arg_num); return -1; }
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t ex = exval ? n2e_funcarg_eval_int(arg, exval) : 0;
	arg->fiber_->fiber_state_ = N2_FIBER_STATE_END;
	arg->fiber_->exit_code_ = N2_SCAST(int, ex);
	return 0;
}

static int n2i_bifunc_isnil(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "isnil：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	n2e_funcarg_pushi(arg, n2_value_get_type(val) == N2_VALUE_NIL ? 1 : 0);
	return 1;
}

static int n2i_bifunc_str(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "str：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	n2e_funcarg_eval_str_and_push(arg, val);
	return 1;
}

static int n2i_bifunc_dim_common(const n2_funcarg_t* arg, n2_value_e valtype, const char* label, n2_bool_t has_granule_size)
{
	const int min_arg_num = has_granule_size ? 2 : 1;
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < min_arg_num) { n2e_funcarg_raise(arg, "%s：引数がたりません", label); return -1; }
	if (arg_num > min_arg_num + N2_VARIABLE_DIM) { n2e_funcarg_raise(arg, "%s：引数が多すぎます、配列は%d次元までです", label, N2_VARIABLE_DIM); return -1; }

	const n2_value_t* var = n2e_funcarg_getarg(arg, 0);
	if (var->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }
	if (var->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "%s：対象の変数の配列要素が指定されています", label); return -1; }

	size_t granule_size = 0;
	size_t dims[N2_VARIABLE_DIM + 1] = {0};

	if (has_granule_size)
	{
		const n2_value_t* nval = n2e_funcarg_getarg(arg, 1);
		const n2_valint_t num = n2e_funcarg_eval_int(arg, nval);
		if (num <= 0)
		{
			n2e_funcarg_raise(arg, "%s：最低確保サイズに0以下の値は指定できません", label);
			return -1;
		}
		granule_size = N2_SCAST(size_t, num);
	}
	for (int i = 0; i < arg_num - min_arg_num; ++i)
	{
		const n2_value_t* nval = n2e_funcarg_getarg(arg, i + min_arg_num);
		const n2_valint_t num = n2e_funcarg_eval_int(arg, nval);
		if (num <= 0)
		{
			n2e_funcarg_raise(arg, "%s：%d次元目に0個以下の要素は確保できません", label, i);
			return -1;
		}
		dims[i] = N2_SCAST(size_t, num);
	}

	n2_variable_prepare(arg->state_, var->field_.varvalue_.var_, valtype, granule_size, dims);
	return 0;
}

static int n2i_bifunc_dim(const n2_funcarg_t* arg) { return n2i_bifunc_dim_common(arg, N2_VALUE_INT, "dim", N2_FALSE); }
static int n2i_bifunc_ddim(const n2_funcarg_t* arg) { return n2i_bifunc_dim_common(arg, N2_VALUE_FLOAT, "ddim", N2_FALSE); }
static int n2i_bifunc_sdim(const n2_funcarg_t* arg) { return n2i_bifunc_dim_common(arg, N2_VALUE_STRING, "sdim", N2_TRUE); }
static int n2i_bifunc_ldim(const n2_funcarg_t* arg) { return n2i_bifunc_dim_common(arg, N2_VALUE_LABEL, "ldim", N2_FALSE); }

static int n2i_bifunc_vartype(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "vartype：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }

	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (val->type_ == N2_VALUE_VARIABLE)
	{
		n2e_funcarg_pushi(arg, n2_value_get_type(val));
	}
	else if (n2_value_get_type(val) == N2_VALUE_STRING)
	{
		const n2_valstr_t* valstr = n2_value_get_strc(val);
		N2_ASSERT(valstr);
		const int valtype = n2_valuetype_find(valstr->str_, N2_TRUE);
		if (valtype < 0)
		{
			n2e_funcarg_raise(arg, "vartype：文字列（%s）が変数の型名ではありません", valstr->str_);
			return -1;
		}
		n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, valtype));
	}
	else
	{
		n2e_funcarg_raise(arg, "vartype：対象が変数でも文字列でもありません");
		return -1;
	}

	return 1;
}

static int n2i_bifunc_varsize(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "varsize：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }

	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (val->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "varsize：対象が変数ではありません"); return -1; }

	const size_t data_size = n2_variable_element_size(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, data_size));
	return 1;
}

static int n2i_bifunc_varptr(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "varptr：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }

	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (val->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "varptr：対象が変数ではありません"); return -1; }

	void* element_ptr = n2_variable_element_ptr(val->field_.varvalue_.var_, val->field_.varvalue_.aptr_);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, N2_RCAST(intptr_t, element_ptr)));
	return 1;
}

static int n2i_bifunc_varuse(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "varuse：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }

	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (val->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "varuse：対象が変数ではありません"); return -1; }

	n2_valint_t resval = 0;
	switch (n2_value_get_type(val))
	{
	case N2_VALUE_MODINST:	resval = n2_value_get_modinstc(val)->instance_ == NULL ? 0 : 1;
	default:	break;
	}

	n2e_funcarg_pushi(arg, resval);
	return 1;
}

static int n2i_bifunc_length_common(const n2_funcarg_t* arg, int dim, const char* label)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d）と違います", label, arg_num, 1); return -1; }

	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (val->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }
	if (val->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "%s：対象の変数の配列要素が指定されています", label); return -1; }

	N2_ASSERT(dim >= 0 && dim < N2_VARIABLE_DIM);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, val->field_.varvalue_.var_->length_[dim]));
	return 1;
}

static int n2i_bifunc_length(const n2_funcarg_t* arg) { return n2i_bifunc_length_common(arg, 0, "length"); }
static int n2i_bifunc_length2(const n2_funcarg_t* arg) { return n2i_bifunc_length_common(arg, 1, "length2"); }
static int n2i_bifunc_length3(const n2_funcarg_t* arg) { return n2i_bifunc_length_common(arg, 2, "length3"); }
static int n2i_bifunc_length4(const n2_funcarg_t* arg) { return n2i_bifunc_length_common(arg, 3, "length4"); }

static int n2i_bifunc_poke_common(const n2_funcarg_t* arg, const char* label, size_t byte_size)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 3) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d）と違います", label, arg_num, 3); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }

	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;

	size_t data_size = 0;
	void* data = n2_variable_map_data(&data_size, var, aptr);
	if (!data || data_size <= 0)
	{
		n2e_funcarg_raise(arg, "%s：対象の変数はpeek/pokeによって直接読み取れるデータ領域が存在しない型です", label);
		return -1;
	}

	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t offset = n2e_funcarg_eval_int(arg, offsetval);

	const n2_value_t* writeval = n2e_funcarg_getarg(arg, 2);
	const n2_bool_t allow_write_string = byte_size == 1;

	if (allow_write_string && n2_value_get_type(writeval) == N2_VALUE_STRING)
	{
		const n2_str_t* write = n2_value_get_strc(writeval);
		byte_size = n2_str_compute_size(write);

		if (offset < 0 || (offset + N2_SCAST(n2_valint_t, byte_size)) > N2_SCAST(n2_valint_t, data_size))
		{
			n2e_funcarg_raise(arg, "%s：対象の変数の範囲外を書き込もうとしています< %s(size=%zu, writeTo=%" N2_VALINT_PRI ")", label, var->name_, data_size, offset);
			return -1;
		}

		void* wto = n2_ptr_offset(data, N2_SCAST(ptrdiff_t, offset));

		N2_MEMCPY(wto, write->str_, byte_size + 1/*including null character*/);
	}
	else
	{
		const n2_valint_t write = n2e_funcarg_eval_int(arg, writeval);

		if (offset < 0 || (offset + N2_SCAST(n2_valint_t, byte_size)) > N2_SCAST(n2_valint_t, data_size))
		{
			n2e_funcarg_raise(arg, "%s：対象の変数の範囲外を書き込もうとしています< %s(size=%zu, writeTo=%" N2_VALINT_PRI ")", label, var->name_, data_size, offset);
			return -1;
		}

		void* wto = n2_ptr_offset(data, N2_SCAST(ptrdiff_t, offset));
#if 0
		// may cause unaligned memory access
		switch (byte_size)
		{
		case 1:		*N2_RCAST(int8_t*, wto) = N2_SCAST(int8_t, write); break;
		case 2:		*N2_RCAST(int16_t*, wto) = N2_SCAST(int16_t, write); break;
		case 4:		*N2_RCAST(int32_t*, wto) = N2_SCAST(int32_t, write); break;
		case 8:		*N2_RCAST(int64_t*, wto) = N2_SCAST(int64_t, write); break;
		default:	N2_ASSERT(0); break;
		}
#else
		switch (byte_size)
		{
		case 1:		{ const uint8_t v = N2_SCAST(uint8_t, write); N2_MEMCPY(wto, &v, 1); } break;
		case 2:		{ const uint16_t v = N2_SCAST(uint16_t, write); N2_MEMCPY(wto, &v, 2); } break;
		case 4:		{ const int32_t v = N2_SCAST(int32_t, write); N2_MEMCPY(wto, &v, 4); } break;
		case 8:		{ const int64_t v = N2_SCAST(int64_t, write); N2_MEMCPY(wto, &v, 8); } break;
		default:	N2_ASSERT(0); break;
		}
#endif
	}

	n2_variable_unmap_data(var, aptr);
	return 0;
}

static int n2i_bifunc_poke(const n2_funcarg_t* arg) { return n2i_bifunc_poke_common(arg, "poke", 1); }
static int n2i_bifunc_wpoke(const n2_funcarg_t* arg) { return n2i_bifunc_poke_common(arg, "wpoke", 2); }
static int n2i_bifunc_lpoke(const n2_funcarg_t* arg) { return n2i_bifunc_poke_common(arg, "lpoke", 4); }
static int n2i_bifunc_llpoke(const n2_funcarg_t* arg) { return n2i_bifunc_poke_common(arg, "llpoke", 8); }

static int n2i_bifunc_peek_common(const n2_funcarg_t* arg, const char* label, size_t byte_size)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d）と違います", label, arg_num, 2); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }

	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;

	size_t data_size = 0;
	const void* data = n2_variable_map_data(&data_size, var, aptr);
	if (!data || data_size <= 0)
	{
		n2e_funcarg_raise(arg, "%s：対象の変数はpeek/pokeによって直接読み取れるデータ領域が存在しない型です", label);
		return -1;
	}

	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t offset = n2e_funcarg_eval_int(arg, offsetval);

	if (offset < 0 || (offset + N2_SCAST(n2_valint_t, byte_size)) > N2_SCAST(n2_valint_t, data_size))
	{
		n2e_funcarg_raise(arg, "%s：対象の変数の範囲外を読み込もうとしています< %s(size=%zu, writeTo=%" N2_VALINT_PRI ")", label, var->name_, data_size, offset);
		return -1;
	}

	const void* rfrom = n2_cptr_offset(data, N2_SCAST(ptrdiff_t, offset));
	n2_valint_t read = 0;
#if 0
	// may cause unaligned memory access
	switch (byte_size)
	{
	case 1:		read = N2_SCAST(n2_valint_t, *N2_RCAST(int8_t*, rfrom)); break;
	case 2:		read = N2_SCAST(n2_valint_t, *N2_RCAST(int16_t*, rfrom)); break;
	case 4:		read = N2_SCAST(n2_valint_t, *N2_RCAST(int32_t*, rfrom)); break;
	case 8:		read = N2_SCAST(n2_valint_t, *N2_RCAST(int64_t*, rfrom)); break;
	default:	N2_ASSERT(0); break;
	}
#else
	switch (byte_size)
	{
	case 1:		{ uint8_t v = 0; N2_MEMCPY(&v, rfrom, 1); read = N2_SCAST(n2_valint_t, v); } break;
	case 2:		{ uint16_t v = 0; N2_MEMCPY(&v, rfrom, 2); read = N2_SCAST(n2_valint_t, v); } break;
	case 4:		{ int32_t v = 0; N2_MEMCPY(&v, rfrom, 4); read = N2_SCAST(n2_valint_t, v); } break;
	case 8:		{ int64_t v = 0; N2_MEMCPY(&v, rfrom, 8); read = N2_SCAST(n2_valint_t, v); } break;
	default:	N2_ASSERT(0); break;
	}
#endif

	n2e_funcarg_pushi(arg, read);
	return 1;
}

static int n2i_bifunc_peek(const n2_funcarg_t* arg) { return n2i_bifunc_peek_common(arg, "peek", 1); }
static int n2i_bifunc_wpeek(const n2_funcarg_t* arg) { return n2i_bifunc_peek_common(arg, "wpeek", 2); }
static int n2i_bifunc_lpeek(const n2_funcarg_t* arg) { return n2i_bifunc_peek_common(arg, "lpeek", 4); }
static int n2i_bifunc_llpeek(const n2_funcarg_t* arg) { return n2i_bifunc_peek_common(arg, "llpeek", 8); }

typedef struct n2i_variable_sort_ctx_t n2i_variable_sort_ctx_t;
struct n2i_variable_sort_ctx_t
{
	n2_bool_t is_reverse_;
	n2_variable_t* var_;
};

static int n2i_variable_sort_cmpfunc(const n2_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	const n2i_variable_sort_ctx_t* ctx = N2_RCAST(const n2i_variable_sort_ctx_t*, key);
	const int lindex = *N2_RCAST(const int*, lkey);
	const int rindex = *N2_RCAST(const int*, rkey);
	const void* le = n2_variable_element_ptr(ctx->var_, lindex);
	const void* re = n2_variable_element_ptr(ctx->var_, rindex);
	int cmp = 0;
	switch (ctx->var_->type_)
	{
	case N2_VALUE_INT:		cmp = N2_SCAST(int, *N2_RCAST(const n2_valint_t*, le) - *N2_RCAST(const n2_valint_t*, re)); break;
	case N2_VALUE_FLOAT:	{ n2_valfloat_t diff = *N2_RCAST(const n2_valfloat_t*, le) - *N2_RCAST(const n2_valfloat_t*, re); cmp = diff == 0 ? 0 : diff < 0 ? -1 : 1; } break;
	case N2_VALUE_STRING:	cmp = N2_STRCMP(N2_RCAST(const n2_valstr_t*, le)->str_, N2_RCAST(const n2_valstr_t*, re)->str_); break;
	case N2_VALUE_LABEL:	cmp = N2_RCAST(const n2_vallabel_t*, le)->label_index_ - N2_RCAST(const n2_vallabel_t*, re)->label_index_; break;
	default:				cmp = 0; break;
	}
	if (cmp == 0) { cmp = lindex - rindex; }// make it stable
	if (ctx->is_reverse_) { cmp = -cmp; }
	return cmp;
}

static int n2i_bifunc_sort_common(const n2_funcarg_t* arg, const char* label, n2_bool_t is_val)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 2) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 1, 2); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }
	if (varval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "%s：対象の変数の配列要素が指定されています", label); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	if (var->length_[1] > 0) { n2e_funcarg_raise(arg, "%s：対象の変数の配列が２次元以上です", label); return -1; }

	const n2_value_e valtype = n2_value_get_type(varval);
	if (is_val)
	{
		if (valtype != N2_VALUE_INT && valtype != N2_VALUE_FLOAT)
		{
			n2e_funcarg_raise(arg, "%s：対象の変数の型が想定と違います", label);
			return -1;
		}
	}
	else
	{
		if (valtype != N2_VALUE_STRING)
		{
			n2e_funcarg_raise(arg, "%s：対象の変数の型が想定と違います", label);
			return -1;
		}
	}

	n2_bool_t is_reverse = N2_FALSE;
	if (arg_num > 1)
	{
		const n2_value_t* rval = n2e_funcarg_getarg(arg, 1);
		const n2_valint_t ri = n2e_funcarg_eval_int(arg, rval);
		is_reverse = ri == 0 ? N2_FALSE : N2_TRUE;
	}

	const size_t len = var->length_[0];
	n2_intarray_t* indices = arg->fiber_->sort_indices_;
	n2_intarray_t* fills = arg->fiber_->sort_fill_;
	n2_intarray_clear(arg->state_, indices); n2_intarray_clear(arg->state_, fills);
	n2_intarray_reserve(arg->state_, indices, len); n2_intarray_reserve(arg->state_, fills, len);
	for (size_t i = 0; i < len; ++i)
	{
		n2_intarray_pushv(arg->state_, indices, N2_SCAST(int, i));
		n2_intarray_pushv(arg->state_, fills, 0);
	}

	n2i_variable_sort_ctx_t ctx;
	ctx.is_reverse_ = is_reverse;
	ctx.var_ = var;
	n2i_array_heapsort(indices, n2i_variable_sort_cmpfunc, &ctx);

	// 直接中身を差し替える
	uint8_t tmp[N2_MAX_VARIABLE_ELEMENT_SIZE];
	N2_ASSERT(sizeof(tmp) >= var->element_size_);
	for (size_t i = 0; i < len; ++i)
	{
		int* f = n2_intarray_peek(fills, N2_SCAST(int, i));
		if (*f) { continue; }
		int c = N2_SCAST(int, i);
		int n = n2_intarray_peekv(indices, c, -1);
		if (c == n)
		{
			*f = 1;
		}
		else
		{
			n2_swap(tmp, n2_variable_element_ptr(var, c), var->element_size_);
			for (;;)
			{
				N2_ASSERT(c >= 0);
				*f = 1;
				f = n2_intarray_peek(fills, N2_SCAST(int, n));
				if (*f) { break; }
				n2_swap(n2_variable_element_ptr(var, c), n2_variable_element_ptr(var, n), var->element_size_);
				c = n;
				n = n2_intarray_peekv(indices, n, -1);
			}
			n2_swap(tmp, n2_variable_element_ptr(var, c), var->element_size_);
		}
	}

	return 0;
}

static int n2i_bifunc_sortval(const n2_funcarg_t* arg) { return n2i_bifunc_sort_common(arg, "sortval", N2_TRUE); }
static int n2i_bifunc_sortstr(const n2_funcarg_t* arg) { return n2i_bifunc_sort_common(arg, "sortstr", N2_FALSE); }

static int n2i_bifunc_sortget(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "sortget：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "sortget：対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;

	const n2_value_t* indexval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t index = n2e_funcarg_eval_int(arg, indexval);

	if (index < 0 || index >= N2_SCAST(n2_valint_t, n2_intarray_size(arg->fiber_->sort_indices_))) { n2e_funcarg_raise(arg, "sortget：取得しようとしたインデックス（%" N2_VALINT_PRI "）が配列の範囲（%zu）を超えています", index, n2_intarray_size(arg->fiber_->sort_indices_)); return -1; }

	n2_value_t v;
	n2i_value_init(&v);
	n2_value_seti(arg->state_, &v, n2_intarray_peekv(arg->fiber_->sort_indices_, N2_SCAST(int, index), -1));
	n2_variable_set(arg->state_, arg->fiber_, var, varval->field_.varvalue_.aptr_, &v);
	n2i_value_teardown(arg->state_, &v);
	return 0;
}

static int n2i_bifunc_radomize(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "randomize：引数が多すぎます"); return -1; }

	uint64_t seed = 0;
	if (arg_num <= 0)
	{
		seed = N2_SCAST(uint64_t, N2_TIME());
	}
	else
	{
		const n2_value_t* nval = n2e_funcarg_getarg(arg, 0);
		seed = N2_SCAST(uint64_t, n2e_funcarg_eval_int(arg, nval));
	}
	n2h_random_init(&arg->fiber_->environment_->random_, seed);
	return 0;
}

static int n2i_bifunc_rnd(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "rnd：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* nval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t i = n2e_funcarg_eval_int(arg, nval);
	if (i <= 0) { n2e_funcarg_raise(arg, "rnd：引数0に0以下の値（%" N2_VALINT_PRI "）が渡されました", i); return -1; }
	const uint64_t r = n2h_random_next_range(&arg->fiber_->environment_->random_, N2_SCAST(uint64_t, i));
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, r));
	return 1;
}

static int n2i_bifunc_rndf(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "rndf：引数の数（%d）が期待（0 - %d）と違います", arg_num, 1); return -1; }
	const n2_value_t* nval = n2e_funcarg_getarg(arg, 0);
	const n2_valfloat_t i = nval && nval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, nval) : 1;
	if (i <= 0) { n2e_funcarg_raise(arg, "rndf：引数0に0以下の値（%" N2_VALFLOAT_PRI "）が渡されました", i); return -1; }
	const double r = n2h_random_next_float(&arg->fiber_->environment_->random_);
	n2_valfloat_t d = N2_SCAST(n2_valfloat_t, r);
	n2e_funcarg_pushf(arg, i * d);
	return 1;
}

static int n2i_bifunc_limit(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "limit：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 3); return -1; }
	const n2_value_t* nval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t n = n2e_funcarg_eval_int(arg, nval);
	const n2_value_t* mival = n2e_funcarg_getarg(arg, 1);
	if (mival && mival->type_ != N2_VALUE_NIL) { n2_valint_t mi = n2e_funcarg_eval_int(arg, mival); n = N2_MAX(n, mi); }
	const n2_value_t* maval = n2e_funcarg_getarg(arg, 2);
	if (maval && maval->type_ != N2_VALUE_NIL) { n2_valint_t ma = n2e_funcarg_eval_int(arg, maval); n = N2_MIN(n, ma); }
	n2e_funcarg_pushi(arg, n);
	return 1;
}

static int n2i_bifunc_limitf(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "limitf：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 3); return -1; }
	const n2_value_t* nval = n2e_funcarg_getarg(arg, 0);
	n2_valfloat_t n = n2e_funcarg_eval_float(arg, nval);
	const n2_value_t* mival = n2e_funcarg_getarg(arg, 1);
	if (mival && mival->type_ != N2_VALUE_NIL) { const n2_valfloat_t mi = n2e_funcarg_eval_float(arg, mival); n = N2_MAX(n, mi); }
	const n2_value_t* maval = n2e_funcarg_getarg(arg, 2);
	if (maval && maval->type_ != N2_VALUE_NIL) { const n2_valfloat_t ma = n2e_funcarg_eval_float(arg, maval); n = N2_MIN(n, ma); }
	n2e_funcarg_pushf(arg, n);
	return 1;
}

#define N2I_DEFINE_BIFUNC_1I(name, exp) \
	static int n2i_bifunc_##name(const n2_funcarg_t* arg) \
	{ \
		const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg)); \
		if (arg_num != 1) { n2e_funcarg_raise(arg, #name "：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; } \
		const n2_value_t* nval = n2e_funcarg_getarg(arg, 0); \
		const n2_valint_t i = n2e_funcarg_eval_int(arg, nval); \
		n2e_funcarg_pushi(arg, exp(i)); \
		return 1; \
	}

#define N2I_DEFINE_BIFUNC_3I(name, exp) \
	static int n2i_bifunc_##name(const n2_funcarg_t* arg) \
	{ \
		const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg)); \
		if (arg_num != 3) { n2e_funcarg_raise(arg, #name "：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; } \
		const n2_value_t* xval = n2e_funcarg_getarg(arg, 0); \
		const n2_value_t* yval = n2e_funcarg_getarg(arg, 1); \
		const n2_value_t* zval = n2e_funcarg_getarg(arg, 2); \
		const n2_valint_t x = n2e_funcarg_eval_int(arg, xval); \
		const n2_valint_t y = n2e_funcarg_eval_int(arg, yval); \
		const n2_valint_t z = n2e_funcarg_eval_int(arg, zval); \
		n2e_funcarg_pushi(arg, exp(x, y, z)); \
		return 1; \
	}

#define N2I_DEFINE_BIFUNC_1F(name, exp) \
	static int n2i_bifunc_##name(const n2_funcarg_t* arg) \
	{ \
		const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg)); \
		if (arg_num != 1) { n2e_funcarg_raise(arg, #name "：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; } \
		const n2_value_t* nval = n2e_funcarg_getarg(arg, 0); \
		const n2_valfloat_t f = n2e_funcarg_eval_float(arg, nval); \
		n2e_funcarg_pushf(arg, exp(f)); \
		return 1; \
	}

#define N2I_DEFINE_BIFUNC_2F(name, exp) \
	static int n2i_bifunc_##name(const n2_funcarg_t* arg) \
	{ \
		const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg)); \
		if (arg_num != 2) { n2e_funcarg_raise(arg, #name "：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; } \
		const n2_value_t* xval = n2e_funcarg_getarg(arg, 0); \
		const n2_value_t* yval = n2e_funcarg_getarg(arg, 1); \
		const n2_valfloat_t x = n2e_funcarg_eval_float(arg, xval); \
		const n2_valfloat_t y = n2e_funcarg_eval_float(arg, yval); \
		n2e_funcarg_pushf(arg, exp(x, y)); \
		return 1; \
	}

#define N2I_DEFINE_BIFUNC_3F(name, exp) \
	static int n2i_bifunc_##name(const n2_funcarg_t* arg) \
	{ \
		const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg)); \
		if (arg_num != 3) { n2e_funcarg_raise(arg, #name "：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; } \
		const n2_value_t* xval = n2e_funcarg_getarg(arg, 0); \
		const n2_value_t* yval = n2e_funcarg_getarg(arg, 1); \
		const n2_value_t* zval = n2e_funcarg_getarg(arg, 2); \
		const n2_valfloat_t x = n2e_funcarg_eval_float(arg, xval); \
		const n2_valfloat_t y = n2e_funcarg_eval_float(arg, yval); \
		const n2_valfloat_t z = n2e_funcarg_eval_float(arg, zval); \
		n2e_funcarg_pushf(arg, exp(x, y, z)); \
		return 1; \
	}

static n2_valint_t n2ih_abs(n2_valint_t x) { return (x >= 0 ? x : -x); }
static n2_valfloat_t n2ih_absf(n2_valfloat_t x) { return (x >= 0 ? x : -x); }
static n2_valfloat_t n2ih_deg2rad(n2_valfloat_t x) { return x * N2_SCAST(n2_valfloat_t, N2_MPI / 180.0); }
static n2_valfloat_t n2ih_rad2deg(n2_valfloat_t x) { return x * N2_SCAST(n2_valfloat_t, 180.0 / N2_MPI); }

N2I_DEFINE_BIFUNC_1I(int, );
N2I_DEFINE_BIFUNC_1F(double, );
N2I_DEFINE_BIFUNC_1I(abs, n2ih_abs);
N2I_DEFINE_BIFUNC_1F(absf, n2ih_absf);
N2I_DEFINE_BIFUNC_1F(deg2rad, n2ih_deg2rad);
N2I_DEFINE_BIFUNC_1F(rad2deg, n2ih_rad2deg);
N2I_DEFINE_BIFUNC_1F(sin, N2_SIN);
N2I_DEFINE_BIFUNC_1F(cos, N2_COS);
N2I_DEFINE_BIFUNC_1F(tan, N2_TAN);
N2I_DEFINE_BIFUNC_1F(asin, N2_ASIN);
N2I_DEFINE_BIFUNC_1F(acos, N2_ACOS);
N2I_DEFINE_BIFUNC_2F(atan, N2_ATAN2);
N2I_DEFINE_BIFUNC_1F(sqrt, N2_SQRT);
N2I_DEFINE_BIFUNC_2F(powf, N2_POW);
N2I_DEFINE_BIFUNC_1F(expf, N2_EXP);
N2I_DEFINE_BIFUNC_1F(logf, N2_LOG);
N2I_DEFINE_BIFUNC_1F(round, N2_ROUND);
N2I_DEFINE_BIFUNC_1F(floor, N2_FLOOR);
N2I_DEFINE_BIFUNC_1F(ceil, N2_CEIL);

static int n2i_bifunc_lerpf(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 3) { n2e_funcarg_raise(arg, "lerpf：引数の数（%d）が期待（%d）と違います", arg_num, 3); return -1; }
	const n2_value_t* lowval = n2e_funcarg_getarg(arg, 0);
	const n2_valfloat_t low = n2e_funcarg_eval_float(arg, lowval);
	const n2_value_t* highval = n2e_funcarg_getarg(arg, 1);
	const n2_valfloat_t high = n2e_funcarg_eval_float(arg, highval);
	const n2_value_t* rateval = n2e_funcarg_getarg(arg, 2);
	const n2_valfloat_t rate = n2e_funcarg_eval_float(arg, rateval);
	n2e_funcarg_pushf(arg, low * (1 - rate) + high * rate);
	return 1;
}

static int n2i_bifunc_setease(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "setease：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 3); return -1; }
	const n2_value_t* lowval = n2e_funcarg_getarg(arg, 0);
	const n2_valfloat_t low = lowval && lowval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, lowval) : 0;
	const n2_value_t* highval = n2e_funcarg_getarg(arg, 1);
	const n2_valfloat_t high = highval && highval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, highval) : 1;
	const n2_value_t* typeval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t type = typeval && typeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, typeval) : N2_EASE_LINEAR;
	arg->fiber_->ease_type_ = type;
	arg->fiber_->ease_start_ = low;
	arg->fiber_->ease_end_ = high;
	return 0;
}

static double n2i_ease_shake_inl(double rate)
{
	const int rr = N2_SCAST(int, rate * rate * 8);
	rate -= N2_SCAST(double, rr);
	if (rr & 1) { return 1 - rate; }
	return rate;
}
static double n2i_ease_shake_in(double rate)
{
	return n2i_ease_shake_inl(1 - rate);
}
static double n2i_ease_shake_out(double rate)
{
	return n2i_ease_shake_inl(rate);
}
static double n2i_ease_shake_inout(double rate)
{
	return rate < 0.5 ? n2i_ease_shake_in(rate * 2) : n2i_ease_shake_out(rate * 2 - 1);
}

static double n2i_bifunc_getease_internal_typed(double rate, n2_valint_t ease_type, double estart, double eend)
{
	if (ease_type & N2_EASE_OPT_LOOP)
	{
		const n2_bool_t reverse = (N2_SCAST(int, N2_FLOOR(rate)) & 1) ? N2_TRUE : N2_FALSE;
		rate = N2_FMOD(rate, 1);
		if (reverse) { rate = 1 - rate; }
	}
	else
	{
		rate = rate < 0 ? 0 : rate > 1 ? 1 : rate;
	}
	double r = 0;
	switch (ease_type & 0xff)
	{
	case N2_EASE_QUAD_IN:		r = n2h_easing_quadratic_in(rate); break;
	case N2_EASE_QUAD_OUT:		r = n2h_easing_quadratic_out(rate); break;
	case N2_EASE_QUAD_INOUT:	r = n2h_easing_quadratic_inout(rate); break;
	case N2_EASE_CUBIC_IN:		r = n2h_easing_cubic_in(rate); break;
	case N2_EASE_CUBIC_OUT:		r = n2h_easing_cubic_out(rate); break;
	case N2_EASE_CUBIC_INOUT:	r = n2h_easing_cubic_inout(rate); break;
	case N2_EASE_QUARTIC_IN:	r = n2h_easing_quartic_in(rate); break;
	case N2_EASE_QUARTIC_OUT:	r = n2h_easing_quartic_out(rate); break;
	case N2_EASE_QUARTIC_INOUT:	r = n2h_easing_quartic_inout(rate); break;
	case N2_EASE_BOUNCE_IN:		r = n2h_easing_bounce_in(rate); break;
	case N2_EASE_BOUNCE_OUT:	r = n2h_easing_bounce_out(rate); break;
	case N2_EASE_BOUNCE_INOUT:	r = n2h_easing_bounce_inout(rate); break;
	case N2_EASE_SHAKE_IN:		r = n2i_ease_shake_in(rate); break;
	case N2_EASE_SHAKE_OUT:		r = n2i_ease_shake_out(rate); break;
	case N2_EASE_SHAKE_INOUT:	r = n2i_ease_shake_inout(rate); break;
	default:					r = n2h_easing_linear(rate); break;
	}
	return estart * (1 - r) + eend * r;
}

static double n2i_bifunc_getease_internal(const n2_funcarg_t* arg, double rate)
{
	return n2i_bifunc_getease_internal_typed(rate, arg->fiber_->ease_type_, arg->fiber_->ease_start_, arg->fiber_->ease_end_);
}

static int n2i_bifunc_getease(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "getease：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 3); return -1; }
	const n2_value_t* eval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t e = eval && eval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, eval) : 0;
	const n2_value_t* highval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t high = highval && highval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, highval) : -1;
	if (high <= 0) { high = 4096; }
	const double rate = N2_SCAST(double, e) / N2_SCAST(double, high);
	const double r = n2i_bifunc_getease_internal(arg, rate);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, N2_ROUND(r)));
	return 1;
}
static int n2i_bifunc_geteasef(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "geteasef：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 3); return -1; }
	const n2_value_t* eval = n2e_funcarg_getarg(arg, 0);
	const n2_valfloat_t e = eval && eval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, eval) : 0;
	const n2_value_t* highval = n2e_funcarg_getarg(arg, 1);
	n2_valfloat_t high = highval && highval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, highval) : -1;
	if (high <= 0) { high = 4096; }
	const double rate = e / high;
	const double r = n2i_bifunc_getease_internal(arg, rate);
	n2e_funcarg_pushf(arg, r);
	return 1;
}
static int n2i_bifunc_ease_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "ease@n2：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 4); return -1; }
	const n2_value_t* typeval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t type = typeval && typeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, typeval) : 0;
	const n2_value_t* rateval = n2e_funcarg_getarg(arg, 1);
	const n2_valfloat_t rate = rateval && rateval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, rateval) : 0;
	const n2_value_t* lowval = n2e_funcarg_getarg(arg, 2);
	const n2_valfloat_t low = lowval && lowval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, lowval) : 0;
	const n2_value_t* highval = n2e_funcarg_getarg(arg, 3);
	const n2_valfloat_t high = highval && highval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, highval) : 1;
	const double r = n2i_bifunc_getease_internal_typed(rate, type, low, high);
	n2e_funcarg_pushf(arg, r);
	return 1;
}

static int n2i_bifunc_strlen(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "strlen：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(val) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strlen：対象が文字列ではありません"); return -1; }
	const n2_valstr_t* str = n2_value_get_strc(val);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, N2_STRNLEN(str->str_, str->buffer_size_)));
	return 1;
}

static int n2i_bifunc_getstr(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 5) { n2e_funcarg_raise(arg, "getstr：引数の数（%d）が期待（%d - %d）と違います", arg_num, 2, 5); return -1; }

	const n2_value_t* tovarval = n2e_funcarg_getarg(arg, 0);
	if (tovarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "getstr：代入対象が変数ではありません"); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 1);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "getstr：読み取り対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;

	size_t data_size = 0;
	const void* data = n2_variable_map_data(&data_size, var, aptr);
	if (!data || data_size <= 0) { n2e_funcarg_raise(arg, "getstr：読み取り対象の変数は直接読み取れるデータ領域が存在しない型です"); return -1; }

	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t offset = offsetval && offsetval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, offsetval) : 0;
	if (offset < 0 || offset > N2_SCAST(n2_valint_t, data_size))
	{
		n2e_funcarg_raise(arg, "getstr：読み取り対象の変数の範囲外を読み込もうとしています< %s(size=%zu, writeTo=%" N2_VALINT_PRI ")", var->name_, data_size, offset);
		return -1;
	}
	const size_t readbound = data_size - N2_SCAST(size_t, offset);

	const n2_value_t* separatorval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t separator = separatorval && separatorval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, separatorval) : 0;
	if (separator < 0 || separator > 255) { 		n2e_funcarg_raise(arg, "getstr：区切り文字のASCIIコード（%" N2_VALINT_PRI ")の値が不正です", separator); return -1; }

	const n2_value_t* readmaxval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t readmax = readmaxval && readmaxval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, readmaxval) : 1024;
	readmax = N2_MIN(readmax, N2_SCAST(n2_valint_t, readbound));

	const uint8_t* datau8 = N2_RCAST(const uint8_t*, data);
	const uint8_t sepu8 = N2_SCAST(uint8_t, separator);

	n2_valint_t r = 0;
	for (; r < readmax; ++r)
	{
		if (datau8[offset + r] == 0 || datau8[offset + r] == N2_SCAST(uint8_t, '\n') || datau8[offset + r] == sepu8) { break; }
	}

	n2_str_t* strval = n2e_funcarg_pushs(arg, "");
	if (r > 0)
	{
		n2_str_reserve(arg->state_, strval, N2_SCAST(size_t, r));
		N2_MEMCPY(strval->str_, datau8, N2_SCAST(size_t, r));
	}
	n2_variable_set(arg->state_, arg->fiber_, tovarval->field_.varvalue_.var_, tovarval->field_.varvalue_.aptr_, n2e_funcarg_get(arg, -1));

	return 0;
}

static int n2i_bifunc_strrep(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 3) { n2e_funcarg_raise(arg, "strrep：引数の数（%d）が期待（%d）と違います", arg_num, 3); return -1; }
	n2_value_t* targetval = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(targetval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strrep：対象が文字列ではありません"); return -1; }
	const n2_value_t* srcval = n2e_funcarg_getarg(arg, 1);
	if (n2_value_get_type(srcval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strrep：検索文字列が文字列ではありません"); return -1; }
	const n2_value_t* toval = n2e_funcarg_getarg(arg, 2);
	if (n2_value_get_type(toval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strrep：置換文字列が文字列ではありません"); return -1; }
	n2_valstr_t* str = n2_value_get_str(targetval);
	n2_str_update_size(str);// 一応内容を更新しておく
	const size_t replace_count = n2_str_replace_pattern(arg->state_, str, n2_value_get_plstr(srcval), SIZE_MAX, n2_value_get_plstr(toval), SIZE_MAX);
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, replace_count));
	return 1;
}

static int n2i_bifunc_instr(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 3) { n2e_funcarg_raise(arg, "instr：引数の数（%d）が期待（%d）と違います", arg_num, 3); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(val) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "instr：対象が文字列ではありません"); return -1; }
	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t offset = n2e_funcarg_eval_int(arg, offsetval);
	if (offset < 0)
	{
		// offsetが負なら常に-1を返す
		n2e_funcarg_pushi(arg, -1);
	}
	else
	{
		const n2_value_t* patternval = n2e_funcarg_getarg(arg, 2);
		if (n2_value_get_type(patternval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "instr：検索文字列が文字列ではありません"); return -1; }
		const n2_valstr_t* str = n2_value_get_strc(val);
		n2e_funcarg_pushi(arg, n2_str_find(str, n2_value_get_plstr(patternval), SIZE_MAX, N2_SCAST(size_t, offset)));
	}
	return 1;
}

static int n2i_bifunc_strmid(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 3) { n2e_funcarg_raise(arg, "strmid：引数の数（%d）が期待（%d）と違います", arg_num, 3); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(val) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "instr：対象が文字列ではありません"); return -1; }
	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t offset = n2e_funcarg_eval_int(arg, offsetval);
	const n2_value_t* getval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t get = n2e_funcarg_eval_int(arg, getval);
	const n2_valstr_t* str = n2_value_get_strc(val);
	n2_valstr_t* dst = n2e_funcarg_pushs(arg, "");
	if (get > 0)
	{
		const size_t poffset = offset >= 0 ? N2_SCAST(size_t, offset) : str->size_ - N2_SCAST(size_t, -offset) - N2_SCAST(size_t, get)/*may cause underflow*/;
		if (poffset < str->size_)
		{
			n2_str_set(arg->state_, dst, str->str_ + poffset, N2_MIN(str->size_ - poffset, N2_SCAST(size_t, get)));
		}
	}
	return 1;
}

static int n2i_bifunc_strtrim(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "strtrim：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 3); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(val) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strtrim：対象が文字列ではありません"); return -1; }
	const n2_value_t* swval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t sw = swval ? n2e_funcarg_eval_int(arg, swval) : 0;
	const n2_value_t* cpval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t cp = cpval && cpval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, cpval) : ' ';
	char cpstr[N2_CODEPOINT_MAX_BUFFER_SIZE]; N2_MEMSET(cpstr, 0, sizeof(cpstr));
	if (!n2_encoding_utf8_print(cpstr, N2_ARRAYDIM(cpstr), N2_SCAST(n2_codepoint_t, cp))) { n2e_funcarg_raise(arg, "strtrim：除去するコードポイント（%" N2_VALINT_PRI "）が不正です", cp); return -1; }
	const n2_valstr_t* str = n2_value_get_strc(val);
	n2_valstr_t* dst = n2e_funcarg_pushs(arg, str->str_);
	switch (sw)
	{
	case 0:		n2_str_trim(dst, cpstr, SIZE_MAX, N2_TRUE); n2_str_trim(dst, cpstr, SIZE_MAX, N2_FALSE); break;
	case 1:		n2_str_trim(dst, cpstr, SIZE_MAX, N2_TRUE); break;
	case 2:		n2_str_trim(dst, cpstr, SIZE_MAX, N2_FALSE); break;
	case 3:		n2_str_replace_pattern(arg->state_, dst, cpstr, SIZE_MAX, "", 0); break;
	default:	n2e_funcarg_raise(arg, "strtrim：除去する位置のモード（%" N2_VALINT_PRI "）が不正な値です", sw); return -1;
	}
	return 1;
}

static int n2i_bifunc_strf(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1) { n2e_funcarg_raise(arg, "strf：引数の数（%d）が期待（%d - ）と違います", arg_num, 1); return -1; }
	const n2_value_t* fmtval = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(fmtval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "strf：対象が文字列ではありません"); return -1; }
	const n2_valstr_t* fmtstr = n2_value_get_strc(fmtval);
	const char* fmt = fmtstr->str_;
	const size_t fmtlen = fmtstr->size_;
	// 書式指定子のみの一時バッファ（自動解放するためにスタックに入れる）
	n2_valstr_t* tmpformatter = n2e_funcarg_pushs(arg, "");
	// 書き込み先
	n2_valstr_t* dst = n2e_funcarg_pushs(arg, "");
	n2_str_reserve(arg->state_, dst, fmtlen);
	// 各フォーマッタをそれぞれパースして入れていく
	int printvalindex = 0;
	size_t prev_cursor = 0, cursor = 0;
	while (cursor < fmtlen)
	{
		if (fmt[cursor] != '%') { ++cursor; continue; }
		// ここまでコピー
		if (cursor > prev_cursor) { n2_str_append(arg->state_, dst, fmt + prev_cursor, cursor - prev_cursor); prev_cursor = cursor; }
		// 特殊ケース
		if (fmt[cursor + 1] == '%') { n2_str_append(arg->state_, dst, "%", SIZE_MAX); cursor += 2; prev_cursor = cursor; continue; }
		if (fmt[cursor + 1] == '\0') { n2_str_append(arg->state_, dst, "%", SIZE_MAX); ++cursor; prev_cursor = cursor; break; }
		// 書式指定子
		const char* b = fmt + cursor;
		++cursor;
		n2_bool_t is = N2_TRUE;
		do
		{
			switch (fmt[cursor])
			{
			case ' ': case '#': case '+': case '-': case '.':
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				++cursor;
				break;
			default:
				is = N2_FALSE;
				break;
			}
		} while (is);
		const char* e = fmt + cursor;
		n2_str_set(arg->state_, tmpformatter, b, e - b);
		// ここまで来たら値の準備をする
		const n2_value_t* printval = n2e_funcarg_getarg(arg, 1 + printvalindex++);
		if (!printval)
		{
			n2e_funcarg_raise(arg, "strf：%d番目の書式指定子に対応する値がありません", printvalindex);
			return -1;
		}
		// その次の本命指定子
		switch (fmt[cursor++])
		{
		case 'p':
			{
				// ポインタ
				n2_str_append(arg->state_, tmpformatter, "p", 1);// pだけいれる
				const n2_valint_t v = n2e_funcarg_eval_int(arg, printval);
				n2_str_append_fmt(arg->state_, dst, tmpformatter->str_, N2_RCAST(void*, N2_SCAST(intptr_t, v)));
			}
			break;
		case 'd': case 'i': case 'c': case 'o': case 'x': case 'X': case 'u':
			{
				// 整数
				n2_str_append(arg->state_, tmpformatter, N2_VALINT_PRI_PF, SIZE_MAX);
				n2_str_append(arg->state_, tmpformatter, fmt + cursor - 1, 1);// dicoxXuだけいれる
				const n2_valint_t v = n2e_funcarg_eval_int(arg, printval);
				n2_str_append_fmt(arg->state_, dst, tmpformatter->str_, v);
			}
			break;
		case 'f': case 'e': case 'E': case 'g': case 'G':
			{
				// 実数
				n2_str_append(arg->state_, tmpformatter, N2_VALFLOAT_PRI_PF, SIZE_MAX);
				n2_str_append(arg->state_, tmpformatter, fmt + cursor - 1, 1);// feEgGだけいれる
				const n2_valfloat_t v = n2e_funcarg_eval_float(arg, printval);
				n2_str_append_fmt(arg->state_, dst, tmpformatter->str_, v);
			}
			break;
		case 's':
			{
				// 文字列
				n2_str_append(arg->state_, tmpformatter, "s", SIZE_MAX);
				n2_valstr_t* v = n2e_funcarg_eval_str(arg, printval);
				n2_str_append_fmt(arg->state_, dst, tmpformatter->str_, v->str_);
				n2_str_free(arg->state_, v);
			}
			break;
		case 'U':
			{
				// ユニコード文字
				char mem[N2_CODEPOINT_MAX_BUFFER_SIZE] = {'\0'};
				const n2_valint_t unicp = n2e_funcarg_eval_int(arg, printval);
				if (unicp < N2_UNICODE_MIN || unicp > N2_UNICODE_MAX)
				{
					// 正しくないならフォールバック
					mem[0] = '?'; mem[1] = '\0';
				}
				else
				{
					const char* end = n2_encoding_utf8_print(mem, sizeof(mem), N2_SCAST(n2_unicp_t, unicp));
					if (n2_encoding_utf8_verify(mem, end - mem) >= 0) { mem[0] = '?'; mem[1] = '\0'; }
				}
				n2_str_append(arg->state_, dst, mem, SIZE_MAX);
			}
			break;
		default:
			n2e_funcarg_raise(arg, "strf：認識できない書式指定子（%c）です", fmt[cursor - 1]);
			return -1;
		}
		// ここまで読んだことにする
		prev_cursor = cursor;
	}
	// あまりをコピー
	if (fmtlen > prev_cursor) { n2_str_append(arg->state_, dst, fmt + prev_cursor, fmtlen - prev_cursor); }
	return 1;
}

static int n2i_bifunc_getpath(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "getpath：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }
	const n2_value_t* pathval = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(pathval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "getpath：対象が文字列ではありません"); return -1; }
	const n2_valstr_t* pathstr = n2_value_get_strc(pathval);
	const n2_value_t* swval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t sw = n2e_funcarg_eval_int(arg, swval);
	n2_valstr_t* dst = n2e_funcarg_pushs(arg, "");
	n2_str_copy_to(arg->state_, dst, pathstr);
	if (sw & 16) { n2i_str_convert_to_lower(dst); }
	n2_str_t tstr, dir, filename, ext;
	n2_str_init(&tstr); n2_str_init(&dir); n2_str_init(&filename); n2_str_init(&ext);
	n2_str_reserve(arg->state_, &tstr, 1); n2_str_reserve(arg->state_, &dir, 1); n2_str_reserve(arg->state_, &filename, 1); n2_str_reserve(arg->state_, &ext, 1);
	n2_path_split(arg->state_, &dir, &filename, &ext, dst);
	if (ext.size_ > 0) { n2_str_prepend(arg->state_, &ext, ".", 1); }
	n2_str_copy_to(arg->state_, &tstr, dst);
	if (sw & 8) { n2_str_fmt_to(arg->state_, &tstr, "%s%s", filename.str_, ext.str_); }
	else if (sw & 32) { n2_str_set(arg->state_, &tstr, pathstr->str_, pathstr->size_ - filename.size_ - ext.size_); }
	switch (sw & 7)
	{
	case 1:		n2_str_set(arg->state_, dst, tstr.str_, tstr.size_ - ext.size_); break;
	case 2:		n2_str_copy_to(arg->state_, dst, &ext); break;
	default:	n2_str_copy_to(arg->state_, dst, &tstr); break;
	}
	n2_str_teardown(arg->state_, &tstr); n2_str_teardown(arg->state_, &dir); n2_str_teardown(arg->state_, &filename); n2_str_teardown(arg->state_, &ext);
	return 1;
}

static int n2i_bifunc_cnvwtos(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "cnvwtos：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(strval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "cnvwtos：対象が文字列ではありません", arg_num, 1); return -1; }
	const n2_str_t* str = n2_value_get_strc(strval);
	N2_ASSERT(str);
	n2_str_t* converted = n2e_funcarg_pushs(arg, "");
	//n2_str_trim_utf16ne_bom(str);
	const size_t wlen = n2_encoding_utf16ne_length(str->str_, str->buffer_size_);
	n2_encoding_utf16ne_convert_to_utf8(arg->state_, converted, str->str_, wlen, '?');
	return 1;
}

static int n2i_bifunc_cnvstow(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "cnvstow：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "cnvstow：対象の引数が変数ではありません"); return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_str_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	n2_str_t* converted = n2e_funcarg_pushs(arg, "");
	n2_encoding_utf16ne_convert_from_utf8(arg->state_, converted, str->str_, str->size_, '?');
	n2_value_t* convertedval = n2e_funcarg_get(arg, -1);
	N2_ASSERT(convertedval->type_ == N2_VALUE_STRING && &convertedval->field_.svalue_ == converted);
	n2_variable_set(arg->state_, arg->fiber_, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, convertedval);
	return 0;
}

#if N2_CONFIG_USE_ENCODING_CP932
static int n2i_bifunc_cnvatos(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "cnvatos：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	if (n2_value_get_type(strval) != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "cnvatos：対象が文字列ではありません", arg_num, 1); return -1; }
	const n2_str_t* str = n2_value_get_strc(strval);
	N2_ASSERT(str);
	n2_str_t* converted = n2e_funcarg_pushs(arg, "");
	const size_t alen = n2_str_compute_size(str);
	n2_encoding_cp932_convert_to_utf8(arg->state_, converted, str->str_, alen, '?');
	return 1;
}

static int n2i_bifunc_cnvstoa(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "cnvstoa：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "cnvstoa：対象の引数が変数ではありません"); return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_str_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	n2_str_t* converted = n2e_funcarg_pushs(arg, "");
	n2_encoding_cp932_convert_from_utf8(arg->state_, converted, str->str_, str->size_, '?');
	n2_value_t* convertedval = n2e_funcarg_get(arg, -1);
	N2_ASSERT(convertedval->type_ == N2_VALUE_STRING && &convertedval->field_.svalue_ == converted);
	n2_variable_set(arg->state_, arg->fiber_, varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_, convertedval);
	return 0;
}
#endif

static int n2i_bifunc_reintfb2d_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "reintfb2d：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* fromval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t from = fromval && fromval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, fromval) : 0;
	const int32_t from32 = N2_SCAST(int32_t, from);
	float tof = 0; N2_MEMCPY(&tof, &from32, sizeof(float));
	n2e_funcarg_pushf(arg, N2_SCAST(n2_valfloat_t, tof));
	return 1;
}

static int n2i_bifunc_reintd2fb_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "reintd2fb：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* fromval = n2e_funcarg_getarg(arg, 0);
	const n2_valfloat_t from = fromval && fromval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, fromval) : 0;
	const float fromf = N2_SCAST(float, from);
	int32_t tofb = 0; N2_MEMCPY(&tofb, &fromf, sizeof(float));
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, tofb));
	return 1;
}

static n2_bool_t n2i_bifunc_internal_notecheck(const n2_funcarg_t* arg, const char* label)
{
	if (!arg->fiber_->notevar_) { n2e_funcarg_raise(arg, "%s：noteの対象変数が設定されていません。", label); return N2_FALSE; }
	if (arg->fiber_->notevar_->type_ != N2_VALUE_STRING) { n2e_funcarg_raise(arg, "%s：noteの対象変数（%s）が文字列型ではありません。", label, arg->fiber_->notevar_->name_); return N2_FALSE; }
	return N2_TRUE;
}

static int n2i_bifunc_notesel(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "notesel：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }
	const n2_value_t* noteval = n2e_funcarg_getarg(arg, 0);
	if (noteval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "notesel：対象が変数ではありません"); return -1; }
	if (n2_value_get_type(noteval) != N2_VALUE_STRING)
	{
		if (noteval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "notesel：対象の変数を文字列型にしようとしましたが、配列の要素のため文字列型に初期化できません"); return -1; }
		n2_variable_prepare(arg->state_, noteval->field_.varvalue_.var_, N2_VALUE_STRING, 64, n2i_variable_nlength);
	}
	arg->fiber_->notevar_ = noteval->field_.varvalue_.var_;
	arg->fiber_->noteaptr_ = noteval->field_.varvalue_.aptr_;
	return 0;
}

static int n2i_bifunc_noteunsel(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 0) { n2e_funcarg_raise(arg, "noteunsel：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	arg->fiber_->notevar_ = NULL;
	arg->fiber_->noteaptr_ = -1;
	return 0;
}

static int n2i_bifunc_noteadd(const n2_funcarg_t* arg)
{
	const char* label = "noteadd";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 1, 3); return -1; }
	if (!n2i_bifunc_internal_notecheck(arg, label)) { return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	n2_str_append(arg->state_, str, "\n", 1);
	const n2_value_t* lineval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t line = lineval && lineval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, lineval) : -1;
	const n2_value_t* modeval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t mode = modeval && modeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, modeval) : 0;
	n2_variable_t* var = arg->fiber_->notevar_;
	const int aptr = arg->fiber_->noteaptr_;
	n2_valstr_t* tostr = n2_variable_get_str(var, aptr);
	N2_ASSERT(tostr);
	n2_str_update_size(tostr);
	if (line < 0)
	{
		// 常に追加
		if (tostr->size_ > 0 && tostr->str_[tostr->size_ - 1] != '\n') { n2_str_append(arg->state_, tostr, "\n", 1); }
		n2_str_append(arg->state_, tostr, str->str_, str->size_);
	}
	else
	{
		const int offset = n2i_sysvar_notelinehead(tostr, N2_SCAST(int, line));
		if (offset >= 0)
		{
			if (mode)
			{
				// そこに上書き
				int last_offset = n2_str_find(tostr, "\n", 1, N2_SCAST(size_t, offset));
				n2_str_replace_range(arg->state_, tostr, N2_SCAST(size_t, offset), last_offset < 0 ? SIZE_MAX : N2_SCAST(size_t, last_offset - offset + 1), str->str_, str->size_);
			}
			else
			{
				// 追加
				n2_str_insert(arg->state_, tostr, N2_SCAST(size_t, offset), str->str_, str->size_);
			}
		}
		else
		{
			// なかったらスルー
		}
	}
	return 0;
}

static int n2i_bifunc_notedel(const n2_funcarg_t* arg)
{
	const char* label = "notedel";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d）と違います", label, arg_num, 1); return -1; }
	if (!n2i_bifunc_internal_notecheck(arg, label)) { return -1; }
	const n2_value_t* lineval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t line = lineval && lineval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, lineval) : 0;
	n2_variable_t* var = arg->fiber_->notevar_;
	const int aptr = arg->fiber_->noteaptr_;
	n2_valstr_t* tostr = n2_variable_get_str(var, aptr);
	N2_ASSERT(tostr);
	n2_str_update_size(tostr);
	const int offset = n2i_sysvar_notelinehead(tostr, N2_SCAST(int, line));
	if (offset >= 0)
	{
		int last_offset = n2_str_find(tostr, "\n", 1, N2_SCAST(size_t, offset));
		n2_str_erase(tostr, N2_SCAST(size_t, offset), last_offset < 0 ? SIZE_MAX : N2_SCAST(size_t, last_offset - offset + 1));
	}
	else
	{
		// なかったらスルー
	}
	return 0;
}

static int n2i_bifunc_noteget(const n2_funcarg_t* arg)
{
	const char* label = "noteget";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 2) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 1, 2); return -1; }
	if (!n2i_bifunc_internal_notecheck(arg, label)) { return -1; }
	const n2_value_t* tovarval = n2e_funcarg_getarg(arg, 0);
	if (tovarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }
	n2_variable_t* tovar = tovarval->field_.varvalue_.var_;
	const n2_value_t* lineval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t line = lineval && lineval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, lineval) : 0;
	n2_variable_t* var = arg->fiber_->notevar_;
	const int aptr = arg->fiber_->noteaptr_;
	n2_valstr_t* fstr = n2_variable_get_str(var, aptr);
	N2_ASSERT(fstr);
	n2_str_update_size(fstr);
	const int offset = n2i_sysvar_notelinehead(fstr, N2_SCAST(int, line));
	n2_valstr_t* asstr = n2e_funcarg_pushs(arg, "");
	n2_value_t* asstrval = n2e_funcarg_get(arg, -1);
	N2_ASSERT(&asstrval->field_.svalue_ == asstr);
	if (offset >= 0)
	{
		int last_offset = n2_str_find(fstr, "\n", 1, N2_SCAST(size_t, offset));
		n2_str_set(arg->state_, asstr, fstr->str_ + offset, last_offset < 0 ? SIZE_MAX : N2_SCAST(size_t, last_offset - offset));
	}
	else
	{
		// なかったらスルー
	}
	n2_variable_set(arg->state_, arg->fiber_, tovar, tovarval->field_.varvalue_.aptr_, asstrval);
	return 0;
}

static int n2si_bifunc_assert(const n2_funcarg_t* arg)
{
#if N2_CONFIG_USE_DEBUGGING
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "assert：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* evval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t ev = n2e_funcarg_eval_int(arg, evval);
	if (!ev)
	{
		n2_environment_t* e = arg->fiber_->environment_;
		if (e->debughook_ && e->debughook_->breakstopfunc_)
		{
			e->debughook_->breakstopfunc_(arg->state_, e->debughook_, arg->fiber_, N2_DEBUGHOOK_STOP_REASON_ASSERT);
		}
		else
		{
			n2e_funcarg_raise(arg, "アサーションに失敗しました。（評価値＝%" N2_VALINT_PRI "）", ev);
			return -1;
		}
	}
#else
	N2_UNUSE(arg);
#endif
	return 0;
}

static int n2si_bifunc_logmes(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "logmes：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* sval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* s = n2e_funcarg_eval_str_and_push(arg, sval);
	n2i_fiber_logmes(arg->state_, arg->fiber_, s);
	return 0;
}

static int n2i_bifunc_newmod(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2) { n2e_funcarg_raise(arg, "newmod：引数の数（%d）が期待（%d）より少ないです", arg_num, 2); return -1; }
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "newmod：対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	if (aptr >= 0) { n2e_funcarg_raise(arg, "newmod：対象の変数の配列要素が指定されています"); return -1; }
	if (var->type_ != N2_VALUE_MODINST) { n2_variable_prepare(arg->state_, var, N2_VALUE_MODINST, 0, n2i_variable_onelength); }
	// 再配置するインデックスを確定
	if (var->length_[1] > 0) { n2e_funcarg_raise(arg, "newmod：対象の変数のモジュール変数が２次元以上です"); return -1; }
	size_t setindex = 0;
	while (setindex < var->length_[0])
	{
		n2_valmodinst_t* inst = N2_RCAST(n2_valmodinst_t*, n2_ptr_offset(var->data_, var->element_size_ * setindex));
		if (!inst->instance_) { break; }
		++setindex;
	}
	// 末尾に作る
	if (setindex >= var->length_[0])
	{
		size_t nlength[N2_VARIABLE_DIM] = {0};
		nlength[0] = setindex + 1;
		n2_variable_redim(arg->state_, var, nlength);
	}
	// 実際に生成するモジュールを確定
	const n2_value_t* modval = n2e_funcarg_getarg(arg, 1);
	if (n2_value_get_type(modval) != N2_VALUE_MODINST) { n2e_funcarg_raise(arg, "newmod：生成するモジュールとしてモジュールが指定されていません"); return -1; }
	const n2_modinstance_t* modinst = n2_value_get_modinstc(modval)->instance_;
	if (modinst == NULL || modinst->module_id_ != arg->fiber_->environment_->module_core_modclass_id_) { n2e_funcarg_raise(arg, "newmod：生成するモジュールとしてモジュールが指定されていません"); return -1; }
	const n2i_crmodclass_instance_t* modclassinst = N2_RCAST(const n2i_crmodclass_instance_t*, modinst);
	N2_ASSERT(modclassinst->refer_module_id_ >= 0);
	n2_module_t* createmodule = n2_moduletable_peek(arg->fiber_->environment_->moduletable_, modclassinst->refer_module_id_);
	N2_ASSERT(createmodule);
	// 作って色々
	n2_modinstance_t* created = n2i_modinstance_create(arg->state_, arg->fiber_, createmodule);
	n2_valmodinst_t* inst = N2_RCAST(n2_valmodinst_t*, n2_ptr_offset(var->data_, var->element_size_ * setindex));
	inst->instance_ = created;
	// modinit
	if (createmodule->modinit_funcindex_ >= 0)
	{
		n2_func_t* func = n2_functable_peek(arg->fiber_->environment_->functable_, createmodule->modinit_funcindex_);
		N2_ASSERT(func);
		n2_modinstance_incref(arg->state_, created);
		n2e_funcarg_pushmodinst(arg, created);
		// 引数
		for (int i = 2; i < arg_num; ++i)
		{
			// 複製はもったいないのでswapで用意する
			n2e_funcarg_pushi(arg, i);
			n2_value_t* dst = n2e_funcarg_get(arg, -1);
			n2_value_t* src = n2e_funcarg_get(arg, i);
			n2_value_swap(dst, src);
		}
		// 呼び出し
		const size_t call_arg_num = N2_SCAST(size_t, arg_num - 2 + 1);
		if (n2e_funcarg_callfunc(arg, func, call_arg_num) < 0) { return -1; }
	}
	// セットしたインデックスを返す
	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, setindex));
	return 1;
}

static int n2i_bifunc_delmod(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "delmod：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "delmod：対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	if (var->type_ != N2_VALUE_MODINST) { n2e_funcarg_raise(arg, "delmod：対象の変数がモジュール変数型ではありません"); return -1; }
	n2_valmodinst_t* valmodinst = N2_RCAST(n2_valmodinst_t*, n2_variable_element_ptr(var, aptr));
	if (valmodinst->instance_)
	{
		const int termres = n2i_modinstance_term(arg, valmodinst->instance_);
		if (termres < 0) { return -1; }
		n2_modinstance_decref(arg->state_, valmodinst->instance_);
		valmodinst->instance_ = NULL;
	}
	return 0;
}

static int n2i_bifunc_gettime(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "gettime：引数の数（0 - %d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* fval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t f = fval && fval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, fval) : 0;
	time_t t = N2_TIME();
	struct tm* ttm = localtime(&t);
	switch (f)
	{
	case 0:		n2e_funcarg_pushi(arg, ttm->tm_year + 1900); break;
	case 1:		n2e_funcarg_pushi(arg, ttm->tm_mon + 1); break;
	case 2:		n2e_funcarg_pushi(arg, ttm->tm_wday); break;
	case 3:		n2e_funcarg_pushi(arg, ttm->tm_mday); break;
	case 4:		n2e_funcarg_pushi(arg, ttm->tm_hour); break;
	case 5:		n2e_funcarg_pushi(arg, ttm->tm_min); break;
	case 6:		n2e_funcarg_pushi(arg, ttm->tm_sec); break;
	case 7:		n2e_funcarg_pushi(arg, 0); break;
	default:	n2e_funcarg_pushi(arg, 0); break;
	}
	return 1;
}

static n2_bool_t n2i_bifunc_internal_fsload(const n2_funcarg_t* arg, n2_buffer_t* to, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset)
{
	if (!n2_state_fs_load(arg->state_, to, N2_STATE_FSFLAG_DEFAULT, filepath, is_binary, readsize, readoffset))
	{
		n2_buffer_teardown(arg->state_, to);
		return N2_FALSE;
	}
	return N2_TRUE;
}

static n2_bool_t n2i_bifunc_internal_fsload_str(const n2_funcarg_t* arg, n2_str_t* to, const char* filepath, size_t readsize, size_t readoffset)
{
	if (!n2_state_fs_load_str(arg->state_, to, N2_STATE_FSFLAG_DEFAULT, filepath, readsize, readoffset))
	{
		n2_str_teardown(arg->state_, to);
		return N2_FALSE;
	}
	return N2_TRUE;
}

static n2_bool_t n2i_bifunc_internal_fssave(const n2_funcarg_t* arg, size_t* dst_writtensize, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset)
{
	if (!n2_state_fs_save(arg->state_, dst_writtensize, N2_STATE_FSFLAG_DEFAULT, filepath, is_binary, writedata, writesize, writeoffset))
	{
		return N2_FALSE;
	}
	return N2_TRUE;
}

static int n2i_bifunc_bload(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 4) { n2e_funcarg_raise(arg, "bload：引数の数（%d - %d）が期待（%d）と違います", arg_num, 2, 4); return -1; }
	const n2_value_t* filepathval = n2e_funcarg_getarg(arg, 0);
	N2_ASSERT(filepathval);
	const n2_str_t* filepath = n2e_funcarg_eval_str_and_push(arg, filepathval);
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 1);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "bload：対象が変数ではありません"); return -1; }
	const n2_value_t* readsizeval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t readsize = readsizeval && readsizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, readsizeval) : -1;
	const n2_value_t* readoffsetval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t readoffset = readoffsetval && readoffsetval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, readoffsetval) : -1;

	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	if (var->type_ != N2_VALUE_STRING)
	{
		if (aptr < 0) { n2_variable_prepare(arg->state_, var, N2_VALUE_STRING, 256, n2i_variable_onelength); }
		else { n2e_funcarg_raise(arg, "bload：対象の変数が文字列型ではありませんでしたが、配列要素が指定されているため、型変更もできません。"); return -1; }
	}
	n2_valstr_t* tostr = n2_variable_get_str(var, aptr);
	N2_ASSERT(tostr);

	n2_buffer_t filebuf;
	n2_buffer_init(&filebuf);
	if (!n2i_bifunc_internal_fsload(arg, &filebuf, filepath->str_, N2_TRUE, readsize < 0 ? SIZE_MAX : N2_SCAST(size_t, readsize), N2_SCAST(size_t, N2_MAX(0, readoffset))))
	{
		n2e_funcarg_raise(arg, "bload：ファイル（%s）の読み込みに失敗しました。", filepath->str_);
		return -1;
	}

	n2_str_reserve(arg->state_, tostr, filebuf.size_ + 1);
	N2_MEMCPY(tostr->str_, filebuf.data_, filebuf.size_);
	tostr->size_ = filebuf.size_;
	tostr->str_[tostr->size_] = '\0';
	arg->fiber_->strsize_ = N2_SCAST(n2_valint_t, tostr->size_);

	n2_buffer_teardown(arg->state_, &filebuf);
	return 0;
}

static int n2i_bifunc_bsave(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 4) { n2e_funcarg_raise(arg, "bsave：引数の数（%d - %d）が期待（%d）と違います", arg_num, 2, 4); return -1; }
	const n2_value_t* filepathval = n2e_funcarg_getarg(arg, 0);
	N2_ASSERT(filepathval);
	const n2_str_t* filepath = n2e_funcarg_eval_str_and_push(arg, filepathval);
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 1);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "bsave：対象が変数ではありません"); return -1; }
	const n2_value_t* writesizeval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t writesize = writesizeval && writesizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, writesizeval) : -1;
	const n2_value_t* writeoffsetval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t writeoffset = writeoffsetval && writeoffsetval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, writeoffsetval) : -1;

	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	size_t data_size = 0;
	const void* data = n2_variable_map_data(&data_size, var, aptr);

	size_t writtensize = 0;
	if (!n2i_bifunc_internal_fssave(arg, &writtensize, filepath->str_, N2_TRUE, data, N2_MIN(writesize < 0 ? SIZE_MAX : N2_SCAST(size_t, writesize), data_size), writeoffset < 0 ? SIZE_MAX : N2_SCAST(size_t, writeoffset)))
	{
		n2e_funcarg_raise(arg, "bsave：ファイル（%s）の書き込みに失敗しました。", filepath->str_);
		return -1;
	}
	return 0;
}

static void n2i_environment_bind_basic_builtins(n2_state_t* state, n2_environment_t* e)
{
	if (e->is_basics_bounded_) { return; }

	static const struct 
	{
		const char* name_;
		n2_func_callback_t callback_;
	} builtins[] =
	{
		{"end"	,				n2i_bifunc_end},
		{"stop"	,				n2i_bifunc_stop},
		{"raise",				n2i_bifunc_raise},
		{"exit",				n2i_bifunc_exit},
		{"isnil",				n2i_bifunc_isnil},
		{"int",					n2i_bifunc_int},
		{"double",				n2i_bifunc_double},
		{"str"	,				n2i_bifunc_str},
		{"dim",					n2i_bifunc_dim},
		{"ddim",				n2i_bifunc_ddim},
		{"sdim",				n2i_bifunc_sdim},
		{"ldim",				n2i_bifunc_ldim},
		{"vartype",				n2i_bifunc_vartype},
		{"varsize",				n2i_bifunc_varsize},
		{"varptr",				n2i_bifunc_varptr},
		{"varuse",				n2i_bifunc_varuse},
		{"length",				n2i_bifunc_length},
		{"length2",				n2i_bifunc_length2},
		{"length3",				n2i_bifunc_length3},
		{"length4",				n2i_bifunc_length4},
		{"poke",				n2i_bifunc_poke},
		{"wpoke",				n2i_bifunc_wpoke},
		{"lpoke",				n2i_bifunc_lpoke},
		{"llpoke",				n2i_bifunc_llpoke},
		{"peek",				n2i_bifunc_peek},
		{"wpeek",				n2i_bifunc_wpeek},
		{"lpeek",				n2i_bifunc_lpeek},
		{"llpeek",				n2i_bifunc_llpeek},
		{"sortval",				n2i_bifunc_sortval},
		{"sortstr",				n2i_bifunc_sortstr},
		{"sortget",				n2i_bifunc_sortget},
		{"randomize",			n2i_bifunc_radomize},
		{"rnd",					n2i_bifunc_rnd},
		{"rndf@n2",				n2i_bifunc_rndf},
		{"abs",					n2i_bifunc_abs},
		{"absf",				n2i_bifunc_absf},
		{"limit",				n2i_bifunc_limit},
		{"limitf",				n2i_bifunc_limitf},
		{"deg2rad",				n2i_bifunc_deg2rad},
		{"rad2deg",				n2i_bifunc_rad2deg},
		{"sin",					n2i_bifunc_sin},
		{"cos",					n2i_bifunc_cos},
		{"tan",					n2i_bifunc_tan},
		{"asin",				n2i_bifunc_asin},
		{"acos",				n2i_bifunc_acos},
		{"atan",				n2i_bifunc_atan},
		{"sqrt",				n2i_bifunc_sqrt},
		{"powf",				n2i_bifunc_powf},
		{"expf",				n2i_bifunc_expf},
		{"logf",				n2i_bifunc_logf},
		{"round",				n2i_bifunc_round},
		{"floor",				n2i_bifunc_floor},
		{"ceil",				n2i_bifunc_ceil},
		{"lerpf@n2",			n2i_bifunc_lerpf},
		{"setease",				n2i_bifunc_setease},
		{"getease",				n2i_bifunc_getease},
		{"geteasef",			n2i_bifunc_geteasef},
		{"ease@n2",				n2i_bifunc_ease_n2},
		{"strlen",				n2i_bifunc_strlen},
		{"getstr",				n2i_bifunc_getstr},
		{"strrep",				n2i_bifunc_strrep},
		{"instr",				n2i_bifunc_instr},
		{"strmid",				n2i_bifunc_strmid},
		{"strtrim",				n2i_bifunc_strtrim},
		{"strf",				n2i_bifunc_strf},
		{"getpath",				n2i_bifunc_getpath},
		{"cnvwtos",				n2i_bifunc_cnvwtos},
		{"cnvstow",				n2i_bifunc_cnvstow},
#if N2_CONFIG_USE_ENCODING_CP932
		{"cnvatos",				n2i_bifunc_cnvatos},
		{"cnvstoa",				n2i_bifunc_cnvstoa},
#endif
		{"reintfb2d@n2",		n2i_bifunc_reintfb2d_n2},
		{"reintd2fb@n2",		n2i_bifunc_reintd2fb_n2},
		{"notesel",				n2i_bifunc_notesel},
		{"noteunsel",			n2i_bifunc_noteunsel},
		{"noteadd"	,			n2i_bifunc_noteadd},
		{"notedel"	,			n2i_bifunc_notedel},
		{"noteget"	,			n2i_bifunc_noteget},
		{"assert",				n2si_bifunc_assert},
		{"logmes",				n2si_bifunc_logmes},
		{"newmod",				n2i_bifunc_newmod},
		{"delmod",				n2i_bifunc_delmod},
		{"gettime",				n2i_bifunc_gettime},
		{"bload",				n2i_bifunc_bload},
		{"bsave",				n2i_bifunc_bsave},
		{NULL,					NULL}
	};
	n2_str_t tstr;
	n2_str_init(&tstr);
	for (size_t i = 0; builtins[i].name_; ++i)
	{
		n2_naming_compute(state, builtins[i].name_, SIZE_MAX, NULL, NULL, &tstr, NULL);
		const int funcindex = n2_functable_register(state, e->functable_, tstr.str_);
		n2_func_t* func = n2_functable_peek(e->functable_, funcindex);
		N2_ASSERT(func);
		n2i_func_setas_callback(state, func, N2_FUNC_INTERNAL, builtins[i].callback_, NULL);
	}
	n2_str_teardown(state, &tstr);

	e->is_basics_bounded_ = N2_TRUE;
}

//=============================================================================
// コンソール組み込み機能

static int n2i_bifunc_print(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	for (int i =0 ; i < arg_num; ++i)
	{
		const n2_value_t* a = n2e_funcarg_getarg(arg, i);
		n2_str_t* s = n2e_funcarg_eval_str(arg, a);
		if (s)
		{
			n2i_printf(arg->state_, "%s", s->str_);
			n2_str_free(arg->state_, s);
		}
	}
	return 0;
}

static int n2i_bifunc_mes(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	for (int i = 0 ; i < arg_num; ++i)
	{
		const n2_value_t* a = n2e_funcarg_getarg(arg, i);
		n2_str_t* s = n2e_funcarg_eval_str(arg, a);
		if (s)
		{
			n2i_printf(arg->state_, "%s", s->str_);
			n2_str_free(arg->state_, s);
		}
	}
	n2i_printf(arg->state_, "\n");
	return 0;
}

#if 0
static int n2i_bifuncinput(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if ( arg_num < 2 )
	{
		raise_error( "input：引数がたりません" );
	}
	if ( arg_num > 3 )
	{
		raise_error( "input：引数が多すぎます" );
	}

	const auto arg_start = -arg_num;
	const auto v = stack_peek( s->stack_, arg_start );
	if ( v->type_ != VALUE_VARIABLE )
	{
		raise_error( "input：対象が変数ではありません" );
	}
	if ( v->index_ > 0 )
	{
		raise_error( "input：対象の変数が配列として指定されています" );
	}

	const auto n = stack_peek( s->stack_, arg_start +1 );
	const auto len = value_calc_int( *n ) +1;

	const auto mode = ( arg_num>2 ? value_calc_int( *stack_peek( s->stack_, arg_start +2 ) ) : 0 );

	auto buf = create_string( len );
	int w =0;
	for( ; ; )
	{
		if ( w >= len )
		{ break; }

		const auto c = getchar();
		if ( c == EOF )
		{ break; }

		const auto ch = static_cast<char>( c );

		if ( mode==1 && ch=='\n' )
		{ break; }

		if ( mode==2 )
		{
			if ( ch == '\r' )
			{
				const auto nc =getchar();
				if ( static_cast<char>(nc) == '\n' )
				{ break; }
				ungetc( nc, stdin );
			}
			else if ( ch == '\n' )
			{ break; }
		}

		buf[w] = static_cast<char>( ch );
		++w;
	}
	buf[w] = '\0';

	auto t = create_value_move( buf );
	variable_set( e->variable_table_, *t, v->variable_->name_, 0 );
	destroy_value( t );

	s->strsize_ = w;

	stack_pop( s->stack_, arg_num );
}
#endif

static void n2i_environment_bind_console_builtins(n2_state_t* state, n2_environment_t* e)
{
	if (e->is_consoles_bounded_) { return; }

	static const struct 
	{
		const char* name_;
		n2_func_callback_t callback_;
	} builtins[] =
	{
		{"print@n2",			n2i_bifunc_print},
		{"mes",					n2i_bifunc_mes},
		{NULL,					NULL}
	};
	n2_str_t tstr;
	n2_str_init(&tstr);
	for (size_t i = 0; builtins[i].name_; ++i)
	{
		n2_naming_compute(state, builtins[i].name_, SIZE_MAX, NULL, NULL, &tstr, NULL);
		const int funcindex = n2_functable_register(state, e->functable_, tstr.str_);
		n2_func_t* func = n2_functable_peek(e->functable_, funcindex);
		N2_ASSERT(func);
		n2i_func_setas_callback(state, func, N2_FUNC_INTERNAL, builtins[i].callback_, NULL);
	}
	n2_str_teardown(state, &tstr);

	e->is_consoles_bounded_ = N2_TRUE;
}

//=============================================================================
// 標準組み込み機能

#define N2SI_DEFINE_BISYSVAR_SE_1I(name) \
	static int n2si_sysvar_ex_##name(const n2_funcarg_t* arg) \
	{ \
		N2_ASSERT(arg->fiber_->environment_->standard_environment_); \
		n2e_funcarg_pushi(arg, arg->fiber_->environment_->standard_environment_->name##_); \
		return 1; \
	} \
	static n2_bool_t n2si_sysvar_ex_inspect_##name(n2_state_t* state, n2_fiber_t* f, n2_str_t* dst, n2_str_t* dst_type, const n2_sysvar_ex_t* sysvarex) \
	{ \
		N2_UNUSE(sysvarex); \
		N2_ASSERT(f->environment_->standard_environment_); \
		n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, N2_SCAST(n2_valint_t, f->environment_->standard_environment_->name##_)); \
		n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); \
		return N2_TRUE; \
	}

#define N2SI_DEFINE_BISYSVAR_SE_1F(name) \
	static int n2si_sysvar_ex_##name(const n2_funcarg_t* arg) \
	{ \
		N2_ASSERT(arg->fiber_->environment_->standard_environment_); \
		n2e_funcarg_pushf(arg, arg->fiber_->environment_->standard_environment_->name##_); \
		return 1; \
	} \
	static n2_bool_t n2si_sysvar_ex_inspect_##name(n2_state_t* state, n2_fiber_t* f, n2_str_t* dst, n2_str_t* dst_type, const n2_sysvar_ex_t* sysvarex) \
	{ \
		N2_UNUSE(sysvarex); \
		N2_ASSERT(f->environment_->standard_environment_); \
		n2_str_fmt_to(state, dst, "%" N2_VALFLOAT_PRI, f->environment_->standard_environment_->name##_); \
		n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_FLOAT, NULL), SIZE_MAX); \
		return N2_TRUE; \
	}

N2SI_DEFINE_BISYSVAR_SE_1F(ginfo_accx);
N2SI_DEFINE_BISYSVAR_SE_1F(ginfo_accy);
N2SI_DEFINE_BISYSVAR_SE_1F(ginfo_accz);

N2SI_DEFINE_BISYSVAR_SE_1I(selected_window_index);

N2SI_DEFINE_BISYSVAR_SE_1I(imgunpackw);
N2SI_DEFINE_BISYSVAR_SE_1I(imgunpackh);

#define N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(name, defval) \
	static int n2si_sysvar_ex_##name(const n2_funcarg_t* arg) \
	{ \
		n2s_environment_t* se = arg->fiber_->environment_->standard_environment_; \
		N2_ASSERT(se); \
		n2s_window_t* sel_win = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL); \
		n2e_funcarg_pushi(arg, sel_win ? N2_SCAST(n2_valint_t, sel_win->name##_) : defval); \
		return 1; \
	} \
	static n2_bool_t n2si_sysvar_ex_inspect_##name(n2_state_t* state, n2_fiber_t* f, n2_str_t* dst, n2_str_t* dst_type, const n2_sysvar_ex_t* sysvarex) \
	{ \
		N2_UNUSE(sysvarex); \
		n2s_environment_t* se = f->environment_->standard_environment_; \
		N2_ASSERT(se); \
		n2s_window_t* sel_win = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL); \
		n2_str_fmt_to(state, dst, "%" N2_VALINT_PRI, sel_win ? N2_SCAST(n2_valint_t,sel_win->name##_) : defval); \
		n2_str_set(state, dst_type, n2_valuetype_name(N2_VALUE_INT, NULL), SIZE_MAX); \
		return N2_TRUE; \
	}

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(width, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(height, 0);

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(mousex, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(mousey, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(mousew, 0);

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(ginfo_r, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(ginfo_g, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(ginfo_b, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(ginfo_a, 0);

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(posx, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(posy, 0);

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(mesx, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(mesy, 0);

N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(hwnd, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(hdc, 0);
N2SI_DEFINE_BISYSVAR_SE_SWIN_1I(hinstance, 0);

static int n2si_bifunc_gsel(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "gsel：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 2); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t id = idval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* modeval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t mode = modeval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, modeval) : 0;
	n2s_window_t* nw = id >= 0 ? n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL) : NULL;
	if (!nw) { n2e_funcarg_raise(arg, "gsel：スクリーンID（%" N2_VALINT_PRI "）が初期化されていません。", id); return -1; }
	const int prev_selected_index = se->selected_window_index_;
	const int next_selected_index = N2_SCAST(int, id);
	if (prev_selected_index != next_selected_index)
	{
		n2si_environment_flush_commandbuffer(arg->state_, se);
	}
	se->selected_window_index_ = next_selected_index;
#if N2_CONFIG_USE_SDL_LIB
	if (nw->window_)
	{
		switch (mode)
		{
		case -1:
			SDL_HideWindow(nw->window_);
			break;
		case 1:
		case 2:
			SDL_ShowWindow(nw->window_); SDL_RaiseWindow(nw->window_);
#if N2_PLATFORM_IS_WINDOWS
			SDL_SysWMinfo wminfo;
			SDL_VERSION(&wminfo.version);
			if (SDL_GetWindowWMInfo(nw->window_, &wminfo) && wminfo.info.win.window)
			{
				SetWindowPos(wminfo.info.win.window, mode == 2 ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}
#endif
			break;
		default:	break;
		}
	}
#else
	N2_UNUSE(mode);
#endif
	return 0;
}

static int n2si_bifunc_pos(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "pos：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 2); return -1; }
	if (arg_num <= 0) { return 0; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* xval = n2e_funcarg_getarg(arg, 0);
	if (xval && n2_value_get_type(xval) != N2_VALUE_NIL) { nw->posx_ = n2e_funcarg_eval_int(arg, xval); }
	const n2_value_t* yval = n2e_funcarg_getarg(arg, 1);
	if (yval && n2_value_get_type(yval) != N2_VALUE_NIL) { nw->posy_ = n2e_funcarg_eval_int(arg, yval); }
	return 0;
}

static int n2si_bifunc_color(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "color：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* rval = n2e_funcarg_getarg(arg, 0);
	nw->ginfo_r_ = n2si_u8channel_clamp(N2_SCAST(int, rval ? n2e_funcarg_eval_int(arg, rval) : 0));
	const n2_value_t* gval = n2e_funcarg_getarg(arg, 1);
	nw->ginfo_g_ = n2si_u8channel_clamp(N2_SCAST(int, gval ? n2e_funcarg_eval_int(arg, gval) : 0));
	const n2_value_t* bval = n2e_funcarg_getarg(arg, 2);
	nw->ginfo_b_ = n2si_u8channel_clamp(N2_SCAST(int, bval ? n2e_funcarg_eval_int(arg, bval) : 0));
	return 0;
}

static int n2si_bifunc_rgbcolor(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "rgbcolor：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* rgbval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t rgb = n2e_funcarg_eval_int(arg, rgbval);
	nw->ginfo_r_ = N2_SCAST(uint8_t, (rgb >> 16) & 0xff);
	nw->ginfo_g_ = N2_SCAST(uint8_t, (rgb >> 8) & 0xff);
	nw->ginfo_b_ = N2_SCAST(uint8_t, (rgb >> 0) & 0xff);
	return 0;
}

static int n2si_bifunc_hsvcolor(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "hsvcolor：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 0);
	const float h = N2_SCAST(float, N2_FMOD(N2_SCAST(double, hval ? n2e_funcarg_eval_int(arg, hval) : 0) / 192, 1));
	const n2_value_t* sval = n2e_funcarg_getarg(arg, 1);
	const float s = n2_float_saturate(N2_SCAST(float, sval ? n2e_funcarg_eval_int(arg, sval) : 0) / 255);
	const n2_value_t* vval = n2e_funcarg_getarg(arg, 2);
	const float v = n2_float_saturate(N2_SCAST(float, vval ? n2e_funcarg_eval_int(arg, vval) : 0) / 255);
	const n2s_u8color_t rgb = n2s_fcolor_to_u8color(n2s_hsv_to_fcolor(n2_fvec3(h, s, v), 0));
	nw->ginfo_r_ = rgb.r_;
	nw->ginfo_g_ = rgb.g_;
	nw->ginfo_b_ = rgb.b_;
	return 0;
}

static int n2si_bifunc_objcolor(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "objcolor：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* rval = n2e_funcarg_getarg(arg, 0);
	nw->objcolor_r_ = n2si_u8channel_clamp(N2_SCAST(int, rval ? n2e_funcarg_eval_int(arg, rval) : 0));
	const n2_value_t* gval = n2e_funcarg_getarg(arg, 1);
	nw->objcolor_g_ = n2si_u8channel_clamp(N2_SCAST(int, gval ? n2e_funcarg_eval_int(arg, gval) : 0));
	const n2_value_t* bval = n2e_funcarg_getarg(arg, 2);
	nw->objcolor_b_ = n2si_u8channel_clamp(N2_SCAST(int, bval ? n2e_funcarg_eval_int(arg, bval) : 0));
	return 0;
}

static int n2si_bifunc_gmode(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "gmode：引数の数（%d）が期待（0 - %d）と違います", arg_num, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* copymodeval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t copymode = copymodeval && n2_value_get_type(copymodeval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, copymodeval) : 0;
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : 32;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : 32;
	const n2_value_t* aval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t a = aval && n2_value_get_type(aval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, aval) : 0;
	if (w < 0 || h < 0) { n2e_funcarg_raise(arg, "gmode：コピーするサイズ（W=%" N2_VALINT_PRI ", H=%" N2_VALINT_PRI "）が不正です", w, h); return -1; }
	nw->gmode_ = N2_SCAST(n2s_gmode_e, (copymode >= 0 && copymode < N2S_MAX_GMODE ? copymode : N2S_GMODE_COPY));
	nw->gmode_copy_width_ = w; nw->gmode_copy_height_ = h;
	nw->ginfo_a_ = n2si_u8channel_clamp(N2_SCAST(int, a));
	return 0;
}

static int n2si_bifunc_gmulcolor(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "gmulcolor：引数の数（%d）が期待（0 - %d）と違います", arg_num, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* rval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t r = rval && n2_value_get_type(rval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, rval) : 255;
	const n2_value_t* gval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t g = gval && n2_value_get_type(gval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, gval) : 255;
	const n2_value_t* bval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t b = bval && n2_value_get_type(bval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, bval) : 255;
	nw->ginfo_mulr_ = n2si_u8channel_clamp(N2_SCAST(int, r));
	nw->ginfo_mulg_ = n2si_u8channel_clamp(N2_SCAST(int, g));
	nw->ginfo_mulb_ = n2si_u8channel_clamp(N2_SCAST(int, b));
	return 0;
}

static int n2si_bifunc_redraw(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "redraw：引数の数（%d）が期待（0 - %d）と違います", arg_num, 5); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* modeval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t mode = modeval && n2_value_get_type(modeval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, modeval) : 1;
	// その他のパラメータは無視
	nw->redraw_ = (mode & 1) ? N2_TRUE : N2_FALSE;
	if ((mode & 2) == 0 && nw->redraw_) { n2si_environment_present_window(arg->state_, se, nw); }
	return 0;
}

#if N2_CONFIG_USE_IMAGE_READ_LIB
static int n2si_bifunc_imgunpack_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 4) { n2e_funcarg_raise(arg, "imgunpack@n2：引数の数（%d）が期待（%d - %d）と違います", arg_num, 2, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const n2_value_t* tovarval = n2e_funcarg_getarg(arg, 0);
	if (!tovarval || tovarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "imgunpack@n2：書き込み対象が変数ではありません"); return -1; }
	if (tovarval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "imgunpack@n2：書き込み対象の変数として変数（%s）の要素（%d）が指定されています", tovarval->field_.varvalue_.var_->name_, tovarval->field_.varvalue_.aptr_); return -1; }
	n2_variable_t* tovar = tovarval->field_.varvalue_.var_;
	const n2_value_t* fromvarval = n2e_funcarg_getarg(arg, 1);
	if (!fromvarval || fromvarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "imgunpack@n2：読み込み対象が変数ではありません"); return -1; }
	n2_variable_t* fromvar = fromvarval->field_.varvalue_.var_;
	const int fromaptr = fromvarval->field_.varvalue_.aptr_;
	size_t from_data_size = 0;
	const void* from_data = n2_variable_map_data(&from_data_size, fromvar, fromaptr);
	if (!from_data || from_data_size <= 0) { n2e_funcarg_raise(arg, "imgunpack@n2：読み込み対象の変数はバイト列として読み込めるメモリ領域を持っていません"); return -1; }
	const n2_value_t* sizeval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t size = sizeval && sizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sizeval) : -1;
	const n2_value_t* offsetval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t offset = offsetval && offsetval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, offsetval) : 0;
	if (offset < 0 || offset > N2_SCAST(n2_valint_t, from_data_size)) { n2e_funcarg_raise(arg, "imgunpack@n2：読み込みオフセット（%" N2_VALINT_PRI "）が読み込める範囲（0 - %zu）外です", offset, from_data_size); return -1; }
	const n2_valint_t readable_size = N2_SCAST(n2_valint_t, from_data_size) - offset;
	if (size < 0 || size > readable_size) { size = readable_size; }
	n2_buffer_t imgbin;
	n2_buffer_init(&imgbin);
	size_t imgw = 0, imgh = 0;
	if (n2h_image_read(arg->state_, &imgbin, &imgw, &imgh, n2_cptr_offset(from_data, offset), N2_SCAST(size_t, size)))
	{
		size_t length[N2_VARIABLE_DIM] = {imgw * imgh, 0};
		n2_variable_prepare(arg->state_, tovar, N2_VALUE_INT, 0, length);
		size_t to_data_size = 0;
		n2_valint_t* to_data = N2_RCAST(n2_valint_t*, n2_variable_map_data(&to_data_size, tovar, -1));
		N2_ASSERT(to_data_size >= sizeof(n2_valint_t) * imgw * imgh);
		N2_ASSERT(to_data);
		for (size_t y = 0; y < imgh; ++y) for (size_t x = 0; x < imgw; ++x)
		{
			const uint8_t* fromp = N2_RCAST(const uint8_t*, imgbin.data_) + ((y * imgw + x) * 4);
			n2_valint_t* top = to_data + (y * imgw + x);
			*top = (fromp[3] << 24) | (fromp[0] << 16) | (fromp[1] << 8) | (fromp[2] << 0);// ARGB
		}
		se->imgunpackw_ = N2_SCAST(n2_valint_t, imgw);
		se->imgunpackh_ = N2_SCAST(n2_valint_t, imgh);
	}
	else
	{
		imgw = imgh = 0;
	}
	n2_buffer_teardown(arg->state_, &imgbin);
	n2e_funcarg_pushi(arg, imgw > 0 && imgh > 0 ? 1 : 0);
	return 1;
}
#endif// N2_CONFIG_USE_IMAGE_READ_LIB

#if N2_CONFIG_USE_IMAGE_WRITE_LIB
static int n2si_bifunc_imgpack_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 4 || arg_num > 5) { n2e_funcarg_raise(arg, "imgpack@n2：引数の数（%d）が期待（%d - %d）と違います", arg_num, 4, 5); return -1; }
	const n2_value_t* tovarval = n2e_funcarg_getarg(arg, 0);
	if (!tovarval || tovarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "imgpack@n2：書き込み対象が変数ではありません"); return -1; }
	if (tovarval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "imgpack@n2：書き込み対象の変数として変数（%s）の要素（%d）が指定されています", tovarval->field_.varvalue_.var_->name_, tovarval->field_.varvalue_.aptr_); return -1; }
	n2_variable_t* tovar = tovarval->field_.varvalue_.var_;
	const n2_value_t* fromvarval = n2e_funcarg_getarg(arg, 1);
	if (!fromvarval || fromvarval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "imgpack@n2：読み込み対象が変数ではありません"); return -1; }
	if (fromvarval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "imgpack@n2：読み込み対象の変数として変数（%s）の要素（%d）が指定されています", fromvarval->field_.varvalue_.var_->name_, fromvarval->field_.varvalue_.aptr_); return -1; }
	if (fromvarval->field_.varvalue_.var_->type_ != N2_VALUE_INT) { n2e_funcarg_raise(arg, "imgpack@n2：読み込み対象の変数がint型ではありません"); return -1; }
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t w = wval && wval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : 0;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t h = hval && hval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : 0;
	const n2_value_t* fileformatval = n2e_funcarg_getarg(arg, 4);
	const n2_valint_t fileformat = fileformatval && fileformatval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, fileformatval) : N2_IMAGE_FILE_PNG;
	if (w <= 0 || h <= 0) { n2e_funcarg_raise(arg, "imgpack@n2：イメージのサイズ指定（%" N2_VALINT_PRI " x %" N2_VALINT_PRI "）が不正です", w, h); return -1; }
	n2_variable_t* fromvar = fromvarval->field_.varvalue_.var_;
	if (fromvar->element_num_ < N2_SCAST(size_t, w) * N2_SCAST(size_t, h)) { n2e_funcarg_raise(arg, "imgpack@n2：読み込み対象の変数の要素数（%zu）がイメージのサイズ（%" N2_VALINT_PRI " x %" N2_VALINT_PRI "）より小さいです", fromvar->element_num_, w, h); return -1; }
	if (fileformat < 0 || fileformat > N2_MAX_IMAGE_FILE) { n2e_funcarg_raise(arg, "imgpack@n2：イメージのファイルフォーマット指定（%" N2_VALINT_PRI "）が不正です", fileformat); return -1; }
	size_t from_data_size = 0;
	const n2_valint_t* from_data = N2_RCAST(const n2_valint_t*, n2_variable_map_data(&from_data_size, fromvar, -1));
	n2_buffer_t imgraw, imgbin;
	n2_buffer_init(&imgraw); n2_buffer_init(&imgbin);
	n2_buffer_reserve(arg->state_, &imgraw, N2_SCAST(size_t, w) * N2_SCAST(size_t, h) * 4);
	for (n2_valint_t y = 0; y < h; ++y) for (n2_valint_t x = 0; x < w; ++x)
	{
		const n2_valint_t fromp = from_data[y * w + x];
		uint8_t* top = N2_RCAST(uint8_t*, imgraw.data_) + (y * w + x) * 4;
		// ARGB
		top[0] = (fromp >> 16) & 0xff;
		top[1] = (fromp >> 8) & 0xff;
		top[2] = (fromp >> 0) & 0xff;
		top[3] = (fromp >> 24) & 0xff;
	}
	const n2_bool_t success = n2h_image_write(arg->state_, &imgbin, N2_SCAST(n2_image_file_e, fileformat), imgraw.data_, imgraw.buffer_size_, N2_SCAST(size_t, w), N2_SCAST(size_t, h), 80);
	if (success)
	{
		const size_t length[N2_VARIABLE_DIM] = {1, 0};
		n2_variable_prepare(arg->state_, tovar, N2_VALUE_STRING, imgbin.size_ + 1/*null terminate*/, length);
		N2_ASSERT(tovar->type_ == N2_VALUE_STRING);
		n2_valstr_t* tostr = n2_variable_get_str(tovar, -1);
		N2_ASSERT(tostr);
		N2_ASSERT(tostr->buffer_size_ > imgbin.size_);
		N2_MEMCPY(tostr->str_, imgbin.data_, imgbin.size_);
		tostr->size_ = imgbin.size_;
		tostr->str_[imgbin.size_] = '\0';
		arg->fiber_->strsize_ = imgbin.size_;
		// @warning assuming char bit width is equal to uint8_t
	}
	n2_buffer_teardown(arg->state_, &imgraw);
	n2_buffer_teardown(arg->state_, &imgbin);
	n2e_funcarg_pushi(arg, success ? 1 : 0);
	return 1;
}
#endif// N2_CONFIG_USE_IMAGE_WRITE_LIB

#if N2_CONFIG_USE_SDL_LIB
static int n2si_bifunc_screen(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "screen：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t id = idval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "screen：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	if (id != 0) { n2e_funcarg_raise(arg, "screen：スクリーンID（%" N2_VALINT_PRI "）は0以外使えません", id); return -1; }
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_window_default_width_);
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_window_default_height_);
	if (w < N2S_WINDOW_SIZE_MIN || w > N2S_WINDOW_SIZE_MAX || h < N2S_WINDOW_SIZE_MIN || h > N2S_WINDOW_SIZE_MAX) { n2e_funcarg_raise(arg, "screen：ウィンドウの大きさの指定（x=%" N2_VALINT_PRI ", y=%" N2_VALINT_PRI "）が不正（サポートされてないサイズ）です", w, h); return -1; }
	n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく
	n2s_window_t* mw = n2s_windowarray_peekv(se->windows_, 0, NULL);
	N2_ASSERT(mw);
	n2s_window_t* nw = NULL;
	SDL_GL_MakeCurrent(mw->window_, mw->gl_context_);// コンテキストスイッチ
	if (id == 0)
	{
		// 0は特殊処理。GL_Contextなどを作り直さないため。
		const size_t pw = mw->width_;
		const size_t ph = mw->height_;
		mw->width_ = N2_SCAST(size_t, w);
		mw->height_ = N2_SCAST(size_t, h);
		if (mw->width_ != pw && mw->height_ != ph)
		{
			n2si_texturebuffer_resize(arg->state_, mw->texturebuffer_, mw->width_, mw->height_, N2_FALSE);
			n2si_texturebuffer_resize(arg->state_, mw->drawcachebuffer_, mw->width_, mw->height_, N2_FALSE);
			n2si_window_reset_state(arg->state_, se, mw);
			if (mw->window_)
			{
				SDL_ShowWindow(mw->window_);
				SDL_SetWindowSize(mw->window_, N2_SCAST(int, mw->width_), N2_SCAST(int, mw->height_));
				{
					// 中心位置固定
					int posx = 0, posy = 0;
					SDL_GetWindowPosition(mw->window_, &posx, &posy);
					SDL_SetWindowPosition(mw->window_, posx - (N2_SCAST(int, mw->width_) - N2_SCAST(int, pw)) / 2, posy - (N2_SCAST(int, mw->height_) - N2_SCAST(int, ph)) / 2);
				}
				SDL_RaiseWindow(mw->window_);
			}
		}
		nw = mw;
	}
	else
	{
		nw = n2si_window_alloc(arg->state_, se, N2S_WINDOW_SCREEN, N2_SCAST(size_t, w), N2_SCAST(size_t, h), 0, N2_FALSE);
		if (!nw) { n2e_funcarg_raise(arg, "screen：ウィンドウ生成に失敗しました（サイズx=%" N2_VALINT_PRI "、y=%" N2_VALINT_PRI "）", w, h); return -1; }
		n2si_window_register(arg->state_, se, nw, N2_SCAST(int, id));
		SDL_RaiseWindow(nw->window_);
	}
	N2_ASSERT(nw);
	n2s_texture_fill_color(&nw->texturebuffer_->texture_, N2S_COLOR_WHITE);
	n2s_texture_submit(arg->state_, &nw->texturebuffer_->texture_, N2_TRUE);
	se->selected_window_index_ = N2_SCAST(int, id);// 操作先を変更
	n2si_environment_fullsync_gmode_commandbuffer(arg->state_, se, se->commandbuffer_);
	return 0;
}

static int n2si_bifunc_buffer(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "buffer：引数の数（%d）が期待（0 - %d）より多いです", arg_num, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t id = idval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "buffer：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	if (id == 0) { n2e_funcarg_raise(arg, "buffer：スクリーンID（%" N2_VALINT_PRI "）はbufferに指定できません", id); return -1; }
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_window_default_width_);
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_window_default_height_);
	if (w <= 0 || h <= 0) { n2e_funcarg_raise(arg, "buffer：スクリーンの大きさの指定（x=%" N2_VALINT_PRI ", y=%" N2_VALINT_PRI "）が不正です", w, h); return -1; }
	// それ以降のパラメータは無視
	n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく
	n2s_window_t* mw = n2s_windowarray_peekv(se->windows_, 0, NULL);
	N2_ASSERT(mw);
	SDL_GL_MakeCurrent(mw->window_, mw->gl_context_);// コンテキストスイッチ
	n2s_window_t* nw = n2si_window_alloc(arg->state_, se, N2S_WINDOW_OFFSCREEN, N2_SCAST(size_t, w), N2_SCAST(size_t, h), 0, N2_FALSE);
	if (!nw) { n2e_funcarg_raise(arg, "buffer：ウィンドウ生成に失敗しました"); return -1; }
	n2si_window_register(arg->state_, se, nw, N2_SCAST(int, id));
	se->selected_window_index_ = N2_SCAST(int, id);// 操作先を変更
	n2si_environment_fullsync_gmode_commandbuffer(arg->state_, se, se->commandbuffer_);
	return 0;
}

static int n2si_bifunc_cls(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 0 || arg_num > 1) { n2e_funcarg_raise(arg, "cls：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 1); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく
	const n2_value_t* colval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t col = colval && colval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, colval) : 0;
	n2s_u8color_t ccol = n2s_u8color(255, 255, 255, 255);
	switch (col)
	{
	case 1:		ccol = n2s_u8color(192, 192, 192, 255); break;
	case 2:		ccol = n2s_u8color(128, 128, 128, 255); break;
	case 3:		ccol = n2s_u8color(64, 64, 64, 255); break;
	case 4:		ccol = n2s_u8color(0, 0, 0, 255); break;
	default:	break;
	}
	n2si_texturebuffer_clear(arg->state_, nw->texturebuffer_, ccol);
	n2si_window_reset_state(arg->state_, se, nw);
	n2si_environment_fullsync_gmode_commandbuffer(arg->state_, se, se->commandbuffer_);
	return 0;
}

static int n2si_bifunc_title(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "title：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	const n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	n2si_window_set_title(arg->state_, nw, str->str_);
	return 0;
}

static int n2si_bifunc_wait(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "wait：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	n2_valint_t wait_val = n2e_funcarg_eval_int(arg, val);
	arg->fiber_->fiber_state_ = N2_FIBER_STATE_YIELD_AWAIT;
	arg->fiber_->yield_await_duration_ms_ = N2_MAX(0, wait_val) * 10;
	return 0;
}

static int n2si_bifunc_await(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "await：引数の数（%d）が期待（0 - %d）と違います", arg_num, 1); return -1; }
	const n2_value_t* val = n2e_funcarg_getarg(arg, 0);
	n2_valint_t wait_val = val && val->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, val) : 0;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const uint64_t now_time = SDL_GetPerformanceCounter();
	int64_t wait_ms = 0;
	if (wait_val > 0)
	{
		const uint64_t diff_ms = (now_time - se->last_async_time_) * 1000 / SDL_GetPerformanceFrequency();
		wait_ms = N2_SCAST(int64_t, wait_val) - N2_SCAST(int64_t, diff_ms);
	}
	arg->fiber_->fiber_state_ = N2_FIBER_STATE_YIELD_AWAIT;
	arg->fiber_->yield_await_duration_ms_ = N2_SCAST(n2_valint_t, N2_MAX(0, wait_ms));
	se->last_async_time_ = now_time;
	return 0;
}

static int n2si_bifunc_systimer_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 0) { n2e_funcarg_raise(arg, "systimer@n2：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	n2e_funcarg_pushf(arg, N2_SCAST(n2_valfloat_t, SDL_GetPerformanceCounter()) / N2_SCAST(n2_valfloat_t, SDL_GetPerformanceFrequency()) * 1000);
	return 1;
}

static int n2si_bifunc_texfilter_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "line：引数の数（%d）が期待（0 - %d）と違います", arg_num, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t id = idval && n2_value_get_type(idval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : -1;
	if (id < 0) { id = se->selected_window_index_; }
	const n2_value_t* filterval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t filter = filterval && n2_value_get_type(filterval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, filterval) : -1;
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "texfilter@n2：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	n2s_window_t* srcw = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, id), NULL);
	if (!srcw) { n2e_funcarg_raise(arg, "texfilter@n2：対象のスクリーンID（" N2_VALINT_PRI "）がまだ初期化されていません", id); return -1; }
	if (filter >= N2S_MAX_SAMPLERFILTER) { n2e_funcarg_raise(arg, "texfilter@n2：テクスチャフィルタの値（" N2_VALINT_PRI "）が不正です", filter); return -1; }
	int res = 0;
	if (filter >= 0) { n2s_texture_set_samplerfilter(arg->state_, &srcw->texturebuffer_->texture_, N2_SCAST(n2s_samplerfilter_e, filter)); }
	else { n2e_funcarg_pushi(arg, srcw->texturebuffer_->texture_.samplerfilter_); res = 1; }
	return res;
}

static int n2si_bifunc_line_common(const n2_funcarg_t* arg, n2_bool_t independent_gmode)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "line：引数の数（%d）が期待（0 - %d）と違います", arg_num, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t ex = exval && n2_value_get_type(exval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, exval) : 0;
	const n2_value_t* eyval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t ey = eyval && n2_value_get_type(eyval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, eyval) : 0;
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : nw->posx_;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : nw->posy_;
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	if (independent_gmode) { n2s_commandbuffer_set_program(arg->state_, se->commandbuffer_, N2S_GPROGRAM_2D); n2s_commandbuffer_set_renderstate(arg->state_, se->commandbuffer_, N2S_RENDERSTATE_2D_NOBLEND); }
	const n2s_u8color_t c = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, independent_gmode ? 255 : nw->ginfo_a_);
	n2s_commandbuffer_line(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, sx), N2_SCAST(float, sy), 0), n2_fvec3(N2_SCAST(float, ex), N2_SCAST(float, ey), 0), c, 1);
	nw->posx_ = ex; nw->posy_ = ey;
	return 0;
}
static int n2si_bifunc_line(const n2_funcarg_t* arg) { return n2si_bifunc_line_common(arg, N2_TRUE); }
static int n2si_bifunc_line_n2(const n2_funcarg_t* arg) { return n2si_bifunc_line_common(arg, N2_FALSE); }

static int n2si_bifunc_boxf_common(const n2_funcarg_t* arg, n2_bool_t independent_gmode)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 4) { n2e_funcarg_raise(arg, "boxf：引数の数（%d）が期待（0 - %d）と違います", arg_num, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t ex = exval && n2_value_get_type(exval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, exval) : N2_SCAST(n2_valint_t, nw->width_);
	const n2_value_t* eyval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t ey = eyval && n2_value_get_type(eyval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, eyval) : N2_SCAST(n2_valint_t, nw->height_);
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	if (independent_gmode) { n2s_commandbuffer_set_program(arg->state_, se->commandbuffer_, N2S_GPROGRAM_2D); n2s_commandbuffer_set_renderstate(arg->state_, se->commandbuffer_, N2S_RENDERSTATE_2D_NOBLEND); }
	const n2s_u8color_t c = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, independent_gmode ? 255 : nw->ginfo_a_);
	n2s_commandbuffer_rect(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, sx), N2_SCAST(float, sy), 0), n2_fvec3(N2_SCAST(float, ex + 1), N2_SCAST(float, ey + 1), 0), c);
	return 0;
}
static int n2si_bifunc_boxf(const n2_funcarg_t* arg) { return n2si_bifunc_boxf_common(arg, N2_TRUE); }
static int n2si_bifunc_boxf_n2(const n2_funcarg_t* arg) { return n2si_bifunc_boxf_common(arg, N2_FALSE); }

static int n2si_bifunc_circle_common(const n2_funcarg_t* arg, n2_bool_t independent_gmode)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "circle：引数の数（%d）が期待（0 - %d）と違います", arg_num, 5); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t ex = exval && n2_value_get_type(exval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, exval) : N2_SCAST(n2_valint_t, nw->width_);
	const n2_value_t* eyval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t ey = eyval && n2_value_get_type(eyval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, eyval) : N2_SCAST(n2_valint_t, nw->height_);
	const n2_value_t* fval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t f = fval && n2_value_get_type(fval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, fval) : 1;
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	if (independent_gmode) { n2s_commandbuffer_set_program(arg->state_, se->commandbuffer_, N2S_GPROGRAM_2D); n2s_commandbuffer_set_renderstate(arg->state_, se->commandbuffer_, N2S_RENDERSTATE_2D_NOBLEND); }
	const n2s_u8color_t c = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, independent_gmode ? 255 : nw->ginfo_a_);
	const n2_fvec3_t center = n2_fvec3((N2_SCAST(float, sx) + N2_SCAST(float, ex)) * 0.5f, (N2_SCAST(float, sy) + N2_SCAST(float, ey)) * 0.5f, 0);
	const n2_fvec2_t scale = n2_fvec2(N2_SCAST(float, ex) - N2_SCAST(float, sx), N2_SCAST(float, ey) - N2_SCAST(float, sy));
	if (f) { n2s_commandbuffer_circle(arg->state_, se->commandbuffer_, center, scale, c, 64); }
	else { n2s_commandbuffer_circle_wire(arg->state_, se->commandbuffer_, center, scale, c, 1, 64); }
	return 0;
}
static int n2si_bifunc_circle(const n2_funcarg_t* arg) { return n2si_bifunc_circle_common(arg, N2_TRUE); }
static int n2si_bifunc_circle_n2(const n2_funcarg_t* arg) { return n2si_bifunc_circle_common(arg, N2_FALSE); }

static int n2si_bifunc_grect(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "grect：引数の数（%d）が期待（0 - %d）と違います", arg_num, 5); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* rotval = n2e_funcarg_getarg(arg, 2);
	n2_valfloat_t rot = rotval && n2_value_get_type(rotval) != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, rotval) : 0.0;
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : 0;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : 0;
	if (!wval || !hval) { n2e_funcarg_raise(arg, "grect：矩形のX・Yサイズが指定されていません"); return -1; }
	if (w <= 0 || h < 0) { return 0; }
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	const n2s_u8color_t c = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, nw->ginfo_a_);
	const n2_fvec3_t center = n2_fvec3(N2_SCAST(float, sx), N2_SCAST(float, sy), 0);
	const n2_fvec2_t scale = n2_fvec2(N2_SCAST(float, w), N2_SCAST(float, h));
	n2s_commandbuffer_rect_textured_rot(arg->state_, se->commandbuffer_, center, n2_fvec2(0.5f, 0.5f), scale, c, NULL, n2_fvec2(0, 0), n2_fvec2(0, 0), N2_SCAST(float, rot), 0, 0);
	return 0;
}

static int n2si_bifunc_gcopy(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "gcopy：引数の数（%d）が期待（0 - %d）と違います", arg_num, 5); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t id = idval && n2_value_get_type(idval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : nw->gmode_copy_width_;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : nw->gmode_copy_height_;
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "gcopy：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	if (id == se->selected_window_index_) { n2e_funcarg_raise(arg, "gcopy：自分自身のスクリーンID（" N2_VALINT_PRI "）をコピー元に指定することはできません", id); return -1; }
	n2s_window_t* srcw = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, id), NULL);
	if (!srcw) { n2e_funcarg_raise(arg, "gcopy：コピー元のスクリーンID（" N2_VALINT_PRI "）がまだ初期化されていません", id); return -1; }
	const n2_valint_t wsign = (w < 0 ? -1 : 1);
	const n2_valint_t hsign = (h < 0 ? -1 : 1);
	w = wsign * w; h = hsign * h;
	if (sx < 0) { w += sx; sx = 0; }
	if (sy < 0) { h += sy; sy = 0; }
	w = N2_MIN(w, N2_SCAST(n2_valint_t, srcw->width_) - sx);
	h = N2_MIN(h, N2_SCAST(n2_valint_t, srcw->height_) - sy);
	if (w <= 0 || h <= 0) { return 0; }
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	n2_valint_t psx = nw->posx_, psy = nw->posy_;
	n2_valint_t pex = psx + w, pey = psy + h;
	const n2s_u8color_t mulc = n2s_u8color(nw->ginfo_mulr_, nw->ginfo_mulg_, nw->ginfo_mulb_, nw->ginfo_a_);
	n2_fvec2_t uv0 = n2_fvec2(N2_SCAST(float, sx) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy) / N2_SCAST(float, srcw->height_)));
	n2_fvec2_t uv1 = n2_fvec2(N2_SCAST(float, sx + w) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy + h) / N2_SCAST(float, srcw->height_)));
	if (psx >= N2_SCAST(n2_valint_t, nw->width_) || psy >= N2_SCAST(n2_valint_t, nw->height_) || pex < 0 || pey < 0) { return 0; }// 範囲外
	n2s_commandbuffer_rect_textured_rot(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, psx), N2_SCAST(float, psy), 0), n2_fvec2(0, 0), n2_fvec2(N2_SCAST(float, w * wsign), N2_SCAST(float, h * hsign)), mulc, &srcw->texturebuffer_->texture_, uv0, uv1, 0, nw->width_, nw->height_);
	return 0;
}

static int n2si_bifunc_gzoom(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 8) { n2e_funcarg_raise(arg, "gzoom：引数の数（%d）が期待（%d - %d）と違います", arg_num, 2, 8); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* cwval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t cw = cwval && n2_value_get_type(cwval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, cwval) : 0;
	const n2_value_t* chval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t ch = chval && n2_value_get_type(chval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, chval) : 0;
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t id = idval && n2_value_get_type(idval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 5);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 6);
	n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : nw->gmode_copy_width_;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 7);
	n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : nw->gmode_copy_height_;
	// それ以外のパラメータは無視
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "gzoom：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	if (id == se->selected_window_index_) { n2e_funcarg_raise(arg, "gzoom：自分自身のスクリーンID（" N2_VALINT_PRI "）をコピー元に指定することはできません", id); return -1; }
	n2s_window_t* srcw = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, id), NULL);
	if (!srcw) { n2e_funcarg_raise(arg, "gzoom：コピー元のスクリーンID（" N2_VALINT_PRI "）がまだ初期化されていません", id); return -1; }
	if (cw == 0 || ch == 0) { return 0; }
	if (sx < 0) { w += sx; sx = 0; }
	if (sy < 0) { h += sy; sy = 0; }
	w = N2_MIN(w, N2_SCAST(n2_valint_t, srcw->width_) - sx);
	h = N2_MIN(h, N2_SCAST(n2_valint_t, srcw->height_) - sy);
	if (w <= 0 || h <= 0) { return 0; }
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	n2_valint_t psx = nw->posx_, psy = nw->posy_;
	n2_valint_t pex = psx + cw, pey = psy + ch;
	const n2s_u8color_t mulc = n2s_u8color(nw->ginfo_mulr_, nw->ginfo_mulg_, nw->ginfo_mulb_, nw->ginfo_a_);
	n2_fvec2_t uv0 = n2_fvec2(N2_SCAST(float, sx) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy) / N2_SCAST(float, srcw->height_)));
	n2_fvec2_t uv1 = n2_fvec2(N2_SCAST(float, sx + w) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy + h) / N2_SCAST(float, srcw->height_)));
	if (psx >= N2_SCAST(n2_valint_t, nw->width_) || psy >= N2_SCAST(n2_valint_t, nw->height_) || pex < 0 || pey < 0) { return 0; }// 範囲外
	n2s_commandbuffer_rect_textured_rot(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, psx), N2_SCAST(float, psy), 0), n2_fvec2(0, 0), n2_fvec2(N2_SCAST(float, cw), N2_SCAST(float, ch)), mulc, &srcw->texturebuffer_->texture_, uv0, uv1, 0, nw->width_, nw->height_);
	return 0;
}

static int n2si_bifunc_grotate(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 6) { n2e_funcarg_raise(arg, "grotate：引数の数（%d）が期待（0 - %d）と違います", arg_num, 6); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	n2_valint_t id = idval && n2_value_get_type(idval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t sx = sxval && n2_value_get_type(sxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t sy = syval && n2_value_get_type(syval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* rotval = n2e_funcarg_getarg(arg, 3);
	n2_valfloat_t rot = rotval && n2_value_get_type(rotval) != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, rotval) : 0.0;
	const n2_value_t* wval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t w = wval && n2_value_get_type(wval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, wval) : nw->gmode_copy_width_;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 5);
	n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : nw->gmode_copy_height_;
	if (id < 0 || id > N2_SCAST(n2_valint_t, n2s_windowarray_size(se->windows_))) { n2e_funcarg_raise(arg, "grotate：スクリーンID（%" N2_VALINT_PRI "）が範囲外（%zu - %zu）です", id, 0, n2s_windowarray_size(se->windows_)); return -1; }
	if (id == se->selected_window_index_) { n2e_funcarg_raise(arg, "grotate：自分自身のスクリーンID（" N2_VALINT_PRI "）をコピー元に指定することはできません", id); return -1; }
	n2s_window_t* srcw = n2s_windowarray_peekv(se->windows_, N2_SCAST(int, id), NULL);
	if (!srcw) { n2e_funcarg_raise(arg, "grotate：コピー元のスクリーンID（" N2_VALINT_PRI "）がまだ初期化されていません", id); return -1; }
	const n2_valint_t wsign = (w < 0 ? -1 : 1);
	const n2_valint_t hsign = (h < 0 ? -1 : 1);
	w = wsign * w; h = hsign * h;
	if (sx < 0) { sx = 0; }
	if (sy < 0) { sy = 0; }
	n2_valint_t sw = nw->gmode_copy_width_, sh = nw->gmode_copy_height_;
	sw = N2_MIN(sw, N2_SCAST(n2_valint_t, srcw->width_) - sx);
	sh = N2_MIN(sh, N2_SCAST(n2_valint_t, srcw->height_) - sy);
	if (sw <= 0 || sh <= 0) { return 0; }
	if (w <= 0 || h <= 0) { return 0; }
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	n2_valint_t psx = nw->posx_, psy = nw->posy_;
	const n2s_u8color_t mulc = n2s_u8color(nw->ginfo_mulr_, nw->ginfo_mulg_, nw->ginfo_mulb_, nw->ginfo_a_);
	n2_fvec2_t uv0 = n2_fvec2(N2_SCAST(float, sx) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy) / N2_SCAST(float, srcw->height_)));
	n2_fvec2_t uv1 = n2_fvec2(N2_SCAST(float, sx + sw) / N2_SCAST(float, srcw->width_), N2SI_FLIP_V(N2_SCAST(float, sy + sh) / N2_SCAST(float, srcw->height_)));
	n2s_commandbuffer_rect_textured_rot(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, psx), N2_SCAST(float, psy), 0), n2_fvec2(0.5f, 0.5f), n2_fvec2(N2_SCAST(float, w * wsign), N2_SCAST(float, h * hsign)), mulc, &srcw->texturebuffer_->texture_, uv0, uv1, N2_SCAST(float, rot), srcw->width_, srcw->height_);
	return 0;
}

static int n2si_bifunc_mes(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 2) { n2e_funcarg_raise(arg, "mes：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 2); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	const n2_str_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	const n2_value_t* swval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t sw = swval && swval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, swval) : 0;
	if (str->size_ > 0)
	{
		// 描画設定
		n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
		const n2_bool_t independent_draw = (sw & (1 << N2S_MESOPT_GMODE)) ? N2_FALSE : N2_TRUE;
		if (independent_draw) { n2s_commandbuffer_set_program(arg->state_, se->commandbuffer_, N2S_GPROGRAM_2D); n2s_commandbuffer_set_renderstate(arg->state_, se->commandbuffer_, N2S_RENDERSTATE_2D_BLEND_ALPHA); }
		const n2s_u8color_t c = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, independent_draw ? 255 : nw->ginfo_a_);
		// ベース位置
		n2_fvec3_t pos = n2_fvec3(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_), 0);
		n2_fvec2_t bb = n2_fvec2(0, 0);
		// ピボット
		if (sw & ((1 << N2S_MESOPT_HCENTER) | (1 << N2S_MESOPT_VCENTER) | (1 << N2S_MESOPT_HRIGHT)))
		{
			n2s_font_text_bb(arg->state_, &bb, nw->draw_font_, str->str_, str->size_, nw->draw_font_height_, -1);
			n2_fvec2_t pivot = n2_fvec2(0, 0);
			if (sw & (1 << N2S_MESOPT_HCENTER)) { pivot.x_ = 0.5f; }
			if (sw & (1 << N2S_MESOPT_VCENTER)) { pivot.y_ = 0.5f; }
			if (sw & (1 << N2S_MESOPT_HRIGHT)) { pivot.x_ = 1; }
			pos.x_ -= bb.x_ * pivot.x_;
			pos.y_ -= bb.y_ * pivot.y_;
		}
		// フラグ
		size_t flags = 0x00;
		if (arg->state_->config_.standard_font_draw_pixel_perfect_) { flags |= N2S_TEXT_RENDER_FLAG_PIXEL_PERFECT; }
		// 描画
		n2s_commandbuffer_text_ex(arg->state_, se->commandbuffer_, pos, nw->draw_font_, str->str_, str->size_, nw->draw_font_height_, c, -1, flags, &bb, (nw->draw_font_style_ & N2S_WINDOW_DRAW_FONT_STYLE_ITALIC) ? nw->draw_font_height_ * 0.2f : 0, sw & (1 << N2S_MESOPT_SHADOW), n2s_u8color(nw->objcolor_r_, nw->objcolor_g_, nw->objcolor_b_, independent_draw ? 255 : nw->ginfo_a_), n2_fvec2(1, 1), n2_fvec2(1, 1), N2_FALSE, N2S_COLOR_BLACK, n2_fvec2(0, 0), n2_fvec2(0, 0));
		// 次のカーソル
		if (sw & (1 << N2S_MESOPT_NOCR)) { nw->posx_ += N2_SCAST(n2_valint_t, bb.x_); }
		else { nw->posy_ += N2_SCAST(n2_valint_t, bb.y_); }
		// 出力サイズ
		nw->mesx_ = N2_SCAST(n2_valint_t, bb.x_); nw->mesy_ = N2_SCAST(n2_valint_t, bb.y_);
	}
	else
	{
		// 空なら次の行へ
		// @note 行加算の計算が本質的には異なるが結果的には同じ。ロジックをちゃんとしないとなぁ…。
		if (sw & (1 << N2S_MESOPT_NOCR)) { /*nothing to do*/ }
		else { nw->posy_ += N2_SCAST(n2_valint_t, nw->draw_font_height_); }
		nw->mesx_ = 0; nw->mesy_ = N2_SCAST(n2_valint_t, nw->draw_font_height_);
	}
	return 0;
}

static int n2si_bifunc_font(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "font：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* nameval = n2e_funcarg_getarg(arg, 0);
	const n2_valstr_t* name = nameval && nameval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_str_and_push(arg, nameval) : NULL;
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 1);
	n2_valint_t h = hval && n2_value_get_type(hval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : 18;
	h = N2_MAX(1, h);
	const n2_value_t* sfval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t sf = sfval && n2_value_get_type(sfval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sfval) : 0;
	n2_bool_t found = N2_FALSE;
	n2s_font_t* nufont = NULL;
	if (name)
	{
		n2s_font_t** nfont = n2s_fontset_find(se->fontset_, name->str_);
		nufont = nfont ? *nfont : NULL;
		if (!nufont) { nufont = se->default_font_; }
		found = nfont ? N2_TRUE : N2_FALSE;
	}
	else
	{
		found = N2_TRUE;
		nufont = nw->draw_font_;
	}
	if (nufont && h > 0)
	{
		n2s_texture_submit(arg->state_, nw->draw_font_->texture_, N2_FALSE);
		nw->draw_font_ = nufont;
		nw->draw_font_height_ = N2_SCAST(float, h);
		nw->draw_font_style_ = ((sf & 2) ? N2S_WINDOW_DRAW_FONT_STYLE_ITALIC : 0);
	}
	n2e_funcarg_pushi(arg, found ? 0 : -1);
	return 1;
}

static int n2si_bifunc_sysfont(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 1) { n2e_funcarg_raise(arg, "sysfont：引数の数（%d）が期待（0 - %d）と違います", arg_num, 1); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	// その他のパラメータは無視
	//const n2_value_t* sval = n2e_funcarg_getarg(arg, 1);
	//n2_valint_t s = sval && n2_value_get_type(sval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sval) : 0;
	n2s_font_t* nfont = se->default_font_;
	if (nfont)
	{
		n2s_texture_submit(arg->state_, nw->draw_font_->texture_, N2_FALSE);
		nw->draw_font_ = nfont;
		nw->draw_font_height_ = arg->state_->config_.standard_font_default_draw_height_;
		nw->draw_font_style_ = 0;
		n2e_funcarg_pushi(arg, 0);
	}
	else
	{
		n2e_funcarg_pushi(arg, -1);
	}
	return 1;
}

static int n2si_bifunc_fontload_common(const n2_funcarg_t* arg, const char* label, const char* fontname, const void* fontbin, size_t fontbin_size, n2_valint_t bakeheight)
{
	N2_UNUSE(label);

	n2_bool_t res = N2_FALSE;

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;

	n2_buffer_t fontbuf;
	n2_buffer_init(&fontbuf);
	if (fontbin && fontbin_size > 0) { n2_buffer_set(arg->state_, &fontbuf, fontbin, fontbin_size); }

	// とりあえず読み込む
	n2s_font_t* nfont = n2s_font_alloc(arg->state_, fontname, SIZE_MAX, se->font_atlas_width_, se->font_atlas_height_);
	if (n2s_font_load_to(arg->state_, nfont, &fontbuf, N2_FALSE))
	{
		nfont->bake_height_ = N2_SCAST(float, bakeheight);
		res = N2_TRUE;
	}
	else
	{
		n2_str_fmt_to(arg->state_, arg->fiber_->refstr_, "フォントデータの読み込みに失敗：有効なフォントデータではありません");
		n2s_font_free(arg->state_, nfont);
		nfont = NULL;
	}

	if (nfont)
	{
		n2s_font_t** efont = n2s_fontset_find(se->fontset_, fontname);
		if (efont && *efont)
		{
			n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく
			n2s_font_swap(*efont, nfont);// n2s_font_t をポインタ参照している場合があるので、中身だけ変える
		}
		else
		{
			n2s_fontset_insert(arg->state_, se->fontset_, N2_RCAST(const n2s_font_t**, &nfont), NULL);
			nfont = NULL;// このフォントは削除しない
		}
	}

	// 古いフォントは削除
	if (nfont)
	{
		n2s_font_free(arg->state_, nfont);
	}

	n2_buffer_teardown(arg->state_, &fontbuf);

	n2e_funcarg_pushi(arg, res ? 1 : 0);
	return 1;
}
static int n2si_bifunc_fontloadmem_n2(const n2_funcarg_t* arg)
{
	const char* label = "fontloadmem";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 4) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 3, 4); return -1; }
	const n2_value_t* nameval = n2e_funcarg_getarg(arg, 0);
	const n2_valstr_t* name = n2e_funcarg_eval_str_and_push(arg, nameval);
	const n2_value_t* filebinval = n2e_funcarg_getarg(arg, 1);
	if (filebinval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象が変数ではありません", label); return -1; }
	const n2_value_t* readsizeval = n2e_funcarg_getarg(arg, 2);
	n2_valint_t readsize = readsizeval && readsizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, readsizeval) : -1;
	const n2_value_t* bakeheighthval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t bakeheight = bakeheighthval && bakeheighthval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, bakeheighthval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_font_default_bake_height_);

	const n2_variable_t* var = filebinval->field_.varvalue_.var_;
	size_t filebinsize = 0;
	const void* filebin = n2_variable_map_data(&filebinsize, var, filebinval->field_.varvalue_.aptr_);
	if (readsize < 0) { readsize = N2_SCAST(n2_valint_t, filebinsize); }
	readsize = N2_MIN(readsize, N2_SCAST(n2_valint_t, filebinsize));

	return n2si_bifunc_fontload_common(arg, label, name->str_, filebin, N2_SCAST(size_t, readsize), bakeheight);
}
static int n2si_bifunc_fontload_n2(const n2_funcarg_t* arg)
{
	const char* label = "fontload";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 2 || arg_num > 3) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 2, 3); return -1; }
	const n2_value_t* nameval = n2e_funcarg_getarg(arg, 0);
	const n2_valstr_t* name = n2e_funcarg_eval_str_and_push(arg, nameval);
	const n2_value_t* filepathval = n2e_funcarg_getarg(arg, 1);
	const n2_valstr_t* filepath = n2e_funcarg_eval_str_and_push(arg, filepathval);
	const n2_value_t* bakeheighthval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t bakeheight = bakeheighthval && bakeheighthval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, bakeheighthval) : N2_SCAST(n2_valint_t, arg->state_->config_.standard_font_default_bake_height_);

	n2_buffer_t filebuf;
	n2_buffer_init(&filebuf);
	if (!n2i_bifunc_internal_fsload(arg, &filebuf, filepath->str_, N2_TRUE, SIZE_MAX, 0))
	{
		n2_buffer_teardown(arg->state_, &filebuf);
		n2e_funcarg_raise(arg, "%s：ファイル（%s）の読み込みに失敗", label, filepath->str_);
		return -1;
	}

	n2_valstr_t* filetmp = n2e_funcarg_pushs(arg, "");
	n2_str_buffer_mutate(filetmp, &filebuf);
	n2_buffer_teardown(arg->state_, &filebuf);

	return n2si_bifunc_fontload_common(arg, label, name->str_, filetmp->str_, filetmp->size_, bakeheight);
}

static int n2si_bifunc_picmes_n2(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "picmes：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 4); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	const n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	const n2_value_t* hval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t h = hval && hval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, hval) : 18;
	const n2_value_t* flagsval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t flags = flagsval && flagsval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, flagsval) : 0;
	n2_fvec2_t texbb;
	n2s_font_text_bb(arg->state_, &texbb, nw->draw_font_, str->str_, str->size_, N2_SCAST(float, h), -1);
	n2_valint_t offsetx = nw->posx_, offsety = nw->posy_;
	n2_bool_t res = N2_FALSE;
	if (offsetx >= 0 && offsetx + N2_SCAST(n2_valint_t, texbb.x_) < N2_SCAST(n2_valint_t, nw->width_) && offsety >= 0 && offsety + N2_SCAST(n2_valint_t, texbb.y_) < N2_SCAST(n2_valint_t, nw->height_))
	{
		n2s_font_render_config_t render_config;
		n2s_font_render_config_init(&render_config, nw->draw_font_, N2_SCAST(float, h), &nw->draw_font_->glyph_staging_alpha_);
		render_config.render_flags_ = (flags & N2S_PICMESOPT_FLAG_ALPHA_BLEND ? N2S_FONT_RENDER_FLAG_ALPHA_BLEND : 0) | N2S_FONT_RENDER_FLAG_VFLIP;
		render_config.color_ = n2s_u8color(nw->ginfo_r_, nw->ginfo_g_, nw->ginfo_b_, 255);
		render_config.cursor_offsetx_ = N2_SCAST(size_t, offsetx);
		render_config.cursor_offsety_ = N2_SCAST(size_t, offsety);
		n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドフラッシュ
		n2s_texturebuffer_read(arg->state_, nw->texturebuffer_);// バッファリード
		if (n2s_font_render_buffer(arg->state_, &nw->texturebuffer_->texture_.imagebuf_, nw->width_, nw->height_, str->str_, str->size_, &render_config))
		{
			n2s_texture_submit(arg->state_, &nw->texturebuffer_->texture_, N2_TRUE);// アップロード
			res = N2_TRUE;
		}
	}
	nw->mesx_ = N2_SCAST(n2_valint_t, texbb.x_);
	nw->mesy_ = N2_SCAST(n2_valint_t, texbb.y_);
	n2e_funcarg_pushi(arg, res ? 1 : 0);
	return 1;
}

static int n2si_bifunc_getkey(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 2) { n2e_funcarg_raise(arg, "getkey：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 2); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "getkey：対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	const n2_value_t* keyval = n2e_funcarg_getarg(arg, 1);
	n2_unicp_t key = N2_SCAST(n2_unicp_t, keyval && keyval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, keyval) : 1);
	n2_bool_t pressed = N2_FALSE;
	key = n2i_unicode_latin_toupper(key);
	if (key == 1 || key == 2 || key == 4)
	{
		// マウス
		pressed = (SDL_GetMouseState(NULL, NULL) & (key == 1 ? SDL_BUTTON_LMASK : key == 2 ? SDL_BUTTON_RMASK : SDL_BUTTON_MMASK)) ? N2_TRUE : N2_FALSE;
	}
	else
	{
		// キーボード
		int scankey = SDL_SCANCODE_UNKNOWN;
		// 一部は別の変換をする
		switch (key)
		{
		case 16:	scankey = SDL_SCANCODE_LSHIFT; break;
		case 17:	scankey = SDL_SCANCODE_LCTRL; break;
		case 18:	scankey = SDL_SCANCODE_LALT; break;
		case 37:	scankey = SDL_SCANCODE_LEFT; break;
		case 38:	scankey = SDL_SCANCODE_UP; break;
		case 39:	scankey = SDL_SCANCODE_RIGHT; break;
		case 40:	scankey = SDL_SCANCODE_DOWN; break;
		case 112:	scankey = SDL_SCANCODE_F1; break;
		case 113:	scankey = SDL_SCANCODE_F2; break;
		case 114:	scankey = SDL_SCANCODE_F3; break;
		case 115:	scankey = SDL_SCANCODE_F4; break;
		case 116:	scankey = SDL_SCANCODE_F5; break;
		case 117:	scankey = SDL_SCANCODE_F6; break;
		case 118:	scankey = SDL_SCANCODE_F7; break;
		case 119:	scankey = SDL_SCANCODE_F8; break;
		case 120:	scankey = SDL_SCANCODE_F9; break;
		case 121:	scankey = SDL_SCANCODE_F10; break;
		case 122:	scankey = SDL_SCANCODE_F11; break;
		case 123:	scankey = SDL_SCANCODE_F12; break;
		default:
			if (key >= 0x41 && key <= 0x5a) { key = SDLK_a + key - 0x41;/*A - Z*/; }
			scankey = SDL_GetScancodeFromKey(N2_SCAST(SDL_Keycode, key));
			break;
		}
		if (scankey != SDL_SCANCODE_UNKNOWN)
		{
			int keynum = 0;
			const Uint8* keystates = SDL_GetKeyboardState(&keynum);
			if (keystates && scankey >= 0 && N2_SCAST(int, scankey) < keynum) { pressed = keystates[scankey] ? N2_TRUE : N2_FALSE; }
		}
	}
	n2_value_t setval;
	n2i_value_init(&setval);
	n2_value_seti(arg->state_, &setval, pressed);
	n2_variable_set(arg->state_, arg->fiber_, var, aptr, &setval);
	n2i_value_teardown(arg->state_, &setval);

	return 0;
}

static int n2si_bifunc_stick(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "stick：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 2); return -1; }

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "stick：対象が変数ではありません"); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	const int aptr = varval->field_.varvalue_.aptr_;
	const n2_value_t* ntrigkeyval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t ntrigkey = ntrigkeyval && ntrigkeyval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, ntrigkeyval) : 0;
	const n2_value_t* activecheckval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t activecheck = activecheckval && activecheckval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, activecheckval) : 1;

	uint32_t sticks = 0;
	const Uint32 active_window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS;
	if (!activecheck || (nw->window_ && ((SDL_GetWindowFlags(nw->window_) & active_window_flags) == active_window_flags)))
	{
		uint32_t bit = 1;
		const Uint8* keystates = SDL_GetKeyboardState(NULL);
		static const uint32_t check_scancodes[] = {
			SDL_SCANCODE_LEFT,
			SDL_SCANCODE_UP,
			SDL_SCANCODE_RIGHT,
			SDL_SCANCODE_DOWN,
			SDL_SCANCODE_SPACE,
			SDL_SCANCODE_RETURN,
			SDL_SCANCODE_LCTRL | (SDL_SCANCODE_RCTRL << 8),
			SDL_SCANCODE_ESCAPE,
		};
		const n2_bool_t keyboard_focus = n2si_window_is_keyboard_focus(nw);
		for (size_t i = 0, l = N2_ARRAYDIM(check_scancodes); i < l; ++i)
		{
			uint32_t keys = check_scancodes[i];
			while (keys > 0)
			{
				const SDL_Scancode scancode = keys & 0xff;
				if (keyboard_focus && keystates[scancode]) { sticks |= bit; break; }
				keys >>= 8;
			}
			bit <<= 1;
		}

#if N2_CONFIG_EVENT_BASED_MOUSE_STATE
		const size_t mousebuttons = nw->mousebuttons_;
#else
		const Uint32 rawmousebuttons = SDL_GetGlobalMouseState(NULL, NULL);
		size_t mousebuttons = 0;
		if (rawmousebuttons & SDL_BUTTON(SDL_BUTTON_LEFT)) { mousebuttons |= 1 << N2S_MOUSE_BUTTON_LEFT; }
		if (rawmousebuttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) { mousebuttons |= 1 << N2S_MOUSE_BUTTON_RIGHT; }
#endif
		const n2_bool_t mouse_focus = n2si_window_is_mouse_focus(nw);
		for (size_t i = 0; i < 2; ++i)
		{
			if (mouse_focus && (mousebuttons & N2_SCAST(size_t, 1 << (i == 0 ? N2S_MOUSE_BUTTON_LEFT : N2S_MOUSE_BUTTON_RIGHT)))) { sticks |= bit; }
			bit <<= 1;
		}

		if (keystates[SDL_SCANCODE_TAB]) { sticks |= bit; }
		bit <<= 1;
	}

	n2_value_t setval;
	n2i_value_init(&setval);
	n2_value_seti(arg->state_, &setval, N2_SCAST(n2_valint_t, (sticks ^ se->stick_last_)/*keytrigs*/ | (sticks & N2_SCAST(uint32_t, ntrigkey))/*pressing*/));
	n2_variable_set(arg->state_, arg->fiber_, var, aptr, &setval);
	n2i_value_teardown(arg->state_, &setval);

	se->stick_last_ = sticks;

	return 0;
}

static int n2si_bifunc_clipchks(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 0) { n2e_funcarg_raise(arg, "clipchks：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	n2e_funcarg_pushi(arg, SDL_HasClipboardText() ? 1 : 0);
	return 1;
}

static int n2si_bifunc_clipgets(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 0) { n2e_funcarg_raise(arg, "clipgets：引数の数（%d）が期待（%d）と違います", arg_num, 0); return -1; }
	n2_valstr_t* res = n2e_funcarg_pushs(arg, "");
	char* cliptext = SDL_GetClipboardText();
	if (cliptext) { n2_str_set(arg->state_, res, cliptext, SIZE_MAX); SDL_free(cliptext); }
	return 1;
}

static int n2si_bifunc_clipputs(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 1) { n2e_funcarg_raise(arg, "clipputs：引数の数（%d）が期待（%d）と違います", arg_num, 1); return -1; }
	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	n2e_funcarg_pushi(arg, SDL_SetClipboardText(str->str_) ? 0 : 1/*return value 0 denotes success*/);
	return 1;
}

#if N2_CONFIG_USE_IMAGE_READ_LIB
static int n2si_bifunc_loadimage_core(const n2_funcarg_t* arg, n2s_environment_t* se, n2_buffer_t* imagebuf, size_t imagew, size_t imageh, int window_index, int f, const char* label)
{
	n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく

	n2s_window_t* mw = n2s_windowarray_peekv(se->windows_, 0, NULL);
	N2_ASSERT(mw);
	SDL_GL_MakeCurrent(mw->window_, mw->gl_context_);// コンテキストスイッチ

	n2s_window_t* uw = NULL;

	int res = 0;
	switch (f)
	{
	case -1:
	case 0:
	case 2:
		{
			if (window_index == 0)
			{
				// 0は特殊
				mw->width_ = N2_SCAST(size_t, imagew);
				mw->height_ = N2_SCAST(size_t, imageh);
				// texture buffer
				n2si_texturebuffer_free(arg->state_, mw->texturebuffer_);
				mw->texturebuffer_ = n2si_texturebuffer_alloc(arg->state_, mw->width_, mw->height_);
				if (f == -1)
				{
					n2s_texture_copy_buffer(&mw->texturebuffer_->texture_, imagebuf, imagew, imageh, 0, 0);
				}
				else
				{
					n2s_texture_fill_color(&mw->texturebuffer_->texture_, f == 0 ? N2S_COLOR_WHITE : N2S_COLOR_BLACK);
					n2s_texture_render_buffer(&mw->texturebuffer_->texture_, imagebuf, imagew, imageh, 0, 0, N2S_COLOR_WHITE);
				}
				n2s_texture_submit(arg->state_, &mw->texturebuffer_->texture_, N2_TRUE);
				// draw cache
				n2si_window_sync_drawbuffer_from_texturebuffer(arg->state_, mw);
				uw = mw;
			}
			else
			{
				n2s_window_t* nw = n2si_window_alloc(arg->state_, se, N2S_WINDOW_OFFSCREEN, imagew, imageh, 0, N2_FALSE);
				if (!nw) { n2e_funcarg_raise(arg, "%s：ウィンドウの再生成に失敗しました", label); res = -1; break; }
				// texture buffer
				if (f == -1)
				{
					n2s_texture_copy_buffer(&nw->texturebuffer_->texture_, imagebuf, imagew, imageh, 0, 0);
				}
				else
				{
					n2s_texture_fill_color(&nw->texturebuffer_->texture_, f == 0 ? N2S_COLOR_WHITE : N2S_COLOR_BLACK);
					n2s_texture_render_buffer(&nw->texturebuffer_->texture_, imagebuf, imagew, imageh, 0, 0, N2S_COLOR_WHITE);
				}
				n2s_texture_submit(arg->state_, &nw->texturebuffer_->texture_, N2_TRUE);
				n2si_window_register(arg->state_, se, nw, window_index);
				// draw cache
				n2si_window_sync_drawbuffer_from_texturebuffer(arg->state_, nw);
				uw = nw;
			}
		}
		break;
	case 1:
		{
			n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, window_index, NULL);
			if (nw)
			{
				n2s_texturebuffer_read(arg->state_, nw->texturebuffer_);
				n2s_texture_render_buffer(&nw->texturebuffer_->texture_, imagebuf, imagew, imageh, N2_SCAST(int, nw->posx_), N2_SCAST(int, nw->posy_), N2S_COLOR_WHITE);
				n2si_window_sync_drawbuffer_from_texturebuffer(arg->state_, nw);
				uw = nw;
			}
			else
			{
				// 新規生成とする
				nw = n2si_window_alloc(arg->state_, se, N2S_WINDOW_OFFSCREEN, imagew, imageh, 0, N2_FALSE);
				if (!nw) { n2e_funcarg_raise(arg, "%s：ウィンドウの再生成に失敗しました", label); res = -1; break; }
				// texture buffer
				n2s_texture_fill_color(&nw->texturebuffer_->texture_, f == 0 ? N2S_COLOR_WHITE : N2S_COLOR_BLACK);
				n2s_texture_render_buffer(&nw->texturebuffer_->texture_, imagebuf, imagew, imageh, 0, 0, N2S_COLOR_WHITE);
				n2s_texture_submit(arg->state_, &nw->texturebuffer_->texture_, N2_TRUE);
				// draw cache
				n2si_window_sync_drawbuffer_from_texturebuffer(arg->state_, nw);
				// register
				n2si_window_register(arg->state_, se, nw, window_index);
				uw = nw;
			}
		}
		break;
	default:	n2e_funcarg_raise(arg, "%s：初期化モード（%d）が不正です", label, f); res = -1; break;
	}

	// cel関係の設定をリセット
	N2_ASSERT(uw);
	uw->celdiv_sizex_ = 0;
	uw->celdiv_sizey_ = 0;
	uw->cel_offset_ = n2_fvec2(0, 0);

	return res;
}

static int n2si_bifunc_picload_common(const n2_funcarg_t* arg, n2_bool_t is_picload)
{
	const char* label = is_picload ? "picload" : "celload";
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (is_picload)
	{
		if (arg_num < 1 || arg_num > 2) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 1, 2); return -1; }
	}
	else
	{
		if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 1, 3); return -1; }
	}
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;

	const n2_value_t* fileval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* file = n2e_funcarg_eval_str_and_push(arg, fileval);

	int wid = se->selected_window_index_;
	if (is_picload)
	{
		n2s_window_t* w = se->selected_window_index_ >= 0 ? n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL) : NULL;
		if (!w) { n2e_funcarg_raise(arg, "%s：対象のウィンドウが選択されていません", label); return -1; }
	}
	else
	{
		const n2_value_t* widval = n2e_funcarg_getarg(arg, 1);
		wid = N2_SCAST(int, widval && n2_value_get_type(widval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, widval) : -1);
		if (wid < 0)
		{
			for (size_t i = 1, l = n2s_windowarray_size(se->windows_) + 1; i < l; ++i)
			{
				if (!n2s_windowarray_peekv(se->windows_, N2_SCAST(int, i), NULL)) { wid = N2_SCAST(int, i); break; }
			}
		}
	}

	const n2_value_t* fval = n2e_funcarg_getarg(arg, is_picload ? 1 : 2);
	const n2_valint_t f = fval && n2_value_get_type(fval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, fval) : 0;

	n2_buffer_t filebuf;
	n2_buffer_init(&filebuf);
	if (!n2i_bifunc_internal_fsload(arg, &filebuf, file->str_, N2_TRUE, SIZE_MAX, 0))
	{
		n2_buffer_teardown(arg->state_, &filebuf);
		n2e_funcarg_raise(arg, "%s：ファイル（%s）の読み込みに失敗", label, file);
		return -1;
	}

	n2_buffer_t imagebuf;
	n2_buffer_init(&imagebuf);
	size_t imagew = 0, imageh = 0;
	if (!n2h_image_read(arg->state_, &imagebuf, &imagew, &imageh, filebuf.data_, filebuf.size_) || imagew <= 0 || imageh <= 0)
	{
		n2_buffer_teardown(arg->state_, &filebuf);
		n2_buffer_teardown(arg->state_, &imagebuf);
		n2e_funcarg_raise(arg, "%s：ファイル（%s）を画像として読み込もうとしましたが失敗：サポートされてない形式です", label, file);
		return -1;
	}

	int res = n2si_bifunc_loadimage_core(arg, se, &imagebuf, imagew, imageh, wid, N2_SCAST(int, f), label);

	n2_buffer_teardown(arg->state_, &filebuf);
	n2_buffer_teardown(arg->state_, &imagebuf);

	if (res < 0) { return res; }// エラー

	if (!is_picload) { n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, wid)); res = 1; }
	return res;
}
static int n2si_bifunc_picload(const n2_funcarg_t* arg) { return n2si_bifunc_picload_common(arg, N2_TRUE); }
static int n2si_bifunc_celload(const n2_funcarg_t* arg) { return n2si_bifunc_picload_common(arg, N2_FALSE); }
#endif// N2_CONFIG_USE_IMAGE_READ_LIB

static int n2si_bifunc_celdiv(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "celdiv：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 5); return -1; }
	const n2_value_t* widval = n2e_funcarg_getarg(arg, 0);
	const int wid = N2_SCAST(int, widval && n2_value_get_type(widval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, widval) : 1);
	const n2_value_t* divxval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t divx = divxval && n2_value_get_type(divxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, divxval) : 0;
	const n2_value_t* divyval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t divy = divyval && n2_value_get_type(divyval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, divyval) : 0;
	const n2_value_t* centerxval = n2e_funcarg_getarg(arg, 3);
	const n2_valint_t centerx = centerxval && n2_value_get_type(centerxval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, centerxval) : 0;
	const n2_value_t* centeryval = n2e_funcarg_getarg(arg, 4);
	const n2_valint_t centery = centeryval && n2_value_get_type(centeryval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, centeryval) : 0;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = wid >= 0 ? n2s_windowarray_peekv(se->windows_, wid, NULL) : NULL;
	if (!nw) { n2e_funcarg_raise(arg, "celdiv：対象のスクリーンID（%d）がまだ初期化されていません", wid); return -1; }
	if (divx < 0 || divy < 0) { n2e_funcarg_raise(arg, "celdiv：画面分割数（%" N2_VALINT_PRI ", %" N2_VALINT_PRI "）が不正です", divx, divy); return -1; }
	nw->celdiv_sizex_ = N2_SCAST(size_t, divx);
	nw->celdiv_sizey_ = N2_SCAST(size_t, divy);
	nw->cel_offset_ = n2_fvec2(N2_SCAST(float, centerx), N2_SCAST(float, centery));
	return 0;
}

static int n2si_bifunc_celput(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 5) { n2e_funcarg_raise(arg, "celput：引数の数（%d）が期待（%d - %d）と違います", arg_num, 0, 5); return -1; }
	const n2_value_t* widval = n2e_funcarg_getarg(arg, 0);
	const int wid = N2_SCAST(int, widval && n2_value_get_type(widval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, widval) : 1);
	const n2_value_t* bidval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t bid = bidval && n2_value_get_type(bidval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, bidval) : 0;
	const n2_value_t* scalexval = n2e_funcarg_getarg(arg, 2);
	const n2_valfloat_t scalex = bidval && n2_value_get_type(scalexval) != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, scalexval) : 1;
	const n2_value_t* scaleyval = n2e_funcarg_getarg(arg, 3);
	const n2_valfloat_t scaley = bidval && n2_value_get_type(scaleyval) != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, scaleyval) : 1;
	const n2_value_t* radval = n2e_funcarg_getarg(arg, 4);
	const n2_valfloat_t rad = radval && n2_value_get_type(radval) != N2_VALUE_NIL ? n2e_funcarg_eval_float(arg, radval) : 0;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	n2s_window_t* bw = wid >= 0 ? n2s_windowarray_peekv(se->windows_, wid, NULL) : NULL;
	if (!bw) { n2e_funcarg_raise(arg, "celput：コピー元のスクリーンID（%d）がまだ初期化されていません", wid); return -1; }
	if (wid == se->selected_window_index_) { n2e_funcarg_raise(arg, "celput：自分自身のスクリーンID（" N2_VALINT_PRI "）をコピー元に指定することはできません", wid); return -1; }
	const size_t srcw = bw->celdiv_sizex_ <= 0 ? bw->width_ : bw->celdiv_sizex_;
	const size_t srch = bw->celdiv_sizey_ <= 0 ? bw->height_ : bw->celdiv_sizey_;
	const size_t patnumx = bw->width_ / srcw;
	const size_t patnumy = bw->height_ / srch;
	const size_t patnum = patnumx * patnumy;
	if (bid < 0) { n2e_funcarg_raise(arg, "celput：ブロックインデックス（%" N2_VALINT_PRI "）が負で不正です。", bid); return -1; }
	if (N2_SCAST(size_t, bid) >= patnum) { n2e_funcarg_raise(arg, "celput：ブロックインデックス（%" N2_VALINT_PRI "）がパターン数（%zu x %zu = %zu）より大きく不正です。", bid, patnumx, patnumy, patnum); return -1; }
	const size_t sx =  (N2_SCAST(size_t, bid) % patnumx) * srcw;
	const size_t sy =  (N2_SCAST(size_t, bid) / patnumx) * srch;
	n2si_environment_checkout_draw_commandbuffer(arg->state_, se);
	const n2s_u8color_t mulc = n2s_u8color(nw->ginfo_mulr_, nw->ginfo_mulg_, nw->ginfo_mulb_, nw->ginfo_a_);
	n2_fvec2_t uv0 = n2_fvec2(N2_SCAST(float, sx) / N2_SCAST(float, bw->width_), N2SI_FLIP_V(N2_SCAST(float, sy) / N2_SCAST(float, bw->height_)));
	n2_fvec2_t uv1 = n2_fvec2(N2_SCAST(float, sx + srcw) / N2_SCAST(float, bw->width_), N2SI_FLIP_V(N2_SCAST(float, sy + srch) / N2_SCAST(float, bw->height_)));
	n2s_commandbuffer_rect_textured_rot(arg->state_, se->commandbuffer_, n2_fvec3(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_), 0), n2_fvec2(bw->cel_offset_.x_ / N2_SCAST(float, srcw), bw->cel_offset_.y_ / N2_SCAST(float, srch)), n2_fvec2(N2_SCAST(float, srcw) * N2_SCAST(float, scalex), N2_SCAST(float, srch) * N2_SCAST(float, scaley)), mulc, &bw->texturebuffer_->texture_, uv0, uv1, N2_SCAST(float, rad), bw->width_, bw->height_);
	nw->posx_ += N2_SCAST(n2_valint_t, N2_SCAST(n2_valfloat_t, srcw) * scalex);
	return 0;
}

static int n2si_bifunc_celbitmap_common(const n2_funcarg_t* arg, const char* label, n2_bool_t is_extended)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	const int arg_max = is_extended ? 7 : 3;
	if (arg_num > arg_max) { n2e_funcarg_raise(arg, "%s：引数の数（%d）が期待（%d - %d）と違います", label, arg_num, 0, arg_max); return -1; }
	const n2_value_t* widval = n2e_funcarg_getarg(arg, 0);
	const int wid = N2_SCAST(int, widval && n2_value_get_type(widval) != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, widval) : 1);
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 1);
	const n2_value_t* modeval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t mode = modeval && modeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, modeval) : 0;
	const n2_value_t* sxval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t sx = sxval && sxval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sxval) : 0;
	const n2_value_t* syval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t sy = syval && syval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, syval) : 0;
	const n2_value_t* exval = n2e_funcarg_getarg(arg, 5);
	n2_valint_t ex = exval && exval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, exval) : 0;
	const n2_value_t* eyval = n2e_funcarg_getarg(arg, 6);
	n2_valint_t ey = eyval && eyval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, eyval) : 0;
	const n2_bool_t is_bgr = (mode & 1) ? N2_TRUE : N2_FALSE;
	const n2_bool_t is_capture = (mode & 16) ? N2_TRUE : N2_FALSE;
	if (!varval || varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "%s：対象として有効な変数を指定されていません", label); return -1; }
	if (varval->field_.varvalue_.aptr_ >= 0) { n2e_funcarg_raise(arg, "%s：対象の変数が変数そのもではありませんでした（配列の要素が指定されています）", label); return -1; }
	n2_variable_t* var = varval->field_.varvalue_.var_;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = wid >= 0 ? n2s_windowarray_peekv(se->windows_, wid, NULL) : NULL;
	if (!nw) { n2e_funcarg_raise(arg, "%s：対象のスクリーンID（%d）がまだ初期化されていません", label, wid); return -1; }
	if (ex <= 0) { ex = N2_SCAST(n2_valint_t, nw->width_); }
	if (ey <= 0) { ey = N2_SCAST(n2_valint_t, nw->height_); }
	if (sx < 0 || sx >= N2_SCAST(n2_valint_t, nw->width_) || sy < 0 || sy >= N2_SCAST(n2_valint_t, nw->height_) || ex > N2_SCAST(n2_valint_t, nw->width_) || ey > N2_SCAST(n2_valint_t, nw->height_)) { n2e_funcarg_raise(arg, "%s：対象の領域が対象のスクリーンIDに対して不正です", label); return -1; }
	if (ex < sx) { const n2_valint_t tx = ex; ex = sx; sx = tx; }
	if (ey < sy) { const n2_valint_t ty = ey; ey = sy; sy = ty; }
	const size_t element_num = N2_SCAST(size_t, ex - sx) * N2_SCAST(size_t, ey - sy);
	if (is_capture)
	{
		const size_t length[N2_VARIABLE_DIM] = {element_num, 0};

		// 型違い
		if (var->type_ != N2_VALUE_INT)
		{
			n2_variable_prepare(arg->state_, var, N2_VALUE_INT, 0, length);
		}
		// 自動拡張
		if (var->element_num_ < element_num)
		{
			n2_variable_redim(arg->state_, var, length);
		}
	}
	else
	{
		if (var->type_ != N2_VALUE_INT) { n2e_funcarg_raise(arg, "%s：対象の変数が整数型ではありません", label); return -1; }
		if (var->element_num_ < element_num) { n2e_funcarg_raise(arg, "%s：対象の変数の配列要素数（%zu）が対象のピクセル数（%zu）より少ないです", label, var->element_num_, element_num); return -1; }
	}
	n2_valint_t* elements = n2_variable_element_ptr(var, 0);
	n2si_environment_flush_commandbuffer(arg->state_, se);// コマンドはフラッシュしておく
	const n2_valint_t iw = ex - sx;
	const n2_valint_t ih = ey - sy;
	if (is_capture)
	{
		n2s_texturebuffer_read(arg->state_, nw->texturebuffer_);
		const void* srcdata = nw->texturebuffer_->texture_.imagebuf_.data_;
		for (n2_valint_t iy = 0; iy < ih; ++iy) for (n2_valint_t ix = 0; ix < iw; ++ix)
		{
			const n2_valint_t y = sy + iy + N2SI_FLIP_V_OR(nw->height_ - ey, 0);
			const n2_valint_t x = sx + ix;
			const uint8_t* sp = N2_RCAST(const uint8_t*, n2_cptr_offset(srcdata, (N2_SCAST(size_t, y) * nw->width_ + N2_SCAST(size_t, x)) * 4));
			elements[iy * iw + ix] = (is_bgr ? ((sp[3] << 24) | (sp[2] << 16) | (sp[1] << 8) | (sp[0])) : ((sp[3] << 24) | (sp[0] << 16) | (sp[1] << 8) | (sp[2])));
		}
	}
	else
	{
		void* todata = nw->texturebuffer_->texture_.imagebuf_.data_;
		for (n2_valint_t iy = 0; iy < ih; ++iy) for (n2_valint_t ix = 0; ix < iw; ++ix)
		{
			const n2_valint_t y = sy + iy + N2SI_FLIP_V_OR(nw->height_ - ey, 0);
			const n2_valint_t x = sx + ix;
			uint8_t* tp = N2_RCAST(uint8_t*, n2_ptr_offset(todata, (N2_SCAST(size_t, y) * nw->width_ + N2_SCAST(size_t, x)) * 4));
			const n2_valint_t sv = elements[iy * iw + ix];
			if (is_bgr)
			{
				tp[0] = (sv >> 16) & 0xff;
				tp[1] = (sv >> 8) & 0xff;
				tp[2] = (sv >> 0) & 0xff;
			}
			else
			{
				tp[0] = (sv >> 0) & 0xff;
				tp[1] = (sv >> 8) & 0xff;
				tp[2] = (sv >> 16) & 0xff;
			}
			tp[3] = (sv >> 24) & 0xff;
		}
		n2s_texture_submit(arg->state_, &nw->texturebuffer_->texture_, N2_TRUE);
	}
	return 0;
}
static int n2si_bifunc_celbitmap(const n2_funcarg_t* arg) { return n2si_bifunc_celbitmap_common(arg, "celbitmap", N2_FALSE); }
static int n2si_bifunc_celbitmap_n2(const n2_funcarg_t* arg) { return n2si_bifunc_celbitmap_common(arg, "celbitmap@n2", N2_TRUE); }

#if N2_CONFIG_USE_GUI_LIB
static void n2si_bifunc_widget_posinc_y(n2s_window_t* nw, n2_valint_t oy)
{
	nw->posy_ += N2_MAX(nw->objminheight_, oy);
}

static int n2si_bifunc_objsize(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 3) { n2e_funcarg_raise(arg, "objsize：引数の数（%d）が期待（0 - %d）と違います", arg_num, 3); return -1; }
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const n2_value_t* xval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t x = xval && xval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, xval) : 64;
	const n2_value_t* yval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t y = yval && yval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, yval) : 24;
	const n2_value_t* minyval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t miny = minyval && minyval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, minyval) : 0;
	if (x <= 0 || y <= 0) { n2e_funcarg_raise(arg, "objsize：サイズの引数（x=%" N2_VALINT_PRI "、y=%" N2_VALINT_PRI "）が負です", x, y); return -1; }
	nw->objx_ = x; nw->objy_ = y; nw->objminheight_ = miny;
	return 0;
}

static int n2si_bifunc_objprm(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "objprm：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t id = idval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* prmval = n2e_funcarg_getarg(arg, 1);
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const size_t idsz = N2_SCAST(size_t, id);
	n2s_widget_t* widget = nw->widgets_ ? n2s_widgetset_find(nw->widgets_, &idsz) : NULL;
	if (!widget) { n2e_funcarg_raise(arg, "objprm：対象のオブジェクト（ID=%" N2_VALINT_PRI "）が見つかりませんでした", id); return -1; }
	switch (widget->type_)
	{
	case N2S_WIDGET_BUTTON:
		{
			n2_valstr_t* prmstr = n2e_funcarg_eval_str_and_push(arg, prmval);
			n2_str_copy_to(arg->state_, &widget->label_, prmstr);
		}
		break;
	case N2S_WIDGET_CHECKBOX:
		{
			const n2_valint_t prm = n2e_funcarg_eval_int(arg, prmval) ? 1 : 0;
			widget->ivalue_ = prm;
			if (widget->capture_)
			{
				n2_value_t tvalue;
				n2i_value_init(&tvalue); n2_value_seti(arg->state_, &tvalue, widget->ivalue_);
				n2_variable_set(arg->state_, arg->fiber_, widget->capture_, widget->capture_aptr_, &tvalue);
				n2i_value_teardown(arg->state_, &tvalue);
			}
		}
		break;
	case N2S_WIDGET_INPUT:
	case N2S_WIDGET_TEXTBOX:
		{
			n2_valstr_t* prmstr = n2e_funcarg_eval_str_and_push(arg, prmval);
			n2_str_copy_to(arg->state_, &widget->strvalue_, prmstr);
			if (widget->capture_)
			{
				n2_value_t* prmstrval = n2e_funcarg_get(arg, -1);
				N2_ASSERT(prmstrval->type_ == N2_VALUE_STRING && &prmstrval->field_.svalue_ == prmstr);
				n2_variable_set(arg->state_, arg->fiber_, widget->capture_, widget->capture_aptr_, prmstrval);
			}
		}
		break;
	default:
		n2e_funcarg_raise(arg, "objprm：対象のオブジェクト（ID=%" N2_VALINT_PRI "）はobjprmによって内容を変更できません", id);
		return -1;
	}
	return 0;
}

static int n2si_bifunc_objenable(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "objenable：引数の数（%d）が期待（0  %d）と違います", arg_num, 2); return -1; }
	const n2_value_t* idval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t id = idval && idval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 0;
	const n2_value_t* enableval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t enable = enableval && enableval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, idval) : 1;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	const size_t idsz = N2_SCAST(size_t, id);
	n2s_widget_t* widget = nw->widgets_ ? n2s_widgetset_find(nw->widgets_, &idsz) : NULL;
	if (!widget) { n2e_funcarg_raise(arg, "objenable：対象のオブジェクト（ID=%" N2_VALINT_PRI "）が見つかりませんでした", id); return -1; }
	widget->enable_ = enable ? N2_TRUE : N2_FALSE;
	return 0;
}

static int n2si_bifunc_clrobj(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num > 2) { n2e_funcarg_raise(arg, "clrobj：引数の数（%d）が期待（0 - %d）と違います", arg_num, 2); return -1; }
	const n2_value_t* startval = n2e_funcarg_getarg(arg, 0);
	const n2_valint_t start = startval && startval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, startval) : 0;
	const n2_value_t* endval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t end = endval && endval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, endval) : -1;
	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	if (nw->widgets_)
	{
		for (size_t wi = 0, wl = n2s_widgetset_size(nw->widgets_); wi < wl; ++wi)
		{
			n2s_widget_t* widget = n2s_widgetset_peek(nw->widgets_, N2_SCAST(int, wi));
			if (!widget) { continue; }
			const n2_valint_t iid = N2_SCAST(n2_valint_t, widget->id_);
			if (iid >= start && (iid <= end || end < 0))
			{
				if (n2s_widgetset_erase_at(arg->state_, nw->widgets_, N2_SCAST(int, wi)))
				{
					--wi;
					--wl;
				}
			}
		}
	}
	return 0;
}

static int n2si_bifunc_button(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "button：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	if (!nw->widgets_ || nw->type_ != N2S_WINDOW_SCREEN) { n2e_funcarg_raise(arg, "button：現在の対象ウィンドウにはウィジェットを配置できません"); return -1; }

	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	const n2_value_t* labelval = n2e_funcarg_getarg(arg, 1);
	const n2_vallabel_t* label = n2_value_get_label(labelval);
	if (!label || label->label_index_ < 0) { n2e_funcarg_raise(arg, "button：有効なラベルが指定されていません"); return -1; }

	const size_t next_id = nw->next_widget_id_++;
	n2s_widget_t widget;
	n2s_widget_init(&widget);
	widget.id_ = next_id;
	widget.type_ = N2S_WIDGET_BUTTON;
	widget.position_ = n2_fvec2(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_));
	widget.size_ = n2_fvec2(N2_SCAST(float, nw->objx_), N2_SCAST(float, nw->objy_));
	widget.label_ = *str; n2_str_init(str);
	widget.lgosub_ = (n2e_funcarg_csflags(arg) & N2_CALLSTATEFLAG_QUAL_GOSUB) ? N2_TRUE : N2_FALSE;
	widget.lvalue_ = *label;
	n2s_widgetset_insert(arg->state_, nw->widgets_, &widget, NULL);

	n2si_bifunc_widget_posinc_y(nw, nw->objy_);

	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, next_id));
	return 1;
}

static int n2si_bifunc_chkbox(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num != 2) { n2e_funcarg_raise(arg, "chkbox：引数の数（%d）が期待（%d）と違います", arg_num, 2); return -1; }

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	if (!nw->widgets_ || nw->type_ != N2S_WINDOW_SCREEN) { n2e_funcarg_raise(arg, "chkbox：現在の対象ウィンドウにはウィジェットを配置できません"); return -1; }

	const n2_value_t* strval = n2e_funcarg_getarg(arg, 0);
	n2_valstr_t* str = n2e_funcarg_eval_str_and_push(arg, strval);
	const n2_value_t* varval = n2e_funcarg_getarg(arg, 1);
	if (!varval || varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "chkbox：対象として有効な変数を指定されていません"); return -1; }
	if (varval->field_.varvalue_.var_->type_ != N2_VALUE_INT) { n2e_funcarg_raise(arg, "chkbox：対象の変数が整数型ではありません"); return -1; }
	const n2_valint_t varbool = n2e_funcarg_eval_int(arg, varval);

	const size_t next_id = nw->next_widget_id_++;
	n2s_widget_t widget;
	n2s_widget_init(&widget);
	widget.id_ = next_id;
	widget.type_ = N2S_WIDGET_CHECKBOX;
	widget.position_ = n2_fvec2(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_));
	widget.size_ = n2_fvec2(N2_SCAST(float, nw->objx_), N2_SCAST(float, nw->objy_));
	widget.label_ = *str; n2_str_init(str);
	widget.ivalue_ = varbool;
	widget.capture_ = varval->field_.varvalue_.var_;
	widget.capture_aptr_ = varval->field_.varvalue_.aptr_;
	n2s_widgetset_insert(arg->state_, nw->widgets_, &widget, NULL);

	n2si_bifunc_widget_posinc_y(nw, nw->objy_);

	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, next_id));
	return 1;
}

static int n2si_bifunc_input(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 3) { n2e_funcarg_raise(arg, "input：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 3); return -1; }

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	if (!nw->widgets_ || nw->type_ != N2S_WINDOW_SCREEN) { n2e_funcarg_raise(arg, "input：現在の対象ウィンドウにはウィジェットを配置できません"); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (!varval || varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "input：対象として有効な変数を指定されていません"); return -1; }
	if (varval->field_.varvalue_.var_->type_ != N2_VALUE_STRING)
	{
		// 無理やりstrに変換
		n2_variable_prepare(arg->state_, varval->field_.varvalue_.var_, N2_VALUE_STRING, 256, n2i_variable_nlength);
	}
	n2_valstr_t* varstr = n2_variable_get_str(varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_);
	if (!varstr) { n2e_funcarg_raise(arg, "input：対象の変数の文字列の値を取り出せませんでした。配列長＝%zu、指定した配列インデックス＝%d", varval->field_.varvalue_.var_->element_num_, varval->field_.varvalue_.aptr_); return -1; }
	const n2_value_t* xval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t x = xval && xval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, xval) : nw->objx_;
	const n2_value_t* yval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t y = yval && yval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, yval) : nw->objy_;
	const n2_value_t* sizeval = n2e_funcarg_getarg(arg, 3);
	n2_valint_t size = sizeval && sizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sizeval) : 0;
	if (size <= 0) { size = N2_SCAST(n2_valint_t, arg->state_->config_.standard_widget_input_default_max_buffer_size_); }

	const size_t next_id = nw->next_widget_id_++;
	n2s_widget_t widget;
	n2s_widget_init(&widget);
	widget.id_ = next_id;
	widget.type_ = N2S_WIDGET_INPUT;
	widget.position_ = n2_fvec2(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_));
	widget.size_ = n2_fvec2(N2_SCAST(float, x), N2_SCAST(float, y));
	n2_str_fmt_to(arg->state_, &widget.label_, "");
	n2_str_copy_to(arg->state_, &widget.strvalue_, varstr);
	n2_str_reserve(arg->state_, &widget.strvalue_, N2_SCAST(size_t, size));
	widget.capture_ = varval->field_.varvalue_.var_;
	widget.capture_aptr_ = varval->field_.varvalue_.aptr_;
	n2s_widgetset_insert(arg->state_, nw->widgets_, &widget, NULL);

	n2si_bifunc_widget_posinc_y(nw, nw->objy_);

	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, next_id));
	return 1;
}

static int n2si_bifunc_mesbox(const n2_funcarg_t* arg)
{
	const int arg_num = N2_SCAST(int, n2e_funcarg_argnum(arg));
	if (arg_num < 1 || arg_num > 4) { n2e_funcarg_raise(arg, "mesbox：引数の数（%d）が期待（%d - %d）と違います", arg_num, 1, 4); return -1; }

	n2s_environment_t* se = arg->fiber_->environment_->standard_environment_;
	n2s_window_t* nw = n2s_windowarray_peekv(se->windows_, se->selected_window_index_, NULL);
	N2_ASSERT(nw);
	if (!nw->widgets_ || nw->type_ != N2S_WINDOW_SCREEN) { n2e_funcarg_raise(arg, "mesbox：現在の対象ウィンドウにはウィジェットを配置できません"); return -1; }

	const n2_value_t* varval = n2e_funcarg_getarg(arg, 0);
	if (!varval || varval->type_ != N2_VALUE_VARIABLE) { n2e_funcarg_raise(arg, "mesbox：対象として有効な変数を指定されていません"); return -1; }
	if (varval->field_.varvalue_.var_->type_ != N2_VALUE_STRING)
	{
		// 無理やりstrに変換
		n2_variable_prepare(arg->state_, varval->field_.varvalue_.var_, N2_VALUE_STRING, 256, n2i_variable_nlength);
	}
	n2_valstr_t* varstr = n2_variable_get_str(varval->field_.varvalue_.var_, varval->field_.varvalue_.aptr_);
	if (!varstr) { n2e_funcarg_raise(arg, "mesbox：対象の変数の文字列の値を取り出せませんでした。配列長＝%zu、指定した配列インデックス＝%d", varval->field_.varvalue_.var_->element_num_, varval->field_.varvalue_.aptr_); return -1; }
	const n2_value_t* xval = n2e_funcarg_getarg(arg, 1);
	const n2_valint_t x = xval && xval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, xval) : nw->objx_;
	const n2_value_t* yval = n2e_funcarg_getarg(arg, 2);
	const n2_valint_t y = yval && yval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, yval) : nw->objy_;
	//const n2_value_t* styleval = n2e_funcarg_getarg(arg, 3);
	//const n2_valint_t style = styleval && styleval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, styleval) : 1;
	const n2_value_t* sizeval = n2e_funcarg_getarg(arg, 4);
	n2_valint_t size = sizeval && sizeval->type_ != N2_VALUE_NIL ? n2e_funcarg_eval_int(arg, sizeval) : 0;
	if (size <= 0) { size = N2_SCAST(n2_valint_t, arg->state_->config_.standard_widget_input_default_max_buffer_size_); }

	const size_t next_id = nw->next_widget_id_++;
	n2s_widget_t widget;
	n2s_widget_init(&widget);
	widget.id_ = next_id;
	widget.type_ = N2S_WIDGET_TEXTBOX;
	widget.position_ = n2_fvec2(N2_SCAST(float, nw->posx_), N2_SCAST(float, nw->posy_));
	widget.size_ = n2_fvec2(N2_SCAST(float, x), N2_SCAST(float, y));
	n2_str_fmt_to(arg->state_, &widget.label_, "");
	n2_str_copy_to(arg->state_, &widget.strvalue_, varstr);
	n2_str_reserve(arg->state_, &widget.strvalue_, N2_SCAST(size_t, size));
	widget.capture_ = varval->field_.varvalue_.var_;
	widget.capture_aptr_ = varval->field_.varvalue_.aptr_;
	n2s_widgetset_insert(arg->state_, nw->widgets_, &widget, NULL);

	n2si_bifunc_widget_posinc_y(nw, nw->objy_);

	n2e_funcarg_pushi(arg, N2_SCAST(n2_valint_t, next_id));
	return 1;
}
#endif// N2_CONFIG_USE_GUI_LIB

#endif// N2_CONFIG_USE_SDL_LIB

static void n2i_environment_bind_standards_builtins(n2_state_t* state, n2_pp_context_t* ppc, n2_environment_t* e)
{
	if (e->is_standards_bounded_) { return; }

	n2_str_t tstr;
	n2_str_init(&tstr);

	// マクロ
	{
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_nocr", 1 << N2S_MESOPT_NOCR);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_shadow", 1 << N2S_MESOPT_SHADOW);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_outline", 1 << N2S_MESOPT_OUTLINE);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_light", 1 << N2S_MESOPT_LIGHT);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_gmode", 1 << N2S_MESOPT_GMODE);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_hcenter@n2", 1 << N2S_MESOPT_HCENTER);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_vcenter@n2", 1 << N2S_MESOPT_VCENTER);
		n2i_pp_context_register_macro_rawi(state, ppc, "mesopt_hright@n2", 1 << N2S_MESOPT_HRIGHT);

		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_gdi", N2S_GMODE_COPY);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_mem", N2S_GMODE_MEMCOPY);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_rgb0", N2S_GMODE_COPY_BLACKTRANS);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_alpha", N2S_GMODE_BLEND);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_rgb0alpha", N2S_GMODE_BLEND_COLTRANS);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_add", N2S_GMODE_BLEND_ADD);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_sub", N2S_GMODE_BLEND_SUB);
		n2i_pp_context_register_macro_rawi(state, ppc, "gmode_pixela", N2S_GMODE_BLEND_RALPHA);

		n2i_pp_context_register_macro_rawi(state, ppc, "picmesopt_alphablend@n2", N2S_PICMESOPT_FLAG_ALPHA_BLEND);

		n2i_pp_context_register_macro_rawi(state, ppc, "celbitmap_rgb", 0);
		n2i_pp_context_register_macro_rawi(state, ppc, "celbitmap_bgr", 1);
		n2i_pp_context_register_macro_rawi(state, ppc, "celbitmap_capture", 16);
	}

	// システム変数
	{
#define N2SI_SYSVAREX_PROPERTY_NAMED(name, fname) \
		{name,			n2si_sysvar_ex_##fname, n2si_sysvar_ex_inspect_##fname}
#define N2SI_SYSVAREX_PROPERTY(name) \
		N2SI_SYSVAREX_PROPERTY_NAMED(#name, name)

		static const struct 
		{
			const char* name_;
			n2_sysvar_ex_callback_t callback_;
			n2_sysvar_ex_inspect_t inspect_;
		}
		builtins[] =
		{
			N2SI_SYSVAREX_PROPERTY(ginfo_accx),
			N2SI_SYSVAREX_PROPERTY(ginfo_accy),
			N2SI_SYSVAREX_PROPERTY(ginfo_accz),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_sel", selected_window_index),
			N2SI_SYSVAREX_PROPERTY_NAMED("imgunpackw@n2", imgunpackw),
			N2SI_SYSVAREX_PROPERTY_NAMED("imgunpackh@n2", imgunpackh),

			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_winx", width),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_winy", height),
			N2SI_SYSVAREX_PROPERTY(mousex),
			N2SI_SYSVAREX_PROPERTY(mousey),
			N2SI_SYSVAREX_PROPERTY(mousew),
			N2SI_SYSVAREX_PROPERTY(ginfo_r),
			N2SI_SYSVAREX_PROPERTY(ginfo_g),
			N2SI_SYSVAREX_PROPERTY(ginfo_b),
			N2SI_SYSVAREX_PROPERTY(ginfo_a),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_cx", posx),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_cy", posy),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_mesx", mesx),
			N2SI_SYSVAREX_PROPERTY_NAMED("ginfo_mesy", mesy),
			N2SI_SYSVAREX_PROPERTY_NAMED("hwnd", hwnd),
			N2SI_SYSVAREX_PROPERTY_NAMED("hdc", hdc),
			N2SI_SYSVAREX_PROPERTY_NAMED("hinstance", hinstance),

			{NULL,	NULL,	NULL}
		};
		for (size_t i = 0; builtins[i].name_; ++i)
		{
			n2e_register_sysvar_ex(state, builtins[i].name_, builtins[i].callback_, builtins[i].inspect_, NULL);
		}

#undef N2SI_SYSVAREX_PROPERTY
#undef N2SI_SYSVAREX_PROPERTY_NAMED
	}

	// 関数
	{
		static const struct 
		{
			const char* name_;
			n2_func_callback_t callback_;
		} builtins[] =
		{
			{"gsel",				n2si_bifunc_gsel},
			{"pos",					n2si_bifunc_pos},
			{"color",				n2si_bifunc_color},
			{"rgbcolor",			n2si_bifunc_rgbcolor},
			{"hsvcolor",			n2si_bifunc_hsvcolor},
			{"objcolor",			n2si_bifunc_objcolor},
			{"gmode",				n2si_bifunc_gmode},
			{"gmulcolor",			n2si_bifunc_gmulcolor},
			{"redraw",				n2si_bifunc_redraw},
#if N2_CONFIG_USE_IMAGE_READ_LIB
			{"imgunpack@n2",		n2si_bifunc_imgunpack_n2},
#endif// N2_CONFIG_USE_IMAGE_READ_LIB
#if N2_CONFIG_USE_IMAGE_WRITE_LIB
			{"imgpack@n2",			n2si_bifunc_imgpack_n2},
#endif// N2_CONFIG_USE_IMAGE_WRITE_LIB
#if N2_CONFIG_USE_SDL_LIB
			{"screen",				n2si_bifunc_screen},
			{"buffer",				n2si_bifunc_buffer},
			{"cls",					n2si_bifunc_cls},
			{"title",				n2si_bifunc_title},
			{"wait",				n2si_bifunc_wait},
			{"await",				n2si_bifunc_await},
			{"systimer@n2",			n2si_bifunc_systimer_n2},
			{"texfilter@n2",		n2si_bifunc_texfilter_n2},
			{"line",				n2si_bifunc_line},
			{"gline@n2",			n2si_bifunc_line_n2},
			{"boxf",				n2si_bifunc_boxf},
			{"gboxf@n2",			n2si_bifunc_boxf_n2},
			{"circle",				n2si_bifunc_circle},
			{"gcircle@n2",			n2si_bifunc_circle_n2},
			{"grect",				n2si_bifunc_grect},
			{"gcopy",				n2si_bifunc_gcopy},
			{"gzoom",				n2si_bifunc_gzoom},
			{"grotate",				n2si_bifunc_grotate},
			{"mes",					n2si_bifunc_mes},
			{"font",				n2si_bifunc_font},
			{"sysfont",				n2si_bifunc_sysfont},
			{"fontloadmem@n2",		n2si_bifunc_fontloadmem_n2},
			{"fontload@n2",			n2si_bifunc_fontload_n2},
			{"picmes@n2",			n2si_bifunc_picmes_n2},
			{"getkey",				n2si_bifunc_getkey},
			{"stick",				n2si_bifunc_stick},
			{"clipchks@n2",			n2si_bifunc_clipchks},
			{"clipgets@n2",			n2si_bifunc_clipgets},
			{"clipputs@n2",			n2si_bifunc_clipputs},
#if N2_CONFIG_USE_IMAGE_READ_LIB
			{"picload",				n2si_bifunc_picload},
			{"celload",				n2si_bifunc_celload},
#endif// N2_CONFIG_USE_IMAGE_READ_LIB
			{"celdiv",				n2si_bifunc_celdiv},
			{"celput",				n2si_bifunc_celput},
			{"celbitmap",			n2si_bifunc_celbitmap},
			{"celbitmap@n2",		n2si_bifunc_celbitmap_n2},
#if N2_CONFIG_USE_GUI_LIB
			{"objsize",				n2si_bifunc_objsize},
			{"objprm",				n2si_bifunc_objprm},
			{"objenable",			n2si_bifunc_objenable},
			{"clrobj",				n2si_bifunc_clrobj},
			{"button",				n2si_bifunc_button},
			{"chkbox",				n2si_bifunc_chkbox},
			{"input",				n2si_bifunc_input},
			{"mesbox",				n2si_bifunc_mesbox},
#endif// N2_CONFIG_USE_GUI_LIB
#endif// N2_CONFIG_USE_SDL_LIB
			{NULL,					NULL}
		};
		for (size_t i = 0; builtins[i].name_; ++i)
		{
			n2_naming_compute(state, builtins[i].name_, SIZE_MAX, NULL, NULL, &tstr, NULL);
			const int funcindex = n2_functable_register(state, e->functable_, tstr.str_);
			n2_func_t* func = n2_functable_peek(e->functable_, funcindex);
			N2_ASSERT(func);
			n2i_func_setas_callback(state, func, N2_FUNC_INTERNAL, builtins[i].callback_, NULL);
		}
	}

	// その他の初期化
	{
	}

	n2_str_teardown(state, &tstr);
	e->is_standards_bounded_ = N2_TRUE;
}


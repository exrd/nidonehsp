
#ifndef N2_HEADER_INCLUDE_GUARD
#define N2_HEADER_INCLUDE_GUARD

/*=============================================================================

	nidonehsp is licensed under NYSL(煮るなり焼くなり好きにしろライセンス):

	ライセンス：
		NYSL Version 0.9982
		A. 本ソフトウェアは Everyone'sWare です。このソフトを手にした一人一人が、
		   ご自分の作ったものを扱うのと同じように、自由に利用することが出来ます。
		  A-1. フリーウェアです。作者からは使用料等を要求しません。
		  A-2. 有料無料や媒体の如何を問わず、自由に転載・再配布できます。
		  A-3. いかなる種類の 改変・他プログラムでの利用 を行っても構いません。
		  A-4. 変更したものや部分的に使用したものは、あなたのものになります。
			   公開する場合は、あなたの名前の下で行って下さい。
		B. このソフトを利用することによって生じた損害等について、作者は
		   責任を負わないものとします。各自の責任においてご利用下さい。
		C. 著作者人格権は exrd に帰属します。著作権は放棄します。
		D. 以上の３項は、ソース・実行バイナリの双方に適用されます。

	in English:
		A. This software is "Everyone'sWare". It means:
		Anybody who has this software can use it as if he/she is
		the author.

		A-1. Freeware. No fee is required.
		A-2. You can freely redistribute this software.
		A-3. You can freely modify this software. And the source
		may be used in any software with no limitation.
		A-4. When you release a modified version to public, you
		must publish it with your name.

		B. The author is not responsible for any kind of damages or loss
		while using or misusing this software, which is distributed
		"AS IS". No warranty of any kind is expressed or implied.
		You use AT YOUR OWN RISK.

		C. Copyrighted to exrd

		D. Above three clauses are applied both to source and binary
		form of this software.

============================================================================*/

//=============================================================================
// コンフィグ

#ifdef N2_CONFIG_PREINCLUDE
#include N2_CONFIG_PREINCLUDE
#endif

// malloc,freeをカスタム
#ifndef N2_CONFIG_USE_STD_MALLOC
#define N2_CONFIG_USE_STD_MALLOC				(1)
#endif

// memcpy, memsetをカスタム
#ifndef N2_CONFIG_USE_STD_MEMUTIL
#define N2_CONFIG_USE_STD_MEMUTIL				(1)
#endif

// assertをカスタム
#ifndef N2_CONFIG_USE_ASSERT
#define N2_CONFIG_USE_ASSERT					(1)
#endif

// sqrtなどをカスタム
#ifndef N2_CONFIG_USE_STD_MATH
#define N2_CONFIG_USE_STD_MATH					(1)
#endif

// strlenなどをカスタム
#ifndef N2_CONFIG_USE_STD_STR
#define N2_CONFIG_USE_STD_STR					(1)
#endif

// atoi,atofなどをカスタム
#ifndef N2_CONFIG_USE_STD_AIF
#define N2_CONFIG_USE_STD_AIF					(1)
#endif

// fileioをカスタム
#ifndef N2_CONFIG_USE_STD_FILEIO
#define N2_CONFIG_USE_STD_FILEIO				(1)
#endif

// timeなどをカスタム
#ifndef N2_CONFIG_USE_STD_TIME
#define N2_CONFIG_USE_STD_TIME					(1)
#endif

// snprintfなどをカスタム
#ifndef N2_CONFIG_USE_STD_PRINT
#define N2_CONFIG_USE_STD_PRINT					(1)
#endif

// stb_sprintfを使う（N2_VSNPRINTFを使わない）
#ifndef N2_CONFIG_USE_SPRINTF_LIB
#define N2_CONFIG_USE_SPRINTF_LIB				(1)
#endif

// rpmallocを使う（使えるようにする）
#ifndef N2_CONFIG_USE_RPMALLOC_LIB
#define N2_CONFIG_USE_RPMALLOC_LIB				(0)
#endif

// stb_image.hを使う
#ifndef N2_CONFIG_USE_IMAGE_READ_LIB
#define N2_CONFIG_USE_IMAGE_READ_LIB			(1)
#endif

// stb_image_write.hを使う
#ifndef N2_CONFIG_USE_IMAGE_WRITE_LIB
#define N2_CONFIG_USE_IMAGE_WRITE_LIB			(1)
#endif

// cute_aseprite.hを使う
#ifndef N2_CONFIG_USE_ASEPRITE_LIB
#define N2_CONFIG_USE_ASEPRITE_LIB				(0)
#endif

// dr_wav.hを使う
#ifndef N2_CONFIG_USE_AUDIO_WAV_LIB
#define N2_CONFIG_USE_AUDIO_WAV_LIB				(1)
#endif

// dr_mp3.hを使う
#ifndef N2_CONFIG_USE_AUDIO_MP3_LIB
#define N2_CONFIG_USE_AUDIO_MP3_LIB				(1)
#endif

// stb_vorbis.cを使う
#ifndef N2_CONFIG_USE_AUDIO_OGG_LIB
#define N2_CONFIG_USE_AUDIO_OGG_LIB				(1)
#endif

// dr_flac.hを使う
#ifndef N2_CONFIG_USE_AUDIO_FLAC_LIB
#define N2_CONFIG_USE_AUDIO_FLAC_LIB			(0)
#endif

// stb_truetype.h(+stb_rect_pack.h)を使う
#ifndef N2_CONFIG_USE_FONT_LIB
#define N2_CONFIG_USE_FONT_LIB					(1)
#endif

// miniz.hを使う
#ifndef N2_CONFIG_USE_Z_LIB
#define N2_CONFIG_USE_Z_LIB						(1)
#endif

// culz.hを使う
#ifndef N2_CONFIG_USE_ULZ_LIB
#define N2_CONFIG_USE_ULZ_LIB					(1)
#endif

// json.hを使う
#ifndef N2_CONFIG_USE_JSON_LIB
#define N2_CONFIG_USE_JSON_LIB					(1)
#endif

// zed_net.hを使う
#ifndef N2_CONFIG_USE_NET_SOCKET_LIB
#define N2_CONFIG_USE_NET_SOCKET_LIB			(0)
#endif

// sdlを使う
#ifndef N2_CONFIG_USE_SDL_LIB
#define N2_CONFIG_USE_SDL_LIB					(0)
#endif

// picomsgpack.hを有効
#ifndef N2_CONFIG_USE_MSGPACK_LIB
#define N2_CONFIG_USE_MSGPACK_LIB				(1)
#endif

// md5.h
#ifndef N2_CONFIG_USE_MD5_LIB
#define N2_CONFIG_USE_MD5_LIB					(1)
#endif

// aes.h
#ifndef N2_CONFIG_USE_AES_LIB
#define N2_CONFIG_USE_AES_LIB					(1)
#endif

// cp932 encodingを有効
#ifndef N2_CONFIG_USE_ENCODING_CP932
#define N2_CONFIG_USE_ENCODING_CP932			(0)
#endif

// n2標準機能
#ifndef N2_CONFIG_USE_N2_STANDARD
#define N2_CONFIG_USE_N2_STANDARD				(0)
#endif

// debugging
#ifndef N2_CONFIG_USE_DEBUGGING
#define N2_CONFIG_USE_DEBUGGING					(0)
#endif

// profiling
#ifndef N2_CONFIG_USE_PROFILING
#define N2_CONFIG_USE_PROFILING					(0)
#endif

// thread_local
#ifndef N2_CONFIG_THREAD_LOCAL
#define N2_THREAD_LOCAL		
#else
#define N2_THREAD_LOCAL		N2_CONFIG_THREAD_LOCAL
#endif

//=============================================================================
// コンフィグから決まる値
#define N2_CONFIG_USE_EMBED_FONT \
	(N2_CONFIG_USE_FONT_LIB && \
		N2_CONFIG_USE_SDL_LIB && \
		N2_CONFIG_USE_N2_STANDARD)

#define N2_CONFIG_USE_GUI_LIB \
	(N2_CONFIG_USE_FONT_LIB && \
		N2_CONFIG_USE_SDL_LIB && \
		N2_CONFIG_USE_N2_STANDARD)

#define N2_CONFIG_USE_INSPECTOR \
	(N2_CONFIG_USE_GUI_LIB && \
		N2_CONFIG_USE_DEBUGGING && \
		0/*WIP*/)

//=============================================================================
// コンフィグに限らず必要なヘッダや定義
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

//=============================================================================
// プラットフォーム
#define N2_PLATFORM_WINDOWS		(0)
#define N2_PLATFORM_EMSCRIPTEN	(1)
#define N2_PLATFORM_UNIX		(2)

#if defined(_WIN32) || defined(_WIN64)
#define N2_PLATFORM				N2_PLATFORM_WINDOWS
#elif defined(__EMSCRIPTEN__)
#define N2_PLATFORM				N2_PLATFORM_EMSCRIPTEN
#else
#error "Unsupported platform"
#endif

#define N2_PLATFORM_IS_WINDOWS		(N2_PLATFORM == N2_PLATFORM_WINDOWS)
#define N2_PLATFORM_IS_EMSCRIPTEN	(N2_PLATFORM == N2_PLATFORM_EMSCRIPTEN)
#define N2_PLATFORM_IS_UNIX			(N2_PLATFORM == N2_PLATFORM_UNIX)

// コンパイラー
#define N2_COMPILER_UNKNOWN		(0)
#define N2_COMPILER_CLANG		(1)
#define N2_COMPILER_MSVC		(2)

#if defined __clang__
#define N2_COMPILER			N2_COMPILER_CLANG
#elif defined _MSC_VER
#define N2_COMPILER			N2_COMPILER_MSVC
#else
#define N2_COMPILER			N2_COMPILER_UNKNOWN
#endif

#define N2_COMPILER_IS_CLANG	(N2_COMPILER == N2_COMPILER_CLANG)
#define N2_COMPILER_IS_MSVC		(N2_COMPILER == N2_COMPILER_MSVC)

// アーキテクチャビット幅
#define N2_ARCHBIT_64BIT	(0)
#define N2_ARCHBIT_32BIT	(1)

#if defined(_WIN64)
#define N2_ARCHBIT		N2_ARCHBIT_64BIT
#elif defined(_WIN32)
#define N2_ARCHBIT		N2_ARCHBIT_32BIT
#elif INTPTR_MAX == INT64_MAX
#define N2_ARCHBIT		N2_ARCHBIT_64BIT
#elif INTPTR_MAX == INT32_MAX
#define N2_ARCHBIT		N2_ARCHBIT_32BIT
#else
#error "Unknown pointer size"
#endif

#define N2_ARCHBIT_IS_64BIT		(N2_ARCHBIT == N2_ARCHBIT_64BIT)
#define N2_ARCHBIT_IS_32BIT		(N2_ARCHBIT == N2_ARCHBIT_32BIT)

// エラーチェック
#if N2_CONFIG_USE_EMBED_FONT && !N2_CONFIG_USE_Z_LIB
#error "embedded font require z lib"
#endif

#if N2_CONFIG_USE_NET_SOCKET_LIB && !N2_PLATFORM_IS_WINDOWS
#error "network library support only windows platform"
#endif

// その他
#define N2_CONFIG_EVENT_BASED_MOUSE_STATE \
	(N2_PLATFORM_IS_EMSCRIPTEN)

//=============================================================================
// コンフィグに伴うヘッダや定義
#include <stdarg.h>// va_***
#include <setjmp.h>// setjmp(), longjmp()
#include <stdlib.h>// abort()

#ifdef __cplusplus
#define N2_CPP		(1)
#define N2_C_CPP(c, cpp)		cpp
#else
#define N2_CPP		(0)
#define N2_C_CPP(c, cpp)		c
#endif

#if N2_CONFIG_USE_STD_MALLOC
#include <stdlib.h>
#endif

#if N2_CONFIG_USE_STD_MEMUTIL
#include <string.h>
#define N2_MEMCPY(dst, src, size)		memcpy(dst, src, size)
#define N2_MEMCMP(lhs, rhs, size)		memcmp(lhs, rhs, size)
#define N2_MEMMOVE(dst, src, size)		memmove(dst, src, size)
#define N2_MEMSET(dst, val, size)		memset(dst, val, size)
#endif

#if N2_CONFIG_USE_ASSERT
#include <assert.h>
#define N2_ASSERT(...)			assert(__VA_ARGS__)
#elif !defined(N2_ASSERT)
#define N2_ASSERT(...) 
#endif

#if N2_CONFIG_USE_STD_MATH
#include <math.h>
#define N2_SIN(x)			sin(x)
#define N2_COS(x)			cos(x)
#define N2_TAN(x)			tan(x)
#define N2_ASIN(x)			sin(x)
#define N2_ACOS(x)			cos(x)
#define N2_ATAN2(y, x)		atan2(y, x)
#define N2_SQRT(x)			sqrt(x)
#define N2_POW(x, y)		pow(x, y)
#define N2_EXP(x)			exp(x)
#define N2_LOG(x)			log(x)
#define N2_FMOD(x, y)		fmod(x, y)
#define N2_ROUND(x)			round(x)
#define N2_FLOOR(x)			floor(x)
#define N2_CEIL(x)			ceil(x)
#endif

#if N2_CONFIG_USE_STD_STR
#include <string.h>
#define N2_STRLEN(s)				strlen(s)
#define N2_STRNLEN(s, size)			strnlen(s, size)
#define N2_STRCMP(l, r)				strcmp(l, r)
#define N2_STRNCMP(l, r, size)		strncmp(l, r, size)
#endif

#if N2_CONFIG_USE_STD_AIF
#include <stdlib.h>
#define N2_STRTOLL(s, e, r)			strtoll(s, e, r)
#define N2_STRTOD(s, e)				strtod(s, e)
#endif

#if N2_CONFIG_USE_STD_FILEIO
#include <stdio.h>
#else
/*you have to supply file_read_ and file_write_ functions in n2_state_config_t for n2_state_init()*/
#endif

#if N2_CONFIG_USE_STD_TIME
#include <time.h>
#define N2_TIME()		time(NULL)
#endif

#if N2_CONFIG_USE_STD_PRINT
#include <stdio.h>
#define N2_VSNPRINTF(buf, size, s, args)	vsnprintf(buf, size, s, args)
#endif

#define N2_VERSION		(0x00000102)// reserved(1byte)-major(1byte)-minor(1byte)-patch(1byte)

#define N2_STRINGIZE_IMPL(s)	#s
#define N2_STRINGIZE(s)			N2_STRINGIZE_IMPL(s)

#define N2_TCAST_IMPL(type, ...)	(type)(__VA_ARGS__)
#define N2_TCAST(type, ...)			(N2_TCAST_IMPL(type, __VA_ARGS__))
#define N2_SCAST(type, ...)			N2_TCAST(type, __VA_ARGS__)
#define N2_RCAST(type, ...)			N2_TCAST(type, __VA_ARGS__)
#define N2_CCAST(type, ...)			N2_TCAST(type, __VA_ARGS__)
#define N2_BCAST(type, ...)			N2_TCAST(type, __VA_ARGS__)

#define N2_TMALLOC(type, state)				(N2_RCAST(type*, n2_malloc(state, sizeof(type))))
#define N2_TMALLOCA(type, state, size)		(N2_RCAST(type*, n2_malloc(state, sizeof(type) * size)))
#define N2_TREALLOC(type, state, size, old_ptr, old_size)		(N2_RCAST(type*, n2_realloc(state, sizeof(type) * size, old_ptr, sizeof(type) * old_size)))

#define N2_ARRAYDIM(ar)		(sizeof(ar) / sizeof(*ar))

#define N2_MIN(x, y)			((x) < (y) ? (x) : (y))
#define N2_MAX(x, y)			((x) < (y) ? (y) : (x))
#define N2_THREE_WAY_CMP(x, y)	(((x) == (y)) ?  0 : ((x) < (y)) ? -1 : 1)

#define N2_MAX_TEMPLATE_STRING_DEPTH	(8)

#define N2_VARIABLE_DIM		(4)
#define N2_MAX_VARIABLE_ELEMENT_SIZE		(128)
#define N2_MAX_FUNC_ALIAS_LOOP				(128)

#define N2_DEFAULT_FILE_READ_TMP_BUFFER_SIZE		(1024 * 1024)

#define N2_DEFAULT_Z_DECOMP_READ_TMP_BUFFER_SIZE	(1024 * 1024)

#define N2_DEFAULT_VALUE_CACHE_NUM					(64)
#define N2_DEFAULT_VARIABLE_ELEMENT_MIN_NUM			(16)
#define N2_DEFAULT_VARIABLE_STR_ELEMENT_MIN_NUM		(1)
#define N2_DEFAULT_VARIABLE_GRANULE_SIZE			(64)
#define N2_DEFAULT_MAX_SHORTFRAME_NEST				(64)
#define N2_DEFAULT_MAX_CALL_NEST					(64)

#define N2_DEFAULT_MESSAGE_LOG_MAX					(1024)

#define N2_DEFAULT_REFERRENCE_HSPVER				(0x3601)

#define N2S_DEFAULT_WINDOW_NUM						(128)
#define N2S_DEFAULT_AWAIT_STEP_DURATION				(16)
#define N2S_DEFAULT_AWAIT_EXIT_MARGIN				(N2_PLATFORM_IS_WINDOWS ? 3 : 1)
#define N2S_DEFAULT_WINDOW_WIDTH					(640)
#define N2S_DEFAULT_WINDOW_HEIGHT					(480)

#define N2S_DEFAULT_STANDARD_VERTEX_NUM				(128 * 1024)
#define N2S_DEFAULT_STANDARD_INDEX_NUM				(128 * 1024)
#define N2S_DEFAULT_STANDARD_COMMAND_NUM			(4 * 1024)
#define N2S_DEFAULT_STANDARD_COMMAND_DATA_NUM		(4 * 1024)

#define N2S_DEFAULT_STANDARD_GUI_VERTEX_NUM			(128 * 1024)
#define N2S_DEFAULT_STANDARD_GUI_INDEX_NUM			(128 * 1024)
#define N2S_DEFAULT_STANDARD_GUI_VERTEX_EXSTEP		(32 * 1024)
#define N2S_DEFAULT_STANDARD_GUI_INDEX_EXSTEP		(32 * 1024)

#define N2S_DEFAULT_FONT_FALLBACK_CODEPOINT			0x3f// '?' in unicode
#define N2S_DEFAULT_FONT_ATLAS_WIDTH				(2048)
#define N2S_DEFAULT_FONT_ATLAS_HEIGHT				(2048)
#define N2S_DEFAULT_FONT_BAKE_HEIGHT				(18.f)
#define N2S_DEFAULT_FONT_DRAW_HEIGHT				(18.f)

#define N2S_DEFAULT_WIDGET_INPUT_MAX_BUFFER_SIZE	(4 * 1024)

#define N2_LINE_BASE		(1)// line index base
#define N2_COLUMN_BASE		(1)// column index base

#ifndef N2_API
#define N2_API		N2_C_CPP( , extern "C")
#endif

#ifndef N2_INLINE
#define N2_INLINE	inline
#endif

#define N2_DECLARE_ENUM(type)	N2_C_CPP(typedef enum type type, )

// 内部フラグ

#ifndef N2I_CONFIG_USE_EMBED_FONT_FA_REGULAR
#define N2I_CONFIG_USE_EMBED_FONT_FA_REGULAR	(0)
#endif

#ifndef N2I_CONFIG_USE_EMBED_FONT_FA_SOLID
#define N2I_CONFIG_USE_EMBED_FONT_FA_SOLID		(N2_CONFIG_USE_DEBUGGING)
#endif

#define N2I_ENABLE_SDL_RENDERER		(0)

//=============================================================================
// ライブラリ依存の宣言など

#if N2_CONFIG_USE_FONT_LIB
struct stbtt_fontinfo;
#endif

#if N2_CONFIG_USE_SDL_LIB

typedef struct SDL_Window SDL_Window;
#if N2I_ENABLE_SDL_RENDERER
typedef struct SDL_Renderer SDL_Renderer;
#endif

#include <SDL_opengles2_khrplatform.h>
#include "embed/glad_gles3.h"

#define N2_SDL_OR(sdl, nosdl)	sdl

#else

#define N2_SDL_OR(sdl, nosdl)	nosdl

#endif

#if N2_CONFIG_USE_GUI_LIB
struct nk_context;
struct nk_buffer;
struct nk_user_font;
#endif

// nidonehsp自身
#if N2_COMPILER_IS_MSVC
#pragma warning(push)
#pragma warning(disable: 4201)// nonstandard extension used: nameless struct/union
#endif

//=============================================================================
// 前方宣言
typedef struct n2_state_t n2_state_t;

typedef struct n2_variable_t n2_variable_t;

N2_DECLARE_ENUM(n2_value_e);
enum n2_value_e
{
	// HSP本家のvartypeと一致させるために、ちょっと順番を弄る
	N2_VALUE_NIL = 0,

	N2_VALUE_LABEL,// = 1
	N2_VALUE_STRING,// = 2
	N2_VALUE_FLOAT,// = 3
	N2_VALUE_INT,// = 4
	N2_VALUE_MODINST,// = 5

	N2_VALUE_VARIABLE,

	N2_MAX_VALUE
};
typedef struct n2_value_t n2_value_t;

typedef struct n2_uselib_t n2_uselib_t;

typedef struct n2_func_t n2_func_t;

typedef struct n2_module_t n2_module_t;
typedef struct n2_modinstance_t n2_modinstance_t;

typedef struct n2_fiber_t n2_fiber_t;
typedef struct n2_environment_t n2_environment_t;
typedef struct n2_ast_evaluate_context_t n2_ast_evaluate_context_t;

typedef int n2_bool_t;
#define N2_TRUE		(1)
#define N2_FALSE	(0)

#define N2_UNUSE(...)	((void)(__VA_ARGS__))

#define N2_MAXALIGN_SIZE		N2_MAX(sizeof(intmax_t), sizeof(size_t))

//=============================================================================
// メモリユーティリティ
typedef void* (*n2_allocate_func_t)(void* alloc_user, size_t new_size, void* old_ptr, size_t old_size);
typedef void (*n2_free_func_t)(void* alloc_user, void* ptr);
typedef void (*n2_allocator_close_func_t)(void* alloc_user);

// メモリアロケーションコンフィグ
typedef struct n2_allocator_t n2_allocator_t;
struct n2_allocator_t
{
	n2_allocate_func_t allocate_;
	n2_free_func_t free_;
	void* alloc_user_;
};

N2_API void n2_swap(void* l, void* r, size_t size);
N2_API void* n2_ptr_offset(void* p, ptrdiff_t offset);
N2_API const void* n2_cptr_offset(const void* p, ptrdiff_t offset);
N2_API ptrdiff_t n2_ptr_diff(const void* lhs, const void* rhs);

N2_API uint8_t n2_ptr_read8(const void* ptr);
N2_API uint16_t n2_ptr_read16(const void* ptr);
N2_API uint32_t n2_ptr_read32(const void* ptr);
N2_API uint64_t n2_ptr_read64(const void* ptr);
N2_API void n2_ptr_write8(void* ptr, uint8_t v);
N2_API void n2_ptr_write16(void* ptr, uint16_t v);
N2_API void n2_ptr_write32(void* ptr, uint32_t v);
N2_API void n2_ptr_write64(void* ptr, uint64_t v);

N2_API void* n2_malloc(n2_state_t* state, size_t size);
N2_API void* n2_realloc(n2_state_t* state, size_t new_size, void* old_ptr, size_t old_size);
N2_API void n2_free(n2_state_t* state, void* ptr);

N2_API void* n2_xmalloc(n2_state_t* state, size_t size);
N2_API void* n2_xrealloc(n2_state_t* state, size_t new_size, void* old_ptr);
N2_API void n2_xfree(n2_state_t* state, void* ptr);

// グローバルステート用（N2_THREAD_LOCALが反映される）
N2_API void n2g_set_state(n2_state_t* state);
N2_API n2_state_t* n2g_get_state();
N2_API void* n2g_malloc(size_t size);
N2_API void* n2g_realloc(size_t new_size, void* old_ptr, size_t old_size);
N2_API void n2g_free(void* ptr);
N2_API void* n2g_xmalloc(size_t size);
N2_API void* n2g_xrealloc(size_t new_size, void* old_ptr);
N2_API void n2g_xfree(void* ptr);

// メモリプール
typedef struct n2_mempool_t n2_mempool_t;
struct n2_mempool_t
{
	void* arena_;
	size_t arena_size_;
	size_t blocksize_;
	size_t blocknum_;
	void* head_;
};

N2_API n2_mempool_t* n2_mempool_alloc(n2_state_t* state, size_t blocksize, size_t blocknum);
N2_API void n2_mempool_free(n2_state_t* state, n2_mempool_t* mempool);

N2_API void* n2_mempool_try_alloc(n2_mempool_t* mempool, size_t size);
N2_API n2_bool_t n2_mempool_test_include(const n2_mempool_t* mempool, void* ptr);
N2_API n2_bool_t n2_mempool_try_free(n2_mempool_t* mempool, void* ptr);

//=============================================================================
// バッファユーティリティ
typedef struct
{
	void* data_;
	size_t size_;
	size_t buffer_size_;
	size_t expand_step_;
} n2_buffer_t;

N2_API void n2_buffer_init(n2_buffer_t* buffer);
N2_API void n2_buffer_teardown(n2_state_t* state, n2_buffer_t* buffer);
N2_API void n2_buffer_set_expand_step(n2_buffer_t* buffer, size_t expand_step);
N2_API void n2_buffer_copy_to(n2_state_t* state, n2_buffer_t* buffer, const n2_buffer_t* rbuffer);
N2_API void n2_buffer_swap(n2_buffer_t* buffer, n2_buffer_t* rbuffer);
N2_API void n2_buffer_clear(n2_buffer_t* buffer);
N2_API n2_bool_t n2_buffer_reserve(n2_state_t* state, n2_buffer_t* buffer, size_t size);
N2_API void n2_buffer_set(n2_state_t* state, n2_buffer_t* buffer, const void* cbuffer, size_t length);
N2_API void n2_buffer_append(n2_state_t* state, n2_buffer_t* buffer, const void* append_buffer, size_t append_length);
N2_API void n2_buffer_append_values(n2_state_t* state, n2_buffer_t* buffer, uint8_t value, size_t append_length);
N2_API void n2_buffer_append_values_transparent(n2_state_t* state, n2_buffer_t* buffer, uint8_t value, size_t append_length);
N2_API n2_bool_t n2_buffer_insert(n2_state_t* state, n2_buffer_t* buffer, size_t offset, const void* data, size_t length);
N2_API size_t n2_buffer_erase(n2_buffer_t* buffer, size_t offset, size_t length);
N2_API size_t n2_buffer_replace_pattern(n2_state_t* state, n2_buffer_t* buffer, const void* src, size_t src_length, const void* to, size_t to_length);

N2_API n2_buffer_t* n2_buffer_alloc(n2_state_t* state, size_t initial_buffer_size);
N2_API n2_buffer_t* n2_buffer_clone(n2_state_t* state, const n2_buffer_t* rbuffer);
N2_API void n2_buffer_free(n2_state_t* state, n2_buffer_t* buffer);


//=============================================================================
// エンコーディングユーティリティ
typedef int32_t n2_codepoint_t;
typedef n2_codepoint_t n2_unicp_t;

#define N2_CODEPOINT_MAX_BUFFER_SIZE	(4 + 1)
#define N2_UNICODE_MIN					(0)
#define N2_UNICODE_MAX					(0x1fffff)// 21bit

N2_DECLARE_ENUM(n2_encoding_e);
enum n2_encoding_e
{
	N2_ENCODING_UNKNOWN = -1,
	N2_ENCODING_UTF8 = 0,
	N2_ENCODING_UTF16NE,
	N2_ENCODING_UTF16LE,
	N2_ENCODING_UTF16BE,
	N2_ENCODING_CP932,

	N2_MAX_ENCODING
};

N2_API n2_encoding_e n2_encoding_find(const char* name, size_t length);
N2_API const char* n2_encoding_name(n2_encoding_e encoding, const char* on_not_found);

typedef struct n2_str_t n2_str_t;

N2_API n2_bool_t n2_unicode_is_newline(n2_unicp_t unicp);

N2_API const char* n2_encoding_utf8_fetch(const char* str, n2_unicp_t* dst);
N2_API size_t n2_encoding_utf8_bytesize(n2_unicp_t unicp);
N2_API char* n2_encoding_utf8_print(char* dst, size_t dst_size, n2_unicp_t unicp);
N2_API int n2_encoding_utf8_verify(const char* str, size_t length);

N2_API size_t n2_encoding_utf16_bytesize(n2_unicp_t unicp);

N2_API const char* n2_encoding_utf16ne_fetch(const char* str, n2_unicp_t* dst);
N2_API char* n2_encoding_utf16ne_print(char* dst, size_t dst_size, n2_unicp_t unicp);
N2_API size_t n2_encoding_utf16ne_length(const char* str, size_t length);
N2_API int n2_encoding_utf16ne_verify(const char* str, size_t length);
N2_API n2_bool_t n2_encoding_utf16ne_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);
N2_API n2_bool_t n2_encoding_utf16ne_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);

N2_API const char* n2_encoding_utf16le_fetch(const char* str, n2_unicp_t* dst);
N2_API char* n2_encoding_utf16le_print(char* dst, size_t dst_size, n2_unicp_t unicp);
N2_API size_t n2_encoding_utf16le_length(const char* str, size_t length);
N2_API int n2_encoding_utf16le_verify(const char* str, size_t length);
N2_API n2_bool_t n2_encoding_utf16le_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);
N2_API n2_bool_t n2_encoding_utf16le_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);

N2_API const char* n2_encoding_utf16be_fetch(const char* str, n2_unicp_t* dst);
N2_API char* n2_encoding_utf16be_print(char* dst, size_t dst_size, n2_unicp_t unicp);
N2_API size_t n2_encoding_utf16be_length(const char* str, size_t length);
N2_API int n2_encoding_utf16be_verify(const char* str, size_t length);
N2_API n2_bool_t n2_encoding_utf16be_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);
N2_API n2_bool_t n2_encoding_utf16be_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);

#if N2_CONFIG_USE_ENCODING_CP932
N2_API n2_unicp_t n2_encoding_cp932_to_unicode(n2_codepoint_t codepoint, n2_unicp_t fallback);
N2_API n2_codepoint_t n2_encoding_cp932_from_unicode(n2_unicp_t unicp, n2_codepoint_t fallback);
N2_API const char* n2_encoding_cp932_fetch(const char* str, n2_codepoint_t* dst);
N2_API size_t n2_encoding_cp932_bytesize(n2_codepoint_t codepoint);
N2_API char* n2_encoding_cp932_print(char* dst, size_t dst_size, n2_codepoint_t codepoint);
N2_API int n2_encoding_cp932_verify(const char* str, size_t length);
N2_API n2_bool_t n2_encoding_cp932_convert_from_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_codepoint_t fallback);
N2_API n2_bool_t n2_encoding_cp932_convert_to_utf8(n2_state_t* state, n2_str_t* dst, const char* src, size_t src_length, n2_unicp_t fallback);
#endif

//=============================================================================
// 文字列ユーティリティ
N2_API int n2_snprintf(char* buf, size_t bufsize, const char* fmt, ...);
N2_API int n2_vsnprintf(char* buf, size_t bufsize, const char* fmt, va_list args);

N2_API char* n2_plstr_clone_size(n2_state_t* state, const char* s, size_t l);
N2_API char* n2_plstr_clone(n2_state_t* state, const char* s);
N2_API int n2_plstr_ncmp_sized(const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length);// 辞書順
N2_API int n2_plstr_ncmp_sized_fast(const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length);// 辞書順ではないが高速
N2_API int n2_plstr_cmp_case(const char* lhs, const char* rhs);
N2_API int n2_plstr_ncmp_case(const char* lhs, const char* rhs, size_t size);
N2_API int n2_plstr_search(const char* str, size_t str_len, const char* pattern, size_t pattern_len);

struct n2_str_t
{
	char* str_;
	size_t size_;
	size_t buffer_size_;
	size_t expand_step_;
};

enum
{
	N2_STR_ESCAPE_FLAG_NO_SINGLEQUOTE = 0x01,
	N2_STR_ESCAPE_FLAG_NO_DOUBLEQUOTE = 0x02,
	N2_STR_ESCAPE_FLAG_NO_BACKQUOTE = 0x04,
	N2_STR_ESCAPE_FLAG_NO_CONTROLS = 0x80,

	N2_STR_ESCAPE_FLAG_DEFAULT = 0x0,
	N2_STR_ESCAPE_FLAG_JSON = N2_STR_ESCAPE_FLAG_NO_SINGLEQUOTE | N2_STR_ESCAPE_FLAG_NO_BACKQUOTE
};

N2_API void n2_str_init(n2_str_t* str);
N2_API void n2_str_teardown(n2_state_t* state, n2_str_t* str);
N2_API const char* n2_str_cstr(const n2_str_t* str);
N2_API void n2_str_set_expand_step(n2_str_t* str, size_t expand_step);
N2_API void n2_str_vfmt_to(n2_state_t* state, n2_str_t* str, const char* fmt, va_list args);
N2_API void n2_str_fmt_to(n2_state_t* state, n2_str_t* str, const char* fmt, ...);
N2_API void n2_str_copy_to(n2_state_t* state, n2_str_t* str, const n2_str_t* rstr);
N2_API void n2_str_swap(n2_str_t* str, n2_str_t* rstr);
N2_API void n2_str_clear(n2_str_t* str);
N2_API n2_bool_t n2_str_reserve(n2_state_t* state, n2_str_t* str, size_t size);
N2_API size_t n2_str_compute_size(const n2_str_t* str);
N2_API size_t n2_str_compute_ut16ne_size(const n2_str_t* str);
N2_API void n2_str_update_size(n2_str_t* str);
N2_API int n2_str_compare(const n2_str_t* lhs, const n2_str_t* rhs);
N2_API void n2_str_set(n2_state_t* state, n2_str_t* str, const char* cstr, size_t length);
N2_API n2_bool_t n2_str_insert(n2_state_t* state, n2_str_t* str, size_t offset, const char* add_str, size_t add_length);
N2_API void n2_str_prepend(n2_state_t* state, n2_str_t* str, const char* add_str, size_t add_length);
N2_API void n2_str_appendv(n2_state_t* state, n2_str_t* str, char c);
N2_API void n2_str_append(n2_state_t* state, n2_str_t* str, const char* append_str, size_t append_length);
N2_API void n2_str_append_fmt(n2_state_t* state, n2_str_t* str, const char* fmt, ...);
N2_API int n2_str_find(const n2_str_t* str, const char* pattern, size_t pattern_length, size_t offset);
N2_API int n2_str_rfind(const n2_str_t* str, const char* pattern, size_t pattern_length, size_t offset);
N2_API n2_bool_t n2_str_starts_with(const n2_str_t* str, const char* pattern, size_t pattern_length);
N2_API n2_bool_t n2_str_ends_with(const n2_str_t* str, const char* pattern, size_t pattern_length);
N2_API size_t n2_str_erase(n2_str_t* str, size_t offset, size_t length);
N2_API n2_bool_t n2_str_replace_range(n2_state_t* state, n2_str_t* str, size_t offset, size_t size, const char* to, size_t to_length);
N2_API size_t n2_str_replace_pattern(n2_state_t* state, n2_str_t* str, const char* src, size_t src_length, const char* to, size_t to_length);
N2_API size_t n2_str_trim(n2_str_t* str, const char* src, size_t src_length, n2_bool_t left);
N2_API n2_bool_t n2_str_trim_utf8_bom(n2_str_t* str);
N2_API n2_bool_t n2_str_trim_utf16ne_bom(n2_str_t* str);
N2_API n2_bool_t n2_str_trim_utf16le_bom(n2_str_t* str);
N2_API n2_bool_t n2_str_trim_utf16be_bom(n2_str_t* str);
N2_API n2_bool_t n2_str_escaped_to(n2_state_t* state, n2_str_t* str, const char* src, size_t length, size_t flags);
N2_API n2_bool_t n2_str_unescaped_to(n2_state_t* state, n2_str_t* str, const char* src, size_t length);

N2_API n2_str_t* n2_str_alloc(n2_state_t* state, size_t initial_buffer_size);
N2_API n2_str_t* n2_str_alloc_fmt(n2_state_t* state, const char* fmt, ...);
N2_API n2_str_t* n2_str_clone(n2_state_t* state, const n2_str_t* rstr);
N2_API void n2_str_free(n2_state_t* state, n2_str_t* str);

N2_API void n2_str_buffer_mutate(n2_str_t* lhs, n2_buffer_t* rhs);

// 文字列パス
N2_DECLARE_ENUM(n2_path_separator_e);
enum n2_path_separator_e
{
	N2_PATH_SEPARATOR_NATIVE,
	N2_PATH_SEPARATOR_SLASH,
	N2_PATH_SEPARATOR_BACKSLASH,

	N2_MAX_PATH_SEPARATOR
};
N2_API char n2_path_separator(n2_path_separator_e separator);
N2_API n2_bool_t n2_path_normalize(n2_state_t* state, n2_str_t* path, n2_path_separator_e separator);
N2_API void n2_path_join(n2_state_t* state, n2_str_t* path, const char* lhs, size_t lhs_length, const char* rhs, size_t rhs_length);
N2_API void n2_path_append(n2_state_t* state, n2_str_t* path, const char* append, size_t length);
N2_API void n2_path_split(n2_state_t* state, n2_str_t* dst_dir, n2_str_t* dst_filename, n2_str_t* dst_ext, const n2_str_t* path);
N2_API void n2_path_basename(n2_state_t* state, n2_str_t* dst, const n2_str_t* path, const char* suffix, size_t suffix_length);
N2_API int n2_path_compare(const n2_str_t* lhs, const n2_str_t* rhs);

//=============================================================================
// リストユーティリティ
typedef struct n2_list_node_t n2_list_node_t;
struct n2_list_node_t
{
	n2_list_node_t* prev_;
	n2_list_node_t* next_;
};

N2_API void n2_list_node_init(n2_list_node_t* node);
N2_API void n2_list_node_link_prev(n2_list_node_t* to, n2_list_node_t* node);
N2_API void n2_list_node_link_next(n2_list_node_t* to, n2_list_node_t* node);
N2_API n2_bool_t n2_list_node_islinked(const n2_list_node_t* node);
N2_API n2_bool_t n2_list_node_unlink(n2_list_node_t* node);

typedef struct n2_list_t n2_list_t;
struct n2_list_t
{
	n2_list_node_t head_;
	n2_list_node_t tail_;
	size_t size_;
	void* user_;
};

typedef void(*n2_list_node_free_func)(n2_state_t* state, n2_list_t* l, n2_list_node_t* node);

N2_API void n2_list_init(n2_list_t* list);
N2_API n2_list_t* n2_list_alloc(n2_state_t* state);
N2_API void n2_list_free(n2_state_t* state, n2_list_t* list);

N2_API void n2_list_clear_free(n2_state_t* state, n2_list_t* list, n2_list_node_free_func freefunc);
N2_API void n2_list_clear(n2_state_t* state, n2_list_t* list);
N2_API void n2_list_prepend(n2_list_t* list, n2_list_node_t* node);
N2_API void n2_list_append(n2_list_t* list, n2_list_node_t* node);
N2_API n2_list_node_t* n2_list_shift(n2_list_t* list);
N2_API n2_list_node_t* n2_list_pop(n2_list_t* list);
N2_API n2_bool_t n2_list_erase(n2_list_t* list, n2_list_node_t* node);
N2_API size_t n2_list_update(n2_list_t* list);

#define N2_LIST_FOREACH_INLINE(list, ...) \
	{ \
		n2_list_node_t* node = (list)->head_.next_; \
		while (node && node != &(list)->tail_) \
		{ \
			n2_list_node_t* const next_node = node->next_; \
			__VA_ARGS__; \
			node = next_node; \
		} \
	}

// 型付き（継承ライクなアプローチ）
#define N2_DECLARE_TLIST(type, prefix, extn) \
	typedef struct prefix##_list_node_t prefix##_list_node_t; \
	struct prefix##_list_node_t \
	{ \
		n2_list_node_t entry_; \
		type value_; \
	}; \
	\
	extn prefix##_list_node_t* prefix##_list_node_alloc(n2_state_t* state, const type* val); \
	extn prefix##_list_node_t* prefix##_list_node_allocv(n2_state_t* state, const type val); \
	extn void prefix##_list_node_free(n2_state_t* state, prefix##_list_node_t* node); \
	\
	typedef n2_list_t prefix##_list_t; \
	extn prefix##_list_t* prefix##_list_alloc(n2_state_t* state); \
	extn void prefix##_list_free(n2_state_t* state, prefix##_list_t* list); \
	extn void prefix##_list_clear(n2_state_t* state, prefix##_list_t* list); \
	extn void prefix##_list_prepend(prefix##_list_t* list, prefix##_list_node_t* node); \
	extn void prefix##_list_append(prefix##_list_t* list, prefix##_list_node_t* node); \
	extn int prefix##_list_erase(prefix##_list_t* list, prefix##_list_node_t* node); \
	\
	typedef int(*prefix##_list_node_compre_func_t)(const type* v, const void* key); \
	extn prefix##_list_node_t* prefix##_list_find(prefix##_list_t* list, const void* key, prefix##_list_node_compre_func_t cmp);

#define N2_DEFINE_TLIST(type, prefix, extn, freefunc) \
	extn prefix##_list_node_t* prefix##_list_node_alloc(n2_state_t* state, const type* val) \
	{ \
		prefix##_list_node_t* node = N2_TMALLOC(prefix##_list_node_t, state); \
		node->entry_.prev_ = node->entry_.next_ = NULL; \
		if (!val) { N2_MEMCPY(&node->value_, val, sizeof(type)); } \
		return node; \
	} \
	extn prefix##_list_node_t* prefix##_list_node_allocv(n2_state_t* state, const type val) \
	{ \
		return prefix##_list_node_alloc(state, &val); \
	} \
	extn void prefix##_list_node_free(n2_state_t* state, prefix##_list_node_t* node) \
	{ \
		N2_ASSERT(n2_list_node_islinked(N2_RCAST(n2_list_node_t*, node)) == N2_FALSE); \
		freefunc(state, node); \
		n2_free(state, node); \
	} \
	\
	extn prefix##_list_t* prefix##_list_alloc(n2_state_t* state) { return n2_list_alloc(state); } \
	extn void prefix##_list_free(n2_state_t* state, prefix##_list_t* list) \
	{ \
		prefix##_list_clear(state, list); \
		n2_list_free(state, list); \
	} \
	extn void prefix##_list_clear(n2_state_t* state, prefix##_list_t* list) \
	{ \
		N2_LIST_FOREACH_INLINE( \
			list, \
			freefunc(state, N2_RCAST(prefix##_list_node_t*, node)); \
		); \
		n2_list_clear(state, list); \
	} \
	extn void prefix##_list_prepend(prefix##_list_t* list, prefix##_list_node_t* node) { n2_list_prepend(list, N2_RCAST(n2_list_node_t*, node)); } \
	extn void prefix##_list_append(prefix##_list_t* list, prefix##_list_node_t* node) { n2_list_append(list, N2_RCAST(n2_list_node_t*, node)); } \
	extn int prefix##_list_erase(prefix##_list_t* list, prefix##_list_node_t* node) { return n2_list_erase(list, N2_RCAST(n2_list_node_t*, node)); } \
	extn prefix##_list_node_t* prefix##_list_find(prefix##_list_t* list, const void* key, prefix##_list_node_compre_func_t cmp) \
	{ \
		N2_ASSERT(list != NULL); \
		N2_ASSERT(cmp != NULL); \
		N2_LIST_FOREACH_INLINE( \
			list, \
			if (cmp(&N2_RCAST(prefix##_list_node_t*, node)->value_, key) == 0) { return N2_RCAST(prefix##_list_node_t*, node); } \
		); \
		return NULL; \
	}

//=============================================================================
// 配列ユーティリティ
typedef struct n2_array_t n2_array_t;

typedef void(*n2_array_element_free_func)(n2_state_t* state, n2_array_t* a, void* element);
typedef int(*n2_array_element_cmp_func)(const n2_array_t* a, const void* lelement, const void* relement, const void* key);
typedef int(*n2_array_element_match_func)(const n2_array_t* a, const void* element, const void* key);

struct n2_array_t
{
	size_t element_size_;
	void* elements_;
	size_t size_;
	size_t buffer_size_;
	size_t expand_step_;
	n2_array_element_free_func freefunc_;
	void* user_;
};

N2_API void n2_array_setup(n2_state_t* state, n2_array_t* a, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc);
N2_API void n2_array_teardown(n2_state_t* state, n2_array_t* a);
N2_API n2_array_t* n2_array_alloc(n2_state_t* state, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc);
N2_API void n2_array_free(n2_state_t* state, n2_array_t* a);
N2_API void n2_array_clear_free(n2_state_t* state, n2_array_t* a, n2_array_element_free_func freefunc);
N2_API void n2_array_clear(n2_state_t* state, n2_array_t* a);
N2_API void n2_array_reserve(n2_state_t* state, n2_array_t* a, size_t size);
N2_API n2_bool_t n2_array_resize(n2_state_t* state, n2_array_t* a, size_t size, const void* fill_element);
N2_API size_t n2_array_size(const n2_array_t* a);
N2_API size_t n2_array_buffer_size(const n2_array_t* a);

N2_API int n2_array_compute_index(const n2_array_t* a, const void* element);
N2_API void* n2_array_peek(n2_array_t* a, int index);
N2_API const void* n2_array_peekc(const n2_array_t* a, int index);
N2_API void* n2_array_insert(n2_state_t* state, n2_array_t* a, int index, const void* element);
N2_API int n2_array_find(const n2_array_t* a, n2_array_element_match_func match, const void* key);
N2_API void* n2_array_findp(n2_array_t* a, n2_array_element_match_func match, const void* key);
N2_API const void* n2_array_findcp(const n2_array_t* a, n2_array_element_match_func match, const void* key);
N2_API n2_bool_t n2_array_erase(n2_state_t* state, n2_array_t* a, int index);
N2_API size_t n2_array_erase_num(n2_state_t* state, n2_array_t* a, int index, size_t num);
N2_API void* n2_array_replace(n2_state_t* state, n2_array_t* a, int index, const void* element);
N2_API void n2_array_sort(n2_array_t* a, n2_array_element_cmp_func cmp, const void* key);

N2_API void* n2_array_push(n2_state_t* state, n2_array_t* a, const void* element);
N2_API size_t n2_array_pop(n2_state_t* state, n2_array_t* a, size_t num);

N2_API void* n2_array_enqueue(n2_state_t* state, n2_array_t* a, const void* element);
N2_API size_t n2_array_dequeue(n2_state_t* state, n2_array_t* a, size_t num);

#define N2_ARRAY_FOREACH_INLINE(type, a, ...) \
	do { \
		for (size_t ae_i = 0; ae_i < (a)->size_; ++ae_i) \
		{ \
			type* element = N2_RCAST(type*, n2_ptr_offset((a)->elements_, (a)->element_size_ * ae_i)); \
			__VA_ARGS__; \
		} \
	} while (0)

// ソート済み
typedef struct n2_sorted_array_t n2_sorted_array_t;

typedef int(*n2_sorted_array_element_cmp_func)(const n2_sorted_array_t* a, const void* lelement, const void* relement, const void* key);
typedef int(*n2_sorted_array_element_match_func)(const n2_sorted_array_t* a, const void* element, const void* key);

struct n2_sorted_array_t
{
	n2_array_t a_;
	n2_sorted_array_element_cmp_func cmp_;
	const void* cmp_key_;
	n2_sorted_array_element_match_func match_;
	const void* match_key_;
};

N2_API void n2_sorted_array_setup(n2_state_t* state, n2_sorted_array_t* a, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc);
N2_API void n2_sorted_array_teardown(n2_state_t* state, n2_sorted_array_t* a);

N2_API n2_sorted_array_t* n2_sorted_array_alloc(n2_state_t* state, size_t element_size, size_t initial_buffer_size, size_t expand_step, n2_array_element_free_func freefunc);
N2_API void n2_sorted_array_free(n2_state_t* state, n2_sorted_array_t* a);
N2_API void n2_sorted_array_clear(n2_state_t* state, n2_sorted_array_t* a);
N2_API void n2_sorted_array_reserve(n2_state_t* state, n2_sorted_array_t* a, size_t size);
N2_API size_t n2_sorted_array_size(const n2_sorted_array_t* a);

N2_API int n2_sorted_array_compute_index(const n2_sorted_array_t* a, const void* element);
N2_API void* n2_sorted_array_peek(n2_sorted_array_t* a, int index);
N2_API const void* n2_sorted_array_peekc(const n2_sorted_array_t* a, int index);

N2_API void* n2_sorted_array_find_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key);
N2_API void* n2_sorted_array_lowerbound_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key);
N2_API void* n2_sorted_array_upperbound_match(n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key, n2_bool_t allow_outrange);
N2_API void* n2_sorted_array_insert_cmp(n2_state_t* state, n2_sorted_array_t* a, const void* element, n2_sorted_array_element_cmp_func cmp, const void* key);
N2_API size_t n2_sorted_array_erase_match(n2_state_t* state, n2_sorted_array_t* a, n2_sorted_array_element_match_func match, const void* key);
N2_API n2_bool_t n2_sorted_array_erase_at(n2_state_t* state, n2_sorted_array_t* a, int index);

N2_API void* n2_sorted_array_find(n2_sorted_array_t* a, const void* key);
N2_API void* n2_sorted_array_lowerbound(n2_sorted_array_t* a, const void* key);
N2_API void* n2_sorted_array_upperbound(n2_sorted_array_t* a, const void* key, n2_bool_t allow_outrange);
N2_API void* n2_sorted_array_insert(n2_state_t* state, n2_sorted_array_t* a, const void* element, const void* key);
N2_API size_t n2_sorted_array_erase(n2_state_t* state, n2_sorted_array_t* a, const void* key);

#define N2_TSORTED_ARRAY_FOREACH_INLINE(type, a, ...) \
	N2_ARRAY_FOREACH_INLINE(type, (&a->a_), __VA_ARGS__)

// 型付き
#define N2_DECLARE_TARRAY(type, prefix, extn) \
	typedef n2_array_t prefix##_t; \
	extn void prefix##_setup(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step); \
	extn void prefix##_setup_user(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step, void* user); \
	extn void prefix##_teardown(n2_state_t* state, prefix##_t* a); \
	extn prefix##_t* prefix##_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step); \
	extn prefix##_t* prefix##_alloc_user(n2_state_t* state, size_t initial_buffer_size, size_t expand_step, void* user); \
	extn void prefix##_free(n2_state_t* state, prefix##_t* a); \
	extn void prefix##_clear(n2_state_t* state, prefix##_t* a); \
	extn void prefix##_reserve(n2_state_t* state, prefix##_t* a, size_t size); \
	extn n2_bool_t prefix##_resize(n2_state_t* state, prefix##_t* a, size_t size, const type* element); \
	extn n2_bool_t prefix##_resizev(n2_state_t* state, prefix##_t* a, size_t size, const type element); \
	extn size_t prefix##_size(const prefix##_t* a); \
	extn int prefix##_compute_index(const prefix##_t* a, const void* element); \
	extn type* prefix##_peek(prefix##_t* a, int index); \
	extn const type* prefix##_peekc(const prefix##_t* a, int index); \
	extn type prefix##_peekv(prefix##_t* a, int index, type d); \
	extn const type prefix##_peekcv(const prefix##_t* a, int index, const type d); \
	extn type* prefix##_insert(n2_state_t* state, prefix##_t* a, int index, const type* element); \
	extn type* prefix##_insertv(n2_state_t* state, prefix##_t* a, int index, const type element); \
	extn int prefix##_find(const prefix##_t* a, n2_array_element_match_func match, const void* key); \
	extn type* prefix##_findp(prefix##_t* a, n2_array_element_match_func match, const void* key); \
	extn const type* prefix##_findcp(const prefix##_t* a, n2_array_element_match_func match, const void* key); \
	extn n2_bool_t prefix##_erase(n2_state_t* state, prefix##_t* a, int index); \
	extn size_t prefix##_erase_num(n2_state_t* state, prefix##_t* a, int index, size_t num); \
	extn type* prefix##_replace(n2_state_t* state, prefix##_t* a, int index, const type* element); \
	extn void prefix##_sort(prefix##_t* a, n2_array_element_cmp_func cmp, const void* key); \
	extn type* prefix##_push(n2_state_t* state, prefix##_t* a, const type* element); \
	extn type* prefix##_pushv(n2_state_t* state, prefix##_t* a, const type element); \
	extn size_t prefix##_pop(n2_state_t* state, prefix##_t* a, size_t num); \
	extn type* prefix##_enqueue(n2_state_t* state, prefix##_t* a, const type* element); \
	extn type* prefix##_enqueuev(n2_state_t* state, prefix##_t* a, const type element); \
	extn size_t prefix##_dequeue(n2_state_t* state, prefix##_t* a, size_t num);

#define N2_DEFINE_TARRAY(type, prefix, extn, setupfunc, freefunc) \
	extn void prefix##_setup(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step) \
	{ \
		n2_array_setup(state, a, sizeof(type), initial_buffer_size, expand_step, freefunc); \
		if (setupfunc) { setupfunc(state, a); } \
	} \
	extn void prefix##_setup_user(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step, void* user) \
	{ \
		prefix##_setup(state, a, initial_buffer_size, expand_step); \
		a->user_ = user; \
	} \
	extn void prefix##_teardown(n2_state_t* state, prefix##_t* a) \
	{ \
		n2_array_teardown(state, a); \
	} \
	extn prefix##_t* prefix##_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step) \
	{ \
		prefix##_t* a = n2_array_alloc(state, sizeof(type), initial_buffer_size, expand_step, freefunc); \
		if (!a) { return a; } \
		if (setupfunc) { setupfunc(state, a); } \
		return a; \
	} \
	extn prefix##_t* prefix##_alloc_user(n2_state_t* state, size_t initial_buffer_size, size_t expand_step, void* user) \
	{ \
		prefix##_t* a = prefix##_alloc(state, initial_buffer_size, expand_step); \
		if (!a) { return a; } \
		a->user_ = user; \
		return a; \
	} \
	extn void prefix##_free(n2_state_t* state, prefix##_t* a) \
	{ \
		n2_array_free(state, a); \
	} \
	extn void prefix##_clear(n2_state_t* state, prefix##_t* a)\
	{ \
		n2_array_clear(state, a); \
	} \
	extn void prefix##_reserve(n2_state_t* state, prefix##_t* a, size_t size) \
	{ \
		n2_array_reserve(state, a, size); \
	} \
	extn n2_bool_t prefix##_resize(n2_state_t* state, prefix##_t* a, size_t size, const type* element) \
	{ \
		return n2_array_resize(state, a, size, element); \
	} \
	extn n2_bool_t prefix##_resizev(n2_state_t* state, prefix##_t* a, size_t size, const type element) \
	{ \
		return n2_array_resize(state, a, size, &element); \
	} \
	extn size_t prefix##_size(const prefix##_t* a) \
	{ \
		return n2_array_size(a); \
	} \
	extn int prefix##_compute_index(const prefix##_t* a, const void* element) \
	{ \
		return n2_array_compute_index(N2_RCAST(const n2_array_t*, a), element); \
	} \
	extn type* prefix##_peek(prefix##_t* a, int index) \
	{ \
		return N2_RCAST(type*, n2_array_peek(a, index)); \
	} \
	extn const type* prefix##_peekc(const prefix##_t* a, int index) \
	{ \
		return N2_RCAST(const type*, n2_array_peekc(a, index)); \
	} \
	extn type prefix##_peekv(prefix##_t* a, int index, type d) \
	{ \
		type* vptr = prefix##_peek(a, index); \
		return vptr ? *vptr : d; \
	} \
	extn const type prefix##_peekcv(const prefix##_t* a, int index, const type d) \
	{ \
		const type* vptr = N2_RCAST(const type*, n2_array_peekc(a, index)); \
		return vptr ? *vptr : d; \
	} \
	extn type* prefix##_insert(n2_state_t* state, prefix##_t* a, int index, const type* element) \
	{ \
		return N2_RCAST(type*, n2_array_insert(state, a, index, element)); \
	} \
	extn type* prefix##_insertv(n2_state_t* state, prefix##_t* a, int index, const type element) \
	{ \
		return prefix##_insert(state, a, index, &element); \
	} \
	extn int prefix##_find(const prefix##_t* a, n2_array_element_match_func match, const void* key) \
	{ \
		return n2_array_find(a, match, key); \
	} \
	extn type* prefix##_findp(prefix##_t* a, n2_array_element_match_func match, const void* key) \
	{ \
		return N2_RCAST(type*, n2_array_findp(a, match, key)); \
	} \
	extn const type* prefix##_findcp(const prefix##_t* a, n2_array_element_match_func match, const void* key) \
	{ \
		return N2_RCAST(const type*, n2_array_findcp(a, match, key)); \
	} \
	extn n2_bool_t prefix##_erase(n2_state_t* state, prefix##_t* a, int index) \
	{ \
		return n2_array_erase(state, a, index); \
	} \
	extn size_t prefix##_erase_num(n2_state_t* state, prefix##_t* a, int index, size_t num) \
	{ \
		return n2_array_erase_num(state, a, index, num); \
	} \
	extn type* prefix##_replace(n2_state_t* state, prefix##_t* a, int index, const type* element) \
	{ \
		return N2_RCAST(type*, n2_array_replace(state, a, index, element)); \
	} \
	extn void prefix##_sort(prefix##_t* a, n2_array_element_cmp_func cmp, const void* key) \
	{ \
		n2_array_sort(a, cmp, key); \
	} \
	extn type* prefix##_push(n2_state_t* state, prefix##_t* a, const type* element) \
	{ \
		return N2_RCAST(type*, n2_array_push(state, a, element)); \
	} \
	extn type* prefix##_pushv(n2_state_t* state, prefix##_t* a, const type element) \
	{ \
		return prefix##_push(state, a, &element); \
	} \
	extn size_t prefix##_pop(n2_state_t* state, prefix##_t* a, size_t num) \
	{ \
		return n2_array_pop(state, a, num); \
	} \
	extn type* prefix##_enqueue(n2_state_t* state, prefix##_t* a, const type* element) \
	{ \
		return N2_RCAST(type*, n2_array_enqueue(state, a, element)); \
	} \
	extn type* prefix##_enqueuev(n2_state_t* state, prefix##_t* a, const type element) \
	{ \
		return prefix##_enqueue(state, a, &element); \
	} \
	extn size_t prefix##_dequeue(n2_state_t* state, prefix##_t* a, size_t num) \
	{ \
		return n2_array_dequeue(state, a, num); \
	}

#define N2_DECLARE_TSORTED_ARRAY(type, cmpkeytype, matchkeytype, prefix, extn) \
	typedef n2_sorted_array_t prefix##_t; \
	extn void prefix##_setup(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step); \
	extn void prefix##_setup_user(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step, void* user); \
	extn void prefix##_teardown(n2_state_t* state, prefix##_t* a); \
	extn prefix##_t* prefix##_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step); \
	extn prefix##_t* prefix##_alloc_user(n2_state_t* state, size_t initial_buffer_size, size_t expand_step, void* user); \
	extn void prefix##_free(n2_state_t* state, prefix##_t* a); \
	extn void prefix##_clear(n2_state_t* state, prefix##_t* a); \
	extn void prefix##_reserve(n2_state_t* state, prefix##_t* a, size_t size); \
	extn size_t prefix##_size(const prefix##_t* a); \
	extn int prefix##_compute_index(const prefix##_t* a, const void* element); \
	extn type* prefix##_peek(prefix##_t* a, int index); \
	extn const type* prefix##_peekc(const prefix##_t* a, int index); \
	extn type* prefix##_find_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key); \
	extn type* prefix##_lowerbound_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key); \
	extn type* prefix##_upperbound_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key, n2_bool_t allow_outrange); \
	extn type* prefix##_insert_cmp(n2_state_t* state, prefix##_t* a, const type* element, n2_sorted_array_element_cmp_func cmp, const cmpkeytype* key); \
	extn size_t prefix##_erase_match(n2_state_t* state, prefix##_t* a, n2_sorted_array_element_match_func match, const void* key); \
	extn n2_bool_t prefix##_erase_at(n2_state_t* state, prefix##_t* a, int index); \
	extn type* prefix##_find(prefix##_t* a, const matchkeytype* key); \
	extn type* prefix##_lowerbound(prefix##_t* a, const matchkeytype* key); \
	extn type* prefix##_upperbound(prefix##_t* a, const matchkeytype* key, n2_bool_t allow_outrange); \
	extn type* prefix##_insert(n2_state_t* state, prefix##_t* a, const type* element, const cmpkeytype* key); \
	extn type* prefix##_insertv(n2_state_t* state, prefix##_t* a, const type element, const cmpkeytype* key); \
	extn size_t prefix##_erase(n2_state_t* state, prefix##_t* a, const matchkeytype* key);

#define N2_DEFINE_TSORTED_ARRAY(type, cmpkeytype, matchkeytype, prefix, extn, setupfunc, freefunc) \
	extn void prefix##_setup(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step) \
	{ \
		n2_sorted_array_setup(state, a, sizeof(type), initial_buffer_size, expand_step, freefunc); \
		if (setupfunc) { setupfunc(state, a); } \
	} \
	extn void prefix##_setup_user(n2_state_t* state, prefix##_t* a, size_t initial_buffer_size, size_t expand_step, void* user) \
	{ \
		prefix##_setup(state, a, initial_buffer_size, expand_step); \
		a->a_.user_ = user; \
	} \
	extn void prefix##_teardown(n2_state_t* state, prefix##_t* a) \
	{ \
		n2_sorted_array_teardown(state, a); \
	} \
	extn prefix##_t* prefix##_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step) \
	{ \
		prefix##_t* a = n2_sorted_array_alloc(state, sizeof(type), initial_buffer_size, expand_step, freefunc); \
		if (!a) { return a; } \
		if (setupfunc) { setupfunc(state, a); } \
		return a; \
	} \
	extn prefix##_t* prefix##_alloc_user(n2_state_t* state, size_t initial_buffer_size, size_t expand_step, void* user) \
	{ \
		prefix##_t* a = prefix##_alloc(state, initial_buffer_size, expand_step); \
		if (!a) { return a; } \
		a->a_.user_ = user; \
		return a; \
	} \
	extn void prefix##_free(n2_state_t* state, prefix##_t* a) \
	{ \
		n2_sorted_array_free(state, a); \
	} \
	extn void prefix##_clear(n2_state_t* state, prefix##_t* a) \
	{ \
		n2_sorted_array_clear(state, a); \
	} \
	extn void prefix##_reserve(n2_state_t* state, prefix##_t* a, size_t size) \
	{ \
		n2_sorted_array_reserve(state, a, size); \
	} \
	extn size_t prefix##_size(const prefix##_t* a) \
	{ \
		return n2_sorted_array_size(a); \
	} \
	extn int prefix##_compute_index(const prefix##_t* a, const void* element) \
	{ \
		return n2_sorted_array_compute_index(a, element); \
	} \
	extn type* prefix##_peek(prefix##_t* a, int index) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_peek(a, index)); \
	} \
	extn const type* prefix##_peekc(const prefix##_t* a, int index) \
	{ \
		return N2_RCAST(const type*, n2_sorted_array_peekc(a, index)); \
	} \
	extn type* prefix##_find_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_find_match(a, match, key)); \
	} \
	extn type* prefix##_lowerbound_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_lowerbound_match(a, match, key)); \
	} \
	extn type* prefix##_upperbound_match(prefix##_t* a, n2_sorted_array_element_match_func match, const matchkeytype* key, n2_bool_t allow_outrange) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_upperbound_match(a, match, key, allow_outrange)); \
	} \
	extn type* prefix##_insert_cmp(n2_state_t* state, prefix##_t* a, const type* element, n2_sorted_array_element_cmp_func cmp, const cmpkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_insert_cmp(state, a, element, cmp, key)); \
	} \
	extn size_t prefix##_erase_match(n2_state_t* state, prefix##_t* a, n2_sorted_array_element_match_func match, const void* key) \
	{ \
		return n2_sorted_array_erase_match(state, a, match, key); \
	} \
	extn n2_bool_t prefix##_erase_at(n2_state_t* state, prefix##_t* a, int index) \
	{ \
		return n2_sorted_array_erase_at(state, a, index); \
	} \
	extn type* prefix##_find(prefix##_t* a, const matchkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_find(a, key)); \
	} \
	extn type* prefix##_lowerbound(prefix##_t* a, const matchkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_lowerbound(a, key)); \
	} \
	extn type* prefix##_upperbound(prefix##_t* a, const matchkeytype* key, n2_bool_t allow_outrange) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_upperbound(a, key, allow_outrange)); \
	} \
	extn type* prefix##_insert(n2_state_t* state, prefix##_t* a, const type* element, const cmpkeytype* key) \
	{ \
		return N2_RCAST(type*, n2_sorted_array_insert(state, a, element, key)); \
	} \
	extn type* prefix##_insertv(n2_state_t* state, prefix##_t* a, const type element, const cmpkeytype* key) \
	{ \
		return prefix##_insert(state, a, &element, key); \
	} \
	extn size_t prefix##_erase(n2_state_t* state, prefix##_t* a, const matchkeytype* key) \
	{ \
		return n2_sorted_array_erase(state, a, key); \
	}

N2_DECLARE_TARRAY(int, n2_intarray, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, int, n2_intset, N2_API);
N2_DECLARE_TARRAY(uint8_t, n2_u8array, N2_API);
N2_DECLARE_TARRAY(uint16_t, n2_u16array, N2_API);
N2_DECLARE_TARRAY(uint32_t, n2_u32array, N2_API);
N2_DECLARE_TARRAY(size_t, n2_szarray, N2_API);
N2_DECLARE_TARRAY(char*, n2_plstrarray, N2_API);
N2_DECLARE_TARRAY(char*, n2_cstrarray, N2_API);
N2_DECLARE_TSORTED_ARRAY(char*, void, char, n2_plstrset, N2_API);
N2_DECLARE_TSORTED_ARRAY(void*, void, void*, n2_ptrset, N2_API);

//=============================================================================
// ファイルユーティリティ
typedef struct n2_fileread_param_t n2_fileread_param_t;
struct n2_fileread_param_t
{
	n2_state_t* state_;
	const char* filepath_;
	n2_bool_t binary_;
	size_t readsize_;
	size_t readoffset_;
	n2_buffer_t* dst_;
};

typedef struct n2_filewrite_param_t n2_filewrite_param_t;
struct n2_filewrite_param_t
{
	n2_state_t* state_;
	const char* filepath_;
	n2_bool_t binary_;
	const void* writedata_;
	size_t writesize_;
	size_t writeoffset_;/*SIZE_MAX for replace file content, otherwise add data*/
	size_t* dst_writtensize_;
};

typedef n2_bool_t (*n2_fileread_func_t)(void* file_user, const n2_fileread_param_t* param);
typedef n2_bool_t (*n2_filewrite_func_t)(void* file_user, const n2_filewrite_param_t* param);

//=============================================================================
// ベクトル
typedef union n2_fvec2_t n2_fvec2_t;
union n2_fvec2_t
{
	struct { float x_, y_; };
	float e_[2];
};

N2_API n2_fvec2_t n2_fvec2(float x, float y);
N2_API n2_fvec2_t n2_fvec2_add(const n2_fvec2_t lhs, const n2_fvec2_t rhs);
N2_API n2_fvec2_t n2_fvec2_sub(const n2_fvec2_t lhs, const n2_fvec2_t rhs);
N2_API n2_fvec2_t n2_fvec2_mul(const n2_fvec2_t lhs, const n2_fvec2_t rhs);
N2_API n2_fvec2_t n2_fvec2_scale(const n2_fvec2_t lhs, float s);
N2_API float n2_fvec2_cross(const n2_fvec2_t lhs, const n2_fvec2_t rhs);
N2_API float n2_fvec2_normalize_to(n2_fvec2_t* lhs);
N2_API n2_fvec2_t n2_fvec2_min(const n2_fvec2_t lhs, const n2_fvec2_t rhs);
N2_API n2_fvec2_t n2_fvec2_max(const n2_fvec2_t lhs, const n2_fvec2_t rhs);

typedef union n2_fvec3_t n2_fvec3_t;
union n2_fvec3_t
{
	struct { float x_, y_, z_; };
	struct { float r_, g_, b_; };
	n2_fvec2_t xy_;
	n2_fvec2_t rg_;
	float e_[3];
};

N2_API n2_fvec3_t n2_fvec3(float x, float y, float z);
N2_API n2_fvec3_t n2_fvec3_add(const n2_fvec3_t lhs, const n2_fvec3_t rhs);
N2_API n2_fvec3_t n2_fvec3_sub(const n2_fvec3_t lhs, const n2_fvec3_t rhs);
N2_API n2_fvec3_t n2_fvec3_scale(const n2_fvec3_t lhs, float s);
N2_API float n2_fvec3_normalize_to(n2_fvec3_t* lhs);

typedef union n2_fvec4_t n2_fvec4_t;
union n2_fvec4_t
{
	struct { float x_, y_, z_, w_; };
	struct { float r_, g_, b_, a_; };
	struct { n2_fvec2_t xy_, zw_; };
	n2_fvec3_t xyz_;
	n2_fvec3_t rgb_;
	float e_[4];
};

N2_API n2_fvec4_t n2_fvec4(float x, float y, float z, float w);
N2_API n2_fvec4_t n2_fvec4_add(const n2_fvec4_t lhs, const n2_fvec4_t rhs);
N2_API n2_fvec4_t n2_fvec4_sub(const n2_fvec4_t lhs, const n2_fvec4_t rhs);
N2_API n2_fvec4_t n2_fvec4_scale(const n2_fvec4_t lhs, float s);

typedef union n2_fmat4_t n2_fmat4_t;
union n2_fmat4_t
{
	struct { n2_fvec4_t x_, y_, z_, w_; };
	n2_fvec4_t col_[4];
	float m_[4][4];
	float e_[16];
};

N2_API void n2_fmat4_zero_to(n2_fmat4_t* to);
N2_API void n2_fmat4_identity_to(n2_fmat4_t* to);
N2_API n2_fmat4_t n2_fmat4_identity();
N2_API void n2_fmat4_copy_to(n2_fmat4_t* to, const n2_fmat4_t* from);
N2_API void n2_fmat4_ortho2d_to(n2_fmat4_t* to, float left, float right, float top, float bottom, float z_near, float z_far);
N2_API void n2_fmat4_ortho3d_to(n2_fmat4_t* to, float left, float right, float bottom, float top, float z_near, float z_far);
N2_API void n2_fmat4_perspective_to(n2_fmat4_t* to, float fovy, float aspect, float z_near, float z_far);

//=============================================================================
// 内部ヘルパー

// rpmalloc
#if N2_CONFIG_USE_RPMALLOC_LIB
N2_API void n2h_rpmalloc_init();
N2_API void n2h_rpmalloc_teardown();
N2_API int n2h_rpmalloc_initialized_count();

N2_API void* n2h_rpmalloc_alloc(size_t size);
N2_API void* n2h_rpmalloc_realloc(size_t size, void* old_ptr);
N2_API void n2h_rpmalloc_free(void* ptr);
#endif

// 動的ライブラリ
#define N2H_DYNLIB_ARG_MAX	(17)

typedef struct n2h_dynlib_t n2h_dynlib_t;
struct n2h_dynlib_t
{
	n2_str_t path_;
	void* native_handle_;
	void* native_data_;
};

N2_API n2_bool_t n2h_dynlib_supported_platform(int platform);
N2_API n2_bool_t n2h_dynlib_supported();

N2_API n2h_dynlib_t* n2h_dynlib_alloc(n2_state_t* state, const char* path, size_t path_length);
N2_API void n2h_dynlib_free(n2_state_t* state, n2h_dynlib_t* dynlib);
N2_API void* n2h_dynlib_find_function(n2_state_t* state, n2h_dynlib_t* dynlib, const char* name);

typedef intptr_t n2h_dynlib_arg_t;
typedef intptr_t n2h_dynlib_result_t;
N2_API n2_bool_t n2h_dynlib_call_single(n2_state_t* state, n2h_dynlib_t* dynlib, void* proc, n2h_dynlib_result_t* dst, const n2h_dynlib_arg_t* args, size_t arg_num);

// crc32
N2_API uint32_t n2h_crc32(const void* src, size_t src_size);

#if N2_CONFIG_USE_MD5_LIB
// md5
typedef struct n2_md5_digest_t n2_md5_digest_t;
struct n2_md5_digest_t
{
	uint8_t digest_[16];
};
N2_API void n2h_md5(n2_md5_digest_t* dst, const void* src, size_t src_size);
#endif

// base85
N2_API void n2h_base85_encode_to(n2_state_t* state, n2_str_t* dst, const void* src, size_t src_size);
N2_API n2_bool_t n2h_base85_decode_to(n2_state_t* state, n2_buffer_t* dst, const char* src, size_t src_size);

// easing
N2_API double n2h_easing_linear(double v);
N2_API double n2h_easing_quadratic_in(double v);
N2_API double n2h_easing_quadratic_out(double v);
N2_API double n2h_easing_quadratic_inout(double v);
N2_API double n2h_easing_cubic_in(double v);
N2_API double n2h_easing_cubic_out(double v);
N2_API double n2h_easing_cubic_inout(double v);
N2_API double n2h_easing_quartic_in(double v);
N2_API double n2h_easing_quartic_out(double v);
N2_API double n2h_easing_quartic_inout(double v);
N2_API double n2h_easing_quintic_in(double v);
N2_API double n2h_easing_quintic_out(double v);
N2_API double n2h_easing_quintic_inout(double v);
N2_API double n2h_easing_sine_in(double v);
N2_API double n2h_easing_sine_out(double v);
N2_API double n2h_easing_sine_inout(double v);
N2_API double n2h_easing_circular_in(double v);
N2_API double n2h_easing_circular_out(double v);
N2_API double n2h_easing_circular_inout(double v);
N2_API double n2h_easing_exponential_in(double v);
N2_API double n2h_easing_exponential_out(double v);
N2_API double n2h_easing_exponential_inout(double v);
N2_API double n2h_easing_elastic_in(double v);
N2_API double n2h_easing_elastic_out(double v);
N2_API double n2h_easing_elastic_inout(double v);
N2_API double n2h_easing_back_in(double v);
N2_API double n2h_easing_back_out(double v);
N2_API double n2h_easing_back_inout(double v);
N2_API double n2h_easing_bounce_out(double v);
N2_API double n2h_easing_bounce_in(double v);
N2_API double n2h_easing_bounce_inout(double v);

// ランダム
typedef struct n2h_random_t n2h_random_t;
struct n2h_random_t
{
	uint64_t state_[2];
};

N2_API void n2h_random_init(n2h_random_t* rd, uint64_t s);
N2_API uint64_t n2h_random_next(n2h_random_t* rd);
N2_API uint64_t n2h_random_next_range(n2h_random_t* rd, uint64_t range);// [0, range)
N2_API double n2h_random_next_float(n2h_random_t* rd);// [0, 1)
N2_API void n2h_random_scratch(void* data, size_t data_size, uint64_t seed);

// バイナリシーケンス
N2_DECLARE_ENUM(n2h_binseq_flag_e);
enum n2h_binseq_flag_e
{
	N2H_BINSEQ_FLAG_SCRATCHED = 1ULL << 0,
};

typedef struct n2h_binseq_header_t n2h_binseq_header_t;
struct n2h_binseq_header_t
{
	uint64_t size_;
	uint64_t flags_;
	uint64_t scratch_key_;
	uint32_t check_;
};

N2_API size_t n2h_binseq_signature_size();

N2_API const uint8_t* n2h_binseq_magic(size_t* dst_size);

N2_API n2_bool_t n2h_binseq_verify(const void* src, size_t src_size);
N2_API n2_bool_t n2h_binseq_get_header(n2h_binseq_header_t* dst, const void* src, size_t src_size);

N2_API size_t n2h_binseq_write_signature(void* dst, const n2h_binseq_header_t* header);

// イメージ
N2_DECLARE_ENUM(n2_image_file_e);
enum n2_image_file_e
{
	N2_IMAGE_FILE_BMP = 0,
	N2_IMAGE_FILE_JPG,
	N2_IMAGE_FILE_PNG,
	N2_IMAGE_FILE_TGA,

	N2_MAX_IMAGE_FILE
};

#if N2_CONFIG_USE_IMAGE_READ_LIB
N2_API n2_bool_t n2h_image_read(n2_state_t* state, n2_buffer_t* dst, size_t* dst_width, size_t* dst_height, const void* src, size_t src_size);
#endif

#if N2_CONFIG_USE_IMAGE_WRITE_LIB
N2_API n2_bool_t n2h_image_write(n2_state_t* state, n2_buffer_t* dst, n2_image_file_e image_file, const void* src, size_t src_size, size_t width, size_t height, int quality);
#endif

// 暗号化
#if N2_CONFIG_USE_AES_LIB
N2_API size_t n2h_aes_blocksize();
N2_API size_t n2h_aes_keysize();
N2_API size_t n2h_aes_ivsize();
N2_API n2_bool_t n2h_aes_encrypt(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, const uint8_t* key, size_t keysize, const uint8_t* iv, size_t ivsize);
N2_API n2_bool_t n2h_aes_decrypt(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, const uint8_t* key, size_t keysize, const uint8_t* iv, size_t ivsize);
#endif

// MessagePack
#if N2_CONFIG_USE_MSGPACK_LIB

N2_DECLARE_ENUM(n2h_msgpack_type_e);
enum n2h_msgpack_type_e
{
	N2H_MSGPACK_TYPE_UNKNOWN = -1,
	N2H_MSGPACK_TYPE_NIL = 0,
	N2H_MSGPACK_TYPE_BOOL,
	N2H_MSGPACK_TYPE_UINT,
	N2H_MSGPACK_TYPE_INT,
	N2H_MSGPACK_TYPE_FLOAT,
	N2H_MSGPACK_TYPE_DOUBLE,
	N2H_MSGPACK_TYPE_STRING,
	N2H_MSGPACK_TYPE_BINARY,
	N2H_MSGPACK_TYPE_ARRAY,
	N2H_MSGPACK_TYPE_MAP,
	N2H_MSGPACK_TYPE_TIMESTAMP,
	N2H_MSGPACK_TYPE_EXTENSION,

	N2H_MSGPACK_MAX_TYPE
};

typedef struct n2h_msgpack_element_t n2h_msgpack_element_t;
typedef struct n2h_msgpack_element_pair_t n2h_msgpack_element_pair_t;

N2_DECLARE_TARRAY(n2h_msgpack_element_t, n2h_msgpack_elementarray, N2_API);
N2_DECLARE_TARRAY(n2h_msgpack_element_pair_t, n2h_msgpack_elementpairarray, N2_API);

typedef struct n2h_msgpack_value_string_t n2h_msgpack_value_string_t;
struct n2h_msgpack_value_string_t
{
	const char* str_;
	uint32_t length_;
};

typedef struct n2h_msgpack_value_binary_t n2h_msgpack_value_binary_t;
struct n2h_msgpack_value_binary_t
{
	const void* bin_;
	uint32_t length_;
};

typedef struct n2h_msgpack_value_array_t n2h_msgpack_value_array_t;
struct n2h_msgpack_value_array_t
{
	n2h_msgpack_elementarray_t* array_;
};

typedef struct n2h_msgpack_value_map_t n2h_msgpack_value_map_t;
struct n2h_msgpack_value_map_t
{
	n2h_msgpack_elementpairarray_t* pairarray_;
};

typedef struct n2h_msgpack_value_timestamp_t n2h_msgpack_value_timestamp_t;
struct n2h_msgpack_value_timestamp_t
{
	uint64_t seconds_;
	uint32_t nanoseconds_;
};

typedef struct n2h_msgpack_value_extension_t n2h_msgpack_value_extension_t;
struct n2h_msgpack_value_extension_t
{
	int8_t subtype_;
	const void* data_;
	uint32_t length_;
};

typedef union n2h_msgpack_content_t n2h_msgpack_content_t;
union n2h_msgpack_content_t
{
	n2_bool_t boolval_;
	uint64_t uintval_;
	int64_t intval_;
	float floatval_;
	double doubleval_;
	n2h_msgpack_value_string_t strval_;
	n2h_msgpack_value_binary_t binval_;
	n2h_msgpack_value_array_t arrayval_;
	n2h_msgpack_value_map_t mapval_;
	n2h_msgpack_value_timestamp_t tsval_;
	n2h_msgpack_value_extension_t extval_;
};

struct n2h_msgpack_element_t
{
	n2h_msgpack_type_e type_;
	n2h_msgpack_content_t content_;
};

struct n2h_msgpack_element_pair_t
{
	size_t original_order_;
	n2h_msgpack_element_t key_;
	n2h_msgpack_element_t value_;
};

N2_API int n2h_msgpack_element_cmp(const n2h_msgpack_element_t* lhs, const n2h_msgpack_element_t* rhs);
N2_API n2h_msgpack_element_t* n2h_msgpack_parse(n2_state_t* state, const void* msgpack, size_t msgpack_size);
N2_API void n2h_msgpack_free(n2_state_t* state, n2h_msgpack_element_t* element);
N2_API const n2h_msgpack_element_t* n2h_msgpack_at(const n2h_msgpack_element_t* ar, int index);
N2_API const n2h_msgpack_element_t* n2h_msgpack_find(const n2h_msgpack_element_t* map, const n2h_msgpack_element_t* key);
N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byuint_strict(const n2h_msgpack_element_t* map, uint64_t keyval);
N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byint_strict(const n2h_msgpack_element_t* map, int64_t keyval);
N2_API const n2h_msgpack_element_t* n2h_msgpack_find_byint(const n2h_msgpack_element_t* map, int64_t keyval);
N2_API const n2h_msgpack_element_t* n2h_msgpack_find_bystr(const n2h_msgpack_element_t* map, const char* name, size_t name_length);
N2_API n2_bool_t n2h_msgpack_get_asbool(n2_bool_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict);
N2_API n2_bool_t n2h_msgpack_get_asint(int64_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict);
N2_API n2_bool_t n2h_msgpack_get_asuint(uint64_t* dst, const n2h_msgpack_element_t* o, n2_bool_t strict);
N2_API n2_bool_t n2h_msgpack_get_asstr(n2_state_t* state, n2_str_t* dst, const n2h_msgpack_element_t* o);
#endif

// データツリー
N2_DECLARE_ENUM(n2h_datatree_e);
enum n2h_datatree_e
{
	N2H_DATATREE_NULL = 0,
	N2H_DATATREE_BOOL,
	N2H_DATATREE_INT,
	N2H_DATATREE_FLOAT,
	N2H_DATATREE_STRING,
	N2H_DATATREE_BINARY,
	N2H_DATATREE_ARRAY,
	N2H_DATATREE_MAP,

	N2H_MAX_DATATREE
};

typedef struct n2h_datatree_t n2h_datatree_t;

N2_API n2h_datatree_t* n2h_datatree_allocnull(n2_state_t* state);
N2_API n2h_datatree_t* n2h_datatree_allocb(n2_state_t* state, n2_bool_t v);
N2_API n2h_datatree_t* n2h_datatree_alloci(n2_state_t* state, int64_t v);
N2_API n2h_datatree_t* n2h_datatree_allocf(n2_state_t* state, double v);
N2_API n2h_datatree_t* n2h_datatree_allocstr(n2_state_t* state, const char* str, size_t str_size);
N2_API n2h_datatree_t* n2h_datatree_allocbin(n2_state_t* state, const void* bin, size_t bin_size);
N2_API n2h_datatree_t* n2h_datatree_allocarray(n2_state_t* state);
N2_API n2h_datatree_t* n2h_datatree_allocmap(n2_state_t* state);
N2_API void n2h_datatree_free(n2_state_t* state, n2h_datatree_t* tree);

N2_API n2h_datatree_e n2h_datatree_type(const n2h_datatree_t* datatree);
N2_API int n2h_datatree_cmp(const n2h_datatree_t* ltree, const n2h_datatree_t* rtree);
N2_API n2_bool_t n2h_datatree_asbool(const n2h_datatree_t* datatree, n2_bool_t orval);
N2_API int64_t n2h_datatree_asint(const n2h_datatree_t* datatree, int64_t orval);
N2_API double n2h_datatree_asfloat(const n2h_datatree_t* datatree, double orval);
N2_API n2_str_t* n2h_datatree_asstr(n2_state_t* state, const n2h_datatree_t* datatree, const char* orval);
N2_API const n2_str_t* n2h_datatree_peekstr(const n2h_datatree_t* datatree);
N2_API size_t n2h_datatree_arraysize(const n2h_datatree_t* datatree);
N2_API size_t n2h_datatree_mapsize(const n2h_datatree_t* datatree);
N2_API size_t n2h_datatree_size(const n2h_datatree_t* datatree);
N2_API const n2h_datatree_t* n2h_datatree_at(const n2h_datatree_t* datatree, int index);
N2_API const n2h_datatree_t* n2h_datatree_find(const n2h_datatree_t* datatree, const n2h_datatree_t* key);
N2_API const n2h_datatree_t* n2h_datatree_find_byint(const n2h_datatree_t* datatree, int64_t keyval);
N2_API const n2h_datatree_t* n2h_datatree_find_bystr(const n2h_datatree_t* datatree, const char* name);
N2_API const n2h_datatree_t* n2h_datatree_get_key(const n2h_datatree_t* datatree, int index);
N2_API const n2h_datatree_t* n2h_datatree_get_value(const n2h_datatree_t* datatree, int index);
N2_API n2_bool_t n2h_datatree_set_at(n2_state_t* state, n2h_datatree_t* datatree, int index, n2h_datatree_t* val);
N2_API n2_bool_t n2h_datatree_append(n2_state_t* state, n2h_datatree_t* datatree, n2h_datatree_t* val);
N2_API n2_bool_t n2h_datatree_set(n2_state_t* state, n2h_datatree_t* datatree, n2h_datatree_t* key, n2h_datatree_t* val);
N2_API n2_bool_t n2h_datatree_set_byint(n2_state_t* state, n2h_datatree_t* datatree, int64_t keyval, n2h_datatree_t* val);
N2_API n2_bool_t n2h_datatree_set_bystr(n2_state_t* state, n2h_datatree_t* datatree, const char* name, size_t name_size, n2h_datatree_t* val);
N2_API n2_bool_t n2h_datatree_erase_at(n2_state_t* state, n2h_datatree_t* datatree, int index);
N2_API n2_bool_t n2h_datatree_erase(n2_state_t* state, n2h_datatree_t* datatree, const n2h_datatree_t* key);
N2_API n2_bool_t n2h_datatree_erase_byint(n2_state_t* state, n2h_datatree_t* datatree, int64_t keyval);
N2_API n2_bool_t n2h_datatree_erase_bystr(n2_state_t* state, n2h_datatree_t* datatree, const char* name);

#if N2_CONFIG_USE_MSGPACK_LIB
N2_API n2h_datatree_t* n2h_datatree_read_from_msgpack(n2_state_t* state, const void* msgpack, size_t msgpack_size);
N2_API n2_bool_t n2h_datatree_write_as_msgpack_to(n2_state_t* state, n2_buffer_t* write_to, const n2h_datatree_t* tree);
#endif

#if N2_CONFIG_USE_JSON_LIB
N2_API n2h_datatree_t* n2h_datatree_read_from_json(n2_state_t* state, const char* json, size_t json_size);
N2_API n2_bool_t n2h_datatree_is_writable_as_json(const n2h_datatree_t* tree);
N2_API n2_bool_t n2h_datatree_write_as_json_to(n2_state_t* state, n2_str_t* write_to, const n2h_datatree_t* tree, n2_bool_t pretty);
#endif

// 圧縮
N2_DECLARE_ENUM(n2h_compress_e);
enum n2h_compress_e
{
	N2H_COMPRESS_NULL = 0,
	N2H_COMPRESS_Z,
	N2H_COMPRESS_ULZ,

	N2H_MAX_COMPRESS
};

N2_API const char* n2h_compress_name(n2h_compress_e compress, const char* on_failed);
N2_API n2h_compress_e n2h_compress_find(const char* name, size_t name_length, n2h_compress_e on_failed);

// Z圧縮
#if N2_CONFIG_USE_Z_LIB
#define N2_Z_COMPRESS_NO_COMPRESS	(1)
#define N2_Z_COMPRESS_SPEED			(1)
#define N2_Z_COMPRESS_NORMAL		(6)
#define N2_Z_COMPRESS_BEST			(9)

N2_API n2_bool_t n2h_z_compress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size, int level);
N2_API n2_bool_t n2h_z_decompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size);
N2_API n2_bool_t n2h_z_decompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size);
#endif

// uzl圧縮
#if N2_CONFIG_USE_ULZ_LIB
N2_API n2_bool_t n2h_ulz_compress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size);
N2_API n2_bool_t n2h_ulz_decompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size);

typedef struct n2h_ulz_wrap_t n2h_ulz_wrap_t;
struct n2h_ulz_wrap_t
{
	uint64_t compressed_size_;
	uint64_t decompressed_size_;
	uint32_t check_;
	uint32_t payload_offset_;
};

N2_API n2_bool_t n2h_ulz_wverify(const void* src, size_t src_size);
N2_API n2_bool_t n2h_ulz_wget(n2h_ulz_wrap_t* dst, const void* src, size_t src_size);
N2_API n2_bool_t n2h_ulz_wcompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size);
N2_API n2_bool_t n2h_ulz_wdecompress_to(n2_state_t* state, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size);
N2_API n2_bool_t n2h_ulz_wdecompress(n2_state_t* state, n2_buffer_t* dst, const void* src, size_t src_size);
#endif

// zip
#if N2_CONFIG_USE_Z_LIB
#define N2_ZIP_COMPRESS_NO_COMPRESS		(0)
#define N2_ZIP_COMPRESS_SPEED			(1)
#define N2_ZIP_COMPRESS_NORMAL			(6)
#define N2_ZIP_COMPRESS_BEST			(9)

typedef struct n2h_zip_t n2h_zip_t;
struct n2h_zip_t
{
	void* zip_archive_;

	const void* src_;
	size_t src_size_;
	n2_buffer_t own_buffer_;
};

typedef struct n2h_zip_filestat_t n2h_zip_filestat_t;
struct n2h_zip_filestat_t
{
	char filename_[260];
	int fileindex_;
	n2_bool_t is_directory_;
	size_t comp_size_;
	size_t decomp_size_;
	uint32_t decomp_crc32_;
};

N2_API void n2h_zip_setup(n2_state_t* state, n2h_zip_t* zip);
N2_API void n2h_zip_teardown(n2_state_t* state, n2h_zip_t* zip);
N2_API n2h_zip_t* n2h_zip_alloc(n2_state_t* state);
N2_API void n2h_zip_free(n2_state_t* state, n2h_zip_t* zip);
N2_API n2_bool_t n2h_zip_is_setup_done(const n2h_zip_t* zip);
N2_API n2_bool_t n2h_zip_is_read_mode(const n2h_zip_t* zip);
N2_API n2_bool_t n2h_zip_is_write_mode(const n2h_zip_t* zip);
N2_API n2_bool_t n2h_zip_close(n2_state_t* state, n2h_zip_t* zip);

// read
N2_API n2_bool_t n2h_zip_openr_to(n2_state_t* state, n2h_zip_t* zip, const void* src, size_t src_size);
N2_API size_t n2h_zip_filenum(const n2h_zip_t* zip);
N2_API int n2h_zip_find(const n2h_zip_t* zip, const char* name);
N2_API n2_bool_t n2h_zip_filestat_to(const n2h_zip_t* zip, n2h_zip_filestat_t* dst, int index);
N2_API n2_bool_t n2h_zip_read_to(n2_state_t* state, const n2h_zip_t* zip, n2_buffer_t* dst, int index);

// write
N2_API n2_bool_t n2h_zip_openw_to(n2_state_t* state, n2h_zip_t* zip);
N2_API n2_bool_t n2h_zip_openwa_to(n2_state_t* state, n2h_zip_t* zip, const void* src, size_t src_size);
N2_API n2_bool_t n2h_zip_add_to(n2_state_t* state, n2h_zip_t* zip, const char* filename, const void* src, size_t src_size, int level);
N2_API n2_bool_t n2h_zip_writedown_and_close(n2_state_t* state, n2h_zip_t* zip, n2_buffer_t* dst);
#endif

// ファイルシステム
N2_DECLARE_ENUM(n2h_filesystem_e);
enum n2h_filesystem_e
{
	N2H_FILESYSTEM_NULL = 0,
	N2H_FILESYSTEM_ARRAY,
	N2H_FILESYSTEM_SYSTEM,
	N2H_FILESYSTEM_MSGPACK,
	N2H_FILESYSTEM_ZIP,

	N2H_MAX_FILESYSTEM
};

N2_DECLARE_ENUM(n2h_filesystem_read_e);
enum n2h_filesystem_read_e
{
	N2H_FILESYSTEM_READ_REFERENCE = 0,
	N2H_FILESYSTEM_READ_MUTABLE,

	N2H_MAX_FILESYSTEM_READ
};

typedef struct n2h_filesystem_handle_t n2h_filesystem_handle_t;
typedef struct n2h_filesystem_readhandle_t n2h_filesystem_readhandle_t;
typedef struct n2h_filesystem_writehandle_t n2h_filesystem_writehandle_t;
typedef struct n2h_filesystem_t n2h_filesystem_t;

typedef struct n2h_filesystem_readparam_t n2h_filesystem_readparam_t;
struct n2h_filesystem_readparam_t
{
	n2_state_t* state_;
	const char* filepath_;
	n2_bool_t binary_;
	size_t readsize_;
	size_t readoffset_;
	n2h_filesystem_read_e read_;
	n2h_filesystem_t* filesystem_;
};

typedef struct n2h_filesystem_writeparam_t n2h_filesystem_writeparam_t;
struct n2h_filesystem_writeparam_t
{
	n2_state_t* state_;
	const char* filepath_;
	n2_bool_t binary_;
	const void* writedata_;
	size_t writesize_;
	size_t writeoffset_;/*SIZE_MAX for replace file content, otherwise add data*/
	n2h_filesystem_t* filesystem_;
};

typedef n2h_filesystem_readhandle_t* (*n2h_filesystem_read_func_t)(const n2h_filesystem_readparam_t* readparam);
typedef n2h_filesystem_writehandle_t* (*n2h_filesystem_write_func_t)(const n2h_filesystem_writeparam_t* writeparam);
typedef void (*n2h_filesystem_close_func_t)(n2_state_t* state, n2h_filesystem_handle_t* handle);
typedef void (*n2h_filesystem_fin_func_t)(n2_state_t* state, n2h_filesystem_t* fs);

struct n2h_filesystem_handle_t
{
	n2h_filesystem_t* filesystem_;
	n2_bool_t is_read_;
	const char* error_hint_;
	void* user_;
};

N2_API void n2h_filesystem_handle_teardown(n2_state_t* state, n2h_filesystem_handle_t* handle);

struct n2h_filesystem_readhandle_t
{
	n2h_filesystem_handle_t handle_;
	const void* data_;
	size_t data_size_;
	n2_buffer_t data_mut_;
};

N2_API void n2h_filesystem_readhandle_init(n2h_filesystem_readhandle_t* dst, n2h_filesystem_t* fs);

struct n2h_filesystem_writehandle_t
{
	n2h_filesystem_handle_t handle_;
	n2_bool_t written_succeeded_;
	size_t written_size_;
};

N2_API void n2h_filesystem_writehandle_init(n2h_filesystem_writehandle_t* dst, n2h_filesystem_t* fs);

struct n2h_filesystem_t
{
	n2h_filesystem_e type_;
	n2_str_t name_;
	int priority_;
	int id_;
	n2h_filesystem_read_func_t read_func_;
	n2h_filesystem_write_func_t write_func_;
	n2h_filesystem_close_func_t close_func_;
	n2h_filesystem_fin_func_t fin_func_;
	void* user_;
};

N2_DECLARE_TARRAY(n2h_filesystem_t*, n2h_filesystemarray, N2_API);

typedef struct n2h_filesystem_array_context_t n2h_filesystem_array_context_t;
struct n2h_filesystem_array_context_t
{
	int next_id_;
	n2h_filesystemarray_t* filesystem_array_;
};

N2_API n2h_filesystem_t* n2h_filesystem_alloc_null(n2_state_t* state);
N2_API n2h_filesystem_t* n2h_filesystem_alloc_system(n2_state_t* state);
N2_API void n2h_filesystem_free(n2_state_t* state, n2h_filesystem_t* fs);

N2_API void n2h_filesystem_set_name(n2_state_t* state, n2h_filesystem_t* fs, const char* name, size_t name_length);
N2_API const n2_str_t* n2h_filesystem_get_name(const n2h_filesystem_t* fs);

N2_API void n2h_filesystem_set_priority(n2_state_t* state, n2h_filesystem_t* fs, int priority);
N2_API int n2h_filesystem_get_priority(const n2h_filesystem_t* fs);

N2_API n2h_filesystem_readhandle_t* n2h_filesystem_read(n2_state_t* state, n2h_filesystem_t* fs, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset, n2h_filesystem_read_e read);
N2_API n2h_filesystem_writehandle_t* n2h_filesystem_write(n2_state_t* state, n2h_filesystem_t* fs, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset);
N2_API void n2h_filesystem_close(n2_state_t* state, n2h_filesystem_handle_t* handle);

N2_API n2_bool_t n2h_filesystem_load(n2_state_t* state, n2h_filesystem_t* fs, n2_buffer_t* dst, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset);
N2_API n2_bool_t n2h_filesystem_save(n2_state_t* state, n2h_filesystem_t* fs, size_t* dst_writtensize, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset);

N2_API n2h_filesystem_t* n2h_filesystem_alloc_array(n2_state_t* state);
N2_API size_t n2h_filesystem_array_size(const n2h_filesystem_t* fs);
N2_API n2h_filesystem_t* n2h_filesystem_array_at(n2h_filesystem_t* fs, int index);
N2_API void n2h_filesystem_array_priority_updated(n2h_filesystem_t* fs);
N2_API void n2h_filesystem_array_insert(n2_state_t* state, n2h_filesystem_t* fs, n2h_filesystem_t* add_fs);

#if N2_CONFIG_USE_MSGPACK_LIB
typedef struct n2h_filesystem_msgpack_context_t n2h_filesystem_msgpack_context_t;
struct n2h_filesystem_msgpack_context_t
{
	const n2h_msgpack_element_t* msgpack_;
};

N2_API n2h_filesystem_t* n2h_filesystem_alloc_msgpack(n2_state_t* state, const n2h_msgpack_element_t* msgpack);
#endif

#if N2_CONFIG_USE_Z_LIB
//N2_API n2h_filesystem_t* n2h_filesystem_alloc_zip(n2_state_t* state, n2h_zip_t* zip);// @todo
#endif

#if N2_CONFIG_USE_NET_SOCKET_LIB
typedef struct n2h_socket_t n2h_socket_t;
struct n2h_socket_t
{
	int port_;
	void* socket_;// zed_net_socket_t*
	n2_str_t host_;
	n2_str_t service_;
};

N2_API n2h_socket_t* n2h_socket_server_alloc(n2_state_t* state, int port);
N2_API void n2h_socket_free(n2_state_t* state, n2h_socket_t* socket);
#endif

//=============================================================================
// 論理ソースコード
typedef struct n2_sourcefile_t n2_sourcefile_t;
N2_DECLARE_TARRAY(n2_sourcefile_t*, n2_sourcefilearray, N2_API);

typedef struct n2_sourcecode_t n2_sourcecode_t;
N2_DECLARE_TARRAY(n2_sourcecode_t*, n2_sourcecodearray, N2_API);
N2_DECLARE_TARRAY(n2_sourcecode_t*, n2_sourcecodeptrarray, N2_API);

struct n2_sourcefile_t
{
	int id_;

	n2_str_t src_resolved_filepath_;
	n2_str_t src_resolved_filepath_escaped_;

	n2_sourcecodeptrarray_t sourcecodeptrs_;
};

N2_API n2_sourcefile_t* n2_sourcefile_alloc(n2_state_t* state);
N2_API void n2_sourcefile_free(n2_state_t* state, n2_sourcefile_t* sourcefile);

N2_API n2_sourcefile_t* n2_sourcefilearray_register_sourcecode(n2_state_t* state, n2_sourcefilearray_t* sourcefiles, n2_sourcecode_t* sourcecode);

struct n2_sourcecode_t
{
	n2_str_t package_;
	n2_str_t src_filepath_;
	n2_str_t src_filename_;
	n2_str_t src_loaded_filepath_;
	n2_str_t searchpath_;

	n2_str_t src_script_;
	n2_cstrarray_t script_lines_;
	n2_str_t src_ppscript_;
	n2_cstrarray_t ppscript_lines_;

	n2_szarray_t codeline_indices_;

	n2_sourcecodearray_t* sourcecodes_;

	n2_sourcecode_t* parent_sourcecode_;
	int parent_line_;

	n2_sourcefile_t* sourcefile_;
};

N2_API n2_sourcecode_t* n2_sourcecode_alloc(n2_state_t* state);
N2_API void n2_sourcecode_free(n2_state_t* state, n2_sourcecode_t* sourcecode);

N2_API n2_bool_t n2_sourcecode_split_script_lines(n2_state_t* state, n2_sourcecode_t* sourcecode);
N2_API n2_bool_t n2_sourcecode_split_ppscript_lines(n2_state_t* state, n2_sourcecode_t* sourcecode);

//=============================================================================
// キーワード
N2_DECLARE_ENUM(n2_keyword_e);
enum n2_keyword_e
{
	N2_KEYWORD_UNDEF = -1,

	N2_KEYWORD_GLOBAL = 0,
	N2_KEYWORD_LOCAL,
	N2_KEYWORD_CTYPE,
	N2_KEYWORD_END,
	N2_KEYWORD_RETURN,
	N2_KEYWORD_GOTO,
	N2_KEYWORD_GOSUB,
	N2_KEYWORD_REPEAT,
	N2_KEYWORD_FOREACH,
	N2_KEYWORD_LOOP,
	N2_KEYWORD_CONTINUE,
	N2_KEYWORD_BREAK,
	N2_KEYWORD_IF,
	N2_KEYWORD_ELSE,
	N2_KEYWORD_THEN,
	N2_KEYWORD_SWITCH,
	N2_KEYWORD_CASE,
	N2_KEYWORD_DEFAULT,
	N2_KEYWORD_SWBREAK,
	N2_KEYWORD_SWEND,
	N2_KEYWORD_INT,
	N2_KEYWORD_DOUBLE,
	N2_KEYWORD_STR,
	N2_KEYWORD_LABEL,
	N2_KEYWORD_VAR,
	N2_KEYWORD_ARRAY,
	N2_KEYWORD_MODVAR,
	N2_KEYWORD_THISMOD,

	N2_MAX_KEYWORD
};

N2_API n2_keyword_e n2_keyword_find(const char* s);

//=============================================================================
// トークナイザ
N2_DECLARE_ENUM(n2_token_e);
enum n2_token_e
{
	N2_TOKEN_UNKNOWN = -1,

	N2_TOKEN_ERROR = 0,
	N2_TOKEN_EOF,
	N2_TOKEN_EOL,
	N2_TOKEN_EOS,

	N2_TOKEN_PP_INDICATOR,
	N2_TOKEN_PP_ARG_INDICATOR,

	N2_TOKEN_LBRACE,
	N2_TOKEN_RBRACE,
	N2_TOKEN_LPARENTHESIS,
	N2_TOKEN_RPARENTHESIS,
	N2_TOKEN_COMMA,

	N2_TOKEN_NIL,
	N2_TOKEN_INT,
	N2_TOKEN_HEXINT,
	N2_TOKEN_FLOAT,
	N2_TOKEN_STRING,
	N2_TOKEN_TEMPLATE_STRING,
	N2_TOKEN_CHAR,

	N2_TOKEN_OP_LOR,
	N2_TOKEN_OP_LAND,
	N2_TOKEN_OP_BOR,
	N2_TOKEN_OP_BAND,
	N2_TOKEN_OP_BXOR,
	N2_TOKEN_OP_EQ,
	N2_TOKEN_OP_NEQ,
	N2_TOKEN_OP_NOT,
	N2_TOKEN_OP_GT,
	N2_TOKEN_OP_GTOE,
	N2_TOKEN_OP_LT,
	N2_TOKEN_OP_LTOE,
	N2_TOKEN_OP_BLSHIFT,
	N2_TOKEN_OP_BRSHIFT,

	N2_TOKEN_OP_ADD,
	N2_TOKEN_OP_SUB,
	N2_TOKEN_OP_MUL,
	N2_TOKEN_OP_DIV,
	N2_TOKEN_OP_MOD,

	N2_TOKEN_ASSIGN,
	N2_TOKEN_LOR_ASSIGN,
	N2_TOKEN_LAND_ASSIGN,
	N2_TOKEN_BOR_ASSIGN,
	N2_TOKEN_BAND_ASSIGN,
	N2_TOKEN_BXOR_ASSIGN,
	N2_TOKEN_BLSHIFT_ASSIGN,
	N2_TOKEN_BRSHIFT_ASSIGN,
	N2_TOKEN_ADD_ASSIGN,
	N2_TOKEN_SUB_ASSIGN,
	N2_TOKEN_MUL_ASSIGN,
	N2_TOKEN_DIV_ASSIGN,
	N2_TOKEN_MOD_ASSIGN,

	N2_TOKEN_INCREMENT,
	N2_TOKEN_DECREMENT,

	N2_TOKEN_IDENTIFIER,
	N2_TOKEN_IDENTIFIER_FQ,

	N2_MAX_TOKEN
};

N2_API n2_token_e n2_token_shadow_find(const char* ident, size_t len);
N2_API n2_bool_t n2_token_is_eos_like(n2_token_e tag);

N2_DECLARE_ENUM(n2_source_order_e);
enum n2_source_order_e
{
	N2_SOURCE_ORDER_UNKNOWN = -1,

	N2_SOURCE_ORDER_INCLUDE_PUSH = 0,
	N2_SOURCE_ORDER_INCLUDE_POP,

	N2_MAX_SOURCE_ORDER
};

N2_API n2_source_order_e n2_source_order_find(const char* s);

typedef struct n2_token_t n2_token_t;
struct n2_token_t
{
	n2_token_e token_;
	char* content_;

	int cursor_begin_, cursor_end_;
	const n2_sourcecode_t* sourcecode_;
	const char* package_;
	const char* appear_line_head_;
	int appear_line_;
	n2_bool_t left_space_, right_space_;
};

typedef struct n2_tokenize_context_t n2_tokenize_context_t;
struct n2_tokenize_context_t
{
	n2_sourcecode_t* sourcecode_;
	const char* package_;
	const char* script_;

	size_t template_str_depth_;
	size_t template_str_levels_[N2_MAX_TEMPLATE_STRING_DEPTH];
	const n2_token_t* template_str_token_[N2_MAX_TEMPLATE_STRING_DEPTH];

	int cursor_;
	int line_;
	const char* line_head_;
};

N2_API void n2_tokenize_context_init(n2_state_t* state, n2_tokenize_context_t* c, n2_sourcecode_t* sourcecode);
N2_API void n2_tokenize_context_init_raw(n2_state_t* state, n2_tokenize_context_t* c, const char* package, const char* script);
N2_API void n2_tokenize_context_fin(n2_state_t* state, n2_tokenize_context_t* c);

N2_API n2_bool_t n2_tokenize_context_next(n2_state_t* state, n2_token_t* to, n2_tokenize_context_t* c);
N2_API void n2_token_free(n2_state_t* state, n2_token_t* t);

N2_DECLARE_TARRAY(n2_token_t*, n2_tokenarray, N2_API);

//=============================================================================
// 名前規則
N2_API n2_bool_t n2_naming_compute(n2_state_t* state, const char* src, size_t src_length, const char* modulename, n2_str_t* dst_shortname, n2_str_t* dst_fullname, n2_str_t* dst_modulename);
N2_API n2_bool_t n2_naming_replace_modulename(n2_state_t* state, const char* src, size_t src_length, const char* modulename, n2_str_t* dst);
N2_API n2_bool_t n2_naming_verify_modulename(const char* src, size_t src_length);

//=============================================================================
// 抽象構文木
N2_DECLARE_ENUM(n2_ast_node_e);
enum n2_ast_node_e
{
	N2_AST_NODE_UNDEF = -1,

	N2_AST_NODE_EMPTY = 0,

	N2_AST_NODE_ROOT,
	N2_AST_NODE_ROOT_PARTS,

	N2_AST_NODE_LINE,
	N2_AST_NODE_STATEMENT,

	N2_AST_NODE_MODULE,
	N2_AST_NODE_MODULE_LOCALVAR,
	N2_AST_NODE_GLOBAL,

	N2_AST_NODE_USELIB,

	N2_AST_NODE_DEFFUNC,
	N2_AST_NODE_DEFCFUNC,
	N2_AST_NODE_MODINIT,
	N2_AST_NODE_MODTERM,
	N2_AST_NODE_MODFUNC,
	N2_AST_NODE_MODCFUNC,
	N2_AST_NODE_FUNC,
	N2_AST_NODE_CFUNC,
	N2_AST_NODE_DEFFUNC_PARTS,
	N2_AST_NODE_DECLARE_PARAM,
	N2_AST_NODE_DECLARE_PARAM_PARTS,

	N2_AST_NODE_LABEL,

	N2_AST_NODE_BLOCK_STATEMENTS,

	N2_AST_NODE_COMMAND,
	N2_AST_NODE_ARGUMENTS,
	N2_AST_NODE_ARGUMENTS_PARTS,
	N2_AST_NODE_ARGUMENTS_EMPTY_ARG,

	N2_AST_NODE_ASSIGN,
	N2_AST_NODE_LOR_ASSIGN,
	N2_AST_NODE_LAND_ASSIGN,
	N2_AST_NODE_BOR_ASSIGN,
	N2_AST_NODE_BAND_ASSIGN,
	N2_AST_NODE_BXOR_ASSIGN,
	N2_AST_NODE_BLSHIFT_ASSIGN,
	N2_AST_NODE_BRSHIFT_ASSIGN,
	N2_AST_NODE_ADD_ASSIGN,
	N2_AST_NODE_SUB_ASSIGN,
	N2_AST_NODE_MUL_ASSIGN,
	N2_AST_NODE_DIV_ASSIGN,
	N2_AST_NODE_MOD_ASSIGN,
	N2_AST_NODE_VARIABLE,

	N2_AST_NODE_EXPRESSION,
	N2_AST_NODE_CONDITIONAL,
	N2_AST_NODE_CONDITIONAL_PARTS,
	N2_AST_NODE_LOR,
	N2_AST_NODE_LAND,
	N2_AST_NODE_BOR,
	N2_AST_NODE_BAND,
	N2_AST_NODE_BXOR,
	N2_AST_NODE_EQ,
	N2_AST_NODE_NEQ,
	N2_AST_NODE_GT,
	N2_AST_NODE_GTOE,
	N2_AST_NODE_LT,
	N2_AST_NODE_LTOE,
	N2_AST_NODE_BLSHIFT,
	N2_AST_NODE_BRSHIFT,
	N2_AST_NODE_ADD,
	N2_AST_NODE_SUB,
	N2_AST_NODE_MUL,
	N2_AST_NODE_DIV,
	N2_AST_NODE_MOD,
	N2_AST_NODE_INCREMENT,
	N2_AST_NODE_DECREMENT,
	N2_AST_NODE_UNARY_NOT,
	N2_AST_NODE_UNARY_MINUS,
	N2_AST_NODE_PRIMITIVE_VALUE,
	N2_AST_NODE_TEMPLATE_STRING,
	N2_AST_NODE_TEMPLATE_STRING_PARTS,
	N2_AST_NODE_LABEL_VALUE,
	N2_AST_NODE_IDENTIFIER_EXPR,

	N2_AST_NODE_END,
	N2_AST_NODE_RETURN,

	N2_AST_NODE_GOTO,
	N2_AST_NODE_GOSUB,

	N2_AST_NODE_REPEAT,
	N2_AST_NODE_FOREACH,
	N2_AST_NODE_LOOP,
	N2_AST_NODE_CONTINUE,
	N2_AST_NODE_BREAK,

	N2_AST_NODE_IF,
	N2_AST_NODE_IF_DISPATCHER,

	N2_AST_NODE_SWITCH,
	N2_AST_NODE_CASE,
	N2_AST_NODE_DEFAULT,
	N2_AST_NODE_SWBREAK,
	N2_AST_NODE_SWEND,

	N2_MAX_AST_NODE
};

typedef struct n2_ast_node_t n2_ast_node_t;
struct n2_ast_node_t
{
	n2_ast_node_e node_;
	const n2_token_t* token_;
	n2_ast_node_t *left_, *right_;
	size_t exflags_;
};

N2_API n2_ast_node_t* n2_ast_node_alloc(n2_state_t* state, n2_ast_node_e tag, n2_ast_node_t* left, n2_ast_node_t* right);
N2_API n2_ast_node_t* n2_ast_node_alloc_token(n2_state_t* state, n2_ast_node_e tag, const n2_token_t* token, n2_ast_node_t* left);
N2_API void n2_ast_node_free_unit(n2_state_t* state, n2_ast_node_t* node);
N2_API void n2_ast_node_free(n2_state_t* state, n2_ast_node_t* node);

N2_API void n2_ast_node_dump(n2_state_t* state, const n2_ast_node_t* ast, n2_bool_t is_detail);

N2_DECLARE_TARRAY(n2_ast_node_t*, n2_astarray, N2_API);

//=============================================================================
// パーサー
typedef struct n2_parser_t n2_parser_t;
struct n2_parser_t
{
	n2_tokenarray_t* tokens_;
	int token_cursor_;
	n2_tokenize_context_t tokenize_context_;
};

N2_API n2_parser_t* n2_parser_alloc(n2_state_t* state);
N2_API void n2_parser_free(n2_state_t* state, n2_parser_t* p);
N2_API void n2_parser_rewind(n2_state_t* state, n2_parser_t* p, n2_sourcecode_t* sourcecode);
N2_API void n2_parser_rewind_raw(n2_state_t* state, n2_parser_t* p, const char* package, const char* script);

N2_API const n2_token_t* n2_parser_read_token(n2_state_t* state, n2_parser_t* p);
N2_API void n2_parser_unread_token(n2_parser_t* p, size_t num);
N2_API const n2_token_t* n2_parser_prev_token(const n2_parser_t* p, size_t num);

N2_API n2_ast_node_t* n2_parser_parse(n2_state_t* state, n2_parser_t* p);
N2_API n2_ast_node_t* n2_parser_parse_expression(n2_state_t* state, n2_parser_t* p);

N2_DECLARE_TARRAY(n2_parser_t*, n2_parserarray, N2_API);

//=============================================================================
// シンボル
typedef struct n2_symbol_t n2_symbol_t;
struct n2_symbol_t
{
	size_t id_;
	n2_str_t name_;
};

N2_DECLARE_TARRAY(n2_symbol_t, n2_symbolarray, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_symbolindexmap, N2_API);

typedef struct n2_symboltable_t n2_symboltable_t;
struct n2_symboltable_t
{
	n2_symbolarray_t* symbolarray_;
	n2_symbolindexmap_t* symbolindexmap_;
};

N2_API n2_symboltable_t* n2_symboltable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step);
N2_API void n2_symboltable_free(n2_state_t* state, n2_symboltable_t* symboltable);
N2_API n2_symbol_t* n2_symboltable_peek(n2_symboltable_t* symboltable, int index);
N2_API n2_symbol_t* n2_symboltable_find(n2_symboltable_t* symboltable, const char* name);
N2_API int n2_symboltable_register(n2_state_t* state, n2_symboltable_t* symboltable, const char* name);

//=============================================================================
// ハンドリング

// print
N2_DECLARE_ENUM(n2_log_level_e);
enum n2_log_level_e
{
	N2_LOG_LEVEL_CRITICAL = 0,
	N2_LOG_LEVEL_WARNING,
	N2_LOG_LEVEL_INFO,
	N2_LOG_LEVEL_LOGMES,

	N2_MAX_LOG_LEVEL
};

typedef void (*n2_print_func_t)(void* print_user, n2_state_t* state, const char* str);
typedef void (*n2_print_log_func_t)(void* print_user, n2_state_t* state, n2_fiber_t* fiber, n2_log_level_e log_level, const char* str);
typedef void (*n2_print_error_func_t)(void* print_user, n2_state_t* state, const char* str);

// エラー
N2_DECLARE_ENUM(n2_error_e);
enum n2_error_e
{
	N2_ERROR_NONE = 0,
	N2_ERROR_PREPROCESS,
	N2_ERROR_TOKENIZE,
	N2_ERROR_PARSE,
	N2_ERROR_COMPILE,
	N2_ERROR_RUNTIME,

	N2_MAX_ERROR
};

typedef struct n2_error_param_t n2_error_param_t;
struct n2_error_param_t
{
	n2_state_t* state_;
	n2_error_e error_;
	const n2_sourcecode_t* sourcecode_;
	const char* package_;
	const char* raw_message_;
	const char* message_;
	const char* subdescription_;
	int line_;
	int column_;
	n2_fiber_t* fiber_;
};

N2_API void n2_error_param_init(n2_error_param_t* error_param);

typedef void (*n2_error_func_t)(void* error_user, const n2_error_param_t* error_param);

//=============================================================================
// デバッガーフック
// ※デバッグ関係の定義は他のコンポーネントが参照する関係で、かなり早期に定義する
typedef struct n2_debughook_t n2_debughook_t;

N2_DECLARE_ENUM(n2_debughook_stop_reason_e);
enum n2_debughook_stop_reason_e
{
	N2_DEBUGHOOK_STOP_REASON_NONE = -1,
	N2_DEBUGHOOK_STOP_REASON_PAUSE = 0,
	N2_DEBUGHOOK_STOP_REASON_ASSERT,
	N2_DEBUGHOOK_STOP_REASON_BREAKPOINT,
	N2_DEBUGHOOK_STOP_REASON_STEP,
	N2_DEBUGHOOK_STOP_REASON_ERROR,

	N2_MAX_DEBUGHOOK_STOP_REASON
};

enum
{
	N2_DEBUGHOOK_POLLFLAG_BUSY = 0x01,
};

typedef void(*n2_debughook_pollfunc_t)(n2_state_t* state, n2_debughook_t* dhook, size_t pollflags);
typedef void(*n2_debughook_breakstopfunc_t)(n2_state_t* state, n2_debughook_t* dhook, n2_fiber_t* fiber, n2_debughook_stop_reason_e reason);
typedef void(*n2_debughook_errorstopfunc_t)(n2_state_t* state, n2_debughook_t* dhook, const n2_error_param_t* error_param);
typedef void(*n2_debughook_finfunc_t)(n2_state_t* state, n2_debughook_t* dhook);

struct n2_debughook_t
{
	// settings
	n2_debughook_pollfunc_t pollfunc_;
	n2_debughook_breakstopfunc_t breakstopfunc_;
	n2_debughook_errorstopfunc_t errorstopfunc_;
	n2_debughook_finfunc_t finfunc_;
	void* user_;

	size_t poll_per_operation_;

	// states
	n2_environment_t* attached_environment_;

	// internal stats
	size_t icounter_poll_operation_;
};

N2_API void n2_debughook_free(n2_state_t* state, n2_debughook_t* debughook);

N2_DECLARE_ENUM(n2_debugint_e);
enum n2_debugint_e
{
	N2_DEBUGINT_NONE = 0,
	N2_DEBUGINT_PAUSE,
	N2_DEBUGINT_NEXT,
	N2_DEBUGINT_STEPIN,
	N2_DEBUGINT_STEPOUT,

	N2_MAX_DEBUGINT
};

N2_DECLARE_ENUM(n2_debugint_granularity_e);
enum n2_debugint_granularity_e
{
	N2_DEBUGINT_GRANULARITY_INSTRUCTION = 0,
	N2_DEBUGINT_GRANULARITY_STATEMENT,
	N2_DEBUGINT_GRANULARITY_LINE,
	N2_DEBUGINT_GRANULARITY_FUNCTION,

	N2_MAX_DEBUGINT_GRANULARITY
};

// デバッガ上で確認できる名前のある値単位
N2_DECLARE_ENUM(n2_debugvariable_e);
enum n2_debugvariable_e
{
	N2_DEBUGVARIABLE_NONE = 0,
	N2_DEBUGVARIABLE_ENVIRONMENT,
	N2_DEBUGVARIABLE_SYSVAR,
	N2_DEBUGVARIABLE_SYSVAR_ELEMENT,
	N2_DEBUGVARIABLE_FIBER,
	N2_DEBUGVARIABLE_FIBER_CALLFRAME,
	N2_DEBUGVARIABLE_VARIABLE_ROOT,
	N2_DEBUGVARIABLE_VARIABLE_DIMENSION,
	N2_DEBUGVARIABLE_VARIABLE_ELEMENT,
	N2_DEBUGVARIABLE_FUNCTIONARG,

	N2_MAX_DEBUGVARIABLE
};

typedef struct n2_debugvariable_t n2_debugvariable_t;
struct n2_debugvariable_t
{
	n2_list_node_t entry_;
	size_t id_;
	n2_debugvariable_e type_;

	union
	{
		n2_environment_t* environment_;
		struct
		{
			n2_fiber_t* fiber_;
		} sysvar_;
		struct
		{
			n2_fiber_t* fiber_;
			int sysvar_index_;
		} sysvar_element_;
		n2_fiber_t* fiber_;
		struct
		{
			n2_fiber_t* fiber_;
			int callframe_index_;
		} fiber_cf_;
		n2_variable_t* var_root_;
		struct
		{
			n2_variable_t* var_;
			size_t dimension_[N2_VARIABLE_DIM];
			size_t dimension_index_;
		} var_dimension_;
		struct
		{
			n2_variable_t* var_;
			size_t element_index_;
		} var_element_;
		struct
		{
			n2_fiber_t* fiber_;
			int callframe_index_;
			int arg_index_;
		} funcarg_;
	} v_;
};

N2_API n2_debugvariable_t* n2_debugvariable_alloc(n2_state_t* state);
N2_API void n2_debugvariable_free(n2_state_t* state, n2_debugvariable_t* debugvar);

N2_DECLARE_TARRAY(n2_debugvariable_t*, n2_debugvararray, N2_API);
N2_API void n2_debugvararray_autoresize(n2_state_t* state, n2_debugvararray_t* a, size_t size);

N2_DECLARE_TSORTED_ARRAY(n2_debugvariable_t*, void, size_t, n2_debugvarset, N2_API);

typedef struct n2_debugvarpool_t n2_debugvarpool_t;
struct n2_debugvarpool_t
{
	n2_debugvarset_t* debugvars_;
	n2_list_t debugvar_pool_;
	size_t next_id_;
};

N2_API n2_debugvarpool_t* n2_debugvarpool_alloc(n2_state_t* state, size_t initial_pool_size);
N2_API void n2_debugvarpool_free(n2_state_t* state, n2_debugvarpool_t* debugvarpool);

N2_API n2_debugvariable_t* n2_debugvarpool_pop_or_alloc(n2_state_t* state, n2_debugvarpool_t* debugvarpool);
N2_API void n2_debugvarpool_push(n2_state_t* state, n2_debugvarpool_t* debugvarpool, n2_debugvariable_t* debugvar);

//=============================================================================
// プリミティブ値
#if 1
// 64bit for int
typedef int64_t n2_valint_t;
#define N2_VALINT_PRI_PF	"I64"
#else
// 32bit for int
typedef int32_t n2_valint_t;
#define N2_VALINT_PRI_PF	""
#endif

#define N2_VALINT_PRI		N2_VALINT_PRI_PF "d"
typedef double n2_valfloat_t;
#define N2_VALFLOAT_PRI_PF	"l"
#define N2_VALFLOAT_PRI		N2_VALFLOAT_PRI_PF "f"

typedef n2_str_t n2_valstr_t;
typedef struct n2_vallabel_t n2_vallabel_t;
typedef struct n2_valvar_t n2_valvar_t;
typedef struct n2_valmodinst_t n2_valmodinst_t;

//=============================================================================
// 変数
struct n2_variable_t
{
	char* name_;// 名前、匿名ならnull可
	n2_value_e type_;// 型
	size_t length_[N2_VARIABLE_DIM];// 次元毎の数
	size_t element_num_;// 次元事の数を全て掛けたもの、実際に保持している数
	size_t element_size_;// 一つのエレメントのサイズ＝ストライド
	size_t granule_size_;// 初期化時の粒度サイズ
	int module_id_;// MODULE時のモジュールのID
	void* data_;// 実際のデータの先頭ポインタ
	size_t data_buffer_size_;// 確保したデータのサイズ
#if N2_CONFIG_USE_DEBUGGING
	n2_debugvarpool_t* debugvarpool_;
	n2_debugvariable_t* debugvarroot_;// この変数のルート
	n2_debugvararray_t debugvardims_[N2_VARIABLE_DIM];// 次元ごと
	n2_debugvararray_t debugvarelements_;// 要素ごと
#endif
};

N2_API n2_variable_t* n2_variable_alloc(n2_state_t* state, n2_environment_t* e, const char* name);
N2_API void n2_variable_free(n2_state_t* state, n2_variable_t* var);
N2_API void n2_variable_prepare(n2_state_t* state, n2_variable_t* var, n2_value_e type, size_t granule_size, const size_t length[N2_VARIABLE_DIM]);
N2_API void n2_variable_redim(n2_state_t* state, n2_variable_t* var, const size_t length[N2_VARIABLE_DIM]);
N2_API void n2_variable_clear(n2_state_t* state, n2_variable_t* var);

N2_API n2_bool_t n2_variable_set(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_bor(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_band(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_bxor(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_blshift(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_blshift(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_add(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_sub(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_mul(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_div(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_mod(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr, const n2_value_t* val);
N2_API n2_bool_t n2_variable_increment(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr);
N2_API n2_bool_t n2_variable_decrement(n2_state_t* state, n2_fiber_t* f, n2_variable_t* var, int aptr);

N2_API size_t n2_variable_compute_dimension_num(const size_t length[N2_VARIABLE_DIM]);
N2_API int n2_variable_compute_aptr_indim(const n2_variable_t* var, const size_t indices[N2_VARIABLE_DIM], size_t indim);
N2_API int n2_variable_compute_aptr(const n2_variable_t* var, const size_t indices[N2_VARIABLE_DIM]);
N2_API void n2_variable_compute_dimension_indices_indim(size_t dst_length[N2_VARIABLE_DIM], size_t element_index, const size_t length[N2_VARIABLE_DIM], size_t indim);
N2_API void n2_variable_compute_dimension_indices(size_t dst_length[N2_VARIABLE_DIM], size_t element_index, const size_t length[N2_VARIABLE_DIM]);
N2_API void* n2_variable_element_ptr(const n2_variable_t* var, int aptr);
N2_API size_t n2_variable_element_size(const n2_variable_t* var, int aptr);
N2_API size_t n2_variable_left_buffer_size(const n2_variable_t* var, int aptr);
N2_API void* n2_variable_map_data(size_t* data_size, const n2_variable_t* var, int aptr);
N2_API void n2_variable_unmap_data(const n2_variable_t* var, int aptr);
N2_API n2_valint_t n2_variable_eval_int(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr);
N2_API n2_valfloat_t n2_variable_eval_float(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr);
N2_API const char* n2_variable_get_plstr(const n2_variable_t* var, int aptr);
N2_API n2_valstr_t* n2_variable_get_str(n2_variable_t* var, int aptr);
N2_API const n2_valstr_t* n2_variable_get_strc(const n2_variable_t* var, int aptr);
N2_API n2_valstr_t* n2_variable_eval_str(n2_state_t* state, n2_fiber_t* f, const n2_variable_t* var, int aptr);
N2_API const n2_vallabel_t* n2_variable_get_label(const n2_variable_t* var, int aptr);
N2_API n2_valmodinst_t* n2_variable_get_modinst(n2_variable_t* var, int aptr);
N2_API const n2_valmodinst_t* n2_variable_get_modinstc(const n2_variable_t* var, int aptr);

N2_API void n2_variable_inspect(n2_state_t* state, n2_environment_t* e, n2_str_t* dst, const n2_variable_t* var, int aptr);
N2_API void n2_variable_ensure_debugvariables(n2_state_t* state, n2_variable_t* var, size_t dim);

N2_DECLARE_TARRAY(n2_variable_t*, n2_vararray, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_varindexmap, N2_API);

typedef struct n2_vartable_t n2_vartable_t;
struct n2_vartable_t
{
	n2_vararray_t vararray_;
	n2_varindexmap_t* varindexmap_;
};

N2_API n2_vartable_t* n2_vartable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step);
N2_API void n2_vartable_free(n2_state_t* state, n2_vartable_t* vartable);
N2_API n2_variable_t* n2_vartable_peek(n2_vartable_t* vartable, int index);
N2_API const n2_variable_t* n2_vartable_peekc(const n2_vartable_t* vartable, int index);
N2_API n2_variable_t* n2_vartable_find(n2_vartable_t* vartable, const char* name);
N2_API int n2_vartable_register(n2_state_t* state, n2_environment_t* e, n2_vartable_t* vartable, const char* name);
N2_API size_t n2_vartable_size_named(const n2_vartable_t* vartable);
N2_API n2_variable_t* n2_vartable_peek_named(n2_vartable_t* vartable, int index);

//=============================================================================
// 値
N2_API const char* n2_valuetype_name(const n2_value_e value, const char* on_failed);
N2_API int n2_valuetype_find(const char* name, n2_bool_t include_ex);

struct n2_vallabel_t
{
	int label_index_;
};

struct n2_valvar_t
{
	n2_variable_t* var_;
	int aptr_;
};

struct n2_valmodinst_t
{
	n2_modinstance_t* instance_;
};

typedef union n2_value_field_t n2_value_field_t;
union n2_value_field_t
{
	n2_valint_t ivalue_;
	n2_valfloat_t fvalue_;
	n2_valstr_t svalue_;
	n2_vallabel_t labelvalue_;
	n2_valvar_t varvalue_;
	n2_valmodinst_t modvalue_;
};

struct n2_value_t
{
	n2_value_e type_;
	n2_value_field_t field_;
};

N2_API n2_value_t* n2_value_allocnil(n2_state_t* state);
N2_API n2_value_t* n2_value_alloci(n2_state_t* state, n2_valint_t v);
N2_API n2_value_t* n2_value_allocf(n2_state_t* state, n2_valfloat_t v);
N2_API n2_value_t* n2_value_allocs(n2_state_t* state, n2_valstr_t* v);
N2_API n2_value_t* n2_value_allocl(n2_state_t* state, int labelindex);
N2_API n2_value_t* n2_value_allocvar(n2_state_t* state, n2_variable_t* var, int aptr);
N2_API n2_value_t* n2_value_allocmodinst(n2_state_t* state, n2_modinstance_t* instance);
N2_API n2_value_t* n2_value_clone(n2_state_t* state, const n2_value_t* rval);
N2_API void n2_value_free(n2_state_t* state, n2_value_t* val);

N2_API void n2_value_swap(n2_value_t* lhs, n2_value_t* rhs);
N2_API void n2_value_seti(n2_state_t* state, n2_value_t* val, n2_valint_t v);
N2_API void n2_value_setf(n2_state_t* state, n2_value_t* val, n2_valfloat_t v);
N2_API void n2_value_sets(n2_state_t* state, n2_value_t* val, const char* v, size_t length);
N2_API void n2_value_replaces(n2_state_t* state, n2_value_t* val, n2_valstr_t* v);
N2_API void n2_value_setl(n2_state_t* state, n2_value_t* val, const n2_vallabel_t* v);
N2_API void n2_value_setvar(n2_state_t* state, n2_value_t* val, n2_variable_t* var, int aptr);
N2_API void n2_value_setmodinstance(n2_state_t* state, n2_value_t* val, n2_modinstance_t* instance);

N2_API n2_value_e n2_value_get_type(const n2_value_t* val);
N2_API n2_bool_t n2_value_eval_bool(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val);
N2_API n2_valint_t n2_value_eval_int(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val);
N2_API n2_valfloat_t n2_value_eval_float(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val);
N2_API const char* n2_value_get_plstr(const n2_value_t* val);
N2_API n2_valstr_t* n2_value_get_str(n2_value_t* val);
N2_API const n2_valstr_t* n2_value_get_strc(const n2_value_t* val);
N2_API n2_valstr_t* n2_value_eval_str(n2_state_t* state, n2_fiber_t* f, const n2_value_t* val);
N2_API const n2_vallabel_t* n2_value_get_label(const n2_value_t* val);
N2_API n2_valmodinst_t* n2_value_get_modinst(n2_value_t* val);
N2_API const n2_valmodinst_t* n2_value_get_modinstc(const n2_value_t* val);
N2_API const n2_value_t* n2_value_eval_as(n2_state_t* state, n2_fiber_t* f, n2_value_e to, const n2_value_t* src, n2_value_t** will_free);
N2_API void n2_value_isolate(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, n2_bool_t nil_to_int);

N2_API n2_bool_t n2_value_bor(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_band(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_bxor(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_eq(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_neq(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_gt(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_gtoe(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_lt(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_ltoe(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_blshift(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_brshift(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_add(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_sub(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_mul(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_div(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_mod(n2_state_t* state, n2_fiber_t* f, n2_value_t* val, const n2_value_t* rhs);
N2_API n2_bool_t n2_value_unary_not(n2_state_t* state, n2_fiber_t* f, n2_value_t* val);
N2_API n2_bool_t n2_value_unary_minus(n2_state_t* state, n2_fiber_t* f, n2_value_t* val);

N2_API void n2_value_inspect(n2_state_t* state, n2_environment_t* e, n2_str_t* dst, const n2_value_t* val);

N2_DECLARE_TARRAY(n2_value_t*, n2_valuearray, N2_API);
N2_DECLARE_TARRAY(n2_value_t, n2_flatvaluearray, N2_API);

//=============================================================================
// 実行コード
typedef int32_t n2_pc_t;

typedef struct n2_label_t n2_label_t;
struct n2_label_t
{
	char* name_;
	n2_pc_t pc_;
};

N2_DECLARE_TARRAY(n2_label_t, n2_labelarray, N2_API);

typedef int32_t n2_opcode_t;

N2_DECLARE_ENUM(n2_opcode_e);
enum n2_opcode_e
{
	N2_OPCODE_NOP = 0,

	N2_OPCODE_POP,
	N2_OPCODE_PUSH_NIL,
	N2_OPCODE_PUSH_SINT,
	N2_OPCODE_PUSH_VAL_LITERAL,
	N2_OPCODE_PUSH_STRING,
	N2_OPCODE_PUSH_TEMPLATE_STRING,
	N2_OPCODE_PUSH_LABEL,
	N2_OPCODE_PUSH_VARIABLE,
	N2_OPCODE_PUSH_SYSVAR,
	N2_OPCODE_PUSH_SYSVAR_EX,
	N2_OPCODE_PUSH_MODULE,
	N2_OPCODE_PUSH_MODULE_LOCALVAR,
	N2_OPCODE_PUSH_STACK,
	N2_OPCODE_PUSH_STACK_REL,
	N2_OPCODE_STORE_STACK,

	N2_OPCODE_SET_VARIABLE_APTR,

	N2_OPCODE_ASSIGN,
	N2_OPCODE_ASSIGN_BULK,
	N2_OPCODE_BOR_ASSIGN,
	N2_OPCODE_BAND_ASSIGN,
	N2_OPCODE_BXOR_ASSIGN,
	N2_OPCODE_BLSHIFT_ASSIGN,
	N2_OPCODE_BRSHIFT_ASSIGN,
	N2_OPCODE_ADD_ASSIGN,
	N2_OPCODE_SUB_ASSIGN,
	N2_OPCODE_MUL_ASSIGN,
	N2_OPCODE_DIV_ASSIGN,
	N2_OPCODE_MOD_ASSIGN,
	N2_OPCODE_INCREMENT,
	N2_OPCODE_DECREMENT,

	N2_OPCODE_BOR,
	N2_OPCODE_BAND,
	N2_OPCODE_BXOR,

	N2_OPCODE_EQ,
	N2_OPCODE_NEQ,
	N2_OPCODE_GT,
	N2_OPCODE_GTOE,
	N2_OPCODE_LT,
	N2_OPCODE_LTOE,

	N2_OPCODE_BLSHIFT,
	N2_OPCODE_BRSHIFT,

	N2_OPCODE_ADD,
	N2_OPCODE_SUB,
	N2_OPCODE_MUL,
	N2_OPCODE_DIV,
	N2_OPCODE_MOD,

	N2_OPCODE_UNARY_NOT,
	N2_OPCODE_UNARY_MINUS,

	N2_OPCODE_TEST_NIL,
	N2_OPCODE_TEST_ORIGINAL_ARG_NUM,

	N2_OPCODE_IF,
	N2_OPCODE_IFNOT,

	N2_OPCODE_REPEAT,
	N2_OPCODE_FOREACH,
	N2_OPCODE_REPEAT_CHECK,
	N2_OPCODE_LOOP,
	N2_OPCODE_CONTINUE,
	N2_OPCODE_BREAK,

	N2_OPCODE_SWITCH,
	N2_OPCODE_SWCASE,
	N2_OPCODE_SWDEFAULT,
	N2_OPCODE_SWBREAK,
	N2_OPCODE_SWEND,

	N2_OPCODE_MODULE,
	N2_OPCODE_GLOBAL,

	N2_OPCODE_DEFFUNC,
	N2_OPCODE_ENTER_FUNCTION,

	N2_OPCODE_LABEL,

	N2_OPCODE_GOSUB,
	N2_OPCODE_GOTO,

	N2_OPCODE_COMMAND,
	N2_OPCODE_FUNCTION,

	N2_OPCODE_JUMP,
	N2_OPCODE_JUMP_RELATIVE,
	N2_OPCODE_RETURN,
	N2_OPCODE_END,

	N2_MAX_OPECODE
};

N2_DECLARE_TARRAY(n2_opcode_t, n2_opcodearray, N2_API);

typedef struct n2_codeline_t n2_codeline_t;
struct n2_codeline_t
{
	n2_pc_t pc_;
	const n2_sourcecode_t* sourcecode_;
	const char* package_;
	int line_;
	int column_;// @todo not supported yet
	const char* line_head_;
	n2_intset_t relative_var_indices_;
};

N2_DECLARE_TSORTED_ARRAY(n2_codeline_t, void, n2_pc_t, n2_codelinetable, N2_API);

enum
{
	// 下位ニブルは属性
	N2_OPCODEFLAG_STATEMENT_HEAD = 0x01,
	N2_OPCODEFLAG_LINE_STATEMENTS_HEAD = 0x02,

	// 上位ニブルは動的オプション
	N2_OPCODEFLAG_BREAKPOINT = 0x10,
};

typedef struct n2_codeimage_t n2_codeimage_t;
struct n2_codeimage_t
{
	n2_opcodearray_t* opcodes_;
	n2_u8array_t* opcodeflags_;

	n2_flatvaluearray_t* val_literals_;
	n2_plstrarray_t* str_literals_;

	n2_sourcefilearray_t* sourcefiles_;
	n2_sourcecodearray_t* sourcecodes_;

	n2_codelinetable_t* codelinetable_;
};

N2_API n2_codeimage_t* n2_codeimage_alloc(n2_state_t* state);
N2_API void n2_codeimage_free(n2_state_t* state, n2_codeimage_t* codeimage);

N2_API const n2_codeline_t* n2_codeimage_find_codeline_from_pc(const n2_codeimage_t* codeimage, n2_pc_t pc);

enum n2_codeimage_dump_e
{
	N2_CODEIMAGE_DUMP_CODELINES = 0x01,
	N2_CODEIMAGE_DUMP_RELATIVE_VARS = 0x02,

	N2_CODEIMAGE_DUMP_DEFAULT = (N2_CODEIMAGE_DUMP_CODELINES),
	N2_CODEIMAGE_DUMP_ALL = 0x0fffffff,
};

N2_API void n2_codeimage_dump(n2_state_t* state, const n2_codeimage_t* codeimage, const n2_environment_t* e, size_t flags);

//=============================================================================
// 関数
typedef struct n2_funcarg_t n2_funcarg_t;
struct n2_funcarg_t
{
	n2_state_t* state_;
	n2_fiber_t* fiber_;
	const n2_func_t* func_;
	void* funcuser_;
};

typedef int(*n2_func_callback_t)(const n2_funcarg_t* arg);

N2_DECLARE_ENUM(n2_func_param_e);
enum n2_func_param_e
{
	N2_FUNC_PARAM_UNKNOWN = -1,
	N2_FUNC_PARAM_INT = 0,
	N2_FUNC_PARAM_FLOAT,
	N2_FUNC_PARAM_STR,
	N2_FUNC_PARAM_LABEL,
	N2_FUNC_PARAM_VAR,
	N2_FUNC_PARAM_ARRAY,
	N2_FUNC_PARAM_LOCAL,
	N2_FUNC_PARAM_MODVAR,

	// 拡張型
	N2_FUNC_PARAM_WSTR,
	N2_FUNC_PARAM_SPTR,
	N2_FUNC_PARAM_WPTR,
	N2_FUNC_PARAM_SINGLEFLOAT,
	N2_FUNC_PARAM_NULLPTR,
	// のn2拡張
	N2_FUNC_PARAM_INT64,
	N2_FUNC_PARAM_U8STR,
	N2_FUNC_PARAM_U8PTR,

	N2_MAX_FUNC_PARAM
};

N2_API n2_func_param_e n2_func_param_from_token(const n2_token_t* token, n2_bool_t allow_dltype);

typedef struct n2_func_param_t n2_func_param_t;
struct n2_func_param_t
{
	char* name_;
	n2_func_param_e type_;
	n2_bool_t omittable_;
};
N2_DECLARE_TARRAY(n2_func_param_t, n2_funcparamarray, N2_API);

N2_DECLARE_ENUM(n2_func_e);
enum n2_func_e
{
	N2_FUNC_UNKNOWN = -1,
	N2_FUNC_INTERNAL = 0,
	N2_FUNC_EXTERNAL,
	N2_FUNC_SCRIPT,
	N2_FUNC_DLFUNC,
	N2_FUNC_ALIAS,

	N2_MAX_FUNC
};

N2_DECLARE_ENUM(n2_funcflag_e);
enum n2_funcflag_e
{
	N2_FUNCFLAG_DEFINED = 0x01
};

struct n2_func_t
{
	n2_func_e func_;
	char* name_;
	char* short_name_;
	size_t flags_;
	n2_func_callback_t callback_;
	void* user_;
	n2_pc_t pc_;
	n2_funcparamarray_t* params_;
	n2_func_t* alias_func_;
	int module_id_;// modfunc/modcfunc/modinit/modterm
	n2_str_t libprocname_;// func/cfunc
	n2h_dynlib_t* lib_;
	void* libproc_;

#if N2_CONFIG_USE_PROFILING
	size_t called_count_;
	uint64_t total_ticks_;
#endif
};

N2_DECLARE_TARRAY(n2_func_t, n2_funcarray, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_funcindexmap, N2_API);

typedef struct n2_functable_t n2_functable_t;
struct n2_functable_t
{
	n2_funcarray_t* funcarray_;
	n2_funcindexmap_t* funcindexmap_;
};

N2_API n2_functable_t* n2_functable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step);
N2_API void n2_functable_free(n2_state_t* state, n2_functable_t* functable);
N2_API n2_func_t* n2_functable_peek(n2_functable_t* functable, int index);
N2_API n2_func_t* n2_functable_find(n2_functable_t* functable, const char* name);
N2_API int n2_functable_register(n2_state_t* state, n2_functable_t* functable, const char* name);

//=============================================================================
// システム変数
N2_DECLARE_ENUM(n2_sysvar_e);
enum n2_sysvar_e
{
	N2_SYSVAR_UNDEF = -1,

	N2_SYSVAR_HSPVER = 0,
	N2_SYSVAR_CNT,
	N2_SYSVAR_STAT,
	N2_SYSVAR_REFDVAL,
	N2_SYSVAR_REFSTR,
	N2_SYSVAR_STRSIZE,
	N2_SYSVAR_LOOPLEV,
	N2_SYSVAR_SUBLEV,
	N2_SYSVAR_NOTEMAX,
	N2_SYSVAR_NOTESIZE,

	N2_MAX_SYSVAR
};

N2_API const char* n2_sysvar_name(n2_sysvar_e sysvar, const char* on_failed);
N2_API n2_sysvar_e n2_sysvar_find(const char* s);

N2_API n2_bool_t n2_sysvar_inspect(n2_state_t* state, n2_str_t* dst, n2_str_t* dst_type, n2_sysvar_e sysvar, const n2_fiber_t* f);

typedef struct n2_sysvar_ex_t n2_sysvar_ex_t;

typedef int(*n2_sysvar_ex_callback_t)(const n2_funcarg_t* arg);
typedef n2_bool_t(*n2_sysvar_ex_inspect_t)(n2_state_t* state, n2_fiber_t* f, n2_str_t* dst, n2_str_t* dst_type, const n2_sysvar_ex_t* sysvarex);

struct n2_sysvar_ex_t
{
	char* name_;
	n2_sysvar_ex_callback_t callback_;
	n2_sysvar_ex_inspect_t inspect_;
	void* user_;
#if N2_CONFIG_USE_DEBUGGING
	n2_debugvarpool_t* debugvarpool_;
	n2_debugvariable_t* debugvarroot_;
#endif
};

N2_DECLARE_TARRAY(n2_sysvar_ex_t, n2_sysvarexarray, N2_API);

//=============================================================================
// モジュール
typedef struct n2_modlocalvar_t n2_modlocalvar_t;
struct n2_modlocalvar_t
{
	char* name_;
};

N2_DECLARE_TARRAY(n2_modlocalvar_t, n2_modlocalvararray, N2_API);

typedef n2_modinstance_t* (*n2_modinstance_alloc_callback_t)(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule);
typedef void (*n2_modinstance_free_callback_t)(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule, n2_modinstance_t* instance);

N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_modfuncindexset, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_modfuncsnameindexset, N2_API);

struct n2_module_t
{
	char* name_;
	int module_id_;
	n2_pc_t pc_begin_;
	n2_modlocalvararray_t* modlocalvars_;
	n2_modfuncindexset_t* modfuncs_;
	n2_modfuncsnameindexset_t* modfuncsnames_;
	int modinit_funcindex_;
	int modterm_funcindex_;
	n2_modinstance_alloc_callback_t alloc_callback_;
	n2_modinstance_free_callback_t free_callback_;
	void* mod_user_;
};

N2_DECLARE_TARRAY(n2_module_t, n2_modulearray, N2_API);
N2_DECLARE_TSORTED_ARRAY(int, void, char, n2_moduleindexmap, N2_API);

typedef struct n2_moduletable_t n2_moduletable_t;
struct n2_moduletable_t
{
	n2_modulearray_t* modulearray_;
	n2_moduleindexmap_t* moduleindexmap_;
};

N2_API n2_moduletable_t* n2_moduletable_alloc(n2_state_t* state, size_t initial_buffer_size, size_t expand_step);
N2_API void n2_moduletable_free(n2_state_t* state, n2_moduletable_t* moduletable);
N2_API n2_module_t* n2_moduletable_peek(n2_moduletable_t* moduletable, int index);
N2_API n2_module_t* n2_moduletable_find(n2_moduletable_t* moduletable, const char* name);
N2_API n2_module_t* n2_moduletable_register(n2_state_t* state, n2_moduletable_t* moduletable, const char* name);

N2_DECLARE_ENUM(n2_modinstance_flag_e);
enum n2_modinstance_flag_e
{
	N2_MODINSTANCE_FLAG_TERMINATED = 1,
};

struct n2_modinstance_t
{
	int module_id_;
	n2_fiber_t* fiber_;// 自分が所属するファイバーを覚えておく
	n2_vartable_t* localvars_;
	int reference_count_;
	size_t flags_;
};

N2_API void n2_modinstance_init(n2_state_t* state, n2_fiber_t* f, n2_module_t* emodule, n2_modinstance_t* instance);
N2_API void n2_modinstance_teardown(n2_state_t* state, n2_modinstance_t* instance);
N2_API void n2_modinstance_incref(n2_state_t* state, n2_modinstance_t* instance);
N2_API void n2_modinstance_decref(n2_state_t* state, n2_modinstance_t* instance);

//=============================================================================
// プリプロセッサ
N2_DECLARE_ENUM(n2_pp_directive_e);
enum n2_pp_directive_e
{
	N2_PP_DIRECTIVE_UNKNOWN = -1,

	N2_PP_DIRECTIVE_ERROR = 0,
	N2_PP_DIRECTIVE_DEFINE,
	N2_PP_DIRECTIVE_UNDEF,
	N2_PP_DIRECTIVE_IF,
	N2_PP_DIRECTIVE_IFDEF,
	N2_PP_DIRECTIVE_IFNDEF,
	N2_PP_DIRECTIVE_ELIF,
	N2_PP_DIRECTIVE_ELSE,
	N2_PP_DIRECTIVE_ENDIF,
	N2_PP_DIRECTIVE_ENUM,
	N2_PP_DIRECTIVE_CONST,
	N2_PP_DIRECTIVE_ADDITION,
	N2_PP_DIRECTIVE_INCLUDE,
	N2_PP_DIRECTIVE_DEFFUNC,
	N2_PP_DIRECTIVE_DEFCFUNC,
	N2_PP_DIRECTIVE_MODULE,
	N2_PP_DIRECTIVE_GLOBAL,
	N2_PP_DIRECTIVE_MODINIT,
	N2_PP_DIRECTIVE_MODTERM,
	N2_PP_DIRECTIVE_MODFUNC,
	N2_PP_DIRECTIVE_MODCFUNC,
	N2_PP_DIRECTIVE_USELIB,
	N2_PP_DIRECTIVE_FUNC,
	N2_PP_DIRECTIVE_CFUNC,

	N2_PP_DIRECTIVE_BOOTOPT,
	N2_PP_DIRECTIVE_CMPOPT,
	N2_PP_DIRECTIVE_PACKOPT,
	N2_PP_DIRECTIVE_PACK,
	N2_PP_DIRECTIVE_EPACK,
	N2_PP_DIRECTIVE_N2PACK,

	N2_MAX_PP_DIRECTIVE
};

N2_API n2_pp_directive_e n2_pp_directive_find(const char* s);

N2_DECLARE_ENUM(n2c_pp_packopt_e);
enum n2c_pp_packopt_e
{
	N2C_PP_PACKOPT_UNKNOWN = -1,
	N2C_PP_PACKOPT_NAME = 0,
	N2C_PP_PACKOPT_TYPE,
	N2C_PP_PACKOPT_XSIZE,
	N2C_PP_PACKOPT_YSIZE,
	N2C_PP_PACKOPT_HIDE,
	N2C_PP_PACKOPT_ORGPATH,
	N2C_PP_PACKOPT_ICON,
	N2C_PP_PACKOPT_VERSION,
	N2C_PP_PACKOPT_MANIFEST,
	N2C_PP_PACKOPT_LANG,
	N2C_PP_PACKOPT_UPX,

	N2C_MAX_PP_PACKOPT
};

N2_API n2c_pp_packopt_e n2c_pp_packopt_find(const char* s);
N2_API const char* n2c_pp_packopt_name(n2c_pp_packopt_e packopt, const char* on_not_found);

enum
{
	N2C_PP_PACKOPT_TYPE_MIN = 0,
	N2C_PP_PACKOPT_TYPE_MAX = 2,
};

typedef struct n2c_pp_packopt_t n2c_pp_packopt_t;
struct n2c_pp_packopt_t
{
	n2_str_t name_;
	int type_;// 0=normal exe, 1=fullscreeen exe, 2=screen saver
	size_t xsize_;
	size_t ysize_;
	n2_bool_t hide_;
	n2_bool_t orgpath_;
	n2_str_t icon_;
	n2_str_t version_;
	n2_str_t manifest_;
	size_t langcode_;// locale id in winapi
	n2_bool_t upx_;
};

N2_API void n2c_pp_packopt_setup(n2_state_t* state, n2c_pp_packopt_t* packopt);
N2_API void n2c_pp_packopt_teardown(n2_state_t* state, n2c_pp_packopt_t* packopt);

typedef struct n2_pp_region_t n2_pp_region_t;
struct n2_pp_region_t
{
	n2_bool_t is_valid_;
	int begin_line_;
	size_t valid_region_count_;
};

N2_DECLARE_TARRAY(n2_pp_region_t, n2_ppregionarray, N2_API);

typedef struct n2_pp_macro_param_t n2_pp_macro_param_t;
struct n2_pp_macro_param_t
{
	n2_str_t default_param_;
};

N2_DECLARE_TARRAY(n2_pp_macro_param_t, n2_ppmacroparamarray, N2_API);

typedef struct n2_pp_macro_arg_t n2_pp_macro_arg_t;
struct n2_pp_macro_arg_t
{
	n2_str_t content_;
};

N2_DECLARE_TARRAY(n2_pp_macro_arg_t, n2_ppmacroargarray, N2_API);

typedef struct n2_pp_macro_t n2_pp_macro_t;
struct n2_pp_macro_t
{
	char* name_;
	n2_str_t replacing_;
	n2_bool_t is_ctype_;
	n2_ppmacroparamarray_t* params_;
};

N2_DECLARE_TARRAY(n2_pp_macro_t, n2_ppmacroarray, N2_API);

typedef struct n2_pp_module_declare_t n2_pp_module_declare_t;
struct n2_pp_module_declare_t
{
	char* name_;
};

N2_DECLARE_TSORTED_ARRAY(n2_pp_module_declare_t, void, char*, n2_ppmoddeclareset, N2_API);

typedef struct n2_pp_func_declare_t n2_pp_func_declare_t;
struct n2_pp_func_declare_t
{
	char* name_;
};

N2_DECLARE_TSORTED_ARRAY(n2_pp_func_declare_t, void, char*, n2_ppfuncdeclareset, N2_API);

typedef struct n2_pp_packfile_t n2_pp_packfile_t;
struct n2_pp_packfile_t
{
	const n2_sourcecode_t* sourcecode_;
	n2_str_t filepath_;
	n2_bool_t epack_;
};

N2_DECLARE_TARRAY(n2_pp_packfile_t, n2_pppackfilearray, N2_API);

typedef struct n2_pp_context_t n2_pp_context_t;
struct n2_pp_context_t
{
	n2_plstrarray_t* searchpaths_;

	n2_ppmacroarray_t* macros_;

	int line_;

	n2_bool_t current_region_valid_;
	size_t valid_region_count_;
	n2_ppregionarray_t* regions_;

	int auto_module_next_;
	n2_valint_t enum_next_;

	n2_ppmoddeclareset_t* mod_decls_;

	n2_sourcefilearray_t* current_sourcefiles_;
	n2_sourcecode_t* current_rootsourcecode_;
	n2_sourcecode_t* current_sourcecode_;
	n2_pp_module_declare_t* current_mod_decl_;
	n2_ppfuncdeclareset_t* staging_func_decls_;

	n2c_pp_packopt_t packopt_;
	n2_pppackfilearray_t* packfiles_;
};

N2_API n2_pp_context_t* n2_pp_context_alloc(n2_state_t* state);
N2_API void n2_pp_context_free(n2_state_t* state, n2_pp_context_t* ppc);

N2_API n2_bool_t n2_pp_context_load_src_file(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* filepath, n2_str_t* dst_resolved_filepath);

N2_API void n2_pp_context_register_default_macros(n2_state_t* state, n2_pp_context_t* ppc);

N2_API n2_bool_t n2_pp_context_preprocess_raw(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, const char* package, const char* src);
N2_API n2_bool_t n2_pp_context_preprocess_root(n2_state_t* state, n2_pp_context_t* ppc, n2_str_t* dst, n2_sourcecode_t* rootsourcecode);

N2_API const n2_pp_macro_t* n2_pp_context_find_macro(n2_pp_context_t* ppc, const char* name);
N2_API n2_bool_t n2_pp_context_register_macro(n2_state_t* state, n2_pp_context_t* ppc, const char* name, const char* replacing);
N2_API n2_bool_t n2_pp_context_erase_macro(n2_state_t* state, n2_pp_context_t* ppc, const char* name);

N2_API void n2_pp_context_clear_staging(n2_state_t* state, n2_pp_context_t* ppc);

//=============================================================================
// 動的ライブラリ
struct n2_uselib_t
{
	char* path_;
	n2_intarray_t func_indices_;
	n2h_dynlib_t* dynlib_;
};

N2_DECLARE_TARRAY(n2_uselib_t, n2_uselibarray, N2_API);

//=============================================================================
// 雑多
N2_DECLARE_ENUM(n2_ease_e);
enum n2_ease_e
{
	N2_EASE_LINEAR = 0,
	N2_EASE_QUAD_IN,
	N2_EASE_QUAD_OUT,
	N2_EASE_QUAD_INOUT,
	N2_EASE_CUBIC_IN,
	N2_EASE_CUBIC_OUT,
	N2_EASE_CUBIC_INOUT,
	N2_EASE_QUARTIC_IN,
	N2_EASE_QUARTIC_OUT,
	N2_EASE_QUARTIC_INOUT,
	N2_EASE_BOUNCE_IN,
	N2_EASE_BOUNCE_OUT,
	N2_EASE_BOUNCE_INOUT,
	N2_EASE_SHAKE_IN,
	N2_EASE_SHAKE_OUT,
	N2_EASE_SHAKE_INOUT,

	N2_MAX_EASE
};

enum
{
	N2_EASE_OPT_LOOP = 4096
};

//=============================================================================
// n2標準機能
typedef union n2s_u8color_t n2s_u8color_t;
union n2s_u8color_t
{
	struct { uint8_t r_; uint8_t g_; uint8_t b_; uint8_t a_; };
	uint8_t e_[4];
};

N2_API n2s_u8color_t n2s_u8color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
N2_API n2s_u8color_t n2s_u8color_clamp(int r, int g, int b, int a);

typedef union n2s_fcolor_t n2s_fcolor_t;
union n2s_fcolor_t
{
	struct { float r_; float g_; float b_; float a_; };
	float e_[4];
};

N2_API n2s_fcolor_t n2s_fcolor(float r, float g, float b, float a);
N2_API n2s_fcolor_t n2s_fcolor_clamp(float r, float g, float b, float a);

N2_API n2s_u8color_t n2s_fcolor_to_u8color(n2s_fcolor_t fcolor);
N2_API n2s_fcolor_t n2s_u8color_to_fcolor(n2s_u8color_t u8color);

N2_API n2s_fcolor_t n2s_hsv_to_fcolor(n2_fvec3_t hsv, float a);
N2_API n2_fvec3_t n2s_fcolor_to_hsv(n2s_fcolor_t fcolor);

typedef struct n2s_vertex_t n2s_vertex_t;
struct n2s_vertex_t
{
	n2_fvec3_t position_;
	n2_fvec2_t uv_;
	n2s_u8color_t color_;
	n2_fvec4_t uv_clamp_;
};

N2_API n2_bool_t n2s_uv_clamp_pixel(n2_fvec2_t* uv0, n2_fvec2_t* uv1, size_t w, size_t h);
N2_API void n2s_vertex_uv_clamp_to(n2s_vertex_t* dst, n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color, n2_fvec2_t uvc0, n2_fvec2_t uvc1);
N2_API void n2s_vertex_to(n2s_vertex_t* dst, n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color);
N2_API n2s_vertex_t n2s_vertex(n2_fvec3_t position, n2_fvec2_t uv, n2s_u8color_t color);
N2_API void n2s_vertex_set_uv_clamp_direct_to(n2s_vertex_t* dst, n2_fvec2_t uv0, n2_fvec2_t uv1);
N2_API void n2s_vertex_set_uv_clamp_pixel(n2s_vertex_t* dst, n2_fvec2_t uv0, n2_fvec2_t uv1, size_t w, size_t h);

N2_DECLARE_TARRAY(n2s_vertex_t, n2s_vertexarray, N2_API);

typedef uint32_t n2s_index_t;

N2_DECLARE_TARRAY(n2s_index_t, n2s_indexarray, N2_API);

N2_DECLARE_ENUM(n2s_samplerfilter_e);
enum n2s_samplerfilter_e
{
	N2S_SAMPLERFILTER_NONE = 0,
	N2S_SAMPLERFILTER_NEAREST,
	N2S_SAMPLERFILTER_BILINEAR,
	N2S_SAMPLERFILTER_TRILINEAR,

	N2S_MAX_SAMPLERFILTER
};

typedef struct n2s_texture_t n2s_texture_t;
struct n2s_texture_t
{
	n2_str_t name_;
	size_t width_;
	size_t height_;
	n2_buffer_t imagebuf_;
	size_t dirty_begin_y_;
	size_t dirty_end_y_;
	n2s_samplerfilter_e samplerfilter_;

	// SDL特有
#if N2_CONFIG_USE_SDL_LIB
	GLuint gl_texture_;
#endif
};

N2_API n2_bool_t n2s_texture_set_samplerfilter(n2_state_t* state, n2s_texture_t* tx, n2s_samplerfilter_e samplerfilter);
N2_API void n2s_texture_dirty_clear(n2s_texture_t* tx);
N2_API void n2s_texture_dirty_all(n2s_texture_t* tx);
N2_API void n2s_texture_dirty_range(n2s_texture_t* tx, size_t begin_y, size_t end_y);
N2_API void n2s_texture_fill_color(n2s_texture_t* tx, n2s_u8color_t color);
N2_API void n2s_texture_render_buffer(n2s_texture_t* tx, const n2_buffer_t* rendertxbuf, size_t rendertxwidth, size_t rendertxheight, int renderx, int rendery, n2s_u8color_t mulcolor);
N2_API void n2s_texture_render(n2s_texture_t* tx, const n2s_texture_t* rendertx, int renderx, int rendery, n2s_u8color_t mulcolor);
N2_API void n2s_texture_copy_buffer(n2s_texture_t* tx, const n2_buffer_t* srctxbuf, size_t srctxwidth, size_t srctxheight, int renderx, int rendery);
N2_API n2_bool_t n2s_texture_submit(n2_state_t* state, n2s_texture_t* tx, n2_bool_t force_submit_all);
N2_API n2_bool_t n2s_texture_resize(n2_state_t* state, n2s_texture_t* tx, size_t width, size_t height, n2_bool_t keep_content);

N2_API n2_bool_t n2s_texture_save_to(n2_state_t* state, n2_buffer_t* dst, const n2s_texture_t* texture, n2_image_file_e imagefile);

typedef struct n2s_texturebuffer_t n2s_texturebuffer_t;
struct n2s_texturebuffer_t
{
	n2s_texture_t texture_;

	// SDL特有
#if N2_CONFIG_USE_SDL_LIB
	GLuint gl_framebuffer_;
#endif
};

N2_API n2_bool_t n2s_texturebuffer_read(n2_state_t* state, n2s_texturebuffer_t* tb);

typedef struct n2s_glyph_t n2s_glyph_t;
struct n2s_glyph_t
{
	n2_codepoint_t codepoint_;
	int glyph_index_;
	size_t bb_x_, bb_y_;
	size_t bb_width_, bb_height_;
	float uv_ltx_, uv_lty_;
	float uv_rbx_, uv_rby_;
	float bake_height_;
	float pixel_offset_x_, pixel_offset_y_;
	float pixel_width_, pixel_height_;
	float pixel_xadvance_;
	float pixel_ascent_;
};

N2_DECLARE_TSORTED_ARRAY(n2s_glyph_t, n2_codepoint_t, n2_codepoint_t, n2s_glyphset, N2_API);

typedef struct n2s_fontdata_t n2s_fontdata_t;
struct n2s_fontdata_t
{
	n2_buffer_t fontbinary_;

	float pixel_scaling_;
	float pixel_ascent_;
	float pixel_descent_;
	float pixel_linegap_;
	float pixel_strict_lineheight_;

#if N2_CONFIG_USE_FONT_LIB
	struct stbtt_fontinfo* fontinfo_;
#endif
};

N2_DECLARE_TARRAY(n2s_fontdata_t, n2s_fontdataarray, N2_API);

// @todo support kerning?
typedef struct n2s_font_t n2s_font_t;
struct n2s_font_t
{
	n2_state_t* birth_state_;// @todo erase this ?
	n2_str_t name_;
	n2_str_t filepath_;

	n2_codepoint_t fallback_codepoint_;
	n2_bool_t ignore_complex_c0_control_codepoints_;
	n2s_glyphset_t* glyphset_;
	n2s_texture_t* texture_;
	n2_buffer_t glyph_staging_alpha_;
	size_t texture_cursor_x_, texture_cursor_y_;
	size_t texture_next_y_;
	size_t bake_padding_;
	float bake_height_;
	float bake_oversample_;
	float pixel_lineheight_;

	n2s_fontdataarray_t* fontdata_;

#if N2_CONFIG_USE_GUI_LIB
	struct nk_user_font* nk_font_;
#endif
};

typedef struct n2s_font_text_callback_param_t n2s_font_text_callback_param_t;
struct n2s_font_text_callback_param_t
{
	n2s_font_t* font_;
	const n2s_glyph_t* glyph_;
	n2_codepoint_t codepoint_;
	n2_codepoint_t prev_codepoint_;
};

typedef void (*n2s_font_text_callback_t)(const n2s_font_text_callback_param_t* param, void* user);

N2_API n2s_font_t* n2s_font_alloc(n2_state_t* state, const char* name, size_t name_size, size_t atlas_width, size_t atlas_height);
N2_API void n2s_font_free(n2_state_t* state, n2s_font_t* font);
N2_API n2_bool_t n2s_font_load_to(n2_state_t* state, n2s_font_t* font, n2_buffer_t* fontbinary, n2_bool_t append);
N2_API void n2s_font_clear(n2_state_t* state, n2s_font_t* font);
N2_API void n2s_font_swap(n2s_font_t* lhs, n2s_font_t* rhs);
N2_API n2_bool_t n2s_font_bake_codepoint(n2_state_t* state, n2s_font_t* font, n2_codepoint_t codepoint, float height/*negative number to use default*/);
N2_API void n2s_font_text(n2_state_t* state, n2s_font_t* font, const char* str, size_t str_length, n2s_font_text_callback_t callback, void* user);
N2_API n2_bool_t n2s_font_text_bb(n2_state_t* state, n2_fvec2_t* dst_bb, n2s_font_t* font, const char* str, size_t str_length, float height, float wrap_width);

N2_DECLARE_ENUM(n2s_font_render_flag_e);
enum n2s_font_render_flag_e
{
	N2S_FONT_RENDER_FLAG_DEFAULT = 0x0,
	N2S_FONT_RENDER_FLAG_ALPHA_BLEND = 0x1,
	N2S_FONT_RENDER_FLAG_VFLIP = 0x2,
};
typedef struct n2s_font_render_config_t n2s_font_render_config_t;
struct n2s_font_render_config_t
{
	const n2s_font_t* font_;
	size_t render_flags_;
	n2_codepoint_t fallback_codepoint_;
	float height_;
	float wrap_width_;
	n2s_u8color_t color_;
	size_t cursor_offsetx_;
	size_t cursor_offsety_;
	n2_buffer_t* staging_alpha_;
};

N2_API void n2s_font_render_config_init(n2s_font_render_config_t* render_config, const n2s_font_t* font, float height, n2_buffer_t* staging_alpha);
N2_API n2_bool_t n2s_font_render_buffer(n2_state_t* state, n2_buffer_t* dst, size_t dst_width, size_t dst_height, const char* str, size_t str_length, const n2s_font_render_config_t* render_config);

N2_DECLARE_TSORTED_ARRAY(n2s_font_t*, void, char, n2s_fontset, N2_API);

typedef struct n2s_text_render_unit_t n2s_text_render_unit_t;
struct n2s_text_render_unit_t
{
	n2_bool_t enable_;
	n2s_u8color_t color_;
	n2_fvec2_t scale_;
	n2_fvec2_t offset_;
	float topskew_;
};

enum
{
	N2S_TEXT_RENDER_FLAG_PIXEL_PERFECT = 0x01,

	N2S_TEXT_RENDER_FLAGS_DEFAULT = N2S_TEXT_RENDER_FLAG_PIXEL_PERFECT
};

N2_DECLARE_ENUM(n2s_gprogram_e);
enum n2s_gprogram_e
{
	N2S_GPROGRAM_2D,
	N2S_GPROGRAM_2D_TRANSCOLOR,
	N2S_GPROGRAM_GUI,

	N2S_MAX_GPROGRAM
};

N2_DECLARE_ENUM(n2s_gprogram_data_e);
enum n2s_gprogram_data_e
{
	N2S_GPROGRAM_DATA_UNKNOWN = -1,
	N2S_GPROGRAM_DATA_INT = 0,
	N2S_GPROGRAM_DATA_IVEC2,
	N2S_GPROGRAM_DATA_IVEC3,
	N2S_GPROGRAM_DATA_IVEC4,
	N2S_GPROGRAM_DATA_UINT,
	N2S_GPROGRAM_DATA_UVEC2,
	N2S_GPROGRAM_DATA_UVEC3,
	N2S_GPROGRAM_DATA_UVEC4,
	N2S_GPROGRAM_DATA_FLOAT,
	N2S_GPROGRAM_DATA_FVEC2,
	N2S_GPROGRAM_DATA_FVEC3,
	N2S_GPROGRAM_DATA_FVEC4,
	N2S_GPROGRAM_DATA_FMAT4,

	N2S_MAX_GPROGRAM_DATA
};

N2_DECLARE_ENUM(n2s_gprogram_uniform_e);
enum n2s_gprogram_uniform_e
{
	N2S_GPROGRAM_UNIFORM_UNKNOWN = -1,
	N2S_GPROGRAM_UNIFORM_TEXTURE = 0,
	N2S_GPROGRAM_UNIFORM_TRANSCOLOR,

	N2S_MAX_GPROGRAM_UNIFORM
};

N2_API n2s_gprogram_uniform_e n2s_gprogram_uniform_find(const char* name, size_t length);
N2_API const char* n2s_gprogram_uniform_name(n2s_gprogram_uniform_e un, const char* on_failed);

typedef struct n2s_gprogram_uniform_data_t n2s_gprogram_uniform_data_t;
struct n2s_gprogram_uniform_data_t
{
	n2s_gprogram_data_e data_type_;
	size_t data_element_num_;
	const void* data_;
};

N2_API void n2s_gprogram_uniform_data_init(n2s_gprogram_uniform_data_t* uniform_data);

N2_DECLARE_ENUM(n2s_gprogram_uniform_block_e);
enum n2s_gprogram_uniform_block_e
{
	N2S_GPROGRAM_UNIFORM_BLOCK_UNKNOWN = -1,
	N2S_GPROGRAM_UNIFORM_BLOCK_DRAWENV = 0,
	N2S_GPROGRAM_UNIFORM_BLOCK_D3ENV,

	N2S_MAX_GPROGRAM_UNIFORM_BLOCK
};

N2_API n2s_gprogram_uniform_block_e n2s_gprogram_uniform_block_find(const char* name, size_t length);
N2_API const char* n2s_gprogram_uniform_block_name(n2s_gprogram_uniform_block_e ubn, const char* on_failed);

typedef struct n2s_guniform_block_drawenv_t n2s_guniform_block_drawenv_t;
struct n2s_guniform_block_drawenv_t
{
	n2_fmat4_t v_mtx_;
	n2_fmat4_t p_mtx_;
	n2_fmat4_t pv_mtx_;
	n2_fvec4_t screen_param_;
};

N2_API void n2s_guniform_block_drawenv_init(n2s_guniform_block_drawenv_t* drawenv);
N2_API void n2s_guniform_block_drawenv_set_screen_param(n2s_guniform_block_drawenv_t* drawenv, size_t width, size_t height);

typedef struct n2s_guniform_block_d3env_t n2s_guniform_block_d3env_t;
struct n2s_guniform_block_d3env_t
{
	// @todo
	n2_fvec4_t color_;
};

N2_DECLARE_ENUM(n2s_gprogram_attribute_e);
enum n2s_gprogram_attribute_e
{
	N2S_GPROGRAM_ATTRIBUTE_UNKNOWN = -1,
	N2S_GPROGRAM_ATTRIBUTE_POSITION = 0,
	N2S_GPROGRAM_ATTRIBUTE_TEXCOORD,
	N2S_GPROGRAM_ATTRIBUTE_COLOR,
	N2S_GPROGRAM_ATTRIBUTE_TEXCOORD_CLAMP,

	N2S_MAX_GPROGRAM_ATTRIBUTE
};

N2_API n2s_gprogram_attribute_e n2s_gprogram_attribute_find(const char* name, size_t length);
N2_API const char* n2s_gprogram_attribute_name(n2s_gprogram_attribute_e attr, const char* on_failed);

typedef struct n2s_gprogram_t n2s_gprogram_t;
struct n2s_gprogram_t
{
	n2_str_t name_;

	n2_str_t last_error_;

#if N2_CONFIG_USE_SDL_LIB
	GLuint gl_vsh_;
	GLuint gl_fsh_;
	GLuint gl_program_;

	GLint gl_ulocation_[N2S_MAX_GPROGRAM_UNIFORM];
	GLint gl_ublocation_[N2S_MAX_GPROGRAM_UNIFORM_BLOCK];
	GLint gl_alocation_[N2S_MAX_GPROGRAM_ATTRIBUTE];
#endif
};

N2_API void n2s_gprogram_init(n2s_gprogram_t* program);
N2_API void n2s_gprogram_teardown(n2_state_t* state, n2s_gprogram_t* program);
N2_API void n2s_gprogram_clear(n2_state_t* state, n2s_gprogram_t* program);
N2_API n2_bool_t n2s_gprogram_load_to(n2_state_t* state, n2s_gprogram_t* program, const char* vsh_src, const char* fsh_src);
N2_API n2_bool_t n2s_gprogram_is_loaded(const n2s_gprogram_t* program);

typedef struct n2s_gprogram_draw_cache_t n2s_gprogram_draw_cache_t;
struct n2s_gprogram_draw_cache_t
{
	size_t u_cached_;
	size_t ub_cached_;
};

N2_API void n2s_gprogram_draw_cache_reset(n2s_gprogram_draw_cache_t* pdc);

N2_DECLARE_ENUM(n2s_renderstate_e);
enum n2s_renderstate_e
{
	N2S_RENDERSTATE_2D_NOBLEND = 0,
	N2S_RENDERSTATE_2D_BLEND_ALPHA,
	N2S_RENDERSTATE_2D_BLEND_ADD,
	N2S_RENDERSTATE_2D_BLEND_SUB,

	N2S_MAX_RENDERSTATE
};

N2_DECLARE_ENUM(n2s_gmode_e);
enum n2s_gmode_e
{
	N2S_GMODE_COPY = 0,
	N2S_GMODE_MEMCOPY,
	N2S_GMODE_COPY_BLACKTRANS,
	N2S_GMODE_BLEND,
	N2S_GMODE_BLEND_COLTRANS,
	N2S_GMODE_BLEND_ADD,
	N2S_GMODE_BLEND_SUB,
	N2S_GMODE_BLEND_RALPHA,

	N2S_MAX_GMODE
};

N2_DECLARE_ENUM(n2s_gfilter_e);
enum n2s_gfilter_e
{
	N2S_GFILTER_NONE = 0,
	N2S_GFILTER_BILINEAR,
	N2S_GFILTER_TRILINEAR,

	N2S_MAX_GFILTER
};

N2_DECLARE_ENUM(n2s_mesopt_e);
enum n2s_mesopt_e
{
	N2S_MESOPT_NOCR = 0,
	N2S_MESOPT_SHADOW,
	N2S_MESOPT_OUTLINE,
	N2S_MESOPT_LIGHT,
	N2S_MESOPT_GMODE,

	N2S_MESOPT_HCENTER = 16,
	N2S_MESOPT_VCENTER,
	N2S_MESOPT_HRIGHT,

	N2S_MAX_MESOPT
};

N2_DECLARE_ENUM(n2s_picmesopt_e);
enum n2s_picmesopt_e
{
	N2S_PICMESOPT_FLAG_ALPHA_BLEND = 0x1,
};

N2_DECLARE_ENUM(n2sc_sysreq_e);
enum n2sc_sysreq_e
{
	N2SC_SYSREQ_CLSMODE = 0,
	N2SC_SYSREQ_CLSCOLOR,
	N2SC_SYSREQ_TIMER,
	N2SC_SYSREQ_PLATFORM,

	N2SC_MAX_SYSREQ
};

N2_DECLARE_ENUM(n2sc_platform_e);
enum n2sc_platform_e
{
	N2SC_PLATFORM_WINDOWS = 0,
	N2SC_PLATFORM_IOS,
	N2SC_PLATFORM_ANDROID,
	N2SC_PLATFORM_WEBGL,
	N2SC_PLATFORM_LINUX,
	N2SC_PLATFORM_RASPBIAN,

	N2SC_MAX_PLATFORM
};

N2_DECLARE_ENUM(n2s_command_e);
enum n2s_command_e
{
	N2S_COMMAND_NONE = 0,
	N2S_COMMAND_DRAW,
	N2S_COMMAND_PROGRAM,
	N2S_COMMAND_RENDERSTATE,
	N2S_COMMAND_SAMPLERFILTER,
	N2S_COMMAND_UNIFORM,
	N2S_COMMAND_UNIFORM_BLOCK,

	N2S_MAX_COMMAND
};

typedef struct n2s_command_draw_t n2s_command_draw_t;
struct n2s_command_draw_t
{
	size_t vertex_count_;
	size_t index_count_;
	const n2s_texture_t* texture_;
};

typedef struct n2s_command_program_t n2s_command_program_t;
struct n2s_command_program_t
{
	n2s_gprogram_e program_;
};

typedef struct n2s_command_renderstate_t n2s_command_renderstate_t;
struct n2s_command_renderstate_t
{
	n2s_renderstate_e renderstate_;
};

typedef struct n2s_command_samplerfilter_t n2s_command_samplerfilter_t;
struct n2s_command_samplerfilter_t
{
	n2s_samplerfilter_e samplerfilter_;
};

typedef struct n2s_command_uniform_t n2s_command_uniform_t;
struct n2s_command_uniform_t
{
	n2s_gprogram_uniform_e uniform_;
	n2s_gprogram_data_e data_type_;
	size_t data_element_num_;
	size_t data_offset_;
};

typedef struct n2s_command_uniform_block_t n2s_command_uniform_block_t;
struct n2s_command_uniform_block_t
{
	n2s_gprogram_uniform_block_e uniform_block_;
	size_t data_size_;
	size_t data_offset_;
};

typedef struct n2s_command_t n2s_command_t;
struct n2s_command_t
{
	n2s_command_e type_;
	union
	{
		n2s_command_draw_t draw_;
		n2s_command_program_t program_;
		n2s_command_renderstate_t renderstate_;
		n2s_command_samplerfilter_t samplerfilter_;
		n2s_command_uniform_t uniform_;
		n2s_command_uniform_block_t uniform_block_;
	};
};

N2_API void n2s_command_draw_to(n2s_command_t* c, size_t vertex, size_t index, const n2s_texture_t* texture);

N2_DECLARE_TARRAY(n2s_command_t, n2s_commandarray, N2_API);

typedef struct n2s_commandbuffer_staging_state_t n2s_commandbuffer_staging_state_t;
struct n2s_commandbuffer_staging_state_t
{
	n2s_command_draw_t draw_;
	int program_;
	int renderstate_;
	int samplerfilter_;

	// n2s 固有
	n2s_u8color_t transcolor_;
};

N2_API void n2s_commandbuffer_staging_state_reset(n2s_commandbuffer_staging_state_t* cbss);

typedef struct n2s_commandbuffer_t n2s_commandbuffer_t;
struct n2s_commandbuffer_t
{
	n2s_vertexarray_t* vertexarray_;
	n2s_indexarray_t* indexarray_;
	n2s_commandarray_t* commandarray_;
	n2_u32array_t* commanddataarray_;

	n2s_commandbuffer_staging_state_t staging_;
};

N2_API n2s_commandbuffer_t* n2s_commandbuffer_alloc(n2_state_t* state, size_t max_command_num, size_t max_vertex_num, size_t max_index_num, size_t max_data_num);
N2_API void n2s_commandbuffer_free(n2_state_t* state, n2s_commandbuffer_t* cb);
N2_API void n2s_commandbuffer_clear(n2_state_t* state, n2s_commandbuffer_t* cb);
N2_API size_t n2s_commandbuffer_command_size(const n2s_commandbuffer_t* cb);
N2_API size_t n2s_commandbuffer_vertex_size(const n2s_commandbuffer_t* cb);
N2_API size_t n2s_commandbuffer_index_size(const n2s_commandbuffer_t* cb);
N2_API n2s_command_t* n2s_commandbuffer_add_command(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num);
N2_API n2_bool_t n2s_commandbuffer_flush_staging(n2_state_t* state, n2s_commandbuffer_t* cb);
N2_API n2_bool_t n2s_commandbuffer_add_command_draw(n2_state_t* state, n2s_commandbuffer_t* cb, size_t vertex_num, size_t index_num);
N2_API n2_bool_t n2s_commandbuffer_add_command_program(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_e program);
N2_API n2_bool_t n2s_commandbuffer_add_command_renderstate(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_renderstate_e renderstate);
N2_API n2s_vertex_t* n2s_commandbuffer_alloc_vertex(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num);
N2_API n2s_index_t* n2s_commandbuffer_alloc_index(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num);
N2_API uint32_t* n2s_commandbuffer_alloc_commanddata(n2_state_t* state, n2s_commandbuffer_t* cb, size_t num);
N2_API size_t n2s_commandbuffer_add_commanddata(n2_state_t* state, n2s_commandbuffer_t* cb, const void* data, size_t bytesize);
N2_API n2_bool_t n2s_commandbuffer_add_uniform(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_uniform_e u, n2s_gprogram_data_e data_type, size_t element_num, const void* data, size_t data_size);

N2_API n2_bool_t n2s_commandbuffer_set_program(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_gprogram_e program);
N2_API n2_bool_t n2s_commandbuffer_set_renderstate(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_renderstate_e renderstate);
N2_API n2_bool_t n2s_commandbuffer_set_texture(n2_state_t* state, n2s_commandbuffer_t* cb, const n2s_texture_t* texture);
N2_API n2_bool_t n2s_commandbuffer_set_transcolor(n2_state_t* state, n2s_commandbuffer_t* cb, n2s_u8color_t transcolor);

N2_API void n2s_commandbuffer_triangle_textured_colored(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, const n2s_texture_t* texture, n2_fvec2_t uv0, n2_fvec2_t uv1, n2_fvec2_t uv2, n2s_u8color_t c0, n2s_u8color_t c1, n2s_u8color_t c2);
N2_API void n2s_commandbuffer_triangle_textured(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, const n2s_texture_t* texture, n2_fvec2_t uv0, n2_fvec2_t uv1, n2_fvec2_t uv2, n2s_u8color_t color);
N2_API void n2s_commandbuffer_triangle_colored(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, n2s_u8color_t c0, n2s_u8color_t c1, n2s_u8color_t c2);
N2_API void n2s_commandbuffer_triangle(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t v0, n2_fvec3_t v1, n2_fvec3_t v2, n2s_u8color_t color);
N2_API void n2s_commandbuffer_line(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t start, n2_fvec3_t end, n2s_u8color_t color, float thickness);
N2_API void n2s_commandbuffer_rect(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t left_top, n2_fvec3_t right_bottom, n2s_u8color_t color);
//N2_API void n2s_commandbuffer_roundrect_ex(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, float rad, float rounding, size_t rounding_corners, size_t rounding_division);
N2_API void n2s_commandbuffer_rect_textured_rot(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, const n2s_texture_t* texture, n2_fvec2_t left_top_uv, n2_fvec2_t right_bottom_uv, float rad, size_t w, size_t h);
N2_API void n2s_commandbuffer_rect_textured_rotskew(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t position, n2_fvec2_t pivot, n2_fvec2_t scale, n2s_u8color_t color, const n2s_texture_t* texture, n2_fvec2_t left_top_uv, n2_fvec2_t right_bottom_uv, float rad, n2_fvec2_t topskew, n2_fvec2_t bottomskew, size_t w, size_t h);
N2_API void n2s_commandbuffer_circle_wire(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t center, n2_fvec2_t scale, n2s_u8color_t color, float thickness, size_t div);
N2_API void n2s_commandbuffer_circle(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t center, n2_fvec2_t scale, n2s_u8color_t color, size_t div);

N2_API n2_bool_t n2s_commandbuffer_text_units(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, const n2s_text_render_unit_t* units, size_t unit_num, float wrap_width, size_t flags, n2_fvec2_t* dst_bb);
N2_API n2_bool_t n2s_commandbuffer_text(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, n2s_u8color_t color, float wrap_width, size_t flags, n2_fvec2_t* dst_bb);
N2_API n2_bool_t n2s_commandbuffer_text_ex(n2_state_t* state, n2s_commandbuffer_t* cb, n2_fvec3_t begin, n2s_font_t* font, const char* str, size_t str_length, float height, n2s_u8color_t color, float wrap_width, size_t flags, n2_fvec2_t* dst_bb, float topskew, n2_bool_t dropshadow, n2s_u8color_t dscolor, n2_fvec2_t dsscale, n2_fvec2_t dsoffset, n2_bool_t outline, n2s_u8color_t olcolor, n2_fvec2_t olscale, n2_fvec2_t oloffset);

typedef struct n2s_commandbuffer_draw_cache_t n2s_commandbuffer_draw_cache_t;
struct n2s_commandbuffer_draw_cache_t
{
	const n2s_guniform_block_drawenv_t* drawenv_;
	const n2s_guniform_block_d3env_t* d3env_;

	int program_;
	const n2s_texture_t* texture_;
	int renderstate_;
	int samplerfilter_;
	n2s_gprogram_uniform_data_t uniforms_[N2S_MAX_GPROGRAM_UNIFORM];
	n2s_gprogram_draw_cache_t program_cache_[N2S_MAX_GPROGRAM];

#if N2_CONFIG_USE_SDL_LIB
	GLuint use_vao_;
	GLuint use_vbo_;
	GLuint use_ebo_;
	GLuint use_ubo_[N2S_MAX_GPROGRAM_UNIFORM_BLOCK];
#endif
};

N2_API void n2s_commandbuffer_draw_cache_init(n2s_commandbuffer_draw_cache_t* cbdc);

N2_DECLARE_ENUM(n2s_widget_e);
enum n2s_widget_e
{
	N2S_WIDGET_BUTTON = 0,
	N2S_WIDGET_CHECKBOX,
	N2S_WIDGET_INPUT,
	N2S_WIDGET_TEXTBOX,
	//N2S_WIDGET_COMBOBOX,// @todo

	N2S_MAX_WIDGET
};

typedef struct n2s_widget_t n2s_widget_t;
struct n2s_widget_t
{
	size_t id_;
	n2s_widget_e type_;
	n2_fvec2_t position_;
	n2_fvec2_t size_;
	n2_str_t label_;
	n2_bool_t enable_;
	size_t value_dirty_count_;
	n2_valint_t ivalue_;
	n2_valstr_t strvalue_;
	n2_vallabel_t lvalue_;
	n2_bool_t lgosub_;
	n2_variable_t* capture_;
	int capture_aptr_;
};

N2_API void n2s_widget_init(n2s_widget_t* widget);
N2_API void n2s_widget_teardown(n2_state_t* state, n2s_widget_t* widget);

N2_DECLARE_TSORTED_ARRAY(n2s_widget_t, void, size_t, n2s_widgetset, N2_API);

N2_DECLARE_ENUM(n2s_special_key_e);
enum n2s_special_key_e
{
	N2S_SPECIAL_KEY_SHIFT = 0,
	N2S_SPECIAL_KEY_CTRL,
	N2S_SPECIAL_KEY_ALT,
	N2S_SPECIAL_KEY_UNDO,
	N2S_SPECIAL_KEY_REDO,
	N2S_SPECIAL_KEY_COPY,
	N2S_SPECIAL_KEY_CUT,
	N2S_SPECIAL_KEY_PASTE,

	N2S_MAX_SPECIAL_KEY
};

N2_DECLARE_ENUM(n2s_mouse_button_e);
enum n2s_mouse_button_e
{
	N2S_MOUSE_BUTTON_LEFT = 0,
	N2S_MOUSE_BUTTON_RIGHT,
	N2S_MOUSE_BUTTON_MIDDLE,

	N2S_MAX_MOUSE_BUTTON
};

N2_DECLARE_ENUM(n2s_window_event_e);
enum n2s_window_event_e
{
	N2S_WINDOW_EVENT_UNKNOWN = -1,
	N2S_WINDOW_EVENT_KEY = 0,
	N2S_WINDOW_EVENT_SPECIALKEY,
	N2S_WINDOW_EVENT_MOUSEBUTTON,

	N2S_MAX_WINDOW_EVENT
};

typedef union n2s_window_event_content_t n2s_window_event_content_t;
union n2s_window_event_content_t
{
	struct
	{
		int key_;
		n2_bool_t is_down_;
	} key_;

	struct
	{
		n2s_special_key_e key_;
		n2_bool_t is_down_;
	} specialkey_;

	struct
	{
		n2s_mouse_button_e button_;
		n2_bool_t is_down_;
		n2_bool_t is_dclick_;
		n2_fvec2_t position_;
	} mousebutton_;
};

typedef struct n2s_window_event_t n2s_window_event_t;
struct n2s_window_event_t
{
	n2s_window_event_e type_;
	n2s_window_event_content_t content_;
};

N2_DECLARE_TARRAY(n2s_window_event_t, n2s_windoweventarray, N2_API);

N2_DECLARE_ENUM(n2s_window_e);
enum n2s_window_e
{
	N2S_WINDOW_SCREEN = 0,
	N2S_WINDOW_OFFSCREEN,

	N2S_MAX_WINDOW
};

enum
{
	// 実験的な値で、まあ使われないだろう…というサイズ
	// これ以外の値を特殊な用途に使う可能性がある
	N2S_WINDOW_SIZE_MIN = 8,
	N2S_WINDOW_SIZE_MAX = 16384,

	// フォント描画スタイル
	N2S_WINDOW_DRAW_FONT_STYLE_ITALIC = 0x01,
};

typedef struct n2s_window_t n2s_window_t;
struct n2s_window_t
{
	n2s_window_e type_;

	n2_str_t name_;
	n2_str_t title_;

	size_t width_;
	size_t height_;

	double dpiscale_x_;
	double dpiscale_y_;

	n2_bool_t redraw_;

	n2_valint_t mousex_;
	n2_valint_t mousey_;
	n2_valint_t prev_mousex_;
	n2_valint_t prev_mousey_;
	n2_valint_t mousew_;
	size_t mousebuttons_;

	uint8_t ginfo_r_;
	uint8_t ginfo_g_;
	uint8_t ginfo_b_;
	uint8_t ginfo_a_;

	uint8_t ginfo_mulr_;
	uint8_t ginfo_mulg_;
	uint8_t ginfo_mulb_;

	uint8_t objcolor_r_;
	uint8_t objcolor_g_;
	uint8_t objcolor_b_;

	n2_valint_t posx_;
	n2_valint_t posy_;

	n2_valint_t objx_;
	n2_valint_t objy_;
	n2_valint_t objminheight_;

	n2_valint_t mesx_;
	n2_valint_t mesy_;

	n2s_gmode_e gmode_;
	n2s_gfilter_e gfilter_;
	n2_valint_t gmode_copy_width_;
	n2_valint_t gmode_copy_height_;

	n2s_texturebuffer_t* texturebuffer_;
	n2s_texturebuffer_t* drawcachebuffer_;

	n2s_windoweventarray_t* events_;
	n2_str_t textinput_;

	n2s_font_t* draw_font_;
	float draw_font_height_;
	size_t draw_font_style_;

	size_t celdiv_sizex_;
	size_t celdiv_sizey_;
	n2_fvec2_t cel_offset_;

	n2s_widgetset_t* widgets_;
	size_t next_widget_id_;

	n2_valint_t hwnd_;
	n2_valint_t hdc_;
	n2_valint_t hinstance_;

	// SDL特有
#if N2_CONFIG_USE_SDL_LIB
	SDL_Window* window_;
	void* gl_context_;
	GLint gl_framebuffer_;
#if N2I_ENABLE_SDL_RENDERER
	SDL_Renderer* renderer_;
#endif
#endif

#if N2_CONFIG_USE_GUI_LIB
	struct nk_context* nk_context_;
	struct nk_buffer* nk_cmd_buf_;
#endif
};

N2_DECLARE_TARRAY(n2s_window_t*, n2s_windowarray, N2_API);

typedef struct n2s_environment_spec_t n2s_environment_spec_t;
struct n2s_environment_spec_t
{
	size_t max_texture_width_;
	size_t max_texture_height_;
};

typedef struct n2s_environment_t n2s_environment_t;
struct n2s_environment_t
{
	n2s_environment_spec_t environment_spec_;

	n2s_gprogram_t gprograms_[N2S_MAX_GPROGRAM];

	n2_bool_t is_quit_requested_;
	uint64_t last_async_time_;

	n2_valfloat_t ginfo_accx_;
	n2_valfloat_t ginfo_accy_;
	n2_valfloat_t ginfo_accz_;

	int selected_window_index_;
	n2s_windowarray_t* windows_;

	n2s_commandbuffer_t* commandbuffer_;
	n2s_commandbuffer_t* syscommandbuffer_;

	n2s_font_t* default_font_;
	n2s_fontset_t* fontset_;
	size_t font_atlas_width_;
	size_t font_atlas_height_;

	uint32_t stick_last_;

	n2_valint_t imgunpackw_;
	n2_valint_t imgunpackh_;

	// SDL特有
#if N2_CONFIG_USE_SDL_LIB
	void* gl_context_;

	GLuint gl_cb_vbo_;
	GLuint gl_cb_vao_;
	GLuint gl_cb_ebo_;
	GLuint gl_cb_ubo_[N2S_MAX_GPROGRAM_UNIFORM_BLOCK];

	GLuint gl_gui_vbo_;
	GLuint gl_gui_vao_;
	GLuint gl_gui_ebo_;
	GLuint gl_gui_ubo_[N2S_MAX_GPROGRAM_UNIFORM_BLOCK];
	n2_buffer_t gui_cmd_buf_;
	n2_buffer_t gui_vbo_buf_;
	n2_buffer_t gui_ebo_buf_;

	n2s_texture_t* white_texture_;
	n2s_texture_t* black_texture_;
	n2s_texture_t* zero_texture_;
#endif

	// インスペクタ
#if N2_CONFIG_USE_INSPECTOR
	n2s_window_t* inspector_;
#endif
};

//=============================================================================
// 実行環境

// 呼び出し側
N2_DECLARE_ENUM(n2_caller_e);
enum n2_caller_e
{
	N2_CALLER_EXTERNAL = 0,
	N2_CALLER_GOSUB,
	N2_CALLER_COMMAND,
	N2_CALLER_FUNCTION,
	N2_CALLER_SYSVAR_EX,

	N2_MAX_CALLER
};

// 関数呼び出し起点毎の情報
typedef struct n2_callframe_t n2_callframe_t;
struct n2_callframe_t
{
	n2_caller_e caller_;
	n2_pc_t caller_pc_;
	const n2_func_t* caller_function_;
	const n2_label_t* caller_label_;
	n2_pc_t next_pc_;
	size_t shortframe_cursor_;
	size_t csflags_;
	int base_;
	int arg_num_;
	int original_arg_num_;
	n2_vararray_t* local_vars_;
#if N2_CONFIG_USE_PROFILING
	n2_debugvarpool_t* debugvarpool_;
	n2_debugvariable_t* debugvarroot_;
	n2_debugvararray_t* debugvarargs_;
#endif
#if N2_CONFIG_USE_PROFILING
	uint64_t call_timestamp_;
#endif
};

N2_DECLARE_TARRAY(n2_callframe_t, n2_callframearray, N2_API);

// repeat-loop/switch-swend毎の情報
N2_DECLARE_ENUM(n2_shortframe_e);
enum n2_shortframe_e
{
	N2_SHORTFRAME_LOOP,// repeat-loop
	N2_SHORTFRAME_SWITCH,// switch-swend

	N2_MAX_SHORTFRAME
};

typedef union n2_shortframe_content_t n2_shortframe_content_t;
union n2_shortframe_content_t
{
	struct
	{
		n2_valint_t counter_;
		n2_valint_t max_;
		n2_valint_t cnt_;
		n2_variable_t* foreach_capture_;
	} loop_;

	struct
	{
		n2_bool_t case_hit_;
	} switch_;
};

typedef struct n2_shortframe_t n2_shortframe_t;
struct n2_shortframe_t
{
	n2_shortframe_e type_;
	n2_pc_t start_pc_;
	n2_pc_t end_pc_;
	n2_shortframe_content_t content_;
};

N2_DECLARE_TARRAY(n2_shortframe_t, n2_shortframearray, N2_API);

N2_API n2_shortframe_t* n2_shortframearray_find_last_typed(n2_shortframearray_t* shortframes, n2_shortframe_e type);
N2_API size_t n2_shortframearray_pop_to(n2_state_t* state, n2_shortframearray_t* shortframes, n2_shortframe_t* sf);

// 実行媒体（ファイバー）のステータス
N2_DECLARE_ENUM(n2_fiber_state_e);
enum n2_fiber_state_e
{
	N2_FIBER_STATE_INITIALIZED,
	N2_FIBER_STATE_YIELD,
	N2_FIBER_STATE_YIELD_AWAIT,
	N2_FIBER_STATE_RUNNING,
	N2_FIBER_STATE_STOPPED,
	N2_FIBER_STATE_END,
	N2_FIBER_STATE_FINISHED,
	N2_FIBER_STATE_ERROR,

	N2_MAX_FIBER_STATE
};

// 実行媒体の呼び出し情報
N2_DECLARE_ENUM(n2_callstateflag_e);
enum n2_callstateflag_e
{
	N2_CALLSTATEFLAG_QUAL_GOSUB = 0x01,
};

typedef struct n2_callstate_t n2_callstate_t;
struct n2_callstate_t
{
	size_t flags_;
	int base_;
	int arg_num_;
	int original_arg_num_;
	const n2_func_t* func_;
	const n2_label_t* label_;
#if N2_CONFIG_USE_DEBUGGING
	n2_debugvararray_t* debugvarargs_;
#endif
};

// 保護フレーム（低レイヤー例外）
typedef struct n2_protectframe_t n2_protectframe_t;
struct n2_protectframe_t
{
	jmp_buf jmp_;
	n2_protectframe_t* previous_;
};

#define N2_PROTECT_ENTER(varname, f) \
	n2_protectframe_t varname; \
	do { \
		varname.previous_ = f->protectframe_; \
		f->protectframe_ = &varname; \
	} while (0)

#define N2_PROTECT_DISPATCH(varname, f) \
	setjmp(varname.jmp_)

#define N2_PROTECT_LEAVE(varname, f) \
	do { \
		f->protectframe_ = f->protectframe_->previous_; \
	} while (0)

// 実行媒体（ファイバー）の情報
struct n2_fiber_t
{
	// ID
	int id_;

	// 名前
	n2_str_t name_;

	// 状態
	n2_fiber_state_e fiber_state_;

	// 終了コード
	int exit_code_;

	// エラーある？
	n2_bool_t has_error_;

	// AST評価時
	n2_ast_evaluate_context_t* ast_evaluate_context_;

	// YIELD_AWAITの時の待ち時間
	n2_valint_t yield_await_duration_ms_;

	// 環境（参照のみ）
	n2_environment_t* environment_;

	// スタック
	n2_valuearray_t* values_;

	// 呼び出し状態
	n2_callstate_t callstate_;

	// プログラムカウンター（インストラクションポインタ）
	n2_pc_t pc_;
	n2_pc_t op_pc_;

	// フレーム
	n2_protectframe_t* protectframe_;
	n2_callframearray_t* callframes_;
	n2_shortframearray_t* shortframes_;

	// ローカル変数
	n2_vararray_t* curscope_local_vars_;

	// notesel
	n2_variable_t* notevar_;
	int noteaptr_;

	// sysvar
	n2_valint_t cnt_;
	n2_valint_t stat_;
	n2_valfloat_t refdval_;
	n2_valstr_t* refstr_;
	n2_valint_t strsize_;
	n2_valint_t looplev_;

	// sortの元インデックスなど
	n2_intarray_t* sort_indices_;
	n2_intarray_t* sort_fill_;

	// easing
	n2_valint_t ease_type_;
	n2_valfloat_t ease_start_;
	n2_valfloat_t ease_end_;

#if N2_CONFIG_USE_DEBUGGING
	// デバッグ用
	n2_debugint_e debugint_type_;
	n2_debugint_granularity_e debugint_granularity_;
	int debugint_granule_size_;
	int debugint_call_depth_;

	n2_debugvarpool_t* debugvarpool_;
	n2_debugvariable_t* debugvarroot_;
	n2_debugvariable_t* debugvarsysvar_;
	n2_debugvariable_t* debugvarsysvarelements_[N2_MAX_SYSVAR];
#endif
};

N2_API n2_fiber_t* n2_fiber_alloc(n2_state_t* state, n2_environment_t* e, int id, const char* name, size_t name_length);
N2_API void n2_fiber_free(n2_state_t* state, n2_fiber_t* fiber);

// 終了したか？
N2_API n2_bool_t n2_fiber_is_finished(const n2_fiber_t* fiber);

// 実行環境の情報
struct n2_environment_t
{
	// パーサー（ASTのトークン列を持つので必要）
	n2_parserarray_t* parsers_;

	// AST
	n2_astarray_t* asts_;

	// コードイメージ
	n2_codeimage_t* codeimage_;

	// 変数テーブル
	n2_vartable_t* vartable_;

	// 関数テーブル
	n2_functable_t* functable_;

	// ラベル
	n2_labelarray_t* labels_;

	// モジュール
	n2_moduletable_t* moduletable_;

	// 動的ライブラリ
	n2_bool_t uselibs_dirty_;
	n2_uselibarray_t* uselibs_;

	// 拡張システム変数
	n2_sysvarexarray_t* sysvar_ex_;

	// 最終エラー
	n2_bool_t load_error_;
	n2_str_t* last_error_;

	// コア機能がバインドされているか
	n2_bool_t is_core_bounded_;

	// コア機能のモジュール
	int module_core_modclass_id_;

	// 基本機能がバインドされているか
	n2_bool_t is_basics_bounded_;

	// コンソール機能がバインドされているか
	n2_bool_t is_consoles_bounded_;

	// n2標準機能がバインドされているか
	n2_bool_t is_standards_bounded_;

	// n2標準機能
	n2s_environment_t* standard_environment_;

	// ランダム
	n2h_random_t random_;

	// ログ
	n2_plstrarray_t* messagelogs_;

#if N2_CONFIG_USE_DEBUGGING
	// デバッガーフック
	n2_debughook_t* debughook_;

	// プール
	n2_debugvarpool_t* debugvarpool_;

	// ルート
	n2_debugvariable_t* debugvarroot_;
#endif

#if N2_CONFIG_USE_PROFILING
	// プロファイリング
	n2_bool_t is_profiling_;
#endif
};

N2_API n2_environment_t* n2_environment_alloc(n2_state_t* state);
N2_API void n2_environment_free(n2_state_t* state, n2_environment_t* e);

N2_API n2_bool_t n2_environment_load_str(n2_state_t* state, n2_pp_context_t* ppc, n2_environment_t* e, const char* package, const char* script, size_t script_size, const char* src_filepath_hint);

N2_API n2_debughook_t* n2_environment_get_debughook(n2_environment_t* e);
N2_API n2_debughook_t* n2_environment_attach_debughook(n2_state_t* state, n2_environment_t* e);
N2_API n2_bool_t n2_environment_detach_debughook(n2_state_t* state, n2_environment_t* e);

//=============================================================================
// 即席実行
struct n2_ast_evaluate_context_t
{
	n2_str_t error_;
};

N2_API void n2_ast_evaluate_context_init(n2_ast_evaluate_context_t* context);
N2_API void n2_ast_evaluate_context_teardown(n2_state_t* state, n2_ast_evaluate_context_t* context);

N2_API n2_value_t* n2_ast_evaluate_immediate(n2_state_t* state, n2_ast_evaluate_context_t* context, const n2_ast_node_t* ast);
N2_API n2_bool_t n2_ast_node_evaluate(n2_state_t* state, n2_fiber_t* f, const n2_ast_node_t* node);

//=============================================================================
// 全体（ステート）

// コンフィグ
typedef struct n2_state_config_t n2_state_config_t;
struct n2_state_config_t
{
	// アロケータ
	n2_allocator_t allocator_;
	n2_allocator_close_func_t allocator_close_;

	// printコンフィグ
	n2_print_func_t print_;
	n2_print_log_func_t print_log_;
	n2_print_error_func_t print_error_;
	void* print_user_;

	// ファイル入出力コンフィグ
	n2_fileread_func_t file_read_;
	n2_filewrite_func_t file_write_;
	void* file_user_;

	size_t file_read_tmp_buffer_size_;// = N2_DEFAULT_FILE_READ_TMP_BUFFER_SIZE

	// Z圧縮コンフィグ
	size_t z_decompress_tmp_buffer_size_;// = N2_DEFAULT_Z_DECOMP_READ_TMP_BUFFER_SIZE

	// エラー関数
	n2_bool_t error_is_print_;
	n2_bool_t error_print_callstack_;
	n2_error_func_t error_;
	void* error_user_;

	// 保護フレーム外アボート
	n2_bool_t abort_on_unprotected_error_;// = N2_TRUE

	// 値のキャッシュ数
	size_t value_cache_size_;// = N2_DEFAULT_VALUE_CACHE_NUM @todo これなくす

	// 変数の最小確保数
	size_t variable_element_min_num_;// = N2_DEFAULT_VARIABLE_ELEMENT_MIN_NUM
	size_t variable_str_element_min_num_;// = N2_DEFAULT_VARIABLE_STR_ELEMENT_MIN_NUM

	// 変数の最小確保粒度
	size_t variable_granule_size_;// = N2_DEFAULT_VARIABLE_GRANULE_SIZE

	// 最大ネスト数（ショートフレーム）
	size_t max_shortframe_nest_;// = N2_DEFAULT_MAX_SHORTFRAME_NEST

	// 最大関数ネスト数
	size_t max_call_nest_;// = N2_DEFAULT_MAX_CALL_NEST

	// デバッグ情報
	n2_bool_t generate_opcodeflags_;// = N2_FALSE
	n2_bool_t generate_codelines_;// = N2_TRUE
	n2_bool_t generate_debugvars_;// = N2_FALSE
	n2_bool_t enable_graphics_assert_;// = N2_FALSE

	// logmesなどのメッセージログ最大数
	size_t max_message_log_;// = N2_DEFAULT_MESSAGE_LOG_MAX

	// __hspver__, hspverとして定義する数
	n2_valint_t reference_hspver_;// = N2_DEFAULT_REFERRENCE_HSPVER: negative number to not define __hspver__

	// __hsp30__定義する？
	n2_bool_t define_hsp30_;// = N2_TRUE

	// __debug__定義する？
	n2_bool_t define_debug_;// = N2_FALSE

	// プリプロセスのinclude_pushエラー
	n2_bool_t enable_error_include_push_;// = N2_TRUE

	// スクリプトUTF16の自動デコード
	n2_bool_t enable_script_auto_decode_utf16_;// = N2_TRUE

	// スクリプトcp932の自動デコード
	n2_bool_t enable_script_auto_decode_cp932_;// = N2_TRUE

	// SDLの初期化をSubSystemで行うか
	n2_bool_t standard_init_sdl_with_subsystem_;// = N2_FALSE

	// n2s_window_tの（最大）数
	size_t standard_window_num_;// = N2S_DEFAULT_WINDOW_NUM

	// awaitのステップ
	n2_valint_t standard_await_step_duration_;// = N2S_DEFAULT_AWAIT_STEP_DURATION

	// awaitの早期解除
	n2_valint_t standard_await_exit_margin_;// = N2S_DEFAULT_AWAIT_EXIT_MARGIN

	// ウィンドウのデフォルトサイズ
	size_t standard_window_default_width_;// = N2S_DEFAULT_WINDOW_WIDTH
	size_t standard_window_default_height_;// = N2S_DEFAULT_WINDOW_HEIGHT

	// ウィンドウのデフォルトタイトル
	const char* standard_window_default_title_;

	// スタートアップウィンドウのサイズ
	size_t standard_startup_window_width_;// = standard_window_default_width_
	size_t standard_startup_window_height_;// = standard_window_default_height_

	// スタートアップウィンドウのデフォルトタイトル
	const char* standard_startup_window_title_;// = standard_window_default_title_

	// スタートアップウィンドウのフラグ
	n2_bool_t standard_statup_window_shown_;// = N2_FALSE

	// ウィンドウのリサイズワークアラウンド
	n2_bool_t standard_window_resize_on_creation_workaround_;// = N2_TRUE

	// コマンドバッファ
	size_t standard_vertex_num_;// = N2S_DEFAULT_STANDARD_VERTEX_NUM
	size_t standard_index_num_;// = N2S_DEFAULT_STANDARD_INDEX_NUM
	size_t standard_command_num_;// = N2S_DEFAULT_STANDARD_COMMAND_NUM
	size_t standard_command_data_num_;// = N2S_DEFAULT_STANDARD_COMMAND_DATA_NUM

	// GUI
	size_t standard_gui_vertex_num_;// = N2S_DEFAULT_STANDARD_GUI_VERTEX_NUM
	size_t standard_gui_index_num_;// = N2S_DEFAULT_STANDARD_GUI_INDEX_NUM
	size_t standard_gui_vertex_expand_step_;// = N2S_DEFAULT_STANDARD_GUI_VERTEX_EXSTEP
	size_t standard_gui_index_expand_step_;// = N2S_DEFAULT_STANDARD_GUI_INDEX_EXSTEP

	// フォント
	n2_codepoint_t standard_font_fallback_codepoint_;// = N2S_DEFAULT_FONT_FALLBACK_CODEPOINT
	size_t standard_font_atlas_width_;// = N2S_DEFAULT_FONT_ATLAS_WIDTH
	size_t standard_font_atlas_height_;// = N2S_DEFAULT_FONT_ATLAS_HEIGHT
	float standard_font_default_bake_height_;// = N2S_DEFAULT_FONT_BAKE_HEIGHT
	float standard_font_default_draw_height_;// = N2S_DEFAULT_FONT_DRAW_HEIGHT
	n2_bool_t standard_font_draw_pixel_perfect_;// = N2_TRUE

	// ウィジェット
	size_t standard_widget_input_default_max_buffer_size_;// = N2S_DEFAULT_WIDGET_INPUT_MAX_BUFFER_SIZE

	// インスペクタ
	n2_bool_t standard_use_inspector_;// = N2_FALSE

	// ユーザーポインタ
	void* user_;
};

enum
{
	N2_STATE_CONFIG_FLAG_DEFAULT = 0x0,

	N2_STATE_CONFIG_FLAG_NO_RPMALLOC = 0x1,
};

// コンフィグ初期化
N2_API void n2_state_config_init(n2_state_config_t* dst_config);
N2_API void n2_state_config_init_ex(n2_state_config_t* dst_config, size_t flags);

// 全データ
struct n2_state_t
{
	// コンフィグ
	n2_state_config_t config_;

	// 値キャッシュ
	n2_value_t** value_cache_;
	size_t value_cache_left_;

	// プリプロセッサ
	n2_pp_context_t* pp_context_;

	// 実行環境
	n2_environment_t* environment_;

	// ファイバーID
	int next_fiber_id_;

	// メインとなるファイバー
	n2_fiber_t* main_fiber_;

	// ファイルシステム
	n2h_filesystem_t* filesystem_;
	n2h_filesystem_t* filesystem_system_;

	// 内部用途
	void* internal_user_;
};

// ステート初期化
N2_API n2_state_t* n2_state_alloc(const n2_state_config_t* config);

// ステート開放
N2_API void n2_state_free(n2_state_t* state);

// 基本機能を全てバインド
N2_API void n2_state_bind_basics(n2_state_t* state);

// コンソール機能を全てバインド
N2_API void n2_state_bind_consoles(n2_state_t* state);

// 標準機能を全てバインド
N2_API void n2_state_bind_standards(n2_state_t* state);

// 読み込み
N2_API n2_bool_t n2_state_load_str(n2_state_t* state, const char* package, const char* script, size_t script_size, const char* src_filepath_hint);
N2_API n2_bool_t n2_state_load_file(n2_state_t* state, const char* src_filepath);

// ファイバー検索
N2_API n2_fiber_t* n2_state_find_fiber(n2_state_t* state, int fiber_id);

// ファイバー実行
N2_API n2_bool_t n2_state_execute_fiber(n2_state_t* state, n2_fiber_t* f);

// 実行
N2_API n2_bool_t n2_state_execute(n2_state_t* state);

// ループ実行（外部実行用）
N2_API n2_bool_t n2_state_loop_frame(n2_state_t* state);

// 終了する？
N2_API n2_bool_t n2_state_is_quit_requested(const n2_state_t* state);

// ファイルシステム
N2_API void n2_state_set_filesystem(n2_state_t* state, n2h_filesystem_t* fs);
N2_API n2h_filesystem_t* n2_state_get_filesystem(n2_state_t* state);

enum
{
	N2_STATE_FSFLAG_USE_PRIMARY_FS = 0x01,
	N2_STATE_FSFLAG_USE_SYSTEM_FS = 0x02,
	N2_STATE_FSFLAG_DEFAULT = (N2_STATE_FSFLAG_USE_PRIMARY_FS | N2_STATE_FSFLAG_USE_SYSTEM_FS)
};
N2_API n2_bool_t n2_state_fs_load(n2_state_t* state, n2_buffer_t* dst, size_t fsflags, const char* filepath, n2_bool_t is_binary, size_t readsize, size_t readoffset);
N2_API n2_bool_t n2_state_fs_load_str(n2_state_t* state, n2_str_t* dst, size_t fsflags, const char* filepath, size_t readsize, size_t readoffset);
N2_API n2_bool_t n2_state_fs_save(n2_state_t* state, size_t* dst_writtensize, size_t fsflags, const char* filepath, n2_bool_t is_binary, const void* writedata, size_t writesize, size_t writeoffset);

// エクスポート
N2_API n2_bool_t n2_state_export_as_script(n2_state_t* state, n2_str_t* dst);

//=============================================================================
// 外部用
N2_API n2_bool_t n2e_register_func(n2_state_t* state, const char* name, n2_func_callback_t callback, void* funcuser);
N2_API n2_bool_t n2e_register_sysvar_ex(n2_state_t* state, const char* name, n2_sysvar_ex_callback_t callback, n2_sysvar_ex_inspect_t inspect, void* sysvaruser);

N2_API n2_module_t* n2e_register_module(n2_state_t* state, const char* name);
N2_API n2_bool_t n2e_register_modcallbacks(n2_module_t* mod, n2_modinstance_alloc_callback_t alloccallback, n2_modinstance_free_callback_t freecallback, void* moduser);
N2_API n2_bool_t n2e_register_modfunc(n2_state_t* state, n2_module_t* mod, const char* name, n2_func_callback_t callback, void* funcuser);

N2_API void n2e_funcarg_raise(const n2_funcarg_t* arg, const char* message, ...);
N2_API n2_bool_t n2e_funcarg_haserror(const n2_funcarg_t* arg);
N2_API size_t n2e_funcarg_csflags(const n2_funcarg_t* arg);
N2_API size_t n2e_funcarg_argnum(const n2_funcarg_t* arg);
N2_API size_t n2e_funcarg_stacktop(const n2_funcarg_t* arg);
N2_API n2_value_t* n2e_funcarg_get(const n2_funcarg_t* arg, int index);
N2_API n2_value_t* n2e_funcarg_getarg(const n2_funcarg_t* arg, int index);
N2_API n2_valint_t n2e_funcarg_eval_int(const n2_funcarg_t* arg, const n2_value_t* val);
N2_API n2_valfloat_t n2e_funcarg_eval_float(const n2_funcarg_t* arg, const n2_value_t* val);
N2_API n2_valstr_t* n2e_funcarg_eval_str(const n2_funcarg_t* arg, const n2_value_t* val);
N2_API n2_valstr_t* n2e_funcarg_eval_str_and_push(const n2_funcarg_t* arg, const n2_value_t* val);
N2_API n2_bool_t n2e_funcarg_pushstack(const n2_funcarg_t* arg, int index);
N2_API void n2e_funcarg_pushi(const n2_funcarg_t* arg, n2_valint_t v);
N2_API void n2e_funcarg_pushf(const n2_funcarg_t* arg, n2_valfloat_t v);
N2_API n2_valstr_t* n2e_funcarg_pushs(const n2_funcarg_t* arg, const char* s);
N2_API void n2e_funcarg_pushmodinst(const n2_funcarg_t* arg, n2_modinstance_t* instance);
N2_API int n2e_funcarg_callfunc(const n2_funcarg_t* arg, const n2_func_t* func, size_t arg_num);

// nidonehsp自身
#if N2_COMPILER_IS_MSVC
#pragma warning(pop)
#endif

/*=============================================================================
あとやること／考えることメモ
	・小さいメモリアロケーションの最適化（例えば128byte単位など）
		これするならvalue_cacheをなくせる
	・文字列などのリテラルの参照保持
		Freeze方式、ReadOnlyならコピーせず保持
	・GC対応
		パフォーマンステスト
	・ファイルシステム整理
	・tre埋め込み
	・bigint埋め込み
	・NanoSVG埋め込み
	・iniファイルパーサー
	・APIを整理する
		大事。というかライブラリとして使う場合に貧弱なAPI…。
	・32bit互換を考える
		コンパイルは通したので、あとは判断のみ
	・アイコン書き換え
		icoパース
	・Vulkan対応
		WebGPUがきてから
	・3D対応
		hgimg4互換？　それとも独自路線？？
		3Dモデルのシェーダ対応
		glTF対応
	・Swizzleを使ったテクスチャメモリ削減
		煩雑性が高いのでしばらく後か？
	・モジュール変数のメンバ呼び出し
	・インスペクタ
	・AMD64 ABI
		System V
	・DebugVariable最適化
		ビット配列など、挿入削除がO(1)のものへ
		※とりあえず遅延確保にしたので大きな問題はない
	・ウィジェットイベントハンドラエラー対処
		イベントハンドル中のclsなど
	・デモ
		もう少し詰める
		他の例、Stg

	近々々
	・VS開発環境
	・GUIのユニットテスト
	・サウンド
=============================================================================*/

#endif/*N2_HEADER_INCLUDE_GUARD*/

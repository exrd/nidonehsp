
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "embed/json.h"
#define LXMSGP_STATIC
#define LXMSGP_IMPLEMENTATION
#include "embed/lxmsgpack.h"
#define CULZ_STATIC
#define CULZ_IMPLEMENTATION
#include "embed/culz.h"
#define LXLZ4_STATIC
//#define LXLZ4_UNALIGNED_MEMORY_ACCESS
#define LXLZ4_IMPLEMENTATION
#include "embed/lxlz4.h"
#define MINIZ_HEADER_FILE_ONLY
#include "embed/miniz.h"
#define ZED_NET_STATIC
#define ZED_NET_IMPLEMENTATION
#include "embed/zed_net.h"
#if 0
#include <../external/lz4/lz4.h>
#include <../external/lz4/lz4.c>
#include <../external/lz4/lz4frame.h>
#include <../external/lz4/lz4frame.c>
#include <../external/lz4/xxhash.h>
#include <../external/lz4/xxhash.c>
#include <../external/lz4/lz4hc.h>
#include <../external/lz4/lz4hc.c>
#endif

#include <nidonehsp.h>
#include "app.h"

#include <SDL.h>

static struct json_value_s* n2u_json_find_named(const struct json_object_s* obj, const char* name, size_t name_length)
{
	if (!obj) { return NULL; }
	if (name_length == SIZE_MAX) { name_length = strlen(name); }

	struct json_object_element_s* cur = obj->start;
	while (cur)
	{
		if (name_length == cur->name->string_size && strncmp(name, cur->name->string, name_length) == 0) { return cur->value; }
		cur = cur->next;
	}
	return NULL;
};

static int n2u_json_find_named_int(const struct json_object_s* obj, const char* name, size_t name_length, int default_value)
{
	struct json_value_s* value = n2u_json_find_named(obj, name, name_length);
	if (value)
	{
		if (json_value_is_null(value)) { return 0; }
		if (json_value_is_false(value)) { return 0; }
		if (json_value_is_true(value)) { return 1; }

		struct json_number_s* num = json_value_as_number(value);
		if (num)
		{
			char* mem = (char*)malloc((num->number_size + 1) * sizeof(char));
			if (mem)
			{
				memcpy(mem, num->number, num->number_size * sizeof(char));
				mem[num->number_size] = '\0';
				const int v = atoi(mem);
				free(mem);
				return v;
			}
		}
	}
	return default_value;
};

static n2_bool_t n2u_json_find_named_str(n2_state_t* state, n2_str_t* dst, const struct json_object_s* obj, const char* name, size_t name_length, const char* default_value)
{
	struct json_value_s* value = n2u_json_find_named(obj, name, name_length);
	if (value)
	{
		struct json_string_s* str = json_value_as_string(value);
		if (str)
		{
			n2_str_set(state, dst, str->string, str->string_size);
			return N2_TRUE;
		}
	}
	n2_str_set(state, dst, default_value, SIZE_MAX);
	return N2_FALSE;
};

static void n2u_print(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	printf("%s", str);
}

static void n2u_print_error(void* print_user, n2_state_t* state, const char* str)
{
	N2_UNUSE(print_user);
	N2_UNUSE(state);
	fprintf(stderr, "%s", str);
}

static int n2u_int_cmpfunc(const n2_array_t* a, const void* lkey, const void* rkey, const void* key)
{
	N2_UNUSE(a);
	N2_UNUSE(key);
	return N2_THREE_WAY_CMP(*N2_RCAST(const int*, lkey), *N2_RCAST(const int*, rkey));
}

int main(int argc, char* argv[])
{
	N2_UNUSE(argc);
	N2_UNUSE(argv);

	n2ri_app_startup_console();

#if 0
	// n2 unittest
	{
		printf("n2 unittest\n");
		n2_state_t* state = n2_state_alloc(NULL);

		// filepath
		if (1)
		{
			printf("filepath\n");
			n2_str_t path;
			n2_str_init(&path);

			n2_str_set(state, &path, "path/to/file", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/to/file") == 0);

			n2_str_set(state, &path, "path/to/../file", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/file") == 0);

			n2_str_set(state, &path, "path/to/../file/..", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/file/..") == 0);

			n2_str_set(state, &path, "path/to/../file/../../", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "") == 0);

			n2_str_set(state, &path, "path/to/../file/../../../", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "../") == 0);

			n2_str_set(state, &path, "path/to/./file", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/to/file") == 0);

			n2_str_set(state, &path, "path/./././to/././file/./", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/to/file/") == 0);

			n2_str_set(state, &path, "path\\.\\.\\./to/.\\./file/.\\", SIZE_MAX);
			n2_path_normalize(state, &path, N2_PATH_SEPARATOR_SLASH);
			N2_ASSERT(N2_STRCMP(path.str_, "path/to/file/") == 0);

			n2_str_teardown(state, &path);
		}

		// color
		if (0)
		{
			printf("color\n");

			printf("hsv conversion\n");
			for (int r = 0; r <= 255; ++r) for (int g = 0; g <= 255; ++g) for (int b = 0; b <= 255; ++b) 
			{
				const n2_fvec3_t hsv = n2s_fcolor_to_hsv(n2s_u8color_to_fcolor(n2s_u8color_clamp(r, g, b, 0)));
				const n2s_u8color_t rgb = n2s_fcolor_to_u8color(n2s_hsv_to_fcolor(hsv, 0));
				N2_ASSERT(r == rgb.r_);
				N2_ASSERT(g == rgb.g_);
				N2_ASSERT(b == rgb.b_);
			}
		}

		// sort
		if (0)
		{
			printf("sort\n");

			n2h_random_t rd;
			n2h_random_init(&rd, 0x12345678ULL);

			n2_intarray_t at;
			n2_intarray_setup(state, &at, 1024, 0);

			for (size_t i = 0; i < 16 * 1024; ++i)
			{
#if 0
				const size_t anum = n2h_random_next_range(&rd, 128);
				const size_t ause = 1024;
#else
				size_t anum = n2h_random_next_range(&rd, 16 * 1024);
				//const size_t ause = 1024;
				const size_t ause = 16 * 1024;
				switch (i)
				{
				case 0: anum = 0; break;
				case 1: anum = 4; break;
				case 2: anum = 7; break;
				default: break;
				}
#endif

				//printf("  sortTest%zu <= %zu\n", i, anum);
				if (i % 100 == 0) { printf("%zu, ", i); }

				n2_intarray_clear(state, &at);
				for (size_t j = 0; j < anum; ++j) { n2_intarray_pushv(state, &at, N2_SCAST(int, n2h_random_next_range(&rd, ause) - 1024)); }

				//if (anum < 128) { printf("  BEFORE : "); for (size_t j = 0; j < anum; ++j) { printf("%d, ", n2_intarray_peekcv(&at, N2_SCAST(int, j), 0)); } printf("\n"); }
				n2_array_sort(&at, n2u_int_cmpfunc, NULL);
				//if (anum < 128) { printf("  AFTER  : "); for (size_t j = 0; j < anum; ++j) { printf("%d, ", n2_intarray_peekcv(&at, N2_SCAST(int, j), 0)); } printf("\n"); }

				for (size_t j = 1; j < anum; ++j) { N2_ASSERT(n2_intarray_peekv(&at, N2_SCAST(int, j - 1), 0) <= n2_intarray_peekv(&at, N2_SCAST(int, j), 0)); }
			}

			n2_intarray_teardown(state, &at);
		}

		// base64
		if (1)
		{
			printf("base64\n");

			n2_buffer_t from_buf;
			n2_buffer_init(&from_buf);
			n2_str_t to_buf;
			n2_str_init(&to_buf);

			// fixed cases
			if (1)
			{
				const struct {
					const char* from_;
					const char* to_;
					const char* to_urlsafe_;
					n2_bool_t from_to_check_;
				} testpair[] = {
					{"test message", "dGVzdCBtZXNzYWdl", "dGVzdCBtZXNzYWdl", N2_TRUE},
					{"123", "MTIz", "MTIz", N2_TRUE},
					{"12", "MTI=", "MTI=", N2_TRUE},
					{"1", "MQ==", "MQ==", N2_TRUE},
					{"!\"#$%'()0987654321\\|^~-=[{]}@`:*;+\\_/?.>,<1", "ISIjJCUnKCkwOTg3NjU0MzIxXHxefi09W3tdfUBgOio7K1xfLz8uPiw8MQ==", "ISIjJCUnKCkwOTg3NjU0MzIxXHxefi09W3tdfUBgOio7K1xfLz8uPiw8MQ==", N2_TRUE},
					{"!-2~_><", "IS0yfl8+PA==", "IS0yfl8-PA==", N2_TRUE},
					{"", "", "", N2_TRUE},
					{"", "=", "=", N2_FALSE},
					{"", "==", "==", N2_FALSE},
				};

				for (size_t i = 0; i < N2_ARRAYDIM(testpair); ++i)
				{
					n2_bool_t dcnv = N2_TRUE;

					const char* from = testpair[i].from_;
					const size_t from_len = N2_STRLEN(from);

					printf(" %zu> %s >> %s >> %s\n", i, from, testpair[i].to_, testpair[i].to_urlsafe_);

					if (testpair[i].from_to_check_)
					{
						n2h_base64_encode_to(state, &to_buf, from, N2_SCAST(size_t, from_len), N2_FALSE);
						N2_ASSERT(N2_STRCMP(to_buf.str_, testpair[i].to_) == 0);
					}
					n2_buffer_clear(&from_buf);
					dcnv = n2h_base64_decode_to(state, &from_buf, testpair[i].to_, N2_STRLEN(testpair[i].to_), N2_FALSE);
					N2_ASSERT(dcnv);
					N2_ASSERT(N2_MEMCMP(from_buf.data_, from, from_buf.size_) == 0);

					if (testpair[i].from_to_check_)
					{
						n2h_base64_encode_to(state, &to_buf, from, N2_SCAST(size_t, from_len), N2_TRUE);
						N2_ASSERT(N2_STRCMP(to_buf.str_, testpair[i].to_urlsafe_) == 0);
					}
					n2_buffer_clear(&from_buf);
					dcnv = n2h_base64_decode_to(state, &from_buf, testpair[i].to_urlsafe_, N2_STRLEN(testpair[i].to_urlsafe_), N2_TRUE);
					N2_ASSERT(dcnv);
					N2_ASSERT(N2_MEMCMP(from_buf.data_, from, from_buf.size_) == 0);
				}
			}

			// random cases
			if (1)
			{
				n2h_random_t rd;
				n2h_random_init(&rd, 0x12345678ULL);

				n2_buffer_t from;
				n2_buffer_init(&from);

				for (size_t test = 0; test < 8 * 1024; ++test)
				{
					if ((test % 1024) == 0) { printf(" random %zu\n", test); }

					const size_t n = n2h_random_next_range(&rd, 1024);
					n2_buffer_reserve(state, &from, n);
					n2_buffer_clear(&from);
					for (size_t i = 0; i < n; ++i)
					{
						const uint8_t w = n2h_random_next(&rd) & 0xff;
						n2_buffer_append(state, &from, &w, 1);
					}

					for (size_t urlsafe = 0; urlsafe < 2; ++urlsafe)
					{
						n2h_base64_encode_to(state, &to_buf, from.data_, from.size_, N2_TOBOOL(urlsafe));
						n2_buffer_clear(&from_buf);
						n2_bool_t dcnv = n2h_base64_decode_to(state, &from_buf, to_buf.str_, to_buf.size_, N2_TOBOOL(urlsafe));
						N2_ASSERT(dcnv);
						N2_ASSERT(N2_MEMCMP(from_buf.data_, from.data_, from_buf.size_) == 0);
					}
				}

				n2_buffer_teardown(state, &from);
			}

			n2_buffer_teardown(state, &from_buf);
			n2_str_teardown(state, &to_buf);
		}

		n2_state_free(state);
		printf("n2 unittest done\n");
	}
#elif 0
	// random key test
	{
		n2h_random_t rd;
		n2h_random_init(&rd, 0x12345678ULL);
		for (size_t i = 0; i < 8; ++i)
		{
			const uint64_t r = n2h_random_next(&rd);
			printf("%zu = %llu\n", i, r);
		}

		printf("random key test\n");
	}
#elif 0
	// network test
	{
		zed_net_init();

		const int port = 8888;
		const int non_blocking = 0;

		zed_net_socket_t sock;

		char buf[255];

#define NET_PRINTERROR() \
	do { \
		printf("%s\n", zed_net_get_error()); \
	} while (0)

#define NET_ERROR() \
	do { \
		NET_PRINTERROR(); \
		exit(-1); \
	} while (0)

#define NET_PCON(l, s) \
	do { printf(l "check connection[%d]\n", zed_net_check_connection(s)); } while (0)

#if N2_PLATFORM_IS_WINDOWS
#define MSLEEP(ms) \
		Sleep(ms)
#else
#define MSLEEP(ms) \
		usleep(ms * 1000);
#endif

		printf("nonbocking[%d]\n", non_blocking);

		if (argc <= 1)
		{
			// server
			printf("server mode\n");

			zed_net_socket_t remotesock;
			zed_net_address_t remoteaddr;

			NET_PCON("preopen sock", &sock);
			if (zed_net_tcp_socket_open(&sock, port, non_blocking, 1)) { NET_ERROR(); }
			NET_PCON("postopen sock", &sock);
			if (non_blocking)
			{
				for (;;)
				{
					const int c = zed_net_tcp_accept(&sock, &remotesock, &remoteaddr);
					printf("waiting accept ...[%d]\n", c);
					if (c == 0) { break; }
					if (c < 0) { NET_ERROR(); }
					MSLEEP(500);
				}
			}
			else
			{
				for (;;)
				{
					const int c = zed_net_check_connection(&sock);
					printf("waiting accept ...[%d]\n", c);
					if (c > 0) { break; }
					if (c < 0) { NET_ERROR(); }
					MSLEEP(500);
				}
				if (zed_net_tcp_accept(&sock, &remotesock, &remoteaddr)) { NET_ERROR(); }
			}
			NET_PCON("postaccept sock", &sock);
			NET_PCON("postaccept rem", &remotesock);

			for (;;)
			{
				int rcv_size = 0;
				for (;;)
				{
					const int c = zed_net_check_connection(&remotesock);
					printf("waiting readable ...[%d]\n", c);
					if (c) { break; }
					MSLEEP(500);
				}
				NET_PCON("prereceive sock", &sock);
				NET_PCON("prereceive rem", &remotesock);
				if (zed_net_tcp_socket_receive(&remotesock, &rcv_size, buf, sizeof(buf))) { printf("rcv failed\n"); NET_PRINTERROR(); break; }
				printf("received[%d bytes] %.*s\n", rcv_size, rcv_size, buf);
				MSLEEP(1000);
				if (zed_net_tcp_socket_send(&remotesock, buf, rcv_size)) { printf("send failed\n"); NET_PRINTERROR(); break; }
			}

			zed_net_socket_close(&remotesock);
		}
		else
		{
			// client
			printf("client mode\n");

			zed_net_address_t remoteaddr;
			if (zed_net_get_address(&remoteaddr, "127.0.0.1", port) != 0) { NET_ERROR(); }

			if (zed_net_tcp_socket_open(&sock, 0, 0, 0)) { NET_ERROR(); }
			if (zed_net_tcp_connect(&sock, remoteaddr)) { NET_ERROR(); }
			MSLEEP(3000);

			for (int i = 0; i < 3; ++i)
			{
				const int written = snprintf(buf, sizeof(buf), "sending %d ...", i);
				if (zed_net_tcp_socket_send(&sock, buf, written)) { printf("send failed\n"); NET_PRINTERROR(); break; }
				int rcv_size = 0;
				if (zed_net_tcp_socket_receive(&sock, &rcv_size, buf, sizeof(buf))) { printf("rcv failed\n"); NET_PRINTERROR(); break; }
				printf("received[%d bytes] %.*s\n", rcv_size, rcv_size, buf);
				MSLEEP(3000);
			}
		}

		zed_net_socket_close(&sock);
		zed_net_shutdown();
	}
#elif 0
	// SDL test
	{
		SDL_Init(SDL_INIT_VIDEO);

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
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

		// gles2
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

		SDL_Window* window = SDL_CreateWindow("n2utest_sdl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);

		int driver_index = -1;
		for (int it = 0; it < SDL_GetNumRenderDrivers(); ++it)
		{
			SDL_RendererInfo rinfo;
			SDL_GetRenderDriverInfo(it, &rinfo);

			printf("Render : %d = %s\n", it, rinfo.name);
			if (N2_STRCMP(rinfo.name, "opengles2") == 0)
			{
				driver_index = it;
				break;
			}
		}
		SDL_Renderer* renderer = SDL_CreateRenderer(window, driver_index, SDL_RENDERER_SOFTWARE);

		int is_quit = 0;
		while (!is_quit)
		{
			SDL_Event evt;

			while (SDL_PollEvent(&evt))
			{
				switch (evt.type)
				{
				case SDL_QUIT:
					is_quit = 1;
					break;
				}
			}

			SDL_RenderClear(renderer);
			{
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
				SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
				SDL_Rect rect;
				rect.x = 150; rect.y = 150; rect.w = 100; rect.h = 100;
				SDL_RenderFillRect(renderer, &rect);
			}
			SDL_RenderPresent(renderer);

			SDL_Delay(100);
		}

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}
#elif 0
	// lxmsgpackテスト
	{
		lxmsgp_pack_t pack;
		lxmsgp_unpack_t unpack;
		lxmsgp_element_t element;
		char mem[1024];

#define UTEST_LXMSGP_RW(label, binpattern, pack_action, unpack_check) \
		do { \
			printf("[%s] ", label); \
			lxmsgp_pack_init_memory(&pack, NULL); \
			do { pack_action; } while (0); \
			printf("pack_action, "); \
			assert(lxmsgp_pack_get_error(&pack) == LXMSGP_ERROR_NONE); \
			size_t serialized_size = 0; \
			const void* serialized = lxmsgp_pack_get_memory(&pack, &serialized_size); \
			printf("serialized[%p <= %zu], ", serialized, serialized_size); \
			assert(serialized && serialized_size > 0); \
			assert(sizeof(mem) * 3 > serialized_size); \
			size_t w = 0; \
			for (size_t i = 0; i < serialized_size; ++i) { if (i > 0) { sprintf(mem + w, " "); ++w; } sprintf(mem + w, "%02x", (unsigned int)(((const uint8_t*)(serialized))[i])); w += 2; } \
			printf("pattern[%s <=> %s], ", mem, binpattern); \
			assert(strcmp(mem, binpattern) == 0); \
			lxmsgp_unpack_init(&unpack, serialized, serialized_size); \
			assert(lxmsgp_unpack_get_element(&unpack, &element)); \
			do { unpack_check; } while (0); \
			size_t element_num = 0; \
			while (lxmsgp_unpack_get_element(&unpack, NULL)) { lxmsgp_unpack_next(&unpack); ++element_num; } \
			printf("elementnum[%zu], ", element_num); \
			assert(lxmsgp_unpack_eof(&unpack)); \
			lxmsgp_unpack_fin(&unpack); \
			lxmsgp_pack_fin(&pack); \
			printf("\n"); \
		} while (0)

		// nil
		UTEST_LXMSGP_RW("nil", "c0", (lxmsgp_pack_put_nil(&pack)), (assert(element.type == LXMSGP_TYPE_NIL)));

		// bool
		UTEST_LXMSGP_RW("true", "c3", (lxmsgp_pack_put_bool(&pack, LXMSGP_TRUE)), (assert(element.type == LXMSGP_TYPE_BOOL), assert(element.content.boolval == LXMSGP_TRUE)));
		UTEST_LXMSGP_RW("false", "c2", (lxmsgp_pack_put_bool(&pack, LXMSGP_FALSE)), (assert(element.type == LXMSGP_TYPE_BOOL), assert(element.content.boolval == LXMSGP_FALSE)));

		// uint
		UTEST_LXMSGP_RW("0", "00", (lxmsgp_pack_put_uint(&pack, 0)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 0)));
		UTEST_LXMSGP_RW("100", "64", (lxmsgp_pack_put_uint(&pack, 100)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 100)));
		UTEST_LXMSGP_RW("200", "cc c8", (lxmsgp_pack_put_uint(&pack, 200)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 200)));
		UTEST_LXMSGP_RW("300", "cd 01 2c", (lxmsgp_pack_put_uint(&pack, 300)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 300)));
		UTEST_LXMSGP_RW("65550", "ce 00 01 00 0e", (lxmsgp_pack_put_uint(&pack, 65550)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 65550)));
		UTEST_LXMSGP_RW("1829304858821", "cf 00 00 01 a9 eb 10 f8 c5", (lxmsgp_pack_put_uint(&pack, 1829304858821ULL)), (assert(element.type == LXMSGP_TYPE_UINT), assert(element.content.uintval == 1829304858821ULL)));

		// int
		UTEST_LXMSGP_RW("0", "d0 00", (lxmsgp_pack_put_int(&pack, 0)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 0)));
		UTEST_LXMSGP_RW("100", "d0 64", (lxmsgp_pack_put_int(&pack, 100)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 100)));
		UTEST_LXMSGP_RW("200", "d1 00 c8", (lxmsgp_pack_put_int(&pack, 200)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 200)));
		UTEST_LXMSGP_RW("300", "d1 01 2c", (lxmsgp_pack_put_int(&pack, 300)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 300)));
		UTEST_LXMSGP_RW("65550", "d2 00 01 00 0e", (lxmsgp_pack_put_int(&pack, 65550)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 65550)));
		UTEST_LXMSGP_RW("1829304858821", "d3 00 00 01 a9 eb 10 f8 c5", (lxmsgp_pack_put_int(&pack, 1829304858821LL)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == 1829304858821LL)));
		UTEST_LXMSGP_RW("-1", "ff", (lxmsgp_pack_put_int(&pack, -1)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -1)));
		UTEST_LXMSGP_RW("-10", "f6", (lxmsgp_pack_put_int(&pack, -10)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -10)));
		UTEST_LXMSGP_RW("-32", "e0", (lxmsgp_pack_put_int(&pack, -32)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -32)));
		UTEST_LXMSGP_RW("-33", "d0 df", (lxmsgp_pack_put_int(&pack, -33)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -33)));
		UTEST_LXMSGP_RW("-100", "d0 9c", (lxmsgp_pack_put_int(&pack, -100)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -100)));
		UTEST_LXMSGP_RW("-200", "d1 ff 38", (lxmsgp_pack_put_int(&pack, -200)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -200)));
		UTEST_LXMSGP_RW("-300", "d1 fe d4", (lxmsgp_pack_put_int(&pack, -300)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -300)));
		UTEST_LXMSGP_RW("-32768", "d1 80 00", (lxmsgp_pack_put_int(&pack, -32768)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -32768)));
		UTEST_LXMSGP_RW("-65550", "d2 ff fe ff f2", (lxmsgp_pack_put_int(&pack, -65550)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -65550)));
		UTEST_LXMSGP_RW("-1829304858821", "d3 ff ff fe 56 14 ef 07 3b", (lxmsgp_pack_put_int(&pack, -1829304858821LL)), (assert(element.type == LXMSGP_TYPE_INT), assert(element.content.intval == -1829304858821LL)));

		// double
		{
			const double epsilon = 0.00000000001;
			UTEST_LXMSGP_RW("0.2", "cb 3f c9 99 99 99 99 99 9a", (lxmsgp_pack_put_double(&pack, 0.2)), (assert(element.type == LXMSGP_TYPE_DOUBLE), assert(fabs(element.content.doubleval - 0.2) < epsilon)));
			UTEST_LXMSGP_RW("100.2839476", "cb 40 59 12 2c 32 8d f1 c6", (lxmsgp_pack_put_double(&pack, 100.2839476)), (assert(element.type == LXMSGP_TYPE_DOUBLE), assert(fabs(element.content.doubleval - 100.2839476) < epsilon)));
			UTEST_LXMSGP_RW("123456789.123456789", "cb 41 9d 6f 34 54 7e 6b 75", (lxmsgp_pack_put_double(&pack, 123456789.123456789)), (assert(element.type == LXMSGP_TYPE_DOUBLE), assert(fabs(element.content.doubleval - 123456789.123456789) < epsilon)));
		}

		// str
		{
			const char* s = "";
			UTEST_LXMSGP_RW("<none>", "a0", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
			s = "abc";
			UTEST_LXMSGP_RW(s, "a3 61 62 63", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
			s = "abcdefghijklmn";
			UTEST_LXMSGP_RW(s, "ae 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
			s = "abcdefghijklmnop";
			UTEST_LXMSGP_RW(s, "b0 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
			s = "abcdefghijklmnopqrstuvwxyz";
			UTEST_LXMSGP_RW(s, "ba 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 76 77 78 79 7a", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
			s = "\xE6\xBC\xA2\xE5\xAD\x97";// u8"漢字"
			UTEST_LXMSGP_RW(s, "a6 e6 bc a2 e5 ad 97", (lxmsgp_pack_put_str(&pack, s, strlen(s))), (assert(element.type == LXMSGP_TYPE_STRING), assert(strncmp(element.content.strval.str, s, strlen(s)) == 0 && element.content.strval.length == strlen(s))));
		}

		// bin
		{
			uint8_t data[64]; size_t data_size;
			data_size = 0;
			UTEST_LXMSGP_RW("<none:data>", "c4 00", (lxmsgp_pack_put_bin(&pack, data, data_size)), (assert(element.type == LXMSGP_TYPE_BINARY), assert(memcmp(element.content.binval.bin, data, data_size) == 0 && element.content.binval.length == data_size)));
			data[0] = 1; data_size = 1;
			UTEST_LXMSGP_RW("<data:1>", "c4 01 01", (lxmsgp_pack_put_bin(&pack, data, data_size)), (assert(element.type == LXMSGP_TYPE_BINARY), assert(memcmp(element.content.binval.bin, data, data_size) == 0 && element.content.binval.length == data_size)));
			data[0] = 0x00; data[1] = 0xff; data_size = 2;
			UTEST_LXMSGP_RW("<data:2>", "c4 02 00 ff", (lxmsgp_pack_put_bin(&pack, data, data_size)), (assert(element.type == LXMSGP_TYPE_BINARY), assert(memcmp(element.content.binval.bin, data, data_size) == 0 && element.content.binval.length == data_size)));
		}

		// array
		{
			UTEST_LXMSGP_RW("<none:array>", "90", (lxmsgp_pack_put_array_size(&pack, 0)), (assert(element.type == LXMSGP_TYPE_ARRAY), assert(element.content.arrayval.length == 0)));
			UTEST_LXMSGP_RW("<array:1>", "91", (lxmsgp_pack_put_array_size(&pack, 1)), (assert(element.type == LXMSGP_TYPE_ARRAY), assert(element.content.arrayval.length == 1)));
			UTEST_LXMSGP_RW("<array[1]>", "91 01", { lxmsgp_pack_put_array_size(&pack, 1); lxmsgp_pack_put_uint(&pack, 1); }, (assert(element.type == LXMSGP_TYPE_ARRAY), assert(element.content.arrayval.length == 1)));
			UTEST_LXMSGP_RW("<array:200>", "dc 00 c8", (lxmsgp_pack_put_array_size(&pack, 200)), (assert(element.type == LXMSGP_TYPE_ARRAY), assert(element.content.arrayval.length == 200)));
			UTEST_LXMSGP_RW("<array:65550>", "dd 00 01 00 0e", (lxmsgp_pack_put_array_size(&pack, 65550)), (assert(element.type == LXMSGP_TYPE_ARRAY), assert(element.content.arrayval.length == 65550)));
		}

		// map
		{
			UTEST_LXMSGP_RW("<none:map>", "80", (lxmsgp_pack_put_map_size(&pack, 0)), (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 0)));
			UTEST_LXMSGP_RW("<map:1>", "81", (lxmsgp_pack_put_map_size(&pack, 1)), (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 1)));
			UTEST_LXMSGP_RW("<map{a:2}>", "81 a1 61 02", { lxmsgp_pack_put_map_size(&pack, 1); lxmsgp_pack_put_str(&pack, "a", 1); lxmsgp_pack_put_uint(&pack, 2); }, (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 1)));
			UTEST_LXMSGP_RW("<map:200>", "de 00 c8", (lxmsgp_pack_put_map_size(&pack, 200)), (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 200)));
			UTEST_LXMSGP_RW("<map:65550>", "df 00 01 00 0e", (lxmsgp_pack_put_map_size(&pack, 65550)), (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 65550)));
			UTEST_LXMSGP_RW("<map{compact:true, schema:0}>", "82 a7 63 6f 6d 70 61 63 74 c3 a6 73 63 68 65 6d 61 00", { lxmsgp_pack_put_map_size(&pack, 2); lxmsgp_pack_put_str(&pack, "compact", 7); lxmsgp_pack_put_bool(&pack, LXMSGP_TRUE); lxmsgp_pack_put_str(&pack, "schema", 6); lxmsgp_pack_put_uint(&pack, 0); }, (assert(element.type == LXMSGP_TYPE_MAP), assert(element.content.mapval.length == 2)));
		}

		//timestamp
		{
			UTEST_LXMSGP_RW("ts:0,0", "d6 ff 00 00 00 00", (lxmsgp_pack_put_timestamp(&pack, 0, 0)), (assert(element.type == LXMSGP_TYPE_TIMESTAMP), assert(element.content.tsval.seconds == 0), assert(element.content.tsval.nanoseconds == 0)));
			UTEST_LXMSGP_RW("ts:1,0", "d6 ff 00 00 00 01", (lxmsgp_pack_put_timestamp(&pack, 1, 0)), (assert(element.type == LXMSGP_TYPE_TIMESTAMP), assert(element.content.tsval.seconds == 1), assert(element.content.tsval.nanoseconds == 0)));
			UTEST_LXMSGP_RW("ts:0,1", "d7 ff 00 00 00 04 00 00 00 00", (lxmsgp_pack_put_timestamp(&pack, 0, 1)), (assert(element.type == LXMSGP_TYPE_TIMESTAMP), assert(element.content.tsval.seconds == 0), assert(element.content.tsval.nanoseconds == 1)));
		}
	}
#elif 0
	// xxhash
	if (0)
	{
		printf("xxhash test\n");
		n2h_random_t rd;
		n2h_random_init(&rd, 0);
		for (size_t i = 0; i < 128 * 1024; ++i)
		{
			size_t size = n2h_random_next_range(&rd, 0x00ffffff) + 0xff;
			uint64_t mode = n2h_random_next_range(&rd, 8);
			if (i < 1024) { size = i; }
			if (i / 1024 < 9) { mode = i / 1024; }

			void* src = malloc(size);
			uint64_t scratch_key = n2h_random_next(&rd);
			//if (i < 24) { continue; }
			memset(src, 0, size);
			n2h_random_scratch(src, size, scratch_key);
			switch (mode)
			{
			case 0: break;
			case 1: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 1; } break;
			case 2: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 2; } break;
			case 3: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 3; } break;
			case 4: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 4; } break;
			case 5: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 5; } break;
			case 6: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 6; } break;
			case 7: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 7; } break;
			case 8: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] = 128; } break;
			default: assert(0); break;
			}

			const uint64_t hash_begin = SDL_GetPerformanceCounter();
			const uint32_t xxhash = lxlz4_xxhash32(src, size, 0);
			const uint64_t hash_end = SDL_GetPerformanceCounter();
			const uint64_t hash_micro = (hash_end - hash_begin) * 1000000 / SDL_GetPerformanceFrequency();

			const uint64_t libhash_begin = SDL_GetPerformanceCounter();
#ifdef LZ4_VERSION_MAJOR
			const uint32_t libxxhash = XXH32(src, size, 0);
#endif
			const uint64_t libhash_end = SDL_GetPerformanceCounter();
			const uint64_t libhash_micro = (libhash_end - libhash_begin) * 1000000 / SDL_GetPerformanceFrequency();
#ifdef LZ4_VERSION_MAJOR
			(void)(libxxhash);
			assert(xxhash == libxxhash);
#endif

			printf("%03zu : size=%zu, got hash=%x, hash=%lld usec, libhash=%lld usec\n", i, size, xxhash, hash_micro, libhash_micro);
		}
	}
	// lxlz4
	if (0)
	{
		printf("lxlz4 test\n");
		n2h_random_t rd;
		n2h_random_init(&rd, 0);
		for (size_t i = 0; i < 128; ++i)
		{
			size_t size = n2h_random_next_range(&rd, 0x00ffffff) + 0xff;
			uint64_t mode = n2h_random_next_range(&rd, 8);
			if (i < 1024) { size = i; }
			if (i / 1024 < 9) { mode = i / 1024; }
			//size = 512;
			mode = 6;

			void* src = malloc(size);
			uint64_t scratch_key = n2h_random_next(&rd);
			//if (i < 24) { continue; }
			memset(src, 0, size);
			n2h_random_scratch(src, size, scratch_key);
			switch (mode)
			{
			case 0: break;
			case 1: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 1; } break;
			case 2: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 2; } break;
			case 3: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 3; } break;
			case 4: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 4; } break;
			case 5: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 5; } break;
			case 6: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 6; } break;
			case 7: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 7; } break;
			case 8: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] = 128; } break;
			default: assert(0); break;
			}

#ifdef LZ4_VERSION_MAJOR
			const size_t libnum = 2;
#else
			const size_t libnum = 1;
#endif
			for (size_t lib = 0; lib < libnum; ++lib)
			{
				const size_t boundsize = lxlz4_compress_bound(size, NULL);
				void* compressed = malloc(boundsize);
				lxlz4_error_e e = LXLZ4_ERROR_NONE;
				size_t compressed_size = 0;
				const uint64_t compress_begin = SDL_GetPerformanceCounter();
				if (lib == 0)
				{
					lxlz4_compress_option_t copt;
					lxlz4_compress_option_init(&copt);
					//copt.level_ = LXLZ4_COMPRESS_LEVEL_NOCOMPRESS;
					e = lxlz4_compress(compressed, boundsize, &compressed_size, src, size, &copt, NULL);
					assert(e == LXLZ4_ERROR_NONE);
				}
				else
				{
#ifdef LZ4_VERSION_MAJOR
					compressed_size = (size_t)LZ4_compress_default((const char*)src, (char*)compressed, (int)size, (int)boundsize);
#endif
				}
				const uint64_t compress_end = SDL_GetPerformanceCounter();
				const uint64_t compress_micro = (compress_end - compress_begin) * 1000000 / SDL_GetPerformanceFrequency();
				void* decompressed = malloc(size);
				const uint64_t decompress_begin = SDL_GetPerformanceCounter();
				size_t decompressed_written = 0;
				if (lib == 0)
				{
					e = lxlz4_decompress(decompressed, size, &decompressed_written, compressed, compressed_size, NULL);
					assert(e == LXLZ4_ERROR_NONE);
				}
				else
				{
#ifdef LZ4_VERSION_MAJOR
					int dw = LZ4_decompress_safe((const char*)compressed, (char*)decompressed, (int)compressed_size, (int)size);
					assert(dw >= 0);
					decompressed_written = (size_t)dw;
#endif
				}
				uint64_t decompress_end = SDL_GetPerformanceCounter();
				uint64_t decompress_micro = (decompress_end - decompress_begin) * 1000000 / SDL_GetPerformanceFrequency();
				assert(decompressed_written == size);
				int cmp = 0;
				size_t cmppos = 0;
				for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
				assert(cmp == 0);
				printf("%03zu(lib=%zu) : size=%zu, compressed=%zu(%+.4lf%%) comp=%llu[us]:%+.2lfMiB/s decomp=%llu[us]:%+.2lfMiB/s\n", i, lib, size, compressed_size, (double)compressed_size / (double)size * 100.0, compress_micro, (double)size / (double)compress_micro * 1000000.0 / 1024.0 / 1024.0, decompress_micro, (double)size / (double)decompress_micro * 1000000.0 / 1024.0 / 1024.0);
				// cross decompression test
				if (0)
				{
#ifdef LZ4_VERSION_MAJOR
					if (lib == 1)
					{
						e = lxlz4_decompress(decompressed, size, &decompressed_written, compressed, compressed_size, NULL);
						assert(e == LXLZ4_ERROR_NONE);
					}
					else
					{
						int dw = LZ4_decompress_safe((const char*)compressed, (char*)decompressed, (int)compressed_size, (int)size);
						assert(dw >= 0);
						decompressed_written = (size_t)dw;
					}
					assert(decompressed_written == size);
					cmp = 0;
					cmppos = 0;
					for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
					assert(cmp == 0);
#endif
				}
				free(compressed);
				free(decompressed);
			}
			free(src);
		}
		printf("lxlz4 test end\n");
	}

	// lxlz4frame
	if (1)
	{
		printf("lxlz4frame test\n");
		n2h_random_t rd;
		n2h_random_init(&rd, 0);
		for (size_t i = 0; i < 128; ++i)
		{
			size_t size = n2h_random_next_range(&rd, 0x00ffffff) + 0x00;
			uint64_t mode = n2h_random_next_range(&rd, 8);
			const size_t enblock = 128;
			(void)(enblock);
			//if (i < enblock) { size = i; }
			//if (i / enblock < 9) { mode = i / enblock; }
			//size = 256;
			mode = 6;

			void* src = malloc(size);
			uint64_t scratch_key = n2h_random_next(&rd);
			//if (i < 24) { continue; }
			memset(src, 0, size);
			n2h_random_scratch(src, size, scratch_key);
			switch (mode)
			{
			case 0: break;
			case 1: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 1; } break;
			case 2: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 2; } break;
			case 3: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 3; } break;
			case 4: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 4; } break;
			case 5: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 5; } break;
			case 6: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 6; } break;
			case 7: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 7; } break;
			case 8: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] = 128; } break;
			default: assert(0); break;
			}

			//if (i < 1024) { continue; }

#ifdef LZ4_VERSION_MAJOR
			const size_t libnum = 2;
#else
			const size_t libnum = 1;
#endif
			for (size_t lib = 0; lib < libnum; ++lib)
			{
				const size_t boundsize = lxlz4_frame_compress_bound(size, NULL);
				void* compressed = malloc(boundsize);
				lxlz4_error_e e = LXLZ4_ERROR_NONE;
				size_t compressed_size = 0;
				const uint64_t compress_begin = SDL_GetPerformanceCounter();
				if (lib == 0)
				{
					lxlz4_compress_option_t copt;
					lxlz4_compress_option_init_compatible(&copt);
					//copt.level_ = LXLZ4_COMPRESS_LEVEL_NOCOMPRESS;
					//copt.level_ = LXLZ4_COMPRESS_LEVEL_NORMAL;
					//copt.is_block_independent_ = LXLZ4_TRUE;
					//copt.block_max_size_ = LXLZ4_BLOCK_SIZE_4MB;
					e = lxlz4_frame_compress(compressed, boundsize, &compressed_size, src, size, &copt, NULL);
					assert(e == LXLZ4_ERROR_NONE);
				}
				else
				{
#ifdef LZ4_VERSION_MAJOR
					LZ4F_preferences_t pref = LZ4F_INIT_PREFERENCES;
					//pref.frameInfo.blockMode = LZ4F_blockIndependent;
					compressed_size = LZ4F_compressFrame(compressed, boundsize, src, size, &pref);
#endif
				}
				const uint64_t compress_end = SDL_GetPerformanceCounter();
				const uint64_t compress_micro = (compress_end - compress_begin) * 1000000 / SDL_GetPerformanceFrequency();
				void* decompressed = malloc(size);
				const uint64_t decompress_begin = SDL_GetPerformanceCounter();
				size_t decompressed_written = 0;
				if (lib == 0)
				{
					e = lxlz4_frame_decompress(decompressed, size, &decompressed_written, compressed, compressed_size, NULL);
					assert(e == LXLZ4_ERROR_NONE);
				}
				else
				{
#ifdef LZ4_VERSION_MAJOR
					LZ4F_dctx* dctx = NULL;
					LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION);
					const uint8_t* ip = (const uint8_t*)compressed;
					const uint8_t* eip = ip + compressed_size;
					uint8_t* op = (uint8_t*)decompressed;
					uint8_t* sop = op;
					uint8_t* eop = op + size;
					for (;;)
					{
						size_t opsize = (size_t)(eop - op);
						size_t ipsize = (size_t)(eip - ip);
						const size_t hint = LZ4F_decompress(dctx, op, &opsize, ip, &ipsize, NULL);
						assert(!LZ4F_isError(hint));
						ip += ipsize; op += opsize;
						//if (ip == eip) { break; }
						if (!hint) { break; }
					}
					decompressed_written = (size_t)(op - sop);
					LZ4F_freeDecompressionContext(dctx);
#endif
				}
				uint64_t decompress_end = SDL_GetPerformanceCounter();
				uint64_t decompress_micro = (decompress_end - decompress_begin) * 1000000 / SDL_GetPerformanceFrequency();
				assert(decompressed_written == size);
				int cmp = 0;
				size_t cmppos = 0;
				if (memcmp(src, decompressed, size))
				{
					for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
				}
				assert(cmp == 0);
				printf("%03zu(lib=%zu) : size=%zu, compressed=%zu(%+.4lf%%) comp=%llu[us]:%+.2lfMiB/s decomp=%llu[us]:%+.2lfMiB/s\n", i, lib, size, compressed_size, (double)compressed_size / (double)size * 100.0, compress_micro, (double)size / (double)compress_micro * 1000000.0 / 1024.0 / 1024.0, decompress_micro, (double)size / (double)decompress_micro * 1000000.0 / 1024.0 / 1024.0);
				// cross decompression test
#ifdef LZ4_VERSION_MAJOR
				{
					if (lib == 1)
					{
						e = lxlz4_frame_decompress(decompressed, size, &decompressed_written, compressed, compressed_size, NULL);
						assert(e == LXLZ4_ERROR_NONE);
					}
					else
					{
						LZ4F_dctx* dctx = NULL;
						LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION);
						const uint8_t* ip = (const uint8_t*)compressed;
						const uint8_t* eip = ip + compressed_size;
						uint8_t* op = (uint8_t*)decompressed;
						uint8_t* sop = op;
						uint8_t* eop = op + size;
						for (;;)
						{
							size_t opsize = (size_t)(eop - op);
							size_t ipsize = (size_t)(eip - ip);
							const size_t hint = LZ4F_decompress(dctx, op, &opsize, ip, &ipsize, NULL);
							assert(!LZ4F_isError(hint));
							ip += ipsize; op += opsize;
							//if (ip == eip) { break; }
							if (!hint) { break; }
						}
						decompressed_written = (size_t)(op - sop);
						LZ4F_freeDecompressionContext(dctx);
					}
					assert(decompressed_written == size);
					cmp = 0;
					cmppos = 0;
					if (memcmp(src, decompressed, size))
					{
						for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
					}
					assert(cmp == 0);
				}
#endif
				free(compressed);
				free(decompressed);
			}
			free(src);
		}
		printf("lxlz4 test end\n");
	}

	// culz
	if (1)
	{
		printf("culz test\n");
		n2h_random_t rd;
		n2h_random_init(&rd, 0);
		for (size_t i = 0; i < 128; ++i)
		{
			size_t size = n2h_random_next_range(&rd, 0x00ffffff) + 0xff;
			void* src = malloc(size);
			uint64_t scratch_key = n2h_random_next(&rd);
			uint64_t mode = n2h_random_next_range(&rd, 8);
			//if (i < 24) { continue; }
			memset(src, 0, size);
			n2h_random_scratch(src, size, scratch_key);
			switch (mode)
			{
			case 0: break;
			case 1: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 1; } break;
			case 2: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 2; } break;
			case 3: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 3; } break;
			case 4: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 4; } break;
			case 5: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 5; } break;
			case 6: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 6; } break;
			case 7: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 7; } break;
			default: assert(0); break;
			}
			size_t boundsize = (size_t)(CulzCompressBound((int)size));
			void* dst = malloc(boundsize);
			int compressed = 0;
			const uint64_t compress_begin = SDL_GetPerformanceCounter();
			compressed = CulzCompressFast((const uint8_t*)src, (int)size, (uint8_t*)dst, NULL);
			//compressed = CulzCompress((const uint8_t*)src, (int)size, (uint8_t*)dst, CULZ_COMPRESS_LEVEL_MIN, NULL);
			const uint64_t compress_end = SDL_GetPerformanceCounter();
			const uint64_t compress_micro = (compress_end - compress_begin) * 1000000 / SDL_GetPerformanceFrequency();
			assert(compressed > 0);
			void* decompressed = malloc(size);
			if (i == 24)
			{
				//printf("%zu decompressed_end=0x%p\n", i, (uint8_t*)decompressed + size);
			}
			const uint64_t decompress_begin = SDL_GetPerformanceCounter();
			int decompressed_size = CulzDecompress((const uint8_t*)dst, compressed, (uint8_t*)decompressed, (int)size);
			const uint64_t decompress_end = SDL_GetPerformanceCounter();
			const uint64_t decompress_micro = (decompress_end - decompress_begin) * 1000000 / SDL_GetPerformanceFrequency();
			assert(decompressed_size == (int)size);
			//const int cmp = memcmp(src, decompressed, size);
			int cmp = 0;
			size_t cmppos = 0;
			for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
			assert(cmp == 0);
			free(src);
			free(dst);
			free(decompressed);
			printf("%03zu : size=%zu, compressed=%d(%+.4lf%%) comp=%llu[us]:%+.2lfMiB/s decomp=%llu[us]:%+.2lfMiB/s\n", i, size, compressed, (double)compressed / (double)size * 100.0, compress_micro, (double)size / (double)compress_micro * 1000000.0 / 1024.0 / 1024.0, decompress_micro, (double)size / (double)decompress_micro * 1000000.0 / 1024.0 / 1024.0);
		}
		printf("culz test end\n");
	}

	// miniz
	if (1)
	{
		printf("miniz test\n");
		n2h_random_t rd;
		n2h_random_init(&rd, 0);
		for (size_t i = 0; i < 128; ++i)
		{
			size_t size = (n2h_random_next(&rd) & 0x00ffffff) + 0xff;
			void* src = malloc(size);
			uint64_t scratch_key = n2h_random_next(&rd);
			uint64_t mode = n2h_random_next(&rd) % 8;
			//if (i < 24) { continue; }
			memset(src, 0, size);
			n2h_random_scratch(src, size, scratch_key);
			switch (mode)
			{
			case 0: break;
			case 1: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 1; } break;
			case 2: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 2; } break;
			case 3: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 3; } break;
			case 4: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 4; } break;
			case 5: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 5; } break;
			case 6: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 6; } break;
			case 7: for (size_t j = 0; j < size; ++j) { ((uint8_t*)src)[j] >>= 7; } break;
			}
			size_t boundsize = (size_t)(mz_compressBound((mz_ulong)size));
			void* dst = malloc(boundsize);
			const uint64_t compress_begin = SDL_GetPerformanceCounter();
			mz_ulong compressed = (mz_ulong)boundsize;
			int compressed_res = mz_compress2((uint8_t*)dst, &compressed, (const uint8_t*)src, (int)size, MZ_BEST_SPEED);
			const uint64_t compress_end = SDL_GetPerformanceCounter();
			const uint64_t compress_micro = (compress_end - compress_begin) * 1000000 / SDL_GetPerformanceFrequency();
			assert(compressed_res == MZ_OK);
			void* decompressed = malloc(size);
			const uint64_t decompress_begin = SDL_GetPerformanceCounter();
			mz_ulong decompressed_size = (mz_ulong)size;
			int decompressed_res = mz_uncompress((uint8_t*)decompressed, &decompressed_size, (const uint8_t*)dst, compressed);
			assert(decompressed_res == MZ_OK);
			const uint64_t decompress_end = SDL_GetPerformanceCounter();
			const uint64_t decompress_micro = (decompress_end - decompress_begin) * 1000000 / SDL_GetPerformanceFrequency();
			assert(decompressed_size == size);
			//const int cmp = memcmp(src, decompressed, size);
			int cmp = 0;
			size_t cmppos = 0;
			for (size_t j = 0; j < size; ++j) { if (((uint8_t*)src)[j] != ((uint8_t*)decompressed)[j]) { cmp = 1; cmppos = j; break; } }
			assert(cmp == 0);
			free(src);
			free(dst);
			free(decompressed);
			printf("%03zu : size=%zu, compressed=%d(%+.4lf%%) comp=%llu[us]:%+.2lfMiB/s decomp=%llu[us]:%+.2lfMiB/s\n", i, size, compressed, (double)compressed / (double)size * 100.0, compress_micro, (double)size / (double)compress_micro * 1000000.0 / 1024.0 / 1024.0, decompress_micro, (double)size / (double)decompress_micro * 1000000.0 / 1024.0 / 1024.0);
		}
		printf("miniz test end\n");
	}
#elif 0
	// vector/matrixテスト
	{
#define N2U_TEST_MAT44_TH(lhs, rhs, eth, ath, exp) \
	do { \
		float ad = 0; \
		for (int j = 0; j < 4; ++j) for (int i = 0;  i < 4; ++i) \
		{ \
			const float d = fabsf((lhs)->m_[j][i] - (rhs)->m_[j][i]); \
			N2_ASSERT(d < eth && "d < eth"); \
			ad += d; \
		} \
		N2_ASSERT(ad < ath && "ad < ath"); \
		exp; \
	} while (0)

		n2h_random_t rd;
		n2h_random_init(&rd, 0x12345678ULL);

		if (1)
		{
			printf("ROTATION(EULER ANGLE X->Y->Z)\n");
			for (int test = 0; test < 1024; ++test)
			{
				n2_fvec3_t rot = n2_fvec3(N2_SCAST(float, n2h_random_next_float(&rd) * M_PI), N2_SCAST(float, n2h_random_next_float(&rd) * M_PI), N2_SCAST(float, n2h_random_next_float(&rd) + M_PI));

				n2_fmat4_t m;
				n2_fmat4_erotation_to(&m, rot);

				n2_fmat4_t mx, my, mz;
				n2_fmat4_arotation_to(&mx, n2_fvec3(1, 0, 0), rot.x_);
				n2_fmat4_arotation_to(&my, n2_fvec3(0, 1, 0), rot.y_);
				n2_fmat4_arotation_to(&mz, n2_fvec3(0, 0, 1), rot.z_);

				n2_fmat4_t mm = n2_fmat4_mul(mz, n2_fmat4_mul(my, mx));

				float tad = 0;
				N2U_TEST_MAT44_TH(&m, &mm, 0.001f, 0.01f, tad = ad);

				//printf("  [%d] ad=%+.8f\n", test, tad);
			}
		}
		if (1)
		{
			printf("ROTATION(QUAT<=>MATRIX)\n");
			for (int test = 0; test < 1024; ++test)
			{
				n2_fvec3_t rota = n2_fvec3(N2_SCAST(float, n2h_random_next_float(&rd)), N2_SCAST(float, n2h_random_next_float(&rd)), N2_SCAST(float, n2h_random_next_float(&rd)));
				float rot = N2_SCAST(float, n2h_random_next_float(&rd) * M_PI);

				n2_fmat4_t m;
				n2_fmat4_arotation_to(&m, rota, rot);

				n2_fquat4_t q = n2_fquat4_arotation(rota, rot);

				n2_fmat4_t mm;
				n2_fmat4_qrotation_to(&mm, q);

				float tad = 0;
				N2U_TEST_MAT44_TH(&m, &mm, 0.001f, 0.01f, tad = ad);
				//printf("  [%d] ad=%+.8f\n", test, tad);
			}
		}
		if (1)
		{
			printf("ROTATION(QUAT OP)\n");
			for (int test = 0; test < 1024; ++test)
			{
				n2_fvec3_t rota = n2_fvec3(N2_SCAST(float, n2h_random_next_float(&rd)), N2_SCAST(float, n2h_random_next_float(&rd)), N2_SCAST(float, n2h_random_next_float(&rd)));
				float rot = N2_SCAST(float, n2h_random_next_float(&rd) * M_PI);
				n2_fvec3_t nrota;
				n2_fvec3_normalize_to(&nrota, rota);

				n2_fmat4_t m;
				n2_fmat4_arotation_to(&m, rota, rot * 2);

				n2_fquat4_t q = n2_fquat4_arotation(rota, rot);
				q = n2_fquat4_mul(q, q);

				n2_fmat4_t mm;
				n2_fmat4_qrotation_to(&mm, q);

				float tad = 0;
				N2U_TEST_MAT44_TH(&m, &mm, 0.001f, 0.01f, tad = ad);
				//printf("  [%d] ad=%+.8f\n", test, tad);

				{
					// decompose
					n2_fvec3_t axis;
					const float r = n2_fquat4_decompose(&axis, q);
					N2_ASSERT(fabsf(r - rot * 2) < 0.001f);
					n2_fvec3_t drota = n2_fvec3_sub(axis, nrota);
					N2_ASSERT(n2_fvec3_length(drota) < 0.001f);
				}
				{
					// inverse
					n2_fquat4_t iq = n2_fquat4_inverse(q);
					n2_fquat4_t zq = n2_fquat4_mul(iq, q);
					n2_fvec3_t axis;
					const float r = n2_fquat4_decompose(&axis, zq);
					N2_ASSERT(fabsf(r) < 0.001f);
				}
			}
		}
		if (1)
		{
			printf("INVERSE\n");
			for (int test = 0; test < 1024; ++test)
			{
				n2_fmat4_t m = n2_fmat4_identity();
				for (int i = 0; i < 16; ++i)
				{
					m.e_[i] = N2_SCAST(float, n2h_random_next_float(&rd) * 10);
				}

				n2_fmat4_t im;
				const float det = n2_fmat4_inverse_to(&im, &m);
				N2_UNUSE(det);

				n2_fmat4_t mm;
				n2_fmat4_fastmul_to(&mm, &im, &m);

				n2_fmat4_t ident = n2_fmat4_identity();

				float tad = 0;
				N2U_TEST_MAT44_TH(&mm, &ident, 0.001f, 0.01f, tad = ad);

				//printf("  [%d] det=%+.8f, ad=%+.8f\n", test, det, tad);
			}
		}
	}
#elif 1
	// nidonehsp ユニットテスト
	{
		// 外部用state
		n2_state_config_t extstateconfig;
		n2_state_config_init(&extstateconfig);
		extstateconfig.print_ = n2u_print;
		extstateconfig.print_error_ = n2u_print_error;

		n2_state_t* extstate = n2_state_alloc(&extstateconfig);

		n2_str_t utest_json;
		n2_str_init(&utest_json);

		if (!n2_state_fs_load_str(extstate, &utest_json, N2_STATE_FSFLAG_DEFAULT, "utest.json", SIZE_MAX, 0))
		{
			printf("failed to read utest.json...\n");
			exit(-1);
		}
		n2_str_trim_utf8_bom(&utest_json);

		struct json_value_s* utest_val = json_parse_ex(utest_json.str_, utest_json.size_, json_parse_flags_allow_json5, NULL, NULL, NULL);
		if (!utest_val)
		{
			printf("failed to load as json...\n");
			exit(-1);
		}
		struct json_object_s* utest_root = json_value_as_object(utest_val);
		if (!utest_root)
		{
			printf("root element is not object ...\n");
			exit(-1);
		}

		n2_str_t ubase_directory;
		n2_str_init(&ubase_directory);
		n2u_json_find_named_str(extstate, &ubase_directory, utest_root, "base_directory", SIZE_MAX, "");

		const struct json_array_s* utest_array = json_value_as_array(n2u_json_find_named(utest_root, "tests", SIZE_MAX));
		if (!utest_array)
		{
			printf("test set not found ...\n");
			exit(-1);
		}

		n2t_leakcheck_context_t ac;
		n2t_leakcheck_context_init(&ac);

		n2_state_config_t config;
		n2_state_config_init_ex(&config, N2_STATE_CONFIG_FLAG_NO_RPMALLOC);
		config.allocator_.allocate_ = n2t_leakcheck_allocfunc;
		config.allocator_.free_ = n2t_leakcheck_freefunc;
		config.allocator_.alloc_user_ = &ac;
		config.print_ = n2u_print;
		config.print_error_ = n2u_print_error;
		config.generate_opcodeflags_ = N2_TRUE;
		config.generate_codelines_ = N2_TRUE;
		config.generate_debugvars_ = N2_TRUE;
		config.enable_graphics_assert_ = N2_TRUE;

		size_t test_num = 0;
		size_t passed_test_num = 0;

		const struct json_array_element_s* cur_utest = utest_array->start;
		while (cur_utest)
		{
			// 読み込み
			const struct json_object_s* thistest_property = json_value_as_object(cur_utest->value);

			n2_str_t thistest_name, thistest_script;
			n2_bool_t thistest_standard = N2_FALSE;
			n2_str_init(&thistest_name);
			n2_str_init(&thistest_script);
			n2u_json_find_named_str(extstate, &thistest_name, thistest_property, "name", SIZE_MAX, "-");
			n2u_json_find_named_str(extstate, &thistest_script, thistest_property, "path", SIZE_MAX, "");
			thistest_standard = n2u_json_find_named_int(thistest_property, "standard", SIZE_MAX, 0) ? N2_TRUE : N2_FALSE;

			if (!thistest_property || thistest_script.size_ <= 0)
			{
				printf("illegal test entry... \n");
				cur_utest = cur_utest->next;
				continue;
			}

			n2_bool_t thistest_predump_ppsrc = N2_FALSE;
			n2_bool_t thistest_predump_ast = N2_FALSE;
			n2_bool_t thistest_predump_opcode = N2_FALSE;
			n2_bool_t thistest_ac_print = N2_FALSE;

			// 特定のスクリプトだけ実行・無視する場合
#if 0
			if (strcmp(thistest_name.str_, "Staging") != 0)
			{
				cur_utest = cur_utest->next;
				continue;
			}
			//thistest_predump_ppsrc = N2_TRUE;
			//thistest_predump_ast = N2_TRUE;
			thistest_predump_opcode = N2_TRUE;
			//thistest_ac_print = N2_TRUE;
#else
			if (strcmp(thistest_name.str_, "Staging") == 0)
			{
				cur_utest = cur_utest->next;
				continue;
			}
#endif

			printf("=====UTEST( %s )    %s\n", thistest_name.str_, thistest_script.str_);

			n2_str_t thistest_scriptfullpath;
			n2_str_init(&thistest_scriptfullpath);
			n2_str_fmt_to(extstate, &thistest_scriptfullpath, "%s/%s", ubase_directory.str_, thistest_script.str_);

			n2_str_t thistest_scriptcontent;
			n2_str_init(&thistest_scriptcontent);
			if (!n2_state_fs_load_str(extstate, &thistest_scriptcontent, N2_STATE_FSFLAG_DEFAULT, thistest_scriptfullpath.str_, SIZE_MAX, 0))
			{
				printf("cannot load script content ... %s\n", thistest_scriptfullpath.str_);
				continue;
			}

			n2_str_trim_utf8_bom(&thistest_scriptcontent);

			// 前準備
			ac.print_ = thistest_ac_print;
			//ac.print_ = N2_TRUE;

			// 生成
			n2_state_t* state = n2_state_alloc(&config);
			n2_state_bind_basics(state);
			n2_state_bind_consoles(state);
			if (thistest_standard) { n2_state_bind_standards(state); }

			// 読み込み
			n2_bool_t passed = N2_TRUE;
			if (n2_state_load_str(state, NULL, thistest_scriptcontent.str_, thistest_scriptcontent.size_, thistest_scriptfullpath.str_))
			{
				// デバッグ
				if (thistest_predump_ppsrc)
				{
					const n2_sourcecode_t* sourcecode = n2_sourcecodearray_peekv(state->environment_->sourcecodes_, 0, NULL);
					printf("PREPROCESSED: %s\n", sourcecode->src_ppscript_.str_);
				}
				if (thistest_predump_ast)
				{
					n2_ast_node_dump(state, n2_astarray_peekv(state->environment_->asts_, 0, NULL), N2_FALSE);
				}
				if (thistest_predump_opcode)
				{
					n2_environment_dump_codeimages(state, state->environment_, N2_CODEIMAGE_DUMP_ALL);
				}

				if (n2_state_execute(state))
				{
					if (state->main_fiber_->exit_code_)
					{
						passed = N2_FALSE;
						printf("  ERROR: aborted( %d )\n", state->main_fiber_->exit_code_);
					}
				}
				else
				{
					passed = N2_FALSE;
					printf("  ERROR: execution failed\n");
				}
			}
			else
			{
				passed = N2_FALSE;
				printf("  ERROR: load failed\n");
			}

			if (n2_valuearray_size(state->main_fiber_->values_) > 1)
			{
				printf("  ERROR: SUSPICIOUS execution : stack size is (%zu)\n", n2_valuearray_size(state->main_fiber_->values_));
				passed = N2_FALSE;
			}

			// ここまでで失敗していたら実行エラーなので詳細ダンプ
			if (!passed)
			{
				if (!thistest_predump_ppsrc)
				{
					const n2_sourcecode_t* sourcecode = n2_sourcecodearray_peekv(state->environment_->sourcecodes_, 0, NULL);
					if (sourcecode)
					{
						printf("PREPROCESSED: %s\n", sourcecode->src_ppscript_.str_);
					}
				}
				if (!thistest_predump_opcode)
				{
					n2_environment_dump_codeimages(state, state->environment_, N2_CODEIMAGE_DUMP_DEFAULT);
				}
			}

			// 後始末
			n2_state_free(state);

			// リークチェック
			if (n2t_leakcheck_context_report(&ac) > 0) { passed = N2_FALSE; }
			n2t_leakcheck_context_teardown(&ac);

			// ここで成功判定
			++test_num;
			if (passed) { ++passed_test_num; }

			// 次
			cur_utest = cur_utest->next;
		}

		printf("========\n");
		printf("========\n");
		printf("TOTAL( %zu )\n  PASSED( %zu )\n  FAILED( %zu )\n", test_num, passed_test_num, test_num - passed_test_num);

		free(utest_val);
		n2_str_teardown(extstate, &utest_json);

		n2_state_free(extstate);
	}
#endif

	return 0;
}



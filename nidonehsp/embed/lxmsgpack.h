//-----------------------------------------------------------------------------
/*
    lxmsgpack.h
      msgpack read/write implementation in C written by exrd.
      lxmsgpack is licensed under CC0 1.0 Universal, see end of this file for more detail.
*/
//-----------------------------------------------------------------------------

#ifndef LXMSGP_HEADER_INCLUDED
#define LXMSGP_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    customization
//

// linkage
#ifdef LXMSGP_STATIC
#define LXMSGP_API  static
#else
#define LXMSGP_API
#endif // LXMSGP_STATIC

// assert
#ifndef LXMSGP_ASSERT
#include <assert.h>
#define LXMSGP_ASSERT    assert
#endif // LXMSGP_ASSERT

// memory api
#ifndef LXMSGP_NO_MEMORY_API
// malloc, free, realloc
#ifndef LXMSGP_MALLOC
#include <stdlib.h>
#define LXMSGP_MALLOC(size, user)       malloc(size)
#define LXMSGP_FREE(ptr, user)          free(ptr)
#define LXMSGP_REALLOC_SIZED(oldptr, newsize, oldsize, user)    realloc(oldptr, newsize)
#endif // LXMSGP_MALLOC
// memcpy
#ifndef LXMSGP_MEMCPY
#include <string.h>
#define LXMSGP_MEMCPY(dst, src, size)   memcpy(dst, src, size)
#endif // LXMSGP_MEMCPY
#endif // LXMSGP_NO_MEMORY_API

// file api
#ifndef LXMSGP_NO_STDIO_FILE_API
#include <stdio.h>
#endif // LXMSGP_NO_STDIO_FILE_API

//-----------------------------------------------------------------------------
//
//    forward declaration
//
#include <stddef.h>
#include <stdint.h>

//
//    common
//
typedef int lxmsgp_bool_t;
#define LXMSGP_TRUE  (1)
#define LXMSGP_FALSE (0)

typedef enum
{
    LXMSGP_TYPE_UNKNOWN = -1,
    LXMSGP_TYPE_NIL = 0,
    LXMSGP_TYPE_BOOL,
    LXMSGP_TYPE_UINT,
    LXMSGP_TYPE_INT,
    LXMSGP_TYPE_FLOAT,
    LXMSGP_TYPE_DOUBLE,
    LXMSGP_TYPE_STRING,
    LXMSGP_TYPE_BINARY,
    LXMSGP_TYPE_ARRAY,
    LXMSGP_TYPE_MAP,
    LXMSGP_TYPE_TIMESTAMP,
    LXMSGP_TYPE_EXTENSION,

    LXMSGP_TYPE_COUNT
} lxmsgp_type_e;

typedef enum
{
    LXMSGP_ERROR_NONE = 0,
    // for pack
    LXMSGP_ERROR_FLUSH_FAILED,
    // for unpack
    LXMSGP_ERROR_ILLEGAL_VALUE,
    LXMSGP_ERROR_INSUFFICIENT_INPUT,
} lxmsgp_error_e;

LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_integral(lxmsgp_type_e type);
LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_floating_point(lxmsgp_type_e type);
LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_number(lxmsgp_type_e type);

//
//    value representation
//
typedef struct lxmsgp_value_string_t lxmsgp_value_string_t;
struct lxmsgp_value_string_t
{
    const char* str;
    uint32_t length;
};

typedef struct lxmsgp_value_binary_t lxmsgp_value_binary_t;
struct lxmsgp_value_binary_t
{
    const void* bin;
    uint32_t length;
};

typedef struct lxmsgp_value_array_t lxmsgp_value_array_t;
struct lxmsgp_value_array_t
{
    uint32_t length;
};

typedef struct lxmsgp_value_map_t lxmsgp_value_map_t;
struct lxmsgp_value_map_t
{
    uint32_t length;
};

typedef struct lxmsgp_value_timestamp_t lxmsgp_value_timestamp_t;
struct lxmsgp_value_timestamp_t
{
    uint64_t seconds;
    uint32_t nanoseconds;
};

typedef struct lxmsgp_value_extension_t lxmsgp_value_extension_t;
struct lxmsgp_value_extension_t
{
    int8_t subtype;
    const void* data;
    uint32_t length;
};

//
//    element
//
typedef union lxmsgp_content_t lxmsgp_content_t;
union lxmsgp_content_t
{
    lxmsgp_bool_t boolval;// for LXMSGP_TYPE_BOOL
    uint64_t uintval;// for LXMSGP_TYPE_UINT
    int64_t intval;// for LXMSGP_TYPE_INT
    float floatval;// for LXMSGP_TYPE_FLOAT
    double doubleval;// for LXMSGP_TYPE_DOUBLE
    lxmsgp_value_string_t strval;// for LXMSGP_TYPE_STRING
    lxmsgp_value_binary_t binval;// for LXMSGP_TYPE_BINARY
    lxmsgp_value_array_t arrayval;// for LXMSGP_TYPE_ARRAY
    lxmsgp_value_map_t mapval;// for LXMSGP_TYPE_MAP
    lxmsgp_value_timestamp_t tsval;// for LXMSGP_TYPE_TIMESTAMP
    lxmsgp_value_extension_t extval;// for LXMSGP_TYPE_EXTENSION
};

typedef struct lxmsgp_element_t lxmsgp_element_t;
struct lxmsgp_element_t
{
    lxmsgp_type_e type;
    lxmsgp_content_t content;
};

LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_int(const lxmsgp_element_t* element, int64_t* dst_intval);
LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_uint(const lxmsgp_element_t* element, uint64_t* dst_uintval);
LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_float(const lxmsgp_element_t* element, float* dst_floatval);
LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_double(const lxmsgp_element_t* element, double* dst_doubleval);

//
//    pack
//
typedef struct lxmsgp_pack_t lxmsgp_pack_t;

typedef lxmsgp_bool_t (*lxmsgp_pack_write_func_t)(void* user, const void* data, size_t length);
typedef void (*lxmsgp_pack_fin_func_t)(void* user, lxmsgp_pack_t* pack);

struct lxmsgp_pack_t
{
    lxmsgp_error_e last_error;// last error
    size_t total_size;// written total byte size
    lxmsgp_pack_write_func_t write_func;// user provided write func
    lxmsgp_pack_fin_func_t fin_func;// user provided fin func
    void* user;// user context for write/fin func
};

LXMSGP_API void lxmsgp_pack_init(lxmsgp_pack_t* pack, lxmsgp_pack_write_func_t write_func, lxmsgp_pack_fin_func_t fin_func, void* user);
LXMSGP_API void lxmsgp_pack_fin(lxmsgp_pack_t* pack);

#ifndef LXMSGP_NO_MEMORY_API
LXMSGP_API void lxmsgp_pack_init_memory(lxmsgp_pack_t* pack, void* alloc_user);
LXMSGP_API void lxmsgp_pack_init_memory_ex(lxmsgp_pack_t* pack, size_t initial_buffer_size, size_t buffer_expand_step, void* alloc_user);
LXMSGP_API const void* lxmsgp_pack_get_memory(const lxmsgp_pack_t* pack, size_t* dst_size);
#endif // LXMSGP_NO_MEMORY_API

#ifndef LXMSGP_NO_STDIO_FILE_API
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_init_file(lxmsgp_pack_t* pack, const char* filepath);
#endif // LXMSGP_NO_STDIO_FILE_API

LXMSGP_API lxmsgp_error_e lxmsgp_pack_get_error(const lxmsgp_pack_t* pack);

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_nil(lxmsgp_pack_t* pack);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_bool(lxmsgp_pack_t* pack, lxmsgp_bool_t boolval);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_uint(lxmsgp_pack_t* pack, uint64_t uintval);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_int(lxmsgp_pack_t* pack, int64_t intval);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_float(lxmsgp_pack_t* pack, float floatval);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_double(lxmsgp_pack_t* pack, double doubleval);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_str(lxmsgp_pack_t* pack, const char* str, uint32_t length);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_bin(lxmsgp_pack_t* pack, const void* bin, uint32_t length);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_array_size(lxmsgp_pack_t* pack, uint32_t length);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_map_size(lxmsgp_pack_t* pack, uint32_t length);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_timestamp(lxmsgp_pack_t* pack, uint64_t seconds, uint32_t nanoseconds);
LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_ext(lxmsgp_pack_t* pack, int8_t subtype, const void* data, uint32_t length);

//
//    unpack
//
typedef struct lxmsgp_iterator_t lxmsgp_iterator_t;
struct lxmsgp_iterator_t
{
    const uint8_t* head;// element head ptr
};

typedef struct lxmsgp_unpack_t lxmsgp_unpack_t;

typedef void (*lxmsgp_unpack_fin_func_t)(void* user, lxmsgp_unpack_t* unpack);

struct lxmsgp_unpack_t
{
    const uint8_t* src;// source data
    size_t src_size;// size of source data
    const uint8_t* src_end;// end of source data
    lxmsgp_iterator_t iterator;// current iterator
    lxmsgp_iterator_t next_iterator;// next iterator
    lxmsgp_element_t element;// current element
    lxmsgp_error_e last_error;// last error
    lxmsgp_unpack_fin_func_t fin_func;// fin func
    void* user;// user context for fin func
};

LXMSGP_API void lxmsgp_unpack_init(lxmsgp_unpack_t* unpack, const void* src, size_t src_size);
LXMSGP_API void lxmsgp_unpack_init_ex(lxmsgp_unpack_t* unpack, const void* src, size_t src_size, lxmsgp_unpack_fin_func_t fin_func, void* user);
LXMSGP_API void lxmsgp_unpack_fin(lxmsgp_unpack_t* unpack);

#if !defined(LXMSGP_NO_MEMORY_API) && !defined(LXMSGP_NO_STDIO_FILE_API)
LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_init_file(lxmsgp_unpack_t* unpack, const char* filepath, void* alloc_user);
#endif // !LXMSGP_NO_MEMORY_API && !LXMSGP_NO_STDIO_FILE_API

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_eof(const lxmsgp_unpack_t* unpack);
LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_get_element(const lxmsgp_unpack_t* unpack, lxmsgp_element_t* dst_element);
LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_next(lxmsgp_unpack_t* unpack);
LXMSGP_API size_t lxmsgp_unpack_skip(lxmsgp_unpack_t* unpack, size_t skip_num);
LXMSGP_API lxmsgp_iterator_t lxmsgp_unpack_get_iterator(const lxmsgp_unpack_t* unpack);
LXMSGP_API void lxmsgp_unpack_set_iterator(lxmsgp_unpack_t* unpack, lxmsgp_iterator_t iterator);

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_get_element_from_iterator_unsafe(const lxmsgp_iterator_t* iterator, lxmsgp_element_t* dst_element);

#endif // LXMSGP_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    implementation
//
#ifdef LXMSGP_IMPLEMENTATION
#ifndef LXMSGP_IMPLEMENTATION_INCLUDED
#define LXMSGP_IMPLEMENTATION_INCLUDED

//
//    common
//
LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_integral(lxmsgp_type_e type)
{
    switch (type)
    {
    case LXMSGP_TYPE_UINT:
    case LXMSGP_TYPE_INT:
        return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_floating_point(lxmsgp_type_e type)
{
    switch (type)
    {
    case LXMSGP_TYPE_FLOAT:
    case LXMSGP_TYPE_DOUBLE:
        return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_type_is_number(lxmsgp_type_e type)
{
    switch (type)
    {
    case LXMSGP_TYPE_UINT:
    case LXMSGP_TYPE_INT:
    case LXMSGP_TYPE_FLOAT:
    case LXMSGP_TYPE_DOUBLE:
        return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

//
//    element
//
LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_int(const lxmsgp_element_t* element, int64_t* dst_intval)
{
    switch (element->type)
    {
    case LXMSGP_TYPE_INT: *dst_intval = element->content.intval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_UINT: if (element->content.uintval > INT64_MAX) { return LXMSGP_FALSE; } *dst_intval = (int64_t)element->content.uintval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_FLOAT: *dst_intval = (int64_t)element->content.floatval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_DOUBLE: *dst_intval = (int64_t)element->content.doubleval; return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_uint(const lxmsgp_element_t* element, uint64_t* dst_uintval)
{
    switch (element->type)
    {
    case LXMSGP_TYPE_INT: if (element->content.intval < 0) { return LXMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.intval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_UINT: *dst_uintval = element->content.uintval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_FLOAT: if (element->content.floatval < 0) { return LXMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.floatval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_DOUBLE: if (element->content.doubleval < 0) { return LXMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.doubleval; return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_float(const lxmsgp_element_t* element, float* dst_floatval)
{
    switch (element->type)
    {
    case LXMSGP_TYPE_INT: *dst_floatval = (float)element->content.intval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_UINT: *dst_floatval = (float)element->content.uintval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_FLOAT: *dst_floatval = (float)element->content.floatval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_DOUBLE: *dst_floatval = (float)element->content.doubleval; return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_element_as_double(const lxmsgp_element_t* element, double* dst_doubleval)
{
    switch (element->type)
    {
    case LXMSGP_TYPE_INT: *dst_doubleval = (double)element->content.intval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_UINT: *dst_doubleval = (double)element->content.uintval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_FLOAT: *dst_doubleval = (double)element->content.floatval; return LXMSGP_TRUE;
    case LXMSGP_TYPE_DOUBLE: *dst_doubleval = (double)element->content.doubleval; return LXMSGP_TRUE;
    default: break;
    }
    return LXMSGP_FALSE;
}

//
//    pack
//
LXMSGP_API void lxmsgp_pack_init(lxmsgp_pack_t* pack, lxmsgp_pack_write_func_t write_func, lxmsgp_pack_fin_func_t fin_func, void* user)
{
    pack->last_error = LXMSGP_ERROR_NONE;
    pack->total_size = 0;
    pack->write_func = write_func;
    pack->fin_func = fin_func;
    pack->user = user;
}

LXMSGP_API void lxmsgp_pack_fin(lxmsgp_pack_t* pack)
{
    if (pack->fin_func) { pack->fin_func(pack->user, pack); }
    pack->last_error = LXMSGP_ERROR_NONE;
    pack->write_func = NULL;
    pack->fin_func = NULL;
    pack->user = NULL;
}

#ifndef LXMSGP_NO_MEMORY_API
typedef struct lxmsgp_internal_pack_memory_t lxmsgp_internal_pack_memory_t;
struct lxmsgp_internal_pack_memory_t
{
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_expand_step;
    size_t written_size;
    void* alloc_user;
};

static lxmsgp_bool_t lxmsgp_internal_pack_memory_flush_callback(void* user, const void* data, size_t length)
{
    lxmsgp_internal_pack_memory_t* m = (lxmsgp_internal_pack_memory_t*)user;
    if (!m->buffer || m->written_size + length > m->buffer_size)
    {
        if (m->buffer)
        {
            size_t expand_step = m->buffer_expand_step ? m->buffer_expand_step : m->buffer_size;
            if (expand_step < length) { expand_step = length; }
            uint8_t* next_buffer = (uint8_t*)(LXMSGP_REALLOC_SIZED(m->buffer, m->buffer_size + expand_step, m->buffer_size, m->alloc_user));
            if (!next_buffer) { return LXMSGP_FALSE; }// failed to realloc
            m->buffer = next_buffer;
        }
        else
        {
            m->buffer = (uint8_t*)(LXMSGP_MALLOC(length, m->alloc_user));
        }
    }
    LXMSGP_ASSERT(m->buffer);
    LXMSGP_MEMCPY(m->buffer + m->written_size, data, length);
    m->written_size += length;
    return LXMSGP_TRUE;
}

static void lxmsgp_internal_pack_memory_fin_callback(void* user, lxmsgp_pack_t* pack)
{
    (void)(pack);
    lxmsgp_internal_pack_memory_t* m = (lxmsgp_internal_pack_memory_t*)user;
    void* alloc_user = m->alloc_user;
    (void)(alloc_user);
    LXMSGP_FREE(m->buffer, alloc_user);
    LXMSGP_FREE(m, alloc_user);
}

LXMSGP_API void lxmsgp_pack_init_memory(lxmsgp_pack_t* pack, void* alloc_user)
{
    lxmsgp_pack_init_memory_ex(pack, 1024, 1024, alloc_user);
}

LXMSGP_API void lxmsgp_pack_init_memory_ex(lxmsgp_pack_t* pack, size_t initial_buffer_size, size_t buffer_expand_step, void* alloc_user)
{
    lxmsgp_internal_pack_memory_t* m = (lxmsgp_internal_pack_memory_t*)(LXMSGP_MALLOC(sizeof(lxmsgp_internal_pack_memory_t), alloc_user));
    LXMSGP_ASSERT(m);
    m->buffer = (uint8_t*)(initial_buffer_size == 0 ? NULL : LXMSGP_MALLOC(initial_buffer_size, alloc_user));
    m->buffer_size = initial_buffer_size;
    m->buffer_expand_step = buffer_expand_step;
    m->written_size = 0;
    m->alloc_user = alloc_user;
    lxmsgp_pack_init(pack, &lxmsgp_internal_pack_memory_flush_callback, &lxmsgp_internal_pack_memory_fin_callback, m);
}

LXMSGP_API const void* lxmsgp_pack_get_memory(const lxmsgp_pack_t* pack, size_t* dst_size)
{
    const lxmsgp_internal_pack_memory_t* m = (const lxmsgp_internal_pack_memory_t*)pack->user;
    if (dst_size) { *dst_size = m->written_size; }
    return m->buffer;
}
#endif // LXMSGP_NO_MEMORY_API

#ifndef LXMSGP_NO_STDIO_FILE_API
static lxmsgp_bool_t lxmsgp_internal_pack_file_flush_callback(void* user, const void* data, size_t length)
{
    FILE* file = (FILE*)user;
    if (!file) { return LXMSGP_FALSE; }
    fwrite(data, 1, length, file);
    return LXMSGP_TRUE;
}

static void lxmsgp_internal_pack_file_fin_callback(void* user, lxmsgp_pack_t* pack)
{
    (void)(pack);
    FILE* file = (FILE*)user;
    if (file) { fclose(file); }
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_init_file(lxmsgp_pack_t* pack, const char* filepath)
{
    FILE* file = fopen(filepath, "wb");
    if (!file) { return LXMSGP_FALSE; }
    lxmsgp_pack_init(pack, &lxmsgp_internal_pack_file_flush_callback, &lxmsgp_internal_pack_file_fin_callback, file);
    return LXMSGP_TRUE;
}
#endif // LXMSGP_NO_STDIO_FILE_API

LXMSGP_API lxmsgp_error_e lxmsgp_pack_get_error(const lxmsgp_pack_t* pack)
{
    return pack->last_error;
}

#define LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack) \
    do { \
        if ((pack)->last_error != LXMSGP_ERROR_NONE) { return LXMSGP_FALSE; } \
    } while (0)
#define LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, size) \
    do { \
        if ((pack)->write_func) \
        { \
            if (!(pack)->write_func(pack->user, (data), (size))) \
            { \
                (pack)->last_error = LXMSGP_ERROR_FLUSH_FAILED; \
                return LXMSGP_FALSE; \
            } \
        } \
        (pack)->total_size += (size); \
    } while (0)
#define LXMSGP_INTERNAL_PACK_PUT_VAL(pack, val, size) \
    do { \
        uint8_t mem[8]; \
        for (size_t i = 0; i < size; ++i) { mem[i] = ((val) >> ((size - i - 1) * 8)) & 0xff; } \
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, mem, size); \
    } while (0)

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_nil(lxmsgp_pack_t* pack)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xc0;
    LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_bool(lxmsgp_pack_t* pack, lxmsgp_bool_t boolval)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = boolval ? 0xc3 : 0xc2;
    LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_uint(lxmsgp_pack_t* pack, uint64_t uintval)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (uintval <= 0x7f)
    {
        uint8_t val = uintval & 0x7f;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (uintval <= 0xff)
    {
        uint8_t val = 0xcc;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = uintval & 0xff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (uintval <= 0xffff)
    {
        uint8_t val = 0xcd;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = uintval & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else if (uintval <= 0xffffffff)
    {
        uint8_t val = 0xce;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = uintval & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    else
    {
        uint8_t val = 0xcf;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, uintval, 8);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_int(lxmsgp_pack_t* pack, int64_t intval)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    //if (intval >= 0x0) { return lxmsgp_pack_put_uint(pack, (uint64_t)intval); }
    if (intval < 0 && intval >= -32)
    {
        int8_t ival = (int8_t)intval;
        uint8_t val = *(uint8_t*)(&ival);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (intval >= -128 && intval <= 127)
    {
        uint8_t val = 0xd0;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = (uint8_t)(intval);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (intval >= -32768 && intval <= 32767)
    {
        uint8_t val = 0xd1;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = (uint16_t)(intval);
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else if (intval >= -2147483648LL && intval <= 2147483647LL)
    {
        uint8_t val = 0xd2;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = (uint32_t)intval;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    else
    {
        uint8_t val = 0xd3;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, intval, 8);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_float(lxmsgp_pack_t* pack, float floatval)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xca;
    LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    uint32_t wval = *(uint32_t*)(&floatval);
    LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_double(lxmsgp_pack_t* pack, double doubleval)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xcb;
    LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    uint64_t wval = *(uint64_t*)(&doubleval);
    LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 8);
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_str(lxmsgp_pack_t* pack, const char* str, uint32_t length)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x1f)
    {
        uint8_t val = 0xa0 | (length & 0x1f);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else if (length <= 0xff)
    {
        uint8_t val = 0xd9;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = length & 0xff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xda;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &wval, 2);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else
    {
        uint8_t val = 0xda;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &wval, 4);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_bin(lxmsgp_pack_t* pack, const void* bin, uint32_t length)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0xff)
    {
        uint8_t val = 0xc4;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = length & 0xff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xc5;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    else
    {
        uint8_t val = 0xc6;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_array_size(lxmsgp_pack_t* pack, uint32_t length)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x0f)
    {
        uint8_t val = 0x90 | (length & 0x0f);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xdc;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else
    {
        uint8_t val = 0xdd;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_map_size(lxmsgp_pack_t* pack, uint32_t length)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x0f)
    {
        uint8_t val = 0x80 | (length & 0x0f);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xde;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else
    {
        uint8_t val = 0xdf;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_timestamp(lxmsgp_pack_t* pack, uint64_t seconds, uint32_t nanoseconds)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (seconds >> 34)
    {
        // 96 bit
        uint8_t val = 0xc7;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        int8_t stval = -1;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, nanoseconds, 4);
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, seconds, 8);
    }
    else
    {
        uint64_t w64val = ((uint64_t)nanoseconds << 34ULL) | seconds;
        if (w64val & 0xffffffff00000000ULL)
        {
            // 64 bit
            uint8_t val = 0xd7;
            LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
            int8_t stval = -1;
            LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
            LXMSGP_INTERNAL_PACK_PUT_VAL(pack, w64val, 8);
        }
        else
        {
            // 32 bit
            uint8_t val = 0xd6;
            LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
            int8_t stval = -1;
            LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
            uint32_t w32val = (uint32_t)w64val;
            LXMSGP_INTERNAL_PACK_PUT_VAL(pack, w32val, 4);
        }
    }
    return LXMSGP_TRUE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_pack_put_ext(lxmsgp_pack_t* pack, int8_t subtype, const void* data, uint32_t length)
{
    LXMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length == 1)
    {
        uint8_t val = 0xd4;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 1);
    }
    else if (length == 2)
    {
        uint8_t val = 0xd5;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 2);
    }
    else if (length == 4)
    {
        uint8_t val = 0xd6;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 4);
    }
    else if (length == 8)
    {
        uint8_t val = 0xd7;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 8);
    }
    else if (length == 16)
    {
        uint8_t val = 0xd8;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 16);
    }
    else if (length <= 0xff)
    {
        uint8_t val = 0xc7;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        val = length & 0xff;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xc8;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        uint16_t wval = length & 0xffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    else
    {
        uint8_t val = 0xc9;
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        uint32_t wval = length & 0xffffffff;
        LXMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
        LXMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    return LXMSGP_TRUE;
}

#undef LXMSGP_INTERNAL_PACK_PUT_PRECHECK
#undef LXMSGP_INTERNAL_PACK_PUT

//
//    unpack
//
#define LXMSGP_INTERNAL_FETCH_U8(to, from) \
    do { \
        to = (from)[0]; \
    } while (0)
#define LXMSGP_INTERNAL_FETCH_U16(to, from) \
    do { \
        to = ((from)[0] << 8) | (from)[1]; \
    } while (0)
#define LXMSGP_INTERNAL_FETCH_U32(to, from) \
    do { \
        to = ((uint32_t)((from)[0]) << 24) | ((uint32_t)((from)[1]) << 16) | ((uint32_t)((from)[2]) << 8) | ((uint32_t)(from)[3]); \
    } while (0)
#define LXMSGP_INTERNAL_FETCH_U64(to, from) \
    do { \
        to = ((uint64_t)((from)[0]) << 56) | ((uint64_t)((from)[1]) << 48) | ((uint64_t)((from)[2]) << 40) | ((uint64_t)((from)[3]) << 32) | ((uint64_t)((from)[4]) << 24) | ((uint64_t)((from)[5]) << 16) | ((uint64_t)((from)[6]) << 8) | (uint64_t)((from)[7]); \
    } while (0)

static lxmsgp_bool_t lxmsgp_internal_unpack_check_and_modify_ext(lxmsgp_element_t* dst_element)
{
    if (dst_element->type != LXMSGP_TYPE_EXTENSION) { return LXMSGP_FALSE; }
    switch (dst_element->content.extval.subtype)
    {
    case -1:
        // timestamp
        {
            uint32_t tu32;
            uint64_t tu64;
            switch (dst_element->content.extval.length)
            {
            case 4:
                LXMSGP_INTERNAL_FETCH_U32(tu32, (const uint8_t*)dst_element->content.extval.data);
                dst_element->type = LXMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu32;
                dst_element->content.tsval.nanoseconds = 0;
                return LXMSGP_TRUE;
            case 8:
                LXMSGP_INTERNAL_FETCH_U64(tu64, (const uint8_t*)dst_element->content.extval.data);
                dst_element->type = LXMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu64 & 0x3ffffffffULL;
                dst_element->content.tsval.nanoseconds = (uint32_t)((tu64 >> 34) & 0x3fffffffULL);
                return LXMSGP_TRUE;
            case 12:
                LXMSGP_INTERNAL_FETCH_U32(tu32, (const uint8_t*)dst_element->content.extval.data);
                LXMSGP_INTERNAL_FETCH_U64(tu64, ((const uint8_t*)dst_element->content.extval.data) + 4);
                dst_element->type = LXMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu64;
                dst_element->content.tsval.nanoseconds = tu32;
                return LXMSGP_TRUE;
            default: break;
            }
        }
        break;
    default: break;
    }
    return LXMSGP_FALSE;
}

static lxmsgp_bool_t lxmsgp_internal_unpack_fetch_element(lxmsgp_unpack_t* unpack, lxmsgp_element_t* dst_element)
{
    if (!unpack->iterator.head || unpack->iterator.head < unpack->src || (unpack->src_end && unpack->iterator.head >= unpack->src_end)) { goto fail_exit; }

#define LXMSGP_INTERNAL_CHECK_SIZE(n) \
    do { \
        if (unpack->src_end && (d + ((n) + 1) > unpack->src_end)) { unpack->last_error = LXMSGP_ERROR_INSUFFICIENT_INPUT; goto fail_exit; } \
    } while (0)

    const uint8_t* d = unpack->iterator.head;
    const uint8_t l = *d;
    uint8_t tu8;
    uint16_t tu16;
    uint32_t tu32;
    uint64_t tu64;
    if (l == 0xc0)
    {
        // nil
        dst_element->type = LXMSGP_TYPE_NIL;
        d += 1;
    }
    else if (l == 0xc2 || l == 0xc3)
    {
        // true or false
        dst_element->type = LXMSGP_TYPE_BOOL;
        dst_element->content.boolval = l == 0xc3 ? LXMSGP_TRUE : LXMSGP_FALSE;
        d += 1;
    }
    else if ((l & 0x80) == 0)
    {
        // positive fixint
        dst_element->type = LXMSGP_TYPE_UINT;
        dst_element->content.uintval = l & 0x7f;
        d += 1;
    }
    else if ((l & 0xe0) == 0xe0)
    {
        // negative fixint
        dst_element->type = LXMSGP_TYPE_INT;
        tu8 = l;
        dst_element->content.intval = *(int8_t*)(&tu8);
        d += 1;
    }
    else if (l >= 0xcc && l <= 0xcf)
    {
        // uint
        dst_element->type = LXMSGP_TYPE_UINT;
        switch (l)
        {
        case 0xcc: LXMSGP_INTERNAL_CHECK_SIZE(1); LXMSGP_INTERNAL_FETCH_U8(dst_element->content.uintval, d + 1); d += 2; break;
        case 0xcd: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(dst_element->content.uintval, d + 1); d += 3; break;
        case 0xce: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(dst_element->content.uintval, d + 1); d += 5; break;
        case 0xcf: LXMSGP_INTERNAL_CHECK_SIZE(8); LXMSGP_INTERNAL_FETCH_U64(dst_element->content.uintval, d + 1); d += 9; break;
        default: LXMSGP_ASSERT(0); dst_element->content.uintval = 0; break;
        }
    }
    else if (l >= 0xd0 && l <= 0xd3)
    {
        // int
        dst_element->type = LXMSGP_TYPE_INT;
        switch (l)
        {
        case 0xd0: LXMSGP_INTERNAL_CHECK_SIZE(1); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); dst_element->content.intval = *(int8_t*)(&tu8); d += 2; break;
        case 0xd1: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(tu16, d + 1); dst_element->content.intval = *(int16_t*)(&tu16); d += 3; break;
        case 0xd2: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); dst_element->content.intval = *(int32_t*)(&tu32); d += 5; break;
        case 0xd3: LXMSGP_INTERNAL_CHECK_SIZE(8); LXMSGP_INTERNAL_FETCH_U64(tu64, d + 1); dst_element->content.intval = *(int64_t*)(&tu64); d += 9; break;
        default: LXMSGP_ASSERT(0); dst_element->content.intval = 0; break;
        }
    }
    else if (l == 0xca || l == 0xcb)
    {
        // float or double
        switch (l)
        {
        case 0xca: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); dst_element->type = LXMSGP_TYPE_FLOAT; *(uint32_t*)(&dst_element->content.floatval) = tu32; d += 5; break;
        case 0xcb: LXMSGP_INTERNAL_CHECK_SIZE(8); LXMSGP_INTERNAL_FETCH_U64(tu64, d + 1); dst_element->type = LXMSGP_TYPE_DOUBLE; *(uint64_t*)(&dst_element->content.doubleval) = tu64; d += 9; break;
        default: LXMSGP_ASSERT(0); dst_element->type = LXMSGP_TYPE_FLOAT; dst_element->content.floatval = 0.f; break;
        }
    }
    else if ((l & 0xe0) == 0xa0)
    {
        // fixstr
        tu32 = l & 0x1f;
        LXMSGP_INTERNAL_CHECK_SIZE(tu32);
        dst_element->type = LXMSGP_TYPE_STRING;
        dst_element->content.strval.str = (const char*)(d + 1);
        dst_element->content.strval.length = tu32;
        d += tu32 + 1;
    }
    else if (l >= 0xd9 && l <= 0xdb)
    {
        // string
        switch (l)
        {
        case 0xd9: LXMSGP_INTERNAL_CHECK_SIZE(1); LXMSGP_INTERNAL_FETCH_U8(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 1); d += 1; break;
        case 0xda: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xdb: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 4); d += 4; break;
        default: LXMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_STRING;
        dst_element->content.strval.str = (const char*)(d + 1);
        dst_element->content.strval.length = tu32;
        d += tu32 + 1;
    }
    else if (l >= 0xc4 && l <= 0xc6)
    {
        // binary
        switch (l)
        {
        case 0xc4: LXMSGP_INTERNAL_CHECK_SIZE(1); LXMSGP_INTERNAL_FETCH_U8(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 1); d += 1; break;
        case 0xc5: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xc6: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 4); d += 4; break;
        default: LXMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_BINARY;
        dst_element->content.binval.bin = (const void*)(d + 1);
        dst_element->content.binval.length = tu32;
        d += tu32 + 1;
    }
    else if ((l & 0xf0) == 0x90)
    {
        // fixarray
        tu32 = l & 0x0f;
        dst_element->type = LXMSGP_TYPE_ARRAY;
        dst_element->content.arrayval.length = tu32;
        d += 1;
    }
    else if (l >= 0xdc && l <= 0xdd)
    {
        // array
        switch (l)
        {
        case 0xdc: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(tu32, d + 1); d += 2; break;
        case 0xdd: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); d += 4; break;
        default: LXMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_ARRAY;
        dst_element->content.arrayval.length = tu32;
        d += 1;
    }
    else if ((l & 0xf0) == 0x80)
    {
        // fixamap
        tu32 = l & 0x0f;
        dst_element->type = LXMSGP_TYPE_MAP;
        dst_element->content.mapval.length = tu32;
        d += 1;
    }
    else if (l >= 0xde && l <= 0xdf)
    {
        // map
        switch (l)
        {
        case 0xde: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U16(tu32, d + 1); d += 2; break;
        case 0xdf: LXMSGP_INTERNAL_CHECK_SIZE(4); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); d += 4; break;
        default: LXMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_MAP;
        dst_element->content.mapval.length = tu32;
        d += 1;
    }
    else if (l >= 0xd4 && l <= 0xd8)
    {
        // fixext
        switch (l)
        {
        case 0xd4: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 1; break;
        case 0xd5: LXMSGP_INTERNAL_CHECK_SIZE(3); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 2; break;
        case 0xd6: LXMSGP_INTERNAL_CHECK_SIZE(5); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 4; break;
        case 0xd7: LXMSGP_INTERNAL_CHECK_SIZE(9); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 8; break;
        case 0xd8: LXMSGP_INTERNAL_CHECK_SIZE(17); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 16; break;
        default: LXMSGP_ASSERT(0); tu8 = 0; tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_EXTENSION;
        dst_element->content.extval.subtype = *(int8_t*)(&tu8);
        dst_element->content.extval.data = (const void*)(d + 2);
        dst_element->content.extval.length = tu32;
        d += tu32 + 2;
        lxmsgp_internal_unpack_check_and_modify_ext(dst_element);
    }
    else if (l >= 0xc7 && l <= 0xc9)
    {
        // ext
        switch (l)
        {
        case 0xc7: LXMSGP_INTERNAL_CHECK_SIZE(2); LXMSGP_INTERNAL_FETCH_U8(tu32, d + 1); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 2); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xc8: LXMSGP_INTERNAL_CHECK_SIZE(3); LXMSGP_INTERNAL_FETCH_U16(tu32, d + 1); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 3); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 3); d += 3; break;
        case 0xc9: LXMSGP_INTERNAL_CHECK_SIZE(5); LXMSGP_INTERNAL_FETCH_U32(tu32, d + 1); LXMSGP_INTERNAL_FETCH_U8(tu8, d + 5); LXMSGP_INTERNAL_CHECK_SIZE(tu32 + 5); d += 5; break;
        default: LXMSGP_ASSERT(0); tu8 = 0; tu32 = 0; break;
        }
        dst_element->type = LXMSGP_TYPE_EXTENSION;
        dst_element->content.extval.subtype = *(int8_t*)(&tu8);
        dst_element->content.extval.data = (const void*)(d + 1);
        dst_element->content.extval.length = tu32;
        d += tu32 + 1;
        lxmsgp_internal_unpack_check_and_modify_ext(dst_element);
    }
    else
    {
        goto fail_exit;
    }

    // check boundary
    if (unpack->src_end && d > unpack->src_end) { goto fail_exit; }

    unpack->next_iterator.head = d;
    return LXMSGP_TRUE;

fail_exit:
    dst_element->type = LXMSGP_TYPE_UNKNOWN;
    unpack->next_iterator.head = NULL;
    return LXMSGP_FALSE;
}

#undef LXMSGP_INTERNAL_CHECK_SIZE
#undef LXMSGP_INTERNAL_FETCH_U8
#undef LXMSGP_INTERNAL_FETCH_U16
#undef LXMSGP_INTERNAL_FETCH_U32
#undef LXMSGP_INTERNAL_FETCH_U64

LXMSGP_API void lxmsgp_unpack_init(lxmsgp_unpack_t* unpack, const void* src, size_t src_size)
{
    lxmsgp_unpack_init_ex(unpack, src, src_size, NULL, NULL);
}

LXMSGP_API void lxmsgp_unpack_init_ex(lxmsgp_unpack_t* unpack, const void* src, size_t src_size, lxmsgp_unpack_fin_func_t fin_func, void* user)
{
    unpack->src = (const uint8_t*)src;
    unpack->src_size = src_size;
    unpack->src_end = unpack->src + unpack->src_size;
    unpack->iterator.head = unpack->src;
    unpack->last_error = LXMSGP_ERROR_NONE;
    unpack->fin_func = fin_func;
    unpack->user = user;
    lxmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
}

LXMSGP_API void lxmsgp_unpack_fin(lxmsgp_unpack_t* unpack)
{
    if (unpack->fin_func) { unpack->fin_func(unpack->user, unpack); }
    unpack->src = NULL;
    unpack->src_size = 0;
    unpack->src_end = NULL;
    unpack->iterator.head = NULL;
    unpack->last_error = LXMSGP_ERROR_NONE;
    unpack->element.type = LXMSGP_TYPE_UNKNOWN;
    unpack->fin_func = NULL;
    unpack->user = NULL;
}

#if !defined(LXMSGP_NO_MEMORY_API) && !defined(LXMSGP_NO_STDIO_FILE_API)
static void lxmsgp_internal_unpack_file_fin_callback(void* user, lxmsgp_unpack_t* unpack)
{
    (void)(user);
    if (unpack->src)
    {
        void* allocated = (void*)(unpack->src);
        LXMSGP_FREE(allocated, user);
    }
}

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_init_file(lxmsgp_unpack_t* unpack, const char* filepath, void* alloc_user)
{
    FILE* file = fopen(filepath, "rb");
    if (!file) { return LXMSGP_FALSE; }
    const int size = fseek(file, 0, SEEK_END);
    if (size < 0) { fclose(file); return LXMSGP_FALSE; }
    fseek(file, 0, SEEK_SET);
    void* filecontent = LXMSGP_MALLOC(size + 1, alloc_user);
    if (!filecontent) { fclose(file); return LXMSGP_FALSE; }
    const size_t readsize = fread(filecontent, 1, (size_t)size, file);
    lxmsgp_unpack_init_ex(unpack, filecontent, readsize, &lxmsgp_internal_unpack_file_fin_callback, alloc_user);
    return LXMSGP_TRUE;
}
#endif // !LXMSGP_NO_MEMORY_API && !LXMSGP_NO_STDIO_FILE_API

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_eof(const lxmsgp_unpack_t* unpack)
{
    return (unpack->src_end && unpack->iterator.head >= unpack->src_end) ? LXMSGP_TRUE : LXMSGP_FALSE;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_get_element(const lxmsgp_unpack_t* unpack, lxmsgp_element_t* dst_element)
{
    if (dst_element) { *dst_element = unpack->element; }
    return unpack->element.type != LXMSGP_TYPE_UNKNOWN;
}

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_next(lxmsgp_unpack_t* unpack)
{
    unpack->iterator = unpack->next_iterator;
    lxmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
    return unpack->element.type != LXMSGP_TYPE_UNKNOWN;
}

LXMSGP_API size_t lxmsgp_unpack_skip(lxmsgp_unpack_t* unpack, size_t skip_num)
{
    size_t skipped = 0;
    while (skipped < skip_num && lxmsgp_unpack_get_element(unpack, NULL)) { lxmsgp_unpack_next(unpack); ++skipped; }
    return skipped;
}

LXMSGP_API lxmsgp_iterator_t lxmsgp_unpack_get_iterator(const lxmsgp_unpack_t* unpack)
{
    return unpack->iterator;
}

LXMSGP_API void lxmsgp_unpack_set_iterator(lxmsgp_unpack_t* unpack, lxmsgp_iterator_t iterator)
{
    unpack->iterator = iterator;
    lxmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
}

LXMSGP_API lxmsgp_bool_t lxmsgp_unpack_get_element_from_iterator_unsafe(const lxmsgp_iterator_t* iterator, lxmsgp_element_t* dst_element)
{
    lxmsgp_unpack_t unpack;
    lxmsgp_unpack_init(&unpack, iterator->head, 0);
    unpack.src_end = NULL;
    return lxmsgp_unpack_get_element(&unpack, dst_element);
}

#endif // LXMSGP_IMPLEMENTATION_INCLUDED
#endif // LXMSGP_IMPLEMENTATION

/*
Creative Commons Legal Code

CC0 1.0 Universal

    CREATIVE COMMONS CORPORATION IS NOT A LAW FIRM AND DOES NOT PROVIDE
    LEGAL SERVICES. DISTRIBUTION OF THIS DOCUMENT DOES NOT CREATE AN
    ATTORNEY-CLIENT RELATIONSHIP. CREATIVE COMMONS PROVIDES THIS
    INFORMATION ON AN "AS-IS" BASIS. CREATIVE COMMONS MAKES NO WARRANTIES
    REGARDING THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS
    PROVIDED HEREUNDER, AND DISCLAIMS LIABILITY FOR DAMAGES RESULTING FROM
    THE USE OF THIS DOCUMENT OR THE INFORMATION OR WORKS PROVIDED
    HEREUNDER.

Statement of Purpose

The laws of most jurisdictions throughout the world automatically confer
exclusive Copyright and Related Rights (defined below) upon the creator
and subsequent owner(s) (each and all, an "owner") of an original work of
authorship and/or a database (each, a "Work").

Certain owners wish to permanently relinquish those rights to a Work for
the purpose of contributing to a commons of creative, cultural and
scientific works ("Commons") that the public can reliably and without fear
of later claims of infringement build upon, modify, incorporate in other
works, reuse and redistribute as freely as possible in any form whatsoever
and for any purposes, including without limitation commercial purposes.
These owners may contribute to the Commons to promote the ideal of a free
culture and the further production of creative, cultural and scientific
works, or to gain reputation or greater distribution for their Work in
part through the use and efforts of others.

For these and/or other purposes and motivations, and without any
expectation of additional consideration or compensation, the person
associating CC0 with a Work (the "Affirmer"), to the extent that he or she
is an owner of Copyright and Related Rights in the Work, voluntarily
elects to apply CC0 to the Work and publicly distribute the Work under its
terms, with knowledge of his or her Copyright and Related Rights in the
Work and the meaning and intended legal effect of CC0 on those rights.

1. Copyright and Related Rights. A Work made available under CC0 may be
protected by copyright and related or neighboring rights ("Copyright and
Related Rights"). Copyright and Related Rights include, but are not
limited to, the following:

  i. the right to reproduce, adapt, distribute, perform, display,
     communicate, and translate a Work;
 ii. moral rights retained by the original author(s) and/or performer(s);
iii. publicity and privacy rights pertaining to a person's image or
     likeness depicted in a Work;
 iv. rights protecting against unfair competition in regards to a Work,
     subject to the limitations in paragraph 4(a), below;
  v. rights protecting the extraction, dissemination, use and reuse of data
     in a Work;
 vi. database rights (such as those arising under Directive 96/9/EC of the
     European Parliament and of the Council of 11 March 1996 on the legal
     protection of databases, and under any national implementation
     thereof, including any amended or successor version of such
     directive); and
vii. other similar, equivalent or corresponding rights throughout the
     world based on applicable law or treaty, and any national
     implementations thereof.

2. Waiver. To the greatest extent permitted by, but not in contravention
of, applicable law, Affirmer hereby overtly, fully, permanently,
irrevocably and unconditionally waives, abandons, and surrenders all of
Affirmer's Copyright and Related Rights and associated claims and causes
of action, whether now known or unknown (including existing as well as
future claims and causes of action), in the Work (i) in all territories
worldwide, (ii) for the maximum duration provided by applicable law or
treaty (including future time extensions), (iii) in any current or future
medium and for any number of copies, and (iv) for any purpose whatsoever,
including without limitation commercial, advertising or promotional
purposes (the "Waiver"). Affirmer makes the Waiver for the benefit of each
member of the public at large and to the detriment of Affirmer's heirs and
successors, fully intending that such Waiver shall not be subject to
revocation, rescission, cancellation, termination, or any other legal or
equitable action to disrupt the quiet enjoyment of the Work by the public
as contemplated by Affirmer's express Statement of Purpose.

3. Public License Fallback. Should any part of the Waiver for any reason
be judged legally invalid or ineffective under applicable law, then the
Waiver shall be preserved to the maximum extent permitted taking into
account Affirmer's express Statement of Purpose. In addition, to the
extent the Waiver is so judged Affirmer hereby grants to each affected
person a royalty-free, non transferable, non sublicensable, non exclusive,
irrevocable and unconditional license to exercise Affirmer's Copyright and
Related Rights in the Work (i) in all territories worldwide, (ii) for the
maximum duration provided by applicable law or treaty (including future
time extensions), (iii) in any current or future medium and for any number
of copies, and (iv) for any purpose whatsoever, including without
limitation commercial, advertising or promotional purposes (the
"License"). The License shall be deemed effective as of the date CC0 was
applied by Affirmer to the Work. Should any part of the License for any
reason be judged legally invalid or ineffective under applicable law, such
partial invalidity or ineffectiveness shall not invalidate the remainder
of the License, and in such case Affirmer hereby affirms that he or she
will not (i) exercise any of his or her remaining Copyright and Related
Rights in the Work or (ii) assert any associated claims and causes of
action with respect to the Work, in either case contrary to Affirmer's
express Statement of Purpose.

4. Limitations and Disclaimers.

 a. No trademark or patent rights held by Affirmer are waived, abandoned,
    surrendered, licensed or otherwise affected by this document.
 b. Affirmer offers the Work as-is and makes no representations or
    warranties of any kind concerning the Work, express, implied,
    statutory or otherwise, including without limitation warranties of
    title, merchantability, fitness for a particular purpose, non
    infringement, or the absence of latent or other defects, accuracy, or
    the present or absence of errors, whether or not discoverable, all to
    the greatest extent permissible under applicable law.
 c. Affirmer disclaims responsibility for clearing rights of other persons
    that may apply to the Work or any use thereof, including without
    limitation any person's Copyright and Related Rights in the Work.
    Further, Affirmer disclaims responsibility for obtaining any necessary
    consents, permissions or other rights required for any use of the
    Work.
 d. Affirmer understands and acknowledges that Creative Commons is not a
    party to this document and has no duty or obligation with respect to
    this CC0 or use of the Work.

For more information, please see
<http://creativecommons.org/publicdomain/zero/1.0/>
*/

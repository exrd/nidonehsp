//-----------------------------------------------------------------------------
/*
    picomsgpack.h
      msgpack read/write implementation in C written by exrd.
      picomsgpack is licensed under CC0 1.0 Universal, see end of this file for more detail.
*/
//-----------------------------------------------------------------------------

#ifndef PMSGP_HEADER_INCLUDED
#define PMSGP_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    customization
//

// linkage
#ifdef PMSGP_STATIC
#define PMSGP_API  static
#else
#define PMSGP_API
#endif // PMSGP_STATIC

// assert
#ifndef PMSGP_ASSERT
#include <assert.h>
#define PMSGP_ASSERT    assert
#endif // PMSGP_ASSERT

// memory api
#ifndef PMSGP_NO_MEMORY_API
// malloc, free, realloc
#ifndef PMSGP_MALLOC
#include <stdlib.h>
#define PMSGP_MALLOC(size, user)        malloc(size)
#define PMSGP_FREE(ptr, user)           free(ptr)
#define PMSGP_REALLOC_SIZED(oldptr, newsize, oldsize, user)     realloc(oldptr, newsize)
#endif // PMSGP_MALLOC
// memcpy
#ifndef PMSGP_MEMCPY
#include <string.h>
#define PMSGP_MEMCPY(dst, src, size)    memcpy(dst, src, size)
#endif // PMSGP_MEMCPY
#endif // PMSGP_NO_MEMORY_API

// file api
#ifndef PMSGP_NO_STDIO_FILE_API
#include <stdio.h>
#endif // PMSGP_NO_STDIO_FILE_API

//-----------------------------------------------------------------------------
//
//    forward declaration
//
#include <stddef.h>
#include <stdint.h>

//
//    common
//
typedef int pmsgp_bool_t;
#define PMSGP_TRUE  (1)
#define PMSGP_FALSE (0)

typedef enum
{
    PMSGP_TYPE_UNKNOWN = -1,
    PMSGP_TYPE_NIL = 0,
    PMSGP_TYPE_BOOL,
    PMSGP_TYPE_UINT,
    PMSGP_TYPE_INT,
    PMSGP_TYPE_FLOAT,
    PMSGP_TYPE_DOUBLE,
    PMSGP_TYPE_STRING,
    PMSGP_TYPE_BINARY,
    PMSGP_TYPE_ARRAY,
    PMSGP_TYPE_MAP,
    PMSGP_TYPE_TIMESTAMP,
    PMSGP_TYPE_EXTENSION,

    PMSGP_TYPE_COUNT
} pmsgp_type_e;

typedef enum
{
    PMSGP_ERROR_NONE = 0,
    // for pack
    PMSGP_ERROR_FLUSH_FAILED,
    // for unpack
    PMSGP_ERROR_ILLEGAL_VALUE,
    PMSGP_ERROR_INSUFFICIENT_INPUT,
} pmsgp_error_e;

PMSGP_API pmsgp_bool_t pmsgp_type_is_integral(pmsgp_type_e type);
PMSGP_API pmsgp_bool_t pmsgp_type_is_floating_point(pmsgp_type_e type);
PMSGP_API pmsgp_bool_t pmsgp_type_is_number(pmsgp_type_e type);

//
//    value representation
//
typedef struct pmsgp_value_string_t pmsgp_value_string_t;
struct pmsgp_value_string_t
{
    const char* str;
    uint32_t length;
};

typedef struct pmsgp_value_binary_t pmsgp_value_binary_t;
struct pmsgp_value_binary_t
{
    const void* bin;
    uint32_t length;
};

typedef struct pmsgp_value_array_t pmsgp_value_array_t;
struct pmsgp_value_array_t
{
    uint32_t length;
};

typedef struct pmsgp_value_map_t pmsgp_value_map_t;
struct pmsgp_value_map_t
{
    uint32_t length;
};

typedef struct pmsgp_value_timestamp_t pmsgp_value_timestamp_t;
struct pmsgp_value_timestamp_t
{
    uint64_t seconds;
    uint32_t nanoseconds;
};

typedef struct pmsgp_value_extension_t pmsgp_value_extension_t;
struct pmsgp_value_extension_t
{
    int8_t subtype;
    const void* data;
    uint32_t length;
};

//
//    element
//
typedef union pmsgp_content_t pmsgp_content_t;
union pmsgp_content_t
{
    pmsgp_bool_t boolval;// for PMSGP_TYPE_BOOL
    uint64_t uintval;// for PMSGP_TYPE_UINT
    int64_t intval;// for PMSGP_TYPE_INT
    float floatval;// for PMSGP_TYPE_FLOAT
    double doubleval;// for PMSGP_TYPE_DOUBLE
    pmsgp_value_string_t strval;// for PMSGP_TYPE_STRING
    pmsgp_value_binary_t binval;// for PMSGP_TYPE_BINARY
    pmsgp_value_array_t arrayval;// for PMSGP_TYPE_ARRAY
    pmsgp_value_map_t mapval;// for PMSGP_TYPE_MAP
    pmsgp_value_timestamp_t tsval;// for PMSGP_TYPE_TIMESTAMP
    pmsgp_value_extension_t extval;// for PMSGP_TYPE_EXTENSION
};

typedef struct pmsgp_element_t pmsgp_element_t;
struct pmsgp_element_t
{
    pmsgp_type_e type;
    pmsgp_content_t content;
};

PMSGP_API pmsgp_bool_t pmsgp_element_as_int(const pmsgp_element_t* element, int64_t* dst_intval);
PMSGP_API pmsgp_bool_t pmsgp_element_as_uint(const pmsgp_element_t* element, uint64_t* dst_uintval);
PMSGP_API pmsgp_bool_t pmsgp_element_as_float(const pmsgp_element_t* element, float* dst_floatval);
PMSGP_API pmsgp_bool_t pmsgp_element_as_double(const pmsgp_element_t* element, double* dst_doubleval);

//
//    pack
//
typedef struct pmsgp_pack_t pmsgp_pack_t;

typedef pmsgp_bool_t (*pmsgp_pack_write_func_t)(void* user, const void* data, size_t length);
typedef void (*pmsgp_pack_fin_func_t)(void* user, pmsgp_pack_t* pack);

struct pmsgp_pack_t
{
    pmsgp_error_e last_error;// last error
    size_t total_size;// written total byte size
    pmsgp_pack_write_func_t write_func;// user provided write func
    pmsgp_pack_fin_func_t fin_func;// user provided fin func
    void* user;// user context for write/fin func
};

PMSGP_API void pmsgp_pack_init(pmsgp_pack_t* pack, pmsgp_pack_write_func_t write_func, pmsgp_pack_fin_func_t fin_func, void* user);
PMSGP_API void pmsgp_pack_fin(pmsgp_pack_t* pack);

#ifndef PMSGP_NO_MEMORY_API
PMSGP_API void pmsgp_pack_init_memory(pmsgp_pack_t* pack, void* alloc_user);
PMSGP_API void pmsgp_pack_init_memory_ex(pmsgp_pack_t* pack, size_t initial_buffer_size, size_t buffer_expand_step, void* alloc_user);
PMSGP_API const void* pmsgp_pack_get_memory(const pmsgp_pack_t* pack, size_t* dst_size);
#endif // PMSGP_NO_MEMORY_API

#ifndef PMSGP_NO_STDIO_FILE_API
PMSGP_API pmsgp_bool_t pmsgp_pack_init_file(pmsgp_pack_t* pack, const char* filepath);
#endif // PMSGP_NO_STDIO_FILE_API

PMSGP_API pmsgp_error_e pmsgp_pack_get_error(const pmsgp_pack_t* pack);

PMSGP_API pmsgp_bool_t pmsgp_pack_put_nil(pmsgp_pack_t* pack);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_bool(pmsgp_pack_t* pack, pmsgp_bool_t boolval);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_uint(pmsgp_pack_t* pack, uint64_t uintval);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_int(pmsgp_pack_t* pack, int64_t intval);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_float(pmsgp_pack_t* pack, float floatval);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_double(pmsgp_pack_t* pack, double doubleval);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_str(pmsgp_pack_t* pack, const char* str, uint32_t length);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_bin(pmsgp_pack_t* pack, const void* bin, uint32_t length);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_array_size(pmsgp_pack_t* pack, uint32_t length);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_map_size(pmsgp_pack_t* pack, uint32_t length);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_timestamp(pmsgp_pack_t* pack, uint64_t seconds, uint32_t nanoseconds);
PMSGP_API pmsgp_bool_t pmsgp_pack_put_ext(pmsgp_pack_t* pack, int8_t subtype, const void* data, uint32_t length);

//
//    unpack
//
typedef struct pmsgp_iterator_t pmsgp_iterator_t;
struct pmsgp_iterator_t
{
    const uint8_t* head;// element head ptr
};

typedef struct pmsgp_unpack_t pmsgp_unpack_t;

typedef void (*pmsgp_unpack_fin_func_t)(void* user, pmsgp_unpack_t* unpack);

struct pmsgp_unpack_t
{
    const uint8_t* src;// source data
    size_t src_size;// size of source data
    const uint8_t* src_end;// end of source data
    pmsgp_iterator_t iterator;// current iterator
    pmsgp_iterator_t next_iterator;// next iterator
    pmsgp_element_t element;// current element
    pmsgp_error_e last_error;// last error
    pmsgp_unpack_fin_func_t fin_func;// fin func
    void* user;// user context for fin func
};

PMSGP_API void pmsgp_unpack_init(pmsgp_unpack_t* unpack, const void* src, size_t src_size);
PMSGP_API void pmsgp_unpack_init_ex(pmsgp_unpack_t* unpack, const void* src, size_t src_size, pmsgp_unpack_fin_func_t fin_func, void* user);
PMSGP_API void pmsgp_unpack_fin(pmsgp_unpack_t* unpack);

#if !defined(PMSGP_NO_MEMORY_API) && !defined(PMSGP_NO_STDIO_FILE_API)
PMSGP_API pmsgp_bool_t pmsgp_unpack_init_file(pmsgp_unpack_t* unpack, const char* filepath, void* alloc_user);
#endif // !PMSGP_NO_MEMORY_API && !PMSGP_NO_STDIO_FILE_API

PMSGP_API pmsgp_bool_t pmsgp_unpack_eof(const pmsgp_unpack_t* unpack);
PMSGP_API pmsgp_bool_t pmsgp_unpack_get_element(const pmsgp_unpack_t* unpack, pmsgp_element_t* dst_element);
PMSGP_API pmsgp_bool_t pmsgp_unpack_next(pmsgp_unpack_t* unpack);
PMSGP_API size_t pmsgp_unpack_skip(pmsgp_unpack_t* unpack, size_t skip_num);
PMSGP_API pmsgp_iterator_t pmsgp_unpack_get_iterator(const pmsgp_unpack_t* unpack);
PMSGP_API void pmsgp_unpack_set_iterator(pmsgp_unpack_t* unpack, pmsgp_iterator_t iterator);

PMSGP_API pmsgp_bool_t pmsgp_unpack_get_element_from_iterator_unsafe(const pmsgp_iterator_t* iterator, pmsgp_element_t* dst_element);

#endif // PMSGP_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    implementation
//
#ifdef PMSGP_IMPLEMENTATION
#ifndef PMSGP_IMPLEMENTATION_INCLUDED
#define PMSGP_IMPLEMENTATION_INCLUDED

//
//    common
//
PMSGP_API pmsgp_bool_t pmsgp_type_is_integral(pmsgp_type_e type)
{
    switch (type)
    {
    case PMSGP_TYPE_UINT:
    case PMSGP_TYPE_INT:
        return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_type_is_floating_point(pmsgp_type_e type)
{
    switch (type)
    {
    case PMSGP_TYPE_FLOAT:
    case PMSGP_TYPE_DOUBLE:
        return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_type_is_number(pmsgp_type_e type)
{
    switch (type)
    {
    case PMSGP_TYPE_UINT:
    case PMSGP_TYPE_INT:
    case PMSGP_TYPE_FLOAT:
    case PMSGP_TYPE_DOUBLE:
        return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

//
//    element
//
PMSGP_API pmsgp_bool_t pmsgp_element_as_int(const pmsgp_element_t* element, int64_t* dst_intval)
{
    switch (element->type)
    {
    case PMSGP_TYPE_INT: *dst_intval = element->content.intval; return PMSGP_TRUE;
    case PMSGP_TYPE_UINT: if (element->content.uintval > INT64_MAX) { return PMSGP_FALSE; } *dst_intval = (int64_t)element->content.uintval; return PMSGP_TRUE;
    case PMSGP_TYPE_FLOAT: *dst_intval = (int64_t)element->content.floatval; return PMSGP_TRUE;
    case PMSGP_TYPE_DOUBLE: *dst_intval = (int64_t)element->content.doubleval; return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_element_as_uint(const pmsgp_element_t* element, uint64_t* dst_uintval)
{
    switch (element->type)
    {
    case PMSGP_TYPE_INT: if (element->content.intval < 0) { return PMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.intval; return PMSGP_TRUE;
    case PMSGP_TYPE_UINT: *dst_uintval = element->content.uintval; return PMSGP_TRUE;
    case PMSGP_TYPE_FLOAT: if (element->content.floatval < 0) { return PMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.floatval; return PMSGP_TRUE;
    case PMSGP_TYPE_DOUBLE: if (element->content.doubleval < 0) { return PMSGP_FALSE; } *dst_uintval = (uint64_t)element->content.doubleval; return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_element_as_float(const pmsgp_element_t* element, float* dst_floatval)
{
    switch (element->type)
    {
    case PMSGP_TYPE_INT: *dst_floatval = (float)element->content.intval; return PMSGP_TRUE;
    case PMSGP_TYPE_UINT: *dst_floatval = (float)element->content.uintval; return PMSGP_TRUE;
    case PMSGP_TYPE_FLOAT: *dst_floatval = (float)element->content.floatval; return PMSGP_TRUE;
    case PMSGP_TYPE_DOUBLE: *dst_floatval = (float)element->content.doubleval; return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_element_as_double(const pmsgp_element_t* element, double* dst_doubleval)
{
    switch (element->type)
    {
    case PMSGP_TYPE_INT: *dst_doubleval = (double)element->content.intval; return PMSGP_TRUE;
    case PMSGP_TYPE_UINT: *dst_doubleval = (double)element->content.uintval; return PMSGP_TRUE;
    case PMSGP_TYPE_FLOAT: *dst_doubleval = (double)element->content.floatval; return PMSGP_TRUE;
    case PMSGP_TYPE_DOUBLE: *dst_doubleval = (double)element->content.doubleval; return PMSGP_TRUE;
    default: break;
    }
    return PMSGP_FALSE;
}

//
//    pack
//
PMSGP_API void pmsgp_pack_init(pmsgp_pack_t* pack, pmsgp_pack_write_func_t write_func, pmsgp_pack_fin_func_t fin_func, void* user)
{
    pack->last_error = PMSGP_ERROR_NONE;
    pack->total_size = 0;
    pack->write_func = write_func;
    pack->fin_func = fin_func;
    pack->user = user;
}

PMSGP_API void pmsgp_pack_fin(pmsgp_pack_t* pack)
{
    if (pack->fin_func) { pack->fin_func(pack->user, pack); }
    pack->last_error = PMSGP_ERROR_NONE;
    pack->write_func = NULL;
    pack->fin_func = NULL;
    pack->user = NULL;
}

#ifndef PMSGP_NO_MEMORY_API
typedef struct pmsgp_internal_pack_memory_t pmsgp_internal_pack_memory_t;
struct pmsgp_internal_pack_memory_t
{
    uint8_t* buffer;
    size_t buffer_size;
    size_t buffer_expand_step;
    size_t written_size;
    void* alloc_user;
};

static pmsgp_bool_t pmsgp_internal_pack_memory_flush_callback(void* user, const void* data, size_t length)
{
    pmsgp_internal_pack_memory_t* m = (pmsgp_internal_pack_memory_t*)user;
    if (!m->buffer || m->written_size + length > m->buffer_size)
    {
        if (m->buffer)
        {
            size_t expand_step = m->buffer_expand_step ? m->buffer_expand_step : m->buffer_size;
            if (expand_step < length) { expand_step = length; }
            uint8_t* next_buffer = (uint8_t*)(PMSGP_REALLOC_SIZED(m->buffer, m->buffer_size + expand_step, m->buffer_size, m->alloc_user));
            if (!next_buffer) { return PMSGP_FALSE; }// failed to realloc
            m->buffer = next_buffer;
        }
        else
        {
            m->buffer = (uint8_t*)(PMSGP_MALLOC(length, m->alloc_user));
        }
    }
    PMSGP_ASSERT(m->buffer);
    PMSGP_MEMCPY(m->buffer + m->written_size, data, length);
    m->written_size += length;
    return PMSGP_TRUE;
}

static void pmsgp_internal_pack_memory_fin_callback(void* user, pmsgp_pack_t* pack)
{
    (void)(pack);
    pmsgp_internal_pack_memory_t* m = (pmsgp_internal_pack_memory_t*)user;
    void* alloc_user = m->alloc_user;
    (void)(alloc_user);
    PMSGP_FREE(m->buffer, alloc_user);
    PMSGP_FREE(m, alloc_user);
}

PMSGP_API void pmsgp_pack_init_memory(pmsgp_pack_t* pack, void* alloc_user)
{
    pmsgp_pack_init_memory_ex(pack, 1024, 1024, alloc_user);
}

PMSGP_API void pmsgp_pack_init_memory_ex(pmsgp_pack_t* pack, size_t initial_buffer_size, size_t buffer_expand_step, void* alloc_user)
{
    pmsgp_internal_pack_memory_t* m = (pmsgp_internal_pack_memory_t*)(PMSGP_MALLOC(sizeof(pmsgp_internal_pack_memory_t), alloc_user));
    PMSGP_ASSERT(m);
    m->buffer = (uint8_t*)(initial_buffer_size == 0 ? NULL : PMSGP_MALLOC(initial_buffer_size, alloc_user));
    m->buffer_size = initial_buffer_size;
    m->buffer_expand_step = buffer_expand_step;
    m->written_size = 0;
    m->alloc_user = alloc_user;
    pmsgp_pack_init(pack, &pmsgp_internal_pack_memory_flush_callback, &pmsgp_internal_pack_memory_fin_callback, m);
}

PMSGP_API const void* pmsgp_pack_get_memory(const pmsgp_pack_t* pack, size_t* dst_size)
{
    const pmsgp_internal_pack_memory_t* m = (const pmsgp_internal_pack_memory_t*)pack->user;
    if (dst_size) { *dst_size = m->written_size; }
    return m->buffer;
}
#endif // PMSGP_NO_MEMORY_API

#ifndef PMSGP_NO_STDIO_FILE_API
static pmsgp_bool_t pmsgp_internal_pack_file_flush_callback(void* user, const void* data, size_t length)
{
    FILE* file = (FILE*)user;
    if (!file) { return PMSGP_FALSE; }
    fwrite(data, 1, length, file);
    return PMSGP_TRUE;
}

static void pmsgp_internal_pack_file_fin_callback(void* user, pmsgp_pack_t* pack)
{
    (void)(pack);
    FILE* file = (FILE*)user;
    if (file) { fclose(file); }
}

PMSGP_API pmsgp_bool_t pmsgp_pack_init_file(pmsgp_pack_t* pack, const char* filepath)
{
    FILE* file = fopen(filepath, "wb");
    if (!file) { return PMSGP_FALSE; }
    pmsgp_pack_init(pack, &pmsgp_internal_pack_file_flush_callback, &pmsgp_internal_pack_file_fin_callback, file);
    return PMSGP_TRUE;
}
#endif // PMSGP_NO_STDIO_FILE_API

PMSGP_API pmsgp_error_e pmsgp_pack_get_error(const pmsgp_pack_t* pack)
{
    return pack->last_error;
}

#define PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack) \
    do { \
        if ((pack)->last_error != PMSGP_ERROR_NONE) { return PMSGP_FALSE; } \
    } while (0)
#define PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, size) \
    do { \
        if ((pack)->write_func) \
        { \
            if (!(pack)->write_func(pack->user, (data), (size))) \
            { \
                (pack)->last_error = PMSGP_ERROR_FLUSH_FAILED; \
                return PMSGP_FALSE; \
            } \
        } \
        (pack)->total_size += (size); \
    } while (0)
#define PMSGP_INTERNAL_PACK_PUT_VAL(pack, val, size) \
    do { \
        uint8_t mem[8]; \
        for (size_t i = 0; i < size; ++i) { mem[i] = ((val) >> ((size - i - 1) * 8)) & 0xff; } \
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, mem, size); \
    } while (0)

PMSGP_API pmsgp_bool_t pmsgp_pack_put_nil(pmsgp_pack_t* pack)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xc0;
    PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_bool(pmsgp_pack_t* pack, pmsgp_bool_t boolval)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = boolval ? 0xc3 : 0xc2;
    PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_uint(pmsgp_pack_t* pack, uint64_t uintval)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (uintval <= 0x7f)
    {
        uint8_t val = uintval & 0x7f;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (uintval <= 0xff)
    {
        uint8_t val = 0xcc;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = uintval & 0xff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (uintval <= 0xffff)
    {
        uint8_t val = 0xcd;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = uintval & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else if (uintval <= 0xffffffff)
    {
        uint8_t val = 0xce;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = uintval & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    else
    {
        uint8_t val = 0xcf;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, uintval, 8);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_int(pmsgp_pack_t* pack, int64_t intval)
{
    //if (intval >= 0x0) { return pmsgp_pack_put_uint(pack, (uint64_t)intval); }
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (intval >= -128 && intval <= 127)
    {
        uint8_t val = 0xd0;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = (uint8_t)(intval);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (intval >= -32768 && intval <= 32767)
    {
        uint8_t val = 0xd1;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = (uint16_t)(intval);
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else if (intval >= -2147483648LL && intval <= 2147483647LL)
    {
        uint8_t val = 0xd2;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = (uint32_t)intval;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    else
    {
        uint8_t val = 0xd3;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, intval, 8);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_float(pmsgp_pack_t* pack, float floatval)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xca;
    PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    uint32_t wval = *(uint32_t*)(&floatval);
    PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_double(pmsgp_pack_t* pack, double doubleval)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    uint8_t val = 0xcb;
    PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    uint64_t wval = *(uint64_t*)(&doubleval);
    PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 8);
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_str(pmsgp_pack_t* pack, const char* str, uint32_t length)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x1f)
    {
        uint8_t val = 0xa0 | (length & 0x1f);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else if (length <= 0xff)
    {
        uint8_t val = 0xd9;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = length & 0xff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xda;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &wval, 2);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    else
    {
        uint8_t val = 0xda;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &wval, 4);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, str, length);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_bin(pmsgp_pack_t* pack, const void* bin, uint32_t length)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0xff)
    {
        uint8_t val = 0xc4;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        val = length & 0xff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xc5;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    else
    {
        uint8_t val = 0xc6;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, bin, length);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_array_size(pmsgp_pack_t* pack, uint32_t length)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x0f)
    {
        uint8_t val = 0x90 | (length & 0x0f);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xdc;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else
    {
        uint8_t val = 0xdd;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_map_size(pmsgp_pack_t* pack, uint32_t length)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length <= 0x0f)
    {
        uint8_t val = 0x80 | (length & 0x0f);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xde;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint16_t wval = length & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
    }
    else
    {
        uint8_t val = 0xdf;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        uint32_t wval = length & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_timestamp(pmsgp_pack_t* pack, uint64_t seconds, uint32_t nanoseconds)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (seconds >> 34)
    {
        // 96 bit
        uint8_t val = 0xc7;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        int8_t stval = -1;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, nanoseconds, 4);
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, seconds, 8);
    }
    else
    {
        uint64_t w64val = ((uint64_t)nanoseconds << 34ULL) | seconds;
        if (w64val & 0xffffffff00000000ULL)
        {
            // 64 bit
            uint8_t val = 0xd7;
            PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
            int8_t stval = -1;
            PMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
            PMSGP_INTERNAL_PACK_PUT_VAL(pack, w64val, 8);
        }
        else
        {
            // 32 bit
            uint8_t val = 0xd6;
            PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
            int8_t stval = -1;
            PMSGP_INTERNAL_PACK_PUT_PTR(pack, &stval, 1);
            uint32_t w32val = (uint32_t)w64val;
            PMSGP_INTERNAL_PACK_PUT_VAL(pack, w32val, 4);
        }
    }
    return PMSGP_TRUE;
}

PMSGP_API pmsgp_bool_t pmsgp_pack_put_ext(pmsgp_pack_t* pack, int8_t subtype, const void* data, uint32_t length)
{
    PMSGP_INTERNAL_PACK_PUT_PRECHECK(pack);
    if (length == 1)
    {
        uint8_t val = 0xd4;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 1);
    }
    else if (length == 2)
    {
        uint8_t val = 0xd5;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 2);
    }
    else if (length == 4)
    {
        uint8_t val = 0xd6;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 4);
    }
    else if (length == 8)
    {
        uint8_t val = 0xd7;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 8);
    }
    else if (length == 16)
    {
        uint8_t val = 0xd8;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, 16);
    }
    else if (length <= 0xff)
    {
        uint8_t val = 0xc7;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        val = length & 0xff;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    else if (length <= 0xffff)
    {
        uint8_t val = 0xc8;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        uint16_t wval = length & 0xffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 2);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    else
    {
        uint8_t val = 0xc9;
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &val, 1);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, &subtype, 1);
        uint32_t wval = length & 0xffffffff;
        PMSGP_INTERNAL_PACK_PUT_VAL(pack, wval, 4);
        PMSGP_INTERNAL_PACK_PUT_PTR(pack, data, length);
    }
    return PMSGP_TRUE;
}

#undef PMSGP_INTERNAL_PACK_PUT_PRECHECK
#undef PMSGP_INTERNAL_PACK_PUT

//
//    unpack
//
#define PMSGP_INTERNAL_FETCH_U8(to, from) \
    do { \
        to = (from)[0]; \
    } while (0)
#define PMSGP_INTERNAL_FETCH_U16(to, from) \
    do { \
        to = ((from)[0] << 8) | (from)[1]; \
    } while (0)
#define PMSGP_INTERNAL_FETCH_U32(to, from) \
    do { \
        to = ((uint32_t)((from)[0]) << 24) | ((uint32_t)((from)[1]) << 16) | ((uint32_t)((from)[2]) << 8) | ((uint32_t)(from)[3]); \
    } while (0)
#define PMSGP_INTERNAL_FETCH_U64(to, from) \
    do { \
        to = ((uint64_t)((from)[0]) << 56) | ((uint64_t)((from)[1]) << 48) | ((uint64_t)((from)[2]) << 40) | ((uint64_t)((from)[3]) << 32) | ((uint64_t)((from)[4]) << 24) | ((uint64_t)((from)[5]) << 16) | ((uint64_t)((from)[6]) << 8) | (uint64_t)((from)[7]); \
    } while (0)

static pmsgp_bool_t pmsgp_internal_unpack_check_and_modify_ext(pmsgp_element_t* dst_element)
{
    if (dst_element->type != PMSGP_TYPE_EXTENSION) { return PMSGP_FALSE; }
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
                PMSGP_INTERNAL_FETCH_U32(tu32, (const uint8_t*)dst_element->content.extval.data);
                dst_element->type = PMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu32;
                dst_element->content.tsval.nanoseconds = 0;
                return PMSGP_TRUE;
            case 8:
                PMSGP_INTERNAL_FETCH_U64(tu64, (const uint8_t*)dst_element->content.extval.data);
                dst_element->type = PMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu64 & 0x3ffffffffULL;
                dst_element->content.tsval.nanoseconds = (uint32_t)((tu64 >> 34) & 0x3fffffffULL);
                return PMSGP_TRUE;
            case 12:
                PMSGP_INTERNAL_FETCH_U32(tu32, (const uint8_t*)dst_element->content.extval.data);
                PMSGP_INTERNAL_FETCH_U64(tu64, ((const uint8_t*)dst_element->content.extval.data) + 4);
                dst_element->type = PMSGP_TYPE_TIMESTAMP;
                dst_element->content.tsval.seconds = tu64;
                dst_element->content.tsval.nanoseconds = tu32;
                return PMSGP_TRUE;
            default: break;
            }
        }
        break;
    default: break;
    }
    return PMSGP_FALSE;
}

static pmsgp_bool_t pmsgp_internal_unpack_fetch_element(pmsgp_unpack_t* unpack, pmsgp_element_t* dst_element)
{
    if (!unpack->iterator.head || unpack->iterator.head < unpack->src || (unpack->src_end && unpack->iterator.head >= unpack->src_end)) { goto fail_exit; }

#define PMSGP_INTERNAL_CHECK_SIZE(n) \
    do { \
        if (unpack->src_end && (d + ((n) + 1) > unpack->src_end)) { unpack->last_error = PMSGP_ERROR_INSUFFICIENT_INPUT; goto fail_exit; } \
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
        dst_element->type = PMSGP_TYPE_NIL;
        d += 1;
    }
    else if (l == 0xc2 || l == 0xc3)
    {
        // true or false
        dst_element->type = PMSGP_TYPE_BOOL;
        dst_element->content.boolval = l == 0xc3 ? PMSGP_TRUE : PMSGP_FALSE;
        d += 1;
    }
    else if ((l & 0x80) == 0)
    {
        // positive fixint
        dst_element->type = PMSGP_TYPE_UINT;
        dst_element->content.uintval = l & 0x7f;
        d += 1;
    }
    else if (l >= 0xcc && l <= 0xcf)
    {
        // uint
        dst_element->type = PMSGP_TYPE_UINT;
        switch (l)
        {
        case 0xcc: PMSGP_INTERNAL_CHECK_SIZE(1); PMSGP_INTERNAL_FETCH_U8(dst_element->content.uintval, d + 1); d += 2; break;
        case 0xcd: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(dst_element->content.uintval, d + 1); d += 3; break;
        case 0xce: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(dst_element->content.uintval, d + 1); d += 5; break;
        case 0xcf: PMSGP_INTERNAL_CHECK_SIZE(8); PMSGP_INTERNAL_FETCH_U64(dst_element->content.uintval, d + 1); d += 9; break;
        default: PMSGP_ASSERT(0); dst_element->content.uintval = 0; break;
        }
    }
    else if (l >= 0xd0 && l <= 0xd3)
    {
        // int
        dst_element->type = PMSGP_TYPE_INT;
        switch (l)
        {
        case 0xd0: PMSGP_INTERNAL_CHECK_SIZE(1); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); dst_element->content.intval = *(int8_t*)(&tu8); d += 2; break;
        case 0xd1: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(tu16, d + 1); dst_element->content.intval = *(int16_t*)(&tu16); d += 3; break;
        case 0xd2: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); dst_element->content.intval = *(int32_t*)(&tu32); d += 5; break;
        case 0xd3: PMSGP_INTERNAL_CHECK_SIZE(8); PMSGP_INTERNAL_FETCH_U64(tu64, d + 1); dst_element->content.intval = *(int64_t*)(&tu64); d += 9; break;
        default: PMSGP_ASSERT(0); dst_element->content.intval = 0; break;
        }
    }
    else if (l == 0xca || l == 0xcb)
    {
        // float or double
        switch (l)
        {
        case 0xca: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); dst_element->type = PMSGP_TYPE_FLOAT; *(uint32_t*)(&dst_element->content.floatval) = tu32; d += 5; break;
        case 0xcb: PMSGP_INTERNAL_CHECK_SIZE(8); PMSGP_INTERNAL_FETCH_U64(tu64, d + 1); dst_element->type = PMSGP_TYPE_DOUBLE; *(uint64_t*)(&dst_element->content.doubleval) = tu64; d += 9; break;
        default: PMSGP_ASSERT(0); dst_element->type = PMSGP_TYPE_FLOAT; dst_element->content.floatval = 0.f; break;
        }
    }
    else if ((l & 0xe0) == 0xa0)
    {
        // fixstr
        tu32 = l & 0x1f;
        PMSGP_INTERNAL_CHECK_SIZE(tu32);
        dst_element->type = PMSGP_TYPE_STRING;
        dst_element->content.strval.str = (const char*)(d + 1);
        dst_element->content.strval.length = tu32;
        d += tu32 + 1;
    }
    else if (l >= 0xd9 && l <= 0xdb)
    {
        // string
        switch (l)
        {
        case 0xd9: PMSGP_INTERNAL_CHECK_SIZE(1); PMSGP_INTERNAL_FETCH_U8(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 1); d += 1; break;
        case 0xda: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xdb: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 4); d += 4; break;
        default: PMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_STRING;
        dst_element->content.strval.str = (const char*)(d + 1);
        dst_element->content.strval.length = tu32;
        d += tu32 + 1;
    }
    else if (l >= 0xc4 && l <= 0xc6)
    {
        // binary
        switch (l)
        {
        case 0xc4: PMSGP_INTERNAL_CHECK_SIZE(1); PMSGP_INTERNAL_FETCH_U8(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 1); d += 1; break;
        case 0xc5: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xc6: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 4); d += 4; break;
        default: PMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_BINARY;
        dst_element->content.binval.bin = (const void*)(d + 1);
        dst_element->content.binval.length = tu32;
        d += tu32 + 1;
    }
    else if ((l & 0xf0) == 0x90)
    {
        // fixarray
        tu32 = l & 0x0f;
        dst_element->type = PMSGP_TYPE_ARRAY;
        dst_element->content.arrayval.length = tu32;
        d += 1;
    }
    else if (l >= 0xdc && l <= 0xdd)
    {
        // array
        switch (l)
        {
        case 0xdc: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(tu32, d + 1); d += 2; break;
        case 0xdd: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); d += 4; break;
        default: PMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_ARRAY;
        dst_element->content.arrayval.length = tu32;
        d += 1;
    }
    else if ((l & 0xf0) == 0x80)
    {
        // fixamap
        tu32 = l & 0x0f;
        dst_element->type = PMSGP_TYPE_MAP;
        dst_element->content.mapval.length = tu32;
        d += 1;
    }
    else if (l >= 0xde && l <= 0xdf)
    {
        // map
        switch (l)
        {
        case 0xde: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U16(tu32, d + 1); d += 2; break;
        case 0xdf: PMSGP_INTERNAL_CHECK_SIZE(4); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); d += 4; break;
        default: PMSGP_ASSERT(0); tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_MAP;
        dst_element->content.mapval.length = tu32;
        d += 1;
    }
    else if (l >= 0xd4 && l <= 0xd8)
    {
        // fixext
        switch (l)
        {
        case 0xd4: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 1; break;
        case 0xd5: PMSGP_INTERNAL_CHECK_SIZE(3); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 2; break;
        case 0xd6: PMSGP_INTERNAL_CHECK_SIZE(5); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 4; break;
        case 0xd7: PMSGP_INTERNAL_CHECK_SIZE(9); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 8; break;
        case 0xd8: PMSGP_INTERNAL_CHECK_SIZE(17); PMSGP_INTERNAL_FETCH_U8(tu8, d + 1); tu32 = 16; break;
        default: PMSGP_ASSERT(0); tu8 = 0; tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_EXTENSION;
        dst_element->content.extval.subtype = *(int8_t*)(&tu8);
        dst_element->content.extval.data = (const void*)(d + 2);
        dst_element->content.extval.length = tu32;
        d += tu32 + 2;
        pmsgp_internal_unpack_check_and_modify_ext(dst_element);
    }
    else if (l >= 0xc7 && l <= 0xc9)
    {
        // ext
        switch (l)
        {
        case 0xc7: PMSGP_INTERNAL_CHECK_SIZE(2); PMSGP_INTERNAL_FETCH_U8(tu32, d + 1); PMSGP_INTERNAL_FETCH_U8(tu8, d + 2); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 2); d += 2; break;
        case 0xc8: PMSGP_INTERNAL_CHECK_SIZE(3); PMSGP_INTERNAL_FETCH_U16(tu32, d + 1); PMSGP_INTERNAL_FETCH_U8(tu8, d + 3); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 3); d += 3; break;
        case 0xc9: PMSGP_INTERNAL_CHECK_SIZE(5); PMSGP_INTERNAL_FETCH_U32(tu32, d + 1); PMSGP_INTERNAL_FETCH_U8(tu8, d + 5); PMSGP_INTERNAL_CHECK_SIZE(tu32 + 5); d += 5; break;
        default: PMSGP_ASSERT(0); tu8 = 0; tu32 = 0; break;
        }
        dst_element->type = PMSGP_TYPE_EXTENSION;
        dst_element->content.extval.subtype = *(int8_t*)(&tu8);
        dst_element->content.extval.data = (const void*)(d + 1);
        dst_element->content.extval.length = tu32;
        d += tu32 + 1;
        pmsgp_internal_unpack_check_and_modify_ext(dst_element);
    }
    else
    {
        goto fail_exit;
    }

    // check boundary
    if (unpack->src_end && d > unpack->src_end) { goto fail_exit; }

    unpack->next_iterator.head = d;
    return PMSGP_TRUE;

fail_exit:
    dst_element->type = PMSGP_TYPE_UNKNOWN;
    unpack->next_iterator.head = NULL;
    return PMSGP_FALSE;
}

#undef PMSGP_INTERNAL_CHECK_SIZE
#undef PMSGP_INTERNAL_FETCH_U8
#undef PMSGP_INTERNAL_FETCH_U16
#undef PMSGP_INTERNAL_FETCH_U32
#undef PMSGP_INTERNAL_FETCH_U64

PMSGP_API void pmsgp_unpack_init(pmsgp_unpack_t* unpack, const void* src, size_t src_size)
{
    pmsgp_unpack_init_ex(unpack, src, src_size, NULL, NULL);
}

PMSGP_API void pmsgp_unpack_init_ex(pmsgp_unpack_t* unpack, const void* src, size_t src_size, pmsgp_unpack_fin_func_t fin_func, void* user)
{
    unpack->src = (const uint8_t*)src;
    unpack->src_size = src_size;
    unpack->src_end = unpack->src + unpack->src_size;
    unpack->iterator.head = unpack->src;
    unpack->last_error = PMSGP_ERROR_NONE;
    unpack->fin_func = fin_func;
    unpack->user = user;
    pmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
}

PMSGP_API void pmsgp_unpack_fin(pmsgp_unpack_t* unpack)
{
    if (unpack->fin_func) { unpack->fin_func(unpack->user, unpack); }
    unpack->src = NULL;
    unpack->src_size = 0;
    unpack->src_end = NULL;
    unpack->iterator.head = NULL;
    unpack->last_error = PMSGP_ERROR_NONE;
    unpack->element.type = PMSGP_TYPE_UNKNOWN;
    unpack->fin_func = NULL;
    unpack->user = NULL;
}

#if !defined(PMSGP_NO_MEMORY_API) && !defined(PMSGP_NO_STDIO_FILE_API)
static void pmsgp_internal_unpack_file_fin_callback(void* user, pmsgp_unpack_t* unpack)
{
    (void)(user);
    if (unpack->src)
    {
        void* allocated = (void*)(unpack->src);
        PMSGP_FREE(allocated, user);
    }
}

PMSGP_API pmsgp_bool_t pmsgp_unpack_init_file(pmsgp_unpack_t* unpack, const char* filepath, void* alloc_user)
{
    FILE* file = fopen(filepath, "rb");
    if (!file) { return PMSGP_FALSE; }
    const int size = fseek(file, 0, SEEK_END);
    if (size < 0) { fclose(file); return PMSGP_FALSE; }
    fseek(file, 0, SEEK_SET);
    void* filecontent = PMSGP_MALLOC(size + 1, alloc_user);
    if (!filecontent) { fclose(file); return PMSGP_FALSE; }
    const size_t readsize = fread(filecontent, 1, (size_t)size, file);
    pmsgp_unpack_init_ex(unpack, filecontent, readsize, &pmsgp_internal_unpack_file_fin_callback, alloc_user);
    return PMSGP_TRUE;
}
#endif // !PMSGP_NO_MEMORY_API && !PMSGP_NO_STDIO_FILE_API

PMSGP_API pmsgp_bool_t pmsgp_unpack_eof(const pmsgp_unpack_t* unpack)
{
    return (unpack->src_end && unpack->iterator.head >= unpack->src_end) ? PMSGP_TRUE : PMSGP_FALSE;
}

PMSGP_API pmsgp_bool_t pmsgp_unpack_get_element(const pmsgp_unpack_t* unpack, pmsgp_element_t* dst_element)
{
    if (dst_element) { *dst_element = unpack->element; }
    return unpack->element.type != PMSGP_TYPE_UNKNOWN;
}

PMSGP_API pmsgp_bool_t pmsgp_unpack_next(pmsgp_unpack_t* unpack)
{
    unpack->iterator = unpack->next_iterator;
    pmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
    return unpack->element.type != PMSGP_TYPE_UNKNOWN;
}

PMSGP_API size_t pmsgp_unpack_skip(pmsgp_unpack_t* unpack, size_t skip_num)
{
    size_t skipped = 0;
    while (skipped < skip_num && pmsgp_unpack_get_element(unpack, NULL)) { pmsgp_unpack_next(unpack); ++skipped; }
    return skipped;
}

PMSGP_API pmsgp_iterator_t pmsgp_unpack_get_iterator(const pmsgp_unpack_t* unpack)
{
    return unpack->iterator;
}

PMSGP_API void pmsgp_unpack_set_iterator(pmsgp_unpack_t* unpack, pmsgp_iterator_t iterator)
{
    unpack->iterator = iterator;
    pmsgp_internal_unpack_fetch_element(unpack, &unpack->element);
}

PMSGP_API pmsgp_bool_t pmsgp_unpack_get_element_from_iterator_unsafe(const pmsgp_iterator_t* iterator, pmsgp_element_t* dst_element)
{
    pmsgp_unpack_t unpack;
    pmsgp_unpack_init(&unpack, iterator->head, 0);
    unpack.src_end = NULL;
    return pmsgp_unpack_get_element(&unpack, dst_element);
}

#endif // PMSGP_IMPLEMENTATION_INCLUDED
#endif // PMSGP_IMPLEMENTATION

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

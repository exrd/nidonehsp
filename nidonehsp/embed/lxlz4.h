//-----------------------------------------------------------------------------
/*
    lxlz4.h
      lz4 file format compress/decompress library in C written by exrd.
      lxlz4 is licensed under CC0 1.0 Universal, see end of this file for more detail.
*/
//-----------------------------------------------------------------------------

// include guard
#ifndef LXLZ4_HEADER_INCLUDED
#define LXLZ4_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    customization
//

// linkage
#ifdef LXLZ4_STATIC
#define LXLZ4_API   static
#else
#define LXLZ4_API
#endif // LXLZ4_STATIC

// unaligned memory access
//#define LXLZ4_UNALIGNED_MEMORY_ACCESS

// assert
#ifndef LXLZ4_ASSERT
#include <assert.h>
#define LXLZ4_ASSERT    assert
#endif // LXLZ4_ASSERT

// malloc, free, realloc
#ifndef LXLZ4_MALLOC
#include <stdlib.h>
#define LXLZ4_MALLOC(size, user)        malloc(size)
#define LXLZ4_FREE(ptr, user)           free(ptr)
#define LXLZ4_REALLOC_SIZED(oldptr, newsize, oldsize, user)     realloc(oldptr, newsize)
#endif // LXLZ4_MALLOC

// memcpy
#ifndef LXLZ4_MEMCPY
#include <string.h>
#define LXLZ4_MEMCPY(dst, src, size)    memcpy(dst, src, size)
#endif // LXLZ4_MEMCPY

// memset
#ifndef LXLZ4_MEMSET
#include <string.h>
#define LXLZ4_MEMSET(dst, val, size)    memset(dst, val, size)
#endif // LXLZ4_MEMSET

// force inline
#ifndef LXLZ4_STRONG_INLINE
#ifdef _MSC_VER
#define LXLZ4_STRONG_INLINE static __forceinline
#else
#define LXLZ4_STRONG_INLINE static inline
#endif
#endif // LXLZ4_STRONG_INLINE

// likely/unlikely
#ifndef LXLZ4_LIKELY
#define LXLZ4_LIKELY(exp)   (exp)
#endif // LXLZ4_LIKELY

#ifndef LXLZ4_UNLIKELY
#define LXLZ4_UNLIKELY(exp) (exp)
#endif // LXLZ4_UNLIKELY

//-----------------------------------------------------------------------------
//
//    forward declaration
//
#include <stddef.h>
#include <stdint.h>

//
//    common
//
#ifdef LXLZ4_NO_STDBOOL
typedef int lxlz4_bool_t;
#define LXLZ4_TRUE  (1)
#define LXLZ4_FALSE (0)
#else
#include <stdbool.h>
typedef bool lxlz4_bool_t;
#define LXLZ4_TRUE  (true)
#define LXLZ4_FALSE (false)
#endif

typedef enum
{
    LXLZ4_ERROR_NONE = 0,
    // general errors
    LXLZ4_ERROR_GENERAL,
    LXLZ4_ERROR_INSUFFICIENT_INPUT,
    LXLZ4_ERROR_INSUFFICIENT_OUTPUT,
    LXLZ4_ERROR_MEMALLOC_FAILED,
    // compress errors
    LXLZ4_ERROR_INVALID_COMPRESS_OPTION,
    LXLZ4_ERROR_COMPRESS_TOO_LARGE_INPUT_DATA_SIZE,
    LXLZ4_ERROR_COMPRESS_INSUFFICIENT_WORK,
    LXLZ4_ERROR_COMPRESS_INVALID_WORK_ALIGN,
    LXLZ4_ERROR_WRITER_STATE_MISMATCH,
    // decompress errors
    LXLZ4_ERROR_INCOMPATIBLE_DATA,
    LXLZ4_ERROR_FRAME_MAGIC_NUMBER_MISMATCH,
    LXLZ4_ERROR_FRAME_CHECKSUM_MISMATCH,
    LXLZ4_ERROR_BLOCK_CHECKSUM_MISMATCH,
    LXLZ4_ERROR_BLOCK_PREVIOUS_BLOCK_REQUIRED,
    LXLZ4_ERROR_DECOMPRESS_OFFSET_OUT_OF_RANGE,
    LXLZ4_ERROR_DECOMPRESS_MATCH_LENGTH_OUT_OF_RANGE,
    LXLZ4_ERROR_DECOMPRESS_ZERO_OFFSET,
} lxlz4_error_e;

typedef enum
{
    LXLZ4_BLOCK_SIZE_64KB = 0,
    LXLZ4_BLOCK_SIZE_256KB,
    LXLZ4_BLOCK_SIZE_1MB,
    LXLZ4_BLOCK_SIZE_4MB,

    LXLZ4_BLOCK_SIZE_END,
} lxlz4_block_size_e;

LXLZ4_API size_t lxlz4_block_bytesize(lxlz4_block_size_e block_size);

typedef enum
{
    LXLZ4_COMPRESS_LEVEL_NOCOMPRESS = 0,
    LXLZ4_COMPRESS_LEVEL_TINY,
    LXLZ4_COMPRESS_LEVEL_FAST,
    LXLZ4_COMPRESS_LEVEL_NORMAL,

    LXLZ4_COMPRESS_LEVEL_MIN = LXLZ4_COMPRESS_LEVEL_NOCOMPRESS,
    LXLZ4_COMPRESS_LEVEL_MAX = LXLZ4_COMPRESS_LEVEL_NORMAL,
} lxlz4_compress_level_e;

typedef enum
{
    LXLZ4_INPUT_RANGE_U16 = 0,
    LXLZ4_INPUT_RANGE_U32,
    LXLZ4_INPUT_RANGE_U64,

    LXLZ4_INPUT_RANGE_MIN = LXLZ4_INPUT_RANGE_U16,
    LXLZ4_INPUT_RANGE_MAX = LXLZ4_INPUT_RANGE_U64,
} lxlz4_input_range_e;

typedef struct lxlz4_frame_t lxlz4_frame_t;
struct lxlz4_frame_t
{
    uint8_t version_;
    lxlz4_bool_t is_block_independent_;
    lxlz4_bool_t has_block_checksum_;
    lxlz4_bool_t has_content_size_;
    uint64_t content_size_;
    lxlz4_bool_t has_content_checksum_;
    lxlz4_bool_t has_dictionary_id_;
    uint32_t dictionary_id_;
    lxlz4_block_size_e block_max_size_;
    size_t header_size_;
};

#define LXLZ4_FRAME_HEADER_SIZE_MIN     (7)
#define LXLZ4_FRAME_HEADER_SIZE_MAX     (19)

#define LXLZ4_FRAME_MARGIN_SIZE_MAX     (LXLZ4_FRAME_HEADER_SIZE_MAX + 4)// header() + footer(4:content_checksum)
#define LXLZ4_BLOCK_MARGIN_SIZE_MAX     (4 + 4)// header(4:block_size) + footer(4:block_checksum)

#define LXLZ4_FRAME_MAGIC   (0x184d2204)

#define LXLZ4_SKIPPABLE_FRAME_MAGIC_BEGIN   (0x184d2a50)
#define LXLZ4_SKIPPABLE_FRAME_MAGIC_END     (0x184d2a60)

#define LXLZ4_INPUT_DATA_MAX    (0xffffffffU)

#define LXLZ4_WORK_ALIGN    (8)

#define LXLZ4_DICTIONARY_SIZE_MIN   (4)
#define LXLZ4_DICTIONARY_SIZE_MAX   (64 * 1024)
#define LXLZ4_DICTIONARY_LOAD_STEP  (4)
#define LXLZ4_DICTIONARY_OUTPUT_PREFIX  ((const void*)(intptr_t)(-1))

#define LXLZ4_COMPRESS_MINBOUND (12)
#define LXLZ4_LITERAL_LENGTH_VL (15)
#define LXLZ4_LITERAL_END_MARGIN    (5)
#define LXLZ4_MATCH_LENGTH_VL   (15)
#define LXLZ4_MATCH_LENGTH_BIAS (4)
#define LXLZ4_MATCH_DISTANCE_MAX    (65535)

typedef enum
{
    LXLZ4_BLOCK_CATEGORY_DATA = 0,
    LXLZ4_BLOCK_CATEGORY_ENDMARK,
} lxlz4_block_category_e;

typedef struct lxlz4_block_t lxlz4_block_t;
struct lxlz4_block_t
{
    lxlz4_block_category_e category_;
    lxlz4_bool_t is_block_compressed_;
    uint32_t block_size_;
    const void* block_data_;
    uint32_t block_checksum_;
    size_t next_block_offset_;
};

typedef struct lxlz4_parse_t lxlz4_parse_t;
struct lxlz4_parse_t
{
    // config
    lxlz4_bool_t parse_endmark_block_;// retrieve endmark block on parsing, default value is FALSE

    // [internal]
    lxlz4_frame_t frame_;
    lxlz4_block_t block_;
    const void* src_;
    size_t src_size_;
    size_t next_;
    lxlz4_error_e error_;
    lxlz4_bool_t endmark_detected_;
    lxlz4_bool_t got_content_checksum_;
    uint32_t content_checksum_;
};

//
//    xxhash
//
LXLZ4_API uint32_t lxlz4_xxhash32(const void* src, size_t src_size, uint32_t seed);

//
//    compress
//
typedef struct lxlz4_compress_option_t lxlz4_compress_option_t;
struct lxlz4_compress_option_t
{
    // raw data
    lxlz4_compress_level_e level_;// default value is FAST
    const void* dictionary_;// custom dictionary: default value is NULL
    size_t dictionary_size_;
    lxlz4_input_range_e input_range_;// input data length range, default value is U32

    // frame data
    lxlz4_bool_t is_block_independent_;// default value is false
    lxlz4_bool_t embed_block_checksum_;// default value is true
    lxlz4_bool_t embed_content_size_;// default value is true
    lxlz4_bool_t embed_content_checksum_;// default value is true
    lxlz4_bool_t embed_dictionary_id_;// default value is false
    lxlz4_block_size_e block_max_size_;// default value is 64KB
    uint32_t dictionary_id_;// default value is 0
};

LXLZ4_API void lxlz4_compress_option_init(lxlz4_compress_option_t* copt);
LXLZ4_API void lxlz4_compress_option_init_compatible(lxlz4_compress_option_t* copt);

// raw data api
LXLZ4_API size_t lxlz4_compress_bound(size_t src_size, const lxlz4_compress_option_t* copt);
LXLZ4_API lxlz4_error_e lxlz4_compress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const lxlz4_compress_option_t* copt, void* alloc_user);

// frame data api
LXLZ4_API size_t lxlz4_frame_compress_bound(size_t src_size, const lxlz4_compress_option_t* copt);
LXLZ4_API lxlz4_error_e lxlz4_frame_compress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const lxlz4_compress_option_t* copt, void* alloc_user);

// low level api
typedef enum
{
    LXLZ4_LLCOMPRESS_STATE_INIT = 0,
    LXLZ4_LLCOMPRESS_STATE_FRAME_HEADER,
    LXLZ4_LLCOMPRESS_STATE_BLOCK_DATA,
    LXLZ4_LLCOMPRESS_STATE_FINISHED,
} lxlz4_llcompress_state_e;

typedef struct lxlz4_llcompress_context_t lxlz4_llcompress_context_t;
struct lxlz4_llcompress_context_t
{
    // config
    lxlz4_compress_option_t copt_;

    // [internal]
    lxlz4_llcompress_state_e state_;
    size_t total_in_;
    size_t processed_in_;
    size_t total_out_;

    void* work_allocated_;
    void* work_;
    size_t work_size_;
    void* alloc_user_;
};

LXLZ4_API size_t lxlz4_llcompress_work_size(const lxlz4_compress_option_t* copt);
LXLZ4_API size_t lxlz4_llcompress_work_size_max();
LXLZ4_API size_t lxlz4_llcompress_work_align(const lxlz4_compress_option_t* copt);
LXLZ4_API lxlz4_error_e lxlz4_llcompress_begin(lxlz4_llcompress_context_t* context, const lxlz4_compress_option_t* copt, void* alloc_user);
LXLZ4_API lxlz4_error_e lxlz4_llcompress_begin_work(lxlz4_llcompress_context_t* context, const lxlz4_compress_option_t* copt, void* work, size_t work_size);
LXLZ4_API void lxlz4_llcompress_end(lxlz4_llcompress_context_t* context);

LXLZ4_API lxlz4_error_e lxlz4_llcompress_raw(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* work, size_t work_size, const lxlz4_compress_option_t* copt);

LXLZ4_API lxlz4_error_e lxlz4_llcompress_enter_frame(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint64_t content_size);
LXLZ4_API lxlz4_error_e lxlz4_llcompress_leave_frame(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t content_checksum);

LXLZ4_API lxlz4_error_e lxlz4_llcompress_enter_block(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t block_size, lxlz4_bool_t block_compressed);
LXLZ4_API lxlz4_error_e lxlz4_llcompress_leave_block(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t block_checksum);

//
//    decompress
//
//      NOTE that though decompress functions take `alloc_user` parameter for malloc/free,
//      no malloc/free occur in decompression in current version.

// raw data api
LXLZ4_API lxlz4_error_e lxlz4_decompress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* alloc_user);

// frame data api
// content_size can be 0 even if return value is LXLZ4_ERROR_NONE when ContentSize is not present in frame header.
LXLZ4_API lxlz4_error_e lxlz4_frame_decompressd_size(uint64_t* content_size, const void* src, size_t src_size);
LXLZ4_API lxlz4_error_e lxlz4_frame_decompress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* alloc_user);

// low level
typedef struct lxlz4_lldecompress_context_t lxlz4_lldecompress_context_t;
struct lxlz4_lldecompress_context_t
{
    // dictonary
    const void* dictionary_;
    size_t dictionary_size_;

    // [internal]
    void* alloc_user_;
};

LXLZ4_API lxlz4_error_e lxlz4_lldecompress_begin(lxlz4_lldecompress_context_t* context, void* alloc_user);
LXLZ4_API void lxlz4_lldecompress_end(lxlz4_lldecompress_context_t* context);

LXLZ4_API lxlz4_error_e lxlz4_lldecompress_block(lxlz4_lldecompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, const lxlz4_block_t* block, const lxlz4_frame_t* frame, const void* prev_block, size_t prev_block_size, lxlz4_bool_t first_block);
LXLZ4_API lxlz4_error_e lxlz4_lldecompress_raw(lxlz4_lldecompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size);

//
//    parser
//
LXLZ4_API void lxlz4_frame_init(lxlz4_frame_t* frame);
LXLZ4_API lxlz4_error_e lxlz4_frame_extract(lxlz4_frame_t* frame, const void* src, size_t src_size);
LXLZ4_API lxlz4_error_e lxlz4_frame_extract_ex(lxlz4_frame_t* frame, const void* src, size_t src_size, lxlz4_bool_t check_header_checksum);

LXLZ4_API void lxlz4_frame_parse_init(lxlz4_parse_t* parse);
LXLZ4_API lxlz4_bool_t lxlz4_frame_parse_begin(lxlz4_parse_t* parse, const void* src, size_t src_size);
LXLZ4_API const lxlz4_block_t* lxlz4_frame_parse_next(lxlz4_parse_t* parse);
LXLZ4_API void lxlz4_frame_parse_end(lxlz4_parse_t* parse);
LXLZ4_API lxlz4_error_e lxlz4_frame_parse_error(const lxlz4_parse_t* parse);

LXLZ4_API void lxlz4_block_init(lxlz4_block_t* block);
LXLZ4_API lxlz4_error_e lxlz4_block_extract(lxlz4_block_t* block, const void* src, size_t src_size, lxlz4_bool_t has_block_checksum);
LXLZ4_API lxlz4_bool_t lxlz4_block_verify_checksum(const lxlz4_block_t* block);

#endif // LXLZ4_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    implementation
//
#if defined(LXLZ4_IMPLEMENTATION)
#ifndef LXLZ4_IMPLEMENTATION_INCLUDED
#define LXLZ4_IMPLEMENTATION_INCLUDED

//
//    internal
//
#define LXLZ4_TOBOOL(v)     ((v) ? LXLZ4_TRUE : LXLZ4_FALSE)

#define LXLZ4_INTERNAL_OUTOFRANGE(p, size, ep)  LXLZ4_UNLIKELY((p) + (size) > ep)

#if 0
#define LXLZ4_INTERNAL_DPRINTF(...) printf(__VA_ARGS__)
#else
#define LXLZ4_INTERNAL_DPRINTF(...) 
#endif

#define LXLZ4_INTERNAL_HASH_BITS_TINY   (10)
#define LXLZ4_INTERNAL_HASH_UNIT_TINY   (4)
#define LXLZ4_INTERNAL_ATOS_TINY        (5)
#define LXLZ4_INTERNAL_MBH_RANGE_TINY   (0)
#define LXLZ4_INTERNAL_MBH_STEP_TINY    (0)

#define LXLZ4_INTERNAL_HASH_BITS_FAST   (12)
#define LXLZ4_INTERNAL_HASH_UNIT_FAST   (4)
#define LXLZ4_INTERNAL_ATOS_FAST        (6)
#define LXLZ4_INTERNAL_MBH_RANGE_FAST   (2)
#define LXLZ4_INTERNAL_MBH_STEP_FAST    (2)

#define LXLZ4_INTERNAL_HASH_BITS_NORMAL (13)
#define LXLZ4_INTERNAL_HASH_UNIT_NORMAL (5)
#define LXLZ4_INTERNAL_ATOS_NORMAL      (7)
#define LXLZ4_INTERNAL_MBH_RANGE_NORMAL (9)
#define LXLZ4_INTERNAL_MBH_STEP_NORMAL  (3)

#ifdef LXLZ4_UNALIGNED_MEMORY_ACCESS
#define LXLZ4_INTERNAL_MEMCOPY32(op, ip) \
    *(uint32_t*)(op) = *(const uint32_t*)(ip)
#define LXLZ4_INTERNAL_MEMCOPY64(op, ip) \
    *(uint64_t*)(op) = *(const uint64_t*)(ip)
#define LXLZ4_INTERNAL_MATCH32(lhsp, rhsp) \
    (*(const uint32_t*)(lhsp) == *(const uint32_t*)(rhsp))
#define LXLZ4_INTERNAL_MATCH64(lhsp, rhsp) \
    (*(const uint64_t*)(lhsp) == *(const uint64_t*)(rhsp))
#define LXLZ4_INTERNAL_LOADU16(ip) \
    (*(const uint16_t*)(ip))
#define LXLZ4_INTERNAL_STOREU16(ip, v) \
    *(uint16_t*)(ip) = (v)
#define LXLZ4_INTERNAL_LOADU32(ip) \
    (*(const uint32_t*)(ip))
#define LXLZ4_INTERNAL_STOREU32(ip, v) \
    *(uint32_t*)(ip) = (v)
#define LXLZ4_INTERNAL_LOADU64(ip) \
    (*(const uint64_t*)(ip))
#define LXLZ4_INTERNAL_STOREU64(ip, v) \
    *(uint64_t*)(ip) = (v)
#else
#define LXLZ4_INTERNAL_MEMCOPY32(op, ip) \
    LXLZ4_MEMCPY(op, ip, 4)
#define LXLZ4_INTERNAL_MEMCOPY64(op, ip) \
    LXLZ4_MEMCPY(op, ip, 8)
#define LXLZ4_INTERNAL_MATCH32(lhsp, rhsp) \
    ((lhsp)[0] == (rhsp)[0] && (lhsp)[1] == (rhsp)[1] && (lhsp)[2] == (rhsp)[2] && (lhsp)[3] == (rhsp)[3])
#define LXLZ4_INTERNAL_MATCH64(lhsp, rhsp) \
    (LXLZ4_INTERNAL_MATCH32((lhsp), (rhsp)) && LXLZ4_INTERNAL_MATCH32((lhsp) + 4, (rhsp) + 4))
#define LXLZ4_INTERNAL_LOADU16(ip) \
    (uint16_t)(((ip)[0]) | ((ip)[1] << 8))
#define LXLZ4_INTERNAL_STOREU16(ip, v) \
    do { \
        (ip)[0] = ((v)) & 0xff; \
        (ip)[1] = ((v) >> 8) & 0xff; \
    } while (0)
#define LXLZ4_INTERNAL_LOADU32(ip) \
    (((ip)[0]) | ((ip)[1] << 8) | ((ip)[2] << 16) | ((ip)[3] << 24))
#define LXLZ4_INTERNAL_STOREU32(ip, v) \
    do { \
        (ip)[0] = ((v)) & 0xff; \
        (ip)[1] = ((v) >> 8) & 0xff; \
        (ip)[2] = ((v) >> 16) & 0xff; \
        (ip)[3] = ((v) >> 24) & 0xff; \
    } while (0)
#define LXLZ4_INTERNAL_LOADU64(ip) \
    (((uint64_t)(ip)[0]) | ((uint64_t)(ip)[1] << 8) | ((uint64_t)(ip)[2] << 16) | ((uint64_t)(ip)[3] << 24) | ((uint64_t)(ip)[4] << 32) | ((uint64_t)(ip)[5] << 40) | ((uint64_t)(ip)[6] << 48) | ((uint64_t)(ip)[7] << 56))
#define LXLZ4_INTERNAL_STOREU64(ip, v) \
    do { \
        (ip)[0] = ((v)) & 0xff; \
        (ip)[1] = ((v) >> 8) & 0xff; \
        (ip)[2] = ((v) >> 16) & 0xff; \
        (ip)[3] = ((v) >> 24) & 0xff; \
        (ip)[4] = ((v) >> 32) & 0xff; \
        (ip)[5] = ((v) >> 40) & 0xff; \
        (ip)[6] = ((v) >> 48) & 0xff; \
        (ip)[7] = ((v) >> 56) & 0xff; \
    } while (0)
#endif // LXLZ4_UNALIGNED_MEMORY_ACCESS

LXLZ4_STRONG_INLINE void lxlz4_internal_matchcopy_greedy(uint8_t* dst, const uint8_t* src, size_t length, size_t offset, lxlz4_bool_t strict)
{
    LXLZ4_ASSERT(offset >= 8);

    // offset
    while (length >= offset) { LXLZ4_MEMCPY(dst, src, offset); dst += offset; length -= offset; }

    // 8 byte
    while (length >= 8) { LXLZ4_INTERNAL_MEMCOPY64(dst, src); dst += 8; src += 8; length -= 8; }

    if (strict)
    {
        //  1byte
        while (length-- > 0) { *dst++ = *src++; }
    }
    else
    {
        // 8 byte overrun
        LXLZ4_INTERNAL_MEMCOPY64(dst, src); dst += 8; src += 8; length -= 8;
    }
}

static inline void lxlz4_internal_matchcopy_general(uint8_t* dst, const uint8_t* src, size_t length, size_t offset)
{
    // @todo OPTIMIZATION: unrolling

    if (offset < 8)
    {
        // 4 byte
        if (offset >= 4)
        {
            while (length >= 4) { LXLZ4_INTERNAL_MEMCOPY32(dst, src); dst += 4; src += 4; length -= 4; }
        }

        // 1 byte
        while (length-- > 0) { *dst++ = *src++; }
        return;
    }
    else
    {
        lxlz4_internal_matchcopy_greedy(dst, src, length, offset, LXLZ4_TRUE);
        return;
    }
}

LXLZ4_STRONG_INLINE void lxlz4_internal_matchcopy_branch(uint8_t* dst, const uint8_t* src, size_t length, size_t offset)
{
    LXLZ4_ASSERT(offset > 0);

    // make large offset
    switch (offset)
    {
    case 1:
        if (length < 8)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        {
            uint32_t u = (*src);
            u |= u << 8;
            u |= u << 16;
            LXLZ4_INTERNAL_MEMCOPY32(dst + 0, &u);
            LXLZ4_INTERNAL_MEMCOPY32(dst + 4, &u);
        }
        dst += 8; length -= 8;
        offset += 8;
        break;
    case 2:
        if (length < 8)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_MEMCPY(dst + 0, src, 2);
        LXLZ4_MEMCPY(dst + 2, src, 2);
        LXLZ4_INTERNAL_MEMCOPY32(dst + 4, dst);
        dst += 8; length -= 8;
        offset += 8;
        break;
    case 3:
        if (length < 9)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_MEMCPY(dst, src, 3);
        LXLZ4_MEMCPY(dst + 3, src, 3);
        LXLZ4_MEMCPY(dst + 6, src, 3);
        dst += 9; length -= 9;
        offset += 9;
        break;
    case 4:
        if (length < 8)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_INTERNAL_MEMCOPY32(dst, src);
        LXLZ4_INTERNAL_MEMCOPY32(dst + 4, src);
        dst += 8; length -= 8;
        offset += 8;
        break;
    case 5:
        if (length < 10)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_MEMCPY(dst, src, 5);
        LXLZ4_MEMCPY(dst + 5, src, 5);
        dst += 10; length -= 10;
        offset += 10;
        break;
    case 6:
        if (length < 12)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_MEMCPY(dst, src, 6);
        LXLZ4_MEMCPY(dst + 6, src, 6);
        dst += 12; length -= 12;
        offset += 12;
        break;
    case 7:
        if (length < 14)
        {
            lxlz4_internal_matchcopy_general(dst, src, length, offset);
            return;
        }
        LXLZ4_MEMCPY(dst, src, 7);
        LXLZ4_MEMCPY(dst + 7, src, 7);
        dst += 14; length -= 14;
        offset += 14;
        break;
    default:
        //lxlz4_internal_matchcopy_greedy(dst, src, length, offset, LXLZ4_TRUE);
        break;
    }

    lxlz4_internal_matchcopy_general(dst, src, length, offset);
}

static inline size_t lxlz4_internal_input_range_to_size(lxlz4_input_range_e input_range)
{
    switch (input_range)
    {
    case LXLZ4_INPUT_RANGE_U16: return sizeof(uint16_t);
    case LXLZ4_INPUT_RANGE_U32: return sizeof(uint32_t);
    case LXLZ4_INPUT_RANGE_U64: return sizeof(uint64_t);
    default: LXLZ4_ASSERT(0); break;
    }
    return 0;
}

static inline size_t lxlz4_internal_input_range_to_num_limit(lxlz4_input_range_e input_range)
{
    switch (input_range)
    {
    case LXLZ4_INPUT_RANGE_U16: return (size_t)UINT16_MAX;
    case LXLZ4_INPUT_RANGE_U32: return (size_t)UINT32_MAX;
    case LXLZ4_INPUT_RANGE_U64: return (size_t)UINT64_MAX;// may overflow
    default: LXLZ4_ASSERT(0); break;
    }
    return 0;
}

LXLZ4_STRONG_INLINE uint32_t lxlz4_internal_hash4(const void* src, size_t hash_bits)
{
    const uint8_t* p = (const uint8_t*)(src);
    const uint32_t value = LXLZ4_INTERNAL_LOADU32(p);
    return (value * 0x9E3779B1U) >> (32 - hash_bits);// xxhash prime
}

LXLZ4_STRONG_INLINE uint32_t lxlz4_internal_hash5(const void* src, size_t hash_bits)
{
    const uint8_t* p = (const uint8_t*)(src);
    const uint32_t value = LXLZ4_INTERNAL_LOADU32(p);
    return ((value * 0x9E3779B1U) ^ (p[4] << 24)) >> (32 - hash_bits);// xxhash prime
}

LXLZ4_STRONG_INLINE uint32_t lxlz4_internal_hash6(const void* src, size_t hash_bits)
{
    const uint8_t* p = (const uint8_t*)(src);
    const uint32_t value = LXLZ4_INTERNAL_LOADU32(p);
    return ((value * 0x9E3779B1U) ^ (p[4] << 24) ^ (p[5] << 16)) >> (32 - hash_bits);// xxhash prime
}

#define LXLZ4_INTERNAL_COMPUTE_HASH(p, hash_bits, hash_unit) \
    ((hash_unit) == 4 ? lxlz4_internal_hash4((p), (hash_bits)) : (hash_unit) == 5 ? lxlz4_internal_hash5((p), (hash_bits)) : lxlz4_internal_hash6((p), (hash_bits)))
#define LXLZ4_INTERNAL_PUT_HASH(input_range, htable, hash, pos) \
    do { \
        if ((input_range) == LXLZ4_INPUT_RANGE_U16) { ((uint16_t*)(htable))[(hash)] = (uint16_t)(pos); } \
        else if ((input_range) == LXLZ4_INPUT_RANGE_U32) { ((uint32_t*)(htable))[(hash)] = (uint32_t)(pos); } \
        else if ((input_range) == LXLZ4_INPUT_RANGE_U64) { ((uint64_t*)(htable))[(hash)] = (uint64_t)(pos); } \
        else { LXLZ4_ASSERT(0); } \
        /*printf("put hash idx(%u) hash(%u)\n", (uint32_t)(pos), (hash));*/ \
    } while (0)
#define LXLZ4_INTERNAL_GET_HASH(input_range, htable, hash) \
    ( \
        (input_range) == LXLZ4_INPUT_RANGE_U16 ? ((const uint16_t*)(htable))[(hash)] : \
        (input_range) == LXLZ4_INPUT_RANGE_U32 ? ((const uint32_t*)(htable))[(hash)] : \
        (input_range) == LXLZ4_INPUT_RANGE_U64 ? ((const uint64_t*)(htable))[(hash)] : \
        (0) \
    )
LXLZ4_STRONG_INLINE lxlz4_error_e lxlz4_internal_llcompress_raw(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* work, size_t work_size, lxlz4_bool_t do_compress, size_t hash_bits, size_t hash_unit, lxlz4_input_range_e input_range, size_t accel_to_step, size_t matched_block_hash_range, size_t matched_block_hash_step, const void* dictionary, size_t dictionary_size)
{
    if (!dst) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    if (!work) { return LXLZ4_ERROR_COMPRESS_INSUFFICIENT_WORK; }
    if ((uintptr_t)work % LXLZ4_WORK_ALIGN) { return LXLZ4_ERROR_COMPRESS_INVALID_WORK_ALIGN; }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    const uint8_t* ip = (const uint8_t*)src;
    const uint8_t* cip = ip;
    const uint8_t* sip = ip;
    const uint8_t* eip = ip + src_size;
    // hash table ptr
    uint8_t* htable = (uint8_t*)work;
    const size_t htable_element_size = lxlz4_internal_input_range_to_size(input_range);
    const size_t htable_bytesize = htable_element_size * ((size_t)1 << hash_bits);
    const uint8_t* dicp = (const uint8_t*)dictionary;
    const uint8_t* edicp = dicp + dictionary_size;
    // compress
    if (do_compress && !LXLZ4_INTERNAL_OUTOFRANGE(ip, LXLZ4_COMPRESS_MINBOUND, eip))
    {
        // prepare hash table
        // @todo OPTIMIZATION: we can omit following reseting/updating hash table in some cases such as compressing sequential blocks in frame format.
        // @todo IMPLEMENT outpu prefix dictionary(decompression already implemented, though compression is not)
        if (work_size < htable_bytesize) { return LXLZ4_ERROR_COMPRESS_INSUFFICIENT_WORK; }
        LXLZ4_MEMSET(htable, 0, htable_bytesize);
        if (dictionary)
        {
            // update hashtable
            if (dictionary_size > LXLZ4_DICTIONARY_SIZE_MAX)
            {
                dictionary_size = LXLZ4_DICTIONARY_SIZE_MAX;
                dicp = edicp - LXLZ4_DICTIONARY_SIZE_MAX;
            }
            const uint8_t* p = dicp;
            while (p < edicp - hash_unit)
            {
                LXLZ4_INTERNAL_PUT_HASH(input_range, htable, LXLZ4_INTERNAL_COMPUTE_HASH(p, hash_bits, hash_unit), (p - dicp));
                p += LXLZ4_DICTIONARY_LOAD_STEP;
            }
        }

        const size_t match_length_max = lxlz4_internal_input_range_to_num_limit(input_range);
        // put first hash
        LXLZ4_INTERNAL_PUT_HASH(input_range, htable, LXLZ4_INTERNAL_COMPUTE_HASH(cip, hash_bits, hash_unit), (cip - sip + dictionary_size));
        ++cip;
        size_t accel = 0;
        ptrdiff_t match_distance = 0;
        for (;;)
        {
            // too small input to compress, encode it as literal
            if (LXLZ4_INTERNAL_OUTOFRANGE(cip, LXLZ4_COMPRESS_MINBOUND, eip)) { break; }
            //if (LXLZ4_INTERNAL_OUTOFRANGE(cip, LXLZ4_MATCH_LENGTH_BIAS + LXLZ4_LITERAL_END_MARGIN, eip)) { break; }// this condition is less strict than above line
            // hashing
            const uint32_t h = LXLZ4_INTERNAL_COMPUTE_HASH(cip, hash_bits, hash_unit);
            const size_t matchpos = (size_t)(LXLZ4_INTERNAL_GET_HASH(input_range, htable, h));
            LXLZ4_INTERNAL_PUT_HASH(input_range, htable, h, (cip - sip + dictionary_size));
            // matching
            const lxlz4_bool_t matchdic = dictionary && matchpos < dictionary_size;
            const uint8_t* match = matchdic ? dicp + matchpos : sip + (matchpos - dictionary_size);
            LXLZ4_ASSERT(matchdic ? (match >= dicp && match < edicp) : (match >= sip && match < cip));
            lxlz4_bool_t valid_match = LXLZ4_INTERNAL_MATCH32(cip, match);
            // check distance
            if (valid_match)
            {
                match_distance = matchdic ? (cip - sip) + (edicp - match) : cip - match;
                LXLZ4_ASSERT(match_distance >= 0);
                if (match_distance > LXLZ4_MATCH_DISTANCE_MAX) { valid_match = LXLZ4_FALSE; }
            }
            if (valid_match)
            {
                // found match
                const uint8_t* nip = cip + 4;
                const uint8_t* nmatch = match + 4;
                // backward match
                while (cip > ip/*anchor*/ && (matchdic ? match > dicp : match > sip)/*match beginning*/ && cip[-1] == match[-1]/*actual match data*/) { --cip; --match; }
                // forward match
                const uint8_t* nip_end = eip - LXLZ4_LITERAL_END_MARGIN;
                if (nip_end > cip + match_length_max) { nip_end = cip + match_length_max + 1; }
                if (matchdic)
                {
                    // dictionary limit
                    if (nip_end - nip > edicp - nmatch) { nip_end = nip + (edicp - nmatch); }
                }
#ifndef LXLZ4_NO_UNALIGNED_MEMORY_ACCESS
                while (nip < nip_end - 8 && LXLZ4_INTERNAL_MATCH64(nmatch, nip)) { nmatch += 8; nip += 8; }
                if (nip < nip_end - 4 && LXLZ4_INTERNAL_MATCH32(nmatch, nip)) { nmatch += 4; nip += 4; }
#endif // #ifndef LXLZ4_NO_UNALIGNED_MEMORY_ACCESS
                while (nip < nip_end && nmatch[0] == nip[0]) { ++nmatch; ++nip; }
                // limit matching
                const size_t match_length = (size_t)(nmatch - match);
                LXLZ4_ASSERT(match_length <= match_length_max);
                LXLZ4_ASSERT(match_length == (size_t)(nip - cip));
                const size_t match_length_embed = match_length - LXLZ4_MATCH_LENGTH_BIAS;
                // flush token(ip -> cip as copy literal, cip -> nip as match)
                const size_t copy_length = (size_t)(cip - ip);
                const uint8_t token = (uint8_t)(
                    (((copy_length > LXLZ4_LITERAL_LENGTH_VL ? LXLZ4_LITERAL_LENGTH_VL : copy_length) & 0x0f) << 4) |
                    ((match_length_embed > LXLZ4_MATCH_LENGTH_VL ? LXLZ4_MATCH_LENGTH_VL : match_length_embed) & 0x0f)
                    );
                if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                *op++ = token;
                // copy literal
                if (copy_length >= LXLZ4_LITERAL_LENGTH_VL)
                {
                    size_t remaining = copy_length - LXLZ4_LITERAL_LENGTH_VL;
                    while (remaining >= 0xff)
                    {
                        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                        *op++ = 0xff;
                        remaining -= 0xff;
                    }
                    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                    *op++ = (uint8_t)remaining;
                }
                // literal data
                if (LXLZ4_INTERNAL_OUTOFRANGE(op, copy_length, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                LXLZ4_MEMCPY(op, ip, copy_length);
                op += copy_length;
                // match offset
                if (LXLZ4_INTERNAL_OUTOFRANGE(op, 2, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                const uint16_t match_offset = (uint16_t)match_distance;
                LXLZ4_ASSERT(match_offset > 0);
                LXLZ4_ASSERT(matchdic || (cip - match_offset >= sip));
                LXLZ4_INTERNAL_STOREU16(op, match_offset);
                op += 2;
                // match length
                if (match_length_embed >= LXLZ4_MATCH_LENGTH_VL)
                {
                    size_t remaining = match_length_embed - LXLZ4_MATCH_LENGTH_VL;
                    while (remaining >= 0xff)
                    {
                        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                        *op++ = 0xff;
                        remaining -= 0xff;
                    }
                    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                    *op++ = (uint8_t)remaining;
                }
                //LXLZ4_INTERNAL_DPRINTF("token copy(%zu) offset(%d) match(%zu)\n", copy_length, match_offset, match_length);

                // next cip
                cip = nip;
                // reset acceleration
                accel = 0;
                // skipped data hashes
                if (matched_block_hash_range > 0 && !matchdic)
                {
                    nip = cip - matched_block_hash_range;
                    if (nip <= ip) { nip = ip + 1; }
                    // protect last hash unit
                    nip_end = cip;
                    if (nip_end + hash_unit > eip) { nip_end = eip - hash_unit; }
                    while (nip < nip_end)
                    {
                        LXLZ4_INTERNAL_PUT_HASH(input_range, htable, LXLZ4_INTERNAL_COMPUTE_HASH(nip, hash_bits, hash_unit), (nip - sip + dictionary_size));
                        nip += matched_block_hash_step;
                    }
                }
                // rewind ip(anchor)
                ip = cip;
                continue;
            }
            // step acceleration
            if (accel_to_step == 0)
            {
                ++cip;
            }
            else
            {
                const size_t step = (accel >> accel_to_step) + 1;
                cip += step;
                ++accel;
            }
        }
    }
    // last literal
    if (ip < eip/*any input remains*/ || sip == ip/*no output performed*/ || !do_compress)// force output last literal in case no compression performed
    {
        // remaining inputs will be copied
        size_t remaining = (size_t)(eip - ip);
        //LXLZ4_INTERNAL_DPRINTF("last run(%zu)\n", remaining);
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        if (remaining >= LXLZ4_LITERAL_LENGTH_VL)
        {
            *op++ = (uint8_t)(LXLZ4_LITERAL_LENGTH_VL << 4);
            remaining -= LXLZ4_LITERAL_LENGTH_VL;
            while (remaining >= 0xff)
            {
                if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
                *op++ = 0xff;
                remaining -= 0xff;
            }
            if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
            *op++ = (uint8_t)remaining;
        }
        else
        {
            *op++ = (uint8_t)(remaining << 4);
        }
        // literal data
        remaining = (size_t)(eip - ip);
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, remaining, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_MEMCPY(op, ip, remaining);
        op += remaining;
        // pointer
        ip = cip = eip;
    }
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    return LXLZ4_ERROR_NONE;
}

#undef LXLZ4_INTERNAL_COMPUTE_HASH
#undef LXLZ4_INTERNAL_PUT_HASH
#undef LXLZ4_INTERNAL_GET_HASH

LXLZ4_STRONG_INLINE lxlz4_error_e lxlz4_internal_llcompress_raw_branch(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* work, size_t work_size, lxlz4_compress_level_e level, lxlz4_input_range_e input_range, const void* dictionary, size_t dictionary_size)
{
    // fix input range
    size_t input_size = src_size + (dictionary ? dictionary_size : 0);
    if (input_size <= 0xffff && input_range > LXLZ4_INPUT_RANGE_U16) { input_range = LXLZ4_INPUT_RANGE_U16; }
    else if (input_size <= 0xffffffffU && input_range > LXLZ4_INPUT_RANGE_U32) { input_range = LXLZ4_INPUT_RANGE_U32; }
    else if (input_range == LXLZ4_INPUT_RANGE_U64 && SIZE_MAX == UINT32_MAX) { input_range = LXLZ4_INPUT_RANGE_U32; }// cannot handle u64 value by size_t(assuming than in such cases, there are no enough memory space to hold src larger than UINT32_MAX)

    if (input_size > lxlz4_internal_input_range_to_num_limit(input_range)) { return LXLZ4_ERROR_COMPRESS_TOO_LARGE_INPUT_DATA_SIZE; }

#define LXLZ4_INTERNAL_LLCOMPRESS_BRANCH_RANGE(do_compress, hash_bits, hash_unit, accel_to_step, matched_block_hash_range, matched_block_hash_step, dictionary, dictionary_size) \
    switch (input_range) \
    { \
        case LXLZ4_INPUT_RANGE_U16: return lxlz4_internal_llcompress_raw(dst, dst_size, dst_written, src, src_size, work, work_size, do_compress, hash_bits, hash_unit, LXLZ4_INPUT_RANGE_U16, accel_to_step, matched_block_hash_range, matched_block_hash_step, dictionary, dictionary_size); \
        case LXLZ4_INPUT_RANGE_U32: return lxlz4_internal_llcompress_raw(dst, dst_size, dst_written, src, src_size, work, work_size, do_compress, hash_bits, hash_unit, LXLZ4_INPUT_RANGE_U32, accel_to_step, matched_block_hash_range, matched_block_hash_step, dictionary, dictionary_size); \
        case LXLZ4_INPUT_RANGE_U64: return lxlz4_internal_llcompress_raw(dst, dst_size, dst_written, src, src_size, work, work_size, do_compress, hash_bits, hash_unit, LXLZ4_INPUT_RANGE_U64, accel_to_step, matched_block_hash_range, matched_block_hash_step, dictionary, dictionary_size); \
        default: break; \
    }
#define LXLZ4_INTERNAL_LLCOMPRESS_BRANCH(do_compress, hash_bits, hash_unit, accel_to_step, matched_block_hash_range, matched_block_hash_step) \
    if (dictionary) \
    { \
        LXLZ4_INTERNAL_LLCOMPRESS_BRANCH_RANGE(do_compress, hash_bits, hash_unit, accel_to_step, matched_block_hash_range, matched_block_hash_step, dictionary, dictionary_size); \
    } \
    else \
    { \
        LXLZ4_INTERNAL_LLCOMPRESS_BRANCH_RANGE(do_compress, hash_bits, hash_unit, accel_to_step, matched_block_hash_range, matched_block_hash_step, NULL, 0); \
    }

    switch (level)
    {
    case LXLZ4_COMPRESS_LEVEL_NOCOMPRESS:
        return lxlz4_internal_llcompress_raw(dst, dst_size, dst_written, src, src_size, work, work_size, LXLZ4_FALSE, 0, 4, input_range, 0, 0, 0, NULL, 0);
    case LXLZ4_COMPRESS_LEVEL_TINY:
        LXLZ4_INTERNAL_LLCOMPRESS_BRANCH(LXLZ4_TRUE, LXLZ4_INTERNAL_HASH_BITS_TINY, LXLZ4_INTERNAL_HASH_UNIT_TINY, LXLZ4_INTERNAL_ATOS_TINY, LXLZ4_INTERNAL_MBH_RANGE_TINY, LXLZ4_INTERNAL_MBH_STEP_TINY);
        break;
    case LXLZ4_COMPRESS_LEVEL_FAST:
        LXLZ4_INTERNAL_LLCOMPRESS_BRANCH(LXLZ4_TRUE, LXLZ4_INTERNAL_HASH_BITS_FAST, LXLZ4_INTERNAL_HASH_UNIT_FAST, LXLZ4_INTERNAL_ATOS_FAST, LXLZ4_INTERNAL_MBH_RANGE_FAST, LXLZ4_INTERNAL_MBH_STEP_FAST);
        break;
    case LXLZ4_COMPRESS_LEVEL_NORMAL:
        LXLZ4_INTERNAL_LLCOMPRESS_BRANCH(LXLZ4_TRUE, LXLZ4_INTERNAL_HASH_BITS_NORMAL, LXLZ4_INTERNAL_HASH_UNIT_NORMAL, LXLZ4_INTERNAL_ATOS_NORMAL, LXLZ4_INTERNAL_MBH_RANGE_NORMAL, LXLZ4_INTERNAL_MBH_STEP_NORMAL);
        break;
    default:
        break;
    };
    return LXLZ4_ERROR_INVALID_COMPRESS_OPTION;

#undef LXLZ4_INTERNAL_LLCOMPRESS_BRANCH
#undef LXLZ4_INTERNAL_LLCOMPRESS_BRANCH_RANGE
}

LXLZ4_STRONG_INLINE lxlz4_error_e lxlz4_internal_lldecompress_raw(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const void* dictionary, size_t dictionary_size)
{
    if (!src) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
    // prepare io
    const uint8_t* ip = (const uint8_t*)src;
    const uint8_t* eip = ip + src_size;
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    // prepare dictionary
    const lxlz4_bool_t op_prefix_dic = dictionary == LXLZ4_DICTIONARY_OUTPUT_PREFIX;
    const uint8_t* dicp = (const uint8_t*)dictionary;
    const uint8_t* edicp = dicp + dictionary_size;
    if (dictionary)
    {
        if (op_prefix_dic)
        {
            edicp = sop;
            dicp = sop - dictionary_size;
        }
        if (dictionary_size > LXLZ4_DICTIONARY_SIZE_MAX)
        {
            dictionary_size = LXLZ4_DICTIONARY_SIZE_MAX;
            dicp = edicp - LXLZ4_DICTIONARY_SIZE_MAX;
        }
    }
    // decode all tokens
    for (;;)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 1, eip))  { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
        const uint8_t token = *ip++;
        size_t copy_length = (token >> 4) & 0x0f;
        size_t match_length = token & 0x0f;
        // literal
        if (copy_length == LXLZ4_LITERAL_LENGTH_VL)
        {
            for (;;)
            {
                if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 1, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
                const uint8_t ad = *ip++;
                copy_length += ad;
                if (ad < 0xff) { break; }
            }
        }
        if (LXLZ4_LIKELY(copy_length > 0))
        {
            if (LXLZ4_INTERNAL_OUTOFRANGE(ip, copy_length, eip))  { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
            if (LXLZ4_INTERNAL_OUTOFRANGE(op, copy_length, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
            LXLZ4_MEMCPY(op, ip, copy_length);
            ip += copy_length;
            op += copy_length;
        }
        // end of block ?
        if (LXLZ4_UNLIKELY(ip == eip && match_length == 0))
        {
            //LXLZ4_INTERNAL_DPRINTF("decompress last run copy(%zu) match(%zu)\n", copy_length, match_length);
            break;
        }
        // offset
        if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 2, eip))  { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
        const uint32_t offset = LXLZ4_INTERNAL_LOADU16(ip);
        ip += 2;
        if (LXLZ4_UNLIKELY(offset == 0)) { return LXLZ4_ERROR_DECOMPRESS_ZERO_OFFSET; }
        // match
        if (match_length == LXLZ4_MATCH_LENGTH_VL)
        {
            for (;;)
            {
                if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 1, eip))  { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
                const uint8_t ad = *ip++;
                match_length += ad;
                if (ad < 0xff) { break; }
            }
        }
        match_length += LXLZ4_MATCH_LENGTH_BIAS;
        const uint8_t* match = op - offset;
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, match_length, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        const uint8_t* match_end = eop;
        if (LXLZ4_UNLIKELY(match < sop))
        {
            // check dictionary
            const size_t dictionary_offset = (size_t)(sop - match);
            if (!dictionary || dictionary_offset > dictionary_size) { return LXLZ4_ERROR_DECOMPRESS_OFFSET_OUT_OF_RANGE; }
            if (!op_prefix_dic && match_length > dictionary_offset) { return LXLZ4_ERROR_DECOMPRESS_MATCH_LENGTH_OUT_OF_RANGE; }
            match = edicp - dictionary_offset;
            match_end = edicp;
        }
        if (LXLZ4_LIKELY((eop - op) >= 15/*8 + 7*/) && LXLZ4_LIKELY(match + match_length <= match_end - 15) && offset >= 8)
        {
            // wildcopy
            lxlz4_internal_matchcopy_greedy(op, match, match_length, offset, LXLZ4_FALSE);
        }
        else
        {
            // strict copy
            lxlz4_internal_matchcopy_branch(op, match, match_length, offset);
        }
        op += match_length;
        // end of block ?(accept non-zero match_length for last sequence)
        if (LXLZ4_UNLIKELY(ip == eip)) { break; }
       // if (op < sop + 16) { LXLZ4_INTERNAL_DPRINTF("decompress copy(%zu) offset(%d) match(%zu)\n", copy_length, offset, match_length); }
    }
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - (uint8_t*)dst); }
    return LXLZ4_ERROR_NONE;
}

LXLZ4_STRONG_INLINE lxlz4_error_e lxlz4_internal_lldecompress_raw_branch(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const void* dictionary, size_t dictionary_size)
{
#define LXLZ4_INTERNAL_LLDECOMPRESS_BRANCH() \
    if (dictionary == LXLZ4_DICTIONARY_OUTPUT_PREFIX) \
    { \
        return lxlz4_internal_lldecompress_raw(dst, dst_size, dst_written, src, src_size, LXLZ4_DICTIONARY_OUTPUT_PREFIX, dictionary_size); \
    } \
    else if (dictionary) \
    { \
        return lxlz4_internal_lldecompress_raw(dst, dst_size, dst_written, src, src_size, dictionary, dictionary_size); \
    } \
    else \
    { \
        return lxlz4_internal_lldecompress_raw(dst, dst_size, dst_written, src, src_size, NULL, 0); \
    }

    LXLZ4_INTERNAL_LLDECOMPRESS_BRANCH();

#undef LXLZ4_INTERNAL_LLDECOMPRESS_BRANCH
}

//
//    common
//
LXLZ4_API size_t lxlz4_block_bytesize(lxlz4_block_size_e block_size)
{
    if (block_size < 0 || block_size >= LXLZ4_BLOCK_SIZE_END) { return 0; }
    return (size_t)(64 * 1024) << (size_t)block_size;
}

//
//    xxhash
//

// the algorithm is based on https://github.com/Cyan4973/xxHash/blob/release/doc/xxhash_spec.md
#define LXLZ4_XXH32_PRIME32_1   (0x9E3779B1U)// 0b10011110001101110111100110110001
#define LXLZ4_XXH32_PRIME32_2   (0x85EBCA77U)// 0b10000101111010111100101001110111
#define LXLZ4_XXH32_PRIME32_3   (0xC2B2AE3DU)// 0b11000010101100101010111000111101
#define LXLZ4_XXH32_PRIME32_4   (0x27D4EB2FU)// 0b00100111110101001110101100101111
#define LXLZ4_XXH32_PRIME32_5   (0x165667B1U)// 0b00010110010101100110011110110001

#define LXLZ4_INTERNAL_ROTL32(v, shift) \
    (((v) << (shift)) | ((v) >> (32 - (shift))))

LXLZ4_API uint32_t lxlz4_xxhash32(const void* src, size_t src_size, uint32_t seed)
{
    uint32_t acc = 0;
    size_t remaining_length = src_size;
    const uint8_t* ip = (const uint8_t*)src;
    // step.1
    if (src_size < 16)
    {
        acc = seed + LXLZ4_XXH32_PRIME32_5;
    }
    else
    {
        uint32_t accN[4];
        accN[0] = seed + LXLZ4_XXH32_PRIME32_1 + LXLZ4_XXH32_PRIME32_2;
        accN[1] = seed + LXLZ4_XXH32_PRIME32_2;
        accN[2] = seed + 0;
        accN[3] = seed - LXLZ4_XXH32_PRIME32_1;
        // step.2
        do
        {
            for (size_t i = 0; i < 4; ++i)
            {
                const uint32_t lane = LXLZ4_INTERNAL_LOADU32(ip);
                accN[i] = accN[i] + (lane * LXLZ4_XXH32_PRIME32_2);
                accN[i] = LXLZ4_INTERNAL_ROTL32(accN[i], 13);
                accN[i] = accN[i] * LXLZ4_XXH32_PRIME32_1;
                ip += 4;
            }
            remaining_length -= 16;
        } while (remaining_length >= 16);
        // step.3
        acc = LXLZ4_INTERNAL_ROTL32(accN[0], 1) + LXLZ4_INTERNAL_ROTL32(accN[1], 7) + LXLZ4_INTERNAL_ROTL32(accN[2], 12) + LXLZ4_INTERNAL_ROTL32(accN[3], 18);
    }
    // step.4
    acc += (uint32_t)src_size;
    // step.5
    while (remaining_length >= 4)
    {
        const uint32_t lane = LXLZ4_INTERNAL_LOADU32(ip);
        acc = acc + lane * LXLZ4_XXH32_PRIME32_3;
        acc = LXLZ4_INTERNAL_ROTL32(acc, 17) * LXLZ4_XXH32_PRIME32_4;
        ip += 4; remaining_length -= 4;
    }
    while (remaining_length >= 1)
    {
        const uint8_t lane = *ip;
        acc = acc + lane * LXLZ4_XXH32_PRIME32_5;
        acc = LXLZ4_INTERNAL_ROTL32(acc, 11) * LXLZ4_XXH32_PRIME32_1;
        ip += 1; remaining_length -= 1;
    }
    // step.6
    acc = acc ^ (acc >> 15);
    acc = acc * LXLZ4_XXH32_PRIME32_2;
    acc = acc ^ (acc >> 13);
    acc = acc * LXLZ4_XXH32_PRIME32_3;
    acc = acc ^ (acc >> 16);
    // result
    return acc;
}

#undef LXLZ4_INTERNAL_ROTL32

//
//    compress
//
LXLZ4_API void lxlz4_compress_option_init(lxlz4_compress_option_t* copt)
{
    LXLZ4_ASSERT(copt);
    if (!copt) { return; }

    copt->level_ = LXLZ4_COMPRESS_LEVEL_FAST;
    copt->dictionary_ = NULL;
    copt->dictionary_size_ = 0;
    copt->input_range_ = LXLZ4_INPUT_RANGE_U32;

    copt->is_block_independent_ = LXLZ4_TRUE;
    copt->embed_block_checksum_ = LXLZ4_TRUE;
    copt->embed_content_size_ = LXLZ4_TRUE;
    copt->embed_content_checksum_ = LXLZ4_TRUE;
    copt->embed_dictionary_id_ = LXLZ4_FALSE;
    copt->block_max_size_ = LXLZ4_BLOCK_SIZE_64KB;
    copt->dictionary_id_ = 0;
}

LXLZ4_API void lxlz4_compress_option_init_compatible(lxlz4_compress_option_t* copt)
{
    LXLZ4_ASSERT(copt);
    if (!copt) { return; }

    lxlz4_compress_option_init(copt);

    copt->is_block_independent_ = LXLZ4_FALSE;
    copt->embed_block_checksum_ = LXLZ4_FALSE;
    copt->embed_content_size_ = LXLZ4_TRUE;
    copt->embed_content_checksum_ = LXLZ4_FALSE;
    copt->embed_dictionary_id_ = LXLZ4_FALSE;
    copt->block_max_size_ = LXLZ4_BLOCK_SIZE_64KB;
}

LXLZ4_API size_t lxlz4_compress_bound(size_t src_size, const lxlz4_compress_option_t* copt)
{
    (void)(copt);
    return src_size + src_size / 255 + 128;
}

LXLZ4_API lxlz4_error_e lxlz4_compress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const lxlz4_compress_option_t* copt, void* alloc_user)
{
    lxlz4_error_e e = LXLZ4_ERROR_NONE;
    lxlz4_llcompress_context_t context;
    e = lxlz4_llcompress_begin(&context, copt, alloc_user);
    if (e != LXLZ4_ERROR_NONE) { return e; }
    e = lxlz4_llcompress_raw(dst, dst_size, dst_written, src, src_size, context.work_, context.work_size_, &context.copt_);
    lxlz4_llcompress_end(&context);
    // accepted
    return e;
}

LXLZ4_API size_t lxlz4_frame_compress_bound(size_t src_size, const lxlz4_compress_option_t* copt)
{
    lxlz4_compress_option_t dummy_copt;
    if (!copt) { lxlz4_compress_option_init(&dummy_copt); copt = &dummy_copt; }
    const size_t block_max_size = lxlz4_block_bytesize(copt->block_max_size_);
    size_t compress_bound = LXLZ4_FRAME_MARGIN_SIZE_MAX;
    // data blocks
    size_t remaining = src_size;
    do
    {
        const size_t block_size = remaining > block_max_size ? block_max_size : remaining;
        compress_bound += lxlz4_compress_bound(block_size, copt) + LXLZ4_BLOCK_MARGIN_SIZE_MAX;
        remaining -= block_size;
    } while (remaining > 0);
    compress_bound += LXLZ4_BLOCK_MARGIN_SIZE_MAX;// endmark block
    return compress_bound;
}

LXLZ4_API lxlz4_error_e lxlz4_frame_compress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, const lxlz4_compress_option_t* copt, void* alloc_user)
{
    lxlz4_error_e e = LXLZ4_ERROR_NONE;
    lxlz4_llcompress_context_t context;
    e = lxlz4_llcompress_begin(&context, copt, alloc_user);
    if (e != LXLZ4_ERROR_NONE) { return e; }
    // prepare block temporary memory
    const size_t block_max_size = lxlz4_block_bytesize(context.copt_.block_max_size_);
    const size_t block_compressed_max_size = lxlz4_compress_bound(block_max_size, &context.copt_);
    void* block_compressed = LXLZ4_MALLOC(block_compressed_max_size, alloc_user);
    if (!block_compressed)
    {
        lxlz4_llcompress_end(&context);
        return LXLZ4_ERROR_MEMALLOC_FAILED;
    }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    size_t op_written = 0;
    // frame format
    {
        // enter frame
        e = lxlz4_llcompress_enter_frame(&context, op, (size_t)(eop - op), &op_written, src_size);
        if (e == LXLZ4_ERROR_NONE)
        {
            op += op_written; op_written = 0;

            // divide source data to blocks, compress them and concat these compressed blocks.
            const uint8_t* ip = (const uint8_t*)src;
            size_t remaining = src_size;

            const uint8_t* prev_block = NULL;
            size_t prev_block_size = 0;

            do
            {
                const size_t in_block_size = remaining > block_max_size ? block_max_size : remaining;

                // compress block content
                lxlz4_bool_t is_compressed = LXLZ4_TRUE;
                size_t block_compressed_size = 0;

                lxlz4_bool_t is_to_compress = LXLZ4_TRUE;
                if (context.copt_.level_ == LXLZ4_COMPRESS_LEVEL_NOCOMPRESS)
                {
                    is_to_compress = LXLZ4_FALSE;
                }

                // try to make compressed data
                if (is_to_compress)
                {
                    is_compressed = LXLZ4_TRUE;
                    if (context.copt_.is_block_independent_ || !prev_block)
                    {
                        e = lxlz4_llcompress_raw(block_compressed, block_compressed_max_size, &block_compressed_size, ip, in_block_size, context.work_, context.work_size_, &context.copt_);
                    }
                    else
                    {
                        e = lxlz4_internal_llcompress_raw_branch(block_compressed, block_compressed_max_size, &block_compressed_size, ip, in_block_size, context.work_, context.work_size_, context.copt_.level_, context.copt_.input_range_, prev_block, prev_block_size);
                    }
                    if (e != LXLZ4_ERROR_NONE) { break; }

                    // In case compressed block is larger than or equal to uncompressed data, make it uncompressed data block.
                    // And we can ensure that the size of output block data is less than or equal to the in_block_data, which is also less than or equal to block_max_size.
                    if (block_compressed_size >= in_block_size)
                    {
                        is_to_compress = LXLZ4_FALSE;
                    }
                }

                // uncompressed data block ?
                if (!is_to_compress)
                {
                    is_compressed = LXLZ4_FALSE;
                }

                // determine writing block data source
                const void* write_block_data = is_compressed ? block_compressed : ip;
                const size_t write_block_data_size = is_compressed ? block_compressed_size : in_block_size;
                LXLZ4_ASSERT(write_block_data_size <= block_max_size);

                // enter block
                e = lxlz4_llcompress_enter_block(&context, op, (size_t)(eop - op), &op_written, (uint32_t)write_block_data_size, is_compressed);
                if (e != LXLZ4_ERROR_NONE) { break; }
                op += op_written; op_written = 0;

                // block content
                if (write_block_data_size > 0)
                {
                    if (LXLZ4_INTERNAL_OUTOFRANGE(op, write_block_data_size, eop))
                    {
                        e = LXLZ4_ERROR_INSUFFICIENT_OUTPUT;
                        break;
                    }
                    LXLZ4_MEMCPY(op, write_block_data, write_block_data_size);
                    op += write_block_data_size;
                }

                // leave block
                uint32_t block_checksum = 0;
                if (context.copt_.embed_block_checksum_) { block_checksum = lxlz4_xxhash32(write_block_data, write_block_data_size, 0); }
                e = lxlz4_llcompress_leave_block(&context, op, (size_t)(eop - op), &op_written, block_checksum);
                if (e != LXLZ4_ERROR_NONE) { break; }
                op += op_written; op_written = 0;

                // store as prev
                prev_block = ip;
                prev_block_size = in_block_size;

                // consume input
                ip += in_block_size;
                remaining -= in_block_size;

                //LXLZ4_INTERNAL_DPRINTF("block in(%zu) -> out(%zu) checksum(%u)\n", in_block_size, block_compressed_size, block_checksum);
            } while (remaining > 0);

            // leave frame
            if (e == LXLZ4_ERROR_NONE)
            {
                uint32_t content_checksum = 0;
                if (context.copt_.embed_content_checksum_) { content_checksum = lxlz4_xxhash32(src, src_size, 0); }
                e = lxlz4_llcompress_leave_frame(&context, op, (size_t)(eop - op), &op_written, content_checksum);
                op += op_written; op_written = 0;
            }
        }
    }
    LXLZ4_FREE(block_compressed, alloc_user);
    lxlz4_llcompress_end(&context);
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    return e;
}

// low level api
LXLZ4_API size_t lxlz4_llcompress_work_size(const lxlz4_compress_option_t* copt)
{
    lxlz4_compress_option_t dummy_copt;
    if (!copt) { lxlz4_compress_option_init(&dummy_copt); copt = &dummy_copt; }
    size_t hash_bits = 0;
    switch (copt->level_)
    {
    case LXLZ4_COMPRESS_LEVEL_TINY: hash_bits = LXLZ4_INTERNAL_HASH_BITS_TINY; break;
    case LXLZ4_COMPRESS_LEVEL_FAST: hash_bits = LXLZ4_INTERNAL_HASH_BITS_FAST; break;
    case LXLZ4_COMPRESS_LEVEL_NORMAL: hash_bits = LXLZ4_INTERNAL_HASH_BITS_NORMAL; break;
    default: break;
    }
    return ((size_t)1 << hash_bits) * lxlz4_internal_input_range_to_size(copt->input_range_);
}

LXLZ4_API size_t lxlz4_llcompress_work_size_max()
{
    lxlz4_compress_option_t copt;
    lxlz4_compress_option_init(&copt);
    copt.level_ = LXLZ4_COMPRESS_LEVEL_MAX;
    copt.input_range_ = LXLZ4_INPUT_RANGE_MAX;
    copt.block_max_size_ = LXLZ4_BLOCK_SIZE_64KB;
    return lxlz4_llcompress_work_size(&copt);
}

LXLZ4_API size_t lxlz4_llcompress_work_align(const lxlz4_compress_option_t* copt)
{
    (void)(copt);
    return LXLZ4_WORK_ALIGN;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_begin(lxlz4_llcompress_context_t* context, const lxlz4_compress_option_t* copt, void* alloc_user)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }

    const size_t work_size = lxlz4_llcompress_work_size(copt);
    if (work_size == 0) { return LXLZ4_ERROR_INVALID_COMPRESS_OPTION; }
    void* work_allocated = LXLZ4_MALLOC(work_size, alloc_user);
    if (!work_allocated) { return LXLZ4_ERROR_MEMALLOC_FAILED; }

    const lxlz4_error_e e = lxlz4_llcompress_begin_work(context, copt, work_allocated, work_size);
    if (e != LXLZ4_ERROR_NONE)
    {
        LXLZ4_FREE(work_allocated, alloc_user);
        return e;
    }

    context->work_allocated_ = work_allocated;
    context->alloc_user_ = alloc_user;

    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_begin_work(lxlz4_llcompress_context_t* context, const lxlz4_compress_option_t* copt, void* work, size_t work_size)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }
    if (!work) { return LXLZ4_ERROR_COMPRESS_INSUFFICIENT_WORK; }

    if (copt) { context->copt_ = *copt; }
    else { lxlz4_compress_option_init(&context->copt_); }

    if (work != NULL && work > 0)
    {
        // check work space
        void* work_use = work;
        const uintptr_t work_align_shift = (uintptr_t)work % LXLZ4_WORK_ALIGN;
        if (work_align_shift > 0)
        {
            const size_t diff = (size_t)(LXLZ4_WORK_ALIGN - work_align_shift);
            work_use = (void*)((uintptr_t)work + diff);
            work_size -= diff;
        }
        if (work_size < lxlz4_llcompress_work_size(&context->copt_)) { return LXLZ4_ERROR_COMPRESS_INSUFFICIENT_WORK; }
    }

    context->state_ = LXLZ4_LLCOMPRESS_STATE_INIT;
    context->total_in_ = 0;
    context->processed_in_ = 0;
    context->total_out_ = 0;

    context->work_ = work;
    context->work_size_ = work_size;
    context->work_allocated_ = NULL;

    return LXLZ4_ERROR_NONE;
}

LXLZ4_API void lxlz4_llcompress_end(lxlz4_llcompress_context_t* context)
{
    if (!context) { return; }

    if (context->work_allocated_)
    {
        LXLZ4_FREE(context->work_allocated_, context->alloc_user_);
        context->work_allocated_ = NULL;
    }
    context->work_ = NULL;
    context->work_size_ = 0;

    context->alloc_user_ = NULL;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_raw(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* work, size_t work_size, const lxlz4_compress_option_t* copt)
{
    if (!copt) { return LXLZ4_ERROR_INVALID_COMPRESS_OPTION; }
    return lxlz4_internal_llcompress_raw_branch(dst, dst_size, dst_written, src, src_size, work, work_size, copt->level_, copt->input_range_, copt->dictionary_, copt->dictionary_size_);
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_enter_frame(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint64_t content_size)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }
    if (context->state_ != LXLZ4_LLCOMPRESS_STATE_INIT) { return LXLZ4_ERROR_WRITER_STATE_MISMATCH; }
    if (!dst) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    // magic number
    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    LXLZ4_INTERNAL_STOREU32(op, LXLZ4_FRAME_MAGIC);
    op += 4;
    // frame descriptor
    const uint8_t* fdp = op;
    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    *op++ = (0x01 << 6) |// version
        ((context->copt_.is_block_independent_ ? 1 : 0) << 5) |
        ((context->copt_.embed_block_checksum_ ? 1 : 0) << 4) |
        ((context->copt_.embed_content_size_ ? 1 : 0) << 3) |
        ((context->copt_.embed_content_checksum_ ? 1 : 0) << 2) |
        ((context->copt_.embed_dictionary_id_ ? 1 : 0) << 0)
        ;
    // bd
    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    *op++ = ((context->copt_.block_max_size_ & 0x07) + 4) << 4;
    // content size
    if (context->copt_.embed_content_size_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 8, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_INTERNAL_STOREU64(op, content_size);
        op += 8;
    }
    // dictionary id
    if (context->copt_.embed_dictionary_id_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_INTERNAL_STOREU32(op, context->copt_.dictionary_id_);
        op += 4;
    }
    // header checksum
    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 1, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    const uint32_t hc = lxlz4_xxhash32(fdp, (size_t)(op - fdp), 0);
    *op = (hc >> 8) & 0xff;
    ++op;
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    context->state_ = LXLZ4_LLCOMPRESS_STATE_FRAME_HEADER;
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_leave_frame(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t content_checksum)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }
    if (context->state_ != LXLZ4_LLCOMPRESS_STATE_BLOCK_DATA) { return LXLZ4_ERROR_WRITER_STATE_MISMATCH; }
    if (!dst) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    // endmark
    {
        uint32_t v = 0;
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_INTERNAL_STOREU32(op, v);
        op += 4;
#if 0
        if (context->copt_.embed_block_checksum_)
        {
            v = lxlz4_xxhash32(NULL, 0, 0);
            if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
            LXLZ4_INTERNAL_STOREU32(op, v);
            op += 4;
        }
#endif
    }
    // content checksum
    if (context->copt_.embed_content_checksum_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_INTERNAL_STOREU32(op, content_checksum);
        op += 4;
    }
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    context->state_ = LXLZ4_LLCOMPRESS_STATE_FINISHED;
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_enter_block(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t block_size, lxlz4_bool_t block_compressed)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }
    if (context->state_ != LXLZ4_LLCOMPRESS_STATE_FRAME_HEADER && context->state_ != LXLZ4_LLCOMPRESS_STATE_BLOCK_DATA) { return LXLZ4_ERROR_WRITER_STATE_MISMATCH; }
    if (!dst) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    // block size
    if (!block_compressed) { block_size |= 0x80000000U; }
    if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    LXLZ4_INTERNAL_STOREU32(op, block_size);
    op += 4;
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    context->state_ = LXLZ4_LLCOMPRESS_STATE_BLOCK_DATA;
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_error_e lxlz4_llcompress_leave_block(lxlz4_llcompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, uint32_t block_checksum)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }
    if (context->state_ != LXLZ4_LLCOMPRESS_STATE_BLOCK_DATA) { return LXLZ4_ERROR_WRITER_STATE_MISMATCH; }
    if (!dst) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
    // prepare io
    uint8_t* op = (uint8_t*)dst;
    uint8_t* sop = op;
    uint8_t* eop = op + dst_size;
    // checksum
    if (context->copt_.embed_block_checksum_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(op, 4, eop)) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_INTERNAL_STOREU32(op, block_checksum);
        op += 4;
    }
    // accepted
    if (dst_written) { *dst_written = (size_t)(op - sop); }
    return LXLZ4_ERROR_NONE;
}

//
//    decompress
//
LXLZ4_API lxlz4_error_e lxlz4_decompress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* alloc_user)
{
    lxlz4_error_e e = LXLZ4_ERROR_NONE;
    lxlz4_lldecompress_context_t context;
    e = lxlz4_lldecompress_begin(&context, alloc_user);
    if (e != LXLZ4_ERROR_NONE) { return e; }
    e = lxlz4_lldecompress_raw(&context, dst, dst_size, dst_written, src, src_size);
    lxlz4_lldecompress_end(&context);
    return e;
}

LXLZ4_API lxlz4_error_e lxlz4_frame_decompressd_size(uint64_t* content_size, const void* src, size_t src_size)
{
    if (!src) { return LXLZ4_ERROR_GENERAL; }
    lxlz4_frame_t frame;
    const lxlz4_error_e e = lxlz4_frame_extract(&frame, src, src_size);
    if (e != LXLZ4_ERROR_NONE) { return e; }
    if (content_size && frame.has_content_size_) { *content_size = frame.content_size_; }
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_error_e lxlz4_frame_decompress(void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size, void* alloc_user)
{
    lxlz4_error_e e = LXLZ4_ERROR_NONE;
    lxlz4_lldecompress_context_t context;
    e = lxlz4_lldecompress_begin(&context, alloc_user);
    if (e != LXLZ4_ERROR_NONE) { return e; }
    // parse all blocks and decode them in sequence
    size_t written = 0;
    lxlz4_parse_t parse;
    lxlz4_frame_parse_init(&parse);
    if (lxlz4_frame_parse_begin(&parse, src, src_size))
    {
        uint8_t* op = (uint8_t*)dst;
        size_t op_size = dst_size;

        const void* prev_block = NULL;
        size_t prev_block_size = 0;
        (void)(prev_block);

        size_t block_index = 0;
        const lxlz4_block_t* block;
        for (;;)
        {
            block = lxlz4_frame_parse_next(&parse);
            if (!block) { break; }

            //LXLZ4_INTERNAL_DPRINTF("decompress block size(%zu) is_compressed(%d) checksum(%u)\n", block->block_size_, block->is_block_compressed_, block->block_checksum_);

            if (parse.frame_.has_block_checksum_)
            {
                const uint32_t block_checksum = lxlz4_xxhash32(block->block_data_, block->block_size_, 0);
                if (block_checksum != block->block_checksum_) { return LXLZ4_ERROR_BLOCK_CHECKSUM_MISMATCH; }
            }

            // ignore empty block such as ENDMARK
            if (block->block_size_ > 0)
            {
                size_t op_written = 0;
                e = lxlz4_lldecompress_block(&context, op, op_size, &op_written, block, &parse.frame_, LXLZ4_DICTIONARY_OUTPUT_PREFIX, prev_block_size, LXLZ4_TOBOOL(block_index == 0));
                if (e != LXLZ4_ERROR_NONE) { break; }

                prev_block = op;
                prev_block_size = op_written;

                op += op_written;
                LXLZ4_ASSERT(op_written <= op_size);
                op_size -= op_written;
                written += op_written;
            }

            ++block_index;
        }
        lxlz4_frame_parse_end(&parse);
    }
    if (e == LXLZ4_ERROR_NONE) { e = lxlz4_frame_parse_error(&parse); }
    lxlz4_lldecompress_end(&context);
    if (dst_written) { *dst_written = written; }
    return e;
}

// low level
LXLZ4_API lxlz4_error_e lxlz4_lldecompress_begin(lxlz4_lldecompress_context_t* context, void* alloc_user)
{
    if (!context) { return LXLZ4_ERROR_GENERAL; }

    context->dictionary_ = NULL;
    context->dictionary_size_ = 0;

    context->alloc_user_ = alloc_user;

    return LXLZ4_ERROR_NONE;
}

LXLZ4_API void lxlz4_lldecompress_end(lxlz4_lldecompress_context_t* context)
{
    if (!context) { return; }

    context->alloc_user_ = NULL;
}

LXLZ4_API lxlz4_error_e lxlz4_lldecompress_block(lxlz4_lldecompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, const lxlz4_block_t* block, const lxlz4_frame_t* frame, const void* prev_block, size_t prev_block_size, lxlz4_bool_t first_block)
{
    if (!dst || !block || !frame) { return LXLZ4_ERROR_GENERAL; }
    // uncompressed data
    if (!block->is_block_compressed_)
    {
        if (dst_size < block->block_size_) { return LXLZ4_ERROR_INSUFFICIENT_OUTPUT; }
        LXLZ4_MEMCPY(dst, block->block_data_, block->block_size_);
        if (dst_written) { *dst_written = block->block_size_; }
        return LXLZ4_ERROR_NONE;
    }
    // compressed data
    if (frame->is_block_independent_ || first_block) { return lxlz4_lldecompress_raw(context, dst, dst_size, dst_written, block->block_data_, block->block_size_); }
    // previous block dependent
    if (!prev_block) { return LXLZ4_ERROR_BLOCK_PREVIOUS_BLOCK_REQUIRED; }
    return lxlz4_internal_lldecompress_raw_branch(dst, dst_size, dst_written, block->block_data_, block->block_size_, prev_block, prev_block_size);
}

LXLZ4_API lxlz4_error_e lxlz4_lldecompress_raw(lxlz4_lldecompress_context_t* context, void* dst, size_t dst_size, size_t* dst_written, const void* src, size_t src_size)
{
    return lxlz4_internal_lldecompress_raw_branch(dst, dst_size, dst_written, src, src_size, context->dictionary_, context->dictionary_size_);
}

//
//    parser
//
LXLZ4_API void lxlz4_frame_init(lxlz4_frame_t* frame)
{
    if (!frame) { return; }

    frame->version_ = 0;
    frame->is_block_independent_ = LXLZ4_FALSE;
    frame->has_block_checksum_ = LXLZ4_FALSE;
    frame->has_content_size_ = LXLZ4_FALSE;
    frame->content_size_ = 0;
    frame->has_content_checksum_ = LXLZ4_FALSE;
    frame->has_dictionary_id_ = LXLZ4_FALSE;
    frame->dictionary_id_ = 0;
    frame->block_max_size_ = LXLZ4_BLOCK_SIZE_64KB;
    frame->header_size_ = 0;
}

LXLZ4_API lxlz4_error_e lxlz4_frame_extract(lxlz4_frame_t* frame, const void* src, size_t src_size)
{
    return lxlz4_frame_extract_ex(frame, src, src_size, LXLZ4_TRUE);
}

LXLZ4_API lxlz4_error_e lxlz4_frame_extract_ex(lxlz4_frame_t* frame, const void* src, size_t src_size, lxlz4_bool_t check_header_checksum)
{
    if (src_size < LXLZ4_FRAME_HEADER_SIZE_MIN) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
    const uint8_t* ip = (const uint8_t*)src;
    const uint8_t* eip = ip + src_size;
    // check magic number
    if (LXLZ4_INTERNAL_LOADU32(ip) != LXLZ4_FRAME_MAGIC) { return LXLZ4_ERROR_FRAME_MAGIC_NUMBER_MISMATCH; }
    ip += 4;
    // verify header
    lxlz4_frame_t dummy_frame;
    if (!frame) { frame = &dummy_frame; }
    // begin of frame descriptor
    const uint8_t* fdp = ip;
    // check flg
    const uint8_t flg = *ip++;
    if (flg & 0x1) { return LXLZ4_ERROR_INCOMPATIBLE_DATA; }// reserved bits must be 0
    frame->version_ = (flg >> 6) & 0x03;
    if (frame->version_ != 0x01) { return LXLZ4_ERROR_INCOMPATIBLE_DATA; }// unsupported version
    frame->is_block_independent_ = LXLZ4_TOBOOL(flg & 0x20);
    frame->has_block_checksum_ = LXLZ4_TOBOOL(flg & 0x10);
    frame->has_content_size_ = LXLZ4_TOBOOL(flg & 0x08);
    frame->has_content_checksum_ = LXLZ4_TOBOOL(flg & 0x04);
    frame->has_dictionary_id_ = LXLZ4_TOBOOL(flg & 0x01);
    // check bd
    const uint8_t bd = *ip++;
    if (bd & 0x8f) { return LXLZ4_ERROR_INCOMPATIBLE_DATA; }// reseved bits must be 0
    const uint8_t block_max_size = bd >> 4;
    if (block_max_size < 4) { return LXLZ4_ERROR_INCOMPATIBLE_DATA; }// invalid block maxsize
    frame->block_max_size_ = (lxlz4_block_size_e)(block_max_size - 4);
    LXLZ4_ASSERT(frame->block_max_size_ >= 0 && frame->block_max_size_ < LXLZ4_BLOCK_SIZE_END);
    // load content size if available
    if (frame->has_content_size_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 8, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
        frame->content_size_ = LXLZ4_INTERNAL_LOADU64(ip);
        ip += 8;
    }
    // load dictionary id if available
    if (frame->has_dictionary_id_)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 4, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
        frame->dictionary_id_ = LXLZ4_INTERNAL_LOADU32(ip);
        ip += 4;
    }
    // header checksum
    if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 1, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
    const uint8_t hc = *ip++;
    if (check_header_checksum)
    {
        const uint32_t computed_hc = lxlz4_xxhash32(fdp, (size_t)(ip - fdp - 1), 0);
        if (hc != ((computed_hc >> 8) & 0xff)) { return LXLZ4_ERROR_FRAME_CHECKSUM_MISMATCH; }
    }
    // accepted
    frame->header_size_ = (size_t)(ip - (const uint8_t*)src);
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API void lxlz4_frame_parse_init(lxlz4_parse_t* parse)
{
    if (!parse) { return; }
    parse->parse_endmark_block_ = LXLZ4_FALSE;
    // [internal]
    lxlz4_frame_init(&parse->frame_);
    lxlz4_block_init(&parse->block_);
    parse->src_ = NULL;
    parse->src_size_ = 0;
    parse->next_ = 0;
    parse->error_ = LXLZ4_ERROR_NONE;
    parse->endmark_detected_ = LXLZ4_FALSE;
    parse->got_content_checksum_ = LXLZ4_FALSE;
    parse->content_checksum_ = 0;
}

LXLZ4_API lxlz4_bool_t lxlz4_frame_parse_begin(lxlz4_parse_t* parse, const void* src, size_t src_size)
{
    if (!parse) { return LXLZ4_FALSE; }
    // extract frame
    parse->error_ = lxlz4_frame_extract(&parse->frame_, src, src_size);
    if (parse->error_ != LXLZ4_ERROR_NONE) { return LXLZ4_FALSE; }
    // setup parameters
    parse->src_ = src;
    parse->src_size_ = src_size;
    parse->next_ = parse->frame_.header_size_;
    parse->error_ = LXLZ4_ERROR_NONE;
    parse->endmark_detected_ = LXLZ4_FALSE;
    parse->got_content_checksum_ = LXLZ4_FALSE;
    parse->content_checksum_ = 0;
    return LXLZ4_TRUE;
}

LXLZ4_API const lxlz4_block_t* lxlz4_frame_parse_next(lxlz4_parse_t* parse)
{
    if (!parse) { return NULL; }
    // check errors
    if (parse->error_ != LXLZ4_ERROR_NONE) { return NULL; }
    if (parse->endmark_detected_) { return NULL; }
    // parse next block
    parse->error_ = lxlz4_block_extract(&parse->block_, (const uint8_t*)parse->src_ + parse->next_, parse->src_size_ - parse->next_, parse->frame_.has_block_checksum_);
    if (parse->error_ != LXLZ4_ERROR_NONE) { return NULL; }
    parse->next_ += parse->block_.next_block_offset_;
    // endmark
    if (parse->block_.category_ == LXLZ4_BLOCK_CATEGORY_ENDMARK)
    {
        parse->endmark_detected_ = LXLZ4_TRUE;
        // get content checksum
        if (parse->frame_.has_content_checksum_)
        {
            const uint8_t* ip = (const uint8_t*)parse->src_ + parse->next_;
            const uint8_t* eip = ip + parse->src_size_;
            if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 4, eip)) { parse->error_ = LXLZ4_ERROR_INSUFFICIENT_INPUT; return NULL; }
            parse->got_content_checksum_ = LXLZ4_TRUE;
            parse->content_checksum_ = LXLZ4_INTERNAL_LOADU32(ip);
            parse->next_ += 4;
        }
        // will parse endmark ?
        if (!parse->parse_endmark_block_) { return NULL; }
    }
    // accepted
    return &parse->block_;
}

LXLZ4_API void lxlz4_frame_parse_end(lxlz4_parse_t* parse)
{
    (void)parse;
}

LXLZ4_API lxlz4_error_e lxlz4_frame_parse_error(const lxlz4_parse_t* parse)
{
    if (!parse) { return LXLZ4_ERROR_GENERAL; }
    return parse->error_;
}

LXLZ4_API void lxlz4_block_init(lxlz4_block_t* block)
{
    if (!block) { return; }

    block->category_ = LXLZ4_BLOCK_CATEGORY_DATA;
    block->is_block_compressed_ = LXLZ4_FALSE;
    block->block_size_ = 0;
    block->block_data_ = NULL;
    block->block_checksum_ = 0;
    block->next_block_offset_ = 0;
}

LXLZ4_API lxlz4_error_e lxlz4_block_extract(lxlz4_block_t* block, const void* src, size_t src_size, lxlz4_bool_t has_block_checksum)
{
    const uint8_t* ip = (const uint8_t*)src;
    const uint8_t* eip = ip + src_size;
    lxlz4_block_t dummy_block;
    if (!block) { block = &dummy_block; }
    // block size
    if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 4, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
    block->block_size_ = LXLZ4_INTERNAL_LOADU32(ip);
    ip += 4;
    if (block->block_size_ == 0)
    {
        // endmark
        block->category_ = LXLZ4_BLOCK_CATEGORY_ENDMARK;
    }
    else
    {
        // data
        block->category_ = LXLZ4_BLOCK_CATEGORY_DATA;
    }
    // data pref
    block->is_block_compressed_ = LXLZ4_TOBOOL((block->block_size_ & 0x80000000U) == 0);
    block->block_size_ &= ~0x80000000U;
    // data ptr
    block->block_data_ = ip;
    ip += block->block_size_;
    if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 0, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
    // checksum
    if (has_block_checksum && block->category_ != LXLZ4_BLOCK_CATEGORY_ENDMARK)
    {
        if (LXLZ4_INTERNAL_OUTOFRANGE(ip, 4, eip)) { return LXLZ4_ERROR_INSUFFICIENT_INPUT; }
        block->block_checksum_ = LXLZ4_INTERNAL_LOADU32(ip);
        ip += 4;
    }
    else
    {
        block->block_checksum_ = 0;
    }
    // accepted
    block->next_block_offset_ = (size_t)(ip - (const uint8_t*)src);
    return LXLZ4_ERROR_NONE;
}

LXLZ4_API lxlz4_bool_t lxlz4_block_verify_checksum(const lxlz4_block_t* block)
{
    if (!block) { return LXLZ4_FALSE; }
    if (!block->block_data_) { return LXLZ4_FALSE; }
    const uint32_t checksum = lxlz4_xxhash32(block->block_data_, block->block_size_, 0);
    return LXLZ4_TOBOOL(checksum == block->block_checksum_);
}

#undef LXLZ4_INTERNAL_OUTOFRANGE

#undef LXLZ4_INTERNAL_LOADU16
#undef LXLZ4_INTERNAL_STOREU16
#undef LXLZ4_INTERNAL_LOADU32
#undef LXLZ4_INTERNAL_STOREU32
#undef LXLZ4_INTERNAL_LOADU64
#undef LXLZ4_INTERNAL_STOREU64

#endif // LXLZ4_IMPLEMENTATION_INCLUDED
#endif // LXLZ4_IMPLEMENTATION

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

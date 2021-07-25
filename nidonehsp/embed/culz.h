//-----------------------------------------------------------------------------
/*
    culz.h
      ulz compression algorithm implementation in C.

      ulz is an ultra-fast LZ77 data compression library.
      original ulz work is written and placed into public domain by Ilya Muravyov,
      see <https://github.com/encode84/ulz> for more information.
*/
//-----------------------------------------------------------------------------

#ifndef CULZ_HEADER_INCLUDED
#define CULZ_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    customization
//

// linkage
#ifndef CULZ_API
#ifdef CULZ_STATIC
#define CULZ_API    static
#else
#define CULZ_API
#endif // CULZ_STATIC
#endif // CULZ_API

// use unaligend memory access
//#define CULZ_UNALIGNED_MEMORY_ACCESS

// sliding window size
//#define CULZ_WINDOW_BITS (bits)

// hash table size
//#define CULZ_HASH_BITS (bits)

// memory api
#ifndef CULZ_NO_MEMORY_API
// malloc, free, realloc
#ifndef CULZ_MALLOC
#include <stdlib.h>
#define CULZ_MALLOC(size, user)        malloc(size)
#define CULZ_FREE(ptr, user)           free(ptr)
#define CULZ_REALLOC_SIZED(oldptr, newsize, oldsize, user)     realloc(oldptr, newsize)
#endif // CULZ_MALLOC
#endif // CULZ_NO_MEMORY_API

// memcpy
#ifndef CULZ_MEMCPY
#include <string.h>
#define CULZ_MEMCPY(dst, src, size)    memcpy(dst, src, size)
#endif // CULZ_MEMCPY

// inline keyword
#ifndef CULZ_INLINE
#define CULZ_INLINE inline
#endif // CULZ_INLINE

//-----------------------------------------------------------------------------
//
//    forward declaration
//
#include <stddef.h>
#include <stdint.h>

#define CULZ_EXCESS (16)

//
//    compression
//
#define CULZ_COMPRESS_LEVEL_MIN     (1)
#define CULZ_COMPRESS_LEVEL_MAX     (9)

CULZ_API int CulzHashTableWorkSize();
CULZ_API int CulzPrevWorkSize();

CULZ_API int CulzCompressBound(int in_len);

CULZ_API int CulzCompressFastNoAlloc(const uint8_t* in, int in_len, uint8_t* out, void* hash_table_work/*must be larger than CulzHashTableWorkSize()*/, void* prev_work/*must be larger than CulzPrevWorkSize()*/);
CULZ_API int CulzCompressNoAlloc(const uint8_t* in, int in_len, uint8_t* out, int level, void* hash_table_work/*must be larger than CulzHashTableWorkSize()*/, void* prev_work/*must be larger than CulzPrevWorkSize()*/);

#ifndef CULZ_NO_MEMORY_API
CULZ_API int CulzCompressFast(const uint8_t* in, int in_len, uint8_t* out, void* alloc_user);
CULZ_API int CulzCompress(const uint8_t* in, int in_len, uint8_t* out, int level, void* alloc_user);
#endif // CULZ_NO_MEMORY_API

//
//    decompression
//
CULZ_API int CulzDecompress(const uint8_t* in, int in_len, uint8_t* out, int out_len);

#endif // CULZ_HEADER_INCLUDED

//-----------------------------------------------------------------------------
//
//    implementation
//
#ifdef CULZ_IMPLEMENTATION
#ifndef CULZ_IMPLEMENTATION_INCLUDED
#define CULZ_IMPLEMENTATION_INCLUDED

//
//    compression
//
#ifndef CULZ_WINDOW_BITS
#define CULZ_WINDOW_BITS (17)
#endif // CULZ_WINDOW_BITS

#ifndef CULZ_HASH_BITS
#define CULZ_HASH_BITS (19)
#endif // CULZ_HASH_BITS

#define CULZ_WINDOW_SIZE (1 << CULZ_WINDOW_BITS)
#define CULZ_WINDOW_MASK (CULZ_WINDOW_SIZE - 1)

#define CULZ_MIN_MATCH (4)

#define CULZ_HASH_SIZE (1 << CULZ_HASH_BITS)
#define CULZ_NIL (-1)

#define CULZ_MIN(a, b) ((a) < (b) ? (a) : (b))
#define CULZ_MAX(a, b) ((a) > (b) ? (a) : (b))

#if defined(CULZ_UNALIGNED_MEMORY_ACCESS)
// fastest copy
static CULZ_INLINE uint16_t CulzUnalignedLoad16(const void* p)
{
    return *(const uint16_t*)(p);
}

static CULZ_INLINE uint32_t CulzUnalignedLoad32(const void* p)
{
    return *(const uint32_t*)(p);
}

static CULZ_INLINE void CulzUnalignedStore16(void* p, uint16_t x)
{
    *(uint16_t*)(p) = x;
}

static CULZ_INLINE void CulzUnalignedCopy64(void* d, const void* s)
{
    *(uint64_t*)(d) = *(const uint64_t*)(s);
}
#elif 0
// much slower impl than memcpy(latter one)
static CULZ_INLINE uint16_t CulzUnalignedLoad16(const void* p)
{
    const uint8_t* u = (const uint8_t*)p;
    return (u[0] << 8) + u[1];
}

static CULZ_INLINE uint32_t CulzUnalignedLoad32(const void* p)
{
    const uint8_t* u = (const uint8_t*)p;
    return (u[0] << 24) + (u[1] << 16) + (u[2] << 8) + u[3];
}

static CULZ_INLINE void CulzUnalignedStore16(void* p, uint16_t x)
{
    uint8_t* u = (uint8_t*)p;
    u[0] = (x >> 8) & 0xff;
    u[1] = x & 0xff;
}

static CULZ_INLINE void CulzUnalignedCopy64(void* d, const void* s)
{
    uint8_t* du = (uint8_t*)d;
    uint8_t* su = (uint8_t*)s;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
    *du++ = *su++;
}
#else
// generic
static CULZ_INLINE uint16_t CulzUnalignedLoad16(const void* p)
{
    uint16_t v;
    CULZ_MEMCPY(&v, p, 2);
    return v;
}

static CULZ_INLINE uint32_t CulzUnalignedLoad32(const void* p)
{
    uint32_t v;
    CULZ_MEMCPY(&v, p, 4);
    return v;
}

static CULZ_INLINE void CulzUnalignedStore16(void* p, uint16_t x)
{
    CULZ_MEMCPY(p, &x, 2);
}

static CULZ_INLINE void CulzUnalignedCopy64(void* d, const void* s)
{
    CULZ_MEMCPY(d, s, 8);
}
#endif

static CULZ_INLINE void CulzWildCopy(uint8_t* d, const uint8_t* s, int n)
{
    // may cause write out of boundary
    CulzUnalignedCopy64(d, s);

    for (int i = 8; i < n; i += 8)
    {
        CulzUnalignedCopy64(d + i, s + i);
    }
}

static CULZ_INLINE void CulzWildCopyWithCheck(uint8_t* d, const uint8_t* s, int n, int on)
{
    int nn = n;
    if (nn & 0x07) { nn = (nn + 8) & ~0x07; }
    if (nn <= on)
    {
        // can copy all segment
        CulzWildCopy(d, s, n);
    }
    else
    {
        // last part
        nn = on;
        if (nn & 0x07)
        {
            int i = 0;
            while (nn >= 8)
            {
                CulzUnalignedCopy64(d + i, s + i);
                i += 8;
                nn -= 8;
            }
            CULZ_MEMCPY(d + i, s + i, nn);
        }
        else
        {
            CulzWildCopy(d, s, nn);
        }
    }
}

static CULZ_INLINE uint32_t CulzHash32(const void* p)
{
    return (CulzUnalignedLoad32(p) * 0x9E3779B9) >> (32 - CULZ_HASH_BITS);
}

static CULZ_INLINE void CulzEncodeMod(uint8_t** pp, uint32_t x)
{
    uint8_t* p = *pp;
    while (x >= 128)
    {
        x -= 128;
        *p++ = 128 + (x & 127);
        x >>= 7;
    }
    *p++ = (uint8_t)x;
    *pp = p;
}

static CULZ_INLINE uint32_t CulzDecodeMod(const uint8_t** pp)
{
    const uint8_t* p = *pp;
    uint32_t x = 0;
    for (int i = 0; i <= 21; i += 7)
    {
        const uint32_t c = *p++;
        x += c << i;
        if (c < 128)
        {
            break;
        }
    }
    *pp = p;
    return x;
}

CULZ_API int CulzHashTableWorkSize()
{
    return CULZ_HASH_SIZE * sizeof(int);
}

CULZ_API int CulzPrevWorkSize()
{
    return CULZ_WINDOW_SIZE * sizeof(int);
}

// LZ77
CULZ_API int CulzCompressBound(int in_len)
{
    // NOTE that this is not theoretical upper bound, but practically almost all cases will fits (... hopefully).
    return in_len + in_len / 255 + 256;
}

CULZ_API int CulzCompressFastNoAlloc(const uint8_t* in, int in_len, uint8_t* out, void* hash_table_work, void* prev_work)
{
    int* hash_table = (int*)hash_table_work;
    int* prev = (int*)prev_work;

    if (!hash_table || !prev)
    {
        return -1;
    }

    for (int i = 0; i < CULZ_HASH_SIZE; ++i)
    {
        hash_table[i] = CULZ_NIL;
    }

    uint8_t* op = out;
    int anchor = 0;

    int p = 0;
    while (p < in_len)
    {
        int best_len = 0;
        int dist = 0;

        const int max_match = in_len - p;
        if (max_match >= CULZ_MIN_MATCH)
        {
            const int limit = CULZ_MAX(p - CULZ_WINDOW_SIZE, CULZ_NIL);

            const uint32_t h = CulzHash32(&in[p]);
            int s = hash_table[h];
            hash_table[h] = p;

            if (s > limit && CulzUnalignedLoad32(&in[s]) == CulzUnalignedLoad32(&in[p]))
            {
                int len = CULZ_MIN_MATCH;
                while (len < max_match && in[s + len] == in[p + len])
                {
                    ++len;
                }

                best_len = len;
                dist = p - s;
            }
        }

        if (best_len == CULZ_MIN_MATCH && (p - anchor) >= (7 + 128))
        {
            best_len = 0;
        }

        if (best_len >= CULZ_MIN_MATCH)
        {
            const int len = best_len - CULZ_MIN_MATCH;
            const int token = ((dist >> 12) & 16) + CULZ_MIN(len, 15);

            if (anchor != p)
            {
                const int run = p - anchor;
                if (run >= 7)
                {
                    *op++ = (uint8_t)((7 << 5) + token);
                    CulzEncodeMod(&op, run - 7);
                }
                else
                {
                    *op++ = (uint8_t)((run << 5) + token);
                }

                CulzWildCopy(op, &in[anchor], run);
                op += run;
            }
            else
            {
                *op++ = (uint8_t)token;
            }

            if (len >= 15)
            {
                CulzEncodeMod(&op, len - 15);
            }

            CulzUnalignedStore16(op, (uint16_t)dist);
            op += 2;

            anchor = p + best_len;
            ++p;
            hash_table[CulzHash32(&in[p])] = p; ++p;
            hash_table[CulzHash32(&in[p])] = p; ++p;
            hash_table[CulzHash32(&in[p])] = p; ++p;
            p = anchor;
        }
        else
        {
            ++p;
        }
    }

    if (anchor != p)
    {
        const int run = p - anchor;
        if (run >= 7)
        {
            *op++ = 7 << 5;
            CulzEncodeMod(&op, run - 7);
        }
        else
        {
            *op++ = (uint8_t)(run << 5);
        }

        CulzWildCopy(op, &in[anchor], run);
        op += run;
    }

    return (int)(op - out);// can be int64 for 64 bit data model environment(LLP64)
}

CULZ_API int CulzCompressNoAlloc(const uint8_t* in, int in_len, uint8_t* out, int level, void* hash_table_work, void* prev_work)
{
    int* hash_table = (int*)hash_table_work;
    int* prev = (int*)prev_work;

    if (!hash_table || !prev)
    {
        return -1;
    }

    if (level < CULZ_COMPRESS_LEVEL_MIN || level > CULZ_COMPRESS_LEVEL_MAX)
    {
        return -1;
    }

    const int max_chain = (level < CULZ_COMPRESS_LEVEL_MAX) ? (1 << level) : (1 << 13);

    for (int i = 0; i < CULZ_HASH_SIZE; ++i)
    {
        hash_table[i] = CULZ_NIL;
    }

    uint8_t* op = out;
    int anchor = 0;

    int p = 0;
    while (p < in_len)
    {
        int best_len = 0;
        int dist = 0;

        const int max_match = in_len - p;
        if (max_match >= CULZ_MIN_MATCH)
        {
            const int limit = CULZ_MAX(p - CULZ_WINDOW_SIZE, CULZ_NIL);
            int chain_len = max_chain;

            int s = hash_table[CulzHash32(&in[p])];
            while (s > limit)
            {
                if (in[s + best_len] == in[p + best_len]
                    && CulzUnalignedLoad32(&in[s]) == CulzUnalignedLoad32(&in[p]))
                {
                    int len = CULZ_MIN_MATCH;
                    while (len < max_match && in[s + len] == in[p + len])
                    {
                        ++len;
                    }

                    if (len > best_len)
                    {
                        best_len = len;
                        dist = p - s;

                        if (len == max_match)
                        {
                            break;
                        }
                    }
                }

                if (--chain_len == 0)
                {
                    break;
                }

                s = prev[s & CULZ_WINDOW_MASK];
            }
        }

        if (best_len == CULZ_MIN_MATCH && (p - anchor) >= (7 + 128))
        {
            best_len = 0;
        }

        if (level >= 5 && best_len >= CULZ_MIN_MATCH && best_len < max_match
            && (p - anchor) != 6)
        {
            const int x = p + 1;
            const int target_len = best_len + 1;

            const int limit = CULZ_MAX(x - CULZ_WINDOW_SIZE, CULZ_NIL);
            int chain_len = max_chain;

            int s = hash_table[CulzHash32(&in[x])];
            while (s > limit)
            {
                if (in[s + best_len] == in[x + best_len]
                    && CulzUnalignedLoad32(&in[s]) == CulzUnalignedLoad32(&in[x]))
                {
                    int len = CULZ_MIN_MATCH;
                    while (len < target_len && in[s + len] == in[x + len])
                    {
                        ++len;
                    }

                    if (len == target_len)
                    {
                        best_len = 0;
                        break;
                    }
                }

                if (--chain_len == 0)
                {
                    break;
                }

                s = prev[s & CULZ_WINDOW_MASK];
            }
        }

        if (best_len >= CULZ_MIN_MATCH)
        {
            const int len = best_len-CULZ_MIN_MATCH;
            const int token = ((dist >> 12) & 16) + CULZ_MIN(len, 15);

            if (anchor != p)
            {
                const int run = p - anchor;
                if (run >= 7)
                {
                    *op++ = (uint8_t)((7 << 5) + token);
                    CulzEncodeMod(&op, run- 7);
                }
                else
                {
                    *op++ = (uint8_t)((run << 5) + token);
                }

                CulzWildCopy(op, &in[anchor], run);
                op += run;
            }
            else
            {
                *op++ = (uint8_t)token;
            }

            if (len >= 15)
            {
                CulzEncodeMod(&op, len - 15);
            }

            CulzUnalignedStore16(op, (uint16_t)dist);
            op += 2;

            while (best_len-- != 0)
            {
                const uint32_t h = CulzHash32(&in[p]);
                prev[p & CULZ_WINDOW_MASK] = hash_table[h];
                hash_table[h] = p++;
            }
            anchor = p;
        }
        else
        {
            const uint32_t h = CulzHash32(&in[p]);
            prev[p & CULZ_WINDOW_MASK] = hash_table[h];
            hash_table[h] = p++;
        }
    }

    if (anchor != p)
    {
        const int run = p - anchor;
        if (run >= 7)
        {
            *op++ = 7 << 5;
            CulzEncodeMod(&op, run - 7);
        }
        else
        {
            *op++ = (uint8_t)(run << 5);
        }

        CulzWildCopy(op, &in[anchor], run);
        op += run;
    }

    return (int)(op - out);
}

#ifndef CULZ_NO_MEMORY_API
CULZ_API int CulzCompressFast(const uint8_t* in, int in_len, uint8_t* out, void* alloc_user)
{
    (void)(alloc_user);// can be unreferenced variable
    void* hash_table_work = CULZ_MALLOC(CulzHashTableWorkSize(), alloc_user);
    void* prev_work = CULZ_MALLOC(CulzPrevWorkSize(), alloc_user);
    const int res = CulzCompressFastNoAlloc(in, in_len, out, hash_table_work, prev_work);
    if (hash_table_work) { CULZ_FREE(hash_table_work, alloc_user); }
    if (prev_work) { CULZ_FREE(prev_work, alloc_user); }
    return res;
}

CULZ_API int CulzCompress(const uint8_t* in, int in_len, uint8_t* out, int level, void* alloc_user)
{
    (void)(alloc_user);// can be unreferenced variable
    void* hash_table_work = CULZ_MALLOC(CulzHashTableWorkSize(), alloc_user);
    void* prev_work = CULZ_MALLOC(CulzPrevWorkSize(), alloc_user);
    const int res = CulzCompressNoAlloc(in, in_len, out, level, hash_table_work, prev_work);
    if (hash_table_work) { CULZ_FREE(hash_table_work, alloc_user); }
    if (prev_work) { CULZ_FREE(prev_work, alloc_user); }
    return res;
}
#endif // CULZ_NO_MEMORY_API

//
//    decompression
//
CULZ_API int CulzDecompress(const uint8_t* in, int in_len, uint8_t* out, int out_len)
{
    uint8_t* op = out;
    const uint8_t* ip = in;

    const uint8_t* ip_end = ip + in_len;
    const uint8_t* op_end = op + out_len;

    while (ip < ip_end)
    {
        const int token = *ip++;

        if (token >= 32)
        {
            int run = token >> 5;
            if (run == 7)
            {
                run += CulzDecodeMod(&ip);
            }
            if ((op_end - op) < run || (ip_end - ip) < run) // Overrun check
            {
                return -1;
            }

            CulzWildCopyWithCheck(op, ip, run, (int)(op_end - op));
            op += run;
            ip += run;
            if (ip >= ip_end)
            {
                break;
            }
        }

        int len = (token & 15) + CULZ_MIN_MATCH;
        if (len == (15 + CULZ_MIN_MATCH))
        {
            len += CulzDecodeMod(&ip);
        }
        if ((op_end - op) < len) // Overrun check
        {
            return -1;
        }

        const int dist = ((token & 16) << 12) + CulzUnalignedLoad16(ip);
        ip += 2;
        uint8_t* cp = op - dist;
        if ((op - out) < dist) // Range check
        {
            return -1;
        }

        if (dist >= 8)
        {
            CulzWildCopyWithCheck(op, cp, len, (int)(op_end - op));
            op += len;
        }
        else
        {
            *op++ = *cp++;
            *op++ = *cp++;
            *op++ = *cp++;
            *op++ = *cp++;
            while (len-- != 4)
            {
                *op++ = *cp++;
            }
        }
    }

    return (int)((ip == ip_end) ? op - out : -1);
}

#endif // CULZ_IMPLEMENTATION_INCLUDED
#endif // CULZ_IMPLEMENTATION

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/

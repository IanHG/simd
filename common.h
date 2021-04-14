#pragma once
#ifndef SIMD_COMMON_H_INCLUDED
#define SIMD_COMMON_H_INCLUDED

#include <immintrin.h>

#if defined(INTEL_IACA)
#include <iacaMarks.h>
#endif /* INTEL_IACA */

#if !defined(IACA_START)
   #define IACA_START
#endif /* IACA_START */
#if !defined(IACA_END)
   #define IACA_END
#endif /* IACA_END */

#include <assert.h>

#include "typedef.h"
#include "simd_switch.h"

Simd_inline void assert_aligned(const void* const ptr, int32 alignment)
{
   assert(((int64)ptr & (alignment - 1)) == 0);
}

#define CACHELINE 64
#define simd_nprefetch(a, b) CACHELINE / a

#endif /* SIMD_COMMON_H_INCLUDED */

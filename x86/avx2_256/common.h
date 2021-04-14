#pragma once
#ifndef X86_AVX2_256_COMMON_H_INCLUDED
#define X86_AVX2_256_COMMON_H_INCLUDED

#include "../../common.h"
#include "../../typedef.h"

#if defined(SIMD_FMA)
   #define avx2_256_fmadd_pd(a, b, c) \
      _mm256_fmadd_pd(a, b, c)
#else
   #define avx2_256_fmadd_pd(a, b, c) \
      _mm256_add_pd(_mm256_mul_pd(a, b), c)
#endif /* SIMD_FMA */

#endif /* X86_AVX2_256_COMMON_H_INCLUDED */

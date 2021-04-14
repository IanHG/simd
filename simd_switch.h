#pragma once
#ifndef SIMD_SWITCH_H_INCLUDED
#define SIMD_SWITCH_H_INCLUDED

/**
 * 
 **/
#if defined(__FMA__)
   #if defined(SIMD_MESSAGE)
      #pragma message "fma"
   #endif /* SIMD_MESSAGE */
   #define SIMD_FMA
#endif /* __FMA __ */

#if defined(__AVX512F__)
   #if defined(SIMD_MESSAGE)
      #pragma message "avx512"
   #endif /* SIMD_MESSAGE */
   #include "x86/avx_512/avx_512.h"
#elif defined(__AVX2__)
   #if defined(SIMD_MESSAGE)
      #pragma message "avx2_256"
   #endif /* SIMD_MESSAGE */
   #include "x86/avx2_256/avx2_256.h"
#elif defined(__SSE4_1__)
   #if defined(SIMD_MESSAGE)
      #pragma message "sse4.1"
   #endif /* SIMD_MESSAGE */
   #include "x86/sse4_1/sse4_1.h"
#else
   #if defined(SIMD_MESSAGE)
      #pragma message "generic"
   #endif /* SIMD_MESSAGE */
   #include "generic/generic.h"
#endif

#endif /* SIMD_SWITCH_H_INCLUDED */

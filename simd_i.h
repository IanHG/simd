#pragma once
#ifndef SIMD_I_H_INCLUDED
#define SIMD_I_H_INCLUDED

#include "common.h"

//#include "simd_d.h"

Simd_inline void zero_ptr_float64(float64* const Simd_restrict a, int n)
{
   #if defined(ALIGNED_ALLOC) && !defined(GENERIC)
   #if defined(SIMD_DEBUG)
   assert_aligned(a, 32);
   #endif /* SIMD_DEBUG */
   CONCAT(SIMD_ISA, _zero_ptr_float64_align32) (a, n);
   #else
   CONCAT(SIMD_ISA, _zero_ptr_float64) (a, n);
   #endif 
}

Simd_inline void set_value_ptr_float64(float64* const Simd_restrict a, float64 value, int n)
{
   #if defined(ALIGNED_ALLOC) && !defined(GENERIC)
   #if defined(SIMD_DEBUG)
   assert_aligned(a, 32);
   #endif /* SIMD_DEBUG */
   CONCAT(SIMD_ISA, _set_value_ptr_float64_align32) (a, value, n);
   #else
   CONCAT(SIMD_ISA, _set_value_ptr_float64) (a, value, n);
   #endif 
}

Simd_inline void axpy_float64(float64* const Simd_restrict y, const float64* const x, float64 a, int n)
{
   #if defined(ALIGNED_ALLOC) && !defined(GENERIC)
   #if defined(SIMD_DEBUG)
   assert_aligned(y, 32);
   assert_aligned(x, 32);
   #endif /* SIMD_DEBUG */
   CONCAT(SIMD_ISA, _axpy_float64_align32) (y, x, a, n);
   #else
   CONCAT(SIMD_ISA, _axpy_float64) (y, x, a, n);
   #endif 
}

Simd_inline float64 pdot_float64(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int n)
{
   #if defined(ALIGNED_ALLOC) && !defined(GENERIC)
   #if defined(SIMD_DEBUG)
   assert_aligned(a, 32);
   assert_aligned(b, 32);
   #endif /* SIMD_DEBUG */
   return CONCAT(SIMD_ISA, _pdot_float64_align32_accu2) (a, b, n);
   //return CONCAT(SIMD_ISA, _pdot_float64_align32) (a, b, n);
   #else
   return CONCAT(SIMD_ISA, _pdot_float64) (a, b, n);
   #endif 
}

#endif /* SIMD_I_H_INCLUDED */

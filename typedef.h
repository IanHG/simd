#pragma once
#ifndef SIMD_TYPEDEF_H_INCLUDED
#define SIMD_TYPEDEF_H_INCLUDED

#define Simd_restrict          __restrict
//#define Simd_restrict         
//#define Simd_attribute_aligned __attribute__((aligned(CACHELINE)))
#define Simd_attribute_aligned 
#define Simd_inline inline

#ifdef __cplusplus
#define Simd_static_cast(a, b)  static_cast<a>(b)
#else
#define Simd_static_cast(a, b)  (a) b
#endif /* __cplusplus */

typedef float  float32;
typedef double float64;

typedef int    int32;
typedef long   int64;

#endif /* SIMD_TYPEDEF_H_INCLUDED */

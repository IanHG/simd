#pragma once
#ifndef X86_AVX2_256_H_INCLUDED
#define X86_AVX2_256_H_INCLUDED

#ifdef SIMD_ISA
#undef SIMD_ISA
#endif /* SIMD_ISA */

#define X86_AVX2_256
#define SIMD_ISA       avx2_256

#include "../../typedef.h"
#include "../../simd_d.h"

#endif /* X86_AVX2_256_H_INCLUDED */

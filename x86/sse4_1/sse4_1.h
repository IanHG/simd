#pragma once
#ifndef X86_SSE4_1_H_INCLUDED
#define X86_SSE4_1_H_INCLUDED

#ifdef SIMD_ISA
#undef SIMD_ISA
#endif /* SIMD_ISA */

#define SIMD_ISA sse4_1
#define X86_SSE4_1

#include "../../typedef.h"
#include "../../simd_d.h"

#endif /* X86_SSE4_1_H_INCLUDED */

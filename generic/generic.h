#pragma once
#ifndef SIMD_GENERIC_H_INCLUDED
#define SIMD_GENERIC_H_INCLUDED

#ifdef SIMD_ISA
#undef SIMD_ISA
#endif /* SIMD_ISA */

#ifndef GENERIC
#define GENERIC
#endif /* GENERIC */

#define SIMD_ISA generic

#include "../typedef.h"
#include "../simd_d.h"

#endif /* SIMD_GENERIC_H_INCLUDED */

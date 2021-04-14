//#pragma once
//#ifndef SIMD_D_H_INCLUDED
//#define SIMD_D_H_INCLUDED

//#include "common.h"

#define CONCAT_IMPL(a, b) \
   a ## b
#define CONCAT(a, b) \
   CONCAT_IMPL(a, b)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void    CONCAT(SIMD_ISA, _zero_ptr_float64             ) (float64* const Simd_restrict a, int n);
void    CONCAT(SIMD_ISA, _zero_ptr_float64_align32     ) (float64* const Simd_restrict a, int n);
void    CONCAT(SIMD_ISA, _set_value_ptr_float64        ) (float64* const Simd_restrict a, float64 value, int n);
void    CONCAT(SIMD_ISA, _set_value_ptr_float64_align32) (float64* const Simd_restrict a, float64 value, int n);
void    CONCAT(SIMD_ISA, _axpy_float64                 ) (float64* const Simd_restrict y, const float64* const Simd_restrict x, float64 a, int n);
void    CONCAT(SIMD_ISA, _axpy_float64_align32         ) (float64* const Simd_restrict y, const float64* const Simd_restrict x, float64 a, int n);
float64 CONCAT(SIMD_ISA, _pdot_float64                 ) (const float64* const Simd_restrict a, const float64* const Simd_restrict b, int n);
float64 CONCAT(SIMD_ISA, _pdot_float64_align32         ) (const float64* const Simd_restrict a, const float64* const Simd_restrict b, int n);
float64 CONCAT(SIMD_ISA, _pdot_float64_align32_accu2   ) (const float64* const Simd_restrict a, const float64* const Simd_restrict b, int n);
float64 CONCAT(SIMD_ISA, _pdot_float64_align32_accu4   ) (const float64* const Simd_restrict a, const float64* const Simd_restrict b, int n);

#ifdef __cplusplus
}
#endif /* __cplusplus */

//#endif /* SIMD_D_H_INCLUDED */

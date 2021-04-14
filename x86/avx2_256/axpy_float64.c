#include "common.h"

#if defined (X86_AVX2_256) 

/**
 * y <- ax + y
 **/

/**
 * Un-aligned
 **/
void avx2_256_axpy_float64(float64* const Simd_restrict y, const float64* const Simd_restrict x, float64 a, int32 n)
{
   __m256d a4 = _mm256_set1_pd(a);

   int32 i;
   const int32 last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      __m256d y4 = _mm256_loadu_pd(y + i);
      __m256d x4 = _mm256_loadu_pd(x + i);
      y4 = _mm256_add_pd(_mm256_mul_pd(a4, x4), y4);
      _mm256_storeu_pd(y + i, y4);
   }

	for(; i < n; ++i)
   {
      y[i] = a * x[i] + y[i];
   }
}

/**
 * Aligned
 **/
void avx2_256_axpy_float64_align32(float64* const Simd_restrict y, const float64* const Simd_restrict x, float64 a, int32 n)
{
   __m256d a4 = _mm256_set1_pd(a);

   int32 i;
   const int32 last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      __m256d y4 = _mm256_load_pd(y + i);
      __m256d x4 = _mm256_load_pd(x + i);
      y4 = _mm256_add_pd(_mm256_mul_pd(a4, x4), y4);
      _mm256_store_pd(y + i, y4);
   }

	for(; i < n; ++i)
   {
      y[i] = a * x[i] + y[i];
   }
}

#endif /* X86_AVX2_256 */

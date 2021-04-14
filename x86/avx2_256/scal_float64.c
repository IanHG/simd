#include "common.h"

#if defined(X86_AVX2_256)

/**
 * y <- ay
 **/
void avx2_256_scal_float64(float64* const Simd_restrict y, float64 a, int n)
{
   __m256d a4 = _mm256_set1_pd(a);

   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      __m256d y4 = _mm256_loadu_pd(y + i);
      y4 = _mm256_mul_pd(a4, y4);
      _mm256_storeu_pd(y + i, y4);
   }

	for(; i < n; ++i)
   {
      y[i] = a * y[i];
   }
}

void avx2_256_scal_float64_align32(float64* const Simd_restrict y, float64 a, int n)
{
   __m256d a4 = _mm256_set1_pd(a);

   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      __m256d y4 = _mm256_load_pd(y + i);
      y4 = _mm256_mul_pd(a4, y4);
      _mm256_store_pd(y + i, y4);
   }

	for(; i < n; ++i)
   {
      y[i] = a * y[i];
   }
}

#endif /* X86_AVX2_256 */

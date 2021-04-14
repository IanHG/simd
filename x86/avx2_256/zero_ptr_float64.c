#include "common.h"

#if defined (X86_AVX2_256) 

void avx2_256_set_value_ptr_float64(float64* const Simd_restrict a, float64 value, int n)
{
   __m256d value4 = _mm256_set1_pd(value);
   
   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      _mm256_storeu_pd(a + i, value4);
   }

	for(; i < n; ++i)
   {
      a[i] = Simd_static_cast(float64, value);
   }
}

void avx2_256_set_value_ptr_float64_align32(float64* const Simd_restrict a, float64 value, int n)
{
   __m256d value4 = _mm256_set1_pd(value);
   
   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      _mm256_store_pd(a + i, value4);
   }

	for(; i < n; ++i)
   {
      a[i] = value;
   }
}

void avx2_256_zero_ptr_float64(float64* const Simd_restrict a, int n) 
{
   __m256d zero4 = _mm256_setzero_pd();
   
   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      _mm256_storeu_pd(a + i, zero4);
   }

	for(; i < n; ++i)
   {
      a[i] = Simd_static_cast(float64, 0.0);
   }
}

void avx2_256_zero_ptr_float64_align32(float64* const Simd_restrict a, int n) 
{
   __m256d zero4 = _mm256_setzero_pd();
   
   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      _mm256_store_pd(a + i, zero4);
   }

	for(; i < n; ++i)
   {
      a[i] = Simd_static_cast(float64, 0.0);
   }
}

#endif /* X86_AVX2_256 */

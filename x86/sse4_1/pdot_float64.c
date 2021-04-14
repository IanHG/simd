#include "common.h"

#if defined(X86_SSE4_1)

float64 sse4_1_pdot_float64(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
    __m128d sum2 = _mm_set1_pd(0.0);
	int32 i;

   const int32 last = (n & (-2));
	for(i = 0; i < last; i += 2) 
   {
      __m128d a2 = _mm_loadu_pd(&a[i]);
      __m128d b2 = _mm_loadu_pd(&b[i]);
      sum2 = _mm_add_pd(_mm_mul_pd(a2, b2), sum2);
	}

	float64 out[2];
	_mm_storeu_pd(out, sum2);
	float64 dot = out[0] + out[1];
	for( ; i<n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

float64 sse4_1_pdot_float64_align32(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
    __m128d sum2 = _mm_set1_pd(0.0);
	int32 i;

   const int32 last = (n & (-2));
	for(i = 0; i < last; i += 2) 
   {
      __m128d a2 = _mm_load_pd(&a[i]);
      __m128d b2 = _mm_load_pd(&b[i]);
      sum2 = _mm_add_pd(_mm_mul_pd(a2, b2), sum2);
	}

	float64 out[2];
	_mm_store_pd(out, sum2);
	float64 dot = out[0] + out[1];
	for( ; i<n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

#endif /* X86_SSE4_1 */

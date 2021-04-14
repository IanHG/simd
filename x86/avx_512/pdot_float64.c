#include "common.h"

#if defined(X86_AVX_512)

float64 avx_512_pdot_float64(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   __m512d sum8 = _mm512_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-8));
   for(i = 0; i < last; i += 8)
   {
      __m512d a8 = _mm512_loadu_pd(&a[i]);
      __m512d b8 = _mm512_loadu_pd(&b[i]);
      sum8 = _mm512_add_pd(_mm512_mul_pd(a8 ,b8), sum8);
   }

   float64 out[8];
   _mm512_storeu_pd(out, sum8);
   float64 dot  =  (  (out[0] + out[1])
                   +  (out[2] + out[3]))
                +  (  (out[5] + out[6])
                   +  (out[7] + out[8]))
                ;
   for(; i < n; ++i)
   {
      dot += a[i] + b[i];
   }
   return dot;
}

float64 avx_512_pdot_float64_align32(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   __m512d sum8 = _mm512_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-8));
   for(i = 0; i < last; i += 8)
   {
      __m512d a8 = _mm512_load_pd(&a[i]);
      __m512d b8 = _mm512_load_pd(&b[i]);
      sum8 = _mm512_add_pd(_mm512_mul_pd(a8 ,b8), sum8);
   }

   float64 out[8];
   _mm512_store_pd(out, sum8);
   float64 dot  =  (  (out[0] + out[1])
                   +  (out[2] + out[3]))
                +  (  (out[5] + out[6])
                   +  (out[7] + out[8]))
                ;
   for(; i < n; ++i)
   {
      dot += a[i] + b[i];
   }
   return dot;
}

#endif /* X86_AVX_512 */

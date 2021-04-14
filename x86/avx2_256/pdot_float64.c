#include "common.h"

#if defined (X86_AVX2_256)

float64 avx2_256_pdot_float64(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   #define avx2_256_pdot_float64_prefetch 1024

   __m256d sum4 = _mm256_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      __m256d a4 = _mm256_loadu_pd(a + i);
      __m256d b4 = _mm256_loadu_pd(b + i);
      sum4 = avx2_256_fmadd_pd(a4, b4, sum4);
      
      #if defined(SIMD_SOFTWARE_PREFETCH)
      if(i % 8 == 0)
      {
         _mm_prefetch(a + i + avx2_256_pdot_float64_prefetch, _MM_HINT_T0);
         _mm_prefetch(b + i + avx2_256_pdot_float64_prefetch, _MM_HINT_T0);
      }
      #endif /* SIMD_SOFTWARE_PREFETCH */
   }

   float64 out[4];
   _mm256_storeu_pd(out, sum4);
   float64 dot  =  (out[0] + out[1]) 
                +  (out[2] + out[3]);
	for(; i < n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

float64 avx2_256_pdot_float64_align32(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   #define avx2_256_pdot_float64_align32_prefetch 1024

   __m256d sum4 = _mm256_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      //IACA_START
      __m256d a4 = _mm256_load_pd(a + i);
      __m256d b4 = _mm256_load_pd(b + i);
      sum4 = avx2_256_fmadd_pd(a4, b4, sum4);
      
      #if defined(SIMD_SOFTWARE_PREFETCH)
      if(i % 8 == 0)
      {
         _mm_prefetch(a + i + avx2_256_pdot_float64_align32_prefetch, _MM_HINT_T0);
         _mm_prefetch(b + i + avx2_256_pdot_float64_align32_prefetch, _MM_HINT_T0);
      }
      #endif /* SIMD_SOFTWARE_PREFETCH */
      //IACA_END
   }

   float64 out[4];
   _mm256_store_pd(out, sum4);
   float64 dot  =  (out[0] + out[1]) 
                +  (out[2] + out[3]);
	for(; i < n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

float64 avx2_256_pdot_float64_align32_accu2(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   //const int32 nprefetch = simd_nprefetch(sizeof(float64), 8);
   #define avx2_256_pdot_float64_align32_accu2_prefetch 1024

   __m256d sum4_1 = _mm256_set1_pd(0.0);
   __m256d sum4_2 = _mm256_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-8));
   for(i = 0; i < last; i += 8)
   {
      //IACA_START

      __m256d a4_1 = _mm256_load_pd(a + i);
      __m256d b4_1 = _mm256_load_pd(b + i);
      __m256d a4_2 = _mm256_load_pd(a + i + 4);
      __m256d b4_2 = _mm256_load_pd(b + i + 4);
      
      sum4_1 = avx2_256_fmadd_pd(a4_1, b4_1, sum4_1);
      sum4_2 = avx2_256_fmadd_pd(a4_2, b4_2, sum4_2);

      #if defined(SIMD_SOFTWARE_PREFETCH)
      _mm_prefetch(a + i + avx2_256_pdot_float64_align32_accu2_prefetch, _MM_HINT_T0);
      _mm_prefetch(b + i + avx2_256_pdot_float64_align32_accu2_prefetch, _MM_HINT_T0);
      #endif /* SIMD_SOFTWARE_PREFETCH */
      
      //IACA_END
   }

   float64 out_1[4];
   _mm256_store_pd(out_1, sum4_1);
   float64 out_2[4];
   _mm256_store_pd(out_2, sum4_2);
   float64 dot  =  (out_1[0] + out_1[1]) 
               +  (out_1[2] + out_1[3]);
   dot  +=  (out_2[0] + out_2[1]) 
         +  (out_2[2] + out_2[3]);
	for(; i < n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

float64 avx2_256_pdot_float64_align32_accu4(const float64* const Simd_restrict a, const float64* const Simd_restrict b, int32 n) 
{
   #define avx2_256_pdot_float64_align32_accu4_prefetch 256

   __m256d sum4_1 = _mm256_set1_pd(0.0);
   __m256d sum4_2 = _mm256_set1_pd(0.0);
   __m256d sum4_3 = _mm256_set1_pd(0.0);
   __m256d sum4_4 = _mm256_set1_pd(0.0);
   
   int32 i;
   const int32 last = (n & (-16));
   for(i = 0; i < last; i += 16)
   {
      //IACA_START
      
      __m256d a4_1 = _mm256_load_pd(a + i);
      __m256d b4_1 = _mm256_load_pd(b + i);
      __m256d a4_2 = _mm256_load_pd(a + i + 4);
      __m256d b4_2 = _mm256_load_pd(b + i + 4);
      __m256d a4_3 = _mm256_load_pd(a + i + 8);
      __m256d b4_3 = _mm256_load_pd(b + i + 8);
      __m256d a4_4 = _mm256_load_pd(a + i + 12);
      __m256d b4_4 = _mm256_load_pd(b + i + 12);

      sum4_1 = avx2_256_fmadd_pd(a4_1, b4_1, sum4_1);
      sum4_2 = avx2_256_fmadd_pd(a4_2, b4_2, sum4_2);
      sum4_3 = avx2_256_fmadd_pd(a4_3, b4_3, sum4_3);
      sum4_4 = avx2_256_fmadd_pd(a4_4, b4_4, sum4_4);

      #if defined(SIMD_SOFTWARE_PREFETCH)
      _mm_prefetch(a + i + avx2_256_pdot_float64_align32_accu4_prefetch    , _MM_HINT_T0);
      _mm_prefetch(b + i + avx2_256_pdot_float64_align32_accu4_prefetch    , _MM_HINT_T0);
      _mm_prefetch(a + i + avx2_256_pdot_float64_align32_accu4_prefetch + 8, _MM_HINT_T0);
      _mm_prefetch(b + i + avx2_256_pdot_float64_align32_accu4_prefetch + 8, _MM_HINT_T0);
      #endif /* SIMD_SOFTWARE_PREFETCH */

      //IACA_END
   }

   float64 out_1[4];
   _mm256_store_pd(out_1, sum4_1);
   float64 out_2[4];
   _mm256_store_pd(out_2, sum4_2);
   float64 out_3[4];
   _mm256_store_pd(out_3, sum4_3);
   float64 out_4[4];
   _mm256_store_pd(out_4, sum4_4);
   float64 dot  =  (out_1[0] + out_1[1]) 
                +  (out_1[2] + out_1[3]);
   dot +=  (out_2[0] + out_2[1]) 
        +  (out_2[2] + out_2[3]);
   dot +=  (out_3[0] + out_3[1]) 
        +  (out_3[2] + out_3[3]);
   dot +=  (out_4[0] + out_4[1]) 
        +  (out_4[2] + out_4[3]);
	for(; i < n; ++i)
   {
      dot += a[i] * b[i]; 
   }
	return dot;
}

#endif /* X86_AVX2_256 */

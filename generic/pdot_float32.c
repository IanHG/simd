#include "common.h"

#if defined (GENERIC)

float32 generic_pdot_float32_no_unroll(const float32* const Simd_restrict a, const float32* const Simd_restrict b, int n)
{
   float32 result = Simd_static_cast(float32, 0.0);

   for(int i = 0; i < n; ++i)
   {
      result += a[i] * b[i];
   }
   
   return result;
}

float32 generic_pdot_float32_unroll2(const float32* const Simd_restrict a, const float32* const Simd_restrict b, int n)
{
   float32 result_array[2] Simd_attribute_aligned = 
      {  Simd_static_cast(float32, 0.0)
      ,  Simd_static_cast(float32, 0.0)
      };

   int i;
   const int last = (n & (-2));
   for(i = 0; i < last; i += 2)
   {
      result_array[0] += a[i + 0] * b[i + 0];
      result_array[1] += a[i + 1] * b[i + 1];
   }
	for(; i < n; ++i)
   {
      result_array[0] += a[i] * b[i]; 
   }

   float32 result = result_array[0] + result_array[1];

   return result;
}

float32 generic_pdot_float32_unroll4(const float32* const Simd_restrict a, const float32* const Simd_restrict b, int n)
{
   float32 result_array[4] Simd_attribute_aligned = 
      {  Simd_static_cast(float32, 0.0)
      ,  Simd_static_cast(float32, 0.0)
      ,  Simd_static_cast(float32, 0.0)
      ,  Simd_static_cast(float32, 0.0)
      };

   int i;
   const int last = (n & (-4));
   for(i = 0; i < last; i += 4)
   {
      result_array[0] += a[i + 0] * b[i + 0];
      result_array[1] += a[i + 1] * b[i + 1];
      result_array[2] += a[i + 2] * b[i + 2];
      result_array[3] += a[i + 3] * b[i + 3];
   }
   for(; i < n; i++)
   {
      result_array[0] += a[i] * b[i]; 
   }

   float32 result = (result_array[0] + result_array[1]) 
                  + (result_array[2] + result_array[3]);

   return result;
}

float32 generic_pdot_float32(const float32* const Simd_restrict a, const float32* const Simd_restrict b, int n)
{
   return generic_pdot_float32_unroll4(a, b, n);
}

#endif /* GENERIC */

#include "common.h"

#if defined(GENERIC)

void generic_set_value_ptr_float64(float64* const Simd_restrict a, float64 value, int n)
{
   for(int i = 0; i < n; ++i)
   {
      a[i] = value;
   }
}

void generic_zero_ptr_float64(float64* const Simd_restrict a, int n) 
{
   generic_set_value_ptr_float64(a, Simd_static_cast(float64, 0.0), n);
}

#endif /* GENERIC */

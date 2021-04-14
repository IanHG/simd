#include "common.h"

#if defined (GENERIC)

void generic_axpy_float64(float64* const Simd_restrict y, const float64* const Simd_restrict x, float64 a, int n)
{
   for(int i = 0; i < n; ++i)
   {
      y[i] = a * x[i] + y[i];
   }
}

#endif /* GENERIC */

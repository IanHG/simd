#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "alloc.h"

#if !defined(SIMD_ALIGNMENT)
#define SIMD_ALIGNMENT 256
#endif /* SIMD_ALIGNMENT */

/**
 * Allocate memory
 **/
void* simd_allocate(int32 size)
{
   void* ptr;
   int status = posix_memalign(&ptr, SIMD_ALIGNMENT, size);
   if(status != 0)
   {
      printf(" Could not allocate \n");
      assert(0);
   }
   return ptr;
}

/**
 * Deallocate memory
 **/
void simd_deallocate(void* ptr)
{
   if(ptr)
   {
      free(ptr);
   }
}

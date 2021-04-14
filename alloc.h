#pragma once
#ifndef SIMD_ALLOC_H_INCLUDED
#define SIMD_ALLOC_H_INCLUDED

#include "typedef.h"

/**
 * Allocate memory
 **/
void* simd_allocate(int32 size);

/**
 * Deallocate memory
 **/
void simd_deallocate(void* ptr);

#endif /* SIMD_ALLOC_H_INCLUDED */

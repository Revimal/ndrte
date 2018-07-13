/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDRTE_DST_COMMON_H
#define NDRTE_DST_COMMON_H

#include <stdint.h>

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_barrier.h"

#ifdef __KERNEL__
#define ndrte_dst_alloc(size) kzalloc((size), GFP_KERNEL)
#define ndrte_dst_free(ptr) kfree(ptr)
#else
#define ndrte_dst_alloc(size) calloc(1, (size))
#define ndrte_dst_free(ptr) free(ptr)
#endif

enum ndrte_dst_mode_enum
{
	NDRTE_DST_BULK,
	NDRTE_DST_AVAIL,
};
typedef enum ndrte_dst_mode_enum ndrte_dst_mode_t;

#endif
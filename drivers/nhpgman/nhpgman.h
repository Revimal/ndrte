/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDR_HUGEPGMAN_H
#define NDR_HUGEPGMAN_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_atomic.h"
#include "drv_common.h"

#define NHPGMAN_GFP_FLAG_DEVICE (GFP_ATOMIC | __GFP_COLD | __GFP_COMP | __GFP_NORETRY | __GFP_NOWARN)
#define NHPGMAN_GFP_FLAG_ATOMIC (GFP_ATOMIC | __GFP_COMP | __GFP_NORETRY | __GFP_NOWARN)
#define NHPGMAN_GFP_FLAG_NORMAL (GFP_KERNEL | __GFP_COMP | __GFP_NORETRY | __GFP_NOWARN)

enum nhpg_gfp_type {
	NHPG_DEV,
	NHPG_IRQ,
	NHPG_NORM,
};
typedef nhpg_gfp_type nhpg_gfp_t;

#endif
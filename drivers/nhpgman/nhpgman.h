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

#define NHPGMAN_GFP_FLAG_PREALLOC (GFP_ATOMIC | __GFP_COLD | __GFP_COMP | __GFP_NORETRY | __GFP_NOWARN)
#define NHPGMAN_GFP_FLAG_RTALLOC (GFP_ATOMIC | __GFP_COLD | __GFP_COMP | __GFP_NORETRY | __GFP_NOWARN)

#endif
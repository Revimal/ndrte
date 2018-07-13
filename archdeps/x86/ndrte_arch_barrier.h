/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDRTE_ARCH_BARRIER_H
#define NDRTE_ARCH_BARRIER_H

#include "ndrte_arch_common.h"

#define ndrte_mb()	__asm__ __volatile__ ("mfence" : : : "memory")
#define ndrte_rmb()	__asm__ __volatile__ ("lfence" : : : "memory")
#define ndrte_wmb()	__asm__ __volatile__ ("sfence" : : : "memory")

#endif

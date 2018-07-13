/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDRTE_ARCH_COMMON_H
#define NDRTE_ARCH_COMMON_H

#define NDRTE_LOCK_PREFIX "\n\tlock; "
#define NDRTE_ARCH_CACHELINE 64

static inline void ndrte_pause( void )
{
	;
}

#endif
#ifndef NDRTE_ARCH_COUNTER_H
#define NDRTE_ARCH_COUNTER_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"
#include "ndrte_arch_barrier.h"

enum ndrte_arch_counter_enum
{
	NDRTE_ARCH_COUNTER_PROGRAMMABLE = 0,
	NDRTE_ARCH_COUNTER_INSTRUCTION = 1 << 30,
	NDRTE_ARCH_COUNTER_CYCLES = (1 << 30) + 1,
	NDRTE_ARCH_COUNTER_REF_CYCLES = (1 << 30) + 2
};
typedef enum ndrte_arch_counter_enum ndrte_arch_counter_t;

static NDRTE_STRONG_INLINE uint64_t ndrte_hwcnt_pmc( ndrte_arch_counter_t type )
{
	register uint32_t l32 __asm__( "eax" );
	register uint32_t h32 __asm__( "edx" );

	__asm__ __volatile__ ( "rdpmc"
							: "=a" (l32), "=d" (h32)
							: "c" (type) );
	return ((uint64_t)h32 << 32) | ((uint64_t)l32);
}

static NDRTE_STRONG_INLINE uint64_t ndrte_hwcnt_tsc( void )
{
	register uint32_t l32 __asm__( "eax" );
	register uint32_t h32 __asm__( "edx" );

	__asm__ __volatile__ ( "rdtsc"
							: "=a" (l32), "=d" (h32) );
	return ((uint64_t)h32 << 32) | ((uint64_t)l32);
}

static NDRTE_STRONG_INLINE uint64_t ndrte_hwcnt_pmc_precise( ndrte_arch_counter_t type )
{
	register uint32_t l32 __asm__( "eax" );
	register uint32_t h32 __asm__( "edx" );

	ndrte_mb();
	__asm__ __volatile__ ( "rdpmc"
							: "=a" (l32), "=d" (h32)
							: "c" (type) );
	return ((uint64_t)h32 << 32) | ((uint64_t)l32);
}

static NDRTE_STRONG_INLINE uint64_t ndrte_hwcnt_tsc_precise( void )
{
	register uint32_t l32 __asm__( "eax" );
	register uint32_t h32 __asm__( "edx" );

	ndrte_mb();
	__asm__ __volatile__ ( "rdtsc"
							: "=a" (l32), "=d" (h32) );
	return ((uint64_t)h32 << 32) | ((uint64_t)l32);
}

#endif
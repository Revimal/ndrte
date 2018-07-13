/******************************************************************************
 Copyright (C) 2018 NDR Opensource Group

 Licensed under the several legal conditions.
 See 'License' in the project root for legal information.
******************************************************************************/

#ifndef NDRTE_ARCH_ATOMIC_H
#define NDRTE_ARCH_ATOMIC_H

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"

typedef struct ndrte_atomic64_struct
{
	uint64_t cnt;
} ndrte_atomic64_t;

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_get( ndrte_atomic64_t *atomic_val )
{
	return NDRTE_ACCESS_ONCE( atomic_val->cnt );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_set( ndrte_atomic64_t *atomic_val, uint64_t mov_val )
{
	atomic_val->cnt = mov_val;
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_or( ndrte_atomic64_t *atomic_val, uint64_t or_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "orq %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (or_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_xor( ndrte_atomic64_t *atomic_val, uint64_t xor_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xorq %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (xor_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_and( ndrte_atomic64_t *atomic_val, uint64_t and_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "andq %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (and_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_add( ndrte_atomic64_t *atomic_val, uint64_t add_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "addq %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (add_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_sub( ndrte_atomic64_t *atomic_val, uint64_t sub_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "subq %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (sub_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_inc( ndrte_atomic64_t *atomic_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "incq %0"
							: "+m" ((atomic_val)->cnt) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_dec( ndrte_atomic64_t *atomic_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "decq %0"
							: "+m" ((atomic_val)->cnt) );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_xchg( ndrte_atomic64_t *atomic_val, uint64_t xchg_val )
{
	register uint64_t ret __asm__( "rax" ) = xchg_val;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xchgq %1, %0"
							: "+a" (ret), "+m" ((atomic_val)->cnt)
							: : "memory" );

	return ret;
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_bset( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btsq %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_bclear( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btrq %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE void ndrte_atomic64_bxchg( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btcq %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_btest( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	register uint64_t ret __asm__( "rax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btq %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_btestset( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	register uint64_t ret __asm__( "rax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btsq %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_btestclear( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	register uint64_t ret __asm__( "rax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btrq %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_btestxchg( ndrte_atomic64_t *atomic_val, uint64_t bit )
{
	register uint64_t ret __asm__( "rax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btcq %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_cmpxchg( ndrte_atomic64_t *atomic_val, uint64_t old_val, uint64_t new_val )
{
	register uint64_t ret __asm__( "rax" );

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgq %2, %1"
							: "=a" (ret), "+m" ((atomic_val)->cnt)
							: "r" (new_val), [oldval] "a" (old_val)
							: "memory" );
	return ret;
}

typedef struct ndrte_atomic32_struct
{
	uint32_t cnt;
} ndrte_atomic32_t;

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_get( ndrte_atomic32_t *atomic_val )
{
	return NDRTE_ACCESS_ONCE( atomic_val->cnt );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_set( ndrte_atomic32_t *atomic_val, uint32_t mov_val )
{
	atomic_val->cnt = mov_val;
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_or( ndrte_atomic32_t *atomic_val, uint32_t or_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "orl %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (or_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_xor( ndrte_atomic32_t *atomic_val, uint32_t xor_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xorl %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (xor_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_and( ndrte_atomic32_t *atomic_val, uint32_t and_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "andl %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (and_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_add( ndrte_atomic32_t *atomic_val, uint32_t add_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "addl %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (add_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_sub( ndrte_atomic32_t *atomic_val, uint32_t sub_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "subl %1, %0"
							: "+m" ((atomic_val)->cnt)
							: "ir" (sub_val) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_inc( ndrte_atomic32_t *atomic_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "incl %0"
							: "+m" ((atomic_val)->cnt) );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_dec( ndrte_atomic32_t *atomic_val )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "decl %0"
							: "+m" ((atomic_val)->cnt) );
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_xchg( ndrte_atomic32_t *atomic_val, uint32_t xchg_val )
{
	register uint32_t ret __asm__( "eax" ) = xchg_val;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xchgl %1, %0"
							: "+a" (ret), "+m" ((atomic_val)->cnt)
							: : "memory" );

	return ret;
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_bset( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btsl %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_bclear( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btrl %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE void ndrte_atomic32_bxchg( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btcl %1, %0"
							: "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_btest( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	register uint32_t ret __asm__( "eax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btl %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_btestset( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	register uint32_t ret __asm__( "eax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "bts %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_btestclear( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	register uint32_t ret __asm__( "eax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btr %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_btestxchg( ndrte_atomic32_t *atomic_val, uint32_t bit )
{
	register uint32_t ret __asm__( "eax" ) = 0;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "btc %2, %1"
							: "=@ccc" (ret), "+m" ((atomic_val)->cnt )
							: "ir" (bit)
							: "memory" );
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_cmpxchg( ndrte_atomic32_t *atomic_val, uint32_t old_val, uint32_t new_val )
{
	register uint32_t ret __asm__( "eax" );

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgl %2, %1"
							: "=a" (ret), "+m" ((atomic_val)->cnt)
							: "r" (new_val), "a" (old_val)
							: "memory" );
	return ret;
}

#endif
#ifndef NDRTE_ARCH_ATOMIC_H
#define NDRTE_ARCH_ATOMIC_H

#include <stdint.h>

#include "ndrte_compiler_common.h"
#include "ndrte_arch_common.h"

#ifdef __KERNEL__
#include <asm/atomic64_t.h>
#include <asm/atomic.h>

typedef atomic64_t ndrte_atomic64_t;

#define ndrte_atomic64_get( atomic_val ) \
	atomic64_read( atomic_val )

#define ndrte_atomic64_set( atomic_val, mov_val ) \
	atomic64_set( atomic_val, mov_val )

#define ndrte_atomic64_add( atomic_val, add_val ) \
	atomic64_add( add_val, atomic_val )

#define ndrte_atomic64_sub( atomic_val, sub_val ) \
	atomic64_sub( sub_val, atomic_val )

#define ndrte_atomic64_inc( atomic_val ) \
	atomic64_inc( atomic_val )

#define ndrte_atomic64_dec( atomic_val ) \
	atomic64_dec( atomic_val )

#define ndrte_atomic64_xchg( atomic_val, old_val, new_val ) \
	atomic64_xchg( atomic_val, old_val, new_val )

#define ndrte_atomic64_cmpxchg( atomic_val, old_val, new_val ) \
	atomic64_cmpxchg( atomic_val, old_val, new_val )

typedef atomic_t ndrte_atomic32_t;

#define ndrte_atomic32_get( atomic_val ) \
	atomic_read( atomic_val )

#define ndrte_atomic32_set( atomic_val, mov_val ) \
	atomic_set( atomic_val, mov_val )

#define ndrte_atomic32_add( atomic_val, add_val ) \
	atomic_add( add_val, atomic_val )

#define ndrte_atomic32_sub( atomic_val, sub_val ) \
	atomic_sub( sub_val, atomic_val )

#define ndrte_atomic32_inc( atomic_val ) \
	atomic_inc( atomic_val )

#define ndrte_atomic32_dec( atomic_val ) \
	atomic_dec( atomic_val )

#define ndrte_atomic32_cxchg( atomic_val, old_val, new_val ) \
	atomic_xchg( atomic_val, old_val, new_val )

#define ndrte_atomic32_cmpxchg( atomic_val, old_val, new_val ) \
	atomic_cmpxchg( atomic_val, old_val, new_val )

#else

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
	NDRTE_ACCESS_ONCE( atomic_val->cnt ) = NDRTE_ACCESS_ONCE( mov_val );
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
	NDRTE_UOPTR( uint64_t ) ptr = ndrte_uoptr_set(atomic_val->cnt);

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xchgq %0, %1"
							: "+a" (ret), "+m" (*ptr)
							: : "memory" );
	
	return ret;
}

static NDRTE_STRONG_INLINE uint64_t ndrte_atomic64_cmpxchg( ndrte_atomic64_t *atomic_val, uint64_t old_val, uint64_t new_val )
{
	register uint64_t ret __asm__( "rax" );
	NDRTE_UOPTR( uint64_t ) ptr = ndrte_uoptr_set(atomic_val->cnt);

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgq %2, %1"
							: "=a" (ret), "+m" (*ptr)
							: "r" (new_val), "a" (old_val)
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
	NDRTE_ACCESS_ONCE( atomic_val->cnt ) = NDRTE_ACCESS_ONCE( mov_val );
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
	NDRTE_UOPTR( uint32_t ) ptr = ndrte_uoptr_set(atomic_val->cnt);

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "xchgl %0, %1"
							: "+a" (ret), "+m" (*ptr)
							: : "memory" );
	
	return ret;
}

static NDRTE_STRONG_INLINE uint32_t ndrte_atomic32_cmpxchg( ndrte_atomic32_t *atomic_val, uint32_t old_val, uint32_t new_val )
{
	register uint32_t ret __asm__( "eax" );
	NDRTE_UOPTR( uint32_t ) ptr = ndrte_uoptr_set(atomic_val->cnt);

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgl %2, %1"
							: "=a" (ret), "+m" (*ptr)
							: "r" (new_val), "a" (old_val)
							: "memory" );
	return ret;
}
#endif

#endif
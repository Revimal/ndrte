#ifndef NDRTE_ARCH_ATOMIC_H
#define NDRTE_ARCH_ATOMIC_H

#include "ndrte_arch_common.h"

#ifdef __KERNEL__
#else
typedef struct ndrte_atomic64_struct
{
	uint64_t cnt;
} ndrte_atomic64_t;

#define ndrte_atomic64_get( atomic_val )\
	*(__volatile__ uint64_t *)( atomic_val )

#define ndrte_atomic64_mov( atomic_val, mov_val )\
	__asm__ __volatile__ ( "movq %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (mov_val) )

#define ndrte_atomic64_add( atomic_val, add_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "addq %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (add_val) )

#define ndrte_atomic64_sub( atomic_val, sub_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "subq %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (sub_val) )

#define ndrte_atomic64_inc( atomic_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "incq %0"\
							: "+m" ((atomic_val)->cnt) )

#define ndrte_atomic64_dec( atomic_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "decq %0"\
							: "+m" ((atomic_val)->cnt) )

__attribute__((always_inline)) static inline int ndrte_atomic64_cmpxchg( ndrte_atomic64_t *atomic_val, uint64_t old_val, uint64_t new_val ){
	register unsigned char __ret asm( "al" );
	__volatile__ uint64_t *__ptr = (__volatile__ uint64_t *)&atomic_val->cnt;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgq %2, %1"
							"\t\nxor %%rax, %%rax"
							"\t\nsete %0"
							: "=a" (__ret), "=m" (*__ptr)
							: "r" (new_val), "m" (*__ptr), "a" (old_val)
							: "memory" );
	return __ret;
}

typedef struct ndrte_atomic32_struct
{
	uint32_t cnt;
} ndrte_atomic32_t;

#define ndrte_atomic32_get( atomic_val )\
	*(__volatile__ uint32_t *)(atomic_val)

#define ndrte_atomic32_mov( atomic_val, mov_val )\
	__asm__ __volatile__ ( "movl %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (mov_val) )

#define ndrte_atomic32_add( atomic_val, add_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "addl %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (add_val) )

#define ndrte_atomic32_sub( atomic_val, sub_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "subl %1, %0"\
							: "+m" ((atomic_val)->cnt)\
							: "ir" (sub_val) )

#define ndrte_atomic32_inc( atomic_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "incl %0"\
							: "+m" ((atomic_val)->cnt) )

#define ndrte_atomic32_dec( atomic_val )\
	__asm__ __volatile__ ( LOCK_PREFIX "decl %0"\
							: "+m" ((atomic_val)->cnt) )

__attribute__((always_inline)) static inline int ndrte_atomic32_cmpxchg( ndrte_atomic32_t *atomic_val, uint32_t old_val, uint32_t new_val )
{
	register unsigned char __ret asm( "al" );
	__volatile__ uint32_t *__ptr = (__volatile__ uint32_t *)&atomic_val->cnt;

	__asm__ __volatile__ ( NDRTE_LOCK_PREFIX "cmpxchgl %2, %1"
							"\t\nxor %%eax, %%eax"
							"\t\nsete %0"
							: "=a" (__ret), "=m" (*__ptr)
							: "r" (new_val), "m" (*__ptr), "a" (old_val)
							: "memory" );
	return __ret;
}
#endif

#endif
#ifndef NDRTE_LFQUEUE_H
#define NDRTE_LFQUEUE_H

#include <string.h>

#include "ndrte_arch_atomic.h"

#define NDRTE_LFQ_DECLARE( lfq_alias, lfq_size ) \
struct ndrte_generic_lfq_ ## lfq_alias \
{ \
    ndrte_atomic64_t q_buf[lfq_size]; \
    uint64_t lfq_sz; \
    ndrte_atomic64_t lfq_front; \
    ndrte_atomic64_t lfq_rear; \
} NDRTE_ALIGN( NDRTE_ARCH_CACHELINE )

#define NDRTE_LFQ( lfq_alias ) \
   struct ndrte_generic_lfq_ ## lfq_alias

#define NDRTE_LFQ_INIT( lfq, lfq_size ) \
do \
{ \
    memset( (lfq), 0, sizeof(*(lfq)) ); \
    (lfq)->lfq_sz = (lfq_size); \
} while ( 0 );

#define ndrte_lfq_get_sz( lfq ) \
    ( (lfq)->lfq_sz )

#define ndrte_lfq_calc_safe( lfq, expr ) \
    ((expr) % ndrte_lfq_get_sz( (lfq) ))

#define ndrte_lfq_get_front( lfq ) \
    ndrte_atomic64_get( &((lfq)->lfq_front) )

#define ndrte_lfq_get_rear( lfq ) \
    ndrte_atomic64_get( &((lfq)->lfq_rear) )

#define ndrte_lfq_enq( lfq, ptr ) \
do{ \
    uint64_t rear, conv_ptr; \
    conv_ptr = (uint64_t) ptr; \
    if ( conv_ptr == 0 ) \
        break; \
    while ( 1 ) \
    { \
        rear = ndrte_lfq_get_rear( lfq ); \
        if ( ndrte_atomic64_get( &((lfq)->q_buf[rear + 1]) ) != 0 ) \
        { \
            conv_ptr = 0; \
            break; \
        } \
        if ( ndrte_atomic64_cmpxchg( &((lfq)->lfq_rear), rear, ndrte_lfq_calc_safe( (lfq), rear + 1 ) ) == rear ) \
        { \
            ndrte_atomic64_set( &((lfq)->q_buf[rear]), conv_ptr ); \
            break; \
        } \
    } \
    ptr = (void *)conv_ptr; \
} while ( 0 )

#define ndrte_lfq_deq( lfq, ptr ) \
do{ \
    uint64_t front, conv_ptr; \
    conv_ptr = 0; \
    while ( 1 ) \
    { \
        front = ndrte_lfq_get_front( lfq ); \
        if ( ndrte_atomic64_get( &((lfq)->q_buf[front]) ) == 0 ) \
        { \
            break; \
        } \
        if ( ndrte_atomic64_cmpxchg( &((lfq)->lfq_front), front, ndrte_lfq_calc_safe( (lfq), front + 1 ) ) == front ) \
        { \
            conv_ptr = ndrte_atomic64_xchg( &((lfq)->q_buf[front]), conv_ptr ); \
            break; \
        } \
    } \
    ptr = (void *)conv_ptr; \
} while ( 0 )

#endif
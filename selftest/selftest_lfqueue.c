#include "selftest_lfqueue.h"
#include "ndrte_lfqueue.h"

#define LFQ_TEST_SIZE 10000000
#define LFQ_TEST_MPNUM 10

NDRTE_LFQ_DECLARE( lfq_test, LFQ_TEST_SIZE + 1 );

static NDRTE_LFQ( lfq_test ) lfq;

static void * lfq_sp_enq( void *args )
{
    uint64_t i;
	void *tmp;

    for ( i = 0; i < LFQ_TEST_SIZE; i++ )
    {
        tmp = (void *)(i + 1);
        ndrte_lfq_enq( &lfq, tmp );
    }

    return NULL;
}

static void * lfq_sp_sc_deq( void *args )
{
    uint64_t i;
	void *tmp;

    for ( i = 0; i < LFQ_TEST_SIZE; i++ )
    {
        ndrte_lfq_deq( &lfq, tmp );
		NTS_CHECK_LVL( lfqueue_sp_sc, i + 1 == (uint64_t)tmp, NTS_LVLSILENT );
    }

    return NULL;
}

NTS_DECLARE_TC( lfqueue_single )
{
    uint64_t i;
	void *tmp;

	NDRTE_LFQ_INIT( &lfq, LFQ_TEST_SIZE + 1 );

    ( void ) lfq_sp_enq( NULL );

    for ( i = 0; i < LFQ_TEST_SIZE; i++ )
    {
        ndrte_lfq_deq( &lfq, tmp );
		NTS_CHECK_LVL( lfqueue_single, i + 1 == (uint64_t)tmp, NTS_LVLSILENT );
    }
}

NTS_DECLARE_TC( lfqueue_sp_sc )
{
    pthread_t enq_th, deq_th;
	void *tmp;

	NDRTE_LFQ_INIT( &lfq, LFQ_TEST_SIZE + 1 );

    pthread_create( &enq_th, NULL, &lfq_sp_enq, NULL );
    pthread_create( &deq_th, NULL, &lfq_sp_sc_deq, NULL );

    pthread_join( enq_th, &tmp );
    pthread_join( deq_th, &tmp );
}
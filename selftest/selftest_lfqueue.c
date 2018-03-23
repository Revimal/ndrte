#include "selftest_lfqueue.h"
#include "ndrte_lfqueue.h"

NDRTE_LFQ_DECLARE( lfq_test, 1000 + 1 );

static NDRTE_LFQ( lfq_test ) lfq;

NTS_DECLARE_TC( lfqueue_sp_deq )
{
	uint64_t i;
	void *tmp;

	NDRTE_LFQ_INIT( &lfq, 1000 + 1 );

    for ( i = 0; i < 1000; i++ )
    {
        tmp = (void *)(i + 1);
        ndrte_lfq_enq( &lfq, tmp );
    }

	for ( i = 0; i < 1000; i++ )
    {
        ndrte_lfq_deq( &lfq, tmp );
		__NTS_ASSERT( lfqueue_sp_deq, i + 1 == (uint64_t)tmp, __NTS_LVLNONE );
    }
}
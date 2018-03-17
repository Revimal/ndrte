#include <stdio.h>

#include "ndrte_lfqueue.h"

NDRTE_LFQ_DECLARE( lfq_test, 1000 + 1 );

static NDRTE_LFQ( lfq_test ) lfq;

int main( int argc, char **argv )
{
    uint64_t i;
    void *tmp;

    NDRTE_LFQ_INIT( lfq_test, 1000 + 1, &lfq );

    printf( "\nEnqueue...\n" );
    for ( i = 0; i < 1000; i++ )
    {
        tmp = (void *)(i + 1);
        printf( "%lu = %lu\n", i, (uint64_t)tmp );
        ndrte_lfq_enq( &lfq, tmp );
    }

    printf( "\nDnqueue...\n" );
    for ( i = 0; i < 1000; i++ )
    {
        ndrte_lfq_deq( &lfq, tmp );
        printf( "%lu = %lu\n", i, (uint64_t)tmp );
    }

    return 0;
}
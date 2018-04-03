#include "selftest.h"

int main( int argc, char **argv )
{
	NTS_CALL_TC( lfqueue_single );
	NTS_REPORT( lfqueue_single );

	NTS_CALL_TC( lfqueue_sp_sc );
	NTS_REPORT( lfqueue_sp_sc );

	return 0;
}
/* quick hack to run its argument detached from the tty.  this is not
the original detach.c, just one I wrote because I needed itand it was
quicker to write this than dial in, search, and find.

Copyright 1996-1999 Arnt Gulbrandsen.  Use, modification and
distribution is allowed without limitation, warranty, or liability of
any kind.  I consider modification of this license to be rude.
*/


#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, char ** argv ) {
    int i;

    i = getdtablesize();
    while( i >= 0 ) {
	close( i );
	i--;
    }
    open( "/dev/null", O_RDWR );
    dup( 0 );
    dup( 0 );

    if ( fork() > 0 )
	exit( 0 );
    setpgrp();
    /* extra fork isn't strictly necessary */
    if ( fork() > 0 )
	exit( 0 );

    argv++;
    execvp( argv[0], argv );
    exit( 0 );
}

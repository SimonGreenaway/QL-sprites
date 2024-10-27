/*
 *              m a l l o c
 *
 * Routine to do a dynamic memory allocation.
 *
 */

#define __LIBRARY__

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <qdos.h>

// SJG ADD:
void *SJGlsbrk _LIB_F1_ (long,   lnbytes );

void *SJGmalloc _LIB_F1_(size_t,   size)
{
    char *ret;

    //assert (stackcheck());

    printf("malloc(%ld)\n",size);

    if ( (size == 0L )
    ||   ((ret = (char *)SJGlsbrk((long)(size += 4)))==NULL) ) {
        return NULL;
    }

    /* The first long word of the area contains the length allocated.
     * In this implementation it is set up within the 'lsbrk' routine
     * so we do not need to do it explicitly here.
     */
     /*    *(long *)ret = size;     */

    //mpause(250);

    printf("Malloc returning %ld\n",ret+4);

    return (void *)(ret + 4);
}


//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include <stdio.h>
#include "biostat.h"

/* function that return the length of a sequence */

STAT_T genelen(SEQ *s_ptr){
    return strlen(s_ptr->seq);
}

/* funtion that return the percentage amount of GC base within the SEQ object, computed as G+C / (A+G+C+T) */

double gcperc(SEQ *s_ptr){
    
    char *ptr;                                                  /* defined for improving code readability */
    ptr = s_ptr->seq;
    
    double gc;
    int i;
    for(gc = 0.0, i = 0; ptr[i]; i++)
        if(ptr[i] == 'G' || ptr[i] == 'C')
            gc++;
    return gc / i;
}

OCC **findocc(unsigned long *cnt, SEQ *s_ptr, SRCH_T *targ){
    
    unsigned long size = INITSIZE;
    
    char *ptr;
    ptr = s_ptr->seq;
    
    OCC **fptr;
    int nocc;
    OCC *o_ptr;
    
    if((fptr = alloc_occptr_arr(size)) == NULL)
        raise_error("findocc1() can't alloc memory for array of pointers to OCC objects\n");
    
    STAT_T fpos;
    int i;
    for(i = 0; !ctrl.eof; i = (fpos + targ->curlen)){
        if((fpos = sfind1(ptr, targ, i)) >= 0 && fpos <= strlen(ptr)){                      /* found occurrences */
            if(nocc >= size){
                // TODO: realloc array of pointers
            }
            
            if((o_ptr = alloc_occ()) == NULL)
                raise_error("findocc1() can't alloc memory for OCC object\n");
            o_ptr->fpos = fpos;
            o_ptr->flen = targ->curlen;
            fptr[nocc++] = o_ptr;
        }
    }
    
    fptr[nocc] = NULL;                                                  /* set the end of the array */
    *cnt = nocc;
    
    if(ctrl.eof)                                                        /* reset the global flag so that other subroutines can use it */
        ctrl.eof = 0;
    
    return fptr;
}

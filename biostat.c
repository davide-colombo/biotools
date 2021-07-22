//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostat.h"

/* function that return the length of a sequence */

LEN_T genelen(SEQ *s_ptr){
    return strlen(s_ptr->seq);
}

/* funtion that return the percentage amount of GC base within the SEQ object, computed as G+C / (A+G+C+T) */

double gcperc(SEQ *s_ptr){
    
    char *ptr;                                                  /* defined for improving code readability */
    ptr = s_ptr->seq;
    
    double gc;
    FPOS_T i;
    for(gc = 0.0, i = 0; ptr[i]; i++)
        if(ptr[i] == 'G' || ptr[i] == 'C')
            gc++;
    return gc / i;
}

/* a function that searches for occurrences of 'targ->str' string within 's_ptr->seq' */

OCC **findocc(LEN_T *cnt, SEQ *s_ptr, SRCH_T *targ){
    
    *cnt = 0;                                                           /* initialize FOR SAFETY the counter to 0 */
    LEN_T size = INITSIZE;                                              /* initialize the size variable to INITSIZE symbolic constant */
    
    char *ptr;                                                          /* define pointer to char to improve code readability */
    ptr = s_ptr->seq;
    
    OCC **fptr;                                                         /* array of pointers to 'OCC *' objects */
    OCC *o_ptr;                                                         /* pointer to 'OCC' object */
    
    if((fptr = alloc_occptr_arr(size)) == NULL)
        raise_error("findocc1() can't alloc memory for \
                    array of pointers to OCC objects\n");
    
    FPOS_T i, fpos;
    for(i = 0; !ctrl.eof; i = (fpos + targ->curlen)){                   /* the loop ENDs when 'sfind()' sets the ctrl.eof flag to 1 */
        if((fpos = sfind(ptr, targ, i)) >= 0 && fpos <= strlen(ptr)){
            if(*cnt >= size){
                printf("you must realloc array of pointer\n");
                break;
            }
            
            if((o_ptr = alloc_occ()) == NULL)                           /* alloc memory for a single OCC object */
                raise_error("findocc1() can't alloc memory\
                            for OCC object\n");
            o_ptr->fpos = fpos;
            o_ptr->flen = targ->curlen;
            fptr[(*cnt)++] = o_ptr;
        }
    }
    
    fptr[*cnt] = NULL;                                                  /* set the end of the array */
    
    if(ctrl.eof)                                                        /* reset the global flag so that other subroutines can use it */
        ctrl.eof = 0;
    
    return fptr;
}

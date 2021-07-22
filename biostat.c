//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include <stdio.h>
#include "biostat.h"

/* function that return the number of occurrences of the string 's' within another the 'SEQ' string */

STAT_T scount(SEQ *s_ptr, char *s){
    
    char *ptr;                                                      /* define pointer to char to improve code readability */
    ptr = s_ptr->seq;
    
    STAT_T cnt;                                                     /* variable in which is stored the number of match */
    int i, f;
    
    for(i = 0, cnt = 0; !ctrl.eof; i+=(f+strlen(s)))                /* cycle until the callee does not set the eof flag */
        if((f = sfind(ptr, s, i)) >= 0 && f <= strlen(ptr))         /* 'f' is the index of the occurrence */
            cnt++;
    
    if(ctrl.eof)                                                    /* reset the global variable to make it available to other functions */
        ctrl.eof = 0;
    
    return cnt;
}

/* function that return the number of sequential occurrences of a the character 'c' that are at least equal to or longer than 'minlen' */

STAT_T repcount(SEQ *s_ptr, char c, unsigned minlen){
    
    char *ptr;
    ptr = s_ptr->seq;
    
    STAT_T cnt, len;
    int i, f;
    for(cnt = 0, len = 0, i = 0; !ctrl.eof; i+=(f+len))
        if((f = repfind(ptr, c, minlen, i, &len)) != NOTFOUND)
            cnt++;
    
    if(ctrl.eof)
        ctrl.eof = 0;
    
    return cnt;
}

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

/* function that do the same job as 'scount()' above but instead of simply return the number of matches, return 'OCC *[]' */

OCC **findocc(SEQ *s_ptr, char *s){
    
    unsigned long size = INITSIZE;
    
    OCC **fptr;                                                 /* define an array of pointer to OCC typedef objects */
    int nocc;
    OCC *o_ptr;                                                 /* pointer to OCC object that will be allocated during the search */
    
    char *ptr;                                                  /* define a pointer to char for increase code readability */
    ptr = s_ptr->seq;
    
    if((fptr = alloc_occptr_arr(size)) == NULL)                 /* alloc memory for array of pointers to OCC objects */
        raise_error("findocc() can't alloc memory for array of pointers to OCC objects\n");
    
    STAT_T fpos;                                                /* position of the match within string pointed by ptr */
    int i;
    for(i = 0, nocc = 0; !ctrl.eof; i = (fpos+strlen(s))){
        if((fpos = sfind(ptr, s, i)) >= 0 && fpos <= strlen(ptr)){
            if(nocc >= size){
                // TODO: realloc OCC array
            }
            
            if((o_ptr = alloc_occ()) == NULL)                   /* occurrence found: alloc a new OCC object */
                raise_error("findocc() can't alloc memory for OCC object\n");
            o_ptr->fpos = fpos;                                 /* save start position */
            o_ptr->flen = strlen(s);                            /* save match length */
            fptr[nocc++] = o_ptr;                               /* save occurrence in the OCC array of pointers and increase 'nocc' by 1 */
        }
    }
    
    fptr[nocc] = NULL;                                          /* stop the searching when printing */
    
    if(ctrl.eof)                                                /* reset the flag used by the callee to signal the end of the string to be scanned */
        ctrl.eof = 0;
    
    return fptr;
}

OCC **findocc1(unsigned long *cnt, SEQ *s_ptr, SRCH_T *targ){
    
    unsigned long size = INITSIZE;
    
    char *ptr;
    ptr = s_ptr->seq;
    
    OCC **fptr;
    int nocc;
    OCC *o_ptr;
    
    if((fptr = alloc_occptr_arr(size)) == NULL)
        raise_error("findocc1() can't alloc memory for array of pointers to OCC objects\n");

    int i;
    for(i = 0; !ctrl.eof; i = (targ->strpos + targ->curlen)){
        *cnt = sfind1(ptr, targ, i);                            /* found occurrences */
        
        if(nocc >= size){
            // TODO: realloc array of pointers
        }
        
        if((o_ptr = alloc_occ()) == NULL)
            raise_error("findocc1() can't alloc memory for OCC object\n");
        o_ptr->fpos = targ->strpos;
        o_ptr->flen = targ->curlen;
        fptr[nocc++] = o_ptr;
    }
        
    fptr[nocc] = NULL;                                          /* set the end of the array */
    
    if(ctrl.eof)                                                /* reset the global flag so that other subroutines can use it */
        ctrl.eof = 0;
    
    return fptr;
}

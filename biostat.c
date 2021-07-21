//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostat.h"

/* function that return the number of occurrences of the string 's' within another the 'SEQ' string */

STAT_T scount(SEQ *s_ptr, char *s){
    
    char *ptr;                                              /* define pointer to char to improve code readability */
    ptr = s_ptr->seq;
    
    STAT_T cnt;                                             /* variable in which is stored the number of match */
    int i, f;
    
    for(i = 0, cnt = 0; !ctrl.eof; i+=(f+strlen(s)))        /* cycle until the callee does not set the eof flag */
        if((f = sfind(ptr, s, i)) != NOTFOUND)              /* 'f' is the index of the occurrence */
            cnt++;
    
    if(ctrl.eof)                                            /* reset the global variable to make it available to other functions */
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
    
    char *ptr;                                              /* defined for improving code readability */
    ptr = s_ptr->seq;
    
    double gc;
    int i;
    for(gc = 0.0, i = 0; ptr[i]; i++)
        if(ptr[i] == 'G' || ptr[i] == 'C')
            gc++;
    return gc / i;
}

OCC **findocc(SEQ *s_ptr, char *s){
    
    unsigned long size = INITSIZE;
    
    OCC **fptr;                                                 /* define an array of pointer to OCC typedef objects */
    int nocc = 0;
    OCC *o_ptr;                                                 /* pointer to OCC object that will be allocated during the search */
    
    char *ptr;                                                  /* define a pointer to char for increase code readability */
    ptr = s_ptr->seq;
    
    fptr = (OCC **)malloc(sizeof(OCC *) * 10);
    
    STAT_T matchpos;                                            /* position of the match within string pointed by ptr */
    int i;
    for(i = 0; !ctrl.eof; i+=(matchpos+strlen(s))){
        if((matchpos = sfind(ptr, s, i)) != NOTFOUND){
            if(nocc >= size){
                // TODO: realloc OCC array
            }
            
            if((o_ptr = (OCC *)malloc(sizeof(OCC))) == NULL)    /* occurrence found: alloc a new OCC object */
                raise_error("findocc() can't alloc memory for OCC object\n");
            o_ptr->strpos = matchpos;                           /* save start position */
            o_ptr->length = strlen(s);                          /* save match length */
            fptr[nocc++] = o_ptr;                               /* save occurrence in the OCC array of pointers and increase 'nocc' by 1 */
        }
    }
    
    fptr[nocc] = NULL;                                          /* stop the searching when printing */
    
    if(ctrl.eof)                                            /* reset the flag used by the callee to signal the end of the string to be scanned */
        ctrl.eof = 0;
    
    return fptr;
}

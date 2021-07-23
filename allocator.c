//
//  allocator.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "allocator.h"

/* this function acts like an OOP constructor for object of type CDS */

CDS_T *cds_t(char *str, char *stp, FPOS_T strpos, LEN_T len){
    CDS_T *c_ptr;
    if((c_ptr = alloc_cds()) == NULL)
        return NULL;
    c_ptr->str = alloc_chararray(strlen(str));
    c_ptr->stp = alloc_chararray(strlen(stp));
    strcpy(c_ptr->str, str);
    strcpy(c_ptr->stp, stp);
    c_ptr->strpos = strpos;
    c_ptr->len = len;
    return c_ptr;
}

CDS_T *alloc_cds(void){
    return (CDS_T *)malloc(sizeof(CDS_T));
}

void free_cds_t(CDS_T *ptr){
    if(ptr == NULL)
        return;
    
    free((void *)ptr->str);
    free((void *)ptr->stp);
    free((void *)ptr);
}

/* this function acts like an OOP constructor */

SRCH_T *srch_t(char *s, LEN_T min, LEN_T max){
    SRCH_T *ptr;
    if((ptr = alloc_srch()) == NULL)
        return NULL;
    ptr->str = alloc_chararray(strlen(s));              /* this function allocate a space equal to the size passed + 1 */
    strcpy(ptr->str, s);
    ptr->minlen = min;
    ptr->maxlen = max;
    return ptr;
}

void free_srch_t(SRCH_T *ptr){
    if(ptr == NULL)
        return;
    
    free((void *)ptr->str);                             /* first, let's free the char array that holds the string */
    free((void *) ptr);                                 /* second, free the 'SRCH_T' object */
}

SRCH_T *alloc_srch(void){
    return (SRCH_T *)malloc(sizeof(SRCH_T));
}

/* ================================================================================================================================== */

OCC **alloc_occptr_arr(LEN_T size){
    return (OCC **)malloc(sizeof(OCC *) * size);
}

void free_occptr_arr(OCC **ptr){
    if(ptr == NULL)
        return;
    
    LEN_T i;
    for(i = 0; *(ptr+i) != NULL; i++)
        free_occ(*(ptr+i));
}

/* ================================================================================================================================== */

/* a function-like an OOP constructor */

OCC *occ(FPOS_T fpos, FPOS_T flen){
    OCC *ptr;
    if((ptr = alloc_occ()) == NULL)
        return NULL;
    ptr->fpos = fpos;
    ptr->flen = flen;
    return ptr;
}

void free_occ(OCC *ptr){
    if(ptr == NULL)
        return;
    free((void *)ptr);
}

OCC *alloc_occ(void){
    return (OCC *)malloc(sizeof(OCC));
}

SEQ *alloc_sequence(void){
    return (SEQ *)malloc(sizeof(SEQ));
}

char *alloc_chararray(LEN_T size){
    return (char *)malloc(sizeof(char) * (size+1));             /* +1 for '\0' */
}

char *realloc_chararray(char *s, LEN_T size){
    char *ptr;
    if((ptr = alloc_chararray(size)) == NULL)
        return NULL;
    strcpy_from(ptr, s, 0);                                     /* save the content of 's' in 'ptr' starting at 0*/
    free((void *)s);                                            /* free the previous content of the array */
    return ptr;
}


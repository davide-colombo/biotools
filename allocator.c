//
//  allocator.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "allocator.h"

OCC **alloc_occptr_arr(unsigned size){
    return (OCC **)malloc(sizeof(OCC *) * size);
}

OCC *alloc_occ(void){
    return (OCC *)malloc(sizeof(OCC));
}

SEQ *alloc_sequence(void){
    return (SEQ *)malloc(sizeof(SEQ));
}

char *alloc_chararray(unsigned size){
    return (char *)malloc(sizeof(char) * (size+1));             /* +1 for '\0' */
}

char *realloc_chararray(char *s, unsigned long size){
    char *ptr;
    if((ptr = alloc_chararray(size)) == NULL)
        return NULL;
    strcpy_from(ptr, s, 0);                                     /* save the content of 's' in 'ptr' starting at 0*/
    free((void *)s);                                            /* free the previous content of the array */
    return ptr;
}

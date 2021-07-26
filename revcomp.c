//
//  revcomp.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "revcomp.h"

SEQ *revcomp(SEQ *s_ptr){
    
    if(!is_dna(s_ptr)){
        raise_error("revcomp() fails because a wrong type of sequence was passed\n");
        return NULL;
    }
    
    SEQ *r_ptr;
    if((r_ptr = alloc_sequence()) == NULL){                                  /* alloc memory for the entire sequence */
        raise_error("revcomp() can't alloc memory for 'SEQ *' object\n");
        return NULL;
    }
    
    if((r_ptr->name = sappend(s_ptr->name, "_revcomp")) == NULL){
        raise_error("revcomp() can't alloc memory for 'char' array\n");
        return NULL;
    }

    if((r_ptr->seq = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL){        /* alloc memory for char array that stores the sequence */
        raise_error("revcomp() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    char *temp;                                                             /* used to improve readability */
    char *ptr;                                                              /* ... */
    temp = s_ptr->seq;                                                      /* pointer to the original sequence */
    ptr = r_ptr->seq;                                                       /* pointer to the rev comp sequence */
        
    FPOS_T i;
    for(i = 0; isalpha(temp[i]); i++)
        ptr[i] = ((temp[i] == 'A') ? temp[i]+A2T :
                  (temp[i] == 'T') ? temp[i]-A2T :
                  (temp[i] == 'C') ? temp[i]+C2G : temp[i]-C2G);
    ptr[i] = '\0';                                                          /* must be inserted to ensure correctness */
    reverse(ptr);                                                           /* reverse the complement string */
    
    return r_ptr;
}

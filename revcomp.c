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
    if((r_ptr = make_seq()) == NULL){                              /* alloc memory for the entire sequence */
        raise_error("revcomp() can't alloc memory for 'SEQ *' object\n");
        return NULL;
    }
    
    if((r_ptr->name = sappend(s_ptr->name, "_revcomp")) == NULL){
        raise_error("revcomp() can't alloc memory for 'char' array\n");
        return NULL;
    }

    if((r_ptr->seq = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL){              /* alloc memory for char array that stores the sequence */
        raise_error("revcomp() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    char *temp, *seq;                                                             /* used to improve readability */
    temp = s_ptr->seq;                                                      /* pointer to the original sequence */
    seq = r_ptr->seq;
    
    FPOS_T i;
    for(i = 0; isalpha(temp[i]); i++)
        seq[i] = ((temp[i] == 'A') ? temp[i]+A2T :
                  (temp[i] == 'T') ? temp[i]-A2T :
                  (temp[i] == 'C') ? temp[i]+C2G : temp[i]-C2G);
    seq[i] = '\0';                                                          /* must be inserted to ensure correctness */
    reverse(seq);                                                           /* reverse the complement string */
    
    r_ptr->is_dna = 1;                                                      /* init the flag */
    
    
    return r_ptr;
}

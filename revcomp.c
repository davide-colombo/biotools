//
//  revcomp.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "revcomp.h"

SEQ *revcomp(SEQ *s_ptr){
    
    SEQ *r_ptr;
    if((r_ptr = alloc_sequence()) == NULL)                                  /* alloc memory for the entire sequence */
        raise_error("revcomp() can't alloc memory for 'SEQ *' object\n");
    if((r_ptr->name = alloc_chararray(strlen(s_ptr->name)+1)) == NULL)      /* +1 for '\0' */
        raise_error("revcomp() can't alloc memory for 'char' array\n");
    strcpy(r_ptr->name, s_ptr->name);                                       /* copy the name */

    if((r_ptr->seq = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL)        /* alloc memory for char array that stores the sequence */
        raise_error("revcomp() can't alloc memory for 'char' array\n");
    
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

//
//  revcomp.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "revcomp.h"


SEQ *revcomp(SEQ *s_ptr){
    
    if((SEQ *r_ptr = alloc_sequence()) == NULL)     /* alloc memory for the entire sequence */
        return NULL;
    
    if((r_ptr->name = alloc_chararray(strlen(s_ptr->name)+1)) == NULL)   /* +1 for '\0' */
        return NULL;
    strcpy(r_ptr->name, s_ptr->name);               /* the name of the reverse complement sequence is the same of the sequence passed as argument */

    if((r_ptr->seq = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL)
        return NULL;
    
    char *temp;                                     /* temporary variable used for improving readability of the code */
    char *ptr;                                      /* ... */
    temp = s_ptr->seq;
    ptr = r_ptr->seq;
    
    int i;
    for(i = 0; isalpha(temp[i]); i++)
        ptr[i] = ((temp[i] == 'A') ? temp[i]+A2T :
                  (temp[i] == 'T') ? temp[i]-A2T :
                  (temp[i] == 'C') ? temp[i]+C2G : temp[i]-C2G);
    ptr[i] = '\0';
    reverse(ptr);                                   /* compute the reverse of the complement */
    
    return r_ptr;
}

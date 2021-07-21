//
//  dna2rna.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "dna2rna.h"


SEQ *transcript(SEQ *s_ptr){
    
    SEQ *t_ptr;                                                                     /* pointer to transcripted SEQ object */
    if((t_ptr = alloc_sequence()) == NULL)                                          /* alloc SEQ object */
        raise_error("transcript() fails to alloc memory for 'SEQ *' object\n");
    if((t_ptr->name = alloc_chararray(strlen(s_ptr->name)+1)) == NULL)              /* alloc memory for char array of the sequence name */
        raise_error("transcript() fails to alloc memory for 'char' array\n");
    strcpy(t_ptr->name, s_ptr->name);                                               /* copy the name */
    
    if((t_ptr->seq = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL)                /* alloc memory for char array of the sequence string */
        raise_error("transcript() fails to alloc memory for 'char' array\n");
    
    char *temp, *ptr;
    temp = s_ptr->seq;
    ptr = t_ptr->seq;
    int i, c;
    for(i = 0; isalpha(temp[i]); i++)
        ptr[i] = (temp[i] == 'T') ? temp[i]+1 : temp[i];                            /* temp[i]+1 == 'U' */
    
    return t_ptr;
}

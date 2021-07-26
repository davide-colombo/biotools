//
//  dna2rna.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "dna2rna.h"

SEQ *transcript(SEQ *s_ptr){
    
    if(!is_dna(s_ptr))
        raise_error("transcript() can't transcribe sequences that are not DNA\n");
    
    SEQ *t_ptr;                                                                     /* pointer to transcripted SEQ object */
    if((t_ptr = alloc_sequence()) == NULL)                                          /* alloc SEQ object */
        raise_error("transcript() can't alloc memory for pointer to SEQ object\n");
    
    if((t_ptr->name = sappend(s_ptr->name, "_transcript")) == NULL)                 /* alloc memory for char array of the sequence name */
        raise_error("transcript() fails to append name\n");

    if((t_ptr->seq = alloc_chararray(strlen(s_ptr->seq))) == NULL)                /* alloc memory for char array of the sequence string */
        raise_error("transcript() fails to alloc sequence char array\n");
    
    char *temp, *ptr;                                                               /* use pointers to char to improve code readability */
    temp = s_ptr->seq;
    ptr = t_ptr->seq;
    
    FPOS_T i;
    for(i = 0; isalpha(temp[i]); i++)
        ptr[i] = (temp[i] == 'T') ? temp[i]+1 : temp[i];                            /* temp[i]+1 == 'U' */
    
    return t_ptr;
}

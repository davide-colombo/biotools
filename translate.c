//
//  translate.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include "translate.h"

/* function that take a pointer to SEQ object and returns a pointer to new SEQ object that contains the translated sequence (i.e., protein) */

SEQ *translate(SEQ *s_ptr, CDS_T *cds){
    
    if(!is_rna(s_ptr))                                                          /* we can transalte only the rna into protein */
        return NULL;
    
    SEQ *p_ptr;
    if((p_ptr = alloc_sequence()) == NULL)
        return NULL;
    
    LEN_T n_aa = (strlen(s_ptr->seq)-1) / 3;                                    /* -1 because the stop codon has no ammino acid associated */
    if((p_ptr->seq = alloc_chararray(n_aa)) == NULL)
        return NULL;

    if((p_ptr->name = sappend(s_ptr->name, "_protein")) == NULL)                /* 'sappend' duplicate and appen the new string */
        return NULL;
    
    return NULL;
}

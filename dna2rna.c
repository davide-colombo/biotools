//
//  dna2rna.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "dna2rna.h"

SEQ *transcript(SEQ *s_ptr){
    
    if(!is_dna(s_ptr)){
        raise_error("transcript() can't transcribe sequences that are not DNA\n");
        return NULL;
    }
    
    char *name;                                                                     /* array for saving the name of the transcribed sequence */
    if((name = sappend(s_ptr->name, "_transcript")) == NULL){                       /* alloc memory for char array of the sequence name */
        raise_error("transcript() fails to append name\n");
        return NULL;
    }

    char *seq;                                                                      /* alloc memory for the transcribe sequence itself */
    if((seq = alloc_chararray(strlen(s_ptr->seq))) == NULL){                        /* alloc memory for char array of the sequence string */
        raise_error("transcript() fails to alloc sequence char array\n");
        return NULL;
    }
    
    char *temp;                                                                     /* use pointers to char to improve code readability */
    temp = s_ptr->seq;
    
    FPOS_T i;
    for(i = 0; isalpha(temp[i]); i++)
        seq[i] = (temp[i] == 'T') ? temp[i]+1 : temp[i];                            /* temp[i]+1 == 'U' */
    
    
    SEQ *t_ptr;                                                                     /* pointer to transcripted SEQ object */
    if((t_ptr = make_seq(name, seq)) == NULL){                                           /* alloc SEQ object */
        raise_error("transcript() can't alloc memory for pointer to SEQ object\n");
        return NULL;
    }
    
    t_ptr->is_rna = 1;                                                              /* set the type flag */
    
    return t_ptr;
}

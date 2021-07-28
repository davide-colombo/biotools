//
//  translate.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include "translate.h"

/* function that take a pointer to SEQ object and returns a pointer to new SEQ object that contains the translated sequence (i.e., protein) */

SEQ *translate(SEQ *s_ptr, CDS_T *cds){
    
    if(!is_rna(s_ptr)){                                                     /* we can transalte only the rna into protein */
        raise_error("translate() fails because it can work only with mRNA sequence\n");
        return NULL;
    }
    
    LEN_T n_aa = (cds->len - 1) / 3;                                        /* -1 because the stop codon has no ammino acid associated */
    
    char *seq;
    if((seq = alloc_chararray(n_aa)) == NULL){
        raise_error("translate() fails to alloc memory for sequence string\n");
        return NULL;
    }

    char *name;
    if((name = sappend(s_ptr->name, "_protein")) == NULL){           /* 'sappend' duplicate and appen the new string */
        raise_error("translate() fails to append name\n");
        return NULL;
    }
    
    char *ptr;
    ptr = s_ptr->seq;
    
    char buf[CODONLEN+1];                                                   /* for storing the translated sequence */
    char *bufp = buf;                                                       /* pointer to the top of the buffer */
    
    FPOS_T off = cds->strpos;                                               /* offset position to use in the test conditions of the cycle */
    struct llist *node;
    int i;                                                                  /* index used to cycle on codons */
    int j;                                                                  /* index used to keep track of ammino */
    for(i = cds->strpos, j = 0; i < (cds->len+off); i++){                   /* condition on 'strlen' is a better test condition */
        *bufp++ = ptr[i];
        if((i-off+1) % CODONLEN)
            continue;
        *bufp = '\0';
        
        if((node = lookup(buf)) == NULL){
            raise_error("translate() fails lookup of a node\n");
            return NULL;
        }
        seq[j++] = *node->amm;                                              /* add amminoacid to the string */
        bufp = buf;                                                         /* re-initialize the pointer to 'buf'. 'buf' will be overridden */
    }
    
    seq[j] = '\0';                                                          /* don't forget to end the string */
    
    
    SEQ *p_ptr;
    if((p_ptr = make_seq(name, seq)) == NULL){
        raise_error("translate() fails to alloc memory space for pointer to SEQ object\n");
        return NULL;
    }
    
    s_ptr->is_pro = 1;                                                      /* set the SEQ type flag */
    
    
    return p_ptr;
}

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
    
    SEQ *p_ptr;
    if((p_ptr = alloc_sequence()) == NULL){
        raise_error("translate() fails to alloc memory space for pointer to SEQ object\n");
        return NULL;
    }
    
    LEN_T n_aa = (strlen(s_ptr->seq)-1) / 3;                                /* -1 because the stop codon has no ammino acid associated */
    if((p_ptr->seq = alloc_chararray(n_aa)) == NULL){
        raise_error("translate() fails to alloc memory for sequence string\n");
        return NULL;
    }

    if((p_ptr->name = sappend(s_ptr->name, "_protein")) == NULL){           /* 'sappend' duplicate and appen the new string */
        raise_error("translate() fails to append name\n");
        return NULL;
    }
    
    char *ptr, *new;
    ptr = s_ptr->seq;
    new = p_ptr->seq;
    
    char buf[CODONLEN+1];                                                   /* for storing the translated sequence */
    char *bufp = buf;                                                       /* pointer to the top of the buffer */
    
    struct llist *node;
    int i, j;
    for(i = j = 0; i < strlen(ptr); i++){                                      /* condition on 'strlen' is a better test condition */
        *bufp++ = ptr[i];
        if((i+1) % CODONLEN)
            continue;
        *bufp = '\0';
        
        if((node = lookup(buf)) == NULL){
            raise_error("translate() fails lookup of a node\n");
            return NULL;
        }
        
        new[j++] = *node->amm;
        printf("amm: = %c\n", *node->amm);
        // TODO: REMOVE ITEMS IN THE LIST WITH EMPTY AMMINO ACID
        bufp = buf;
    }
    
    return p_ptr;
}

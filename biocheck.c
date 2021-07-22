//
//  biocheck.c
//  
//
//  Created by Davide Colombo on 22/07/21.
//

#include "biocheck.h"

unsigned int is_dna(SEQ *s_ptr){
    return s_ptr->is_dna;
}

unsigned int is_rna(SEQ *s_ptr){
    return s_ptr->is_rna;
}

unsigned int is_pro(SEQ *s_ptr){
    return s_ptr->is_pro;
}

unsigned int is_cds(SEQ *s_ptr){
    
    if(!is_dna(s_ptr))
        return 0;
    
    char *ptr;
    ptr = s_ptr->seq;
    
    if(strlen(ptr) % CODONLEN != 0)                             /* a valid CDS must be multiple of CODONLEN */
        return 0;
    
    char start[CODONLEN+1];
    strncpy(start, ptr, CODONLEN);                              /* copy the first CODONLEN char to 'start' array */
    
    char stop[CODONLEN+1];
    strncpy_r(stop, ptr, CODONLEN);                             /* copy last CODONLEN char to 'stop' array */
    
    return (strcmp(start, "ATG") == 0 && (strcmp(stop, "TAA") == 0 ||
                                          strcmp(stop, "TGA") == 0 ||
                                          strcmp(stop, "TAG") == 0)) ? 1 : 0;
}

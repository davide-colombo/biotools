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

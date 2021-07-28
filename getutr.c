//
//  getutr.c
//  
//
//  Created by Davide Colombo on 28/07/21.
//

#include "getutr.h"

UTR_T *getutr(SEQ *s_ptr, CDS_T *cds){
    
    UTR_T *u_ptr;
    FPOS_T str5f, str3f;
    LEN_T len5f, len3f;
    
    str5f = 0UL;
    len5f = cds->strpos;
    str3f = cds->strpos + cds->len;
    len3f = strlen(s_ptr->seq) - str3f;
    
    if((u_ptr = utr_t(cds, str5f, len5f, str3f, len3f)) == NULL){
        raise_error("getutr() fails to alloc memory for 'UTR_T' object\n");
        return NULL;
    }
    
    return u_ptr;
}

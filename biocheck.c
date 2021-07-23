//
//  biocheck.c
//  
//
//  Created by Davide Colombo on 22/07/21.
//

#include <stdio.h>
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

unsigned int is_cds(SEQ *s_ptr, FPOS_T strpos){
        
    char *ptr;
    ptr = s_ptr->seq;
    
    char start[CODONLEN+1];
    char stop[CODONLEN+1];
    
    strncpy_from(start, ptr, strpos, CODONLEN);                     /* copy the first CODONLEN char to 'start' array */
    
    if(!IS_START(start)){
        printf("not start codon: %s\n", start);
        return 0;
    }
    
    taa = srch_t("TAA", CODONLEN, CODONLEN);
    tga = srch_t("TGA", CODONLEN, CODONLEN);
    tag = srch_t("TAG", CODONLEN, CODONLEN);
       
    FPOS_T i;
    FPOS_T d;
    
    FPOS_T ftaa = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftaa+CODONLEN))
        if((ftaa = sfind(ptr, taa, i)) >= 0 && ftaa <= strlen(ptr))
            if((d = ftaa - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
    
    FPOS_T ftga = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftga+CODONLEN))
        if((ftga = sfind(ptr, tga, i)) >= 0 && ftga <= strlen(ptr))
            if((d = ftga - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
    
    FPOS_T ftag = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftag+CODONLEN))
        if((ftag = sfind(ptr, tag, i)) >= 0 && ftag <= strlen(ptr))
            if((d = ftag - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
    
    printf("ftaa = %lu\n", ftaa);
    printf("ftag = %lu\n", ftag);
    printf("ftga = %lu\n", ftga);
    
    FPOS_T fpos = ftaa;
    strncpy_from(stop, ptr, ftaa, CODONLEN);
    
    if(fpos > ftga){
        fpos = ftga;
        strncpy_from(stop, ptr, ftga, CODONLEN);
    }
    
    if(fpos > ftag){
        fpos = ftag;
        strncpy_from(stop, ptr, ftag, CODONLEN);
    }
    
    printf("stop = %s\n", stop);
    
    return IS_START(start) && IS_STOP(stop);
}

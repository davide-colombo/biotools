//
//  getcds.c
//  
//
//  Created by Davide Colombo on 23/07/21.
//

#include "getcds.h"

CDS_T *getcds(SEQ *s_ptr, FPOS_T strpos){
    
    char *ptr;                                                          /* var used for code readability */
    ptr = s_ptr->seq;
    
    char start[CODONLEN+1];                                             /* the array for the start codon (+1 for '\0') */
    char stop[CODONLEN+1];                                              /* the array for the stop codon (+1 for '\0') */
    
    strncpy_from(start, ptr, strpos, CODONLEN);                         /* copy the first CODONLEN starting at 'strpos' */
    
    if(!IS_START(start)){                                                /* check valid start codon */
        raise_error("getcds() fails because 'start' is not a valid codon\n");
        return NULL;
    }
    
    FPOS_T i;                                                           /* var used for searching the SEQ->seq sequence */
    LEN_T d;                                                            /* var that stores the difference between stop codon and 'strpos' */
    
    FPOS_T ftaa = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftaa+CODONLEN))
        if((ftaa = sfind(ptr, &taa, i)) >= 0 && ftaa <= strlen(ptr))
            if((d = ftaa - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
    
    FPOS_T ftga = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftga+CODONLEN))
        if((ftga = sfind(ptr, &tga, i)) >= 0 && ftga <= strlen(ptr))
            if((d = ftga - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
    
    FPOS_T ftag = 0UL;
    for(i = strpos; !ctrl.eof; i = (ftag+CODONLEN))
        if((ftag = sfind(ptr, &tag, i)) >= 0 && ftag <= strlen(ptr))
            if((d = ftag - strpos) != 0 && d % 3 == 0)
                break;
    if(ctrl.eof)
        ctrl.eof = 0;
    
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
    
    CDS_T *c_ptr;
    if((c_ptr = cds_t(s_ptr, strpos, (fpos+CODONLEN-strpos))) == NULL){                     /* alloc memory for CDS_T object */
        raise_error("getcds() fails to alloc memory for pointer to CDS_T object\n");
        return NULL;
    }
    
    return c_ptr;
}


/* a function that takes an array of pointers to OCC objects and return the longest valid CDS sequence */
/* THE USER MUST PROVIDE OCCURRENCES OF START CODONS */

CDS_T *search_cds(SEQ *s_ptr, OCC **strocc, LEN_T cnt){
    
    CDS_T *cds, *temp;
    FPOS_T i;
    
    temp = getcds(s_ptr, (strocc[0])->fpos);
    
    for(i = 1; i < cnt; i++){
        if((cds = getcds(s_ptr, (strocc[i])->fpos)) == NULL){
            raise_error("search_cds() fails at index (%d): getcds() return NULL\n", i);
            return NULL;
        }
        if(cds->len > temp->len)
            temp = cds;
    }
    
    free((void *)cds);
    
    return temp;
}

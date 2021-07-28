//
//  getseq.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "getseq.h"

SEQ *getseq(FILE *fp){
    
    unsigned long size = INITSIZE;                                          /* the size of the arrays */
    
    char *seq;
    if((seq = alloc_chararray(size)) == NULL){                        /* alloc memory for 'char' array that stores the sequence */
        raise_error("getseq() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    char *name;
    if((name = alloc_chararray(size)) == NULL){                       /* alloc memory for 'char' array that stores the name */
        raise_error("getseq() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    char line[size];                                                        /* array in which is stored the current line */
    if(fgetline(fp, line, size) == 0 && ctrl.eof){
        raise_error("getseq() try to read the first line but fails\n");
        return NULL;
    }
    
    if(line[0] != '>'){
        raise_error("getseq() can't alloc sequence because name is missing\n");
        return NULL;
    }
    
    strcpy(name, line);                                              /* copy the line included '\0' */
    
    LEN_T len, i;
    for(i = 0; (len = fgetline(fp, line, size)) > 0; i += len){
        if(i+len >= size)
            if((seq = realloc_chararray(seq, size+=EXPAND)) == NULL){
                raise_error("getseq() try to realloc memory but fails. Target size = %lu\n", size);
                return NULL;
            }
        
        strcpy_from(seq, line, i);
        
        if(ctrl.eof)
            break;
    }
    
    SEQ *s_ptr;                                                             /* pointer to SEQ object */
    if((s_ptr = make_seq(name, seq)) == NULL){                              /* alloc memory for SEQ object */
        raise_error("getseq() can't alloc memory for 'SEQ *' object\n");
        return NULL;
    }
    
    if(strstr(s_ptr->name, "protein") != NULL)                              /* determine if is a protein */
        s_ptr->is_pro = 1;
    else if(strstr(s_ptr->name, "transcript") != NULL)                      /* determine if is a transcript */
        s_ptr->is_rna = 1;
    else
        s_ptr->is_dna = 1;
    
    ctrl.eof = 0;                                                           /* initialize global variable after its use */
    return s_ptr;
}

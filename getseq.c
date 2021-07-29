//
//  getseq.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "getseq.h"

SEQ *getseq(FILE *fp){
    
    unsigned long size = INITSIZE;                                          /* the size of the arrays */
    
    SEQ *s_ptr;                                                             /* pointer to SEQ object */
    if((s_ptr = make_seq()) == NULL){                              /* alloc memory for SEQ object */
        raise_error("getseq() can't alloc memory for 'SEQ *' object\n");
        return NULL;
    }
    
    if((s_ptr->seq = alloc_chararray(size)) == NULL){                        /* alloc memory for 'char' array that stores the sequence */
        raise_error("getseq() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    if((s_ptr->name = alloc_chararray(size)) == NULL){                       /* alloc memory for 'char' array that stores the name */
        raise_error("getseq() can't alloc memory for 'char' array\n");
        return NULL;
    }
    
    char line[size];                                                    /* array in which is stored the current line */
    if(fgetline(fp, line, size) == 0){                                  /* read a first time to understand if the line is a name */
        fgetline(fp, line, size);                                       /* read a second time to get the name: set HEADER flag to zero */
        strcpy(s_ptr->name, line);
    }
    
    LEN_T len, i;
    for(i = 0; (len = fgetline(fp, line, size)) > 0; i += len){
        if(i+len >= size){
            /* since 'realloc()' will copy the content of the string to the new memory location, we have to tell the strcpy function where the
             string ends */
            (s_ptr->seq)[i] = '\0';
            
            if((s_ptr->seq = realloc_chararray(s_ptr->seq, size+=EXPAND)) == NULL){
                raise_error("getseq() try to realloc memory but fails. Target size = %lu\n", size);
                return NULL;
            }
        }
        
        strcpy_from(s_ptr->seq, line, i);
        
        if(ctrl.eof)
            break;
    }
    
    (s_ptr->seq)[i] = '\0';                                                 /* add null character to the sequence */
    
    if(len == 0UL)                                      /* If we exit the loop because the name of a new seq was found: reset header flag */
        ctrl.header = 0;
    
    if(strstr(s_ptr->name, "protein") != NULL)                              /* determine if is a protein */
        s_ptr->is_pro = 1;
    else if(strstr(s_ptr->name, "transcript") != NULL)                      /* determine if is a transcript */
        s_ptr->is_rna = 1;
    else
        s_ptr->is_dna = 1;
    
    return s_ptr;
}

/* function that takes a FILE object and return an array of pointers to SEQ objects. FILE MUST BE ALREADY OPENED!!! */

SEQ **get_multiseq(FILE *fp){
    
    SEQ **parr;
    if((parr = (SEQ **)malloc(sizeof(SEQ *) * INITSIZE)) == NULL){
        raise_error("get_multiseq() fails to alloc memory for array of pointers to 'SEQ *': requested size is %lu\n", INITSIZE);
        return NULL;
    }
    LEN_T nseq = 0UL;
    
    while(!ctrl.eof)
        if((parr[nseq++] = getseq(fp)) == NULL){
            raise_error("get_multiseq() fails: getseq() return NULL\n");
            return parr;
        }
    
    if(ctrl.eof)
        ctrl.eof = 0;
    
    return parr;
    
}

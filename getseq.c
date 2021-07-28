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
    
    char line[size];                                                    /* array in which is stored the current line */
    if(fgetline(fp, line, size) == 0){
        fgetline(fp, line, size);                                       /* read a second time to get the name */
        strcpy(name, line);
    }
    
    /*
    if(line[0] != '>'){
        raise_error("getseq() can't alloc sequence because name is missing\n");
        return NULL;
    }*/
    
    LEN_T len, i;
    for(i = 0; (len = fgetline(fp, line, size)) > 0; i += len){
        if(len == 0)    /* break when 'fgetline()' find a header */
            break;
        
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
    
    return s_ptr;
}

/* function that takes a FILE object and return an array of pointers to SEQ objects */

SEQ **get_multiseq(FILE *fp){
    
    SEQ **parr;
    if((parr = (SEQ **)malloc(sizeof(SEQ *) * INITSIZE)) == NULL){
        raise_error("get_multiseq() fails to alloc memory for array of pointers to 'SEQ *': requested size is %lu\n", INITSIZE);
        return NULL;
    }
    LEN_T nseq = 0UL;
    
    SEQ *pseq;
    while(!ctrl.eof){
        printf("in\n");
        
        if((pseq = getseq(fp)) == NULL){
            printf("inside\n");
            raise_error("get_multiseq() fails: getseq() return NULL\n");
            return NULL;
        }
        
        //printf("name:\t%s\n", pseq->name);
        //printf("string:\t%s\n", pseq->seq);
        
        parr[nseq++] = pseq;
    }
    
    printf("nseq = %lu\n", nseq);
    //parr[nseq] = NULL;
    
    return parr;
    
}

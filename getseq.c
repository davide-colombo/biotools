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
    
    if((s_ptr = alloc_sequence()) == NULL)                                  /* alloc memory for SEQ object */
        raise_error("getseq() can't alloc memory for 'SEQ *' object\n");
    if((s_ptr->seq = alloc_chararray(size)) == NULL)                        /* alloc memory for 'char' array that stores the sequence */
        raise_error("getseq() can't alloc memory for 'char' array\n");
    if((s_ptr->name = alloc_chararray(size)) == NULL)                       /* alloc memory for 'char' array that stores the name */
        raise_error("getseq() can't alloc memory for 'char' array\n");
    
    char line[size];                                                        /* array in which is stored the current line */
    if(fgetline(fp, line, size) == 0 && ctrl.eof)
        raise_error("getseq() try to read the first line but fails\n");
    strcpy(s_ptr->name, line);                                              /* copy the line included '\0' */
    
    int i, len;
    for(i = 0; (len = fgetline(fp, line, size)) > 0; i += len){
        if(i+len >= size)
            if((s_ptr->seq = realloc_chararray(s_ptr->seq, size+=EXPAND)) == NULL)
                raise_error("getseq() try to realloc memory but fails. Target size = %lu\n", size);
        
        strcpy_from(s_ptr->seq, line, i);
        
        if(ctrl.eof)
            break;
    }
    
    return s_ptr;
}
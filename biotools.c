//
//  biotools.c
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#include <stdio.h>
#include "biotools.h"

FLAG ctrl;                      /* define a FLAG variable for */

int main(int argc, char *argv[]){
    
    FILE *fp;
    
    if(argc != 2){
        fprintf(stderr, "Usage: prog FASTA\n");
        return 1;
    }else{
        if((fp = fopen(argv[1], "r")) == NULL){
            fprintf(stderr, "error in biotools.c: can't open file at '%s'\n", argv[1]);
            return 2;
        }
    }
    
    SEQ *s_ptr = NULL;                                      /* pointer to a new sequence */
    
    if((s_ptr = getsequence(s_ptr, fp)) == NULL){
        fprintf(stderr, "error in biotools.c: can't read sequence\n");
        return 3;
    }
    
    return 0;
}

SEQ *getsequence(SEQ *s_ptr, FILE *fp){
    
    if(s_ptr == NULL){
        if((s_ptr = alloc_sequence()) == NULL){
            fprintf(stderr, "error in getsequence: can't alloc memory for SEQ *\n");
            return NULL;
        }
        
        if((s_ptr->seq = alloc_chararray(DEFAULT_SIZE)) == NULL){
            fprintf(stderr, "error in getsequence: can't alloc memory for sequence char array\n");
            return NULL;
        }
        
        if((s_ptr->name = alloc_chararray(DEFAULT_SIZE)) == NULL){
            fprintf(stderr, "error in getsequence: can't alloc memory for name char array\n");
            return NULL;
        }
    }
    
    unsigned long size = DEFAULT_SIZE;
    char line[DEFAULT_SIZE];
    
    if(fgetline(fp, line, DEFAULT_SIZE) <= 0){
        fprintf(stderr, "error in getsequence: can't read the first line of the file\n");
        return NULL;
    }
    
    strcpy(s_ptr->name, line);                          /* the library function copies the '\0' too */
    
    int i, len;
    for(i = 0; (len = fgetline(fp, line, DEFAULT_SIZE)) > 0; i += len){
        if((i+len) >= size)
            if((s_ptr->seq = __realloc(s_ptr->seq, size+=1000)) == NULL){
                fprintf(stderr, "error in getsequence: can't re-alloc memory with size %lu\n", size);
                return NULL;
            }
        __strcpy(s_ptr->seq, line, i);
        
        if(ctrl.eof)            /* this control terminate the loop: it must be done after the copy otherwise the last line is not copied */
            break;
    }
    
    return s_ptr;
}

SEQ *transcript(SEQ *s_ptr){
    int c;
    while((c = *s_ptr->seq) == ' ' || c == '\t')
        ;
    
    char *ptr;
    if((ptr = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL)
        return NULL;
    
    int i;
    char *s;
    s = s_ptr->seq;
    for(i = 0; isalpha(s[i]); i++)
        ptr[i] = (s[i] == 'T' || s[i] == 't') ? s[i]+1 : s[i];
    ptr[i] = '\0';
    
    SEQ *mrna;
    if((mrna = alloc_sequence()) == NULL)
        return NULL;
    strcpy(mrna->seq, ptr);
    strcpy(mrna->name, s_ptr->name);
    
    free((void *)ptr);                                      /* frees memory used to store the string */
    return mrna;
}

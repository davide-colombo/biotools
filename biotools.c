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

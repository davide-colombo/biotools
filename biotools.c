//
//  biotools.c
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#include <stdio.h>
#include "biotools.h"

int main(int argc, char *argv[]){
    
    FILE *fp;
    
    if(argc != 2)                                                           /* check correct usage */
        raise_error("main() detect wrong usage. Usage: prog fn\n");
    if((fp = fopen(argv[1], "r")) == NULL)                                  /* try to open the file */
        raise_error("main() can't open file at '%s'\n", argv[1]);
    
    SEQ *s_ptr;
    s_ptr = getseq(fp);                                                     /* read sequence */
    
    printf("%s\n", s_ptr->seq);
    
    return 0;
}












/*
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
    
    free((void *)ptr);
    return mrna;
}
 */

//
//  biotools.c
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#include <stdio.h>
#include "biotools.h"

char *alloc_chararray(unsigned);
void reverse(char *);
void __strcpy(char *, char *);
char *__realloc(char *, unsigned long);
SEQ *alloc_sequence(void);                              /* OK */

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
    
    SEQ *s_ptr = NULL;                                            /* pointer to a new sequence */
    
    if(getsequence(s_ptr, fp) == NULL){
        fprintf(stderr, "error in biotools.c: can't read sequence\n");
        return 3;
    }
    
    printf("back to the main\n");
    // printf("%s\n", s_ptr->seq);
    
    
    /*
    _DNA_ dna = "GAGTAGTCCCTTCGCAAGCCC";
    _DNA_ rev;
    if((rev = rev_complement(dna)) == NULL){
        fprintf(stderr, "error in biotools.c: can't compute reverse complement\n");
        return 2;
    }
    
    _RNA_ mrna;
    if((mrna = transcript(dna)) == NULL){
        fprintf(stderr, "error in biotools.c: can't transcript dna\n");
        return 3;
    }
    printf("DNA\t%s\n", dna);
    printf("RNA\t%s\n", mrna);
     
     */
    
    return 0;
}

SEQ *getsequence(SEQ *s_ptr, FILE *fp){
    
    if(s_ptr == NULL){
        s_ptr = alloc_sequence();
        s_ptr->seq = NULL;
        s_ptr->name = NULL;
    }
    
    unsigned long size = DEFAULT_SIZE;
    char *temp = alloc_chararray(size);
    
    int c, i;
    for(i = 0; (c = getc(fp)) != EOF; i++){
        if(i >= size){
            //temp[size] = '\0';
            if((temp = __realloc(temp, size+=1000)) == NULL)
                return NULL;
        }
       temp[i] = c;
    }
    printf("%s\n", temp);
    printf("i = %d\n", i);
    printf("out\n");
    printf("strlen = %lu\n", strlen(temp));
    temp[i] = '\0';
    return s_ptr;
}

SEQ *rev_complement(SEQ *s_ptr){
    int c;
    while((c = *s_ptr->seq) == ' ' || c == '\t')
        s_ptr->seq++;
    
    char *ptr;
    if((ptr = alloc_chararray(strlen(s_ptr->seq)+1)) == NULL)       /* +1 for '\0' */
        return NULL;
    
    int i;
    char *s;
    s = s_ptr->seq;
    for(i = 0; isalpha(s[i]); i++)
        ptr[i] = ((s[i] == 'A') ? s[i]+A2T :
                  (s[i] == 'T') ? s[i]-A2T :
                  (s[i] == 'C') ? s[i]+C2G : s[i]-C2G);
    ptr[i] = '\0';
    reverse(ptr);                                                   /* compute the reverse of the complement */
    
    SEQ *rev;
    if((rev = alloc_sequence()) == NULL)
        return NULL;
    strcpy(rev->seq, ptr);                                          /* copy the reverse of the complement string */
    strcpy(rev->name, s_ptr->name);                                 /* sequence name is the same */
    return rev;
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
    
    free((void *)ptr);                      /* frees memory used to store the string */
    
    return mrna;
}

char *alloc_chararray(unsigned size){
    return (char *)malloc(sizeof(char) * (size + 1));       /* +1 for '\0' */
}

void reverse(char *s){
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

char *__realloc(char *s, unsigned long sz){
    char *ptr;
    if((ptr = (char *)malloc(sizeof(char) * sz)) == NULL)
        return NULL;
    __strcpy(ptr, s);                       /* save the content of 's' in 'ptr' */
    free((void *)s);                        /* free the previous content of the array */
    return ptr;
}

void __strcpy(char *to, char *from){
    int i;
    for(i = 0; from[i]; i++)                /* loops and copy until reaches a null character */
        to[i] = from[i];
}

SEQ *alloc_sequence(void){
    return (SEQ *)malloc(sizeof(SEQ));
}

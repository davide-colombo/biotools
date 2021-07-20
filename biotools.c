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
    
    _DNA_ seq;              /* declare pointer to _DNA_ sequence */
    if((seq = getsequence(seq, fp)) == NULL){
        fprintf(stderr, "error in biotools.c: can't read sequence\n");
        return 3;
    }
    
    printf("%s\n", seq);
    
    
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

_DNA_ getsequence(_DNA_ ptr, FILE *fp){

    if((ptr = (_DNA_)alloc_chararray(DEFAULT_SIZE)) == NULL)
        return NULL;
    
    unsigned long size = DEFAULT_SIZE;
    int i;
    int c;
    for(i = 0; (c = getc(fp)) != EOF; i++){
        if(i >= size){
            size += 1000;
            _DNA_ tmp;
            if((tmp = (_DNA_)__realloc(ptr, size)) == NULL)
                return NULL;
            ptr = tmp;
        }
        ptr[i] = c;
    }
    ptr[i] = '\0';
    return ptr;
}

_DNA_ rev_complement(_DNA_ s){
    int c;
    while((c = *s) == ' ' || c == '\t')
        s++;
    
    _DNA_ ptr;
    if((ptr = (_DNA_)alloc_chararray(strlen(s)+1)) == NULL)                   /* +1 for '\0' */
        return NULL;
    
    int i;
    for(i = 0; isalpha(s[i]); i++)
        ptr[i] = ((s[i] == 'A' || s[i] == 'a') ? s[i]+A2T :
                  (s[i] == 'T' || s[i] == 't') ? s[i]-A2T :
                  (s[i] == 'C' || s[i] == 'c') ? s[i]+C2G : s[i]-C2G);
    ptr[i] = '\0';
    reverse(ptr);
    return ptr;
}

_RNA_ transcript(_DNA_ s){
    int c;
    while((c = *s) == ' ' || c == '\t')
        ;
    
    _RNA_ ptr;
    if((ptr = (_RNA_)alloc_chararray(strlen(s)+1)) == NULL)
        return NULL;
    
    int i;
    for(i = 0; isalpha(s[i]); i++)
        ptr[i] = (s[i] == 'T' || s[i] == 't') ? s[i]+1 : s[i];
    ptr[i] = '\0';
    return ptr;
}

char *alloc_chararray(unsigned size){
    return (char *)malloc(sizeof(char) * size);
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
    for(i = 0; from[i]; i++)                /* loops until reaches a null character */
        to[i] = from[i];
}

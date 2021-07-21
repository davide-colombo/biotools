//
//  biotools.c
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#include <stdio.h>
#include "biotools.h"

void reverse(char *);
void __strcpy(char *, char *, unsigned);
char *__realloc(char *, unsigned long);

SEQ *alloc_sequence(void);
char *alloc_chararray(unsigned);
int fgetline(FILE *, char *, unsigned long);

FLAG ctrl;

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
    
    /*
    printf("%s\n", s_ptr->seq);
    printf("name: %s\n", s_ptr->name);
    */
    
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
    
    free((void *)ptr);                                      /* frees memory used to store the string */
    return mrna;
}

char *alloc_chararray(unsigned size){
    return (char *)malloc(sizeof(char) * (size+1));         /* +1 for '\0' */
}

void reverse(char *s){
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

char *__realloc(char *s, unsigned long size){
    char *ptr;
    if((ptr = alloc_chararray(size)) == NULL)
        return NULL;
    __strcpy(ptr, s, 0);                                    /* save the content of 's' in 'ptr' */
    free((void *)s);                                        /* free the previous content of the array */
    return ptr;
}

void __strcpy(char *to, char *from, unsigned start){
    int i, j;
    for(i = start, j = 0; from[j]; i++, j++)                /* loops and copy until reaches a null character */
        to[i] = from[j];
}

SEQ *alloc_sequence(void){
    return (SEQ *)malloc(sizeof(SEQ));
}

int fgetline(FILE *fp, char *s, unsigned long lim){
    extern FLAG ctrl;
    
    int c, i;
    for(i = 0; lim-- > 0 && (c = getc(fp)) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    
    if(c == EOF)
        ctrl.eof = 1;
    
    return i;
}

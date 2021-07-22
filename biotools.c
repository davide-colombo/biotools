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
    printf("name:\t%s\n", s_ptr->name);
    printf("string:\t%s\n", s_ptr->seq);
    
    SEQ *r_ptr;
    r_ptr = revcomp(s_ptr);                                                 /* reverse complement */
    printf("name:\t%s\n", r_ptr->name);
    printf("revcom:\t%s\n", r_ptr->seq);
    
    SEQ *t_ptr;
    t_ptr = transcript(s_ptr);                                              /* compute transcription of gene sequence */
    printf("name:\t%s\n", t_ptr->name);
    printf("mRNA:\t%s\n", t_ptr->seq);
    
    printf("len:\t%lu\n", genelen(s_ptr));                                  /* get gene length */
    
    printf("GC%%:\t%.4g\n", gcperc(s_ptr));                                 /* gc percentage */
    
/* ================================================ search a plain text sequence ================================================ */
    
    char tosearch[] = "ATG";                                                /* string to search within SEQ->str sequence */
    SRCH_T *targ;
    targ = srch_t(tosearch, strlen(tosearch), strlen(tosearch));            /* minlen = maxlen = strlen() */
    
    OCC **fptr;
    LEN_T nocc;
    fptr = findocc(&nocc, s_ptr, targ);                                     /* find occurrences and get the count */
    
    LEN_T i;
    for(i = 0; i < nocc; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        
    printf("nocc:\t%lu\n", nocc);
    
/* ================================================ search a repeated sequence ================================================ */
    
    char repseq[] = "T";
    SRCH_T *reptarg;
    reptarg = srch_t(repseq, 3UL, UNSET);                                   /* minlen = 3 and maxlen = UNSET */
    
    OCC **fptr1;
    LEN_T nocc1;
    
    fptr1 = findocc(&nocc1, s_ptr, reptarg);
    
    for(i = 0; i < nocc1; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, reptarg->str, (*(fptr1+i))->fpos);
        
    printf("nocc1:\t%lu\n", nocc1);
    
    return 0;
}

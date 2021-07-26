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
    printf("is_dna = %ud\tis_rna = %ud\tis_pro = %ud\n",
           s_ptr->is_dna, s_ptr->is_rna, s_ptr->is_pro);
    
    if(is_dna(s_ptr)){                                                      /* reveverse complement is computed only if SEQ is dna */
        SEQ *r_ptr;
        r_ptr = revcomp(s_ptr);                                             /* reverse complement */
        printf("name:\t%s\n", r_ptr->name);
    printf("revcom:\t%s\n", r_ptr->seq);
    }
    
/* ================================================ is valid cds? ================================================ */
    
    CDS_T *c_ptr;
    if((c_ptr = getcds(s_ptr, 62UL)) == NULL)
        raise_error("main() fails to compute CDS\n");
    printf("str: %s\tat %lu\tstp: %s\tlen: %lu\tend: %lu\n", c_ptr->str, c_ptr->strpos, c_ptr->stp, c_ptr->len, (c_ptr->strpos+c_ptr->len));
    
    SEQ *t_ptr;
    if(is_dna(s_ptr)){
        t_ptr = transcript(s_ptr);                                          /* compute transcription of gene sequence */
        printf("name:\t%s\n", t_ptr->name);
        printf("mRNA:\t%s\n", t_ptr->seq);
    }
    
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
    for(i = 0; i < nocc; i++){
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        /*if(is_cds(s_ptr, (*(fptr+i))->fpos))
            printf("(%lu) valid cds starts at %lu\n", i, (*(fptr+i))->fpos);*/
    }
        
    printf("nocc:\t%lu\n", nocc);
    
/* ================================================ search a repeated sequence ================================================ */
    
    free_srch_t(targ);
    
    free_occptr_arr(fptr);
    
    char repseq[] = "T";
    targ = srch_t(repseq, 3UL, UNSET);
    fptr = findocc(&nocc, s_ptr, targ);
    
    for(i = 0; i < nocc; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        
    printf("nocc:\t%lu\n", nocc);
    
    
/* ================================================ TOKENIZE STRING ================================================ */
    
    FILE *fp1;
    
    if((fp1 = fopen("gcode.txt", "r")) == NULL)                      /* open the file in read mode */
        return 1;
    
    struct llist *node;
    
    while((node = getnode(fp1)) != NULL){
        printf("cdn: %s\n", node->cdn);
        printf("amm: %s\n", node->amm);
        printf("is_start: %d\n", node->is_start);
        printf("is_stop: %d\n", node->is_stop);
        printf(" ============================================================ \n");
    }
    
    fclose(fp1);
    
    return 0;
}

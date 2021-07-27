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
    
/* ================================================ READ THE SEQUENCE ================================================ */
    
    SEQ *s_ptr;
    s_ptr = getseq(fp);
    if(!ctrl.error){
        printf("name:\t%s\n", s_ptr->name);
        printf("string:\t%s\n", s_ptr->seq);
        printf("is_dna = %ud\tis_rna = %ud\tis_pro = %ud\n",
               s_ptr->is_dna, s_ptr->is_rna, s_ptr->is_pro);
    }else
        ctrl.error = 0;

/* ================================================ REVERSE COMPLEMENT ================================================ */
    
    SEQ *r_ptr;
    r_ptr = revcomp(s_ptr);
    if(!ctrl.error){
        printf("name:\t%s\n", r_ptr->name);
        printf("revcom:\t%s\n", r_ptr->seq);
    }else
        ctrl.error = 0;
    
/* ================================================ is valid cds? ================================================ */
    
    CDS_T *c_ptr;
    c_ptr = getcds(s_ptr, 62UL);
    if(!ctrl.error)
        printf("str: %s\tat %lu\tstp: %s\tlen: %lu\tend: %lu\n",
               c_ptr->str, c_ptr->strpos, c_ptr->stp, c_ptr->len, (c_ptr->strpos+c_ptr->len));
    else
        ctrl.error = 0;
    
/* ================================================ TRANSCRIPTION ================================================ */
    
    SEQ *t_ptr;
    t_ptr = transcript(s_ptr);
    if(!ctrl.error){
        printf("name:\t%s\n", t_ptr->name);
        printf("mRNA:\t%s\n", t_ptr->seq);
    }else
        ctrl.error = 0;
    
/* ================================================ GENE INFO ================================================ */
    
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
    
    
/* ================================================ READ THE GENETIC CODE ================================================ */
    
    FILE *fp1;
    
    if((fp1 = fopen("gcode.txt", "r")) == NULL)                      /* open the file in read mode */
        return 1;
    
    struct llist *node;
    for(i = 0; (node = fgetnode_tok(fp1)) != NULL; i++){
        install_or_error(node);
        if(ctrl.error){
            raise_error("main() can't install node in the linked list\n");
            ctrl.error = 0;
            break;
        }
    }
    
    free((void *) node);
    
    int j;
    for(i = j = 0; i < HASHSIZE; i++){
        if((node = codontab[i]) == NULL)
            continue;
        
        for(; node != NULL; node = node->next, j++){
            printf("cdn: %s\n", node->cdn);
            printf("amm: %s\n", node->amm);
            printf("is_start: %d\n", node->is_start);
            printf("is_stop: %d\n", node->is_stop);
            printf(" ============================================================ \n");
        }
    }
    
    printf("ncodons = %d\n", j);
    
    fclose(fp1);
    
/* ================================================ TRANSLATE ================================================ */
    
    SEQ *pro_ptr;
    pro_ptr = translate(s_ptr, c_ptr);
    if(!ctrl.error){
        printf("translated seq: %s\n", pro_ptr->name);
        for(i = 0; i < strlen(pro_ptr->seq); i++)
            printf("%c", (pro_ptr->seq)[i]);
    }else
        ctrl.error = 0;
    
    return 0;
}

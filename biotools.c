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
    
/* ================================================ READ THE GENETIC CODE ================================================ */
    
    FILE *fp1;
    
    if((fp1 = fopen("gcode.txt", "r")) == NULL)                      /* open the file in read mode */
        return 1;
    
    LEN_T i;
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
    
    /* THIS SNIPPET OF CODE PRINTS ON THE STANDARD OUTPUT THE GENETIC CODE
     
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
    */
    
    fclose(fp1);
    
/* ================================================ GET MULTIPLE SEQUENCES WITHIN A FILE ================================================ */
    
    SEQ **ptrarr;
    ptrarr = get_multiseq(fp);                  /* fill the sequence array of pointers */
    fclose(fp);                                 /* close the file */
    
    int k;
    if(!ctrl.error){
        for(k = 0; ptrarr[k]; k++){
            printf("name:\t%s\n", (ptrarr[k])->name);
            printf("string:\t%s\n", (ptrarr[k])->seq);
            printf("is_dna = %ud\tis_rna = %ud\tis_pro = %ud\n",
                   (ptrarr[k])->is_dna, (ptrarr[k])->is_rna, (ptrarr[k])->is_pro);
            printf("\n\n\n\n");
        }
    }else
        return 2;
    
    SEQ *gene = ptrarr[0];                      /* gene sequence object */
    SEQ *trs1 = ptrarr[1];                      /* transcript sequence object */
    
/* ================================================ REVERSE COMPLEMENT ================================================ */
    
    SEQ *r_ptr;
    r_ptr = revcomp(gene);
    if(!ctrl.error){
        printf("name:\t%s\n", r_ptr->name);
        printf("revcom:\t%s\n", r_ptr->seq);
    }else
        ctrl.error = 0;
    
/* ================================================ TRANSCRIPTION ================================================ */
    
    SEQ *t_ptr;
    t_ptr = transcript(gene);
    if(!ctrl.error){
        printf("name:\t%s\n", t_ptr->name);
        printf("mRNA:\t%s\n", t_ptr->seq);
    }else
        ctrl.error = 0;
    
/* ================================================ GENE INFO ================================================ */
    
    printf("len:\t%lu\n", genelen(gene));                                  /* get gene length */
    
    printf("GC%%:\t%.4g\n", gcperc(gene));                                 /* gc percentage */
    
/* ================================================ search a plain text sequence ================================================ */
    
    char tosearch[] = "ATG";                                                /* string to search within SEQ->str sequence */
    SRCH_T *targ;
    targ = srch_t(tosearch, strlen(tosearch), strlen(tosearch));            /* minlen = maxlen = strlen() */
    
    OCC **fptr;
    LEN_T nocc;
    fptr = findocc(&nocc, trs1, targ);                                      /* find occurrences and get the count */
    
    for(i = 0; i < nocc; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        
    printf("nocc:\t%lu\n", nocc);
  
/* ================================================ search a repeated sequence ================================================ */
    
    CDS_T *c_ptr;
    if(nocc != 0){
        c_ptr = search_cds(trs1, fptr, nocc);
        if(!ctrl.error){
            printf("found at: %lu\tlen: %lu\tend: %lu\n",
                c_ptr->strpos, c_ptr->len, (c_ptr->strpos+c_ptr->len));
        }
        else
            ctrl.error = 0;
    }
    
/* ================================================ search a repeated sequence ================================================ */
    
    free_srch_t(targ);
    
    free_occptr_arr(fptr);
    
    char repseq[] = "T";
    targ = srch_t(repseq, 3UL, UNSET);
    fptr = findocc(&nocc, trs1, targ);                                              /* 'findocc()' already initialize 'nocc' */
    
    printf("In: %s\n", trs1->name);
    for(i = 0; i < nocc; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        
    printf("nocc:\t%lu\n", nocc);
    
/* ================================================ TRANSLATE ================================================ */
    
    SEQ *pro_ptr;
    pro_ptr = translate(trs1, c_ptr);
    if(!ctrl.error){
        printf("translated seq: %s\n", pro_ptr->name);
        for(i = 0; i < strlen(pro_ptr->seq); i++)
            printf("%c", (pro_ptr->seq)[i]);
        printf("\n");
    }else
        ctrl.error = 0;
    
    
/* ================================================ UTR REGIONS ================================================ */
    
    UTR_T *u_ptr;
    u_ptr = getutr(trs1, c_ptr);
    if(!ctrl.error){
        printf("5' - strpos = %lu\tlen = %lu\n", u_ptr->str5f, u_ptr->len5f);
        printf("3' - strpos = %lu\tlen = %lu\n", u_ptr->str3f, u_ptr->len3f);
    }else
        ctrl.error = 0;
    
    
/* ================================================ FREE MEMORY ================================================ */
    
    for(k = 0; ptrarr[k]; k++)                  /* free all the sequences read from the file passed as argument */
        free_seq(ptrarr[k]);
    free((void *)ptrarr);
    
    free_seq(r_ptr);                            /* free reverse complement sequence (if any) */
    free_seq(t_ptr);                            /* free transcript sequence (if any) */
    
    free_srch_t(targ);                          /* free target object */
    
    free_occptr_arr(fptr);                      /* free array of occurrences */
    
    free_cds_t(c_ptr);                          /* free CDS sequence */
    free_seq(pro_ptr);                          /* free translated protein sequence */
    
    return 0;
}

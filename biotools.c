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
    /*
    s_ptr = getseq(fp);
    if(!ctrl.error){
        printf("name:\t%s\n", s_ptr->name);
        printf("string:\t%s\n", s_ptr->seq);
        printf("is_dna = %ud\tis_rna = %ud\tis_pro = %ud\n",
               s_ptr->is_dna, s_ptr->is_rna, s_ptr->is_pro);
    }else
        return 1;*/

    
/* ================================================ GET MULTIPLE SEQUENCES WITHIN A FILE ================================================ */
    
    SEQ **ptrarr;
    ptrarr = get_multiseq(fp);
    
    int k;
    if(!ctrl.error){
        /*
        printf("*ptrarr == NULL? %s\n", (*ptrarr == NULL) ? "TRUE" : "FALSE");
        for(k = 0; k < 2; k++){
            printf("name:\t%s\n", (ptrarr[k])->name);
            printf("string:\t%s\n", (ptrarr[k])->seq);
            printf("is_dna = %ud\tis_rna = %ud\tis_pro = %ud\n",
                   (ptrarr[k])->is_dna, (ptrarr[k])->is_rna, (ptrarr[k])->is_pro);
            printf("\n\n\n\n");
        }*/
    }else
        return 2;
    
    
    return 0;
    
/* ================================================ REVERSE COMPLEMENT ================================================ */
    
    SEQ *r_ptr;
    r_ptr = revcomp(s_ptr);
    if(!ctrl.error){
        printf("name:\t%s\n", r_ptr->name);
        printf("revcom:\t%s\n", r_ptr->seq);
    }else
        ctrl.error = 0;
    
/* ================================================ is valid cds? ================================================ */
    /* this snippet of code can be removed */
    
    /*
    CDS_T *c_ptr;
    c_ptr = getcds(s_ptr, 1306UL);
    if(!ctrl.error)
        printf("found at: %lu\tlen: %lu\tend: %lu\n",
            c_ptr->strpos, c_ptr->len, (c_ptr->strpos+c_ptr->len));
    else
        ctrl.error = 0;
    */
    
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
    for(i = 0; i < nocc; i++)
        printf("(%lu) found occurrence of '%s' at %lu\n",
               i, targ->str, (*(fptr+i))->fpos);
        
    printf("nocc:\t%lu\n", nocc);
  
/* ================================================ search a repeated sequence ================================================ */
    
    CDS_T *c_ptr;
    c_ptr = search_cds(s_ptr, fptr, nocc);
    if(!ctrl.error){
        printf("found at: %lu\tlen: %lu\tend: %lu\n",
            c_ptr->strpos, c_ptr->len, (c_ptr->strpos+c_ptr->len));
    }
    else
        ctrl.error = 0;
    
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
    
    /*
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
    
/* ================================================ TRANSLATE ================================================ */
    
    SEQ *pro_ptr;
    pro_ptr = translate(s_ptr, c_ptr);
    if(!ctrl.error){
        printf("translated seq: %s\n", pro_ptr->name);
        for(i = 0; i < strlen(pro_ptr->seq); i++)
            printf("%c", (pro_ptr->seq)[i]);
        printf("\n");
    }else
        ctrl.error = 0;
    
    
/* ================================================ UTR REGIONS ================================================ */
    
    UTR_T *u_ptr;
    u_ptr = getutr(s_ptr, c_ptr);
    if(!ctrl.error){
        printf("5' - strpos = %lu\tlen = %lu\n", u_ptr->str5f, u_ptr->len5f);
        printf("3' - strpos = %lu\tlen = %lu\n", u_ptr->str3f, u_ptr->len3f);
    }else
        ctrl.error = 0;
    
    
    return 0;
}

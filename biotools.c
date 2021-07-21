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
    
    STAT_T cnt;
    cnt = scount(s_ptr, "ATG");                                             /* count 'ATG' occurrences in sequence */
    printf("cnt:\t%lu\n", cnt);
    
    printf("len:\t%lu\n", genelen(s_ptr));                                  /* get gene length */
    
    printf("gc%%:\t%.4g\n", gcperc(s_ptr));                                 /* gc percentage */
    
    printf("T>3:\t%lu\n", repcount(s_ptr, 'T', 3U));                        /* count number of times in which T is repeated more than 3 times */
    
    OCC **fptr;
    fptr = findocc(s_ptr, "ATG");
    
    int i;
    for(i = 0; *(fptr+i) != NULL; i++)
        printf("(%d) found occurrence of '%s' at %lu\n", i, "ATG", (*(fptr+i))->strpos);
        
    return 0;
}

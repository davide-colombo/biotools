//
//  biotypes.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef biotypes_h
#define biotypes_h

/* a structure that define a FASTA sequence object */

typedef struct seq {
    char *name;
    char *seq;
    unsigned int is_dna : 1;
    unsigned int is_rna : 1;
    unsigned int is_pro : 1;
} SEQ;

/* a structure that defines some useful flags */

typedef struct flag {
    unsigned int eof : 1;
} FLAG;

/* define a type for position within a sequence string */

typedef unsigned long FPOS_T;

/* define a type for the length of a sequence string */

typedef unsigned long LEN_T;

/* define a type for saving occurrences within a SEQ object */

typedef struct occurrence {
    FPOS_T fpos;                            /* tells where the match is starting from index 0 */
    FPOS_T flen;                            /* tells how much is long the match */
} OCC;

/* define a type for performing a search within a sequence */

typedef struct search {
    char *str;                              /* string to search */
    LEN_T minlen;                           /* minimum length of the string to search */
    LEN_T maxlen;                           /* maximum length of the string to search (IF ANY) */
    LEN_T curlen;                           /* true length of the found string */
} SRCH_T;

/* define a type for CDS */

typedef struct cds {
    char *str;                              /* start codon */
    char *stp;                              /* stop codon */
    FPOS_T strpos;                          /* starting position */
    LEN_T len;                              /* length of the sequence */
} CDS_T;


#endif /* biotypes_h */

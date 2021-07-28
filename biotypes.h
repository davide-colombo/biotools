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
    unsigned int error : 1;
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

// TODO: refactor the 'CDS_T' type to add 'SEQ *' object

typedef struct cds {
    SEQ *seq;                               /* the sequence to which this 'CDS_T' object correspond to */
    FPOS_T strpos;                          /* starting position */
    LEN_T len;                              /* length of the sequence */
} CDS_T;

/* define a type for codon-aminoacid translation */

struct llist {
    struct llist *next;                     /* pointer to next element of the linked list */
    char *cdn;                              /* codon name */
    char *amm;                              /* amminoacid associate with this codon */
    unsigned int is_start : 1;              /* whether this codon is a start codon */
    unsigned int is_stop : 1;               /* whether this codon is a stop codon */
};

/* define a type for the 5' - 3' untranslated regions */

typedef struct utr{
    CDS_T *cds;                             /* pointer to 'CDS_T' object to which the utr regions are referred to */
    FPOS_T str5f;                           /* start position of the 5' UTR sequence*/
    LEN_T len5f;                            /* length of the 5' UTR sequence */
    FPOS_T str3f;                           /* start position of the 3' UTR sequence */
    LEN_T len3f;                            /* length of the 3' UTR sequence */
} UTR_T;


#endif /* biotypes_h */

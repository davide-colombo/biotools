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
} SEQ;

/* a structure that defines some useful flags */

typedef struct flag {
    unsigned int eof : 1;
} FLAG;

/* define a type for statistical values */

typedef unsigned long STAT_T;

/* define a type for saving occurrences within a SEQ object */

typedef struct occurrence {
    STAT_T fpos;                            /* tells where the match is starting from index 0 */
    STAT_T flen;                            /* tells how much is long the match */
} OCC;

#endif /* biotypes_h */

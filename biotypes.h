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

#endif /* biotypes_h */

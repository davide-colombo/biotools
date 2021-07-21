//
//  biotools.h
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#ifndef biotools_h
#define biotools_h

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_SIZE 100
#define A2T ('t'-'a')                   /* symbolic constant that allow to switch from 'A' to 'T' and vice versa */
#define C2G ('g'-'c')                   /* symbolic constant that allow to switch from 'C' to 'G' and vice versa */

typedef struct dna {
    char *name;
    char *seq;
} SEQ;

SEQ *rev_complement(SEQ *);             /* take a sequence and return the reverse complement of that sequence */
SEQ *getsequence(SEQ *, FILE *);        /* read the FILE and return a new sequence */
SEQ *transcript(SEQ *);                 /* take a DNA sequence and return an RNA sequence */

#endif /* biotools_h */

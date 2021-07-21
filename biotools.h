//
//  biotools.h
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#ifndef biotools_h
#define biotools_h

#include "biotypes.h"                   /* include types: !!! THIS MUST BE DONE BEFORE INCLUDING OTHER FILES THAT USES THIS ONE !!! */
#include "bioconst.h"                   /* include constant: !!! THIS MUST BE DONE BEFORE INCLUDING OTHER FILES THAT USES THIS ONE !!! */
#include "bioerr.h"                     /* include error function */
#include "biostr.h"                     /* define functions for string manipulation */
#include "allocator.h"                  /* define functions for handling dynamically allocation of the memory */
#include "revcomp.h"                    /* define function for computing the reverse complement of a SEQ object */
#include "getseq.h"                     /* define function for creating a SEQ object from a FILE object */


SEQ *transcript(SEQ *);                 /* take a DNA sequence and return an RNA sequence */

#endif /* biotools_h */

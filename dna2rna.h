//
//  dna2rna.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef dna2rna_h
#define dna2rna_h

#include <string.h>
#include <ctype.h>
#include "biotypes.h"
#include "bioconst.h"
#include "bioerr.h"
#include "allocator.h"
#include "biocheck.h"

SEQ *transcript(SEQ *s_ptr);                    /* transcription process applied to 's_ptr->seq' */

#endif /* dna2rna_h */

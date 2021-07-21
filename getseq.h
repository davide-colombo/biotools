//
//  getseq.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef getseq_h
#define getseq_h

#include <string.h>
#include "biotypes.h"
#include "bioconst.h"
#include "bioerr.h"
#include "biostr.h"
#include "allocator.h"

#include "biovar.h"
extern FLAG ctrl;

SEQ *getseq(FILE *);

#endif /* getseq_h */

//
//  biocheck.h
//  
//
//  Created by Davide Colombo on 22/07/21.
//

#ifndef biocheck_h
#define biocheck_h

#include <string.h>
#include "biotypes.h"
#include "bioconst.h"
#include "biostr.h"
#include "biovar.h"
extern SRCH_T taa, tga, tag;
extern FLAG ctrl;

unsigned int is_dna(SEQ *);
unsigned int is_rna(SEQ *);
unsigned int is_pro(SEQ *);
unsigned int is_cds(SEQ *, FPOS_T strpos);

#endif /* biocheck_h */

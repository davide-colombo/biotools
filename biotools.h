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
#include "dna2rna.h"                    /* define function for converting DNA seq into RNA seq */
#include "biostat.h"                    /* define functions for computing useful insights about SEQ objects */
#include "biocheck.h"                   /* define functions for understanting type and check validity of SEQ objects */
#include "getcds.h"                     /* define function for manipulating CDS_T objects */
#include "llist.h"                      /* define a set of function for manipulate linked list */
#include "filemanager.h"                /* define functions for reading files */
#include "translate.h"                  /* define a function for biological translation (mRNA -> DNA) */
#include "getutr.h"                     /* define a function for getting the UTR regions of a sequence */

extern struct llist *codontab[];
extern FLAG ctrl;

#endif /* biotools_h */

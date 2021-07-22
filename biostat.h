//
//  biostat.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef biostat_h
#define biostat_h


#include "biotypes.h"
#include "bioconst.h"
#include "bioerr.h"
#include "biostr.h"
#include "allocator.h"

#include "biovar.h"
FLAG ctrl;

STAT_T genelen(SEQ *s_ptr);                                             /* return strlen of 's_ptr->seq' */
double gcperc(SEQ *s_ptr);                                              /* return 'G+C / (A+C+G+T)' */
OCC **findocc(unsigned long *cnt, SEQ *s_ptr, SRCH_T *targ);

#endif /* biostat_h */

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
#include "biostr.h"

#include "biovar.h"
FLAG ctrl;

STAT_T scount(SEQ *, char *);
STAT_T repcount(SEQ *, char, unsigned);
STAT_T genelen(SEQ *);
double gcperc(SEQ *);

#endif /* biostat_h */

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

STAT_T scount(SEQ *s_ptr, char *s);                                     /* search occurrences of 's' within 's_ptr->seq' */
STAT_T repcount(SEQ *s_ptr, char c, unsigned minlen);                   /* search occurrences of 'c' at least as long as minlen in 's_ptr->seq' */
STAT_T genelen(SEQ *s_ptr);                                             /* return strlen of 's_ptr->seq' */
double gcperc(SEQ *s_ptr);                                              /* return 'G+C / (A+C+G+T)' */

#endif /* biostat_h */

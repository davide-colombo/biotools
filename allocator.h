//
//  allocator.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef allocator_h
#define allocator_h

#include <stdlib.h>
#include <string.h>
#include "biotypes.h"
#include "biostr.h"

SRCH_T *srch_t(char *s, LEN_T min, LEN_T max);
SRCH_T *alloc_srch(void);
OCC **alloc_occptr_arr(LEN_T size);
OCC *alloc_occ(void);
SEQ *alloc_sequence(void);
char *alloc_chararray(LEN_T size);
char *realloc_chararray(char *, LEN_T size);

#endif /* allocator_h */

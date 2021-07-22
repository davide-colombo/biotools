//
//  allocator.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef allocator_h
#define allocator_h

#include <stdlib.h>
#include "biotypes.h"
#include "biostr.h"

OCC **alloc_occptr_arr(unsigned size);
OCC *alloc_occ(void);
SEQ *alloc_sequence(void);
char *alloc_chararray(unsigned size);
char *realloc_chararray(char *, unsigned long);

#endif /* allocator_h */

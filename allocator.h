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

SEQ *alloc_sequence(SEQ *);
char *alloc_chararray(unsigned);
char *realloc_chararray(char *, unsigned long);

#endif /* allocator_h */

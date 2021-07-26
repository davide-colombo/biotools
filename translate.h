//
//  translate.h
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#ifndef translate_h
#define translate_h

#include <string.h>
#include "biotypes.h"
#include "bioconst.h"
#include "biocheck.h"
#include "allocator.h"
#include "biostr.h"

#include "biovar.h"
extern struct llist *codontab[];

SEQ *translate(SEQ *s_ptr, CDS_T *cds);

#endif /* translate_h */

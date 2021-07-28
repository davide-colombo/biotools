//
//  getutr.h
//  
//
//  Created by Davide Colombo on 28/07/21.
//

#ifndef getutr_h
#define getutr_h

#include <string.h>
#include "biotypes.h"
#include "bioconst.h"
#include "biostr.h"
#include "allocator.h"
#include "bioerr.h"

#include "biovar.h"
extern FLAG ctrl;

UTR_T *getutr(SEQ *s_ptr, CDS_T *cds);

#endif /* getutr_h */

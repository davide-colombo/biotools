//
//  getcds.h
//  
//
//  Created by Davide Colombo on 23/07/21.
//

#ifndef getcds_h
#define getcds_h

#include "biotypes.h"
#include "bioconst.h"
#include "allocator.h"
#include "biostr.h"
#include "bioerr.h"

#include "biovar.h"
extern SRCH_T taa, tga, tag;
extern FLAG ctrl;

CDS_T *getcds(SEQ *, FPOS_T strpos);

#endif /* getcds_h */

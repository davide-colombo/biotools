//
//  biovar.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef biovar_h
#define biovar_h

#include "biotypes.h"
#include "bioconst.h"
#include "allocator.h"

FLAG ctrl;                                              /* FLAG variable to communicate between caller and callee */

SRCH_T *taa, *tga, *tag;                                /* define pointers to 'SRCH_T' object that correspond to STOP codon */

#endif /* biovar_h */

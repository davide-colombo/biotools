//
//  bioerr.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef bioerr_h
#define bioerr_h

#include <stdlib.h>                      /* for exit(int) */
#include <stdio.h>
#include <stdarg.h>
#include "biotypes.h"
#include "biovar.h"
extern FLAG ctrl;

void raise_error(char *msg, ...);

#endif /* bioerr_h */

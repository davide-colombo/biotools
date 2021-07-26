//
//  filemanager.h
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#ifndef filemanager_h
#define filemanager_h

#include <stdio.h>

#include "biotypes.h"
#include "bioconst.h"
#include "biovar.h"
#include "biostr.h"
#include "llist.h"

struct llist *readgcode(void);

#endif /* filemanager_h */

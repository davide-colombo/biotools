//
//  llist.h
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#ifndef llist_h
#define llist_h

#include "biotypes.h"
#include "bioconst.h"
#include "biovar.h"
#include "biostr.h"

unsigned hash(char *str);
struct llist *lookup(char *str);
struct llist *install(char *name, char *defn);

#endif /* llist_h */

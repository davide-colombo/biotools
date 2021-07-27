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

extern FLAG ctrl;

unsigned hash(char *str);
struct llist *lookup(char *str);
struct llist *install_or_error(struct llist *node);

#endif /* llist_h */

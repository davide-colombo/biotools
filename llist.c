//
//  llist.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include "llist.h"

/* function that return a positive integer that correspond to the position to start to search in the list */

unsigned hash(char *s){
    unsigned hashval;
    
    for(hashval = 0; *s; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* function that return pointer to the element at index 'hashval' or NULL if not exist */

struct llist *lookup(char *s){
    
    struct llist *ptr;
    
    for(ptr = codontab[hash(s)]; ptr != NULL; ptr = ptr->next)
        if(strcmp(s, ptr->cdn) == 0)
            return ptr;

    return NULL;
}

/* function for storing values within the table. The new element is inserted at 'hashval' */

struct llist *install_or_error(struct llist *node){
    
    unsigned hashval;
    
    if(lookup(node->cdn) == NULL){                                      /* if 'lookup()' fails we need to add */
        hashval = hash(node->cdn);                                      /* compute the hashval given the 'name' char array */
        node->next = codontab[hashval];                                 /* bound the next node of the new node to the one at 'hashval' */
        codontab[hashval] = node;                                       /* insert the new node */
    }else
        ctrl.error = 1;                                                 /* if already exist, there's an error in the genetic code */
    
    return node;
}

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
        hashval = *s + (N_CODONS-1) * hashval;
    return hashval % N_CODONS;
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

struct llist *install(char *name, char *defn){
    
    struct llist *new;
    unsigned hashval;
    
    if((new = lookup(name)) == NULL){
        new = (struct llist *)malloc(sizeof(*new));
        if(new == NULL || (new->cdn = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        new->next = codontab[hashval];
        codontab[hashval] = new;
    }else
        free((void *) new->amm);
    if((new->amm = strdup(defn)) == NULL)
        return NULL;
    
    return new;
}

//
//  filemanager.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include "filemanager.h"

struct llist *getnode(FILE *fp){
    
    if(ctrl.eof){
        ctrl.eof = 0;
        return NULL;
    }
    
    struct llist *ptr;
    if((ptr = (struct llist *)malloc(sizeof(*ptr))) == NULL)
        return NULL;
    ptr->cdn = alloc_chararray(CODONLEN);
    ptr->amm = alloc_chararray(1);
    *ptr->cdn = *ptr->amm = '\0';                           /* set this to '\0' for understanding if already set the value */
    
    char line[INITSIZE];
    char *token;
    
    fgetline(fp, line, INITSIZE);
    
    while((token = strtok(line, "\t")) != NULL){
        if(isalpha(token[0]) && !*ptr->cdn)
            ptr->cdn = strdup(token);
        else if(isalpha(token[0]) && !*ptr->amm)
            ptr->amm = strdup(token);
        else if(isdigit(token[0]) && ptr->is_start == 0)
            ptr->is_start = atoi(token);
        else
            ptr->is_stop = atoi(token);
    }
    
    return ptr;
}

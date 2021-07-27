//
//  filemanager.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include "filemanager.h"

struct llist *fgetnode_tok(FILE *fp){
    
    if(ctrl.eof){                                           /* when enter the function and find EOF (setted by 'fgetline()') end and reset */
        ctrl.eof = 0;
        return NULL;
    }
    
    struct llist *ptr;
    if((ptr = (struct llist *)malloc(sizeof(*ptr))) == NULL)    /* alloc memory for the next node in the list */
        return NULL;
    
    ptr->cdn = alloc_chararray(CODONLEN);
    ptr->amm = alloc_chararray(1);
    *ptr->cdn = *ptr->amm = '\0';                           /* set this to '\0' for understanding if already set the value */
    
    unsigned start_set = 0;                                 /* a flag used to understand whether the 'is_start' flag is set */
    
    char line[INITSIZE];
    char *token;
    
    fgetline(fp, line, INITSIZE);                           /* read next valid line from the file */
    
    while((token = strtok(line, "\t")) != NULL){
        if(isalpha(token[0]) && !*ptr->cdn)                 /* is a codon name */
            ptr->cdn = strdup(token);
        else if(isalpha(token[0]) && !*ptr->amm)            /* is amino acid name*/
            ptr->amm = strdup(token);
        else if(isdigit(token[0]) && !start_set){           /* is 'is_start' flag */
            ptr->is_start = atoi(token);
            start_set = 1;
        }else
            ptr->is_stop = atoi(token);                     /* is 'is_stop' flag */
    }
    
    return ptr;
}

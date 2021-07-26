//
//  filemanager.c
//  
//
//  Created by Davide Colombo on 26/07/21.
//

#include <stdio.h>
#include "filemanager.h"

struct llist *readgcode(void){
    
    struct llist *ptr;
    FILE *fp;
    
    if((fp = fopen("gcode.txt", "r")) == NULL)                      /* open the file in read mode */
        return NULL;
    
    char line[INITSIZE];
    int i = 0;
    char *token;
    while(!ctrl.eof){                                               /* fgetline() function sets the 'ctrl.eof' flag to 1 when ends */
        fgetline(fp, line, INITSIZE);                               /* read the next line in the file */
        printf("(%d) line: %s\n", i, line);
        while((token = strtok(line, "\t")) != NULL)
            printf("tok = %s\n", token);
        printf("\n");
        i++;
    }
    
    if(ctrl.eof)
        ctrl.eof = 0;                                               /* reset 'eof' global flag */
    
    return NULL;
}

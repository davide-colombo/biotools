//
//  bioerr.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "bioerr.h"

void raise_error(char *msg, ...){
    va_list args;
    
    fprintf(stderr, "error: ");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}

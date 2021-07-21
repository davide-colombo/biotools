//
//  bioerr.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "bioerr.h"

void raise_error(char *msg){
    fprintf(stderr, "error: %s\n", msg);
    exit(1);
}

//
//  biostr.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef biostr_h
#define biostr_h

#include <stdio.h>
#include <string.h>

#include "biovar.h"
extern FLAG ctrl;

unsigned fgetline(FILE *, char *, unsigned long);
void strcpy_from(char *to, char *from, unsigned start);
void reverse(char *);

#endif /* biostr_h */

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
#include "biotypes.h"
#include "bioconst.h"
#include "allocator.h"

#include "biovar.h"
extern FLAG ctrl;

char *strncpy_from(char *to, char *from, FPOS_T strpos, unsigned howmany);
LEN_T fgetline(FILE *fp, char *line, unsigned long lim);
FPOS_T sfind(char *targ, SRCH_T *pat, FPOS_T strpos);
void strcpy_from(char *to, const char *from, FPOS_T start);
void reverse(char *s);
char *strdup(const char *);

char *strtok(char *str, const char *sep);
int strncmp_from(const char *s1, const char *s2, FPOS_T strpos, LEN_T howmany);
char *sappend(char *original, const char *to_append);

#endif /* biostr_h */

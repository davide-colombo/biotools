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

#include "biovar.h"
extern FLAG ctrl;

unsigned fgetline(FILE *fp, char *line, unsigned long lim);
void strcpy_from(char *to, char *from, unsigned start);
void reverse(char *s);
unsigned sfind(char *tosearch, char *tofind, unsigned startpos);
unsigned repfind(char *tosearch, char tofind, unsigned minlen, unsigned startpos, STAT_T *actlen);


unsigned long sfind1(char *targ, SRCH_T *pat, unsigned long start);

#endif /* biostr_h */

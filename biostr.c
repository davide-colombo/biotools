//
//  biostr.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostr.h"

/* a function that return the length of the line read and sets the external FLAG when the last line is read */

LEN_T fgetline(FILE *fp, char *s, LEN_T lim){

    LEN_T i;
    int c;
    for(i = 0; --lim > 0 && (c = getc(fp)) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    
    if(c == EOF)
        ctrl.eof = 1;
    return i;
}

/* a function that copies characters from 'from' char array to 'to' char array starting at 'start' index */

void strcpy_from(char *to, char *from, FPOS_T start){
    FPOS_T i, j;
    for(i = start, j = 0; from[j]; i++, j++)
        to[i] = from[j];
}

/* a function that reverses the string that is passed */

void reverse(char *s){
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

/* a function that takes a target sequence to search and return the number of occurrences of that sequence */

FPOS_T sfind(char *targ, SRCH_T *pat, FPOS_T start){
    
    int c;
    FPOS_T i, j;
    for(i = start; targ[i]; i++)
        if(targ[i] == (c = *pat->str)){                                         /* MUST set 'c' here, otherwise it does not enter the loop */
            for(j = 0; targ[i] == c; i++){
                j++;
                c = (pat->maxlen == UNSET) ? *pat->str : (pat->str)[j];         /* decice the char for testing the next condition */
            }
            
            if((pat->maxlen == UNSET && j >= pat->minlen) ||
               (pat->maxlen != UNSET && !(pat->str)[j])){
                pat->curlen = j;
                return i-j;
            }
        }
    
    /* outside the for-i loop */
    
    if(!ctrl.eof)
        ctrl.eof = 1;
        
    return NOTFOUND;
}

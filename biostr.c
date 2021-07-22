//
//  biostr.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostr.h"

/* a function that return the length of the line read and sets the external FLAG when the last line is read */

unsigned fgetline(FILE *fp, char *s, unsigned long lim){

    int i, c;
    for(i = 0; --lim > 0 && (c = getc(fp)) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    
    if(c == EOF)
        ctrl.eof = 1;
    return i;
}

/* a function that copies characters from 'from' char array to 'to' char array starting at 'start' index */

void strcpy_from(char *to, char *from, unsigned start){
    int i, j;
    for(i = start, j = 0; from[j]; i++, j++)
        to[i] = from[j];
}

/* a function that reverses the string that is passed */

void reverse(char *s){
    int c, i, j;
    for(i = 0, j = strlen(s)-1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

/* function that searches occurrences of 'p' within 's' starting from 'start' and communicate end to the caller by setting 'ctrl.eof' to 1 */

unsigned sfind(char *s, char *p, unsigned start){
    
    int i, j;
    for(i = start; s[i]; i++)
        if(s[i] == p[0]){
            for(j = 0; s[i] == p[j]; i++, j++)
                ;
            if(!p[j])
                return i-j;
        }
    
    if(s[i] == '\0')                                /* this tells the caller that the string 's' has been completely scanned */
        ctrl.eof = 1;
    
    return NOTFOUND;
}

/* function that searcher occurrences of 'c' at least as long as 'minlen' within 's' starting from 'start'.
   Also, stores the length of the current repeated sequence in 'len' and communicate end to the calles by setting 'ctrl.eof' to 1 */

unsigned repfind(char *s, char c, unsigned minlen, unsigned start, STAT_T *len){
    
    int i, j;
    for(i = start; s[i]; i++)
        if(s[i] == c){
            for(j = 0; s[i] == c; i++, j++)
                ;
            if(j >= minlen){
                *len = j;
                return i-j;
            }
        }
    
    if(s[i] == '\0')                                    /* tell the caller that the string has been completely scanned */
        ctrl.eof = 1;
        
    return NOTFOUND;
}

/* a function that takes a target sequence to search and return the number of occurrences of that sequence */
unsigned long sfind1(char *targ, SRCH_T *pat, unsigned long start){
    
    static unsigned long cnt = 0;                       /* the counter of the number of occurrences of the string within 'targ' */
    
    int i, j;
    for(i = start; targ[i]; i++)
        if(targ[i] == *pat->str){
            for(j = 0; targ[i] == (pat->str)[0]; i++, j++)
                ;
            if(pat->maxlen == UNSET){
                if(j >= pat->minlen){
                    cnt++;                              /* found occurrence: increment the counter */
                    pat->curlen = j;                    /* save the current length of the string found */
                    pat->strpos = i-j;                  /* save the starting position */
                    return cnt;
                }
            }else{
                if(!(pat->str)[j]){                     /* here, I check that the null character was reached in pat->str */
                    cnt++;
                    pat->curlen = j;
                    pat->strpos = i-j;
                    return cnt;
                }
            }
        }
    
    if(!ctrl.eof)
        ctrl.eof = 1;
        
    return cnt;
}

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

unsigned sfind(char *s, char *p, unsigned start){
    
    int i, j;
    for(i = start; s[i]; i++)
        if(s[i] == p[0]){
            for(j = 0; (s[i] == p[j]) && p[j]; i++, j++)
                ;
            if(!p[j])
                return i-j;
        }
    
    if(s[i] == '\0')                                /* this tells the caller that the string 's' has been completely scanned */
        ctrl.eof = 1;
    
    return NOTFOUND;
}

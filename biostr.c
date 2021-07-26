//
//  biostr.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostr.h"

char *strncpy_from(char *to, char *from, FPOS_T strpos, unsigned howmany){
    FPOS_T i, j;
    for(i = strpos, j = 0; j < howmany && (to[j] = from[i]); i++, j++)
        ;
    to[j] = '\0';
    return to;
}

/* a function that return the length of the line read and sets the external FLAG when the last line is read */

LEN_T fgetline(FILE *fp, char *s, LEN_T lim){

    int c;
    LEN_T i = 0;
    
    while((c = getc(fp)) == '#')                                                     /* skip the lines that begin with '#' */
        while((c = getc(fp)) != '\n' && c != EOF)
            ;
    
    for(s[i++] = c; --lim > 0 && (c = getc(fp)) != EOF && c != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    
    if(c == EOF)
        ctrl.eof = 1;
    
    return i;
}

/* a function that copies characters from 'from' char array to 'to' char array starting at 'start' index */

void strcpy_from(char *to, const char *from, FPOS_T start){
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

char *strdup(const char *str){
    char *ptr;
    
    if((ptr = alloc_chararray(strlen(str))) == NULL)                  /* +1 for '\0' */
       return NULL;
    strcpy(ptr, str);
    return ptr;
}

/* function that splits the 'str' input argument in token by using 'sep' separator and return an array of pointers to single char array */

char *strtok(char *str, const char *sep){
    
    LEN_T toksize = 1UL;                                                        /* for memory efficienty use a small TOKENSIZE */
    char *token;
    if((token = alloc_chararray(toksize)) == NULL)                              /* alloc memory for the next token to be read */
        return NULL;
    
    LEN_T toklen;
    static int i = 0;                                                           /* this variable is initialize only once */
    
    if(str[i] == '\0'){                                                         /* exit condition since 'i' is a static variable */
        i = 0;
        return NULL;
    }
    
    int cond;
    for(toklen = 0;                                                             /* initialize the length of this token */
        str[i] && (cond = strncmp_from(str, sep, i, strlen(sep)));              /* not '\0' and not */
        token[toklen++] = str[i++]){
        if(i >= toksize)
            if((token = realloc_chararray(token, toksize+=3)) == NULL)          /* realloc if the size is not enough */
                return NULL;
    }
    
    if(cond == 0)                                                               /* if a separator was found, then increment 'i' */
        i++;
    
    token[toklen] = '\0';                                                       /* when '\0' occurr, end the token and return */
    return token;
}

/* function that compares the first 'howmany' chars of the two strings beginning at 'strpos' */

int strncmp_from(const char *s1, const char *s2, FPOS_T strpos, LEN_T howmany){
    int i, j;
    for(j = 0, i = strpos; j < howmany && (s1[i] == s2[j]); i++, j++)
        ;
    
    if(j == howmany)                                                            /* because 'i' does not start from 0 */
        return 0;
    return s1[i]-s2[i];
}

/* a function for appending a string to another */

char *sappend(char *str, const char *a){
    LEN_T new_len = strlen(str) + strlen(a);
    
    char *ptr;
    if((ptr = alloc_chararray(new_len)) == NULL)
        return NULL;
    strcpy_from(ptr, str, 0UL);                                                 /* do not include the '\0' character */
    strcpy_from(ptr, a, strlen(str));                                           /* do not copy the '\0' */
    ptr[new_len] = '\0';                                                        /* insert the '\0' to end the string */
    return ptr;
}

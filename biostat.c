//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostat.h"


STAT_T scount(SEQ *s_ptr, char *s){
    
    char *ptr;                                              /* define pointer to char to improve code readability */
    ptr = s_ptr->seq;
    
    STAT_T cnt;                                             /* variable in which is stored the number of match */
    int i, f;
    
    for(i = 0, cnt = 0; !ctrl.eof; i+=(f+strlen(s)))        /* cycle until the callee does not set the eof flag */
        if((f = sfind(ptr, s, i)) != NOTFOUND)              /* 'f' is the index of the occurrence */
            cnt++;
    
    if(ctrl.eof)                                            /* reset the global variable to make it available to other functions */
        ctrl.eof = 0;
    
    return cnt;
}

STAT_T repcount(SEQ *s_ptr, char c, unsigned minlen){
    
    char *ptr;
    ptr = s_ptr->seq;
    
    STAT_T cnt, len;
    int i, f;
    for(cnt = 0, len = 0, i = 0; !ctrl.eof; i+=(f+len))
        if((f = repfind(ptr, c, minlen, i, &len)) != NOTFOUND)
            cnt++;
    
    if(ctrl.eof)
        ctrl.eof = 0;
    return cnt;
}

STAT_T genelen(SEQ *s_ptr){
    return strlen(s_ptr->seq);
}

double gcperc(SEQ *s_ptr){
    
    char *ptr;                                              /* defined for improving code readability */
    ptr = s_ptr->seq;
    
    double gc;
    int i;
    for(gc = 0.0, i = 0; ptr[i]; i++)
        if(ptr[i] == 'G' || ptr[i] == 'C')
            gc++;
    return gc / i;
}

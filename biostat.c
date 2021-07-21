//
//  biostat.c
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#include "biostat.h"


unsigned long scount(SEQ *s_ptr, char *s){
    
    char *ptr;                                              /* define pointer to char to improve code readability */
    ptr = s_ptr->seq;
    
    unsigned long cnt;                                      /* variable in which is stored the number of match */
    int i, f;
    
    for(i = 0, cnt = 0; !ctrl.eof; i+=(f+strlen(s)))        /* cycle until the callee does not set the eof flag */
        if((f = sfind(ptr, s, i)) != NOTFOUND)              /* 'f' is the index of the occurrence */
            cnt++;
    return cnt;
}

unsigned long genelen(SEQ *s_ptr){
    return strlen(s_ptr->seq);
}

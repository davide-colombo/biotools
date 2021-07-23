//
//  bioconst.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef bioconst_h
#define bioconst_h

#define INITSIZE 100
#define EXPAND 1000
#define NOTFOUND -1
#define UNSET 0
#define CODONLEN 3

#define A2T ('t'-'a')                   /* symbolic constant that allow to switch from 'A' to 'T' and vice versa */
#define C2G ('g'-'c')                   /* symbolic constant that allow to switch from 'C' to 'G' and vice versa */

#define IS_START(str) ( (strcmp(str, "ATG") == 0) ? 1 : 0)
#define IS_STOP(str) ( (strcmp(str, "TAG") == 0 || strcmp(str, "TGA") == 0 || strcmp(str, "TAA") == 0) ? 1 : 0 )

#endif /* bioconst_h */

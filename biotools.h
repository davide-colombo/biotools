//
//  biotools.h
//  
//
//  Created by Davide Colombo on 20/07/21.
//

#ifndef biotools_h
#define biotools_h

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_SIZE 10
#define A2T ('t'-'a')               /* symbolic constant that allow to switch from 'A' to 'T' and vice versa */
#define C2G ('g'-'c')               /* symbolic constant that allow to switch from 'C' to 'G' and vice versa */

typedef char *_DNA_;                /* define DNA datatype */
typedef char *_RNA_;

_DNA_ rev_complement(_DNA_);
_DNA_ getsequence(_DNA_, FILE *);
_RNA_ transcript(_DNA_);

#endif /* biotools_h */

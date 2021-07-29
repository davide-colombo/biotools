//
//  allocator.h
//  
//
//  Created by Davide Colombo on 21/07/21.
//

#ifndef allocator_h
#define allocator_h

#include <stdlib.h>
#include <string.h>
#include "biotypes.h"
#include "biostr.h"

CDS_T *cds_t(SEQ *s_ptr, FPOS_T strpos, LEN_T len);
CDS_T *alloc_cds(void);
void free_cds_t(CDS_T *);

SRCH_T *srch_t(char *s, LEN_T min, LEN_T max);
void free_srch_t(SRCH_T *ptr);
SRCH_T *alloc_srch(void);

OCC **alloc_occptr_arr(LEN_T size);
void free_occptr_arr(OCC **tofree);

OCC *occ(FPOS_T fpos, FPOS_T flen);
void free_occ(OCC *ptr);
OCC *alloc_occ(void);

SEQ *make_seq(void);
char *alloc_chararray(LEN_T size);
char *realloc_chararray(char *, LEN_T size);

UTR_T*utr_t(CDS_T *cds, FPOS_T str5f, LEN_T len5f, FPOS_T str3f, LEN_T len3f);

#endif /* allocator_h */

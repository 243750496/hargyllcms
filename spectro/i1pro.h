#ifndef I1PRO_H

/* 
 * Argyll Color Correction System
 *
 * Gretag i1Pro related defines
 *
 * Author: Graeme W. Gill
 * Date:   24/11/2006
 *
 * Copyright 2006 - 2007, Graeme W. Gill
 * All rights reserved.
 *
 * This material is licenced under the GNU AFFERO GENERAL PUBLIC LICENSE Version 3 :-
 * see the License.txt file for licencing details.
 */

/* 
   If you make use of the instrument driver code here, please note
   that it is the author(s) of the code who take responsibility
   for its operation. Any problems or queries regarding driving
   instruments with the Argyll drivers, should be directed to
   the Argyll's author(s), and not to any other party.

   If there is some instrument feature or function that you
   would like supported here, it is recommended that you
   contact Argyll's author(s) first, rather than attempt to
   modify the software yourself, if you don't have firm knowledge
   of the instrument communicate protocols. There is a chance
   that an instrument could be damaged by an incautious command
   sequence, and the instrument companies generally cannot and
   will not support developers that they have not qualified
   and agreed to support.
 */

#include "inst.h"

/* I1PRO communication object */
struct _i1pro {
	INST_OBJ_BASE

	int       dtype;			/* Device type: 0 = ?? */	

	/* *** i1pro private data **** */
	inst_capability  cap;		/* Instrument capability */
	inst2_capability cap2;		/* Instrument capability 2 */

	void *m;					/* Implementation - i1proimp type */
}; typedef struct _i1pro i1pro;

/* Constructor */
extern i1pro *new_i1pro(icoms *icom, int debug, int verb);

#define I1PRO_H
#endif /* I1PRO_H */

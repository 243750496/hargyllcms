/* 
 * Argyll Color Correction System
 *
 * Instrument supported types utilities
 *
 * Author: Graeme W. Gill
 * Date:   10/3/2001
 *
 * Copyright 2001 - 2007 Graeme W. Gill
 * All rights reserved.
 *
 * This material is licenced under the GNU AFFERO GENERAL PUBLIC LICENSE Version 3 :-
 * see the License.txt file for licencing details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "copyright.h"
#include "config.h"
#include "xspect.h"
#include "insttypes.h"

/* NOTE NOTE NOTE: */
/* Need to add a new instrument to new_inst() in */
/* inst.c as well !!! */

/* Utility functions */

/* Return the instrument identification name (static string) */
char *inst_name(instType itype) {
	switch (itype) {
		case instDTP20:
			return "Xrite DTP20";
		case instDTP22:
			return "Xrite DTP22";
		case instDTP41:
			return "Xrite DTP41";
		case instDTP51:
			return "Xrite DTP51";
		case instDTP92:
			return "Xrite DTP92";
		case instDTP94:
			return "Xrite DTP94";
		case instSpectrolino:
			return "GretagMacbeth Spectrolino";
		case instSpectroScan:
			return "GretagMacbeth SpectroScan";
		case instSpectroScanT:
			return "GretagMacbeth SpectroScanT";
		case instSpectrocam:
			return "Spectrocam";
		case instI1Display:
			return "GretagMacbeth i1 Display";
		case instI1Monitor:
			return "GretagMacbeth i1 Monitor";
		case instI1Pro:
			return "GretagMacbeth i1 Pro";
		case instColorMunki:
			return "X-Rite ColorMunki";
		case instHCFR:
			return "Colorimtre HCFR";
		case instSpyder2:
			return "ColorVision Spyder2";
		case instSpyder3:
			return "Datacolor Spyder3";
		case instHuey:
			return "GretagMacbeth Huey";
		default:
			break;
	}
	return "Unknown Instrument";
}

/* Given an instrument identification name, return the matching */
/* instType, or instUnknown if not matched */
instType inst_enum(char *name) {

	if (strcmp(name, "Xrite DTP20") == 0)
		return instDTP20;
	else if (strcmp(name, "Xrite DTP22") == 0)
		return instDTP22;
	else if (strcmp(name, "Xrite DTP41") == 0)
		return instDTP41;
	else if (strcmp(name, "Xrite DTP51") == 0)
		return instDTP51;
	else if (strcmp(name, "Xrite DTP92") == 0)
		return instDTP92;
	else if (strcmp(name, "Xrite DTP94") == 0)
		return instDTP94;
	else if (strcmp(name, "GretagMacbeth Spectrolino") == 0)
		return instSpectrolino;
	else if (strcmp(name, "GretagMacbeth SpectroScan") == 0)
		return instSpectroScan;
	else if (strcmp(name, "GretagMacbeth SpectroScanT") == 0)
		return instSpectroScanT;
	else if (strcmp(name, "Spectrocam") == 0)
		return instSpectrocam;
	else if (strcmp(name, "GretagMacbeth i1 Display") == 0)
		return instI1Display;
	else if (strcmp(name, "GretagMacbeth i1 Monitor") == 0)
		return instI1Monitor;
	else if (strcmp(name, "GretagMacbeth i1 Pro") == 0)
		return instI1Pro;
	else if (strcmp(name, "X-Rite ColorMunki") == 0)
		return instColorMunki;
	else if (strcmp(name, "Colorimtre HCFR") == 0)
		return instHCFR;
	else if (strcmp(name, "ColorVision Spyder2") == 0)
		return instSpyder2;
	else if (strcmp(name, "Datacolor Spyder3") == 0)
		return instSpyder3;
	else if (strcmp(name, "GretagMacbeth Huey") == 0)
		return instHuey;

	return instUnknown;
}

#ifdef ENABLE_USB

/* Given a USB vendor and product ID, */
/* return the matching instrument type, or */
/* instUnknown if none match. */
instType inst_usb_match(
unsigned short idVendor,
unsigned short idProduct) {

	if (idVendor  == 0x0765) {		/* X-Rite */
		if (idProduct == 0xD020)	/* DTP20 */
			return instDTP20;
		if (idProduct == 0xD092)	/* DTP92Q */
			return instDTP92;
	  	if (idProduct == 0xD094)	/* DTP94 */
			return instDTP94;
//	  	if (idProduct == 0x5001)	/* HueyPro */
//			return instHuey;
	}

	if (idVendor  == 0x0971) {		/* Gretag Macbeth */
		if (idProduct == 0x2000)	/* i1 Pro */
			return instI1Pro;
		if (idProduct == 0x2001)	/* i1 Monitor */
			return instI1Monitor;
		if (idProduct == 0x2003)	/* i1 Display */
			return instI1Display;
		if (idProduct == 0x2005)	/* Huey */
			return instHuey;
		if (idProduct == 0x2007)	/* ColorMunki */
			return instColorMunki;
	}

	if (idVendor  == 0x0670) {		/* Sequel Imaging */
		if (idProduct == 0x0001)	/* Monaco Optix / i1 Display 1 */
									/* Sequel Chroma 4 / i1 Display 1 */
			return instI1Display;	/* Alias to the i1 Display */
	}

	if (idVendor  == 0x04DB) {
		if (idProduct == 0x005B)	/* Colorimtre HCFR */
			return instHCFR;
	}

	if (idVendor  == 0x085C) {
		if (idProduct == 0x0200)	/* ColorVison Spyder2 */
			return instSpyder2;
		if (idProduct == 0x0300)	/* ColorVison Spyder3 */
			return instSpyder3;
	}

	/* Add other instruments here */

	return instUnknown;
}

#endif /* ENABLE_USB */

/* Should deprecate the following. It should be replaced with a */
/* method in the instrument class that returns its configured spectrum, */
/* and the spectrum should be embedded in the .ti3 file, not the instrument */
/* name. */

/* Fill in an instruments illuminant spectrum. */
/* Return 0 on sucess, 1 if not not applicable. */
int inst_illuminant(xspect *sp, instType itype) {

	switch (itype) {
		case instDTP20:
			return standardIlluminant(sp, icxIT_A, 0);		/* 2850K */

		case instDTP22:
			return standardIlluminant(sp, icxIT_A, 0);		/* 2850K */

		case instDTP41:
			return standardIlluminant(sp, icxIT_A, 0);		/* 2850K */

		case instDTP51:
			return standardIlluminant(sp, icxIT_A, 0);		/* 2850K */

		case instDTP92:
		case instDTP94:
			return 1;										/* Not applicable */

		/* Strictly the Spectrolino could have the UV or D65 filter on, */
		/* but since we're not currently passing this inform through, we */
		/* are simply assuming the default A type illuminant. */

		case instSpectrolino:
			return standardIlluminant(sp, icxIT_A, 0);		/* Standard A type assumed */

		case instSpectroScan:
			return standardIlluminant(sp, icxIT_A, 0);		/* Standard A type assumed */

		case instSpectroScanT:
			return standardIlluminant(sp, icxIT_A, 0);		/* Standard A type assumed */

		case instSpectrocam:
			return standardIlluminant(sp, icxIT_Spectrocam, 0);   /* Spectrocam Xenon Lamp */

		case instI1Display:
			return 1;										/* Not applicable */

		case instI1Monitor:
			return 1;										/* Not applicable */

		case instI1Pro:
			return standardIlluminant(sp, icxIT_A, 0);		/* Standard A type assumed */

		case instColorMunki:
			return 1;										/* No U.V. */

		case instHCFR:
			return 1;										/* Not applicable */

		case instSpyder2:
			return 1;										/* Not applicable */

		case instSpyder3:
			return 1;										/* Not applicable */

		case instHuey:
			return 1;										/* Not applicable */

		default:
			break;
	}
	return 1;
}



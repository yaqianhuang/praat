#ifndef _LongSound_h_
#define _LongSound_h_
/* LongSound.h
 *
 * Copyright (C) 1992-2004 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * pb 2004/11/24
 */

#ifndef _Sound_h_
	#include "Sound.h"
#endif
#ifndef _Collection_h_
	#include "Collection.h"
#endif

#define LongSound_members Sampled_members \
	structMelderFile file; \
	FILE *f; \
	int audioFileType, numberOfChannels, encoding, numberOfBytesPerSamplePoint; \
	double sampleRate; \
	long startOfData; \
	double bufferLength; \
	short *buffer; \
	long imin, imax, nmax;
#define LongSound_methods Sampled_methods
class_create (LongSound, Sampled)

LongSound LongSound_open (MelderFile fs);

Sound LongSound_extractPart (LongSound me, double tmin, double tmax, int preserveTimes);

int LongSound_haveWindow (LongSound me, double tmin, double tmax);
/*
 * Returns 0 if error or if window exceeds buffer, otherwise 1;
 */

void LongSound_getWindowExtrema (LongSound me, double tmin, double tmax, int channel, double *minimum, double *maximum);

void LongSound_playPart (LongSound me, double tmin, double tmax,
	int (*callback) (void *closure, int phase, double tmin, double tmax, double t), void *closure);

int LongSound_writePartToAudioFile16 (LongSound me, int audioFileType, double tmin, double tmax, MelderFile file);
int LongSound_writeChannelToAudioFile16 (LongSound me, int audioFileType, int channel, MelderFile file);

int LongSound_concatenate (Ordered collection, MelderFile file, int audioFileType);
/* Concatenate a collection of Sound and LongSound objects. */

void LongSound_prefs (void);
long LongSound_getBufferSizePref_seconds (void);
void LongSound_setBufferSizePref_seconds (long size);

/* End of file LongSound.h */
#endif

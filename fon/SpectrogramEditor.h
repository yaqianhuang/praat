#ifndef _SpectrogramEditor_h_
#define _SpectrogramEditor_h_
/* SpectrogramEditor.h
 *
 * Copyright (C) 1992-2002 Paul Boersma
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
 * pb 1995/06/04
 * pb 2002/07/16 GPL
 */

#ifndef _FunctionEditor_h_
	#include "FunctionEditor.h"
#endif
#ifndef _Spectrogram_h_
	#include "Spectrogram.h"
#endif

#define SpectrogramEditor_members FunctionEditor_members \
	double maximum;
#define SpectrogramEditor_methods FunctionEditor_methods
class_create (SpectrogramEditor, FunctionEditor)

Any SpectrogramEditor_create (Widget parent, char *title, Any data);

/* End of file SpectrogramEditor.h */
#endif

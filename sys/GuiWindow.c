/* GuiWindow.c
 *
 * Copyright (C) 1993-2004 Paul Boersma
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
 * pb 2004/01/07 this file separated from Gui.c
 * pb 2004/02/12 don't trust window modification feedback on MacOS 9
 * pb 2004/04/06 GuiWindow_drain separated from XmUpdateDisplay
 */

#include "GuiP.h"

int GuiWindow_setDirty (Widget me, int dirty) {
	#if mac && defined (__MACH__)
		SetWindowModified (my nat.window.ptr, dirty);
		return 1;
	#else
		(void) me;
		(void) dirty;
		return 0;
	#endif
}

void GuiWindow_drain (Widget me) {
	#if mac && carbon
		QDFlushPortBuffer (GetWindowPort (my macWindow), NULL);
		/*
		 * The following TRICK cost me half a day to work out.
		 * It turns out that after a call to QDFlushPortBuffer (),
		 * it takes MacOS ages to compute a new dirty region while
		 * the next graphics commands are executed. Such a dirty region
		 * could well be the region that includes all the pixels drawn by
		 * the graphics commands, and nothing else. One can imagine
		 * that such a thing takes five seconds when the graphics is
		 * a simple Graphics_function () of e.g. noise.
		 */
		{
			static Rect bounds = { -32768, -32768, 32767, 32767 };
			QDAddRectToDirtyRegion (GetWindowPort (my macWindow), & bounds);
		}
	#else
		(void) me;
	#endif
}

/* End of file GuiWindow.c */

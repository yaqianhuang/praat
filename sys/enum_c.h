/* enum_c.h
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
 * pb 1995/07/14
 * pb 2002/03/07 GPL
 */

/* See enum.h */

/* For C files. */

#undef enum_begin
#undef enum
#undef enum_end
#define enum_begin(type,zero)  type enum_##type = { enumlength (type), #type, #zero,
#define enum(element)  #element,
#define enum_end(type)  (char *) 0, (int) 0 };

/* End of file enum_c.h */

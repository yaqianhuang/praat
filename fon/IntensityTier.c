/* IntensityTier.c
 *
 * Copyright (C) 1992-2003 Paul Boersma
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
 * pb 2001/08/16
 * pb 2002/07/16 GPL
 * pb 2003/05/31 use PointProcess_upto_RealTier
 */

#include "IntensityTier.h"

class_methods (IntensityTier, RealTier)
class_methods_end

IntensityTier IntensityTier_create (double tmin, double tmax) {
	IntensityTier me = new (IntensityTier);
	if (! me || ! RealTier_init (me, tmin, tmax)) { forget (me); return NULL; }
	return me;
}

void IntensityTier_draw (IntensityTier me, Graphics g, double tmin, double tmax,
	double ymin, double ymax, int garnish)
{
	RealTier_draw (me, g, tmin, tmax, ymin, ymax, garnish, "Intensity (dB)");
}

IntensityTier PointProcess_upto_IntensityTier (PointProcess me, double intensity) {
	IntensityTier thee = (IntensityTier) PointProcess_upto_RealTier (me, intensity);
	if (! thee) return NULL;
	Thing_overrideClass (thee, classIntensityTier);
	return thee;
}

IntensityTier Intensity_downto_IntensityTier (Intensity me) {
	IntensityTier thee = (IntensityTier) Vector_to_RealTier (me);
	if (! thee) return NULL;
	Thing_overrideClass (thee, classIntensityTier);
	return thee;
}

IntensityTier Intensity_to_IntensityTier_peaks (Intensity me) {
	IntensityTier thee = (IntensityTier) Vector_to_RealTier_peaks (me);
	if (! thee) return NULL;
	Thing_overrideClass (thee, classIntensityTier);
	return thee;
}

IntensityTier Intensity_to_IntensityTier_valleys (Intensity me) {
	IntensityTier thee = (IntensityTier) Vector_to_RealTier_valleys (me);
	if (! thee) return NULL;
	Thing_overrideClass (thee, classIntensityTier);
	return thee;
}

IntensityTier Intensity_PointProcess_to_IntensityTier (Intensity me, PointProcess pp) {
	IntensityTier temp = NULL, thee = NULL;
	temp = Intensity_downto_IntensityTier (me); cherror
	thee = IntensityTier_PointProcess_to_IntensityTier (temp, pp); cherror
end:
	forget (temp);
	iferror forget (thee);
	return thee;
}

IntensityTier IntensityTier_PointProcess_to_IntensityTier (IntensityTier me, PointProcess pp) {
	long i;
	IntensityTier thee = NULL;
	if (my points -> size == 0) return Melder_errorp ("No intensity points.");
	thee = IntensityTier_create (pp -> xmin, pp -> xmax); cherror;
	for (i = 1; i <= pp -> nt; i ++) {
		double time = pp -> t [i];
		double value = RealTier_getValueAtTime (me, time);
		RealTier_addPoint (thee, time, value); cherror
	}
end:
	iferror forget (thee);
	return thee;
}

TableOfReal IntensityTier_downto_TableOfReal (IntensityTier me) {
	return RealTier_downto_TableOfReal (me, "Time (s)", "Intensity (dB)");
}

void Sound_IntensityTier_multiply_inline (Sound me, IntensityTier intensity) {
	long isamp; float *amp = my z [1];
	if (intensity -> points -> size == 0) return;
	for (isamp = 1; isamp <= my nx; isamp ++) {
		double t = my x1 + (isamp - 1) * my dx;
		amp [isamp] *= pow (10, RealTier_getValueAtTime (intensity, t) / 20);
	}
}

Sound Sound_IntensityTier_multiply (Sound me, IntensityTier intensity) {
	Sound thee = Data_copy (me);
	if (! thee) return NULL;
	Sound_IntensityTier_multiply_inline (thee, intensity);
	Vector_scale (thee, 0.9);
	return thee;
}

/* End of file IntensityTier.c */

/* Sound_enhance.c
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
 * pb 2002/07/16 GPL
 * pb 2004/11/22 simplified Sound_to_Spectrum ()
 */

#include "Manipulation.h"
#include "Sound_to_Pitch.h"
#include "Pitch_to_PitchTier.h"
#include "Pitch_to_PointProcess.h"
#include "Sound_and_Spectrum.h"

Sound Sound_lengthen_psola (Sound me, double fmin, double fmax, double factor) {
	Sound sound = NULL, thee = NULL;
	Pitch pitch = NULL;
	PointProcess pulses = NULL;
	PitchTier pitchTier = NULL;
	DurationTier duration = NULL;

	sound = Data_copy (me); cherror
	Vector_subtractMean (sound);
	pitch = Sound_to_Pitch (sound, 0.8 / fmin, fmin, fmax); cherror
	pulses = Sound_Pitch_to_PointProcess_cc (sound, pitch); cherror
	pitchTier = Pitch_to_PitchTier (pitch); cherror
	duration = DurationTier_create (my xmin, my xmax); cherror
	RealTier_addPoint (duration, 0.5 * (my xmin + my xmax), factor); cherror
	thee = Sound_Point_Pitch_Duration_to_Sound (sound, pulses, pitchTier, duration, 1.5 / fmin); cherror
end:
	forget (sound);
	forget (pitch);
	forget (pulses);
	forget (pitchTier);
	forget (duration);
	iferror forget (thee);
	return thee;
}

Sound Sound_deepenBandModulation (Sound me, double enhancement_dB,
	double flow, double fhigh, double slowModulation, double fastModulation, double bandSmoothing)
{
	Sound thee = NULL, band = NULL, intensity = NULL;
	Spectrum orgspec = NULL, spec = NULL, intensityFilter = NULL;
	double fmin, maximumFactor = pow (10, enhancement_dB / 20), alpha = sqrt (log (2.0));
	long i, n;
	float *amp;
	double alphaslow = alpha / slowModulation, alphafast = alpha / fastModulation;

	orgspec = Sound_to_Spectrum (me, TRUE); cherror

	/*
	 * Keep the part of the sound that is outside the filter bank.
	 */
	spec = Data_copy (orgspec); cherror
	Spectrum_stopHannBand (spec, flow, fhigh, bandSmoothing);
	thee = Spectrum_to_Sound (spec); cherror

	fmin = flow;
	while (fmin < fhigh) {
		/*
		 * Take a one-bark frequency band.
		 */
		double fmid_bark = NUMhertzToBark (fmin) + 0.5, ceiling;
		double fmax = NUMbarkToHertz (NUMhertzToBark (fmin) + 1);
		if (fmax > fhigh) fmax = fhigh;
		Melder_progress (fmin / fhigh, "Band: %.0f ... %.0f Hz", fmin, fmax); cherror
		NUMfmatrix_copyElements (orgspec -> z, spec -> z, 1, 2, 1, spec -> nx);
		Spectrum_passHannBand (spec, fmin, fmax, bandSmoothing);
		band = Spectrum_to_Sound (spec); cherror
		/*
		 * Compute a relative intensity contour.
		 */		
		intensity = Data_copy (band); cherror
		n = intensity -> nx;
		amp = intensity -> z [1];
		for (i = 1; i <= n; i ++) amp [i] = 10 * log10 (amp [i] * amp [i] + 1e-6);
		intensityFilter = Sound_to_Spectrum (intensity, TRUE);
		forget (intensity);
		n = intensityFilter -> nx;
		for (i = 1; i <= n; i ++) {
			double frequency = intensityFilter -> x1 + (i - 1) * intensityFilter -> dx;
			double slow = alphaslow * frequency, fast = alphafast * frequency;
			double factor = exp (- fast * fast) - exp (- slow * slow);
			intensityFilter -> z [1] [i] *= factor;
			intensityFilter -> z [2] [i] *= factor;
		}
		intensity = Spectrum_to_Sound (intensityFilter); cherror
		forget (intensityFilter);
		n = intensity -> nx;
		amp = intensity -> z [1];
		for (i = 1; i <= n; i ++) amp [i] = pow (10, amp [i] / 2);
		/*
		 * Clip to maximum enhancement.
		 */
		ceiling = 1 + (maximumFactor - 1.0) * (0.5 - 0.5 * cos (NUMpi * fmid_bark / 13));
		for (i = 1; i <= n; i ++) amp [i] = 1 / (1 / amp [i] + 1 / ceiling);

		n = thy nx;
		amp = thy z [1];
		for (i = 1; i <= n; i ++) amp [i] += band -> z [1] [i] * intensity -> z [1] [i];
		forget (intensity);
		forget (band);

		fmin = fmax;
	}
	Vector_scale (thee, 0.99);
	/* Truncate. */
	thy xmin = my xmin;
	thy xmax = my xmax;
	thy nx = my nx;
	thy x1 = my x1;
end:
	Melder_progress (1.0, NULL);
	forget (orgspec);
	forget (spec);
	forget (band);
	forget (intensity);
	forget (intensityFilter);
	iferror forget (thee);
	return thee;
}

/* End of file Sound_enhance.c */

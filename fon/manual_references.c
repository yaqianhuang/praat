/* manual_references.c
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

#include "ManPagesM.h"

void manual_references_init (ManPages me);
void manual_references_init (ManPages me) {

MAN_BEGIN ("Archangeli & Pulleyblank (1994)", "ppgb", 19971021)
NORMAL ("Diana Archangeli & Douglas Pulleyblank (1994): %%Grounded Phonology%. "
	"Cambridge, Mass.: MIT Press.")
MAN_END

MAN_BEGIN ("Boersma (1993)", "ppgb", 20030312)
NORMAL ("Paul Boersma (1993): \"Accurate short-term analysis of the fundamental frequency "
	"and the harmonics-to-noise ratio of a sampled sound.\" "
	"%%Proceedings of the Institute of Phonetic Sciences% #17: 97\\--110. University of Amsterdam.")
NORMAL ("Can be downloaded as a PDF file from http://fon.hum.uva.nl/paul/")
MAN_END

MAN_BEGIN ("Boersma (1997a)", "ppgb", 19981219)
NORMAL ("Paul Boersma (1997a): \"The elements of Functional Phonology.\" "
	"Ms. University of Amsterdam.")
NORMAL ("Available as Rutgers Optimality Archive #173, http://ruccs.rutgers.edu/roa.html")
NORMAL ("Superseded by chapters 1 and 7 through 13 of @@Boersma (1998)@.")
MAN_END

MAN_BEGIN ("Boersma (1997b)", "ppgb", 19981219)
NORMAL ("Paul Boersma (1997b): \"How we learn variation, optionality, and probability.\" "
	"%%Proceedings of the Institute of Phonetic Sciences% #21: 43\\--58. University of Amsterdam.")
NORMAL ("Equals chapter 15 of @@Boersma (1998)@.")
NORMAL ("A less correct version (demoting and promoting a single pair of constraints, instead of them all) "
	"is available as Rutgers Optimality Archive #221, http://ruccs.rutgers.edu/roa.html")
MAN_END

MAN_BEGIN ("Boersma (1998)", "ppgb", 20041020)
NORMAL ("Paul Boersma (1998): %%Functional Phonology% [%%LOT International Series% ##11#]. "
	"The Hague: Holland Academic Graphics. Pages i-ix, 1-493. [Doctoral thesis, University of Amsterdam]")
NORMAL ("This book can be downloaded as a PDF file from ##http://www.fon.hum.uva.nl/paul/#, "
	"where you can also find many Praat scripts for the simulations and pictures in this book. "
	"A paperback version is also available from the author (paul.boersma\\@ uva.nl).")
MAN_END

MAN_BEGIN ("Boersma (2000)", "ppgb", 20001027)
NORMAL ("Paul Boersma (2000): \"Learning a grammar in Functional Phonology.\" "
	"In Joost Dekkers, Frank van der Leeuw, & Jeroen van de Weijer (eds.): "
	"%%Phonology, Syntax, and Acquisition in Optimality Theory%. Oxford University Press.")
NORMAL ("An extended version is chapter 14 of @@Boersma (1998)@.")
MAN_END

MAN_BEGIN ("Boersma & Hayes (2001)", "ppgb", 20020511)
NORMAL ("Paul Boersma & Bruce Hayes (2001): \"Empirical tests of the Gradual Learning Algorithm.\" "
	"%%Linguistic Inquiry% #32: 45\\--86.")
MAN_END

MAN_BEGIN ("Childers (1978)", "ppgb", 20030515)
NORMAL ("%%Modern spectrum analysis%, IEEE Press.")
NORMAL ("The Burg algorithm for linear prediction coefficients is described on pages 252-255.")
MAN_END

MAN_BEGIN ("Deliyski (1993)", "ppgb", 20030312)
NORMAL ("Dimitar D. Deliyski: \"Acoustic model and evaluation of pathological voice production.\" "
	"%%Proceedings Eurospeech '93%, Vol. 3, 1969\\--1972.")
MAN_END

MAN_BEGIN ("Jesteadt, Wier & Green (1977)", "ppgb", 20021215)
NORMAL ("W. Jesteadt, G.C. Wier, & D.M. Green (1977): \"Intensity discrimination as a function "
	"of frequency and sensation level.\" %%Journal of the Acoustical Society of America% #61: 169\\--177.")
MAN_END

MAN_BEGIN ("Ladefoged (2001)", "ppgb", 20030316)
NORMAL ("Peter Ladefoged (2001). %%Vowels and consonants%: %%an introduction to the sounds of languages%. "
	"Oxford: Blackwell.")
NORMAL ("A very readable introduction to phonetics, mainly acoustic and articulatory. "
	"Has lots of spectrograms of the sounds of the world's languages. Comes with a CD that has all those "
	"sounds and includes training material for transcription (from another book).")
NORMAL ("For a more encyclopaedic treatment of the sounds of the world's languages, "
	"see @@Ladefoged & Maddieson (1996)@ instead.")
MAN_END

MAN_BEGIN ("Ladefoged & Maddieson (1996)", "ppgb", 20030316)
NORMAL ("Peter Ladefoged & Ian Maddieson (1996). %%The sounds of the world's languages%. "
	"Oxford: Blackwell.")
NORMAL ("An extensive reference source for the articulation and acoustics of `all' vowels and consonants "
	"that occur in the world's languages. If you don't find the answer in this book, you will find the "
	"answer in the articles referred to in this book. "
	"The book uses lots of spectrograms, palatograms, and other techniques.")
NORMAL ("The book is not an introductory text. For that, see @@Ladefoged (2001)@ instead.")
MAN_END

MAN_BEGIN ("Patterson & Wightman (1976)", "ppgb", 20021215)
NORMAL ("R. Patterson & F. Wightman (1976): \"Residue pitch as a function of component spacing.\" "
	"%%Journal of the Acoustical Society of America% #59: 1450\\--1459.")
MAN_END

MAN_BEGIN ("Plomp (1967)", "ppgb", 20021215)
NORMAL ("Reinier Plomp (1967): \"Frequencies dominant in the perception of pitch of complex sounds.\" "
	"%%Journal of the Acoustical Society of America% #42: 191\\--198.")
MAN_END

MAN_BEGIN ("Tesar & Smolensky (1998)", "ppgb", 19991019)
NORMAL ("Bruce Tesar & Paul Smolensky (1998): \"Learnability in Optimality Theory.\" "
	"%%Linguistic Inquiry% #29: 229\\--268.")
NORMAL ("The first version of the constraint-demotion algorithm appeared in:")
NORMAL ("Bruce Tesar & Paul Smolensky (1993): \"The learnability of Optimality Theory: "
	"an algorithm and some basic complexity results\", "
	"ms. Department of Computer Science & Institute of Cognitive Science, University of Colorado at Boulder. "
	"Available as Rutgers Optimality Archive #2, http://ruccs.rutgers.edu/roa.html")
NORMAL ("The Error-Driven Constraint Demotion algorithm can be found in:")
NORMAL ("Bruce Tesar & Paul Smolensky (1996): \"Learnability in Optimality Theory (long version)\". "
 	"Technical Report ##96-3#, Department of Cognitive Science, Johns Hopkins University, Baltimore. "
	"Available as Rutgers Optimality Archive #156, http://ruccs.rutgers.edu/roa.html")
MAN_END

MAN_BEGIN ("Willems (1986)", "ppgb", 20021215)
NORMAL ("Lei Willems (1986): \"Robust formant analysis.\" %%IPO report% #529: 1\\--25. "
	"Eindhoven: Institute for Perception Research.")
MAN_END

}

/* End of file manual_references.c */

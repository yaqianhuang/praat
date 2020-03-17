/* MAT_numerics.cpp
 *
 * Copyright (C) 2018-2020 David Weenink
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "NUMlapack.h"
#include "MAT_numerics.h"
#include "SVD.h"
#include "PAIRWISE_SUM.h"

void MAT_getEigenSystemFromSymmetricMatrix_preallocated (MAT eigenvectors, VEC eigenvalues, constMATVU const& m, bool sortAscending) {
	Melder_assert (m.nrow == m.ncol);
	Melder_assert (eigenvalues.size == m.ncol);
	Melder_assert (eigenvectors.nrow == eigenvectors.ncol);
	Melder_assert (m.nrow == eigenvectors.nrow);

	integer lwork = -1, info, ncol = m.ncol;
	double wt [1];
	
	eigenvectors <<= m;
	/*
		0. No need to transpose a because it is a symmetric matrix
		1. Query for the size of the work array
	*/
	(void) NUMlapack_dsyev_ ("V", "U", ncol, & eigenvectors [1] [1], ncol, & eigenvalues [1], wt, lwork, & info);

	Melder_require (info == 0,
		U"dsyev initialization code = ", info, U").");
	
	lwork = Melder_iceiling (wt [0]);
	autoVEC work = newVECraw (lwork);
	/*
		2. Calculate the eigenvalues and eigenvectors (row-wise)
	*/
	(void) NUMlapack_dsyev_ ("V", "U", ncol, & eigenvectors [1] [1], ncol, & eigenvalues [1], & work [1], lwork, & info);
	Melder_require (info == 0,
		U"dsyev code = ", info, U").");
	/*
		3. Eigenvalues are returned in ascending order
	*/
	if (! sortAscending) {
		for (integer i = 1; i <= m.ncol / 2; i ++) {
			const integer ilast = m.ncol - i + 1;
			std::swap (eigenvalues [i], eigenvalues [ilast]);
				for (integer j = 1; j <= m.ncol; j ++)
					std::swap (eigenvectors [i] [j], eigenvectors [ilast] [j]);
		}
	}
}

void MAT_getEigenSystemFromSymmetricMatrix (constMAT a, autoMAT *out_eigenvectors, autoVEC *out_eigenvalues, bool sortAscending) {
	Melder_assert (a.nrow == a.ncol);	
	autoVEC eigenvalues = newVECraw (a.nrow);
	autoMAT eigenvectors = newMATraw (a.nrow, a.ncol);	
	
	MAT_getEigenSystemFromSymmetricMatrix_preallocated (eigenvectors.get(), eigenvalues.get(), a, sortAscending);
	
	if (out_eigenvectors)
		*out_eigenvectors = eigenvectors.move ();
	if (out_eigenvalues)
		*out_eigenvalues = eigenvalues.move ();
}

void MAT_eigenvectors_decompress (constMAT eigenvectors, constVEC eigenvalues_re, constVEC eigenvalues_im, autoMAT *out_eigenvectors_reim) {
	const integer n = eigenvalues_re.size;	
	Melder_assert (eigenvalues_im.size == n);
	Melder_assert (eigenvectors.nrow == n && eigenvectors.ncol == eigenvectors.nrow);
		
	autoMAT eigenvectors_reim = newMATzero (n, 2 * n);
	integer pair_index = 0;
	for (integer ivec = 1; ivec <= eigenvalues_re.size; ivec ++) {
		/*
			Eigenvalues of a real matrix are either real or occur in complex conjugate pairs
		*/
		if (eigenvalues_im [ivec] == 0.0) { // real eigenvalue
			for (integer j = 1; j <= n; j ++)
				eigenvectors_reim [j] [2 * ivec - 1] = eigenvectors [ivec] [j];
		} else if (ivec > 1 && eigenvalues_re [ivec] == eigenvalues_re [ivec - 1] &&
			eigenvalues_im [ivec] == -eigenvalues_im [ivec - 1] && ivec - pair_index > 1) {
			for (integer j = 1; j <= n; j ++) {
				eigenvectors_reim [j] [2 * (ivec - 1) - 1]= eigenvectors [ivec - 1] [j];
				eigenvectors_reim [j] [2 * (ivec - 1)] = eigenvectors [ivec] [j];
				eigenvectors_reim [j] [2 * ivec - 1]  = eigenvectors [ivec - 1] [j];
				eigenvectors_reim [j] [2 * ivec] = eigenvectors [ivec] [j] != 0.0 ? -eigenvectors [ivec] [j] : 0.0; // avoid -0
			}
			pair_index = ivec; // guard for multiple equal complex conjugate pairs
		}
	}
	if (out_eigenvectors_reim)
		*out_eigenvectors_reim = eigenvectors_reim.move();
}

void MAT_getEigenSystemFromGeneralMatrix (constMAT a, autoMAT *out_left_ev, autoMAT *out_right_ev, autoVEC *out_eigenvalues_re, autoVEC *out_eigenvalues_im) {
	Melder_assert (a.nrow == a.ncol);
	integer n = a.nrow;
	
	autoMAT data = newMATtranspose (a);   // lapack is fortran storage
	autoVEC eigenvalues_re = newVECraw (n);
	autoVEC eigenvalues_im = newVECraw (n);

	autoMAT left_ev;
	double *p_left_ev = nullptr;
	if (out_left_ev) {
		left_ev = newMATraw (n, n);
		p_left_ev = & left_ev [1] [1];
	}
	autoMAT right_ev;
	double *p_right_ev = nullptr;
	if (out_right_ev) {
		right_ev = newMATraw (n, n);
		p_right_ev = & right_ev [1] [1];
	}
	conststring8 jobvl = out_left_ev ? "V" : "N";
	conststring8 jobvr = out_right_ev ? "V" : "N";
	double wtmp;
	integer lwork = -1, info;
	NUMlapack_dgeev_ (jobvl, jobvr, n, & data [1] [1], n, & eigenvalues_re [1],
		& eigenvalues_im [1], p_left_ev, n, p_right_ev, n, & wtmp, lwork, & info);
	Melder_require (info == 0,
		U"NUMlapack_dhseqr_ query returns error ", info, U".");
	
	lwork = Melder_iceiling (wtmp);
	autoVEC work = newVECraw (lwork);
	NUMlapack_dgeev_ (jobvl, jobvr, n, & data [1] [1], n, & eigenvalues_re [1],
		& eigenvalues_im [1], p_left_ev, n, p_right_ev, n, & work [1], lwork, & info);
	Melder_require (info == 0,
		U"NUMlapack_dhseqr_ returns error ", info, U".");
	
	if (out_right_ev)
		*out_right_ev = right_ev.move();
	if (out_left_ev)
		*out_left_ev = left_ev.move();
	if (out_eigenvalues_re)
		*out_eigenvalues_re = eigenvalues_re.move();
	if (out_eigenvalues_im)
		*out_eigenvalues_im = eigenvalues_im.move();
}

void MAT_asPrincipalComponents_preallocated (MATVU result, constMATVU const& m, integer numberOfComponents) {
	Melder_assert (numberOfComponents  > 0 && numberOfComponents <= m.ncol);
	Melder_assert (result.nrow == m.nrow && result.ncol == numberOfComponents);
	autoSVD svd = SVD_createFromGeneralMatrix (m);
	MATmul (result, m, svd -> v.verticalBand (1, result.ncol));
}

autoMAT MAT_asPrincipalComponents (constMATVU m, integer numberOfComponents) {
	Melder_assert (numberOfComponents  > 0 && numberOfComponents <= m.ncol);
	autoMAT result = newMATraw (m.nrow, numberOfComponents);
	MAT_asPrincipalComponents_preallocated (result.get(), m, numberOfComponents);
	return result;
}

void MATpseudoInverse (MATVU const& target, constMATVU const& mat, double tolerance) {
	Melder_assert (target.nrow == mat.ncol && target.ncol == mat.nrow);
	autoSVD me = SVD_createFromGeneralMatrix (mat);
	(void) SVD_zeroSmallSingularValues (me.get(), tolerance);
	for (integer irow = 1; irow <= target.nrow; irow ++) {
		for (integer icol = 1; icol <= target.ncol; icol ++) {
			PAIRWISE_SUM (
				longdouble, sum,
				integer, mat.ncol,
				integer k = 1,
				my d [k] == 0.0 ? 0.0 : my v [irow] [k] * my u [icol] [k] / my d [k],
				k += 1
			)
			target [irow] [icol] = double (sum);
		}
	}
}

autoMAT newMATpseudoInverse (constMATVU const& mat, double tolerance) {
	autoMAT result = newMATraw (mat.ncol, mat.nrow);
	MATpseudoInverse (result.all(), mat, tolerance);
	return result;
}

/* End of file MAT_numerics.cpp */

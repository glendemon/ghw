/* 
 * File:   main.h
 * Author: Victor
 *
 * Created on January 1, 2014, 8:46 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <cstdlib>
#include "flint/nmod_matxx.h"
#include "flint/flintxx/ltuple.h"
#include "flint/permxx.h"

using namespace std;
using namespace flint;

typedef nmod_matxx matrix_t;

void print_matrix(const matrix_t& obj);
void print_matrix(const nmod_mat_t& obj, mp_limb_t modulus);
inline matrix_t check_matrix(const matrix_t& C)
{
    nmod_mat_t X;
    nmod_mat_init(X, C.cols(), C.cols(), C.modulus());
    slong rank = nmod_mat_nullspace(X,C._mat());
	matrix_t check_matrix = matrix_t(C.cols(), C.cols() - rank, C.modulus());
	for (slong i = 0; i < check_matrix.rows(); i++)
	{
		for (slong j = 0; j < check_matrix.cols(); j++)
		{
			nmod_mat_entry(check_matrix._mat(), i, j) = nmod_mat_entry(X, i, j);
		}
	}
    nmod_mat_clear(X);
	return check_matrix.transpose().evaluate();
}

#endif	/* MAIN_H */


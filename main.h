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
typedef vector<ptrdiff_t> set_t;
typedef vector<set_t> powerset_t;

static fmpzxx CHUNK_SIZE(1073741824 / 1024); // 1gb/32

void print_matrix(const matrix_t& obj);
void print_matrix(const nmod_mat_t& obj, mp_limb_t modulus);

vector<ptrdiff_t> range(ptrdiff_t limit);
powerset_t powerset(vector<ptrdiff_t> M, const fmpzxx &start, const fmpzxx &offset);

void print_weight_hierarchy(const matrix_t& C);
vector<ptrdiff_t> weight_hierarchy(const matrix_t& C);
ptrdiff_t matrix_rank(const matrix_t& m);

inline matrix_t generate_check_matrix(const matrix_t& C)
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

inline matrix_t matrix_from_columns(const matrix_t& m, set_t indexes)
{
	matrix_t result(m.rows(), indexes.size(), m.modulus());
	for (set_t::const_iterator iterator = indexes.begin(), end = indexes.end(); iterator != end; ++iterator)
	{
        for (size_t i = 0; i < m.rows(); i++)
        {
            nmod_mat_entry(result._mat(), i, *iterator) = nmod_mat_entry(m._mat(), i, *iterator);
        }
	}
	return result;
}

#endif	/* MAIN_H */


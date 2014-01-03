/* 
 * File:   main.h
 * Author: Victor
 *
 * Created on January 1, 2014, 8:46 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <omp.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "flint/nmod_matxx.h"
#include "flint/flintxx/ltuple.h"
#include "flint/permxx.h"

using namespace std;
using namespace flint;

typedef nmod_matxx matrix_t;
typedef vector<ptrdiff_t> set_t;
typedef vector<set_t> powerset_t;

static fmpzxx CHUNK_SIZE(1073741824 / 256); // 1gb/32

void print_matrix(const matrix_t& obj);
void print_matrix(const nmod_mat_t& obj, mp_limb_t modulus);

vector<ptrdiff_t> range(ptrdiff_t limit);
powerset_t powerset(const vector<ptrdiff_t>& M, const fmpzxx &start, const fmpzxx &offset);

void print_weight_hierarchy(const matrix_t& C);
vector<ulong> weight_hierarchy(const matrix_t& C);
ulong matrix_rank(const matrix_t& m);

inline matrix_t generate_check_matrix(const matrix_t& C)
{
    nmod_mat_t X;
    slong size = max(C.rows(),C.cols());
    nmod_mat_init(X, size, size, C.modulus());
    slong rank = nmod_mat_nullspace(X,C._mat());
	matrix_t check_matrix = matrix_t(size, rank, C.modulus());
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
    slong col = 0;
	for (set_t::const_iterator iterator = indexes.begin(), end = indexes.end(); iterator != end; ++iterator)
	{
        for (slong row = 0; row < m.rows(); row++)
        {
            nmod_mat_entry(result._mat(), row, col) = nmod_mat_entry(m._mat(), row, *iterator);
        }
        col++;
	}
	return result;
}

inline matrix_t load_matrix(std::string filename)
{
	int rows, cols, base;
    if (filename.empty())
        filename.append("data.txt");
	ifstream data(filename.c_str());
	string line;

	if (data.is_open())
	{
		//get sizes
		getline(data, line);
		istringstream iss(line);
		iss >> rows;
		iss >> cols;
		iss >> base;
        matrix_t matrix(rows, cols, base);

		//get matrix
		int row = 0, col = 0;
		while (getline(data, line))
		{
			istringstream iss(line);
			float n;
			col = 0;
			while (iss >> n)
			{
                nmod_mat_entry(matrix._mat(), row, col) = n;
				col++;
			}
			row++;
		}
        return matrix;
	}
	else
    {
		cout << "Unable to open file " << filename << ". Use random matrix" << endl;
        matrix_t C(5, 15, 5);
        frandxx state;
        C.set_randtest(state);
        return C;
    }
	
}

#endif	/* MAIN_H */


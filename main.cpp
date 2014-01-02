/* 
 * File:   main.cpp
 * Author: Victor
 *
 * Created on January 1, 2014, 6:25 PM
 */

#include "main.h"

/*
 * 
 */
int main(int argc, char** argv) {
    matrix_t C(5, 10, 5);
    frandxx state;
    C.set_randtest(state);
    print_matrix(C);
    print_matrix(generate_check_matrix(C));
    print_weight_hierarchy(C);

    return 0;
}

void print_weight_hierarchy(const matrix_t& C)
{
	vector<ptrdiff_t> weights = weight_hierarchy(C);
    for (size_t i = 0; i < weights.size(); i++)
	{
        cout << "d_" << i+1 << ": " << weights[i] << endl;
	}
}

vector<ptrdiff_t> weight_hierarchy(const matrix_t& C)
{
	matrix_t check_matrix = generate_check_matrix(C);
	ptrdiff_t generator_rank = matrix_rank(C);

    vector<ptrdiff_t> min_length;
	for (int r = 1; r <= generator_rank; r++)
		min_length.push_back(check_matrix.cols()+1);

	fmpzxx n(2), limit;
	vector<ptrdiff_t> set = range(check_matrix.cols());
	n.pow(set.size());
    if (n < CHUNK_SIZE)
        limit = fmpzxx(1);
    else
        limit = (n + CHUNK_SIZE - fmpzxx(1)) / CHUNK_SIZE; //ceil(n / CHUNK_SIZE)
	#pragma omp parallel
	{
		for (fmpzxx i(0); i < limit; i = i + fmpzxx(1))
		{
			#pragma omp single nowait
			{
				fmpzxx start;
				start = i * CHUNK_SIZE;
				set_t I;
				powerset_t indexes = powerset(set, start, CHUNK_SIZE);
				for (powerset_t::const_iterator iterator = indexes.begin(), end = indexes.end(); iterator != end; ++iterator)
				{
					I = *iterator;
					size_t length = I.size();
					ptrdiff_t rank = matrix_rank(matrix_from_columns(check_matrix, I));
					for (ptrdiff_t r = 1; r <= generator_rank; r++)
					{
						if (length - rank >= r)
						{
							if (length < min_length[r-1])
							{
								min_length[r-1] = length;
							}
						}
					}
				}
			}
		}
	}
    return min_length;
}

ptrdiff_t matrix_rank(const matrix_t& m)
{
    return m.rank();
}


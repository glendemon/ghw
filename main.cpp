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
int main(int, char** argv) {
    matrix_t C = load_matrix(argv[1] != NULL ? std::string(argv[1]) : "");
    print_matrix(C);
    print_matrix(generate_check_matrix(C));
    print_weight_hierarchy(C);

    return 0;
}

void print_weight_hierarchy(const matrix_t& C)
{
	vector<ulong> weights = weight_hierarchy(C);
    for (size_t i = 0; i < weights.size(); i++)
	{
        cout << "d_" << i+1 << ": " << weights[i] << endl;
	}
}

vector<ulong> weight_hierarchy(const matrix_t& C)
{
	matrix_t check_matrix = generate_check_matrix(C);
	ulong generator_rank = matrix_rank(C);

    vector<ulong> min_length;
	for (ulong r = 1; r <= generator_rank; r++)
		min_length.push_back(check_matrix.cols()+1);

	fmpzxx n(2), limit;
	vector<ptrdiff_t> set = range(check_matrix.cols());
	n = n.pow(set.size());
    if (n < CHUNK_SIZE)
        limit = fmpzxx(1);
    else
        limit = (n + CHUNK_SIZE - fmpzxx(1)) / CHUNK_SIZE; //ceil(n / CHUNK_SIZE)

    slong i, limit2 = limit.to<slong>();
    #pragma omp parallel for
    for (i = 0; i < limit2; i++)
    {
        fmpzxx start;
        start = i * CHUNK_SIZE;
        set_t I;
        powerset_t indexes = powerset(set, start, CHUNK_SIZE);
        for (powerset_t::const_iterator iterator = indexes.begin(), end = indexes.end(); iterator != end; ++iterator)
        {
            I = *iterator;
            size_t length = I.size();
            ulong rank = matrix_rank(matrix_from_columns(check_matrix, I));
            for (ulong r = 1; r <= generator_rank; r++)
            {
                if (length - rank >= r)
                {
                    #pragma omp critical(minlength)
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
    return min_length;
}

ulong matrix_rank(const matrix_t& m)
{
    return m.rank();
}


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
	vector<ulong> weights = weight_hierarchy_adjacency_classes(C);
    for (size_t i = 0; i < weights.size(); i++)
	{
        cout << "d_" << i+1 << ": " << weights[i] << endl;
	}
}

vector<ulong> weight_hierarchy_brute_force(const matrix_t& C)
{
	matrix_t check_matrix = generate_check_matrix(C);
	ulong generator_rank = matrix_rank(C);

    vector<ulong> min_length;
	for (ulong r = 1; r <= generator_rank; r++)
		min_length.push_back(check_matrix.cols()+1);

	fmpzxx n(2), limit;
	set_t set = range(check_matrix.cols());
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

vector<ulong> weight_hierarchy_adjacency_classes(const matrix_t& C)
{
    matrix_t check_matrix = generate_check_matrix(C);
    vector< std::pair<size_t, set_t> > classes = adjacency_classes(C);
    map<size_t, size_t> result_map = map<size_t, size_t>();
    for (size_t i = 0; i < classes.size(); i++)
	{
        if (classes[i].second.size() > result_map[classes[i].first])
            result_map[classes[i].first] = classes[i].second.size();
	}

    ulong generator_rank = matrix_rank(C);
    vector<ulong> weights;
	for (ulong r = 1; r <= generator_rank; r++)
		weights.push_back(check_matrix.cols()+1);

    for (map<size_t, size_t>::iterator it = result_map.begin(); it != result_map.end(); it++)
    {
        size_t rank = (*it).first;
        size_t lenght = (*it).second;
        //cout << "rank " << rank << ": " << lenght << endl;
        if (lenght-rank > 0 && lenght < weights[lenght-rank-1])
        {
            do {
            weights[lenght-rank-1] = lenght;
            lenght--;
            } while (lenght-rank > 0 && weights[lenght-rank-1] == check_matrix.cols()+1);
        }
    }
    return weights;
}

vector< std::pair<size_t, set_t> > adjacency_classes(const matrix_t& C)
{
	matrix_t check_matrix = generate_check_matrix(C);
    fmpzxx n(2), limit;
    set_t set = range(check_matrix.cols());

    vector< std::pair<size_t, set_t> > result = vector< std::pair<size_t, set_t> >();
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
        ptrdiff_t J;
        powerset_t indexes = powerset(set, start, CHUNK_SIZE);
        for (powerset_t::const_iterator iterator = indexes.begin(), end = indexes.end(); iterator != end; ++iterator)
        {
            I = *iterator;
//            if (is_set_in_result(I, result))
//                continue;
            set_t ids(I);
            for (set_t::const_iterator it = set.begin(), end = set.end(); it != end; ++it)
            {
                J = *it;
                if (I.count(J))
                    continue;
                set_t temp(I);
                temp.insert(J);
                ulong rank = matrix_rank(matrix_from_columns(check_matrix, temp));
                if (rank == I.size())
                    ids.insert(J);
            }
            std::pair<size_t, set_t> pair(I.size(), ids);
            result.push_back(pair);
            if (ids.size() == check_matrix.cols())
                break;
        }
    }
    return result;
}


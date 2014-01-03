#include "main.h"

/**
 * Print matrix
 * (fix bug in nmod_mat_print_pretty)
 * @param obj
 */
void print_matrix(const matrix_t& obj)
{
    print_matrix(obj._mat(), obj.modulus());
}

/**
 * Print matrix
 * (fix bug in nmod_mat_print_pretty)
 * @param obj
 */
void print_matrix(const nmod_mat_t& obj, mp_limb_t modulus)
{
    slong i, j;
    int width;
    char fmt[FLINT_BITS + 5];

    flint_printf("<%wd x %wd integer matrix mod %wu>\n", nmod_mat_nrows(obj), nmod_mat_ncols(obj), modulus);

    if (!(nmod_mat_ncols(obj)) || !(nmod_mat_nrows(obj)))
        return;

    width = n_sizeinbase(modulus, 10);

    sprintf(fmt, "%%%dlu", width);
    for (i = 0; i < nmod_mat_nrows(obj); i++)
    {
        printf("[");

        for (j = 0; j < nmod_mat_ncols(obj); j++)
        {
            printf(fmt, nmod_mat_entry(obj, i, j));
            if (j + 1 < nmod_mat_ncols(obj))
                printf(" ");
        }

        printf("]\n");
    }
}

powerset_t powerset(const vector<ptrdiff_t>& M, const fmpzxx &start = fmpzxx(0), const fmpzxx &offset = fmpzxx(0))
{
	//M --множество
    size_t w = M.size(); //--кол-во элементов множества
	powerset_t result = powerset_t();
    fmpzxx n(2), i, real_start, limit;
	n = n.pow(w);
	if (!offset.is_zero() && start + offset <= n)
    {
		limit = start + offset;
        result.reserve(offset.to<size_t>());
    }
	else
		limit = n;
    if (start.is_zero())//pass empty set
        real_start.set_one();
    else
        real_start = start;
    for ( i = real_start; i < limit; i = i + fmpzxx(1) ) //--перебор битовых маск
    {
		set_t set = set_t();
        set.reserve(w);
        for (size_t j = 0; j < w; j++ ) //--перебор битов в маске
		{
            if ( (i & fmpzxx(1 << j)) != 0) //--если j-й бит установлен
			{
			   set.push_back(M[j]);
			}
		}
		result.push_back(set);
    }
    return result;
}

vector<ptrdiff_t> range(ptrdiff_t limit)
{
	vector<ptrdiff_t> result = vector<ptrdiff_t>();
	for (ptrdiff_t i = 0; i < limit; i++)
		result.push_back(i);
	return result;
}
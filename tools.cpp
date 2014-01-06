#include <set>

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

ulong matrix_rank(const matrix_t& m)
{
    return m.rank();
}

bool is_set_in_result(const set_t& I, const vector< std::pair<size_t, set_t> >& result)
{
    for (vector< std::pair<size_t, set_t> >::const_iterator iterator = result.begin(), end = result.end(); iterator != end; ++iterator)
    {
        std::pair<size_t, set_t> res = *iterator;
        bool is_subset = std::includes(res.second.begin(), res.second.end(), I.begin(), I.end());
        if (is_subset)
        {
            return is_subset;
        }
    }
    return false;
}

powerset_t powerset(const set_t& M, const fmpzxx &start = fmpzxx(0), const fmpzxx &offset = fmpzxx(0))
{
	//M --множество
    size_t w = M.size(); //--кол-во элементов множества
	powerset_t result = powerset_t();
    fmpzxx n(2);
    fmpz_t i, real_start, limit;
	n = n.pow(w);
	if (!offset.is_zero() && start + offset <= n)
    {
        fmpz_init_set(limit, start._fmpz());
        fmpz_add(limit, limit, offset._fmpz());
        result.reserve(offset.to<size_t>());
    }
	else
        fmpz_init_set(limit, n._fmpz());
    if (start.is_zero())//pass empty set
        fmpz_init_set_ui(real_start, 1);
    else
        fmpz_init_set(real_start, start._fmpz());
    for ( fmpz_init_set(i, real_start); fmpz_cmp(i, limit) < 0; fmpz_add_ui(i, i, 1) ) //--перебор битовых маск
    {
		set_t set = set_t();
        set_t::iterator it = M.begin();
        for (size_t j = 0; j < w; j++ ) //--перебор битов в маске
		{
            if ( fmpz_tstbit (i, j) != 0) //--если j-й бит установлен
			{
			   set.insert(*it);
			}
            it++;
		}
		result.push_back(set);
    }
    return result;
}

set_t range(ptrdiff_t limit)
{
	set_t result = set_t();
	for (ptrdiff_t i = 0; i < limit; i++)
		result.insert(i);
	return result;
}
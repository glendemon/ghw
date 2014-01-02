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

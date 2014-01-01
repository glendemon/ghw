#include "main.h"

/**
 * Print matrix
 * (fix bug in nmod_mat_print_pretty)
 * @param obj
 */
void print_mat(const mat_t& obj)
{
    slong i, j;
    int width;
    char fmt[FLINT_BITS + 5];

    flint_printf("<%wd x %wd integer matrix mod %wu>\n", obj.rows(), obj.cols(), obj.modulus());

    if (!(obj.cols()) || !(obj.rows()))
        return;

    width = n_sizeinbase(obj.modulus(), 10);

    sprintf(fmt, "%%%dlu", width);
    for (i = 0; i < obj.rows(); i++)
    {
        printf("[");

        for (j = 0; j < obj.cols(); j++)
        {
            printf(fmt, obj.at(i, j)._limb());
            if (j + 1 < obj.cols())
                printf(" ");
        }

        printf("]\n");
    }
}
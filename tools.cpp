#include "main.h"

void print_mat(const mat_t& obj)
{
//    nmod_mat_print_pretty(obj._mat());
//    return;
    for (int i = 0; i < obj.rows(); i++)
    {
        for (int j = 0; j < obj.cols(); j++)
        {
            cout << obj.at(i, j)._limb() << " ";
        }
        cout << endl;
    }
}
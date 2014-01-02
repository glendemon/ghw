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
    mat_t S1(5, 10, 5);
    frandxx state;
    S1.set_randtest(state);
    print_mat(S1);
    cout << "Matrix rank: " << S1.rank() << endl;

    nmod_mat_t X;
    nmod_mat_init(X, S1.cols(), S1.cols(), S1.modulus());
    slong rank;
    rank = nmod_mat_nullspace(X,S1._mat());
    cout << "Matrix rank: " << rank << endl;
    print_mat(X, S1.modulus());
    nmod_mat_clear(X);

    return 0;
}


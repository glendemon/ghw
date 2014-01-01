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
    int n = 10;
    mat_t S1(5, 10, 5);
    frandxx state;
    S1.set_randtest(state);
    std::cout << S1.at(1,1) << std::endl;
    print_mat(S1);

    flint_printf("S1:\n");
    print_pretty(S1);
    flint_printf("\n\n");

    return 0;
}


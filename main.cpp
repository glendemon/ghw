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

    return 0;
}


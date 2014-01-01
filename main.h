/* 
 * File:   main.h
 * Author: Victor
 *
 * Created on January 1, 2014, 8:46 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <cstdlib>
#include "flint/nmod_matxx.h"

using namespace std;
using namespace flint;

typedef nmod_matxx mat_t;

void print_mat(const mat_t& obj);

#endif	/* MAIN_H */


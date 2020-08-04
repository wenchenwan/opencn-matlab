#pragma once

//#define CLP_USE_OPENBLAS 3

#include "time_prof.h"
//#include <functions.h>
#include <stddef.h>


#if defined(MATLAB_MEX_FILE)
  #include <mex.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
int simplex_solve(const double* f, const int* fsize, const double* Avs, const int* Ais, const int* Ajs,
		const int* Asize, int An, const double* b, const int* bsize, const double* beq, const int* beqsize, double* C, int* Csize);

#ifdef __cplusplus
}
#endif

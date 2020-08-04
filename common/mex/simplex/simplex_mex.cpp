
//#define COIN_USE_BLAS
#include <ClpSimplex.hpp>
#include <CoinBuild.hpp>
#include <CoinHelperFunctions.hpp>
#include <CoinModel.hpp>
#include <CoinTime.hpp>
#include <cassert>
#include <iomanip>

#include "mex.h"

#include "c_simplex.hpp"

// build with: mex -I/usr/include/coin -lClp -lCoinUtils -largeArrayDims ../coinor-clp-test/src/test1.cpp
// Usage: test1(f, [A; Aeq], b, beq);

void mexFunction_sparse(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("MATLAB:clp:invalidNumOutputs", "One output required.");
    }

    if (nrhs != 4) {
        mexErrMsgIdAndTxt("MATLAB:clp:invalidNumInputs", "Usage: test1(f, [A; Aeq], b, beq)");
    }

    const mxArray *A = prhs[1];

    if (!mxIsSparse(A)) {
        mexErrMsgIdAndTxt("MATLAB:clp:invalidInputSparisty", "A  must be a sparse array.");
    }

    const double *b = mxGetPr(prhs[2]);
    const double *beq = mxGetPr(prhs[3]);
    const double *f = mxGetPr(prhs[0]);

    mwSize Mb = mxGetM(prhs[2]);
    mwSize Mbeq = mxGetM(prhs[3]);

    mwSize nzmax = mxGetNzmax(A);
    mwSize ncol = mxGetN(A);
    /* NOTE: nnz is the actual number of nonzeros and is stored as the
     * last element of the jc array where the size of the jc array is the
     * number of columns + 1 */
    mwSize nnz = *(mxGetJc(A) + ncol);
    const mwSize *ir = mxGetIr(A);
    const mwSize *jc = mxGetJc(A);
    const double *pr = mxGetPr(A);

    // mexPrintf("input: %dx%d with %d non-zeros\n", mxGetM(A), mxGetN(A), nnz);

    // mexPrintf("Ir = ");
    // for(int i = 0; i < nnz; i++) {
    //     mexPrintf("%d ", ir[i]);
    // }
    // mexPrintf("\n");

    // mexPrintf("Jc = ");
    // for(int i = 0; i < ncol; i++) {
    //     mexPrintf("%d ", jc[i]);
    // }
    // mexPrintf("\n");

    // mexPrintf("Pr = ");
    // for(int i = 0; i < nnz; i++) {
    //     mexPrintf("%.1f ", pr[i]);
    // }
    // mexPrintf("\n");

    // we need to convert the matlab format into triples
    const int Nmax = 1 << 14;
    static int indRow[Nmax];
    static int indCol[Nmax];
    static double rowub[Nmax];
    static double rowlb[Nmax];

    // We do not set any limits on the primal variables
    // static double colub[Nmax];
    // static double collb[Nmax];

    if (nnz > Nmax) {
        mexErrMsgIdAndTxt("MATLAB:clp:memory",
                          "Not enough space in static arrays for matrix conversion, increase Nmax in test1.cpp");
    }

    int col = -1;
    int k = 0;
    for (int j = 0; j < ncol; j++) {
        for (k = jc[j]; k < jc[j + 1]; k++) {
            indRow[k] = ir[k];
            indCol[k] = j;
        }
    }

    // CoinPackedMatrix (const bool colordered, const int *rowIndices, const int *colIndices, const double *elements,
    // CoinBigIndex numels)
    CoinPackedMatrix matrix(true, indRow, indCol, pr, nnz);
    // mexPrintf("CoinPackedMatrix: %dx%d\n", matrix.getNumRows(), matrix.getNumCols());

    // A x <= b
    std::copy(b, b + Mb, rowub);				 //  b for upper bound
    std::fill(rowlb, rowlb + Mb, -COIN_DBL_MAX); // -Infinity for lower bound

    // A x == b
    std::copy(beq, beq + Mbeq, rowub + Mb); // both lower and upper bounds are the same on EQ
    std::copy(beq, beq + Mbeq, rowlb + Mb);

    ClpSimplex model;
    model.setLogLevel(0);
    // constraint matrix, lower/upper bound of x, objective coeffs, lower/upper bounds of complex variables
    model.loadProblem(matrix, nullptr, nullptr, f, rowlb, rowub);
    model.setPrimalTolerance(1e-6);
    model.setDualTolerance(1e-6);

    model.initialDualSolve();
    model.dual();

    double *solution = model.primalColumnSolution();

    plhs[0] = mxCreateDoubleMatrix(ncol, 1, mxREAL);
    double *solution_data = mxGetPr(plhs[0]);
    std::copy(solution, solution + ncol, solution_data);
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("MATLAB:clp:invalidNumOutputs", "One output required.");
    }

    if (nrhs != 4) {
        mexErrMsgIdAndTxt("MATLAB:clp:invalidNumInputs", "Usage: test1(f, [A; Aeq], b, beq)");
    }

    double *f = mxGetPr(prhs[0]);
    double *A = mxGetPr(prhs[1]);
    double *b = mxGetPr(prhs[2]);
    double *beq = mxGetPr(prhs[3]);

    mwSize Mb = mxGetM(prhs[2]);
    mwSize Mbeq = mxGetM(prhs[3]);

    const size_t nrow = mxGetM(prhs[1]);
    const size_t ncol = mxGetN(prhs[1]);

    SimplexProblem pb;
    pb.f = prhs[0];
    pb.f = Matrix{f, mxGetM(prhs[0]), mxGetN(prhs[0])};
    pb.A = Matrix{A, nrow, ncol};
    pb.b = Matrix{b, Mb, 1};
    pb.beq = Matrix{beq, Mbeq, 1};

    plhs[0] = mxCreateDoubleMatrix(static_cast<mwSize>(ncol), 1, mxREAL);
    double *solution_data = mxGetPr(plhs[0]);

    SimplexSolution solution;
    solution.solution = Matrix{solution_data, ncol, 1};

    simplex_solve(&pb, &solution);
}

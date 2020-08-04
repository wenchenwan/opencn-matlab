#include "c_simplex.hpp"

#define COIN_USE_BLAS
#include <ClpSimplex.hpp>
#include <CoinBuild.hpp>
#include <CoinHelperFunctions.hpp>
#include <CoinModel.hpp>
#include <CoinTime.hpp>
#include <cassert>
#include <iomanip>

#include "mex.h"
static const int Nmax = 1 << 20;
static int indRow[Nmax];
static int indCol[Nmax];
static double rowub[Nmax];
static double rowlb[Nmax];
static double sparse_data[Nmax];

void simplex_solve(SimplexProblem *pb, SimplexSolution *solution)
{
    // we need to convert the dense matrix into triples

    PROF_BLOCK(simplex_solve);

    static const double zero_threshold = 0;

    const int nrow = pb->A->size[0];
    const int ncol = pb->A->size[1];

    //    mexPrintf("A: %dx%d\n", nrow, ncol);

    // We do not set any limits on the primal variables
    // static double colub[Nmax];
    // static double collb[Nmax];

    if (nrow * ncol > Nmax) {

        //        mexErrMsgIdAndTxt(
        //            "MATLAB:clp:memory",
        //            "Not enough space in static arrays for matrix conversion, increase Nmax in
        //            test1.cpp");
    }
    size_t index = 0;
    {
        PROF_BLOCK(sparse_convert);

        for (int j = 0; j < ncol; j++) {
            for (int i = 0; i < nrow; i++) {
                if (fabs(pb->A->data[i + j * nrow]) > zero_threshold) {
                    indRow[index] = i;
                    indCol[index] = j;
                    sparse_data[index] = pb->A->data[i + j * nrow];
                    ++index;
                }
            }
        }
    }

    //    fprintf(stdout, "Keeping %d/%d entries\n", index, nrow * ncol);

    // CoinPackedMatrix (const bool colordered, const int *rowIndices, const int *colIndices, const
    // double *elements, CoinBigIndex numels)
    PROF_IN(CoinPackedMatrix);
    // 3512x135, 6512x135
    CoinPackedMatrix matrix(true, indRow, indCol, sparse_data, index);
    PROF_OUT(CoinPackedMatrix);
    //    fprintf(stdout, "CoinPackedMatrix: %dx%d\n", matrix.getNumRows(), matrix.getNumCols());

    // A x <= b
    std::copy(pb->b->data, pb->b->data + pb->b->size[0], rowub); //  b for upper bound
    std::fill(rowlb, rowlb + pb->b->size[0], -COIN_DBL_MAX);     // -Infinity for lower bound

    // A x == b
    std::copy(pb->beq.data, pb->beq.data + pb->beq.size[0],
              rowub + pb->b->size[0]); // both lower and upper bounds are the same on EQ
    std::copy(pb->beq.data, pb->beq.data + pb->beq.size[0], rowlb + pb->b->size[0]);
    ClpSimplex model;
    {
        PROF_BLOCK(ModelPrepare);
        model.setLogLevel(0);
        // constraint matrix, lower/upper bound of x, objective coeffs, lower/upper bounds of
        // complex variables
        model.loadProblem(matrix, nullptr, nullptr, pb->f.data, rowlb, rowub);
        model.setPrimalTolerance(1e-6);
        model.setDualTolerance(1e-6);
    }

    {
        {
            PROF_BLOCK(initial_dual_solve);
            model.initialDualSolve();
        }
        {
            PROF_BLOCK(dual);
            model.dual();
        }
    }
    //    fprintf(stdout, "simplex_solve: model.status() =  %d\n", model.status());
    double *sol = model.primalColumnSolution();
    std::copy(sol, sol + ncol, solution->solution->data);
}

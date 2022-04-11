extern int errno;
#include "cpp_simplex.hpp"

#include <coin/ClpSimplex.hpp>
#include <coin/ClpInterior.hpp>
#include <coin/CoinBuild.hpp>
#include <coin/CoinHelperFunctions.hpp>
#include <coin/CoinModel.hpp>
#include <coin/CoinTime.hpp>
#include <cassert>
#include <iomanip>

#include "time_prof.h"

#define USE_INTERIOR_POINT 0

#define SIMPLEX_DLEVEL 0

static const int Nmax = 1 << 20;
//static int indRow[Nmax];
//static int indCol[Nmax];
static double rowub[Nmax];
static double rowlb[Nmax];
static double collb[Nmax];
//static double sparse_data[Nmax];

//void simplex_solve(SimplexProblem *pb, SimplexSolution *solution)
//{
//    // we need to convert the dense matrix into triples
//
//    PROF_BLOCK(simplex_solve);
//
//    static const double zero_threshold = 0;
//
//    const int nrow = pb->A->size[0];
//    const int ncol = pb->A->size[1];
//
//    //    mexPrintf("A: %dx%d\n", nrow, ncol);
//
//    // We do not set any limits on the primal variables
//    // static double colub[Nmax];
//    // static double collb[Nmax];
//
//    if (nrow * ncol > Nmax) {
//
//        //        mexErrMsgIdAndTxt(
//        //            "MATLAB:clp:memory",
//        //            "Not enough space in static arrays for matrix conversion, increase Nmax in
//        //            test1.cpp");
//    }
//    size_t index = 0;
//    {
//        PROF_BLOCK(sparse_convert);
//
//        for (int j = 0; j < ncol; j++) {
//            for (int i = 0; i < nrow; i++) {
//                if (fabs(pb->A->data[i + j * nrow]) > zero_threshold) {
//                    indRow[index] = i;
//                    indCol[index] = j;
//                    sparse_data[index] = pb->A->data[i + j * nrow];
//                    ++index;
//                }
//            }
//        }
//    }
//
//    //    fprintf(stdout, "Keeping %d/%d entries\n", index, nrow * ncol);
//
//    // CoinPackedMatrix (const bool colordered, const int *rowIndices, const int *colIndices, const
//    // double *elements, CoinBigIndex numels)
//    PROF_IN(CoinPackedMatrix);
//    // 3512x135, 6512x135
//    CoinPackedMatrix matrix(true, indRow, indCol, sparse_data, index);
//    PROF_OUT(CoinPackedMatrix);
//    //    fprintf(stdout, "CoinPackedMatrix: %dx%d\n", matrix.getNumRows(), matrix.getNumCols());
//
//    // A x <= b
//    std::copy(pb->b->data, pb->b->data + pb->b->size[0], rowub); //  b for upper bound
//    std::fill(rowlb, rowlb + pb->b->size[0], -COIN_DBL_MAX);     // -Infinity for lower bound
//
//    // A x == b
//    std::copy(pb->beq.data, pb->beq.data + pb->beq.size[0],
//              rowub + pb->b->size[0]); // both lower and upper bounds are the same on EQ
//    std::copy(pb->beq.data, pb->beq.data + pb->beq.size[0], rowlb + pb->b->size[0]);
//    ClpSimplex model;
//    {
//        PROF_BLOCK(ModelPrepare);
//        model.setLogLevel(0);
//        // constraint matrix, lower/upper bound of x, objective coeffs, lower/upper bounds of
//        // complex variables
//        model.loadProblem(matrix, nullptr, nullptr, pb->f.data, rowlb, rowub);
//        model.setPrimalTolerance(1e-6);
//        model.setDualTolerance(1e-6);
//    }
//
//    {
//        {
//            PROF_BLOCK(initial_dual_solve);
//            model.initialDualSolve();
//        }
//        {
//            PROF_BLOCK(dual);
//            model.dual();
//        }
//    }
//    //    fprintf(stdout, "simplex_solve: model.status() =  %d\n", model.status());
//    double *sol = model.primalColumnSolution();
//    std::copy(sol, sol + ncol, solution->solution->data);
//}

/* FROM c_simplex.c
simplex_solve(&f_data[0], &fsize[0], &Avs_data[0], &Ais_data[0], &Ajs_data[0],
                  v->size[0], &b_data[0], &bsize[0], &beq_data[0], &beqsize[0],
                  &C_data[0], &Csize[0]);*/

int simplex_solve(const double* f, const int* fsize, const double* Avs, const int* Ais, const int* Ajs,
		const int* Asize, int An, const double* b, const int* bsize, const double* beq, const int* beqsize, double* C, int* Csize)
{
    // we need to convert the dense matrix into triples

//	printf("simplex_solve: fsize = [%d,%d], Asize = [%d,%d], bsize = [%d,%d], beqsize = [%d,%d]\n",
//			fsize[0], fsize[1], Asize[0], Asize[1], bsize[0], bsize[1], beqsize[0], beqsize[1]);
//	fflush(stdout);

#ifdef DEBUG_RS274
    fprintf(stdout, ".");
    fflush(stdout);
#endif

    PROF_BLOCK(simplex_solve);

//	const int nrow = Asize[0];
	const int ncol = Asize[1];

    // We do not set any limits on the primal variables
    // static double colub[Nmax];
    // static double collb[Nmax];

    // CoinPackedMatrix (const bool colordered, const int *rowIndices, const int *colIndices, const
    // double *elements, CoinBigIndex numels)
    PROF_IN(CoinPackedMatrix);
    // 3512x135, 6512x135
//    printf("Atot: %d elements\n", An);
//    for(int i = 0; i < An; i++) {
////    	printf("[%3d %3d] = %f\n", Ais[i], Ajs[i], Avs[i]);
//    	printf("%.4f ", Avs[i]);
//    }
    CoinPackedMatrix matrix(true, Ais, Ajs, Avs, An);

    PROF_OUT(CoinPackedMatrix);
//    fprintf(stdout, "CoinPackedMatrix: %dx%d\n", matrix.getNumRows(), matrix.getNumCols());
//    matrix.dumpMatrix();

    // A x <= b
    // std::copy(b, b + bsize[0], rowub); //  b for upper bound
    std::memcpy(rowub, b, sizeof(double)*bsize[0]);
    std::fill(rowlb, rowlb + bsize[0], -COIN_DBL_MAX);     // -Infinity for lower bound
    std::fill(collb, collb + bsize[0], 0.0);

    // A x == b
    // std::copy(beq, beq + beqsize[0], rowub + bsize[0]); // both lower and upper bounds are the same on EQ
    std::memcpy(rowub + bsize[0], beq, sizeof(double)*beqsize[0]);

    // std::copy(beq, beq + beqsize[0], rowlb + bsize[0]);
    std::memcpy(rowlb + bsize[0], beq, sizeof(double)*beqsize[0]);

#if USE_INTERIOR_POINT
    ClpInterior model;
    {   
        PROF_BLOCK(ModelPrepare);
        model.setLogLevel( SIMPLEX_DLEVEL );
        // constraint matrix, lower/upper bound of x, objective coeffs, lower/upper bounds of
        // complex variables
        model.loadProblem(matrix, collb, nullptr, f, rowlb, rowub);
        model.setPrimalTolerance(1e-6);
        model.setDualTolerance(1e-6);
//        model.setMaximumSeconds(1.0);
    }
    model.setDelta(1);
    model.primalDual();
//    model.primalDual();
    const double *sol = model.getColSolution();


#else
    ClpSimplex model;
    {
        PROF_BLOCK(ModelPrepare);
        model.setLogLevel( SIMPLEX_DLEVEL );
        // constraint matrix, lower/upper bound of x, objective coeffs, lower/upper bounds of
        // complex variables
        model.loadProblem(matrix, collb, nullptr, f, rowlb, rowub);
        model.setPrimalTolerance(1e-6);
        model.setDualTolerance(1e-6);
        //model.setMaximumSeconds(1.0);
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
    double *sol = model.primalColumnSolution();
#endif


//    fprintf(stdout, "simplex_solve: model.status() =  %d\n", model.status());
//    fprintf(stdout, "coeffs = ");
    for(int i = 0; i < ncol; i++) {
    	C[i] = sol[i];
//    	fprintf(stdout, "%.2f ", C[i]);
    }
//    fprintf(stdout, "\n");
//    fflush(stdout);

    Csize[0] = ncol;
    Csize[1] = 1;
    
    return model.status();
}

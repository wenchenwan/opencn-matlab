//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:00:11
//

// Include Files
#include "ConstrTransP5Struct.h"
#include "ConstrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include <emmintrin.h>

// Function Definitions
//
// function CurvStruct = ConstrTransP5Struct(trafo, HSC, Poff, ...
//                                           Aoff, Uoff, Doff, avec, uvec,...
//                                           CoeffP5, FeedRate)
//
// Arguments    : bool trafo
//                bool HSC
//                const double Poff[3]
//                const double Aoff[3]
//                const double Uoff[3]
//                double Doff
//                const double avec[2][3]
//                const double uvec[2][3]
//                const double CoeffP5[6][3]
//                double FeedRate
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrTransP5Struct(bool trafo, bool HSC, const double Poff[3], const double Aoff[3],
                         const double Uoff[3], double Doff, const double avec[2][3],
                         const double uvec[2][3], const double CoeffP5[6][3], double FeedRate,
                         CurvStruct *b_CurvStruct)
{
    double P0[3];
    double P1[3];
    double dv[3];
    double dv1[3];
    // 'ConstrTransP5Struct:4' Type        = CurveType.TransP5;
    // 'ConstrTransP5Struct:6' P0          = mypolyval(CoeffP5,0);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    // 'mypolyval:12' for i=2:nc
    // 'ConstrTransP5Struct:7' P1          = mypolyval(CoeffP5,1);
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    // 'mypolyval:4' [nD, nc] = size(p);
    // 'mypolyval:5' siz_x    = length(x);
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:8' y = zeros(nD, siz_x);
    // 'mypolyval:9' if nc > 0
    // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
    P1[0] = CoeffP5[0][0];
    P1[1] = CoeffP5[0][1];
    P1[2] = CoeffP5[0][2];
    // 'mypolyval:12' for i=2:nc
    for (int i{0}; i < 5; i++) {
        __m128d r;
        double P0_tmp;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        P0[0] = CoeffP5[i + 1][0];
        P0[1] = CoeffP5[i + 1][1];
        P0_tmp = CoeffP5[i + 1][2];
        P0[2] = P0_tmp;
        // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
        r = _mm_loadu_pd(&P1[0]);
        _mm_storeu_pd(&P1[0], _mm_add_pd(r, _mm_loadu_pd((const double *)&CoeffP5[i + 1][0])));
        P1[2] += P0_tmp;
    }
    // 'ConstrTransP5Struct:8' A0          = avec(:,1);
    // 'ConstrTransP5Struct:9' A1          = avec(:,end);
    // 'ConstrTransP5Struct:10' U0          = uvec(:,1);
    // 'ConstrTransP5Struct:11' U1          = uvec(:,end);
    // 'ConstrTransP5Struct:13' Cprim       = zeros(3, 1);
    // 'ConstrTransP5Struct:14' delta       = 0.0;
    // 'ConstrTransP5Struct:15' evec        = zeros(3, 1);
    // 'ConstrTransP5Struct:16' theta       = 0.0;
    // 'ConstrTransP5Struct:17' pitch       = 0.0;
    // 'ConstrTransP5Struct:19' CurvStruct  = ConstrCurvStruct(Type, ZSpdMode.NN, trafo, HSC, ...
    // 'ConstrTransP5Struct:20'                                    Poff, Aoff, Uoff, Doff, P0, P1,
    // A0, ... 'ConstrTransP5Struct:21'                                    A1, U0, U1, Cprim, delta,
    // evec, theta,... 'ConstrTransP5Struct:22'                                    pitch, CoeffP5,
    // FeedRate);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, trafo, HSC, Poff, Aoff, Uoff, Doff, P0, P1,
                     *(double(*)[3]) & avec[0][0], *(double(*)[3]) & avec[1][0],
                     *(double(*)[3]) & uvec[0][0], *(double(*)[3]) & uvec[1][0], dv, 0.0, dv1, 0.0,
                     0.0, CoeffP5, FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrTransP5Struct.cpp
//
// [EOF]
//

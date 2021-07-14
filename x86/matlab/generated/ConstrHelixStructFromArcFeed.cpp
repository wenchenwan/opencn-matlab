//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "ConstrHelixStructFromArcFeed.h"
#include "ConstrHelixStruct.h"
#include "CorrectArcCenter.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : double p0x
//                double p0y
//                double p0z
//                double p1x
//                double p1y
//                double p1z
//                double cx
//                double cy
//                double cz
//                double rotation
//                const double evec[3]
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrHelixStructFromArcFeed(double p0x, double p0y, double p0z, double p1x, double p1y,
                                  double p1z, double cx, double cy, double cz, double rotation,
                                  const double evec[3], CurvStruct *b_CurvStruct)
{
    double P0[3];
    double P1[3];
    double b[3];
    double b_Cprim[3];
    double Cprim[2];
    double b_P0[2];
    double b_P1[2];
    double a__1;
    double a__2;
    double a__3;
    double delta;
    double phi0;
    double phi1;
    double theta;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    P0[0] = p0x;
    P0[1] = p0y;
    P0[2] = p0z;
    P1[0] = p1x;
    P1[1] = p1y;
    P1[2] = p1z;
    if (evec[0] > 0.5) {
        __m128d r;
        __m128d r3;
        __m128d r6;
        __m128d r8;
        double R0_idx_1;
        double R0_idx_2;
        //  YZ
        Cprim[0] = cy;
        Cprim[1] = cz;
        b_P0[0] = p0y;
        b_P0[1] = p0z;
        b_P1[0] = p1y;
        b_P1[1] = p1z;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__1, &delta);
        b_Cprim[0] = cx;
        b_Cprim[1] = Cprim[0];
        b_Cprim[2] = Cprim[1];
        r = _mm_loadu_pd(&P0[0]);
        r3 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r, r3));
        R0_idx_1 = b[0] * evec[2] - evec[0] * (p0z - Cprim[1]);
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        r6 = _mm_loadu_pd(&P1[0]);
        r8 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r6, r8));
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        phi1 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          b[0] * evec[2] - evec[0] * (p1z - Cprim[1]));
    } else if (evec[1] > 0.5) {
        __m128d r10;
        __m128d r2;
        __m128d r5;
        __m128d r7;
        double R0_idx_0;
        double R0_idx_2;
        //  ZX
        Cprim[0] = cz;
        Cprim[1] = cx;
        b_P0[0] = p0z;
        b_P0[1] = p0x;
        b_P1[0] = p1z;
        b_P1[1] = p1x;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__2, &delta);
        b_Cprim[0] = Cprim[1];
        b_Cprim[1] = cy;
        b_Cprim[2] = Cprim[0];
        r2 = _mm_loadu_pd(&P0[0]);
        r5 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r2, r5));
        R0_idx_0 = evec[1] * (p0z - Cprim[0]) - b[1] * evec[2];
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        r7 = _mm_loadu_pd(&P1[0]);
        r10 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r7, r10));
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        phi0 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          evec[1] * (p1z - Cprim[0]) - b[1] * evec[2]);
    } else {
        __m128d r1;
        __m128d r11;
        __m128d r4;
        __m128d r9;
        double R0_idx_0;
        double R0_idx_1;
        //  XY
        Cprim[0] = cx;
        Cprim[1] = cy;
        b_P0[0] = p0x;
        b_P0[1] = p0y;
        b_P1[0] = p1x;
        b_P1[1] = p1y;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__3, &delta);
        b_Cprim[0] = Cprim[0];
        b_Cprim[1] = Cprim[1];
        b_Cprim[2] = cz;
        r1 = _mm_loadu_pd(&P0[0]);
        r4 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r1, r4));
        b[2] = p0z - cz;
        R0_idx_0 = evec[1] * b[2] - b[1] * evec[2];
        R0_idx_1 = b[0] * evec[2] - evec[0] * b[2];
        r9 = _mm_loadu_pd(&P1[0]);
        r11 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r9, r11));
        b[2] = p1z - cz;
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        phi1 = std::atan2(b[0] * evec[2] - evec[0] * b[2], evec[1] * b[2] - b[1] * evec[2]);
    }
    theta = phi1 - phi0;
    if (rotation > 0.0) {
        if (theta <= 0.0) {
            theta += 6.2831853071795862;
        }
        theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
    } else {
        if (theta >= 0.0) {
            theta -= 6.2831853071795862;
        }
        theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
    }
    ConstrHelixStruct(P0, P1, b_Cprim, delta, evec, theta,
                      (((evec[0] * p1x + evec[1] * p1y) + evec[2] * p1z) -
                       ((evec[0] * p0x + evec[1] * p0y) + evec[2] * p0z)) /
                          theta * 2.0 * 3.1415926535897931,
                      1.0, ZSpdMode_NN, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrHelixStructFromArcFeed.cpp
//
// [EOF]
//

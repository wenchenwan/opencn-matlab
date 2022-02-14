//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:26:14
//

// Include Files
#include "ConstrHelixStructFromArcFeed.h"
#include "ConstrCurvStruct.h"
#include "CorrectArcCenter.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function CurvStruct = ConstrHelixStructFromArcFeed(p0x, p0y, p0z, p1x, p1y, p1z, cx, cy, cz,
// rotation, evec)
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
    double dv[6][3];
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
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrHelixStructFromArcFeed:3' coder.inline("never");
    // 'ConstrHelixStructFromArcFeed:5' P0 = [p0x, p0y, p0z]';
    P0[0] = p0x;
    P0[1] = p0y;
    P0[2] = p0z;
    // 'ConstrHelixStructFromArcFeed:6' P1 = [p1x, p1y, p1z]';
    P1[0] = p1x;
    P1[1] = p1y;
    P1[2] = p1z;
    // 'ConstrHelixStructFromArcFeed:7' C  = [cx, cy, cz]';
    // 'ConstrHelixStructFromArcFeed:9' if evec(1) > 0.5
    if (evec[0] > 0.5) {
        __m128d r;
        __m128d r1;
        __m128d r6;
        __m128d r7;
        double R0_idx_1;
        double R0_idx_2;
        //  YZ
        // 'ConstrHelixStructFromArcFeed:10' [~, Cprim, delta] = CorrectArcCenter([P0(2), P0(3)]',
        // [P1(2), P1(3)]', [C(2), C(3)]');
        Cprim[0] = cy;
        Cprim[1] = cz;
        b_P0[0] = p0y;
        b_P0[1] = p0z;
        b_P1[0] = p1y;
        b_P1[1] = p1z;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__1, &delta);
        // 'ConstrHelixStructFromArcFeed:11' Cprim = [cx, Cprim(1), Cprim(2)]';
        b_Cprim[0] = cx;
        b_Cprim[1] = Cprim[0];
        b_Cprim[2] = Cprim[1];
        // 'ConstrHelixStructFromArcFeed:12' R0 = cross(evec, P0 - Cprim);
        r = _mm_loadu_pd(&P0[0]);
        r1 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r, r1));
        R0_idx_1 = b[0] * evec[2] - evec[0] * (p0z - Cprim[1]);
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        // 'ConstrHelixStructFromArcFeed:13' R1 = cross(evec, P1 - Cprim);
        r6 = _mm_loadu_pd(&P1[0]);
        r7 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r6, r7));
        // 'ConstrHelixStructFromArcFeed:14' phi0 = atan2(R0(3), R0(2));
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        // 'ConstrHelixStructFromArcFeed:15' phi1 = atan2(R1(3), R1(2));
        phi1 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          b[0] * evec[2] - evec[0] * (p1z - Cprim[1]));
    } else if (evec[1] > 0.5) {
        __m128d r10;
        __m128d r3;
        __m128d r5;
        __m128d r8;
        double R0_idx_0;
        double R0_idx_2;
        // 'ConstrHelixStructFromArcFeed:17' elseif evec(2) > 0.5
        //  ZX
        // 'ConstrHelixStructFromArcFeed:18' [~, Cprim, delta] = CorrectArcCenter([P0(3), P0(1)]',
        // [P1(3), P1(1)]', [C(3), C(1)]');
        Cprim[0] = cz;
        Cprim[1] = cx;
        b_P0[0] = p0z;
        b_P0[1] = p0x;
        b_P1[0] = p1z;
        b_P1[1] = p1x;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__2, &delta);
        // 'ConstrHelixStructFromArcFeed:19' Cprim = [Cprim(2), cy, Cprim(1)]';
        b_Cprim[0] = Cprim[1];
        b_Cprim[1] = cy;
        b_Cprim[2] = Cprim[0];
        // 'ConstrHelixStructFromArcFeed:20' R0 = cross(evec, P0 - Cprim);
        r3 = _mm_loadu_pd(&P0[0]);
        r5 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r3, r5));
        R0_idx_0 = evec[1] * (p0z - Cprim[0]) - b[1] * evec[2];
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        // 'ConstrHelixStructFromArcFeed:21' R1 = cross(evec, P1 - Cprim);
        r8 = _mm_loadu_pd(&P1[0]);
        r10 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r8, r10));
        // 'ConstrHelixStructFromArcFeed:22' phi1 = atan2(R0(3), R0(1));
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        // 'ConstrHelixStructFromArcFeed:23' phi0 = atan2(R1(3), R1(1));
        phi0 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          evec[1] * (p1z - Cprim[0]) - b[1] * evec[2]);
    } else {
        __m128d r11;
        __m128d r2;
        __m128d r4;
        __m128d r9;
        double R0_idx_0;
        double R0_idx_1;
        // 'ConstrHelixStructFromArcFeed:25' else
        //  XY
        // 'ConstrHelixStructFromArcFeed:26' [~, Cprim, delta] = CorrectArcCenter([P0(1), P0(2)]',
        // [P1(1), P1(2)]', [C(1), C(2)]');
        Cprim[0] = cx;
        Cprim[1] = cy;
        b_P0[0] = p0x;
        b_P0[1] = p0y;
        b_P1[0] = p1x;
        b_P1[1] = p1y;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__3, &delta);
        // 'ConstrHelixStructFromArcFeed:27' Cprim = [Cprim(1), Cprim(2), cz]';
        b_Cprim[0] = Cprim[0];
        b_Cprim[1] = Cprim[1];
        b_Cprim[2] = cz;
        // 'ConstrHelixStructFromArcFeed:28' R0 = cross(evec, P0 - Cprim);
        r2 = _mm_loadu_pd(&P0[0]);
        r4 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r2, r4));
        b[2] = p0z - cz;
        R0_idx_0 = evec[1] * b[2] - b[1] * evec[2];
        R0_idx_1 = b[0] * evec[2] - evec[0] * b[2];
        // 'ConstrHelixStructFromArcFeed:29' R1 = cross(evec, P1 - Cprim);
        r9 = _mm_loadu_pd(&P1[0]);
        r11 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r9, r11));
        b[2] = p1z - cz;
        // 'ConstrHelixStructFromArcFeed:30' phi0 = atan2(R0(2), R0(1));
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        // 'ConstrHelixStructFromArcFeed:31' phi1 = atan2(R1(2), R1(1));
        phi1 = std::atan2(b[0] * evec[2] - evec[0] * b[2], evec[1] * b[2] - b[1] * evec[2]);
    }
    // 'ConstrHelixStructFromArcFeed:35' theta = phi1 - phi0;
    theta = phi1 - phi0;
    // 'ConstrHelixStructFromArcFeed:37' devec = dot(evec, P1) - dot(evec, P0);
    // 'ConstrHelixStructFromArcFeed:39' if rotation > 0
    if (rotation > 0.0) {
        // 'ConstrHelixStructFromArcFeed:40' if theta <= 0
        if (theta <= 0.0) {
            // 'ConstrHelixStructFromArcFeed:41' theta = theta + 2*pi;
            theta += 6.2831853071795862;
        }
        // 'ConstrHelixStructFromArcFeed:43' theta = theta + (rotation-1)*2*pi;
        theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
    } else {
        // 'ConstrHelixStructFromArcFeed:45' else
        // 'ConstrHelixStructFromArcFeed:46' if theta >= 0
        if (theta >= 0.0) {
            // 'ConstrHelixStructFromArcFeed:47' theta = theta - 2*pi;
            theta -= 6.2831853071795862;
        }
        // 'ConstrHelixStructFromArcFeed:49' theta = theta + (rotation+1)*2*pi;
        theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
    }
    // 'ConstrHelixStructFromArcFeed:53' pitch = devec/theta*2*pi;
    // 'ConstrHelixStructFromArcFeed:54' CurvStruct = ConstrHelixStruct(P0, P1, Cprim, delta, evec,
    // theta, pitch, 1, ZSpdMode.NN); 'ConstrHelixStruct:3' CoeffP5     = zeros(3, 6);
    // 'ConstrHelixStruct:5' CurvStruct  = ConstrCurvStruct(CurveType.Helix, ZSpdMode, P0, P1,
    // Cprim, delta, evec, theta, pitch, CoeffP5, FeedRate);
    for (int i{0}; i < 6; i++) {
        dv[i][0] = 0.0;
        dv[i][1] = 0.0;
        dv[i][2] = 0.0;
    }
    ConstrCurvStruct(CurveType_Helix, ZSpdMode_NN, P0, P1, b_Cprim, delta, evec, theta,
                     (((evec[0] * p1x + evec[1] * p1y) + evec[2] * p1z) -
                      ((evec[0] * p0x + evec[1] * p0y) + evec[2] * p0z)) /
                         theta * 2.0 * 3.1415926535897931,
                     dv, 1.0, b_CurvStruct);
    // 'ConstrHelixStruct:6' coder.cstructname(CurvStruct, 'CurvStruct');
}

} // namespace ocn

//
// File trailer for ConstrHelixStructFromArcFeed.cpp
//
// [EOF]
//

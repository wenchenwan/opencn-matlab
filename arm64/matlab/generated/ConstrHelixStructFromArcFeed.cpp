//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "ConstrHelixStructFromArcFeed.h"
#include "ConstrHelixStruct.h"
#include "CorrectArcCenter.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include <cmath>

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
        double R0_idx_1;
        double R0_idx_2;
        double b_idx_0;
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
        b_idx_0 = p0x - cx;
        R0_idx_1 = b_idx_0 * evec[2] - evec[0] * (p0z - Cprim[1]);
        R0_idx_2 = evec[0] * (p0y - Cprim[0]) - b_idx_0 * evec[1];
        b_idx_0 = p1x - cx;
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        phi1 = std::atan2(evec[0] * (p1y - Cprim[0]) - b_idx_0 * evec[1],
                          b_idx_0 * evec[2] - evec[0] * (p1z - Cprim[1]));
    } else if (evec[1] > 0.5) {
        double R0_idx_0;
        double R0_idx_2;
        double b_idx_1;
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
        b_idx_1 = p0y - cy;
        R0_idx_0 = evec[1] * (p0z - Cprim[0]) - b_idx_1 * evec[2];
        R0_idx_2 = evec[0] * b_idx_1 - (p0x - Cprim[1]) * evec[1];
        b_idx_1 = p1y - cy;
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        phi0 = std::atan2(evec[0] * b_idx_1 - (p1x - Cprim[1]) * evec[1],
                          evec[1] * (p1z - Cprim[0]) - b_idx_1 * evec[2]);
    } else {
        double R0_idx_0;
        double R0_idx_1;
        double b_idx_2;
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
        b_idx_2 = p0z - cz;
        R0_idx_0 = evec[1] * b_idx_2 - (p0y - Cprim[1]) * evec[2];
        R0_idx_1 = (p0x - Cprim[0]) * evec[2] - evec[0] * b_idx_2;
        b_idx_2 = p1z - cz;
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        phi1 = std::atan2((p1x - Cprim[0]) * evec[2] - evec[0] * b_idx_2,
                          evec[1] * b_idx_2 - (p1y - Cprim[1]) * evec[2]);
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

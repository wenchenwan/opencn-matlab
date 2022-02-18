//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
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
#include <emmintrin.h>

// Function Definitions
//
// ConstrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis (x,y,z) with a circular
//  motion in the perpendicular plan (XY, ZX, YZ).
//
//  trafo     : Flag for the trafo directive
//  Poff      : Offset on the position {X, Y, Z}
//  Aoff      : Offset on the angle {A, B, C}
//  Uoff      : Offset on the sub-axis {U, V, W}
//  Doff      : Offset for the diameter of the tool
//  p0x       : Value in the x axis of point P0
//  p0y       : Value in the y axis of point P0
//  p0z       : Value in the z axis of point P0
//  p1x       : Value in the x axis of point P1
//  p1y       : Value in the y axis of point P1
//  p1z       : Value in the z axis of point P1
//  cx        : Value in the x axis of the center C
//  cy        : Value in the y axis of the center C
//  cz        : Value in the z axis of the center C
//  A0        : Vector of the orientation angles at starting pose
//  A1        : Vector of the orientation angles at ending pose
//  U0        : Vector of for the secondary axes at starting pose
//  U1        : Vector of for the secondary axes at ending pose
//  rotation  : Number of rotation to realize (positive ; Clockwise |
//              negative ; Counterclockwise | zero ; pure translation)
//  evec      : Unit vector orthogonal to the planned of the projected circle
//
//  CurvStruct : The resulting CurvStruct
//
// Arguments    : bool trafo
//                const double Poff[3]
//                const double Aoff[3]
//                const double Uoff[3]
//                double Doff
//                double p0x
//                double p0y
//                double p0z
//                double p1x
//                double p1y
//                double p1z
//                double cx
//                double cy
//                double cz
//                const double A0[3]
//                const double A1[3]
//                const double U0[3]
//                const double U1[3]
//                double rotation
//                const double evec[3]
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrHelixStructFromArcFeed(bool trafo, const double Poff[3], const double Aoff[3],
                                  const double Uoff[3], double Doff, double p0x, double p0y,
                                  double p0z, double p1x, double p1y, double p1z, double cx,
                                  double cy, double cz, const double A0[3], const double A1[3],
                                  const double U0[3], const double U1[3], double rotation,
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
    double devec;
    double phi0;
    double phi1;
    double pitch;
    double theta;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    //  Create vectors
    P0[0] = p0x;
    P0[1] = p0y;
    P0[2] = p0z;
    P1[0] = p1x;
    P1[1] = p1y;
    P1[2] = p1z;
    if (evec[0] > 0.5) {
        __m128d r;
        __m128d r2;
        __m128d r5;
        __m128d r7;
        double R0_idx_1;
        double R0_idx_2;
        //  YZ
        Cprim[0] = cy;
        Cprim[1] = cz;
        CorrectArcCenter(*(double(*)[2]) & P0[1], *(double(*)[2]) & P1[1], Cprim, &a__1, &delta);
        b_Cprim[0] = cx;
        b_Cprim[1] = Cprim[0];
        b_Cprim[2] = Cprim[1];
        r = _mm_loadu_pd(&P0[0]);
        r2 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r, r2));
        R0_idx_1 = b[0] * evec[2] - evec[0] * (p0z - Cprim[1]);
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        r5 = _mm_loadu_pd(&P1[0]);
        r7 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r5, r7));
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        phi1 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          b[0] * evec[2] - evec[0] * (p1z - Cprim[1]));
    } else if (evec[1] > 0.5) {
        __m128d r10;
        __m128d r11;
        __m128d r4;
        __m128d r6;
        double R0_idx_0;
        double R0_idx_2;
        //  ZX
        Cprim[0] = cz;
        b_P0[0] = p0z;
        b_P1[0] = p1z;
        Cprim[1] = cx;
        b_P0[1] = p0x;
        b_P1[1] = p1x;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__2, &delta);
        b_Cprim[0] = Cprim[1];
        b_Cprim[1] = cy;
        b_Cprim[2] = Cprim[0];
        r4 = _mm_loadu_pd(&P0[0]);
        r6 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r4, r6));
        R0_idx_0 = evec[1] * (p0z - Cprim[0]) - b[1] * evec[2];
        R0_idx_2 = evec[0] * b[1] - b[0] * evec[1];
        r10 = _mm_loadu_pd(&P1[0]);
        r11 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r10, r11));
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        phi0 = std::atan2(evec[0] * b[1] - b[0] * evec[1],
                          evec[1] * (p1z - Cprim[0]) - b[1] * evec[2]);
    } else {
        __m128d r1;
        __m128d r3;
        __m128d r8;
        __m128d r9;
        double R0_idx_0;
        double R0_idx_1;
        //  XY
        Cprim[0] = cx;
        Cprim[1] = cy;
        CorrectArcCenter(*(double(*)[2]) & P0[0], *(double(*)[2]) & P1[0], Cprim, &a__3, &delta);
        b_Cprim[0] = Cprim[0];
        b_Cprim[1] = Cprim[1];
        b_Cprim[2] = cz;
        r1 = _mm_loadu_pd(&P0[0]);
        r3 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r1, r3));
        b[2] = p0z - cz;
        R0_idx_0 = evec[1] * b[2] - b[1] * evec[2];
        R0_idx_1 = b[0] * evec[2] - evec[0] * b[2];
        r8 = _mm_loadu_pd(&P1[0]);
        r9 = _mm_loadu_pd(&b_Cprim[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r8, r9));
        b[2] = p1z - cz;
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        phi1 = std::atan2(b[0] * evec[2] - evec[0] * b[2], evec[1] * b[2] - b[1] * evec[2]);
    }
    //  Theta is in [-2 pi; 2 pi]
    theta = phi1 - phi0;
    //  Projection of P10 along the linear motion. Note evec is a unit vector.
    devec = (evec[0] * (p1x - p0x) + evec[1] * (p1y - p0y)) + evec[2] * (p1z - p0z);
    if (rotation == 0.0) {
        //  Linear motion
        theta = 0.0;
        pitch = devec;
    } else {
        if (rotation > 0.0) {
            //  Clockwise rotation
            if (theta <= 0.0) {
                theta += 6.2831853071795862;
            }
            theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
        } else {
            //  Counterclockwise rotation
            if (theta >= 0.0) {
                theta -= 6.2831853071795862;
            }
            theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
        }
        if (theta == 0.0) {
            //  Linear motion
            pitch = devec;
        } else {
            pitch = devec / theta * 2.0 * 3.1415926535897931;
        }
    }
    ConstrHelixStruct(trafo, Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, U0, U1, b_Cprim, delta, evec,
                      theta, pitch, 1.0, ZSpdMode_NN, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrHelixStructFromArcFeed.cpp
//
// [EOF]
//

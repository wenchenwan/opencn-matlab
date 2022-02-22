//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:18:27
//

// Include Files
#include "ConstrHelixStructFromArcFeed.h"
#include "ConstrHelixStruct.h"
#include "CorrectArcCenter.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include <cmath>

// Function Definitions
//
// function CurvStruct = ConstrHelixStructFromArcFeed(trafo, ...
//                       Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
//                       p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
//                       evec)
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
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrHelixStructFromArcFeed:33' coder.inline("never");
    //  Create vectors
    // 'ConstrHelixStructFromArcFeed:37' P0 = [p0x, p0y, p0z]';
    P0[0] = p0x;
    P0[1] = p0y;
    P0[2] = p0z;
    // 'ConstrHelixStructFromArcFeed:38' P1 = [p1x, p1y, p1z]';
    P1[0] = p1x;
    P1[1] = p1y;
    P1[2] = p1z;
    // 'ConstrHelixStructFromArcFeed:39' C  = [cx,  cy,  cz]';
    // 'ConstrHelixStructFromArcFeed:41' if evec(1) > 0.5
    if (evec[0] > 0.5) {
        double R0_idx_1;
        double R0_idx_2;
        double b_idx_0;
        //  YZ
        // 'ConstrHelixStructFromArcFeed:42' indYZ = [2, 3];
        // 'ConstrHelixStructFromArcFeed:43' [~, Cprim, delta] = CorrectArcCenter(P0(indYZ),
        // P1(indYZ), C(indYZ));
        Cprim[0] = cy;
        Cprim[1] = cz;
        CorrectArcCenter(*(double(*)[2]) & P0[1], *(double(*)[2]) & P1[1], Cprim, &a__1, &delta);
        // 'ConstrHelixStructFromArcFeed:44' Cprim = [cx, Cprim(1), Cprim(2)]';
        b_Cprim[0] = cx;
        b_Cprim[1] = Cprim[0];
        b_Cprim[2] = Cprim[1];
        // 'ConstrHelixStructFromArcFeed:45' R0 = cross(evec, P0 - Cprim);
        b_idx_0 = p0x - cx;
        R0_idx_1 = b_idx_0 * evec[2] - evec[0] * (p0z - Cprim[1]);
        R0_idx_2 = evec[0] * (p0y - Cprim[0]) - b_idx_0 * evec[1];
        // 'ConstrHelixStructFromArcFeed:46' R1 = cross(evec, P1 - Cprim);
        b_idx_0 = p1x - cx;
        // 'ConstrHelixStructFromArcFeed:47' phi0 = atan2(R0(3), R0(2));
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        // 'ConstrHelixStructFromArcFeed:48' phi1 = atan2(R1(3), R1(2));
        phi1 = std::atan2(evec[0] * (p1y - Cprim[0]) - b_idx_0 * evec[1],
                          b_idx_0 * evec[2] - evec[0] * (p1z - Cprim[1]));
    } else if (evec[1] > 0.5) {
        double R0_idx_0;
        double R0_idx_2;
        double b_idx_1;
        // 'ConstrHelixStructFromArcFeed:50' elseif evec(2) > 0.5
        //  ZX
        // 'ConstrHelixStructFromArcFeed:51' indZX = [3, 1];
        // 'ConstrHelixStructFromArcFeed:52' [~, Cprim, delta] = CorrectArcCenter(P0(indZX),
        // P1(indZX), C(indZX));
        Cprim[0] = cz;
        b_P0[0] = p0z;
        b_P1[0] = p1z;
        Cprim[1] = cx;
        b_P0[1] = p0x;
        b_P1[1] = p1x;
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__2, &delta);
        // 'ConstrHelixStructFromArcFeed:53' Cprim = [Cprim(2), cy, Cprim(1)]';
        b_Cprim[0] = Cprim[1];
        b_Cprim[1] = cy;
        b_Cprim[2] = Cprim[0];
        // 'ConstrHelixStructFromArcFeed:54' R0 = cross(evec, P0 - Cprim);
        b_idx_1 = p0y - cy;
        R0_idx_0 = evec[1] * (p0z - Cprim[0]) - b_idx_1 * evec[2];
        R0_idx_2 = evec[0] * b_idx_1 - (p0x - Cprim[1]) * evec[1];
        // 'ConstrHelixStructFromArcFeed:55' R1 = cross(evec, P1 - Cprim);
        b_idx_1 = p1y - cy;
        // 'ConstrHelixStructFromArcFeed:56' phi1 = atan2(R0(3), R0(1));
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        // 'ConstrHelixStructFromArcFeed:57' phi0 = atan2(R1(3), R1(1));
        phi0 = std::atan2(evec[0] * b_idx_1 - (p1x - Cprim[1]) * evec[1],
                          evec[1] * (p1z - Cprim[0]) - b_idx_1 * evec[2]);
    } else {
        double R0_idx_0;
        double R0_idx_1;
        double b_idx_2;
        // 'ConstrHelixStructFromArcFeed:59' else
        //  XY
        // 'ConstrHelixStructFromArcFeed:60' indXY = [1,2];
        // 'ConstrHelixStructFromArcFeed:61' [~, Cprim, delta] = CorrectArcCenter(P0(indXY),
        // P1(indXY), C(indXY));
        Cprim[0] = cx;
        Cprim[1] = cy;
        CorrectArcCenter(*(double(*)[2]) & P0[0], *(double(*)[2]) & P1[0], Cprim, &a__3, &delta);
        // 'ConstrHelixStructFromArcFeed:62' Cprim = [Cprim(1), Cprim(2), cz]';
        b_Cprim[0] = Cprim[0];
        b_Cprim[1] = Cprim[1];
        b_Cprim[2] = cz;
        // 'ConstrHelixStructFromArcFeed:63' R0 = cross(evec, P0 - Cprim);
        b_idx_2 = p0z - cz;
        R0_idx_0 = evec[1] * b_idx_2 - (p0y - Cprim[1]) * evec[2];
        R0_idx_1 = (p0x - Cprim[0]) * evec[2] - evec[0] * b_idx_2;
        // 'ConstrHelixStructFromArcFeed:64' R1 = cross(evec, P1 - Cprim);
        b_idx_2 = p1z - cz;
        // 'ConstrHelixStructFromArcFeed:65' phi0 = atan2(R0(2), R0(1));
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        // 'ConstrHelixStructFromArcFeed:66' phi1 = atan2(R1(2), R1(1));
        phi1 = std::atan2((p1x - Cprim[0]) * evec[2] - evec[0] * b_idx_2,
                          evec[1] * b_idx_2 - (p1y - Cprim[1]) * evec[2]);
    }
    // 'ConstrHelixStructFromArcFeed:70' P10 = P1 - P0;
    //  Theta is in [-2 pi; 2 pi]
    // 'ConstrHelixStructFromArcFeed:72' theta = phi1 - phi0;
    theta = phi1 - phi0;
    //  Projection of P10 along the linear motion. Note evec is a unit vector.
    // 'ConstrHelixStructFromArcFeed:74' devec = dot(evec, P10);
    devec = (evec[0] * (p1x - p0x) + evec[1] * (p1y - p0y)) + evec[2] * (p1z - p0z);
    // 'ConstrHelixStructFromArcFeed:76' if rotation == 0
    if (rotation == 0.0) {
        //  Linear motion
        // 'ConstrHelixStructFromArcFeed:77' theta = 0;
        theta = 0.0;
        // 'ConstrHelixStructFromArcFeed:77' pitch = devec;
        pitch = devec;
    } else {
        // 'ConstrHelixStructFromArcFeed:78' else
        // 'ConstrHelixStructFromArcFeed:79' if rotation > 0
        if (rotation > 0.0) {
            //  Clockwise rotation
            // 'ConstrHelixStructFromArcFeed:80' if theta <= 0
            if (theta <= 0.0) {
                // 'ConstrHelixStructFromArcFeed:80' theta = theta + 2*pi;
                theta += 6.2831853071795862;
            }
            // 'ConstrHelixStructFromArcFeed:81' theta = theta + ( rotation - 1 ) * 2*pi;
            theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
        } else {
            // 'ConstrHelixStructFromArcFeed:82' else
            //  Counterclockwise rotation
            // 'ConstrHelixStructFromArcFeed:83' if theta >= 0
            if (theta >= 0.0) {
                // 'ConstrHelixStructFromArcFeed:83' theta = theta - 2*pi;
                theta -= 6.2831853071795862;
            }
            // 'ConstrHelixStructFromArcFeed:84' theta = theta + ( rotation + 1 ) * 2*pi;
            theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
        }
        // 'ConstrHelixStructFromArcFeed:86' if( theta == 0 )
        if (theta == 0.0) {
            //  Linear motion
            // 'ConstrHelixStructFromArcFeed:87' pitch = devec;
            pitch = devec;
        } else {
            // 'ConstrHelixStructFromArcFeed:88' else
            // 'ConstrHelixStructFromArcFeed:89' pitch = (devec / theta) * 2*pi;
            pitch = devec / theta * 2.0 * 3.1415926535897931;
        }
    }
    // 'ConstrHelixStructFromArcFeed:93' CurvStruct = ConstrHelixStruct(trafo, Poff, Aoff, Uoff, ...
    // 'ConstrHelixStructFromArcFeed:94'                                 Doff, P0, P1, A0, A1, U0,
    // U1, Cprim, ... 'ConstrHelixStructFromArcFeed:95'                                 delta, evec,
    // theta, pitch, 1, ZSpdMode.NN);
    ConstrHelixStruct(trafo, Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, U0, U1, b_Cprim, delta, evec,
                      theta, pitch, 1.0, ZSpdMode_NN, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrHelixStructFromArcFeed.cpp
//
// [EOF]
//

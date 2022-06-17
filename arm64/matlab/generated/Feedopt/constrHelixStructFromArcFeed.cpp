//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStructFromArcFeed.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "constrHelixStructFromArcFeed.h"
#include "CorrectArcCenter.h"
#include "constrHelixStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include <cmath>

// Function Definitions
//
// function [ CStrct ] = constrHelixStructFromArcFeed( gcodeInfoStruct, ...
//                                                         P0, P1, C, A0, A1, ...
//                                                         rotation, evec)
//
// ConstrHelixStructFromArcFeed : Construct a Curv struct filled with the
//  parameters of a helix. The resulting helix is the combination of a linear
//  motion along one of the three reference axis ( x, y, z ) with a circular
//  motion in the perpendicular plan ( XY, ZX, YZ ).
//
//  gcodeInfoStruct : struct containing the information from the Gcode
//  P0        : Starting point of the helix P0
//  P1        : Ending point of the helix P0
//  C         : Center C
//  A0        : Vector of the orientation angles at starting pose
//  A1        : Vector of the orientation angles at ending pose
//  rotation  : Number of rotation to realize (positive ; Clockwise |
//              negative ; Counterclockwise | zero ; pure translation)
//  evec      : Unit vector orthogonal to the planned of the projected circle
//
//  CStrct : The resulting CurvStruct
//
// Arguments    : const GcodeInfoStruct *gcodeInfoStruct
//                const double P0[3]
//                const double P1[3]
//                const double C[3]
//                const double A0[3]
//                const double A1[3]
//                double rotation
//                const double evec[3]
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void constrHelixStructFromArcFeed(const GcodeInfoStruct *gcodeInfoStruct, const double P0[3],
                                  const double P1[3], const double C[3], const double A0[3],
                                  const double A1[3], double rotation, const double evec[3],
                                  CurvStruct *CStrct)
{
    GcodeInfoStruct b_gcodeInfoStruct;
    double c_P0[6];
    double c_P1[6];
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
    // 'constrHelixStructFromArcFeed:20' coder.inline( "never" );
    //  Create vectors
    // 'constrHelixStructFromArcFeed:23' P0 = getColVec( P0 );
    // 'constrHelixStructFromArcFeed:89' if( isrow( vec ) )
    // 'constrHelixStructFromArcFeed:91' else
    // 'constrHelixStructFromArcFeed:92' col_vec = vec;
    // 'constrHelixStructFromArcFeed:24' P1 = getColVec( P1 );
    // 'constrHelixStructFromArcFeed:89' if( isrow( vec ) )
    // 'constrHelixStructFromArcFeed:91' else
    // 'constrHelixStructFromArcFeed:92' col_vec = vec;
    // 'constrHelixStructFromArcFeed:25' A0 = getColVec( A0 );
    // 'constrHelixStructFromArcFeed:89' if( isrow( vec ) )
    // 'constrHelixStructFromArcFeed:91' else
    // 'constrHelixStructFromArcFeed:92' col_vec = vec;
    // 'constrHelixStructFromArcFeed:26' A1 = getColVec( A1 );
    // 'constrHelixStructFromArcFeed:89' if( isrow( vec ) )
    // 'constrHelixStructFromArcFeed:91' else
    // 'constrHelixStructFromArcFeed:92' col_vec = vec;
    // 'constrHelixStructFromArcFeed:27' C  = getColVec( C );
    // 'constrHelixStructFromArcFeed:89' if( isrow( vec ) )
    // 'constrHelixStructFromArcFeed:91' else
    // 'constrHelixStructFromArcFeed:92' col_vec = vec;
    // 'constrHelixStructFromArcFeed:29' if evec(1) > 0.5
    if (evec[0] > 0.5) {
        double R0_idx_1;
        double R0_idx_2;
        double b_idx_0;
        //  YZ
        // 'constrHelixStructFromArcFeed:30' indYZ = [2, 3];
        // 'constrHelixStructFromArcFeed:31' [~, Cprim, delta] = CorrectArcCenter(P0(indYZ),
        // P1(indYZ), C(indYZ));
        Cprim[0] = C[1];
        Cprim[1] = C[2];
        CorrectArcCenter(*(double(*)[2]) & P0[1], *(double(*)[2]) & P1[1], Cprim, &a__1, &delta);
        // 'constrHelixStructFromArcFeed:32' Cprim = [C( 1 ), Cprim(1), Cprim(2)]';
        b_Cprim[0] = C[0];
        b_Cprim[1] = Cprim[0];
        b_Cprim[2] = Cprim[1];
        // 'constrHelixStructFromArcFeed:33' R0 = cross(evec, P0 - Cprim);
        b_idx_0 = P0[0] - C[0];
        R0_idx_1 = b_idx_0 * evec[2] - evec[0] * (P0[2] - Cprim[1]);
        R0_idx_2 = evec[0] * (P0[1] - Cprim[0]) - b_idx_0 * evec[1];
        // 'constrHelixStructFromArcFeed:34' R1 = cross(evec, P1 - Cprim);
        b_idx_0 = P1[0] - C[0];
        // 'constrHelixStructFromArcFeed:35' phi0 = atan2(R0(3), R0(2));
        phi0 = std::atan2(R0_idx_2, R0_idx_1);
        // 'constrHelixStructFromArcFeed:36' phi1 = atan2(R1(3), R1(2));
        phi1 = std::atan2(evec[0] * (P1[1] - Cprim[0]) - b_idx_0 * evec[1],
                          b_idx_0 * evec[2] - evec[0] * (P1[2] - Cprim[1]));
    } else if (evec[1] > 0.5) {
        double R0_idx_0;
        double R0_idx_2;
        double b_idx_1;
        // 'constrHelixStructFromArcFeed:38' elseif evec(2) > 0.5
        //  ZX
        // 'constrHelixStructFromArcFeed:39' indZX = [3, 1];
        // 'constrHelixStructFromArcFeed:40' [~, Cprim, delta] = CorrectArcCenter(P0(indZX),
        // P1(indZX), C(indZX));
        Cprim[0] = C[2];
        b_P0[0] = P0[2];
        b_P1[0] = P1[2];
        Cprim[1] = C[0];
        b_P0[1] = P0[0];
        b_P1[1] = P1[0];
        CorrectArcCenter(b_P0, b_P1, Cprim, &a__2, &delta);
        // 'constrHelixStructFromArcFeed:41' Cprim = [Cprim(2), C( 2 ), Cprim(1)]';
        b_Cprim[0] = Cprim[1];
        b_Cprim[1] = C[1];
        b_Cprim[2] = Cprim[0];
        // 'constrHelixStructFromArcFeed:42' R0 = cross(evec, P0 - Cprim);
        b_idx_1 = P0[1] - C[1];
        R0_idx_0 = evec[1] * (P0[2] - Cprim[0]) - b_idx_1 * evec[2];
        R0_idx_2 = evec[0] * b_idx_1 - (P0[0] - Cprim[1]) * evec[1];
        // 'constrHelixStructFromArcFeed:43' R1 = cross(evec, P1 - Cprim);
        b_idx_1 = P1[1] - C[1];
        // 'constrHelixStructFromArcFeed:44' phi1 = atan2(R0(3), R0(1));
        phi1 = std::atan2(R0_idx_2, R0_idx_0);
        // 'constrHelixStructFromArcFeed:45' phi0 = atan2(R1(3), R1(1));
        phi0 = std::atan2(evec[0] * b_idx_1 - (P1[0] - Cprim[1]) * evec[1],
                          evec[1] * (P1[2] - Cprim[0]) - b_idx_1 * evec[2]);
    } else {
        double R0_idx_0;
        double R0_idx_1;
        double b_idx_2;
        // 'constrHelixStructFromArcFeed:47' else
        //  XY
        // 'constrHelixStructFromArcFeed:48' indXY = [1,2];
        // 'constrHelixStructFromArcFeed:49' [~, Cprim, delta] = CorrectArcCenter(P0(indXY),
        // P1(indXY), C(indXY));
        Cprim[0] = C[0];
        Cprim[1] = C[1];
        CorrectArcCenter(*(double(*)[2]) & P0[0], *(double(*)[2]) & P1[0], Cprim, &a__3, &delta);
        // 'constrHelixStructFromArcFeed:50' Cprim = [Cprim(1), Cprim(2), C( 3 )]';
        b_Cprim[0] = Cprim[0];
        b_Cprim[1] = Cprim[1];
        b_Cprim[2] = C[2];
        // 'constrHelixStructFromArcFeed:51' R0 = cross(evec, P0 - Cprim);
        b_idx_2 = P0[2] - C[2];
        R0_idx_0 = evec[1] * b_idx_2 - (P0[1] - Cprim[1]) * evec[2];
        R0_idx_1 = (P0[0] - Cprim[0]) * evec[2] - evec[0] * b_idx_2;
        // 'constrHelixStructFromArcFeed:52' R1 = cross(evec, P1 - Cprim);
        b_idx_2 = P1[2] - C[2];
        // 'constrHelixStructFromArcFeed:53' phi0 = atan2(R0(2), R0(1));
        phi0 = std::atan2(R0_idx_1, R0_idx_0);
        // 'constrHelixStructFromArcFeed:54' phi1 = atan2(R1(2), R1(1));
        phi1 = std::atan2((P1[0] - Cprim[0]) * evec[2] - evec[0] * b_idx_2,
                          evec[1] * b_idx_2 - (P1[1] - Cprim[1]) * evec[2]);
    }
    // 'constrHelixStructFromArcFeed:58' P10 = P1 - P0;
    //  Theta is in [-2 pi; 2 pi]
    // 'constrHelixStructFromArcFeed:60' theta = phi1 - phi0;
    theta = phi1 - phi0;
    //  Projection of P10 along the linear motion. Note evec is a unit vector.
    // 'constrHelixStructFromArcFeed:62' devec = dot(evec, P10);
    devec = (evec[0] * (P1[0] - P0[0]) + evec[1] * (P1[1] - P0[1])) + evec[2] * (P1[2] - P0[2]);
    // 'constrHelixStructFromArcFeed:64' if rotation == 0
    if (rotation == 0.0) {
        //  Linear motion
        // 'constrHelixStructFromArcFeed:65' theta = 0;
        theta = 0.0;
        // 'constrHelixStructFromArcFeed:65' pitch = devec;
        pitch = devec;
    } else {
        // 'constrHelixStructFromArcFeed:66' else
        // 'constrHelixStructFromArcFeed:67' if rotation > 0
        if (rotation > 0.0) {
            //  Clockwise rotation
            // 'constrHelixStructFromArcFeed:68' if theta <= 0
            if (theta <= 0.0) {
                // 'constrHelixStructFromArcFeed:68' theta = theta + 2*pi;
                theta += 6.2831853071795862;
            }
            // 'constrHelixStructFromArcFeed:69' theta = theta + ( rotation - 1 ) * 2*pi;
            theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
        } else {
            // 'constrHelixStructFromArcFeed:70' else
            //  Counterclockwise rotation
            // 'constrHelixStructFromArcFeed:71' if theta >= 0
            if (theta >= 0.0) {
                // 'constrHelixStructFromArcFeed:71' theta = theta - 2*pi;
                theta -= 6.2831853071795862;
            }
            // 'constrHelixStructFromArcFeed:72' theta = theta + ( rotation + 1 ) * 2*pi;
            theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
        }
        // 'constrHelixStructFromArcFeed:74' if( theta == 0 )
        if (theta == 0.0) {
            //  Linear motion
            // 'constrHelixStructFromArcFeed:75' pitch = devec;
            pitch = devec;
        } else {
            // 'constrHelixStructFromArcFeed:76' else
            // 'constrHelixStructFromArcFeed:77' pitch = (devec / theta) * 2*pi;
            pitch = devec / theta * 2.0 * 3.1415926535897931;
        }
    }
    // 'constrHelixStructFromArcFeed:81' R0 = [ P0; A0 ];
    // 'constrHelixStructFromArcFeed:82' R1 = [ P1; A1 ];
    // 'constrHelixStructFromArcFeed:84' [ CStrct ] = constrHelixStruct( gcodeInfoStruct, R0, R1,
    // Cprim, delta, ... 'constrHelixStructFromArcFeed:85'                                     evec,
    // theta, pitch );
    c_P0[0] = P0[0];
    c_P0[3] = A0[0];
    c_P1[0] = P1[0];
    c_P1[3] = A1[0];
    c_P0[1] = P0[1];
    c_P0[4] = A0[1];
    c_P1[1] = P1[1];
    c_P1[4] = A1[1];
    c_P0[2] = P0[2];
    c_P0[5] = A0[2];
    c_P1[2] = P1[2];
    c_P1[5] = A1[2];
    b_gcodeInfoStruct = *gcodeInfoStruct;
    constrHelixStruct(&b_gcodeInfoStruct, c_P0, c_P1, b_Cprim, delta, evec, theta, pitch, CStrct);
}

} // namespace ocn

//
// File trailer for constrHelixStructFromArcFeed.cpp
//
// [EOF]
//

//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrAxesStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "constrAxesStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [ CStruct ] = constrAxesStruct( x, y, z, a, b, c, u, v, w )
//
// Construct a struct containing axes information.
//
//  Inputs :
//  x     : Axis X
//  y     : Axis Y
//  z     : Axis Z
//  a     : Axis A
//  b     : Axis B
//  c     : Axis C
//  u     : Axis U
//  v     : Axis V
//  w     : Axis W
//
//  Outputs :
//  CStruct       : The resulting structure
//
// Arguments    : double x
//                double y
//                double z
//                double a
//                double b
//                double c
//                double u
//                double v
//                double w
//                Axes *CStruct
// Return Type  : void
//
namespace ocn {
void constrAxesStruct(double x, double y, double z, double a, double b, double c, double u,
                      double v, double w, Axes *CStruct)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrAxesStruct:19' CStruct = struct(   'x', x, ...
    // 'constrAxesStruct:20'                     'y', y, ...
    // 'constrAxesStruct:21'                     'z', z, ...
    // 'constrAxesStruct:22'                     'a', a, ...
    // 'constrAxesStruct:23'                     'b', b, ...
    // 'constrAxesStruct:24'                     'c', c, ...
    // 'constrAxesStruct:25'                     'u', u, ...
    // 'constrAxesStruct:26'                     'v', v, ...
    // 'constrAxesStruct:27'                     'w', w ...
    // 'constrAxesStruct:28'                 );
    CStruct->x = x;
    CStruct->y = y;
    CStruct->z = z;
    CStruct->a = a;
    CStruct->b = b;
    CStruct->c = c;
    CStruct->u = u;
    CStruct->v = v;
    CStruct->w = w;
    // 'constrAxesStruct:30' coder.cstructname( CStruct, StructTypeName.Axes );
}

} // namespace ocn

//
// File trailer for constrAxesStruct.cpp
//
// [EOF]
//

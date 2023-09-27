//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrToolStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "constrToolStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [ CStruct ] = constrToolStruct( toolno, pocketno, offset, ...
//     diameter, frontangle, backangle, orientation)
//
// Construct a struct containing the information from the Gcode.
//
//  Inputs :
//  toolno        : Tool number
//  pocketno      : Pocket number used to store the tool
//  offset        : Struct used to store the axes offset
//  diameter      : Diameter of the tool
//  frontangle    : Frontangle of the tool
//  backangle     : Backangle of the tool
//  orientation   : Orientation of the tool
//
//  Outputs :
//  CStruct       : The resulting structure
//
// Arguments    : int *CStruct_toolno
//                int *CStruct_pocketno
//                double *CStruct_offset_x
//                double *CStruct_offset_y
//                double *CStruct_offset_z
//                double *CStruct_offset_a
//                double *CStruct_offset_b
//                double *CStruct_offset_c
//                double *CStruct_offset_u
//                double *CStruct_offset_v
//                double *CStruct_offset_w
//                double *CStruct_diameter
//                double *CStruct_frontangle
//                double *CStruct_backangle
//                int *CStruct_orientation
// Return Type  : void
//
namespace ocn {
void b_constrToolStruct(int *CStruct_toolno, int *CStruct_pocketno, double *CStruct_offset_x,
                        double *CStruct_offset_y, double *CStruct_offset_z,
                        double *CStruct_offset_a, double *CStruct_offset_b,
                        double *CStruct_offset_c, double *CStruct_offset_u,
                        double *CStruct_offset_v, double *CStruct_offset_w,
                        double *CStruct_diameter, double *CStruct_frontangle,
                        double *CStruct_backangle, int *CStruct_orientation)
{
    // 'constrToolStruct:16' coder.inline("never");
    // 'constrToolStruct:18' CStruct = struct(   'toolno',       toolno, ...
    // 'constrToolStruct:19'                     'pocketno',     pocketno, ...
    // 'constrToolStruct:20'                     'offset',       offset, ...
    // 'constrToolStruct:21'                     'diameter',     diameter, ...
    // 'constrToolStruct:22'                     'frontangle',   frontangle, ...
    // 'constrToolStruct:23'                     'backangle',    backangle, ...
    // 'constrToolStruct:24'                     'orientation',  orientation ...
    // 'constrToolStruct:25'                 );
    *CStruct_toolno = 0;
    *CStruct_pocketno = 0;
    *CStruct_offset_x = 0.0;
    *CStruct_offset_y = 0.0;
    *CStruct_offset_z = 0.0;
    *CStruct_offset_a = 0.0;
    *CStruct_offset_b = 0.0;
    *CStruct_offset_c = 0.0;
    *CStruct_offset_u = 0.0;
    *CStruct_offset_v = 0.0;
    *CStruct_offset_w = 0.0;
    *CStruct_diameter = 0.0;
    *CStruct_frontangle = 0.0;
    *CStruct_backangle = 0.0;
    *CStruct_orientation = 0;
    // 'constrToolStruct:27' if ~coder.target( 'MATLAB' )
    // 'constrToolStruct:28' coder.cstructname( CStruct.offset,  StructTypeName.Axes );
    // 'constrToolStruct:29' coder.cstructname( CStruct,         StructTypeName.Tool );
}

//
// function [ CStruct ] = constrToolStruct( toolno, pocketno, offset, ...
//     diameter, frontangle, backangle, orientation)
//
// Construct a struct containing the information from the Gcode.
//
//  Inputs :
//  toolno        : Tool number
//  pocketno      : Pocket number used to store the tool
//  offset        : Struct used to store the axes offset
//  diameter      : Diameter of the tool
//  frontangle    : Frontangle of the tool
//  backangle     : Backangle of the tool
//  orientation   : Orientation of the tool
//
//  Outputs :
//  CStruct       : The resulting structure
//
// Arguments    : int toolno
//                int pocketno
//                const Axes *offset
//                double diameter
//                double frontangle
//                double backangle
//                int orientation
//                Tool *CStruct
// Return Type  : void
//
void constrToolStruct(int toolno, int pocketno, const Axes *offset, double diameter,
                      double frontangle, double backangle, int orientation, Tool *CStruct)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrToolStruct:16' coder.inline("never");
    // 'constrToolStruct:18' CStruct = struct(   'toolno',       toolno, ...
    // 'constrToolStruct:19'                     'pocketno',     pocketno, ...
    // 'constrToolStruct:20'                     'offset',       offset, ...
    // 'constrToolStruct:21'                     'diameter',     diameter, ...
    // 'constrToolStruct:22'                     'frontangle',   frontangle, ...
    // 'constrToolStruct:23'                     'backangle',    backangle, ...
    // 'constrToolStruct:24'                     'orientation',  orientation ...
    // 'constrToolStruct:25'                 );
    CStruct->toolno = toolno;
    CStruct->pocketno = pocketno;
    CStruct->offset = *offset;
    CStruct->diameter = diameter;
    CStruct->frontangle = frontangle;
    CStruct->backangle = backangle;
    CStruct->orientation = orientation;
    // 'constrToolStruct:27' if ~coder.target( 'MATLAB' )
    // 'constrToolStruct:28' coder.cstructname( CStruct.offset,  StructTypeName.Axes );
    // 'constrToolStruct:29' coder.cstructname( CStruct,         StructTypeName.Tool );
}

} // namespace ocn

//
// File trailer for constrToolStruct.cpp
//
// [EOF]
//

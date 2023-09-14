//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkGeometry.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

// Include Files
#include "checkGeometry.h"
#include "isSameGeometry.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "toolIsEqual.h"
#include "coder_array.h"

// Function Definitions
//
// function [ valid ] = checkGeometry( queue )
//
// checkZSpdmode : Check if the queue has a valid geometry
//
// Arguments    : const queue_coder *queue
// Return Type  : bool
//
namespace ocn {
bool checkGeometry(const queue_coder *queue)
{
    ::coder::array<bool, 2U> c_x;
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    unsigned int N;
    bool valid;
    // 'checkGeometry:4' valid = false;
    valid = false;
    // 'checkGeometry:6' N = queue.size;
    N = queue->size();
    // 'checkGeometry:8' if( N == 0 )
    if (N == 0U) {
        // 'checkGeometry:9' valid = true;
        valid = true;
    } else {
        double curv_a_param;
        double curv_b_param;
        double curv_delta;
        double curv_tool_backangle;
        double curv_tool_diameter;
        double curv_tool_frontangle;
        double curv_tool_offset_a;
        double curv_tool_offset_b;
        double curv_tool_offset_c;
        double curv_tool_offset_u;
        double curv_tool_offset_v;
        double curv_tool_offset_w;
        double curv_tool_offset_x;
        double curv_tool_offset_y;
        double curv_tool_offset_z;
        int curv_Info_gcode_source_line;
        unsigned int curv_sp_index;
        int curv_tool_orientation;
        int curv_tool_pocketno;
        int curv_tool_toolno;
        unsigned int k;
        bool curv_Info_TRAFO;
        CurveType curv_Info_Type;
        // 'checkGeometry:13' curv = queue.get( 1 );
        queue->get(static_cast<double>(1.0), &expl_temp);
        curv_Info_Type = expl_temp.Info.Type;
        curv_Info_TRAFO = expl_temp.Info.TRAFO;
        curv_Info_gcode_source_line = expl_temp.Info.gcode_source_line;
        curv_tool_toolno = expl_temp.tool.toolno;
        curv_tool_pocketno = expl_temp.tool.pocketno;
        curv_tool_offset_x = expl_temp.tool.offset.x;
        curv_tool_offset_y = expl_temp.tool.offset.y;
        curv_tool_offset_z = expl_temp.tool.offset.z;
        curv_tool_offset_a = expl_temp.tool.offset.a;
        curv_tool_offset_b = expl_temp.tool.offset.b;
        curv_tool_offset_c = expl_temp.tool.offset.c;
        curv_tool_offset_u = expl_temp.tool.offset.u;
        curv_tool_offset_v = expl_temp.tool.offset.v;
        curv_tool_offset_w = expl_temp.tool.offset.w;
        curv_tool_diameter = expl_temp.tool.diameter;
        curv_tool_frontangle = expl_temp.tool.frontangle;
        curv_tool_backangle = expl_temp.tool.backangle;
        curv_tool_orientation = expl_temp.tool.orientation;
        curv_delta = expl_temp.delta;
        curv_sp_index = expl_temp.sp_index;
        curv_a_param = expl_temp.a_param;
        curv_b_param = expl_temp.b_param;
        // 'checkGeometry:15' for k = 2 : N
        k = 2U;
        int exitg1;
        do {
            exitg1 = 0;
            if (k <= N) {
                bool isSame;
                // 'checkGeometry:16' curvNext = queue.get( k );
                queue->get(k, &b_expl_temp);
                // 'checkGeometry:18' if( isSameGeometry(curv, curvNext) )
                //  Check if the machine parameters are equals
                // 'isSameGeometry:3' isSame = false;
                isSame = false;
                // 'isSameGeometry:4' if( curv1.Info.Type ~= curv2.Info.Type )
                if ((curv_Info_Type == b_expl_temp.Info.Type) &&
                    (curv_Info_TRAFO == b_expl_temp.Info.TRAFO)) {
                    int b_k;
                    bool x[6];
                    bool exitg2;
                    bool y;
                    // 'isSameGeometry:5' if( curv1.Info.TRAFO ~= curv2.Info.TRAFO )
                    // 'isSameGeometry:6' if( any(curv1.R0 ~= curv2.R0) )
                    for (int i{0}; i < 6; i++) {
                        x[i] = (expl_temp.R0[i] != b_expl_temp.R0[i]);
                    }
                    y = false;
                    b_k = 0;
                    exitg2 = false;
                    while ((!exitg2) && (b_k < 6)) {
                        if (x[b_k]) {
                            y = true;
                            exitg2 = true;
                        } else {
                            b_k++;
                        }
                    }
                    if (!y) {
                        int c_k;
                        bool b_y;
                        // 'isSameGeometry:7' if( any(curv1.R1 ~= curv2.R1) )
                        for (int b_i{0}; b_i < 6; b_i++) {
                            x[b_i] = (expl_temp.R1[b_i] != b_expl_temp.R1[b_i]);
                        }
                        b_y = false;
                        c_k = 0;
                        exitg2 = false;
                        while ((!exitg2) && (c_k < 6)) {
                            if (x[c_k]) {
                                b_y = true;
                                exitg2 = true;
                            } else {
                                c_k++;
                            }
                        }
                        if ((!b_y) && (curv_a_param == b_expl_temp.a_param) &&
                            (curv_b_param == b_expl_temp.b_param)) {
                            int d_k;
                            bool b_x[3];
                            bool c_y;
                            // 'isSameGeometry:8' if( curv1.a_param ~= curv2.a_param )
                            // 'isSameGeometry:9' if( curv1.b_param ~= curv2.b_param )
                            // 'isSameGeometry:10' if( any(curv1.CorrectedHelixCenter ~=
                            // curv2.CorrectedHelixCenter) )
                            b_x[0] = (expl_temp.CorrectedHelixCenter[0] !=
                                      b_expl_temp.CorrectedHelixCenter[0]);
                            b_x[1] = (expl_temp.CorrectedHelixCenter[1] !=
                                      b_expl_temp.CorrectedHelixCenter[1]);
                            b_x[2] = (expl_temp.CorrectedHelixCenter[2] !=
                                      b_expl_temp.CorrectedHelixCenter[2]);
                            c_y = false;
                            d_k = 0;
                            exitg2 = false;
                            while ((!exitg2) && (d_k < 3)) {
                                if (b_x[d_k]) {
                                    c_y = true;
                                    exitg2 = true;
                                } else {
                                    d_k++;
                                }
                            }
                            if ((!c_y) && (curv_delta == b_expl_temp.delta)) {
                                int f_k;
                                bool d_y[6];
                                bool e_y;
                                // 'isSameGeometry:12' if( curv1.delta ~= curv2.delta )
                                // 'isSameGeometry:13' if( any(curv1.CoeffP5 ~= curv2.CoeffP5) )
                                if (expl_temp.CoeffP5.size(0) == b_expl_temp.CoeffP5.size(0)) {
                                    int b_loop_ub;
                                    c_x.set_size(expl_temp.CoeffP5.size(0), 6);
                                    b_loop_ub = expl_temp.CoeffP5.size(0);
                                    for (int i1{0}; i1 < 6; i1++) {
                                        for (int i2{0}; i2 < b_loop_ub; i2++) {
                                            c_x[i2 + c_x.size(0) * i1] =
                                                (expl_temp.CoeffP5[i2 + expl_temp.CoeffP5.size(0) *
                                                                            i1] !=
                                                 b_expl_temp
                                                     .CoeffP5[i2 +
                                                              b_expl_temp.CoeffP5.size(0) * i1]);
                                        }
                                    }
                                } else {
                                    d_binary_expand_op(c_x, &expl_temp, &b_expl_temp);
                                }
                                for (int e_k{0}; e_k < 6; e_k++) {
                                    int g_k;
                                    d_y[e_k] = false;
                                    g_k = 0;
                                    exitg2 = false;
                                    while ((!exitg2) && (g_k <= c_x.size(0) - 1)) {
                                        if (c_x[g_k + c_x.size(0) * e_k]) {
                                            d_y[e_k] = true;
                                            exitg2 = true;
                                        } else {
                                            g_k++;
                                        }
                                    }
                                }
                                e_y = true;
                                f_k = 0;
                                exitg2 = false;
                                while ((!exitg2) && (f_k < 6)) {
                                    if (!d_y[f_k]) {
                                        e_y = false;
                                        exitg2 = true;
                                    } else {
                                        f_k++;
                                    }
                                }
                                if (!e_y) {
                                    int h_k;
                                    bool f_y;
                                    // 'isSameGeometry:14' if( any(curv1.evec ~= curv2.evec) )
                                    b_x[0] = (expl_temp.evec[0] != b_expl_temp.evec[0]);
                                    b_x[1] = (expl_temp.evec[1] != b_expl_temp.evec[1]);
                                    b_x[2] = (expl_temp.evec[2] != b_expl_temp.evec[2]);
                                    f_y = false;
                                    h_k = 0;
                                    exitg2 = false;
                                    while ((!exitg2) && (h_k < 3)) {
                                        if (b_x[h_k]) {
                                            f_y = true;
                                            exitg2 = true;
                                        } else {
                                            h_k++;
                                        }
                                    }
                                    if ((!f_y) &&
                                        toolIsEqual(
                                            curv_tool_toolno, curv_tool_pocketno,
                                            curv_tool_offset_x, curv_tool_offset_y,
                                            curv_tool_offset_z, curv_tool_offset_a,
                                            curv_tool_offset_b, curv_tool_offset_c,
                                            curv_tool_offset_u, curv_tool_offset_v,
                                            curv_tool_offset_w, curv_tool_diameter,
                                            curv_tool_frontangle, curv_tool_backangle,
                                            curv_tool_orientation, b_expl_temp.tool.toolno,
                                            b_expl_temp.tool.pocketno, &b_expl_temp.tool.offset,
                                            b_expl_temp.tool.diameter, b_expl_temp.tool.frontangle,
                                            b_expl_temp.tool.backangle,
                                            b_expl_temp.tool.orientation) &&
                                        (curv_sp_index == b_expl_temp.sp_index) &&
                                        (curv_Info_gcode_source_line ==
                                         b_expl_temp.Info.gcode_source_line)) {
                                        // 'isSameGeometry:15' if( ~toolIsEqual(curv1.tool,
                                        // curv2.tool ) ) 'isSameGeometry:16' if( curv1.sp_index ~=
                                        // curv2.sp_index ) 'isSameGeometry:17' if(
                                        // curv1.Info.gcode_source_line ~=
                                        // curv2.Info.gcode_source_line ) 'isSameGeometry:18' isSame
                                        // = true;
                                        isSame = true;
                                    }
                                }
                            }
                        }
                    }
                }
                if (isSame) {
                    exitg1 = 1;
                } else {
                    int loop_ub;
                    // 'checkGeometry:22' curv = curvNext;
                    curv_Info_Type = b_expl_temp.Info.Type;
                    curv_Info_TRAFO = b_expl_temp.Info.TRAFO;
                    curv_Info_gcode_source_line = b_expl_temp.Info.gcode_source_line;
                    curv_tool_toolno = b_expl_temp.tool.toolno;
                    curv_tool_pocketno = b_expl_temp.tool.pocketno;
                    curv_tool_offset_x = b_expl_temp.tool.offset.x;
                    curv_tool_offset_y = b_expl_temp.tool.offset.y;
                    curv_tool_offset_z = b_expl_temp.tool.offset.z;
                    curv_tool_offset_a = b_expl_temp.tool.offset.a;
                    curv_tool_offset_b = b_expl_temp.tool.offset.b;
                    curv_tool_offset_c = b_expl_temp.tool.offset.c;
                    curv_tool_offset_u = b_expl_temp.tool.offset.u;
                    curv_tool_offset_v = b_expl_temp.tool.offset.v;
                    curv_tool_offset_w = b_expl_temp.tool.offset.w;
                    curv_tool_diameter = b_expl_temp.tool.diameter;
                    curv_tool_frontangle = b_expl_temp.tool.frontangle;
                    curv_tool_backangle = b_expl_temp.tool.backangle;
                    curv_tool_orientation = b_expl_temp.tool.orientation;
                    curv_delta = b_expl_temp.delta;
                    expl_temp.CorrectedHelixCenter[0] = b_expl_temp.CorrectedHelixCenter[0];
                    expl_temp.evec[0] = b_expl_temp.evec[0];
                    expl_temp.CorrectedHelixCenter[1] = b_expl_temp.CorrectedHelixCenter[1];
                    expl_temp.evec[1] = b_expl_temp.evec[1];
                    expl_temp.CorrectedHelixCenter[2] = b_expl_temp.CorrectedHelixCenter[2];
                    expl_temp.evec[2] = b_expl_temp.evec[2];
                    expl_temp.CoeffP5.set_size(b_expl_temp.CoeffP5.size(0), 6);
                    loop_ub = b_expl_temp.CoeffP5.size(0);
                    for (int c_i{0}; c_i < 6; c_i++) {
                        expl_temp.R0[c_i] = b_expl_temp.R0[c_i];
                        expl_temp.R1[c_i] = b_expl_temp.R1[c_i];
                        for (int d_i{0}; d_i < loop_ub; d_i++) {
                            expl_temp.CoeffP5[d_i + expl_temp.CoeffP5.size(0) * c_i] =
                                b_expl_temp.CoeffP5[d_i + b_expl_temp.CoeffP5.size(0) * c_i];
                        }
                    }
                    curv_sp_index = b_expl_temp.sp_index;
                    curv_a_param = b_expl_temp.a_param;
                    curv_b_param = b_expl_temp.b_param;
                    k++;
                }
            } else {
                // 'checkGeometry:25' valid = true;
                valid = true;
                exitg1 = 1;
            }
        } while (exitg1 == 0);
    }
    return valid;
}

} // namespace ocn

//
// File trailer for checkGeometry.cpp
//
// [EOF]
//

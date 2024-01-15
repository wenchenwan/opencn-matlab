
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: checkGeometry.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "checkGeometry.h"
#include "isSameGeometry.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "toolIsEqual.h"
#include "coder_array.h"

// Function Definitions
//
// function [ valid ] = checkGeometry( queueCurv )
//
// checkZSpdmode : Check if the queue have two folowing curvs with the same
//  geometry.
//
//  Inputs :
//    queueCurv   : A queue a curvStructs
//
//  Outputs :
//    valid       : Boolean value, TRUE means they are no same curv geometry
//                  in the whole queue.
//
//
// Arguments    : const queue_coder *queueCurv
// Return Type  : bool
//
namespace ocn {
bool checkGeometry(const queue_coder *queueCurv)
{
    ::coder::array<bool, 2U> b_y;
    ::coder::array<bool, 2U> c_x;
    ::coder::array<bool, 1U> x;
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    unsigned int N;
    bool valid;
    // 'checkGeometry:12' valid = false;
    valid = false;
    // 'checkGeometry:14' N = queueCurv.size;
    N = queueCurv->size();
    // 'checkGeometry:16' if( N == 0 )
    if (N == 0U) {
        // 'checkGeometry:17' valid = true;
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
        // 'checkGeometry:21' curv = queueCurv.get( 1 );
        queueCurv->get(&expl_temp);
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
        // 'checkGeometry:23' for k = 2 : N
        k = 2U;
        int exitg1;
        do {
            exitg1 = 0;
            if (k <= N) {
                bool isSame;
                // 'checkGeometry:24' curvNext = queueCurv.get( k );
                queueCurv->get(k, &b_expl_temp);
                // 'checkGeometry:26' if( isSameGeometry(curv, curvNext) )
                //  isSameGeometry : Check if the curves geometry is equal
                //
                //  Inputs :
                //    curv1 : First curve
                //    curv2 : Second curve
                //
                //  Outputs :
                //    value : Boolean value. TRUE means the two curves are equals.
                //
                // 'isSameGeometry:12' isSame = false;
                isSame = false;
                // 'isSameGeometry:13' if( curv1.Info.Type ~= curv2.Info.Type )
                if ((curv_Info_Type == b_expl_temp.Info.Type) &&
                    (curv_Info_TRAFO == b_expl_temp.Info.TRAFO)) {
                    int b_k;
                    bool exitg2;
                    bool varargout_1;
                    // 'isSameGeometry:14' if( curv1.Info.TRAFO ~= curv2.Info.TRAFO )
                    // 'isSameGeometry:15' if( any(curv1.R0 ~= curv2.R0) )
                    if (expl_temp.R0.size(0) == b_expl_temp.R0.size(0)) {
                        int loop_ub;
                        x.set_size(expl_temp.R0.size(0));
                        loop_ub = expl_temp.R0.size(0);
                        for (int i{0}; i < loop_ub; i++) {
                            x[i] = (expl_temp.R0[i] != b_expl_temp.R0[i]);
                        }
                    } else {
                        d_binary_expand_op(x, &expl_temp, &b_expl_temp);
                    }
                    varargout_1 = false;
                    b_k = 0;
                    exitg2 = false;
                    while ((!exitg2) && (b_k <= x.size(0) - 1)) {
                        if (x[b_k]) {
                            varargout_1 = true;
                            exitg2 = true;
                        } else {
                            b_k++;
                        }
                    }
                    if (!varargout_1) {
                        int c_k;
                        bool b_varargout_1;
                        // 'isSameGeometry:16' if( any(curv1.R1 ~= curv2.R1) )
                        if (expl_temp.R1.size(0) == b_expl_temp.R1.size(0)) {
                            int b_loop_ub;
                            x.set_size(expl_temp.R1.size(0));
                            b_loop_ub = expl_temp.R1.size(0);
                            for (int i1{0}; i1 < b_loop_ub; i1++) {
                                x[i1] = (expl_temp.R1[i1] != b_expl_temp.R1[i1]);
                            }
                        } else {
                            c_binary_expand_op(x, &expl_temp, &b_expl_temp);
                        }
                        b_varargout_1 = false;
                        c_k = 0;
                        exitg2 = false;
                        while ((!exitg2) && (c_k <= x.size(0) - 1)) {
                            if (x[c_k]) {
                                b_varargout_1 = true;
                                exitg2 = true;
                            } else {
                                c_k++;
                            }
                        }
                        if ((!b_varargout_1) && (curv_a_param == b_expl_temp.a_param) &&
                            (curv_b_param == b_expl_temp.b_param)) {
                            int d_k;
                            bool b_x[3];
                            bool y;
                            // 'isSameGeometry:17' if( curv1.a_param ~= curv2.a_param )
                            // 'isSameGeometry:18' if( curv1.b_param ~= curv2.b_param )
                            // 'isSameGeometry:19' if( any(curv1.CorrectedHelixCenter ~=
                            // curv2.CorrectedHelixCenter) )
                            b_x[0] = (expl_temp.CorrectedHelixCenter[0] !=
                                      b_expl_temp.CorrectedHelixCenter[0]);
                            b_x[1] = (expl_temp.CorrectedHelixCenter[1] !=
                                      b_expl_temp.CorrectedHelixCenter[1]);
                            b_x[2] = (expl_temp.CorrectedHelixCenter[2] !=
                                      b_expl_temp.CorrectedHelixCenter[2]);
                            y = false;
                            d_k = 0;
                            exitg2 = false;
                            while ((!exitg2) && (d_k < 3)) {
                                if (b_x[d_k]) {
                                    y = true;
                                    exitg2 = true;
                                } else {
                                    d_k++;
                                }
                            }
                            if ((!y) && (curv_delta == b_expl_temp.delta)) {
                                int h_loop_ub;
                                int hi;
                                bool c_y;
                                // 'isSameGeometry:21' if( curv1.delta ~= curv2.delta )
                                // 'isSameGeometry:22' if( any(curv1.CoeffP5 ~= curv2.CoeffP5) )
                                if ((expl_temp.CoeffP5.size(0) == b_expl_temp.CoeffP5.size(0)) &&
                                    (expl_temp.CoeffP5.size(1) == b_expl_temp.CoeffP5.size(1))) {
                                    int f_loop_ub;
                                    c_x.set_size(expl_temp.CoeffP5.size(0),
                                                 expl_temp.CoeffP5.size(1));
                                    f_loop_ub = expl_temp.CoeffP5.size(1);
                                    for (int i5{0}; i5 < f_loop_ub; i5++) {
                                        int i_loop_ub;
                                        i_loop_ub = expl_temp.CoeffP5.size(0);
                                        for (int i8{0}; i8 < i_loop_ub; i8++) {
                                            c_x[i8 + c_x.size(0) * i5] =
                                                (expl_temp.CoeffP5[i8 + expl_temp.CoeffP5.size(0) *
                                                                            i5] !=
                                                 b_expl_temp
                                                     .CoeffP5[i8 +
                                                              b_expl_temp.CoeffP5.size(0) * i5]);
                                        }
                                    }
                                } else {
                                    b_binary_expand_op(c_x, &expl_temp, &b_expl_temp);
                                }
                                b_y.set_size(1, c_x.size(1));
                                h_loop_ub = c_x.size(1);
                                for (int i7{0}; i7 < h_loop_ub; i7++) {
                                    b_y[i7] = false;
                                }
                                hi = c_x.size(1);
                                for (int e_k{0}; e_k < hi; e_k++) {
                                    int f_k;
                                    b_y[e_k] = false;
                                    f_k = 0;
                                    exitg2 = false;
                                    while ((!exitg2) && (f_k <= c_x.size(0) - 1)) {
                                        if (c_x[f_k + c_x.size(0) * e_k]) {
                                            b_y[e_k] = true;
                                            exitg2 = true;
                                        } else {
                                            f_k++;
                                        }
                                    }
                                }
                                c_y = (b_y.size(1) != 0);
                                if (c_y) {
                                    int g_k;
                                    g_k = 0;
                                    exitg2 = false;
                                    while ((!exitg2) && (g_k <= b_y.size(1) - 1)) {
                                        if (!b_y[g_k]) {
                                            c_y = false;
                                            exitg2 = true;
                                        } else {
                                            g_k++;
                                        }
                                    }
                                }
                                if (!c_y) {
                                    int h_k;
                                    bool d_y;
                                    // 'isSameGeometry:23' if( any(curv1.evec ~= curv2.evec) )
                                    b_x[0] = (expl_temp.evec[0] != b_expl_temp.evec[0]);
                                    b_x[1] = (expl_temp.evec[1] != b_expl_temp.evec[1]);
                                    b_x[2] = (expl_temp.evec[2] != b_expl_temp.evec[2]);
                                    d_y = false;
                                    h_k = 0;
                                    exitg2 = false;
                                    while ((!exitg2) && (h_k < 3)) {
                                        if (b_x[h_k]) {
                                            d_y = true;
                                            exitg2 = true;
                                        } else {
                                            h_k++;
                                        }
                                    }
                                    if ((!d_y) &&
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
                                        // 'isSameGeometry:24' if( ~toolIsEqual(curv1.tool,
                                        // curv2.tool ) ) 'isSameGeometry:25' if( curv1.sp_index ~=
                                        // curv2.sp_index ) 'isSameGeometry:26' if(
                                        // curv1.Info.gcode_source_line ~=
                                        // curv2.Info.gcode_source_line ) 'isSameGeometry:27' isSame
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
                    int c_loop_ub;
                    int d_loop_ub;
                    int e_loop_ub;
                    // 'checkGeometry:30' curv = curvNext;
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
                    expl_temp.R0.set_size(b_expl_temp.R0.size(0));
                    c_loop_ub = b_expl_temp.R0.size(0);
                    for (int i2{0}; i2 < c_loop_ub; i2++) {
                        expl_temp.R0[i2] = b_expl_temp.R0[i2];
                    }
                    expl_temp.R1.set_size(b_expl_temp.R1.size(0));
                    d_loop_ub = b_expl_temp.R1.size(0);
                    for (int i3{0}; i3 < d_loop_ub; i3++) {
                        expl_temp.R1[i3] = b_expl_temp.R1[i3];
                    }
                    curv_delta = b_expl_temp.delta;
                    expl_temp.CorrectedHelixCenter[0] = b_expl_temp.CorrectedHelixCenter[0];
                    expl_temp.evec[0] = b_expl_temp.evec[0];
                    expl_temp.CorrectedHelixCenter[1] = b_expl_temp.CorrectedHelixCenter[1];
                    expl_temp.evec[1] = b_expl_temp.evec[1];
                    expl_temp.CorrectedHelixCenter[2] = b_expl_temp.CorrectedHelixCenter[2];
                    expl_temp.evec[2] = b_expl_temp.evec[2];
                    expl_temp.CoeffP5.set_size(b_expl_temp.CoeffP5.size(0),
                                               b_expl_temp.CoeffP5.size(1));
                    e_loop_ub = b_expl_temp.CoeffP5.size(1);
                    for (int i4{0}; i4 < e_loop_ub; i4++) {
                        int g_loop_ub;
                        g_loop_ub = b_expl_temp.CoeffP5.size(0);
                        for (int i6{0}; i6 < g_loop_ub; i6++) {
                            expl_temp.CoeffP5[i6 + expl_temp.CoeffP5.size(0) * i4] =
                                b_expl_temp.CoeffP5[i6 + b_expl_temp.CoeffP5.size(0) * i4];
                        }
                    }
                    curv_sp_index = b_expl_temp.sp_index;
                    curv_a_param = b_expl_temp.a_param;
                    curv_b_param = b_expl_temp.b_param;
                    k++;
                }
            } else {
                // 'checkGeometry:33' valid = true;
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

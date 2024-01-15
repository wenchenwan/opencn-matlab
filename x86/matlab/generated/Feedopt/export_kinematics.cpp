
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: export_kinematics.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "export_kinematics.h"
#include "Kinematics.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(double in1_data[], int *in1_size,
                             const ::coder::array<double, 1U> &in2);

static void binary_expand_op(::coder::array<double, 2U> &in1,
                             const ::coder::array<double, 2U> &in2);

static void binary_expand_op(double in1_data[], int *in1_size,
                             const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3,
                             const ::coder::array<double, 1U> &in4,
                             const ::coder::array<double, 1U> &in5);

static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3,
                             const ::coder::array<double, 1U> &in4,
                             const ::coder::array<double, 1U> &in5);

static void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size,
                             const double in4_data[], const int *in4_size, const double in5_data[],
                             const int *in5_size);

static void binary_expand_op(::coder::array<double, 2U> &in1, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size,
                             const double in4_data[], const int *in4_size, const double in5_data[],
                             const int *in5_size);

} // namespace ocn

// Function Definitions
//
// Arguments    : double in1_data[]
//                int *in1_size
//                const ::coder::array<double, 1U> &in2
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(double in1_data[], int *in1_size,
                             const ::coder::array<double, 1U> &in2)
{
    double b_in1_data[6];
    int b_in1_size;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in2.size(0) == 1) {
        b_in1_size = *in1_size;
    } else {
        b_in1_size = in2.size(0);
    }
    stride_0_0 = (*in1_size != 1);
    stride_1_0 = (in2.size(0) != 1);
    if (in2.size(0) == 1) {
        loop_ub = *in1_size;
    } else {
        loop_ub = in2.size(0);
    }
    for (int i{0}; i < loop_ub; i++) {
        b_in1_data[i] = in1_data[i * stride_0_0] + in2[i * stride_1_0];
    }
    *in1_size = b_in1_size;
    if (b_in1_size - 1 >= 0) {
        std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2)
{
    ::coder::array<double, 2U> b_in1;
    int aux_0_1;
    int aux_1_1;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    if (in2.size(0) == 1) {
        i = in1.size(0);
    } else {
        i = in2.size(0);
    }
    if (in2.size(1) == 1) {
        i1 = in1.size(1);
    } else {
        i1 = in2.size(1);
    }
    b_in1.set_size(i, i1);
    stride_0_0 = (in1.size(0) != 1);
    stride_0_1 = (in1.size(1) != 1);
    stride_1_0 = (in2.size(0) != 1);
    stride_1_1 = (in2.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in2.size(1) == 1) {
        loop_ub = in1.size(1);
    } else {
        loop_ub = in2.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int c_loop_ub;
        if (in2.size(0) == 1) {
            c_loop_ub = in1.size(0);
        } else {
            c_loop_ub = in2.size(0);
        }
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            b_in1[i4 + b_in1.size(0) * i2] = in1[i4 * stride_0_0 + in1.size(0) * aux_0_1] +
                                             in2[i4 * stride_1_0 + in2.size(0) * aux_1_1];
        }
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    in1.set_size(b_in1.size(0), b_in1.size(1));
    b_loop_ub = b_in1.size(1);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = b_in1.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i3] = b_in1[i5 + b_in1.size(0) * i3];
        }
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const ::coder::array<double, 1U> &in2
//                const ::coder::array<double, 1U> &in3
//                const ::coder::array<double, 1U> &in4
//                const ::coder::array<double, 1U> &in5
// Return Type  : void
//
static void binary_expand_op(double in1_data[], int *in1_size,
                             const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3,
                             const ::coder::array<double, 1U> &in4,
                             const ::coder::array<double, 1U> &in5)
{
    double b_in1_data[6];
    int b_in1_size;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    int stride_4_0;
    if (in5.size(0) == 1) {
        if (in4.size(0) == 1) {
            if (in3.size(0) == 1) {
                if (in2.size(0) == 1) {
                    b_in1_size = *in1_size;
                } else {
                    b_in1_size = in2.size(0);
                }
            } else {
                b_in1_size = in3.size(0);
            }
        } else {
            b_in1_size = in4.size(0);
        }
    } else {
        b_in1_size = in5.size(0);
    }
    stride_0_0 = (*in1_size != 1);
    stride_1_0 = (in2.size(0) != 1);
    stride_2_0 = (in3.size(0) != 1);
    stride_3_0 = (in4.size(0) != 1);
    stride_4_0 = (in5.size(0) != 1);
    if (in5.size(0) == 1) {
        if (in4.size(0) == 1) {
            if (in3.size(0) == 1) {
                if (in2.size(0) == 1) {
                    loop_ub = *in1_size;
                } else {
                    loop_ub = in2.size(0);
                }
            } else {
                loop_ub = in3.size(0);
            }
        } else {
            loop_ub = in4.size(0);
        }
    } else {
        loop_ub = in5.size(0);
    }
    for (int i{0}; i < loop_ub; i++) {
        b_in1_data[i] = (((in1_data[i * stride_0_0] + in2[i * stride_1_0]) + in3[i * stride_2_0]) +
                         in4[i * stride_3_0]) +
                        in5[i * stride_4_0];
    }
    *in1_size = b_in1_size;
    if (b_in1_size - 1 >= 0) {
        std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 1U> &in2
//                const ::coder::array<double, 1U> &in3
//                const ::coder::array<double, 1U> &in4
//                const ::coder::array<double, 1U> &in5
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3,
                             const ::coder::array<double, 1U> &in4,
                             const ::coder::array<double, 1U> &in5)
{
    ::coder::array<double, 2U> b_in1;
    int b_in5_idx_0;
    int b_loop_ub;
    int in2_idx_0;
    int in3_idx_0;
    int in4_idx_0;
    int in5_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    int stride_4_0;
    in2_idx_0 = in2.size(0);
    in3_idx_0 = in3.size(0);
    in4_idx_0 = in4.size(0);
    in5_idx_0 = in5.size(0);
    if (in5_idx_0 == 1) {
        if (in4_idx_0 == 1) {
            if (in3_idx_0 == 1) {
                if (in2_idx_0 == 1) {
                    b_in5_idx_0 = in1.size(0);
                } else {
                    b_in5_idx_0 = in2_idx_0;
                }
            } else {
                b_in5_idx_0 = in3_idx_0;
            }
        } else {
            b_in5_idx_0 = in4_idx_0;
        }
    } else {
        b_in5_idx_0 = in5_idx_0;
    }
    b_in1.set_size(b_in5_idx_0, in1.size(1));
    stride_0_0 = (in1.size(0) != 1);
    stride_1_0 = (in2_idx_0 != 1);
    stride_2_0 = (in3_idx_0 != 1);
    stride_3_0 = (in4_idx_0 != 1);
    stride_4_0 = (in5_idx_0 != 1);
    loop_ub = in1.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int c_loop_ub;
        if (in5_idx_0 == 1) {
            if (in4_idx_0 == 1) {
                if (in3_idx_0 == 1) {
                    if (in2_idx_0 == 1) {
                        c_loop_ub = in1.size(0);
                    } else {
                        c_loop_ub = in2_idx_0;
                    }
                } else {
                    c_loop_ub = in3_idx_0;
                }
            } else {
                c_loop_ub = in4_idx_0;
            }
        } else {
            c_loop_ub = in5_idx_0;
        }
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            b_in1[i2 + b_in1.size(0) * i] =
                (((in1[i2 * stride_0_0 + in1.size(0) * i] + in2[i2 * stride_1_0]) +
                  in3[i2 * stride_2_0]) +
                 in4[i2 * stride_3_0]) +
                in5[i2 * stride_4_0];
        }
    }
    in1.set_size(b_in1.size(0), b_in1.size(1));
    b_loop_ub = b_in1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int d_loop_ub;
        d_loop_ub = b_in1.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            in1[i3 + in1.size(0) * i1] = b_in1[i3 + b_in1.size(0) * i1];
        }
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2_data[]
//                const int *in2_size
//                const double in3_data[]
//                const int *in3_size
//                const double in4_data[]
//                const int *in4_size
//                const double in5_data[]
//                const int *in5_size
// Return Type  : void
//
static void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size,
                             const double in4_data[], const int *in4_size, const double in5_data[],
                             const int *in5_size)
{
    double b_in1_data[6];
    int b_in1_size;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    int stride_4_0;
    if (*in5_size == 1) {
        if (*in4_size == 1) {
            if (*in3_size == 1) {
                if (*in2_size == 1) {
                    b_in1_size = *in1_size;
                } else {
                    b_in1_size = *in2_size;
                }
            } else {
                b_in1_size = *in3_size;
            }
        } else {
            b_in1_size = *in4_size;
        }
    } else {
        b_in1_size = *in5_size;
    }
    stride_0_0 = (*in1_size != 1);
    stride_1_0 = (*in2_size != 1);
    stride_2_0 = (*in3_size != 1);
    stride_3_0 = (*in4_size != 1);
    stride_4_0 = (*in5_size != 1);
    if (*in5_size == 1) {
        if (*in4_size == 1) {
            if (*in3_size == 1) {
                if (*in2_size == 1) {
                    loop_ub = *in1_size;
                } else {
                    loop_ub = *in2_size;
                }
            } else {
                loop_ub = *in3_size;
            }
        } else {
            loop_ub = *in4_size;
        }
    } else {
        loop_ub = *in5_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        b_in1_data[i] =
            (((in1_data[i * stride_0_0] + in2_data[i * stride_1_0]) + in3_data[i * stride_2_0]) +
             in4_data[i * stride_3_0]) +
            in5_data[i * stride_4_0];
    }
    *in1_size = b_in1_size;
    if (b_in1_size - 1 >= 0) {
        std::copy(&b_in1_data[0], &b_in1_data[b_in1_size], &in1_data[0]);
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const double in2_data[]
//                const int *in2_size
//                const double in3_data[]
//                const int *in3_size
//                const double in4_data[]
//                const int *in4_size
//                const double in5_data[]
//                const int *in5_size
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size,
                             const double in4_data[], const int *in4_size, const double in5_data[],
                             const int *in5_size)
{
    ::coder::array<double, 2U> b_in1;
    int b_in5_idx_0;
    int b_loop_ub;
    int in2_idx_0;
    int in3_idx_0;
    int in4_idx_0;
    int in5_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    int stride_4_0;
    in2_idx_0 = *in2_size;
    in3_idx_0 = *in3_size;
    in4_idx_0 = *in4_size;
    in5_idx_0 = *in5_size;
    if (in5_idx_0 == 1) {
        if (in4_idx_0 == 1) {
            if (in3_idx_0 == 1) {
                if (in2_idx_0 == 1) {
                    b_in5_idx_0 = in1.size(0);
                } else {
                    b_in5_idx_0 = in2_idx_0;
                }
            } else {
                b_in5_idx_0 = in3_idx_0;
            }
        } else {
            b_in5_idx_0 = in4_idx_0;
        }
    } else {
        b_in5_idx_0 = in5_idx_0;
    }
    b_in1.set_size(b_in5_idx_0, in1.size(1));
    stride_0_0 = (in1.size(0) != 1);
    stride_1_0 = (in2_idx_0 != 1);
    stride_2_0 = (in3_idx_0 != 1);
    stride_3_0 = (in4_idx_0 != 1);
    stride_4_0 = (in5_idx_0 != 1);
    loop_ub = in1.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int c_loop_ub;
        if (in5_idx_0 == 1) {
            if (in4_idx_0 == 1) {
                if (in3_idx_0 == 1) {
                    if (in2_idx_0 == 1) {
                        c_loop_ub = in1.size(0);
                    } else {
                        c_loop_ub = in2_idx_0;
                    }
                } else {
                    c_loop_ub = in3_idx_0;
                }
            } else {
                c_loop_ub = in4_idx_0;
            }
        } else {
            c_loop_ub = in5_idx_0;
        }
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            b_in1[i2 + b_in1.size(0) * i] =
                (((in1[i2 * stride_0_0 + in1.size(0) * i] + in2_data[i2 * stride_1_0]) +
                  in3_data[i2 * stride_2_0]) +
                 in4_data[i2 * stride_3_0]) +
                in5_data[i2 * stride_4_0];
        }
    }
    in1.set_size(b_in1.size(0), b_in1.size(1));
    b_loop_ub = b_in1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        int d_loop_ub;
        d_loop_ub = b_in1.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            in1[i3 + in1.size(0) * i1] = b_in1[i3 + b_in1.size(0) * i1];
        }
    }
}

//
// function [ kin, vec, params, type, resVec, resMatrix ] = export_kinematics( cfg, Rvec, RMatrix )
//
// Arguments    : const FeedoptConfig cfg
//                const double Rvec_data[]
//                const int Rvec_size[1]
//                const ::coder::array<double, 2U> &RMatrix
//                Kinematics *kin
//                double params_data[]
//                int params_size[1]
//                char type[8]
//                double resVec_data[]
//                int resVec_size[1]
//                ::coder::array<double, 2U> &resMatrix
// Return Type  : void
//
void export_kinematics(const FeedoptConfig cfg, const double Rvec_data[], const int Rvec_size[1],
                       const ::coder::array<double, 2U> &RMatrix, Kinematics *kin,
                       double params_data[], int params_size[1], char type[8], double resVec_data[],
                       int resVec_size[1], ::coder::array<double, 2U> &resMatrix)
{
    ::coder::array<double, 2U> b_resMatrix;
    ::coder::array<double, 2U> c_resMatrix;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 1U> a_piece;
    ::coder::array<double, 1U> b_Rvec_data;
    ::coder::array<double, 1U> c_Rvec_data;
    ::coder::array<double, 1U> d_Rvec_data;
    ::coder::array<double, 1U> e_Rvec_data;
    ::coder::array<double, 1U> f_Rvec_data;
    ::coder::array<double, 1U> g_Rvec_data;
    ::coder::array<double, 1U> h_Rvec_data;
    ::coder::array<double, 1U> i_Rvec_data;
    ::coder::array<double, 1U> j_Rvec_data;
    ::coder::array<double, 1U> j_piece;
    ::coder::array<double, 1U> k_Rvec_data;
    ::coder::array<double, 1U> piece;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> v_piece;
    double a_jointM_data[6];
    double a_joint_data[6];
    double j_jointM_data[6];
    double j_joint_data[6];
    double jointM_data[6];
    double joint_data[6];
    double v_jointM_data[6];
    double v_joint_data[6];
    double dv[3];
    int a_jointM_size;
    int a_joint_size;
    int b_resVec_size;
    int c_resVec_size;
    int d_resVec_size;
    int e_resVec_size;
    int f_resVec_size;
    int g_resVec_size;
    int h_resVec_size;
    int i;
    int i10;
    int i14;
    int i18;
    int i22;
    int i28;
    int i29;
    int i3;
    int i30;
    int i31;
    int i32;
    int i33;
    int i34;
    int i40;
    int i41;
    int i42;
    int i43;
    int i44;
    int i45;
    int i46;
    int i_resVec_size;
    int j_jointM_size;
    int j_joint_size;
    int j_resVec_size;
    int jointM_size;
    int joint_size;
    int k_resVec_size;
    int l_resVec_size;
    int m_resVec_size;
    int n_resVec_size;
    int o_resVec_size;
    int v_jointM_size;
    int v_joint_size;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    //  export_kinematics : Export the kinematics class using several entry
    //  functions. This necessary to export all the functions of a matlab class.
    //
    //  Inputs :
    //    cfg         : The configuration structure.
    //    Rvec        : Input vector with specific size for the code generation
    //    RMatrix     : Input matrix with specific size for the code generation
    //
    //  Outputs :
    //    kin         : The kinematics instance.
    //    vec         : The dummy vec
    //    params      : Vector parameters of the kinematics
    //    type        : Type of the kinematics
    //    resVec      : The resulting vector
    //    resMatrix   : The resulting matrix
    //
    // 'export_kinematics:19' vec     = [];
    // 'export_kinematics:20' kin     = kinematics_init( cfg.kin_type, cfg.kin_params );
    // 'export_kinematics:76' kin = Kinematics( type, params );
    // 'export_kinematics:21' kin     = kinematics_set_parameters( kin, cfg.kin_params );
    // 'export_kinematics:72' kin = kin.set_params( params );
    // 'export_kinematics:22' kin     = kinematics_set_type( kin, cfg.kin_type );
    // 'export_kinematics:80' kin = kin.set_type( type );
    // 'export_kinematics:23' kin     = kinematics_set_machine_offset( kin, zeros( 3, 1) );
    // 'export_kinematics:84' kin = kin.set_machine_offset( offset );
    kin->init(cfg.kin_type, cfg.kin_params.data, cfg.kin_params.size[0]);
    kin->set_params(cfg.kin_params.data, cfg.kin_params.size[0]);
    kin->set_type(cfg.kin_type);
    dv[0] = 0.0;
    dv[1] = 0.0;
    dv[2] = 0.0;
    kin->set_machine_offset(dv);
    // 'export_kinematics:24' kin     = kinematics_set_piece_offset( kin, zeros( 3, 1) );
    // 'export_kinematics:92' kin = kin.set_piece_offset( offset );
    dv[0] = 0.0;
    dv[1] = 0.0;
    dv[2] = 0.0;
    kin->set_piece_offset(dv);
    // 'export_kinematics:25' kin     = kinematics_set_tool_offset( kin, zeros( 3, 1) );
    // 'export_kinematics:88' kin = kin.set_tool_offset( offset );
    dv[0] = 0.0;
    dv[1] = 0.0;
    dv[2] = 0.0;
    kin->set_tool_offset(dv);
    // 'export_kinematics:26' kin     = kinematics_set_tool_length( kin, 0 );
    // 'export_kinematics:96' kin = kin.set_piece_offset( tool_length );
    kin->set_piece_offset();
    // 'export_kinematics:27' params  = kinematics_get_params( kin );
    // 'export_kinematics:100' params = kin.get_params();
    kin->get_params(params_data, &params_size[0]);
    // 'export_kinematics:28' type    = kinematics_get_type( kin );
    // 'export_kinematics:104' type = kin.get_type();
    kin->get_type(type);
    //  Forward kinematics (piece frame)
    // 'export_kinematics:31' resVec        = kinematics_r_relative( kin, Rvec );
    // 'export_kinematics:108' piece = kin.r_relative( joint );
    kin->r_relative(Rvec_data, Rvec_size[0], resVec_data, &resVec_size[0]);
    // 'export_kinematics:32' resMatrix     = kinematics_r_relative( kin, RMatrix );
    // 'export_kinematics:108' piece = kin.r_relative( joint );
    kin->r_relative(RMatrix, resMatrix);
    //  Inverse kinematics (joint frame)
    // 'export_kinematics:34' resVec        = resVec + kinematics_r_joint( kin, Rvec );
    // 'export_kinematics:112' joint = kin.r_joint( piece );
    r.reserve(6);
    kin->r_joint(Rvec_data, Rvec_size[0], (double *)r.data(), &i);
    (*(int(*)[1])r.size())[0] = i;
    if (resVec_size[0] == r.size(0)) {
        int loop_ub;
        int scalarLB;
        int vectorUB;
        loop_ub = resVec_size[0];
        scalarLB = (resVec_size[0] / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i1{0}; i1 <= vectorUB; i1 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&resVec_data[i1]);
            r3 = _mm_loadu_pd(&r[i1]);
            _mm_storeu_pd(&resVec_data[i1], _mm_add_pd(r2, r3));
        }
        for (int i1{scalarLB}; i1 < loop_ub; i1++) {
            resVec_data[i1] += r[i1];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:35' resMatrix     = resMatrix + kinematics_r_joint( kin, RMatrix );
    // 'export_kinematics:112' joint = kin.r_joint( piece );
    kin->r_joint(RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int b_loop_ub;
        b_loop_ub = resMatrix.size(1);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            int b_scalarLB;
            int b_vectorUB;
            int c_loop_ub;
            c_loop_ub = resMatrix.size(0);
            b_scalarLB = (resMatrix.size(0) / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (int i4{0}; i4 <= b_vectorUB; i4 += 2) {
                __m128d r4;
                __m128d r5;
                r4 = _mm_loadu_pd(&resMatrix[i4 + resMatrix.size(0) * i2]);
                r5 = _mm_loadu_pd(&r1[i4 + r1.size(0) * i2]);
                _mm_storeu_pd(&resMatrix[i4 + resMatrix.size(0) * i2], _mm_add_pd(r4, r5));
            }
            for (int i4{b_scalarLB}; i4 < c_loop_ub; i4++) {
                resMatrix[i4 + resMatrix.size(0) * i2] =
                    resMatrix[i4 + resMatrix.size(0) * i2] + r1[i4 + r1.size(0) * i2];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Speed on piece frame
    // 'export_kinematics:37' resVec        = resVec + kinematics_v_relative( kin, Rvec, Rvec );
    // 'export_kinematics:116' v_piece = kin.v_relative( joint, v_joint );
    r.reserve(6);
    kin->v_relative(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], (double *)r.data(), &i3);
    (*(int(*)[1])r.size())[0] = i3;
    if (resVec_size[0] == r.size(0)) {
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        d_loop_ub = resVec_size[0];
        c_scalarLB = (resVec_size[0] / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i5{0}; i5 <= c_vectorUB; i5 += 2) {
            __m128d r6;
            __m128d r7;
            r6 = _mm_loadu_pd(&resVec_data[i5]);
            r7 = _mm_loadu_pd(&r[i5]);
            _mm_storeu_pd(&resVec_data[i5], _mm_add_pd(r6, r7));
        }
        for (int i5{c_scalarLB}; i5 < d_loop_ub; i5++) {
            resVec_data[i5] += r[i5];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:38' resMatrix     = resMatrix + kinematics_v_relative( kin, RMatrix,
    // RMatrix ); 'export_kinematics:116' v_piece = kin.v_relative( joint, v_joint );
    kin->v_relative(RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int e_loop_ub;
        e_loop_ub = resMatrix.size(1);
        for (int i6{0}; i6 < e_loop_ub; i6++) {
            int d_scalarLB;
            int d_vectorUB;
            int f_loop_ub;
            f_loop_ub = resMatrix.size(0);
            d_scalarLB = (resMatrix.size(0) / 2) << 1;
            d_vectorUB = d_scalarLB - 2;
            for (int i7{0}; i7 <= d_vectorUB; i7 += 2) {
                __m128d r8;
                __m128d r9;
                r8 = _mm_loadu_pd(&resMatrix[i7 + resMatrix.size(0) * i6]);
                r9 = _mm_loadu_pd(&r1[i7 + r1.size(0) * i6]);
                _mm_storeu_pd(&resMatrix[i7 + resMatrix.size(0) * i6], _mm_add_pd(r8, r9));
            }
            for (int i7{d_scalarLB}; i7 < f_loop_ub; i7++) {
                resMatrix[i7 + resMatrix.size(0) * i6] =
                    resMatrix[i7 + resMatrix.size(0) * i6] + r1[i7 + r1.size(0) * i6];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Speed on joint frame
    // 'export_kinematics:40' resVec        = resVec + kinematics_v_joint( kin, Rvec, Rvec );
    // 'export_kinematics:120' v_joint = kin.v_joint( piece, v_piece );
    b_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    c_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    kin->v_joint(b_Rvec_data, c_Rvec_data, r);
    if (resVec_size[0] == r.size(0)) {
        int e_scalarLB;
        int e_vectorUB;
        int g_loop_ub;
        g_loop_ub = resVec_size[0];
        e_scalarLB = (resVec_size[0] / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i8{0}; i8 <= e_vectorUB; i8 += 2) {
            __m128d r10;
            __m128d r11;
            r10 = _mm_loadu_pd(&resVec_data[i8]);
            r11 = _mm_loadu_pd(&r[i8]);
            _mm_storeu_pd(&resVec_data[i8], _mm_add_pd(r10, r11));
        }
        for (int i8{e_scalarLB}; i8 < g_loop_ub; i8++) {
            resVec_data[i8] += r[i8];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:41' resMatrix     = resMatrix + kinematics_v_joint( kin, RMatrix, RMatrix
    // ); 'export_kinematics:120' v_joint = kin.v_joint( piece, v_piece );
    kin->v_joint(RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int h_loop_ub;
        h_loop_ub = resMatrix.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            int f_scalarLB;
            int f_vectorUB;
            int i_loop_ub;
            i_loop_ub = resMatrix.size(0);
            f_scalarLB = (resMatrix.size(0) / 2) << 1;
            f_vectorUB = f_scalarLB - 2;
            for (int i11{0}; i11 <= f_vectorUB; i11 += 2) {
                __m128d r12;
                __m128d r13;
                r12 = _mm_loadu_pd(&resMatrix[i11 + resMatrix.size(0) * i9]);
                r13 = _mm_loadu_pd(&r1[i11 + r1.size(0) * i9]);
                _mm_storeu_pd(&resMatrix[i11 + resMatrix.size(0) * i9], _mm_add_pd(r12, r13));
            }
            for (int i11{f_scalarLB}; i11 < i_loop_ub; i11++) {
                resMatrix[i11 + resMatrix.size(0) * i9] =
                    resMatrix[i11 + resMatrix.size(0) * i9] + r1[i11 + r1.size(0) * i9];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Acceleration on piece frame
    // 'export_kinematics:43' resVec        = resVec + kinematics_a_relative( kin, Rvec, Rvec, Rvec
    // ); 'export_kinematics:124' a_piece = kin.a_relative( joint, v_joint, a_joint );
    r.reserve(6);
    kin->a_relative(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0],
                    (double *)r.data(), &i10);
    (*(int(*)[1])r.size())[0] = i10;
    if (resVec_size[0] == r.size(0)) {
        int g_scalarLB;
        int g_vectorUB;
        int j_loop_ub;
        j_loop_ub = resVec_size[0];
        g_scalarLB = (resVec_size[0] / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (int i12{0}; i12 <= g_vectorUB; i12 += 2) {
            __m128d r14;
            __m128d r15;
            r14 = _mm_loadu_pd(&resVec_data[i12]);
            r15 = _mm_loadu_pd(&r[i12]);
            _mm_storeu_pd(&resVec_data[i12], _mm_add_pd(r14, r15));
        }
        for (int i12{g_scalarLB}; i12 < j_loop_ub; i12++) {
            resVec_data[i12] += r[i12];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:44' resMatrix     = resMatrix + kinematics_a_relative( kin, RMatrix,
    // RMatrix, RMatrix ); 'export_kinematics:124' a_piece = kin.a_relative( joint, v_joint, a_joint
    // );
    kin->a_relative(RMatrix, RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int k_loop_ub;
        k_loop_ub = resMatrix.size(1);
        for (int i13{0}; i13 < k_loop_ub; i13++) {
            int h_scalarLB;
            int h_vectorUB;
            int l_loop_ub;
            l_loop_ub = resMatrix.size(0);
            h_scalarLB = (resMatrix.size(0) / 2) << 1;
            h_vectorUB = h_scalarLB - 2;
            for (int i15{0}; i15 <= h_vectorUB; i15 += 2) {
                __m128d r16;
                __m128d r17;
                r16 = _mm_loadu_pd(&resMatrix[i15 + resMatrix.size(0) * i13]);
                r17 = _mm_loadu_pd(&r1[i15 + r1.size(0) * i13]);
                _mm_storeu_pd(&resMatrix[i15 + resMatrix.size(0) * i13], _mm_add_pd(r16, r17));
            }
            for (int i15{h_scalarLB}; i15 < l_loop_ub; i15++) {
                resMatrix[i15 + resMatrix.size(0) * i13] =
                    resMatrix[i15 + resMatrix.size(0) * i13] + r1[i15 + r1.size(0) * i13];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Acceleration on joint frame
    // 'export_kinematics:46' resVec        = resVec + kinematics_a_joint( kin, Rvec, Rvec, Rvec );
    // 'export_kinematics:128' a_joint = kin.a_joint( piece, v_piece, a_piece );
    r.reserve(6);
    kin->a_joint(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0],
                 (double *)r.data(), &i14);
    (*(int(*)[1])r.size())[0] = i14;
    if (resVec_size[0] == r.size(0)) {
        int i_scalarLB;
        int i_vectorUB;
        int m_loop_ub;
        m_loop_ub = resVec_size[0];
        i_scalarLB = (resVec_size[0] / 2) << 1;
        i_vectorUB = i_scalarLB - 2;
        for (int i16{0}; i16 <= i_vectorUB; i16 += 2) {
            __m128d r18;
            __m128d r19;
            r18 = _mm_loadu_pd(&resVec_data[i16]);
            r19 = _mm_loadu_pd(&r[i16]);
            _mm_storeu_pd(&resVec_data[i16], _mm_add_pd(r18, r19));
        }
        for (int i16{i_scalarLB}; i16 < m_loop_ub; i16++) {
            resVec_data[i16] += r[i16];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:47' resMatrix     = resMatrix + kinematics_a_joint( kin, RMatrix, RMatrix,
    // RMatrix ); 'export_kinematics:128' a_joint = kin.a_joint( piece, v_piece, a_piece );
    kin->a_joint(RMatrix, RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int n_loop_ub;
        n_loop_ub = resMatrix.size(1);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            int j_scalarLB;
            int j_vectorUB;
            int o_loop_ub;
            o_loop_ub = resMatrix.size(0);
            j_scalarLB = (resMatrix.size(0) / 2) << 1;
            j_vectorUB = j_scalarLB - 2;
            for (int i19{0}; i19 <= j_vectorUB; i19 += 2) {
                __m128d r20;
                __m128d r21;
                r20 = _mm_loadu_pd(&resMatrix[i19 + resMatrix.size(0) * i17]);
                r21 = _mm_loadu_pd(&r1[i19 + r1.size(0) * i17]);
                _mm_storeu_pd(&resMatrix[i19 + resMatrix.size(0) * i17], _mm_add_pd(r20, r21));
            }
            for (int i19{j_scalarLB}; i19 < o_loop_ub; i19++) {
                resMatrix[i19 + resMatrix.size(0) * i17] =
                    resMatrix[i19 + resMatrix.size(0) * i17] + r1[i19 + r1.size(0) * i17];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Jerk on piece frame
    // 'export_kinematics:49' resVec        = resVec + kinematics_j_relative( kin, Rvec, Rvec, Rvec,
    // Rvec ); 'export_kinematics:132' j_piece = kin.j_relative( joint, v_joint, a_joint, j_joint );
    r.reserve(6);
    kin->j_relative(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0],
                    Rvec_data, Rvec_size[0], (double *)r.data(), &i18);
    (*(int(*)[1])r.size())[0] = i18;
    if (resVec_size[0] == r.size(0)) {
        int k_scalarLB;
        int k_vectorUB;
        int p_loop_ub;
        p_loop_ub = resVec_size[0];
        k_scalarLB = (resVec_size[0] / 2) << 1;
        k_vectorUB = k_scalarLB - 2;
        for (int i20{0}; i20 <= k_vectorUB; i20 += 2) {
            __m128d r22;
            __m128d r23;
            r22 = _mm_loadu_pd(&resVec_data[i20]);
            r23 = _mm_loadu_pd(&r[i20]);
            _mm_storeu_pd(&resVec_data[i20], _mm_add_pd(r22, r23));
        }
        for (int i20{k_scalarLB}; i20 < p_loop_ub; i20++) {
            resVec_data[i20] += r[i20];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:50' resMatrix     = resMatrix + kinematics_j_relative( kin, RMatrix,
    // RMatrix, RMatrix, RMatrix ); 'export_kinematics:132' j_piece = kin.j_relative( joint,
    // v_joint, a_joint, j_joint );
    kin->j_relative(RMatrix, RMatrix, RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int q_loop_ub;
        q_loop_ub = resMatrix.size(1);
        for (int i21{0}; i21 < q_loop_ub; i21++) {
            int l_scalarLB;
            int l_vectorUB;
            int r_loop_ub;
            r_loop_ub = resMatrix.size(0);
            l_scalarLB = (resMatrix.size(0) / 2) << 1;
            l_vectorUB = l_scalarLB - 2;
            for (int i23{0}; i23 <= l_vectorUB; i23 += 2) {
                __m128d r24;
                __m128d r25;
                r24 = _mm_loadu_pd(&resMatrix[i23 + resMatrix.size(0) * i21]);
                r25 = _mm_loadu_pd(&r1[i23 + r1.size(0) * i21]);
                _mm_storeu_pd(&resMatrix[i23 + resMatrix.size(0) * i21], _mm_add_pd(r24, r25));
            }
            for (int i23{l_scalarLB}; i23 < r_loop_ub; i23++) {
                resMatrix[i23 + resMatrix.size(0) * i21] =
                    resMatrix[i23 + resMatrix.size(0) * i21] + r1[i23 + r1.size(0) * i21];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Jerk on joint frame
    // 'export_kinematics:52' resVec        = resVec + kinematics_j_joint( kin, Rvec, Rvec, Rvec,
    // Rvec ); 'export_kinematics:136' j_joint = kin.j_joint( piece, v_piece, a_piece, j_piece );
    r.reserve(6);
    kin->j_joint(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0],
                 Rvec_data, Rvec_size[0], (double *)r.data(), &i22);
    (*(int(*)[1])r.size())[0] = i22;
    if (resVec_size[0] == r.size(0)) {
        int m_scalarLB;
        int m_vectorUB;
        int s_loop_ub;
        s_loop_ub = resVec_size[0];
        m_scalarLB = (resVec_size[0] / 2) << 1;
        m_vectorUB = m_scalarLB - 2;
        for (int i24{0}; i24 <= m_vectorUB; i24 += 2) {
            __m128d r26;
            __m128d r27;
            r26 = _mm_loadu_pd(&resVec_data[i24]);
            r27 = _mm_loadu_pd(&r[i24]);
            _mm_storeu_pd(&resVec_data[i24], _mm_add_pd(r26, r27));
        }
        for (int i24{m_scalarLB}; i24 < s_loop_ub; i24++) {
            resVec_data[i24] += r[i24];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], r);
    }
    // 'export_kinematics:53' resMatrix     = resMatrix + kinematics_j_joint( kin, RMatrix, RMatrix,
    // RMatrix, RMatrix ); 'export_kinematics:136' j_joint = kin.j_joint( piece, v_piece, a_piece,
    // j_piece );
    kin->j_joint(RMatrix, RMatrix, RMatrix, RMatrix, r1);
    if ((resMatrix.size(0) == r1.size(0)) && (resMatrix.size(1) == r1.size(1))) {
        int t_loop_ub;
        t_loop_ub = resMatrix.size(1);
        for (int i25{0}; i25 < t_loop_ub; i25++) {
            int n_scalarLB;
            int n_vectorUB;
            int u_loop_ub;
            u_loop_ub = resMatrix.size(0);
            n_scalarLB = (resMatrix.size(0) / 2) << 1;
            n_vectorUB = n_scalarLB - 2;
            for (int i26{0}; i26 <= n_vectorUB; i26 += 2) {
                __m128d r28;
                __m128d r29;
                r28 = _mm_loadu_pd(&resMatrix[i26 + resMatrix.size(0) * i25]);
                r29 = _mm_loadu_pd(&r1[i26 + r1.size(0) * i25]);
                _mm_storeu_pd(&resMatrix[i26 + resMatrix.size(0) * i25], _mm_add_pd(r28, r29));
            }
            for (int i26{n_scalarLB}; i26 < u_loop_ub; i26++) {
                resMatrix[i26 + resMatrix.size(0) * i25] =
                    resMatrix[i26 + resMatrix.size(0) * i25] + r1[i26 + r1.size(0) * i25];
            }
        }
    } else {
        binary_expand_op(resMatrix, r1);
    }
    //  Complete transformation (Piece frame)
    // 'export_kinematics:56' [ piece, v_piece, a_piece, j_piece ] = kinematics_relative( kin, Rvec,
    // Rvec, Rvec, Rvec ); 'export_kinematics:140' [ piece, v_piece, a_piece, j_piece ] =
    // kin.relative( joint, v_joint, a_joint, j_joint );
    d_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    e_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    f_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    g_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    kin->relative(d_Rvec_data, e_Rvec_data, f_Rvec_data, g_Rvec_data, piece, v_piece, a_piece,
                  j_piece);
    // 'export_kinematics:57' resVec        = resVec + piece + v_piece + a_piece + j_piece;
    if (resVec_size[0] == 1) {
        b_resVec_size = piece.size(0);
    } else {
        b_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        c_resVec_size = piece.size(0);
    } else {
        c_resVec_size = resVec_size[0];
    }
    if (c_resVec_size == 1) {
        d_resVec_size = v_piece.size(0);
    } else if (resVec_size[0] == 1) {
        d_resVec_size = piece.size(0);
    } else {
        d_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        e_resVec_size = piece.size(0);
    } else {
        e_resVec_size = resVec_size[0];
    }
    if (e_resVec_size == 1) {
        f_resVec_size = v_piece.size(0);
    } else if (resVec_size[0] == 1) {
        f_resVec_size = piece.size(0);
    } else {
        f_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        g_resVec_size = piece.size(0);
    } else {
        g_resVec_size = resVec_size[0];
    }
    if (f_resVec_size == 1) {
        h_resVec_size = a_piece.size(0);
    } else if (g_resVec_size == 1) {
        h_resVec_size = v_piece.size(0);
    } else if (resVec_size[0] == 1) {
        h_resVec_size = piece.size(0);
    } else {
        h_resVec_size = resVec_size[0];
    }
    if ((resVec_size[0] == piece.size(0)) && (b_resVec_size == v_piece.size(0)) &&
        (d_resVec_size == a_piece.size(0)) && (h_resVec_size == j_piece.size(0))) {
        int o_scalarLB;
        int o_vectorUB;
        int v_loop_ub;
        v_loop_ub = resVec_size[0];
        o_scalarLB = (resVec_size[0] / 2) << 1;
        o_vectorUB = o_scalarLB - 2;
        for (int i27{0}; i27 <= o_vectorUB; i27 += 2) {
            __m128d r30;
            __m128d r31;
            __m128d r32;
            __m128d r33;
            __m128d r34;
            r30 = _mm_loadu_pd(&resVec_data[i27]);
            r31 = _mm_loadu_pd(&piece[i27]);
            r32 = _mm_loadu_pd(&v_piece[i27]);
            r33 = _mm_loadu_pd(&a_piece[i27]);
            r34 = _mm_loadu_pd(&j_piece[i27]);
            _mm_storeu_pd(&resVec_data[i27],
                          _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r30, r31), r32), r33), r34));
        }
        for (int i27{o_scalarLB}; i27 < v_loop_ub; i27++) {
            resVec_data[i27] =
                (((resVec_data[i27] + piece[i27]) + v_piece[i27]) + a_piece[i27]) + j_piece[i27];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], piece, v_piece, a_piece, j_piece);
    }
    // 'export_kinematics:59' [ pieceM, v_pieceM, a_pieceM, j_pieceM ] = kinematics_relative( kin,
    // Rvec, Rvec, Rvec, Rvec ); 'export_kinematics:140' [ piece, v_piece, a_piece, j_piece ] =
    // kin.relative( joint, v_joint, a_joint, j_joint );
    h_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    i_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    j_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    k_Rvec_data.set((double *)&Rvec_data[0], Rvec_size[0]);
    kin->relative(h_Rvec_data, i_Rvec_data, j_Rvec_data, k_Rvec_data, piece, v_piece, a_piece,
                  j_piece);
    // 'export_kinematics:60' resMatrix     = resMatrix + pieceM + v_pieceM + a_pieceM + j_pieceM;
    if (resMatrix.size(0) == 1) {
        i28 = piece.size(0);
    } else {
        i28 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i29 = piece.size(0);
    } else {
        i29 = resMatrix.size(0);
    }
    if (i29 == 1) {
        i30 = v_piece.size(0);
    } else if (resMatrix.size(0) == 1) {
        i30 = piece.size(0);
    } else {
        i30 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i31 = piece.size(0);
    } else {
        i31 = resMatrix.size(0);
    }
    if (i31 == 1) {
        i32 = v_piece.size(0);
    } else if (resMatrix.size(0) == 1) {
        i32 = piece.size(0);
    } else {
        i32 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i33 = piece.size(0);
    } else {
        i33 = resMatrix.size(0);
    }
    if (i32 == 1) {
        i34 = a_piece.size(0);
    } else if (i33 == 1) {
        i34 = v_piece.size(0);
    } else if (resMatrix.size(0) == 1) {
        i34 = piece.size(0);
    } else {
        i34 = resMatrix.size(0);
    }
    if ((resMatrix.size(0) == piece.size(0)) && (i28 == v_piece.size(0)) &&
        (i30 == a_piece.size(0)) && (i34 == j_piece.size(0))) {
        int w_loop_ub;
        int y_loop_ub;
        b_resMatrix.set_size(resMatrix.size(0), resMatrix.size(1));
        w_loop_ub = resMatrix.size(1);
        for (int i35{0}; i35 < w_loop_ub; i35++) {
            int p_scalarLB;
            int p_vectorUB;
            int x_loop_ub;
            x_loop_ub = resMatrix.size(0);
            p_scalarLB = (resMatrix.size(0) / 2) << 1;
            p_vectorUB = p_scalarLB - 2;
            for (int i37{0}; i37 <= p_vectorUB; i37 += 2) {
                __m128d r35;
                __m128d r36;
                __m128d r37;
                __m128d r38;
                __m128d r39;
                r35 = _mm_loadu_pd(&resMatrix[i37 + resMatrix.size(0) * i35]);
                r36 = _mm_loadu_pd(&piece[i37]);
                r37 = _mm_loadu_pd(&v_piece[i37]);
                r38 = _mm_loadu_pd(&a_piece[i37]);
                r39 = _mm_loadu_pd(&j_piece[i37]);
                _mm_storeu_pd(
                    &b_resMatrix[i37 + b_resMatrix.size(0) * i35],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r35, r36), r37), r38), r39));
            }
            for (int i37{p_scalarLB}; i37 < x_loop_ub; i37++) {
                b_resMatrix[i37 + b_resMatrix.size(0) * i35] =
                    (((resMatrix[i37 + resMatrix.size(0) * i35] + piece[i37]) + v_piece[i37]) +
                     a_piece[i37]) +
                    j_piece[i37];
            }
        }
        resMatrix.set_size(b_resMatrix.size(0), b_resMatrix.size(1));
        y_loop_ub = b_resMatrix.size(1);
        for (int i36{0}; i36 < y_loop_ub; i36++) {
            int ab_loop_ub;
            ab_loop_ub = b_resMatrix.size(0);
            for (int i38{0}; i38 < ab_loop_ub; i38++) {
                resMatrix[i38 + resMatrix.size(0) * i36] =
                    b_resMatrix[i38 + b_resMatrix.size(0) * i36];
            }
        }
    } else {
        binary_expand_op(resMatrix, piece, v_piece, a_piece, j_piece);
    }
    //  Complete transformation (Joint frame)
    // 'export_kinematics:63' [ joint, v_joint, a_joint, j_joint ] = kinematics_joint( kin, Rvec,
    // Rvec, Rvec, Rvec ); 'export_kinematics:144' [ joint, v_joint, a_joint, j_joint ] = kin.joint(
    // piece, v_piece, a_piece, j_piece );
    kin->joint(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data,
               Rvec_size[0], joint_data, &joint_size, v_joint_data, &v_joint_size, a_joint_data,
               &a_joint_size, j_joint_data, &j_joint_size);
    // 'export_kinematics:64' resVec        = resVec + joint + v_joint + a_joint + j_joint;
    if (resVec_size[0] == 1) {
        i_resVec_size = joint_size;
    } else {
        i_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        j_resVec_size = joint_size;
    } else {
        j_resVec_size = resVec_size[0];
    }
    if (j_resVec_size == 1) {
        k_resVec_size = v_joint_size;
    } else if (resVec_size[0] == 1) {
        k_resVec_size = joint_size;
    } else {
        k_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        l_resVec_size = joint_size;
    } else {
        l_resVec_size = resVec_size[0];
    }
    if (l_resVec_size == 1) {
        m_resVec_size = v_joint_size;
    } else if (resVec_size[0] == 1) {
        m_resVec_size = joint_size;
    } else {
        m_resVec_size = resVec_size[0];
    }
    if (resVec_size[0] == 1) {
        n_resVec_size = joint_size;
    } else {
        n_resVec_size = resVec_size[0];
    }
    if (m_resVec_size == 1) {
        o_resVec_size = a_joint_size;
    } else if (n_resVec_size == 1) {
        o_resVec_size = v_joint_size;
    } else if (resVec_size[0] == 1) {
        o_resVec_size = joint_size;
    } else {
        o_resVec_size = resVec_size[0];
    }
    if ((resVec_size[0] == joint_size) && (i_resVec_size == v_joint_size) &&
        (k_resVec_size == a_joint_size) && (o_resVec_size == j_joint_size)) {
        int bb_loop_ub;
        int q_scalarLB;
        int q_vectorUB;
        bb_loop_ub = resVec_size[0];
        q_scalarLB = (resVec_size[0] / 2) << 1;
        q_vectorUB = q_scalarLB - 2;
        for (int i39{0}; i39 <= q_vectorUB; i39 += 2) {
            __m128d r40;
            __m128d r41;
            __m128d r42;
            __m128d r43;
            __m128d r44;
            r40 = _mm_loadu_pd(&resVec_data[i39]);
            r41 = _mm_loadu_pd(&joint_data[i39]);
            r42 = _mm_loadu_pd(&v_joint_data[i39]);
            r43 = _mm_loadu_pd(&a_joint_data[i39]);
            r44 = _mm_loadu_pd(&j_joint_data[i39]);
            _mm_storeu_pd(&resVec_data[i39],
                          _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r40, r41), r42), r43), r44));
        }
        for (int i39{q_scalarLB}; i39 < bb_loop_ub; i39++) {
            resVec_data[i39] =
                (((resVec_data[i39] + joint_data[i39]) + v_joint_data[i39]) + a_joint_data[i39]) +
                j_joint_data[i39];
        }
    } else {
        binary_expand_op(resVec_data, &resVec_size[0], joint_data, &joint_size, v_joint_data,
                         &v_joint_size, a_joint_data, &a_joint_size, j_joint_data, &j_joint_size);
    }
    // 'export_kinematics:66' [ jointM, v_jointM, a_jointM, j_jointM ] = kinematics_joint( kin,
    // Rvec, Rvec, Rvec, Rvec ); 'export_kinematics:144' [ joint, v_joint, a_joint, j_joint ] =
    // kin.joint( piece, v_piece, a_piece, j_piece );
    kin->joint(Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data, Rvec_size[0], Rvec_data,
               Rvec_size[0], jointM_data, &jointM_size, v_jointM_data, &v_jointM_size,
               a_jointM_data, &a_jointM_size, j_jointM_data, &j_jointM_size);
    // 'export_kinematics:67' resMatrix     = resMatrix + jointM + v_jointM + a_jointM + j_jointM;
    if (resMatrix.size(0) == 1) {
        i40 = jointM_size;
    } else {
        i40 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i41 = jointM_size;
    } else {
        i41 = resMatrix.size(0);
    }
    if (i41 == 1) {
        i42 = v_jointM_size;
    } else if (resMatrix.size(0) == 1) {
        i42 = jointM_size;
    } else {
        i42 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i43 = jointM_size;
    } else {
        i43 = resMatrix.size(0);
    }
    if (i43 == 1) {
        i44 = v_jointM_size;
    } else if (resMatrix.size(0) == 1) {
        i44 = jointM_size;
    } else {
        i44 = resMatrix.size(0);
    }
    if (resMatrix.size(0) == 1) {
        i45 = jointM_size;
    } else {
        i45 = resMatrix.size(0);
    }
    if (i44 == 1) {
        i46 = a_jointM_size;
    } else if (i45 == 1) {
        i46 = v_jointM_size;
    } else if (resMatrix.size(0) == 1) {
        i46 = jointM_size;
    } else {
        i46 = resMatrix.size(0);
    }
    if ((resMatrix.size(0) == jointM_size) && (i40 == v_jointM_size) && (i42 == a_jointM_size) &&
        (i46 == j_jointM_size)) {
        int cb_loop_ub;
        int eb_loop_ub;
        c_resMatrix.set_size(resMatrix.size(0), resMatrix.size(1));
        cb_loop_ub = resMatrix.size(1);
        for (int i47{0}; i47 < cb_loop_ub; i47++) {
            int db_loop_ub;
            int r_scalarLB;
            int r_vectorUB;
            db_loop_ub = resMatrix.size(0);
            r_scalarLB = (resMatrix.size(0) / 2) << 1;
            r_vectorUB = r_scalarLB - 2;
            for (int i49{0}; i49 <= r_vectorUB; i49 += 2) {
                __m128d r45;
                __m128d r46;
                __m128d r47;
                __m128d r48;
                __m128d r49;
                r45 = _mm_loadu_pd(&resMatrix[i49 + resMatrix.size(0) * i47]);
                r46 = _mm_loadu_pd(&jointM_data[i49]);
                r47 = _mm_loadu_pd(&v_jointM_data[i49]);
                r48 = _mm_loadu_pd(&a_jointM_data[i49]);
                r49 = _mm_loadu_pd(&j_jointM_data[i49]);
                _mm_storeu_pd(
                    &c_resMatrix[i49 + c_resMatrix.size(0) * i47],
                    _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r45, r46), r47), r48), r49));
            }
            for (int i49{r_scalarLB}; i49 < db_loop_ub; i49++) {
                c_resMatrix[i49 + c_resMatrix.size(0) * i47] =
                    (((resMatrix[i49 + resMatrix.size(0) * i47] + jointM_data[i49]) +
                      v_jointM_data[i49]) +
                     a_jointM_data[i49]) +
                    j_jointM_data[i49];
            }
        }
        resMatrix.set_size(c_resMatrix.size(0), c_resMatrix.size(1));
        eb_loop_ub = c_resMatrix.size(1);
        for (int i48{0}; i48 < eb_loop_ub; i48++) {
            int fb_loop_ub;
            fb_loop_ub = c_resMatrix.size(0);
            for (int i50{0}; i50 < fb_loop_ub; i50++) {
                resMatrix[i50 + resMatrix.size(0) * i48] =
                    c_resMatrix[i50 + c_resMatrix.size(0) * i48];
            }
        }
    } else {
        binary_expand_op(resMatrix, jointM_data, &jointM_size, v_jointM_data, &v_jointM_size,
                         a_jointM_data, &a_jointM_size, j_jointM_data, &j_jointM_size);
    }
}

} // namespace ocn

//
// File trailer for export_kinematics.cpp
//
// [EOF]
//

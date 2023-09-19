//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: div.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "div.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const ::coder::array<double, 1U> &in3
//                const ::coder::array<double, 1U> &in4
//                const double in5_data[]
//                const int *in5_size
// Return Type  : void
//
namespace ocn {
void b_binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                        const ::coder::array<double, 1U> &in3,
                        const ::coder::array<double, 1U> &in4, const double in5_data[],
                        const int *in5_size)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    double f_in2;
    double g_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    b_in2 = in2[12];
    c_in2 = in2[13];
    d_in2 = in2[14];
    e_in2 = in2[15];
    f_in2 = in2[10];
    g_in2 = in2[11];
    if (*in5_size == 1) {
        if (in4.size(0) == 1) {
            *in1_size = in3.size(0);
        } else {
            *in1_size = in4.size(0);
        }
    } else {
        *in1_size = *in5_size;
    }
    stride_0_0 = (in3.size(0) != 1);
    stride_1_0 = (in4.size(0) != 1);
    stride_2_0 = (*in5_size != 1);
    stride_3_0 = (*in5_size != 1);
    if (*in5_size == 1) {
        if (in4.size(0) == 1) {
            loop_ub = in3.size(0);
        } else {
            loop_ub = in4.size(0);
        }
    } else {
        loop_ub = *in5_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = -(((b_in2 * in3[i * stride_0_0] + c_in2 * in4[i * stride_1_0]) +
                         d_in2 * in5_data[i * stride_2_0]) +
                        e_in2) /
                      (f_in2 * in5_data[i * stride_3_0] + g_in2);
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const double in3_data[]
//                const int *in3_size
//                const double in4_data[]
//                const int *in4_size
//                const double in5_data[]
//                const int *in5_size
//                const double in6_data[]
//                const int *in6_size
//                const double in7_data[]
//                const int *in7_size
//                const ::coder::array<double, 1U> &in8
//                const ::coder::array<double, 1U> &in9
//                const ::coder::array<double, 1U> &in10
// Return Type  : void
//
void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                      const double in3_data[], const int *in3_size, const double in4_data[],
                      const int *in4_size, const double in5_data[], const int *in5_size,
                      const double in6_data[], const int *in6_size, const double in7_data[],
                      const int *in7_size, const ::coder::array<double, 1U> &in8,
                      const ::coder::array<double, 1U> &in9, const ::coder::array<double, 1U> &in10)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    double f_in2;
    double g_in2;
    double h_in2;
    double i_in2;
    double j_in2;
    double k_in2;
    int b_in5_size;
    int c_in5_size;
    int d_in5_size;
    int e_in5_size;
    int f_in5_size;
    int g_in5_size;
    int h_in5_size;
    int i;
    int i2;
    int i_in5_size;
    int loop_ub;
    int q_in5_size;
    int r_in5_size;
    int s_in5_size;
    int stride_0_0;
    int stride_10_0;
    int stride_11_0;
    int stride_12_0;
    int stride_13_0;
    int stride_14_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    int stride_4_0;
    int stride_5_0;
    int stride_6_0;
    int stride_7_0;
    int stride_8_0;
    int stride_9_0;
    int t_in5_size;
    int u_in5_size;
    int v_in5_size;
    int w_in5_size;
    int x_in5_size;
    b_in2 = in2[15];
    c_in2 = in2[11];
    d_in2 = in2[9];
    e_in2 = in2[13];
    f_in2 = in2[12];
    g_in2 = in2[14];
    h_in2 = in2[10];
    i_in2 = in2[8];
    j_in2 = in2[13];
    k_in2 = in2[12];
    if (*in5_size == 1) {
        b_in5_size = in10.size(0);
    } else {
        b_in5_size = *in5_size;
    }
    if (b_in5_size == 1) {
        c_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        c_in5_size = in10.size(0);
    } else {
        c_in5_size = *in5_size;
    }
    if (*in5_size == 1) {
        d_in5_size = in10.size(0);
    } else {
        d_in5_size = *in5_size;
    }
    if (c_in5_size == 1) {
        e_in5_size = in9.size(0);
    } else if (d_in5_size == 1) {
        e_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        e_in5_size = in10.size(0);
    } else {
        e_in5_size = *in5_size;
    }
    if (in9.size(0) == 1) {
        i = *in7_size;
    } else {
        i = in9.size(0);
    }
    if (*in5_size == 1) {
        f_in5_size = in10.size(0);
    } else {
        f_in5_size = *in5_size;
    }
    if (f_in5_size == 1) {
        g_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        g_in5_size = in10.size(0);
    } else {
        g_in5_size = *in5_size;
    }
    if (*in5_size == 1) {
        h_in5_size = in10.size(0);
    } else {
        h_in5_size = *in5_size;
    }
    if (e_in5_size == 1) {
        if (i == 1) {
            if (*in4_size == 1) {
                i_in5_size = *in3_size;
            } else {
                i_in5_size = *in4_size;
            }
        } else if (in9.size(0) == 1) {
            i_in5_size = *in7_size;
        } else {
            i_in5_size = in9.size(0);
        }
    } else if (g_in5_size == 1) {
        i_in5_size = in9.size(0);
    } else if (h_in5_size == 1) {
        i_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        i_in5_size = in10.size(0);
    } else {
        i_in5_size = *in5_size;
    }
    if (i_in5_size == 1) {
        int b_in6_size;
        if (*in6_size == 1) {
            if (in8.size(0) == 1) {
                b_in6_size = *in7_size;
            } else {
                b_in6_size = in8.size(0);
            }
        } else {
            b_in6_size = *in6_size;
        }
        if (b_in6_size == 1) {
            int c_in6_size;
            if (*in6_size == 1) {
                c_in6_size = *in5_size;
            } else {
                c_in6_size = *in6_size;
            }
            if (c_in6_size == 1) {
                if (*in4_size == 1) {
                    *in1_size = *in3_size;
                } else {
                    *in1_size = *in4_size;
                }
            } else if (*in6_size == 1) {
                *in1_size = *in5_size;
            } else {
                *in1_size = *in6_size;
            }
        } else if (*in6_size == 1) {
            if (in8.size(0) == 1) {
                *in1_size = *in7_size;
            } else {
                *in1_size = in8.size(0);
            }
        } else {
            *in1_size = *in6_size;
        }
    } else {
        int j_in5_size;
        int k_in5_size;
        int l_in5_size;
        int m_in5_size;
        if (*in5_size == 1) {
            j_in5_size = in10.size(0);
        } else {
            j_in5_size = *in5_size;
        }
        if (j_in5_size == 1) {
            k_in5_size = *in6_size;
        } else if (*in5_size == 1) {
            k_in5_size = in10.size(0);
        } else {
            k_in5_size = *in5_size;
        }
        if (*in5_size == 1) {
            l_in5_size = in10.size(0);
        } else {
            l_in5_size = *in5_size;
        }
        if (k_in5_size == 1) {
            m_in5_size = in9.size(0);
        } else if (l_in5_size == 1) {
            m_in5_size = *in6_size;
        } else if (*in5_size == 1) {
            m_in5_size = in10.size(0);
        } else {
            m_in5_size = *in5_size;
        }
        if (m_in5_size == 1) {
            int i1;
            if (in9.size(0) == 1) {
                i1 = *in7_size;
            } else {
                i1 = in9.size(0);
            }
            if (i1 == 1) {
                if (*in4_size == 1) {
                    *in1_size = *in3_size;
                } else {
                    *in1_size = *in4_size;
                }
            } else if (in9.size(0) == 1) {
                *in1_size = *in7_size;
            } else {
                *in1_size = in9.size(0);
            }
        } else {
            int n_in5_size;
            int o_in5_size;
            if (*in5_size == 1) {
                n_in5_size = in10.size(0);
            } else {
                n_in5_size = *in5_size;
            }
            if (n_in5_size == 1) {
                o_in5_size = *in6_size;
            } else if (*in5_size == 1) {
                o_in5_size = in10.size(0);
            } else {
                o_in5_size = *in5_size;
            }
            if (o_in5_size == 1) {
                *in1_size = in9.size(0);
            } else {
                int p_in5_size;
                if (*in5_size == 1) {
                    p_in5_size = in10.size(0);
                } else {
                    p_in5_size = *in5_size;
                }
                if (p_in5_size == 1) {
                    *in1_size = *in6_size;
                } else if (*in5_size == 1) {
                    *in1_size = in10.size(0);
                } else {
                    *in1_size = *in5_size;
                }
            }
        }
    }
    stride_0_0 = (*in3_size != 1);
    stride_1_0 = (*in4_size != 1);
    stride_2_0 = (*in5_size != 1);
    stride_3_0 = (*in6_size != 1);
    stride_4_0 = (*in7_size != 1);
    stride_5_0 = (in8.size(0) != 1);
    stride_6_0 = (*in6_size != 1);
    stride_7_0 = (*in3_size != 1);
    stride_8_0 = (*in4_size != 1);
    stride_9_0 = (*in7_size != 1);
    stride_10_0 = (in9.size(0) != 1);
    stride_11_0 = (in9.size(0) != 1);
    stride_12_0 = (*in6_size != 1);
    stride_13_0 = (in10.size(0) != 1);
    stride_14_0 = (*in5_size != 1);
    if (*in5_size == 1) {
        q_in5_size = in10.size(0);
    } else {
        q_in5_size = *in5_size;
    }
    if (q_in5_size == 1) {
        r_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        r_in5_size = in10.size(0);
    } else {
        r_in5_size = *in5_size;
    }
    if (*in5_size == 1) {
        s_in5_size = in10.size(0);
    } else {
        s_in5_size = *in5_size;
    }
    if (r_in5_size == 1) {
        t_in5_size = in9.size(0);
    } else if (s_in5_size == 1) {
        t_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        t_in5_size = in10.size(0);
    } else {
        t_in5_size = *in5_size;
    }
    if (in9.size(0) == 1) {
        i2 = *in7_size;
    } else {
        i2 = in9.size(0);
    }
    if (*in5_size == 1) {
        u_in5_size = in10.size(0);
    } else {
        u_in5_size = *in5_size;
    }
    if (u_in5_size == 1) {
        v_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        v_in5_size = in10.size(0);
    } else {
        v_in5_size = *in5_size;
    }
    if (*in5_size == 1) {
        w_in5_size = in10.size(0);
    } else {
        w_in5_size = *in5_size;
    }
    if (t_in5_size == 1) {
        if (i2 == 1) {
            if (*in4_size == 1) {
                x_in5_size = *in3_size;
            } else {
                x_in5_size = *in4_size;
            }
        } else if (in9.size(0) == 1) {
            x_in5_size = *in7_size;
        } else {
            x_in5_size = in9.size(0);
        }
    } else if (v_in5_size == 1) {
        x_in5_size = in9.size(0);
    } else if (w_in5_size == 1) {
        x_in5_size = *in6_size;
    } else if (*in5_size == 1) {
        x_in5_size = in10.size(0);
    } else {
        x_in5_size = *in5_size;
    }
    if (x_in5_size == 1) {
        int d_in6_size;
        if (*in6_size == 1) {
            if (in8.size(0) == 1) {
                d_in6_size = *in7_size;
            } else {
                d_in6_size = in8.size(0);
            }
        } else {
            d_in6_size = *in6_size;
        }
        if (d_in6_size == 1) {
            int e_in6_size;
            if (*in6_size == 1) {
                e_in6_size = *in5_size;
            } else {
                e_in6_size = *in6_size;
            }
            if (e_in6_size == 1) {
                if (*in4_size == 1) {
                    loop_ub = *in3_size;
                } else {
                    loop_ub = *in4_size;
                }
            } else if (*in6_size == 1) {
                loop_ub = *in5_size;
            } else {
                loop_ub = *in6_size;
            }
        } else if (*in6_size == 1) {
            if (in8.size(0) == 1) {
                loop_ub = *in7_size;
            } else {
                loop_ub = in8.size(0);
            }
        } else {
            loop_ub = *in6_size;
        }
    } else {
        int ab_in5_size;
        int bb_in5_size;
        int cb_in5_size;
        int y_in5_size;
        if (*in5_size == 1) {
            y_in5_size = in10.size(0);
        } else {
            y_in5_size = *in5_size;
        }
        if (y_in5_size == 1) {
            ab_in5_size = *in6_size;
        } else if (*in5_size == 1) {
            ab_in5_size = in10.size(0);
        } else {
            ab_in5_size = *in5_size;
        }
        if (*in5_size == 1) {
            bb_in5_size = in10.size(0);
        } else {
            bb_in5_size = *in5_size;
        }
        if (ab_in5_size == 1) {
            cb_in5_size = in9.size(0);
        } else if (bb_in5_size == 1) {
            cb_in5_size = *in6_size;
        } else if (*in5_size == 1) {
            cb_in5_size = in10.size(0);
        } else {
            cb_in5_size = *in5_size;
        }
        if (cb_in5_size == 1) {
            int i4;
            if (in9.size(0) == 1) {
                i4 = *in7_size;
            } else {
                i4 = in9.size(0);
            }
            if (i4 == 1) {
                if (*in4_size == 1) {
                    loop_ub = *in3_size;
                } else {
                    loop_ub = *in4_size;
                }
            } else if (in9.size(0) == 1) {
                loop_ub = *in7_size;
            } else {
                loop_ub = in9.size(0);
            }
        } else {
            int db_in5_size;
            int eb_in5_size;
            if (*in5_size == 1) {
                db_in5_size = in10.size(0);
            } else {
                db_in5_size = *in5_size;
            }
            if (db_in5_size == 1) {
                eb_in5_size = *in6_size;
            } else if (*in5_size == 1) {
                eb_in5_size = in10.size(0);
            } else {
                eb_in5_size = *in5_size;
            }
            if (eb_in5_size == 1) {
                loop_ub = in9.size(0);
            } else {
                int fb_in5_size;
                if (*in5_size == 1) {
                    fb_in5_size = in10.size(0);
                } else {
                    fb_in5_size = *in5_size;
                }
                if (fb_in5_size == 1) {
                    loop_ub = *in6_size;
                } else if (*in5_size == 1) {
                    loop_ub = in10.size(0);
                } else {
                    loop_ub = *in5_size;
                }
            }
        }
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        in1_data[i3] =
            -((((b_in2 + in3_data[i3 * stride_0_0] * c_in2) + d_in2 * in4_data[i3 * stride_1_0]) -
               e_in2 * in5_data[i3 * stride_2_0] * in6_data[i3 * stride_3_0]) +
              f_in2 * in7_data[i3 * stride_4_0] * in8[i3 * stride_5_0] *
                  in6_data[i3 * stride_6_0]) /
            ((((g_in2 + in3_data[i3 * stride_7_0] * h_in2) + i_in2 * in4_data[i3 * stride_8_0]) -
              j_in2 * in7_data[i3 * stride_9_0] * in9[i3 * stride_10_0]) -
             k_in2 * in9[i3 * stride_11_0] *
                 (in6_data[i3 * stride_12_0] -
                  in10[i3 * stride_13_0] * in5_data[i3 * stride_14_0]));
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2[16]
//                const ::coder::array<double, 1U> &in3
//                const ::coder::array<double, 1U> &in4
//                const double in5_data[]
//                const int *in5_size
// Return Type  : void
//
void binary_expand_op(double in1_data[], int *in1_size, const double in2[16],
                      const ::coder::array<double, 1U> &in3, const ::coder::array<double, 1U> &in4,
                      const double in5_data[], const int *in5_size)
{
    double b_in2;
    double c_in2;
    double d_in2;
    double e_in2;
    double f_in2;
    double g_in2;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    int stride_3_0;
    b_in2 = in2[4];
    c_in2 = in2[5];
    d_in2 = in2[6];
    e_in2 = in2[7];
    f_in2 = in2[2];
    g_in2 = in2[3];
    if (*in5_size == 1) {
        if (in4.size(0) == 1) {
            *in1_size = in3.size(0);
        } else {
            *in1_size = in4.size(0);
        }
    } else {
        *in1_size = *in5_size;
    }
    stride_0_0 = (in3.size(0) != 1);
    stride_1_0 = (in4.size(0) != 1);
    stride_2_0 = (*in5_size != 1);
    stride_3_0 = (*in5_size != 1);
    if (*in5_size == 1) {
        if (in4.size(0) == 1) {
            loop_ub = in3.size(0);
        } else {
            loop_ub = in4.size(0);
        }
    } else {
        loop_ub = *in5_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = -(((b_in2 * in3[i * stride_0_0] + c_in2 * in4[i * stride_1_0]) +
                         d_in2 * in5_data[i * stride_2_0]) +
                        e_in2) /
                      (f_in2 * in5_data[i * stride_3_0] + g_in2);
    }
}

} // namespace ocn

//
// File trailer for div.cpp
//
// [EOF]
//

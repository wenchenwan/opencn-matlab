//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: div.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 14:58:55
//

// Include Files
#include "div.h"

// Function Definitions
//
// Arguments    : double alpha0_t_data[]
//                int *alpha0_t_size
//                const double CoefPS[16]
//                const double alpha1_t_data[]
//                const int *alpha1_t_size
//                const double t5_data[]
//                const int *t5_size
//                const double t11_data[]
//                const int *t11_size
//                const double t12_data[]
//                const int *t12_size
//                const double t10_data[]
//                const int *t10_size
//                const double _data[]
//                const int *_size
//                const double b__data[]
//                const int *b__size
// Return Type  : void
//
namespace ocn {
void binary_expand_op(double alpha0_t_data[], int *alpha0_t_size, const double CoefPS[16],
                      const double alpha1_t_data[], const int *alpha1_t_size,
                      const double t5_data[], const int *t5_size, const double t11_data[],
                      const int *t11_size, const double t12_data[], const int *t12_size,
                      const double t10_data[], const int *t10_size, const double _data[],
                      const int *_size, const double b__data[], const int *b__size)
{
    double b_CoefPS;
    double c_CoefPS;
    double d_CoefPS;
    double e_CoefPS;
    double f_CoefPS;
    double g_CoefPS;
    double h_CoefPS;
    double i_CoefPS;
    double j_CoefPS;
    double k_CoefPS;
    int ab_t11_size;
    int b_t11_size;
    int bb_t11_size;
    int c_t11_size;
    int d_t11_size;
    int e_t11_size;
    int f_t11_size;
    int g_t11_size;
    int h_t11_size;
    int i_t11_size;
    int j_t11_size;
    int loop_ub;
    int s_t11_size;
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
    int t_t11_size;
    int u_t11_size;
    int v_t11_size;
    int w_t11_size;
    int x_t11_size;
    int y_t11_size;
    b_CoefPS = CoefPS[15];
    c_CoefPS = CoefPS[11];
    d_CoefPS = CoefPS[9];
    e_CoefPS = CoefPS[13];
    f_CoefPS = CoefPS[12];
    g_CoefPS = CoefPS[14];
    h_CoefPS = CoefPS[10];
    i_CoefPS = CoefPS[8];
    j_CoefPS = CoefPS[13];
    k_CoefPS = CoefPS[12];
    if (*t11_size == 1) {
        b_t11_size = *b__size;
    } else {
        b_t11_size = *t11_size;
    }
    if (b_t11_size == 1) {
        c_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        c_t11_size = *b__size;
    } else {
        c_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        d_t11_size = *b__size;
    } else {
        d_t11_size = *t11_size;
    }
    if (c_t11_size == 1) {
        e_t11_size = *t11_size;
    } else if (d_t11_size == 1) {
        e_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        e_t11_size = *b__size;
    } else {
        e_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        f_t11_size = *t10_size;
        g_t11_size = *b__size;
    } else {
        f_t11_size = *t11_size;
        g_t11_size = *t11_size;
    }
    if (g_t11_size == 1) {
        h_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        h_t11_size = *b__size;
    } else {
        h_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        i_t11_size = *b__size;
    } else {
        i_t11_size = *t11_size;
    }
    if (e_t11_size == 1) {
        if (f_t11_size == 1) {
            if (*t5_size == 1) {
                j_t11_size = *alpha1_t_size;
            } else {
                j_t11_size = *t5_size;
            }
        } else if (*t11_size == 1) {
            j_t11_size = *t10_size;
        } else {
            j_t11_size = *t11_size;
        }
    } else if (h_t11_size == 1) {
        j_t11_size = *t11_size;
    } else if (i_t11_size == 1) {
        j_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        j_t11_size = *b__size;
    } else {
        j_t11_size = *t11_size;
    }
    if (j_t11_size == 1) {
        int b_t12_size;
        if (*t12_size == 1) {
            if (*_size == 1) {
                b_t12_size = *t10_size;
            } else {
                b_t12_size = *_size;
            }
        } else {
            b_t12_size = *t12_size;
        }
        if (b_t12_size == 1) {
            int c_t12_size;
            if (*t12_size == 1) {
                c_t12_size = *t11_size;
            } else {
                c_t12_size = *t12_size;
            }
            if (c_t12_size == 1) {
                if (*t5_size == 1) {
                    *alpha0_t_size = *alpha1_t_size;
                } else {
                    *alpha0_t_size = *t5_size;
                }
            } else if (*t12_size == 1) {
                *alpha0_t_size = *t11_size;
            } else {
                *alpha0_t_size = *t12_size;
            }
        } else if (*t12_size == 1) {
            if (*_size == 1) {
                *alpha0_t_size = *t10_size;
            } else {
                *alpha0_t_size = *_size;
            }
        } else {
            *alpha0_t_size = *t12_size;
        }
    } else {
        int k_t11_size;
        int l_t11_size;
        int m_t11_size;
        int n_t11_size;
        if (*t11_size == 1) {
            k_t11_size = *b__size;
        } else {
            k_t11_size = *t11_size;
        }
        if (k_t11_size == 1) {
            l_t11_size = *t12_size;
        } else if (*t11_size == 1) {
            l_t11_size = *b__size;
        } else {
            l_t11_size = *t11_size;
        }
        if (*t11_size == 1) {
            m_t11_size = *b__size;
        } else {
            m_t11_size = *t11_size;
        }
        if (l_t11_size == 1) {
            n_t11_size = *t11_size;
        } else if (m_t11_size == 1) {
            n_t11_size = *t12_size;
        } else if (*t11_size == 1) {
            n_t11_size = *b__size;
        } else {
            n_t11_size = *t11_size;
        }
        if (n_t11_size == 1) {
            int p_t11_size;
            if (*t11_size == 1) {
                p_t11_size = *t10_size;
            } else {
                p_t11_size = *t11_size;
            }
            if (p_t11_size == 1) {
                if (*t5_size == 1) {
                    *alpha0_t_size = *alpha1_t_size;
                } else {
                    *alpha0_t_size = *t5_size;
                }
            } else if (*t11_size == 1) {
                *alpha0_t_size = *t10_size;
            } else {
                *alpha0_t_size = *t11_size;
            }
        } else {
            int o_t11_size;
            int q_t11_size;
            if (*t11_size == 1) {
                o_t11_size = *b__size;
            } else {
                o_t11_size = *t11_size;
            }
            if (o_t11_size == 1) {
                q_t11_size = *t12_size;
            } else if (*t11_size == 1) {
                q_t11_size = *b__size;
            } else {
                q_t11_size = *t11_size;
            }
            if (q_t11_size == 1) {
                *alpha0_t_size = *t11_size;
            } else {
                int r_t11_size;
                if (*t11_size == 1) {
                    r_t11_size = *b__size;
                } else {
                    r_t11_size = *t11_size;
                }
                if (r_t11_size == 1) {
                    *alpha0_t_size = *t12_size;
                } else if (*t11_size == 1) {
                    *alpha0_t_size = *b__size;
                } else {
                    *alpha0_t_size = *t11_size;
                }
            }
        }
    }
    stride_0_0 = (*alpha1_t_size != 1);
    stride_1_0 = (*t5_size != 1);
    stride_2_0 = (*t11_size != 1);
    stride_3_0 = (*t12_size != 1);
    stride_4_0 = (*t10_size != 1);
    stride_5_0 = (*_size != 1);
    stride_6_0 = (*t12_size != 1);
    stride_7_0 = (*alpha1_t_size != 1);
    stride_8_0 = (*t5_size != 1);
    stride_9_0 = (*t10_size != 1);
    stride_10_0 = (*t11_size != 1);
    stride_11_0 = (*t11_size != 1);
    stride_12_0 = (*t12_size != 1);
    stride_13_0 = (*b__size != 1);
    stride_14_0 = (*t11_size != 1);
    if (*t11_size == 1) {
        s_t11_size = *b__size;
    } else {
        s_t11_size = *t11_size;
    }
    if (s_t11_size == 1) {
        t_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        t_t11_size = *b__size;
    } else {
        t_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        u_t11_size = *b__size;
    } else {
        u_t11_size = *t11_size;
    }
    if (t_t11_size == 1) {
        v_t11_size = *t11_size;
    } else if (u_t11_size == 1) {
        v_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        v_t11_size = *b__size;
    } else {
        v_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        w_t11_size = *t10_size;
        x_t11_size = *b__size;
    } else {
        w_t11_size = *t11_size;
        x_t11_size = *t11_size;
    }
    if (x_t11_size == 1) {
        y_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        y_t11_size = *b__size;
    } else {
        y_t11_size = *t11_size;
    }
    if (*t11_size == 1) {
        ab_t11_size = *b__size;
    } else {
        ab_t11_size = *t11_size;
    }
    if (v_t11_size == 1) {
        if (w_t11_size == 1) {
            if (*t5_size == 1) {
                bb_t11_size = *alpha1_t_size;
            } else {
                bb_t11_size = *t5_size;
            }
        } else if (*t11_size == 1) {
            bb_t11_size = *t10_size;
        } else {
            bb_t11_size = *t11_size;
        }
    } else if (y_t11_size == 1) {
        bb_t11_size = *t11_size;
    } else if (ab_t11_size == 1) {
        bb_t11_size = *t12_size;
    } else if (*t11_size == 1) {
        bb_t11_size = *b__size;
    } else {
        bb_t11_size = *t11_size;
    }
    if (bb_t11_size == 1) {
        int d_t12_size;
        if (*t12_size == 1) {
            if (*_size == 1) {
                d_t12_size = *t10_size;
            } else {
                d_t12_size = *_size;
            }
        } else {
            d_t12_size = *t12_size;
        }
        if (d_t12_size == 1) {
            int e_t12_size;
            if (*t12_size == 1) {
                e_t12_size = *t11_size;
            } else {
                e_t12_size = *t12_size;
            }
            if (e_t12_size == 1) {
                if (*t5_size == 1) {
                    loop_ub = *alpha1_t_size;
                } else {
                    loop_ub = *t5_size;
                }
            } else if (*t12_size == 1) {
                loop_ub = *t11_size;
            } else {
                loop_ub = *t12_size;
            }
        } else if (*t12_size == 1) {
            if (*_size == 1) {
                loop_ub = *t10_size;
            } else {
                loop_ub = *_size;
            }
        } else {
            loop_ub = *t12_size;
        }
    } else {
        int cb_t11_size;
        int db_t11_size;
        int eb_t11_size;
        int fb_t11_size;
        if (*t11_size == 1) {
            cb_t11_size = *b__size;
        } else {
            cb_t11_size = *t11_size;
        }
        if (cb_t11_size == 1) {
            db_t11_size = *t12_size;
        } else if (*t11_size == 1) {
            db_t11_size = *b__size;
        } else {
            db_t11_size = *t11_size;
        }
        if (*t11_size == 1) {
            eb_t11_size = *b__size;
        } else {
            eb_t11_size = *t11_size;
        }
        if (db_t11_size == 1) {
            fb_t11_size = *t11_size;
        } else if (eb_t11_size == 1) {
            fb_t11_size = *t12_size;
        } else if (*t11_size == 1) {
            fb_t11_size = *b__size;
        } else {
            fb_t11_size = *t11_size;
        }
        if (fb_t11_size == 1) {
            int hb_t11_size;
            if (*t11_size == 1) {
                hb_t11_size = *t10_size;
            } else {
                hb_t11_size = *t11_size;
            }
            if (hb_t11_size == 1) {
                if (*t5_size == 1) {
                    loop_ub = *alpha1_t_size;
                } else {
                    loop_ub = *t5_size;
                }
            } else if (*t11_size == 1) {
                loop_ub = *t10_size;
            } else {
                loop_ub = *t11_size;
            }
        } else {
            int gb_t11_size;
            int ib_t11_size;
            if (*t11_size == 1) {
                gb_t11_size = *b__size;
            } else {
                gb_t11_size = *t11_size;
            }
            if (gb_t11_size == 1) {
                ib_t11_size = *t12_size;
            } else if (*t11_size == 1) {
                ib_t11_size = *b__size;
            } else {
                ib_t11_size = *t11_size;
            }
            if (ib_t11_size == 1) {
                loop_ub = *t11_size;
            } else {
                int jb_t11_size;
                if (*t11_size == 1) {
                    jb_t11_size = *b__size;
                } else {
                    jb_t11_size = *t11_size;
                }
                if (jb_t11_size == 1) {
                    loop_ub = *t12_size;
                } else if (*t11_size == 1) {
                    loop_ub = *b__size;
                } else {
                    loop_ub = *t11_size;
                }
            }
        }
    }
    for (int i{0}; i < loop_ub; i++) {
        alpha0_t_data[i] = -((((b_CoefPS + alpha1_t_data[i * stride_0_0] * c_CoefPS) +
                               d_CoefPS * t5_data[i * stride_1_0]) -
                              e_CoefPS * t11_data[i * stride_2_0] * t12_data[i * stride_3_0]) +
                             f_CoefPS * t10_data[i * stride_4_0] * _data[i * stride_5_0] *
                                 t12_data[i * stride_6_0]) /
                           ((((g_CoefPS + alpha1_t_data[i * stride_7_0] * h_CoefPS) +
                              i_CoefPS * t5_data[i * stride_8_0]) -
                             j_CoefPS * t10_data[i * stride_9_0] * t11_data[i * stride_10_0]) -
                            k_CoefPS * t11_data[i * stride_11_0] *
                                (t12_data[i * stride_12_0] -
                                 b__data[i * stride_13_0] * t11_data[i * stride_14_0]));
    }
}

} // namespace ocn

//
// File trailer for div.cpp
//
// [EOF]
//

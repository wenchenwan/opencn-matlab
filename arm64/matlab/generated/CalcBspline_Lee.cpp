//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "CalcBspline_Lee.h"
#include "bspline_eval.h"
#include "bspline_eval_vec.h"
#include "mldivide.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>

// Function Definitions
//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : int cfg_SplineDegree
//                const double points[2][3]
//                double sp3D_CoeffX[4]
//                double sp3D_CoeffY[4]
//                double sp3D_CoeffZ[4]
//                int *sp3D_Bl_ncoeff
//                ::coder::array<double, 2U> &sp3D_Bl_breakpoints
//                unsigned long *sp3D_Bl_handle
//                int *sp3D_Bl_degree
//                double sp3D_knots[8]
// Return Type  : void
//
namespace ocn {
void CalcBspline_Lee(int cfg_SplineDegree, const double points[2][3], double sp3D_CoeffX[4],
                     double sp3D_CoeffY[4], double sp3D_CoeffZ[4], int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, double sp3D_knots[8])
{
    double A[4][4];
    double BasisVal[4][2];
    double x[3][2];
    double BasisValDD0[4];
    double BasisValDD1[4];
    double coef[4];
    double dv1[4];
    double breakpoints[2];
    double dv[2];
    double u[2];
    double a__2;
    double a__3;
    double a__4;
    double a__5;
    unsigned long Bl_handle;
    //  number of points in 3D space
    for (int i{0}; i < 3; i++) {
        x[i][0] = points[0][i];
        x[i][1] = points[1][i];
    }
    double d;
    d = std::pow((std::pow((&x[0][0])[1] - (&x[0][0])[0], 2.0) +
                  std::pow((&x[0][0])[3] - (&x[0][0])[2], 2.0)) +
                     std::pow((&x[0][0])[5] - (&x[0][0])[4], 2.0),
                 0.25);
    u[0] = 0.0 / d;
    u[1] = d / d;
    //  normalize knots to interval [0...1]
    sp3D_knots[0] = 0.0;
    sp3D_knots[1] = 0.0;
    sp3D_knots[2] = 0.0;
    sp3D_knots[3] = u[0];
    sp3D_knots[4] = u[1];
    sp3D_knots[5] = 1.0;
    sp3D_knots[6] = 1.0;
    sp3D_knots[7] = 1.0;
    breakpoints[0] = u[0];
    breakpoints[1] = u[1];
    c_bspline_create_with_breakpoints(&Bl_handle, cfg_SplineDegree, &breakpoints[0], 2);
    sp3D_Bl_breakpoints.set_size(1, 2);
    sp3D_Bl_breakpoints[0] = u[0];
    sp3D_Bl_breakpoints[1] = u[1];
    //  preallocation
    //  preallocation
    //  preallocation
    //
    for (int k{0}; k < 4; k++) {
        //  evaluate basis functions at the knots
        coef[0] = 0.0;
        coef[1] = 0.0;
        coef[2] = 0.0;
        coef[3] = 0.0;
        coef[k] = 1.0;
        //      sp             = spmak(knots, coef);
        //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
        bspline_eval_vec(Bl_handle, coef, u, dv);
        BasisVal[k][0] = dv[0];
        BasisVal[k][1] = dv[1];
        //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions
        //      @u=0,1
        a__2 = 0.0;
        bspline_eval(Bl_handle, coef, &a__2, &a__3, &BasisValDD0[k]);
        a__4 = 1.0;
        bspline_eval(Bl_handle, coef, &a__4, &a__5, &BasisValDD1[k]);
        //      BasisValDD0(k) = spval(sp2D, 0);
        //      BasisValDD1(k) = spval(sp2D, 1);
    }
    //
    for (int i1{0}; i1 < 4; i1++) {
        A[i1][0] = BasisValDD0[i1];
        A[i1][1] = BasisVal[i1][0];
        A[i1][2] = BasisVal[i1][1];
        A[i1][3] = BasisValDD1[i1];
    }
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    //  solve sparse banded linear system
    //  solve sparse banded linear system
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    dv1[0] = 0.0;
    dv1[1] = points[0][0];
    dv1[2] = points[1][0];
    dv1[3] = 0.0;
    coder::mldivide(A, dv1, sp3D_CoeffZ);
    sp3D_CoeffX[0] = sp3D_CoeffZ[0];
    sp3D_CoeffX[1] = sp3D_CoeffZ[1];
    sp3D_CoeffX[2] = sp3D_CoeffZ[2];
    sp3D_CoeffX[3] = sp3D_CoeffZ[3];
    dv1[0] = 0.0;
    dv1[1] = points[0][1];
    dv1[2] = points[1][1];
    dv1[3] = 0.0;
    coder::mldivide(A, dv1, sp3D_CoeffZ);
    sp3D_CoeffY[0] = sp3D_CoeffZ[0];
    sp3D_CoeffY[1] = sp3D_CoeffZ[1];
    sp3D_CoeffY[2] = sp3D_CoeffZ[2];
    sp3D_CoeffY[3] = sp3D_CoeffZ[3];
    dv1[0] = 0.0;
    dv1[1] = points[0][2];
    dv1[2] = points[1][2];
    dv1[3] = 0.0;
    coder::mldivide(A, dv1, sp3D_CoeffZ);
    //  else
    //      sp3D = CalcBspline_Lee_matlab(points);
    //  end
    *sp3D_Bl_ncoeff = cfg_SplineDegree;
    *sp3D_Bl_handle = Bl_handle;
    *sp3D_Bl_degree = cfg_SplineDegree;
}

//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : int cfg_SplineDegree
//                const ::coder::array<double, 2U> &points
//                ::coder::array<double, 2U> &sp3D_CoeffX
//                ::coder::array<double, 2U> &sp3D_CoeffY
//                ::coder::array<double, 2U> &sp3D_CoeffZ
//                int *sp3D_Bl_ncoeff
//                ::coder::array<double, 2U> &sp3D_Bl_breakpoints
//                unsigned long *sp3D_Bl_handle
//                int *sp3D_Bl_degree
//                ::coder::array<double, 2U> &sp3D_knots
// Return Type  : void
//
void CalcBspline_Lee(int cfg_SplineDegree, const ::coder::array<double, 2U> &points,
                     ::coder::array<double, 2U> &sp3D_CoeffX,
                     ::coder::array<double, 2U> &sp3D_CoeffY,
                     ::coder::array<double, 2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, ::coder::array<double, 2U> &sp3D_knots)
{
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValDD0;
    ::coder::array<double, 2U> BasisValDD1;
    ::coder::array<double, 2U> b_r;
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> c_z1;
    ::coder::array<double, 2U> coef;
    ::coder::array<double, 2U> du;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r2;
    double a__2;
    double a__3;
    double a__4;
    double a__5;
    double b_sp3D_Bl_breakpoints;
    unsigned long Bl_handle;
    int b_N;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int dimSize;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int i13;
    int i_loop_ub;
    int input_sizes_idx_0;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int t_loop_ub;
    int u_loop_ub;
    int unnamed_idx_1;
    //  number of points in 3D space
    x.set_size(points.size(1), 3);
    loop_ub = points.size(1);
    for (int i{0}; i < 3; i++) {
        for (int i1{0}; i1 < loop_ub; i1++) {
            x[i1 + x.size(0) * i] = points[i + 3 * i1];
        }
    }
    dimSize = x.size(0);
    if (x.size(0) == 0) {
        b_y1.set_size(0, 3);
    } else {
        int u0;
        int y;
        u0 = x.size(0) - 1;
        if (u0 < 1) {
            y = u0;
        } else {
            y = 1;
        }
        if (y < 1) {
            b_y1.set_size(0, 3);
        } else {
            b_y1.set_size(x.size(0) - 1, 3);
            if (x.size(0) - 1 != 0) {
                int iyStart;
                iyStart = 0;
                for (int r{0}; r < 3; r++) {
                    double work_data;
                    int ixLead_tmp;
                    ixLead_tmp = r * dimSize;
                    work_data = x[ixLead_tmp];
                    for (int m{2}; m <= dimSize; m++) {
                        double d;
                        double tmp1;
                        tmp1 = x[(ixLead_tmp + m) - 1];
                        d = tmp1;
                        tmp1 -= work_data;
                        work_data = d;
                        b_y1[(iyStart + m) - 2] = tmp1;
                    }
                    iyStart = (iyStart + dimSize) - 1;
                }
            }
        }
    }
    z1.set_size(b_y1.size(0), 3);
    for (int k{0}; k < 3; k++) {
        int N;
        N = z1.size(0);
        for (int b_k{0}; b_k < N; b_k++) {
            z1[b_k + z1.size(0) * k] = std::pow(b_y1[b_k + b_y1.size(0) * k], 2.0);
        }
    }
    b_z1.set_size(3, z1.size(0));
    b_loop_ub = z1.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        b_z1[3 * i2] = z1[i2];
        b_z1[3 * i2 + 1] = z1[i2 + z1.size(0)];
        b_z1[3 * i2 + 2] = z1[i2 + z1.size(0) * 2];
    }
    if (b_z1.size(1) == 0) {
        du.set_size(1, 0);
    } else {
        int i3;
        du.set_size(1, b_z1.size(1));
        i3 = b_z1.size(1);
        for (int c_k{0}; c_k < i3; c_k++) {
            du[c_k] = b_z1[3 * c_k];
            du[c_k] = du[c_k] + b_z1[3 * c_k + 1];
            du[c_k] = du[c_k] + b_z1[3 * c_k + 2];
        }
    }
    c_z1.set_size(1, du.size(1));
    b_N = du.size(1);
    for (int d_k{0}; d_k < b_N; d_k++) {
        c_z1[d_k] = std::pow(du[d_k], 0.25);
    }
    sp3D_Bl_breakpoints.set_size(1, c_z1.size(1) + 1);
    sp3D_Bl_breakpoints[0] = 0.0;
    c_loop_ub = c_z1.size(1);
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        sp3D_Bl_breakpoints[i4 + 1] = c_z1[i4];
    }
    if (sp3D_Bl_breakpoints.size(1) != 1) {
        int i5;
        i5 = sp3D_Bl_breakpoints.size(1);
        for (int e_k{0}; e_k <= i5 - 2; e_k++) {
            sp3D_Bl_breakpoints[e_k + 1] = sp3D_Bl_breakpoints[e_k] + sp3D_Bl_breakpoints[e_k + 1];
        }
    }
    b_sp3D_Bl_breakpoints = sp3D_Bl_breakpoints[sp3D_Bl_breakpoints.size(1) - 1];
    sp3D_Bl_breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    d_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        sp3D_Bl_breakpoints[i6] = sp3D_Bl_breakpoints[i6] / b_sp3D_Bl_breakpoints;
    }
    //  normalize knots to interval [0...1]
    sp3D_knots.set_size(1, sp3D_Bl_breakpoints.size(1) + 6);
    sp3D_knots[0] = 0.0;
    sp3D_knots[1] = 0.0;
    sp3D_knots[2] = 0.0;
    e_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        sp3D_knots[i7 + 3] = sp3D_Bl_breakpoints[i7];
    }
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 3] = 1.0;
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 4] = 1.0;
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 5] = 1.0;
    breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    f_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        breakpoints[i8] = sp3D_Bl_breakpoints[i8];
    }
    c_bspline_create_with_breakpoints(&Bl_handle, cfg_SplineDegree, &breakpoints[0],
                                      sp3D_Bl_breakpoints.size(1));
    BasisVal.set_size(points.size(1), points.size(1) + 2);
    g_loop_ub = points.size(1) + 2;
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        int h_loop_ub;
        h_loop_ub = points.size(1);
        for (int i10{0}; i10 < h_loop_ub; i10++) {
            BasisVal[i10 + BasisVal.size(0) * i9] = 0.0;
        }
    }
    //  preallocation
    BasisValDD0.set_size(1, points.size(1) + 2);
    i_loop_ub = points.size(1) + 2;
    for (int i11{0}; i11 < i_loop_ub; i11++) {
        BasisValDD0[i11] = 0.0;
    }
    //  preallocation
    unnamed_idx_1 = points.size(1) + 2;
    BasisValDD1.set_size(1, points.size(1) + 2);
    j_loop_ub = points.size(1) + 2;
    for (int i12{0}; i12 < j_loop_ub; i12++) {
        BasisValDD1[i12] = 0.0;
    }
    //  preallocation
    //
    i13 = points.size(1) + 1;
    if (0 <= points.size(1) + 1) {
        unnamed_idx_1 = points.size(1) + 2;
        k_loop_ub = points.size(1) + 2;
    }
    for (int f_k{0}; f_k <= i13; f_k++) {
        int n_loop_ub;
        //  evaluate basis functions at the knots
        coef.set_size(1, unnamed_idx_1);
        for (int i14{0}; i14 < k_loop_ub; i14++) {
            coef[i14] = 0.0;
        }
        coef[f_k] = 1.0;
        //      sp             = spmak(knots, coef);
        //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
        bspline_eval_vec(Bl_handle, coef, sp3D_Bl_breakpoints, b_r);
        n_loop_ub = BasisVal.size(0);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            BasisVal[i17 + BasisVal.size(0) * f_k] = b_r[i17];
        }
        //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions
        //      @u=0,1
        a__2 = 0.0;
        bspline_eval(Bl_handle, coef, &a__2, &a__3, &BasisValDD0[f_k]);
        a__4 = 1.0;
        bspline_eval(Bl_handle, coef, &a__4, &a__5, &BasisValDD1[f_k]);
        //      BasisValDD0(k) = spval(sp2D, 0);
        //      BasisValDD1(k) = spval(sp2D, 1);
    }
    //
    if ((BasisValDD0.size(1) == 0) || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
        input_sizes_idx_0 = BasisVal.size(0);
    } else {
        input_sizes_idx_0 = 0;
    }
    A.set_size(input_sizes_idx_0 + 2, BasisValDD0.size(1));
    l_loop_ub = BasisValDD0.size(1);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        A[A.size(0) * i15] = BasisValDD0[i15];
    }
    m_loop_ub = BasisValDD0.size(1);
    for (int i16{0}; i16 < m_loop_ub; i16++) {
        for (int i18{0}; i18 < input_sizes_idx_0; i18++) {
            A[(i18 + A.size(0) * i16) + 1] = BasisVal[i18 + input_sizes_idx_0 * i16];
        }
    }
    o_loop_ub = BasisValDD0.size(1);
    for (int i19{0}; i19 < o_loop_ub; i19++) {
        for (int i20{0}; i20 < 1; i20++) {
            A[(input_sizes_idx_0 + A.size(0) * i19) + 1] = BasisValDD1[i19];
        }
    }
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    //  solve sparse banded linear system
    //  solve sparse banded linear system
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    p_loop_ub = points.size(1);
    r1.set_size(points.size(1) + 2);
    r1[0] = 0.0;
    for (int i21{0}; i21 < p_loop_ub; i21++) {
        r1[i21 + 1] = points[3 * i21];
    }
    r1[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r1, r2);
    sp3D_CoeffX.set_size(1, r2.size(0));
    q_loop_ub = r2.size(0);
    for (int i22{0}; i22 < q_loop_ub; i22++) {
        sp3D_CoeffX[i22] = r2[i22];
    }
    r_loop_ub = points.size(1);
    r1.set_size(points.size(1) + 2);
    r1[0] = 0.0;
    for (int i23{0}; i23 < r_loop_ub; i23++) {
        r1[i23 + 1] = points[3 * i23 + 1];
    }
    r1[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r1, r2);
    sp3D_CoeffY.set_size(1, r2.size(0));
    s_loop_ub = r2.size(0);
    for (int i24{0}; i24 < s_loop_ub; i24++) {
        sp3D_CoeffY[i24] = r2[i24];
    }
    t_loop_ub = points.size(1);
    r1.set_size(points.size(1) + 2);
    r1[0] = 0.0;
    for (int i25{0}; i25 < t_loop_ub; i25++) {
        r1[i25 + 1] = points[3 * i25 + 2];
    }
    r1[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r1, r2);
    sp3D_CoeffZ.set_size(1, r2.size(0));
    u_loop_ub = r2.size(0);
    for (int i26{0}; i26 < u_loop_ub; i26++) {
        sp3D_CoeffZ[i26] = r2[i26];
    }
    int b_sp3D_Bl_ncoeff;
    b_sp3D_Bl_ncoeff = (sp3D_Bl_breakpoints.size(1) + cfg_SplineDegree) - 2;
    //  else
    //      sp3D = CalcBspline_Lee_matlab(points);
    //  end
    *sp3D_Bl_ncoeff = b_sp3D_Bl_ncoeff;
    *sp3D_Bl_handle = Bl_handle;
    *sp3D_Bl_degree = cfg_SplineDegree;
}

} // namespace ocn

//
// File trailer for CalcBspline_Lee.cpp
//
// [EOF]
//

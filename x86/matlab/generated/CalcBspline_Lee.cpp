//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "CalcBspline_Lee.h"
#include "bspline_eval.h"
#include "bspline_eval_vec.h"
#include "mldivide.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : int cfg_SplineDegree
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
void CalcBspline_Lee(int cfg_SplineDegree, double sp3D_CoeffX[4], double sp3D_CoeffY[4],
                     double sp3D_CoeffZ[4], int *sp3D_Bl_ncoeff,
                     ::coder::array<double, 2U> &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle,
                     int *sp3D_Bl_degree, double sp3D_knots[8])
{
    static const signed char bx[4]{0, 0, 1, 0};
    __m128d r;
    double A[4][4];
    double BasisVal[4][2];
    double BasisValDD0[4];
    double BasisValDD1[4];
    double coef[4];
    double breakpoints[2];
    double dv[2];
    double u[2];
    double a__2;
    double a__3;
    double a__4;
    double a__5;
    double u_tmp;
    double z1_tmp;
    unsigned long Bl_handle;
    signed char ipiv[4];
    //  number of points in 3D space
    z1_tmp = std::pow(1.0, 2.0);
    u[0] = 0.0;
    u_tmp = std::pow((z1_tmp + z1_tmp) + z1_tmp, 0.25);
    u[1] = u_tmp;
    r = _mm_loadu_pd(&u[0]);
    _mm_storeu_pd(&u[0], _mm_div_pd(r, _mm_set1_pd(u_tmp)));
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
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    for (int i{0}; i < 4; i++) {
        A[i][0] = BasisValDD0[i];
        A[i][1] = BasisVal[i][0];
        A[i][2] = BasisVal[i][1];
        A[i][3] = BasisValDD1[i];
        sp3D_CoeffX[i] = bx[i];
        ipiv[i] = static_cast<signed char>(i + 1);
    }
    for (int j{0}; j < 3; j++) {
        double smax;
        int a;
        int b_tmp;
        int jA;
        int jp1j;
        int mmj_tmp;
        int n;
        signed char i3;
        mmj_tmp = 2 - j;
        b_tmp = j * 5;
        jp1j = b_tmp + 2;
        n = 4 - j;
        a = 0;
        smax = std::abs((&A[0][0])[b_tmp]);
        for (int d_k{2}; d_k <= n; d_k++) {
            double s;
            s = std::abs((&A[0][0])[(b_tmp + d_k) - 1]);
            if (s > smax) {
                a = d_k - 1;
                smax = s;
            }
        }
        if ((&A[0][0])[b_tmp + a] != 0.0) {
            int i2;
            if (a != 0) {
                double temp;
                int ipiv_tmp;
                ipiv_tmp = j + a;
                ipiv[j] = static_cast<signed char>(ipiv_tmp + 1);
                temp = (&A[0][0])[j];
                (&A[0][0])[j] = (&A[0][0])[ipiv_tmp];
                (&A[0][0])[ipiv_tmp] = temp;
                temp = (&A[0][0])[j + 4];
                (&A[0][0])[j + 4] = (&A[0][0])[ipiv_tmp + 4];
                (&A[0][0])[ipiv_tmp + 4] = temp;
                temp = (&A[0][0])[j + 8];
                (&A[0][0])[j + 8] = (&A[0][0])[ipiv_tmp + 8];
                (&A[0][0])[ipiv_tmp + 8] = temp;
                temp = (&A[0][0])[j + 12];
                (&A[0][0])[j + 12] = (&A[0][0])[ipiv_tmp + 12];
                (&A[0][0])[ipiv_tmp + 12] = temp;
            }
            i2 = (b_tmp - j) + 4;
            for (int d_i{jp1j}; d_i <= i2; d_i++) {
                (&A[0][0])[d_i - 1] /= (&A[0][0])[b_tmp];
            }
        }
        jA = b_tmp;
        for (int b_j{0}; b_j <= mmj_tmp; b_j++) {
            double yjy_tmp;
            yjy_tmp = (&A[0][0])[(b_tmp + (b_j << 2)) + 4];
            if (yjy_tmp != 0.0) {
                int i4;
                int i5;
                i4 = jA + 6;
                i5 = (jA - j) + 8;
                for (int ijA{i4}; ijA <= i5; ijA++) {
                    (&A[0][0])[ijA - 1] += (&A[0][0])[((b_tmp + ijA) - jA) - 5] * -yjy_tmp;
                }
            }
            jA += 4;
        }
        i3 = ipiv[j];
        if (i3 != j + 1) {
            double b_temp;
            b_temp = sp3D_CoeffX[j];
            sp3D_CoeffX[j] = sp3D_CoeffX[i3 - 1];
            sp3D_CoeffX[i3 - 1] = b_temp;
        }
    }
    for (int b_k{0}; b_k < 4; b_k++) {
        int kAcol;
        kAcol = b_k << 2;
        if (sp3D_CoeffX[b_k] != 0.0) {
            int i1;
            i1 = b_k + 2;
            for (int b_i{i1}; b_i < 5; b_i++) {
                sp3D_CoeffX[b_i - 1] -= sp3D_CoeffX[b_k] * (&A[0][0])[(b_i + kAcol) - 1];
            }
        }
    }
    for (int c_k{3}; c_k >= 0; c_k--) {
        int b_kAcol;
        b_kAcol = c_k << 2;
        if (sp3D_CoeffX[c_k] != 0.0) {
            sp3D_CoeffX[c_k] /= (&A[0][0])[c_k + b_kAcol];
            for (int c_i{0}; c_i < c_k; c_i++) {
                sp3D_CoeffX[c_i] -= sp3D_CoeffX[c_k] * (&A[0][0])[c_i + b_kAcol];
            }
        }
    }
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    sp3D_CoeffY[0] = sp3D_CoeffX[0];
    sp3D_CoeffZ[0] = sp3D_CoeffX[0];
    sp3D_CoeffY[1] = sp3D_CoeffX[1];
    sp3D_CoeffZ[1] = sp3D_CoeffX[1];
    sp3D_CoeffY[2] = sp3D_CoeffX[2];
    sp3D_CoeffZ[2] = sp3D_CoeffX[2];
    sp3D_CoeffY[3] = sp3D_CoeffX[3];
    sp3D_CoeffZ[3] = sp3D_CoeffX[3];
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
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> coef;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> r4;
    ::coder::array<double, 1U> r5;
    double a__2;
    double a__3;
    double a__4;
    double a__5;
    double b_sp3D_Bl_breakpoints;
    unsigned long Bl_handle;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int dimSize;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i16;
    int i9;
    int i_loop_ub;
    int input_sizes_idx_0;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int scalarLB;
    int t_loop_ub;
    int u_loop_ub;
    int unnamed_idx_1;
    int v_loop_ub;
    int vectorUB;
    int w_loop_ub;
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
        if (u0 <= 1) {
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
                for (int b_r{0}; b_r < 3; b_r++) {
                    double work_data;
                    int ixLead_tmp;
                    ixLead_tmp = b_r * dimSize;
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
    r.set_size(b_y1.size(0), 3);
    b_loop_ub = b_y1.size(0);
    for (int i2{0}; i2 < 3; i2++) {
        for (int i3{0}; i3 < b_loop_ub; i3++) {
            double varargin_1;
            varargin_1 = b_y1[i3 + b_y1.size(0) * i2];
            r[i3 + r.size(0) * i2] = std::pow(varargin_1, 2.0);
        }
    }
    r1.set_size(3, r.size(0));
    c_loop_ub = r.size(0);
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        r1[3 * i4] = r[i4];
        r1[3 * i4 + 1] = r[i4 + r.size(0)];
        r1[3 * i4 + 2] = r[i4 + r.size(0) * 2];
    }
    if (r1.size(1) == 0) {
        r2.set_size(1, 0);
    } else {
        int i5;
        r2.set_size(1, r1.size(1));
        i5 = r1.size(1);
        for (int k{0}; k < i5; k++) {
            r2[k] = r1[3 * k];
            r2[k] = r2[k] + r1[3 * k + 1];
            r2[k] = r2[k] + r1[3 * k + 2];
        }
    }
    r2.set_size(1, r2.size(1));
    d_loop_ub = r2.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        double b_varargin_1;
        b_varargin_1 = r2[i6];
        r2[i6] = std::pow(b_varargin_1, 0.25);
    }
    sp3D_Bl_breakpoints.set_size(1, r2.size(1) + 1);
    sp3D_Bl_breakpoints[0] = 0.0;
    e_loop_ub = r2.size(1);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        sp3D_Bl_breakpoints[i7 + 1] = r2[i7];
    }
    if (sp3D_Bl_breakpoints.size(1) != 1) {
        int i8;
        i8 = sp3D_Bl_breakpoints.size(1);
        for (int b_k{0}; b_k <= i8 - 2; b_k++) {
            sp3D_Bl_breakpoints[b_k + 1] = sp3D_Bl_breakpoints[b_k] + sp3D_Bl_breakpoints[b_k + 1];
        }
    }
    b_sp3D_Bl_breakpoints = sp3D_Bl_breakpoints[sp3D_Bl_breakpoints.size(1) - 1];
    sp3D_Bl_breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    f_loop_ub = sp3D_Bl_breakpoints.size(1);
    scalarLB = (sp3D_Bl_breakpoints.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i9 = 0; i9 <= vectorUB; i9 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&sp3D_Bl_breakpoints[i9]);
        _mm_storeu_pd(&sp3D_Bl_breakpoints[i9], _mm_div_pd(r3, _mm_set1_pd(b_sp3D_Bl_breakpoints)));
    }
    for (i9 = scalarLB; i9 < f_loop_ub; i9++) {
        sp3D_Bl_breakpoints[i9] = sp3D_Bl_breakpoints[i9] / b_sp3D_Bl_breakpoints;
    }
    //  normalize knots to interval [0...1]
    sp3D_knots.set_size(1, sp3D_Bl_breakpoints.size(1) + 6);
    sp3D_knots[0] = 0.0;
    sp3D_knots[1] = 0.0;
    sp3D_knots[2] = 0.0;
    g_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        sp3D_knots[i10 + 3] = sp3D_Bl_breakpoints[i10];
    }
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 3] = 1.0;
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 4] = 1.0;
    sp3D_knots[sp3D_Bl_breakpoints.size(1) + 5] = 1.0;
    breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    h_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        breakpoints[i11] = sp3D_Bl_breakpoints[i11];
    }
    c_bspline_create_with_breakpoints(&Bl_handle, cfg_SplineDegree, &breakpoints[0],
                                      sp3D_Bl_breakpoints.size(1));
    BasisVal.set_size(points.size(1), points.size(1) + 2);
    i_loop_ub = points.size(1) + 2;
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        int j_loop_ub;
        j_loop_ub = points.size(1);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            BasisVal[i13 + BasisVal.size(0) * i12] = 0.0;
        }
    }
    //  preallocation
    BasisValDD0.set_size(1, points.size(1) + 2);
    k_loop_ub = points.size(1) + 2;
    for (int i14{0}; i14 < k_loop_ub; i14++) {
        BasisValDD0[i14] = 0.0;
    }
    //  preallocation
    unnamed_idx_1 = points.size(1) + 2;
    BasisValDD1.set_size(1, points.size(1) + 2);
    l_loop_ub = points.size(1) + 2;
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        BasisValDD1[i15] = 0.0;
    }
    //  preallocation
    //
    i16 = points.size(1) + 1;
    if (0 <= points.size(1) + 1) {
        unnamed_idx_1 = points.size(1) + 2;
        m_loop_ub = points.size(1) + 2;
    }
    for (int c_k{0}; c_k <= i16; c_k++) {
        int p_loop_ub;
        //  evaluate basis functions at the knots
        coef.set_size(1, unnamed_idx_1);
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            coef[i17] = 0.0;
        }
        coef[c_k] = 1.0;
        //      sp             = spmak(knots, coef);
        //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
        bspline_eval_vec(Bl_handle, coef, sp3D_Bl_breakpoints, r2);
        p_loop_ub = BasisVal.size(0);
        for (int i20{0}; i20 < p_loop_ub; i20++) {
            BasisVal[i20 + BasisVal.size(0) * c_k] = r2[i20];
        }
        //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions
        //      @u=0,1
        a__2 = 0.0;
        bspline_eval(Bl_handle, coef, &a__2, &a__3, &BasisValDD0[c_k]);
        a__4 = 1.0;
        bspline_eval(Bl_handle, coef, &a__4, &a__5, &BasisValDD1[c_k]);
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
    n_loop_ub = BasisValDD0.size(1);
    for (int i18{0}; i18 < n_loop_ub; i18++) {
        A[A.size(0) * i18] = BasisValDD0[i18];
    }
    o_loop_ub = BasisValDD0.size(1);
    for (int i19{0}; i19 < o_loop_ub; i19++) {
        for (int i21{0}; i21 < input_sizes_idx_0; i21++) {
            A[(i21 + A.size(0) * i19) + 1] = BasisVal[i21 + input_sizes_idx_0 * i19];
        }
    }
    q_loop_ub = BasisValDD0.size(1);
    for (int i22{0}; i22 < q_loop_ub; i22++) {
        A[(input_sizes_idx_0 + A.size(0) * i22) + 1] = BasisValDD1[i22];
    }
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    r_loop_ub = points.size(1);
    r4.set_size(points.size(1) + 2);
    r4[0] = 0.0;
    for (int i23{0}; i23 < r_loop_ub; i23++) {
        r4[i23 + 1] = points[3 * i23];
    }
    r4[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r4, r5);
    sp3D_CoeffX.set_size(1, r5.size(0));
    s_loop_ub = r5.size(0);
    for (int i24{0}; i24 < s_loop_ub; i24++) {
        sp3D_CoeffX[i24] = r5[i24];
    }
    t_loop_ub = points.size(1);
    r4.set_size(points.size(1) + 2);
    r4[0] = 0.0;
    for (int i25{0}; i25 < t_loop_ub; i25++) {
        r4[i25 + 1] = points[3 * i25 + 1];
    }
    r4[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r4, r5);
    sp3D_CoeffY.set_size(1, r5.size(0));
    u_loop_ub = r5.size(0);
    for (int i26{0}; i26 < u_loop_ub; i26++) {
        sp3D_CoeffY[i26] = r5[i26];
    }
    v_loop_ub = points.size(1);
    r4.set_size(points.size(1) + 2);
    r4[0] = 0.0;
    for (int i27{0}; i27 < v_loop_ub; i27++) {
        r4[i27 + 1] = points[3 * i27 + 2];
    }
    r4[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r4, r5);
    sp3D_CoeffZ.set_size(1, r5.size(0));
    w_loop_ub = r5.size(0);
    for (int i28{0}; i28 < w_loop_ub; i28++) {
        sp3D_CoeffZ[i28] = r5[i28];
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

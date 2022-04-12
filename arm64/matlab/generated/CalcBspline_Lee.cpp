//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

// Include Files
#include "CalcBspline_Lee.h"
#include "bspline_eval.h"
#include "mldivide.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>

// Function Definitions
//
// function sp3D = CalcBspline_Lee(cfg, points)
//
// Arguments    : int cfg_LeeSplineDegree
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
namespace ocn {
void CalcBspline_Lee(int cfg_LeeSplineDegree, const ::coder::array<double, 2U> &points,
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
    ::coder::array<double, 2U> xd;
    ::coder::array<double, 2U> xdd;
    ::coder::array<double, 2U> xddd;
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> r4;
    double a__2;
    double a__3;
    double a__4;
    double a__5;
    double b_sp3D_Bl_breakpoints;
    double d1;
    double d2;
    double d3;
    unsigned long Bl_handle;
    int N;
    int ab_loop_ub;
    int b_loop_ub;
    int bb_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int dimSize;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i16;
    int i_loop_ub;
    int input_sizes_idx_0;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int v_loop_ub;
    int w_loop_ub;
    int x_loop_ub;
    int y_loop_ub;
    // 'CalcBspline_Lee:3' [~, N] = size(points);
    N = points.size(1);
    //  number of points in 3D space
    // 'CalcBspline_Lee:4' du     = sum((diff(points.').^2).');
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
    // 'CalcBspline_Lee:5' u      = cumsum([0,du.^(1/4)]);
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
    // 'CalcBspline_Lee:6' u      = u / u(end);
    b_sp3D_Bl_breakpoints = sp3D_Bl_breakpoints[sp3D_Bl_breakpoints.size(1) - 1];
    sp3D_Bl_breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    f_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        sp3D_Bl_breakpoints[i9] = sp3D_Bl_breakpoints[i9] / b_sp3D_Bl_breakpoints;
    }
    //  normalize knots to interval [0...1]
    // 'CalcBspline_Lee:7' knots  = [zeros(1, 3), u, ones(1, 3)];
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
    // 'CalcBspline_Lee:9' Bl = bspline_create(cfg.LeeSplineDegree, u);
    // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:8' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:9' coder.cinclude('src/c_spline.h');
    // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
    h_loop_ub = sp3D_Bl_breakpoints.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        breakpoints[i11] = sp3D_Bl_breakpoints[i11];
    }
    c_bspline_create_with_breakpoints(&Bl_handle, cfg_LeeSplineDegree, &breakpoints[0],
                                      sp3D_Bl_breakpoints.size(1));
    // 'bspline_create:11' Bl.ncoeff = ncoeff;
    // 'bspline_create:12' Bl.breakpoints = breakpoints;
    // 'bspline_create:13' Bl.handle = h;
    // 'bspline_create:14' Bl.degree = int32(degree);
    // 'bspline_create:15' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
    // 'CalcBspline_Lee:11' BasisVal    = zeros(N, N+2);
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
    // 'CalcBspline_Lee:12' BasisValDD0 = zeros(1, N+2);
    BasisValDD0.set_size(1, points.size(1) + 2);
    k_loop_ub = points.size(1) + 2;
    for (int i14{0}; i14 < k_loop_ub; i14++) {
        BasisValDD0[i14] = 0.0;
    }
    //  preallocation
    // 'CalcBspline_Lee:13' BasisValDD1 = zeros(1, N+2);
    BasisValDD1.set_size(1, points.size(1) + 2);
    l_loop_ub = points.size(1) + 2;
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        BasisValDD1[i15] = 0.0;
    }
    //  preallocation
    //
    // 'CalcBspline_Lee:15' for k = 1:N+2
    i16 = points.size(1) + 1;
    for (int c_k{0}; c_k <= i16; c_k++) {
        int i26;
        int m_loop_ub;
        int q_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        int t_loop_ub;
        int u_loop_ub;
        //  evaluate basis functions at the knots
        // 'CalcBspline_Lee:16' coef           = zeros(1, N+2);
        coef.set_size(1, N + 2);
        m_loop_ub = N + 2;
        for (int i17{0}; i17 < m_loop_ub; i17++) {
            coef[i17] = 0.0;
        }
        // 'CalcBspline_Lee:17' coef(:, k)     = 1;
        coef[c_k] = 1.0;
        //      sp             = spmak(knots, coef);
        //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
        // 'CalcBspline_Lee:20' BasisVal(:, k) = bspline_eval_vec(Bl, coef, u);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        r2.set_size(1, sp3D_Bl_breakpoints.size(1));
        q_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i22{0}; i22 < q_loop_ub; i22++) {
            r2[i22] = 0.0;
        }
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        xd.set_size(1, sp3D_Bl_breakpoints.size(1));
        r_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i23{0}; i23 < r_loop_ub; i23++) {
            xd[i23] = 0.0;
        }
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        xdd.set_size(1, sp3D_Bl_breakpoints.size(1));
        s_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i24{0}; i24 < s_loop_ub; i24++) {
            xdd[i24] = 0.0;
        }
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        xddd.set_size(1, sp3D_Bl_breakpoints.size(1));
        t_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i25{0}; i25 < t_loop_ub; i25++) {
            xddd[i25] = 0.0;
        }
        // 'bspline_eval_vec:8' for k = 1:length(u)
        i26 = sp3D_Bl_breakpoints.size(1);
        for (int d_k{0}; d_k < i26; d_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r2[d_k] = sp3D_Bl_breakpoints[d_k];
            bspline_eval(Bl_handle, coef, &r2[d_k], &d1, &d2, &d3);
            xddd[d_k] = d3;
            xdd[d_k] = d2;
            xd[d_k] = d1;
            // 'bspline_eval_vec:10' x(k) = xk;
            // 'bspline_eval_vec:11' xd(k) = xdk;
            // 'bspline_eval_vec:12' xdd(k) = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        u_loop_ub = BasisVal.size(0);
        for (int i27{0}; i27 < u_loop_ub; i27++) {
            BasisVal[i27 + BasisVal.size(0) * c_k] = r2[i27];
        }
        //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions
        //      @u=0,1
        // 'CalcBspline_Lee:24' [~, ~, BasisValDD0(k)] = bspline_eval(Bl, coef, 0);
        a__2 = 0.0;
        bspline_eval(Bl_handle, coef, &a__2, &a__3, &BasisValDD0[c_k]);
        // 'CalcBspline_Lee:25' [~, ~, BasisValDD1(k)] = bspline_eval(Bl, coef, 1);
        a__4 = 1.0;
        bspline_eval(Bl_handle, coef, &a__4, &a__5, &BasisValDD1[c_k]);
        //      BasisValDD0(k) = spval(sp2D, 0);
        //      BasisValDD1(k) = spval(sp2D, 1);
    }
    //
    // 'CalcBspline_Lee:30' A = [BasisValDD0; BasisVal; BasisValDD1];
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
        for (int i20{0}; i20 < input_sizes_idx_0; i20++) {
            A[(i20 + A.size(0) * i19) + 1] = BasisVal[i20 + input_sizes_idx_0 * i19];
        }
    }
    p_loop_ub = BasisValDD0.size(1);
    for (int i21{0}; i21 < p_loop_ub; i21++) {
        A[(input_sizes_idx_0 + A.size(0) * i21) + 1] = BasisValDD1[i21];
    }
    //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into
    //  generation') A = sparse(A); figure; spy(A)
    //
    // 'CalcBspline_Lee:37' bx = [0; points(1, :)'; 0];
    // 'CalcBspline_Lee:38' by = [0; points(2, :)'; 0];
    // 'CalcBspline_Lee:39' bz = [0; points(3, :)'; 0];
    //
    //  mmdflag = spparms('autommd'); % protect current spparms setting
    //  spparms('autommd',0);         % suppress pivoting
    //
    // tic
    // 'CalcBspline_Lee:46' cx = A\bx;
    //  solve sparse banded linear system
    // 'CalcBspline_Lee:47' cy = A\by;
    //  solve sparse banded linear system
    // 'CalcBspline_Lee:48' cz = A\bz;
    //  solve sparse banded linear system
    // toc
    //
    //  spparms('autommd',mmdflag);   % restore spparms setting
    //
    //  sp3D = spmak(knots, [cx'; cy'; cz']);
    //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
    // 'CalcBspline_Lee:55' sp3D.CoeffX = cx.';
    v_loop_ub = points.size(1);
    r3.set_size(points.size(1) + 2);
    r3[0] = 0.0;
    for (int i28{0}; i28 < v_loop_ub; i28++) {
        r3[i28 + 1] = points[3 * i28];
    }
    r3[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r3, r4);
    sp3D_CoeffX.set_size(1, r4.size(0));
    w_loop_ub = r4.size(0);
    for (int i29{0}; i29 < w_loop_ub; i29++) {
        sp3D_CoeffX[i29] = r4[i29];
    }
    // 'CalcBspline_Lee:56' sp3D.CoeffY = cy.';
    x_loop_ub = points.size(1);
    r3.set_size(points.size(1) + 2);
    r3[0] = 0.0;
    for (int i30{0}; i30 < x_loop_ub; i30++) {
        r3[i30 + 1] = points[3 * i30 + 1];
    }
    r3[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r3, r4);
    sp3D_CoeffY.set_size(1, r4.size(0));
    y_loop_ub = r4.size(0);
    for (int i31{0}; i31 < y_loop_ub; i31++) {
        sp3D_CoeffY[i31] = r4[i31];
    }
    // 'CalcBspline_Lee:57' sp3D.CoeffZ = cz.';
    ab_loop_ub = points.size(1);
    r3.set_size(points.size(1) + 2);
    r3[0] = 0.0;
    for (int i32{0}; i32 < ab_loop_ub; i32++) {
        r3[i32 + 1] = points[3 * i32 + 2];
    }
    r3[points.size(1) + 1] = 0.0;
    coder::mldivide(A, r3, r4);
    sp3D_CoeffZ.set_size(1, r4.size(0));
    bb_loop_ub = r4.size(0);
    for (int i33{0}; i33 < bb_loop_ub; i33++) {
        sp3D_CoeffZ[i33] = r4[i33];
    }
    int b_sp3D_Bl_ncoeff;
    // 'CalcBspline_Lee:58' sp3D.Bl = Bl;
    b_sp3D_Bl_ncoeff = (sp3D_Bl_breakpoints.size(1) + cfg_LeeSplineDegree) - 2;
    // 'CalcBspline_Lee:59' sp3D.knots = knots;
    *sp3D_Bl_ncoeff = b_sp3D_Bl_ncoeff;
    *sp3D_Bl_handle = Bl_handle;
    *sp3D_Bl_degree = cfg_LeeSplineDegree;
}

} // namespace ocn

//
// File trailer for CalcBspline_Lee.cpp
//
// [EOF]
//

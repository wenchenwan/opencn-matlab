//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_simplex.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

// Include Files
#include "c_simplex.h"
#include "find.h"
#include "sparse1.h"
#include "coder_array.h"
#include "cpp_simplex.hpp"

// Function Definitions
//
// function [C, success, status, msg] = c_simplex(f, A, b, Aeq, beq, ctx)
//
// Arguments    : const ::coder::array<double, 2U> &f
//                const coder::sparse *A
//                const ::coder::array<double, 1U> &b
//                const ::coder::array<double, 2U> &Aeq
//                const ::coder::array<double, 1U> &beq
//                ::coder::array<double, 2U> &C
//                bool *success
//                int *status
// Return Type  : void
//
namespace ocn {
void c_simplex(const ::coder::array<double, 2U> &f, const coder::sparse *A,
               const ::coder::array<double, 1U> &b, const ::coder::array<double, 2U> &Aeq,
               const ::coder::array<double, 1U> &beq, ::coder::array<double, 2U> &C, bool *success,
               int *status)
{
    coder::sparse Atot;
    ::coder::array<double, 1U> Avs;
    ::coder::array<int, 1U> Ais;
    ::coder::array<int, 1U> Ajs;
    ::coder::array<int, 1U> ii;
    ::coder::array<int, 1U> jj;
    int Asize[2];
    int Csize[2];
    int beqsize[2];
    int bsize[2];
    int fsize[2];
    int c_loop_ub;
    int d_loop_ub;
    int i4;
    int loop_ub;
    int n;
    // 'c_simplex:2' msg = "";
    // 'c_simplex:3' if coder.target('rtw') || coder.target('mex')
    // 'c_simplex:4' c_prof_in(mfilename);
    // 'c_simplex:5' c_prof_in('join_A');
    // 'c_simplex:6' Atot = [A; Aeq];
    A->b_vertcat(Aeq, &Atot);
    // 'c_simplex:7' c_prof_out('join_A');
    //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    // 'c_simplex:9' [NCoeff, NHorz] = size(f);
    // 'c_simplex:10' C = zeros(NCoeff, NHorz);
    C.set_size(f.size(0), f.size(1));
    loop_ub = f.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = f.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            C[i1 + C.size(0) * i] = 0.0;
        }
    }
    // 'c_simplex:11' coder.varsize('C', [Inf, Inf], [1,1]);
    // 'c_simplex:13' [Aisd, Ajsd, Avs] = find(Atot);
    coder::b_eml_find(&Atot, ii, jj, Avs);
    // 'c_simplex:14' Ais = int32(Aisd)-1;
    Ais.set_size(ii.size(0));
    c_loop_ub = ii.size(0);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        Ais[i2] = ii[i2] - 1;
    }
    // 'c_simplex:15' Ajs = int32(Ajsd)-1;
    Ajs.set_size(jj.size(0));
    d_loop_ub = jj.size(0);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        Ajs[i3] = jj[i3] - 1;
    }
    // 'c_simplex:17' coder.varsize('Avs', [Inf, 1], [1, 0]);
    // 'c_simplex:18' coder.varsize('Ais', [Inf, 1], [1, 0]);
    // 'c_simplex:19' coder.varsize('Ajs', [Inf, 1], [1, 0]);
    // 'c_simplex:21' fsize = int32(size(f));
    fsize[0] = f.size(0);
    fsize[1] = f.size(1);
    // 'c_simplex:22' Asize = int32(size(Atot));
    Asize[0] = Atot.m;
    Asize[1] = Atot.n;
    // 'c_simplex:23' An = int32(nnz(Avs));
    n = 0;
    i4 = Avs.size(0);
    for (int k{0}; k < i4; k++) {
        if (Avs[k] != 0.0) {
            n++;
        }
    }
    int b_status;
    // 'c_simplex:24' bsize = int32(size(b));
    bsize[0] = b.size(0);
    bsize[1] = 1;
    // 'c_simplex:25' beqsize = int32(size(beq));
    beqsize[0] = beq.size(0);
    beqsize[1] = 1;
    // 'c_simplex:26' Csize = int32(size(C));
    Csize[0] = f.size(0);
    Csize[1] = f.size(1);
    // 'c_simplex:27' success = int32(0);
    // 'c_simplex:28' status = int32(0);
    // 'c_simplex:29' coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp',
    // '$(START_DIR)/src/'); 'c_simplex:30' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.clp.lflags); 'c_simplex:31' coder.cinclude('cpp_simplex.hpp'); 'c_simplex:32' status
    // = coder.ceval('simplex_solve', coder.rref(f), fsize,... 'c_simplex:33' coder.rref(Avs),
    // coder.rref(Ais), coder.rref(Ajs), Asize, An,... 'c_simplex:34'         coder.rref(b), bsize,
    // coder.rref(beq),beqsize,... 'c_simplex:35'         coder.ref(C), Csize);
    b_status = simplex_solve(&f[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0], &(Ajs.data())[0],
                             &Asize[0], n, &(((::coder::array<double, 1U> *)&b)->data())[0],
                             &bsize[0], &(((::coder::array<double, 1U> *)&beq)->data())[0],
                             &beqsize[0], &C[0], &Csize[0]);
    //          C = solution.solution;
    // 'c_simplex:37' success = status == 0;
    //  Status :
    //        0 : Primal Dual Optimality
    //        1 : Primal Infeasible
    //        2 : Dual Infeasible
    //        3 : Max iteration reached
    //        4 : isAbandoned
    // 'c_simplex:44' c_prof_out(mfilename);
    *success = (b_status == 0);
    *status = b_status;
}

} // namespace ocn

//
// File trailer for c_simplex.cpp
//
// [EOF]
//

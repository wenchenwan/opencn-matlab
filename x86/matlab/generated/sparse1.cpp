//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sparse1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "sparse1.h"
#include "coder_array.h"
#include <cstddef>
#include <cstring>
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &rhs
//                const ::coder::array<double, 2U> &varargin_1
//                const ::coder::array<double, 2U> &varargin_2
// Return Type  : void
//
namespace ocn {
namespace coder {
void sparse::parenAssign(const ::coder::array<double, 2U> &rhs,
                         const ::coder::array<double, 2U> &varargin_1,
                         const ::coder::array<double, 2U> &varargin_2)
{
    ::coder::array<double, 1U> dt;
    ::coder::array<int, 1U> x_tmp;
    int rhsIter_idx;
    int sm;
    int sn;
    sm = varargin_1.size(1);
    sn = varargin_2.size(1);
    rhsIter_idx = 0;
    for (int cidx{0}; cidx < sn; cidx++) {
        double b_d;
        b_d = varargin_2[cidx];
        for (int ridx{0}; ridx < sm; ridx++) {
            double nt;
            double rhsv;
            double thisv;
            int i1;
            int i2;
            int loop_ub;
            int vidx;
            bool found;
            nt = varargin_1[ridx];
            x_tmp.set_size(rowidx.size(0));
            loop_ub = rowidx.size(0);
            for (int i{0}; i < loop_ub; i++) {
                x_tmp[i] = rowidx[i];
            }
            i1 = colidx[static_cast<int>(b_d) - 1];
            i2 = colidx[static_cast<int>(b_d)];
            if (i1 < i2) {
                if (static_cast<int>(nt) < rowidx[i1 - 1]) {
                    vidx = i1 - 1;
                    found = false;
                } else {
                    int high_i;
                    int low_i;
                    int low_ip1;
                    high_i = i2;
                    low_i = i1;
                    low_ip1 = colidx[static_cast<int>(b_d) - 1];
                    while (high_i > low_ip1 + 1) {
                        int mid_i;
                        mid_i = (low_i >> 1) + (high_i >> 1);
                        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                            mid_i++;
                        }
                        if (static_cast<int>(nt) >= rowidx[mid_i - 1]) {
                            low_i = mid_i;
                            low_ip1 = mid_i;
                        } else {
                            high_i = mid_i;
                        }
                    }
                    vidx = low_i;
                    found = (rowidx[low_i - 1] == static_cast<int>(nt));
                }
            } else if (i1 == i2) {
                vidx = colidx[static_cast<int>(b_d) - 1] - 1;
                found = false;
            } else {
                vidx = 0;
                found = false;
            }
            if (found) {
                thisv = d[vidx - 1];
            } else {
                thisv = 0.0;
            }
            rhsv = rhs[rhsIter_idx];
            rhsIter_idx++;
            if ((thisv != 0.0) || (rhsv != 0.0)) {
                int nz;
                nz = colidx[colidx.size(0) - 1] - 1;
                if ((thisv != 0.0) && (rhsv != 0.0)) {
                    d[vidx - 1] = rhsv;
                } else if (thisv == 0.0) {
                    int b_k;
                    int b_scalarLB;
                    int b_vectorUB;
                    int i6;
                    int i7;
                    int idx;
                    idx = vidx + 1;
                    if (colidx[colidx.size(0) - 1] - 1 == maxnz) {
                        int b_loop_ub;
                        int highOrderA;
                        int highOrderB;
                        int lowOrderB;
                        int numAlloc;
                        int overflow;
                        int partialResults_idx_0_tmp;
                        int partialResults_idx_1;
                        int tmp;
                        dt.set_size(d.size(0));
                        b_loop_ub = d.size(0);
                        for (int i5{0}; i5 < b_loop_ub; i5++) {
                            dt[i5] = d[i5];
                        }
                        int lowOrderA;
                        highOrderA = m >> 16;
                        lowOrderA = m & 65535;
                        highOrderB = n >> 16;
                        lowOrderB = n & 65535;
                        partialResults_idx_0_tmp = lowOrderA * lowOrderB;
                        tmp = lowOrderA * highOrderB;
                        partialResults_idx_1 = tmp << 16;
                        overflow = tmp >> 16;
                        if (overflow <= 0) {
                            tmp = highOrderA * lowOrderB;
                            overflow = tmp >> 16;
                            if (overflow <= 0) {
                                overflow = highOrderA * highOrderB;
                                if (overflow <= 0) {
                                    int a__4;
                                    if (partialResults_idx_0_tmp >
                                        MAX_int32_T - partialResults_idx_1) {
                                        a__4 = (partialResults_idx_0_tmp + partialResults_idx_1) -
                                               MAX_int32_T;
                                        overflow = 1;
                                    } else {
                                        a__4 = partialResults_idx_0_tmp + partialResults_idx_1;
                                    }
                                    if (a__4 > MAX_int32_T - (tmp << 16)) {
                                        overflow++;
                                    }
                                }
                            }
                        }
                        if (overflow == 0) {
                            int b_u1;
                            int u0;
                            int y;
                            u0 = colidx[colidx.size(0) - 1] + 9;
                            b_u1 = m * n;
                            if (u0 <= b_u1) {
                                y = u0;
                            } else {
                                y = b_u1;
                            }
                            if (1 >= y) {
                                numAlloc = 1;
                            } else {
                                numAlloc = y;
                            }
                        } else {
                            int u1;
                            u1 = colidx[colidx.size(0) - 1] + 9;
                            if (1 >= u1) {
                                numAlloc = 1;
                            } else {
                                numAlloc = u1;
                            }
                        }
                        rowidx.set_size(numAlloc);
                        for (int i8{0}; i8 < numAlloc; i8++) {
                            rowidx[i8] = 0;
                        }
                        d.set_size(numAlloc);
                        for (int i9{0}; i9 < numAlloc; i9++) {
                            d[i9] = 0.0;
                        }
                        maxnz = numAlloc;
                        for (int c_k{0}; c_k < vidx; c_k++) {
                            rowidx[c_k] = x_tmp[c_k];
                            d[c_k] = dt[c_k];
                        }
                        for (int d_k{idx}; d_k <= nz; d_k++) {
                            rowidx[d_k] = x_tmp[d_k - 1];
                            d[d_k] = dt[d_k - 1];
                        }
                        rowidx[vidx] = static_cast<int>(nt);
                        d[vidx] = rhsv;
                    } else {
                        int b_nelem;
                        b_nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                        if (b_nelem > 0) {
                            std::memmove((void *)&rowidx[vidx + 1], (void *)&rowidx[vidx],
                                         (unsigned int)((size_t)b_nelem * sizeof(int)));
                            std::memmove((void *)&d[vidx + 1], (void *)&d[vidx],
                                         (unsigned int)((size_t)b_nelem * sizeof(double)));
                        }
                        d[vidx] = rhsv;
                        rowidx[vidx] = static_cast<int>(nt);
                    }
                    i6 = static_cast<int>(b_d) + 1;
                    i7 = n + 1;
                    b_scalarLB =
                        ((((i7 - static_cast<int>(b_d)) / 4) << 2) + static_cast<int>(b_d)) + 1;
                    b_vectorUB = b_scalarLB - 4;
                    for (b_k = i6; b_k <= b_vectorUB; b_k += 4) {
                        __m128i r1;
                        r1 = _mm_loadu_si128((const __m128i *)&colidx[b_k - 1]);
                        _mm_storeu_si128((__m128i *)&colidx[b_k - 1],
                                         _mm_add_epi32(r1, _mm_set1_epi32(1)));
                    }
                    for (b_k = b_scalarLB; b_k <= i7; b_k++) {
                        colidx[b_k - 1] = colidx[b_k - 1] + 1;
                    }
                } else {
                    int i3;
                    int i4;
                    int k;
                    int nelem;
                    int scalarLB;
                    int vectorUB;
                    nelem = (colidx[colidx.size(0) - 1] - vidx) - 1;
                    if (nelem > 0) {
                        std::memmove((void *)&rowidx[vidx - 1], (void *)&rowidx[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(int)));
                        std::memmove((void *)&d[vidx - 1], (void *)&d[vidx],
                                     (unsigned int)((size_t)nelem * sizeof(double)));
                    }
                    i3 = static_cast<int>(b_d) + 1;
                    i4 = n + 1;
                    scalarLB =
                        ((((i4 - static_cast<int>(b_d)) / 4) << 2) + static_cast<int>(b_d)) + 1;
                    vectorUB = scalarLB - 4;
                    for (k = i3; k <= vectorUB; k += 4) {
                        __m128i r;
                        r = _mm_loadu_si128((const __m128i *)&colidx[k - 1]);
                        _mm_storeu_si128((__m128i *)&colidx[k - 1],
                                         _mm_sub_epi32(r, _mm_set1_epi32(1)));
                    }
                    for (k = scalarLB; k <= i4; k++) {
                        colidx[k - 1] = colidx[k - 1] - 1;
                    }
                }
            }
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for sparse1.cpp
//
// [EOF]
//

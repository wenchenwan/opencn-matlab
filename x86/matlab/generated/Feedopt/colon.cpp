//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: colon.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

// Include Files
#include "colon.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int b
//                ::coder::array<int, 2U> &y
// Return Type  : void
//
namespace ocn {
namespace coder {
void eml_integer_colon_dispatcher(int b, ::coder::array<int, 2U> &y)
{
    int n;
    if (b < 1) {
        n = 0;
    } else {
        n = b;
    }
    y.set_size(1, n);
    if (n > 0) {
        int yk;
        y[0] = 1;
        yk = 1;
        for (int k{2}; k <= n; k++) {
            yk++;
            y[k - 1] = yk;
        }
    }
}

} // namespace coder
} // namespace ocn

//
// File trailer for colon.cpp
//
// [EOF]
//

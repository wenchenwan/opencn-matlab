//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: c_roots_.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "c_roots_.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "functions.h"
#include <cstring>

// Function Declarations
namespace ocn {
static int div_s32_floor(int numerator, int denominator);

}

// Function Definitions
//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
namespace ocn {
static int div_s32_floor(int numerator, int denominator)
{
    int quotient;
    if (denominator == 0) {
        if (numerator >= 0) {
            quotient = MAX_int32_T;
        } else {
            quotient = MIN_int32_T;
        }
    } else {
        unsigned int absDenominator;
        unsigned int absNumerator;
        unsigned int tempAbsQuotient;
        bool quotientNeedsNegation;
        if (numerator < 0) {
            absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
        } else {
            absNumerator = static_cast<unsigned int>(numerator);
        }
        if (denominator < 0) {
            absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
        } else {
            absDenominator = static_cast<unsigned int>(denominator);
        }
        quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
        tempAbsQuotient = absNumerator / absDenominator;
        if (quotientNeedsNegation) {
            absNumerator %= absDenominator;
            if (absNumerator > 0U) {
                tempAbsQuotient++;
            }
            quotient = -static_cast<int>(tempAbsQuotient);
        } else {
            quotient = static_cast<int>(tempAbsQuotient);
        }
    }
    return quotient;
}

//
// Arguments    : const double coeffs[4]
//                creal_T Y[3]
// Return Type  : void
//
void b_c_roots_(const double coeffs[4], creal_T Y[3])
{
    double dv[4];
    Y[0].re = 0.0;
    Y[0].im = 0.0;
    Y[1].re = 0.0;
    Y[1].im = 0.0;
    Y[2].re = 0.0;
    Y[2].im = 0.0;
    dv[0] = coeffs[3];
    dv[1] = coeffs[2];
    dv[2] = coeffs[1];
    dv[3] = coeffs[0];
    c_roots(&dv[0], &Y[0], 4);
}

//
// Arguments    : const double coeffs[10]
//                creal_T Y[9]
// Return Type  : void
//
void c_c_roots_(const double coeffs[10], creal_T Y[9])
{
    double dv[10];
    std::memset(&Y[0], 0, 9U * sizeof(creal_T));
    for (int i{0}; i < 10; i++) {
        dv[i] = coeffs[9 - i];
    }
    c_roots(&dv[0], &Y[0], 10);
}

//
// Arguments    : const double coeffs_data[]
//                const int coeffs_size[2]
//                creal_T Y_data[]
//                int Y_size[1]
// Return Type  : void
//
void c_roots_(const double coeffs_data[], const int coeffs_size[2], creal_T Y_data[], int Y_size[1])
{
    double tmp_data[13];
    int b_loop_ub;
    int i;
    int i1;
    int i2;
    int loop_ub;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    Y_size[0] = coeffs_size[1] - 1;
    loop_ub = coeffs_size[1] - 1;
    if (0 <= loop_ub - 1) {
        std::memset(&Y_data[0], 0, loop_ub * sizeof(creal_T));
    }
    if (1 > coeffs_size[1]) {
        i = 0;
        i1 = 1;
        i2 = -1;
    } else {
        i = coeffs_size[1] - 1;
        i1 = -1;
        i2 = 0;
    }
    b_loop_ub = div_s32_floor(i2 - i, i1);
    for (int i3{0}; i3 <= b_loop_ub; i3++) {
        tmp_data[i3] = coeffs_data[i + i1 * i3];
    }
    c_roots(&tmp_data[0], &Y_data[0], coeffs_size[1]);
}

} // namespace ocn

//
// File trailer for c_roots_.cpp
//
// [EOF]
//

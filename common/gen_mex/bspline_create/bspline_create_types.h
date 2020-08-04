//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  bspline_create_types.h
//
//  Code generation for function 'bspline_create_types'
//


#pragma once

// Include files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
namespace ocn
{
  struct struct0_T
  {
    int32_T ncoeff;
    coder::array<real_T, 2U> breakpoints;
    uint64_T handle;
    int32_T degree;
  };
}

#ifdef _MSC_VER

#pragma warning(pop)

#endif

// End of code generation (bspline_create_types.h)

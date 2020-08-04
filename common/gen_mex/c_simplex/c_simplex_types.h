//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  c_simplex_types.h
//
//  Code generation for function 'c_simplex_types'
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
  struct coder_internal_sparse
  {
    coder::array<real_T, 1U> d;
    coder::array<int32_T, 1U> colidx;
    coder::array<int32_T, 1U> rowidx;
    int32_T m;
    int32_T n;
    int32_T maxnz;
  };
}

#ifdef _MSC_VER

#pragma warning(pop)

#endif

// End of code generation (c_simplex_types.h)

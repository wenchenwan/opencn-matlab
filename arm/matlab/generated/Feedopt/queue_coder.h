//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

#ifndef QUEUE_CODER_H
#define QUEUE_CODER_H

// Include Files
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
class queue_coder {
  public:
    void init(const CurvStruct *b_value_type);
    void push(const CurvStruct *value) const;
    void get(unsigned int b_index, CurvStruct *value) const;
    bool isempty() const;
    unsigned int size() const;
    void set(unsigned int b_index, const CurvStruct *value) const;
    void get(int b_index, CurvStruct *value) const;
    void get(CurvStruct *value) const;
    void rget(CurvStruct *value) const;
    queue_coder();
    ~queue_coder();
    uint64m_T ptr;
    CurvStruct value_type;
};

} // namespace ocn

#endif
//
// File trailer for queue_coder.h
//
// [EOF]
//

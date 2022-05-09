//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 06-May-2022 16:42:15
//

// Include Files
#include "queue_coder.h"
#include "opencn_matlab_types1.h"

// Function Definitions
//
// function this = queue_coder(value_type)
//
// Arguments    : const CurvStruct *b_value_type
// Return Type  : void
//
namespace ocn {
void queue_coder::init(const CurvStruct *b_value_type)
{
    // 'queue_coder:9' coder.inline("never");
    // 'queue_coder:10' this.value_type = value_type;
    value_type = *b_value_type;
    // 'queue_coder:11' this.ptr = queue_new();
    // 'queue_new:2' if coder.target( 'MATLAB' )
    // 'queue_new:4' else
    // 'queue_new:5' ptr = uint64(0);
    // 'queue_new:6' ptr = coder.ceval( 'c_queue_new' );
    ptr = c_queue_new();
    // 'queue_coder:3' uint64
    // 'queue_coder:3' ptr
}

//
// function push(this, value)
//
// Arguments    : const CurvStruct *value
// Return Type  : void
//
void queue_coder::push(const CurvStruct *value) const
{
    // 'queue_coder:15' coder.inline("never");
    // 'queue_coder:16' queue_push(this.ptr, value);
    // 'queue_push:2' if coder.target('matlab')
    // 'queue_push:4' else
    // 'queue_push:5' coder.ceval('c_queue_push', uint64(ptr), value);
    c_queue_push(ptr, *value);
}

//
// Arguments    : void
// Return Type  : queue_coder
//
queue_coder::queue_coder()
{
}

//
// Arguments    : void
// Return Type  : void
//
queue_coder::~queue_coder()
{
}

} // namespace ocn

//
// File trailer for queue_coder.cpp
//
// [EOF]
//

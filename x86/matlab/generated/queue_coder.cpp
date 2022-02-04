//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "queue_coder.h"
#include "sinspace_types1.h"
#include <cmath>

// Function Definitions
//
// Arguments    : unsigned long b_index
//                CurvStruct *value
// Return Type  : void
//
namespace ocn {
void queue_coder::get(unsigned long b_index, CurvStruct *value) const
{
    *value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : long b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(long b_index, CurvStruct *value) const
{
    *value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : unsigned int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(unsigned int b_index, CurvStruct *value) const
{
    *value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(ptr, b_index, value);
}

//
// Arguments    : double b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(double b_index, CurvStruct *value) const
{
    *value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(ptr, static_cast<unsigned int>(std::round(b_index)), value);
}

//
// Arguments    : int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(int b_index, CurvStruct *value) const
{
    *value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : const CurvStruct *b_value_type
// Return Type  : void
//
void queue_coder::init(const CurvStruct *b_value_type)
{
    value_type = *b_value_type;
    ptr = c_queue_new();
}

//
// Arguments    : void
// Return Type  : bool
//
bool queue_coder::isempty() const
{
    return size() == 0U;
}

//
// Arguments    : const CurvStruct *value
// Return Type  : void
//
void queue_coder::push(const CurvStruct *value) const
{
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

//
// Arguments    : CurvStruct *value
// Return Type  : void
//
void queue_coder::rget(CurvStruct *value) const
{
    size();
    get(size(), value);
}

//
// Arguments    : unsigned int b_index
//                const CurvStruct *value
// Return Type  : void
//
void queue_coder::set(unsigned int b_index, const CurvStruct *value) const
{
    c_queue_set(ptr, b_index, *value);
}

//
// Arguments    : void
// Return Type  : unsigned int
//
unsigned int queue_coder::size() const
{
    return c_queue_size(ptr);
}

} // namespace ocn

//
// File trailer for queue_coder.cpp
//
// [EOF]
//

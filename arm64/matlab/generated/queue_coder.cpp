//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "queue_coder.h"
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
    *value = this->value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : long b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(long b_index, CurvStruct *value) const
{
    *value = this->value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : unsigned int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(unsigned int b_index, CurvStruct *value) const
{
    *value = this->value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(this->ptr, b_index, value);
}

//
// Arguments    : double b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(double b_index, CurvStruct *value) const
{
    *value = this->value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(this->ptr, static_cast<unsigned int>(std::round(b_index)), value);
}

//
// Arguments    : int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(int b_index, CurvStruct *value) const
{
    *value = this->value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
}

//
// Arguments    : const CurvStruct *b_value_type
// Return Type  : void
//
void queue_coder::init(const CurvStruct *b_value_type)
{
    this->value_type = *b_value_type;
    this->ptr = c_queue_new();
}

//
// Arguments    : void
// Return Type  : bool
//
bool queue_coder::isempty() const
{
    return this->size() == 0U;
}

//
// Arguments    : const CurvStruct *value
// Return Type  : void
//
void queue_coder::push(const CurvStruct *value) const
{
    c_queue_push(this->ptr, *value);
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
    this->size();
    this->get(this->size(), value);
}

//
// Arguments    : unsigned int b_index
//                const CurvStruct *value
// Return Type  : void
//
void queue_coder::set(unsigned int b_index, const CurvStruct *value) const
{
    c_queue_set(this->ptr, b_index, *value);
}

//
// Arguments    : void
// Return Type  : unsigned int
//
unsigned int queue_coder::size() const
{
    return c_queue_size(this->ptr);
}

} // namespace ocn

//
// File trailer for queue_coder.cpp
//
// [EOF]
//

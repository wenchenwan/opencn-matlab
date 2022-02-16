//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:29:45
//

// Include Files
#include "queue_coder.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include <cmath>

// Function Declarations
namespace ocn {
static unsigned int MultiWord2uLong(const unsigned int u[]);

}

// Function Definitions
//
// Arguments    : const unsigned int u[]
// Return Type  : unsigned int
//
namespace ocn {
static unsigned int MultiWord2uLong(const unsigned int u[])
{
    return u[0];
}

//
// function value = get(this, index)
//
// Arguments    : const int64m_T b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(const int64m_T b_index, CurvStruct *value) const
{
    // 'queue_coder:20' coder.inline("never");
    // 'queue_coder:21' value = queue_get(this.ptr, this.value_type, index);
    *value = value_type;
    // 'queue_get:2' if coder.target('matlab')
    // 'queue_get:4' else
    // 'queue_get:5' value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    // 'queue_get:6' coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
    c_queue_get(ptr, MultiWord2uLong((unsigned int *)&b_index.chunks[0U]), value);
}

//
// function value = get(this, index)
//
// Arguments    : const uint64m_T b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(const uint64m_T b_index, CurvStruct *value) const
{
    // 'queue_coder:20' coder.inline("never");
    // 'queue_coder:21' value = queue_get(this.ptr, this.value_type, index);
    *value = value_type;
    // 'queue_get:2' if coder.target('matlab')
    // 'queue_get:4' else
    // 'queue_get:5' value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    // 'queue_get:6' coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
    c_queue_get(ptr, MultiWord2uLong((unsigned int *)&b_index.chunks[0U]), value);
}

//
// function value = get(this, index)
//
// Arguments    : double b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(double b_index, CurvStruct *value) const
{
    // 'queue_coder:20' coder.inline("never");
    // 'queue_coder:21' value = queue_get(this.ptr, this.value_type, index);
    *value = value_type;
    // 'queue_get:2' if coder.target('matlab')
    // 'queue_get:4' else
    // 'queue_get:5' value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    // 'queue_get:6' coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
    c_queue_get(ptr, static_cast<unsigned int>(std::round(b_index)), value);
}

//
// function value = get(this, index)
//
// Arguments    : unsigned int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(unsigned int b_index, CurvStruct *value) const
{
    // 'queue_coder:20' coder.inline("never");
    // 'queue_coder:21' value = queue_get(this.ptr, this.value_type, index);
    *value = value_type;
    // 'queue_get:2' if coder.target('matlab')
    // 'queue_get:4' else
    // 'queue_get:5' value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    // 'queue_get:6' coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
    c_queue_get(ptr, b_index, value);
}

//
// function value = get(this, index)
//
// Arguments    : int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(int b_index, CurvStruct *value) const
{
    // 'queue_coder:20' coder.inline("never");
    // 'queue_coder:21' value = queue_get(this.ptr, this.value_type, index);
    *value = value_type;
    // 'queue_get:2' if coder.target('matlab')
    // 'queue_get:4' else
    // 'queue_get:5' value = value_type;
    // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
    // 'queue_get:6' coder.ceval('c_queue_get', uint64(ptr), uint32(index), coder.ref(value));
    c_queue_get(ptr, static_cast<unsigned int>(b_index), value);
}

//
// function this = queue_coder(value_type)
//
// Arguments    : const CurvStruct *b_value_type
// Return Type  : void
//
void queue_coder::init(const CurvStruct *b_value_type)
{
    // 'queue_coder:9' coder.inline("never");
    // 'queue_coder:10' this.value_type = value_type;
    value_type = *b_value_type;
    // 'queue_coder:11' this.ptr = queue_new();
    // 'queue_new:2' if coder.target('matlab')
    // 'queue_new:4' else
    // 'queue_new:5' ptr = uint64(0);
    // 'queue_new:6' ptr = coder.ceval('c_queue_new');
    ptr = c_queue_new();
    // 'queue_coder:3' uint64
    // 'queue_coder:3' ptr
}

//
// function value = isempty(this)
//
// Arguments    : void
// Return Type  : bool
//
bool queue_coder::isempty() const
{
    // 'queue_coder:40' coder.inline("never");
    // 'queue_coder:41' value = (this.size() == 0);
    return size() == 0U;
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

//
// function value = rget(this, index)
//
// Arguments    : CurvStruct *value
// Return Type  : void
//
void queue_coder::rget(CurvStruct *value) const
{
    // 'queue_coder:30' coder.inline("never");
    // 'queue_coder:31' value = this.get(this.size - index + 1);
    size();
    get(size(), value);
}

//
// function set(this, index, value)
//
// Arguments    : unsigned int b_index
//                const CurvStruct *value
// Return Type  : void
//
void queue_coder::set(unsigned int b_index, const CurvStruct *value) const
{
    // 'queue_coder:25' coder.inline("never");
    // 'queue_coder:26' queue_set(this.ptr, index, value);
    // 'queue_set:2' if coder.target('matlab')
    // 'queue_set:4' else
    // 'queue_set:5' coder.ceval('c_queue_set', uint64(ptr), uint32(index), value);
    c_queue_set(ptr, b_index, *value);
}

//
// function value = size(this)
//
// Arguments    : void
// Return Type  : unsigned int
//
unsigned int queue_coder::size() const
{
    // 'queue_coder:35' coder.inline("never");
    // 'queue_coder:36' value = queue_size(this.ptr);
    // 'queue_size:2' if coder.target('matlab')
    // 'queue_size:4' else
    // 'queue_size:5' value = uint32(0);
    // 'queue_size:6' value = coder.ceval('c_queue_size', uint64(ptr));
    return c_queue_size(ptr);
}

} // namespace ocn

//
// File trailer for queue_coder.cpp
//
// [EOF]
//

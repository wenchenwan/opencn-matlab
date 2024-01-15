
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: queue_coder.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "queue_coder.h"
#include "opencn_matlab_types111.h"

// Function Definitions
//
// function [ value ] = get( this, index )
//
// get : Get the element at a given index from the queue
//
// Arguments    : CurvStruct *value
// Return Type  : void
//
namespace ocn {
void queue_coder::get(CurvStruct *value) const
{
    // 'queue_coder:24' coder.inline("never");
    // 'queue_coder:25' value = queue_get( this.ptr, this.value_type, index );
    *value = value_type;
    //  queue_get : Get an element of the queue at a given index
    //
    //  Inputs    :
    //  ptr           : Handle to a queue instance
    //  value_type    : Value type of an instance in the queue
    //  index         : Index on the queue
    //
    //  Outputs    :
    //  value         : Element in the queue
    //
    // 'queue_get:12' if coder.target( 'MATLAB' )
    // 'queue_get:14' else
    // 'queue_get:15' value = value_type;
    // 'queue_get:16' coder.ceval( 'c_queue_get', uint64( ptr ), uint32( index ), ...
    // 'queue_get:17'         coder.ref( value ) );
    c_queue_get(ptr, 1U, value);
}

//
// function [ value ] = get( this, index )
//
// get : Get the element at a given index from the queue
//
// Arguments    : int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(int b_index, CurvStruct *value) const
{
    // 'queue_coder:24' coder.inline("never");
    // 'queue_coder:25' value = queue_get( this.ptr, this.value_type, index );
    *value = value_type;
    //  queue_get : Get an element of the queue at a given index
    //
    //  Inputs    :
    //  ptr           : Handle to a queue instance
    //  value_type    : Value type of an instance in the queue
    //  index         : Index on the queue
    //
    //  Outputs    :
    //  value         : Element in the queue
    //
    // 'queue_get:12' if coder.target( 'MATLAB' )
    // 'queue_get:14' else
    // 'queue_get:15' value = value_type;
    // 'queue_get:16' coder.ceval( 'c_queue_get', uint64( ptr ), uint32( index ), ...
    // 'queue_get:17'         coder.ref( value ) );
    c_queue_get(ptr, static_cast<unsigned int>(b_index), value);
}

//
// function [ value ] = get( this, index )
//
// get : Get the element at a given index from the queue
//
// Arguments    : unsigned int b_index
//                CurvStruct *value
// Return Type  : void
//
void queue_coder::get(unsigned int b_index, CurvStruct *value) const
{
    // 'queue_coder:24' coder.inline("never");
    // 'queue_coder:25' value = queue_get( this.ptr, this.value_type, index );
    *value = value_type;
    //  queue_get : Get an element of the queue at a given index
    //
    //  Inputs    :
    //  ptr           : Handle to a queue instance
    //  value_type    : Value type of an instance in the queue
    //  index         : Index on the queue
    //
    //  Outputs    :
    //  value         : Element in the queue
    //
    // 'queue_get:12' if coder.target( 'MATLAB' )
    // 'queue_get:14' else
    // 'queue_get:15' value = value_type;
    // 'queue_get:16' coder.ceval( 'c_queue_get', uint64( ptr ), uint32( index ), ...
    // 'queue_get:17'         coder.ref( value ) );
    c_queue_get(ptr, b_index, value);
}

//
// function [ this ] = queue_coder( value_type )
//
// queue_coder : Class constructor
//
// Arguments    : const CurvStruct *b_value_type
// Return Type  : void
//
void queue_coder::init(const CurvStruct *b_value_type)
{
    // 'queue_coder:11' coder.inline( "never" );
    // 'queue_coder:12' this.value_type = value_type;
    value_type = *b_value_type;
    // 'queue_coder:13' this.ptr        = queue_new();
    //  queue_new : Create a new queue
    //
    //  Outputs :
    //  ptr   : Handle to a queue instance
    //
    // 'queue_new:7' if coder.target( 'MATLAB' )
    // 'queue_new:9' else
    // 'queue_new:10' ptr = uint64( 0 );
    // 'queue_new:11' ptr = coder.ceval( 'c_queue_new' );
    ptr = c_queue_new();
    // 'queue_coder:4' uint64
    // 'queue_coder:4' ptr
}

//
// function [ value ] = isempty( this )
//
// isempty : Return emptiness of the queue
//
// Arguments    : void
// Return Type  : bool
//
bool queue_coder::isempty() const
{
    // 'queue_coder:48' coder.inline("never");
    // 'queue_coder:49' value = (this.size() == 0);
    return size() == 0U;
}

//
// function push( this, value )
//
// push : Push the new element in the queue
//
// Arguments    : const CurvStruct *value
// Return Type  : void
//
void queue_coder::push(const CurvStruct *value) const
{
    // 'queue_coder:18' coder.inline( "never" );
    // 'queue_coder:19' queue_push( this.ptr, value );
    //  queue_push : Push an element at the end of the queue
    //
    //  Inputs    :
    //  ptr   : Handle to a queue instance
    //  elem  : Element to add to the queue
    //
    // 'queue_push:8' if coder.target( "MATLAB" )
    // 'queue_push:10' else
    // 'queue_push:11' coder.ceval( 'c_queue_push', uint64(ptr), elem );
    c_queue_push(ptr, *value);
}

//
// Arguments    : void
// Return Type  : queue_coder
//
queue_coder::queue_coder() = default;

//
// Arguments    : void
// Return Type  : void
//
queue_coder::~queue_coder() = default;

//
// function delete( this )
//
// delete : Delete the elements of the queue
//
// Arguments    : void
// Return Type  : void
//
void queue_coder::queue_coder_delete() const
{
    // 'queue_coder:60' coder.inline("never");
    // 'queue_coder:61' queue_delete( this.ptr );
    //  queue_delete : Delete the queue and it elements
    //
    //  Inputs :
    //  ptr   : Pointer to a queue instance
    //
    // 'queue_delete:7' if coder.target( 'MATLAB' )
    // 'queue_delete:9' else
    // 'queue_delete:10' coder.ceval( 'c_queue_delete', uint64( ptr ) );
    c_queue_delete(ptr);
}

//
// function [ value ] = rget(this, index)
//
// rget : Reverse get the element from the queue
//
// Arguments    : CurvStruct *value
// Return Type  : void
//
void queue_coder::rget(CurvStruct *value) const
{
    // 'queue_coder:36' coder.inline("never");
    // 'queue_coder:37' value = this.get( this.size - index + 1 );
    size();
    get(size(), value);
}

//
// function set(this, index, value)
//
// set : Set the element at a given index in the queue
//
// Arguments    : int b_index
//                const CurvStruct *value
// Return Type  : void
//
void queue_coder::set(int b_index, const CurvStruct *value) const
{
    // 'queue_coder:30' coder.inline("never");
    // 'queue_coder:31' queue_set( this.ptr, index, value );
    //  queue_set : Set an element at a given indey in the queue
    //
    //  Inputs    :
    //  ptr       : Handle to a queue instance
    //  index     : The index in the queue to store the element
    //  elem      : An element to store in the queue
    //
    // 'queue_set:9' if coder.target( 'MATLAB' )
    // 'queue_set:11' else
    // 'queue_set:12' coder.ceval( 'c_queue_set', uint64(ptr), uint32(index), elem );
    c_queue_set(ptr, static_cast<unsigned int>(b_index), *value);
}

//
// function set(this, index, value)
//
// set : Set the element at a given index in the queue
//
// Arguments    : unsigned int b_index
//                const CurvStruct *value
// Return Type  : void
//
void queue_coder::set(unsigned int b_index, const CurvStruct *value) const
{
    // 'queue_coder:30' coder.inline("never");
    // 'queue_coder:31' queue_set( this.ptr, index, value );
    //  queue_set : Set an element at a given indey in the queue
    //
    //  Inputs    :
    //  ptr       : Handle to a queue instance
    //  index     : The index in the queue to store the element
    //  elem      : An element to store in the queue
    //
    // 'queue_set:9' if coder.target( 'MATLAB' )
    // 'queue_set:11' else
    // 'queue_set:12' coder.ceval( 'c_queue_set', uint64(ptr), uint32(index), elem );
    c_queue_set(ptr, b_index, *value);
}

//
// function [ value ] = size( this )
//
// size : Get the queue size
//
// Arguments    : void
// Return Type  : unsigned int
//
unsigned int queue_coder::size() const
{
    // 'queue_coder:42' coder.inline("never");
    // 'queue_coder:43' value = queue_size( this.ptr );
    //  queue_size : Get the queue size
    //
    //  Inputs    :
    //  ptr       : Handle to a queue instance
    //
    //  Outputs   :
    //  value     : The size of the queue
    //
    // 'queue_size:10' if coder.target( "MATLAB" )
    // 'queue_size:12' else
    // 'queue_size:13' value = uint32( 0 );
    // 'queue_size:14' value = coder.ceval( 'c_queue_size', uint64( ptr ) );
    return c_queue_size(ptr);
}

} // namespace ocn

//
// File trailer for queue_coder.cpp
//
// [EOF]
//

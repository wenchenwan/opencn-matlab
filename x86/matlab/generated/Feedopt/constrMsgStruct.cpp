
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrMsgStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constrMsgStruct.h"
#include "string1.h"
#include "coder_bounded_array.h"
#include <algorithm>

// Function Definitions
//
// function [ CStruct ] = constrMsgStruct( msg )
//
// Construct a struct containing char msg.
//
//  Inputs :
//  msg     : Char array to store the msg
//
//  Outputs :
//  CStruct       : The resulting structure
//
// Arguments    : const coder::rtString *msg
//                char CStruct_msg[2048]
//                double *CStruct_size
// Return Type  : void
//
namespace ocn {
void constrMsgStruct(const coder::rtString *msg, char CStruct_msg[2048], double *CStruct_size)
{
    int l;
    int loop_ub;
    // 'constrMsgStruct:10' msgChar     = char( msg );
    // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
    // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
    // 'constrMsgStruct:13' l           = length( msgChar );
    l = msg->Value.size[1];
    // 'constrMsgStruct:15' if( l > dim( 2 ) )
    if (msg->Value.size[1] > 2048) {
        // 'constrMsgStruct:15' l = dim( 2 );
        l = 2048;
    }
    // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
    // 'constrMsgStruct:18'                     'size', l ...
    // 'constrMsgStruct:19'                     );
    for (int i{0}; i < 2048; i++) {
        CStruct_msg[i] = '0';
    }
    *CStruct_size = l;
    // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
    if (l < 1) {
        loop_ub = 0;
    } else {
        loop_ub = l;
    }
    if (loop_ub - 1 >= 0) {
        std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &CStruct_msg[0]);
    }
    // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
    CStruct_msg[l - 1] = '0';
    // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
}

} // namespace ocn

//
// File trailer for constrMsgStruct.cpp
//
// [EOF]
//

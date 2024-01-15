
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ocn_print1.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "ocn_print1.h"
#include "constrMsgStruct.h"
#include "opencn_matlab_types.h"
#include "string1.h"
#include "coder_bounded_array.h"
#include "ocn_print.hpp"
#include <algorithm>

// Function Definitions
//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
// Return Type  : void
//
namespace ocn {
void b_ocn_print(bool condition)
{
    static const char b_cv[38]{'[', 'r', 'e', 's', 'a', 'm', 'p', 'l', 'e', 'C', 'u', 'r', 'v',
                               ']', 'Q', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ', 'n', 'o', 't',
                               ' ', 'b', 'e', ' ', 'n', 'e', 'g', 'a', 't', 'i', 'v', 'e'};
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' msgChar     = char( msg );
        // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
        // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:13' l           = length( msgChar );
        // 'constrMsgStruct:15' if( l > dim( 2 ) )
        // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:18'                     'size', l ...
        // 'constrMsgStruct:19'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_msg.msg[i] = '0';
        }
        ocn_msg.size = 38.0;
        // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
        for (int i1{0}; i1 < 38; i1++) {
            ocn_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
        ocn_msg.msg[37] = '0';
        // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
// Return Type  : void
//
void c_ocn_print(bool condition)
{
    static const char b_cv[66]{'[', 'r', 'e', 's', 'a', 'm', 'p', 'l', 'e', 'C', 'u', 'r', 'v', ']',
                               'U', ' ', 'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', ' ', 's', 'h',
                               'o', 'u', 'l', 'd', ' ', 'n', 'o', 't', ' ', 'b', 'e', ' ', 'n', 'e',
                               'g', 'a', 't', 'i', 'v', 'e', ' ', 'd', 'u', 'r', 'i', 'n', 'g', ' ',
                               'r', 'e', 's', 'a', 'm', 'p', 'l', 'i', 'n', 'g'};
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' msgChar     = char( msg );
        // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
        // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:13' l           = length( msgChar );
        // 'constrMsgStruct:15' if( l > dim( 2 ) )
        // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:18'                     'size', l ...
        // 'constrMsgStruct:19'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_msg.msg[i] = '0';
        }
        ocn_msg.size = 66.0;
        // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
        std::copy(&b_cv[0], &b_cv[66], &ocn_msg.msg[0]);
        // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
        ocn_msg.msg[65] = '0';
        // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
// Return Type  : void
//
void d_ocn_print(bool condition)
{
    static const char b_cv[78]{'[', 'r', 'e', 's', 'a', 'm', 'p', 'l', 'e', 'C', 'u', 'r', 'v',
                               ']', 'U', ' ', 'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r', ' ',
                               'i', 's', ' ', 't', 'o', 'o', ' ', 'c', 'l', 'o', 's', 'e', ' ',
                               'f', 'r', 'o', 'm', ' ', 't', 'h', 'e', ' ', 'p', 'r', 'e', 'v',
                               'i', 'o', 'u', 's', ' ', 'o', 'n', 'e', ' ', 'd', 'u', 'r', 'i',
                               'n', 'g', ' ', 'r', 'e', 's', 'a', 'm', 'p', 'l', 'i', 'n', 'g'};
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' msgChar     = char( msg );
        // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
        // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:13' l           = length( msgChar );
        // 'constrMsgStruct:15' if( l > dim( 2 ) )
        // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:18'                     'size', l ...
        // 'constrMsgStruct:19'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_msg.msg[i] = '0';
        }
        ocn_msg.size = 78.0;
        // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
        std::copy(&b_cv[0], &b_cv[78], &ocn_msg.msg[0]);
        // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
        ocn_msg.msg[77] = '0';
        // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
// Return Type  : void
//
void e_ocn_print(bool condition)
{
    static const char b_cv[35]{'[', 'r', 'e', 's', 'a', 'm', 'p', 'l', 'e', 'C', 'u', 'r',
                               'v', ']', 'T', 'r', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ',
                               'b', 'e', ' ', 'p', 'o', 's', 'i', 't', 'i', 'v', 'e'};
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' msgChar     = char( msg );
        // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
        // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:13' l           = length( msgChar );
        // 'constrMsgStruct:15' if( l > dim( 2 ) )
        // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:18'                     'size', l ...
        // 'constrMsgStruct:19'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_msg.msg[i] = '0';
        }
        ocn_msg.size = 35.0;
        // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
        for (int i1{0}; i1 < 35; i1++) {
            ocn_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
        ocn_msg.msg[34] = '0';
        // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void f_ocn_print(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[18]{'[', 'C', 'h', 'e', 'c', 'k', 'C', 'u', 'r',
                                    'v', 'S', 't', 'r', 'u', 'c', 't', 's', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        int loop_ub;
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        msg_long.Value.size[0] = 1;
        msg_long.Value.size[1] = msg->Value.size[1] + 18;
        for (int i{0}; i < 18; i++) {
            msg_long.Value.data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[18]);
        }
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void g_ocn_print(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[21]{'[', 'c', 'o', 'm', 'p', 'r', 'e', 's', 's', 'C', 'u',
                                    'r', 'v', 'S', 't', 'r', 'u', 'c', 't', 's', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        int loop_ub;
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        msg_long.Value.size[0] = 1;
        msg_long.Value.size[1] = msg->Value.size[1] + 21;
        for (int i{0}; i < 21; i++) {
            msg_long.Value.data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[21]);
        }
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void h_ocn_print(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[19]{'[', 's', 'm', 'o', 'o', 't', 'h', 'C', 'u', 'r',
                                    'v', 'S', 't', 'r', 'u', 'c', 't', 's', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        int loop_ub;
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        msg_long.Value.size[0] = 1;
        msg_long.Value.size[1] = msg->Value.size[1] + 19;
        for (int i{0}; i < 19; i++) {
            msg_long.Value.data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[19]);
        }
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void i_ocn_print(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[12]{'[', 's', 'p', 'l', 'i', 't', 'Q', 'u', 'e', 'u', 'e', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        int loop_ub;
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        msg_long.Value.size[0] = 1;
        msg_long.Value.size[1] = msg->Value.size[1] + 12;
        for (int i{0}; i < 12; i++) {
            msg_long.Value.data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[12]);
        }
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
// Return Type  : void
//
void j_ocn_print(bool condition)
{
    static const char b_cv[32]{'[', 'f', 'e', 'e', 'd', 'r', 'a', 't', 'e', 'P', 'l',
                               'a', 'n', 'n', 'i', 'n', 'g', ']', 'Q', 'u', 'e', 'u',
                               'e', ' ', 'e', 'm', 'p', 't', 'y', '.', '.', '.'};
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' msgChar     = char( msg );
        // 'constrMsgStruct:11' dim         = StructTypeName.dimMsg{ 1 };
        // 'constrMsgStruct:12' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:13' l           = length( msgChar );
        // 'constrMsgStruct:15' if( l > dim( 2 ) )
        // 'constrMsgStruct:17' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:18'                     'size', l ...
        // 'constrMsgStruct:19'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_msg.msg[i] = '0';
        }
        ocn_msg.size = 32.0;
        // 'constrMsgStruct:21' CStruct.msg( 1 : l )    = msgChar( 1 : l );
        for (int i1{0}; i1 < 32; i1++) {
            ocn_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:22' CStruct.msg( l )        = '0';
        ocn_msg.msg[31] = '0';
        // 'constrMsgStruct:23' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void k_ocn_print(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[18]{'[', 'f', 'e', 'e', 'd', 'r', 'a', 't', 'e',
                                    'P', 'l', 'a', 'n', 'n', 'i', 'n', 'g', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    if (condition) {
        int loop_ub;
        // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
        msg_long.Value.size[0] = 1;
        msg_long.Value.size[1] = msg->Value.size[1] + 18;
        for (int i{0}; i < 18; i++) {
            msg_long.Value.data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[18]);
        }
        // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_print:25' else
        // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
        constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
        // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
        ocn_print_msg(&ocn_msg);
    }
}

//
// function ocn_print( condition, msg, fileName )
//
// ocn_print : Custom implementation of the print function. se C++ code for
//  the real time implementation.
//
//  Inputs :
//    condition : Enable print
//    msg : Message to print
//    filename : Filename calling the function
//
//
// Arguments    : const coder::rtString *msg
// Return Type  : void
//
void ocn_print(const coder::rtString *msg)
{
    static const char obj1Value[14]{'[', 'b', 's', 'p', 'l', 'i', 'n',
                                    'e', '_', 'e', 'v', 'a', 'l', ']'};
    coder::rtString msg_long;
    MsgStruct ocn_msg;
    int loop_ub;
    // 'ocn_print:11' coder.inline( "never" )
    // 'ocn_print:13' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_print:14' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_print:15' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_print:16' coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    // 'ocn_print:17' coder.cinclude( 'ocn_print.hpp' );
    // 'ocn_print:20' if( condition )
    // 'ocn_print:21' msg_long = "[" + fileName + "]" + msg;
    msg_long.Value.size[0] = 1;
    msg_long.Value.size[1] = msg->Value.size[1] + 14;
    for (int i{0}; i < 14; i++) {
        msg_long.Value.data[i] = obj1Value[i];
    }
    loop_ub = msg->Value.size[1];
    if (loop_ub - 1 >= 0) {
        std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_long.Value.data[14]);
    }
    // 'ocn_print:23' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
    // 'ocn_print:25' else
    // 'ocn_print:26' ocn_msg = constrMsgStruct( msg_long );
    constrMsgStruct(&msg_long, ocn_msg.msg, &ocn_msg.size);
    // 'ocn_print:27' coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
    ocn_print_msg(&ocn_msg);
}

} // namespace ocn

//
// File trailer for ocn_print1.cpp
//
// [EOF]
//

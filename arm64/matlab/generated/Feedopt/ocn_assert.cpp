
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ocn_assert.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "ocn_assert.h"
#include "opencn_matlab_types.h"
#include "string1.h"
#include "coder_bounded_array.h"
#include "ocn_error.hpp"
#include <algorithm>

// Function Definitions
//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
namespace ocn {
void ab_ocn_assert(bool condition)
{
    static const char b_cv[35]{"[cutZeroEnd]Continuity C2 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 35.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 35; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void b_ocn_assert(bool condition)
{
    static const char b_cv[33]{"[EvalCurvStructNoCtx]u_vec < 0\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 33.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 33; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void bb_ocn_assert(bool condition)
{
    static const char b_cv[43]{"[splitCurvStruct]Curve Length not valide\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 43.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 43; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void c_ocn_assert(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[11]{'[', 'R', 'e', 'a', 'd', 'G', 'C', 'o', 'd', 'e', ']'};
    MsgStruct ocn_error_msg;
    char msg_data[2157];
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        int l;
        int loop_ub;
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        for (int i{0}; i < 11; i++) {
            msg_data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_data[11]);
        }
        msg_data[msg->Value.size[1] + 11] = '\\';
        msg_data[msg->Value.size[1] + 12] = 'n';
        msg_data[msg->Value.size[1] + 13] = '\x00';
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        l = msg->Value.size[1] + 14;
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        if (msg->Value.size[1] + 14 > 2048) {
            // 'constrMsgStruct:14' l = dim( 2 );
            l = 2048;
        }
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i1{0}; i1 < 2048; i1++) {
            ocn_error_msg.msg[i1] = '0';
        }
        ocn_error_msg.size = l;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&msg_data[0], &msg_data[l], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void cb_ocn_assert(bool condition)
{
    static const char b_cv[46]{"[FeedoptPlan]Opt - Check geometry failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 46.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 46; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void d_ocn_assert(bool condition)
{
    static const char b_cv[58]{"[FeedoptPlan]FeedoptPlan: error code was not handled...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 58.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 58; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void db_ocn_assert(bool condition)
{
    static const char b_cv[46]{"[FeedoptPlan]Opt - Check zspdmode failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 46.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 46; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void e_ocn_assert(bool condition)
{
    static const char b_cv[36]{"[FeedoptPlan]Gcode queue is empty\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 36.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 36; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void eb_ocn_assert(bool condition)
{
    static const char b_cv[53]{"[FeedoptPlan]Opt - Check parametrisation failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 53.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 53; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
//                const coder::rtString *msg
// Return Type  : void
//
void f_ocn_assert(bool condition, const coder::rtString *msg)
{
    static const char obj1Value[13]{'[', 'F', 'e', 'e', 'd', 'o', 'p',
                                    't', 'P', 'l', 'a', 'n', ']'};
    MsgStruct ocn_error_msg;
    char msg_data[2157];
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        int l;
        int loop_ub;
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        for (int i{0}; i < 13; i++) {
            msg_data[i] = obj1Value[i];
        }
        loop_ub = msg->Value.size[1];
        if (loop_ub - 1 >= 0) {
            std::copy(&msg->Value.data[0], &msg->Value.data[loop_ub], &msg_data[13]);
        }
        msg_data[msg->Value.size[1] + 13] = '\\';
        msg_data[msg->Value.size[1] + 14] = 'n';
        msg_data[msg->Value.size[1] + 15] = '\x00';
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        l = msg->Value.size[1] + 16;
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        if (msg->Value.size[1] + 16 > 2048) {
            // 'constrMsgStruct:14' l = dim( 2 );
            l = 2048;
        }
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i1{0}; i1 < 2048; i1++) {
            ocn_error_msg.msg[i1] = '0';
        }
        ocn_error_msg.size = l;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&msg_data[0], &msg_data[l], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void fb_ocn_assert(bool condition)
{
    static const char b_cv[36]{"[buildConstr]b should be positive\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 36.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 36; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void g_ocn_assert(bool condition)
{
    static const char b_cv[43]{"[splineLength]u2 must be greater than u1\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 43.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 43; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void gb_ocn_assert(bool condition)
{
    static const char b_cv[82]{
        "[feedratePlanningForceZeroStop]Should not be called one the first set of curves\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 82.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&b_cv[0], &b_cv[82], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void h_ocn_assert(bool condition)
{
    static const char b_cv[71]{
        "[splineLength]u1 must be greater or equal than the first spline knot\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 71.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&b_cv[0], &b_cv[71], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void hb_ocn_assert(bool condition)
{
    static const char b_cv[61]{"[feedratePlanningForceZeroStop]Curve should be a Zero Stop\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 61.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 61; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void i_ocn_assert(bool condition)
{
    static const char b_cv[70]{
        "[splineLength]u2 must be smaller or equal than the last spline knot\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 70.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&b_cv[0], &b_cv[70], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : void
// Return Type  : void
//
void ib_ocn_assert()
{
    static const char b_cv[54]{"[EvalCurvStructNoCtx]Unknown Curve Type for Eval...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
    // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
    // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
    // 'ocn_assert:17' else
    // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
    //  Construct a struct containing char msg.
    //
    //  Inputs :
    //  msg     : Char array to store the msg
    //
    //  Outputs :
    //  CStruct       : The resulting structure
    // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
    // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
    // 'constrMsgStruct:12' l           = length( msg );
    // 'constrMsgStruct:14' if( l > dim( 2 ) )
    // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
    // 'constrMsgStruct:17'                     'size', l ...
    // 'constrMsgStruct:18'                     );
    for (int i{0}; i < 2048; i++) {
        ocn_error_msg.msg[i] = '0';
    }
    ocn_error_msg.size = 54.0;
    // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
    for (int i1{0}; i1 < 54; i1++) {
        ocn_error_msg.msg[i1] = b_cv[i1];
    }
    // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
    ocn_error_msg.msg[2047] = '0';
    // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
    // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
    ocn_throw_error(&ocn_error_msg);
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void j_ocn_assert(bool condition)
{
    static const char b_cv[58]{"[bspline_eval_lee]u_vec should be greater or equal to 0\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 58.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 58; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : void
// Return Type  : void
//
void jb_ocn_assert()
{
    static const char b_cv[44]{"[LengthCurv]BAD CURVE TYPE IN LENGTH CURV\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
    // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
    // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
    // 'ocn_assert:17' else
    // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
    //  Construct a struct containing char msg.
    //
    //  Inputs :
    //  msg     : Char array to store the msg
    //
    //  Outputs :
    //  CStruct       : The resulting structure
    // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
    // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
    // 'constrMsgStruct:12' l           = length( msg );
    // 'constrMsgStruct:14' if( l > dim( 2 ) )
    // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
    // 'constrMsgStruct:17'                     'size', l ...
    // 'constrMsgStruct:18'                     );
    for (int i{0}; i < 2048; i++) {
        ocn_error_msg.msg[i] = '0';
    }
    ocn_error_msg.size = 44.0;
    // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
    for (int i1{0}; i1 < 44; i1++) {
        ocn_error_msg.msg[i1] = b_cv[i1];
    }
    // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
    ocn_error_msg.msg[2047] = '0';
    // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
    // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
    ocn_throw_error(&ocn_error_msg);
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void k_ocn_assert(bool condition)
{
    static const char b_cv[58]{"[bspline_eval_lee]u_vec should be greater or equal to 1\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 58.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 58; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void l_ocn_assert(bool condition)
{
    static const char b_cv[76]{
        "[splineLengthFindU]u0 must be greater or equal than the first spline knot\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 76.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&b_cv[0], &b_cv[76], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void m_ocn_assert(bool condition)
{
    static const char b_cv[76]{
        "[splineLengthFindU]u0 must be smaller or equal than the first spline knot\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 76.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        std::copy(&b_cv[0], &b_cv[76], &ocn_error_msg.msg[0]);
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void n_ocn_assert(bool condition)
{
    static const char b_cv[45]{"[splineLengthFindU]Fails to compute length\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 45.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 45; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void o_ocn_assert(bool condition)
{
    static const char b_cv[42]{"[calcTransition]Curve Length not valide\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 42.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 42; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void ocn_assert(bool condition)
{
    static const char b_cv[33]{"[EvalCurvStructNoCtx]u_vec > 1\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 33.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 33; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void p_ocn_assert(bool condition)
{
    static const char b_cv[48]{"[FeedoptPlan]Split - Check geometry failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 48.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 48; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void q_ocn_assert(bool condition)
{
    static const char b_cv[48]{"[FeedoptPlan]Split - Check zspdmode failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 48.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 48; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void r_ocn_assert(bool condition)
{
    static const char b_cv[55]{"[FeedoptPlan]Split - Check parametrisation failed...\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 55.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 55; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void s_ocn_assert(bool condition)
{
    static const char b_cv[40]{"[cutZeroStart]Curve Length not valide\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 40.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 40; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void t_ocn_assert(bool condition)
{
    static const char b_cv[37]{"[cutZeroStart]Continuity C0 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 37.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 37; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void u_ocn_assert(bool condition)
{
    static const char b_cv[37]{"[cutZeroStart]Continuity C1 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 37.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 37; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void v_ocn_assert(bool condition)
{
    static const char b_cv[37]{"[cutZeroStart]Continuity C2 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 37.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 37; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void w_ocn_assert(bool condition)
{
    static const char b_cv[38]{"[cutZeroEnd]Curve Length not valide\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 38.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 38; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void x_ocn_assert(bool condition)
{
    static const char b_cv[35]{"[cutZeroEnd]Continuity C0 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 35.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 35; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

//
// function ocn_assert( condition, msg, fileName )
//
// Arguments    : bool condition
// Return Type  : void
//
void y_ocn_assert(bool condition)
{
    static const char b_cv[35]{"[cutZeroEnd]Continuity C1 failed\\n"};
    MsgStruct ocn_error_msg;
    // 'ocn_assert:2' coder.inline( "never" )
    // 'ocn_assert:4' if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    // 'ocn_assert:5' my_path = StructTypeName.WDIR + "/src";
    // 'ocn_assert:6' coder.updateBuildInfo( 'addIncludePaths', my_path );
    // 'ocn_assert:7' coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    // 'ocn_assert:8' coder.cinclude( 'ocn_error.hpp' );
    // 'ocn_assert:11' if( ~condition )
    if (!condition) {
        // 'ocn_assert:12' err_msg         = "[" + fileName + "]" + msg + "\n";
        // 'ocn_assert:13' err_msg_char    = [ char(err_msg) 0 ];
        // 'ocn_assert:15' if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        // 'ocn_assert:17' else
        // 'ocn_assert:18' ocn_error_msg = constrMsgStruct( err_msg_char );
        //  Construct a struct containing char msg.
        //
        //  Inputs :
        //  msg     : Char array to store the msg
        //
        //  Outputs :
        //  CStruct       : The resulting structure
        // 'constrMsgStruct:10' dim         = StructTypeName.dimMsg{1};
        // 'constrMsgStruct:11' msgDefault  = repmat( '0', dim );
        // 'constrMsgStruct:12' l           = length( msg );
        // 'constrMsgStruct:14' if( l > dim( 2 ) )
        // 'constrMsgStruct:16' CStruct = struct(   'msg',  msgDefault, ...
        // 'constrMsgStruct:17'                     'size', l ...
        // 'constrMsgStruct:18'                     );
        for (int i{0}; i < 2048; i++) {
            ocn_error_msg.msg[i] = '0';
        }
        ocn_error_msg.size = 35.0;
        // 'constrMsgStruct:19' CStruct.msg( 1 : l )    = msg( 1 : l );
        for (int i1{0}; i1 < 35; i1++) {
            ocn_error_msg.msg[i1] = b_cv[i1];
        }
        // 'constrMsgStruct:20' CStruct.msg( end )      = '0';
        ocn_error_msg.msg[2047] = '0';
        // 'constrMsgStruct:21' coder.cstructname( CStruct, StructTypeName.Msg );
        // 'ocn_assert:19' coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
        ocn_throw_error(&ocn_error_msg);
    }
}

} // namespace ocn

//
// File trailer for ocn_assert.cpp
//
// [EOF]
//

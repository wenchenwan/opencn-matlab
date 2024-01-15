#pragma once
#include <matlab_headers.h>

/**
 * @brief OpenCN builtin runtime error arising during the execution of the matlab generated code.
 * 
 * @param err_msg 
 */
void ocn_throw_error( ocn::MsgStruct* msg_struct );

namespace ocn {

    /**
     * @brief Class used to throw well formated error
     * 
     */
    class Error : public std::exception
    {

        public :
        Error( ocn::MsgStruct* msg_str) : msg_struct( *msg_str ) {}

        char* what() { 
            return msg_struct.msg; 
            }
    
        ocn::MsgStruct& errorMsg() { return msg_struct; };
        
        private :
        ocn::MsgStruct msg_struct;
    };

}

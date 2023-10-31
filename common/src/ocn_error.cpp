#include <stdexcept>
#include "ocn_error.hpp"

/**
 * @brief OpenCN builtin runtime error arising during the execution of the matlab generated code.
 * 
 * @param msg_struct 
 */
void ocn_throw_error( ocn::MsgStruct* msg_struct ) {
    throw ocn::Error( msg_struct );
}
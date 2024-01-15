#include <iostream>

#include "ocn_print.hpp"
#include "ocn_error.hpp"

/**
 * @brief OpenCN builtin print msg.
 * 
 * @param ocn_msg 
 */
void ocn_print_msg( ocn::MsgStruct* ocn_msg ) {
    std::cout.write( ocn_msg->msg, ocn_msg->size) << std::endl;
}
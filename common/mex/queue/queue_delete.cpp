#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        if (inputs.size() != 1) {
            return;
        }
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::ArrayFactory factory;

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);
        if( not( q->elems.empty() ) ){
            q->elems.clear();
            q->elems.~vector();
        }
        //std::vector<matlab::data::Array>().swap( q->elems );
        //delete q;
    }
};

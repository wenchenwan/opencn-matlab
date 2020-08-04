#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    // Called with ptr (uint64_t)
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        if (inputs.size() != 1) {
            return;
        }
        
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::ArrayFactory factory;

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);

//         if (index - 1 >= q->elems.size()) {
//             std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
//             matlab::data::ArrayFactory factory;
//             matlabPtr->feval(u"error", 0,
//                              std::vector<matlab::data::Array>(
//                                  {factory.createScalar("queue_get: index(%d) out of range (%d)"), //
//                                   factory.createScalar(index),									  //
//                                   factory.createScalar(q->elems.size())}));
//         }
        
        outputs[0] = factory.createArray<matlab::data::Array>({1, q->elems.size()});
        
        int index = 0;
        for (const auto elem: q->elems) {
            outputs[0][index] = elem;
            index++;
        }
    }
};

#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    // Called with ptr (uint64_t), index (uint64_t)
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        if (inputs.size() != 2) {
            return;
        }

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);

        uint64_t index = inputs[1][0];

        if (index - 1 >= q->elems.size()) {
            std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
            matlab::data::ArrayFactory factory;
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>(
                                 {factory.createScalar("queue_get: index(%d) out of range (%d)"), //
                                  factory.createScalar(index),									  //
                                  factory.createScalar(q->elems.size())}));
        }
        // auto it = q->elems.begin();
        // std::advance(it, index - 1);

        // auto elem = *it;
        //        q->elems.erase(it);

        outputs[0] = q->elems[index - 1];
    }
};

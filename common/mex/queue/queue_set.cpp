#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        if (inputs.size() != 3) {
            return;
        }

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);

        // convert matlab 1-base index to 0-base index
        uint64_t index = static_cast<uint64_t>(inputs[1][0]) - 1;

        if (index >= q->elems.size()) {
            std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
            matlab::data::ArrayFactory factory;
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>(
                                 {factory.createScalar("queue_set: index(%d) out of range (%d)"), //
                                  factory.createScalar(index),									  //
                                  factory.createScalar(q->elems.size())}));
        }
        auto it = q->elems.begin();

        std::advance(it, index);

        *it = inputs[2];
    }
};

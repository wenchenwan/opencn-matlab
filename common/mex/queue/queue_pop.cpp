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

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);

        if (q->elems.empty()) {
            std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
            matlab::data::ArrayFactory factory;
            matlabPtr->feval(
                u"error", 0,
                std::vector<matlab::data::Array>({factory.createScalar("queue_pop: empty")}));
        }

        if (outputs.size() > 0) {
            outputs[0] = std::move(q->elems.front());
        }

//         q->elems.pop_front();
        q->elems.erase(begin(q->elems));
    }
};

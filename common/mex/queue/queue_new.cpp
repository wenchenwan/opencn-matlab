#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::ArrayFactory factory;

        Queue *q = new Queue;

        outputs[0] = factory.createScalar(reinterpret_cast<uint64_t>(q));

        //        matlabPtr->feval(u"fprintf", 0,
        //                         std::vector<matlab::data::Array>(
        //                             {factory.createScalar("queue_new, elem size = %d\n"), //
        //                              factory.createScalar(a)}));
    }
};

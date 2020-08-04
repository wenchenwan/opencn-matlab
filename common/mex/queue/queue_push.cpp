#include "queue.h"

using matlab::mex::ArgumentList;
using namespace matlab::data;

class MexFunction : public matlab::mex::Function
{
public:
    void operator()(ArgumentList outputs, ArgumentList inputs)
    {
        if (inputs.size() != 2) {
            return;
        }

        uint64_t qptr = inputs[0][0];
        Queue *q = reinterpret_cast<Queue *>(qptr);
        q->elems.push_back(inputs[1]);
    }
};

#pragma once

#include <vector>
#include <mex.hpp>
#include <mexAdapter.hpp>

struct Queue {
    std::vector<matlab::data::Array> elems;
};

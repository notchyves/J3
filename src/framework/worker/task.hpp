#pragma once
#include "common.hpp"

class task {
public:
    std::function<void(task&)> work{ nullptr };
    std::string name{ "Starting background task..." };
    volatile float progress{ 0 };
};

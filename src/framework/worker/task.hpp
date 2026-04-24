#pragma once
#include "common.hpp"

class task {
public:
    std::string name{ "Unknown" };
    std::function<void(task)> work{ nullptr };
    std::atomic<float> progress{ 0 };
};

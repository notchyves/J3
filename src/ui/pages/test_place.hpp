#pragma once
#include "common.hpp"

struct test_place {
    std::string_view id();
    std::string_view layout();
    std::string_view styles();
};

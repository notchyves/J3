#pragma once
#include "common.hpp"

struct hierarchy_layer {
    entt::entity parent = entt::null;
    uint32_t index = 0;
    bool dirty = false;

    // no vector of children because it gets expensive
};

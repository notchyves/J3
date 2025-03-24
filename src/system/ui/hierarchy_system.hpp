#pragma once
#include "common.hpp"

#include "component/ui/hierarchy_layer.hpp"

struct hierarchy_system {
    void initialize();
    void update(entt::registry& registry);
    void destroy();
};

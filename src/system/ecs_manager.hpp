#pragma once
#include "common.hpp"
#include "entity_system.hpp"

class ecs_manager {
public:
    void initialize();
    void update();

    template <typename system_t, typename... args>
    void add_system(args&&... a) {
        systems.push_back(entity_system{system_t(std::forward<args>(a)...)});
    }

private:
    std::vector<entity_system> systems;
    entt::registry registry;
};

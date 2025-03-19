#pragma once
#include "common.hpp"

struct c_entity_system : entt::type_list<void(), void(entt::registry&), void()> {
    template <typename base>
    struct type : base {
        void initialize() { entt::poly_call<0>(*this); }
        void update(entt::registry& registry) { entt::poly_call<1>(*this, registry); }
        void destroy() { entt::poly_call<2>(*this); }
    };

    template <typename obj>
    using impl = entt::value_list<&obj::initialize, &obj::update, &obj::destroy>;
};

using entity_system = entt::poly<c_entity_system>;

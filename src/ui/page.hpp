#pragma once
#include "common.hpp"

struct c_page : entt::type_list<std::string_view(), std::string_view(), std::string_view()> {
    template <typename base>
    struct type : base {
        std::string_view id() { return entt::poly_call<0>(*this); }
        std::string_view layout() { return entt::poly_call<1>(*this); }
        std::string_view styles() { return entt::poly_call<2>(*this); }
    };

    template <typename obj>
    using impl = entt::value_list<&obj::id, &obj::layout, &obj::styles>;
};

using page = entt::poly<c_page>;

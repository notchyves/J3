#pragma once
#include "common.hpp"
#include "service.hpp"

class service_collection {
public:
    template <std::derived_from<service>... services_t>
    void add();

    template <std::derived_from<service> service_t>
    std::shared_ptr<service_t> get();

private:
    using service_hash = std::uint32_t;
    std::unordered_map<service_hash, std::shared_ptr<service>> service_map;

    template <std::derived_from<service> service_t>
    void add_service();
};

template <std::derived_from<service>... services_t>
void service_collection::add() {
    (this->add_service<services_t>(), ...);
}

template <std::derived_from<service> service_t>
std::shared_ptr<service_t> service_collection::get() {
    static constexpr service_hash hash = entt::type_hash<service_t>::value();
    return this->service_map.contains(hash) ? this->service_map[hash] : nullptr;
}

template <std::derived_from<service> service_t>
void service_collection::add_service() {
    static constexpr service_hash hash = entt::type_hash<service_t>::value();
    this->service_map[hash] = std::make_unique<service_t>();
}

#pragma once
#include "common.hpp"
#include "service.hpp"

class service_collection {
    template <std::derived_from<service> service_t>
    struct storage {
        static inline std::shared_ptr<service_t> service = nullptr;
    };

public:
    template <std::derived_from<service>... services_t>
    void add();

    template <std::derived_from<service> service_t>
    std::shared_ptr<service_t> get();

private:
    template <std::derived_from<service> service_t>
    void add_service();
};

template <std::derived_from<service>... services_t>
void service_collection::add() {
    (this->add_service<services_t>(), ...);
}

template <std::derived_from<service> service_t>
std::shared_ptr<service_t> service_collection::get() {
    return storage<service_t>::service;
}

template <std::derived_from<service> service_t>
void service_collection::add_service() {
    storage<service_t>::service = std::make_shared<service_t>();
}

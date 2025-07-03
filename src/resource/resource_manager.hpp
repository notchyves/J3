#pragma once
#include "common.hpp"
#include "resource_pool.hpp"

// probably my favorite class
class resource_manager {
    template <typename T>
    struct storage {
        static inline std::unique_ptr<resource_pool<T>> pool;
    };

public:
    template <typename T, typename... args>
    std::shared_ptr<T> add(const std::string& name, args&&... a);

    template <typename T>
    std::shared_ptr<T> get(const std::string& name);

private:
    template <typename T>
    std::unique_ptr<resource_pool<T>>& get_pool();
};

template <typename T, typename... args>
std::shared_ptr<T> resource_manager::add(const std::string& name, args&&... a) {
    auto& pool = get_pool<T>();
    return pool->add(name, std::forward<args>(a)...);
}

template <typename T>
std::shared_ptr<T> resource_manager::get(const std::string& name) {
    auto& pool = get_pool<T>();
    return pool->get(name);
}

template <typename T>
std::unique_ptr<resource_pool<T>>& resource_manager::get_pool() {
    if (storage<T>::pool == nullptr) storage<T>::pool = std::make_unique<resource_pool<T>>();

    return storage<T>::pool;
}

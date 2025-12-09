#pragma once
#include "common.hpp"

// template should have a constructor, else it will not work
template <typename T>
class resource_pool {
public:
    template <typename... args>
    std::shared_ptr<T> add(const std::string& name, args&&... a) {
        if (auto ptr_if_exists = get(name)) {
            return ptr_if_exists;
        }

        auto ptr = std::make_shared<T>(std::forward<args>(a)...);
        pool.emplace(name, ptr);
        return ptr;
    }

    std::shared_ptr<T> get(const std::string& name) {
        if (auto it = pool.find(name); it != pool.end()) {
            return it->second;
        }

        spdlog::warn("Resource not found in pool: {}", name);
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<T>> pool;
};

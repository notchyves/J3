#pragma once
#include "common.hpp"
#include "framework/resource/resource.hpp"

struct texture {
    std::filesystem::path path{ };
    // or
    resource res{ resource::empty() };
    
    vector2 size = { 0, 0 };

    // renderer ensures that this is loaded
    winrt::com_ptr<ID3D11ShaderResourceView> texture_view = nullptr;

    texture(const std::filesystem::path& path) : path(path) { }
    texture(const resource& resource) : res(resource) { }
};

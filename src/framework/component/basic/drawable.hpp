#pragma once
#include "common.hpp"

#include "framework/system/render/material/texture.hpp"
#include "framework/system/render/mesh/mesh.hpp"
#include "framework/system/render/shader/shader.hpp"

struct drawable {
    std::shared_ptr<mesh> mesh{ nullptr };
    std::shared_ptr<texture> tex{ nullptr };
    D3D11_PRIMITIVE_TOPOLOGY topology{ D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST };
    
    std::shared_ptr<vertex_shader> vs{ nullptr };
    std::shared_ptr<pixel_shader> ps{ nullptr };
    cb_vertex vs_cbuffer{ };
    cb_pixel ps_cbuffer{ };
};

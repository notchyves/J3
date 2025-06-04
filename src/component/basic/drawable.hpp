#pragma once
#include "common.hpp"

#include "system/render/material/texture.hpp"
#include "system/render/mesh/mesh.hpp"
#include "system/render/shader/shader.hpp"

struct drawable {
    std::shared_ptr<mesh> mesh;
    std::shared_ptr<texture> tex;
    D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    
    std::shared_ptr<vertex_shader> vs;
    std::shared_ptr<pixel_shader> ps;
    cb_vertex vs_cbuffer;
    cb_pixel ps_cbuffer;
};

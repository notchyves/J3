#pragma once
#include "common.hpp"

#include "buffer/d3d_buffer.hpp"
#include "material/texture.hpp"
#include "mesh/mesh.hpp"

struct renderer {
    static renderer& get_for_window(HWND handle);

    renderer(HWND handle, vector2 size, bool hardware_accelerated = true);
    void initialize();
    void update(entt::registry& registry);
    void destroy();

    void set_background_color(vector4 col);
    void resize(vector2 new_size);

    winrt::com_ptr<ID3D11Device>& get_device();
    winrt::com_ptr<ID3D11RenderTargetView>& get_rtv();

private:
    static std::unordered_map<HWND, renderer*> renderer_map;
    
    HWND window_handle{ nullptr };
    vector2 window_size { 0, 0 };
    bool hardware_accelerated{ true }; // by default
    std::array<float, 4> background_color{ };
    DXGI_FORMAT back_buffer_format{ DXGI_FORMAT_R8G8B8A8_UNORM };
    UINT swap_chain_flags{ DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH };
    
    winrt::com_ptr<ID3D11Device> device{ nullptr };
    winrt::com_ptr<ID3D11DeviceContext> device_context{ nullptr };
    winrt::com_ptr<IDXGISwapChain> swap_chain{ nullptr };

    winrt::com_ptr<ID3D11Texture2D> render_target{ nullptr };
    winrt::com_ptr<ID3D11RenderTargetView> render_target_view{ nullptr };

    // for MSAA
    UINT msaa_count{ 4 };
    UINT msaa_quality{ 0 };
    winrt::com_ptr<ID3D11Texture2D> multisampled_render_target{ nullptr };
    winrt::com_ptr<ID3D11RenderTargetView> multisampled_render_target_view{ nullptr };
    winrt::com_ptr<ID3D11DepthStencilView> multisampled_depth_stencil_view{ nullptr };

    winrt::com_ptr<ID3D11InputLayout> input_layout{ nullptr };

    d3d_buffer vertex_buffer{ };
    d3d_buffer index_buffer{ };
    
    winrt::com_ptr<ID3D11RasterizerState> rasterizer_state{ nullptr };
    winrt::com_ptr<ID3D11SamplerState> sampler_state{ nullptr };
    winrt::com_ptr<ID3D11BlendState> blend_state{ nullptr };
    
    void render_frame(entt::registry& registry);
    
    void create_device_and_swap_chain();
    void create_render_targets();
    void set_viewport() const;
    void create_rasterizer();
    void create_sampler();
    void create_blend_state();
    void create_default_resources();

    void ensure_texture_loaded(const std::shared_ptr<texture>& tex) const;
    void ensure_mesh_buffers_created(const std::shared_ptr<mesh>& m) const;
};

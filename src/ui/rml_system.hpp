#pragma once
#include "common.hpp"
#include <RmlUi_Renderer_DX11.h>
#include <RmlUi_Platform_Win32.h>

struct rml_system {
    rml_system(HWND handle, vector2 size, const winrt::com_ptr<ID3D11Device>& device, const winrt::com_ptr<ID3D11RenderTargetView>& rtv);
    void initialize();
    void render();
    void destroy();

private:
    HWND window_handle = nullptr;
    Rml::Vector2i window_size = Rml::Vector2i();
    
    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11RenderTargetView> render_target_view;
    
    RenderInterface_DX11 render_interface;
    SystemInterface_Win32 system_interface;

    std::unique_ptr<Rml::Context> context;
};

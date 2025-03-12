#pragma once
#include "common.hpp"

class adapter_data {
public:
    winrt::com_ptr<IDXGIAdapter> adapter;
    DXGI_ADAPTER_DESC description;

    explicit adapter_data(const winrt::com_ptr<IDXGIAdapter>& adapter) : adapter(adapter) {
        this->adapter->GetDesc(&description);
    }
};

class renderer {
public:
    void initialize(HWND handle, vector2 size, bool hardware_accelerated = true);
    void render_frame();

private:
    HWND window_handle = nullptr;
    vector2 window_size = { 0, 0 };
    
    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11DeviceContext> device_context;
    winrt::com_ptr<IDXGISwapChain> swap_chain;
    winrt::com_ptr<ID3D11RenderTargetView> render_target_view;
    
    void create_device_and_swap_chain(bool hardware_accelerated);
    void create_render_target();
};

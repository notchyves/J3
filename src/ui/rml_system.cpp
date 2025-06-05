#include "rml_system.hpp"

rml_system::rml_system(HWND handle, vector2 size, const winrt::com_ptr<ID3D11Device>& device,
    const winrt::com_ptr<ID3D11RenderTargetView>& rtv) {
    this->window_handle = handle;
    this->window_size = Rml::Vector2i(
        static_cast<int>(size.x),
        static_cast<int>(size.y)
    );
    this->device = device;
    this->render_target_view = rtv;
}

void rml_system::initialize() {
    this->render_interface.Init(this->device.get());
    this->system_interface.SetWindow(this->window_handle);

    Rml::SetRenderInterface(&this->render_interface);
    Rml::SetSystemInterface(&this->system_interface);

    Rml::Initialise();
    context = std::unique_ptr<Rml::Context>(Rml::CreateContext("main", this->window_size));

    // load fonts here
}

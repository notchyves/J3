#include "rml_system.hpp"

#include <RmlUi/Debugger/Debugger.h>

#include "framework/resource/resource.hpp"

void rml_system::initialize(
    HWND handle, vector2 size, const winrt::com_ptr<ID3D11Device>& device,
    const winrt::com_ptr<ID3D11RenderTargetView>& rtv
) {
    this->window_handle = handle;
    this->window_size = Rml::Vector2i(static_cast<int>(size.x), static_cast<int>(size.y));
    this->device = device;
    this->render_target_view = rtv;

    this->render_interface = Rml::MakeUnique<dxtk_render_interface>(device);
    Rml::SetRenderInterface(this->render_interface.get());

    this->system_interface = Rml::MakeUnique<SystemInterface_Win32>();
    this->system_interface->SetWindow(this->window_handle);
    Rml::SetSystemInterface(this->system_interface.get());

    this->font_engine = Rml::MakeUnique<FontEngineInterfaceHarfBuzz>();
    Rml::SetFontEngineInterface(this->font_engine.get());

    // add languages (BCP47 code for language, ISO15924 code for script... then text direction obviously)
    this->font_engine->RegisterLanguage("en", "Latn", TextFlowDirection::LeftToRight);

    this->ime = Rml::MakeUnique<TextInputMethodEditor_Win32>();
    Rml::SetTextInputHandler(this->ime.get());

    Rml::Initialise();
    this->context = Rml::CreateContext("main", this->window_size);

#ifndef NDEBUG // debug
    Rml::Debugger::Initialise(this->context);
#endif

    Rml::LoadFontFace("resources/fonts/Montserrat.ttf");
    Rml::LoadFontFace("resources/fonts/MontserratItalic.ttf");

    this->default_styles = Rml::Factory::InstanceStyleSheetFile("resources/ui/css/default.css");
}

void rml_system::update() {
    this->context->Update();
    this->render_interface->SetViewport(this->window_size.x, this->window_size.y);
    this->render_interface->BeginFrame(this->render_target_view.get());
    this->context->Render();
    this->render_interface->EndFrame();
}

void rml_system::request_update(const double timeout) { this->context->RequestNextUpdate(timeout); }

void rml_system::destroy() {
    Rml::Shutdown();
    this->ime.reset();
}

void rml_system::resize(const vector2 new_size, const winrt::com_ptr<ID3D11RenderTargetView>& rtv) {
    this->window_size = { static_cast<int>(new_size.x), static_cast<int>(new_size.y) };
    this->context->SetDimensions(this->window_size);
    this->render_target_view = rtv;
}

bool rml_system::window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param) {
    if (this->ime == nullptr) return false; // prevent access of null pointer after destruction

#ifndef NDEBUG // debug
    if (message == WM_KEYUP && w_param == VK_F12) {
        Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
    }
#endif
    
    return !RmlWin32::WindowProcedure(this->context, *this->ime, window_handle, message, w_param, l_param);
}
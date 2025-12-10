#pragma once
#include "common.hpp"

#include "framework/resource/resource.hpp"
#include "interface/render/dxtk_render_interface.hpp"

#include <RmlUi/Core/Input.h>
#include <RmlUi_Platform_Win32.h>
#include <FontEngineInterfaceHarfBuzz.h>

struct rml_system {
    void initialize(
        HWND handle, vector2 size, const winrt::com_ptr<ID3D11Device>& device,
        const winrt::com_ptr<ID3D11RenderTargetView>& rtv
    );

    void update();
    void request_update(double timeout = 0.0);
    void destroy();

    void resize(vector2 new_size, const winrt::com_ptr<ID3D11RenderTargetView>& rtv);
    void set_dip_ratio(float ratio);
    bool window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);

    template <typename page_t>
    void register_page();

    template <typename page_t>
    void show_page();

    template <typename page_t>
    void hide_page();

private:
    class refresh_listener : public Rml::EventListener {
    public:
        void ProcessEvent(Rml::Event& event) override {
            Rml::Input::KeyIdentifier key = event.GetParameter("key_identifier", Rml::Input::KeyIdentifier::KI_UNKNOWN);
            if (key == Rml::Input::KI_F5) {
                event.GetTargetElement()->GetOwnerDocument()->ReloadStyleSheet();
            }
        }
    };

    template <typename page_t>
    struct storage {
        static inline page_t page;
        static inline Rml::ElementDocument* document = nullptr;
        static inline refresh_listener refresh_listener;
    };

    HWND window_handle = nullptr;
    Rml::Vector2i window_size = Rml::Vector2i();

    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11RenderTargetView> render_target_view;

    Rml::UniquePtr<dxtk_render_interface> render_interface;
    Rml::UniquePtr<SystemInterface_Win32> system_interface;
    Rml::UniquePtr<FontEngineInterfaceHarfBuzz> font_engine;

    Rml::Context* context = nullptr;
    Rml::UniquePtr<TextInputMethodEditor_Win32> ime;
};

template <typename page_t>
void rml_system::register_page() {
    Rml::DataModelConstructor dmc = this->context->CreateDataModel(Rml::String(page_t::name.c_str()) + "_data");
    storage<page_t>::page.initialize(dmc);

    Rml::ElementDocument* document = this->context->LoadDocument(page_t::path.str());
    if (!document) return;

    document->AddEventListener(Rml::EventId::Keydown, &storage<page_t>::refresh_listener);

    storage<page_t>::document = document;
    storage<page_t>::page.after_load();
}

template <typename page_t>
void rml_system::show_page() {
    if (storage<page_t>::document == nullptr) return;

    storage<page_t>::document->Show();
}

template <typename page_t>
void rml_system::hide_page() {
    if (storage<page_t>::document == nullptr) return;

    storage<page_t>::document->Hide();
}

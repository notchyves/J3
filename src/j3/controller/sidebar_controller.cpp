#include "sidebar_controller.hpp"

#include "framework/core/application.hpp"
#include "j3/view/backups.hpp"
#include "j3/view/home.hpp"
#include "j3/view/mods.hpp"
#include "j3/view/settings.hpp"
#include "j3/view/versions.hpp"

void sidebar_controller::bind_data(Rml::DataModelConstructor& dmc) {
    dmc.Bind("selected_tab", &this->model.selected_tab);
    dmc.Bind("pinned", &this->model.pinned);

    dmc.BindEventCallback("bring_to_front", &sidebar_controller::bring_to_front, this);
    dmc.BindEventCallback("switch_tab", &sidebar_controller::switch_tab, this);
}

void sidebar_controller::bring_to_front(Rml::DataModelHandle, Rml::Event& event, const Rml::VariantList&) {
    event.GetTargetElement()->GetOwnerDocument()->PullToFront();
}

void sidebar_controller::switch_tab(Rml::DataModelHandle handle, Rml::Event& event, const Rml::VariantList& args) {
    if (args.empty()) return;
    
    int requested_tab = args[0].Get(-1);
    if (requested_tab == -1) return;
    this->model.selected_tab = requested_tab;
    
    auto& app = application::get();
    auto& window = app.get_main_window();
    
    window->rml.hide_page<home>();
    window->rml.hide_page<mods>();
    window->rml.hide_page<backups>();
    window->rml.hide_page<versions>();
    window->rml.hide_page<settings>();
    
    switch (requested_tab) {
    case 0:
        window->rml.show_page<home>();
        break;
    case 1:
        window->rml.show_page<mods>();
        break;
    case 2:
        window->rml.show_page<backups>();
        break;
    case 3:
        window->rml.show_page<versions>();
        break;
    case 4:
        window->rml.show_page<settings>();
        break;
    default:
        spdlog::warn("Unknown page requested: {}", requested_tab);
        break;
    }
    
    // make sure sidebar is on top after switching tabs
    event.GetTargetElement()->GetOwnerDocument()->PullToFront();
    
    handle.DirtyVariable("selected_tab");
}
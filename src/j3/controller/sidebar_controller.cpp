#include "sidebar_controller.hpp"

void sidebar_controller::bind_data(Rml::DataModelConstructor& dmc) {
    dmc.Bind("home_selected", &this->model.home_selected);
    dmc.Bind("mods_selected", &this->model.mods_selected);
    dmc.Bind("archives_selected", &this->model.archives_selected);
    dmc.Bind("versions_selected", &this->model.versions_selected);
    dmc.Bind("settings_selected", &this->model.settings_selected);

    dmc.Bind("pinned", &this->model.pinned);
}
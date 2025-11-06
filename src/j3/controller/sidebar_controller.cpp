#include "sidebar_controller.hpp"

void sidebar_controller::bind_data(Rml::DataModelConstructor& dmc) {
    dmc.Bind("selected_tab", &this->model.selected_tab);

    dmc.Bind("pinned", &this->model.pinned);
}
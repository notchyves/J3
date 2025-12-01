#pragma once
#include "common.hpp"

#include "framework/ui/controller/controller.hpp"
#include "j3/model/test_place_model.hpp"

class test_place_controller : public controller {
public:
    void bind_data(Rml::DataModelConstructor& dmc) override;
    
private:
    test_place_model model;
    Rml::DataModelHandle handle;

    void toggle_drop_down_item(Rml::DataModelHandle handle, Rml::Event& e, const Rml::VariantList& args);
    void update_formatted_text();
};

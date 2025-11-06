#pragma once
#include "common.hpp"

#include "framework/ui/controller/controller.hpp"

class test_place_controller : public controller {
public:
    void bind_data(Rml::DataModelConstructor& dmc) override;
};

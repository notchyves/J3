#pragma once
#include "common.hpp"
#include "core/application.hpp"

struct test_place {
    std::string_view id();
    std::string_view layout();
    std::string_view styles();
    void bind_data(Rml::DataModelConstructor& dmc);

private:
    int count = 0;

    void increment_counter(Rml::DataModelHandle handle, Rml::Event&, const Rml::VariantList&) {
        this->count++;
        application::get().log.debug("called");
        handle.DirtyVariable("count");
    }
    
    Rml::DataModelHandle model_handle;
};

#pragma once
#include "common.hpp"

#include "ui/rml_system.hpp"

struct rml_container {
private:
    rml_system& system;
    
public:
    explicit rml_container(rml_system& sys) : system(sys) {}
    
    void render() const {
        system.update();
    }
};
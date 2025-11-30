#include "main_window.hpp"

#include "framework/component/basic/drawable.hpp"
#include "framework/component/basic/transform.hpp"
#include "framework/system/render/renderer.hpp"
#include "j3/view/sidebar.hpp"
#include "j3/view/test_place.hpp"

main_window::main_window(HINSTANCE instance, const std::wstring& title, vector2 size, bool main_window)
    : window(instance, title, size, main_window) {
    this->set_background_color({ 0.058f, 0.058f, 0.058f, 1 });

    this->rml.register_page<test_place>();
    this->rml.register_page<sidebar>();

    this->rml.show_page<test_place>();

    // sidebar must be shown after everything so it appears above everything on first launch
    this->rml.show_page<sidebar>();
}

void main_window::update() {
    window::update(); // allow ECS to update

    // do any updates here
}
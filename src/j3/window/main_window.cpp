#include "main_window.hpp"

#include "framework/component/basic/drawable.hpp"
#include "framework/component/basic/transform.hpp"
#include "framework/system/render/renderer.hpp"

LOAD_RESOURCE(resources_models_jiayi_logo_obj)

main_window::main_window(HINSTANCE instance, const std::wstring& title, vector2 size, bool main_window)
    : window(instance, title, size, main_window) {
    auto& app = application::get();

    this->set_background_color({ 0.058f, 0.058f, 0.058f, 1 });

    // create resources
    std::vector<mesh> jiayi_logo_model = mesh::load(GET_RESOURCE(resources_models_jiayi_logo_obj));
    auto jiayi_logo = app.resources.add<mesh>("jiayi_logo", jiayi_logo_model[0]);

    // jiayi logo
    this->jiayi_logo_entity = this->ecs.create_entity();
    this->ecs.add_component<drawable>(this->jiayi_logo_entity, jiayi_logo);

    auto& tr = this->ecs.add_component<transform>(this->jiayi_logo_entity);
    tr.set_position({ 0, 0, 3 });
}
void main_window::update() {
    window::update(); // allow ECS to update

    auto& t = this->ecs.get_component<transform>(this->jiayi_logo_entity);

    vector3 rotation = t.get_rotation();
    rotation.x += 0.53f;
    rotation.y += 0.5f;
    rotation.z += 0.5f;

    t.set_rotation(rotation);
}
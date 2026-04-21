#include "backups_controller.hpp"

#include "j3/game/minecraft.hpp"

void backups_controller::bind_data(Rml::DataModelConstructor& dmc) {
    dmc.Bind("current_version", &this->model.current_version);
    dmc.Bind("current_w", &this->model.current_w);
    dmc.Bind("current_rp", &this->model.current_rp);
    dmc.Bind("current_bp", &this->model.current_bp);
    
    // init values
    minecraft game;
    this->model.current_version = game.version();
    
    auto current_contents = this->manager.count_backup_contents(game.data_path());
    this->model.current_w = current_contents.worlds;
    this->model.current_rp = current_contents.resource_packs;
    this->model.current_bp = current_contents.behavior_packs;
}
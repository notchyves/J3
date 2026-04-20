#include "backup_manager.hpp"

#include <glaze/core/ostream_buffer.hpp>

backup_manager::backup_manager(const std::filesystem::path& path) : current_path(path) {
    spdlog::info("Loading backup collection from {}", path.string());
    auto json_path = this->current_path / "backups.json";
    
    if (std::filesystem::exists(json_path)) {
        if (auto error = glz::read_file_json(this->collection, json_path.string(), std::string{}); !error) {
            spdlog::info("Loaded backup collection");
        } else {
            spdlog::error("Failed to load backup collection: {}", glz::format_error(error));
        }
        
        return;
    }
    
    // create new
    spdlog::debug("Backup collection does not exist here, creating");
    std::filesystem::create_directories(this->current_path);
    if (auto error = glz::write_file_json(this->collection, json_path.string(), std::string{}); !error) {
        spdlog::info("Created new backup collection");
    } else {
        spdlog::error("Failed to create new backup collection: {}", glz::format_error(error));
    }
}

void backup_manager::save() {
    auto json_path = this->current_path / "backups.json";
    
    if (auto error = glz::write_file_json(this->collection, json_path.string(), std::string{}); !error) {
        spdlog::info("Created new backup collection");
    } else {
        spdlog::error("Failed to create new backup collection: {}", glz::format_error(error));
    }
}

backup_collection& backup_manager::get_backups() {
    return this->collection;
}

void backup_manager::create_backup(const std::string& name, const minecraft_version& for_version) {}
void backup_manager::remove_backup(const std::string& name) {}
#pragma once
#include "common.hpp"
#include "backup.hpp"

class backup_manager {
public:
    std::filesystem::path current_path;
    
    // loads backups from this folder, creates the folder if it doesn't exist
    backup_manager(const std::filesystem::path& path);
    void save();
    
    backup_collection& get_backups();
    void create_backup(const std::string& name, const minecraft_version& for_version);
    void rename_backup(const std::string& name, const std::string& new_name);
    void remove_backup(const std::string& name);
    
    struct backup::contents count_backup_contents(const std::filesystem::path& path);
    
private:
    backup_collection collection;
};

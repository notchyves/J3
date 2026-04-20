#pragma once
#include "common.hpp"
#include "j3/version/minecraft_version.hpp"

struct backup {
    struct contents {
        int worlds;
        int resource_packs;
        int behavior_packs;
    };
    
    std::string name;
    std::string path;
    minecraft_version from_version;
    std::chrono::system_clock::time_point timestamp;
    contents contents;
};
using backup_collection = std::vector<backup>;

static_assert(glz::reflectable<backup>);

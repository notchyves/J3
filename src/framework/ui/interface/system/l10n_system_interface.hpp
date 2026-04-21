#pragma once
#include "common.hpp"

#include <RmlUi_Platform_Win32.h>

class l10n_system_interface : public SystemInterface_Win32 {
public:
    l10n_system_interface(const std::filesystem::path& load_from = "./resources/l10n");
    
    int TranslateString(Rml::String& translated, const Rml::String& input) override;
    
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> locales_to_strings;
    std::string current_locale{ "en_US" };
};

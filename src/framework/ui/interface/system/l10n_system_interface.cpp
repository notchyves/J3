#include "l10n_system_interface.hpp"

l10n_system_interface::l10n_system_interface(const std::filesystem::path& load_from) {
    for (const auto& entry : std::filesystem::directory_iterator{load_from}) {
        std::string locale = entry.path().stem().string();
        std::unordered_map<std::string, std::string> strings;
        
        if (auto error = glz::read_file_json(strings, entry.path().string(), std::string{}); !error) {
            this->locales_to_strings[locale] = strings;
            
            spdlog::debug("Loaded string table for locale {}", locale);
        } else {
            spdlog::warn("Error while loading string table for locale {}, this language will be unavailable: {}", 
                locale, glz::format_error(error));
        }
    }
}

int l10n_system_interface::TranslateString(Rml::String& translated, const Rml::String& input) {
    auto t = this->locales_to_strings[this->current_locale].find(input);
    if (t != this->locales_to_strings[this->current_locale].end()) {
        translated = t->second;
        return 1;
    }
    
    // passthrough
    translated = input;
    return 0;
}
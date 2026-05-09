#pragma once
#include "common.hpp"

class minecraft_version {
public:
    uint16_t major{ 0 };
    uint16_t minor{ 0 };
    uint16_t build{ 0 };
    uint16_t revision{ 0 };
    
    minecraft_version() = default;
    minecraft_version(uint16_t major, uint16_t minor, uint16_t build, uint16_t revision);
    minecraft_version(const std::string& version);
    
    [[nodiscard]] std::string string(bool friendly = true) const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] bool is_gdk() const;
    
    auto operator<=>(const minecraft_version& other) const {
        if (this->empty() && other.empty()) return std::strong_ordering::equal;
        if (this->empty()) return std::strong_ordering::less;
        if (other.empty()) return std::strong_ordering::greater;
        
        // return immediately if not equal, continue otherwise
        if (auto c_major = this->major <=> other.major; c_major != std::strong_ordering::equal)
            return c_major;
        
        if (auto c_minor =this->minor <=> other.minor; c_minor != std::strong_ordering::equal)
            return c_minor;
        
        if (auto c_build = this->build <=> other.build; c_build != std::strong_ordering::equal)
            return c_build;
        
        return this->revision <=> other.revision;
    }

    bool operator==(const minecraft_version& other) const = default;
};
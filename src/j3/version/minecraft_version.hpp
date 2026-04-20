#pragma once
#include "common.hpp"

#include <Shlwapi.h>

// really cool class
class minecraft_version : public std::string {
public:
    auto operator<=>(const minecraft_version& other) const {
        if (this->empty() && other.empty()) return std::strong_ordering::equal;
        if (this->empty()) return std::strong_ordering::less;
        if (other.empty()) return std::strong_ordering::greater;
        
        // convert to wide string to use this function because windows is GOOD
        std::wstring wthis{ this->begin(), this->end() };
        std::wstring wother{ other.begin(), other.end() };
        
        switch (StrCmpLogicalW(wthis.c_str(), wother.c_str())) {
        case 0:
            return std::strong_ordering::equal;
        case -1:
            return std::strong_ordering::less;
        case 1:
            return std::strong_ordering::greater;
        default:
            // ???
            return std::strong_ordering::equal;
        }
    }
};
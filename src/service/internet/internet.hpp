#pragma once
#include "common.hpp"

#include "service/service.hpp"

#include <winrt/Windows.Web.Http.Headers.h>

struct internet : service {
    std::wstring get_string(const std::wstring& uri) const;
    
private:
    winrt::Windows::Web::Http::HttpClient client;
};

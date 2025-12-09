#include "internet.hpp"

std::wstring internet::get_string(const std::wstring& request_uri) const {
    const auto headers{ this->client.DefaultRequestHeaders() };

    if (!headers.UserAgent().TryParseAdd(L"jsft/3.0 (Windows NT 10.0; Win64; x64) J3/1.0.0 Chrome/124.0.0.0 Safari/537.36")) {
        spdlog::error("Failed to set user agent for web request");
        return L"";
    }

    winrt::Windows::Foundation::Uri uri{ request_uri };
    std::wstring response_body;

    winrt::Windows::Web::Http::HttpResponseMessage response_message = this->client.GetAsync(uri).get();
    if (!response_message.IsSuccessStatusCode()) {
        spdlog::error("Web request failed with code {}", static_cast<int>(response_message.StatusCode()));
    }
    
    response_body = response_message.Content().ReadAsStringAsync().get();
    return response_body;
}

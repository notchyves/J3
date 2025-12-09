#pragma once
#include "common.hpp"

#include "framework/resource/resource_manager.hpp"
#include "framework/service/service_collection.hpp"
#include "timer.hpp"
#include "window.hpp"

class application {
public:
    timer time;
    std::vector<std::unique_ptr<window>> windows;
    resource_manager resources;
    service_collection services;
    
    explicit application(HINSTANCE instance);

    static application& get();

    // helper function for getting services with a shorter code path
    template <std::derived_from<service> service_t>
    static std::shared_ptr<service_t> service();

    void run();
    void quit(int exit_code = 0);

    template <std::derived_from<window> T>
    std::unique_ptr<window>& create_window(const std::wstring& title, vector2 size);

    template <std::derived_from<window> T>
    std::unique_ptr<window>& create_window(const std::wstring& title, vector2 position, vector2 size);

    std::unique_ptr<window>& get_main_window();
    
private:
    HINSTANCE instance;
    bool running = false;
    
    static LRESULT CALLBACK window_proc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);
    bool get_message(MSG& message, UINT timeout);
};

template <std::derived_from<service> service_t>
std::shared_ptr<service_t> application::service() {
    return get().services.get<service_t>();
}

template <std::derived_from<window> T>
std::unique_ptr<window>& application::create_window(const std::wstring& title, vector2 size) {
    this->windows.push_back(std::make_unique<T>(this->instance, title, size, this->windows.empty()));
    return this->windows.back();
}

template <std::derived_from<window> T>
std::unique_ptr<window>& application::create_window(const std::wstring& title, vector2 position, vector2 size) {
    this->windows.push_back(std::make_unique<T>(this->instance, title, position, size, this->windows.empty()));
    return this->windows.back();
}

extern char application_buffer[sizeof(application)];

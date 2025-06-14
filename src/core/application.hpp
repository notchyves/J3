#pragma once
#include "common.hpp"

#include "log.hpp"
#include "timer.hpp"
#include "window.hpp"
#include "resource/resource_manager.hpp"
#include "service/service_collection.hpp"

class application {
public:
    class log log;
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

    std::unique_ptr<window>& create_window(const std::wstring& title, vector2 size);
    std::unique_ptr<window>& create_window(const std::wstring& title, vector2 position, vector2 size);
    std::unique_ptr<window>& get_main_window();
    
private:
    HINSTANCE instance;
    bool running = false;
    
    static LRESULT CALLBACK window_proc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param);
};

template <std::derived_from<service> service_t>
std::shared_ptr<service_t> application::service() {
    return get().services.get<service_t>();
}

extern char application_buffer[sizeof(application)];

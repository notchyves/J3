#pragma once
#include "common.hpp"
#include "render/renderer.hpp"

class window {
public:
    HWND handle;
    bool main_window;
    renderer renderer;

    window(HINSTANCE instance, const std::wstring& title, vector2 size, bool main_window);
    window(HINSTANCE instance, const std::wstring& title, vector2 position, vector2 size, bool main_window);

    void finish_create(HINSTANCE instance, const std::wstring& title, vector2 position, vector2 size);

    void show() const;
    void update();
    void close();
    
    bool window_proc(UINT message, WPARAM w_param, LPARAM l_param);

    ~window();

private:
    bool closing;
};

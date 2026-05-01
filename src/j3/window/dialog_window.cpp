#include "dialog_window.hpp"

dialog_window::dialog_window(HINSTANCE instance, const std::wstring& title, const vector2 size)
    : window(instance, title, size, false) {
    this->set_background_color({ 0.058f, 0.058f, 0.058f, 1 });
}
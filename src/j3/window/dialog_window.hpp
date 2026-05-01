#pragma once
#include "common.hpp"

#include "framework/core/window.hpp"

class dialog_window : public window {
    dialog_window(HINSTANCE instance, const std::wstring& title, vector2 size);
};

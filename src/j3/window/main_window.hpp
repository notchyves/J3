#pragma once
#include "common.hpp"

#include "framework/core/application.hpp"

class main_window : public window {
public:
    main_window(HINSTANCE instance, const std::wstring& title, vector2 size, bool main_window);

    void update() override;
};

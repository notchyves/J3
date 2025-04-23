#pragma once
#include "common.hpp"
#include "resource/resource.hpp"

#include <artery-font/artery-font.h>
#include <artery-font/std-artery-font.h>

class font_resource {
public:
    font_resource(const resource& data);

private:
    artery_font::StdArteryFont<float> font;
};

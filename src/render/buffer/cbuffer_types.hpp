#pragma once
#include "common.hpp"

struct cbuffer { }; // base struct for constant buffers

struct cb_vertex : cbuffer {
    matrix mat;
};

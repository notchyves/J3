#pragma once
#include "common.hpp"

class timer {
public:
    double time = 0; // total time elapsed in seconds
    double delta_time = 0; // time elapsed since last frame in seconds
    double fps = 0; // frames per second
    
    timer();

    void update();

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point last_time;
    std::chrono::high_resolution_clock::time_point fps_time;
    int frames = 0;
};

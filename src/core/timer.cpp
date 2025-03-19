#include "timer.hpp"

timer::timer() {
    start_time = std::chrono::high_resolution_clock::now();
    last_time = start_time;
    fps_time = start_time;
}

void timer::update() {
    auto now = std::chrono::high_resolution_clock::now();
    delta_time = std::chrono::duration<double>(now - last_time).count();
    time = std::chrono::duration<double>(now - start_time).count();
    last_time = now;
    frames++;

    // calc fps
    if (std::chrono::duration<double>(now - fps_time).count() >= 1.0) {
        fps = frames;
        frames = 0;
        fps_time = now;
    }
}

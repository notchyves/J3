#include "worker.hpp"

worker::worker(moodycamel::BlockingConcurrentQueue<task>& task_queue) : task_queue(task_queue) { }

void worker::run() {
    this->running = true;
    
    this->thread = std::thread([&] {
        while (this->running) {
            if (!this->task_queue.wait_dequeue_timed(this->current_task, std::chrono::milliseconds{ 5 })) continue;
            
            spdlog::debug("Task assigned: {}", this->current_task.name);
            this->current_task.work(this->current_task);
            spdlog::debug("Task completed: {}", this->current_task.name);
        }
    });
}

worker::~worker() {
    this->running = false;
    this->thread.join();
}
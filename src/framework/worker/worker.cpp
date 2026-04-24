#include "worker.hpp"

worker::worker(moodycamel::BlockingConcurrentQueue<task>& task_queue) : task_queue(task_queue) {
    
}

void worker::run() {
    this->running = true;
    
    this->thread = std::thread([&] {
        task t;
        while (this->running) {
            this->task_queue.wait_dequeue(t);
            t.work(t);
            
        }
    })
}

worker::~worker() {
    
}
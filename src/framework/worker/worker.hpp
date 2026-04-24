#pragma once
#include "common.hpp"

#include "task.hpp"

#include <blockingconcurrentqueue.h>

class worker {
public:
    std::atomic<bool> running{ false };
    
    worker(moodycamel::BlockingConcurrentQueue<task>& task_queue);
    ~worker(); // My only purpose is to work. If I am not working, I am as good as dead.
    
    void run();
    
private:
    std::thread thread{};
    moodycamel::BlockingConcurrentQueue<task>& task_queue;
};

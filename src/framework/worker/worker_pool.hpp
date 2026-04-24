#pragma once
#include "common.hpp"

#include "worker.hpp"

#include <blockingconcurrentqueue.h>

class worker_pool {
public:
    moodycamel::BlockingConcurrentQueue<task> task_queue;
    std::vector<worker> workers;
    
    void add_task(const task& t);
    void allocate(int num_workers);
};

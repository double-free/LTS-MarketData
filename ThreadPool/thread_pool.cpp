#include <iostream>

#include "thread_pool.h"

/*******************
 * Implementations *
 *******************/
ThreadPool::ThreadPool(int thread_num) : shutdown_(false) {
  threads_.reserve(thread_num);
  for (int i = 0; i < thread_num; ++i) {
    // emplace_back 会自动调用 thread 的构造函数
    // 相比 push_back 少了一次 move 过程
    threads_.emplace_back(&ThreadPool::threadEntry, this, i);
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> ul(mu_);
    shutdown_ = true;
    cond_.notify_all(); // 通知所有线程
  }
  std::cerr << "Waiting for threads to finish..." << std::endl;
  for (auto &t : threads_) {
    t.join();
  }
}

void ThreadPool::threadEntry(int i) {
  std::function<void(void)> task;
  printf("ThreadPool: thread %d id = %08x\n", i, std::this_thread::get_id());
  while (true) {
    {
      // 这里不适合使用 lock_guard，因为等待过程中会加锁解锁
      std::unique_lock<std::mutex> ul(mu_);

      // 解锁 ul，阻塞直到满足以下条件之一：
      // 1. 即将关闭 2. 有任务到来
      // 然后获得锁 ul
      cond_.wait(ul, [this]() { return shutdown_ || !tasks_.empty(); });

      if (tasks_.empty()) {
        // 通过了前面的阻塞，然而没有任务，说明是即将关闭
        std::cerr << "Thread " << i << " terminates" << std::endl;
        return;
      }

      std::cerr << "Thread " << i << " does a job" << std::endl;
      task = std::move(tasks_.front());
      tasks_.pop();
      // unlock here
    }
    task();
  }
}

void ThreadPool::doJob(std::function<void(void)> func) {
  std::unique_lock<std::mutex> ul(mu_);
  tasks_.emplace(std::move(func));
  cond_.notify_one(); // 通知调度中的下一个线程
}

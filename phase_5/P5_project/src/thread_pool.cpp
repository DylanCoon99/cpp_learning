// Reuse your ThreadPool implementation from step 20.
// Copy your working code here.

#include "thread_pool.h"

// YOUR CODE HERE
ThreadPool::ThreadPool(int num_threads) {
	for (int i = 0; i < num_threads; ++i) {
		workers_.emplace_back(std::thread(&ThreadPool::worker_loop, this));
	}
}


ThreadPool::~ThreadPool() {
	stop_ = true;
	cv_.notify_all();
	for (auto& thread : workers_) {
		thread.join(); // wait for each thread to finish it's current task
	}
}


void ThreadPool::worker_loop() {

	while (true) {
		
		std::function<void()> task;
		{

			// Anything that includes shared resources needs to be in the lock's scope
			std::unique_lock<std::mutex> lock(mtx_);
			cv_.wait(lock, [this]{ return stop_ || !tasks_.empty(); });  

			if (stop_ && tasks_.empty()) return;

			task = std::move(tasks_.front());                                                                                                                                     
			tasks_.pop();
		}
		                                                                                                                                   
		task();
		
	}

}


int ThreadPool::pending() const {
	return tasks_.size();
}


int ThreadPool::num_workers() const {
	return workers_.size();
}
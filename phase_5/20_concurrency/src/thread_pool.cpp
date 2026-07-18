// Implement the ThreadPool methods.
//
// Constructor:
//   - Create 'num_threads' worker threads
//   - Each runs worker_loop()
//   - Store them in workers_ vector
//
// worker_loop:
//   - Loop forever until stop_ is true AND tasks_ is empty
//   - Wait on cv_ with unique_lock
//   - When woken: if stop_ and queue empty, return
//   - Otherwise: pop a task from the queue, unlock, execute it
//
// Destructor:
//   - Set stop_ to true
//   - Notify all workers (cv_.notify_all())
//   - Join all worker threads
//
// pending:
//   - Lock mutex, return tasks_.size()

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
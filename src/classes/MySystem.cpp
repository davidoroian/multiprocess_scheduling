#include "MySystem.h"

#include <chrono>
#include <iostream>

MySystem::MySystem(const std::vector<MyProcess>& process_types)
    : process_types(process_types), running(false), current_time(0) {}

std::vector<MyProcess> MySystem::getProcessTypes() const {
  return process_types;
}
std::queue<MyProcess> MySystem::getProcessQueue() const {
  return process_queue;
}
void MySystem::pushProcessToQueue(MyProcess process) {
  std::lock_guard<std::mutex> lock(queue_mutex);
  process_queue.push(process);
  std::cout << "Pushed Process " << process.getName() << " to the queue\n";
  cv.notify_one();  // Notify the queueHandler thread
}
void MySystem::popProcessFromQueue() {
  std::lock_guard<std::mutex> lock(queue_mutex);
  if (!process_queue.empty()) {
    process_queue.pop();
  }
}
void MySystem::timeManager(int seconds) {
  const auto start_time = std::chrono::steady_clock::now();
  while (current_time < seconds && running) {
    current_time =
        static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                             std::chrono::steady_clock::now() - start_time)
                             .count());
    std::cout << "Current second " << current_time << "\n";
    time_cv.notify_all();  // Notify the processSpawner thread
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  running = false;
  cv.notify_all();       // Notify all waiting threads to wake up for graceful
  time_cv.notify_all();  // termination
}
void MySystem::processSpawner() {
  while (running) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    // if (running) {
    time_cv.wait(lock);
    // } else {
    // break;
    // }
    for (const auto& process : getProcessTypes()) {
      if (current_time % process.getSpawnTime() == 0) {
        lock.unlock();
        pushProcessToQueue(process);
        lock.lock();
      }
    }
  }
}
void MySystem::queueHandler() {
  while (running) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    cv.wait(lock);
    while (!process_queue.empty()) {
      MyProcess process = process_queue.front();
      process_queue.pop();
      // this might be moved in a CPU class somehow
      lock.unlock();  // unlock the mutex while this thread is handling the
                      // process
      // handle the process
      std::cout << "Handling Process " << process.getName() << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(
          process.getExecutionTime()));  // simulate the process execution
      std::cout << "Finished Handling Process " << process.getName() << "\n";
      lock.lock();  // Lock the mutex again before checking the queue
      if (running) {
        time_cv.wait(lock);  // Wait for the next second to pass
      } else {
        break;
      }
    }
  }
}
void MySystem::run(int seconds) {
  running = true;
  std::thread time_thread(&MySystem::timeManager, this, seconds);
  std::thread spawner_thread(&MySystem::processSpawner, this);
  std::thread queue_thread(&MySystem::queueHandler, this);

  time_thread.join();
  spawner_thread.join();
  queue_thread.join();
}
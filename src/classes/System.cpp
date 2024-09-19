#include "System.h"

#include <chrono>
#include <iostream>


System::System(const std::vector<Process>& process_types)
    : process_types(process_types), running(false), current_time(0) {}

std::vector<Process> System::getProcessTypes() const { return process_types; }
std::queue<Process> System::getProcessQueue() const { return process_queue; }
void System::pushProcessToQueue(Process process) {
  std::lock_guard<std::mutex> lock(queue_mutex);
  process_queue.push(process);
  cv.notify_one();  // Notify the queueHandler thread
}
void System::popProcessFromQueue() {
  std::lock_guard<std::mutex> lock(queue_mutex);
  if (!process_queue.empty()) {
    process_queue.pop();
  }
}
void System::timeManager(int seconds) {
  const auto start_time = std::chrono::steady_clock::now();
  while (current_time < seconds && running) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    current_time = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(
                       std::chrono::steady_clock::now() - start_time)
                       .count());
    time_cv.notify_all();  // Notify the processSpawner thread
  }
  running = false;
  cv.notify_all();       // Notify all waiting threads to wake up for graceful
  time_cv.notify_all();  // termination
}
void System::processSpawner() {
  while (running) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    time_cv.wait(lock, [this] { return !running || current_time > 0; });

    for (const auto& process : getProcessTypes()) {
      if (current_time % process.getSpawnTime() == 0) {
        pushProcessToQueue(process);
      }
    }
  }
}
void System::queueHandler() {
  while (running) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    cv.wait(lock, [this] { return !process_queue.empty() || !running; });
    while (!process_queue.empty()) {
      Process process = process_queue.front();
      process_queue.pop();
      // this might be moved in a CPU class somehow
      lock.unlock();  // unlock the mutex while this thread is handling the
                      // process
      // handle the process
      std::cout << "Handling Process " << process.getName() << "\n";
      std::this_thread::sleep_for(std::chrono::seconds(
          process.getExecutionTime()));  // simulate the process execution
      lock.lock();  // Lock the mutex again before checking the queue
      time_cv.wait(lock, [this] {
        return !running || current_time > 0;
      });  // Wait for the next second to pass
    }
  }
}
void System::run(int seconds) {
  running = true;
  std::thread time_thread(&System::timeManager, this, seconds);
  std::thread spawner_thread(&System::processSpawner, this);
  std::thread queue_thread(&System::queueHandler, this);

  time_thread.join();
  spawner_thread.join();
  queue_thread.join();
}
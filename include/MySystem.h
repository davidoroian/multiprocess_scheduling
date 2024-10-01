#ifndef MYSYSTEM_H
#define MYSYSTEM_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "MyProcess.h"

/**
 * @class MySystem
 * @brief Represents a system with a list of processes and a queue in which
 * processes spawn with respect to their spawn time.
 * @param process_types The list of processes types to be executed by the
 * system.
 */
class MySystem {
 private:
  std::vector<MyProcess> process_types;
  std::queue<MyProcess> process_queue;
  std::mutex queue_mutex;
  std::condition_variable cv;
  std::condition_variable time_cv;
  bool running;
  int current_time;

 public:
  /**
   * @brief Constructs a new MySystem object.
   *
   * @param process_types The list of process types to be executed by the
   * system.
   */
  MySystem(const std::vector<MyProcess>& process_types);
  /**
   * @brief Gets the list of process types in the system.
   *
   * @return The list of process types in the system.
   */
  std::vector<MyProcess> getProcessTypes() const;
  /**
   * @brief Gets the process queue from the system.
   *
   * @return The process queue from the system.
   */
  std::queue<MyProcess> getProcessQueue() const;
  /**
   * @brief Adds a process to the end of the queue.
   */
  void pushProcessToQueue(MyProcess process);
  /**
   * @brief Remove a process from the front of the queue.
   */
  void popProcessFromQueue();
  /**
   * @brief Handles the passage of time.
   */
  void timeManager(int seconds);
  /**
   * @brief Spawns processes based on the elapsed time and the processes' spawn
   * time.
   */
  void processSpawner();
  /**
   * @brief Handles the processes in the queue.
   */
  void queueHandler();
  /**
   * @brief Runs the system for a specified amount of seconds.
   *
   * @param seconds The amount of time to run the system for in seconds.
   */
  void run(int seconds);
};

#endif  // MYSYSTEM_H

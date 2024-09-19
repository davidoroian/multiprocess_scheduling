#ifndef SYSTEM_H
#define SYSTEM_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "Process.h"

/**
 * @class System
 * @brief Represents a system with a list of processes and a queue in which
 * processes spawn with respect to their spawn time.
 * @param process_types The list of processes types to be executed by the
 * system.
 */
class System {
 private:
  std::vector<Process> process_types;
  std::queue<Process> process_queue;
  std::mutex queue_mutex;
  std::condition_variable cv;
  std::condition_variable time_cv;
  bool running;
  int current_time;

 public:
  /**
   * @brief Constructs a new System object.
   *
   * @param process_types The list of processes types to be executed by the
   * system.
   */
  System(const std::vector<Process>& process_types);
  /**
   * @brief Gets the list of process types in the system.
   *
   * @return The list of process types in the system.
   */
  std::vector<Process> getProcessTypes() const;
  /**
   * @brief Gets the process queue from the system.
   *
   * @return The process queue from the system.
   */
  std::queue<Process> getProcessQueue() const;
  /**
   * @brief Adds a process to the end of the queue.
   */
  void pushProcessToQueue(Process process);
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

#endif  // SYSTEM_H


#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <string>

/**
 * @class MyProcess
 * @brief Represents a process with name, spawn time, deadline, and execution
 * time.
 * @param name The name of the process.
 * @param spawn_time The time after which the process is respawned.
 * @param deadline The time in which the process must be completed. If deadlline
 * will be missed by taking the execution time into account, the process will be
 * discraded.
 * @param execution_time The execution time it takes for the process to finish.
 *
 * The Process class encapsulates the attributes of a process including its
 * name, spawn time, deadline, and execution time. It provides methods to access
 * these attributes.
 */
class MyProcess {
 private:
  std::string name;
  int spawn_time;
  int deadline;
  int execution_time;

 public:
  /**
   * @brief Constructs a new MyProcess object.
   *
   * @param name The name of the process.
   * @param spawn_time The time after which the process is respawned.
   * @param deadline The time in which the process must be completed. If
   * deadlline will be missed by taking the execution time into account, the
   * process will be discraded.
   * @param execution_time The execution time it takes for the process to
   * finish.
   */
  MyProcess(const std::string& name, int spawn_time, int deadline,
          int execution_time);
  /**
   * @brief Gets the name of the process.
   *
   * @return The name of the process.
   */
  std::string getName() const;
  /**
   * @brief Gets the spawn time of the process.
   *
   * @return The spawn time of the process.
   */
  int getSpawnTime() const;
  /**
   * @brief Gets the deadline of the process.
   *
   * @return The deadline of the process.
   */
  int getDeadline() const;
  /**
   * @brief Gets the execution time of the process.
   *
   * @return The execution time of the process.
   */
  int getExecutionTime() const;
};

#endif  // MYPROCESS_H
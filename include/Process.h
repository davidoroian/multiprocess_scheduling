
#ifndef PROCESS_H
#define PROCESS_H
/**
 * @class Process
 * @brief Represents a process with spawn time, deadline, and execution time.
 *
 * The Process class encapsulates the attributes of a process including its
 * spawn time, deadline, and execution time. It provides methods to access
 * these attributes.
 */
class Process {
 private:
  int spawn_time;
  int deadline;
  int execution_time;

 public:
  /**
   * @brief Constructs a new Process object.
   *
   * @param spawn The time aftert which the process is respawned.
   * @param dead The time in which the process must be completed. If deadlline
   * will be missed by taking the execution time into account, the process will
   * be discraded.
   * @param exec The execution time it taked for the process to finish.
   */
  Process(int spawn, int dead, int exec);
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

#endif  // PROCESS_H
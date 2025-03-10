#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

#include "CPU.h"
#include "Process.h"

enum SchedulingPolicy { FCFS, EDF };

class Scheduler {
 public:
  std::vector<CPU> cpus;
  std::vector<Process> processes;
  SchedulingPolicy policy;

  Scheduler(int num_cpus, SchedulingPolicy policy);
  void add_process(Process process);
  void run(int total_time);
  void schedule();
};

#endif  // SCHEDULER_H
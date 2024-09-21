#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include <vector>

#include "CPU.h"
#include "MyProcess.h"

enum SchedulingPolicy { FCFS, EDF };

class MyScheduler {
 public:
  std::vector<CPU> cpus;
  std::vector<MyProcess> processes;
  SchedulingPolicy policy;

  MyScheduler(int num_cpus, SchedulingPolicy policy);
  void add_process(MyProcess process);
  void run(int total_time);
  void schedule();
};

#endif  // MYSCHEDULER_H
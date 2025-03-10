#ifndef CPU_H
#define CPU_H

#include "Process.h"

class CPU {
 public:
  bool is_busy;
  Process* current_process;

  CPU();
  void assign_process(Process* process);
};

#endif  // CPU_H

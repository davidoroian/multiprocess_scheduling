#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "Process.h"
#include "System.h"

int main() {
  std::vector<Process> process_types = {
      Process("Process 1", 1, 10, 2),
      Process("Process 2", 2, 10, 3),
      Process("Process 3", 3, 10, 4),
  };
  System system(process_types);
  system.run(10);

  return 0;
}
#include "MyProcess.h"
#include "MySystem.h"

int main() {
  std::vector<MyProcess> process_types = {
      MyProcess("Process 1", 1, 10, 2),
      MyProcess("Process 2", 2, 10, 3),
      MyProcess("Process 3", 3, 10, 4),
  };
  MySystem system(process_types);
  system.run(10);

  return 0;
}
#include "MySystem.h"

int main() {
  std::vector<MyProcess> process_types = {
      MyProcess("A", 30, 10, 7),
      MyProcess("B", 10, 7, 4),
      MyProcess("C", 5, 2, 1),
  };
  MySystem system(process_types);
  system.run(30);

  return 0;
}
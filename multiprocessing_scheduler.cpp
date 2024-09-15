#include <iostream>

#include "Process.h"

int main() {

  Process p(10, 20, 30);

  std::cout << "Spawn Time: " << p.getSpawnTime() << std::endl;
  std::cout << "Deadline: " << p.getDeadline() << std::endl;
  std::cout << "Execution Time: " << p.getExecutionTime() << std::endl;

  return 0;
}
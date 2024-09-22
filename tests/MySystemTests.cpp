#include <gtest/gtest.h>

#include "MySystem.h"


// Test fixture for MySystem
class MySystemTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up code here
    std::vector<MyProcess> process_types = {
        MyProcess("Process 1", 1, 10, 2),
        MyProcess("Process 2", 2, 10, 3),
        MyProcess("Process 3", 3, 10, 4),
    };
    system = new MySystem(process_types);
  }

  void TearDown() override {
    // Clean up code here
    delete system;
  }

  std::vector<MyProcess> processes;
  MySystem* system;
};

// Test case for processSpawner
TEST_F(MySystemTest, ProcessSpawnerTest) {
  std::thread spawner_thread(&MySystem::processSpawner, system);
  system->run(5);  // Run the system for 5 seconds
  spawner_thread.join();

  // Check if processes are pushed to the queue correctly
  auto queue = system->getProcessQueue();
  EXPECT_FALSE(queue.empty());
}
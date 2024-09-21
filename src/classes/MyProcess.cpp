#include "MyProcess.h"

MyProcess::MyProcess(const std::string& name, int spawn, int dead, int exec)
    : name(name), spawn_time(spawn), deadline(dead), execution_time(exec) {}

std::string MyProcess::getName() const { return name; }
int MyProcess::getSpawnTime() const { return spawn_time; }
int MyProcess::getDeadline() const { return deadline; }
int MyProcess::getExecutionTime() const { return execution_time; }
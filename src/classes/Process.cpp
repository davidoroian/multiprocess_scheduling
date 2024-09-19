#include "Process.h"

Process::Process(const std::string& name, int spawn, int dead, int exec)
    : name(name), spawn_time(spawn), deadline(dead), execution_time(exec) {}

std::string Process::getName() const { return name; }
int Process::getSpawnTime() const { return spawn_time; }
int Process::getDeadline() const { return deadline; }
int Process::getExecutionTime() const { return execution_time; }
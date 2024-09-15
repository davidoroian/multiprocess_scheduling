#include "Process.h"

Process::Process(int spawn, int dead, int exec)
    : spawn_time(spawn), deadline(dead), execution_time(exec) {}

int Process::getSpawnTime() const { return spawn_time; }
int Process::getDeadline() const { return deadline; }
int Process::getExecutionTime() const { return execution_time; }
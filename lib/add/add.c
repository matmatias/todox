#include "globals.h"
#include "registry.h"
#include <string.h>

void addTask(int taskNameLength, char taskName[]) {
  if (getDoesTasksRegistryExist() != 1) {
    createCSVFile();
  }

  Task task;
  task.name = taskName;
  task.is_completed = false;

  writeTaskToFile(task);
  printf("Task %s added\n", taskName);

  return;
}
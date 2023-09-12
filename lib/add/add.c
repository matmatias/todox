#include "globals.h"
#include "registry.h"
#include <string.h>

void addTask(int taskNameLength, char taskName[]) {
  if (getDoesTasksRegistryExist() != 1) {
    createCSVFile();
  }

  Task newTask;
  strcpy(newTask.name, taskName);
  newTask.completed = 0;

  writeTaskToFile(newTask);
  printf("Task %s added\n", taskName);

  return;
}
#include "globals.h"
#include "registry.h"

#include <stdio.h>

int listTasks() {
  int isTasksRegistryEmpty = getIsTasksRegistryEmpty();
  int doesTasksRegistryExist = getDoesTasksRegistryExist();

  if (isTasksRegistryEmpty == ERROR_INVALID_TASKS_REGISTRY) {
    return ERROR_INVALID_TASKS_REGISTRY;
  }
  if (isTasksRegistryEmpty == TRUE || doesTasksRegistryExist == FALSE) {
    printf("No tasks to be listed\n");
    return 0;
  } else {
    printf("To be implemented\n");
    /* implementation */
    FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
    // read csv header
    // parse csv
    return 0;
  }
}
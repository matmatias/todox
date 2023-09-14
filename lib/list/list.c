#include "globals.h"
#include "registry.h"

#include <stdio.h>
#include <stdlib.h>

int listTasks() {
  int isTasksRegistryEmpty = getIsTasksRegistryEmpty();
  int doesTasksRegistryExist = getDoesTasksRegistryExist();

  if (isTasksRegistryEmpty == ERROR_INVALID_TASKS_REGISTRY) {
    return ERROR_INVALID_TASKS_REGISTRY;
  }
  if (isTasksRegistryEmpty == TRUE || doesTasksRegistryExist == FALSE) {
    printf("No tasks to be listed\n");
    return 0;
  }

  FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
  readHeader(taskRegistry);

  Task *tasks = NULL;
  int tasksLen = 0;
  int *tasksLenPtr = &tasksLen;
  int parseIntStatus = parseRegistry(taskRegistry, &tasks, tasksLenPtr);

  printf("Tasks:\n");
  for (int i = 0; i < tasksLen; ++i) {
    printf("%s\n", tasks[i].name);
  }

  free(tasks);
  return parseIntStatus;
}
#include "globals.h"
#include "registry.h"

#include <stdio.h>
#include <stdlib.h>

int getRegistryStatus() {
  int isTasksRegistryEmpty = getIsTasksRegistryEmpty();
  int doesTasksRegistryExist = getDoesTasksRegistryExist();

  if (isTasksRegistryEmpty == ERROR_INVALID_TASKS_REGISTRY) {
    return ERROR_INVALID_TASKS_REGISTRY;
  }

  if (isTasksRegistryEmpty == TRUE || doesTasksRegistryExist == FALSE) {
    printf("No tasks to be listed\n");
    return 0;
  }

  if (isTasksRegistryEmpty == ERROR_INVALID_TASKS_REGISTRY) {
    return ERROR_INVALID_TASKS_REGISTRY;
  }

  if (isTasksRegistryEmpty == TRUE || doesTasksRegistryExist == FALSE) {
    printf("No tasks to be listed\n");
    return 0;
  }

  return 0;
}

int listTasks() {
  int registryStatus = getRegistryStatus();
  if (registryStatus != 0) {
    return registryStatus;
  }

  FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
  readHeader(taskRegistry);

  Task *tasks = NULL;
  int tasksLen = 0;
  int *tasksLenPtr = &tasksLen;
  int parseRegistryStatus = parseRegistry(taskRegistry, &tasks, tasksLenPtr);

  printf("Tasks:\n");
  for (int i = 0; i < tasksLen; ++i) {
    Task task = tasks[i];
    char *status = NULL;

    if (task.is_completed == false) {
      status = "PENDING";
    } else {
      status = "COMPLETED";
    }

    printf("%s, %s\n", task.name, status);
  }

  free(tasks);
  return parseRegistryStatus;
}

int listPendingTasks() {
  int registryStatus = getRegistryStatus();
  if (registryStatus != 0) {
    return registryStatus;
  }

  FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
  readHeader(taskRegistry);

  Task *tasks = NULL;
  int tasksLen = 0;
  int *tasksLenPtr = &tasksLen;
  int parseIntStatus = parseRegistry(taskRegistry, &tasks, tasksLenPtr);

  printf("PENDING Tasks:\n");
  for (int i = 0; i < tasksLen; ++i) {
    if (tasks[i].is_completed == false) {
      printf("%s\n", tasks[i].name);
    }
  }

  free(tasks);
  return parseIntStatus;
}

int listCompletedTasks() {
  int registryStatus = getRegistryStatus();
  if (registryStatus != 0) {
    return registryStatus;
  }

  FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
  readHeader(taskRegistry);

  Task *tasks = NULL;
  int tasksLen = 0;
  int *tasksLenPtr = &tasksLen;
  int parseIntStatus = parseRegistry(taskRegistry, &tasks, tasksLenPtr);

  printf("COMPLETED Tasks:\n");
  for (int i = 0; i < tasksLen; ++i) {
    if (tasks[i].is_completed == true) {
      printf("%s\n", tasks[i].name);
    }
  }

  free(tasks);
  return parseIntStatus;
}
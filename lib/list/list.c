#include "globals.h"
#include "registry.h"
#include <stdio.h>
#include <stdlib.h>

void listTasks(void) {
  bool is_tasks_registry_populated = get_is_tasks_registry_populated();
  if (is_tasks_registry_populated == false) {
    printf("No tasks to be listed\n");
    return;
  }

  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *taskRegistry = fopen(tasks_registry_full_path, "r");
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
}

void listPendingTasks(void) {
  bool is_tasks_registry_populated = get_is_tasks_registry_populated();
  if (is_tasks_registry_populated == false) {
    printf("No tasks to be listed\n");
    return;
  }

  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *taskRegistry = fopen(tasks_registry_full_path, "r");
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
}

void listCompletedTasks(void) {
  bool is_tasks_registry_populated = get_is_tasks_registry_populated();
  if (is_tasks_registry_populated == false) {
    printf("No tasks to be listed\n");
    return;
  }

  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *taskRegistry = fopen(tasks_registry_full_path, "r");
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
}

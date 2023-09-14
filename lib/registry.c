#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void createCSVFile() {
  FILE *file = fopen(TASKS_REGISTRY_NAME, "w");

  fprintf(file, "NAME,COMPLETED");
  fclose(file);
}

void writeTaskToFile(Task task) {
  FILE *file = fopen(TASKS_REGISTRY_NAME, "a");

  fprintf(file, "\n%s,%d", task.name, task.is_completed);
  fclose(file);

  return;
}

int getDoesTasksRegistryExist() {
  if (access(TASKS_REGISTRY_NAME, F_OK) == 0) {
    return TRUE;
  }

  return FALSE;
}

int getIsTasksRegistryEmpty() {
  FILE *file;
  file = fopen(TASKS_REGISTRY_NAME, "r");
  if (file == NULL) {
    return ERROR_TASKS_REGISTRY_DOES_NOT_EXIST;
  }

  /* read file header */
  char fileChar;
  for (int i = 0; i < TASKS_REGISTRY_HEADER_BUFFER + 1; ++i) {
    fileChar = fgetc(file);
  }

  if (fileChar == EOF) {
    fclose(file);
    return TRUE;
  }

  if (fileChar == '\n') {
    fileChar = fgetc(file);
    if (fileChar == EOF) {
      fclose(file);
      return TRUE;
    }

    while (fileChar != EOF) {
      if (fileChar != '\n' && fileChar != '\t' && fileChar != ' ') {
        fclose(file);
        return FALSE;
      }
      fileChar = fgetc(file);
    }

    fclose(file);
    return TRUE;
  }

  fclose(file);
  return ERROR_INVALID_TASKS_REGISTRY;
}

int readHeader(FILE *taskRegistry) {
  char *header = "NAME,COMPLETED\n";

  for (int i = 0; i < strlen(header); ++i) {
    fgetc(taskRegistry);
  }

  return 0;
}

int parseRegistry(FILE *taskRegistry, Task *out_tasks[], int *out_tasksLen) {
  Task *temp_out_tasks = NULL;

  char line[MAX_TASKS_NAME_LENGTH + 2];

  while (fgets(line, MAX_TASKS_NAME_LENGTH + 2, taskRegistry)) {
    char *lineTmp = strdup(line);
    char *token = strtok(lineTmp, ",");

    while (token) {
      int taskNameLen = strlen(token) - 1;
      char *taskName = (char *)malloc(taskNameLen);
      if (taskName == NULL) {
        fprintf(stderr, "Memory allocation failed");
        return ERROR_MEM_ALLOCATION_FAILED;
      }
      strcpy(taskName, token);

      char *completedEnd;
      char *completedToken = strtok(NULL, ",");
      int completed = strtol(completedToken, &completedEnd, 10);

      Task task;
      task.name = taskName;
      task.is_completed = completed;

      temp_out_tasks =
          (Task *)realloc(temp_out_tasks, ++(*out_tasksLen) * sizeof(Task));

      if (temp_out_tasks == NULL) {
        fprintf(stderr, "Memory allocation failed");
        return ERROR_MEM_ALLOCATION_FAILED;
      }

      temp_out_tasks[*out_tasksLen - 1] = task;
      token = strtok(NULL, ",");
    }

    *out_tasks = temp_out_tasks;
    free(lineTmp);
  }

  return 0;
}
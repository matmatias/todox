#include "globals.h"
#include <stdio.h>
#include <unistd.h>

void createCSVFile() {
  FILE *file = fopen(TASKS_REGISTRY_NAME, "w");

  fprintf(file, "NAME,COMPLETED");
  fclose(file);
}

void writeTaskToFile(Task task) {
  FILE *file = fopen(TASKS_REGISTRY_NAME, "a");

  fprintf(file, "\n%s,%d", task.name, task.completed);
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
  for (int i = 0; i < TASKS_REGISTRY_HEADER_BUFFER; ++i) {
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
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

bool get_does_dir_exists(const char *tasks_registry_path) {
  if (access(tasks_registry_path, F_OK) == 0) {
    return true;
  };

  return false;
}

char *get_tasks_registry_base_path(void) {
  char *tasks_registry_base_path = NULL;
  char *tasks_registry_dir_location = ".local/share";
  int separator_slashes_qty = 2;

  tasks_registry_base_path = (char *)malloc(
      strlen(getenv("HOME")) + strlen(tasks_registry_dir_location) +
      strlen(PROGRAM_NAME) + separator_slashes_qty);

  sprintf(tasks_registry_base_path, "%s/%s/%s", getenv("HOME"),
          tasks_registry_dir_location, PROGRAM_NAME);

  return tasks_registry_base_path;
}

char *get_tasks_registry_full_path() {
  char *tasks_registry_base_path = get_tasks_registry_base_path();

  int separator_slashes_qty = 1;
  char *tasks_registry_full_path = NULL;
  tasks_registry_full_path =
      (char *)malloc(strlen(tasks_registry_base_path) +
                     strlen(TASKS_REGISTRY_NAME) + separator_slashes_qty);
  sprintf(tasks_registry_full_path, "%s/%s", get_tasks_registry_base_path(),
          TASKS_REGISTRY_NAME);

  free(tasks_registry_base_path);
  return tasks_registry_full_path;
}

void createCSVFile(void) {
  if (get_does_dir_exists(get_tasks_registry_base_path()) == false) {
    const int mkdir_status = mkdir(get_tasks_registry_base_path(), 0755);

    if (mkdir_status != 0) {
      fprintf(stderr, "Error creating tasks registry in %s\n",
              get_tasks_registry_base_path());
      exit(1);
    };
  }

  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *file = fopen(tasks_registry_full_path, "w");
  free(tasks_registry_full_path);

  fprintf(file, "NAME,COMPLETED\n");
  fclose(file);
}

void writeTaskToFile(Task task) {
  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *file = fopen(tasks_registry_full_path, "a");
  free(tasks_registry_full_path);

  fprintf(file, "%s,%d\n", task.name, task.is_completed);
  fclose(file);

  return;
}

bool getDoesTasksRegistryExist(void) {
  char *tasks_registry_full_path = get_tasks_registry_full_path();

  if (access(tasks_registry_full_path, F_OK) == 0) {
    free(tasks_registry_full_path);
    return true;
  }

  free(tasks_registry_full_path);
  return false;
}

bool getIsTasksRegistryEmpty(void) {
  FILE *file;
  char *tasks_registry_full_path = get_tasks_registry_full_path();
  file = fopen(tasks_registry_full_path, "r");
  free(tasks_registry_full_path);

  /* read file header */
  char fileChar;
  for (int i = 0; i < TASKS_REGISTRY_HEADER_BUFFER + 1; ++i) {
    fileChar = fgetc(file);
  }

  if (fileChar == EOF) {
    fclose(file);
    return true;
  }

  if (fileChar == '\n') {
    fileChar = fgetc(file);
    if (fileChar == EOF) {
      fclose(file);
      return true;
    }

    while (fileChar != EOF) {
      if (fileChar != '\n' && fileChar != '\t' && fileChar != ' ') {
        fclose(file);
        return false;
      }
      fileChar = fgetc(file);
    }

    fclose(file);
    return true;
  }

  fclose(file);
  fprintf(stderr,
          "ERROR_INVALID_TASKS_REGISTRY: invalid tasks registry format.\n");
  exit(1);
}

bool get_is_tasks_registry_populated(void) {
  bool doesTasksRegistryExist = getDoesTasksRegistryExist();
  if (doesTasksRegistryExist == false) {
    return false;
  }

  bool isTasksRegistryEmpty = getIsTasksRegistryEmpty();
  if (isTasksRegistryEmpty == true) {
    return false;
  }

  return true;
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

void changeCompleteInRegistry(FILE *readBuffer, char searchedTask[],
                              bool isCompleted) {
  char line[MAX_TASKS_NAME_LENGTH + 3];

  // Assemble the temp file full path
  char tempFileName[] = ".temp_write_registry.csv";
  char *temp_file_full_path = NULL;
  temp_file_full_path = (char *)malloc(strlen(get_tasks_registry_base_path()) +
                                       strlen(tempFileName) + 1);
  sprintf(temp_file_full_path, "%s/%s", get_tasks_registry_base_path(),
          tempFileName);

  FILE *writeBuffer = fopen(temp_file_full_path, "w");
  char *headerLine = (char *)malloc(strlen(TASKS_REGISTRY_HEADER) + 1);

  sprintf(headerLine, "%s\n", TASKS_REGISTRY_HEADER);
  fputs(headerLine, writeBuffer);

  while (fgets(line, sizeof(line), readBuffer) != NULL) {
    char *tmpLine = strdup(line);
    char *token = strtok(tmpLine, ",");
    int taskNameLen = strlen(token);

    if (strcmp(searchedTask, token) == 0) {
      char newLine[taskNameLen + 3];
      sprintf(newLine, "%s,%d\n", searchedTask, isCompleted);

      fputs(newLine, writeBuffer);
    } else {
      fputs(line, writeBuffer);
    }
  }

  char *tasks_registry_full_path = get_tasks_registry_full_path();
  if (remove(tasks_registry_full_path) != 0) {
    fprintf(stderr, "File deletion failed in changeCompleteInRegistry");
    exit(1);
  }

  if (rename(temp_file_full_path, tasks_registry_full_path) != 0) {
    fprintf(stderr, "File rename failed in changeCompleteInRegistry");
    exit(1);
  }

  free(tasks_registry_full_path);
  fclose(readBuffer);
  fclose(writeBuffer);
}

void purge_registry(void) {
  char *tasks_registry_full_path = get_tasks_registry_full_path();

  int remove_tasks_registry_status = remove(tasks_registry_full_path);
  if (remove_tasks_registry_status == 0) {
    free(tasks_registry_full_path);
    printf("Tasks registry successfully purged\n");

    return;
  }

  free(tasks_registry_full_path);
  fprintf(stderr, "Error purging tasks registry. ERROR CODE: %d\n",
          remove_tasks_registry_status);
  exit(1);
}

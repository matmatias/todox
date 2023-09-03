#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

#define CORRECT_MANIPULATION_ARGUMENTS_NUMBER 3
#define CORRECT_LISTAGE_ARGUMENTS_NUMBER 2

#define MAX_TASKS 100
#define MAX_TASKS_NAME_LENGTH 1000
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define TASKS_REGISTRY_FILENAME ".tasks_registry.csv"
#define TASKS_REGISTRY_HEADER_BUFFER 15 // number of bytes of the CSV header
#define TASKS_REGISTRY_HEADER "NAME,COMPLETED"
// Error codes
#define ERROR_INVALID_NUMBER_OF_ARGS -1
#define ERROR_INVALID_OPERATION -2
#define ERROR_TASKS_REGISTRY_DOES_NOT_EXIST -3
#define ERROR_INVALID_TASKS_REGISTRY -4

typedef struct {
  char name[MAX_TASKS_NAME_LENGTH];
  int completed;
} Task;

enum Operations { Add, Remove, List, Complete };

void createCSVFile() {
  FILE *file = fopen(TASKS_REGISTRY_FILENAME, "w");

  fprintf(file, "NAME,COMPLETED");
  fclose(file);
}

void writeTaskToFile(Task task) {
  FILE *file = fopen(TASKS_REGISTRY_FILENAME, "a");

  fprintf(file, "\n%s,%d", task.name, task.completed);
  fclose(file);

  return;
}

int doesTasksRegistryExist() {
  if (access(TASKS_REGISTRY_FILENAME, F_OK) == 0) {
    return TRUE;
  }

  return FALSE;
}

int isTasksRegistryEmpty() {
  FILE *file;
  file = fopen(TASKS_REGISTRY_FILENAME, "r");
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

void addTask(int taskNameLength, char taskName[taskNameLength]) {
  if (doesTasksRegistryExist() != 1) {
    createCSVFile();
  }

  Task newTask;
  strcpy(newTask.name, taskName);
  newTask.completed = 0;

  writeTaskToFile(newTask);
  printf("Task %s added\n", taskName);

  return;
}

int getOperationFromCmd(int operationStrLength,
                        char operationStr[operationStrLength]) {
  if (strcmp(operationStr, "add") == 0) {
    return Add;
  } else if (strcmp(operationStr, "remove") == 0) {
    return Remove;
  } else if (strcmp(operationStr, "list") == 0) {
    return List;
  } else if (strcmp(operationStr, "complete") == 0) {
    return Complete;
  }

  return ERROR_INVALID_OPERATION;
}

int getNumberOfArgs(int argc, int operation) {
  int correctArgsNumber;

  if (operation == List) {
    correctArgsNumber = CORRECT_LISTAGE_ARGUMENTS_NUMBER;
  } else {
    correctArgsNumber = CORRECT_MANIPULATION_ARGUMENTS_NUMBER;
  }

  if (argc != correctArgsNumber) {
    return ERROR_INVALID_NUMBER_OF_ARGS;
  } else {
    return 0;
  }
}

int listTasks() {
  if (isTasksRegistryEmpty() == ERROR_INVALID_TASKS_REGISTRY) {
    return ERROR_INVALID_TASKS_REGISTRY;
  }
  if (isTasksRegistryEmpty() == TRUE || doesTasksRegistryExist() == FALSE) {
    printf("No tasks to be listed\n");
    return 0;
  } else {
    printf("To be implemented\n");
    /* implementation */

    return 0;
  }
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr,
            "ERROR_INVALID_NUMBER_OF_ARGS: this program must be executed on "
            "the following form: todox list or todox [operation] [taskName]\n");
    return ERROR_INVALID_NUMBER_OF_ARGS;
  }

  int operationCmdLength = ARRAY_LENGTH(argv[1]);
  char operationCmd[operationCmdLength];
  strcpy(operationCmd, argv[1]);
  int operation = getOperationFromCmd(operationCmdLength, operationCmd);

  int numberOfArgs = getNumberOfArgs(argc, operation);
  if (numberOfArgs == ERROR_INVALID_NUMBER_OF_ARGS) {
    fprintf(stderr,
            "ERROR_INVALID_NUMBER_OF_ARGS: this program must be executed on "
            "the following form: todox list or todox [operation] [taskName]\n");
    return ERROR_INVALID_NUMBER_OF_ARGS;
  }

  switch (operation) {
  case Add: {
    char taskNameLength = ARRAY_LENGTH(argv[1]);
    char taskName[taskNameLength];
    strcpy(taskName, argv[2]);

    addTask(taskNameLength, taskName);
    break;
  }
  case Remove:
    printf("To be implemented\n");
    break;
  case List:
    if (listTasks() == ERROR_INVALID_TASKS_REGISTRY) {
      fprintf(stderr,
              "ERROR_INVALID_TASKS_REGISTRY: invalid tasks registry format.\n");
      return 1;
    }
    break;
  case Complete:
    printf("To be implemented\n");
    break;
  default:
    fprintf(stderr, "ERROR_INVALID_OPERATION: operations supported are: add, "
                    "remove, list or complete\n");
    return 1;
  }

  return 0;
}
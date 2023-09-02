#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORRECT_ARGUMENTS_NUMBER 3
#define MAX_TASKS 100
#define MAX_TASKS_NAME_LENGTH 1000
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

// Error codes
#define ERROR_INVALID_NUMBER_OF_ARGS -1
#define ERROR_INVALID_OPERATION -2

typedef struct {
  char name[MAX_TASKS_NAME_LENGTH];
  int completed;
} Task;

enum Operations { Add, Remove, List, Complete };

Task tasks[MAX_TASKS];
int numTasks = 0;

void addTask(int taskNameLength, char taskName[taskNameLength]) {
  if (numTasks >= MAX_TASKS) {
    printf("Task addition failed: maximum number of tasks (%d) reached\n",
           MAX_TASKS);
    return;
  }

  Task newTask;
  strcpy(newTask.name, taskName);
  newTask.completed = 0;

  tasks[numTasks++] = newTask;
  printf("Task %s added\n", taskName);

  printf("Tasks:\n");
  for (int i = 0; i < numTasks; ++i) {
    printf("%s\n", tasks[i].name);
  }

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

int getNumberOfArgs(int argc) {
  if (argc != CORRECT_ARGUMENTS_NUMBER) {
    return ERROR_INVALID_NUMBER_OF_ARGS;
  } else {
    return 0;
  }
}

int main(int argc, char *argv[]) {
  int numberOfArgs = getNumberOfArgs(argc);
  if (numberOfArgs == ERROR_INVALID_NUMBER_OF_ARGS) {
    fprintf(stderr,
            "ERROR_INVALID_NUMBER_OF_ARGS: this program must be executed on "
            "the following form: todox [operation] [taskName]\n");
    return ERROR_INVALID_NUMBER_OF_ARGS;
  }

  int operationCmdLength = ARRAY_LENGTH(argv[1]);
  char operationCmd[operationCmdLength];
  strcpy(operationCmd, argv[1]);

  int operation = getOperationFromCmd(operationCmdLength, operationCmd);

  char taskNameLength = ARRAY_LENGTH(argv[1]);
  char taskName[taskNameLength];
  strcpy(taskName, argv[2]);

  switch (operation) {
  case Add:
    addTask(taskNameLength, taskName);
    break;
  case Remove:
    printf("To be implemented\n");
    break;
  case List:
    printf("To be implemented\n");
    break;
  case Complete:
    printf("To be implemented\n");
    break;
  default:
    fprintf(stderr, "ERROR_INVALID_OPERATION: operations supported are: add, "
                    "remove, list or complete\n");
    return ERROR_INVALID_OPERATION;
  }

  return 0;
}
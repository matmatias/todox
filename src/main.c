#include "globals.h"

#include "add.h"
#include "list.h"
#include <stdio.h>
#include <string.h>

enum Operations { Add, Complete, Remove, ListAll, ListPending, ListCompleted };

int getOperationFromCmd(int operationStrLength,
                        char operationStr[operationStrLength]) {
  if (strcmp(operationStr, "add") == 0) {
    return Add;
  } else if (strcmp(operationStr, "remove") == 0) {
    return Remove;
  } else if (strcmp(operationStr, "list-all") == 0) {
    return ListAll;
  } else if (strcmp(operationStr, "complete") == 0) {
    return Complete;
  } else if (strcmp(operationStr, "list") == 0) {
    return ListPending;
  } else if (strcmp(operationStr, "list-completed") == 0) {
    return ListCompleted;
  }

  return ERROR_INVALID_OPERATION;
}

int getNumberOfArgs(int argc, int operation) {
  int correctArgsNumber;

  if (operation == ListAll || operation == ListPending ||
      operation == ListCompleted) {
    correctArgsNumber = CORRECT_LISTAGE_ARGUMENTS_NUMBER;
  } else if (operation == Remove || operation == Complete || operation == Add) {
    correctArgsNumber = CORRECT_MANIPULATION_ARGUMENTS_NUMBER;
  }

  if (argc != correctArgsNumber) {
    return ERROR_INVALID_NUMBER_OF_ARGS;
  } else {
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

  int operationCmdLength = strlen(argv[1]);
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
    char taskNameLength = strlen(argv[1]);
    char taskName[taskNameLength];
    strcpy(taskName, argv[2]);

    addTask(taskNameLength, taskName);
    break;
  }
  case Remove:
    printf("To be implemented\n");
    break;
  case ListAll:
    if (listTasks() == ERROR_INVALID_TASKS_REGISTRY) {
      fprintf(stderr,
              "ERROR_INVALID_TASKS_REGISTRY: invalid tasks registry format.\n");
      return 1;
    }
    break;
  case ListPending:
    if (listPendingTasks() == ERROR_INVALID_TASKS_REGISTRY) {
      fprintf(stderr,
              "ERROR_INVALID_TASKS_REGISTRY: invalid tasks registry format.\n");
      return 1;
    }
    break;
  case ListCompleted:
    if (listCompletedTasks() == ERROR_INVALID_TASKS_REGISTRY) {
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
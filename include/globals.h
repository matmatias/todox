#ifndef GLOBALS_H
#define GLOBALS_H

#define TRUE 1
#define FALSE 0

#define CORRECT_MANIPULATION_ARGUMENTS_NUMBER 3
#define CORRECT_LISTAGE_ARGUMENTS_NUMBER 2

#define MAX_TASKS 100
#define MAX_TASKS_NAME_LENGTH 1000
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define TASKS_REGISTRY_NAME ".tasks_registry.csv"
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

#endif
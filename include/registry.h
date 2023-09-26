#ifndef REGISTRY_H
#define REGISTRY_H

#include "globals.h"
#include <stdio.h>

void createCSVFile(void);
void writeTaskToFile(Task task);
bool getDoesTasksRegistryExist(void);
bool getIsTasksRegistryEmpty(void);
bool get_is_tasks_registry_populated(void);
int readHeader(FILE *taskRegistry);
int parseRegistry(FILE *taskRegistry, Task *out_tasks[], int *out_tasksLen);
void changeCompleteInRegistry(FILE *taskRegistry, char searchedTask[],
                             bool isCompleted);
int purge_registry();
char *get_tasks_registry_full_path();

#endif

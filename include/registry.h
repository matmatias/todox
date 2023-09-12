#ifndef REGISTRY_H
#define REGISTRY_H

#include "globals.h"
#include <stdio.h>

void createCSVFile();
void writeTaskToFile(Task task);
int getDoesTasksRegistryExist();
int getIsTasksRegistryEmpty();

#endif
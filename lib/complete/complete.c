#include "registry.h"

int complete_task(char task_name[]) {
  FILE *taskRegistry = fopen(TASKS_REGISTRY_NAME, "r");
  readHeader(taskRegistry);

  return changeCompleteInRegistry(taskRegistry, task_name, true);
}
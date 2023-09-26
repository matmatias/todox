#include "registry.h"
#include <stdlib.h>

void complete_task(char task_name[]) {
  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *taskRegistry = fopen(tasks_registry_full_path, "r");
  free(tasks_registry_full_path);

  const bool is_tasks_registry_populated = get_is_tasks_registry_populated();
  if (is_tasks_registry_populated == false) {
    printf("There are no tasks to be completed\n");
    return;
  }

  readHeader(taskRegistry);
  changeCompleteInRegistry(taskRegistry, task_name, true);
  printf("Task: \"%s\" marked as completed.\n", task_name);
}

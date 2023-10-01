#include "registry.h"
#include <stdlib.h>

void remove_task(char task_name[]) {
  char *tasks_registry_full_path = get_tasks_registry_full_path();
  FILE *taskRegistry = fopen(tasks_registry_full_path, "r");
  free(tasks_registry_full_path);

  const bool is_tasks_registry_populated = get_is_tasks_registry_populated();
  if (is_tasks_registry_populated == false) {
    printf("There are no tasks to be completed\n");
    return;
  }

  readHeader(taskRegistry);

  bool was_task_removed = remove_task_from_registry(taskRegistry, task_name);

  if (was_task_removed == true) {
    printf("Task: \"%s\" removed.\n", task_name);
    return;
  }

  printf("No Task named \"%s\" was found to be removed.\n", task_name);
}

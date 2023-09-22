# TodoX (WORK IN PROGRESS)

## About

This is a terminal todo list tracker written in C.

## Dependencies
- A C compiler
- [make](https://www.gnu.org/software/make/)
- [cmake](https://cmake.org/)

## Setup
Create the build directory. From the root of the project, run:
```bash
mkdir build
```

## Features

### Done

The following features are done:

1. Add new tasks
2. Persist tasks in the system
3. List all tasks
4. List completed tasks
5. List pending tasks
6. Mark tasks as completed

### Work in Progress:

The following features are being worked on:

1. Remove tasks
2. Purge all tasks

## Compiling

From the project's root directory, run:

```bash
cmake -S . -B build
mv ./build/compile_commands.json ./compile_commands.json
make -C build
```

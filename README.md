# TodoX

## About

This is a terminal todo list tracker written in C.

## Usage
```bash
todox [command] [task]?
```

### \[command\]:

1. **list**: list pending tasks
2. **list-all**: list pending and completed tasks
3. **list-completed**: list completed tasks
4. **purge**: remove all tasks
5. **add** [task]: add pending task
6. **complete** [task]: mark [task] as completed

### \[task\]

String of 999 characters maximum.

## Dependencies
- A C compiler
- [make](https://www.gnu.org/software/make/)
- [cmake](https://cmake.org/)

## Install
You can get the todox binaries from the latest release.

**IMPORTANT**: these binaries are for amd64 archtecture only!

- To install as a .deb package, run:
```bash
sudo dpkg -i todox_1.0_amd64.deb
```

- Or you can just download the raw binary and put it in /usr/bin.

## Uninstalling
- To uninstall as a .deb package, run:
```bash
sudo apt uninstall todox
```

- To uninstall as a raw binary, run:
```bash
sudo rm /usr/bin/todox
```

## Setup
Create the build directory. From the root of the project, run:

```bash
mkdir build
cmake -S . -B build
mv ./build/compile_commands.json ./compile_commands.json
```

This might be necessary to get code completion/snippets.

## Features

The following features are done:

1. Add new tasks
2. Persist tasks in the system
3. List all tasks
4. List completed tasks
5. List pending tasks
6. Mark tasks as completed
7. Purge all tasks
8. Remove specific tasks

## Compiling

From the project's root directory, run:

```bash
cmake -S . -B build
mv ./build/compile_commands.json ./compile_commands.json
make -C build
```

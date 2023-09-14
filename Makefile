build:
	gcc main.c -o todox

build_dev:
	gcc -g -I./include src/main.c lib/registry.c lib/add/add.c lib/list/list.c -o build/todox

run_list_all:
	./build/todox list-all

run_list:
	./build/todox list

run_list_completed:
	./build/todox list-completed
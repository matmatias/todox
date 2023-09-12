build:
	gcc main.c -o todox

build_dev:
	gcc -g -I./include src/main.c lib/registry.c lib/add/add.c lib/list/list.c -o todox

run_list:
	./todox list
all: sem.c
	gcc -o sem sem.c
run: all
	./sem -c 4
	./sem -v
	./sem -c 3
	./sem -v
	./sem -r

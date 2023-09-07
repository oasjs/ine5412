build:
	g++ src/main.cpp -o bin/scheduler

default-run:
	./bin/scheduler src/entrada.txt 1

default-all: build default-run
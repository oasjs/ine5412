# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra
DEBUG = -DDEBUG

SRCS = ./src/main.cpp
TARGET = scheduler
INPUT = entrada.txt

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

debug-build: $(SRCS)
	$(CC) $(CFLAGS) $(DEBUG) $(SRCS) -o $(TARGET)

default-run:
	./$(TARGET) $(INPUT)

fcfs-run:
	./$(TARGET) $(INPUT) 1

stf-run:
	./$(TARGET) $(INPUT) 2

pnp-run:
	./$(TARGET) $(INPUT) 3

pwp-run:
	./$(TARGET) $(INPUT) 4

rr-run:
	./$(TARGET) $(INPUT) 5 $(QUANTUM)

default-all: build default-run

clean:
	rm -f $(TARGET)
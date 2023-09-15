# Compiler and flags
CC = g++
CFLAGS = -Wall -Wextra
DEBUG = -DDEBUG

SRCS = src/main.cpp
TARGET = bin/scheduler
INPUT = inputs/input.txt
SRCS_INPUT_GENERATOR = src/input_generator.cpp
TARGER_INPUT_GENERATOR = bin/input_generator

all: check-args build-input-generator run-input-generator build run-default

all-default: ARGS := 5 10 4 5
all-default: check-args build-input-generator run-input-generator build run-default

build: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

debug-build: $(SRCS)
	$(CC) $(CFLAGS) $(DEBUG) $(SRCS) -o $(TARGET)

run-default:
	./$(TARGET) $(INPUT)

run-fcfs:
	./$(TARGET) $(INPUT) 1

run-sjf:
	./$(TARGET) $(INPUT) 2

run-pnp:
	./$(TARGET) $(INPUT) 3

run-pwp:
	./$(TARGET) $(INPUT) 4

run-rr:
	./$(TARGET) $(INPUT) 5 $(QUANTUM)

check-args:
	@if [ -z "$(ARGS)" ]; then \
        echo "ARGS is not set. Please pass arguments when calling make, e.g.,"; \
		echo "make ARGS=\"<number_of_processes> <max_creation_time> <max_duration> <max_priority>\" \n"; \
        exit 1; \
    fi

build-input-generator: 
	$(CC) $(CFLAGS) $(SRCS_INPUT_GENERATOR) -o ./$(TARGER_INPUT_GENERATOR) 

run-input-generator: check-args
	./$(TARGER_INPUT_GENERATOR) $(ARGS)
	mv input.txt inputs/

clean:
	rm -f bin/*
	rm -f inputs/*
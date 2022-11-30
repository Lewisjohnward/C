CC = gcc
CFLAGS = #-Wall -Werror -Wpedantic
TARGET = server

all: $(TARGET) run

$(TARGET): main.c
	$(CC) $(CFLAGS) -o server main.c server.c

run:
	./server 8080

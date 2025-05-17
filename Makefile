CC = gcc
CFLAGS = -Wall -g -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)


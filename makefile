# Makefile for building myshell
CC = gcc
CFLAGS = -Wall -Werror -g
SRCS = main.c path.c
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = myshell

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
.PHONY: all clean
clean:
	rm -f $(OBJS) $(TARGET)

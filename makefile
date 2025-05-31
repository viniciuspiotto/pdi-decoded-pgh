CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinclude

SRCS = decode.c include/imagelib.c include/huffman.c include/descompact.c
OBJS = $(SRCS:.c=.o)

TARGET = decode

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
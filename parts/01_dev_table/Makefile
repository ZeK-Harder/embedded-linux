CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = ../../bin/step4

$(TARGET): dev_table.c main.c dev_table.h
	$(CC) $(CFLAGS) main.c dev_table.c -o $@

clean:
	rm -f $(TARGET)

.PHONY: clean
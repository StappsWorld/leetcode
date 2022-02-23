# A simple Makefile
# Samuel Rembisz 

CC = gcc
CFLAGS = -g -Wall -ggdb3 -pedantic-errors
LIBS = -lm

TARGET = solution

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	 rm $(TARGET)

# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
TARGET = hello_world
CC = g++
CFLAGS = -Wall -g -std=c++11
# ****************************************************
# Targets needed to bring the executable up to date
 
hello_world: hello_world.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o
 
# The hello_world.o target can be written more simply
 
$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

clean:
	$(RM) $(TARGET) $(TARGET).o

# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
TARGET = test_proc_1
CC = g++
CFLAGS = -Wall -g -std=c++11
# ****************************************************
# Targets needed to bring the executable up to date
 
test_proc_1: test_proc_1.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o
 
# The test_proc_1.o target can be written more simply
 
$(TARGET).o: $(TARGET).cpp
	$(CC) $(CFLAGS) -c $(TARGET).cpp

clean:
	$(RM) $(TARGET) $(TARGET).o

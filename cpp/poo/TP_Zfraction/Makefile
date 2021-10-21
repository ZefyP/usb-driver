# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o ZFraction.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o ZFraction.o
	
# The main.o target can be written more simply

$(TARGET).o: $(TARGET).cpp ZFraction.o
	$(CC) $(CFLAGS) -c $(TARGET).cpp

ZFraction.o: ZFraction.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) ZFraction.o

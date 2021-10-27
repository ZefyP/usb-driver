# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Duree.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o Duree.o
	
# The main.o target can be written more simply

$(TARGET).o: $(TARGET).cpp Duree.o
	$(CC) $(CFLAGS) -c $(TARGET).cpp

Duree.o: Duree.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) Duree.o

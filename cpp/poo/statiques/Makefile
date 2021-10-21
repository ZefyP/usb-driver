# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g
# ****************************************************
# Targets needed to bring the executable up to date

main: main.o MaClasse.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o MaClasse.o
	
# The main.o target can be written more simply

$(TARGET).o: $(TARGET).cpp MaClasse.o
	$(CC) $(CFLAGS) -c $(TARGET).cpp

MaClasse.o: MaClasse.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) MaClasse.o

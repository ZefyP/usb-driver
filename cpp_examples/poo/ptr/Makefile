# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o Personnage.o Arme.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o Personnage.o Arme.o
 
# The main.o target can be written more simply
 
$(TARGET).o: $(TARGET).cpp Personnage.h Arme.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

Personnage.o: Personnage.h

Arme.o: Arme.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) Personnage.o
	$(RM) Arme.o
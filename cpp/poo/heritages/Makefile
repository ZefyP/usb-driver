# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o Personnage.o Guerrier.o Magicien.o Arme.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o Personnage.o Guerrier.o Magicien.o Arme.o
 
# The main.o target can be written more simply
 
$(TARGET).o: $(TARGET).cpp Personnage.h Guerrier.h Magicien.h Arme.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

Personnage.o: Personnage.h

Arme.o: Arme.h

Guerrier.o: Guerrier.h

Magicien.o: Magicien.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) Personnage.o
	$(RM) Arme.o
	$(RM) Guerrier.o
	$(RM) Magicien.o
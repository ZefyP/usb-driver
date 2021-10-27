# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
TARGET = main
CC = g++
CFLAGS = -Wall -g 
# ****************************************************
# Targets needed to bring the executable up to date
 
main: main.o Garage.o Vehicule.o Voiture.o Moto.o Camion.o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o Garage.o Vehicule.o Voiture.o Moto.o Camion.o
 
# The main.o target can be written more simply
 
$(TARGET).o: $(TARGET).cpp Garage.h Vehicule.h Voiture.h Moto.h Camion.h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

Garage.o: Garage.h

Vehicule.o: Vehicule.h

Voiture.o: Voiture.h

Moto.o: Moto.h

Camion.o: Camion.h

clean:
	$(RM) $(TARGET) $(TARGET).o
	$(RM) Garage.o
	$(RM) Vehicule.o
	$(RM) Voiture.o
	$(RM) Moto.o
	$(RM) Camion.o

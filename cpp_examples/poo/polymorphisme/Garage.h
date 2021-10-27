#ifndef GARAGE_H_INCLUDED
#define GARAGE_H_INCLUDED
#include <string>
#include <iostream>
#include "Vehicule.h"
#include "Moto.h"
#include "Voiture.h"
#include "Camion.h"
#include <vector>
class Garage{
    public:
    Garage();
    void affiche() const;  //Affiche une description du Garage
    void add(Vehicule *v);
    void remove(Vehicule *v);
    void remove(int emplacement);
    ~Garage();
    private:
    std::vector<Vehicule*> m_listeVehicules;
};
#endif
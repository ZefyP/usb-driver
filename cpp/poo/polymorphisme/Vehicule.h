#ifndef VEHICULE_H_INCLUDED
#define VEHICULE_H_INCLUDED
#include <string>
#include <iostream>
class Vehicule{
    public:
    Vehicule();
    virtual void affiche() const;  //Affiche une description du Vehicule
    virtual std::string type() const = 0;
    virtual int nbRoue() const = 0;
    virtual ~Vehicule();
    protected:
    int m_prix;  //Chaque véhicule a un prix
};
#endif
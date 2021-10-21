#ifndef MOTO_H_INCLUDED
#define MOTO_H_INCLUDED
#include "Vehicule.h"

class Moto : public Vehicule  //Une Moto EST UN Vehicule
{
    public:
    Moto();
    virtual void affiche() const;
    virtual ~Moto();
    virtual int nbRoue() const;
    virtual std::string type() const;
    private:
    double m_vitesse;  //La vitesse maximale de la moto
};
#endif
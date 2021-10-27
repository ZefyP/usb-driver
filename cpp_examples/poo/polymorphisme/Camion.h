#ifndef CAMION_H_INCLUDED
#define CAMION_H_INCLUDED
#include "Vehicule.h"

class Camion : public Vehicule  //Une Moto EST UN Vehicule
{
    public:
    Camion();
    virtual void affiche() const;
    virtual ~Camion();
    virtual int nbRoue() const;
    virtual std::string type() const;
    private:
    double m_poid;  //La charge max du camion
};
#endif
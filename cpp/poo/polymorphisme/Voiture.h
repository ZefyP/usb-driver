#ifndef VOITURE_H_INCLUDED
#define VOITURE_H_INCLUDED
#include "Vehicule.h"
class Voiture : public Vehicule //Une Voiture EST UN Vehicule
{
    public:
    Voiture();
    virtual void affiche() const;
    virtual std::string type() const;
    virtual ~Voiture();
    virtual int nbRoue() const;
    private:
    int m_portes;  //Le nombre de portes de la voiture
};
#endif
#ifndef MAGICIEN_H_INCLUDED
#define MAGICIEN_H_INCLUDED
#include <iostream>
#include <string>
#include "Personnage.h"
 
class Magicien : public Personnage{
    private:
        int m_mana;
    
    public:
        Magicien();
        Magicien(std::string nom);
        void bouleDeFeu() const;
        void bouleDeGlace() const;
};
#endif
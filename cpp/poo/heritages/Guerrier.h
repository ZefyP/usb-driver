#ifndef GUERRIER_H_INCLUDED
#define GUERRIER_H_INCLUDED
#include <iostream>
#include <string>
#include "Personnage.h"
 
class Guerrier : public Personnage{
    private:

    public:
    Guerrier();
    Guerrier(std::string nom);
    void sePresenter() const;
    void frapperCommeUnSourdAvecUnMarteau() const;
};
#endif
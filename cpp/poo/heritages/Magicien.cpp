#include "Magicien.h"
using namespace std;

//Obligation d'appeler le constructeur de la classe mère au format de la liste d'initialisation :'(
Magicien::Magicien() : Personnage(){

}

Magicien::Magicien(string nom) : Personnage(nom){
    
}

void Magicien::bouleDeFeu() const{
    
}

void Magicien::bouleDeGlace() const{
    
}
#include "Guerrier.h"
using namespace std;

//Obligation d'appeler le constructeur de la classe mère au format de la liste d'initialisation :'(
Guerrier::Guerrier() : Personnage(){

}

Guerrier::Guerrier(string nom) : Personnage(nom){
    
}

void Guerrier::frapperCommeUnSourdAvecUnMarteau() const{

}

void Guerrier::sePresenter() const{
    Personnage::sePresenter();
    cout << "Je suis un Guerrier redoutable." << endl;
}
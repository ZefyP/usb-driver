#include "Vehicule.h"
using namespace std;

Vehicule::Vehicule(){
    m_prix = 0;
}

void Vehicule::affiche() const{
    cout << "Ceci est un vehicule." << endl;
}

Vehicule::~Vehicule(){
    cout << "Destructeur de Vehicule" << endl;
}
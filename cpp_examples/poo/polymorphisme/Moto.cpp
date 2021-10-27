#include "Moto.h"
using namespace std;

Moto::Moto(){
    m_vitesse = 0;
}

void Moto::affiche() const{
    cout << "Ceci est une moto." << endl;
}
int Moto::nbRoue() const{
    return 2;
}
string Moto::type() const{
    return "moto";
}
Moto::~Moto(){
    cout << "Destructeur de Moto" << endl;
}
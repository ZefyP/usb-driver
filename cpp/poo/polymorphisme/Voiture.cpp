#include "Voiture.h"
using namespace std;

Voiture::Voiture(){
    m_portes = 0;
}

void Voiture::affiche() const{
    cout << "Ceci est une voiture." << endl;
}
int Voiture::nbRoue() const{
    return 4;
}
string Voiture::type() const{
    return "voiture";
}
Voiture::~Voiture(){
    cout << "Destructeur de voiture" << endl;
}
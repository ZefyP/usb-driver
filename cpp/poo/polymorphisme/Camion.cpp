#include "Camion.h"
using namespace std;

Camion::Camion(){
    m_poid = 0;
}

void Camion::affiche() const{
    cout << "Ceci est un camion." << endl;
}
int Camion::nbRoue() const{
    return 8;
}
string Camion::type() const{
    return "camion";
}
Camion::~Camion(){
    cout << "Destructeur de Camion" << endl;
}
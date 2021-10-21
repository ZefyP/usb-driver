#include "Garage.h"
using namespace std;

Garage::Garage(){
    m_listeVehicules.clear();
}

void Garage::affiche() const{
    cout << "Ceci est un Garage." << endl;
    for (size_t i = 0; i < m_listeVehicules.size(); i++){
        m_listeVehicules[i]->affiche();
    }
}

void Garage::add(Vehicule *v){
    cout << "Ajout de " << v->type() << endl;
    m_listeVehicules.push_back(v);
}

void Garage::remove(Vehicule *v){
    int index=0;
    for (size_t i = 0; i < m_listeVehicules.size(); i++){
        if (m_listeVehicules[i] == v){
            index = i;
            delete m_listeVehicules[i];
            break;
        }
    }
    
    m_listeVehicules.erase(m_listeVehicules.begin()+index);
}

void Garage::remove(int emplacement){
    int index=0;
    if (m_listeVehicules.size() > emplacement){
        delete m_listeVehicules[emplacement];
        m_listeVehicules[emplacement] = 0;
        m_listeVehicules.erase(m_listeVehicules.begin()+emplacement);
    }
}

Garage::~Garage(){
    cout << "Destructeur de Garage" << endl;
    for (size_t i = 0; i < m_listeVehicules.size(); i++){
        delete m_listeVehicules[i];
        m_listeVehicules[i] = 0;
    }
    m_listeVehicules.clear();
}
#include "Arme.h"
using namespace std;

//Construtcteur
Arme::Arme(){
    m_nom = "Poings";
    m_degats = 1;
}
Arme::Arme(string nom,int degats){
    m_nom = nom;
    m_degats = degats;
}

//Destructeur
Arme::~Arme(){

}

//Methodes Membres
int Arme::getDegats() const{
    return m_degats;
}

void Arme::changer(std::string nom, int degats){
    m_nom = nom;
    m_degats = degats;
}

void Arme::afficher() const{
    cout << "Arme : " << m_nom << " (Dégâts : " << m_degats << ")" << endl << endl;
}

string Arme::get_nom() const{
    return m_nom;
}
#include "Personnage.h"
 
using namespace std;
 
Personnage::Personnage(){
    m_nom = "Jack";
    m_vie = 100;
}
Personnage::Personnage(string nom){
    m_nom = nom;
    m_vie = 100;
}

void Personnage::recevoirDegats(int degats){
    m_vie -= degats;
}
 
void Personnage::coupDePoing(Personnage &cible) const{
    cible.recevoirDegats(10);
}

void Personnage::afficher(ostream &flux) const{
    flux << m_nom;
}

void Personnage::sePresenter() const{
    cout << "Bonjour, je m'appelle " << m_nom << "." << endl;
    cout << "J'ai encore " << m_vie << " points de vie." << endl;
}


ostream &operator<<(ostream &flux, Personnage const &p){
    p.afficher(flux);

    return flux;
}
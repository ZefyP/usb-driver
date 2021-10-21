#include "Personnage.h"
using namespace std;

//Construtcteur
Personnage::Personnage(){
    m_vie = 100;
    m_mana = 100;
    m_nom = "noname";
}

Personnage::Personnage(string nom_arme, int degat_arme){
    m_vie = 100;
    m_mana = 100;
    changerArme(nom_arme,degat_arme);
}

Personnage::Personnage(Arme arme){
    m_vie = 100;
    m_mana = 100;
    m_arme = arme;
}

Personnage::Personnage(string nom){
    m_vie = 100;
    m_mana = 100;
    m_nom = nom;
}
//Destructeur
Personnage::~Personnage(){

}
//Methodes Membres
int Personnage::recevoirDegats(int const degats){
    m_vie-=degats;
    
    if (m_vie < 0){
        m_vie = 0;
    }
    cout << m_nom << " recoit " << degats << " de dégats, il lui reste " << m_vie << " pdv."<< endl;
    return 0;
}

int Personnage::attaquer(Personnage &cible){
    cout << m_nom << " attaque " << cible.get_nom() << " avec " << m_arme.get_nom() << "." << endl;
    cible.recevoirDegats(m_arme.getDegats());
    return 0;
}

int Personnage::seSoigner(int const qte){
    m_vie += qte;
    if (m_vie > 100){
        m_vie = 100;
    }
    cout << m_nom << " se soigne avec une potion (" << qte << "), il à maintenant " << m_vie << " pdv." << endl;
    return 0;
}

int Personnage::changerArme(string const nom, int const degats){
    cout << m_nom << " équipe " << nom  << " (Dégâts : " << degats << ")" << endl;
    m_arme.changer(nom,degats);
    return 0;
}

bool Personnage::estVivant() const{
    return m_vie > 0;
}

string Personnage::get_nom() const{
    return m_nom;
}

void Personnage::set_nom(string nom){
    m_nom = nom;
}

void Personnage::afficherEtat() const
{
    cout << m_nom << " :"<< endl;
    cout << "Vie : " << m_vie << endl;
    cout << "Mana : " << m_mana << endl;
    m_arme.afficher();
}

int Personnage::get_degats() const{
    return m_arme.getDegats();
}
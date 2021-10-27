#include "Personnage.h"
using namespace std;

//Construtcteur
Personnage::Personnage(){
    m_vie = 100;
    m_mana = 100;
    m_nom = "noname";
    m_arme = new Arme();
}

Personnage::Personnage(string nom_arme, int degat_arme){
    m_vie = 100;
    m_mana = 100;
    m_nom = "noname";
    m_arme = new Arme(nom_arme,degat_arme);
    //changerArme(nom_arme,degat_arme);
}

Personnage::Personnage(Arme arme){
    m_vie = 100;
    m_mana = 100;
    m_nom = "noname";
    m_arme = new Arme(arme);
}

Personnage::Personnage(string nom){
    m_vie = 100;
    m_mana = 100;
    m_nom = nom;
    m_arme = new Arme();
}

Personnage::Personnage(Personnage const &personnageACopier){
    m_vie = personnageACopier.m_vie;
    m_mana = personnageACopier.m_mana;
    m_nom = personnageACopier.m_nom;
    m_arme = new Arme(*personnageACopier.m_arme);
}
//Destructeur
Personnage::~Personnage(){
    delete m_arme;
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
    cout << m_nom << " attaque " << cible.get_nom() << " avec " << m_arme->get_nom() << "." << endl;
    cible.recevoirDegats(m_arme->getDegats());
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
    m_arme->changer(nom,degats);
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
    m_arme->afficher();
}

int Personnage::get_degats() const{
    return m_arme->getDegats();
}

//Operateurs

Personnage& Personnage::operator=(Personnage const &autre){
    if (&autre != this){
        m_vie = autre.m_vie;
        m_mana = autre.m_mana;
        m_nom = autre.m_nom;
        delete m_arme;
        m_arme = new Arme(*autre.m_arme);
    }

    return *this;
}
#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
#include "Arme.h"
class Personnage
{
    private:
    //Attributs membres
    int m_vie;
    int m_mana;
    Arme *m_arme;
    std::string m_nom;
    
    public:
    // Constructeurs
    Personnage();
    Personnage(Arme arme);
    Personnage(std::string nom_arme, int degat_arme);
    Personnage(std::string nom);
    //copy
    Personnage(Personnage const &personnageACopier);

    //Destructeur
    ~Personnage();

    //Methodes membres
    int recevoirDegats(int const degats);
    int attaquer(Personnage &cible);
    int seSoigner(int const qte);
    int get_degats() const;
    int changerArme(std::string const nom, int const degats);
    bool estVivant() const;
    void set_nom(std::string nom);
    std::string get_nom() const;
    void afficherEtat() const;
    Personnage& operator=(Personnage const &autre);
};
#endif
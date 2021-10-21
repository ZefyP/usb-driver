#ifndef DEF_ARME
#define DEF_ARME
#include <string>
#include <iostream>
class Arme
{
    private:
    //Attributs membres
    std::string m_nom;
    int m_degats;


    public:
    // Constructeurs
    Arme();
    Arme(std::string nomArme, int degatsArme);

    //Destructeur
    ~Arme();

    //Methodes membres
    int getDegats() const;
    void changer(std::string nom, int degats);
    void afficher() const;
    std::string get_nom() const;
};
#endif
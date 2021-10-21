#ifndef DEF_PERSONNAGE
#define DEF_PERSONNAGE
 
#include <iostream>
#include <string>
 
class Personnage
{
    public:
        Personnage();
        Personnage(std::string nom);
        void recevoirDegats(int degats);
        void coupDePoing(Personnage &cible) const;
        void afficher(std::ostream &flux) const;
        void sePresenter() const;
    protected:
        int m_vie;
        std::string m_nom;
    private:
};

std::ostream &operator<<(std::ostream &flux, Personnage const &p);

#endif

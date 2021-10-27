#ifndef DUREE_H_INCLUDED
#define DUREE_H_INCLUDED
#include <string>
#include <iostream>
class Duree
{
    private:
    int m_hours;
    int m_minutes;
    int m_seconds;


    public:
    //Constructeurs
    Duree(int heures=0, int minutes=0, int secondes=0);

    //Destructeur
    ~Duree();

    //Methodes membres
    //void afficher();
    void afficher(std::ostream &flux) const;
    bool estEgal(Duree const &d) const;
    bool estPlusPetitQue(Duree const &d) const;

    Duree& operator+=(Duree const &a);
    Duree& operator+=(int secondes);

    Duree& operator-=(Duree const &a);
    Duree& operator-=(int secondes);
};

bool operator==(Duree const &a, Duree const &b);
bool operator!=(Duree const &a, Duree const &b);
bool operator<(Duree const &a, Duree const &b);
bool operator>(Duree const &a, Duree const &b);
bool operator<=(Duree const &a, Duree const &b);
bool operator>=(Duree const &a, Duree const &b);

Duree operator+(Duree const &a, Duree const &b);
Duree operator+(Duree const &a, int secondes);

Duree operator-(Duree const &a, Duree const &b);
Duree operator-(Duree const &a, int secondes);
std::ostream &operator<<(std::ostream &flux, Duree const &a);

#endif
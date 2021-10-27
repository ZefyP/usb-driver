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
        void afficher(std::ostream &flux) const;
        friend std::ostream &operator<<(std::ostream &flux, Duree const &a);
        friend bool operator==(Duree const &a, Duree const &b);
        friend bool operator<(Duree const &a, Duree const &b);
    public:
        //Constructeurs
        Duree(int heures=0, int minutes=0, int secondes=0);

        //Destructeur
        ~Duree();

        //Methodes membres
        //void afficher();
        


        Duree& operator+=(Duree const &a);
        Duree& operator+=(int secondes);

        Duree& operator-=(Duree const &a);
        Duree& operator-=(int secondes);
};


bool operator!=(Duree const &a, Duree const &b);

bool operator>(Duree const &a, Duree const &b);
bool operator<=(Duree const &a, Duree const &b);
bool operator>=(Duree const &a, Duree const &b);

Duree operator+(Duree const &a, Duree const &b);
Duree operator+(Duree const &a, int secondes);

Duree operator-(Duree const &a, Duree const &b);
Duree operator-(Duree const &a, int secondes);

#endif
#ifndef ZFRACTION_H_INCLUDED
#define ZFRACTION_H_INCLUDED

#include <ostream>

class ZFraction
{
    private:
    int m_numerator;
    int m_denominator;

    public:
    //Constructeurs
    ZFraction();
    ZFraction(int numerator);
    ZFraction(int numerator, int denominator);

    //Destructeur
    ~ZFraction();

    //Methodes membres
    //void afficher();
    void afficher(std::ostream &flux) const;
    bool estEgal(ZFraction const &d) const;
    bool estPlusPetitQue(ZFraction const &d) const;
    void reduire();
    
    ZFraction& operator+=(ZFraction const &a);
    ZFraction& operator+=(int entier);

    ZFraction& operator*=(ZFraction const &a);
    ZFraction& operator*=(int entier);

    ZFraction& operator-=(ZFraction const &a);
    ZFraction& operator-=(int entier);

//Todo -------------------------------------------------------------
    ZFraction& operator/=(ZFraction const &a);
    ZFraction& operator/=(int entier);
//------------------------------------------------------------------
};
int pgcd(int a, int b);
bool operator==(ZFraction const &a, ZFraction const &b);
bool operator!=(ZFraction const &a, ZFraction const &b);
bool operator<(ZFraction const &a, ZFraction const &b);
bool operator>(ZFraction const &a, ZFraction const &b);
bool operator<=(ZFraction const &a, ZFraction const &b);
bool operator>=(ZFraction const &a, ZFraction const &b);

ZFraction operator+(ZFraction const &a, ZFraction const &b);
ZFraction operator+(ZFraction const &a, int entier);

ZFraction operator*(ZFraction const &a, ZFraction const &b);

ZFraction operator-(ZFraction const &a, ZFraction const &b);
ZFraction operator-(ZFraction const &a, int entier);


std::ostream &operator<<(std::ostream &flux, ZFraction const &a);


//Todo -------------------------------------------------------------
ZFraction operator/(ZFraction const &a, ZFraction const &b);
ZFraction operator/(ZFraction const &a, int entier);
//------------------------------------------------------------------
#endif
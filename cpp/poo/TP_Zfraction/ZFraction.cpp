#include "ZFraction.h"
using namespace std;
//Constructeurs
ZFraction::ZFraction(){
    m_numerator = 0;
    m_denominator = 1;
}

ZFraction::ZFraction(int numerator){
    m_numerator = numerator;
    m_denominator = 1;
}

ZFraction::ZFraction(int numerator, int denominator){
    m_numerator = numerator;
    if(denominator != 0){
        m_denominator = denominator;
        reduire();
    }
    else{
        m_denominator = 1;
    }
    
}

//Destrucuteur
ZFraction::~ZFraction(){
    
}

ZFraction& ZFraction::operator+=(ZFraction const &a){

    m_numerator *= a.m_denominator;
    m_numerator+=a.m_numerator*m_denominator;
    m_denominator*= a.m_denominator;
    this->reduire();
    return *this;
}

ZFraction& ZFraction::operator+=(int entier){
    m_numerator+=entier*m_denominator;
    this->reduire();
    return *this;
}

ZFraction& ZFraction::operator*=(ZFraction const &a){
    m_numerator*=a.m_numerator;
    m_denominator*=a.m_denominator;
    this->reduire();
    return *this;
}
ZFraction& ZFraction::operator*=(int entier){
    m_numerator*=entier;
    this->reduire();
    return *this;
}

ZFraction& ZFraction::operator-=(ZFraction const &a){
    ZFraction inter(a*-1);
    *this+=inter;
    return *this;
}
ZFraction& ZFraction::operator-=(int entier){
    *this+= (entier*-1);
    return *this;
}

void ZFraction::afficher(ostream &flux) const{
    if (m_denominator == 1){
        flux << m_numerator;
    }
    else{
        flux << m_numerator << "/" << m_denominator;
    }
}

bool ZFraction::estEgal(ZFraction const &d) const{
    return m_numerator==d.m_numerator && m_denominator == d.m_denominator;
}

bool ZFraction::estPlusPetitQue(ZFraction const &d) const{
    double me, d_2;
    me = m_numerator/m_denominator;
    d_2 = d.m_numerator/d.m_denominator;

    return me < d_2;
}




ZFraction operator+(ZFraction const &a, ZFraction const &b){
    ZFraction result;
    result = a;
    result += b;
    return result;
}
ZFraction operator+(ZFraction const &a, int entier){
    ZFraction result;
    result = a;
    result += entier;
    return result;
}


ZFraction operator-(ZFraction const &a, ZFraction const &b){
    ZFraction result;
    result = a;
    result -= b;
    return result;
}
ZFraction operator-(ZFraction const &a, int entier){
    ZFraction result;
    result = a;
    result -= entier;
    return result;
}

ZFraction operator*(ZFraction const &a, ZFraction const &b){
    ZFraction result;
    result = a;
    result*=b;
    return result;
}

ZFraction operator*(ZFraction const &a, int entier){
    ZFraction result;
    result = a;
    result *= entier;
    return result;
}

bool operator==(ZFraction const &a, ZFraction const & b)
{
    return a.estEgal(b);
}

bool operator!=(ZFraction const& a, ZFraction const& b)
{
    return !(a==b);
}

bool operator<(ZFraction const &a, ZFraction const &b){
    return a.estPlusPetitQue(b);
}
bool operator>(ZFraction const &a, ZFraction const &b){
    return (!(a < b) && (a!=b));
}

bool operator<=(ZFraction const &a, ZFraction const &b){
    return (a < b || a==b);
}
bool operator>=(ZFraction const &a, ZFraction const &b){
    return (a > b || a==b);
}


int pgcd(int a, int b){
    while (b != 0)
    {
        const int t = b;
        b = a%b;
        a=t;
    }
    return a;
}

void ZFraction::reduire(){
    int pgcd_n;
    pgcd_n = pgcd(m_numerator,m_denominator);
    m_numerator /= pgcd_n;
    m_denominator /= pgcd_n;

    if (m_denominator < 0){
        m_numerator *= -1;
        m_denominator *= -1;
    }
    
}

ostream &operator<<(ostream &flux, ZFraction const &a){
    a.afficher(flux);
    return flux;
}
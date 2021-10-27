#include "Duree.h"
using namespace std;

Duree::Duree(int heures, int minutes, int secondes){
    m_seconds = secondes % 60;
    m_minutes = minutes%60 + secondes/60;
    m_hours = heures + minutes/60;

}

Duree::~Duree(){
}

void Duree::afficher(ostream &flux) const{
    flux << m_hours << "h" << m_minutes << "m" << m_seconds << "s";
    //cout << m_hours << ":" << m_minutes << ":" << m_seconds << endl;
}
bool Duree::estEgal(Duree const &d) const{
    return (m_hours == d.m_hours && m_minutes == d.m_minutes && m_seconds == d.m_seconds);
}

bool Duree::estPlusPetitQue(Duree const &d) const{
    return (m_hours < d.m_hours || (m_hours == d.m_hours && m_minutes < d.m_minutes) || (m_hours == d.m_hours && m_minutes == d.m_minutes && m_seconds < d.m_seconds));
}

Duree& Duree::operator+=(Duree const& a){

    m_hours   += a.m_hours + (m_minutes + a.m_minutes)/60 + (m_seconds + a.m_seconds)/60;

    m_minutes += a.m_minutes + (m_seconds + a.m_seconds)/60;
    m_minutes %=60;

    m_seconds += a.m_seconds;
    m_seconds %=60;

    return *this;
}

Duree& Duree::operator+=(int secondes){
    m_seconds += secondes;
    m_minutes += (m_seconds/60);
    m_seconds %=60;
    m_hours += (m_minutes/60);
    m_minutes %=60;

    return *this;
}

Duree& Duree::operator-=(Duree const &a){


    if(*this < a){
        cout << m_hours << ":" << m_minutes << ":" << m_seconds << " < " << a.m_hours << ":" << a.m_minutes << ":" << a.m_seconds << endl;
        return *this;
    }
    else{
        m_seconds -= a.m_seconds;
        while(m_seconds < 0){
            m_seconds += 60;
            m_minutes -= 1;
        }
        m_minutes -= a.m_minutes;
        while(m_minutes < 0){
            m_minutes += 60;
            m_hours -= 1;
        }
        m_hours -= a.m_hours;
    }
    return *this;
}

Duree& Duree::operator-=(int secondes){
    Duree s(0,0,secondes);
    *this-=s;
    return *this;
}

bool operator==(Duree const &a, Duree const & b)
{
    return a.estEgal(b);
}

bool operator!=(Duree const& a, Duree const& b)
{
    return !(a==b);
}

bool operator<(Duree const &a, Duree const &b){
    return a.estPlusPetitQue(b);
}
bool operator>(Duree const &a, Duree const &b){
    return (!(a < b) && (a!=b));
}

bool operator<=(Duree const &a, Duree const &b){
    return (a < b || a==b);
}
bool operator>=(Duree const &a, Duree const &b){
    return (a > b || a==b);
}

Duree operator+(Duree const &a, Duree const &b){
    Duree result(a);
    result+=b;
    return result;
}

Duree operator+(Duree const &a, int secondes){
    Duree result(a);
    result+=secondes;
    return result;
}

Duree operator-(Duree const &a, Duree const &b){
    Duree result(a);
    result-=b;
    return result;
}

Duree operator-(Duree const &a, int secondes){
    Duree result(a);
    result-=secondes;
    return result;
}

ostream &operator<<(ostream &flux, Duree const &a){
    
    a.afficher(flux);
    //Affichage des attributs
    return flux;
}
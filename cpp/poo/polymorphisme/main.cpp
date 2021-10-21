#include "main.h"

using namespace std;

int main(){
    
    Garage g;
    g.add(new Voiture());
    g.add(new Voiture());
    g.add(new Moto());
    g.remove(2);
    g.affiche();
    return 0;
}

void presenter(Vehicule *v)  //Présente le véhicule passé en argument
{
    v->affiche();
}
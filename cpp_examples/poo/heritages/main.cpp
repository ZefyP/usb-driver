#include "main.h"

using namespace std;
int main(){
    Magicien p1("Joe");
    Guerrier p2("Jack");
    Personnage marcel("Marcel");
    cout << marcel << ":" << endl;
    marcel.sePresenter();

    p1.bouleDeFeu();
    p2.frapperCommeUnSourdAvecUnMarteau();

    p1.coupDePoing(p2);
    p2.coupDePoing(p1);
    cout << p2 << ":" << endl;
    p2.sePresenter();
    return 0;
}
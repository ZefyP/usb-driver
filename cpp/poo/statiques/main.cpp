#include "main.h"
using namespace std;

int main(){
    MaClasse::maMethode();
    cout<< "MaClasse *a, b;" << endl;
    MaClasse *a, b;
    MaClasse::maMethode();
    cout<< "a = new MaClasse();" << endl;
    a = new MaClasse();
    MaClasse::maMethode();
    cout<< "delete a;" << endl << "a = 0;" << endl;
    delete a;
    a = 0;
    MaClasse::maMethode();
    return 0;
}
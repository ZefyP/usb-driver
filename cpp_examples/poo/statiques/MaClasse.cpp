#include "MaClasse.h"
using namespace std;

int MaClasse::nbInstance = 0;

MaClasse::MaClasse(){
    MaClasse::nbInstance +=1;
}

MaClasse::~MaClasse(){
    MaClasse::nbInstance -= 1;
}

void MaClasse::maMethode(){
    cout << "// "<< nbInstance << " instance(s) de cette classe existe(nt) !" << endl;
}
#include <iostream>
#include "main.h"
using namespace std;

int main(){

    double a, b, c, resultat;
    int x, y;
    double mytab[3] = {3,4,5};
    double my3dTab[10][10][10][2];
    vector<double> tableauDoubles(5,1.5);
    tableauDoubles.push_back(10);
    tableauDoubles.pop_back();
    cout << "Entrez un nombre : " << endl;
    cin >> x;
    cout << "Entrez un nombre : " << endl;
    cin >> y;
    cout << "La moyenne du tableau est " << moyenneTab(tableauDoubles) << endl;
/*    cout << "Entrez un nombre : " << endl;
    cin >> c;
    resultat = addition(a,b,c);
    cout << a << "+" << b << "+" << c << "=" << resultat << endl;
 */
    if( drawRect(x,y) != 0){
        return 1;
    }
    cout << x <<"^2=";
    carre(x);
    cout << x << endl;
    return 0;
}

int addition(int a, int b){
    return a+b;
}

int addition(int a, int b, int c){
    return addition(addition(a,b),c);
}
int carre(int &a){
    a*=a;
    return 0;
}
int carre(double &a){
    a*=a;
    return 0;
}

int drawRect(int x, int y){

    if( x < 1 || x > 9 || y < 1 || y > 9){
        cout << "Taille incorrect" << endl;
        return 1;
    }

    for(int line(0); line < y; line ++){
        for(int column(0); column < x ;column++){
           if (line == 0 || column == 0 || line+1 == y|| column+1 == x){
               cout << "*";
           }
           else{
               cout << " ";
           }
        }
        cout << endl;
    }
    return 0;
}

double moyenneTab(double* tab,int size){
    double moyenne = 0.00;
    for (int i = 0; i < size; i++){
        moyenne+=tab[i];
    }
    return moyenne/size;
}

double moyenneTab(vector<double> const& tab){
    double moyenne = 0.00;
    for (int i = 0; i < tab.size(); i++){
        moyenne+=tab[i];
    }
    return moyenne/tab.size();
}

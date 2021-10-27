#include <fstream>
#include <iostream>
#include "main.h"
using namespace std;

int main(){
    ofstream myFlux;

    myFlux.open("file");
    if(myFlux){
        for (size_t i = 0; i < 1000; i++)
        {
            myFlux << "Coucou " << i << " J'adore ce truc" << endl;
        }
        
    }
    else{
        cout << "Vérifie quand même.." << endl;
    }
    

    ifstream myFlux2;
    string line;
    string content;

    myFlux2.open("file");
    if (myFlux2){
        while(getline(myFlux2,line)){
            content.append(line+"\n");
        }
        myFlux << content;
    }
    else{
        cout << "Vérifie quand même 2.." << endl;
    }
    myFlux2.close();
    myFlux.close();
    return 0; 
}

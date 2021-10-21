#include "main.h"
using namespace std;

#define MAX_VAL 100

int main(){

    // Locals variables declarations
    int number, secret;
    bool continuer = false;
    string playerName;
    
    getPlayerName(playerName);
    srand(time(NULL));

    do{
        std::system("clear");
        setRandomNumber(secret);
        //cout << "Le nombre secret est " << secret << endl;
       	do
        {
            getNumber(number);
            std::system("clear");
            if(number < secret){
                cout << "C'est plus grand " << playerName << " !" << endl;
            }
            else if(number > secret){
		cout << "C'est plus petit " << playerName << " !"<< endl;
            }
            else{
                cout << "Tu as trouvé "<< playerName << ", la réponse était bien "<< secret << " !" << endl;
            }
        } while (number != secret);
        FinDePartie(continuer);
    } while (continuer);
    

    
}

int getPlayerName(string& playerName){
	cout << "Bonjour, comment t'appeles-tu ?" << endl;
	do{
		cin >> playerName;
	}while(playerName.size()==0);

	return 0;
}

int getNumber(int& number){

    string reponse = "";

    do
    {
            cout << "Entre un nombre :" << endl;
            cin >> reponse;
    } while(!isNumber(reponse));
    
   number = stoi(reponse);

    return 0;
}

int setRandomNumber(int& number){
    number = rand() % MAX_VAL;
    return 0;
}

int FinDePartie(bool& choix){
    string reponse;
    
    do{
        cout << "Veux-tu continuer ? (o/n)" << endl;
        cin >> reponse;
    }while(reponse != "o" && reponse != "n");

    choix = reponse == "o";
    return 0;
}

bool isNumber (string const str){
    //Ne doit pas être vide
    if(str.size() < 1){
        cout << "false" << endl;
        return false;
    }
    //Ne doit contenir que des chiffres 
    for (size_t i = 0; i < str.size(); i++){
        if(str[i]>0x39 || str[i]<0x30){
            return false;
        }
    }
    //cout << "\"" << str << "\" est un nombre" << endl;
    return true;
}

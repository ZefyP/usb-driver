#include <iostream>
#include <fstream>
#include "main.h"

using namespace std;

int main(){
    
    string secret, shuffled, reponse;
    bool continuer;
    srand(time(NULL));

    do{
        std::system("clear");
        getWordFromFrenchDict(secret);
        //while (getWordFromPlayer1(secret) != 0);
        std::system("clear");
        while (getWordFromPlayer2(shuffled,reponse,secret) != 0);
        cout << "Bravo !" << endl;
        while (FinDePartie(continuer));
    }while(continuer);
    
    return 0;
}

int FinDePartie(bool& choix){
    string reponse;

    cout << "Veux-tu continuer ? (o/n)" << endl;
    cin >> reponse;

    choix = reponse == "o";
    
    if(reponse != "o" && reponse != "n"){
        return 1;
    }

    return 0;
    
}

int shuffle(string const word, string& result){
    //locals variables
    string writable_copy = word;
    int const size_of_word = word.size();
    int rand_position;
    result = "";
    //for every letter in word
    while(writable_copy.size() != 0)
    {
        rand_position = rand() % writable_copy.size();
        result+=writable_copy[rand_position];
        writable_copy.erase(rand_position,1);
    }
        
    return 0;
}

int getWordFromPlayer2(string shuffled, string& word, string const secret){
    shuffle(secret, shuffled);
    cout << shuffled << endl << "Joueur 2 => Quel est ce mot ?" << endl;
    cin >> word;

    for (size_t i = 0; i < word.size(); i++)
    {
        word[i] = toupper(word[i]);
    }
    
    if(word==secret){

        return 0;
    }
    cout << "Ce n'est pas le mot !" << endl << endl;
    
    return 1;
}

int getWordFromFrenchDict(std::string& word){
    ifstream myFlux;
    unsigned int size, rand_position,i;
    char tester;

    myFlux.open("dict");

    myFlux.seekg(0, ios::end);
    size = myFlux.tellg();
    rand_position = rand() % size;
    i = 0;
    while (tester != '\n'){
        myFlux.seekg(rand_position-i++,ios::beg);
        myFlux.get(tester);
    }

    rand_position -= i;
    rand_position += 2;

    myFlux.seekg(rand_position,ios::beg);
    //Get the line 
    getline(myFlux,word);
    //Remove the new line char from the word.
    word.pop_back();

    myFlux.close();
    for (size_t i = 0; i < word.size(); i++)
    {
        word[i] = toupper(word[i]);
    }
    return 0;
}

int getWordFromPlayer1(string& word){
    cout << "Joueur 1 => Entrez un mot :" << endl;
    cin >> word;

    if (word.size()<1){
        return 1;
    }

    for (size_t i = 0; i < word.size(); i++)
    {
        word[i] = toupper(word[i]);
        if (word[i] < 0x41 || word[i]>0x5A)
        {
            return 2;
        }
        
    }
    
    return 0;
}
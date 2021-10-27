#include "main.h"

using namespace std;

int main(){

   Personnage joueur, bot("Goliath");
   int choix;
   string nom;
   std::system("clear");
  
   getNameFromUser(nom);
   joueur.set_nom(nom);
   do
   {
      while(getActionFromUser(choix));
      std::system("clear");
      //cout << "vous avez choisis " << choix << endl;
      gameProcess(choix,&joueur,&bot);
      if(bot.estVivant() && joueur.estVivant()){
         if(bot.get_degats()<40){
            choix = 3;
         }else{
            choix = 1;
         }
         gameProcess(choix,&bot,&joueur);
      }
   } while (joueur.estVivant() && bot.estVivant());
   if (joueur.estVivant()){
      cout << "Vous avez gagné ! Bravo !" << endl;
   }
   else{
      cout << "Vous êtes mort mais ferez mieux dans une autre vie.." << endl;
   }
   
   return 0;
}

bool getActionFromUser(int &choix){
   string answer;
   cout << "Que voulez vous faire ?" << endl << "1: Attaquer            2: Soigner" << endl 
                                             << "3: Changer d'arme      4: Abandonner" << endl;
   cin >> answer;
   if (answer != "1" && answer != "2" && answer != "3" && answer != "4"){
      return true;
   }
   choix = stoi(answer);
   return false;
}

bool getNameFromUser(string &nom){
   cout << "Choisissez un nom pour votre personnage :" << endl;
   cin >> nom;

   return false;
}

bool gameProcess(int choix, Personnage *actif, Personnage *autre){
   string armes[5] = {"Poings","Epée en bois","Arc de cercle","Epée Nice","Corne de licorne fraichement arrachée"};
   int degats_armes[5] = {1,5,20,40,66};
   int randomiser;
   
   switch (choix){
      case 1:
      actif->attaquer(*autre);
      break;

      case 2:
      actif->seSoigner(20);
      break;

      case 3:
      randomiser = rand()%5;
      actif->changerArme(armes[randomiser],degats_armes[randomiser]);
      break;
      case 4:
      cout << "Vous mourrez.." << endl;
      actif->recevoirDegats(100);
      break;

      default:
         cout << "IMPOSSIBLE" << endl;
         return true;
      break;
   }
   return false;
}
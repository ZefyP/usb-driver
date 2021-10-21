#include "main.h"
#include <iostream>
using namespace std;

int main(){
   int random_variable = 0x55;
   int *pointer_to_random_variable(0);
   int **pointer_to_pointer(0);
   
   pointer_to_random_variable = &random_variable;
   pointer_to_pointer = & pointer_to_random_variable;

   cout << "Valeur de la variable (var)    : "<< random_variable << endl;
   cout << "Adresse de la variable (&)     : " << &random_variable << endl;

   cout << "Valeur de la variable (*ptr)   : "<< *pointer_to_random_variable << endl;
   cout << "Adresse de la variable (ptr)   : "<< pointer_to_random_variable << endl;

   cout << "Adresse de ptr (&)             : " << &pointer_to_random_variable << endl;
   cout << "Adresse de ptr (ptr2)          : "<< pointer_to_pointer << endl;

   cout << "Valeur de la variable (**ptr2) : "<< **pointer_to_pointer << endl;
   cout << endl;

   int *pointer_to_integer(0);
   pointer_to_integer = new(int);

   cout << "   //Pointeur vers la case       : " << pointer_to_integer << endl;
   cout << "   //Valeur dans la case pointée : " << *pointer_to_integer << endl;
   cout << "(*pointer_to_integer)++;" << endl;
   (*pointer_to_integer)++;
   cout << "   //Valeur dans la case pointée : " << *pointer_to_integer << endl;
   cout << "delete(pointer_to_integer);" << endl;
   delete(pointer_to_integer);
   cout << "   //Pointeur vers la case       : " << pointer_to_integer << endl;
   cout << "   //Valeur dans la case pointée : " << *pointer_to_integer << endl;
   pointer_to_integer = 0;
   cout << "pointer_to_integer = 0;" << endl;
   cout << "   //Pointeur vers la case       : " << pointer_to_integer << endl;


   string *pointer_to_answer;
   pointer_to_answer = new(string);
   cout << "Appuyez sur une touche puis entrer pour continuer." << endl;
   cin >> *pointer_to_answer;
   std::system("clear");

   cout << "Quel age avec vous ?" << endl;
   cin >> *pointer_to_answer;

   cout << "Vous avez " << *pointer_to_answer << " ans !" << endl;  
   delete(pointer_to_answer);
   pointer_to_answer = 0;
   return 0;
}

// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;

// int main()
// {
//     vector<string> msg {"Hello\\", "C++", "World", "from", "VS Code", "and the C++ extension!"};
//     unsigned int ageUtilisateur(26), nombreAmis(10);
//     string nomUtilisateur ("Kevin");
//     for (const string& word : msg)
//     {
//         cout << word << " ";
//     }
//     cout << endl << nomUtilisateur << " " << ageUtilisateur << " " << nombreAmis;
//     cout << endl;
    
//     return 0;
// }

#include<iostream>
#include <string>

using namespace std;

class PSPOH
{
  private:
  const char var;
  
  public:
  PSPOH(int constant_value):var(constant_value)
  {
   // cout << "Value is " << var << " \n";
  }
}; //end class

int main()
{
    
  int runs;
  cin >> runs; //select number of sample runs
  
 
   for (int i = 1; i <= runs; ++i) {
     cout << i << " ";
     //PSPOH myobject('h');
     string msg;
     msg = "this is the test command\n";
     cout << msg;
     
    }
    
    return 0;
}//end main


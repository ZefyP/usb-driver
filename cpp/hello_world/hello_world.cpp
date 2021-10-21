#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello\\", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    unsigned int ageUtilisateur(26), nombreAmis(10);
    string nomUtilisateur ("Kevin");
    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl << nomUtilisateur << " " << ageUtilisateur << " " << nombreAmis;
    cout << endl;
    
    return 0;
}
#include "main.h"
using namespace std;

int main(){
    Duree d2(1,0,0), d1(0,59,59), result;

    //result = d1 + d2;
    cout << d2 << endl;
    cout << d1 << endl;

    //d2-=d1;
    result = d2 - 3600;
    cout << d2-3600 << endl;

    return 0;
}
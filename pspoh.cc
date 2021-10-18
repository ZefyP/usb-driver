#include <cstring>
#include "USB_a.h"
#include <chrono>
#include <thread>
#include <vector>


int main(){
   // TC_PSFE_V2 card;
   //float result;
   // card.control(card.HIV,result);

    TC_PSPOH card;
    float result;
    card.control(card._HIV,result);
    std::cout << result << "\n\n" << std::endl;
 
    return 0;
    //return result;
}

//%%%%%%%%%%

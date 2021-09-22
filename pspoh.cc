#include <cstring>
#include "USB_a.h"
#include <chrono>
#include <thread>
#include <vector>


int main(){
   // TC_PSFE_V2 card;
    //float result;
   // card.get_voltage(card.HIV,result);

    TC_PSPOH card;
    float result;
    card.get_voltage(card._HIV,result);
    std::cout << result << "\n\n" << std::endl;
 
    return 0;
    //return result;
}

//%%%%%%%%%%

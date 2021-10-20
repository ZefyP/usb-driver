#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
int main(){

   TC_PSPOH card;
   string answer ="";
   if(card.getHV_status(answer) == 0){
      cout << "SPI answer : '" << answer  << "'" << endl;
   }
   
   
   // while(1){
   //    cout << "led turning on" << endl;
   //    card.turn_on_led();
   //    this_thread::sleep_for(chrono::milliseconds(500));
   //    cout << "led turning off" << endl;
   //    card.turn_off_led();
   //    this_thread::sleep_for(chrono::milliseconds(500));
   // } 
   return 0;

}

//%%%%%%%%%%

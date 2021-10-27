#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <thread>
#include <vector>

//#define DEUGO

using namespace std;
int main(){

   TC_PSPOH cTC_PSPOH; 
   //cout << "CP2130 initialized : " << TC_2SFE_V2.is_initialized << endl;
   string answer ="";
   if(cTC_PSPOH.getHV_status(answer) > 0){
      cout << "SPI answer : '" << answer  << "'" << endl;
   }
   
   #ifdef DEUGO
   while(1){
      cout << "led turning on" << endl;
      card.turn_on_led();
      this_thread::sleep_for(chrono::milliseconds(500));
      cout << "led turning off" << endl;
      card.turn_off_led();
      this_thread::sleep_for(chrono::milliseconds(500));
   }
   #endif

   return 0;
}

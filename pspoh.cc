#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <thread>
#include <vector>

//#define DEBUGO

using namespace std;
int main(){

   TC_PSPOH cTC_PSPOH;
   //cout << "CP2130 initialized : " << TC_2SFE_V2.is_initialized << endl;
   string answer ="";
   if(cTC_PSPOH.getHV_status(answer) > 0){
      cout << "SPI answer : '" << answer  << "'" << endl;
   }

   if(cTC_PSPOH.getHV_status(answer) > 0){
      cout << "SPI answer : '" << answer  << "'" << endl;
   }
   std::this_thread::sleep_for(std::chrono::milliseconds(50));
   cTC_PSPOH.spi_write("meas:temp?\r\n");
   std::this_thread::sleep_for(std::chrono::milliseconds(250));
   cTC_PSPOH.spi_read(answer,48);
   cout << "SPI answer : '" << answer  << "'" << endl;
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

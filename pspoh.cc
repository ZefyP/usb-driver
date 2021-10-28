#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <ctime>  
#include <thread>
#include <vector>
#include <iostream>
//#define DEBUGO
//#define RESET
using namespace std;
int main(){

   //Time measurement
   auto end = std::chrono::system_clock::now();
   auto start = std::chrono::system_clock::now();
   
   //Local variables
   TC_PSPOH cTC_PSPOH;
   string answer ="";
   /*
   //Get HIV status
   cout << "Get HV status" << endl ;
   cTC_PSPOH.spi_write("hiv?\r\n");
   if(cTC_PSPOH.wait_for_RTR()==0){
      cTC_PSPOH.spi_read(answer,256);
      cout << "SPI answer : '" << answer  << "'" << endl << endl;
   }
   cout << "Get HV status" << endl ;
   cTC_PSPOH.spi_write("hiv?\r\n");
   if(cTC_PSPOH.wait_for_RTR()==0){
      cTC_PSPOH.spi_read(answer,256);
      cout << "SPI answer : '" << answer  << "'" << endl << endl;
   }

   cout << "Get temperature values" << endl ;
   
   cTC_PSPOH.spi_write("meas:temp?\r\n");
   if(cTC_PSPOH.wait_for_RTR()==0){
      cTC_PSPOH.spi_read(answer,256);
      cout << "SPI answer : '" << answer  << "'" << endl << endl;
   }
   
    cout << "Get temperature values" << endl ;
   
   cTC_PSPOH.spi_write("meas:temp?\r\n");
   if(cTC_PSPOH.wait_for_RTR()==0){
      cTC_PSPOH.spi_read(answer,256);
      cout << "SPI answer : '" << answer  << "'" << endl << endl;
   }
   */
   start = std::chrono::system_clock::now();
   cTC_PSPOH.spi_write("meas:hiv:in?\r\n");
   if(cTC_PSPOH.wait_for_RTR()==0){
      cTC_PSPOH.spi_read(answer,256);
      end = std::chrono::system_clock::now();
      cout << "SPI answer : '" << answer  << "'" << endl << endl;
   }

   cTC_PSPOH.system_reset();
   
   //Time measurement
  
   std::chrono::duration<double> elapsed_seconds = end-start;
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
   return 0;
}

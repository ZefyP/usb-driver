#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
int main(){


   TC_PSPOH cTC_PSPOH;
   //cTC_PSPOH.system_reset();
   cTC_PSPOH.cpu_reset();
   //std::this_thread::sleep_for(std::chrono::milliseconds(200)); //wait 200 millis
   return 0;
}

 #include <cstring>
#include "USB_a.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>




int main(){
	TC_2SFE cTC_2SFE;
	std::cout << cTC_2SFE.product_string << std::endl;
	float result;
	while(1){
	cTC_2SFE.adc_get(cTC_2SFE.ISEN,result);
	std::cout << "I="<< result << std::endl;
	cTC_2SFE.adc_get(cTC_2SFE.THERM_SENSE,result);
	std::cout << "THERM="<< result << std::endl;
    	cTC_2SFE.toggle_led();   
	sleep(1);
	}
    return 0;
}

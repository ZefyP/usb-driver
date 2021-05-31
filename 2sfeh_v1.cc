 #include <cstring>
#include "USB_a.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>




int main(){
        /*TC_2SFE cTC_2SFE(1,32);
        const char* al=cTC_2SFE.get_product_string();
	for (int i=0; i<50; i++){
	std::cout << *(al+i);
	}
	std::cout << std::endl;
	float result;
	while(1){
	cTC_2SFE.adc_get(cTC_2SFE.ISEN,result);
	std::cout << "I="<< result << std::endl;
	cTC_2SFE.adc_get(cTC_2SFE.THERM_SENSE,result);
	std::cout << "THERM="<< result << std::endl;
    	cTC_2SFE.toggle_led();   
	sleep(1);
	}
        */
    TC_2SFE_V2 cTC_2SFE;
    float result;
    cTC_2SFE.set_voltage(cTC_2SFE._1300mV);
    cTC_2SFE.adc_get(cTC_2SFE.AMUX,result);
    std::cout << "AMUX="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE.ISEN_1V4,result);
    std::cout << "ISEN_1V4="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE.ANT_PULL,result);
    std::cout << "ANT_PULL="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE._3V3,result);
    std::cout << "_3V3="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE.ISEN_3V3,result);
    std::cout << "ISEN_3V3="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE._1V4,result);
    std::cout << "_1V4="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE._1V25_REG,result);
    std::cout << "_1V25_REG="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE._1V25_HYB,result);
    std::cout << "_1V25_HYB="<< result << std::endl;
    cTC_2SFE.adc_get(cTC_2SFE.THERM_SENSE,result);
    std::cout << "THERM_SENSE="<< result << std::endl;
    return 0;
}

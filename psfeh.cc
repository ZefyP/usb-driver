#include <cstring>
#include "USB_a.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>




int main(){
	TC_PSFE cTC_PSFE;
	float result;
	cTC_PSFE.adc_get(cTC_PSFE.ANT_PULL,result );
	cTC_PSFE.antenna_fc7(800,cTC_PSFE._1); //512 positive
	cTC_PSFE.adc_get(cTC_PSFE.ANT_PULL,result );
	cTC_PSFE.antenna_fc7(800,cTC_PSFE.NONE); //512 positive
	cTC_PSFE.adc_get(cTC_PSFE.ANT_PULL,result );
	//cTC_PSFE.antenna_fc7(800,cTC_PSFE._2); //512 positive
/*	float result;
	for (int i=0; i<=27; i++){
	cTC_PSFE.adc_get(static_cast<TC_PSFE::measurement>(i),result);
	}

	std::cout << std::endl;
	cTC_PSFE.adc_get(cTC_PSFE._1V,result );
	cTC_PSFE.adc_get(cTC_PSFE._1V25, result);
	cTC_PSFE.mode_control(cTC_PSFE.SSA_OUT);
	cTC_PSFE.set_voltage(cTC_PSFE._950mV,cTC_PSFE._1150mV);
	cTC_PSFE.antenna_fc7(512,cTC_PSFE._1); //512 positive
	//std::cout << std::endl;
	//cTC_PSFE.adc_get(cTC_PSFE._625mV_REF,result );
	//cTC_PSFE.adc_get(cTC_PSFE.GROUND,result );
	//cTC_PSFE.adc_get(cTC_PSFE._1V25_REF,result );
	cTC_PSFE.adc_get(cTC_PSFE._1V,result );
	cTC_PSFE.adc_get(cTC_PSFE._1V25, result);
	//cTC_PSFE.adc_get(cTC_PSFE.ISEN_1V25,result );
	//cTC_PSFE.adc_get(cTC_PSFE.ISEN_1V,result );
	//cTC_PSFE.adc_get(cTC_PSFE.ANT_PULL,result );
	//cTC_PSFE.pogo_selftest(cTC_PSFE.DISABLED);
	//cTC_PSFE.pogo_selftest(cTC_PSFE.BUFFER_ONE);
	//cTC_PSFE.pogo_selftest(cTC_PSFE.POGO_ONE);
	//cTC_PSFE.pogo_selftest(cTC_PSFE.POGO_ZERO);
	//cTC_PSFE.adc_get(cTC_PSFE.ISEN_3V3,result );
	cTC_PSFE.antenna_fc7(512,cTC_PSFE._2); //512 positive
	cTC_PSFE.adc_get(cTC_PSFE._1V,result );
	cTC_PSFE.adc_get(cTC_PSFE._1V25, result);
	cTC_PSFE.antenna_fc7(512,cTC_PSFE.ALL); //512 positive
	cTC_PSFE.adc_get(cTC_PSFE._1V,result );
	cTC_PSFE.adc_get(cTC_PSFE._1V25, result);
	std::cout << cTC_PSFE.product_string << std::endl;
	std::cout <<cTC_PSFE.chirality<< std::endl;
	{
	TC_PSFE a;
	std::cout <<a.chirality<< std::endl;
	}
	std::cout <<cTC_PSFE.chirality<< std::endl;
*/
    return 0;
}

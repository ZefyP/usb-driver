#include "USB_libusb.h"
#include<unistd.h>
bool TC_2SSEH::is_initialized=false;
unsigned int TC_2SSEH::AMUX_R_set=0;
unsigned int TC_2SSEH::AMUX_L_set=0;
bool TC_2SSEH::load1_enable=false;
bool TC_2SSEH::load2_enable=false;
bool TC_2SSEH::load1_path=false;
bool TC_2SSEH::load2_path=false;
unsigned int TC_2SSEH::load1_setvalue=0;
unsigned int TC_2SSEH::load2_setvalue=0;

bool TC_2SSEH::HV_relay=false;
bool TC_2SSEH::HVMONX7_relay=false;
bool TC_2SSEH::HVMONX8_relay=false;
unsigned int TC_2SSEH::HVDAC_setvalue=0;



CP2130_2S TC_2SSEH::cCP2130; 
std::string TC_2SSEH::product_string;

TC_2SSEH::TC_2SSEH()
{
    int res;
    if(!is_initialized){
    cCP2130.initialize();
    product_string.resize(64,' ');
    
    cCP2130.configure_spi(cCP2130.cs0,cCP2130.muController);
    cCP2130.choose_spi(cCP2130.cs0);
    
    is_initialized=true;
    AMUX_R_set=0;
    AMUX_L_set=0;
    
    }
}


int TC_2SSEH::read_temperature(temperatureMeasurement m, float& output)
{   //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x08, 0x00, 0x00, 0x00,
    0x03,0x00,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                                        //Temperature[0]: Temp1 MSB; Temperature[1]: Temp1 LSB		
																						//Temperature[2]: Temp2 MSB; Temperature[3]: Temp2 LSB
																						//Temperature[4]: Temp3 MSB; Temperature[5]: Temp3 LSB
																						//Temperature[6]: Temp SEH MSB; Temperature[7]: Temp SEH LSB
																			
 
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[m*2+4]<<(8) | read_input_buf[5+m*2];
    std::cout<<resetMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    
    output=temp*convFactor;
    return 0;

}

int TC_2SSEH::read_supply(supplyMeasurement m, float& output) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x14, 0x00, 0x00, 0x00,
    0x00,0x03,0x00,0x14,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00};
    unsigned char read_input_buf[64];   
                                //UI_supply[0]: U P5V MSB; UI_supply[1]: U P5V LSB
 								//UI_supply[2]: I P5V MSB; UI_supply[3]: I P5V LSB
 								//UI_supply[4]: U P3V3 MSB; UI_supply[5]: U P3V3 LSB
 								//UI_supply[6]: I P3V3 MSB; UI_supply[7]: I P3V3 LSB
 								//UI_supply[8]: U P2V5 MSB; UI_supply[9]: U P2V5 LSB
 								//UI_supply[10]: I P2V5 MSB; UI_supply[11]: I P2V5 LSB
 								//UI_supply[12]: U P1V25 MSB; UI_supply[13]: U P1V25 LSB
 								//UI_supply[14]: I P1V25 MSB; UI_supply[15]: I P1V25 LSB
 								//UI_supply[16]: U SEH MSB; UI_supply[17]: U SEH LSB
 								//UI_supply[18]: I SEH MSB; UI_supply[19]: I SEH LSB
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    int temp=read_input_buf[m*2+4]<<(8) | read_input_buf[5+m*2];
    std::cout<<supplyMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    output=temp*convFactor;
    return 0;

}

int TC_2SSEH::read_load(loadMeasurement m, float& output) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x08, 0x00, 0x00, 0x00,
    0x00,0x0C,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                                        //UI_load[0]: U P1V2 R MSB; UI_load[1]: U P1V2 R LSB
																						//UI_load[2]: I P1V2 R MSB; UI_load[3]: I P1V2 R LSB
																						//UI_load[4]: U P1V2 L MSB; UI_load[5]: U P1V2 L LSB
																						//UI_load[6]: I P1V2 L MSB; UI_load[7]: I P1V2 L LSB
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[m*2+4]<<(8) | read_input_buf[5+m*2];
    std::cout<<loadMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    output=temp*convFactor;
    return 0;

}

int TC_2SSEH::read_hvmon(hvmonMeasurement m, float& output) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x08, 0x00, 0x00, 0x00,
    0x20,0x20,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                                        //HVMON[0]: Mon MSB; HVMON[1]: Mon LSB
																						//HVMON[2]: HV_meas MSB; HVMON[3]: HV_meas[2]
																						//HVMON[4]: VHVJ7 MSB; HVMON[5]: VHVJ7 LSB
																						//HVMON[6]: VHVJ8 MSB; HVMON[7]: VHVJ8 LSB
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[4+m*2]<<(8) | read_input_buf[5+m*2];
    std::cout<<hvmonMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    output=temp*convFactor;
    return 0;

}


int TC_2SSEH::read_reset(resetMeasurement m, float& output) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x08, 0x00, 0x00, 0x00,
    0x00,0xC0,0x00,0x08,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                                        //RST[0]: RST_CBC_R MSB; RST[1]: RST_CBC_R LSB	
																						//RST[2]: RST_CIC_R MSB; RST[3]: RST_CIC_R LSB
																						//RST[4]: RST_CBC_L MSB; RST[5]: RST_CBC_L LSB	
																						//RST[6]: RST_CIC_L MSB; RST[7]: RST_CIC_L LSB	
																						
 
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[m*2+4]<<(8) | read_input_buf[5+m*2];
    std::cout<<resetMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    output=temp*convFactor;
    return 0;

}

int TC_2SSEH::read_state(state s, bool& output) {
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0x08,0x08,0x00,0x03,
    0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                                         //TestCardState[0]: Bit0: "1" -> P5V overvoltage
																						//					Bit1: "1" -> P5V undervoltage
																						//					Bit2: "1" -> P5V overcurrent
																						//					Bit3: "1" -> P3V3 overvoltage
																						//					Bit4: "1" -> P3V3 undervoltage
																						//					Bit5: "1" -> P3V3 overcurrent
																						//					Bit6: "1" -> P2V5 overvoltage
																						//					Bit7: "1" -> P2V5 undervoltage
																						//TestCardState[1]: Bit0: "1" -> P2V5 overcurrent
																						//					Bit1: "1" -> P1V25 overvoltage
																						//					Bit2: "1" -> P1V25 undervoltage
																						//					Bit3: "1" -> P1V25 overcurrent
																						//					Bit4: "1" -> Temperature1 error
																						//					Bit5: "1" -> Temperature2 error
																						//					Bit6: "1" -> Temperature3 error
																						//					Bit7: "1" -> Temperature SEH error
																						//TestCardState[2]	Bit0: "1" -> 
																						//					Bit1: "1" -> 
																						//					Bit2: "1" -> 																				
 
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    
    unsigned char temp=(read_input_buf[s/8+4]&(0x80>>(7-(s%8))))>>(s%8);
    // quite a lot of bit suffeling going on to select the right bit for each status
    // first select the right byte s/8
    // then mask all but the desired bit, & 0x80 is the mask, >>(7-s%8) shifts the mask to the right location
    // >> s%8 shifts the result to be 1 bit long
    if (temp==1){
        output=true;
    }else{
        output=false;
    }
    
     
    std::cout<<stateName[s]<<": " <<output <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    // for(unsigned short int i = 0; i < sizeof(supply_value); i++){
    // supply_value[i]=(read_input_buf[0+i*5]<<(8*4)) | (read_input_buf[1+i*5]<<(8*3)) |(read_input_buf[2+i*5]<<(8*2)) |(read_input_buf[3+i*5]<<(8*1)) |(read_input_buf[4+i*5])     ;
    // }
    // std::cout << std::endl;
    // for(unsigned short int i = 0; i < sizeof(supply_value); i++){
    //     std::cout << std::hex << (int) supply_value[i] << std::dec << ' ';
    // }
    // std::cout << std::endl;
    //output=temp*convFactor;
    return 0;

}


int TC_2SSEH::read_limit(limit l, float& output) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor=1;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x10, 0x00, 0x00, 0x00,
    0x04,0x04,0x00,0x10,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                //P5V Voltage tolerance default +-100mV
																//Imax P5V default 500mA
																//P3V3 Voltage tolerance default +-100mV
																//Imax P3V3 default 1000mA
																//P3V3 Voltage tolerance default +-100mV
																//Imax P2V5 default 200mA
																//P3V3 Voltage tolerance default +-100mV
															    //Imax P1V25 default 200mA
																//T1max default 70°C
																//T1min default -40°C
																//T2max default 70°C
																//T2min default -40°C
																//T3max default 70°C
																//T3min default -40°C
																//Temperature SEH max default 60°C
																//Temperature SEH min default -35°C
																//limitValues[0]: U P5V tolerance; 1Bit=1mV
																						//limitValues[1]: I P5V max; 1Bit=10mA
																						//limitValues[2]: U P3V3 tolerance; 1Bit=1mV
																						//limitValues[3]: I P3V3 max; 1Bit=10mA
																						//limitValues[4]: U P2V5 tolerance; 1Bit=1mV
																						//limitValues[5]: I P2V5 max; 1Bit=10mA
																						//limitValues[6]: U P1V25 tolerance; 1Bit=1mV
																						//limitValues[7]: I P1V25 max; 1Bit=50mA
																						//limitValues[8]: Temperature1 max; 1Bit=+1°C
																						//limitValues[9]: Temperature1 min; 1Bit=-1°C
																						//limitValues[10]: Temperature2 max; 1Bit=+1°C
																						//limitValues[11]: Temperature2 min; 1Bit=-1°C
																						//limitValues[12]: Temperature3 max; 1Bit=+1°C
																						//limitValues[13]: Temperature3 min; 1Bit=-1°C

    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[l+4];
    std::cout<<limitName[l]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    output=temp*convFactor;
    return 0;
}

int TC_2SSEH::readI2C(unsigned char regMSB, unsigned char regLSB, unsigned char& value){
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x02, 0x00, 0x00, 0x00,
    0x80,0x01,0x00,0x02,
    regLSB,regMSB,0xFF};
    unsigned char read_input_buf[64]; 
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);

    unsigned char writeread_command_buf2[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0x40,0x02,0x00,0x03,
    0x00,0x00,0x00};
    unsigned char read_input_buf2[64]; 
    sleep(2);
    cCP2130.spi_writeRead(writeread_command_buf2,sizeof(writeread_command_buf2),read_input_buf2);
    //int temp=read_input_buf[m*2]<<(8) | read_input_buf[1+m*2];
    //std::cout<<supplyMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    for(unsigned short int i = 0; i < sizeof(read_input_buf2); i++){
        std::cout << std::hex << (int) read_input_buf2[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    
    
    return 0;


}


int TC_2SSEH::writeI2C(unsigned char regMSB, unsigned char regLSB, unsigned char value){
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0x80,0x80,0x00,0x03,
    regLSB,regMSB,value,0xff};
    unsigned char read_input_buf[64]; 
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);

    
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    
    
    return 0;


}

int TC_2SSEH::set_limit(limit l, unsigned char value) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x10, 0x00, 0x00, 0x00,
    0x04,0x04,0x00,0x10,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    };
    unsigned char read_input_buf[64];   
                                                                //P5V Voltage tolerance default +-100mV
																//Imax P5V default 500mA
																//P3V3 Voltage tolerance default +-100mV
																//Imax P3V3 default 1000mA
																//P3V3 Voltage tolerance default +-100mV
																//Imax P2V5 default 200mA
																//P3V3 Voltage tolerance default +-100mV
															    //Imax P1V25 default 200mA
																//T1max default 70°C
																//T1min default -40°C
																//T2max default 70°C
																//T2min default -40°C
																//T3max default 70°C
																//T3min default -40°C
																//Temperature SEH max default 60°C
																//Temperature SEH min default -35°C
																//limitValues[0]: U P5V tolerance; 1Bit=1mV
																						//limitValues[1]: I P5V max; 1Bit=10mA
																						//limitValues[2]: U P3V3 tolerance; 1Bit=1mV
																						//limitValues[3]: I P3V3 max; 1Bit=10mA
																						//limitValues[4]: U P2V5 tolerance; 1Bit=1mV
																						//limitValues[5]: I P2V5 max; 1Bit=10mA
																						//limitValues[6]: U P1V25 tolerance; 1Bit=1mV
																						//limitValues[7]: I P1V25 max; 1Bit=50mA
																						//limitValues[8]: Temperature1 max; 1Bit=+1°C
																						//limitValues[9]: Temperature1 min; 1Bit=-1°C
																						//limitValues[10]: Temperature2 max; 1Bit=+1°C
																						//limitValues[11]: Temperature2 min; 1Bit=-1°C
																						//limitValues[12]: Temperature3 max; 1Bit=+1°C
																						//limitValues[13]: Temperature3 min; 1Bit=-1°C

    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    unsigned int temp=read_input_buf[l+4];
    std::cout<<limitName[l]<<": " <<"0x" << std::hex << (int) temp <<std::endl;
    for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
        std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    unsigned char writeread_command_buf2[] = {0x00,0x00, 0x02, 0x00, 
    0x11, 0x00, 0x00, 0x00,
    0x02,0x02,0x00,0x10,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
    };
    for(unsigned short int i = 0; i < 16; i++){
        writeread_command_buf2[i+12]=read_input_buf[i+4];
    }
    writeread_command_buf2[l+12]=value;
    for(unsigned short int i = 0; i < sizeof(writeread_command_buf2); i++){
        std::cout << std::hex << (int) writeread_command_buf2[i] << std::dec << ' ';
    }
    std::cout << std::endl;
    
    cCP2130.spi_writeRead(writeread_command_buf2,sizeof(writeread_command_buf2),read_input_buf);

    return 0;
}

int TC_2SSEH::set_AMUX(unsigned int rightValue=AMUX_R_set, unsigned int leftValue=AMUX_L_set) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    //float convFactor;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x05, 0x00, 0x00, 0x00,
    0x00,0x30,0x00,0x04,
    (unsigned char)(rightValue>>8),(unsigned char)(rightValue),(unsigned char)(leftValue>>8),(unsigned char)(leftValue)
    ,0xFF 
    //casting the int to char to allow integer input to function
    };
                                                                                        //AMUX[0]: AMUX R MSB; AMUX[1]: AMUX R LSB
																						//AMUX[2]: AMUX L MSB; AMUX[3]: AMUX L LSB
    unsigned char read_input_buf[64];   
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    
    std::cout <<"Wrote to AMUX_R " <<std::hex << rightValue <<" and AMUX_L " <<std::hex << leftValue << std::endl;
    AMUX_R_set=rightValue;
    AMUX_L_set=leftValue;
    
    return 0;

}

int TC_2SSEH::set_SehSupply(sehSupplyState state) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    //float convFactor;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x02, 0x00, 0x00, 0x00,
    0x0C,0x00,0x00,0x01,state
        ,0xFF 
    
    };
    //Bit 0: "0" -> Supply SEH OFF; "1" -> Supply SEH ON
	unsigned char read_input_buf[64];   
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    
    std::cout <<"Set State of SEH Supply to: " <<state << std::endl;
    
    return 0;

}

int TC_2SSEH::set_load1(bool enable=load1_enable,bool path=load1_path, unsigned int value=load1_setvalue ){
    
unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0x30,0x00,0x00,0x02,
    (unsigned char)((unsigned char)((enable?1:0)<<7)|(unsigned char)((path?1:0)<<6)|((unsigned char)((value>>8)&0x0f))),
    (unsigned char)value,0xFF 
    };
                                                                                        //Load1_control[0]: Bit 7: "0" -> Load1 OFF; "1" -> Load1 ON
																						//					Bit 6: "0" -> Loar1 intern; "1" -> Load1 extern
																						//					Bit 0 to 3: -> current value MSB
																						//Load1_control[1]: current value LSB		
																						
    
    
	unsigned char read_input_buf[64];   
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    std::cout <<"Set Load1: Enable? " <<enable<<" External "<<path<<" Value 0x"<<std::hex<<(value&0x0fff) << std::endl;
    load1_enable=enable;
    load1_path=path;
    load1_setvalue=value;
    return 0;

}

int TC_2SSEH::set_load2(bool enable=load2_enable,bool path=load2_path, unsigned int value=load2_setvalue ){   
unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0xC0,0x00,0x00,0x02,
    (unsigned char)((unsigned char)((enable?1:0)<<7)|(unsigned char)((path?1:0)<<6)|((unsigned char)((value>>8)&0x0f))),
    (unsigned char)value,0xFF 
    };
                                                                                        //Load2_control[0]: Bit 7: "0" -> Load2 OFF; "1" -> Load2 ON
																						//					Bit 6: "0" -> Loar2 intern; "1" -> Load2 extern
																						//					Bit 0 to 3 -> current value MSB
																						//Load2_control[1]: current value LSB	
																			
    
    
	unsigned char read_input_buf[64];   
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    std::cout <<"Set Load2: Enable? " <<enable<<" External "<<path<<" Value 0x"<<std::hex<<(value&0x0fff) << std::endl;
    load2_enable=enable;
    load2_path=path;
    load2_setvalue=value;
    return 0;
}

int TC_2SSEH::set_HV(bool hvRelay=HV_relay,bool hvmonx7Relay=HVMONX7_relay,bool hvmonx8Relay=HVMONX8_relay, unsigned int value=HVDAC_setvalue ){   
unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x03, 0x00, 0x00, 0x00,
    0x01,0x01,0x00,0x02,
    (unsigned char)((unsigned char)((hvRelay?1:0)<<7)|(unsigned char)((hvmonx7Relay?1:0)<<6)|(unsigned char)((hvmonx8Relay?1:0)<<5)|((unsigned char)((value>>8)&0x03))),
    (unsigned char)value,0xFF 
    };
                                                                                        //HV[0]: Bit 7: "0" -> HV OFF; "1" -> HV ON
																						//		 Bit 6: "0" -> HVMONX7 OFF; "1" -> HVMONX7 ON
																						//		 Bit 5: "0" -> HVMONX8 OFF; "1" -> HVMONX8 ON
																						//		 Bit 0 and 1: -> HV DAC Value MSB
																						//HV[1]: HV DAC LSB	

    
    
	unsigned char read_input_buf[64];   
    
    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
    std::cout <<"Set HV: HV Relay? " <<hvRelay<<" HVMONX7 Relay? "<<hvmonx7Relay<<" HVMONX8 Relay? "<<hvmonx8Relay<<" Value 0x"<<std::hex<<(value&0x03ff) << std::endl;
    HV_relay=hvRelay;
    HVMONX7_relay=hvmonx7Relay;
    HVMONX8_relay=hvmonx8Relay;
    HVDAC_setvalue=value;
    return 0;

}

int TC_2SSEH::set_fuse(bool value) {
    //unsigned int supply_value[4]; // dummy result to exercise data handling
    float convFactor;
    unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
    0x02, 0x00, 0x00, 0x00,
    0x10,0x10,0x00,0x01,
    (unsigned char)value?1:0,0xff,
    };
    //Bit0: "0" -> deactivate FUSE, "1" -> activate Fuse
    unsigned char read_input_buf[64];   
   

    cCP2130.spi_writeRead(writeread_command_buf,sizeof(writeread_command_buf),read_input_buf);
   
    std::cout<<"Wrote Fuse: " << value <<std::endl;
    
    return 0;
}

int TC_2SSEH::sendLPGBTconfig(unsigned char* buffer,int bufSize) {
    
    unsigned char read_input_buf[64];   
   

    cCP2130.spi_writeRead(buffer,bufSize,read_input_buf);
   
    std::cout<<"Wrote lpGBT config"<<std::endl;
    
    return 0;
}


TC_2SSEH::~TC_2SSEH() {}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

CP2130_2S::CP2130_2S() {}
CP2130_2S::~CP2130_2S(){
    if(fUsbHandle) close();
}
int CP2130_2S::initialize()
{
     if ( ( fUsbHandle = setup_libusb_access() ) == NULL )
     {
        std::cout << "Failed to connect with CP2130, check if it is plugged in the USB port." << std::endl;
        exit ( -1 ); 
     }
     //get_usb_config();
     //libusb_reset_device ( fUsbHandle ); // MISO doesn't work wihthout this...
     return 0;
}

void CP2130_2S::close()
{
    if (fUsbHandle)
        libusb_release_interface(fUsbHandle, 0);
    if (kernelAttached)
        libusb_attach_kernel_driver(fUsbHandle, 0);
    if (fUsbHandle)
        libusb_close(fUsbHandle);
    if (deviceList)
        libusb_free_device_list(deviceList, 1);
    if (context)
        libusb_exit(context);
    
    fUsbHandle = NULL;
    context = NULL;
    deviceList = NULL;
    kernelAttached = 0;
    delete fUsbHandle;
    std::cout << "Closed SPI device" << std::endl;
}

// int CP2130::gpio_set_input(cs_line c)
// {
//     char data[3]={(char)c,0,0};
//     int result=usb_control_msg(fUsbHandle, 0x40, 0x23, 0, 0,  data, sizeof(data), fUsbTimeout);
//     return 0;
// }

int CP2130_2S::gpio_set_output(cs_line c, bool level)
{

    unsigned char data[3]={(char)c,2,level};
    
    if (libusb_control_transfer(fUsbHandle, 0x40, 0x23, 0, 0,  data, sizeof(data), fUsbTimeout) != sizeof(data))
    {
        std::cout << "ERROR: Error in control transfer" << std::endl;
        return -1;
    }
    std::cout << "Successfully set GPIO" << std::endl;
    return 0;

    
    
 }

int CP2130_2S::choose_spi(cs_line c)
{
    
    unsigned char control_buf_in_cse[2]={c,0x02};
    if (libusb_control_transfer(fUsbHandle, 0x40, 0x25, 0x0000, 0x0000, control_buf_in_cse, sizeof(control_buf_in_cse), fUsbTimeout) != sizeof(control_buf_in_cse))
    {
        std::cout << "ERROR: Error in control transfer" << std::endl;
        return -1;
    }
    return 0;
    

}

int CP2130_2S::configure_spi(cs_line c, spiDevice d)
{
    unsigned char data[2]={c,0};
    switch(d){
        case muController:
        {  
        //configure muC
            unsigned char control_buf_in_muC[2]={0x00,0b00001011};
            if (libusb_control_transfer(fUsbHandle, 0x40, 0x31, 0x0000, 0x0000, control_buf_in_muC, sizeof(control_buf_in_muC), fUsbTimeout) != sizeof(control_buf_in_muC))
            {
                std::cout << "ERROR: Error in control transfer" << std::endl;
                return -1;
            }
            unsigned char control_buf_in_delay[8] = {0, 0b00000000,0, 0, 0, 0, 0, 0}; 
            if (libusb_control_transfer(fUsbHandle, 0x40, 0x33, 0x0000, 0x0000, control_buf_in_delay, sizeof(control_buf_in_delay), fUsbTimeout) != sizeof(control_buf_in_delay))
            {
                std::cout << "ERROR: Error in control transfer" << std::endl;
                return -1;
            }
            std::cout << "Configured muC" << std::endl;
            
        
        break;
        }
    break;
    }
    
    return 0;
}

// int CP2130::spi_write(char* data, int size)
// {
//     return usb_bulk_write(fUsbHandle, fUsbEndpointBulkOut, data, size, fUsbTimeout );
// }

int CP2130_2S::spi_writeRead(unsigned char* writeread_command_buf, int size_of_buf, unsigned char* read_input_buf)
{
    // This example shows how to implement a CP2130 WriteRead operation using bulk write and read requests

    
    // unsigned char writeread_command_buf[] = {
    //     0x00, 0x00,             // Reserved
    //     0x02,                   // WriteRead command
    //     0x00,                   // Reserved
    //     0x06, 0x00, 0x00, 0x00, // Read 6 bytes, little-endian
    //     0x00, 0x11, 0x22, 0x33, 0x44, 0x55 // Test data, 6 bytes
    // };
    
    //unsigned char read_input_buf[64];
    int bytesWritten, bytesRead;
    int usbTimeout = 500;

    // Read the TransferPriority byte (usbConfig[8]) to determine endpoint assignments
    unsigned char control_buf_in_trans[9];
    if (libusb_control_transfer(fUsbHandle, 0xC0, 0x60, 0x0000, 0x0000, control_buf_in_trans, sizeof(control_buf_in_trans), usbTimeout) != sizeof(control_buf_in_trans))
    {
        std::cout << "ERROR: Error in control transfer" << std::endl;
        return -1;
    }
    unsigned char writeEp, readEp;
    if(control_buf_in_trans[8])
    {
        // CP2130 configured for HighPriorityWrite
        writeEp = 0x01;
        readEp  = 0x82;
    }
    else
    {
        // CP2130 configured for HighPriorityRead
        writeEp = 0x02;
        readEp  = 0x81;
    }
    // for(unsigned short int i = 0; i < 20; i++){
    // std::cout << std::hex << (int) writeread_command_buf[i] << std::dec << ' ';
    // }
    // std::cout << std::endl;
    // std::cout << sizeof(writeread_command_buf) << std::endl;
    // std::cout << size_of_buf << std::endl;
    // Use bulk Write to send the WriteRead command and appended test data
   
     
    //for(unsigned short int i = 0; i < sizeof(writeread_command_buf); i++){
    
    
    if (libusb_bulk_transfer(fUsbHandle, writeEp, writeread_command_buf, size_of_buf , &bytesWritten, usbTimeout))
    {
        std::cout << "ERROR: Error in bulk write part of WriteRead operation" << std::endl;
        return -1;
    }
    std::cout << "Successfully wrote to SPI MOSI, number of bytes written = " << std::dec << bytesWritten << std::endl;

   

    // Use bulk read to read data from CP2130
    if (libusb_bulk_transfer(fUsbHandle, readEp, read_input_buf, size_of_buf-8, &bytesRead, usbTimeout))
    {
        std::cout << "ERROR: Error in bulk read part of WriteRead operation" << std::endl;
        return -1;
    }
    std::cout << "Successfully read from SPI MISO, number of bytes read = " << std::dec << bytesRead << std::endl;
    if(bytesRead != size_of_buf-8)
    {
        std::cout << "*** UNEXPECTED NUMBER OF BYTES READ:  NUM_BYTES_TO_READ =  " << std::dec << bytesRead << "bytesRead =  " << std::endl;
    }
    // for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
    // std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    // }
    // std::cout << std::endl;
    return 0;

}

// int CP2130::spi_read(char* data, int size)
// {
//  return usb_bulk_read (fUsbHandle, fUsbEndpointBulkIn, data, size, fUsbTimeout);
// }

// int CP2130::get_product_string(unsigned char* data)
// {
//     int result = libusb_control_transfer(fUsbHandle, 0xC0, 0x66, 0, 0, (unsigned char*) data, 0x40, fUsbTimeout );
//     std::rotate(data,data-2,data+sizeof(data)-1);
//     return 0;
// }

// int CP2130::get_gpio_value(cs_line c, bool& level)
// {
//     char data[2]={0,0};
//     int result = usb_control_msg (fUsbHandle, 0xC0, 0x20, 0, 0, data, 0x02, fUsbTimeout);
//     switch(c){
//         case cs0:
//         level=(data[1]&0b00001000)!=0;break;
//         case cs1:
//         level=(data[1]&0b00010000)!=0;break;
//         case cs2:
//         level=(data[1]&0b00100000)!=0;break;
//         case cs3:
//         level=(data[1]&0b01000000)!=0;break;
//         case cs4:
//         level=(data[1]&0b10000000)!=0;break;
//         case cs5:
//         level=(data[0]&0b00000001)!=0;break;
//         case cs6:
//         level=(data[0]&0b00000100)!=0;break;
//         case cs7:
//         level=(data[0]&0b00001000)!=0;break;
//         case cs8:
//         level=(data[0]&0b00010000)!=0;break;
//         case cs9:
//         level=(data[0]&0b00100000)!=0;break;
//         case cs10:
//         level=(data[0]&0b01000000)!=0;break;
//     }
//     return 0;
// }

// int CP2130::set_usb_config()
// {
//     char data[10]={0,0,0,0,0,0x00,0,0,0,0b11111111};
//     int result = usb_control_msg (fUsbHandle, 0x40, 0x61, 0, 0, data, 0x0A, fUsbTimeout);
//     return 0;
// }
// int CP2130::get_usb_config()
// {
//     char data[9]={0};
//     int result = usb_control_msg (fUsbHandle, 0xC0, 0x60, 0, 0, &data[0], 0x09, fUsbTimeout);
//     return 0;
// 	//printf ("%c\n",data[5]);
// }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

libusb_device_handle* CP2130_2S::setup_libusb_access()
{
    
std::cout << "CP2130 LibUSB Example" << std::endl;

    
    libusb_device_handle* cp2130Handle = NULL;
    
    
    // Initialize libusb
    if (libusb_init(&context) != 0)
        goto exit;
    
    // Search the connected devices to find and open a handle to the CP2130
    deviceCount = libusb_get_device_list(context, &deviceList);
    if (deviceCount <= 0)
        goto exit;
    for (int i = 0; i < deviceCount; i++)
    {
        if (libusb_get_device_descriptor(deviceList[i], &deviceDescriptor) == 0)
        {
            if ((deviceDescriptor.idVendor == 0x10C4) &&
                    (deviceDescriptor.idProduct == 0x87A0))
            {
                device = deviceList[i];
                break;
            }
        }
    }
    if (device == NULL)
    {
        std::cout << "ERROR: Device not found" << std::endl;
        goto exit;
    }
    
    // If a device is found, then open it
    if (libusb_open(device, &cp2130Handle) != 0)
    {
        std::cout << "ERROR: Could not open device" << std::endl;
        goto exit;
    }
    
    // See if a kernel driver is active already, if so detach it and store a
    // flag so we can reattach when we are done
    if (libusb_kernel_driver_active(cp2130Handle, 0) != 0)
    {
        libusb_detach_kernel_driver(cp2130Handle, 0); 
        kernelAttached = 1;
    }
 
    // Finally, claim the interface
    if (libusb_claim_interface(cp2130Handle, 0) != 0)
    {
        std::cout << "ERROR: Could not claim interface" << std::endl;
        goto exit;
    }

std::cout << cp2130Handle << std::endl; 
    return cp2130Handle;

    exit:
    // Cleanup and deinitialize libusb
     std::cout << "Exiting" << std::endl;
    if (cp2130Handle)
        libusb_release_interface(cp2130Handle, 0);
    if (kernelAttached)
        libusb_attach_kernel_driver(cp2130Handle, 0);
    if (cp2130Handle)
        libusb_close(cp2130Handle);
    if (deviceList)
        libusb_free_device_list(deviceList, 1);
    if (context)
        libusb_exit(context);
    
    return NULL;
    
}


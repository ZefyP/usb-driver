#include <cstring>
#include "USB_libusb.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>


std::vector<std::pair<int,int>> read_lpgbt_min_config(std::string file)
{
    std::ifstream myReadFile(file);
    std::vector<std::pair<int,int>> myreg;

    std::string line;
    while (std::getline(myReadFile, line))
	{
    std::stringstream ss(line);
    std::pair<int,int> reg;
    if (ss >> reg.first >> std::hex >> reg.second >> std::dec)
    {
	std::cout << reg.first << " " << std::hex<< +reg.second << std::dec<< std::endl;
	myreg.push_back(reg);
    }
	}
    return myreg;
}


int main(){
    auto cRegs = read_lpgbt_min_config("lpgbt_minimal_config.txt");
    // unsigned char reg_value_buf[333]={0x00,0x00,0x02,0x00,
    //                                     0x41,0x01,0x00,0x00,
    //                                     0x40,0x40,0x01,0x41};
    // for(unsigned short int i = 0; i < 317; i++){
    // reg_value_buf[i+12]=cRegs[i].second;
    // }
    // for (int reg_value : reg_value_buf)
    // {
    //     std::cout << reg_value <<  std::endl;
    // }
    float k;
    int m=0;
    bool wahr;
    unsigned char l;
    unsigned int test=0xabcd;
    //unsigned char read_input_buf[]={0x12,0x34,0xab,0xcd,0x00,0x00,0x00,0x00,
    // 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    // 0x00,0x00,(unsigned char)(test>>8),(unsigned char)(test)};
    // for(unsigned short int i = 0; i < sizeof(read_input_buf); i++){
    //     std::cout << std::hex << (int) read_input_buf[i] << std::dec << ' ';
    // }
    // std::cout << std::endl;
//     bool enable=true;
//     bool path=true;
//     int value=0xcdab;
//     unsigned char writeread_command_buf[] = {0x00,0x00, 0x02, 0x00, 
//     0x08, 0x00, 0x00, 0x00,
//     0x30,0x00,0x00,0x02,
//     (unsigned char)((unsigned char)((enable?1:0)<<7)|(unsigned char)((path?1:0)<<6)|((unsigned char)((value>>8)&0x0f))),
//     (unsigned char)value,0xFF 
//     };
//     for(unsigned short int i = 0; i < sizeof(writeread_command_buf); i++){
//         std::cout << std::hex << (int) writeread_command_buf[i] << std::dec << ' ';
// }
//     std::cout << std::endl;
//     std::cout <<"Set Load1: Enable? " <<enable<<" External "<<path<<" Value 0x"<<std::hex<<(value&0x0fff) << std::endl;
    // unsigned char read_input_buf[] = {0b11100101,0b11100101, 0b11100101, };   
    // bool output;
    // //unsigned char temp=(read_input_buf[s/8]&(0x80>>(s%8))>>(7-(s%8)));
    // const char *stateName[16] = {"P5V_overvoltage","P5V_undervoltage","P5V_overcurrent","P3V3_overvoltage","P3V3_undervoltage","P3V3_overcurrent","P2V5_overvoltage","P2V5_undervoltage","P2V5_overcurrent","P1V25_overvoltage","P1V25_undervoltage","P1V25_overcurrent","T1_error","T2_error","T3_error","T_SEH_error"};
    // for(unsigned short int s = 0; s < 16; s++){
    //     unsigned char temp=(read_input_buf[s/8]&(0x80>>(7-(s%8))))>>(s%8);
    //     std::cout<<stateName[s]<<": " <<std::hex<<(int)temp <<std::endl;
    // }
//     std::cout << std::endl;   
    // int temp=read_input_buf[m*2]<<(8) | read_input_buf[1+m*2];
    // std::cout <<  "0x"<<std::hex<<temp <<std::endl;
    // const char *supplyMeasurementName[10] ={"U_P5V", "I_P5V","U_P3V3", "I_P3V3","U_P2V5", "I_P2V5","U_P1V25", "I_P1V25","U_SEH", "I_SEH"};
    // std::cout<< supplyMeasurementName[m]<<": " <<"0x" << std::hex << (int) temp <<std::endl;

	TC_2SSEH cTC_2SSEH;

    //cTC_2SSEH.writeI2C(0x00,0x53,0x20);
    //cTC_2SSEH.writeI2C(0x00,0x53,0x20);
    //cTC_2SSEH.readI2C(0x00,0x53,l);

    //cTC_2SSEH.sendLPGBTconfig(reg_value_buf,sizeof(reg_value_buf));
    //-------------------------------------------
//     while(true){
//         cTC_2SSEH.read_hvmon(cTC_2SSEH.VHVJ8,k);
//         std::this_thread::sleep_for (std::chrono::milliseconds (200) );
//     }
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp1,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp2,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp3,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp_SEH,k);
    
//     cTC_2SSEH.read_supply(cTC_2SSEH.U_P5V,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.I_P5V,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.U_P3V3,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.I_P3V3,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.U_P2V5,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.I_P2V5,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.U_P1V25,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.I_P1V25,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.U_SEH,k);
//     cTC_2SSEH.read_supply(cTC_2SSEH.I_SEH,k);

//     cTC_2SSEH.read_load(cTC_2SSEH.U_P1V2_R,k);
//     cTC_2SSEH.read_load(cTC_2SSEH.I_P1V2_R,k);
//     cTC_2SSEH.read_load(cTC_2SSEH.U_P1V2_L,k);
//     cTC_2SSEH.read_load(cTC_2SSEH.I_P1V2_L,k);
    
//     cTC_2SSEH.read_hvmon(cTC_2SSEH.Mon,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp1,k);
//     cTC_2SSEH.read_hvmon(cTC_2SSEH.HV_meas,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp1,k);
//     cTC_2SSEH.read_hvmon(cTC_2SSEH.VHVJ7,k);
//     cTC_2SSEH.read_temperature(cTC_2SSEH.Temp1,k);
//     cTC_2SSEH.read_hvmon(cTC_2SSEH.VHVJ8,k);

//     cTC_2SSEH.read_state(cTC_2SSEH.P5V_overvoltage,wahr);
    
//     cTC_2SSEH.read_state(cTC_2SSEH.P5V_undervoltage,wahr);
//     cTC_2SSEH.read_reset(cTC_2SSEH.RST_CBC_L,k);
//     cTC_2SSEH.read_reset(cTC_2SSEH.RST_CBC_R,k);
//     cTC_2SSEH.read_reset(cTC_2SSEH.RST_CIC_L,k);
//     cTC_2SSEH.read_reset(cTC_2SSEH.RST_CIC_R,k);

//     cTC_2SSEH.set_HV(false,false,true,0x155);//0x155=100V
//     cTC_2SSEH.set_SehSupply(cTC_2SSEH.sehSupply_Off);
//     cTC_2SSEH.set_fuse(false);
//  cTC_2SSEH.read_i2c(0x00);
    //cTC_2SSEH.set_AMUX(0x3f01,0x7f01);
    //cTC_2SSEH.read_reset(cTC_2SSEH.RST_CBC_L,k);
    //cTC_2SSEH.toggle_led(); 
    //cTC_2SSEH.set_SehSupply(cTC_2SSEH.sehSupply_On);
    cTC_2SSEH.set_load1(true,false, 0x555);
    //cTC_2SSEH.set_load2(false,false, 0x00);
    //cTC_2SSEH.set_HV(true,true,true,0x55);
    //cTC_2SSEH.read_state(cTC_2SSEH.T_SEH_error,wahr);
    //cTC_2SSEH.set_limit(cTC_2SSEH.I_P1V25_max,0x34);
    //cTC_2SSEH.read_limit(cTC_2SSEH.I_P1V25_max,k);
    //cTC_2SSEH.set_fuse(false);
    
    //a test
    return 0;
}

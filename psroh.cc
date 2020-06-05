#include <cstring>
#include "USB_a.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

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
	//std::cout << reg.first << " " << std::hex<< +reg.second << std::dec<< std::endl;
	myreg.push_back(reg);
    }
	}
    return myreg;
}


int main(){
	TC_PSROH cTC_PSROH;
	auto cRegs = read_lpgbt_min_config("lpgbt_minimal_config.txt");
	for( auto reg : cRegs )
	{
        cTC_PSROH.write_i2c(reg.first,reg.second);
	}
	std::cout << "PUSM after def config \n";
	cTC_PSROH.read_i2c(0x1c7);

	//float result;
	cTC_PSROH.read_i2c(0x162);
	cTC_PSROH.read_i2c(0x18C);
        for(int a=96; a<=96 ; a++){
	cTC_PSROH.write_i2c(0x0F1,a);
	cTC_PSROH.write_i2c(0x0FF,a);
	cTC_PSROH.write_i2c(0x0F8,0);
	cTC_PSROH.write_i2c(0x0F2,0b00001011);
	cTC_PSROH.write_i2c(0x0F9,0b00001011);
	cTC_PSROH.write_i2c(0x100,0b00001011);	
	cTC_PSROH.write_i2c(0x0F6,0x0);
	cTC_PSROH.write_i2c(0x104,0x0);
	cTC_PSROH.write_i2c(0x0FD,0x0);
	cTC_PSROH.write_i2c(0x0F2,0b00000000);
	cTC_PSROH.write_i2c(0x0F9,0b00000000);
	cTC_PSROH.write_i2c(0x100,0b00000000);	
	cTC_PSROH.write_i2c(0x0F3,0b00000000);
	cTC_PSROH.write_i2c(0x0FA,0b00000000);
	cTC_PSROH.write_i2c(0x101,0b00000000);	
	cTC_PSROH.write_i2c(0x0F6,0xC);
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	cTC_PSROH.read_i2c(0x15F);
	cTC_PSROH.read_i2c(0x161);
	cTC_PSROH.read_i2c(0x162);
	cTC_PSROH.write_i2c(0x104,0xC);
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	cTC_PSROH.read_i2c(0x189);	
	cTC_PSROH.read_i2c(0x18B);
	cTC_PSROH.read_i2c(0x18C);
	cTC_PSROH.write_i2c(0x0FD,0x3);
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	cTC_PSROH.read_i2c(0x174);
	cTC_PSROH.read_i2c(0x176);
	cTC_PSROH.read_i2c(0x177);
	}
        //std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//cTC_PSROH.read_i2c(0x161);
	//cTC_PSROH.read_i2c(0x18B);
	//cTC_PSROH.read_i2c(0x176);
	//I2C MASTERS CKECK END//
	//FCMD check//
/*
	cTC_PSROH.write_i2c(0x11D,0xFF);
	cTC_PSROH.write_i2c(0x11E,0xC1);
	cTC_PSROH.write_i2c(0x11F,0xC1);
	cTC_PSROH.write_i2c(0x120,0xC1);
	cTC_PSROH.write_i2c(0x121,0xC1);
	cTC_PSROH.write_i2c(0x0A7,0xFF);
	cTC_PSROH.write_i2c(0x0A9,0xFF);
	cTC_PSROH.write_i2c(0x0AA,0xFF);
	cTC_PSROH.write_i2c(0x0AC,0x07);
	cTC_PSROH.write_i2c(0x0B0,0x07);
	cTC_PSROH.write_i2c(0x0B4,0x07);
	cTC_PSROH.write_i2c(0x0B8,0x07);
*/
	
	//CLK OUT TEST//
/*	
	cTC_PSROH.write_i2c(0x06E,0b00111100);
	cTC_PSROH.write_i2c(0x0A0,0b01111100);
	cTC_PSROH.write_i2c(0x078,0b00111101);
	cTC_PSROH.write_i2c(0x082,0b01111101);
*/

    return 0;
}

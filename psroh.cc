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
	/*
	std::cout << cTC_PSROH.read_i2c(0x1A1)<< "\n";
	cTC_PSROH.write_i2c(0x12C,0x00); 	
	cTC_PSROH.write_i2c(0x12C,0x40); 
	std::cout << cTC_PSROH.read_i2c(0x1A1)<< "\n";
	cTC_PSROH.write_i2c(0x12C,0x00); 
	std::cout << cTC_PSROH.read_i2c(0x12c)<< "\n";
	std::cout << cTC_PSROH.read_i2c(0x1A1)<< "\n";
	*/
	
       // while ((cTC_PSROH.read_i2c(0x1c7)&2 )) {std::cout << "doulepse\n";}
	
	//cTC_PSROH.toggle_2v5();
        //std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	//cTC_PSROH.toggle_2v5();
//	sleep(10);
	//cTC_PSROH.toggle_SCI2C();
	  	
	/*
	auto cRegs = read_lpgbt_min_config("lpgbt_minimal_config.txt");
	for( auto reg : cRegs )
	{
        cTC_PSROH.write_i2c(reg.first,reg.second);
	}
	std::cout << "PUSM after def config \n";
	*/

	std::cout << cTC_PSROH.read_i2c(0x1C7) << "\n";
	sleep(4);
	//fusing%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	/*
	cTC_PSROH.write_i2c(0x110,0xA3);//toggle_2v5 magic number
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control
	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x20); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0xF8); 
	cTC_PSROH.write_i2c(0x10B,0x24); 
	cTC_PSROH.write_i2c(0x10C,0x44); 
	cTC_PSROH.write_i2c(0x10D,0x55);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	int i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x24); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x55); 
	cTC_PSROH.write_i2c(0x10B,0x55); 
	cTC_PSROH.write_i2c(0x10C,0x55); 
	cTC_PSROH.write_i2c(0x10D,0x55);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x28); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x0F); 
	cTC_PSROH.write_i2c(0x10B,0x36); 
	cTC_PSROH.write_i2c(0x10C,0x00); 
	cTC_PSROH.write_i2c(0x10D,0x00);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x2C); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0xA0); 
	cTC_PSROH.write_i2c(0x10B,0x89); 
	cTC_PSROH.write_i2c(0x10C,0x99); 
	cTC_PSROH.write_i2c(0x10D,0x0A);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x30); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x1A); 
	cTC_PSROH.write_i2c(0x10B,0x2A); 
	cTC_PSROH.write_i2c(0x10C,0x3A); 
	cTC_PSROH.write_i2c(0x10D,0x0A);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x34); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x64); 
	cTC_PSROH.write_i2c(0x10B,0x00); 
	cTC_PSROH.write_i2c(0x10C,0x80); 
	cTC_PSROH.write_i2c(0x10D,0x18);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0x38); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x00); 
	cTC_PSROH.write_i2c(0x10B,0x40); 
	cTC_PSROH.write_i2c(0x10C,0x20); 
	cTC_PSROH.write_i2c(0x10D,0x03);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off

	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10F,0xEC); // Address low of 32bit block to be fused
	cTC_PSROH.write_i2c(0x10A,0x00); 
	cTC_PSROH.write_i2c(0x10B,0x00); 
	cTC_PSROH.write_i2c(0x10C,0x00); 
	cTC_PSROH.write_i2c(0x10D,0x07);
	cTC_PSROH.toggle_2v5(); //enable 2v5
        std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	cTC_PSROH.write_i2c(0x109,0xC1); //toggle_2v5 control on
	i=0;
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;std::cout << cTC_PSROH.read_i2c(0x1A1) << "\n";}
	cTC_PSROH.toggle_2v5(); //disable 2v5
	cTC_PSROH.write_i2c(0x109,0xC0); //toggle_2v5 control off
	*/
	/*
	cTC_PSROH.write_i2c(0x109,0xC2); //toggle_2v5 control read
	while(!(cTC_PSROH.read_i2c(0x1A1)&0b00000100)) {std::cout << "reading in progress\n";}
	cTC_PSROH.write_i2c(0x10E,0x00); // Address high of 32bit block to read
	cTC_PSROH.write_i2c(0x10F,0x9C); // Address low of 32bit block to read
	std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	std::cout << cTC_PSROH.read_i2c(0x1A2) << "\n";
	std::cout << cTC_PSROH.read_i2c(0x1A3) << "\n";
	std::cout << cTC_PSROH.read_i2c(0x1A4) << "\n";
	std::cout << cTC_PSROH.read_i2c(0x1A5) << "\n";
	std::cout << cTC_PSROH.read_i2c(0x1c7) << "\n";
	*/
	//if (cTC_PSROH.read_i2c(0x1c7)==0x12) std::cout << "doulepse\n";
	//float result;
	/*
	cTC_PSROH.write_i2c(0x12c,0x00);
	cTC_PSROH.write_i2c(0x12c,0x07);
	cTC_PSROH.write_i2c(0x12c,0x00);
	cTC_PSROH.read_i2c(0x162);
	cTC_PSROH.read_i2c(0x18C);
	//cTC_PSROH.write_i2c(0x0F7,0b01111000);
        for(int a=96; a<=96 ; a++){
	cTC_PSROH.write_i2c(0x0F1,a);
	cTC_PSROH.write_i2c(0x0FF,a);
	cTC_PSROH.write_i2c(0x0F8,0);
	cTC_PSROH.write_i2c(0x0F2,0b00001000);
	cTC_PSROH.write_i2c(0x0F9,0b00001000);
	cTC_PSROH.write_i2c(0x100,0b00001000);	
	cTC_PSROH.write_i2c(0x0F6,0x0);
	cTC_PSROH.write_i2c(0x104,0x0);
	cTC_PSROH.write_i2c(0x0FD,0x0);
	cTC_PSROH.write_i2c(0x0F2,0x0);
	cTC_PSROH.write_i2c(0x0F9,0x0);
	cTC_PSROH.write_i2c(0x100,0x0);	
	cTC_PSROH.write_i2c(0x0F3,0x0);
	cTC_PSROH.write_i2c(0x0FA,0x0);
	cTC_PSROH.write_i2c(0x101,0x0);	
	cTC_PSROH.write_i2c(0x0F6,0xC);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x15F);
	cTC_PSROH.read_i2c(0x161);
	cTC_PSROH.read_i2c(0x162);
	cTC_PSROH.write_i2c(0x104,0xC);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x189);	
	cTC_PSROH.read_i2c(0x18B);
	cTC_PSROH.read_i2c(0x18C);
	cTC_PSROH.write_i2c(0x0FD,0x2);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x174);
	cTC_PSROH.read_i2c(0x176);
	cTC_PSROH.read_i2c(0x177);
	}
        //std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//cTC_PSROH.read_i2c(0x161);
	//cTC_PSROH.read_i2c(0x18B);
	//cTC_PSROH.read_i2c(0x176);
	//I2C MASTERS CKECK END//
	*/
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
/*

	cTC_PSROH.dac_output(0);
	cTC_PSROH.write_i2c(0x111,0xF<<0);
	cTC_PSROH.write_i2c(0x113,1<<2);
	cTC_PSROH.write_i2c(0x01c,1<<7);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,(1<<7)|(1<<2));
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x1b8);
	cTC_PSROH.read_i2c(0x1b9);

	cTC_PSROH.dac_output(1000);
	cTC_PSROH.write_i2c(0x111,0xF<<0);
	cTC_PSROH.write_i2c(0x113,1<<2);
	cTC_PSROH.write_i2c(0x01c,1<<7);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,(1<<7)|(1<<2));
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x1b8);
	cTC_PSROH.read_i2c(0x1b9);
	cTC_PSROH.dac_output(4000);
	cTC_PSROH.write_i2c(0x111,0xF<<0);
	cTC_PSROH.write_i2c(0x113,1<<2);
	cTC_PSROH.write_i2c(0x01c,1<<7);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,(1<<7)|(1<<2));
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x1b8);
	cTC_PSROH.read_i2c(0x1b9);
*/

    return 0;
}

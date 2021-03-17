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
	//std::cout <<cTC_PSROH.read_i2c(0x1C7)<<"\n";

	cTC_PSROH.write_i2c(0x12c,0x00);
	cTC_PSROH.write_i2c(0x12c,0x07);
	cTC_PSROH.write_i2c(0x12c,0x00);
	int errors=0, repet=0, trials=0;
	unsigned int w1=3,w2=4,w3=5,w4=6;
	//enable clocks
	
	/*
	cTC_PSROH.write_i2c(0x06E,0b00111011);
	cTC_PSROH.write_i2c(0x0A0,0b00111011);
	cTC_PSROH.write_i2c(0x078,0b00111011);
	cTC_PSROH.write_i2c(0x082,0b00111011);
	*/
	cTC_PSROH.write_i2c(0x06E,0b01010100);
	cTC_PSROH.write_i2c(0x0A0,0b01010100);
	cTC_PSROH.write_i2c(0x078,0b01010100);
	cTC_PSROH.write_i2c(0x082,0b01010100);
	
	// enable front end chips
	cTC_PSROH.write_i2c(0x053,0b00000000);
	cTC_PSROH.write_i2c(0x05b,0b11111111);
	cTC_PSROH.write_i2c(0x055,0b11111111);
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	cTC_PSROH.write_i2c(0x053,0b00001011);
	//cTC_PSROH.write_i2c(0x053,0b00000001);

	/*
	cTC_PSROH.write_i2c(0x113,0b00000000);
	cTC_PSROH.write_i2c(0x112,0b00111111);
	int dacout=2000;
	for (dacout=0;dacout<4000;dacout=dacout+50){
	cTC_PSROH.dac_output(dacout);
	std::cout << dacout*1.25/4.096<< "	";
	cTC_PSROH.write_i2c(0x111,0b00111111);////////////////////mux
	cTC_PSROH.write_i2c(0x113,0b00000100);
	cTC_PSROH.write_i2c(0x01c,1<<7|25);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,0b10000100);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x1b8)<< "	"<<cTC_PSROH.read_i2c(0x1b9)<<"	";
	std::cout << (cTC_PSROH.read_i2c(0x1b8)&(0b00000011))*256+cTC_PSROH.read_i2c(0x1b9)<< "\n";
	}
	*/

	
	

	while(1){

	cTC_PSROH.write_i2c(0x111,0b00011111);////////////////1V
	//cTC_PSROH.write_i2c(0x111,0b01101111);////////////////////1v25 measure
	cTC_PSROH.write_i2c(0x113,0b00000100);
	cTC_PSROH.write_i2c(0x01c,1<<7|45);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,0b10000100);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	std::cout << "1V at panasonic connector=";
	std::cout << ((cTC_PSROH.read_i2c(0x1b8)&(0b00000011))*256+cTC_PSROH.read_i2c(0x1b9))/1.024<< "\n";


	cTC_PSROH.write_i2c(0x111,0b01101111);////////////////////1v25 measure
	cTC_PSROH.write_i2c(0x113,0b00000100);
	cTC_PSROH.write_i2c(0x01c,1<<7|45);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,0b10000100);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	std::cout << "1V25 @lpGBT=";
	std::cout << ((cTC_PSROH.read_i2c(0x1b8)&(0b00000011))*256+cTC_PSROH.read_i2c(0x1b9))*1.55/1.024<< "\n";
	/*
	std::cout << "Vtrx+ com"<< "\n";
	cTC_PSROH.write_i2c(0x0F8,0x50);//slave address
	cTC_PSROH.write_i2c(0x0F9,0b00010011); //control data
	cTC_PSROH.write_i2c(0x0FD,0x0);
	cTC_PSROH.write_i2c(0x0F9,0x0);
	cTC_PSROH.write_i2c(0x0FA,0x0);
	cTC_PSROH.write_i2c(0x0FB,0x0);
	cTC_PSROH.write_i2c(0x0FC,0x0);

	cTC_PSROH.write_i2c(0x0FD,0x2); //single byte write to start reading from 0x0
	//std::cout <<cTC_PSROH.read_i2c(0x176)<< "\n"; //status
	if(cTC_PSROH.read_i2c(0x176)!=4) errors++;	
	cTC_PSROH.write_i2c(0x0FD,0xD); //multi read
	//std::cout <<cTC_PSROH.read_i2c(0x176)<< "\n"; //status
	if(cTC_PSROH.read_i2c(0x176)!=4) errors++;	
	for(int a=0x186; a<=0x188 ; a++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(a)<< "\n";
	}

	
	cTC_PSROH.write_i2c(0x0F9,0x00);
	cTC_PSROH.write_i2c(0x0FA,w1);
	cTC_PSROH.write_i2c(0x0FB,w2);
	cTC_PSROH.write_i2c(0x0FC,w3);
	cTC_PSROH.write_i2c(0x0FD,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0FD,0xC); //multi send
	//std::cout <<cTC_PSROH.read_i2c(76)<< "\n"; //status
	if(cTC_PSROH.read_i2c(0x176)!=4) errors++;
	

	cTC_PSROH.write_i2c(0x0F9,0x0);
	cTC_PSROH.write_i2c(0x0FA,0x0);
	cTC_PSROH.write_i2c(0x0FB,0x0);
	cTC_PSROH.write_i2c(0x0FC,0x0);

	cTC_PSROH.write_i2c(0x0FD,0x2); //single byte write to start reading from 0x0
	//std::cout <<cTC_PSROH.read_i2c(0x176)<< "\n"; //status
	if(cTC_PSROH.read_i2c(0x176)!=4) errors++;	
	cTC_PSROH.write_i2c(0x0FD,0xD); //multi read
	//std::cout <<cTC_PSROH.read_i2c(0x176)<< "\n"; //status
	if(cTC_PSROH.read_i2c(0x176)!=4) errors++;	
	for(int a=0x186; a<=0x188 ; a++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(a)<< "\n";
	}
	if(cTC_PSROH.read_i2c(0x186)!=w3||cTC_PSROH.read_i2c(0x187)!=w2||cTC_PSROH.read_i2c(0x188)!=w1){
 	errors++;
	std::cout <<" vTRX+ write-read mismatch"<< "\n";}
	*/
	
	int address=32;
	
	std::cout << "PSFEHL com"<< "\n";
	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b00010011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2,0b00000011);
	cTC_PSROH.write_i2c(0x0F3,0b00000011);
	cTC_PSROH.write_i2c(0x0F4,w1);//
	cTC_PSROH.write_i2c(0x0F5,w2);//
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0
        //std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	cTC_PSROH.write_i2c(0x0F2,0b00001011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2, 0b00000011);
	cTC_PSROH.write_i2c(0x0F3, 0b00000011);
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
        trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b01000011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F6,0xD); //multi read
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	for(int k=0x171; k<=0x173 ; k++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(k)<< "\n";
	}
	if(cTC_PSROH.read_i2c(0x172)!=w2||cTC_PSROH.read_i2c(0x173)!=w1){
 	errors++;
	std::cout <<"SSA FARAWAY write-read mismatch"<< "\n";}

	address=39;
	
	std::cout << "PSFEHL com"<< "\n";
	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b00010011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2,0b00000011);
	cTC_PSROH.write_i2c(0x0F3,0b00000011);
	cTC_PSROH.write_i2c(0x0F4,w1);//
	cTC_PSROH.write_i2c(0x0F5,w2);//
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0
        //std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	cTC_PSROH.write_i2c(0x0F2,0b00001011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2, 0b00000011);
	cTC_PSROH.write_i2c(0x0F3, 0b00000011);
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
        trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b01000011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F6,0xD); //multi read
        std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	//if(cTC_PSROH.read_i2c(0x161)!=4) {errors++;std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";}
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	for(int k=0x171; k<=0x173 ; k++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(k)<< "\n";
	}
	if(cTC_PSROH.read_i2c(0x172)!=w2||cTC_PSROH.read_i2c(0x173)!=w1){
 	errors++;
	std::cout <<"SSA CLOSE write-read mismatch"<< "\n";}
	
	address=96;
	cTC_PSROH.write_i2c(0x0F0,0b00101000);//i2c config
	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b00010011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2,0b00000000);
	cTC_PSROH.write_i2c(0x0F3,0b00000000);
	cTC_PSROH.write_i2c(0x0F4,w1);//
	cTC_PSROH.write_i2c(0x0F5,w2);//
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0

	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
        trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}
	cTC_PSROH.write_i2c(0x0F2,0b00001011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F2, 0b00000000);
	cTC_PSROH.write_i2c(0x0F3, 0b00000000);
	cTC_PSROH.write_i2c(0x0F6,0x8); //store bytes to send
	cTC_PSROH.write_i2c(0x0F6,0xC); //multi byte write to start reading from 0x0
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	cTC_PSROH.write_i2c(0x0F1,address);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b01000011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);

	cTC_PSROH.write_i2c(0x0F6,0xD); //multi read
	//std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	trials=0;
	while(cTC_PSROH.read_i2c(0x161)!=4 && trials<1000) {trials++;}
	if(trials==100){errors++;}

	for(int k=0x172; k<=0x173 ; k++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(k)<< "\n";
	}

	if(cTC_PSROH.read_i2c(0x172)!=w2||cTC_PSROH.read_i2c(0x173)!=w1){
 	errors++;
	std::cout <<"CIC write-read mismatch"<< "\n";}
	std::cout <<"\n";
	
	repet++;
	std::cout <<"repet="<< repet<< "\n";
	std::cout <<"errors="<< errors<< "\n";
	w1++;w2++;w3++;;w4++;
	if (w1>15) w1=0; if (w2>15) w2=0; if (w3>15) w3=0; if (w4>15) w4=0;
	
	}

	/*for (int a=0;a<=123;a++){
	std::cout << "PSFEHL"<< "\n";
	cTC_PSROH.write_i2c(0x0F1,a);//slave address
	cTC_PSROH.write_i2c(0x0F2,0b00010011); //control data
	cTC_PSROH.write_i2c(0x0F6,0x0);
	cTC_PSROH.write_i2c(0x0F2,0x0);
	cTC_PSROH.write_i2c(0x0F3,0x0);
	cTC_PSROH.write_i2c(0x0F4,0x0);
	cTC_PSROH.write_i2c(0x0F5,0x0);

	cTC_PSROH.write_i2c(0x0F6,0x2); //single byte write to start reading from 0x0
	std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	cTC_PSROH.write_i2c(0x0F6,0xD); //multi read
	std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n"; //status
	for(int a=0x170; a<=0x173 ; a++){
	std::cout << "read back=";
	std::cout <<cTC_PSROH.read_i2c(a)<< "\n";
	}
	}*/

	//cTC_PSROH.read_i2c(0x162);
	//cTC_PSROH.read_i2c(0x18C);
	//cTC_PSROH.write_i2c(0x0F7,0b01111000);
       /* for(int a=96; a<=96 ; a++){
	cTC_PSROH.write_i2c(0x0F1,a);
	cTC_PSROH.write_i2c(0x0FF,a);
	cTC_PSROH.write_i2c(0x0F8,0x50);
	cTC_PSROH.write_i2c(0x0F2,0b00001000);
	cTC_PSROH.write_i2c(0x0F9,0b00001011);
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
	std::cout <<cTC_PSROH.read_i2c(0x161)<< "\n";
	cTC_PSROH.read_i2c(0x162);
	cTC_PSROH.write_i2c(0x104,0xC);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x189);	
	std::cout <<cTC_PSROH.read_i2c(0x18B)<< "\n";
	cTC_PSROH.read_i2c(0x18C);
	cTC_PSROH.write_i2c(0x0FD,0x2);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.read_i2c(0x174);
	std::cout <<cTC_PSROH.read_i2c(0x176)<< "\n";
	cTC_PSROH.read_i2c(0x177);
	}
	//CLK OUT TEST//
	
	cTC_PSROH.write_i2c(0x06E,0b00111011);
	cTC_PSROH.write_i2c(0x0A0,0b01111011);
	cTC_PSROH.write_i2c(0x078,0b00111011);
	cTC_PSROH.write_i2c(0x082,0b01111011);
*/
        //std::this_thread::sleep_for (std::chrono::milliseconds (100) ); 
	//cTC_PSROH.read_i2c(0x161);
	//cTC_PSROH.read_i2c(0x18B);
	//cTC_PSROH.read_i2c(0x176);
	/* ////////////////////////////////////////ADC measurements///////////////////////
	cTC_PSROH.write_i2c(0x113,0b00000000);
	cTC_PSROH.write_i2c(0x112,0b00111111);
	int dacout=2000;
	for (dacout=0;dacout<4000;dacout=dacout+50){
	cTC_PSROH.dac_output(dacout);
	std::cout << dacout*1.25/4.096<< "	";
	cTC_PSROH.write_i2c(0x111,0b11101110);////////////////////mux
	cTC_PSROH.write_i2c(0x113,0b00000100);
	cTC_PSROH.write_i2c(0x01c,1<<7);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	cTC_PSROH.write_i2c(0x113,0b10000100);
        std::this_thread::sleep_for (std::chrono::milliseconds (10) ); 
	//std::cout <<cTC_PSROH.read_i2c(0x1b8)<< "	"<<cTC_PSROH.read_i2c(0x1b9)<<"	";
	std::cout << (cTC_PSROH.read_i2c(0x1b8)&(0b00000011))*256+cTC_PSROH.read_i2c(0x1b9)<< "\n";	
	}
	*/
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
	std::cout <<cTC_PSROH.read_i2c(0x1C7)<<"\n";
	
	while(cTC_PSROH.read_i2c(0x1C7)==18){
	std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
	}	
	std::cout <<cTC_PSROH.read_i2c(0x1C7)<<"\n";
	*/
	//sleep(4);
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
	cTC_PSROH.write_i2c(0x11E,0xAA);
	cTC_PSROH.write_i2c(0x11F,0xAA);
	cTC_PSROH.write_i2c(0x120,0xAA);
	cTC_PSROH.write_i2c(0x121,0xAA);
	cTC_PSROH.write_i2c(0x0A7,0xFF);
	cTC_PSROH.write_i2c(0x0A9,0xFF);
	cTC_PSROH.write_i2c(0x0AA,0xFF);
	cTC_PSROH.write_i2c(0x0AC,0x07);
	cTC_PSROH.write_i2c(0x0B0,0x07);
	cTC_PSROH.write_i2c(0x0B4,0x07);
	cTC_PSROH.write_i2c(0x0B8,0x07);

	
	//CLK OUT TEST//
	
	cTC_PSROH.write_i2c(0x06E,0b00111011);
	cTC_PSROH.write_i2c(0x0A0,0b01111011);
	cTC_PSROH.write_i2c(0x078,0b00111011);
	cTC_PSROH.write_i2c(0x082,0b01111011);

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


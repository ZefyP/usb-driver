#include "TC_PSPOH.h"
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <ctime>  

bool reset_and_repeat(int times, TC_PSPOH child);

int main(int argc, char *argv[])
{
    uint32_t bus = std::atoi(argv[1]);
    uint8_t device = std::atoi(argv[2]);
    TC_PSPOH cTC_PSPOH( bus, device);
    // TC_PSPOH cTC_PSPOH;
    // std::cout << "Going to reset... " << std::endl;
    cTC_PSPOH.cpu_reset();
    cTC_PSPOH.reset_cp2130();
    // std::cout << "Exiting..." <<std::endl;

    std::string answer = " ";


    cTC_PSPOH.scpi_write("HIV ON\r\n",true);

    int resets = 0;


    while(true)
    {
        
            time_t time = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
            std::cout << ctime(&time)<< std::endl;  

            std::cout << "--------LOOP START--------" << std::endl;
            cTC_PSPOH.scpi_write("SET:LOAD 0.8\r\n",true); 

            cTC_PSPOH.scpi_write_readback("SET:LOAD?\r\n", answer, 256, true);            
            answer.clear();

            cTC_PSPOH.scpi_write_readback("MEAS:HIV:IN?\r\n", answer, 256, true);            
            answer.clear();

            cTC_PSPOH.scpi_write_readback("MEAS:HIV:CUR?\r\n", answer, 256, true);        
            answer.clear();    

            cTC_PSPOH.scpi_write_readback("MEAS:PIN?\r\n", answer, 256, true);            
            answer.clear();

            cTC_PSPOH.scpi_write_readback("MEAS:POUT?\r\n", answer, 256, true);          
            answer.clear();  

            cTC_PSPOH.scpi_write_readback("MEAS:EFF?\r\n", answer, 256, true);         
            answer.clear();   

            cTC_PSPOH.scpi_write_readback("MEAS:RIP?\r\n", answer, 256, true);        
            answer.clear();    

            cTC_PSPOH.scpi_write_readback("MEAS:TEMP?\r\n", answer, 256, true);         
            answer.clear();   


            // cTC_PSPOH.spi_write("SET:LOAD 0.8\r\n",true); 

            // cTC_PSPOH.spi_write("SET:LOAD?\r\n", true);      
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);      
            // answer.clear();

            // cTC_PSPOH.spi_write("MEAS:HIV:IN?\r\n", true);     
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);            
            // answer.clear();

            // cTC_PSPOH.spi_write("MEAS:HIV:CUR?\r\n", true);      
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);       
            // answer.clear();    

            // cTC_PSPOH.spi_write("MEAS:PIN?\r\n", true);        
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);         
            // answer.clear();

            // cTC_PSPOH.spi_write("MEAS:POUT?\r\n", true);       
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);        
            // answer.clear();  

            // cTC_PSPOH.spi_write("MEAS:EFF?\r\n", true);       
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);       
            // answer.clear();   

            // cTC_PSPOH.spi_write("MEAS:RIP?\r\n", true);      
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);       
            // answer.clear();    

            // cTC_PSPOH.spi_write("MEAS:TEMP?\r\n", true);      
            // cTC_PSPOH.wait_for_RTR();
            // cTC_PSPOH.spi_read(answer, 256, true);        
            // answer.clear();   
    }

    return 0;
}
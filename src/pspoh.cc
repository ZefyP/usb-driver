// initial libraries
#include <cstring>
#include "TC_PSPOH.h"
#include <chrono>
#include <ctime>  
#include <thread>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <fstream>
//#include <boost/algorithm/string.hpp> //for extract_val
#include <bits/stdc++.h>
//#define DEBUGO
//#define RESET

// power supply libraries
#include "DeviceHandler.h"
#include "PowerSupply.h"
#include "PowerSupplyChannel.h"
#include <boost/program_options.hpp> //!For command line arg parsing
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include "RohdeSchwarz.h"

// argument parcer module
//#include "test_options.h"

#include "temp_test_options.h"

using namespace std;
using namespace chrono;

/*!
 ************************************************
 * Main.
 ************************************************
 */

bool fileExists(const string &name);

vector<string> extract_val(string sentence);
string return_val( vector<string> values , int pos );

int main(int argc, char *argv[])
{
   // Create object for command argument parsing
   TemporaryCommandLineOptions cTemporaryCommandLineOptions(argc, argv);
         
   bool verbose = cTemporaryCommandLineOptions.get_verbose(); //later create get_verbose();
   //cout << "pipepath ; "<< cTemporaryCommandLineOptions.get_pipe_path() << "," << endl;

   //Files
   string fname_base = "./results/" + cTemporaryCommandLineOptions.get_new_directory();
   fname_base = fname_base + "/result" ;
   string ext= ".txt", fname;
   int cnt = 0;
   do{
      if(cnt!=0 && verbose){
         cout << "file exists : \"" << fname << "\"" << endl;
      }
      fname = fname_base + boost::lexical_cast<string>(cnt++)+ext;
   }while (fileExists(fname));
   
   cout << "creating file...\"" << fname << "\""<< endl;

   ofstream MyFile(fname);
   cout << "opening file..." << endl;
   if (MyFile.is_open()){

      //Hybrid Id
      MyFile << "****************************************************************************" << endl;
      string id = cTemporaryCommandLineOptions.get_hybridId();
      cout << "Hybrid ; " << id << endl << "-------------------------------------------------------------------------------" << endl;
      MyFile << "Hybrid ; " << id << "," << endl << "****************************************************************************" << endl;
   
      // string example = "HIV,END,2V44,HELLO,345^4,2.2222,,";
      // vector<string> v_example = extract_val(example);
      // string val = return_val(v_example , 1); // return the 2nd token of the sentence

      // MyFile << "your extracted value is " << val << endl ;

      
      //Time measurement
      cout << "calculating time..."<<endl;
      auto end = system_clock::now();
      auto start = system_clock::now();
      time_t start_time = system_clock::to_time_t(start);
      MyFile << "Started computation at " << ctime(&start_time)<< endl;  

      // Test Parameters
      int step = cTemporaryCommandLineOptions.get_step();
      int stepMax = cTemporaryCommandLineOptions.get_stepMax();
      MyFile << "maxLoad ; " << stepMax <<","<<endl<< "step ; " << step <<","<< endl;
   
      
/*!
 *** POWER SUPPLY **********************************************
 */
    cout << "-------------------------------------------------------------------------------" << endl; 
    cout << "Initialising power supply..." << endl;
    MyFile << "\nInitialising power supply..." << endl;

    std::string  docPath = cTemporaryCommandLineOptions.get_docPath();
    pugi::xml_document docSettings;
    DeviceHandler theHandler;
    theHandler.readSettings(docPath, docSettings);
    PowerSupply*        powerSupply;
    PowerSupplyChannel* channel1;
    PowerSupplyChannel* channel2;
    PowerSupplyChannel* channel3;
    PowerSupplyChannel* channel4;

    try
    {
        powerSupply = theHandler.getPowerSupply("MyRohdeSchwarz");
        channel1    = powerSupply->getChannel("LV_Module1");
        channel2    = powerSupply->getChannel("LV_Module2");
        channel3    = powerSupply->getChannel("LV_Module3");
        channel4    = powerSupply->getChannel("LV_Module4");
    }
    catch(const std::out_of_range& oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        throw std::out_of_range(oor.what());
    } 

    channel1->setVoltage(3.3);
    channel2->setVoltage(5.0);
    channel3->setVoltage(3.3);
    channel4->setVoltage(11.0);

    channel1->setCurrent(0.50);
    channel2->setCurrent(0.50);
    channel3->setCurrent(4.0);
    channel4->setCurrent(1.2);

    channel1->turnOn();
    channel2->turnOn();
    channel3->turnOn();
    channel4->turnOn();
    //allow a moment to stabilise supply input values
    std::this_thread::sleep_for(std::chrono::milliseconds(300)); //300ms min
    
    std::cout << "Channel 1 On: " << channel1->isOn()
              << std::endl
              //    << "OVP: " << channel1->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel1->getOutputVoltage() << std::endl
              << "Current: " << channel1->getCurrent() << std::endl;
    MyFile << "Channel 1: " << channel1->getOutputVoltage()<< " V, " << channel1->getCurrent() << " A " << endl;
               //wait();
    std::cout << "Channel 2 On: " << channel2->isOn()
              << std::endl
              //    << "OVP: " << channel2->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel2->getOutputVoltage() << std::endl
              << "Current: " << channel2->getCurrent() << std::endl;            
    MyFile << "Channel 2: " << channel2->getOutputVoltage()<< " V, " << channel2->getCurrent() << " A " << endl;
               //wait();
    std::cout << "Channel 3 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel3->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel3->getOutputVoltage() << std::endl
              << "Current: " << channel3->getCurrent() << std::endl;           
    MyFile << "Channel 3: " << channel3->getOutputVoltage()<< " V, " << channel3->getCurrent() << " A " << endl;
              //wait();
    std::cout << "Channel 4 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel4->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel4->getOutputVoltage() << std::endl
              << "Current: " << channel4->getCurrent() << std::endl;
    MyFile << "Channel 4: " << channel4->getOutputVoltage()<< " V, " << channel4->getCurrent() << " A " << endl;
    wait();
     // std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    std::cout << "-------------------------------------------------------------------------------" << endl;

 /*!
   *** TEST CARD **********************************************
  */
      //Local variables
      TC_PSPOH cTC_PSPOH;
      string answer ="";
      vector<string> v_answer;
      string val ="";
    
      std::cout << "-------------------------------------------------------------------------------" << endl;
      MyFile << "****************************************************************************" << endl;
    
      // cTC_PSPOH.spi_write("DEFIB\r\n",verbose);
      // MyFile << "card reset\r\n";
      
     
      for (size_t i = 0; i <= stepMax; i+=step)
      {
         //Card high input voltage 
         cTC_PSPOH.spi_write("HIV ON\r\n",verbose);
         MyFile << "HIV ; ON,\r\n";

         //Print supply status after turning on the test card
         
         // MyFile << "Channel 1: " << channel1->getOutputVoltage()<< " V, " << channel1->getCurrent() << " A " << endl;
         // MyFile << "Channel 2: " << channel2->getOutputVoltage()<< " V, " << channel2->getCurrent() << " A " << endl;
         // MyFile << "Channel 3: " << channel3->getOutputVoltage()<< " V, " << channel3->getCurrent() << " A " << endl;
         // MyFile << "Channel 4: " << channel4->getOutputVoltage()<< " V, " << channel4->getCurrent() << " A " << endl;
         // MyFile << "****************************************************************************" << endl;
    
         string load =  boost::lexical_cast<string>(float(i)/100);
         cTC_PSPOH.spi_write("SET:LOAD "+load+"\r\n",verbose);
         MyFile << "SET:LOAD ; "+load+","<<endl;

         //set load
         cTC_PSPOH.spi_write("SET:LOAD?\r\n",verbose);
         MyFile << "Load Setting: \r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
           // MyFile << answer << endl;
         }
         v_answer = extract_val(answer);
         MyFile << "LOAD_1v25L ; " << return_val(v_answer , 0) << "," << endl;
         MyFile << "LOAD_1v25R ; " << return_val(v_answer , 1) << "," << endl;
         MyFile << "LOAD_1v25T ; " << return_val(v_answer , 2) << "," << endl;
         MyFile << "LOAD_1vL ; "   << return_val(v_answer , 3) << "," << endl;
         MyFile << "LOAD_1vR ; "   << return_val(v_answer , 4) << "," << endl;

         cTC_PSPOH.spi_write("MEAS:HIV:IN?\r\n",verbose);
         MyFile << "Voltages:\r\n";
         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
            //MyFile << answer << endl;
         }
         v_answer = extract_val(answer);
         MyFile << "HIV ; "    << return_val(v_answer , 0) << "," << endl;
         MyFile << "2v55 ; "   << return_val(v_answer , 1) << "," << endl;
         MyFile << "1v25_L ; " << return_val(v_answer , 2) << "," << endl;
         MyFile << "1v25_R ; " << return_val(v_answer , 3) << "," << endl;
         MyFile << "1v25_T ; " << return_val(v_answer , 4) << "," << endl;
         MyFile << "1v_L ; "   << return_val(v_answer , 5) << "," << endl;
         MyFile << "1v_R ; "   << return_val(v_answer , 6) << "," << endl;

         cTC_PSPOH.spi_write("MEAS:HIV:CUR?\r\n",verbose);
         MyFile << "Currents:\r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
            //MyFile << answer << endl;
         }
         v_answer = extract_val(answer);
         MyFile << "HIV ; "    << return_val(v_answer , 0) << "," << endl;
         MyFile << "2v55 ; "   << return_val(v_answer , 1) << "," << endl;
         MyFile << "1v25_L ; " << return_val(v_answer , 2) << "," << endl;
         MyFile << "1v25_R ; " << return_val(v_answer , 3) << "," << endl;
         MyFile << "1v25_T ; " << return_val(v_answer , 4) << "," << endl;
         MyFile << "1v_L ; "   << return_val(v_answer , 5) << "," << endl;
         MyFile << "1v_R ; "   << return_val(v_answer , 6) << "," << endl;

         cTC_PSPOH.spi_write("MEAS:PIN?\r\n",verbose);
         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
         }
         MyFile << "Input Power ; " << answer << "," << endl;
         
         cTC_PSPOH.spi_write("MEAS:POUT?\r\n",verbose);
         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
         }
         MyFile << "Output Power ; " << answer << "," << endl;

         cTC_PSPOH.spi_write("MEAS:EFF?\r\n",verbose);
         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);    
         }
         MyFile << "Efficiency % ; " << answer << "," << endl;

         cTC_PSPOH.spi_write("MEAS:RIP?\r\n",verbose);
         MyFile << "Ripples:\r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
         }
         v_answer = extract_val(answer);
         MyFile << "2v55 ; " << return_val(v_answer , 0) << "," << endl;
         MyFile << "1v25 ; " << return_val(v_answer , 1) << "," << endl;
         MyFile << "1V ; "   << return_val(v_answer , 2) << "," << endl;
         
         cTC_PSPOH.spi_write("MEAS:TEMP?\r\n",verbose);
         MyFile << "Temperature PCB, AMB, HYB, ptatOffset, PTAT \r\n";
         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
         }
         v_answer = extract_val(answer);
         MyFile << "PCB ; "    << return_val(v_answer , 0) << "," << endl;
         MyFile << "AMB ; "    << return_val(v_answer , 1) << "," << endl;
         MyFile << "HYB ; "    << return_val(v_answer , 2) << "," << endl;
         MyFile << "PTAT ; "   << return_val(v_answer , 4) << "," << endl;
         MyFile << "offset ; " << return_val(v_answer , 3) << "," << endl;

         MyFile << "-------------------------------------------------------------------------------" << endl;
         if(verbose) {cout << "-------------------------------------------------------------------------------" << endl;}
      }

      std::cout << "Turning off" << std::endl;
      MyFile << "Turning off... " << endl;
      
      cTC_PSPOH.spi_write("SET:LOAD 0\r\n",verbose);
      MyFile << "SET:LOAD 0\r\n";

      cTC_PSPOH.spi_write("HIV OFF\r\n",verbose);
      MyFile << "HIV OFF\r\n";
      MyFile << "Power Supply OFF\r\n";
      cTC_PSPOH.system_reset();
      end = system_clock::now();

      //Time measurement
      duration<double> elapsed_seconds = end-start;
      time_t end_time = system_clock::to_time_t(end);

      cout << endl << "Finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
      MyFile << endl << "Finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
      MyFile << "****************************************************************************" << endl;
     
      MyFile.close();

      
      /***SUPPLY TURN OFF***/
      channel1->turnOff();
      channel2->turnOff();
      channel3->turnOff();
      channel4->turnOff();
      std::cout << "CH 1 " << channel1->isOn() << std::endl;
      std::cout << "CH 2 " << channel2->isOn() << std::endl;
      std::cout << "CH 3 " << channel3->isOn() << std::endl;
      std::cout << "CH 4 " << channel4->isOn() << std::endl;
      cout << "-------------------------------------------------------------------------------" << endl;
   
   }

   return 0;
}


bool fileExists(const string &name){
    ifstream ifile;
    ifile.open(&name[0]);
    if(ifile){
        ifile.close();
        return true;
    }
    else{
        return false;
    }
}

//separates sentence in tokens
vector<string> extract_val(string sentence ){
   vector <string> v;
   stringstream all_values(sentence);

   while (all_values.good( )){
      string val;
      getline(all_values,val,',');
      v.push_back(val);
   }

   // for (size_t i=0; i<v.size(); i++){
   //    cout << v[i] << endl;

   // }
   return v; 
}

//returns desired extracted token
string return_val( vector<string> values , int pos ){
   string extracted_value = values[pos];
   return extracted_value;
}
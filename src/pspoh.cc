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
#include <sstream>
#include <bits/stdc++.h>
//#define DEBUGO
//#define RESET

// power supply libraries
#include "DeviceHandler.h"
#include "PowerSupply.h"
#include "PowerSupplyChannel.h"
#include <boost/program_options.hpp> //!For command line arg parsing
#include <iomanip>
#include <limits>
#include "RohdeSchwarz.h"

// argument parcer module
#include "temp_test_options.h"

#include "gui_logger.h"

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
bool scpi_error_occured(string sentence);

int main(int argc, char *argv[])
{
   // Create object for command argument parsing
   TemporaryCommandLineOptions cTemporaryCommandLineOptions(argc, argv);
         
   bool verbose = cTemporaryCommandLineOptions.get_verbose();
   bool cGui = cTemporaryCommandLineOptions.get_usegui();
   bool useVector = cTemporaryCommandLineOptions.get_usevector();
   
   if( cGui ){
      gui::init( argv [ argc - 1 ] );
      gui::message("hello gui");
      gui::status("Test has started please wait");
      gui::progress(0.1/10.0);
   }

   //Files
   string fname_base = "./results/" + cTemporaryCommandLineOptions.get_new_directory();
   fname_base = fname_base + "/result" ;
   string ext= ".txt", fname;
   int cnt = 0;
   // fname = fname_base + boost::lexical_cast<string>(cnt++)+ext;
   do {
      if(cnt!=0 && verbose){
         std::cout << "file exists : \"" << fname << "\"" << endl;
      }
      fname = fname_base + boost::lexical_cast<string>(cnt++)+ext;

   }while (fileExists(fname));
   std::cout << "path is----------------->"<<  fname << endl;
   if( cGui ){
      gui::data("ResultsDirectory",fname.c_str()); //sending the results directory path to the gui
   }
   
   std::cout << "creating file...\"" << fname << "\""<< endl;

   ofstream MyFile(fname);
   std::cout << "opening file..." << endl;
   if (MyFile.is_open()){
      std::cout << "opened file" << endl;
      //Hybrid Id
      //MyFile << "****************************************************************************" << endl;
      string id = cTemporaryCommandLineOptions.get_hybridId();
      std::cout << "Hybrid ; " << id << endl << "-------------------------------------------------------------------------------" << endl;
      MyFile << "Hybrid ; " << id << endl;
      //Time measurement
      std::cout << "calculating time..."<<endl;
      auto end = system_clock::now();
      auto start = system_clock::now();
      time_t start_time = system_clock::to_time_t(start);
      // Test Parameters
      int step = cTemporaryCommandLineOptions.get_step();
      int stepMax = cTemporaryCommandLineOptions.get_stepMax();
      MyFile << "maxLoad ; " << stepMax << endl << "step ; " << step << endl;
      int stepMin = cTemporaryCommandLineOptions.get_stepMin();
      MyFile << "minLoad ; " << stepMin << endl;
      int supstep = cTemporaryCommandLineOptions.get_supply_step();
      int supmin = cTemporaryCommandLineOptions.get_supply_min();
      int supmax = cTemporaryCommandLineOptions.get_supply_max();
      MyFile << "SupStep ; " << supstep << endl;
      MyFile << "SupMin ; " << supmin << endl;
      MyFile << "SupMax ; " << supmax << endl;
      std::vector<int> arr_load_settings = {0,80,100,120};
      
/*!
 *** POWER SUPPLY **********************************************
 */
    std::cout << "-------------------------------------------------------------------------------" << endl; 
    std::cout << "Initialising power supply..." << endl;
    MyFile << "\nSupply ; INIT\r" << endl;

    
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


    channel1 -> setOverVoltageProtection(4.0);
    channel2 -> setOverVoltageProtection(6.0);
    channel3 -> setOverVoltageProtection(4.0);
    channel4 -> setOverVoltageProtection(12.0);

    channel1->setVoltage(3.5);
    channel2->setVoltage(5.0);
    channel3->setVoltage(3.3);
    channel4->setVoltage(11.0);

    channel1->setCurrent(4.0);
    channel2->setCurrent(0.5);
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
     MyFile << "CH 1: V ; " << channel1->getOutputVoltage()<< endl << " CH 1: A ; " << channel1->getCurrent() << endl;
               //wait();
    std::cout << "Channel 2 On: " << channel2->isOn()
              << std::endl
              //    << "OVP: " << channel2->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel2->getOutputVoltage() << std::endl
              << "Current: " << channel2->getCurrent() << std::endl;            
    MyFile << "CH 2: V ; " << channel2->getOutputVoltage()<< endl << "CH 2: A ; " << channel2->getCurrent() << endl;
               //wait();
    std::cout << "Channel 3 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel3->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel3->getOutputVoltage() << std::endl
              << "Current: " << channel3->getCurrent() << std::endl;           
    MyFile << "CH 3: V ; " << channel3->getOutputVoltage()<< endl << "CH 3: A ; " << channel3->getCurrent() << endl;
              //wait();
    std::cout << "Channel 4 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel4->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel4->getOutputVoltage() << endl
              << "Current: " << channel4->getCurrent() << endl;
    MyFile << "CH 4: V ; " << channel4->getOutputVoltage()<< endl << " CH 4: A ; " << channel4->getCurrent() << endl;
    wait();
     // std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    std::cout << "-------------------------------------------------------------------------------" << endl;
 /*!
   *** TEST CARD **********************************************
  */
      //Local variables
      TC_PSPOH cTC_PSPOH;
      cTC_PSPOH.cpu_reset();
      string answer ="";
      vector<string> v_answer;
      string val ="";
      MyFile << "Started computation at ; " << ctime(&start_time)<< endl;  
      MyFile << "header-end ; 0" << endl << endl;
      std::cout << "-------------------------------------------------------------------------------" << endl;
      
      bool turn_on = true;
      int selectedLoad = 0;
      
      for (int sup_volt = supmin; sup_volt < (supmax+ supstep*0.5); sup_volt +=supstep){
         channel4->setVoltage( ((float)sup_volt) /10 ); //! because the test parameter calls 105 instead of 10.5 V
         //channel2->setCurrent(1.0);
         MyFile << "\nSET:VIN ; "<< (float)sup_volt/10 << endl;
         if(verbose) {std::cout << "-------------->SET:VIN ;"<< sup_volt << endl;}
         
         if (turn_on == true)
         {
         // Card high input voltage 
            cTC_PSPOH.spi_write("HIV ON\r\n",verbose);
            MyFile << "HIV ; ON\r\n";
            turn_on = false;
         }

         stepMin = cTemporaryCommandLineOptions.get_stepMin();
         
         if(useVector)
         {
            stepMin = 0;
            stepMax = arr_load_settings.size() -1 ; 
            step = 1;
         }
         
         //for (size_t i = 0; i <= stepMax; i+=step) //(temp!!!) uncomment for load sweep to stepMax
         //for ( auto selectedLoad : arr_load_settings)
         for (int index = stepMin ; index <= stepMax; index+=step)
         {
            if(useVector)
            {
               selectedLoad = arr_load_settings[index];
            }else{
               selectedLoad = index;
            }

            //Print supply status after turning on the test card 
            MyFile << "CH 1: V ; " << channel1->getOutputVoltage()<< endl << "CH 1: A ; " << channel1->getCurrent() << endl;
            MyFile << "CH2 V ; " << channel2->getOutputVoltage()<< endl << "CH2 A ; " << channel2->getCurrent() << endl;
            MyFile << "CH 3: V ; " << channel3->getOutputVoltage()<< endl << "CH 3: A ; " << channel3->getCurrent() << endl;
            MyFile << "CH 4: V ; " << channel4->getOutputVoltage()<< endl << "CH 4: A ; " << channel4->getCurrent() << endl;
            
            string load =  boost::lexical_cast<string>( float(selectedLoad) /100 ); 
            cTC_PSPOH.spi_write("SET:LOAD "+load+"\r\n",verbose);
            MyFile << "SET:LOAD ; "+load+"\r\n"<<endl;

            //set load
            cTC_PSPOH.spi_write("SET:LOAD?\r\n",verbose);
         
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
            // MyFile << answer << endl;
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            v_answer = extract_val(answer);
            MyFile << "LOAD_1v25L ; " << return_val(v_answer , 0) << endl;
            MyFile << "LOAD_1v25R ; " << return_val(v_answer , 1) << endl;
            MyFile << "LOAD_1v25T ; " << return_val(v_answer , 2) << endl;
            MyFile << "LOAD_1vL ; "   << return_val(v_answer , 3) << endl;
            MyFile << "LOAD_1vR ; "   << return_val(v_answer , 4) << endl;

            cTC_PSPOH.spi_write("MEAS:HIV:IN?\r\n",verbose);
            //MyFile << "Voltages:\r\n";
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
               //MyFile << answer << endl;
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            v_answer = extract_val(answer);
            MyFile << "V_HIV ; "    << return_val(v_answer , 0) << endl;
            MyFile << "V_2v55 ; "   << return_val(v_answer , 1) << endl;
            MyFile << "V_1v25_L ; " << return_val(v_answer , 2) << endl;
            MyFile << "V_1v25_R ; " << return_val(v_answer , 3) << endl;
            MyFile << "V_1v25_T ; " << return_val(v_answer , 4) << endl;
            MyFile << "V_1v_L ; "   << return_val(v_answer , 5) << endl;
            MyFile << "V_1v_R ; "   << return_val(v_answer , 6) << endl;

            cTC_PSPOH.spi_write("MEAS:HIV:CUR?\r\n",verbose);
            //MyFile << "Currents:\r\n";

            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
               //MyFile << answer << endl;
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            v_answer = extract_val(answer);
            MyFile << "C_HIV ; "    << return_val(v_answer , 0) << endl;
            MyFile << "C_2v55 ; "   << return_val(v_answer , 1) << endl;
            MyFile << "C_1v25_L ; " << return_val(v_answer , 2) << endl;
            MyFile << "C_1v25_R ; " << return_val(v_answer , 3) << endl;
            MyFile << "C_1v25_T ; " << return_val(v_answer , 4) << endl;
            MyFile << "C_1v_L ; "   << return_val(v_answer , 5) << endl;
            MyFile << "C_1v_R ; "   << return_val(v_answer , 6) << endl;

            // MyFile << "Power: \n";
            cTC_PSPOH.spi_write("MEAS:PIN?\r\n",verbose);
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }


            v_answer = extract_val(answer);
            MyFile << "P_IN ; " << answer;
            cTC_PSPOH.spi_write("MEAS:POUT?\r\n",verbose);
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }

            v_answer = extract_val(answer);
            MyFile << "P_OUT ; " << answer;
            cTC_PSPOH.spi_write("MEAS:EFF?\r\n",verbose);
            //MyFile << "Efficiency:\r\n";
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);    
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            MyFile << "EFF_% ; " << answer << "\r" <<endl;

            cTC_PSPOH.spi_write("MEAS:RIP?\r\n",verbose);
            //MyFile << "Ripples (V):\r\n";
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            v_answer = extract_val(answer);
            MyFile << "R_2v55 ; " << return_val(v_answer , 0) << endl;
            MyFile << "R_1v25 ; " << return_val(v_answer , 1) << endl;
            MyFile << "R_1V ; "   << return_val(v_answer , 2) << endl;
            
            cTC_PSPOH.spi_write("MEAS:TEMP?\r\n",verbose);
            //MyFile << "Temperature\r\n";
            if(cTC_PSPOH.wait_for_RTR()==0){
               cTC_PSPOH.spi_read(answer,256,verbose);
            }else{

               cTC_PSPOH.cpu_reset();
               index = index - step;
               continue;
               //+ create flag for repeat test
            }
            v_answer = extract_val(answer);
            MyFile << "T_PCB ; "    << return_val(v_answer , 0) << endl;
            MyFile << "T_AMB ; "    << return_val(v_answer , 1) << endl;
            MyFile << "T_HYB ; "    << return_val(v_answer , 2) << endl;
            MyFile << "T_PTAT ; "   << return_val(v_answer , 3) << endl;
            MyFile << "PTAT_offset ; " << return_val(v_answer , 4) << endl;

            
            if( cGui ){
               if( std::find( arr_load_settings.begin(), arr_load_settings.end(), selectedLoad) != arr_load_settings.end() )
                  gui::progress( float( 1+std::distance(arr_load_settings.begin(), std::find(arr_load_settings.begin(), arr_load_settings.end(), selectedLoad) ) ) / (arr_load_settings.size() + 2) );
            }

            if(verbose) {std::cout << "-------------------------------------------------------------------------------" << endl;}
         } // end load loop
        
      } // end supply loop

      std::cout << "Turning off ; 0" << std::endl;
      MyFile << "Turning off ; 0" << endl;
      
      cTC_PSPOH.spi_write("SET:LOAD 0\r\n",verbose);
      MyFile << "SET:LOAD ; 0\r\n";

      cTC_PSPOH.spi_write("HIV OFF\r\n",verbose);
      MyFile << "HIV ; OFF\r\n";
      MyFile << "Supply ; OFF\r\n";
      //cTC_PSPOH.system_reset();
      end = system_clock::now();

      //Time measurement
      duration<double> elapsed_seconds = end-start;
      time_t end_time = system_clock::to_time_t(end);

      std::cout << endl << "Finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
      MyFile << endl << "Finished computation at ; " << ctime(&end_time) << endl << "elapsed time(s);" << elapsed_seconds.count() << endl;
     
      MyFile.close();

     /*
      //SUPPLY TURN OFF
      channel1->turnOff();
      channel2->turnOff();
      channel3->turnOff();
      channel4->turnOff();
      std::cout << "CH 1 ;" << channel1->isOn() << std::endl;
      std::cout << "CH 2 ;" << channel2->isOn() << std::endl;
      std::cout << "CH 3 ;" << channel3->isOn() << std::endl;
      std::cout << "CH 4 ;" << channel4->isOn() << std::endl;
      cout << "-------------------------------------------------------------------------------" << endl;
      
     */ 
     
   }
   
   if( cGui ){
      gui::progress(10.0/10.0);
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



bool scpi_error_occured(string sentence){
      // if SCPI ERROR occured
   string s = "SCPI ERROR;";
   bool exists = false;

   // turn stringstream into string pointer
   //const std::string& sentence_ptr = sentence();   

   // if SCPI string exists in sentence
   if ( strstr( s.c_str(), sentence.c_str() ) )
   {
      std::cout << sentence << endl;
      exists = true;
   }
   return exists;
}

//separates a  sentence in tokens
vector<string> extract_val(string sentence ){
   vector <string> v;
   stringstream all_values(sentence);   
   while (all_values.good( )){
      string val;
      getline(all_values,val,',');
      v.push_back(val);

   }

   //check for SCPI error in the result
      if ( scpi_error_occured(all_values.str()) ){
         exit(22);
      }
   return v; 
}

//returns desired extracted token
string return_val( vector<string> values , int pos ){
   string extracted_value = values[pos];
   return extracted_value;
}

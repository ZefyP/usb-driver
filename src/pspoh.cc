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

using namespace std;
using namespace chrono;
namespace po = boost::program_options;


bool verbose,useGui;
int step,ID;

/*!
************************************************
* Argument parser.
************************************************
*/
//-------------------------------------------------------------------------
// Handle command line options for pspoh
//
// Options:
// [-h|--help]                Show help menu
// [-t|--time]                  time
// [-G|--useGui                a flag
// [-f]--file ARG (string)    Input file
// [--value] ARG (int)User value
//
// example command: pspoh -f ../results1.txt --time -35000.2 --value 42 -G
// --------------------------------------------------------------------------

po::variables_map process_program_options(const int argc, const char* const argv[])
{
    po::options_description desc("Allowed options");

    desc.add_options()
         ("help,h", "produce help message")
         ("config,c", po::value<string>()->default_value("default"),"set configuration file path (default files defined for each test) " "...")
         ("verbose,v", po::value<string>()->implicit_value("0"), "verbosity level")
         ("step,s", po::value< int > (&step)-> default_value(10), "Load percentage step from NO LOAD to 120pc of the nominal values" )
         ("useGui,G",po::value<bool>(&useGui)-> default_value(false),"use the Gui")
         ("hybridId,id", po::value<string>() (&ID)-> implicit_value(000000000),"Scanned hybrid module ID");
    //Parses the command line
    po::variables_map vm;
    try
    {
       //Parsing and storing args
        po::store(po::parse_command_line(argc, argv, desc), vm);
    }
    catch(po::error const& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
    //Must be called after parsing and storing
    po::notify(vm);

    // Help Option
    if(vm.count("help"))
    {
        cout << desc << "\n";
        return 0;
    }

    //Test Card objects

     if(vm.count( "verbose") )
     {
         verbose = true;
         cout << argc-1 << " args was given to this program. These are: " << endl;
         for (size_t i = 1; i < argc; i++){
            cout << argv[i] << endl;
         }
     }
      if(vm.count("step") )
      {
         //step = atoi(argv[2] ) ;
         cout << "the step is: \"" << step << "\"" << endl;
      }

      // Power supply object object
     if(vm.count("object"))
      { 
       cout << "Object to initialize set to " << vm["object"].as<string>() << endl; 
      }

      // GUI Object
      if(vm.count("useGui"))
      {
         cout << "use GUI application " << vm["useGui"].as<bool>() << endl;
      }

    return vm;
}

/*!
 ************************************************
 * Main.
 ************************************************
 */

bool fileExists(const string &name);

int main(int argc, char *argv[])
{
   
   boost::program_options::variables_map v_map = process_program_options(argc, argv);

   if (argc > 1)
   {
      //Set verbose if it is asked
   //    if(string(argv[1]) == "-v"){
   //       verbose = true;
   //       cout << argc-1 << " args was given to this program :" << endl;
   //       for (size_t i = 1; i < argc; i++){
   //          cout << argv[i] << endl;
   //       }
   //    }  
    }


   // int step = atoi(argv[2] ) ;
   // cout << "the step is: \"" << step << "\"" << endl;

   //Files
   string fname_base = "./results/result", ext = ".txt", fname;
   int cnt = 0;

   do{
      if(cnt!=0 && verbose){
         cout << "file exist : \"" << fname << "\"" << endl;
      }
      fname = fname_base + boost::lexical_cast<string>(cnt++)+ext;
   }while (fileExists(fname));
   
   cout << "creating file...\"" << fname << "\""<< endl;

   ofstream MyFile(fname);
   cout << "opening file..." << endl;
   if (MyFile.is_open()){

    cout << "calculating time..."<<endl;
      //Time measurement
      auto end = system_clock::now();
      auto start = system_clock::now();
      time_t start_time = system_clock::to_time_t(start);
      MyFile << "Started computation at " << ctime(&start_time)<< endl;



/*!
 *** POWER SUPPLY **********************************************
 */
    std::cout << "-------------------------------------------------------------------------------" << endl;
    std::cout << "Initializing power supply..." << std::endl;

    std::string        docPath = v_map["config"].as<string>();
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
        
        //        channel4    = powerSupply->getChannel("LV_Module4");
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


    std::cout << "Channel 1 On: " << channel1->isOn()
              << std::endl
              //    << "OVP: " << channel1->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel1->getOutputVoltage() << std::endl
              << "Current: " << channel1->getCurrent() << std::endl;
               //wait();
    std::cout << "Channel 2 On: " << channel2->isOn()
              << std::endl
              //    << "OVP: " << channel2->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel2->getOutputVoltage() << std::endl
              << "Current: " << channel2->getCurrent() << std::endl;
               //wait();
    std::cout << "Channel 3 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel3->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel3->getOutputVoltage() << std::endl
              << "Current: " << channel3->getCurrent() << std::endl;
              //wait();
    std::cout << "Channel 4 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel4->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel4->getOutputVoltage() << std::endl
              << "Current: " << channel4->getCurrent() << std::endl;
    wait();
     // std::this_thread::sleep_for(std::chrono::milliseconds(500)); 



    std::cout << "-------------------------------------------------------------------------------" << endl;
      
     /*!
      *** TEST CARD **********************************************
     */
      //Local variables
      TC_PSPOH cTC_PSPOH;
      string answer ="";

      // cTC_PSPOH.spi_write("DEFIB\r\n",verbose);
      // MyFile << "card reset\r\n";
      
      for (size_t i = 0; i <= 5; i+=step)
      {

         cTC_PSPOH.spi_write("HIV ON\r\n",verbose);
         MyFile << "HIV ON\r\n";

         string load =  boost::lexical_cast<string>(float(i)/100);
         cTC_PSPOH.spi_write("SET:LOAD "+load+"\r\n",verbose);
         MyFile << "SET:LOAD "+load+"\r\n";

         cTC_PSPOH.spi_write("SET:LOAD?\r\n",verbose);
         MyFile << "SET:LOAD?\r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
            MyFile << answer << endl;
         }

         cTC_PSPOH.spi_write("MEAS:HIV:IN?\r\n",verbose);
         MyFile << "MEAS:HIV:IN?\r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
            MyFile << answer << endl;
         }

         cTC_PSPOH.spi_write("MEAS:RIP?\r\n",verbose);
         MyFile << "MEAS:RIP?\r\n";

         if(cTC_PSPOH.wait_for_RTR()==0){
            cTC_PSPOH.spi_read(answer,256,verbose);
            MyFile << answer << endl;
         }
         MyFile << "-------------------------------------------------------------------------------" << endl;
         std::cout << "-------------------------------------------------------------------------------" << endl;
      }

      std::cout << "Turning off" << std::endl;
      
      cTC_PSPOH.spi_write("SET:LOAD 0\r\n",verbose);
      MyFile << "SET:LOAD 0\r\n";
      cTC_PSPOH.system_reset();
      end = system_clock::now();

      //Time measurement
      duration<double> elapsed_seconds = end-start;
      time_t end_time = system_clock::to_time_t(end);
      
      MyFile << endl << "finished computation at " << ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
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
      std::cout << "-------------------------------------------------------------------------------" << endl;
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


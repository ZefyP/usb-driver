//initial libraries
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


using namespace std;
using namespace chrono;
namespace po = boost::program_options;


bool verbose;
int step;

/*!
************************************************
* Argument parser.
************************************************
*/
po::variables_map process_program_options(const int argc, const char* const argv[])
{
    po::options_description desc("Allowed options");

    desc.add_options()
         ("help,h", "produce help message")
         ("config,c", po::value<string>()->default_value("default"),"set configuration file path (default files defined for each test) " "...")
         ("verbose,v", po::value<string>()->implicit_value("0"), "verbosity level")
         ("step,s", po::value< int > (&step)-> default_value(10), "Load percentage step from NO LOAD to 120pc of the nominal values" );

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

    // Power supply object option
    if(vm.count("object"))
    { 
       cout << "Object to initialize set to " << vm["object"].as<string>() << endl; 
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
   
   cout << "creating file \"" << fname << "\""<< endl;

   ofstream MyFile(fname);
   cout << "before filie open" << endl;
   if (MyFile.is_open()){

    cout << "after file open"<<endl;
      //Time measurement
      auto end = system_clock::now();
      auto start = system_clock::now();
      time_t start_time = system_clock::to_time_t(start);
      MyFile << "Started computation at " << ctime(&start_time)<< endl;



/*!
 *** POWER SUPPLY **********************************************
 */
    
    std::cout << "Initializing power supply..." << std::endl;

    std::string        docPath = v_map["config"].as<string>();
    pugi::xml_document docSettings;

    DeviceHandler theHandler;
    theHandler.readSettings(docPath, docSettings);
    PowerSupply*        powerSupply;
    PowerSupplyChannel* channel1;
    PowerSupplyChannel* channel2;
    PowerSupplyChannel* channel3;

    try
    {
        powerSupply = theHandler.getPowerSupply("MyRohdeSchwarz");
        channel1    = powerSupply->getChannel("LV_Module1");
        channel2    = powerSupply->getChannel("LV_Module2");
        channel3    = powerSupply->getChannel("LV_Module3");
        //        channel4    = powerSupply->getChannel("LV_Module4");
    }
    catch(const std::out_of_range& oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        throw std::out_of_range(oor.what());
    } 

    channel1->setVoltage(1.25);
    channel2->setVoltage(1.1222);
    channel3->setVoltage(1.1333);

    channel1->setCurrent(0.71);
    channel2->setCurrent(0.72);
    channel3->setCurrent(0.73);

    channel1->turnOn();
    channel2->turnOn();
    channel3->turnOn();


    std::cout << "Channel 1 On: " << channel1->isOn()
              << std::endl
              //    << "OVP: " << channel1->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel1->getOutputVoltage() << std::endl
              << "Current: " << channel1->getCurrent() << std::endl;
    wait();
    std::cout << "Channel 2 On: " << channel2->isOn()
              << std::endl
              //    << "OVP: " << channel2->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel2->getOutputVoltage() << std::endl
              << "Current: " << channel2->getCurrent() << std::endl;
    wait();
    std::cout << "Channel 3 On: " << channel3->isOn()
              << std::endl
              //    << "OVP: " << channel3->getOverVoltageProtection() << std::endl
              << "Voltage: " << channel3->getOutputVoltage() << std::endl
              << "Current: " << channel3->getCurrent() << std::endl;
    wait();

    //std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
     /*!
      *** TEST CARD **********************************************
     */
      //Local variables
      TC_PSPOH cTC_PSPOH;
      string answer ="";

      // cTC_PSPOH.spi_write("DEFIB\r\n",verbose);
      // MyFile << "card reset\r\n";


      for (size_t i = 0; i <= 120; i+=step)
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
      }
      
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
      std::cout << "Turning off" << std::endl;
      channel1->turnOff();
      std::cout << "On: " << channel1->isOn() << std::endl;

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


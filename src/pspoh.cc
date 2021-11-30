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
using namespace std;
using namespace chrono;

bool fileExists(const string &name);

int main(int argc, char *argv[]){
   bool verbose;

   if (argc > 1)
   {
      //Set verbose if it is asked
      if(string(argv[1]) == "-v"){
         verbose = true;
         cout << argc-1 << " args was given to this program :" << endl;
         for (size_t i = 1; i < argc; i++){
            cout << argv[i] << endl;
         }
      }  
   }


   int step = atoi(argv[2] ) ;
   cout << "the step is: \"" << step << "\"" << endl;

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

   if (MyFile.is_open()){


      //Time measurement
      auto end = system_clock::now();
      auto start = system_clock::now();
      time_t start_time = system_clock::to_time_t(start);
      MyFile << "Started computation at " << ctime(&start_time)<< endl;
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


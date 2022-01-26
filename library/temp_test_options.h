#ifndef _TEMP_TEST_OPTIONS_H__
#define _TEMP_TEST_OPTIONS_H__

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;


/*!
************************************************
* Argument parser.
************************************************
*/
//-------------------------------------------------------------------------
// Handle command line options for pspoh testing
//
// Options:
// [-h|--help]                Show help menu
// [-i|--hybridId]            Scanned qr code from the hybrid
// [-G|--useGui]              Flag to use the gui
// [-s|--step]                card load step
// [-S|--supply]              supply step
// [-d|--directory]           new directory for tests saved within /results
// example command: pspoh -f ../results1.txt --time -35000.2 --value 42 -G
// --------------------------------------------------------------------------

//processes the program options entered in main
// void parcer(int argc, char* argv[]);

std::string path; //temp fix for get_docPath


class TemporaryCommandLineOptions
{
 public:
    enum statusReturn_e
    {
        OPTS_SUCCESS,
        OPTS_VERSION,
        OPTS_HELP,
        OPTS_FAILURE
    };

      TemporaryCommandLineOptions(const int argc, const char* const argv[]);
      ~TemporaryCommandLineOptions();
     
      statusReturn_e parse(int argc, char* argv[]);
    
    
      void setup(const int argc, const char* const argv[]); //to setup the program options
      std::string get_docPath();
      std::string get_hybridId();
      int get_step();
      int get_stepMax();

      int get_supply_step();
      int get_supply_min();
      int get_supply_max();
      
      bool new_directory(std::string name);
      std::string get_new_directory(); 
      bool get_verbose();
      std::string get_pipe_path();
      
   
      //not implemented -- not for use 
      //limits the available contructor options to ones chosen below
      // TemporaryCommandLineOptions(const TemporaryCommandLineOptions &rhs );
      // TemporaryCommandLineOptions &operator = (const TemporaryCommandLineOptions &rhs);
     private:
      //variables for commands
      po::options_description myOptions;
      std::string config;
      bool verbose;
      std::string my_new_directory;

      std::string hybridId;

      int step;   //for loads
      int stepMax; 

      int supply;
      int supply_step;
      int supply_min;
      int supply_max;

      bool flagG; //for gui
      std::string namedpipe_path;

};








#endif
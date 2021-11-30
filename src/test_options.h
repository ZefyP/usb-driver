#ifndef _TEST_OPTIONS_H__
#define _TEST_OPTIONS_H__

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

//------------------------------------------
// Handle command line options for pspoh
//
// Options:
// [-h|--help]                Show help menu
// [-t|--time]                  time
// [-G|--gflag                a flag
// [-f]--file ARG (string)    Input file
// [--value] ARG (int)User value
// --------------------------------------------------------------

class CommandLineOptions
{
 public:
 enum statusReturn_e
 {
    OPTS_SUCCESS,
    OPTS_VERSION,
    OPTS_HELP,
    OPTS_FAILURE
 };

CommandLineOptions();
~CommandLineOptions();
statusReturn_e parse(int argc, char* argv[]);

inline const std::string & getInputFile() const;
inline int getUserValue(){return myUserValue; };
inline bool getGFlag(){ return myGFlag; };

protected:
  void setup(); //to setup the program options
  bool validateFiles(); //not in use for now

private: 
   //not implemented -- not for use 
   //limits the available contructor options to ones chosen below
   CommandLineOptions(const CommandLineOptions &rhs );
   CommandLineOptions &operator = (const CommandLineOptions &rhs);

   po::options_description myOptions;
   std::string myInputFile;
   int myUserValue;
   bool myGFlag;

// inlineconst std::string & CommandLineOptions::getInputFile() const
//  {}

}

#endif //_TEST_OPTIONS_H__

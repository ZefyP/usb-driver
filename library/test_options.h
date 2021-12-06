#ifndef _TEST_OPTIONS_H__
#define _TEST_OPTIONS_H__

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;

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
    inline double getUserTime(){ return myUserTime; };
    inline int hybridID(){return ID; };
    inline bool useGui(){ return flagG; };

protected:
  void setup(); //to setup the program options
//  bool validateFiles(); //not in use for now

private: 
   //not implemented -- not for use 
   //limits the available contructor options to ones chosen below
   CommandLineOptions(const CommandLineOptions &rhs );
   CommandLineOptions &operator = (const CommandLineOptions &rhs);

   po::options_description myOptions;
   std::string myInputFile;
   int ID;
   double myUserTime;
   bool flagG;

// inlineconst std::string & CommandLineOptions::getInputFile() const
//  {}

};

#endif //_TEST_OPTIONS_H__

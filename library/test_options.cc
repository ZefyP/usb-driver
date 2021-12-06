#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace fs = boost::filesystem;

#include "test_options.h"

CommandLineOptions::CommandLineOptions():
    myOptions(""),
    myInputFile(""),
    myUserTime(-99999.99999),
    ID( 1212 ),
    flagG( false )
{
    setup();
}

CommandLineOptions::~CommandLineOptions() //destructor
{

}

void CommandLineOptions::setup()
{
    po::options_description options( "Program Options" );
    options.add_options()
    ("help,h", "Display help menu");
    // ("time,t", po::value< double >( &myUserTime)->default_value(100.0), "User-specified time")
    // ("value", po::value< int > ( &myUserValue)->default_value( 43 ), "User-specified value")
    // ("file,f",po::value< std::string >( &myInputFile ), "User-specified input file" )
    // ("useGui,G", po::bool_switch( &myGFlag)->default_value(false), "Toggle G-flag");
    //  --hybridId
    //  --output ability to create new directory to save results . e.g. temp
    //

    myOptions.add( options);

}


CommandLineOptions::statusReturn_e CommandLineOptions::parse( int argc, char* argv[] )
{
    statusReturn_e ret = OPTS_SUCCESS;

    po::variables_map varMap;
   //char filename[2000];

    try
    {
        po::store( po::parse_command_line(argc, argv, myOptions), varMap );
        po::notify( varMap );

        //Help option
        if (varMap.count ("help") )
        {
            std::cout << myOptions << std::endl;
            return OPTS_HELP;
        }

        // //Version info (not in use for now)
        // if (varMap.count ( "version") )
        // {
        //     return OPTS_VERSION;
        // }

        
        /****not in use for now****
        //Enforce an input file argument every time
        if( !( 0< varMap.count("file") ) )
        {
            std::cout << " ERROR - INput file must be specified!" << std::endl;
            std::cout << myOptions << std::endl;
            return OPTS_FAILURE;
        }
        else
        {
            //Strip whitespaces from front/back of filename string
            boost::algorithm::trim(myInputFile);
            //resolve the filename to become fully qualified
            realpath(myInputFile.c_str(), filename);
            myInputFile = filename;

            ret = validateFiles() ? OPTS_SUCCESS : OPTS_FAILURE;
        }
        */

        // // If we want to check if a value is defaulted 
        // if (!varMap[ "value" ].defaulted() )
        // {
        //     std::cout << "WARNING - default value User-value overwritten to "<< myUserValue << std::endl;

        // }




    }
    catch( std::exception &e )
    {
        std::cout << "ERROR - parsing error: " << e.what() << std::endl ;
        ret = OPTS_FAILURE;
    }
    catch( ... )
    {
        std::cout << "ERROR - parsing error: unknown type." << std::endl ; 
        ret = OPTS_FAILURE;
    }

  return ret;


}
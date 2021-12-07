
#include "temp_test_options.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>

using namespace std;
namespace fs = boost::filesystem;


TemporaryCommandLineOptions::TemporaryCommandLineOptions(const int argc, const char* const argv[]):
    myOptions(""),
    config(""),
    verbose(""),
    my_new_directory(""),
    hybridId(""),
    flagG(false),
    step(5),
    supply(0)

{
    setup(argc, argv);
    get_docPath();
}

TemporaryCommandLineOptions::~TemporaryCommandLineOptions() //destructor
{

}


void TemporaryCommandLineOptions::setup(const int argc, const char* const argv[])
{

    // po::variables_map process_program_options(const int argc, const char* const argv[])
    // {
        po::options_description desc("Allowed options");

        desc.add_options()
            ("help,h", "produce help message")
            ("config,c", po::value<string>()->default_value("default"),"set configuration file path for the power supply")
            ("verbose,v", po::value<string>()->implicit_value("0"), "verbosity level")
            ("step,s", po::value< int > (&step)-> default_value(10), "Load percentage step from NO LOAD to 120pc of the nominal values" )
            //("supply,S",po::value< int > (&supply)-> default_value(0), "Step the input voltage of the power supply")
            ("useGui,G",po::value< bool >(&flagG)-> default_value(false),"use the Gui")
            ("hybridId,id", po::value<string> (&hybridId)->default_value("000"), "Scanned hybrid module ID");
            // my_new_directory
            // --useGui <namedpipe>
            // 'flagG' is set to true if --useGui has been sent, false otherwise
            // 'namedpipe_path' is the value of the argument --useGui

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
            // return 0;
        }

        //Test Card objects

        if(vm.count( "verbose") )
        {
            //verbose = true;
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

        if(vm.count("config"))
        {
            path =  vm["config"].as<string>();
            //get_docPath();
        }

        // GUI Object
        if(vm.count("useGui"))
        {
            cout << "use GUI application " << vm["useGui"].as<bool>() << endl;
        }

        
        // hybridId Object
        if(vm.count("hybridId"))
        {
            cout << "the hybridId you entered is " << vm["hybridId"].as<string>() << endl;
        }

        // return vm;
    // };
}   



string TemporaryCommandLineOptions::get_docPath()
{
    return path;
};





//}

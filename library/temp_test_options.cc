#include "temp_test_options.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string/trim.hpp>

#include "gui_logger.h"

using namespace std;
namespace fs = boost::filesystem;


/*!
************************************************
* Argument parser.
************************************************
*/


TemporaryCommandLineOptions::TemporaryCommandLineOptions(const int argc, const char* const argv[])
    // myOptions(""),
    // config(""),
    // verbose(false),
    // my_new_directory(""),
    // hybridId(""),
    // step(60),
    // stepMax(120),
    // flagG(false),
    // flagV(false)
{
    setup(argc, argv);
    // get_verbose();
    // get_docPath();

    // get_step();
    // get_stepMin();
    // get_stepMax();

    // get_supply_step();
    // get_supply_min();
    // get_supply_max();

    // get_hybridId();
    // new_directory(my_new_directory);
    // get_new_directory();
    // get_usegui();
    // get_usevector();

}

TemporaryCommandLineOptions::~TemporaryCommandLineOptions() //destructor
{}


void TemporaryCommandLineOptions::setup(const int argc, const char* const argv[])
{
    
    po::options_description desc("Allowed options");

    desc.add_options()
        ("help,h", "produce help message")
        ("config,f", po::value<string>()->default_value("default"),"set configuration file path for the power supply")
        ("verbose,v",po::bool_switch (&verbose)-> default_value(false), "verbosity level")
        
        ("step,s", po::value< int > (&step)-> default_value(10), "Load percentage step from NO LOAD to 120pc of the nominal values" )
        ("stepMin", po::value< int > (&stepMin)-> default_value(0), "Minimum load for this test" )
        ("stepMax", po::value< int > (&stepMax)-> default_value(20), "Maximum load for this test" )
        
        ("supstep", po::value< int > (&supply_step)-> default_value(10), "Supply step from set min to max voltage" )
        ("supmin", po::value< int > (&supply_min)-> default_value(110), "Supply min" )
        ("supmax", po::value< int > (&supply_max)-> default_value(110), "Supply max" )
                
        
        ("hybridId,i", po::value<string> (&hybridId)->default_value("000"), "Scanned hybrid module ID")
        ("output,o", po::value <string> (&my_new_directory), "Test results will be saved in a new directory")

        ("useGui,G",po::bool_switch (&flagG)-> default_value(false),"Use the Gui")
        ("useVector,V",po::bool_switch (&flagV)-> default_value(false),"Test with array of selected loads");   
        
        

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

    // Test Card objects

    if(vm.count( "verbose") )
    {
        verbose = vm["verbose"].as<bool>();
        cout << "verbose ; " << verbose << endl;
        cout << argc-1 << " args were given to this program. These are: " << endl;
        for (size_t i = 1; i < argc; i++){
            cout << argv[i] << endl;
        }
    }

    // load
    if(vm.count("step") )
    {
        cout << "step ; " << step << endl;
    }

    if(vm.count("stepMin" ))
    {   
        stepMax = vm["stepMin"].as<int>();
        cout << "minLoad ; " << stepMin << endl;
    }

    if(vm.count("stepMax" ))
    {   
        stepMax = vm["stepMax"].as<int>();
        cout << "maxLoad ; " << stepMax << endl;
    }

    // supply
    if(vm.count("supstep") )
    {
        cout << "Supply step ; " << supply_step << endl;
    }

    if(vm.count("supmin") )
    {
        cout << "Supply min ; " << supply_min << endl;
    }
    if(vm.count("supmax") )
    {
        cout << "Supply max ; " << supply_max << endl;
    }

    // Power supply object
    if(vm.count("config"))
    {
        path =  vm["config"].as<string>();
    }

    
    // hybridId object
    if(vm.count("hybridId"))
    {
        cout << "hybridId ; " << vm["hybridId"].as<string>() << endl;
    }

    //New Directory
     if(vm.count("output")) //abstract at later stage
    {
        my_new_directory = vm["output"].as<string>();
        new_directory(my_new_directory);
        cout << "The results will be saved in directory named "<< my_new_directory << endl;
    }else
    {
        my_new_directory = "";
        new_directory(my_new_directory);
        cout << "The results will be saved in directory named "<< my_new_directory << endl;
    }

    // GUI Object
    if(vm.count("useGui"))
    {
        cout << "Guiflag ; " << vm["useGui"].as<bool>() << endl;
    }
    
    // Vector Object
    if(vm.count("useVector"))
    {
        cout << "Vectorflag ; " << vm["useVector"].as<bool>() << endl;
    }        
}//end Options::setup()   

string TemporaryCommandLineOptions::get_docPath()
{
    return path;
}


int TemporaryCommandLineOptions::get_step()
{
    return step; 
}

int TemporaryCommandLineOptions::get_stepMax()
{
    return stepMax; 
}

int TemporaryCommandLineOptions::get_stepMin()
{
    return stepMin;
}

string TemporaryCommandLineOptions::get_hybridId()
{
    return hybridId;
}


int TemporaryCommandLineOptions::get_supply_step()
{
    return supply_step;
}
int TemporaryCommandLineOptions::get_supply_min()
{
    return supply_min;
}
int TemporaryCommandLineOptions::get_supply_max()
{
    return supply_max;
}

bool TemporaryCommandLineOptions::new_directory(string name) 
{
   string parent_dir = "results/";
   bool my_new_directory = fs::create_directories(parent_dir+name);

    return my_new_directory;
}

string TemporaryCommandLineOptions::get_new_directory()
{
    return my_new_directory;
}

bool TemporaryCommandLineOptions::get_verbose()
{
    return verbose;
}


bool TemporaryCommandLineOptions::get_usegui()
{
    return flagG;
}

bool::TemporaryCommandLineOptions::get_usevector()
{
    return flagV;
}
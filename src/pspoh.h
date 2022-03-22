#ifndef DEF_PSPOH_H
#define DEF_PSPOH_H


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
#include <string>
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
bool reset_and_repeat(int times, TC_PSPOH child);
void print_computation_time(ofstream &MyFile,  std::chrono::time_point<std::chrono::system_clock> &end,  std::chrono::time_point<std::chrono::system_clock> start);

int ERR_HYB_CONN_Vhiv = 10;   // Hybrid module not properly connected based on current measurement.
int ERR_HYB_CONN_Chiv = 11; 
int ERR_HYB_CONN_Cleft = 12;
int ERR_HYB_CONN_Cright = 13;
int ERR_HYB_CONN_Ctail = 14;
int ERR_SCPI = 15;            // An error was flagged by the microcontroller.
int ERR_RTR_TIME_OUT = 16;
int ERR_LOW_HIV = 17;         // Supply inpute voltage is too low. PSPOH is rated for 10-12 V



#endif

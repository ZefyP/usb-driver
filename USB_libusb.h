#ifndef USB_libusb_h__
#define USB_libusb_h__

#include <libusb-1.0/libusb.h>
//#include <usb.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <bitset>



class CP2130_2S
{
    public:
    enum cs_line:char{cs0,cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9,cs10};
    enum spiDevice:char{ADG731,SI8902,ADG714,ADG1414,AD5231,LTC6903,MCP4921,SC18IS600,muController};
    CP2130_2S();
    ~CP2130_2S();
    int initialize();
    void close();
    // int gpio_set_input(cs_line);
    int gpio_set_output(cs_line, bool);
    // //read chip select enable state for a channel
    int choose_spi(cs_line);
    int configure_spi(cs_line,spiDevice);
    int spi_writeRead(unsigned char*, int, unsigned char*,bool=true);
    //int get_product_string(unsigned char*);
    // int get_gpio_value(cs_line, bool&);
    // int set_usb_config();
    // int get_usb_config();

    private:
    
    libusb_device_handle* setup_libusb_access();
    libusb_device_handle* fUsbHandle;
    libusb_context* context = NULL;
    libusb_device** deviceList = NULL;
    ssize_t deviceCount = 0;
    struct libusb_device_descriptor deviceDescriptor;
    libusb_device* device = NULL;
    int kernelAttached = 0;
    
    // std::string VERSION="0.1.0";
    // const static int VENDOR_ID=0x10C4; 
    // const static int PRODUCT_ID=0x87A0;
    // const static int INTERF=0;

    // const static int fUsbEndpointBulkIn = 0x82;  // usb endpoint 0x82 address for USB IN bulk transfers
    // const static int fUsbEndpointBulkOut = 0x01;  // usb endpoint 0x01 address for USB OUT bulk transfers
    // const static int fUsbEndpointBulkReadWrite = 0x01;  // usb endpoint 0x01 address for USB OUT bulk transfers
    const static int fUsbTimeout = 1000;  // usb operation timeout in ms
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//


class TC_2SSEH
{
    public:

    enum temperatureMeasurement:char{Temp1,Temp2,Temp3,Temp_SEH};
    const char *temperatureMeasurementName[4] ={"Temp1","Temp2","Temp3","Temp_SEH"};
    float temperatureConvFactor[4]={0.03125,0.03125,0.03125,1};

    enum supplyMeasurement:char{U_P5V, I_P5V,U_P3V3, I_P3V3,U_P2V5, I_P2V5,U_P1V25, I_P1V25,U_SEH, I_SEH};
    const char *supplyMeasurementName[10] ={"U_P5V", "I_P5V","U_P3V3", "I_P3V3","U_P2V5", "I_P2V5","U_P1V25", "I_P1V25","U_SEH", "I_SEH"};
    float supplyConvFactor[10]={1.25e-3,20e-6,1.25e-3,50e-6,1.25e-3,30e-6,1.25e-3,30e-6,1.25e-3,80e-6};
    const char *supplyUnit[2]={"V","A"};

    enum loadMeasurement:char{U_P1V2_R,I_P1V2_R,U_P1V2_L,I_P1V2_L};
    const char *loadMeasurementName[4] ={"U_P1V2_R","I_P1V2_R","U_P1V2_L","I_P1V2_L"};
    float loadConvFactor[10]={1.25e-3,80e-6,1.25e-3,80e-6};
    const char *loadUnit[2]={"V","A"};

    enum hvmonMeasurement:char{Mon,HV_meas,VHVJ7,VHVJ8};
    const char *hvmonMeasurementName[4] ={"Mon","HV_meas","VHVJ7","VHVJ8"};
    double muControllerConversionFactor=2.048/4095;
    double hvmonConvFactor[4]={muControllerConversionFactor,1e9/(65536-1)*5/201.4/4.99/1e4,muControllerConversionFactor,muControllerConversionFactor};
    double HV_measOffset=0.5*5/201.4/4.99/1e4*1e9;
    const char *hvmonUnit[4]={"V","nA","V","V"};

    enum resetMeasurement:char{RST_CBC_R,RST_CIC_R,RST_CBC_L,RST_CIC_L};
    const char *resetMeasurementName[4] ={"RST_CBC_R","RST_CIC_R","RST_CBC_L","RST_CIC_L"};

    //enum amuxSelect:char{right,left};
    //const char *amuxSelectName[2] ={"AMUX right","AMUX left"};
    
    
    
    
    enum limit:char{U_P5V_tolerance, I_P5V_max,U_P3V3_tolerance, I_P3V3_max,U_P2V5_tolerance, I_P2V5_max,U_P1V25_tolerance, I_P1V25_max,T1_max,T1_min,T2_max,T2_min,T3_max,T3_min,T_SEH_max,T_SEH_min};
    const char *limitName[16] ={"U_P5V_tolerance","I_P5V_max","U_P3V3_tolerance","I_P3V3_max","U_P2V5_tolerance","I_P2V5_max","U_P1V25_tolerance","I_P1V25_max","T1_max","T1_min","T2_max","T2_min","T3_max","T3_min","T_SEH_max","T_SEH_min"};

    enum state:char{P5V_overvoltage,P5V_undervoltage,P5V_overcurrent,P3V3_overvoltage,P3V3_undervoltage,P3V3_overcurrent,P2V5_overvoltage,P2V5_undervoltage,P2V5_overcurrent,P1V25_overvoltage,P1V25_undervoltage,P1V25_overcurrent,T1_error,T2_error,T3_error,T_SEH_error};
    const char *stateName[16] = {"P5V_overvoltage","P5V_undervoltage","P5V_overcurrent","P3V3_overvoltage","P3V3_undervoltage","P3V3_overcurrent","P2V5_overvoltage","P2V5_undervoltage","P2V5_overcurrent","P1V25_overvoltage","P1V25_undervoltage","P1V25_overcurrent","T1_error","T2_error","T3_error","T_SEH_error"};
    
    
    enum sehSupplyState:char{sehSupply_Off,sehSupply_On};
    enum P1V25SenseState:char{P1V25SenseState_Off,P1V25SenseState_On};

    static std::string product_string;
    //       //
    TC_2SSEH();
    ~TC_2SSEH();
    int toggle_led();
    int read_temperature(temperatureMeasurement,float&);
    int read_supply(supplyMeasurement,float&);
    int read_load(loadMeasurement,float&);
    int read_limit(limit,float&);
    int read_hvmon(hvmonMeasurement,float&);
    int read_state(state,bool &);

    int set_AMUX(unsigned int, unsigned int);
    int set_P1V25_L_Sense(P1V25SenseState);

    int read_reset(resetMeasurement,float&);
    int set_SehSupply(sehSupplyState);
    int set_load1(bool, bool, unsigned int);
    int set_load2(bool, bool, unsigned int);

    int set_HV(bool, bool, bool,unsigned int);
    int set_limit(limit,unsigned char); //carefull with temperature limits, require signed char
    int fuse(short int , char, char, char, char ); //format: starting address of block to be burned, 4 register content
    int set_fuse(bool);
    int writeI2C(unsigned char, unsigned char, unsigned char);
    int readI2C(unsigned char, unsigned char, unsigned char&);
    int write_i2c(unsigned short int, unsigned char); //ROH syntax compatible 
    int read_i2c(unsigned short int);                 //ROH syntax compatible 
    int sendLPGBTconfig(unsigned char*,int);
    private:
    static CP2130_2S cCP2130; // declare CP2130 object    
    bool test_led_state=0;
    static unsigned int AMUX_R_set;
    static unsigned int AMUX_L_set;

    static  bool load1_enable;
    static  bool load2_enable;
    static  bool load1_path;
    static  bool load2_path;
    static unsigned int load1_setvalue;
    static unsigned int load2_setvalue;

    static  bool HV_relay;
    static  bool HVMONX7_relay;
    static  bool HVMONX8_relay;
    static unsigned int HVDAC_setvalue;

    static bool is_initialized; // initialization of test card only occurs once
};

#endif


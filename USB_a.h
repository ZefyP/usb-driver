#ifndef USB_a_h__
#define USB_a_h__

#include <usb.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <thread>
#include <bitset>



class CP2130
{
    public:
    enum cs_line:char{cs0,cs1,cs2,cs3,cs4,cs5,cs6,cs7,cs8,cs9,cs10};
    enum device:char{ADG731,SI8902,ADG714,ADG1414,AD5231,LTC6903,MCP4921,SC18IS600};
    CP2130();
    ~CP2130();
    int initialize();
    void close();
    int gpio_set_input(cs_line);
    int gpio_set_output(cs_line, bool);
    //read chip select enable state for a channel
    int choose_spi(cs_line);
    int configure_spi(cs_line,device);
    int spi_write(char*, int);
    int spi_read(char*, int);
    int get_product_string(char*);
    int get_gpio_value(cs_line, bool&);
    int set_usb_config();
    int get_usb_config();

    private:
    usb_dev_handle* fUsbHandle;
    
    usb_dev_handle* find_usb_handle();
    usb_dev_handle* setup_libusb_access();
    
    std::string VERSION="0.1.0";
    const static int VENDOR_ID=0x10C4; 
    const static int PRODUCT_ID=0x87A0;
    const static int INTERF=0;

    const static int fUsbEndpointBulkIn = 0x82;  // usb endpoint 0x82 address for USB IN bulk transfers
    const static int fUsbEndpointBulkOut = 0x01;  // usb endpoint 0x01 address for USB OUT bulk transfers
    const static int fUsbTimeout = 1000;  // usb operation timeout in ms
};
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//


class TC_2SFE
{
    public:
    enum measurement:char{AMUX,ISEN,THERM_SENSE};
    enum ant_channel:char{NONE,_1,_2,_3,_4,ALL}; // Antenna Options
    TC_2SFE();
    ~TC_2SFE();
    //Card Id// Full after creating a TC_2SFE object
	std::string product_string;
    //       //
    int adc_get(measurement,float&);
    int toggle_led();   
    int antenna_fc7(uint16_t,ant_channel);

    private:
    CP2130 cCP2130;
    uint16_t saved_pot_value=0; // saved value of potentiometer, during operation
    float ADC_VREF=1.25;
    bool test_led_state=0;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

class TC_PSFE
{
    public:
    enum measurement:char{AMUX,THERM_SENSE,ANT_PULL,C_TEST_PG,C_TEST_P12,_1V_OUT,_1V_AMP,_1V,
                            _3V3_OUT,_3V3_AMP,_3V3,_1V25_OUT,_1V25_AMP,_1V25,MPA_1V_3,_2V5,
                                MPA_RST_TEST,MPA_1V25A_3,_1V25_REF,GROUND,_625mV_REF,ISEN_1V,
                                    ISEN_1V25,ISEN_3V3,ROH_GND,ROH_GND_AMP,MPA_1V25A_4,MPA_1V_4}; // Available on-board measurements
    enum mode:char{SSA_OUT,CIC_IN}; // SSA_OUT or CIC_IN mode - Switch to test CIC/SSA
    enum st_mode:char{DISABLED,BUFFER_ONE,POGO_ONE,POGO_ZERO}; // SELF-TEST OPTIONS. FORMAT: SourceLocation_Value
    enum v_control:char{_900mV,_950mV,_1000mV,_1050mV,_1100mV,_1150mV,_1200mV,_1250mV}; // Voltage Control Options
    enum ant_channel:char{NONE,_1,_2,ALL}; // Antenna Options  _2 EVEN, _1 ODD
    
    //Card Id// Full after creating a TC_PSFE object
    static bool chirality; // 0 LEFT, 1 RIGHT
    static std::string product_string; // Product string
    //       //
    TC_PSFE();
    ~TC_PSFE();
    int adc_get(measurement,float&); // arguments: measurement choice, float output 
    int set_voltage(v_control, v_control);// arguments: 1V_CONTROL, 1V25_CONTROL
    int mode_control(mode); 
    int pogo_selftest(st_mode);
    int antenna_fc7(uint16_t,ant_channel); //arguments: Potentiometer value, Antenna channel
    private:
    static CP2130 cCP2130; // declare CP2130 object
    static char adg714_state; //saved state of adg714, during operation
    static uint16_t saved_pot_value; // saved value of potentiometer, during operation
    static bool is_initialized; // initialization of test card only occurs once
    float ADC_VREF=1.25; // Vref for ADC
    const static uint8_t antenna_mask=0x0C; // mask for bits/switches corresponding to antenna channel control - the rest are for voltage control
    const static int fTempLookUpTableSize = 34;
    float fTempLookUpTable[fTempLookUpTableSize] = {848, 804, 755, 701, 643, 584, 525, // 848 corresponds to -40 deg C, steps every 5 degree
                                                    467, 413, 362, 315, 273, 236, 203, 175, 150, 129, 111, 95,
                                                    82, 71, 61, 53, 46, 40, 35, 31, 27, 24, 21, 18, 16, 14, 13
                                                   }; // 13 corresponds to 125 deg C
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

class TC_PSROH
{
    public:
    enum measurement:char{THERM_SENSE,L_SSA_RST,L_MPA_RST,L_CIC_RST,R_CIC_RST,R_MPA_RST,R_SSA_RST,
                            _3V3,_2V55,_1V25,_1V25_REF,GROUND,_625mV_REF,ISEN_2V55,ISEN_3V3,ISEN_1V25};
    //Card Id// Full after creating a TC_PSFE object
    //char product_string[64]; // Product string
    static std::string product_string;
    //       //
    TC_PSROH();
    ~TC_PSROH();
    int adc_get (measurement,float&);
    int dac_output(uint16_t); // range: 0-4095  (0-1.25V)
    int toggle_led();
    int fusing(); // !!!NOT READY!!!
    int read_i2c(short int);
    int write_i2c(short int , char );
    int read_bridge_reg();
    int toggle_SCI2C(); // PULL DOWN SC_I2C - writing a register using "write_i2c" of this library,  will undo this. 
    private:
    static CP2130 cCP2130; // declare CP2130 object    
    bool test_led_state=0;
    float ADC_VREF=1.25; // Vref for ADC
    static bool is_initialized; // initialization of test card only occurs once
};



#endif


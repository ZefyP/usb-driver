#ifndef DEF_TC_PSPOH
#define DEF_TC_PSPOH

#include "USB_a.h"
#include <usb.h>
#include <time.h>
#include <iostream>
#include <iomanip>
class TC_PSPOH
{
    public:
    //Public attributes
    enum measurement:char{THERM_SENSE,_HIV,_1V25L,_1V25R,_1V25T,__1VL,_1VR,_2V55};
    enum status:char{HIV_STATUS};

    //Public Fonctions
    int get_product_string(std::string&);
    int get_product_string(std::string&, bool);
    int getStatus(status, std::string&);
    int control(measurement m, float&);
    int getHV_status(std::string &);
    int toggle_led();
    int turn_on_led();
    int turn_off_led();
    int system_reset();
    int cpu_reset();  //Doesn't work
    int spi_write(const std::string&);
    int spi_write(const std::string&,bool);
    int spi_read(std::string&, int);
    int spi_read(std::string&, int, bool);
    int wait_for_RTR();
    int wait_for_nRTR();
    //Constructors and destructors
    TC_PSPOH();
    //TC_PSPOH(uint32_t,uint8_t); // constructor for multi usb applications // arguments : bus, device number (lsusb) // can be called only once and then revert to the empty one
    ~TC_PSPOH();
   
    
    private:
    bool test_led_state = false;
    //Static members
    static CP2130 cCP2130;              //Cp2130 class instance
    static std::string product_string;
    static bool is_initialized;
};
void delay(int);
#endif

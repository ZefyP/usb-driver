#include "TC_PSPOH.h"

using namespace std;

//init static members of PSPOH
bool TC_PSPOH::is_initialized=false;
CP2130 TC_PSPOH::cCP2130; 
string TC_PSPOH::product_string;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

//Default constructor
TC_PSPOH::TC_PSPOH()
{   
    if(!is_initialized){
        cCP2130.initialize();
        product_string.resize(64,' ');
        cCP2130.get_product_string(&product_string[1]);                     //gets ID product descriptor
        cout << "\n\nThe USB Descriptor is " << product_string << endl;
        cCP2130.gpio_set_output(cCP2130.cs1,1);                             //n_SYSRST
        
        turn_off_led();
        //cCP2130.gpio_set_input(cCP2130.cs3);                                //RTR ready to read
        cCP2130.configure_spi(cCP2130.cs0,cCP2130.ATSAMD51P20A0A_PSPOH); //chip select

        is_initialized=true;
    }
}

int TC_PSPOH::getStatus(status s, string &answer){

    switch (s)
    {
        case HIV_STATUS:
            getHV_status(answer);
        break;

        default : return 1;
    }
    return 0;
}

int TC_PSPOH::getHV_status(string &answer){
    int w_status=0, r_status = 0;

    char w_buff[6] = {'h','i','v','?',0x0D, 0x0A};
    char r_buff[10] = {0 ,0 ,0 ,0, 0};

    cCP2130.choose_spi(cCP2130.cs0);

    turn_on_led();
 
    w_status = cCP2130.spi_write(w_buff,sizeof(w_buff));
    //this_thread::sleep_for(chrono::milliseconds(1000));
    r_status = cCP2130.spi_read(r_buff,sizeof(r_buff));
    turn_off_led();

    if(w_status > 0){
        cout << w_status << " bytes write on spi" << endl;
    }
    else{
        cout << "Unknow SPI Write status : " << w_status << endl;
    }

    if (r_status == -110){
        cout << "SPI Read Timout" << endl;
    }
    else if(r_status > 0){
        cout << r_status << " bytes read from spi" << endl;
    }
    else{
        cout << "Unknow SPI Read status : " << r_status << endl;
    }
    
    return r_status;
}

int TC_PSPOH::toggle_led()
{
    test_led_state=!test_led_state;
    cCP2130.gpio_set_output(cCP2130.cs8,test_led_state);
    return 0;
}
int TC_PSPOH::turn_on_led(){
    test_led_state = true;
    cCP2130.gpio_set_output(cCP2130.cs8,!test_led_state);
    return 0;
}
int TC_PSPOH::turn_off_led(){
    test_led_state = false;
    cCP2130.gpio_set_output(cCP2130.cs8,!test_led_state);
    return 0;
}

int TC_PSPOH::system_reset(){
    cCP2130.gpio_set_output(cCP2130.cs1,0);
    this_thread::sleep_for(chrono::milliseconds(1));
    cCP2130.gpio_set_output(cCP2130.cs1,1);
    return 0;
}

int TC_PSPOH::cpu_reset(){
    cCP2130.gpio_set_output(cCP2130.cs2,0);
    this_thread::sleep_for(chrono::milliseconds(1));
    cCP2130.gpio_set_output(cCP2130.cs2,1);
    return 0;
}

int TC_PSPOH::get_spi_word(char& word){
    char r_data;
    usb_control_msg (cCP2130.find_usb_handle(), 0xC0, 0x30, 0, 0, r_data, sizeof(r_data), fUsbTimeout);
    std::cout << "SPI word CS0:" << int(r_data[0]) << std::endl;
}
//Destructor, better to declare it even if it is empty
TC_PSPOH::~TC_PSPOH() {}

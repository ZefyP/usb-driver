#include "TC_PSPOH.h"

using namespace std;

//init static members of PSPOH
bool TC_PSPOH::is_initialized=false;
CP2130 TC_PSPOH::cCP2130; 
string TC_PSPOH::product_string;

//Default constructor
TC_PSPOH::TC_PSPOH()
{   
    if(!is_initialized){
        cCP2130.initialize();
        
        product_string.resize(64,' ');
        cCP2130.get_product_string(&product_string[0]);                             //gets ID product descriptor
        cout << "\n\nThe USB Descriptor is " << product_string << endl;
        cCP2130.gpio_set_output(cCP2130.cs1,1);                                 //n_SYSRST
        turn_off_led();
        //cCP2130.gpio_set_input(cCP2130.cs3);                                  //RTR ready to read
        cCP2130.configure_spi(cCP2130.cs0,cCP2130.ATSAMD51P20A0A_PSPOH);        //chip select
        //cCP2130.choose_spi(cCP2130.cs0);

        // cCP2130.choose_spi(cCP2130.cs0);
        // char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
        // cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
        // int t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
        
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
    cCP2130.choose_spi(cCP2130.cs0);
    char w_buff[] = {
        0x00, 0x00,             // Reserved
        0x01,                   // Write command
        0x00,                   // Reserved
        0x06, 0x00, 0x00, 0x00, // Write 6 bytes, little-endian
        'h', 'i', 'v', '?', '\r', '\n' // Test data, 6 bytes
    };
    string command = "hiv?\r\a";
    // spitousbwrite(command);
    // spiwrite()
    char r_buff[5] = {0 ,0 ,0 ,0, 0};

   
    
    //turn_on_led();
   
    w_status = cCP2130.spi_write(w_buff,sizeof(w_buff));
    //turn_off_led();
    //this_thread::sleep_for(chrono::milliseconds(1000));
    //turn_on_led();
    //r_status = cCP2130.spi_read(r_buff,sizeof(r_buff));
    //turn_off_led();

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

//Destructor, better to declare it even if it is empty
TC_PSPOH::~TC_PSPOH() {}

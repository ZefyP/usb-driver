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
        //Init
        /*cCP2130.initialize();
        
        //System reset
        system_reset();
        cCP2130.reset_usb();
        cCP2130.close();
        //TC_PSPOH need some time to init
        std::this_thread::sleep_for(std::chrono::milliseconds(100));*/

        //Init
        cCP2130.initialize();
        
        //Get product string
        product_string.resize(64,' ');
        cCP2130.get_product_string(&product_string[0]);                             //gets ID product descriptor
        cout << "The USB Descriptor is " << product_string << endl;

        //SPI buffer
        turn_off_led();
        //cCP2130.gpio_set_input(cCP2130.cs3);                                  //RTR ready to read

        cCP2130.configure_spi(cCP2130.cs0,cCP2130.ATSAMD51P20A0A_PSPOH);

        // cCP2130.choose_spi(cCP2130.cs4);
        // char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[6] ={0}; // com buffers for ADC
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
//#define DEBUGO
int TC_PSPOH::spi_read(string& answer, int len){
    
    int r_status = 0;
    char read_command_buf[8];
    read_command_buf[0] = 0x00;
    read_command_buf[1] = 0x00;
    read_command_buf[2] = 0x00;
    read_command_buf[3] = 0x00;
    read_command_buf[4] = 0x01%0xFF;
    read_command_buf[5] = (0x01/0xFF)%0xFF;
    read_command_buf[6] = (0x01/0xFFFF)%0xFF;
    read_command_buf[7] = (0x01/0xFFFFFF)%0xFF;

    char read_input_buf[len];
    char garbage_buff[1];
    cCP2130.choose_spi(cCP2130.cs0);
    turn_on_led();

    //Send read commande
    cCP2130.spi_write(read_command_buf,sizeof(read_command_buf));
    //Reading
    r_status = cCP2130.spi_read(garbage_buff,sizeof(garbage_buff));

    read_command_buf[0] = 0x00;
    read_command_buf[1] = 0x00;
    read_command_buf[2] = 0x00;
    read_command_buf[3] = 0x00;
    read_command_buf[4] = len%0xFF;
    read_command_buf[5] = (len/0xFF)%0xFF;
    read_command_buf[6] = (len/0xFFFF)%0xFF;
    read_command_buf[7] = (len/0xFFFFFF)%0xFF;

    //Send read commande
    cCP2130.spi_write(read_command_buf,sizeof(read_command_buf));
    //Reading
    r_status = cCP2130.spi_read(read_input_buf,sizeof(read_input_buf));
    turn_off_led();

    if (r_status == -110){
        cout << "SPI Read Timout" << endl;
    }
    else if(r_status > 0){
       
        cout << r_status << " bytes read from spi" << endl;
        answer = string(read_input_buf);
        cout << "'" << endl;
        #ifdef DEBUGO
        for (size_t i = 0; i < sizeof(read_input_buf); i++)
        {
            if (read_input_buf[i] == '\n'){
                cout << "[NL]" << endl;
            }
            else if (read_input_buf[i] == '\r'){
                cout << "[CR]" << endl;
            }
            else{
                cout << hex << read_input_buf[i] << dec << endl;
            }
        }
        cout << "'" << endl;
        #endif
    }
    else{
        cout << "Unknow SPI Read status : " << r_status << endl;
    }
    return r_status;
}

int TC_PSPOH::spi_write(const std::string& command){
    //Local variables déclaration
    int w_status=0;
    int len = command.length();
    char write_command_buf[len+8];

    //Local variables init.
    write_command_buf[0] = 0x00;
    write_command_buf[1] = 0x00;
    write_command_buf[2] = 0x01;
    write_command_buf[3] = 0x00;
    write_command_buf[4] = len%0xFF;
    write_command_buf[5] = (len/0xFF)%0xFF;
    write_command_buf[6] = (len/0xFFFF)%0xFF;
    write_command_buf[7] = (len/0xFFFFFF)%0xFF;
    for (size_t i = 0; i < len ; i++){
        write_command_buf[i+8] = char(command[i]);
    }

    //Select uC cs 
    cCP2130.choose_spi(cCP2130.cs0);

    turn_on_led();
    //Writing
    w_status = cCP2130.spi_write(write_command_buf,sizeof(write_command_buf));
    
    turn_off_led();

    //Status
    if(w_status > 0){
        cout << w_status << " bytes write on spi" << endl;
    }
    else{
        cout << "Unknow SPI Write status : " << w_status << endl;
    }

    return w_status;
}

int TC_PSPOH::getHV_status(string &answer){
    int r_status = 0, w_status = 0;
    //Write on SPI
    w_status = spi_write("hiv?\r\n");

    if(w_status <= 0){
        return w_status;
    }

    //Read on SPI
    r_status = spi_read(answer,5);

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

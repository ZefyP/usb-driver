#include "TC_PSPOH.h"

using namespace std;

//init static members of PSPOH
bool TC_PSPOH::is_initialized=false;
CP2130 TC_PSPOH::cCP2130; 
wstring TC_PSPOH::product_string;

//Default constructor
TC_PSPOH::TC_PSPOH()
{   
    if(!is_initialized){
        //Init
        // std::string iProduct = "CP2130 USB-to-SPI Bridge";
        // cCP2130.initialize((char*)iProduct.c_str());
        cCP2130.initialize();
    
        //Get product string
        // product_string.clear();
        // product_string.resize(62);
        // std::string product_string_narrow;
        // product_string_narrow.resize(64, ' ');
        // cCP2130.get_product_string(&product_string_narrow[0]);
        // product_string = utf8_to_wstring(product_string_narrow);
        // product_string[ product_string.length() - 1] = '\0';    

        initialize();

        is_initialized=true;
    }
}

//Constructor with bus, device
TC_PSPOH::TC_PSPOH( uint32_t bus, uint8_t device )
{   
    if(!is_initialized){
        //Init
        // std::string iProduct = "CP2130 USB-to-SPI Bridge";
        // cCP2130.initialize((char*)iProduct.c_str());
        cCP2130.initialize(bus, device);
    
        //Get product stringnn
        // product_string.clear();
        // product_string.resize(62);
        // std::string product_string_narrow;
        // product_string_narrow.resize(64, ' ');
        // cCP2130.get_product_string(&product_string_narrow[0]);
        // product_string = utf8_to_wstring(product_string_narrow);
        // product_string[ product_string.length() - 1] = '\0';    

        initialize();

        is_initialized=true;
    }
}

void TC_PSPOH::initialize()
{
    //SPI buffer
    turn_off_led();
    cCP2130.gpio_set_input(cCP2130.cs3);                                  //RTR ready to read

    cCP2130.gpio_set_output(cCP2130.cs1, 1);                              // SYS reset low
    cCP2130.gpio_set_output(cCP2130.cs2, 1);			                  // CPU reset low

    cCP2130.configure_spi(cCP2130.cs0,cCP2130.ATSAMD51P20A0A_PSPOH);
    // cCP2130.choose_spi(cCP2130.cs0);
}

void TC_PSPOH::reset_cp2130()
{
    std::cout << "Resetting CP2130" << std::endl;
    cCP2130.reset_device();
    initialize();
}

int TC_PSPOH::get_product_string(std::string& answer, bool verbose){
    
    return get_product_string(answer);
}

int TC_PSPOH::get_product_string(std::string& answer){
    cCP2130.get_product_string(&answer[0]);
    answer[ answer.length() ] = '\0';
    return 0;
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


// #define DEBUGO

int TC_PSPOH::cpu_reset(){
    cCP2130.gpio_set_output(cCP2130.cs2,0);
    this_thread::sleep_for(chrono::milliseconds(1));
    cCP2130.gpio_set_output(cCP2130.cs2,1);
    return 0;
}


int TC_PSPOH::spi_read(string& answer, int len,bool verbose){
    int status = spi_read(answer,len);
    if(verbose){
        cout << answer;
    }
    return status;
}

int TC_PSPOH::spi_read(string& answer, int len){
    answer.resize(len);
    int r_status = 0;
    char read_command_buf[8];
    read_command_buf[0] = 0x00;
    read_command_buf[1] = 0x00;
    read_command_buf[2] = 0x04;
    read_command_buf[3] = 0x00;
    read_command_buf[4] = 0x01%0xFF;
    read_command_buf[5] = (0x01/0xFF)%0xFF;
    read_command_buf[6] = (0x01/0xFFFF)%0xFF;
    read_command_buf[7] = (0x01/0xFFFFFF)%0xFF;

    char read_input_buf[len];
    char garbage_buff[1];
    
    // std::this_thread::sleep_for(std::chrono::milliseconds(30));
    cCP2130.choose_spi(cCP2130.cs0);
    turn_on_led();
    
    //Send read commande
    cCP2130.spi_write(read_command_buf,sizeof(read_command_buf));
    // wait_for_RTR();
    // if ( wait_for_RTR() == 1 )
    // {
    //     return spi_read(answer, len);
    // }
    //Reading
    r_status = cCP2130.spi_read(garbage_buff,sizeof(garbage_buff));

    read_command_buf[0] = 0x00;
    read_command_buf[1] = 0x00;
    read_command_buf[2] = 0x04;
    read_command_buf[3] = 0x00;
    read_command_buf[4] = len%0xFF;
    read_command_buf[5] = (len/0xFF)%0xFF;
    read_command_buf[6] = (len/0xFFFF)%0xFF;
    read_command_buf[7] = (len/0xFFFFFF)%0xFF;

    //Send read commande
    cCP2130.spi_write(read_command_buf,sizeof(read_command_buf));
    
    
    //Reading
    r_status = cCP2130.spi_read(read_input_buf,sizeof(read_input_buf));
    cCP2130.stopRTR();
    turn_off_led();

    if (r_status == -110){
        cout << "SPI Read Timout" << endl;  
        cout << "FAILED SPI READOUT" << endl;
        // exit(33);
        reset_cp2130();
       // cCP2130.usb_reset();
        cout << "Retrying the read" << endl;
        // r_status = cCP2130.spi_read(garbage_buff,sizeof(garbage_buff));
        return spi_read(answer, len);
    }
    else if(r_status > 0){
        
        answer = string(read_input_buf);
        answer.resize(len);
        answer.erase(remove(answer.begin(), answer.end(), '\0'), answer.end());
        #ifdef DEBUGO
        cout << r_status << " bytes read from spi" << endl;
        cout << "'" << endl;
        for (size_t i = 0; i < sizeof(read_input_buf); i++)
        {
            if (read_input_buf[i] == '\n'){
                cout << i << ": [NL]" << endl;
            }
            else if (read_input_buf[i] == '\r'){
                cout << i << ": [CR]" << endl;
            }
            else{
                cout << i << ": " << hex << read_input_buf[i] << dec << endl;
            }
        }
        cout << "'" << endl;
        #endif
    }
    else{
        #ifdef DEBUGO
        cout << "Unknow SPI Read status : " << r_status << endl;
        #endif
    }
    return r_status;
}

int  TC_PSPOH::wait_for_RTR(){
    bool rtr_active = true;
    bool first = true;
    auto start = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    auto now = std::chrono::system_clock::now();
    int status;
    while (rtr_active){
        status = cCP2130.get_gpio_value(cCP2130.cs3,rtr_active);
        if (status != 2){
            cout << "waiting for rtr" << endl;
        }
        
        now = std::chrono::system_clock::now();
        elapsed_seconds = now-start;

        if (elapsed_seconds>std::chrono::seconds(10))
        {
            cout << "RTR timed out" << endl;
            cout << "RTR FAILED" << endl;
            cCP2130.stopRTR();
            // reset_cp2130();
            return 1;
        }

        #ifdef DEBUGO
        if(!rtr_active){
            
            cout << "Rtr activated !" << endl;
        }
        else if (first){
            first = false;
            cout << "Rtr missing !" << endl;
        }
        #endif
    }
    return 0;
}

int TC_PSPOH::spi_write(const std::string& command,bool verbose){
    if(verbose){
        cout << command;
    }
    return spi_write(command);
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
    // std::this_thread::sleep_for(std::chrono::milliseconds(30));
    cCP2130.choose_spi(cCP2130.cs0);

    turn_on_led();
    //Writing
    w_status = cCP2130.spi_write(write_command_buf,sizeof(write_command_buf));
    
    turn_off_led();

    //Status
    #ifdef DEBUGO
    if(w_status > 0){
        cout << w_status << " bytes write on spi" << endl << endl;
    }
    else{
        cout << "Unknow SPI Write status : " << w_status << endl;
    }
    #endif
    return w_status;
}

int TC_PSPOH::getHV_status(string &answer){
    int r_status = 0, w_status = 0;
    //Write on SPI
    w_status = spi_write("hiv?\r\n");

    if(w_status <= 0){
        return w_status;
    }
    //Wait Data are ready
    // int cWaitForRTRStatus = wait_for_RTR();
    // if(cWaitForRTRStatus !=0){
    //     if(cWaitForRTRStatus == 1)
    //         return getHV_status(answer);
    if(wait_for_RTR()!=0){
        return 0;
    }
    //Read on SPI
    r_status = spi_read(answer,256);

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

int TC_PSPOH::scpi_write(const std::string& command,bool verbose, bool recursion)
{
    std::cout << command << std::endl;
    int len = command.length();
    char write_command_buf[len+8];

    cCP2130.choose_spi(cCP2130.cs0);

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
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    int w_status = cCP2130.spi_write(write_command_buf, sizeof(write_command_buf));
    if( w_status < 0 )
    {
        std::cout << "Write status: " << w_status << "-> SPI write failed, retrying..." << std::endl;
        if(recursion)
            return 1;
        else
            this->scpi_write(command, verbose, true);
    }
    else
        std::cout << w_status << " bytes sent to CP2130 for SPI write" << std::endl;
    //TO DO redefine returncode for failed write.
    return w_status;
}

int TC_PSPOH::scpi_write_readback(const std::string& command, std::string& answer, int len, bool verbose, bool recursion)
{
    // std::cout << command << std::endl;
    int command_len = command.length();
    char write_command_buf[command_len+8];

    cCP2130.choose_spi(cCP2130.cs0);

    //Send SCPI command to retrieve mearurements
    write_command_buf[0] = 0x00;
    write_command_buf[1] = 0x00;
    write_command_buf[2] = 0x01;
    write_command_buf[3] = 0x00;
    write_command_buf[4] = command_len%0xFF;
    write_command_buf[5] = (command_len/0xFF)%0xFF;
    write_command_buf[6] = (command_len/0xFFFF)%0xFF;
    write_command_buf[7] = (command_len/0xFFFFFF)%0xFF;
    for (size_t i = 0; i < command_len ; i++){
        write_command_buf[i+8] = char(command[i]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    int w_status = cCP2130.spi_write(write_command_buf, sizeof(write_command_buf));
    if( w_status < 0 )
    {
        std::cout << "Write status: " << w_status << "-> SPI write failed, retrying..." << std::endl;
        if ( this->scpi_write(command, verbose, true) == 1)
            return 1;
    }
    // else
    //     std::cout << w_status << " bytes sent to CP2130 for SPI write" << std::endl;
    std::cout << command << std::endl;
    int r_status = -20;

    std::this_thread::sleep_for(std::chrono::milliseconds(15));

    if( wait_for_RTR()==0 )
    {
        cCP2130.stopRTR();

        //Create read command block (using read, not writeread)
        char read_command_buf[] = {
        0x00, 0x00,             // Reserved
        0x00,                   // Read command
        0x00,                   // Reserved
        0xFF, 0x00, 0x00, 0x00, // Read 6 bytes, little-endian
        };    
        char read_input_buf[255];
        cCP2130.spi_write( read_command_buf, sizeof(read_command_buf) ); //Not SPI write but usb_bulk_write to write the 'read' command


        cCP2130.spi_read( read_input_buf, sizeof(read_input_buf));

        answer = read_input_buf;
        if ( answer.length() > 1 )
            answer = answer.substr(1, answer.length()-2 );
        std::cout << answer << std::endl;
        return r_status;

    }
    else{
        std::cout << "RTR timed out" << std::endl;
        // exit(0);
        reset_cp2130();
        if ( recursion )
            return 1;
        else
            return scpi_write_readback(command, answer, len, verbose, true);
    }
}


//Destructor, better to declare it even if it is empty
TC_PSPOH::~TC_PSPOH() {
   system_reset();
}

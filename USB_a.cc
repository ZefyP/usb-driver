#include "USB_a.h"

bool TC_PSROH::is_initialized=false, TC_PSROH::fuse_active=false;
CP2130 TC_PSROH::cCP2130; 
std::string TC_PSROH::product_string;



TC_PSROH::TC_PSROH()
{
    if(!is_initialized){
    cCP2130.initialize();
    product_string.resize(64,' ');
    cCP2130.get_product_string(&product_string[0]);
    cCP2130.gpio_set_output(cCP2130.cs9,test_led_state);
    cCP2130.configure_spi(cCP2130.cs4,cCP2130.SI8902);
    cCP2130.configure_spi(cCP2130.cs6,cCP2130.ADG731);
    cCP2130.configure_spi(cCP2130.cs7,cCP2130.MCP4921);
    cCP2130.configure_spi(cCP2130.cs10,cCP2130.SC18IS600);
    /////
    cCP2130.choose_spi(cCP2130.cs4);
    char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
    cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    int t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
    /////
    //%%%configure SPI to I2C chip%%%//
    char buf_IoConfig[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x00, 0b10101010}, // All GPIOs Push-Pull
         buf_IoState[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x01, 0b00001001}, // All GPIOs to zero
         buf_I2cClock[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x02, 0b00000101}; // max speed I2C, 369KHz
    cCP2130.choose_spi(cCP2130.cs10);
    cCP2130.spi_write(buf_IoState,sizeof(buf_IoState));
    cCP2130.spi_write(buf_IoConfig,sizeof(buf_IoConfig));
    cCP2130.spi_write(buf_I2cClock,sizeof(buf_I2cClock));
    //sleep(1);
    is_initialized=true;
    }
}

TC_PSROH::~TC_PSROH() {}

int TC_PSROH::toggle_SCI2C()
{
    char activate[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x01, 0b00000000}; 
    cCP2130.choose_spi(cCP2130.cs10);
    cCP2130.spi_write(activate,sizeof(activate));
    return 0;
}

int TC_PSROH::adc_get(measurement m,float& output)
{
    char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
    char buff_s_mux[9] = {0, 0, 1, 0, 1, 0, 0, 0, 0}; // com buffer for MUX:32:1 
    int t_code;
    uint16_t ADC_value;
    float conv=1;
    buff_s_adc[8]=0b11000011; buff_s_mux[8]=0b10000000;//default: Mux input for adc, all off for Mux
switch (m)
    {
        case ISEN_1V25:   buff_s_adc[8]=0b11010011; conv=2;   break;
        case THERM_SENSE: buff_s_adc[8]=0b11100011;           break;
        case L_SSA_RST:   buff_s_mux[8]=0;                    break;
        case L_MPA_RST:   buff_s_mux[8]=1;                    break;
        case L_CIC_RST:   buff_s_mux[8]=2;                    break;
        case R_CIC_RST:   buff_s_mux[8]=5;                    break;
        case R_MPA_RST:   buff_s_mux[8]=6;                    break;
        case R_SSA_RST:   buff_s_mux[8]=7;                    break;
        case _3V3:        buff_s_mux[8]=9;          conv=4;   break;
        case _2V55:       buff_s_mux[8]=10;         conv=4;   break;
        case _1V25:       buff_s_mux[8]=11;         conv=2;   break;
        case _1V25_REF:   buff_s_mux[8]=17;         conv=2;   break;
        case GROUND:      buff_s_mux[8]=18;                   break;
        case _625mV_REF:  buff_s_mux[8]=19;                   break;
        case ISEN_2V55:   buff_s_mux[8]=25;         conv=2;   break;
        case ISEN_3V3:    buff_s_mux[8]=17;         conv=2;   break;
    }
    cCP2130.choose_spi(cCP2130.cs6);
    cCP2130.spi_write(buff_s_mux,sizeof(buff_s_mux));
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    cCP2130.choose_spi(cCP2130.cs4);
    cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
    if (t_code != 4 )
    {
        printf ("USB Transaction ERROR!\n");
        return -1000.0;
    }
    else if (buff_r_adc[1] != buff_s_adc[8])
    {
        printf ("SPI Transaction ERROR!\n");
        return -1000.0;
    }
    else
    {
        ADC_value = ( ( (buff_r_adc[2] & 0x0F) << 6) + ( (buff_r_adc[3] >> 1) & 0x3F) );
        //std::cout << ADC_value << std::endl;
    }
    switch(m)
    {
        case THERM_SENSE: break; // conversion to temperature
        default:
        output = ( (ADC_value * ADC_VREF) * 1000 * conv ) / 1023;
        std::cout << output << std::endl;
        break;
    }
    return 0;
}




int TC_PSROH::toggle_led()
{
    test_led_state=!test_led_state;
    cCP2130.gpio_set_output(cCP2130.cs9,test_led_state);
    return 0;
}

int TC_PSROH::write_i2c(short int address, char value)
{
    char low = ( address & 0x00FF );
    char high= ( address & 0xFF00 ) >> 8;
    //std::cout << std::bitset<8>(high) << std::bitset<8>(low) << std::endl;
    //std::cout << "address= 0x" << std::hex<< +(address) << std::dec << " " ;
    //std::cout << "write_value= 0x" << std::hex<< +(value&0xFF) << std::dec  << " ";
    char activate[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x01, 0b00001001}; // turn on led
    char data[14]={0,0,1,0,6,0,0,0,0x00,3,0b11100000,low,high,value}; // write to register
    cCP2130.choose_spi(cCP2130.cs10);
    //cCP2130.spi_write(activate,sizeof(activate));
    cCP2130.spi_write(data,sizeof(data));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //return read_i2c(address);
    return 0;	
}

int TC_PSROH::read_i2c( short int address)
{
    char low = ( address & 0x00FF );
    char high= ( address & 0xFF00 ) >> 8;
    char read_reg[15]={0,0,1,0,7,0,0,0,0x02,2,1,0b11100000,low,high,0b11100001};
    char command_rb[9]={0,0,1,0,1,0,0,0,0x06}; 
    char dummy_send[9]={0,0,2,0,1,0,0,0,0x00};
    char buffer=0;
    cCP2130.choose_spi(cCP2130.cs10);
    cCP2130.spi_write(read_reg,sizeof(read_reg)); // read register
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    cCP2130.spi_write(command_rb,sizeof(command_rb)); // command to read buffer
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    cCP2130.spi_write(dummy_send,sizeof(dummy_send)); // send dummy receive data    
    int t_code=cCP2130.spi_read(&buffer,sizeof(buffer));
    //std::cout << "i2c read= 0x" << std::hex << +(buffer&0xFF) << std::dec  << std::endl;
    return +(buffer&0xFF);

}

int TC_PSROH::read_bridge_reg()
{
    char read_reg[11]={0,0,2,0,3,0,0,0,0x21,0x04,0xFF};
    char temp[3]={0};
    cCP2130.spi_write(read_reg,sizeof(read_reg));
    int t_this=cCP2130.spi_read(temp,sizeof(temp));
    char ff=temp[2];
    std::cout << "bridge reg= " << std::bitset<8>(ff)  << std::endl;
}


int TC_PSROH::toggle_2v5()
{
    char fuse[11]={0, 0, 1, 0, 3, 0, 0, 0, 0x20, 0x01, 0b00000000}; 
    fuse[10]=(fuse_active)? 0b00001101 : 0b00001011 ;
    fuse_active=!fuse_active; 
    cCP2130.choose_spi(cCP2130.cs10);
    cCP2130.spi_write(fuse,sizeof(fuse));
    return 0;
}

int TC_PSROH::fuse(short int address, char A, char B, char C, char D )
{
    char low = ( address & 0x00FF );
    char high= ( address & 0xFF00 ) >> 8;
    this->write_i2c(0x110,0xA3);//toggle_2v5 magic number
    this->write_i2c(0x109,0xC0); //toggle_2v5 control
    this->write_i2c(0x10E,high); // Address high of 32bit block to be fused
    this->write_i2c(0x10F,low); // Address low of 32bit block to be fused
    this->write_i2c(0x10A,A); 
    this->write_i2c(0x10B,B); 
    this->write_i2c(0x10C,C); 
    this->write_i2c(0x10D,D);
    this->toggle_2v5(); //enable 2v5
    std::this_thread::sleep_for (std::chrono::milliseconds (1) ); 
    this->write_i2c(0x109,0xC1); //toggle_2v5 control on
    int i=0;
    while(!(this->read_i2c(0x1A1)&0b00000010) && i<2 ) {std::cout << "toggle_2v5 in progress\n"; i++;}
    this->toggle_2v5(); //disable 2v5
    this->write_i2c(0x109,0xC0); //toggle_2v5 control off
}

int TC_PSROH::dac_output(uint16_t level)
{
	if (level<0||level>4095){
	std::cout << "Impossible voltage value : 0-4095 range" << std::endl;
        exit(0);
	}
	char low = ( level & 0x00FF );
   	char high= ( level & 0xFF00 ) >> 8;
	char buf_s[]={0, 0, 1, 0, 2, 0, 0, 0, 0b00110000|high, low};
	cCP2130.choose_spi(cCP2130.cs7);
	cCP2130.spi_write(buf_s,sizeof(buf_s));
	return 0;
}




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

//init static members of PSFE
char TC_PSFE::adg714_state=0;
uint16_t TC_PSFE::saved_pot_value=0; 
bool TC_PSFE::is_initialized=false;
bool TC_PSFE::chirality=0;
CP2130 TC_PSFE::cCP2130; 
std::string TC_PSFE::product_string;

TC_PSFE::TC_PSFE()
{
    if(!is_initialized){
    cCP2130.initialize();
    product_string.resize(64,' ');
    cCP2130.get_product_string(&product_string[0]);
    cCP2130.gpio_set_output(cCP2130.cs1,0);
    cCP2130.gpio_set_output(cCP2130.cs3,1);
    cCP2130.gpio_set_output(cCP2130.cs5,0);
    cCP2130.gpio_set_output(cCP2130.cs7,0);
    cCP2130.gpio_set_output(cCP2130.cs8,0);
    cCP2130.gpio_set_output(cCP2130.cs9,0);
    cCP2130.gpio_set_input(cCP2130.cs10);
    cCP2130.configure_spi(cCP2130.cs0,cCP2130.ADG714);
    cCP2130.configure_spi(cCP2130.cs2,cCP2130.AD5231);
    cCP2130.configure_spi(cCP2130.cs4,cCP2130.SI8902);
    cCP2130.configure_spi(cCP2130.cs6,cCP2130.ADG731);
        /////
    cCP2130.choose_spi(cCP2130.cs4);
    char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
    cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    int t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
    /////
    cCP2130.get_gpio_value(cCP2130.cs10,chirality);
    antenna_fc7(512 , NONE); // default state of antenna
    is_initialized=true;
    }
}

TC_PSFE::~TC_PSFE(){}

int TC_PSFE::adc_get(measurement m, float& output)
{
    char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
    char buff_s_mux[9] = {0, 0, 1, 0, 1, 0, 0, 0, 0}; // com buffer for MUX:32:1 
    int t_code;
    uint16_t ADC_value;
    float conv=1;
    buff_s_adc[8]=0b11010011; buff_s_mux[8]=0b10000000;//default: Mux input for adc, all off for Mux
    switch (m)
    {
        case AMUX:        buff_s_adc[8]=0b11000011;   break;
        case THERM_SENSE: buff_s_adc[8]=0b11100011;   break;
        case ANT_PULL:    buff_s_mux[8]=0;  conv=4;   break;
        case C_TEST_PG:   buff_s_mux[8]=1;            break;
        case C_TEST_P12:  buff_s_mux[8]=2;            break;
        case _1V_OUT:     buff_s_mux[8]=3;            break;
        case _1V_AMP:     buff_s_mux[8]=4;  conv=0.1; break;
        case _1V:         buff_s_mux[8]=5;            break;
        case _3V3_OUT:    buff_s_mux[8]=6;  conv=4;   break;
        case _3V3_AMP:    buff_s_mux[8]=7;  conv=0.1; break;
        case _3V3:        buff_s_mux[8]=8;  conv=4;   break;
        case _1V25_OUT:   buff_s_mux[8]=9;  conv=2;   break;
        case _1V25_AMP:   buff_s_mux[8]=10; conv=0.1; break;
        case _1V25:       buff_s_mux[8]=11; conv=2;   break;
        case MPA_1V_3:    buff_s_mux[8]=12;           break;
        case _2V5:        buff_s_mux[8]=13; conv=4;   break;
        case MPA_RST_TEST:buff_s_mux[8]=14;           break;
        case MPA_1V25A_3: buff_s_mux[8]=15;           break;
        case _1V25_REF:   buff_s_mux[8]=17;           break;
        case GROUND:      buff_s_mux[8]=18;           break;
        case _625mV_REF:  buff_s_mux[8]=19;           break;
        case ISEN_1V:     buff_s_mux[8]=25; conv=2;   break;
        case ISEN_1V25:   buff_s_mux[8]=26; conv=2;   break;
        case ISEN_3V3:    buff_s_mux[8]=27; conv=4;   break;
        case ROH_GND:     buff_s_mux[8]=28;           break;
        case ROH_GND_AMP: buff_s_mux[8]=29; conv=0.1; break;
        case MPA_1V25A_4: buff_s_mux[8]=30;           break;
        case MPA_1V_4:    buff_s_mux[8]=31;           break;
    }
    cCP2130.choose_spi(cCP2130.cs6);
    cCP2130.spi_write(buff_s_mux,sizeof(buff_s_mux));
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
    cCP2130.choose_spi(cCP2130.cs4);
    cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
    if (t_code != 4 )
    {
	
	cCP2130.reset_usb();
	cCP2130.choose_spi(cCP2130.cs4);
    	cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    	t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc)); 
	if (t_code != 4 ) return -1000.0;
	printf ("recovered from USB transaction error\n");
        ADC_value = ( ( (buff_r_adc[2] & 0x0F) << 6) + ( (buff_r_adc[3] >> 1) & 0x3F) );
    }
    else if (buff_r_adc[1] != buff_s_adc[8])
    {
        printf ("SPI Transaction ERROR!\n");
        return -1000.0;
    }
    else
    {
        ADC_value = ( ( (buff_r_adc[2] & 0x0F) << 6) + ( (buff_r_adc[3] >> 1) & 0x3F) );
        //std::cout << ADC_value << std::endl;
    }
   float pADC_value=(float)ADC_value;
    switch(m)
    {
        case THERM_SENSE:
    	if (pADC_value >= fTempLookUpTable[0]) output=-40.0;
    	else if (pADC_value <= fTempLookUpTable[fTempLookUpTableSize - 1]) output=125.0;
    	else
    	{
	int i = 1;
        while ( i < fTempLookUpTableSize)
        {
        if (pADC_value > fTempLookUpTable[i]){
	output= (5 * i - 40 - 5 * (pADC_value - fTempLookUpTable[i]) / (fTempLookUpTable[i - 1] - fTempLookUpTable[i]) );
	break;
	}
	i++;
        }
    	}

 	break; // conversion to temperature
        case C_TEST_PG: case C_TEST_P12: // conversion to test output
        output = (ADC_value>800) ? 1 : 0 ;
        break; 
        case MPA_RST_TEST:
        output = (ADC_value>300 && ADC_value<500) ? 1 : 0 ;
        break;
        default:
        output = ( (ADC_value * ADC_VREF) * 1000 * conv ) / 1023;
        break;
    }
        std::cout << output << std::endl;
    return 0;
}    


int TC_PSFE::mode_control(mode m)
{
    switch(m)
    {
        case SSA_OUT: cCP2130.gpio_set_output(cCP2130.cs7,0); break;
        case CIC_IN: cCP2130.gpio_set_output(cCP2130.cs7,1); break;
    }
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}

int TC_PSFE::set_voltage(v_control c1, v_control c2)
{
    char volt_state=0;
    switch(c1)
    {
        case _900mV:  volt_state=0b00100000; break;
        case _950mV:  volt_state=0b01100000; break;
        case _1000mV: volt_state=0b00010000; break;
        case _1050mV: volt_state=0b01010000; break;
        case _1100mV: volt_state=0b00110000; break;
        case _1150mV: volt_state=0b01110000; break;
        default: 
        std::cout << "Impossible voltage value - Check test card manual" << std::endl;
        exit(0);
        break;

    }
    switch(c2)
    {
        case _1100mV: volt_state=volt_state|0b00000010; break; 
        case _1150mV: volt_state=volt_state|0b10000010; break;
        case _1200mV: volt_state=volt_state|0b00000001; break;
        case _1250mV: volt_state=volt_state|0b10000001; break;
        default: 
        std::cout << "Impossible voltage value - Check test card manual" << std::endl;
        exit(0);
        break;
    }
    adg714_state=(adg714_state&antenna_mask)|volt_state;
    char buf_s[9]={0, 0, 1, 0, 1, 0, 0, 0, adg714_state};
    cCP2130.choose_spi(cCP2130.cs0);
    cCP2130.spi_write(buf_s,sizeof(buf_s));
    return 0;
}

int TC_PSFE::pogo_selftest(st_mode m)
{
    switch(m)
    {
        case DISABLED:
        cCP2130.gpio_set_output(cCP2130.cs8,0);
        cCP2130.gpio_set_output(cCP2130.cs9,0);
        break;
        case BUFFER_ONE:
        cCP2130.gpio_set_output(cCP2130.cs8,0);
        cCP2130.gpio_set_output(cCP2130.cs9,1);
        break;
        case POGO_ONE:
        cCP2130.gpio_set_output(cCP2130.cs8,1);
        cCP2130.gpio_set_output(cCP2130.cs9,0);
        break;
        case POGO_ZERO:
        cCP2130.gpio_set_output(cCP2130.cs8,1);
        cCP2130.gpio_set_output(cCP2130.cs9,1);
        break;
    }
    return 0;
}

int TC_PSFE::antenna_fc7(uint16_t pot_value,ant_channel c)
{
    cCP2130.gpio_set_output(cCP2130.cs5,0); //should be default configuration
    char ant_state=0, buf_s[11]={0, 0, 1, 0, 3, 0, 0, 0, 0xB0, 0, 0};
    if(pot_value!=saved_pot_value||c==NONE){
    if(c==NONE) pot_value=512;
    buf_s[9]= ((pot_value&0x300) >> 8);
    buf_s[10]= (pot_value & 0xFF);
    cCP2130.choose_spi(cCP2130.cs2);
    cCP2130.spi_write(buf_s,sizeof(buf_s));
    saved_pot_value=pot_value;
    }
    switch(c)
    {
        case NONE:
        cCP2130.gpio_set_output(cCP2130.cs1,0);
        ant_state=0b00000000;
        break;
        case _1:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00001000;
        break;
        case _2:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00000100;
        break;
        case ALL:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00001100;
        break;
    }
    adg714_state=(adg714_state&(~antenna_mask))|ant_state;
    char buf_s2[9]={0, 0, 1, 0, 1, 0, 0, 0, adg714_state};
    cCP2130.choose_spi(cCP2130.cs0);
    cCP2130.spi_write(buf_s2,sizeof(buf_s2));
    return 0;
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
TC_2SFE::TC_2SFE()
{
    cCP2130.initialize();
    product_string.resize(64,' ');
    cCP2130.get_product_string(&product_string[0]);
    cCP2130.gpio_set_output(cCP2130.cs1,0);
    cCP2130.gpio_set_output(cCP2130.cs3,1);
    cCP2130.gpio_set_output(cCP2130.cs5,0);
    cCP2130.configure_spi(cCP2130.cs4,cCP2130.SI8902);
    cCP2130.configure_spi(cCP2130.cs0,cCP2130.ADG1414);
    cCP2130.configure_spi(cCP2130.cs2,cCP2130.AD5231);
    cCP2130.configure_spi(cCP2130.cs3,cCP2130.LTC6903);
    /////
    cCP2130.choose_spi(cCP2130.cs4);
    char buff_s_adc[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r_adc[4] ={0}; // com buffers for ADC
    cCP2130.spi_write (buff_s_adc,sizeof(buff_s_adc));
    int t_code=cCP2130.spi_read(buff_r_adc,sizeof(buff_r_adc));
    /////
}
TC_2SFE::~TC_2SFE(){}

int TC_2SFE::adc_get(measurement m, float& output)
{
    cCP2130.choose_spi(cCP2130.cs4);
    sleep(0.1);
    char buff_s[12] = {0, 0, 2, 0, 4, 0, 0, 0, 0, 0xFF, 0xFF,0xFF}, buff_r[4] ={0};
    int t_code;
    uint16_t ADC_value;
    switch (m)
    {
        case AMUX: buff_s[8]=0b11000011; break;
        case ISEN: buff_s[8]=0b11010011; break;
        case THERM_SENSE: buff_s[8]=0b11100011; break;
    }
    cCP2130.spi_write (buff_s,sizeof(buff_s));
    t_code=cCP2130.spi_read(buff_r,sizeof(buff_r));
    if (t_code != 4 )
    {
        printf ("USB Transaction ERROR!\n");
        return -1000.0;
    }
    else if (buff_r[1] != buff_s[8])
    {
        printf ("SPI Transaction ERROR!\n");
        return -1000.0;
    }
    else
    {
        ADC_value = ( ( (buff_r[2] & 0x0F) << 6) + ( (buff_r[3] >> 1) & 0x3F) );
        std::cout << ADC_value << std::endl;
    }
    switch(m)
    {
        case THERM_SENSE:
        break;
        default:
        output = ( (ADC_value * ADC_VREF) * 1000) / 1023;
        std::cout << output << std::endl;
        break;
    }
    return 0;

}

int TC_2SFE::antenna_fc7(uint16_t pot_value,ant_channel c)
{
    cCP2130.gpio_set_output(cCP2130.cs5,0); //should be default configuration
    char ant_state=0;
    if(pot_value!=saved_pot_value){
    char buf_s[11]= {0, 0, 1, 0, 3, 0, 0, 0, 0xB0, ((pot_value&0x300) >> 8), (pot_value & 0xFF)};
    cCP2130.choose_spi(cCP2130.cs2);
    cCP2130.spi_write(buf_s,sizeof(buf_s));
    saved_pot_value=pot_value;
    }
    switch(c)
    {
        case NONE:
        cCP2130.gpio_set_output(cCP2130.cs1,0);
        ant_state=0b00000000;
        break;
        case _1:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00001000;
        break;
        case _2:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00000100;
        break;
        case _3:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00000010;
        break;
        case _4:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00000001;
        break;
        case ALL:
        cCP2130.gpio_set_output(cCP2130.cs1,1);
        ant_state=0b00001111;
        break;
    }
    char buf_s[9]={0, 0, 1, 0, 1, 0, 0, 0, ant_state};
    cCP2130.choose_spi(cCP2130.cs0);
    cCP2130.spi_write(buf_s,sizeof(buf_s));
    return 0;
}
int TC_2SFE::toggle_led()
{
    cCP2130.gpio_set_output(cCP2130.cs6,!test_led_state);
    return 0;
} 

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//

CP2130::CP2130() {}
CP2130::~CP2130(){
    if(fUsbHandle) close();
}
int CP2130::initialize()
{
     if ( ( fUsbHandle = setup_libusb_access() ) == NULL )
     {
        std::cout << "Failed to connect with CP2130, check if it is plugged in the USB port." << std::endl;
        exit ( -1 ); 
     }
     get_usb_config();
     usb_reset ( fUsbHandle ); // MISO doesn't work wihthout this...
     return 0;
}

void CP2130::close()
{
    usb_release_interface ( fUsbHandle, 0 );
    usb_close ( fUsbHandle );
    fUsbHandle = NULL;
    delete fUsbHandle;
}

void CP2130::reset_usb()
{
     usb_reset ( fUsbHandle );
}

int CP2130::gpio_set_input(cs_line c)
{
    char data[3]={(char)c,0,0};
    int result=usb_control_msg(fUsbHandle, 0x40, 0x23, 0, 0,  data, sizeof(data), fUsbTimeout);
    return 0;
}

int CP2130::gpio_set_output(cs_line c, bool level)
{
    char data[3]={(char)c,2,level};
    int result=usb_control_msg(fUsbHandle, 0x40, 0x23, 0, 0,  data, sizeof(data), fUsbTimeout);
    return 0;
}
int CP2130::choose_spi(cs_line c)
{
    char data[2]={c,2};
    int result = usb_control_msg(fUsbHandle, 0x40, 0x25, 0, 0, data, sizeof(data), fUsbTimeout);
    return 0;
    

}

int CP2130::configure_spi(cs_line c, device d)
{
    char data[2]={c,0};
    switch(d){
        case ADG731:
        data[1]=0b00011001; break; // analog switch ADG731
        case SI8902:
        data[1]=0b00111101; // ADC SI8902
        {
        char spi_delay[8] = {c, 0x0F,0, 1, 0, 0, 0, 1};
        int result2 = usb_control_msg (fUsbHandle, 0x40, 0x33, 0, 0, spi_delay, sizeof(spi_delay), fUsbTimeout);
        sleep(0.1);
        }
        break; 
        case ADG714: case ADG1414:
        data[1]=0b00011001; break; // analog switch ADG714
        case AD5231: case LTC6903:
        data[1]=0b00001101; break; // clock generator & digital potentiometer AD5231
        case MCP4921: 
	data[1]=0b00001010; break; // 12-bit DAC 
        case SC18IS600: 
        data[1]=0b00111011; // SPI TO I2C bridge
        {
        char spi_delay[8] = {c, 0b00001111,0, 0, 0, 0, 0, 0}; 
        int result2 = usb_control_msg (fUsbHandle, 0x40, 0x33, 0, 0, spi_delay, sizeof(spi_delay), fUsbTimeout);
        sleep(0.1);
        }
        break;
    }
    int result = usb_control_msg (fUsbHandle, 0x40, 0x31, 0, 0,  data , sizeof (data), fUsbTimeout );
    return 0;
}

int CP2130::spi_write(char* data, int size)
{
    return usb_bulk_write(fUsbHandle, fUsbEndpointBulkOut, data, size, fUsbTimeout );
}

int CP2130::spi_read(char* data, int size)
{
    return usb_bulk_read (fUsbHandle, fUsbEndpointBulkIn, data, size, fUsbTimeout);
}

int CP2130::get_product_string(char* data)
{
    int result = usb_control_msg (fUsbHandle, 0xC0, 0x66, 0, 0, (char*) data, 0x40, fUsbTimeout );
    std::rotate(data,data-2,data+sizeof(data)-1);
    return 0;
}

int CP2130::get_gpio_value(cs_line c, bool& level)
{
    char data[2]={0,0};
    int result = usb_control_msg (fUsbHandle, 0xC0, 0x20, 0, 0, data, 0x02, fUsbTimeout);
    switch(c){
        case cs0:
        level=(data[1]&0b00001000)!=0;break;
        case cs1:
        level=(data[1]&0b00010000)!=0;break;
        case cs2:
        level=(data[1]&0b00100000)!=0;break;
        case cs3:
        level=(data[1]&0b01000000)!=0;break;
        case cs4:
        level=(data[1]&0b10000000)!=0;break;
        case cs5:
        level=(data[0]&0b00000001)!=0;break;
        case cs6:
        level=(data[0]&0b00000100)!=0;break;
        case cs7:
        level=(data[0]&0b00001000)!=0;break;
        case cs8:
        level=(data[0]&0b00010000)!=0;break;
        case cs9:
        level=(data[0]&0b00100000)!=0;break;
        case cs10:
        level=(data[0]&0b01000000)!=0;break;
    }
    return 0;
}

int CP2130::set_usb_config()
{
    char data[10]={0,0,0,0,0,0x00,0,0,0,0b11111111};
    int result = usb_control_msg (fUsbHandle, 0x40, 0x61, 0, 0, data, 0x0A, fUsbTimeout);
    return 0;
}
int CP2130::get_usb_config()
{
    char data[9]={0};
    int result = usb_control_msg (fUsbHandle, 0xC0, 0x60, 0, 0, &data[0], 0x09, fUsbTimeout);
    return 0;
	//printf ("%c\n",data[5]);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
usb_dev_handle* CP2130::find_usb_handle()
{
    struct usb_bus* bus;
    struct usb_device* dev;

    for ( bus = usb_busses; bus; bus = bus->next )
    {
        for ( dev = bus->devices; dev; dev = dev->next )
        {
            if ( dev->descriptor.idVendor == VENDOR_ID &&
                    dev->descriptor.idProduct == PRODUCT_ID )
            {
                usb_dev_handle* handle;

                if ( ! ( handle = usb_open ( dev ) ) )
                {
                    exit(0);
                    return NULL;
                }

                return handle;
            }
        }
    }

    return NULL;
}

usb_dev_handle* CP2130::setup_libusb_access()
{
    usb_dev_handle* usb_handle;
    usb_set_debug ( 0 ); 
    usb_init();
    usb_find_busses();
    usb_find_devices();

    if ( ! ( usb_handle = find_usb_handle() ) )
    {
        std::cout << "Couldn't find the USB device, Exiting" << std::endl;
        std::cin.ignore();
        exit(0);
        return NULL;
    }

    if ( usb_set_configuration ( usb_handle, 1 ) < 0 )
    {
        std::cout << "Could not set configuration 1 : " << std::endl;

        return NULL;
    }

    if ( usb_claim_interface ( usb_handle, INTERF ) < 0 )
    {
        std::cout << "Could not claim interface: " << std::endl;
        exit(0);
        return NULL;
    }

    return usb_handle;
}

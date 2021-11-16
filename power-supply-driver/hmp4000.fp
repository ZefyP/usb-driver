s��        =�   O G  .�   �   ����                               hmp4000                         HAMEG HMP4000 Power Supply Driver                                                                        � ��ViStatus     � ��ViRsrc     	� 	��ViBoolean     	� 	��ViSession     � ��ViString     � ��ViUInt32  �  � ��ViInt32  � � ��ViReal64     �  ViChar[]  � � ��ViInt16  � � ��ViUInt16     	�  ViInt16[]     	�  ViInt32[]     
�  	ViReal64[]     � 	 
ViBoolean[]   L    This instrument module provides programming support for the HAMEG HMP4000.     T    This class contains all necessary functions for succesfull instrument configuring.     ]    This class contains all necessary functions for succesfull configuring Arbitrary Generator.     Q    This class contains all necessary functions for succesfull current configuring.     Q    This class contains all necessary functions for succesfull voltage configuring.        The section "General Instrument Settings" describes the settings which do not directly affect signal generation.

The following sections contain the remote-control functions for the general settings which are grouped in the Setup menus for manual control.     �    The section "Measurement" describes the settings which do not directly affect output.

The following sections contain the remote-control functions for the measuring the values.    Y    This class contains functions and sub-classes that control common instrument operations. These functions include many of functions that VXIplug&play require, such as reset, self-test, revision query, error query, and error message. This class also contains functions that access error infomation, lock the session, and perform instrument I/O.
     T    This class contains sub-classes for the set, get, and check attribute functions.       �    This class contains functions that set an attribute to a new value.  There are typesafe functions for each attribute data type.     V    This class contains functions that obtain the repeated capabilities of an attribute.     �    This class contains functions that obtain the current value of an attribute.  There are typesafe functions for each attribute data type.     N    This class contains functions that retrieve and clear the error information.     F    This class contains functions that send and receive instrument data.    �    Performs the following initialization actions:

- Creates a new instrument driver session.

- Opens a session to the specified device using the interface and address you specify for the Resource Name parameter.

- If the ID Query parameter is set to VI_TRUE, this function queries the instrument ID and checks that it is valid for this instrument driver.

- If the Reset parameter is set to VI_TRUE, this function resets the instrument to a known state.

- Sends initialization commands to set the instrument to the state necessary for the operation of the instrument driver.

- Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.

Important note:
The function creates new session each time you invoke it. Although for some instruments this is possible, we recommend not doing so.

The function hmp4000_InitWithOptions() offers the option to open new session or safely reuse an existing session. Consequently, no matter how many times you call it, there will be only one active session opened and you always get back the same instrumentHandle. For that, use the following call:

hmp4000_InitWithOptions(resourceName, idQuery, resetDevice, "ReuseSession=1", &instrumentHandle)    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.    �    Pass the resource name of the device to initialize.
You can also pass the name of a virtual instrument or logical name that you configure with the VISA Configuration utility. 

Examples of the direct VISA Resource Names (not all might be applicable to your instrument):

TCPIP0::192.168.2.100::inst0::INSTR - instrument is connected over LAN (VXI-11 protocol), its IP address is 192.168.2.100. The 'TCPIP0' identifies LAN-adapter index, if more than one are available. The part 'inst0' identifies the instance of an instrument in case of more logical instruments share the same IP address (e.g. R&S CMW). You can leave it out and use the shorter form TCPIP::192.168.2.100::INSTR

TCPIP0::192.168.2.100::hislip0 - instrument is connected over LAN (HiSLIP protocol), its IP address is 192.168.2.100. Similar to VXI-11, '0' at the end identifies instrument instance. Make sure your instrument supports the HISLIP protocol

TCPIP0::192.168.2.100::5025::SOCKET - instrument is connected over LAN (RawSocket), its IP address is 192.168.2.100 and the port is 5025

GPIB0::20::INSTR - instrument is connected over GPIB interface, its GPIB address is 20. If more GPIB controller cards are available, you distinguish between them with the 'GPIB0', 'GPIB1', 'GPIB2' and so on.

ASRL3::INSTR - instrument is connected over serial interface COM3.

USB::0x0AAD::0x0119::022019943::INSTR - instrument is connected over USB interface (USB Test and Measurement Class), with Vendor ID 0xAAD, Product ID 0x119, Serial Number 022019943        Specify whether you want the instrument driver to perform an ID Query.

Valid Range:
VI_TRUE  (1) - Perform ID Query (Default Value)
VI_FALSE (0) - Skip ID Query

When you set this parameter to VI_TRUE, the driver verifies that the instrument you initialize is a type that this driver supports.  

Circumstances can arise where it is undesirable to send an ID Query command string to the instrument.  When you set this parameter to VI_FALSE, the function initializes the instrument without performing an ID Query.     �    Specify whether you want the to reset the instrument during the initialization procedure.

Valid Range:
VI_TRUE  (1) - Reset Device (Default Value)
VI_FALSE (0) - Don't Reset

     �    Returns a unique ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.
The function creates new session each time you invoke it - see the note in the function description.    E#����  `    Status                             9   �  �    Resource Name                      9 �       ID Query                           9� �       Reset Device                      � �� �  �    Instrument Handle                  	           "GPIB::20::INSTR"   Yes VI_TRUE No VI_FALSE   Yes VI_TRUE No VI_FALSE    	           �    Performs the same actions as the hmp4000_init(), but in addition, you can change certain driver settings with the variable optionString. Option string consists of comma-separated tokens. See its description for more details.    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.    �    Pass the resource name of the device to initialize.
You can also pass the name of a virtual instrument or logical name that you configure with the VISA Configuration utility. 

Examples of the direct VISA Resource Names (not all might be applicable to your instrument):

TCPIP0::192.168.2.100::inst0::INSTR - instrument is connected over LAN (VXI-11 protocol), its IP address is 192.168.2.100. The 'TCPIP0' identifies LAN-adapter index, if more than one are available. The part 'inst0' identifies the instance of an instrument in case of more logical instruments share the same IP address (e.g. R&S CMW). You can leave it out and use the shorter form TCPIP::192.168.2.100::INSTR

TCPIP0::192.168.2.100::hislip0 - instrument is connected over LAN (HiSLIP protocol), its IP address is 192.168.2.100. Similar to VXI-11, '0' at the end identifies instrument instance. Make sure your instrument supports the HISLIP protocol

TCPIP0::192.168.2.100::5025::SOCKET - instrument is connected over LAN (RawSocket), its IP address is 192.168.2.100 and the port is 5025

GPIB0::20::INSTR - instrument is connected over GPIB interface, its GPIB address is 20. If more GPIB controller cards are available, you distinguish between them with the 'GPIB0', 'GPIB1', 'GPIB2' and so on.

ASRL3::INSTR - instrument is connected over serial interface COM3.

USB::0x0AAD::0x0119::022019943::INSTR - instrument is connected over USB interface (USB Test and Measurement Class), with Vendor ID 0xAAD, Product ID 0x119, Serial Number 022019943        Specify whether you want the instrument driver to perform an ID Query.

Valid Range:
VI_TRUE  (1) - Perform ID Query (Default Value)
VI_FALSE (0) - Skip ID Query

When you set this parameter to VI_TRUE, the driver verifies that the instrument you initialize is a type that this driver supports.  

Circumstances can arise where it is undesirable to send an ID Query command string to the instrument.  When you set this parameter to VI_FALSE, the function initializes the instrument without performing an ID Query.     �    Specify whether you want the to reset the instrument during the initialization procedure.

Valid Range:
VI_TRUE  (1) - Reset Device (Default Value)
VI_FALSE (0) - Don't Reset

    g    Modifies standard behavior of the driver session. The string consists of comma-separated tokens (Key = Value), which set the parameters of the driver session in that exact order. That means, if a token key is mentioned multiple times, the last value wins. Token names are case-insensitive. 
For boolean types, you can use the following values:
For FALSE: 0 / FALSE / False / OFF / Off /  VI_FALSE
For TRUE: 1 / TRUE / True / ON / On / VI_TRUE

Available tokens:

Simulate = boolean (default is FALSE). If set to TRUE, the driver session works in simulation mode.

ReuseSession  = boolean (default is FALSE). If FALSE, each call of the hmp4000_InitWithOptions() opens new 
VISA session to the instrument. If set to TRUE, as long as the entered resourceName is the same, the function first tries to reuse an existing session. Only if the session does not exist yet, it opens a new one.

UseExternalSession = boolean (default is FALSE). If set to TRUE, you can provide an externally opened VISA Session in the instrumentHandle variable as an input value. In this case, the driver does not open any new VISA session, but uses the provided one.
Calling hmp4000_close() does not cause this external VISA session to close.

MultiThreadLocking = boolean (default is FALSE). Set it to TRUE, if you work with multiple threads, and wish to make your session multithread-safe.

RangeCheck = boolean (default is TRUE). Sets the driver's range checking ON/OFF. Change it later with hmp4000_ConfigureErrorChecking()

QueryInstrStatus = boolean (default is TRUE). Sets the driver's instrument status checking after each command (*STB?) to ON/OFF. Change it later with hmp4000_ConfigureErrorChecking()

AutoSystemErrorQuery = boolean (default is FALSE). This feature is by default set to FALSE for legacy reasons. We recommend setting it to TRUE. If TRUE, in case the instrument status checking detects an error in the instrument error queue, it reads all the errors from that queue and makes them available through the hmp4000_GetError() function. Change it later with hmp4000_ConfigureAutoSystemErrQuery()

SendOpcQueryInCheckstatus = boolean (default is FALSE). If TRUE, the driver sends *OPC? query in the status checking. Use this if you experience measurement synchronization problems. Note, that this makes the communication with your instrument slower.

WriteDelay = integer (default is 0ms). Sets delay applied before each driver's VISA Write function.

ReadDelay = integer (default is 0ms). Sets delay applied before each driver's VISA Read function.

VisaTimeout = integer (default is driver-dependent, usually 10000ms). Sets the VISA timeout for the session. Change it later with hmp4000_SetVISATimeout()

OpcTimeout = integer (default is driver-dependent, usually 10000ms). Sets the OPC (Operation complete) timeout  for the session. Change it later with hmp4000_SetTimeout() or hmp4000_SetOpcTimeout()

IoSegmentSize = integer (default is 1E6 bytes). The maximum data size transferred in one chunk over VISA (write or read). If the required message is longer than this number, the communication is split to more read/write calls. The behavior is transparent for the user.

AssureWriteWithLf = boolean (default is TRUE for Socket and Serial interface, FALSE for all others). If set to TRUE, each VISA Write message is terminated with linefeed character (0x0A).

SelfTestTimeout = integer (default is 600000ms). Timeout for the self-test function of the driver. In case the self-test takes more time than this, change it with this token.

Example of the option string:
"Simulate=False, AutoSystemErrorQuery=True, SelfTestTimeout=100, IoSegmentSize=100E3, VisaTimeout=5000, OpcTimeout=30000"     �    Returns a unique ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.
The function creates new session each time you invoke it - see the note in the function description.    	#����  `    Status                            � 9   �  �    Resource Name                     #� 9 �       ID Query                          %� 9� �       Reset Device                      &� �  � �    Option String                     4� �� �  �    Instrument Handle                  	           "GPIB::14::INSTR"   Yes VI_TRUE No VI_FALSE   Yes VI_TRUE No VI_FALSE    "QueryInstrStatus=1"    	           �    This function selects the channels. All the following channel-selective commands will be applied for this channel

Attribute(s):
HMP4000_ATTR_SELECTION_OF_CHANNEL

Remote-control command(s):
INSTrument:SELect OUTPut1 | OUTPut2 | OUTPut3 | OUTPut4    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    $    This control selects the output channel.

Valid Values:
HMP4000_VAL_OUTPUT_1 (1) - Channel 1
HMP4000_VAL_OUTPUT_2 (2) - Channel 2
HMP4000_VAL_OUTPUT_3 (3) - Channel 3
HMP4000_VAL_OUTPUT_4 (4) - Channel 4

Default Value: HMP4000_VAL_OUTPUT_1 (1)

Attribute:
HMP4000_ATTR_SELECTION_OF_CHANNEL    8�#����  `    Status                            :g-   �  `    Instrument Handle                 ;� G � � `    Channel                            	           VI_NULL               |Channel 1 HMP4000_VAL_OUTPUT_1 Channel 2 HMP4000_VAL_OUTPUT_2 Channel 3 HMP4000_VAL_OUTPUT_3 Channel 4 HMP4000_VAL_OUTPUT_4    �    This function returns the currently selected channel.

Attribute(s):
HMP4000_ATTR_SELECTION_OF_CHANNEL

Remote-control command(s):
INSTrument:SELect?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control returns the selected channel.

Valid Values:
HMP4000_VAL_OUTPUT_1 (1) - Channel 1
HMP4000_VAL_OUTPUT_2 (2) - Channel 2
HMP4000_VAL_OUTPUT_3 (3) - Channel 3
HMP4000_VAL_OUTPUT_4 (4) - Channel 4

Attribute:
HMP4000_ATTR_SELECTION_OF_CHANNEL    >�#����  `    Status                            @[-   �  `    Instrument Handle                 A{ G � �  `    Channel                            	           VI_NULL    	            d    This function configures voltage and current. 

Attribute(s):
-

Remote-control command(s):
APPLy
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control adjust the output voltage level. 

Valid Values:
0.0 to 32.0 V

Default Value:
0.0

Note(s):

(1) - maximum level depends on channel
     �    This control adjust the output current value. 

Valid Values:
0.0 to 10.0 A

Default Value:
0.0

Note(s):

(1) - maximum value depends on channel

    C�#����  `    Status                            Ev-   �  `    Instrument Handle                 F� G � �  `    Voltage                           G2 HE �  `    Current                            	           VI_NULL    0.0    0.0   ~    Turns the channel output ON or OFF. When switching the channel ON, General output switch is also switched ON. When switching the channel OFF, General output switch is not changed. If changing the General output switch status is not desired, use the hmp4000_ConfigureOutputStateChannelOnly.

Attribute(s):
HMP4000_ATTR_OUTPUT_STATE

Remote-control command(s):
OUTPut:STATe ON | OFF    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Switches the output On or Off.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute(s):
HMP4000_ATTR_OUTPUT_STATE
    JN����  �    Status                            L   �  �    Instrument Handle                 L� G �  `    Output State                       	               On VI_TRUE Off VI_FALSE    �    Turning on / off all previous selected channels simultaneously.

Attribute(s):
HMP4000_ATTR_GENERAL_OUTPUT_STATE

Remote-control command(s):
OUTPut:GENeral    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Turning on / off all previous selected channels simultaneously. 

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute(s):
HMP4000_ATTR_GENERAL_OUTPUT_STATE
    N�����  �    Status                            P�   �  �    Instrument Handle                 Q. G �  `    Output State                       	               On VI_TRUE Off VI_FALSE    �    Turns the channel output ON or OFF. Compared to hmp4000_ConfigureOutputState, it doesn't change the General output switch settings. 

Attribute(s):
HMP4000_ATTR_OUTPUT_SELECT

Remote-control command(s):
OUTPut:SELect    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Turns the channel output ON or OFF.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute(s):
HMP4000_ATTR_OUTPUT_SELECT
    S�����  �    Status                            Uo   �  �    Instrument Handle                 V G �  `    Output State                       	               On VI_TRUE Off VI_FALSE       This function stores or recalls the settings from selected locations of a nonvolatile memory.

Attribute(s):
HMP4000_ATTR_SETTINGS_STORE_LOCATION
HMP4000_ATTR_SETTINGS_RECALL_LOCATION

Remote-control command(s):
*SAV {0|1|2|3|4|5|6|7|8|9}
*RCL {0|1|2|3|4|5|6|7|8|9}    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control selects the location. 

Valid Values:
0 to 9

Default Value:
0

Attribute(s):
HMP4000_ATTR_SETTINGS_STORE_LOCATION
HMP4000_ATTR_SETTINGS_RECALL_LOCATION
     �    This control selects the memory operation.

Valid Values:
HMP4000_VAL_MEM_OPERATION_STORE  (0) - Store
HMP4000_VAL_MEM_OPERATION_RECALL (1) - Recall

Default Value: HMP4000_VAL_MEM_OPERATION_STORE  (0)    X�#����  `    Status                            Z\-   �  `    Instrument Handle                 [| G8 �  `    Location                          \, G � � `    Memory Operation                   	           VI_NULL    0               NStore HMP4000_VAL_MEM_OPERATION_STORE Recall HMP4000_VAL_MEM_OPERATION_RECALL    u    This function queries combined setting of voltage and current. 

Attribute(s):
-

Remote-control command(s):
APPLy?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     C    This control returns the output voltage level. 

Attribute(s):
-
     C    This control returns the output current value. 

Attribute(s):
-
    ^�#����  `    Status                            `�-   �  `    Instrument Handle                 a� G k �  `    Voltage Value                     a� Ge �  `    Current                            	           VI_NULL    	           	              This function sets the parameters of the freely programmable waveforms. Set points defining voltage, current and dwell
time are required.

A maximum of 128 set points (index 0 ... 128) may be used and
will be repetitively addressed.

The maximum number of repetitions is 255. If Repetitons 0 is selected, the waveform will be repeated indefinitely. 

Attribute(s):
-
HMP4000_ATTR_ARBITRARY_GENERTOR_REPETITION

Remote-control command(s):
ARBitrary:DATA <voltage1, current1, time1, voltage2, ...>
ARBitrary:REPetitions    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    No. of repetition. The maximum number of repetitions is 255. If 0 is selected, the waveform will be repeated indefi nitely.

Valid Values:
0 to 255

Default Value: 0

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERTOR_REPETITION
     �    This control defines the array of voltage points for waveform data.

Valid Values:
0.0 to 32.0 V

Default Value: 0.0

Attribute(s):
-
     �    This control defines the array of current points for waveform data.

Valid Values:
0.0 to 10.0 A

Default Value: 0.0

Attribute(s):
-
     �    This control defines the array of time points for waveform data.

Valid Values:
0.0 to 99.99 s

Default Value: 0.0

Attribute(s):
-
     �    This control defines no. of points of voltage, current and time array for Waveform Data. 

Valid Values:
0 to 128

Default Value: 128
    eY#����  `    Status                            g!-   �  `    Instrument Handle                 hA � � �  `    Repetition                        i+ � p �  `    Voltage                           i� � � �  `    Current                           jK �j �  `    Time                              j� G � �  `    Array Size                         	           VI_NULL    0                128    �    This function selects the channel for starting arbitrary generator. 

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERTOR_START_CHANNEL

Remote-control command(s):
ARBitrary:STARt    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    h    This control selects the output channel.

Valid Values:
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_1 (1)

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERTOR_START_CHANNEL

Note(s):
HMP4030 - Channel 4 not available
    m�#����  `    Status                            o�-   �  `    Instrument Handle                 p� G � � `    Channel                            	           VI_NULL               lChannel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4    �    This function selects the channel where stop the arbitrary generator. 

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERTOR_STOP_CHANNEL

Remote-control command(s):
ARBitrary:STOP    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    g    This control selects the output channel.

Valid Values:
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_1 (1)

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERTOR_STOP_CHANNEL

Note(s):
HMP4030 - Channel 4 not available
    t#����  `    Status                            u�-   �  `    Instrument Handle                 v� G � � `    Channel                            	           VI_NULL               lChannel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4    �    This function selects the channel where the data entered are sent to.

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL

Remote-control command(s):
ARBitrary:TRANsfer    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    q    This control selects the output channel.

Valid Values:
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_1 (1)

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL

Note(s):
HMP4030 - Channel 4 not available
    zN#����  `    Status                            |-   �  `    Instrument Handle                 }6 G � � `    Channel                            	           VI_NULL               lChannel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4   ;    This function selects the storage for saving, recalling or clearing arbitrary generator waveform data. 

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE
HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL
HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR

Remote-control command(s):
ARBitrary:SAVE
ARBitrary:RESTore
ARBitrary:CLEar
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    W    This control selects the memory index.

Valid Values:
HMP4000_VAL_MEM_1 (1) - Memory index 1
HMP4000_VAL_MEM_2 (2) - Memory index 2
HMP4000_VAL_MEM_3 (3) - Memory index 3

Default Value: HMP4000_VAL_MEM_1 (1)

Attribute(s):
HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE
HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL
HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR
     �    This control selects the memory operation.

Valid Values:
HMP4000_VAL_MEM_OPERATION_STORE  (0) - Store
HMP4000_VAL_MEM_OPERATION_RECALL (1) - Recall
HMP4000_VAL_MEM_OPERATION_CLEAR  (2) - Clear

Default Value: HMP4000_VAL_MEM_OPERATION_STORE  (0)    �##����  `    Status                            ��-   �  `    Instrument Handle                 � G1 � `    Memory Index                      �j H � � `    Memory Operation                   	           VI_NULL               <1 HMP4000_VAL_MEM_1 2 HMP4000_VAL_MEM_2 3 HMP4000_VAL_MEM_3               tStore HMP4000_VAL_MEM_OPERATION_STORE Recall HMP4000_VAL_MEM_OPERATION_RECALL Clear HMP4000_VAL_MEM_OPERATION_CLEAR    �    This function adjusts the output current. 

Attribute(s):
HMP4000_ATTR_OUTPUT_CURRENT_LEVEL

Remote-control command(s):
SOURce:CURRent:LEVel:AMPLitude
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control adjust the output current value. 

Valid Values:
0.0 to 10.0 A

Default Value:
0.0

Attribute(s):
HMP4000_ATTR_OUTPUT_CURRENT_LEVEL

Note(s):

(1) - maximum value depends on channel
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    Current                            	           VI_NULL    0.0   )    This function switches On or Off the electronic fuse and link or unlink from the channel.

Attribute(s):
HMP4000_ATTR_ELECTRONIC_FUSE_STATE
HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK
HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK

Remote-control command(s):
FUSE:STATe ON | OFF
FUSE:LINK
FUSE:UNLink    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None     �    Switches the fuse On or Off.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)

Attribute(s):
HMP4000_ATTR_ELECTRONIC_FUSE_STATE
    �    This control selects the output channel for electronic fuse.

Valid Values:
HMP4000_VAL_CH_N (0)  - Not Used
HMP4000_VAL_CH_1 (1)  - Output Channel 1
HMP4000_VAL_CH_2 (2)  - Output Channel 2
HMP4000_VAL_CH_3 (3)  - Output Channel 3
HMP4000_VAL_CH_4 (4)  - Output Channel 4

Default Value: HMP4000_VAL_CH_N (0)

Attribute(s):
HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK

Note(s):
HMP4030 - Channel 4 not available
    �    This control selects the output channel for electronic fuse.

Valid Values:
HMP4000_VAL_CH_N (0) - Not Used
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_N (0)

Attribute(s):
HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK

Note(s):
HMP4030 - Channel 4 not available
    �g����  �    Status                            �/   �  �    Instrument Handle                 �� G � �  `    Fuse                              �x G � � `    Link to Channel                   � Gj � `    Unlink from Channel                	               On VI_TRUE Off VI_FALSE               �Not Used HMP4000_VAL_CH_N Channel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4               �Not used HMP4000_VAL_CH_N Channel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4    �    This function configures the output current step value. 

Attribute(s):
HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP

Remote-control command(s):
SOURce:CURRent:LEVel:AMPLitude:STEP:INCRement    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control sets the current step.

Valid Values:
0.0 to 10.0 A

Default Value: 0.0

Attribute(s):
HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    Current Step                       	           VI_NULL    0.0    �    This function queries the electronic fuse status. 

Attribute(s):
HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS

Remote-control command(s):
FUSE:TRIPped?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    Returns the fuse status.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Attribute(s):
HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    Fuse Status                        	           VI_NULL    	            �    This function adjusts the output voltage level. 

Attribute(s):
HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL

Remote-control command(s):
SOURce:VOLTage:LEVel:AMPLitude
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control adjust the output voltage level. 

Valid Values:
0.0 to 32.0 V

Default Value:
0.0

Attribute(s):
HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL

Note(s):

(1) - maximum level depends on channel
    ��#����  `    Status                            �a-   �  `    Instrument Handle                 �� G � �  `    Voltage                            	           VI_NULL    0.0    �    This function configures the over voltage protection (OVP). 

Attribute(s):
HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL

Remote-control command(s):
VOLTage:PROTection:LEVel
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control configures the output over voltage protection level. 

Valid Values:
0.0 to 33.0 V

Default Value:
33.0

Attribute(s):
HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    OVP Value                          	           VI_NULL    33.0    �    This function configures the output voltage step value. 

Attribute(s):
HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP

Remote-control command(s):
SOURce:VOLTage:LEVel:AMPLitude:STEP:INCRement    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    This control sets the voltge step.

Valid Values:
0.0 to 32.0 V

Default Value: 0.0

Attribute(s):
HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    Voltage Step                       	           VI_NULL    0.0    �    This function queries the over voltage protection (OVP) status. 

Attribute(s):
HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS

Remote-control command(s):
VOLTage:PROTection:TRIPped?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     �    Returns the OVP status.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Attribute(s):
HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    OVP Status                         	           VI_NULL    	            �    This function clears the over voltage protection (OVP). 

Attribute(s):
HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR

Remote-control command(s):
VOLTage:PROTection:CLEar    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    ��#����  `    Status                            ��-   �  `    Instrument Handle                  	           VI_NULL    �    Sets the OVP mode for the previously selected channel.

Attribute(s):
HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE

Remote-control command(s):
[SOURce:]VOLTage:PROTection:MODE    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
    �    Sets the OVP mode for the previously selected channel.

Valid Values:
HMP4000_VAL_OVP_MODE_MEASURED  (0) - Measured
HMP4000_VAL_OVP_MODE_PROTECTED (1) - Protected

Default Value: HMP4000_VAL_OVP_MODE_MEASURED (0)

Attribute:
HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE

Note(s):

(1) Measured: The OVP turns off if the measured value exceeds the threshold.

(2) Protected: If the adjusted threshold is exceeded, you cannot turn on the output of the instrument. In addition, the measured value is monitored.    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� L � � `    Mode                               	           VI_NULL               PMeasured HMP4000_VAL_OVP_MODE_MEASURED Protected HMP4000_VAL_OVP_MODE_PROTECTED    �    This function configures the beeper.

Attribute(s):
HMP4000_ATTR_BEEPER_MODE

Remote-control command(s):
SYSTem:BEEPer[:IMMediate]    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
        This control selects the mode of the beeper.

Valid Values:
HMP4000_VAL_BEEPER_OFF      (0) - Off
HMP4000_VAL_BEEPER_ON       (1) - On
HMP4000_VAL_BEEPER_CRITICAL (2) - Critical Events Only

Default Value: HMP4000_VAL_BEEPER_OFF (0)

Attribute(s):
HMP4000_ATTR_BEEPER_MODE
    �z#����  `    Status                            �B-   �  `    Instrument Handle                 �b G � � `    Beeper                             	           VI_NULL               eOff HMP4000_VAL_BEEPER_OFF On HMP4000_VAL_BEEPER_ON Critical Events Only HMP4000_VAL_BEEPER_CRITICAL    �    This function queries the measured voltage value. 

Attribute(s):
HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE

Remote-control command(s):
MEASure[:VOLTage][:DC]?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     ^    This control returns the measured value.

Attribute(s):
HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE
    �J#����  `    Status                            �-   �  `    Instrument Handle                 �2 G � �  `    Voltage Value                      	           VI_NULL    	           �    This function queries the measured Current value. 

Attribute(s):
HMP4000_ATTR_MEASUREMENT_DC_CURRENT

Remote-control command(s):
MEASure:CURRent[:DC]?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     ^    This control returns the measured value.

Attribute(s):
HMP4000_ATTR_MEASUREMENT_DC_CURRENT
    ��#����  `    Status                            ��-   �  `    Instrument Handle                 �� G � �  `    Current Value                      	           VI_NULL    	          �    This function sets the value of a ViInt32 attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes.  It is best to use the high-level driver functions as much as possible.  They handle order dependencies and multithread locking for you.  In addition, they perform status checking only after setting all of the attributes.  In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change.  Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.


    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    (    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Attributes 
  whose value cannot be set are dim.  Help text is shown for 
  each attribute.  Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box.  If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all the attributes of the ViInt32 type.   
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim.  If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                           ��#����  `    Status                            ա-   �  `    Instrument Handle                 �Y =  �  �    Repeated Capability Name          �5 = � � �    Attribute ID                      �e � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViReal64 attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    5    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViReal64
  type.  If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViReal64 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                           ��#����  `    Status                            �-   �  `    Instrument Handle                 �c =  �  �    Repeated Capability Name          �? = � � �    Attribute ID                      �| � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViString attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    4    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViString
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViString are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                           ��#����  `    Status                            ��-   �  `    Instrument Handle                 �z =  �  �    Repeated Capability Name          �V = � � �    Attribute ID                     � � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0       �    This function sets the value of a ViBoolean attribute.

This is a low-level function that you can use to set the values of instrument-specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid or is different than the value you specify. 

This instrument driver contains high-level functions that set most of the instrument attributes. It is best to use the high-level driver functions as much as possible. They handle order dependencies and multithread locking for you. In addition, they perform status checking only after setting all of the attributes. In contrast, when you set multiple attributes using the SetAttribute functions, the functions check the instrument status after each call.

Also, when state caching is enabled, the high-level functions that configure multiple attributes perform instrument I/O only for the attributes whose value you change. Thus, you can safely call the high-level functions without the penalty of redundant instrument I/O.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    6    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Attributes 
  whose value cannot be set are dim. Help text is shown for 
  each attribute. Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box. If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViBoolean
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box.
  Attributes with data types other than ViBoolean are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
        Pass the value to which you want to set the attribute.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has constants as valid values, you can view a list of
  the constants by pressing <ENTER> on this control.  Select a
  value by double-clicking on it or by selecting it and then
  pressing <ENTER>.  

  Note:  Some of the values might not be valid depending on the
  current settings of the instrument session.

Default Value: none  ���� � ���                                          
#����  `    Status                           �-   �  `    Instrument Handle                � =  �  �    Repeated Capability Name         m = � � �    Attribute ID                     � � � �  �    Attribute Value                    .Press <ENTER> for a list of 
value constants.    	               ""                0        �    Function used by Hi-level functions to obtain a repCap name from:
    - attributeID
    - repCapNameID
    - 0-based index in the repCapNames    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.The handle identifies a particular instrument session.

Default Value:  None
    (    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Attributes 
  whose value cannot be set are dim.  Help text is shown for 
  each attribute.  Select an attribute by double-clicking on it  
  or by selecting it and then pressing <ENTER>.

  Read-only attributes appear dim in the list box.  If you 
  select a read-only attribute, an error message appears.

  A ring control at the top of the dialog box allows you to see 
  all the attributes of the ViInt32 type.   
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box. 
  Attributes with data types other than ViInt32 are dim.  If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
         RepCap Name ID.     &    Zero based index in the repCapNames.     k    Pass the number of bytes in the string you allocate for the repCapName.

Valid Range:
-

Default Value: 0         String returning RepCap name.   �#����  `    Status                           �-   �  `    Instrument Handle                v G % � �    Attribute ID                     � G �  `    RepCap Name ID                   � G� �  `    Index                            � � ~ �  x    Buffer Size                       ` �3 �  `    RepCapName                         	                       L  �Class Driver Major Version RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MAJOR_VERSION Class Driver Minor Version RS_ATTR_CLASS_DRIVER_CLASS_SPEC_MINOR_VERSION Class Specification Major Version RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION Class Specification Minor Version RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION Channel Count RS_ATTR_CHANNEL_COUNT Primary Error RS_ATTR_PRIMARY_ERROR Secondary Error RS_ATTR_SECONDARY_ERROR Driver Major Version RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION Driver Minor Version RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION Driver Minor Minor Version RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION Class Major Version RS_ATTR_CLASS_DRIVER_MAJOR_VERSION Class Minor Version RS_ATTR_CLASS_DRIVER_MINOR_VERSION Engine Major Version RS_ATTR_ENGINE_MAJOR_VERSION Engine Minor Version RS_ATTR_ENGINE_MINOR_VERSION Operation Complete (OPC) Timeout RS_ATTR_OPC_TIMEOUT Display Size RSPWRMETER_ATTR_DISP_SIZE Selected Window RSPWRMETER_ATTR_DISP_SELECTED_WINDOW User-Defined Message Type RSPWRMETER_ATTR_DISP_MSG_TYPE Channel Mode RSPWRMETER_ATTR_CHANNEL_MODE Auxiliary RSPWRMETER_ATTR_CHANNEL_AUXILIARY Selected Timegate RSPWRMETER_ATTR_CHANNEL_SELECTED_TIMEGATE Display Resolution RSPWRMETER_ATTR_CHANNEL_DISPLAY_RESOLUTION Display Timeslot RSPWRMETER_ATTR_CHANNEL_DISPLAY_TIMESLOT Display Mode RSPWRMETER_ATTR_CHANNEL_DISPLAY_MODE Additional Info RSPWRMETER_ATTR_CHANNEL_DISPLAY_ADDITIONAL_INFO Average Count RSPWRMETER_ATTR_CHANNEL_AVER_COUNT Average Domain RSPWRMETER_ATTR_CHANNEL_AVER_DOMAIN Average Terminal Control RSPWRMETER_ATTR_CHANNEL_AVER_TERMINAL_CONTROL Average Auto Mode RSPWRMETER_ATTR_CHANNEL_AVER_AUTO_MODE Average Auto Resolution RSPWRMETER_ATTR_CHANNEL_AVER_AUTO_RESOLUTION Average Auto Timeslot RSPWRMETER_ATTR_CHANNEL_AVER_AUTO_TIMESLOT Range Path RSPWRMETER_ATTR_RANGE_PATH Channel Trigger Source RSPWRMETER_ATTR_CHANNEL_TRIGGER_SOURCE Channel Trigger Count RSPWRMETER_ATTR_CHANNEL_TRIGGER_COUNT Channel Trigger Slope RSPWRMETER_ATTR_CHANNEL_TRIGGER_SLOPE Channel Trigger Master Port RSPWRMETER_ATTR_CHANNEL_TRIGGER_MASTER_PORT Channel Trigger Synchronize Port RSPWRMETER_ATTR_CHANNEL_TRIGGER_SYNCHRONIZE_PORT Channel External Trigger Impedance RSPWRMETER_ATTR_CHANNEL_TRIGGER_EXTERNAL_IMPEDANCE Trigger Jitter Suppression Method RSPWRMETER_ATTR_TRIGGER_JITTER_SUPPRESSION_METHOD Device RSPWRMETER_ATTR_CORR_SPARAM_DEVICE ContAv Buffer Size RSPWRMETER_ATTR_CHANNEL_CONTAV_BUFFER_SIZE ContAv Sampling Rate RSPWRMETER_ATTR_CHANNEL_CONTAV_SAMPLING Points RSPWRMETER_ATTR_CHANNEL_TRACE_POINTS Trace Average Count RSPWRMETER_ATTR_CHANNEL_TRACE_FILTER_AVER_COUNT Trace Terminal Control RSPWRMETER_ATTR_CHANNEL_TRACE_FILTER_TERMINAL_CONTROL Algorithm RSPWRMETER_ATTR_CHANNEL_TRACE_MEAS_ALGORITHM Statistics Samples RSPWRMETER_ATTR_CHANNEL_STAT_SAMPLES Statistics Scale Points RSPWRMETER_ATTR_CHANNEL_STAT_SCALE_POINTS Timeslot Count RSPWRMETER_ATTR_CHANNEL_TIMESLOT_COUNT Volt IQ Sample Count RSPWRMETER_ATTR_VOLT_IQ_SAMPLE_COUNT Filter Type RSPWRMETER_ATTR_FILTER_TYPE Bandwidth Type RSPWRMETER_ATTR_BANDWIDTH_TYPE IF Sideband Selected RSPWRMETER_ATTR_IF_SIDEBAND_SELECTED Reference Oscillator Source RSPWRMETER_ATTR_REFERENCE_OSCILLATOR_SOURCE Trigger Source RSPWRMETER_ATTR_TRIGGER_SOURCE Trigger Count RSPWRMETER_ATTR_TRIGGER_COUNT Trigger Slope RSPWRMETER_ATTR_TRIGGER_SLOPE Units RSPWRMETER_ATTR_MEAS_BLOCK_UNITS Ratio Units RSPWRMETER_ATTR_MEAS_BLOCK_RATIO_UNITS Calculation RSPWRMETER_ATTR_MEAS_GATE_CALCULATION System Speed RSPWRMETER_ATTR_SYSTEM_SPEED Operation Complete (OPC) Timeout RSPWRMETER_ATTR_OPC_TIMEOUT Visa Timeout RSPWRMETER_ATTR_VISA_TIMEOUT System Emulation RSPWRMETER_ATTR_SYSTEM_EMULATION System Clock Source RSPWRMETER_ATTR_SYSTEM_CLOCK_SOURCE TTL Active RSPWRMETER_ATTR_SYSTEM_IO_OUT1_TTL_ACTIVE TTL Fail RSPWRMETER_ATTR_SYSTEM_IO_OUT1_TTL_FAIL TTL Limited Calc Block RSPWRMETER_ATTR_SYSTEM_IO_OUT1_TTL_LIMITED_CALC_BLOCK Selected Calc Block RSPWRMETER_ATTR_SYSTEM_IO_ANALOG_OUTPUT_SELECTED_CALC_BLOCK Display Update RSPWRMETER_ATTR_SYSTEM_MISC_DISPLAY_UPDATE System Trigger Source RSPWRMETER_ATTR_SYSTEM_STD_TRIGGER_SOURCE IP Address Mode RSPWRMETER_ATTR_SYSTEM_NETWORK_IP_ADDRESS_MODE Socket Mode RSPWRMETER_ATTR_SYSTEM_NETWORK_SOCKET_MODE Socket Port RSPWRMETER_ATTR_SYSTEM_NETWORK_SOCKET_PORT LED Mode RSPWRMETER_ATTR_LED_MODE LED Color RSPWRMETER_ATTR_LED_COLOR    ""    0    0    	            �    This function returns the repeated capability id(s) that belongs to the attribute you specify. More then one id is listed in comma separated string.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         Pass the ID of an attribute.
     ~    Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id(s) parameter.  

Default Value: 256
    |    The buffer in which the function returns the repeated capability id(s) belonging to the attribute. The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.

If the attribute applies to a repeated capability such as a trace, this parameter returns the Ids of the repeated capability on which to set the value of the attribute.
   3�#����  `    Status                           5z-   �  `    Instrument Handle                62 G L � �    Attribute ID                     6Y G[ �  �    Buffer Size                      6� � L � �    Repeated Capability Id(s)          	                           0    256    	            �    This function returns the repeated capability name(s) that belongs to the attribute and single repeated capability id you may specify. More then one name is listed in comma separated string.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         Pass the ID of an attribute.
     �    If the attribute applies to a repeated capability such as a trace, this parameter defines the Id of the repeated capability on which to query repeated capability id name(s).

Default Value: ""
     �    Pass the number of bytes in the ViChar array you specify for the Repeated Capability Id Name(s) parameter.  

Default Value: 256
     �    The buffer in which the function returns the repeated capability id name(s) belonging to the attribute. The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.
   :j#����  `    Status                           <2-   �  `    Instrument Handle                <� G  � �    Attribute ID                     = G �  �    Repeated Capability Id           =� G� �  b    Buffer Size                      >g � L � �    Repeated Capability Id Name(s)     	                           0    ""    256    	           �    This function queries the value of a ViInt32 attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""
    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViInt32 type. 
  If you choose to see all attributes, the data types appear
  to the right of the attribute names in the list box.  
  Attributes with data types other than ViInt32 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViInt32 variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   Bu#����  `    Status                           D=-   �  `    Instrument Handle                D� =  �  �    Repeated Capability Name         F� = � � �    Attribute ID                     Kg � � �  �    Attribute Value                    	               ""                0    	           �    This function queries the value of a ViReal64 attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes. Help text is
  shown for each attribute. Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViReal64
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViReal64 are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViReal64 variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   P#����  `    Status                           Q�-   �  `    Instrument Handle                R� =  �  �    Repeated Capability Name         Tt = � � �    Attribute ID                     Y
 � � �  �    Attribute Value                    	               ""                0    	          )    This function queries the value of a ViString attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid. 

You must provide a ViChar array to serve as a buffer for the value. You pass the number of bytes in the buffer as the Buffer Size parameter. If the current value of the attribute, including the terminating NUL byte, is larger than the size you indicate in the Buffer Size parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you want to call this function just to get the required buffer size, you can pass 0 for the Buffer Size and VI_NULL for the Attribute Value buffer.  

If you want the function to fill in the buffer regardless of the   number of bytes in the value, pass a negative number for the Buffer Size parameter.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Help text is
  shown for each attribute.  Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViString
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViString are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Pass the number of bytes in the ViChar array you specify for the Attribute Value parameter.  

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Attribute Value buffer parameter.

Default Value: 512    &    The buffer in which the function returns the current value of the attribute.  The buffer must be of type ViChar and have at least as many bytes as indicated in the Buffer Size parameter.

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you specify 0 for the Buffer Size parameter, you can pass VI_NULL for this parameter.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   a7#����  `    Status                           b�-   �  `    Instrument Handle                c� =  �  �    Repeated Capability Name         e� = � � �    Attribute ID                     j* =� �  �    Buffer Size                      m  � L � �    Attribute Value                    	               ""                0    512    	           �    This function queries the value of a ViBoolean attribute.

You can use this function to get the values of instrument- specific attributes and inherent attributes. If the attribute represents an instrument state, this function performs instrument I/O in the following cases:

- State caching is disabled for the entire session or for the particular attribute.

- State caching is enabled and the currently cached value is invalid.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    If the attribute applies to a repeated capability such as a trace, this parameter specifies the name of the repeated capability on which to set the value of the attribute. If the attribute does not apply to a repeated capability, then pass VI_NULL or an empty string.

This control accepts either a virtual repeated capability name or an instrument-specific name. For valid repeated capability names, refer to your configuration settings in MAX.

Default Value:  ""    �    Pass the ID of an attribute.

From the function panel window, you can use this control as follows.

- Click on the control or press <ENTER>, <spacebar>, or
  <ctrl-down arrow>, to display a dialog box containing a
  hierarchical list of the available attributes.  Help text is
  shown for each attribute.  Select an attribute by 
  double-clicking on it or by selecting it and then pressing
  <ENTER>.

  A ring control at the top of the dialog box allows you to see 
  all attributes or only the attributes of the ViBoolean
  type. If you choose to see all attributes, the data types
  appear to the right of the attribute names in the list box. 
  Attributes with data types other than ViBoolean are dim. If
  you select an attribute data type that is dim, LabWindows/CVI
  transfers you to the function panel for the corresponding
  function that is consistent with the data type.

- If you want to enter a variable name, press <CTRL-T> to change
  this ring control to a manual input box.

- If the attribute in this ring control has named constants as  
  valid values, you can view the constants by moving to the 
  Attribute Value control and pressing <ENTER>.
    �    Returns the current value of the attribute.  Pass the address of a ViBoolean variable.

From the function panel window, you can use this control as follows.

- If the attribute currently showing in the Attribute ID ring
  control has named constants as valid values, you can view a
  list of the constants by pressing <ENTER> on this control.  
  Select a value by double-clicking on it or by selecting it and 
  then pressing <ENTER>.  
   t#����  `    Status                           vG-   �  `    Instrument Handle                v� =  �  �    Repeated Capability Name         x� = � � �    Attribute ID                     }t � � �  �    Attribute Value                    	               ""                0    	           X    This function resets the instrument to a known state and sends initialization commands to the instrument. The initialization commands set instrument settings such as Headers Off, Short Command form, and Data Transfer Binary to the state necessary for the operation of the instrument driver.

Attribute(s):
-

Remote-control command(s):
*RST

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   ��#����  `    Status                           ��-   �  `    Instrument Handle                  	               �    This function runs the instrument's self test routine and returns the test result(s). 

Attribute(s):
HMP4000_ATTR_SERVICE_STEST

Remote-control command(s):
*TST?
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    This control contains the value returned from the instrument self test.  Zero means success.  For any other code, see the device's operator's manual.
     �    This control contains the string returned from the self test. See the device's operation manual for an explanation of the string's contents.

Notes:

(1) The array must contain at least 256 elements ViChar[256].   �x#����  `    Status                           �@-   �  `    Instrument Handle                �� G Q �  `    Self Test Result                 �� G � � ,    Self-Test Message                  	               	           	            �    This function returns the revision numbers of the instrument driver and instrument firmware.

Attribute(s):

Remote-control command(s):



    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     �    Returns the instrument driver software revision numbers in the form of a string.

You must pass a ViChar array with at least 256 bytes.     �    Returns the instrument firmware revision numbers in the form of a string.

You must pass a ViChar array with at least 256 bytes.
   �#����  `    Status                           ��-   �  `    Instrument Handle                �� 9  �  �    Instrument Driver Revision       � 9Y �  �    Firmware Revision                  	               	            	            �    This function queries the number of the SCPI version, which is relevant for the instrument.

Attribute(s):
HMP4000_ATTR_SYSTEM_VERSION

Remote-control command(s):
SYSTem:VERSion?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the agesa_init or agesa_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None     b    Sets the allocated memory length of System Version string.

Valid Values: >0

Default Value: 255     P    Returns the number of the SCPI version, which is relevant for the instrument.
   �Z#����  `    Status                           �"-   �  `    Instrument Handle                �� G | �  `    Length                           �? GE �  `    System Version                     	               255    	           �    This function reads an error code and a message from the instrument's error queue.

Attribute(s):
HMP4000_ATTR_SYST_ERR

Remote-control command(s):
SYSTem:ERRor?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     B    Returns the error code read from the instrument's error queue.

     �    Returns the error message string read from the instrument's error message queue.

You must pass a ViChar array with at least 1024 bytes.
   �9#����  `    Status                           �-   �  `    Instrument Handle                �� 9  �  �    Error Code                       � 9 � � ,    Error Message                      	               	           	            �    This function converts a status code returned by an instrument driver function into a user-readable string. 

Attribute(s):

Remote-control command(s):
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.        The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

You can pass VI_NULL for this parameter.  This is useful when one of the initialize functions fail.

Default Value:  VI_NULL
     z    Pass the Status parameter that is returned from any of the instrument driver functions.

Default Value:  0  (VI_SUCCESS)     �    Returns the user-readable message string that corresponds to the status code you specify.

You must pass a ViChar array with at least 256 bytes.
   �4#����  `    Status                           ��-   �  `    Instrument Handle                � 9  �  h    Error Code                       �� 9 � � �    Error Message                      	           VI_NULL    0    	           z    This function configures the selected register enable values.

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER

Remote-control command(s):
STATus:QUEStionable:ENABle
STATus:QUEStionable:INSTrument:ENABle
STATus:QUEStionable:INSTrument:ISUMmary<n>:ENABle    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None    O    Select register.

Valid Values:
HMP4000_VAL_QUESTIONABLE_REGISTER (0) - Questionable Register
HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER (1) - Questionable Instrument Register
HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER (2) - Questionable Instrument Specific Register

Default Value: HMP4000_VAL_QUESTIONABLE_REGISTER (0)     �    Configures the selected register value.

Default Value: 0

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER
    �    This control selects the channel.

Valid Values:
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_1 (1)

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER

Note(s):
(1) HMP4030 - Channel 4 not available
(2) Valid only for instrument specific registers   ������  �    Status                           �   �  �    Instrument Handle                � G & � �    Registers                        �u �j �  `    Value                            �e Hj � `    Channel                            	                          �Questionable Register HMP4000_VAL_QUESTIONABLE_REGISTER Questionable Instrument Register HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER Questionable Instrument Specific Register HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER    0               lChannel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4   �    This function queries the selected register event and condition values.

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER

Remote-control command(s):
STATus:QUEStionable:ENABle
STATus:QUEStionable:INSTrument:ENABle
STATus:QUEStionable:INSTrument:ISUMmary<n>:ENABle
STATus:QUEStionable:INSTrument:ISUMmary<n>:CONDition?
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    This control accepts the Instrument Handle returned by the Initialize function to select the desired instrument driver session.

Default Value:  None        Select register.

Valid Values:
HMP4000_VAL_QUESTIONABLE_REGISTER                               (0) - Questionable Register
HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER                    (1) - Questionable Instrument Register
HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER           (2) - Questionable Instrument Specific Register
HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER (3) - Questionable Instrument Specific Register Condition

Default Value: HMP4000_VAL_QUESTIONABLE_REGISTER (0)        Returns the selected register value.

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER
    �    This control selects the channel.

Valid Values:
HMP4000_VAL_CH_1 (1) - Output Channel 1
HMP4000_VAL_CH_2 (2) - Output Channel 2
HMP4000_VAL_CH_3 (3) - Output Channel 3
HMP4000_VAL_CH_4 (4) - Output Channel 4

Default Value: HMP4000_VAL_CH_1 (1)

Attribute(s):
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER
HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER

Note(s):
(1) HMP4030 - Channel 4 not available
(2) Valid only for instrument specific registers   ������  �    Status                           �l   �  �    Instrument Handle                � G % � �    Registers                        � �j �  `    Value                            �3 Hj � `    Channel                            	                         ZQuestionable Register HMP4000_VAL_QUESTIONABLE_REGISTER Questionable Instrument Register HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER Questionable Instrument Specific Register HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER Questionable Instrument Specific Register Condition HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER    	                       lChannel 1 HMP4000_VAL_CH_1 Channel 2 HMP4000_VAL_CH_2 Channel 3 HMP4000_VAL_CH_3 Channel 4 HMP4000_VAL_CH_4    �    This function configures the remote mode.

Attribute(s):
HMP4000_ATTR_SYSTEM_LOCAL
HMP4000_ATTR_SYSTEM_REMOTE
HMP4000_ATTR_SYSTEM_REMOTE_LOCK
HMP4000_ATTR_SYSTEM_REMOTE_MIX

Remote-control command(s):
SYSTem:LOCal
SYSTem:REMote
SYSTem:RWLock
SYSTem:MIX    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    �    This control selects the remote mode.

Valid Values:
HMP4000_VAL_LOCAL       (0) - Local
HMP4000_VAL_REMOTE      (1) - Remote
HMP4000_VAL_REMOTE_LOCK (2) - Remote Lock
HMP4000_VAL_REMOTE_MIX  (3) - Remote Mix

Default Value: HMP4000_VAL_LOCAL (0)

Note(s):

(1) Local: Sets the system to front panel control. The front panel control is unlocked.

(2) Remote: Sets the system to remote state. The front panel control is locked. By pushing the REMOTE button the front panel control will be activated. If the instrument receives a remote command it will be switched into remote control automatically (REMOTE button LED lights up).

(3) Remote Lock: Sets the system to remote state. The front panel control is locked and can not be unlocked via REMOTE button). You are only able to unlock the front panel control via function hmp4000_RemoteMode - Local.

(4) Remote Mix: Sets the system to remote state. The front panel and remote control are possible simultaneously (mixed mode).
   �0#����  �    Status                           ��-   �  �    Instrument Handle                �� G � � `    Remote Mode                        	                          xLocal HMP4000_VAL_LOCAL Remote HMP4000_VAL_REMOTE Remote Lock HMP4000_VAL_REMOTE_LOCK Remote Mix HMP4000_VAL_REMOTE_MIX    P    This function clears status.

Attribute(s):
-

Remote-control command(s):
*CLS    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   �#����  �    Status                           ��-   �  �    Instrument Handle                  	               h    This function returns the ID Query response string.

Attribute(s):
-

Remote-control command(s):
*IDN?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     Z    Returns the ID Query response string. The array should consist of at least 256 elements.   #����  �    Status                           �K-   �  �    Instrument Handle                � G � �  `    ID Query Response                  	               	            �    Stops further command processing until all commands sent before *WAI have been executed.

Attribute(s):
-

Remote-control command(s):
*WAI    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   ƴ#����  �    Status                           �|-   �  �    Instrument Handle                  	               S    This function queries the OPC.

Attribute(s):
-

Remote-control command(s):
*OPC?    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         Queries the OPC.   �	#����  �    Status                           ��-   �  �    Instrument Handle                ̉ G � �  `    OPC                                	               	            W    This function switches ON/OFF various error checkings performed inside of the driver.    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
         This control is not used.     �    This control enables or disables range checking.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_TRUE

Attribute:
RS_ATTR_RANGE_CHECK    �    This control enables or disables instrument state checking (reading of the status byte and checking it for error). All driver functions are using state checking. Switch this function to ON when debugging your application. For better bus throughput and instrument performance switch it OFF.


Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_TRUE

Attribute:
RS_ATTR_QUERY_INSTRUMENT_STATUS   ͽ����  �    Status                           υ   �  �    Instrument Handle                �= G I �       Option Checking                  �` G � �       Range Checking                   � G� �       Status Checking                    	              On VI_TRUE Off VI_FALSE   On VI_TRUE Off VI_FALSE   On VI_TRUE Off VI_FALSE    �    This function specifies the minimum timeout value to use (in milliseconds) when accessing the device associated with the given session.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     Z    This control sets the timeout value.

Valid Values: not checked

Default Value: 15000 ms   Ԧ#����  �    Status                           �n-   �  �    Instrument Handle                �& Q � �  `    VISA Timeout                       	               15000    �    This function returns the minimum timeout value to use (in milliseconds) when accessing the device associated with the given session.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     &    This control gets the timeout value.   ��#����  �    Status                           ژ-   �  �    Instrument Handle                �P Q � �  `    VISA Timeout                       	               	            �    If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
Use the function hmp4000_GetError afterwards to get the detailed information about the instrument error(s).    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.The handle identifies a particular instrument session.

Default Value:  None
    I    If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
Use the function hmp4000_GetError afterwards to get the detailed information about the instrument error(s).

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)   �9#����  `    Status                           �-   �  `    Instrument Handle                ߷ G �  `    Auto Syst Err Query                	               On 1 Off 0    �    Session-related mutex switch.
If TRUE (default after init is FALSE), the driver sets a mutual-exclusion mechanism for every driver's hi-level function and attribute access.
Set this value to TRUE if you plan to use one session in more than one thread.    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.The handle identifies a particular instrument session.

Default Value:  None
    N    Session-related mutex switch.
If TRUE (default after init is FALSE), the driver sets a mutual-exclusion mechanism for every driver's hi-level function and attribute access.
Set this value to TRUE if you plan to use one session in more than one thread.

Valid Values:
VI_FALSE (0) - Off
VI_TRUE  (1) - On

Default Value: VI_FALSE (0)   ��#����  `    Status                           �-   �  `    Instrument Handle                �H G �  `    Multi Thread Locking               	               On 1 Off 0   a    Retrieves detailed description of the last error that occurred in the entered driver session. The latest error overwrites the description. If you enter NULL as the instrumentHandle parameter, the driver returns the last error that occured in the current execution thread.
The function also clears the error - calls the hmp4000_ClearError() at the end.    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
    a    Retrieves detailed description of the last error that occurred in the entered driver session. The latest error overwrites the description. If you enter NULL as the instrumentHandle parameter, the driver returns the last error that occured in the current execution thread.
The function also clears the error - calls the hmp4000_ClearError() at the end.     �    Pass the number of bytes in the ViChar array you specify for the Description parameter. If the error description is longer, it is truncated and properly 0-terminated.     �    Returns the error description for the session or execution thread. If there is no description, the function returns an empty string.   ��#����  `    Status                           �-   �  `    Instrument Handle                �D 9  �  �    Code                             � 9� �  �    BufferSize                       �] � Q � �    Description                        	               	               	            �    Clears the information about the last error that occured for the entered session. If you enter NULL as the instrumentHandle, the function clears the error for the current execution thread.    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   ��#����  `    Status                           �-   �  `    Instrument Handle                  	               �    This function writes a user-specified string to the instrument.

Note:

This function bypasses attribute state caching. Therefore, when you call this function, the cached values for all attributes will be invalidated.
    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     2    Pass the string to be written to the instrument.   ��#����  `    Status                           ��-   �  `    Instrument Handle                �D 9 � �  �    Write Buffer                       	                   .    This function queries the ViBoolean value.

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViBoolean value
   �g#����  `    Status                           �/-   �  `    Instrument Handle                �� I  �      Command                          �, �q �  �    Value                              	               ""    	            ,    This function queries the ViInt32 value.

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViInt32 value
   �|#����  `    Status                           �D-   �  `    Instrument Handle                �� I  �      Command                          �A �q �  �    Value                              	               ""    	            -    This function queries the ViReal64 value.

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""         Returns the ViReal64 value
   ��#����  `    Status                           X-   �  `    Instrument Handle                 I  �      Command                          U �q �  �    Value                              	               ""    	           -    This function queries the ViString value.

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
     =    The query to be sent to the instrument.

Default Value:  ""    �    Pass the number of bytes in the ViChar array you specify for the  Value parameter.  

If the current value of the attribute, including the terminating NUL byte, contains more bytes that you indicate in this parameter, the function copies Buffer Size - 1 bytes into the buffer, places an ASCII NUL byte at the end of the buffer, and returns the buffer size you must pass to get the entire value.  For example, if the value is "123456" and the Buffer Size is 4, the function places "123" into the buffer and returns 7.

If you pass a negative number, the function copies the value to the buffer regardless of the number of bytes in the value.

If you pass 0, you can pass VI_NULL for the Value buffer parameter.

Default Value: 512         Returns the ViBoolean value
   �#����  `    Status                           m-   �  `    Instrument Handle                % I  �      Command                          j �  �  �    Buffer Size                      	M �q �  �    Value                              	               ""    512    	           �    This function performs the following operations:

- Closes the instrument I/O session.

- Destroys the instrument driver session and all of its attributes.

- Deallocates any memory resources the driver uses.

Notes:

(1) You must unlock the session before calling hmp4000_close.

(2) After calling hmp4000_close, you cannot use the instrument driver again until you call hmp4000_init or hmp4000_InitWithOptions.

    �    Returns the status code. Zero signals no error. Negative values mean an error has occurred, positive values signal warnings. Call the hmp4000_GetError() to get detailed description about the last error that occurred.
You can also convert the status code to a general error message with hmp4000_error_message(). We recommend using hmp4000_GetError(), since the returned description describes the specific circumstances of the last error occurence.     �    The ViSession handle that you obtain from the hmp4000_init or hmp4000_InitWithOptions function.  The handle identifies a particular instrument session.

Default Value:  None
   M#����  `    Status                           -   �  `    Instrument Handle                  	            ����         	a  �             K.        init                                                                                                                                    ����           5�             K.        InitWithOptions                                                                                                                         ����         7�  <�             K.        ConfigureChannel                                                                                                                        ����         =�  B�             K.        GetChannel                                                                                                                              ����         CB  G�             K.        ConfigureCombinedVoltageAndCurrent                                                                                                      ����         H�  MX             K.        ConfigureOutputState                                                                                                                    ����         N"  Q�             K.        ConfigureGeneralOutputState                                                                                                             ����         R�  V�             K.        ConfigureOutputStateChannelOnly                                                                                                         ����         W�  \�             K.        ConfigureSettingsLocation                                                                                                               ����         ^L  bG             K.        QueryCombinedVoltageAndCurrent                                                                                                          ����         cJ  ki             K.        ConfigureArbitraryGeneratorWaveformData                                                                                                 ����         m  r             K.        ConfigureArbitraryGeneratorStartChannel                                                                                                 ����         sK  xY             K.        ConfigureArbitraryGeneratorStopChannel                                                                                                  ����         y�  ~�             K.        ConfigureArbitraryGeneratorDataTransferChannel                                                                                          ����         �  �j             K.        ConfigureArbitraryGeneratorDataStorage                                                                                                  ����         �#  �y             K.        ConfigureCurrentValue                                                                                                                   ����         �6  ��             G.        ConfigureElectronicFuse                                                                                                                 ����         �  �\             K.        ConfigureCurrentStepValue                                                                                                               ����         �  �0             K.        QueryElectronicFuseStatus                                                                                                               ����         ��  �N             K.        ConfigureVoltageValue                                                                                                                   ����         �  �b             K.        ConfigureOverVoltageProtection                                                                                                          ����         �   �^             K.        ConfigureVoltageStepValue                                                                                                               ����         �  �]             K.        QueryOverVoltageProtectionStatus                                                                                                        ����         �  ��             K.        ClearOverVoltageProtection                                                                                                              ����         �9  ��             K.        ConfigureOverVoltageProtectionMode                                                                                                      ����         ��  �}             K.        ConfigureBeeper                                                                                                                         ����         ŧ  ɘ             K.        ReadVoltageOutput                                                                                                                       ����         �Z  �I             K.        ReadCurrentOutput                                                                                                                       ����         �  ߀             K.        SetAttributeViInt32                                                                                                                     ����         �  �             K.        SetAttributeViReal64                                                                                                                    ����         �2 �             K.        SetAttributeViString                                                                                                                    ����        H �             K.        SetAttributeViBoolean                                                                                                                   ����        a  �             K.        GetAttributeRepCapName                                                                                                                  ����        3 8c             K.        GetAttributeRepeatedCapabilityIds                                                                                                       ����        9� ?F             K.        GetAttributeRepeatedCapabilityIdNames                                                                                                   ����        @� M%             K.        GetAttributeViInt32                                                                                                                     ����        Nb Z�             K.        GetAttributeViReal64                                                                                                                    ����        \ qN             K.        GetAttributeViString                                                                                                                    ����        r� 4             K.        GetAttributeViBoolean                                                                                                                   ����        �q �Q             K.        reset                                                                                                                                   ����        �� �u             K.        self_test                                                                                                                               ����        �q ��             K.        revision_query                                                                                                                          ����        �� ��             K.        SystemVersion                                                                                                                           ����        �� ��             K.        error_query                                                                                                                             ����        �� �9             K.        error_message                                                                                                                           ����        �5 �             K.        SetRegister                                                                                                                             ����        �� �!             K.        GetRegister                                                                                                                             ����        �* ��             K.        RemoteMode                                                                                                                              ����        �� ��             K.        ClearStatus                                                                                                                             ����        � �e             K.        IDQueryResponse                                                                                                                         ����        �  �4             K.        ProcessAllPreviousCommands                                                                                                              ����        ɮ ̣             K.        QueryOPC                                                                                                                                ����        �^ Ҫ             K.        ConfigureErrorChecking                                                                                                                  ����        � ׈             K.        SetVISATimeout                                                                                                                          ����        �@ �~             K.        GetVISATimeout                                                                                                                          ����        �9 �             K.        ConfigureAutoSystemErrQuery                                                                                                             ����        �� �             K.        ConfigureMultiThreadLocking                                                                                                             ����        �[ ��             K.        GetError                                                                                                                                ����        �  �f             K.        ClearError                                                                                                                              ����        �� �~             K.        WriteInstrData                                                                                                                          ����        �1 �R             K.        QueryViBoolean                                                                                                                          ����        �H �e             K.        QueryViInt32                                                                                                                            ����        �[ z             K.        QueryViReal64                                                                                                                           ����        p 	s             K.        QueryViString                                                                                                                           ����        
� �             K.        close                                                                                                                                         �                                                                                     �Initialize                                                                           �Initialize With Options                                                             QConfiguration                                                                        �Configure Channel                                                                    �Get Channel                                                                          �Configure Combined Voltage And Current                                               �Configure Output State                                                               �Configure General Output State                                                       �Configure Output State Channel Only                                                  �Configure Settings Location                                                          �Query Combined Voltage And Current                                                  �Arbitrary Generator                                                                  �Configure Arbitrary Generator Waveform Data                                          �Configure Arbitrary Generator Start Channel                                          �Configure Arbitrary Generator Stop Channel                                           �Configure Arbitrary Generator Data Transfer Channel                                  �Configure Arbitrary Generator Data Storage                                          Current Configuration                                                                �Configure Current Value                                                              �Configure Electronic Fuse                                                            �Configure Current Step Value                                                         �Query Electronic Fuse Status                                                        kVoltage Configuration                                                                �Configure Voltage Value                                                              �Configure Over Voltage Protection                                                    �Configure Voltage Step Value                                                         �Query Over Voltage Protection Status                                                 �Clear Over Voltage Protection                                                        �Configure Over Voltage Protection Mode                                              �General Instrument Settings                                                          �Configure Beeper                                                                    �Measurement                                                                          �Read Voltage Output                                                                  �Read Current Output                                                                 �Utility Functions                                                                   �Set/Get/Check Attribute                                                             DSet Attribute                                                                        �Set Attribute ViInt32                                                                �Set Attribute ViReal64                                                               �Set Attribute ViString                                                               �Set Attribute ViBoolean                                                             �Repeated Capability                                                                  �Get Attribute RepCap Name                                                            �Get Attribute Repeated Capability Id(s)                                              �Get Attribute Repeated Capability Id Name(s)                                        +Get Attribute                                                                        �Get Attribute ViInt32                                                                �Get Attribute ViReal64                                                               �Get Attribute ViString                                                               �Get Attribute ViBoolean                                                              �Reset                                                                                �Self-Test                                                                            �Revision Query                                                                       �System Version                                                                       �Error-Query                                                                          �Error Message                                                                        �Set Register                                                                         �Get Register                                                                         �Remote Mode                                                                          �Clear Status                                                                         �ID Query Response                                                                    �Process All Previous Commands                                                        �Query OPC                                                                            �Configure Error Checking                                                             �Set VISA Timeout                                                                     �Get VISA Timeout                                                                     �Configure Auto System Err Query                                                      �Configure Multi Thread Locking                                                      �Error Info                                                                           �Get Error                                                                            �Clear Error                                                                         	Instrument I/O                                                                       �Write Instrument Data                                                                �Query ViBoolean                                                                      �Query ViInt32                                                                        �Query ViReal64                                                                       �Query ViString                                                                       �Close                                                                           
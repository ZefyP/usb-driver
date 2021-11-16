//==============================================================================
//
// Title:      hmp4000_simple_example
// Purpose:    Demonstration example on how to use hmp4000 instrument driver
//             to control channel 1 and channel 2 output voltage and current
//             and example of the application error handling
// Notes:      To run the example you need to install hmp4000 VXI Plug&Play
//             instrument driver version 2.1.0 or later.
//
//             Default locations of instrument driver files on 32bit Windows:
//             C:\Program Files (x86)\IVI Foundation\VISA\WinNT\hmp4000\hmp4000.fp
//             C:\Program Files (x86)\IVI Foundation\VISA\WinNT\include\hmp4000.h
//             C:\Program Files (x86)\IVI Foundation\VISA\WinNT\lib\msc\hmp4000.lib
//             
//             Default locations of instrument driver files on 64bit Windows:
//             C:\Program Files\IVI Foundation\VISA\Win64\hmp4000\hmp4000.fp
//             C:\Program Files\IVI Foundation\VISA\Win64\include\hmp4000.h
//             C:\Program Files\IVI Foundation\VISA\Win64\Lib_x64\msc\hmp400064.lib
//
//             In CVI add the hmp4000.lib or hmp400064 to the project
//			   In Visual Studio C++ add the hmp4000.lib or hmp400064 to the project Additional Dependencies:
//             Project Properties -> Linker -> Input -> Additional Dependencies
//
// Created on: 2016-06-09 by Miloslav Macko
// Copyright:  Rohde & Schwarz GmbH & Co. KG. All Rights Reserved.
//

#include "hmp4000.h"

static ViString  sResourceName = "TCPIP::127.0.0.1::5025::SOCKET";
static ViBoolean hIDQuery = VI_TRUE;
static ViBoolean hResetDevice = VI_TRUE;

ViSession io = 0;
ViStatus  iStatus = 0;
ViChar _VI_FAR sUserMessage[4096], sGetErrorMessage[4096], sInstrErrorMessage[4096];
ViChar _VI_FAR sIdnQuery[4096];
ViInt32 iErrorLine, iErrorCode = 0, iInstrErrorCode = 0;

//definition of the error handling macro
#define CHECKERR(call)\
	iStatus = call; if (iStatus < VI_SUCCESS)\
	{\
		iErrorLine = __LINE__;\
		goto ERROR;\
	}

int main(int argc, char *argv[])
{
	printf("Initializing instrument '%s' ... ", sResourceName);
	CHECKERR(hmp4000_init(sResourceName, hIDQuery, hResetDevice, &io));
	printf("success.\n\n");

	//RemoteMode Mix doesn't block the manual operation
	printf("Reading instrument *IDN? string ... ");
	CHECKERR(hmp4000_IDQueryResponse(io, sIdnQuery));
	printf("success.\n\n");
	printf("Connected instrument: %s\n\n", sIdnQuery);
	
	printf("Setting mixed remote-control mode ... ");
	CHECKERR(hmp4000_RemoteMode(io, HMP4000_VAL_REMOTE_MIX));
	printf("success.\n\n");

	printf("Configuring Channel 1 ... ");
	CHECKERR(hmp4000_ConfigureChannel(io, HMP4000_VAL_OUTPUT_1));
	CHECKERR(hmp4000_ConfigureVoltageValue(io, 3.0)); //3 Volts
	CHECKERR(hmp4000_ConfigureCurrentValue(io, 0.2)); //0.2 Amps
	CHECKERR(hmp4000_ConfigureOutputStateChannelOnly(io, VI_TRUE)); //only the channel 1 state changes, not the general output state
	printf("success.\n\n");

	printf("Configuring Channel 2 ... ");
	CHECKERR(hmp4000_ConfigureChannel(io, HMP4000_VAL_OUTPUT_2));
	CHECKERR(hmp4000_ConfigureVoltageValue(io, 5.0)); //5 Volts
	CHECKERR(hmp4000_ConfigureCurrentValue(io, 0.1)); //0.1 Amps
	CHECKERR(hmp4000_ConfigureOutputStateChannelOnly(io, VI_TRUE)); //only the channel 2 state changes, not the general output state
	printf("success.\n\n");

	//now change the general output state - all channels will be switched on synchronously
	printf("Switching master output ON");
	CHECKERR(hmp4000_ConfigureGeneralOutputState(io, VI_TRUE));
	printf("success.\n\n");

ERROR: //error label

	printf("\nChecking Error");
	hmp4000_GetError(io, &iErrorCode, 4096, sGetErrorMessage);

	if (iErrorCode < VI_SUCCESS)
	{
		if (iStatus == RS_ERROR_INSTRUMENT_STATUS) //instrument reports an error, read the instrument error queue
		{
			iStatus = hmp4000_error_query(io, &iInstrErrorCode, sInstrErrorMessage);
			sprintf(sUserMessage, "Line %d - Instrument error occured: %d, %s\nInstrument error queue: %d, %s",
				iErrorLine,
				iErrorCode, sGetErrorMessage,
				iInstrErrorCode, sInstrErrorMessage);

			printf(sUserMessage);
		}
		else
		{
			sprintf(sUserMessage, "Line %d - Driver error occured: %d, %s",
				iErrorLine,
				iErrorCode, sGetErrorMessage);
			
			printf(sUserMessage);
		}
	}
	else
	{
		printf("No error detected");
	}

	hmp4000_close(io);
	printf("\nPress ENTER to continue...");
	(void)getchar();

	return 0;

}


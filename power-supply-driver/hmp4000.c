/*****************************************************************************
 *  HAMEG Power Supply driver
 *  VXIpnp Instrument Driver
 *  Original Release: February 2010
 *  By: Marian Mindek
 *
 *  Should you have any technical questions please contact the hotline of
 *  HAMEG Support Center
 *
 *  e-mail: support@hameg.com
 *
 *  Modification History:
 *     see ChangeLog
 *****************************************************************************/
#include "hmp4000.h"

#include <stdio.h>

#include "visatype.h"
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define ANSI
#endif
#ifndef ANSI                /* UNIX compatible */
#include <sys/timeb.h>
#include <sys/types.h>
#include <unistd.h>
#define Sleep sleep
#else                       /* ANSI compatible */
#include <Windows.h>
#endif
#if defined (_CVI_)
#include <utility.h>
#endif

/*****************************************************************************
 *- Value Definition and Range Tables ---------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- User-Callable Functions (Exportable Functions) --------------------------*
 *****************************************************************************/

 /// HIFN VXIplug&play required function. Calls the hmp4000_InitWithOptions function.
 /// HIRET Returns the status code of this operation.
 /// HIPAR resourceName/Pass the resource name of the device to initialize
 /// HIPAR IDQuery/Specify whether you want the instrument driver to perform an ID Query.
 /// HIPAR resetDevice/Specify whether you want the to reset the instrument during the initialization procedure.
 /// HIPAR newInstrSession/Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.
ViStatus hmp4000_init(ViRsrc resourceName, ViBoolean IDQuery,
    ViBoolean resetDevice, ViSession* newInstrSession)
{
    ViStatus error = VI_SUCCESS;

    if (newInstrSession == NULL)
    {
        (void)RsCore_SetErrorInfo(0, VI_FALSE, RS_ERROR_INVALID_PARAMETER,
            VI_ERROR_PARAMETER4, "Null address for Instrument Handle");

        checkErr(RS_ERROR_INVALID_PARAMETER);
    }

    checkErr(hmp4000_InitWithOptions(resourceName, IDQuery, resetDevice, "", newInstrSession));

Error:
    return error;
}

/// HIFN This function creates a new RS session and calls the RsInit function.
/// HIRET Returns the status code of this operation.
/// HIPAR resourceName/Pass the resource name of the device to initialize
/// HIPAR IDQuery/Specify whether you want the instrument driver to perform an ID Query.
/// HIPAR resetDevice/Specify whether you want the to reset the instrument during the initialization procedure.
/// HIPAR newInstrSession/Returns a ViSession handle that you use to identify the instrument in all subsequent instrument driver function calls.
ViStatus hmp4000_InitWithOptions(
    ViRsrc resourceName,
    ViBoolean IDQuery,
    ViBoolean resetDevice,
    ViString optionString,
    ViSession* newInstrSession
)
{
    ViStatus error = VI_SUCCESS;
    RsCoreAttributePtr* attrList = NULL;
    ViSession instrSession = *newInstrSession;
    RsCoreSessionPtr sessionProperties = NULL;
    ViChar completeOptionString[RS_MAX_MESSAGE_BUF_SIZE];

    if (newInstrSession == NULL)
    {
        (void)RsCore_SetErrorInfo(0, VI_FALSE, RS_ERROR_INVALID_PARAMETER, VI_ERROR_PARAMETER5, "Null address for Instrument Handle");
        checkErr(RS_ERROR_INVALID_PARAMETER);
    }

    attrList = (RsCoreAttributePtr*)hmp4000_RsCoreAttributeList;

    // USB session to non-vxi capable
    (void)RsCore_CopyToUserBufferAsciiData(completeOptionString, RS_MAX_MESSAGE_BUF_SIZE, optionString);
    (void)RsCore_AppendToCsvString(completeOptionString, ",", RS_MAX_MESSAGE_BUF_SIZE, "AdditionalFlags=1");

    checkErr(RsCore_NewSpecificDriver(
        resourceName, // VISA Resource Name
        "hmp4000", // driver prefix
        completeOptionString, // Init Options string, is applied to the session settings
        attrList, // List of all attributes from the rsxxx_AttrPropertiesList
        hmp4000_RsCoreAttributeListLength, // Attributes count
        VI_FALSE, //idnModelFullName Model has the full *IDN? query name e.g. true: "SMW200A", VI_FALSE: "SMW" Used in CheckInstrument()
        40, // WriteDelay
        40, // ReadDelay
        1000, // IO Segment Size
        RS_VAL_OPCWAIT_STBPOLLINGSLOW, // OPC Wait Mode
        HMP4000_OPC_TIMEOUT, // OPC timeout
        5000, // VISA Timeout
        600000, // Self-test timeout
        RS_VAL_BIN_FLOAT_FORMAT_SINGLE_4BYTES, // BinaryFloatNumbersFormat
        RS_VAL_BIN_INTEGER_FORMAT_INT32_4BYTES, // binaryIntegerNumbersFormat
        &instrSession));

    // Minimal allowed rscore version is 4.0.0
    checkErr(RsCore_CheckMinimalEngineVersion(instrSession, 4, 0, 0));

    checkErr(RsCore_GetRsSession(instrSession, &sessionProperties));

	// For USB and ASRL, block the viClear()
    if (sessionProperties->sessionType == RS_INTF_USB || sessionProperties->sessionType == RS_INTF_ASRL)
    {
        sessionProperties->allowViClear = VI_FALSE;
    }

    // No SCPI command has been sent yet.
    // Call viClear before sending any SCPI command
    checkErr(RsCore_ViClear(instrSession));

    /* --- Here perform settings that are default for this driver,
    but can be overwritten by the optionsString settings */

    sessionProperties->addTermCharToWriteBinBlock = VI_TRUE;
    sessionProperties->autoSystErrQuery = VI_FALSE;
    sessionProperties->assureWriteWithLF = VI_TRUE;
    sessionProperties->assureResponseEndWithLF = VI_TRUE;
    sessionProperties->optionChecking = VI_FALSE;
    sessionProperties->addTermCharToWriteBinBlock = VI_TRUE;

	// Session-specific read/write delays
	if (sessionProperties->sessionType == RS_INTF_ASRL)
	{
        sessionProperties->writeDelay = 35;
        sessionProperties->readDelay = 35;
	}
	else if (sessionProperties->sessionType == RS_INTF_SOCKET)
	{
	    sessionProperties->writeDelay = 20;
	    sessionProperties->readDelay = 20;
	}
	else if (sessionProperties->sessionType == RS_INTF_USB)
	{
	    sessionProperties->writeDelay = 10;
	    sessionProperties->readDelay = 30;
	}
	else if (sessionProperties->sessionType == RS_INTF_GPIB)
	{
	    sessionProperties->writeDelay = 30;
	    sessionProperties->readDelay = 30;
	}

    // Parse option string and optionally sets the initial state of the following session attributes
    checkErr(RsCore_ApplyOptionString(instrSession, optionString));
    checkErr(RsCore_BuildRepCapTable(instrSession, hmp4000_RsCoreRepCapTable, hmp4000_RsCoreRepCapTableCount));

    // Query *IDN? string, parse it and set the following attributes:
    // -RS_ATTR_INSTRUMENT_MANUFACTURER
    // - RS_ATTR_INSTRUMENT_MODEL - based on the sessionProperties->idnModelFullName true: "HMC8012", false : "HMC"
    // - RS_ATTR_INSTRUMENT_FIRMWARE_REVISION
    checkErr(RsCore_QueryAndParseIDNstring(instrSession, HMP4000_SIMULATION_ID_QUERY, NULL));

    // Default Instrument Setup + optional *RST
    if (resetDevice == VI_TRUE)
    {
        checkErr(hmp4000_reset(instrSession));
    }
    else
    {
        checkErr(hmp4000_DefaultInstrSetup(instrSession));
    }

    if (IDQuery == VI_TRUE)
    {
        checkErr(RsCore_FitsIDNpattern(instrSession, HMP4000_VALID_ID_RESPONSE_STRING1, HMP4000_VALID_ID_RESPONSE_STRING2));
    }

    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_AfterErrorInInit(instrSession, sessionProperties, error, newInstrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureChannel
 * Purpose:  This function selects the channels.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_SELECTION_OF_CHANNEL
 *
 *           Remote-control command(s):
 *           INSTrument:SELect OUTPut1 | OUTPut2 | OUTPut3 | OUTPut4
 *****************************************************************************/
ViStatus hmp4000_ConfigureChannel(ViSession instrSession,
                                  ViInt32   channel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_SELECTION_OF_CHANNEL, channel),
            2, "Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the currently selected channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR channel/This control returns the selected channel.
ViStatus hmp4000_GetChannel(ViSession instrSession,
                            ViInt32   *channel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViInt32(instrSession, "", HMP4000_ATTR_SELECTION_OF_CHANNEL, channel),
            2, "Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureCombinedVoltageAndCurrent
 * Purpose:  This function configures voltage and current.
 *
 *           Attribute(s):
 *           -
 *
 *           Remote-control command(s):
 *           APPLy
 *
 *****************************************************************************/
ViStatus hmp4000_ConfigureCombinedVoltageAndCurrent(ViSession instrSession,
                                                    ViReal64  voltage,
                                                    ViReal64  current)
{
    ViStatus error = VI_SUCCESS;
    ViChar   cmd[RS_MAX_MESSAGE_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    snprintf(cmd, RS_MAX_MESSAGE_BUF_SIZE, "APPL %.12lG,%.12lG", voltage, current);
    checkErr(RsCore_Write(instrSession, cmd));
    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureOutputState
 * Purpose:  Turns the channel output ON or OFF. When switching the channel ON,
 *           General output switch is also switched ON. When switching the channel OFF,
 *           General output switch is not changed. If changing the General output
 *           switch status is not desired, use the hmp4000_ConfigureOutputStateChannelOnly
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OUTPUT_STATE
 *
 *           Remote-control command(s):
 *           OUTPut:STATe ON | OFF
 *****************************************************************************/
ViStatus hmp4000_ConfigureOutputState(ViSession instrSession,
                                      ViBoolean outputState)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViBoolean(instrSession, "", HMP4000_ATTR_OUTPUT_STATE, outputState),
            2, "Output State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Turning on / off all previous selected channels simultaneously.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR outputState/Turning on / off all previous selected channels simultaneously.
ViStatus hmp4000_ConfigureGeneralOutputState(ViSession instrSession,
                                             ViBoolean outputState)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViBoolean(instrSession, "", HMP4000_ATTR_GENERAL_OUTPUT_STATE, outputState),
            2, "Output State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Turns the channel output ON or OFF. Compared to
/// HIFN  hmp4000_ConfigureOutputState, it doesn't change the General
/// HIFN  output switch settings.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR outputState/Turns the channel output ON or OFF.
ViStatus hmp4000_ConfigureOutputStateChannelOnly(ViSession instrSession,
                                                 ViBoolean outputState)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViBoolean(instrSession, "", HMP4000_ATTR_OUTPUT_SELECT, outputState),
            2, "Output State");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureSettingsLocation
 * Purpose:  This function stores or recalls the settings from selected
 *           locations of a nonvolatile memory.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_SETTINGS_STORE_LOCATION
 *           HMP4000_ATTR_SETTINGS_RECALL_LOCATION
 *
 *           Remote-control command(s):
 *           *SAV {0|1|2|3|4|5|6|7|8|9}
 *           *RCL {0|1|2|3|4|5|6|7|8|9}
 *****************************************************************************/
ViStatus hmp4000_ConfigureSettingsLocation(ViSession instrSession,
                                           ViInt32   memoryOperation,
                                           ViInt32   location)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    switch(memoryOperation){
        case HMP4000_VAL_MEM_OPERATION_STORE:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_SETTINGS_STORE_LOCATION, location),
                3, "Location");
            break;
        case HMP4000_VAL_MEM_OPERATION_RECALL:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_SETTINGS_RECALL_LOCATION, location),
                3, "Location");
            break;
        default:
            error = RS_ERROR_VALUE_NOT_AVAILABLE;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_QueryCombinedVoltageAndCurrent
 * Purpose:  This function queries combined setting of voltage and current.
 *
 *           Attribute(s):
 *           -
 *
 *           Remote-control command(s):
 *           APPLy?
 *****************************************************************************/
ViStatus hmp4000_QueryCombinedVoltageAndCurrent(ViSession instrSession,
                                                ViReal64* voltageValue,
                                                ViReal64* current)
{
    ViStatus error = VI_SUCCESS;
    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_QueryTupleViReal64(instrSession, "APPLY?", voltageValue, current, NULL, NULL));
    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureArbitraryGeneratorWaveformData
 * Purpose:  This function sets the parameters of the freely programmable
 *           waveforms. Set points defining voltage, current and dwell
 *           time are required.
 *
 *           A maximum of 128 set points (index 0 ... 128) may be used and
 *           will be repetitively addressed.
 *
 *           The maximum number of repetitions is 255. If Repetitons 0 is
 *           selected, the waveform will be repeated indefinitely.
 *
 *           Attribute(s):
 *           -
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION
 *
 *           Remote-control command(s):
 *           ARBitrary:DATA <voltage1, current1, time1, voltage2, ...>
 *           ARBitrary:REPetitions
 *****************************************************************************/
ViStatus hmp4000_ConfigureArbitraryGeneratorWaveformData(ViSession instrSession,
                                                         ViInt32   arraySize,
                                                         ViReal64  voltage[],
                                                         ViReal64  current[],
                                                         ViReal64  time[],
                                                         ViInt32   repetition)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_WriteAsciiViReal64ArraysInterleaved(instrSession, "ARBitrary:DATA ", arraySize, voltage, current, time, NULL, NULL, NULL));
    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION, repetition),
            6, "Repetition");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureArbitraryGeneratorStartChannel
 * Purpose:  This function selects the channel for starting arbitrary
 *           generator.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL
 *
 *           Remote-control command(s):
 *           ARBitrary:STARt
 *****************************************************************************/
ViStatus hmp4000_ConfigureArbitraryGeneratorStartChannel(ViSession instrSession,
                                                         ViInt32   channel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL, channel),
            2, "Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureArbitraryGeneratorStopChannel
 * Purpose:  This function selects the channel where stop the arbitrary
 *           generator.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL
 *
 *           Remote-control command(s):
 *           ARBitrary:STOP
 *****************************************************************************/
ViStatus hmp4000_ConfigureArbitraryGeneratorStopChannel(ViSession instrSession,
                                                        ViInt32   channel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL, channel),
            2, "Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureArbitraryGeneratorDataTransferChannel
 * Purpose:  This function selects the channel where the data entered are sent
 *           to.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL
 *
 *           Remote-control command(s):
 *           ARBitrary:TRANsfer
 *****************************************************************************/
ViStatus hmp4000_ConfigureArbitraryGeneratorDataTransferChannel(
                            ViSession instrSession,
                            ViInt32   channel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL, channel),
            2, "Channel");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureArbitraryGeneratorDataStorage
 * Purpose:  This function selects the storage for saving, recalling or
 *           clearing arbitrary generator waveform data.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL
 *           HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR
 *
 *           Remote-control command(s):
 *           ARBitrary:SAVE
 *           ARBitrary:RESTore
 *           ARBitrary:CLEar
 *
 *****************************************************************************/
ViStatus hmp4000_ConfigureArbitraryGeneratorDataStorage(ViSession instrSession,
                                                        ViInt32   memoryOperation,
                                                        ViInt32   memoryIndex)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    switch(memoryOperation){
        case HMP4000_VAL_MEM_OPERATION_STORE:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE, memoryIndex),
                3, "Memory Index");
            break;
        case HMP4000_VAL_MEM_OPERATION_RECALL:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL, memoryIndex),
                3, "Memory Index");
            break;
        case HMP4000_VAL_MEM_OPERATION_CLEAR:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR, memoryIndex),
                3, "Memory Index");
            break;
        default:
            error = RS_ERROR_VALUE_NOT_AVAILABLE;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureCurrentValue
 * Purpose:  This function adjusts the output current.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OUTPUT_CURRENT_LEVEL
 *
 *           Remote-control command(s):
 *           SOURce:CURRent:LEVel:AMPLitude
 *
 *****************************************************************************/
ViStatus hmp4000_ConfigureCurrentValue(ViSession instrSession,
                                       ViReal64  current)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViReal64(instrSession, "", HMP4000_ATTR_OUTPUT_CURRENT_LEVEL, current),
            2, "Current");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureElectronicFuse
 * Purpose:  This function switches On or Off the electronic fuse and link or
 *           unlink from the channel.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_ELECTRONIC_FUSE_STATE
 *           HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK
 *           HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK
 *
 *           Remote-control command(s):
 *           FUSE:STATe ON | OFF
 *           FUSE:LINK
 *           FUSE:UNLink
 *****************************************************************************/
ViStatus hmp4000_ConfigureElectronicFuse(ViSession instrSession,
                                         ViBoolean fuse,
                                         ViInt32   linktoChannel,
                                         ViInt32   unlinkfromChannel)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViBoolean(instrSession, "", HMP4000_ATTR_ELECTRONIC_FUSE_STATE, fuse),
            2, "Fuse State");

    if(linktoChannel != HMP4000_VAL_CH_N)
    {
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK, linktoChannel),
                3, "Channel Link");
    }

    if(unlinkfromChannel != HMP4000_VAL_CH_N)
    {
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK, unlinkfromChannel),
                4, "Channel Unlink");
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureCurrentStepValue
 * Purpose:  This function configures the output current step value.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP
 *
 *           Remote-control command(s):
 *           SOURce:CURRent:LEVel:AMPLitude:STEP:INCRement
 *****************************************************************************/
ViStatus hmp4000_ConfigureCurrentStepValue(ViSession instrSession,
                                           ViReal64  currentStep)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViReal64(instrSession, "", HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP, currentStep),
            2, "Current Step");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_QueryElectronicFuseStatus
 * Purpose:  This function queries the electronic fuse status.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS
 *
 *           Remote-control command(s):
 *           FUSE:TRIPped?
 *****************************************************************************/
ViStatus hmp4000_QueryElectronicFuseStatus(ViSession  instrSession,
                                           ViBoolean* fuseStatus)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViBoolean(instrSession, "", HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS, fuseStatus),
            2, "Fuse Status");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureVoltageValue
 * Purpose:  This function adjusts the output voltage level.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL
 *
 *           Remote-control command(s):
 *           SOURce:VOLTage:LEVel:AMPLitude
 *
 *****************************************************************************/
ViStatus hmp4000_ConfigureVoltageValue(ViSession instrSession,
                                       ViReal64  voltage)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViReal64(instrSession, "", HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL, voltage),
            2, "Voltage");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ConfigureOverVoltageProtection
 * Purpose:  This function configures the over voltage protection (OVP).
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL
 *
 *           Remote-control command(s):
 *           VOLTage:PROTection:LEVel
 *
 *****************************************************************************/
ViStatus hmp4000_ConfigureOverVoltageProtection(ViSession instrSession,
                                                ViReal64  ovpValue)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViReal64(instrSession, "", HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL, ovpValue),
            2, "Over Voltage Protection Level");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/*****************************************************************************
 * Function: hmp4000_ConfigureVoltageStepValue
 * Purpose:  This function configures the output voltage step value.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP
 *
 *           Remote-control command(s):
 *           SOURce:VOLTage:LEVel:AMPLitude:STEP:INCRement
 *****************************************************************************/
ViStatus hmp4000_ConfigureVoltageStepValue(ViSession instrSession,
                                           ViReal64  voltageStep)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViReal64(instrSession, "", HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP, voltageStep),
            2, "Voltage Step");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/*****************************************************************************
 * Function: hmp4000_QueryOverVoltageProtectionStatus
 * Purpose:  This function queries the over voltage protection (OVP) status.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS
 *
 *           Remote-control command(s):
 *           VOLTage:PROTection:TRIPped?
 *****************************************************************************/
ViStatus hmp4000_QueryOverVoltageProtectionStatus(ViSession  instrSession,
                                                  ViBoolean* ovpStatus)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViBoolean(instrSession, "", HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS, ovpStatus),
            2, "Over Voltage Protection Status");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/*****************************************************************************
 * Function: hmp4000_ClearOverVoltageProtection
 * Purpose:  This function clears the over voltage protection (OVP).
 *
 *           Attribute(s):
 *           HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR
 *
 *           Remote-control command(s):
 *           VOLTage:PROTection:CLEar
 *****************************************************************************/
ViStatus hmp4000_ClearOverVoltageProtection(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(hmp4000_SetAttributeViString(instrSession, "", HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR, NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}
/// HIFN  Sets the OVP mode for the previously selected channel.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR mode/Sets the OVP mode for the previously selected channel.
ViStatus hmp4000_ConfigureOverVoltageProtectionMode(ViSession instrSession,
                                                    ViInt32   mode)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE, mode),
            2, "Mode");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}







/*****************************************************************************
 * Function: hmp4000_ConfigureBeeper
 * Purpose:  This function configures the beeper.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_BEEPER_MODE
 *
 *           Remote-control command(s):
 *           SYSTem:BEEPer[:IMMediate]
 *****************************************************************************/
ViStatus hmp4000_ConfigureBeeper(ViSession instrSession,
                                 ViInt32   beeper)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_BEEPER_MODE, beeper),
            2, "Beeper");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ReadVoltageOutput
 * Purpose:  This function queries the measured voltage value.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE
 *
 *           Remote-control command(s):
 *           MEASure[:VOLTage][:DC]?
 *****************************************************************************/
ViStatus hmp4000_ReadVoltageOutput(ViSession instrSession,
                                   ViReal64* voltageValue)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViReal64(instrSession, "", HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE, voltageValue),
            2, "Voltage Value");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_ReadCurrentOutput
 * Purpose:  This function queries the measured Current value.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_MEASUREMENT_DC_CURRENT
 *
 *           Remote-control command(s):
 *           MEASure:CURRent[:DC]?
 *****************************************************************************/
ViStatus hmp4000_ReadCurrentOutput(ViSession instrSession,
                                   ViReal64* currentValue)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViReal64(instrSession, "", HMP4000_ATTR_MEASUREMENT_DC_CURRENT, currentValue),
            2, "Current Value");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_SetAttribute<type> Functions
 * Purpose:  These functions enable the instrument driver user to set
 *           attribute values directly.  There are typesafe versions for
 *           ViInt32, ViReal64, ViString, ViBoolean, and ViSession datatypes.
 *****************************************************************************/

ViStatus hmp4000_SetAttributeViInt32(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViInt32   value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);

    error = RsCore_SetAttributeViInt32(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_SetAttributeViReal64(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViReal64  value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);

    error = RsCore_SetAttributeViReal64(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_SetAttributeViString(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViString  value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);

    error = RsCore_SetAttributeViStringOrRawString(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_SetAttributeViBoolean(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViBoolean value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);

    error = RsCore_SetAttributeViBoolean(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_GetAttribute<type> Functions
 * Purpose:  These functions enable the instrument driver user to get
 *           attribute values directly.  There are typesafe versions for
 *           ViInt32, ViReal64, ViString, ViBoolean, and ViSession attributes.
 *****************************************************************************/

ViStatus hmp4000_GetAttributeViInt32(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViInt32* value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);
    error = RsCore_GetAttributeViInt32(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_GetAttributeViReal64(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViReal64* value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);
    error = RsCore_GetAttributeViReal64(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_GetAttributeViString(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViInt32   bufferSize,
    ViChar    value[])
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);

    error = RsCore_GetAttributeViStringOrRawString(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, bufferSize, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_GetAttributeViBoolean(ViSession instrSession,
    ViString  repeatedCapabilityName,
    ViUInt32  attributeId,
    ViBoolean* value)
{
    ViStatus error = VI_SUCCESS;

    (void)RsCore_LockSession(instrSession);
    error = RsCore_GetAttributeViBoolean(instrSession, repeatedCapabilityName, attributeId, RS_VAL_DIRECT_USER_CALL, value);

    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN Function used by Hi-level functions to obtain a repCap name from:
/// HIFN - attributeID
/// HIFN - repCapNameID
/// HIFN - 0-based index in the repCapNames
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the rscmwgs_init or
/// HIPAR instrSession/rscmwgs_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR attributeId/Pass the ID of an attribute.
/// HIPAR repCapNameId/RepCap Name ID.
/// HIPAR index/Zero based index in the repCapNames.
/// HIPAR bufferSize/Pass the number of bytes in the string you allocate for the repCapName.
/// HIPAR repCapName/String returning RepCap name
ViStatus hmp4000_GetAttributeRepCapName(ViSession instrSession,
                                        ViUInt32  attributeId,
                                        ViString  repCapNameId,
                                        ViInt32   index,
                                        ViInt32   bufferSize,
                                        ViChar    repCapName[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_GetAttributeRepCapName(instrSession, attributeId, repCapNameId, index, bufferSize, repCapName));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_GetAttributeRepeatedCapabilityIds
 * Purpose:  This function returns the repeated capability id(s) that
 *           belongs to the attribute you specify. More then one id is listed
 *           in comma separated string.
 *****************************************************************************/
ViStatus hmp4000_GetAttributeRepeatedCapabilityIds(ViSession instrSession,
    ViUInt32  attributeID,
    ViInt32   bufferSize,
    ViChar    repeatedCapabilityIds[])
{
    ViStatus error = VI_SUCCESS;

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, bufferSize, 1, RS_MAX_SHORT_MESSAGE_BUF_SIZE),
        3, "Buffer Size");

    checkErr(RsCore_GetAttributeRepCapNameIds(instrSession, attributeID, bufferSize, repeatedCapabilityIds));

Error:
    return error;
}

/*****************************************************************************
 * Function: Get Attribute Repeated Capability Id Name(s)
 * Purpose:  This function returns the repeated capability name(s) that
 *           belongs to the attribute and single repeated capability id you
 *           may specify. More then one name is listed in comma separated
 *           string.
 *****************************************************************************/
ViStatus hmp4000_GetAttributeRepeatedCapabilityIdNames(ViSession instrSession,
    ViUInt32  attributeID,
    ViString  repeatedCapabilityId,
    ViInt32   bufferSize,
    ViChar    repeatedCapabilityIdNames[])
{
    ViStatus error = VI_SUCCESS;

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, bufferSize, 1, RS_MAX_SHORT_MESSAGE_BUF_SIZE),
        4, "Buffer Size");

    checkErr(RsCore_GetAttributeRepCapNamesAll(instrSession,
        attributeID,
        repeatedCapabilityId,
        bufferSize,
        repeatedCapabilityIdNames));

Error:
    return error;
}

/*****************************************************************************
 * Function: Reset
 * Purpose:  This function resets the instrument.
 *****************************************************************************/
ViStatus hmp4000_reset(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    if (RsCore_Simulating(instrSession) == 0)
    {
		checkErr(RsCore_Write(instrSession, "*RST"));
		RsCore_Delay(0.2);
		checkErr(RsCore_QueryViInt32(instrSession, "*OPC?", NULL));
    }

    checkErr(hmp4000_DefaultInstrSetup(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);

    return error;
}

/*****************************************************************************
 * Function: Self Test
 * Purpose:  This function executes the instrument self-test and returns the
 *           result.
 *****************************************************************************/
ViStatus hmp4000_self_test(ViSession instrSession,
                           ViInt16   *testResult,
                           ViChar    testMessage[])
{
    ViStatus error = VI_SUCCESS;
    ViChar   response[RS_MAX_MESSAGE_BUF_SIZE];

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidNullPointer(instrSession, testResult), 2, "Null address for Test Result");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, testMessage), 3, "Null address for Test Message");

    if (RsCore_Simulating(instrSession) == 0)
    {
	    checkErr(RsCore_QueryViString(instrSession, "*TST?", response));
	    if (*testResult == 0)
	        strcpy (testMessage, "Self-Test Passed.");
	    else
	        strcpy (testMessage, "Self-Test Failed.");
    }
    else
    {
		// Simulate Self Test
		*testResult = 0;
		strcpy (testMessage, "No error.");
    }

    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Revision Query
 * Purpose:  This function returns the driver and instrument revisions.
 *****************************************************************************/
ViStatus hmp4000_revision_query(ViSession instrSession,
                                ViChar    instrumentDriverRevision[],
                                ViChar    firmwareRevision[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidNullPointer(instrSession, instrumentDriverRevision), 2, "Null address for Instrument Driver Revision");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, firmwareRevision), 3, "Null address for Instrument Revision");

    checkErr(RsCore_GetAttributeViString(instrSession, NULL, RS_ATTR_SPECIFIC_DRIVER_REVISION, 0, 256, instrumentDriverRevision));
    checkErr(RsCore_GetAttributeViString(instrSession, NULL, RS_ATTR_INSTRUMENT_FIRMWARE_REVISION, 0, 256, firmwareRevision));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function:    System Version
 * Purpose:     This function queries the number of the SCPI version, which
 *              is relevant for the instrument.
 *****************************************************************************/
ViStatus hmp4000_SystemVersion(ViSession instrSession,
                               ViInt32   length,
                               ViChar    systemVersion[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(hmp4000_GetAttributeViString(instrSession, "", HMP4000_ATTR_SYSTEM_VERSION, length, systemVersion),
            2, "System Version");

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Error Query
 * Purpose:  This function queries the instrument error queue and returns
 *           the result.
 *****************************************************************************/
ViStatus hmp4000_error_query(ViSession instrSession,
                             ViInt32   * errorCode,
                             ViChar    errorMessage[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidNullPointer(instrSession, errorCode), 2, "Null address for Error Code");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, errorMessage), 3, "Null address for Error Message");

    checkErr(RsCore_ErrorQueryAll(instrSession, errorCode, 1024, errorMessage));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Error Message
 * Purpose:  This function translates the error codes returned by this
 *           instrument driver into user-readable strings.
 *
 *           Note:  The caller can pass NULL for the vi parameter.  This
 *           is useful if one of the init functions fail.
 *****************************************************************************/
ViStatus hmp4000_error_message(ViSession instrSession,
                               ViStatus  errorCode,
                               ViChar    errorMessage[])
{
    ViStatus error = VI_SUCCESS;

    (void)(RsCore_LockSession(instrSession));

    static RsCoreStringValueTable errorTable =
    {
        HMP4000_ERROR_CODES_AND_MSGS,
        {0, NULL}
    };

    // all VISA and RS error codes are handled as well as codes in the table
    viCheckParm(RsCore_InvalidNullPointer(instrSession, errorMessage), 3, "Null address for Error Message");

    checkErr(RsCore_GetSpecificDriverStatusDesc(instrSession, errorCode, errorMessage, 256, errorTable));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/*****************************************************************************
 * Function: hmp4000_SetRegister
 * Purpose:  This function configures the selected register enable values.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER
 *           HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER
 *           HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER
 *
 *           Remote-control command(s):
 *           STATus:QUEStionable:ENABle
 *           STATus:QUEStionable:INSTrument:ENABle
 *           STATus:QUEStionable:INSTrument:ISUMmary<n>:ENABle
 *****************************************************************************/
ViStatus hmp4000_SetRegister(ViSession instrSession,
                             ViInt32   registers,
                             ViInt32   channel,
                             ViInt32   value)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    switch(registers){
        case HMP4000_VAL_QUESTIONABLE_REGISTER:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER, value),
                4, "Value");
            break;
        case HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER:
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, "", HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER, value),
                4, "Value");
            break;
        case HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER:

        viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, 1, 4), 3, "Channel");;

        snprintf(repCap, RS_REPCAP_BUF_SIZE, "CH%ld", channel);
        viCheckParm(hmp4000_SetAttributeViInt32(instrSession, repCap, HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER, value),
                4, "Value");
            break;
        default:
            error = RS_ERROR_VALUE_NOT_AVAILABLE;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}



/*****************************************************************************
 * Function: hmp4000_GetRegister
 * Purpose:  This function queries the selected register event and condition
 *           values.
 *
 *           Attribute(s):
 *           HMP4000_ATTR_QUESTIONABLE_EVENT_REGISTER
 *           HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_EVENT_REGISTER
 *           HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_EVENT_REGISTER
 *           HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER
 *
 *           Remote-control command(s):
 *           STATus:QUEStionable[:EVENt]?
 *           STATus:QUEStionable:INSTrument[:EVENt]?
 *           STATus:QUEStionable:INSTrument:ISUMmary<n>[:EVENt]?
 *           STATus:QUEStionable:INSTrument:ISUMmary<n>:CONDition?
 *
 *****************************************************************************/
ViStatus hmp4000_GetRegister(ViSession instrSession,
                             ViInt32   registers,
                             ViInt32   channel,
                             ViInt32*  value)
{
    ViStatus error = VI_SUCCESS;
    ViChar   repCap[RS_REPCAP_BUF_SIZE] = "";

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, channel, 1, 4), 3, "Channel");;

    snprintf(repCap, RS_REPCAP_BUF_SIZE, "CH%ld", channel);

    switch(registers){
        case HMP4000_VAL_QUESTIONABLE_REGISTER:
        viCheckParm(hmp4000_GetAttributeViInt32(instrSession, "", HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER, value),
                4, "Value");
            break;
        case HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER:
        viCheckParm(hmp4000_GetAttributeViInt32(instrSession, "", HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER, value),
                4, "Value");
            break;
        case HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER:
        viCheckParm(hmp4000_GetAttributeViInt32(instrSession, repCap, HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER, value),
                4, "Value");
            break;
        case HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER:
        viCheckParm(hmp4000_GetAttributeViInt32(instrSession, repCap, HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER, value),
                4, "Value");
            break;
        default:
            error = RS_ERROR_VALUE_NOT_AVAILABLE;
    }

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function configures the remote mode.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR remoteMode/This control selects the remote mode.
ViStatus hmp4000_RemoteMode(ViSession instrSession,
                            ViInt32   remoteMode)
{
    ViStatus error = VI_SUCCESS;
    ViAttr   attr[] = {HMP4000_ATTR_SYSTEM_LOCAL,
             HMP4000_ATTR_SYSTEM_REMOTE,
             HMP4000_ATTR_SYSTEM_REMOTE_LOCK,
             HMP4000_ATTR_SYSTEM_REMOTE_MIX};

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidViInt32Range(instrSession, remoteMode, HMP4000_VAL_LOCAL, HMP4000_VAL_REMOTE_MIX), 2, "Remote Mode");

    checkErr(hmp4000_SetAttributeViString(instrSession, "", attr[remoteMode], NULL));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function clears status.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus hmp4000_ClearStatus(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(RsCore_ClearStatus(instrSession));
    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function returns the ID Query response string.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR IDQueryResponse/Returns the ID Query response string.
ViStatus hmp4000_IDQueryResponse(ViSession instrSession,
                                 ViChar    IDQueryResponse[])
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(hmp4000_QueryViString(instrSession, "*IDN?", 256, IDQueryResponse));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  Stops further command processing until all commands sent before
/// HIFN  *WAI have been executed.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
ViStatus hmp4000_ProcessAllPreviousCommands(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(hmp4000_WriteInstrData(instrSession, "*WAI"));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN  This function queries the OPC.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.  The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR OPC/Queries the OPC.
ViStatus hmp4000_QueryOPC(ViSession instrSession,
                          ViInt32   *OPC)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    checkErr(hmp4000_QueryViInt32(instrSession, "*OPC?", OPC));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/// HIFN This function switches ON/OFF various error checkings performed inside of the driver.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/This control accepts the Instrument Handle returned by the Initialize
/// HIPAR instrSession/function to select the desired instrument driver session.
/// HIPAR optionChecking/This control switches option checking On or Off.
/// HIPAR rangeChecking/This control enables or disables range checking.
/// HIPAR statusChecking/This control enables or disables instrument state checking
ViStatus hmp4000_ConfigureErrorChecking(ViSession instrSession,
                                        ViBoolean optionChecking,
                                        ViBoolean rangeChecking,
                                        ViBoolean statusChecking)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    rsSession->optionChecking = VI_FALSE;
    checkErr(RsCore_SetAttributeViBoolean(instrSession, "", RS_ATTR_QUERY_INSTRUMENT_STATUS, 0, statusChecking));
    checkErr(RsCore_SetAttributeViBoolean(instrSession, "", RS_ATTR_RANGE_CHECK, 0, rangeChecking));

Error:
    return error;
}

/// HIFN This function specifies the minimum timeout value to use (in
/// HIFN milliseconds) when accessing the device associated with the
/// HIFN given session.
/// HIFN Note that the actual timeout used may be higher than the one
/// HIFN requested.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function. The handle identifies a
/// HIPAR instrSession/particular instrument session.
/// HIPAR VISATimeout/Specifies the minimum timeout value to use (in milliseconds)
/// HIPAR VISATimeout/when accessing the device associated with the given session.
/// HIPAR VISATimeout/Note that the actual timeout used may be higher than the one
/// HIPAR VISATimeout/requested.
ViStatus hmp4000_SetVISATimeout(ViSession instrSession,
    ViUInt32  VISATimeout)
{
    return RsCore_SetVisaTimeout(instrSession, VISATimeout);
}

/// HIFN This function queries the minimum timeout value to use (in
/// HIFN milliseconds) when accessing the device associated with the
/// HIFN given session.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function. The handle identifies a
/// HIPAR instrSession/particular instrument session.
/// HIPAR VISATimeout/Queries the minimum timeout value to use (in milliseconds)
/// HIPAR VISATimeout/when accessing the device associated with the given session.
ViStatus hmp4000_GetVISATimeout(ViSession instrSession,
    ViUInt32* VISATimeout)
{
    return RsCore_GetVisaTimeout(instrSession, VISATimeout);
}

/// HIFN If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
/// HIFN Use the function hmp4000_GetError afterwards to get the detailed information about the instrument error(s).
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR autoSystErrQuery/If TRUE (default after init is FALSE), the driver calls SYST:ERR? automatically in CheckStatus() when Instrument Status Error is detected.
ViStatus hmp4000_ConfigureAutoSystemErrQuery(ViSession instrSession,
    ViBoolean autoSystErrQuery)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    rsSession->autoSystErrQuery = autoSystErrQuery;

Error:
    return error;
}

/// HIFN Session-related mutex switch.
/// HIFN If TRUE (default after init is FALSE), the driver sets a mutual-exclusion mechanism for every driver's hi-level function and attribute access.
/// HIFN Set this value to TRUE if you plan to use one session in more than one thread.
/// HIRET Returns the status code of this operation.
/// HIPAR instrSession/The ViSession handle that you obtain from the hmp4000_init or
/// HIPAR instrSession/hmp4000_InitWithOptions function.The handle identifies a particular
/// HIPAR instrSession/instrument session.
/// HIPAR multiThreadLocking/Session-related mutex switch
ViStatus hmp4000_ConfigureMultiThreadLocking(ViSession instrSession,
    ViBoolean multiThreadLocking)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    rsSession->multiThreadLocking = multiThreadLocking;

Error:
    return error;
}

/*****************************************************************************
 * Function: Get Error and Clear Error Functions
 * Purpose:  These functions enable the instrument driver user to
 *           get or clear the error information the driver associates with the
 *           RS session.
 *****************************************************************************/
ViStatus hmp4000_GetError(ViSession instrSession,
                          ViStatus  *errorCode,
                          ViInt32   bufferSize,
                          ViChar    description[])
{
    ViStatus error = VI_SUCCESS;

    // Lock Session - do not jump to the end, even with invalid instrSession the function continues further
    (void)RsCore_LockSession(instrSession);

    // Test for nulls and acquire error data
    viCheckParm(RsCore_InvalidNullPointer(instrSession, errorCode), 2, "Null address for Error");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, description), 4, "Null address for Description");

    checkErr(RsCore_GetErrorCompleteDescription(instrSession, &hmp4000_error_message, errorCode, bufferSize, description));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

ViStatus hmp4000_ClearError(ViSession instrSession)
{
    return RsCore_ClearErrorInfo(instrSession);
}

/*****************************************************************************
 * Function: WriteInstrData
 * Purpose:  These functions enable the instrument driver user to
 *           write commands directly to the instrument.
 *
 *****************************************************************************/

ViStatus hmp4000_WriteInstrData(ViSession instrSession,
                                ViString  writeBuffer)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    error = RsCore_Write(instrSession, writeBuffer);

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Query ViBoolean
 * Purpose:  This function queries the ViBoolean value.
 *****************************************************************************/
ViStatus hmp4000_QueryViBoolean(ViSession instrSession,
                                ViString  command,
                                ViBoolean *value)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidStringLength(instrSession, command, 1, -1), 2, "Command (null string length)");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

    checkErr(RsCore_QueryViBoolean(instrSession, command, value));

    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Query ViInt32
 * Purpose:  This function queries the ViInt32 value.
 *****************************************************************************/
ViStatus hmp4000_QueryViInt32(ViSession instrSession,
                              ViString  command,
                              ViInt32   *value)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidStringLength(instrSession, command, 1, -1), 2, "Command (null string length)");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

    checkErr(RsCore_QueryViInt32(instrSession, command, value));

    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: Query ViReal64
 * Purpose:  This function queries the ViReal64 value.
 *****************************************************************************/
ViStatus hmp4000_QueryViReal64(ViSession instrSession,
                               ViString  command,
                               ViReal64  *value)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidStringLength(instrSession, command, 1, -1), 2, "Command (null string length)");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

    checkErr(RsCore_QueryViReal64(instrSession, command, value));

    checkErr(hmp4000_CheckStatus(instrSession));

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}


/*****************************************************************************
 * Function: Query ViString
 * Purpose:  This function queries the ViString value.
 *****************************************************************************/
ViStatus hmp4000_QueryViString(ViSession instrSession,
                               ViString  command,
                               ViInt32   bufferSize,
                               ViChar    value[])
{
    ViStatus error = VI_SUCCESS;
    ViChar* pbuffer = NULL;

    checkErr(RsCore_LockSession(instrSession));

    viCheckParm(RsCore_InvalidStringLength(instrSession, command, 1, -1), 2, "Command (null string length)");
    viCheckParm(RsCore_InvalidNullPointer(instrSession, value), 3, "Value");

    checkErr(RsCore_QueryViStringUnknownLength(instrSession, command, &pbuffer));

    checkErr(hmp4000_CheckStatus(instrSession));

    checkErr(RsCore_CopyToUserBufferAsciiData(value, bufferSize, pbuffer));

Error:
    if (pbuffer) free(pbuffer);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

/*****************************************************************************
 * Function: hmp4000_close
 * Purpose:  This function closes the instrument.
 *
 *           Note:  This function must unlock the session before calling
 *           Rs_Dispose.
 *****************************************************************************/
ViStatus hmp4000_close(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    checkErr(RsCore_LockSession(instrSession));

    if (instrSession > 0)
        checkErr(RsCore_Write(instrSession, "SYST:LOC"));

    checkErr(RsCore_ViClose(instrSession));

Error:
    (void)RsCore_Dispose(instrSession);
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

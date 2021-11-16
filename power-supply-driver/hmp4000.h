/****************************************************************************
 *
 * HAMEG driver include file
 *
 ****************************************************************************/

#ifndef __HMP4000_HEADER
#define __HMP4000_HEADER

#include "rscore.h"
#include "hmp4000_attributes.h"
#include "hmp4000_utility.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Useful Macros & Constants -----------------------------------------------*
 *****************************************************************************/

#define HMP4000_SIMULATION_ID_QUERY      "ROHDE&SCHWARZ,HMP4040,123456/789,2.62"  /* Default definition of ID Query Response for simulation */
#define HMP4000_VALID_ID_RESPONSE_STRING1 "HAMEG"               /* Valid response for identification query - HAMEG instruments*/
#define HMP4000_VALID_ID_RESPONSE_STRING2 "ROHDE&SCHWARZ"      /* Valid response for identification query - R&S instruments*/
#define HMP4000_SIMULATION_OPT_QUERY     ""      /* Simulated response for *OPT? command */

#define HMP4000_OPC_TIMEOUT              5000L   /* Maximum time to wait for OPC in milliseconds */

/****************************************************************************
 *----------------- Instrument Driver Revision Information -----------------*
 ****************************************************************************/

/* Class Driver Identification */

#define HMP4000_CLASS_DRIVER_DESCRIPTION           ""
#define HMP4000_CLASS_DRIVER_PREFIX                ""
#define HMP4000_CLASS_DRIVER_VENDOR                ""
#define HMP4000_CLASS_DRIVER_REVISION              ""
#define HMP4000_CLASS_SPEC_MAJOR_VERSION           1L    /* Class specification major version */
#define HMP4000_CLASS_SPEC_MINOR_VERSION           0L    /* Class specification minor version */

/* Driver Identification */

#define HMP4000_SPECIFIC_DRIVER_DESCRIPTION        ""
#define HMP4000_SPECIFIC_DRIVER_PREFIX             "HMP4000"
#define HMP4000_SPECIFIC_DRIVER_LOCATOR            ""
#define HMP4000_SPECIFIC_DRIVER_VENDOR             "Rohde&Schwarz"
#define HMP4000_MAJOR_VERSION                      3L    /* Instrument driver major version          */
#define HMP4000_MINOR_VERSION                      0L   /* Instrument driver minor version          */
#define HMP4000_MINOR_MINOR_VERSION                0L    /* Instrument driver minor minor version    */

/* Driver Capabilities */

#define HMP4000_SUPPORTED_INSTRUMENT_MODELS        "HMP4000,HMP4030,HMP4040,HMP2000,HMP2020,HMP2030"    /* Instrument driver supported model(s)     */
#define HMP4000_GROUP_CAPABILITIES                 ""
#define HMP4000_FUNCTION_CAPABILITIES              ""

/****************************************************************************
 *------------------------------ Useful Macros -----------------------------*
 ****************************************************************************/

/****************************************************************************
 *---------------------------- Attribute Defines ---------------------------*
 ****************************************************************************/

/*- Inherent Instrument Specific Attributes ----------------------------*/


#define HMP4000_ATTR_RANGE_CHECK                                           RS_ATTR_RANGE_CHECK                                     // ViBoolean
#define HMP4000_ATTR_QUERY_INSTRUMENT_STATUS                               RS_ATTR_QUERY_INSTRUMENT_STATUS                         // ViBoolean
#define HMP4000_ATTR_SIMULATE                                              RS_ATTR_SIMULATE                                        // ViBoolean

#define HMP4000_ATTR_SPECIFIC_DRIVER_DESCRIPTION                           RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION                     // ViString, read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_PREFIX                                RS_ATTR_SPECIFIC_DRIVER_PREFIX                          // ViString, read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_LOCATOR                               RS_ATTR_SPECIFIC_DRIVER_LOCATOR                         // ViString, read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_VENDOR                                RS_ATTR_SPECIFIC_DRIVER_VENDOR                          // ViString, read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_REVISION                              RS_ATTR_SPECIFIC_DRIVER_REVISION                        // ViString, read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION        // ViInt32,  read-only
#define HMP4000_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION              RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION        // ViInt32,  read-only


#define HMP4000_ATTR_SUPPORTED_INSTRUMENT_MODELS                           RS_ATTR_SUPPORTED_INSTRUMENT_MODELS                     // ViString, read-only
#define HMP4000_ATTR_GROUP_CAPABILITIES                                    RS_ATTR_GROUP_CAPABILITIES                              // ViString, read-only
#define HMP4000_ATTR_FUNCTION_CAPABILITIES                                 RS_ATTR_FUNCTION_CAPABILITIES                           // ViString, read-only
#define HMP4000_ATTR_CHANNEL_COUNT                                         RS_ATTR_CHANNEL_COUNT                                   // ViInt32,  read-only


#define HMP4000_ATTR_DRIVER_SETUP                                          RS_ATTR_DRIVER_SETUP                                    /* ViString            */


#define HMP4000_ATTR_INSTRUMENT_MANUFACTURER                               RS_ATTR_INSTRUMENT_MANUFACTURER                         // ViString, read-only
#define HMP4000_ATTR_INSTRUMENT_MODEL                                      RS_ATTR_INSTRUMENT_MODEL                                // ViString, read-only
#define HMP4000_ATTR_INSTRUMENT_FIRMWARE_REVISION                          RS_ATTR_INSTRUMENT_FIRMWARE_REVISION                    // ViString, read-only


#define HMP4000_ATTR_IO_RESOURCE_DESCRIPTOR                                RS_ATTR_IO_RESOURCE_DESCRIPTOR                          // ViString, read-only
#define HMP4000_ATTR_LOGICAL_NAME                                          RS_ATTR_LOGICAL_NAME                                    // ViString, read-only


//#define HMP4000_ATTR_ID_QUERY_RESPONSE                                     (RS_SPECIFIC_PUBLIC_ATTR_BASE + 1L)                     /* ViString (Read Only)              */

/* BEGIN GENERATE */
#define HMP4000_ATTR_SELECTION_OF_CHANNEL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 49
#define HMP4000_ATTR_OUTPUT_STATE                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 1
#define HMP4000_ATTR_GENERAL_OUTPUT_STATE                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 54
#define HMP4000_ATTR_OUTPUT_SELECT                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 55
#define HMP4000_ATTR_SETTINGS_STORE_LOCATION                                RS_SPECIFIC_PUBLIC_ATTR_BASE + 2
#define HMP4000_ATTR_SETTINGS_RECALL_LOCATION                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 3
#define HMP4000_ATTR_BEEPER_MODE                                            RS_SPECIFIC_PUBLIC_ATTR_BASE + 4
#define HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 5
#define HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_MAX                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 81
#define HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 6
#define HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 7
#define HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 8
#define HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 9
#define HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 87
#define HMP4000_ATTR_OUTPUT_CURRENT_LEVEL                                   RS_SPECIFIC_PUBLIC_ATTR_BASE + 10
#define HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_MAX                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 80
#define HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 11
#define HMP4000_ATTR_ELECTRONIC_FUSE_STATE                                  RS_SPECIFIC_PUBLIC_ATTR_BASE + 12
#define HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 13
#define HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 14
#define HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 15
#define HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 16
#define HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 17
#define HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL                       RS_SPECIFIC_PUBLIC_ATTR_BASE + 18
#define HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL              RS_SPECIFIC_PUBLIC_ATTR_BASE + 19
#define HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE                               RS_SPECIFIC_PUBLIC_ATTR_BASE + 20
#define HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL                             RS_SPECIFIC_PUBLIC_ATTR_BASE + 21
#define HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR                              RS_SPECIFIC_PUBLIC_ATTR_BASE + 22
#define HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 23
#define HMP4000_ATTR_MEASUREMENT_DC_CURRENT                                 RS_SPECIFIC_PUBLIC_ATTR_BASE + 24
#define HMP4000_ATTR_SYSTEM_VERSION                                         RS_SPECIFIC_PUBLIC_ATTR_BASE + 25
#define HMP4000_ATTR_SYSTEM_ERROR                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 26
#define HMP4000_ATTR_SYSTEM_ALL_ERRORS                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 27
#define HMP4000_ATTR_SYSTEM_LOCAL                                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 50
#define HMP4000_ATTR_SYSTEM_REMOTE                                          RS_SPECIFIC_PUBLIC_ATTR_BASE + 51
#define HMP4000_ATTR_SYSTEM_REMOTE_LOCK                                     RS_SPECIFIC_PUBLIC_ATTR_BASE + 52
#define HMP4000_ATTR_SYSTEM_REMOTE_MIX                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 53
#define HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER                           RS_SPECIFIC_PUBLIC_ATTR_BASE + 29
#define HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER                RS_SPECIFIC_PUBLIC_ATTR_BASE + 30
#define HMP4000_ATTR_ID_QUERY_RESPONSE                                      RS_SPECIFIC_PUBLIC_ATTR_BASE + 33
#define HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER       RS_SPECIFIC_PUBLIC_ATTR_BASE + 31
#define HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER    RS_SPECIFIC_PUBLIC_ATTR_BASE + 32

// hmp4000_rngChannel
#define HMP4000_VAL_CH_N                                                    0
#define HMP4000_VAL_CH_1                                                    1
#define HMP4000_VAL_CH_2                                                    2
#define HMP4000_VAL_CH_3                                                    3
#define HMP4000_VAL_CH_4                                                    4

// hmp4000_rngMemoryIndex
#define HMP4000_VAL_MEM_1                                                   1
#define HMP4000_VAL_MEM_2                                                   2
#define HMP4000_VAL_MEM_3                                                   3

// hmp4000_rngOutput
#define HMP4000_VAL_OUTPUT_1                                                1
#define HMP4000_VAL_OUTPUT_2                                                2
#define HMP4000_VAL_OUTPUT_3                                                3
#define HMP4000_VAL_OUTPUT_4                                                4

// hmp4000_rngBeeper
#define HMP4000_VAL_BEEPER_OFF                                              0
#define HMP4000_VAL_BEEPER_ON                                               1
#define HMP4000_VAL_BEEPER_CRITICAL                                         2

// Hmp4000_rngOverVoltageProtectionMode
#define HMP4000_VAL_OVP_MODE_MEASURED                                       0
#define HMP4000_VAL_OVP_MODE_PROTECTED                                      1

//repcap Channel
#define HMP4000_REPCAP_CHANNEL_CH1                                          1
#define HMP4000_REPCAP_CHANNEL_CH2                                          2
#define HMP4000_REPCAP_CHANNEL_CH3                                          3
#define HMP4000_REPCAP_CHANNEL_CH4                                          4
/* END GENERATE */

/*****************************************************************************
 *- Hidden Attribute Declarations -------------------------------------------*
 *****************************************************************************/
/*
#define HMP4000_ATTR_OPC_TIMEOUT               (RS_ATTR_OPC_TIMEOUT)
#define HMP4000_ATTR_IO_SESSION                (RS_ATTR_IO_SESSION)
#define HMP4000_ATTR_OPC_CALLBACK              (RS_ATTR_OPC_CALLBACK)
#define HMP4000_ATTR_CHECK_STATUS_CALLBACK     (RS_ATTR_CHECK_STATUS_CALLBACK)
*/
/****************************************************************************
 *---------------- Constant definition  ------------------------------------*
 ****************************************************************************/

#define HMP4000_VAL_FUSE_LINK   0
#define HMP4000_VAL_FUSE_UNLINK 1

#define HMP4000_VAL_QUESTIONABLE_REGISTER 0
#define HMP4000_VAL_QUESTIONABLE_INSTRUMENT_REGISTER 1
#define HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_REGISTER 2
#define HMP4000_VAL_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER 3

#define HMP4000_VAL_MEM_OPERATION_STORE  0
#define HMP4000_VAL_MEM_OPERATION_RECALL 1
#define HMP4000_VAL_MEM_OPERATION_CLEAR  2

#define HMP4000_VAL_LOCAL       0
#define HMP4000_VAL_REMOTE      1
#define HMP4000_VAL_REMOTE_LOCK 2
#define HMP4000_VAL_REMOTE_MIX  3

/****************************************************************************
 *---------------- Instrument Driver Function Declarations -----------------*
 ****************************************************************************/

ViStatus hmp4000_init(ViRsrc resourceName, ViBoolean IDQuery,
    ViBoolean resetDevice, ViSession* newInstrSession);

ViStatus hmp4000_InitWithOptions(
    ViRsrc resourceName,
    ViBoolean IDQuery,
    ViBoolean resetDevice,
    ViString optionString,
    ViSession* newInstrSession
);

ViStatus hmp4000_ConfigureChannel(ViSession instrSession,
                                  ViInt32   channel);

ViStatus hmp4000_GetChannel(ViSession instrSession,
                            ViInt32*  channel);

ViStatus hmp4000_ConfigureCombinedVoltageAndCurrent(ViSession instrSession,
                                                    ViReal64  voltage,
                                                    ViReal64  current);

ViStatus hmp4000_ConfigureOutputState(ViSession instrSession,
                                      ViBoolean outputState);

ViStatus hmp4000_ConfigureGeneralOutputState(ViSession instrSession,
                                             ViBoolean outputState);

ViStatus hmp4000_ConfigureOutputStateChannelOnly(ViSession instrSession,
                                                 ViBoolean outputState);

ViStatus hmp4000_ConfigureSettingsLocation(ViSession instrSession,
                                           ViInt32   memoryOperation,
                                           ViInt32   location);

ViStatus hmp4000_QueryCombinedVoltageAndCurrent(ViSession instrSession,
                                                ViReal64* voltageValue,
                                                ViReal64* current);

ViStatus hmp4000_ConfigureArbitraryGeneratorWaveformData(ViSession instrSession,
                                                         ViInt32   arraySize,
                                                         ViReal64  voltage[],
                                                         ViReal64  current[],
                                                         ViReal64  time[],
                                                         ViInt32   repetition);

ViStatus hmp4000_ConfigureArbitraryGeneratorStartChannel(ViSession instrSession,
                                                         ViInt32   channel);

ViStatus hmp4000_ConfigureArbitraryGeneratorStopChannel(ViSession instrSession,
                                                        ViInt32   channel);

ViStatus hmp4000_ConfigureArbitraryGeneratorDataTransferChannel(
                            ViSession instrSession,
                            ViInt32   channel);

ViStatus hmp4000_ConfigureArbitraryGeneratorDataStorage(ViSession instrSession,
                                                        ViInt32   memoryOperation,
                                                        ViInt32   memoryIndex);

ViStatus hmp4000_ConfigureCurrentValue(ViSession instrSession,
                                       ViReal64  current);

ViStatus hmp4000_ConfigureElectronicFuse(ViSession instrSession,
                                         ViBoolean fuse,
                                         ViInt32   linkToChannel,
                                         ViInt32   unlinkFromChannel);

ViStatus hmp4000_ConfigureCurrentStepValue(ViSession instrSession,
                                           ViReal64  currentStep);

ViStatus hmp4000_QueryElectronicFuseStatus(ViSession  instrSession,
                                           ViBoolean* fuseStatus);

ViStatus hmp4000_ConfigureVoltageValue(ViSession instrSession,
                                       ViReal64  voltage);

ViStatus hmp4000_ConfigureOverVoltageProtection(ViSession instrSession,
                                                ViReal64  OVPValue);

ViStatus hmp4000_ConfigureVoltageStepValue(ViSession instrSession,
                                           ViReal64  voltageStep);

ViStatus hmp4000_QueryOverVoltageProtectionStatus(ViSession  instrSession,
                                                  ViBoolean* OVPStatus);

ViStatus hmp4000_ClearOverVoltageProtection(ViSession instrSession);

ViStatus hmp4000_ConfigureOverVoltageProtectionMode(ViSession instrSession,
                                                    ViInt32   mode);

ViStatus hmp4000_ConfigureBeeper(ViSession instrSession,
                                 ViInt32   beeper);

ViStatus hmp4000_ReadVoltageOutput(ViSession instrSession,
                                   ViReal64* voltageValue);

ViStatus hmp4000_ReadCurrentOutput(ViSession instrSession,
                                   ViReal64* currentValue);

ViStatus hmp4000_SetAttributeViInt32(ViSession instrSession,
                                     ViString  repeatedCapabilityName,
                                     ViUInt32  attributeID,
                                     ViInt32   attributeValue);

ViStatus hmp4000_SetAttributeViReal64(ViSession instrSession,
                                      ViString  repeatedCapabilityName,
                                      ViUInt32  attributeID,
                                      ViReal64  attributeValue);

ViStatus hmp4000_SetAttributeViString(ViSession instrSession,
                                      ViString  repeatedCapabilityName,
                                      ViUInt32  attributeID,
                                      ViString  attributeValue);

ViStatus hmp4000_SetAttributeViBoolean(ViSession instrSession,
                                       ViString  repeatedCapabilityName,
                                       ViUInt32  attributeID,
                                       ViBoolean attributeValue);

ViStatus hmp4000_GetAttributeRepCapName(ViSession instrSession,
                                        ViUInt32  attributeId,
                                        ViString  repCapNameId,
                                        ViInt32   index,
                                        ViInt32   bufferSize,
                                        ViChar    repCapName[]);

ViStatus hmp4000_GetAttributeRepeatedCapabilityIds(ViSession instrSession,
                                                   ViUInt32  attributeID,
                                                   ViInt32   bufferSize,
                                                   ViChar    repeatedCapabilityIds[]);

ViStatus hmp4000_GetAttributeRepeatedCapabilityIdNames(ViSession instrSession,
                                                       ViUInt32  attributeID,
                                                       ViString  repeatedCapabilityId,
                                                       ViInt32   bufferSize,
                                                       ViChar    repeatedCapabilityIdNames[]);

ViStatus hmp4000_GetAttributeViInt32(ViSession instrSession,
                                     ViString  repeatedCapabilityName,
                                     ViUInt32  attributeID,
                                     ViInt32*  attributeValue);

ViStatus hmp4000_GetAttributeViReal64(ViSession instrSession,
                                      ViString  repeatedCapabilityName,
                                      ViUInt32  attributeID,
                                      ViReal64* attributeValue);

ViStatus hmp4000_GetAttributeViString(ViSession instrSession,
                                      ViString  repeatedCapabilityName,
                                      ViUInt32  attributeID,
                                      ViInt32   bufferSize,
                                      ViChar    attributeValue[]);

ViStatus hmp4000_GetAttributeViBoolean(ViSession  instrSession,
                                       ViString   repeatedCapabilityName,
                                       ViUInt32   attributeID,
                                       ViBoolean* attributeValue);

ViStatus hmp4000_reset(ViSession instrSession);

ViStatus hmp4000_self_test(ViSession instrSession,
                           ViInt16*  selfTestResult,
                           ViChar    selfTestMessage[]);

ViStatus hmp4000_revision_query(ViSession instrSession,
                                ViChar    instrumentDriverRevision[],
                                ViChar    firmwareRevision[]);

ViStatus hmp4000_SystemVersion(ViSession instrSession,
                               ViInt32   length,
                               ViChar    systemVersion[]);

ViStatus hmp4000_error_query(ViSession instrSession,
                             ViInt32*  errorCode,
                             ViChar    errorMessage[]);

ViStatus hmp4000_error_message(ViSession instrSession,
                               ViStatus  errorCode,
                               ViChar    errorMessage[]);

ViStatus hmp4000_SetRegister(ViSession instrSession,
                             ViInt32   registers,
                             ViInt32   channel,
                             ViInt32   value);

ViStatus hmp4000_GetRegister(ViSession instrSession,
                             ViInt32   registers,
                             ViInt32   channel,
                             ViInt32*  value);

ViStatus hmp4000_RemoteMode(ViSession instrSession,
                            ViInt32   remoteMode);

ViStatus hmp4000_ClearStatus(ViSession instrSession);

ViStatus hmp4000_IDQueryResponse(ViSession instrSession,
                                 ViChar    IDQueryResponse[]);

ViStatus hmp4000_ProcessAllPreviousCommands(ViSession instrSession);

ViStatus hmp4000_QueryOPC(ViSession instrSession,
                          ViInt32*  OPC);

ViStatus hmp4000_ConfigureErrorChecking(ViSession instrSession,
                                        ViBoolean optionChecking,
                                        ViBoolean rangeChecking,
                                        ViBoolean statusChecking);

ViStatus hmp4000_SetVISATimeout(ViSession instrSession,
    ViUInt32  VISATimeout);
	
ViStatus hmp4000_GetVISATimeout(ViSession instrSession,
    ViUInt32* VISATimeout);

ViStatus hmp4000_ConfigureAutoSystemErrQuery(ViSession instrSession,
    ViBoolean autoSystErrQuery);

ViStatus hmp4000_ConfigureMultiThreadLocking(ViSession instrSession,
    ViBoolean multiThreadLocking);

ViStatus hmp4000_GetError(ViSession instrSession,
                          ViStatus* code,
                          ViInt32   bufferSize,
                          ViChar    description[]);

ViStatus hmp4000_ClearError(ViSession instrSession);

ViStatus hmp4000_WriteInstrData(ViSession instrSession,
                                ViString  writeBuffer);

ViStatus hmp4000_QueryViBoolean(ViSession  instrSession,
                                ViString   command,
                                ViBoolean* value);

ViStatus hmp4000_QueryViInt32(ViSession instrSession,
                              ViString  command,
                              ViInt32*  value);

ViStatus hmp4000_QueryViReal64(ViSession instrSession,
                               ViString  command,
                               ViReal64* value);

ViStatus hmp4000_QueryViString(ViSession instrSession,
                               ViString  command,
                               ViInt32   bufferSize,
                               ViChar    value[]);

ViStatus hmp4000_close(ViSession instrSession);

/****************************************************************************
 *------------------------ Error And Completion Codes ----------------------*
 ****************************************************************************/

#define HMP4000_WARN_MEASURE_UNCALIBRATED    (RS_CLASS_WARN_BASE + 0x0001L)
#define HMP4000_WARN_OVER_RANGE              (RS_CLASS_WARN_BASE + 0x0002L)

#define HMP4000_ERROR_INCORRECT_STATE        (RS_CLASS_ERROR_BASE + 0x0003L)
#define HMP4000_ERROR_INCORRECT_RESPONSE     (RS_CLASS_ERROR_BASE + 0x0002L)
#define HMP4000_ERROR_MAX_TIME_EXCEEDED      (RS_CLASS_ERROR_BASE + 0x0001L)

#define HMP4000_WARNMSG_MEASURE_UNCALIBRATED "Uncalibrated measurement"
#define HMP4000_WARNMSG_OVER_RANGE           "Measurement overrange"

#define HMP4000_ERRMSG_INCORRECT_STATE       "Instrument in incorrect state"
#define HMP4000_ERRMSG_INCORRECT_RESPONSE    "Response incorrect; report problem to HAMEG support!"
#define HMP4000_ERRMSG_MAX_TIME_EXCEEDED     "Max Time Exceeded"

#define HMP4000_ERROR_CODES_AND_MSGS \
    {HMP4000_ERROR_INCORRECT_STATE,   HMP4000_ERRMSG_INCORRECT_STATE},\
    {HMP4000_ERROR_INCORRECT_RESPONSE,     HMP4000_ERRMSG_INCORRECT_RESPONSE},\
    {HMP4000_ERROR_MAX_TIME_EXCEEDED,    HMP4000_ERRMSG_MAX_TIME_EXCEEDED}

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/

#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __HMP4000_HEADER */

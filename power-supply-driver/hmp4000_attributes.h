/*****************************************************************************
 *  Rohde&Schwarz Instrument Driver Specific Attribute callbacks include file
 *
 *  WARNING: Do not add to, delete from, or otherwise modify the contents
 *           of this include file. It is generated from DrBase repository.
 *
 *  Built on: 2021-05-07 13:39:09Z
 *****************************************************************************/

#ifndef __HMP4000_ATTRIBUTES_HEADER
#define __HMP4000_ATTRIBUTES_HEADER

#include "rscore.h"

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C" {
#endif

/*****************************************************************************
 *- Read Callbacks ----------------------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 *- Write Callbacks ---------------------------------------------------------*
 *****************************************************************************/
ViStatus hmp4000_Delayed_Int32_WriteCallback(ViSession          io,
                                             ViConstString      repCapName,
                                             RsCoreAttributePtr attr,
                                             void               *value);

/*****************************************************************************
 *- Range Tables ------------------------------------------------------------*
 *****************************************************************************/
extern RsCoreRangeTableDiscrete hmp4000_rngChannel;
extern RsCoreRangeTableDiscrete hmp4000_rngMemoryIndex;
extern RsCoreRangeTableDiscrete hmp4000_rngOutput;
extern RsCoreRangeTableRanged hmp4000_rngOutputVoltage;
extern RsCoreRangeTableRanged hmp4000_rngOutputCurrent;
extern RsCoreRangeTableRanged hmp4000_rngMemoryLocation;
extern RsCoreRangeTableRanged hmp4000_rngArbRepetition;
extern RsCoreRangeTableRanged hmp4000_rngOVP;
extern RsCoreRangeTableDiscrete hmp4000_rngBeeper;
extern RsCoreRangeTableDiscrete Hmp4000_rngOverVoltageProtectionMode;

/*****************************************************************************
 *- Attributes --------------------------------------------------------------*
 *****************************************************************************/
extern RsCoreAttribute g_HMP4000_RS_ATTR_RANGE_CHECK;
extern RsCoreAttribute g_HMP4000_RS_ATTR_QUERY_INSTRUMENT_STATUS;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SIMULATE;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_PREFIX;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_LOCATOR;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_VENDOR;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_REVISION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS;
extern RsCoreAttribute g_HMP4000_RS_ATTR_GROUP_CAPABILITIES;
extern RsCoreAttribute g_HMP4000_RS_ATTR_FUNCTION_CAPABILITIES;
extern RsCoreAttribute g_HMP4000_RS_ATTR_CHANNEL_COUNT;
extern RsCoreAttribute g_HMP4000_RS_ATTR_DRIVER_SETUP;
extern RsCoreAttribute g_HMP4000_RS_ATTR_INSTRUMENT_MANUFACTURER;
extern RsCoreAttribute g_HMP4000_RS_ATTR_INSTRUMENT_MODEL;
extern RsCoreAttribute g_HMP4000_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_OPTIONS_LIST;
extern RsCoreAttribute g_HMP4000_RS_ATTR_IO_RESOURCE_DESCRIPTOR;
extern RsCoreAttribute g_HMP4000_RS_ATTR_LOGICAL_NAME;
extern RsCoreAttribute g_HMP4000_RS_ATTR_PRIMARY_ERROR;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SECONDARY_ERROR;
extern RsCoreAttribute g_HMP4000_RS_ATTR_ERROR_ELABORATION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_CLASS_DRIVER_MINOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_ENGINE_MAJOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_ENGINE_MINOR_VERSION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_ENGINE_REVISION;
extern RsCoreAttribute g_HMP4000_RS_ATTR_OPC_TIMEOUT;
extern RsCoreAttribute g_HMP4000_ATTR_SELECTION_OF_CHANNEL;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_STATE;
extern RsCoreAttribute g_HMP4000_ATTR_GENERAL_OUTPUT_STATE;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_SELECT;
extern RsCoreAttribute g_HMP4000_ATTR_SETTINGS_STORE_LOCATION;
extern RsCoreAttribute g_HMP4000_ATTR_SETTINGS_RECALL_LOCATION;
extern RsCoreAttribute g_HMP4000_ATTR_BEEPER_MODE;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_MAX;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP;
extern RsCoreAttribute g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL;
extern RsCoreAttribute g_HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS;
extern RsCoreAttribute g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR;
extern RsCoreAttribute g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_MAX;
extern RsCoreAttribute g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP;
extern RsCoreAttribute g_HMP4000_ATTR_ELECTRONIC_FUSE_STATE;
extern RsCoreAttribute g_HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS;
extern RsCoreAttribute g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK;
extern RsCoreAttribute g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL;
extern RsCoreAttribute g_HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR;
extern RsCoreAttribute g_HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE;
extern RsCoreAttribute g_HMP4000_ATTR_MEASUREMENT_DC_CURRENT;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_VERSION;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_ERROR;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_ALL_ERRORS;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_LOCAL;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_REMOTE;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_REMOTE_LOCK;
extern RsCoreAttribute g_HMP4000_ATTR_SYSTEM_REMOTE_MIX;
extern RsCoreAttribute g_HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER;
extern RsCoreAttribute g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER;
extern RsCoreAttribute g_HMP4000_ATTR_ID_QUERY_RESPONSE;
extern RsCoreAttribute g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER;
extern RsCoreAttribute g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER;

/*****************************************************************************
 *- Repeated Capabilities Table --------------------------------------------------------------*
 *****************************************************************************/
extern RsCoreRepCap hmp4000_RsCoreRepCapTable[];
extern ViInt32 hmp4000_RsCoreRepCapTableCount;

/*****************************************************************************
 *- Attributes List ---------------------------------------------------------*
 *****************************************************************************/
extern RsCoreAttributePtr hmp4000_RsCoreAttributeList[];
extern ViInt32 hmp4000_RsCoreAttributeListLength;

/****************************************************************************
 *---------------------------- End Include File ----------------------------*
 ****************************************************************************/
#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif
#endif /* __HMP4000_ATTRIBUTES_HEADER */

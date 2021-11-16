/*****************************************************************************
 *  Rohde&Schwarz Instrument Driver Specific Attribute callbacks
 *
 *  WARNING: Do not add to, delete from, or otherwise modify the contents
 *           of this source file. It is generated from DrBase repository.
 *
 *  Built on: 2021-05-13 11:34:44Z
 *****************************************************************************/

#include "hmp4000.h"

/*****************************************************************************
 *- Repeated Capabilities ---------------------------------------------------*
 *****************************************************************************/

ViInt32 hmp4000_RsCoreRepCapTableCount = 1;

RsCoreRepCap hmp4000_RsCoreRepCapTable[1] =
  { /*
    {
      repCapName  ... Repeated capability name, e.g. "Channel"
      identifiers ... Repeated capability identifiers (comma separated values), e.g. "Ch1,Ch2,Ch3"
      cmdValues   ... Command values (comma separated values), e.g. "1,2,3"
    } */
    {
      "Channel",
      "CH1,CH2,CH3,CH4",
      "1,2,3,4"
    }
  };

/*****************************************************************************
 *- Range Tables ------------------------------------------------------------*
 *****************************************************************************/

static RsCoreRangeTableDiscreteEntry hmp4000_rngChannelEntries[5] =
  {
    { HMP4000_VAL_CH_N, "" },
    { HMP4000_VAL_CH_1, "1" },
    { HMP4000_VAL_CH_2, "2" },
    { HMP4000_VAL_CH_3, "3" },
    { HMP4000_VAL_CH_4, "4" }
  };
RsCoreRangeTableDiscrete hmp4000_rngChannel = { 5, hmp4000_rngChannelEntries };

static RsCoreRangeTableDiscreteEntry hmp4000_rngMemoryIndexEntries[3] =
  {
    { HMP4000_VAL_MEM_1, "1" },
    { HMP4000_VAL_MEM_2, "2" },
    { HMP4000_VAL_MEM_3, "3" }
  };
RsCoreRangeTableDiscrete hmp4000_rngMemoryIndex = { 3, hmp4000_rngMemoryIndexEntries };

static RsCoreRangeTableDiscreteEntry hmp4000_rngOutputEntries[4] =
  {
    { HMP4000_VAL_OUTPUT_1, "OUTP1" },
    { HMP4000_VAL_OUTPUT_2, "OUTP2" },
    { HMP4000_VAL_OUTPUT_3, "OUTP3" },
    { HMP4000_VAL_OUTPUT_4, "OUTP4" }
  };
RsCoreRangeTableDiscrete hmp4000_rngOutput = { 4, hmp4000_rngOutputEntries };

RsCoreRangeTableRanged hmp4000_rngOutputVoltage = { 0, 32.00, "V" };

RsCoreRangeTableRanged hmp4000_rngOutputCurrent = { 0, 10.00, "A" };

RsCoreRangeTableRanged hmp4000_rngMemoryLocation = { 0, 9, "" };

RsCoreRangeTableRanged hmp4000_rngArbRepetition = { 0, 255, "" };

RsCoreRangeTableRanged hmp4000_rngOVP = { 0, 33, "V" };

static RsCoreRangeTableDiscreteEntry hmp4000_rngBeeperEntries[3] =
  {
    { HMP4000_VAL_BEEPER_OFF, "OFF" },
    { HMP4000_VAL_BEEPER_ON, "ON" },
    { HMP4000_VAL_BEEPER_CRITICAL, "CRIT" }
  };
RsCoreRangeTableDiscrete hmp4000_rngBeeper = { 3, hmp4000_rngBeeperEntries };

static RsCoreRangeTableDiscreteEntry Hmp4000_rngOverVoltageProtectionModeEntries[2] =
  {
    { HMP4000_VAL_OVP_MODE_MEASURED, "MEAS" },
    { HMP4000_VAL_OVP_MODE_PROTECTED, "PROT" }
  };
RsCoreRangeTableDiscrete Hmp4000_rngOverVoltageProtectionMode = { 2, Hmp4000_rngOverVoltageProtectionModeEntries };


/*****************************************************************************
 *- Attributes --------------------------------------------------------------*
 *****************************************************************************/

RsCoreAttribute  g_HMP4000_RS_ATTR_RANGE_CHECK =
  {
    RS_ATTR_RANGE_CHECK,
    "Range Check",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_TRUE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_QUERY_INSTRUMENT_STATUS =
  {
    RS_ATTR_QUERY_INSTRUMENT_STATUS,
    "Query Instrument Status",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_TRUE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SIMULATE =
  {
    RS_ATTR_SIMULATE,
    "Simulate",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION =
  {
    RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION,
    "Driver Description",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "description",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_PREFIX =
  {
    RS_ATTR_SPECIFIC_DRIVER_PREFIX,
    "Driver Prefix",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "hmp4000",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_LOCATOR =
  {
    RS_ATTR_SPECIFIC_DRIVER_LOCATOR,
    "Driver Locator",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "locator",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_VENDOR =
  {
    RS_ATTR_SPECIFIC_DRIVER_VENDOR,
    "Driver Vendor",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "Vendor",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_REVISION =
  {
    RS_ATTR_SPECIFIC_DRIVER_REVISION,
    "Driver Revision",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "revision",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION =
  {
    RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION,
    "Class Specification Major Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION =
  {
    RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION,
    "Class Specification Minor Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS =
  {
    RS_ATTR_SUPPORTED_INSTRUMENT_MODELS,
    "Supported Instrument Models",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "models",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_GROUP_CAPABILITIES =
  {
    RS_ATTR_GROUP_CAPABILITIES,
    "Class Group Capabilities",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "capabilities",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_FUNCTION_CAPABILITIES =
  {
    RS_ATTR_FUNCTION_CAPABILITIES,
    "Function Capabilities",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "capabilities",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_CHANNEL_COUNT =
  {
    RS_ATTR_CHANNEL_COUNT,
    "Channel Count",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_DRIVER_SETUP =
  {
    RS_ATTR_DRIVER_SETUP,
    "Driver Setup",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "setup",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_INSTRUMENT_MANUFACTURER =
  {
    RS_ATTR_INSTRUMENT_MANUFACTURER,
    "Instrument Manufacturer",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "RohdeSchwarz",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_INSTRUMENT_MODEL =
  {
    RS_ATTR_INSTRUMENT_MODEL,
    "Instrument Model",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "model",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION =
  {
    RS_ATTR_INSTRUMENT_FIRMWARE_REVISION,
    "Instrument Firmware Revision",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "revision",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_OPTIONS_LIST =
  {
    RS_ATTR_OPTIONS_LIST,
    "Options List",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "list",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_IO_RESOURCE_DESCRIPTOR =
  {
    RS_ATTR_IO_RESOURCE_DESCRIPTOR,
    "Resource Descriptor",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "descriptor",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_LOGICAL_NAME =
  {
    RS_ATTR_LOGICAL_NAME,
    "Logical Name",
    RS_VAL_READ_ONLY,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "name",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_PRIMARY_ERROR =
  {
    RS_ATTR_PRIMARY_ERROR,
    "Primary Error",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SECONDARY_ERROR =
  {
    RS_ATTR_SECONDARY_ERROR,
    "Secondary Error",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_ERROR_ELABORATION =
  {
    RS_ATTR_ERROR_ELABORATION,
    "Error Elaboration",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "elaboration",
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION =
  {
    RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION,
    "Driver Major Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION =
  {
    RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION,
    "Driver Minor Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION =
  {
    RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION,
    "Driver Minor Minor Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION =
  {
    RS_ATTR_CLASS_DRIVER_MAJOR_VERSION,
    "Class Major Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_CLASS_DRIVER_MINOR_VERSION =
  {
    RS_ATTR_CLASS_DRIVER_MINOR_VERSION,
    "Class Minor Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_ENGINE_MAJOR_VERSION =
  {
    RS_ATTR_ENGINE_MAJOR_VERSION,
    "Engine Major Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_ENGINE_MINOR_VERSION =
  {
    RS_ATTR_ENGINE_MINOR_VERSION,
    "Engine Minor Version",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_ENGINE_REVISION =
  {
    RS_ATTR_ENGINE_REVISION,
    "Engine Revision",
    RS_VAL_READ_WRITE,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "0",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_RS_ATTR_OPC_TIMEOUT =
  {
    RS_ATTR_OPC_TIMEOUT,
    "Operation Complete (OPC) Timeout",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    NULL, // No command
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SELECTION_OF_CHANNEL =
  {
    HMP4000_ATTR_SELECTION_OF_CHANNEL,
    "Selection Of Channel",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    &hmp4000_rngOutput, NULL, NULL,
    "INST:SEL",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_OUTPUT_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_STATE =
  {
    HMP4000_ATTR_OUTPUT_STATE,
    "Output State",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "OUTP:STAT",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_GENERAL_OUTPUT_STATE =
  {
    HMP4000_ATTR_GENERAL_OUTPUT_STATE,
    "General Output State",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "OUTP:GEN",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_SELECT =
  {
    HMP4000_ATTR_OUTPUT_SELECT,
    "Output Select",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "OUTP:SEL",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SETTINGS_STORE_LOCATION =
  {
    HMP4000_ATTR_SETTINGS_STORE_LOCATION,
    "Settings Store Location",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    NULL, &hmp4000_rngMemoryLocation, NULL,
    "*SAV",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SETTINGS_RECALL_LOCATION =
  {
    HMP4000_ATTR_SETTINGS_RECALL_LOCATION,
    "Settings Recall Location",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    NULL, &hmp4000_rngMemoryLocation, NULL,
    "*RCL",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_BEEPER_MODE =
  {
    HMP4000_ATTR_BEEPER_MODE,
    "Beeper Mode",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    &hmp4000_rngBeeper, NULL, NULL,
    "SYST:BEEP:IMM",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_BEEPER_OFF,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL =
  {
    HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL,
    "Output Voltage Level",
    RS_VAL_READ_WRITE,
    RS_VAL_REAL64,
    NULL, &hmp4000_rngOutputVoltage, NULL,
    "SOUR:VOLT:LEV:AMPL",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_MAX =
  {
    HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_MAX,
    "Output Voltage Level Max",
    RS_VAL_READ_ONLY,
    RS_VAL_REAL64,
    NULL, NULL, NULL,
    "VOLT? MAX",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    10,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP =
  {
    HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP,
    "Output Voltage Level Step",
    RS_VAL_READ_WRITE,
    RS_VAL_REAL64,
    NULL, &hmp4000_rngOutputVoltage, NULL,
    "SOUR:VOLT:LEV:AMPL:STEP:INCR",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL =
  {
    HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL,
    "Over Voltage Protection Level",
    RS_VAL_READ_WRITE,
    RS_VAL_REAL64,
    NULL, &hmp4000_rngOVP, NULL,
    "VOLT:PROT:LEV",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    33.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS =
  {
    HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS,
    "Query Over Voltage Protection Status",
    RS_VAL_READ_ONLY,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "VOLT:PROT:TRIP?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR =
  {
    HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR,
    "Over Voltage Protection Clear",
    RS_VAL_WRITE_ONLY,
    RS_VAL_EVENT,
    NULL, NULL, NULL,
    "VOLT:PROT:CLE",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE =
  {
    HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE,
    "Over Voltage Protection Mode",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    &Hmp4000_rngOverVoltageProtectionMode, NULL, NULL,
    "VOLT:PROT:MODE",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_OVP_MODE_MEASURED,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL =
  {
    HMP4000_ATTR_OUTPUT_CURRENT_LEVEL,
    "Output Current Level",
    RS_VAL_READ_WRITE,
    RS_VAL_REAL64,
    NULL, &hmp4000_rngOutputCurrent, NULL,
    "SOUR:CURR:LEV:AMPL",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_MAX =
  {
    HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_MAX,
    "Output Current Level Max",
    RS_VAL_READ_ONLY,
    RS_VAL_REAL64,
    NULL, NULL, NULL,
    "CURR? MAX",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    10.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP =
  {
    HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP,
    "Output Current Level Step",
    RS_VAL_READ_WRITE,
    RS_VAL_REAL64,
    NULL, &hmp4000_rngOutputCurrent, NULL,
    "SOUR:CURR:LEV:AMPL:STEP:INCR",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ELECTRONIC_FUSE_STATE =
  {
    HMP4000_ATTR_ELECTRONIC_FUSE_STATE,
    "Electronic Fuse State",
    RS_VAL_READ_WRITE,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "FUSE:STAT",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS =
  {
    HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS,
    "Query Electronic Fuse Status",
    RS_VAL_READ_ONLY,
    RS_VAL_BOOLEAN,
    NULL, NULL, NULL,
    "FUSE:TRIP?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK =
  {
    HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK,
    "Electronic Fuse Channel Link",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngChannel, NULL, NULL,
    "FUSE:LINK",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_CH_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK =
  {
    HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK,
    "Electronic Fuse Channel Unlink",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngChannel, NULL, NULL,
    "FUSE:UNL",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_CH_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION,
    "Arbitrary Generator Repetition",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, &hmp4000_rngArbRepetition, NULL,
    "ARB:REP",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL,
    "Arbitrary Generator Start Channel",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngChannel, NULL, NULL,
    "ARB:STAR",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_CH_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL,
    "Arbitrary Generator Stop Channel",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngChannel, NULL, NULL,
    "ARB:STOP",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_CH_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL,
    "Arbitrary Generator Data Transfer Channel",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngChannel, NULL, NULL,
    "ARB:TRAN",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_CH_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE,
    "Arbitrary Generator Save",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngMemoryIndex, NULL, NULL,
    "ARB:SAVE",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_MEM_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    hmp4000_Delayed_Int32_WriteCallback,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL,
    "Arbitrary Generator Recall",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngMemoryIndex, NULL, NULL,
    "ARB:REST",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_MEM_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR =
  {
    HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR,
    "Arbitrary Generator Clear",
    RS_VAL_WRITE_ONLY,
    RS_VAL_INT32,
    &hmp4000_rngMemoryIndex, NULL, NULL,
    "ARB:CLE",
    // Defaults I32, I64, Float, Bool, String
    HMP4000_VAL_MEM_1,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE =
  {
    HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE,
    "Measurement DC Voltage",
    RS_VAL_READ_ONLY,
    RS_VAL_REAL64,
    NULL, NULL, NULL,
    "MEAS:VOLT:DC?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_MEASUREMENT_DC_CURRENT =
  {
    HMP4000_ATTR_MEASUREMENT_DC_CURRENT,
    "Measurement DC Current",
    RS_VAL_READ_ONLY,
    RS_VAL_REAL64,
    NULL, NULL, NULL,
    "MEAS:CURR:DC?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_VERSION =
  {
    HMP4000_ATTR_SYSTEM_VERSION,
    "System Version",
    RS_VAL_READ_ONLY,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    "SYST:VERSion?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "version",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_ERROR =
  {
    HMP4000_ATTR_SYSTEM_ERROR,
    "System Error",
    RS_VAL_READ_ONLY,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    "SYST:ERRor?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "error",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_ALL_ERRORS =
  {
    HMP4000_ATTR_SYSTEM_ALL_ERRORS,
    "System All Errors",
    RS_VAL_READ_ONLY,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    "SYST:ERR:ALL?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "errors",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_LOCAL =
  {
    HMP4000_ATTR_SYSTEM_LOCAL,
    "System Local",
    RS_VAL_WRITE_ONLY,
    RS_VAL_EVENT,
    NULL, NULL, NULL,
    "SYST:LOC",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_REMOTE =
  {
    HMP4000_ATTR_SYSTEM_REMOTE,
    "System Remote",
    RS_VAL_WRITE_ONLY,
    RS_VAL_EVENT,
    NULL, NULL, NULL,
    "SYST:REM",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_REMOTE_LOCK =
  {
    HMP4000_ATTR_SYSTEM_REMOTE_LOCK,
    "System Remote Lock",
    RS_VAL_WRITE_ONLY,
    RS_VAL_EVENT,
    NULL, NULL, NULL,
    "SYST:RWL",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_SYSTEM_REMOTE_MIX =
  {
    HMP4000_ATTR_SYSTEM_REMOTE_MIX,
    "System Remote Mix",
    RS_VAL_WRITE_ONLY,
    RS_VAL_EVENT,
    NULL, NULL, NULL,
    "SYST:MIX",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    RS_VAL_DONT_CHECK_STATUS,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER =
  {
    HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER,
    "Questionable Enable Register",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    "STAT:QUES:ENAB",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER =
  {
    HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER,
    "Questionable Instrument Enable Register",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    "STAT:QUES:INST:ENAB",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_ID_QUERY_RESPONSE =
  {
    HMP4000_ATTR_ID_QUERY_RESPONSE,
    "ID Query Response",
    RS_VAL_READ_ONLY,
    RS_VAL_STRING,
    NULL, NULL, NULL,
    "*IDN?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    "response",
    // Flags, HasRepCaps
    0,
    VI_FALSE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER =
  {
    HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER,
    "Questionable Instrument Specific Enable Register",
    RS_VAL_READ_WRITE,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    "STAT:QUES:INST:ISUM{Channel}:ENAB",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_TRUE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };

RsCoreAttribute  g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER =
  {
    HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER,
    "Questionable Instrument Specific Condition Register",
    RS_VAL_READ_ONLY,
    RS_VAL_INT32,
    NULL, NULL, NULL,
    "STAT:QUES:INST:ISUM{Channel}:COND?",
    // Defaults I32, I64, Float, Bool, String
    0,
    0,
    0.0,
    VI_FALSE,
    NULL,
    // Flags, HasRepCaps
    0,
    VI_TRUE,
    // Models, Options
    NULL,
    NULL,
    // Callbacks Read, Write, p2Value
    NULL,
    NULL,
    NULL,
  };


/*****************************************************************************
 *- Attributes List ---------------------------------------------------------*
 *****************************************************************************/

ViInt32 hmp4000_RsCoreAttributeListLength = 75;

RsCoreAttributePtr hmp4000_RsCoreAttributeList[75] =
  {
    &g_HMP4000_RS_ATTR_RANGE_CHECK,
    &g_HMP4000_RS_ATTR_QUERY_INSTRUMENT_STATUS,
    &g_HMP4000_RS_ATTR_SIMULATE,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_PREFIX,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_LOCATOR,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_VENDOR,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_REVISION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION,
    &g_HMP4000_RS_ATTR_SUPPORTED_INSTRUMENT_MODELS,
    &g_HMP4000_RS_ATTR_GROUP_CAPABILITIES,
    &g_HMP4000_RS_ATTR_FUNCTION_CAPABILITIES,
    &g_HMP4000_RS_ATTR_CHANNEL_COUNT,
    &g_HMP4000_RS_ATTR_DRIVER_SETUP,
    &g_HMP4000_RS_ATTR_INSTRUMENT_MANUFACTURER,
    &g_HMP4000_RS_ATTR_INSTRUMENT_MODEL,
    &g_HMP4000_RS_ATTR_INSTRUMENT_FIRMWARE_REVISION,
    &g_HMP4000_RS_ATTR_OPTIONS_LIST,
    &g_HMP4000_RS_ATTR_IO_RESOURCE_DESCRIPTOR,
    &g_HMP4000_RS_ATTR_LOGICAL_NAME,
    &g_HMP4000_RS_ATTR_PRIMARY_ERROR,
    &g_HMP4000_RS_ATTR_SECONDARY_ERROR,
    &g_HMP4000_RS_ATTR_ERROR_ELABORATION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION,
    &g_HMP4000_RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION,
    &g_HMP4000_RS_ATTR_CLASS_DRIVER_MAJOR_VERSION,
    &g_HMP4000_RS_ATTR_CLASS_DRIVER_MINOR_VERSION,
    &g_HMP4000_RS_ATTR_ENGINE_MAJOR_VERSION,
    &g_HMP4000_RS_ATTR_ENGINE_MINOR_VERSION,
    &g_HMP4000_RS_ATTR_ENGINE_REVISION,
    &g_HMP4000_RS_ATTR_OPC_TIMEOUT,
    &g_HMP4000_ATTR_SELECTION_OF_CHANNEL,
    &g_HMP4000_ATTR_OUTPUT_STATE,
    &g_HMP4000_ATTR_GENERAL_OUTPUT_STATE,
    &g_HMP4000_ATTR_OUTPUT_SELECT,
    &g_HMP4000_ATTR_SETTINGS_STORE_LOCATION,
    &g_HMP4000_ATTR_SETTINGS_RECALL_LOCATION,
    &g_HMP4000_ATTR_BEEPER_MODE,
    &g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL,
    &g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_MAX,
    &g_HMP4000_ATTR_OUTPUT_VOLTAGE_LEVEL_STEP,
    &g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_LEVEL,
    &g_HMP4000_ATTR_QUERY_OVER_VOLTAGE_PROTECTION_STATUS,
    &g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_CLEAR,
    &g_HMP4000_ATTR_OVER_VOLTAGE_PROTECTION_MODE,
    &g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL,
    &g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_MAX,
    &g_HMP4000_ATTR_OUTPUT_CURRENT_LEVEL_STEP,
    &g_HMP4000_ATTR_ELECTRONIC_FUSE_STATE,
    &g_HMP4000_ATTR_QUERY_ELECTRONIC_FUSE_STATUS,
    &g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_LINK,
    &g_HMP4000_ATTR_ELECTRONIC_FUSE_CHANNEL_UNLINK,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_REPETITION,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_START_CHANNEL,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_STOP_CHANNEL,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_DATA_TRANSFER_CHANNEL,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_RECALL,
    &g_HMP4000_ATTR_ARBITRARY_GENERATOR_CLEAR,
    &g_HMP4000_ATTR_MEASUREMENT_DC_VOLTAGE,
    &g_HMP4000_ATTR_MEASUREMENT_DC_CURRENT,
    &g_HMP4000_ATTR_SYSTEM_VERSION,
    &g_HMP4000_ATTR_SYSTEM_ERROR,
    &g_HMP4000_ATTR_SYSTEM_ALL_ERRORS,
    &g_HMP4000_ATTR_SYSTEM_LOCAL,
    &g_HMP4000_ATTR_SYSTEM_REMOTE,
    &g_HMP4000_ATTR_SYSTEM_REMOTE_LOCK,
    &g_HMP4000_ATTR_SYSTEM_REMOTE_MIX,
    &g_HMP4000_ATTR_QUESTIONABLE_ENABLE_REGISTER,
    &g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_ENABLE_REGISTER,
    &g_HMP4000_ATTR_ID_QUERY_RESPONSE,
    &g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_ENABLE_REGISTER,
    &g_HMP4000_ATTR_QUESTIONABLE_INSTRUMENT_SPECIFIC_CONDITION_REGISTER
  };

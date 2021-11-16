/*****************************************************************************
 *------------------------ Utility  -----------------------------------------*
 *****************************************************************************/
#include "hmp4000.h"

#pragma warning( disable : 4152 )

/*****************************************************************************
 *- Common Callback Declarations --------------------------------------------*
 *****************************************************************************/

/*****************************************************************************
 * Function: hmp4000_InitAttributes
 * Purpose:  This function inits attributes to the desired values if needed.
 *****************************************************************************/
ViStatus hmp4000_InitAttributes(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    // - Driver Identification -
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_DESCRIPTION, 0, HMP4000_SPECIFIC_DRIVER_DESCRIPTION));
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_PREFIX, 0, HMP4000_SPECIFIC_DRIVER_PREFIX));
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_LOCATOR, 0, HMP4000_SPECIFIC_DRIVER_LOCATOR));
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_VENDOR, 0, HMP4000_SPECIFIC_DRIVER_VENDOR));
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MAJOR_VERSION, 0, HMP4000_CLASS_SPEC_MAJOR_VERSION));
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_CLASS_SPEC_MINOR_VERSION, 0, HMP4000_CLASS_SPEC_MINOR_VERSION));

    // - Driver Capabilities -
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_SUPPORTED_INSTRUMENT_MODELS, 0, HMP4000_SUPPORTED_INSTRUMENT_MODELS));
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_GROUP_CAPABILITIES, 0, HMP4000_GROUP_CAPABILITIES));
    checkErr(RsCore_SetAttributeViString(instrSession, "", RS_ATTR_FUNCTION_CAPABILITIES, 0, HMP4000_FUNCTION_CAPABILITIES));

    // - Version Info -
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MAJOR_VERSION, 0, HMP4000_MAJOR_VERSION));
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_VERSION, 0, HMP4000_MINOR_VERSION));
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_SPECIFIC_DRIVER_MINOR_MINOR_VERSION, 0, HMP4000_MINOR_MINOR_VERSION));

    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_MAJOR_VERSION, 0, HMP4000_CLASS_SPEC_MAJOR_VERSION));
    checkErr(RsCore_SetAttributeViInt32(instrSession, "", RS_ATTR_CLASS_DRIVER_MINOR_VERSION, 0, HMP4000_CLASS_SPEC_MINOR_VERSION));

    checkErr(RsCore_SetSpecificDriverRevision(instrSession, RS_ATTR_SPECIFIC_DRIVER_REVISION));

Error:
    return error;
}

/*****************************************************************************
 * Function: hmp4000_DefaultInstrSetup
 * Purpose:  This function sends a default setup to the instrument. The
 *           hmp4000_reset function calls this function. The
 *           hmp4000_RsInit function calls this function when the
 *           user passes VI_FALSE for the reset parameter. This function is
 *           useful for configuring settings that other instrument driver
 *           functions require.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus hmp4000_DefaultInstrSetup(ViSession instrSession)
{
    ViStatus         error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

    checkErr(RsCore_GetRsSession(instrSession, &rsSession));
    // Set all the attributes to the default state. Do not update inherent attributes!
    checkErr(RsCore_ApplyAttributeDefaults(instrSession, VI_FALSE));

    checkErr(hmp4000_InitAttributes(instrSession));
    rsSession->fastSweepInstrument = 0;
    checkErr(RsCore_ResetRegistersEseSre(instrSession));

    if (!RsCore_Simulating(instrSession))
    {
        checkErr(RsCore_ClearStatus(instrSession));
    }

Error:
    return error;
}

/*****************************************************************************
 * Function: hmp4000_CheckStatus
 * Purpose:  This function checks the status of the instrument to detect
 *           whether the instrument has encountered an error. This function
 *           is called at the end of most exported driver functions. If the
 *           instrument reports an error, this function returns
 *           RS_ERROR_INSTRUMENT_SPECIFIC. The user can set the
 *           hmp4000_ATTR_QUERY_INSTRUMENT_STATUS attribute to VI_FALSE to disable this
 *           check and increase execution speed.
 *
 *           Note:  Call this function only when the session is locked.
 *****************************************************************************/
ViStatus hmp4000_CheckStatus(ViSession instrSession)
{
    ViStatus error = VI_SUCCESS;

    if (RsCore_QueryInstrStatus(instrSession) && !RsCore_Simulating(instrSession))
    {
        checkErr(RsCore_CheckStatus(instrSession, VI_SUCCESS));
    }

Error:
    return error;
}

/*****************************************************************************
* Function: hmp4000_Delayed_Int32_WriteCallback
* Purpose:  This function overrides standard calback funtion
*           - waiting 4.0 seconds after the write for ASRL interface
*           - used in HMP4000_ATTR_ARBITRARY_GENERATOR_SAVE
*****************************************************************************/
ViStatus hmp4000_Delayed_Int32_WriteCallback(ViSession instrSession,
    ViConstString repCapName,
    RsCoreAttributePtr attr,
    void* value)
{
    ViStatus    error = VI_SUCCESS;
    RsCoreSessionPtr rsSession = NULL;

	checkErr(RsCore_LockSession(instrSession));
	
    checkErr(RsCore_GetRsSession(instrSession, &rsSession));

    checkErr(RsCore_WriteCallback(instrSession, repCapName, attr, value));
	if (rsSession->sessionType == RS_INTF_ASRL)
	{
        RsCore_Delay(4000);
    }
	else
	{
		RsCore_Delay(100);
	}

Error:
    (void)RsCore_UnlockSession(instrSession);
    return error;
}

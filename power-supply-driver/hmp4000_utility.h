/*****************************************************************************
 *- Utility Function Declarations (Non-Exported) ----------------------------*
 *****************************************************************************/

#pragma once
#include <visatype.h>

ViStatus hmp4000_InitAttributes(ViSession instrSession);

ViStatus hmp4000_DefaultInstrSetup(ViSession openInstrSession);

ViStatus hmp4000_CheckStatus(ViSession instrSession);

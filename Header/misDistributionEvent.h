#pragma  once

#include "misDataBoundstr.h"
#include "misDistributionStruct.h"
#include "misEvent.h"
#include "misPlaneContrast.h"
#include "misVertebraEnum.h"

#pragma warning (push)
#pragma warning (disable : 4800)	// IGSTK crap

igstkLoadedEventMacro(misUpdatePositionEvent, misEvent, misUpdatePositionInfoStruct);
igstkLoadedEventMacro(misAddLandmarkEvent, misEvent, misLandmarkInfoStruct);
igstkLoadedEventMacro(misPlaneContrastEvent, misEvent, misPlaneIndexWinLevStr);
igstkLoadedEventMacro(misUpdateLandmarkStatusEvent, misEvent, misLandmarkInfoStruct);
igstkEventMacro(misBackToPanModeEvent, misEvent);
igstkLoadedEventMacro(misROIWidgetUpdateEvent, misEvent, misDataBoundStr);
#pragma warning (pop)

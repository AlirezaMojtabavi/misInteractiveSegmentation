#pragma once


#include "TipCalibrationWithSVDresults.h"
#include "TrackingReportData.h"
#include "misEvent.h"
#include "misGuiStructures.h"
#include "misNewDetectedToolData.h"
#include "misStrctConnectOption.h"
#include "misStrctToolAdd.h"
#include "misTrackingManagerEnums.h"
#include "misTrackingManagerTypes.h"
#include "misTrackingStateReport.h"
#include "misTrackingToolMarkerReport.h"

#pragma warning( push)
#pragma warning( disable : 4800 )
#pragma warning( disable : 4275 )

itkEventMacro( misUpdateOnTrackingEvent,				misEvent);
itkEventMacro( misCancelPivotingEvent,					misEvent);
itkEventMacro( misCalibrationToToolEvent,				misEvent);
itkEventMacro( misUpdateOffTrackingEvent,				misEvent);
itkEventMacro( misTrackingViewerEventCore,				misEvent);
itkEventMacro( misRequestResetToolsForOtherTabsCore,		misEvent);
igstkLoadedEventMacro( misTrackingStateReportEventCore, misEvent, misTrackingStateReport );
igstkLoadedEventMacro( misTrackingToolMarkerReportEventCore, misEvent, misTrackingToolMarkerReport );

igstkLoadedEventMacro( misCalibrationInputEvent,		misEvent,		misStrctInputCalibrationData ) ;
igstkLoadedEventMacro( misUnLoadToolEvent,				misEvent,		misStrctSimpleToolProperties) ;
 igstkLoadedEventMacro( misCalibrationOutputEvent,		misEvent,		misStrctOutputCalibrationData ) ;
igstkLoadedEventMacro( misNewDetectedToolEventCore,			misEvent,		misNewDetectedToolData );
itkEventMacro( misStartToolAccuracy,misEvent);
igstkLoadedEventMacro( misConnectTrackerEventCore,			misEvent,		misStrctComConnectionOptions ) ;
igstkLoadedEventMacro( misUpdateToolListToGUICore,			misEvent,		misSimpleToolNameListTypdef ) ; 
igstkLoadedEventMacro( misAddToolListEventCore,				misEvent,		misToolPropertiesListTypdef);
igstkLoadedEventMacro( misDeltetedToolEventCore,			misEvent,		misStrctSimpleToolProperties );
igstkLoadedEventMacro( misAddedToolEventCore,				misEvent,		misStrctToolAdd ) ;


itkEventMacro( misTrackerNotFountd,misEvent);

//////////////added by -M.A- for handling a progress bar when launching Pivot calibration
igstkLoadedEventMacro(misPivotCalibrationProgressBarEventCore,misEvent,double);//-added  by -M.A-

igstkLoadedEventMacro(misDisconnectTrackerEvent, misEvent, bool);
itkEventMacro(misReConnectTrackerEvent, misEvent);

//////////////added by -M.A- for controlling time of showing tip calibration window 10 minutes
itkEventMacro(misCalibrationWindowTimedOutEventCore,misEvent);

//////////////added by -M.A- for controlling time of data gathering
itkEventMacro(misDataGatheringTimedOutEventCore,misEvent);

#pragma warning(pop )


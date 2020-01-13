#pragma once
#include "misGuiEvent.h"
#include "misGuiStructures.h"
#include <misAutoCaptureScreenStrcts.h>
#include <misImageContainedPolyDataStructs.h>
#include "misWindowsLayout.h"
#include "SOURCEDEST.h"
#include "misLoadedEventMacro.h"
#include "voreen\misCroppingDirectionInVR.h"
#include "TargetPointData.h"

misLoadedEventMacro(misRequestFreezNavigation, misGUIEvent, bool);
misLoadedEventMacro(misRequestAutoMeasurmentNavigation, misGUIEvent, MeasurmentWidgetstrct);
misLoadedEventMacro(misRequestWidgetTypeChange, misGUIEvent, misCursorType);
misLoadedEventMacro(misRequestEraseTextureInNavigation, misGUIEvent, bool);
misLoadedEventMacro(misRequestErasedObjectColorChange, misGUIEvent, misColorStruct);
misLoadedEventMacro(misUpdateErasedObjectDisplayStateEvent, misGUIEvent, bool);
misLoadedEventMacro(misSetTargetRegionRadiusEvent, misGUIEvent, double);
misLoadedEventMacro(misAutoVirtualTipExtension, misGUIEvent, bool);


misGUIEventMacro(misUpViewModeChanging, misGUIEvent);
misGUIEventMacro(misModifyEntryPointByTracker, misGUIEvent);
misGUIEventMacro(misModifyTargetPointByVirtualTip, misGUIEvent);
misGUIEventMacro(misBiopsy3DStlClockwiseRotate, misGUIEvent);
misGUIEventMacro(misBiopsy3DStlCounterClockwiseRotate, misGUIEvent);
misGUIEventMacro(misSpine3DStlClockwiseRotate, misGUIEvent);
misGUIEventMacro(misSpine3DStlCounterClockwiseRotate, misGUIEvent);

misLoadedEventMacro(misRequestShowToolProjection, misGUIEvent, bool);
misLoadedEventMacro(misRequest3DMeasurmentActivation, misGUIEvent, bool);
misLoadedEventMacro(misRequestCheckPointsActivation, misGUIEvent, bool);
misLoadedEventMacro(misRequestTargetPointsActivation, misGUIEvent, bool);

misLoadedEventMacro(misRequestButton3DMeasurmentChangeState, misGUIEvent, SOURCEDEST);

misLoadedEventMacro(Update3DDistanceEvent, misGUIEvent, double);
misLoadedEventMacro(Update3DDistanceGUIStateEvent, misGUIEvent, LandmarkStateListTypdef);
misLoadedEventMacro(UpdateNearesetLandmarkInfoEvent, misGUIEvent, misNearsetLandmarkStr);
misLoadedEventMacro(UpdateTargetPointInfoEvent, misGUIEvent, TargetPointData);
misLoadedEventMacro(ShowCutDirectionGridEvent, misGUIEvent, bool);

misLoadedEventMacro(misRequestDistanceToLandmarkChangeState, misGUIEvent, int);
misLoadedEventMacro(misRequestDistanceToTargetPointChangeState, misGUIEvent, LandmarkStatus);
misLoadedEventMacro(UpdateNearesetLandmarkGUIStateEvent, misGUIEvent, LandmarkStateListTypdef);
misLoadedEventMacro(SetAutoPilotButtonsEnableEvent, misGUIEvent, bool);

misLoadedEventMacro(UpdateTargetPointGUIStateEvent, misGUIEvent, LandmarkStateListTypdef);
misLoadedEventMacro(UpdateTakeSnapShotTimerEvent, misGUIEvent, double);
misLoadedEventMacro(misRequestToSetPlaneVisibility, misGUIEvent, ImageVisibilityInformation);
misLoadedEventMacro(UpdateNoFlyZoneInformation, misGUIEvent, std::vector<PropertiesOfPixelInImageType>);


misLoadedEventMacro(misRequestToObliqueViewEvent, misGUIEvent, bool);
//misLoadedEventMacro( misRequestButton3DMeasurmentChangeState,	misGUIEvent, double );

misLoadedEventMacro(misVideoWindowExistEvent, misGUIEvent, bool);

misLoadedEventMacro(misRequestAutoRecordCaptureScreenEvent, misGUIEvent, bool);
misLoadedEventMacro(misCaptureScreenStatusEvent, misGUIEvent, misCaptureScreenStatus);
misLoadedEventMacro(misCaptureScreenStatusForcedFromGUIEvent, misGUIEvent, misCaptureScreenStatus);
misLoadedEventMacro(misUpdateLayouEvent, misGUIEvent, misWindowsLayout);
misLoadedEventMacro(misClearLayouEvent, misGUIEvent, misWindowsLayout);

misLoadedEventMacro(AutomaticGotoFullScreenEvent, misGUIEvent, double);
misGUIEventMacro(misAutoFullScreenUpdateSettingStatus, misGUIEvent);

misLoadedEventMacro(misRequestVirtualTipLengthSetEvent, misGUIEvent, double);
misLoadedEventMacro(misRequestToolTorusStateEvent, misGUIEvent, bool);

misGUIEventMacro(misPackageSelectenStatusEvent, misGUIEvent);
misLoadedEventMacro(misForceViewersToFreezEvent, misGUIEvent,bool);

misLoadedEventMacro(misRequestShowSegmentedObjectIn2D, misGUIEvent, bool);

misLoadedEventMacro(misSendGeneralNoFlyZoneFlag, misGUIEvent, bool);
misLoadedEventMacro(misSendGeneralNoFlyZoneSound, misGUIEvent, bool);

misLoadedEventMacro(misToggleTrackerLowPassFilter, misGUIEvent, bool);

using ToolNamePair = std::pair<std::string, std::string>;
misLoadedEventMacro(UpdateCorrelationVariationToolNames, misGUIEvent, ToolNamePair);
misLoadedEventMacro(UpdateCorrelationAngularDeviation, misGUIEvent, std::string);
misLoadedEventMacro(UpdateCorrelationRadialDeviation, misGUIEvent, std::string);
misGUIEventMacro(miToolCorrelationVariationCalibrateNow, misGUIEvent);
misLoadedEventMacro(misVirtualTipAutomaticLengthEvent, misGUIEvent, double);
misLoadedEventMacro(misPlanTargetRadiusSliderEvent, misGUIEvent, double);
misLoadedEventMacro(misPlanTargetIsPassedEvent, misGUIEvent, bool);
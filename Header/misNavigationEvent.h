#pragma once

#include "misEvent.h"
#include "misAutoCaptureScreenStrcts.h"
#include "misGuiStructures.h"
#include "TargetPointData.h"

igstkLoadedEventMacro(AutomaticGotoFullScreenEventCore,misEvent, double );
igstkLoadedEventMacro(UpdateNearesetLandmarkInfoEventCore,misEvent, misNearsetLandmarkStr);
igstkLoadedEventMacro(Update3DDistanceEventCore,misEvent, double);
igstkLoadedEventMacro(misCaptureScreenStatusEventCore,misEvent,misCaptureScreenStatus);
itkEventMacro(misTakeSnapShotEventCore,misEvent);
igstkLoadedEventMacro(UpdateTakeSnapShotTimerEventCore,misEvent, double );
igstkLoadedEventMacro(UpdateTargetPointInfoEventCore , misEvent, TargetPointData);

using ToolNamePair = std::pair<std::string, std::string>;
igstkLoadedEventMacro(UpdateCorrelationVariationToolNamesCore, misEvent, ToolNamePair);
igstkLoadedEventMacro(UpdateCorrelationAngularDeviationCore, misEvent, std::string);
igstkLoadedEventMacro(UpdateCorrelationRadialDeviationCore, misEvent, std::string);
igstkLoadedEventMacro(misVirtualTipAutomaticLengthEventCore, misEvent, double);
igstkLoadedEventMacro(misPlanTargetRadiusSliderEventCore, misEvent, double);
igstkLoadedEventMacro(misPlanTargetIsPassedEventCore, misEvent, bool);

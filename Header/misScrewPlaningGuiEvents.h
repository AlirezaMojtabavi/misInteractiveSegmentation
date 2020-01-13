#include "misGuiEvent.h"
#include "misColorStruct.h"
#include "misPlanSTRCT.h"
#include "misVertebraEnum.h"
#include "misVertebraEnum.h"

// These below events created from GUI or any other clients and processed by ScrrewPlaning subseqence

misLoadedEventMacro( misPlanningPackageDataSelectedEvent,misGUIEvent,std::string);
misLoadedEventMacro( misSetScrewSourceType,misGUIEvent,ScrewWidgetSourceType);
misLoadedEventMacro(misScrewVerbetraLocationType, misGUIEvent, std::string);
misLoadedEventMacro(misScrewVerbetraPositionType, misGUIEvent, std::string);

misGUIEventMacro( misCreateNewScrew, misGUIEvent);
misGUIEventMacro( misSetEndPoint, misGUIEvent);
misGUIEventMacro( misSetStartPoint, misGUIEvent);
misGUIEventMacro( misDeleteEndPoint, misGUIEvent);
misGUIEventMacro( misDeleteStartPoint, misGUIEvent);
misGUIEventMacro( misModifyEndPoint , misGUIEvent);
misGUIEventMacro( misModifyStartPoint , misGUIEvent);
misGUIEventMacro(misSetScrewInteractionStyleToFree, misGUIEvent);
misGUIEventMacro(misSetScrewInteractionStyleToFreeLength, misGUIEvent);
misGUIEventMacro(misSetScrewInteractionStyleToFreeOrientation, misGUIEvent);
misGUIEventMacro(misAcceptSpline, misGUIEvent);
misGUIEventMacro(misUndoSpline, misGUIEvent);
misGUIEventMacro(misNewSpline, misGUIEvent);
misLoadedEventMacro( misAcceptPlan, misGUIEvent,ScrewPlanInformation);
misGUIEventMacro( misDeletePlan, misGUIEvent);
misLoadedEventMacro(misScrewColorChanged,misGUIEvent,misColorStruct);
misLoadedEventMacro(UpdateIndicatorValue,misGUIEvent,ScrewPlanPropertyIndicator);
misLoadedEventMacro(misScrewWidthChanged, misGUIEvent, double);
misLoadedEventMacro(misPlanCentricViewAngleChanged, misGUIEvent, double);
misGUIEventMacro(misRemoveCutDirection, misGUIEvent);
misGUIEventMacro(misStartStopAngleMeasurement, misGUIEvent);
misLoadedEventMacro(misUpdatePlanColor, misGUIEvent, misColorStruct);


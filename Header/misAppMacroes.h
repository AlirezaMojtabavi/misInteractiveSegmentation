#pragma once
#include "misEnums.h"
#include "misEvent.h"
#include "misGUITypes.h"
#include "misGuiEvent.h"

igstkLoadedEventMacro(ApplySubSegStatesEventToGUICore, misEvent, CurrentSubSequenseStateStrct);
igstkLoadedEventMacro(misSaveSoloutionEventCore, misEvent, misSaveSolutionMode);
itkEventMacro(UpdateMainMenuGUIEventCore, misEvent);
itkEventMacro(misActiveNextSubTabEventCore, misEvent);
itkEventMacro(misBackToPanStateEventCore, misEvent);
itkEventMacro(misDisableAllSlidersEventCore, misEvent);
itkEventMacro(misTaskDoneOnSubTabLeaveCore, misEvent);
itkEventMacro(misRefreshGUIEvent, misEvent);
itkEventMacro(misSubTabSelectionChangeCore, misEvent);
itkEventMacro(misTabSelectionChangeCore, misEvent);
misGUIEventMacro(misActiveNextSubTabEvent, misGUIEvent);
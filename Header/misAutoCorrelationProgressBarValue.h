#pragma once
#include "misLoadedEventMacro.h"
#include "misGUIEvent.h"
#include "ProgressBarStatus.h"

misLoadedEventMacro(misAutoCorrelationProgressBarState, misGUIEvent, ProgressBarStatus);
misLoadedEventMacro(misAutoCorrelationProgressBarValue, misGUIEvent, double);

#pragma once
#include "misevent.h"
#include "misSimplePointType.h"
#include "igstkMacros.h"

igstkLoadedEventMacro(misChangedInterctionStateEvent, misEvent, int);

igstkLoadedEventMacro(misMoveLandmarkWithitsWidget, misEvent, misSimplePointType);

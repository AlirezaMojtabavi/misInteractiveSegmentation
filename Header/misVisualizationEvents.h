#pragma once

#include "misEvent.h"
#include "ILandmarkPointerRepresentation.h"

typedef itk::Point<double, 3> misItkPointType;;

igstkLoadedEventMacro( misPointAdded, misEvent,    std::shared_ptr<ILandmarkPointerRepresentation>) ;
//when  viewer is in landmark selection mode this event occure
igstkLoadedEventMacro( misPointSelect, misEvent,   misItkPointType) ;
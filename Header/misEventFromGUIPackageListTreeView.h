#pragma once

// all event calls by clicking on package tree view must define here !

#include "misLoadedEventMacro.h"
#include "misGUIEvent.h"
#include "misStrctDicomIO.h"
#include "misGuiStructures.h"

misLoadedEventMacro(misTreeviewImageClicked,misGUIEvent,ImageIndexData);
misLoadedEventMacro(misTreeviewPatientClicked,misGUIEvent,ImageIndexData);
misLoadedEventMacro(misTreeviewSerieClicked,misGUIEvent,ImageIndexData);

misLoadedEventMacro(misRequestToChangeVisibility,misGUIEvent,ObjectInformationStrct);
misLoadedEventMacro(misRequestSetObjectVisibility,misGUIEvent,ObjectInformationVisibility);

misLoadedEventMacro(misRequestObjectProperty , misGUIEvent, ObjectInformationStrct);
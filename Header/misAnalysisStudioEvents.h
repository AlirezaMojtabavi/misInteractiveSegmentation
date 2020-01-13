#ifndef __misAnalysisStudioEvents__
#define __misAnalysisStudioEvents__

#include "misCoreEvents.h"
#include "itkImage.h"

typedef itk::Image< float , 3 > misitkImageType;

typedef misitkImageType::IndexType     misitkSeedType;

#pragma warning (push)
#pragma warning (disable : 4800)	// IGSTK crap

//igstkLoadedEventMacro(misShowBGSeedInGUI,misEvent,SeedListType);
//igstkLoadedEventMacro(misShowFGSeedInGUI,misEvent,SeedListType);

//igstkLoadedEventMacro(misLowerThresholdChanged,misGUIEvent,double);
//igstkLoadedEventMacro(misUpperThresholdChanged,misGUIEvent,double);
igstkLoadedEventMacro(misThresholdChanged,misEvent,double);
igstkLoadedEventMacro(misSegmentationThresholdUpdatedCore , misEvent, double);
igstkLoadedEventMacro(misSet3DModelNameCore, misEvent, std::string);

//igstkLoadedEventMacro(misShowLowerthresholdInGUI,misGUIEvent,std::string);
//igstkLoadedEventMacro(misShowUpperthresholdInGUI,misGUIEvent,std::string);
//igstkLoadedEventMacro(misShowthresholdInGUI,misGUIEvent,double);
igstkLoadedEventMacro(misSegmentationSetObjectColor,misEvent,misColorStruct);
//JHB
//igstkLoadedEventMacro(misSetNewObjectName,misEvent,std::string);

//itkEventMacro(CancelSegmentation,misEvent);

//igstkLoadedEventMacro(misSegmentationOperatingModeChanged,misGUIEvent,bool);

//igstkLoadedEventMacro(misSetSilder,misGUIEvent,int);

//skin event
//itkEventMacro(misStartSkinSegmentation,misGUIEvent);
//igstkLoadedEventMacro(misSkinSetUppThr,misGUIEvent,double);
//igstkLoadedEventMacro(misSkinSetlowThr,misGUIEvent,double);
//igstkLoadedEventMacro(misTypeOfModel,misGUIEvent,mis3DModelTypes);
//itkEventMacro(misSkinAccept,misGUIEvent);
//itkEventMacro(misSkinDeny,misGUIEvent);
//create composie gui events:

#pragma warning (pop)

#endif

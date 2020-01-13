#pragma once

#include "misEvent.h"
#include "misGuiStructures.h"
#include "misPackageViewingItemsStrct.h"
#include "misRegistrationStrcts.h"
#include "misSTRCT.h"
#include "misTrackingManagerEnums.h"
#include "misTrackingManagerTypes.h"
#include "misTrackingToolStateReport.h"
#include "SurfaceRegistrationDataStrct.h"

#pragma warning (push)
#pragma warning (disable : 4800)

#define   UNINITILZEDTHRESHOLDVALUE -10000000

struct   misISoSurfacePolyData
{
	misISoSurfacePolyData()
	{
		thresholdValue = UNINITILZEDTHRESHOLDVALUE;
		m_poly = NULL;
	}
	double thresholdValue;
	vtkPolyData*  m_poly;
};

struct   misISoSurfaceMutex
{
	itk::MutexLock::Pointer  m_Mutex;
};

igstkLoadedEventMacro( misUpdateRegistrationStatusEventCore, misEvent,bool);
igstkLoadedEventMacro( misRegistrationLandmarkSelectionIDCore, misEvent,int);

igstkLoadedEventMacro( misRegistartionDeleteTrackerPointCore,misEvent,int);
igstkLoadedEventMacro( misRegistrationLandmarkSelectionListUpdateCore, misEvent, std::vector<mislandMarkPosAndStatusStr>);

//igstkLoadedEventMacro( misChangeToolStatusEventCore,		misEvent,		misToolPositionDataListTypdef);
igstkLoadedEventMacro( misRegistrationLandmarkRegistrationListUpdateCore, misEvent, std::vector<mislandMarkPosAndStatusStr>);
itkEventMacro( misResetRegistrationCore, misEvent);

igstkLoadedEventMacro( misRegistrationResultEventCore,misEvent,RegistrationResultStr );
itkEventMacro(RequestConnectTrackerFromDifferrentSubTabEventCore, misEvent);

igstkLoadedEventMacro( misRefrenceToolNameUsedForRegEventCore,misEvent,std::string); 
igstkLoadedEventMacro( misTargetRegistrationErrorEventCore,misEvent,TREStrct); 

igstkLoadedEventMacro(landmarkselectionPointsEventCore,misEvent,int);
igstkLoadedEventMacro(landmarkRegistrationPointsEventCore,misEvent,int);
igstkLoadedEventMacro( misRegistartionDeleteLandMarkCore,misEvent,int);
itkEventMacro( misStratRegistrationEventCore, misEvent);
igstkLoadedEventMacro( misLandmarkRegistartionTabChangeEventCore,misEvent,SubTabSelection);
itkEventMacro( misSetRegistrationPointRequestCore, misEvent) ;
igstkLoadedEventMacro( misPackageListUpdateEventCore,misEvent,PackageViewingListTypedef);
igstkLoadedEventMacro( misSurfaceRegistrationDatasEventCore,misEvent,SurfaceRegistrationDataStrct);
igstkLoadedEventMacro(misSetPackageUIDToGUIEventCore, misEvent,misUID);
igstkLoadedEventMacro(UpdateAutomaticCaptureLandmarkTimeEventCore,misEvent, double );


#pragma warning (pop)

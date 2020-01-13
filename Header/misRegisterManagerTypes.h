#pragma once

#include "misDataManagerTypes.h"
#include "misEvent.h"
#include "misGUITypes.h"
#include "misMacros.h"
#include "misRegistrationEnums.h"
#include "misStrctDicomIO.h"
#include "misitkTypdef.h"

igstkLoadedEventMacro( misLandMarkListIDSelectionEvent,misEvent,int); // id of list
igstkLoadedEventMacro( misLandMarkListIDSetEvent,misEvent,int); // id in the  list
igstkLoadedEventMacro( misLandMarkListIDCancelEvent,misEvent,int); // id in the  list


igstkLoadedEventMacro( misLandMarkLoaded,misEvent,int);

//itkEventMacro( misResetAllCapturedPoint, misEvent);

igstkLoadedEventMacro( misSetTrackingStateInLnadMarkRegistrationCore,misEvent,CurrentSubSequenseStateStrct); // id of list
//igstkLoadedEventMacro( misLandmarkRegistartionTabChangeEvent,misEvent,SubTabSelection);



//struct misLandMarksDataStr
//{
//	misItkPointType PositionInFixedImage;
//	misItkPointType PositionMovablePoint; // it comes from from capturing point or select in the second Image
//	misItkPointType PositionMovablePointAfterRegistration;
//	//misItkPointType PositionEndLine;
//
//	LandmarkStatus     StatusPositionInImage;
//	//LandmarkStatus     StatusPositionEndLine;
//	LandmarkStatus     StatusPositionCaptured;
//
//	double             error;
//	int                AttemptForCaturing;
//	     
//
//	void ClearFixedPoint(void)
//	{
//		PositionInFixedImage[0] = -1;
//		PositionInFixedImage[1] = -1;
//		PositionInFixedImage[2] = -1;
//		StatusPositionInImage  = InvalidPoint;
//	};
//
//	void ClearMovablePoint(void)
//	{
//		PositionMovablePoint[0] = -1;
//		PositionMovablePoint[1] = -1;
//		PositionMovablePoint[2] = -1;
//
//		PositionMovablePointAfterRegistration[0] = -1;
//		PositionMovablePointAfterRegistration[1] = -1;
//		PositionMovablePointAfterRegistration[2] = -1;
//
//		if (misLandmarkBasedRegistrationType::imageToPatientRegistration == landmarkType)
//		{
//			if (ValidPoint == StatusPositionInImage )
//			{
//				StatusPositionCaptured = InvalidPoint; // it must be inactive while the corresponded image point is not valid
//			}
//			else if (InvalidPoint == StatusPositionInImage )
//			{
//               StatusPositionCaptured = InactivePoint; // it must be inactive while the corresponded image point is not valid
//			}
//			
//		}
//		else
//		{
//			StatusPositionCaptured = InvalidPoint; // it must be inactive while the corresponded image point is not valid
//		}
//		
//		error = -1;
//		AttemptForCaturing = 0;
//	};
//
//	void ClearAll(void)
//	{
//        this->ClearFixedPoint();      
//		this->ClearMovablePoint();	
//	};
//
//	misLandMarksDataStr(misLandmarkBasedRegistrationType type)
//	{
//		landmarkType = type;
//		this->ClearAll();
//	};
//
//	void SetLandmarkType(misLandmarkBasedRegistrationType type)
//	{
//      landmarkType = type;
//	};
//
//private:
//	misLandmarkBasedRegistrationType landmarkType; 
//};
//typedef std::vector<misLandMarksDataStr>  misLandMarkDataListType;


struct misSurfaceLandMarksDataStr
{
	misItkPointType PositionCaptured;
	misItkPointType PositionCapturedAfterRegistration;


	double             error;

	void Clear(void)
	{
		PositionCaptured[0] = -1;
		PositionCaptured[1] = -1;
		PositionCaptured[2] = -1;

		PositionCapturedAfterRegistration[0] = -1;
		PositionCapturedAfterRegistration[1] = -1;
		PositionCapturedAfterRegistration[2] = -1;

		error = -1;
	};

	misSurfaceLandMarksDataStr()
	{
		this->Clear();
	};


};
typedef std::vector<misSurfaceLandMarksDataStr>  misSurfaceLandMarkListType;



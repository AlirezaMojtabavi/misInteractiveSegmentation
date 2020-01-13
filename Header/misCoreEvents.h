#pragma once

#include "PlanIndicators.h"
#include "VirtualKeyStruct.h"
#include "misDataProdecureEnum.h"
#include "misEnums.h"
#include "misEvent.h"
#include "misGUITypes.h"
#include "misGuiStructures.h"
#include "misImageIndexData.h"
#include "misPackageViewingItemsStrct.h"
#include "misPairLandmarkStr.h"
#include "misPlanSTRCT.h"
#include "misShowBoardMessageEventPayload.h"
#include "misSolutionProperty.h"
#include "misSoundAlertTypesNative.h"
#include "misStrctDicomIO.h"
#include "misTransformContainer.h"
#include "misWaitingBarStringsStruct.h"
#include "misWindowsLayout.h"
#include "voreen/misCroppingDirectionInVR.h"
#include "misImageContainedPolyDataStructs.h"
#include "VisualizationGeneralTypes.h"
#include "ILicenseTimeValidator.h"
#include "misVolumeViewingTypes.h"
#include "ProgressBarStatus.h"

class  vtkTransform;

#pragma warning (push)
#pragma warning (disable : 4800)	// IGSTK crap
#pragma warning (disable : 4275)	// IGSTK crap

class  misControlEvent: public misEvent { 
public: 
	typedef misControlEvent Self; 
	typedef misEvent Superclass; 

	misControlEvent() 
	{
		this->m_cascade=true;
		this->m_Proccessed=false;
		this->m_SubTab="firstSubTab";
	} 

	virtual ~misControlEvent() {} 
	virtual const char * GetEventName() const { return "misControlEvent"; } 
	virtual bool CheckEvent(const ::itk::EventObject* e) const 
	{ return dynamic_cast<const Self*>(e); } 
	virtual ::itk::EventObject* MakeObject() const 
	{ return new Self; } 
	misControlEvent(const Self &s) :misEvent(s){}; 
	std::string GetControlName()
	{
		return m_controlName; 
	}
	void SetControlName(std::string name)
	{
		this->m_controlName=name;
	}

private: 
	void operator=(const Self&); 
	std::string m_controlName;

};
//////////
igstkLoadedEventMacro(misPackageListEventCore, misEvent ,PackageViewingListTypedef);
igstkLoadedEventMacro(misCompletetreeViewListEventCore , misEvent, PackageViewingListTypedef);
igstkLoadedEventMacro(misNewCompositePackageStrctEventCore, misEvent ,PackageViewingListTypedef);
igstkLoadedEventMacro(misSendWarningMessageToCompositeEventCore, misEvent , std::string);
igstkLoadedEventMacro(misSendImageAnd3DModelSettingPropertiesEventCore, misEvent, misImageAnd3DModelPropertiesSettingStrct);
igstkLoadedEventMacro(misSelectedPackageEventCore, misEvent, misUID);
igstkLoadedEventMacro(misSelectedPlanEventCore, misEvent, misUID);
igstkLoadedEventMacro(misUpdatePlanIndicatorsCore, misEvent, parcast::PlanIndicators);
igstkLoadedEventMacro(misUpdatePlanColorCore, misEvent, misColorStruct);
// old must remove
//igstkLoadedEventMacro(  misUpdatePackageListCore, misEvent ,PackageViewingListTypedef);

// Home

igstkLoadedEventMacro(UpdateSolutionUIDEventCore, misEvent,misUID);
igstkLoadedEventMacro(UpdateSolutionsListEventCore, misEvent,std::vector<misSolutionProperty>);
igstkLoadedEventMacro(misPatientUploadingStatusInGUICore,misEvent, bool);
igstkLoadedEventMacro(LicenseValidityEventCore, misEvent,bool);
igstkLoadedEventMacro(LicenseTimeValidityEventCore, misEvent, parcast::LicenceTimeState);
igstkLoadedEventMacro(LicenseTimeRemainingEventCore, misEvent, SYSTEMTIME);

//====================================================================================================
igstkLoadedEventMacro(misUpdateMainGUIStateEventCore,misEvent, TabAbstractStateListTypdef);

igstkLoadedEventMacro(misShowLoadedSeriInGUICore,misEvent,ImageViewingListTypedef);
igstkLoadedEventMacro(misShowAcceptedImagesInGUICore,misEvent,ImageViewingListTypedef);
igstkLoadedEventMacro( misloadedDicomListEventCore, misEvent,ImageViewingListTypedef );

igstkLoadedEventMacro( misPackageListUpdateEventDataSelection,misEvent,PackageViewingListTypedef);
igstkLoadedEventMacro( misImageListUpdateEvent,misEvent,PackageViewingListTypedef);
//igstkLoadedEventMacro(misShowPackageInCompositeGUICore,misEvent,PackageViewingListTypedef);
//igstkLoadedEventMacro(misShowLoadedSeriInSegmentationGUICore,misEvent,PackageViewingListTypedef);
igstkLoadedEventMacro( misImageListUpdateEventCore,misEvent,PackageViewingListTypedef);
igstkLoadedEventMacro( misSelectedNodeInTreeEventCore,misEvent,ObjectInformationStrct);



igstkLoadedEventMacro(misShowLoadedSeriInCorrelationGUICore,misEvent,ImageCorrelationViewingListTypedef);
itkEventMacro( misAskForThisPackageTypeEventCore,misEvent);


itkEventMacro( misStartCorrelationEvent, misEvent);

igstkLoadedEventMacro(misSendPackageValidityToSurfaceEventCore , misEvent , bool);

//===============mian   superclasssess for  Events===========================

itkEventMacro( misDataSetManagerEvent,misEvent );
igstkLoadedEventMacro( misRegistrationDoneEventCore, misEvent,misTransformContainer);
igstkLoadedEventMacro( misSendVolumeTypeEventCore, misEvent,misVolumeViewingTypes);
igstkLoadedEventMacro( misSendSliderValueEventCore, misEvent, misSliderStrc);
igstkLoadedEventMacro(misSendImageModalityEventCore, misEvent, misImageDataModality);
//==============================================================================



igstkLoadedEventMacro( ImportImageEvent, misEvent,   std::string ) ;
igstkLoadedEventMacro( misAddRegistrationModel, misEvent,   std::string) ;



//====================================================================

// call from next and back button
itkEventMacro( misSelectNextSubTabButton_Event, misEvent) ;
itkEventMacro( misSelectBackSubTabButton_Event, misEvent) ;

itkEventMacro( RequestUpdateMainMenu, misEvent) ;
//igstkLoadedEventMacro( misLandmarkRegistartionTabChangeEvent,misEvent,SubTabSelection);

//=====================================================================

struct simpleSliderData
{
	int currentRendererIndex;
	int  sliderValueChange;
};
igstkLoadedEventMacro( misSliderChangedEventToSubSeq,misEvent,simpleSliderData);

igstkLoadedEventMacro( misSubSequenceStatusEvent, misEvent,   CurrentSubSequenseStateStrct) ;
//==========================================================================
igstkLoadedEventMacro( misErrorEvent,			misEvent, std::string);



igstkLoadedEventMacro( misSetSliderInfoEventCore,misEvent,misSliderStrc);
igstkLoadedEventMacro(misSetSelectedImageIndexEventCore, misEvent, int);
igstkLoadedEventMacro(misCurrentSliceChangedCore,misEvent,sliderInfoStruct);
igstkLoadedEventMacro(misDispatcherOrientationCore, misEvent,IMAGEORIENTATION);

#pragma region dataProcedure

#pragma region PacsEvents
//Added by -M.A-
//======================pacs events
igstkLoadedEventMacro(misPacsEventCore, misEvent, std::string);


//////////////////////////////////////
#pragma  endregion

igstkLoadedEventMacro(misVRThresholdSliderValueEventCore,misEvent,double);
igstkLoadedEventMacro(misChangeThresholdSliderRangeEventCore, misEvent, misSliderStrc);

igstkLoadedEventMacro(misUpdateFaceInformationEventCore,misEvent,faceInformationListTypdef);
igstkLoadedEventMacro(misImageProblemReportEventCore,misEvent, std::string);

igstkLoadedEventMacro( misOpenWaitingBarEventCore, misEvent,WaitingBarStringsStr );
#define OpenProgressBar(TITLE,STATUS)\
	misOpenWaitingBarEventCore evOpen;\
	evOpen.SetSequenceName(this->m_SequenceName);\
	evOpen.SetSubTab(this->m_SubsequenceName);\
	WaitingBarStringsStr waitingBarString;\
	waitingBarString.title=TITLE;\
	waitingBarString.status = STATUS;\
	evOpen.Set(waitingBarString);\
	this->InvokeEvent(evOpen);
igstkLoadedEventMacro( misOpenNonthreadingWaitingBarEventCore, misEvent,WaitingBarStringsStr );
#define OpenNonthreadingProgressBar(TITLE,STATUS)\
	misOpenNonthreadingWaitingBarEventCore evOpen;\
	evOpen.SetSequenceName(this->m_SequenceName);\
	evOpen.SetSubTab(this->m_SubsequenceName);\
	WaitingBarStringsStr waitingBarString;\
	waitingBarString.title=TITLE;\
	waitingBarString.status = STATUS;\
	evOpen.Set(waitingBarString);\
	this->InvokeEvent(evOpen);

igstkLoadedEventMacro( misUpdateWaitingBarValueEventCore, misEvent,double );
igstkLoadedEventMacro( misUpdateNonthreadingWaitingBarValueEventCore, misEvent,double );
itkEventMacro ( misCloseWaitingbarEventCore,misEvent);
#define CloseCurrentProgressBar()\
misCloseWaitingbarEventCore evClose;\
evClose.SetSequenceName(this->m_SequenceName);\
evClose.SetSubTab(this->m_SubsequenceName);\
this->InvokeEvent(evClose);
itkEventMacro (misCloseNonthreadingWaitingbarEventCore, misEvent);
#define CloseCurrentNonthreadingProgressBar()\
	misCloseNonthreadingWaitingbarEventCore evClose;\
	evClose.SetSequenceName(this->m_SequenceName);\
	evClose.SetSubTab(this->m_SubsequenceName);\
	this->InvokeEvent(evClose);
igstkLoadedEventMacro(misAskForUploadingWithDifficultiesEventCore,misEvent,misImgeProblemList);
igstkLoadedEventMacro(misTreeviewSerieClickedCore,misEvent,misImageIndexData);

//igstkLoadedEventMacro(misDicomDirRead,misEvent, std::string);
 igstkLoadedEventMacro( misDicomTreeListEventCore, misEvent, PatientsContainerViewingTypdef);
igstkLoadedEventMacro( misLoadedSeriesSelectedCore, misEvent, bool );
igstkLoadedEventMacro( misUpdateDicomPropertiesEventCore,  misEvent, misDicomDataViewingProperties);
//igstkLoadedEventMacro( misSetPatientPropertiesCore, misEvent,misPatientProperties );

igstkLoadedEventMacro(misDicomDirReadCore,misEvent, std::string);

igstkLoadedEventMacro( misSetPatientPropertiesEventCore,        misEvent, misPatientProperties );
igstkLoadedEventMacro( misRequestSetPatientPropertiesEventCore, misEvent, misPatientProperties );

igstkLoadedEventMacro( misCorrelationWarningEventCore, misEvent , misCorrelationWarningState);
igstkLoadedEventMacro(misShowLandmarkInGUICore , misEvent , misPairLandMarkStatusListType);
igstkLoadedEventMacro(misAutoCorrelationProgressBarStateCore , misEvent , ProgressBarStatus);
igstkLoadedEventMacro(misAutoCorrelationProgressBarValueCore, misEvent, double);
igstkLoadedEventMacro(misSendISCorrelationExistedEventCore , misEvent , bool);
itkEventMacro(misResetUIDsInGUICore, misEvent);
itkEventMacro(misRequestToChangeStateButtonCore, misEvent);
#pragma endregion dataProcedure




#pragma region Segmentation



igstkLoadedEventMacro(misShowObjectVolumeTextInGUICore,misEvent,double);
igstkLoadedEventMacro(misShowBGSeedInGUICore,misEvent,misSimplePointListType);
igstkLoadedEventMacro(misShowFGSeedInGUICore,misEvent,misSimplePointListType);

igstkLoadedEventMacro(misSetNormalizedVolumeThresholdEventCore,misEvent,double);

igstkLoadedEventMacro(misShowObjectPropertiesInGUICore , misEvent, misShort3DModelViewingStrct);

igstkLoadedEventMacro(misHeadRestStatusCore,misEvent,bool);
#pragma endregion Segmentation


#pragma region Planning
// itkEventMacro( misDeletePlanCore, misEvent);
// 
// itkEventMacro( misDeleteEntryPointbuttonCore, misEvent);
// itkEventMacro( misDeleteTargetPointbuttonCore, misEvent);
igstkLoadedEventMacro(misSendLastPointInfoEventCore, misEvent, double);
igstkLoadedEventMacro(misPlanFlowEndEventCore , misEvent, misCineDirection);
igstkLoadedEventMacro(UpdateIndicatorValueCore, misEvent, ScrewPlanPropertyIndicator);
#pragma endregion Planning





itkEventMacro( misFootSwitchOnEventCore,misEvent) ;

igstkLoadedEventMacro( misCalibrationTimerOutputEvent,	misEvent,		int );
itkEventMacro(misShowNavigationListEventCore, misEvent);

itkEventMacro(misInActiveNextSubTabEventCore,misEvent);
itkEventMacro(misSelectNextSubTabEventCore,misEvent);

igstkLoadedEventMacro( misSetSliderPropertyCore, misEvent,double );
igstkLoadedEventMacro(misSetNormalizedSurfaceThresholdEventCore,misEvent,double);




itkEventMacro(misEnableSeedBasedSegmentationWindowEvent,misEvent);
itkEventMacro(misEnableThresholdBasedSegmentationWindowEvent,misEvent);

itkEventMacro(misSelectPreviousSubTabEventCore,misEvent);
igstkLoadedEventMacro( misCaptureTrackerCore, misEvent,int);

igstkLoadedEventMacro(misSetTransformEventCore, misEvent,misTransformContainer);

//=====misGEneralToolbar=====//
igstkLoadedEventMacro( misChangeButtomStateCore,misEvent,misGeneralToolbarState);
//igstkLoadedEventMacro(UpdateZoomGUIStatusEventCore, misEvent, misZoomState);
igstkLoadedEventMacro(misSoundAlertRequestEventCore,misEvent,misSoundAlertTypesNative );
 //===== this event is applied after Rightclick in order to reset the scene =========//
 itkEventMacro(misResetAutoMeasurmentButtomCore, misEvent);


 igstkLoadedEventMacro(UpdateSnapShotFolderAddressEventCore,misEvent,  std::string);
 igstkLoadedEventMacro(misVideoRecordingAddressEventCore,misEvent, std::string );
  

 ///////////////////   Navigation
 igstkLoadedEventMacro(Update3DDistanceGUIStateEventCore,misEvent, LandmarkStateListTypdef);
 igstkLoadedEventMacro(UpdateNoFlyZoneInformationCore, misEvent, std::vector<PropertiesOfPixelInImageType>);
 igstkLoadedEventMacro(UpdateNearesetLandmarkGUIStateEventCore, misEvent, LandmarkStateListTypdef);
 igstkLoadedEventMacro(SetAutoPilotButtonsEnableEventCore,misEvent, bool);
 igstkLoadedEventMacro(UpdateTargetPointGUIStateEventCore , misEvent, LandmarkStateListTypdef);
 igstkLoadedEventMacro(ShowCutDirectionGridEventCore , misEvent , bool);
 igstkLoadedEventMacro(UpdateGUICroppingDirectionEventCore,misEvent, misCroppingDirectionInVR );
 itkEventMacro(misPackageSelectenStatusEventCore, misEvent);
 igstkLoadedEventMacro(misForceViewersToFreezEventCore, misEvent,bool);
 igstkLoadedEventMacro(misUpdateLayouEventCore, misEvent, misWindowsLayout);
 itkEventMacro(misClearLayoutEventCore, misEvent);
 ////////////// VirtualKey
 igstkLoadedEventMacro(misVirtualKeyPlateDisplayEventCore, misEvent, bool);
 igstkLoadedEventMacro(misVirtualKeyButtonsEventCore, misEvent, VirtualKeyCommand);

 igstkLoadedEventMacro(misSetViewTypesEventCore, misEvent, std::vector<std::string>);
 igstkLoadedEventMacro(misShowBoardMessageCore, misEvent, GuiBoardMessage);

#pragma warning (pop)



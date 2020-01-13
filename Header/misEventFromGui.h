#pragma once

#include "PlanIndicators.h"
#include "TrackingReportData.h"
#include "misCalibrationEnums.h"
#include "misDataProdecureEnum.h"
#include "misEnums.h"
#include "misFGBGSeeds.h"
#include "misGuiEvent.h"
#include "misGuiStructures.h"
#include "misImageIndexData.h"
#include "misLoadedEventMacro.h"
#include "misPackageViewingItemsStrct.h"
#include "misPairLandmarkStr.h"
#include "misPlanSTRCT.h"
#include "misRobotStrct.h"
#include "misShowBoardMessageEventPayload.h"
#include "misSolutionProperty.h"
#include "misStrctConnectOption.h"
#include "misStrctDataEssantialToExport.h"
#include "misStrctDicomIO.h"
#include "misStrctPatientData.h"
#include "misStrctToolAdd.h"
#include "misToolProperties.h"
#include "misTrackingManagerTypes.h"
#include "misTrackingStateReport.h"
#include "misTypes.h"
#include "misWaitingBarStringsStruct.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"
#include "VirtualKeyStruct.h"
#include "misguitypes.h"
#include "ApproachAndModelInformationStrct.h"
#include "SurfaceRegistrationDataStrct.h"
#include "misRegistrationGuiEvents.h"
#include "misRegistrationStrcts.h"
#include "VisualizationGeneralTypes.h"
#include "voreen\misCroppingDirectionInVR.h"
#include "ILicenseTimeValidator.h"
#include "BiopsyPlanInformation.h"


struct CalibrationTipOffsetData
{
	double X;
	double Y;
	double Z;
	std::string partNumber;
	//misToolBodyType toolBodyType;
	misToolApplicationType toolBodyType;
};

misGUIEventMacro(misApplicationLoopStarted, misGUIEvent);
misGUIEventMacro(misTaskDoneOnSubTabLeave, misGUIEvent);
misGUIEventMacro(misTabSelectionChange, misGUIEvent);
misGUIEventMacro(misChangeToStandardLayoutEvent, misGUIEvent);
misGUIEventMacro(misTakeSnapShotEvent, misGUIEvent);
misGUIEventMacro(misResetApplicationEvent, misGUIEvent);
misGUIEventMacro(misClosePropertyInGUI, misGUIEvent);
misGUIEventMacro(misPulseEvent, misGUIEvent);
misGUIEventMacro(misToolStatusAccepted, misGUIEvent);
misGUIEventMacro(misNextCalibrationStepEvent, misGUIEvent);
misGUIEventMacro(misPreviousCalibrationStepEvent, misGUIEvent);
misGUIEventMacro(misNeedCalibrationEvent, misGUIEvent);
misGUIEventMacro(misNeedOrientationCalibrationEvent, misGUIEvent);
misGUIEventMacro(misResetCalibrationEvent, misGUIEvent);
misGUIEventMacro(misResetOrientationCalibrationEvent, misGUIEvent);
misGUIEventMacro(misTrackingViewerEvent, misGUIEvent);
misGUIEventMacro(misNewDetectedToolEvent, misGUIEvent);
misGUIEventMacro(misDenyToolStatus, misGUIEvent);
misGUIEventMacro(misResetToolAccuracySubSeq, misGUIEvent);
misLoadedEventMacro(misAutomaticCalibrationEvent, misGUIEvent, bool);

// home 
misLoadedEventMacro(UpdateSolutionsListEvent, misGUIEvent, std::vector<misSolutionProperty>);
misLoadedEventMacro(UpdateSolutionUIDEvent, misGUIEvent, misUID);
misLoadedEventMacro(LicenseValidityEvent, misGUIEvent, bool);
misLoadedEventMacro(LicenseTimeValidityEvent, misGUIEvent, parcast::LicenceTimeState);
misLoadedEventMacro(LicenseTimeRemainingEvent, misGUIEvent, SYSTEMTIME);

misLoadedEventMacro(misVirtualKeyPlateDisplayEvent, misGUIEvent, bool);
misLoadedEventMacro(misVirtualKeyButtonsEvent, misGUIEvent, VirtualKeyCommand);
misLoadedEventMacro(misSetViewTypesEvent, misGUIEvent, std::vector<std::string>);
misLoadedEventMacro(misPatientUploadingStatusInGUI, misGUIEvent, bool);
misLoadedEventMacro(misShowLoadedSeriInGUI, misGUIEvent, ImageViewingListTypedef);
misLoadedEventMacro(misShowAcceptedImagesInGUI, misGUIEvent, ImageViewingListTypedef);
misLoadedEventMacro(misloadedDicomListEvent, misGUIEvent, ImageViewingListTypedef);
misLoadedEventMacro(misSelectedNodeInTreeEvent, misGUIEvent, ObjectInformationStrct);
misGUIEventMacro(misDisableAllSlidersEvent, misGUIEvent);
misLoadedEventMacro(misPackageListEvent, misGUIEvent, PackageViewingListTypedef);
misLoadedEventMacro(misCompletetreeViewListEvent, misGUIEvent, PackageViewingListTypedef);
misLoadedEventMacro(misNewCompositePackageStrctEvent, misGUIEvent, PackageViewingListTypedef);
misLoadedEventMacro(misSendWarningMessageToCompositeEvent, misGUIEvent, std::string);
misLoadedEventMacro(misSendImageSettingPropertiesEvent, misGUIEvent, misImageAnd3DModelPropertiesSettingStrct);
misLoadedEventMacro(misSelectedPackageEvent, misGUIEvent, misUID);
misLoadedEventMacro(misSelectedPlanEvent, misGUIEvent, misUID);
misLoadedEventMacro(misUpdatePlanIndicatorsEvent, misGUIEvent, parcast::PlanIndicators);
misLoadedEventMacro(misShowLoadedSeriInCorrelationGUI, misGUIEvent, ImageCorrelationViewingListTypedef);
misGUIEventMacro(misAskForThisPackageTypeEvent, misGUIEvent);
misLoadedEventMacro(misSendPackageValidityToSurfaceEvent, misGUIEvent, bool);
misLoadedEventMacro(mis3DPanEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(mis3DRotateEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(DeleteSolutionEvent, misGUIEvent, std::string);
misLoadedEventMacro(misAxialViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misCoronalViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misSagitalViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misAnteriorViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misPosteriorViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misSupreriorViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misInferiorViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misLeftViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misRightViewEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misSliderEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misImageCorrelationSliderEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misZoomEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misResetContrastEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misAllResetEvent, misGUIEvent, SingleWrapperStrct);
misLoadedEventMacro(misContrastEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misPresetContrastEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misAddToolListEvent, misGUIEvent, misToolPropertiesListTypdef);
misLoadedEventMacro(misDicomDirRead, misGUIEvent, std::string);
misLoadedEventMacro(misLoadedSeriClick, misGUIEvent, misUID);
misLoadedEventMacro(misPatientTreeDeleteClick, misGUIEvent, misUID);
misLoadedEventMacro(misTreeviewImageClicked, misGUIEvent, misImageIndexData);
misLoadedEventMacro(misTreeviewPatientClicked, misGUIEvent, misImageIndexData);
misLoadedEventMacro(misTreeviewSerieClicked, misGUIEvent, misImageIndexData);
misLoadedEventMacro(misTreeviewStudyClicked, misGUIEvent, misImageIndexData);
misLoadedEventMacro(misPatientTreePropClick, misGUIEvent, misImageViewingItemsStruct);
misLoadedEventMacro(misEditButtonClicked, misGUIEvent, misPatientProperties);
misGUIEventMacro(misConnectTrackerEvent, misGUIEvent);

#pragma region Planining
misLoadedEventMacro(misAcceptAllPlan, misGUIEvent, BiopsyPlanInformation);
misGUIEventMacro(misCreatenewApproach, misGUIEvent);
misLoadedEventMacro(misEntryPoint, misGUIEvent, std::string);
misLoadedEventMacro(misTargetPoint, misGUIEvent, std::string);
misGUIEventMacro(misModifyTargetPoint, misGUIEvent);
misGUIEventMacro(misDeleteTargetPoint, misGUIEvent);
misGUIEventMacro(misModifyEntryPoint, misGUIEvent);
misGUIEventMacro(misDeleteEntryPoint, misGUIEvent);
misGUIEventMacro(misDenyAllPlan, misGUIEvent);
misLoadedEventMacro(misPlanningColorChanged, misGUIEvent, misColorStruct);
misLoadedEventMacro(misSendLastPointInfoEvent, misGUIEvent, double);
misGUIEventMacro(misPrevPlanStopRequest, misGUIEvent);
misLoadedEventMacro(misPrevPlanButtonClicked, misGUIEvent, misCineDirection);
misLoadedEventMacro(misPlanFlowSliderValue, misGUIEvent, double);
misLoadedEventMacro(misPlanFlowEndEvent, misGUIEvent, misCineDirection);
#pragma endregion Planining

misGUIEventMacro(misResetTrackerEvent, misGUIEvent);
misGUIEventMacro(CancelBrowseAndAalysisFolder, misGUIEvent);
misGUIEventMacro(CancelReadingSerie, misGUIEvent);
misGUIEventMacro(misUpdateToolListEvent, misGUIEvent);
misGUIEventMacro(misShowNavigationListEvent, misGUIEvent);
misLoadedEventMacro(misKeyEvent, misGUIEvent, char);
misLoadedEventMacro(misNavigationPackageDataSelectedEvent, misGUIEvent, std::string);
misLoadedEventMacro(misForcedDataSelectedEvent, misGUIEvent, std::string);
misLoadedEventMacro(UpdateGUICroppingDirectionEvent, misGUIEvent, misCroppingDirectionInVR);

#pragma region Registration
misLoadedEventMacro(landmarkRegistrationPointsEvent, misGUIEvent, int);
misLoadedEventMacro(misShowBoardMessage, misGUIEvent, GuiBoardMessage);
misGUIEventMacro(misCameraLaserOnEvent, misGUIEvent);
misGUIEventMacro(misCameraLaserOffEvent, misGUIEvent);
misGUIEventMacro(misRequestResetRegistrationEvent, misGUIEvent);
misGUIEventMacro(misSetLandmarkSelectionToInitialState, misGUIEvent);
misLoadedEventMacro(landmarkselectionPointsEvent, misGUIEvent, int);
misLoadedEventMacro(misLandmarkRegistartionTabChangeEvent, misGUIEvent, SubTabSelection);
misLoadedEventMacro(misLandmarkSelectionTabChangeEvent, misGUIEvent, SubTabSelection);
misLoadedEventMacro(misRequestVolumeTypeInRegistration, misGUIEvent, misVolumeViewingTypes);
misGUIEventMacro(misUpdatePreviousRegistrationEvent, misGUIEvent);
misLoadedEventMacro(misLandMarkNumbersEvent, misGUIEvent, int);
misLoadedEventMacro(misCaptureTracker, misGUIEvent, int);
misLoadedEventMacro(misRegistartionDeleteLandMark, misGUIEvent, int);
misLoadedEventMacro(misRegistartionDeleteTrackerPoint, misGUIEvent, int);
misGUIEventMacro(misSetRegistrationPointRequest, misGUIEvent);
misLoadedEventMacro(misTargetRegistrationErrorEvent, misGUIEvent, TREStrct);
misLoadedEventMacro(misTrackingStateReportEvent, misGUIEvent, misTrackingStateReport);
misLoadedEventMacro(misTrackingToolMarkerReportEvent, misGUIEvent, misTrackingToolMarkerReport);
misLoadedEventMacro(misRegistrationResultEvent, misGUIEvent, RegistrationResultStr);
misLoadedEventMacro(misUpdateRegistrationStatusEvent, misGUIEvent, bool);
misGUIEventMacro(misFootSwitchOnEvent, misGUIEvent);
misGUIEventMacro(misFootSwitchOffEvent, misGUIEvent);
misLoadedEventMacro(misRegistrationLandmarkSelectionListUpdate, misGUIEvent, std::vector<mislandMarkPosAndStatusStr>);
misLoadedEventMacro(misSendVolumeTypeEvent, misGUIEvent, misVolumeViewingTypes);
misLoadedEventMacro(misRegistrationLandmarkRegistrationListUpdate, misGUIEvent, std::vector<mislandMarkPosAndStatusStr>);
misLoadedEventMacro(misSendSliderValueEvent, misGUIEvent, misSliderStrc);
misLoadedEventMacro(misSendImageModalityEvent, misGUIEvent, misImageDataModality);
misLoadedEventMacro(misRegistrationLandmarkSelectionID, misGUIEvent, int);
misLoadedEventMacro(misRefrenceToolNameUsedForRegEvent, misGUIEvent, std::string);
misLoadedEventMacro(misSetTrackingStateInOtherTab, misGUIEvent, CurrentSubSequenseStateStrct); // id of list
misGUIEventMacro(misGoToNextLandmarkEvent, misGUIEvent);
misGUIEventMacro(misCalculateSurfaceRegistrationEvent, misGUIEvent);
misGUIEventMacro(misAcceptSurfaceRegistrationEvent, misGUIEvent);
misGUIEventMacro(misResetSurfaceRegistrationEvent, misGUIEvent);
misGUIEventMacro(misCaptureSurfacePointEvent, misGUIEvent);
misGUIEventMacro(misStartCapturingPointForSurfaceRegistrationEvent, misGUIEvent);
misLoadedEventMacro(misSurfaceRegistrationDatasEvent, misGUIEvent, SurfaceRegistrationDataStrct);
misLoadedEventMacro(misSetPackageUIDToGUIEvent, misGUIEvent, misUID);
misLoadedEventMacro(UpdateAutomaticCaptureLandmarkTimeEvent, misGUIEvent, double);
misLoadedEventMacro(UpdateAutomaticCaptureLandmarkSettingEvent, misGUIEvent, double);
#pragma endregion Registration

misLoadedEventMacro(misSetFixedImageIndex, misGUIEvent, misUID);

#pragma region Correlation
misGUIEventMacro(CancelImageCorrelation, misGUIEvent);
misGUIEventMacro(StopImageCorrelation, misGUIEvent);
misLoadedEventMacro(misCorrelatedColorChanged, misGUIEvent, misColorAndUID);
misLoadedEventMacro(misCorrelationOpacityChanged, misGUIEvent, misOpacityAndUID);
misGUIEventMacro(misCorrelationPlaneSwap, misGUIEvent);
misLoadedEventMacro(misCorrelationPatternOverlayChanged, misGUIEvent, enum misCorrelationPatternOverlay);
misLoadedEventMacro(mislandmarkselectionEvent, misGUIEvent, misCorrelationManualRegistrationStructure);
misLoadedEventMacro(misChangeRegistrationModeEvent, misGUIEvent, enum misRegistrationMode);
misGUIEventMacro(misAddEmptyLandmarkEvent, misGUIEvent);
misGUIEventMacro(misDeleteLandmarkEvent, misGUIEvent);
misLoadedEventMacro(misChangeImageSync, misGUIEvent, bool);
misGUIEventMacro(misSwapCorrelatedImages, misGUIEvent);
#pragma endregion Correlation

#pragma region DataProcedure

#pragma region PacsEvents
misLoadedEventMacro(misPacsEvent, misGUIEvent, std::string);
#pragma endregion

misLoadedEventMacro(misPrevSeriIntervalChanged, misGUIEvent, int);
misLoadedEventMacro(misPrevSeriButtonClicked, misGUIEvent, misCineDirection);
//A & P & S & I & R & L Event
misGUIEventMacro(misAnteriorEvent, misGUIEvent);
misGUIEventMacro(misPosteriorEvent, misGUIEvent);
misGUIEventMacro(misSuperiorEvent, misGUIEvent);
misGUIEventMacro(misInferiorEvent, misGUIEvent);
misGUIEventMacro(misRightEvent, misGUIEvent);
misGUIEventMacro(misLeftEvent, misGUIEvent);
misGUIEventMacro(misStByStButtonClicked, misGUIEvent);
misGUIEventMacro(misCalculateCorrelationStartEvent, misGUIEvent);
misGUIEventMacro(misReCalculateButtonClicked, misGUIEvent);
misGUIEventMacro(misCorrelationAcceptButtonClicked, misGUIEvent);
misGUIEventMacro(misCorrelationDenyButtonClicked, misGUIEvent);
misLoadedEventMacro(misSetMovingImageIndex, misGUIEvent, misUID);
misGUIEventMacro(misCorrelationTreeViewClicked, misGUIEvent);
misGUIEventMacro(misPrevSeriStopRequest, misGUIEvent);
misGUIEventMacro(misPreviewImageButtonClicked, misGUIEvent);
misGUIEventMacro(misUploadSerie, misGUIEvent);
misGUIEventMacro(misAcceptButtonClicked, misGUIEvent);
misGUIEventMacro(misDenyButtonClicked, misGUIEvent);
misGUIEventMacro(misResetButtonClicked, misGUIEvent);
misGUIEventMacro(misTestButtonClicked, misGUIEvent);
misLoadedEventMacro(misChangeOrientationInSameViewPort, misGUIEvent, IMAGEORIENTATION);
misLoadedEventMacro(misChangeViewPort, misGUIEvent, ViewPortType);
misLoadedEventMacro(misFreeTranslation, misGUIEvent, FusionMoveDirectionStrct);
misLoadedEventMacro(misFreeRotation, misGUIEvent, FusionRotateDirectionStrct);
misLoadedEventMacro(misFreeSliceMovement, misGUIEvent, FusionMoveDirectionStrct);
misLoadedEventMacro(misChangeFreeTranslationStep, misGUIEvent, double);
misLoadedEventMacro(misSelectedLayout, misGUIEvent, std::string);
misLoadedEventMacro(misChangeFreeRotationStep, misGUIEvent, double);
misLoadedEventMacro(misChangeFreeMoveSliceStep, misGUIEvent, double);
misLoadedEventMacro(misUpdateFaceInformationEvent, misGUIEvent, faceInformationListTypdef);
misLoadedEventMacro(misSetSelectedImageIndexEvent, misGUIEvent, int);
misLoadedEventMacro(misVRThresholdSliderValueEvent, misGUIEvent, double);
misLoadedEventMacro(misChangeThresholdSliderRangeEvent, misGUIEvent, misSliderStrc);
misLoadedEventMacro(misImageProblemReportEvent, misGUIEvent, std::string);
misLoadedEventMacro(misSetSliderProperty, misGUIEvent, double);
misLoadedEventMacro(misDicomTreeListEvent, misGUIEvent, PatientsContainerViewingTypdef);
misLoadedEventMacro(misLoadedSeriesSelected, misGUIEvent, bool);
misLoadedEventMacro(misAskForUploadingWithDifficultiesEvent, misGUIEvent, misImgeProblemList);
misLoadedEventMacro(misUpdateDicomPropertiesEvent, misGUIEvent, misDicomDataViewingProperties);
misLoadedEventMacro(misSetPatientPropertiesEvent, misGUIEvent, misPatientProperties);
misLoadedEventMacro(misRequestSetPatientPropertiesEvent, misGUIEvent, misPatientProperties);
misLoadedEventMacro(misSet3DModelNameEvent, misGUIEvent, std::string);
misLoadedEventMacro(misCorrelationWarningEvent, misGUIEvent, int);
misLoadedEventMacro(misShowLandmarkInGUI, misGUIEvent, misPairLandMarkStatusListType);
misLoadedEventMacro(misSendISCorrelationExistedEvent, misGUIEvent, bool);
misGUIEventMacro(misResetUIDsInGUI, misGUIEvent);
misGUIEventMacro(misRequestToChangeStateButton, misGUIEvent);
misGUIEventMacro(misSet3DROI, misGUIEvent);
misGUIEventMacro(misRemoveROI, misGUIEvent);
misGUIEventMacro(misAcceptROIEv, misGUIEvent);
#pragma endregion DataProcedure

misGUIEventMacro(AddNewEmptyPointEvent, misGUIEvent);

#pragma region Segmentation
misGUIEventMacro(misStartSegmentation, misGUIEvent);
misLoadedEventMacro(misStartSegmentationSeeds, misGUIEvent, misFGBGSeeds);
misGUIEventMacro(CancelSegmentation, misGUIEvent);
misGUIEventMacro(misSegmentationDeny, misGUIEvent);
misGUIEventMacro(misSegmentationAccept, misGUIEvent);
misGUIEventMacro(misSegmentationColormapAccept, misGUIEvent);
misGUIEventMacro(misSegmentationColormapDeny, misGUIEvent);
misLoadedEventMacro(misSetNormalizedVolumeThresholdEvent, misGUIEvent, double);
misLoadedEventMacro(misSetNormalizedSurfaceThresholdEvent, misGUIEvent, double);
misLoadedEventMacro(misSetNormalizedHeadRestThresholdEvent, misGUIEvent, double);
misGUIEventMacro(misThresholdReset, misGUIEvent);
misLoadedEventMacro(misSetVolumeRenderingThreshold, misGUIEvent, double);
misLoadedEventMacro(misTreeViewAllImagesClicked, misGUIEvent, misUID);
misGUIEventMacro(misAddFGSeedClicked, misGUIEvent);
misGUIEventMacro(misAddToExistedModel, misGUIEvent);
misLoadedEventMacro(misTreeViewPackageClicked, misGUIEvent, misUID);
misLoadedEventMacro(misSegmentedObjectTypeEvent, misGUIEvent, mis3DModelTypes);
misLoadedEventMacro(misSetObjectTransparencyEvent, misGUIEvent, ApproachAndModelOpacityInformation);
misLoadedEventMacro(misSegmentationColorChanged, misGUIEvent, ApproachAndModelColorInformation);
misLoadedEventMacro(misTreeViewSegmentationClicked, misGUIEvent, misUID);
misGUIEventMacro(misDeleteSegmentationSeedsEvent, misGUIEvent);
misGUIEventMacro(misAddBGSeedClicked, misGUIEvent);
misGUIEventMacro(misShowItem, misGUIEvent);
misLoadedEventMacro(misShowMarginRegion, misGUIEvent, bool);
misLoadedEventMacro(misSetMarginValue, misGUIEvent, int);
misLoadedEventMacro(misSetMarginAlarm, misGUIEvent, bool);
#pragma endregion Segmentation

#pragma region CreateComposite
misLoadedEventMacro(misImageTreeViewClicked, misGUIEvent, ImageInformationStrct);
misLoadedEventMacro(misApproachAndModelTreeViewClicked, misGUIEvent, ApproachAndModelInformationStrct);
misLoadedEventMacro(misImageSettingTreeViewClicked, misGUIEvent, ImageInformationStrct);
misLoadedEventMacro(misApproachAndModelSettingTreeViewClicked, misGUIEvent, ApproachAndModelInformationStrct);
misLoadedEventMacro(misImageTreeViewNewCompositeClicked, misGUIEvent, ImageInformationStrct);
misLoadedEventMacro(misApproachAndModelTreeViewNewCompositeClicked, misGUIEvent, ApproachAndModelInformationStrct);
misLoadedEventMacro(misDecisionMakingForCompositeEvent, misGUIEvent, bool);
misGUIEventMacro(misCreateNewCompositeEvent, misGUIEvent);
misGUIEventMacro(misModifyCompositeEvent, misGUIEvent);
misGUIEventMacro(misDeleteCompositePackageEvent, misGUIEvent);
misGUIEventMacro(misDeleteCompositeItemEvent, misGUIEvent);
misGUIEventMacro(misChangePackageEvent, misGUIEvent);
misLoadedEventMacro(misSetItemVisibility2D, misGUIEvent, ApproachAndModelVisibilityInformation);
misLoadedEventMacro(misSetItemVisibility3D, misGUIEvent, ApproachAndModelVisibilityInformation);
misLoadedEventMacro(misChangeImageWindow, misGUIEvent, int);
misLoadedEventMacro(misChangeImageLevel, misGUIEvent, int);
misLoadedEventMacro(misChangeImageOpacity, misGUIEvent, float);
misLoadedEventMacro(misChange3DModelOpacity, misGUIEvent, float);
misLoadedEventMacro(misChangeImageColor, misGUIEvent, misColorStruct);
misLoadedEventMacro(misChange3DModelColor, misGUIEvent, ApproachAndModelColorInformation);
#pragma endregion CreateComposite

misGUIEventMacro(misTerminatedEvent, misGUIEvent);
misGUIEventMacro(misClearAllSolutionsFormDBEvent, misGUIEvent);
misLoadedEventMacro(misExportPatientEvent, misGUIEvent, misStrctDataEssantialToExport);
misLoadedEventMacro(misImportPatientEvent, misGUIEvent, std::string);
misGUIEventMacro(misRequestUpdateSolutionListEvent, misGUIEvent);
misGUIEventMacro(misInActiveNextSubTabEvent, misGUIEvent);
misGUIEventMacro(misSelectNextSubTabEvent, misGUIEvent);
misGUIEventMacro(misSelectPreviousSubTabEvent, misGUIEvent);
misGUIEventMacro(misForceToUploadWithProblemEvent, misGUIEvent);
misLoadedEventMacro(ApplySubSegStatesEventToGUI, misGUIEvent, CurrentSubSequenseStateStrct);
misLoadedEventMacro(misSetSliderInfoEvent, misGUIEvent, misSliderStrc);
misLoadedEventMacro(misShowBGSeedInGUI, misGUIEvent, GUISeedListType);
misLoadedEventMacro(misShowFGSeedInGUI, misGUIEvent, GUISeedListType);
misLoadedEventMacro(misSetNewObjectName, misGUIEvent, std::string);
misLoadedEventMacro(misShowObjectVolumeTextInGUI, misGUIEvent, double);
misGUIEventMacro(misRequestShowLoadedSeriInSegmentationGUI, misGUIEvent);
misLoadedEventMacro(misSliderValueChanged, misGUIEvent, sliderInfoStruct);
misGUIEventMacro(misRequestShowPackageInCompositeGUI, misGUIEvent);
misLoadedEventMacro(misRequestObjectProperty, misGUIEvent, ApproachAndModelInformationStrct);
misGUIEventMacro(misRequestToDeleteSegmentedObject, misGUIEvent);
misLoadedEventMacro(misShowObjectPropertiesInGUI, misGUIEvent, misShort3DModelViewingStrct);
misLoadedEventMacro(misRequestToSetVisibility, misGUIEvent, ApproachAndModelVisibilityInformation);
misLoadedEventMacro(misSegmentationThresholdUpdated, misGUIEvent, double);

#pragma region Tracking
misLoadedEventMacro(misUpdateToolListToGUI, misGUIEvent, misSimpleToolNameListTypdef);
misGUIEventMacro(RequestConnectTrackerFromDifferrentSubTabEvent, misGUIEvent);
misLoadedEventMacro(misAddedToolEvent, misGUIEvent, misStrctToolAdd);
misLoadedEventMacro(misOrientationCalibrationStatus, misGUIEvent, OrientationCalibrationData);
misLoadedEventMacro(misCameraImageUpdate, misGUIEvent, CameraImageData);
misLoadedEventMacro(misValidationStatus, misGUIEvent, ToolValidationStatusData);
misLoadedEventMacro(misDoneToolValidation, misGUIEvent, bool);
misGUIEventMacro(DentalClearVirtualTipTextBox, misGUIEvent);
misGUIEventMacro(misExitCalibration, misGUIEvent);
misGUIEventMacro(misCloseTrackingWindowEvent, misGUIEvent);
misGUIEventMacro(misUpdateRefrence, misGUIEvent);
#pragma endregion Tracking

#pragma region ROI
misGUIEventMacro(misROIActive, misGUIEvent);
misGUIEventMacro(misROIDeactive, misGUIEvent);
misGUIEventMacro(misRedo, misGUIEvent);
#pragma endregion ROI

#pragma  region HeadRest
misGUIEventMacro(misRemoveHeadRestClick, misGUIEvent);
misGUIEventMacro(misRemoveMoreHeadRest, misGUIEvent);
misGUIEventMacro(misRemoveHeadRestSeedDelete, misGUIEvent);
misGUIEventMacro(misResetHeadRest, misGUIEvent);
misGUIEventMacro(misApplyRemoveHeadRest, misGUIEvent);
misGUIEventMacro(misRemoveHeadRestSeedSelection, misGUIEvent);
misGUIEventMacro(misRemoveHeadRestSeedUpdatePosition, misGUIEvent);
misGUIEventMacro(misOkRemoveHeadRest, misGUIEvent);
misGUIEventMacro(misRequestHeadRestStatus, misGUIEvent);
misLoadedEventMacro(misHeadRestStatus, misGUIEvent, bool);
misLoadedEventMacro(misSetNormalizedHeadRestVolumeThresholdEvent, misGUIEvent, double);
#pragma endregion HeadRest

misLoadedEventMacro(misSaveSoloutionEvent, misGUIEvent, misSaveSolutionMode);
misLoadedEventMacro(misUpdateMainGUIStateEvent, misGUIEvent, TabAbstractStateListTypdef);
misLoadedEventMacro(UpdateSnapShotFolderAddressEvent, misGUIEvent, std::string);
misLoadedEventMacro(misVideoRecordingAddressEvent, misGUIEvent, std::string);
misLoadedEventMacro(misSetWaitingBarStatusEvent, misGUIEvent, std::string);
misGUIEventMacro(misCloseWaitingbarEvent, misGUIEvent);
misGUIEventMacro(misCloseNonthreadingWaitingbarEvent, misGUIEvent);
misLoadedEventMacro(misOpenWaitingBarEvent, misGUIEvent, WaitingBarStringsStr);
misLoadedEventMacro(misOpenNonthreadingWaitingBarEvent, misGUIEvent, WaitingBarStringsStr);
misLoadedEventMacro(misUpdateWaitingBarValueEvent, misGUIEvent, double);
misLoadedEventMacro(misUpdateNonthreadingWaitingBarValueEvent, misGUIEvent, double);
misLoadedEventMacro(misDeltetedToolEvent, misGUIEvent, misStrctSimpleToolProperties);
misGUIEventMacro(misRequestResetToolsForOtherTabs, misGUIEvent);
misLoadedEventMacro(misPanModeEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misMeasurmentWidgetEvent, misGUIEvent, wrapperStrct);
misLoadedEventMacro(misMeasurmentWidgetPressedEvent, misGUIEvent, bool);
//=====misGEneralToolbar=====//
misLoadedEventMacro(misChangeButtomState, misGUIEvent, misGeneralToolbarState);
misLoadedEventMacro(misChangeZoomPercentage, misGUIEvent, double);
misGUIEventMacro(misBackToPanStateEvent, misGUIEvent);
misGUIEventMacro(misResetAutoMeasurmentButtom, misGUIEvent);
misLoadedEventMacro(misRobotCommand, misGUIEvent, misRobotCommandStr);
misLoadedEventMacro(misRobotCommandLog, misGUIEvent, std::string);
misLoadedEventMacro(misRobotonnectionEvent, misGUIEvent, misStrctComConnectionOptions);
misGUIEventMacro(misRobotInitialCalibrationEvent, misGUIEvent);
misLoadedEventMacro(misPivotCalibrationProgressBarEvent, misGUIEvent, double);
misLoadedEventMacro(misUpdateLicenseInfo, misGUIEvent, std::string);
misLoadedEventMacro(misRequestCroppingVREvent, misGUIEvent, misCroppingDirectionInVR);
misGUIEventMacro(misLayoutEvent, misGUIEvent);

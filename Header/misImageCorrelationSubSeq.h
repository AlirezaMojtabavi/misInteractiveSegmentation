#pragma once
#include "misCompositePlaneRepresentation.h"
#include "misDatasetManager.h"
#include "misEnums.h"
#include "misEventFromGui.h"
#include "misGuiEvent.h"
#include "misGuiStructures.h"
#include "misImageGeoProperties.h"
#include "misImageNormalizer.h"
#include "misImageToImageLandmarkBasedRegistration.h"
#include "misVolumeSlicer.h"
#include "misMultiResCorrelation.h"
#include "misMultiViewSubSequence.h"
#include "misPyramidCalculator.h"
#include "misSubsequenceLayout.h"
#include "misVoreenRepresentation.h"
#include "misImageCorrelationSetting.h"
#include "IImageCorrelationTempCompositePackageCreator.h"
#include "IImageCorrelationSynchronizer.h"
#include "IImageCorrelationInitialTransformMatrixCreator.h"
#include "IImageCorrelationSettingReader.h"
#include "ImageCorrelationTransformMatrixCalculator.h"
#include "IImageCorrelationUiUpdater.h"
#include "IImageCorrelationViewingList.h"
#include "ICreateCorrelatedPackageList.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ICorrelationShowImagesAndVolumes.h"
#include "ICorrelationUpdateViewerLandmarks.h"
#include "ICorrelationSetRegistrationMatrix2Representators.h"
#include "ICorrelationChangeOpacity.h"
#include "ICorrelationUpdateTransform.h"
#include "ICorrelationShowVolumes.h"
#include "ICorrelationGetAutomaticCorrelationMatrix.h"
#include "CorrelationRegistrationState.h"
class IMultiplaViewCorrelationAdapter;
using namespace itk;

class misImageCorrelationSubSeq : public misMultiViewSubSequence
{
public:
	misImageCorrelationSubSeq(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<parcast::IImageCorrelationTempCompositePackageCreator>
		imageCorrelationTempPackageCreator,
		std::unique_ptr<parcast::IImageCorrelationSynchronizer> imageCorrelationSynchronizer,
		std::shared_ptr<parcast::IImageCorrelationInitialTransformMatrixCreator>
		imageCorrelationInitialTransformMatrixCreator,
		std::unique_ptr<parcast::IImageCorrelationSettingReader> imageCorrelationSettingReader,
		std::unique_ptr<parcast::IImageCorrelationTransformMatrixCalculator>
		imageCorrelationTransformMatrixCalculator,
		std::unique_ptr<parcast::IImageCorrelationViewingList> imageCorrelationViewingList,
		misApplicationType applicationType, std::shared_ptr<misSoftwareInformation> softwareInformation);
	
	void Render(void);
	misEventListTypedef GetEventToGui();
	bool ProcessRequest(misGUIEvent* pEvent);
	void WaitUntilRegistrationFinished();
	bool ChangeColor(misColorAndUID& colorPack);
	bool ShowImagesInitialState();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
 	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;

private:

	typedef float PixelType;
	typedef itk::Image<PixelType, 3> CorrelationImageType;
	typedef misPyramidCalculator<CorrelationImageType> PyramidCalculator;
	typedef PyramidCalculator::Pointer PyramidCalculatorPointer;
	typedef RecursivePyramidFilter<CorrelationImageType, CorrelationImageType> ImagePyramidType;
	typedef CorrelationImageType::RegionType FixedImageRegionType;
	typedef misImageNormalizer<CorrelationImageType, CorrelationImageType> ImageNormalizerType;
	typedef ImageNormalizerType::Pointer ImageNormalizerPointer;
	struct PyramidAndRegion
	{
		ImagePyramidType::Pointer imagePyramid;
		vector<FixedImageRegionType> pyramidRegion;
	};

	void ResetVariables();
	static void CalculatePyramidsInThread(void* pParams);
	void FindInitialCorrelationTransform();
	void SetInitialColorAndOpacity();
 	void RequestOnCalculate();
	void RequestOnAccept();
	void RequestOnDeny();
	void RemoveLastTrialTransform();
	void RequestShowLoadedSeriInCorrelationGUI(bool removeLastTransform);
	bool StartCalculation();
	void TaskOnLeave();
	void OnSelected();
	static void DeletePyramidThread(void* pParams);
	void UpdateTemporaryTransform();
	void AcceptCorrelationResult();
	void ResetCorrelationResult();
	void RealseResources();
	void RealseAllResources()
	{
	}
	void CalculatePyramids();
	void PrepareAndInsertPyramidToMap(std::shared_ptr<IImage> imageCorrelation);
	void UpdateStatus(long long int puls);
	void StopAutoCorrelation();
	void UpdateLandmarkListInGui();
	void SetRegistrationMatrix2Representators();
	void DeleteLandmark();
	void DeleteAllLandmarks();
	void CancelCorrelationPrecedure();
	void StopCorrelationProcedure();
	void StartCorrelation();
	void CreatePermuteAndFlipAxes();
	void SetImagesToInitialPoint();
	void FreeFusionTranslate(FusionMoveDirectionStrct);
	void FreeFusionSliceMovement(FusionMoveDirectionStrct);
	void FreeFusionRotate(FusionRotateDirectionStrct);
	bool HasImagePairDirectTimedCorrelation(const std::string& fixedImageUID, const std::string& movingImageUID);
	void ResetFreeFusionResault();
	vtkSmartPointer<vtkMatrix4x4> GetRotationMatrix(FusionRotateDirectionStrct dir);
	vtkSmartPointer<vtkMatrix4x4> GetTranslateMatrix(FusionMoveDirectionStrct dir);
	vtkSmartPointer<vtkMatrix4x4> GetSliceMovementMatrix(FusionMoveDirectionStrct dir);
	void SetViewPortType();
	void SetSameViewOrientation(IMAGEORIENTATION imageOrientation);
	void SetFixedImageAsSceneReference();
	void FindAutomaticPackage();
	void UpdateLevelInfoAndNumberOfLevel();
	void UpdateIsPackageAcceptedFlagInGui();
	void CompleteProcess(itk::Object* caller, const itk::EventObject& pEvent);

 
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CSCorrelationManager;
	misUID m_FixedImageUID;
	misUID m_MovingImageUID;
	misColorStruct m_FixedColor;
	misColorStruct m_MovingColor;
	double m_FixedImageOpacity;
	double m_MovingImageOpacity;
	typedef float PixelType;
	misDatasetManager* m_DataSetManger;
	std::shared_ptr<IImage> m_FixedImage;
	std::shared_ptr<IImage> m_MovingImage;
	misImageGeoProperties m_FixedImageProp;
	misImageGeoProperties m_MovingImageProp;
	bool m_WaitingBarIsClosed;
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix;
	misOpacityAndUID m_LastOpacityPack;
	vector<levelInformation> m_levelInfo;
	int m_NumberOfLevel;
	std::shared_ptr<CorrelationRegistrationState> m_CorrelationRegistrationState = std::make_shared<CorrelationRegistrationState>();

	bool m_TransformMatrixModification;
	bool m_StopCorrelation;
	bool m_ResetCorrelation;
	bool m_IsAutoCalculated;
	bool m_IsFreeDone;
	bool m_IsPyramidCalculated;
	bool m_IsPyramidCalculatedInMultiThreadProcedure;
	itk::FixedArray<unsigned int, 3> m_Permute;
	itk::FixedArray<bool, 3> m_Flip;
	HANDLE m_PyramidMutex;
	double m_StartPyramidCalculationTime;
	double m_FinishPyramidCalculationTime;
	std::shared_ptr<misImageToImageLandmarkBasedRegistration> m_LandmarkBasedFusion;
	misCorrelationManualRegistrationStructure m_RegistrationStrct;
	misMultiResCorrelation::Pointer m_MultiResCorrelation;
	misRegistrationMode m_RegistrationMode; //for control the tab
	map<misUID, PyramidAndRegion> m_ImagePyramidAndRegionMap;
	unsigned int m_pastIteration;
	double m_FreeFusionTranslateStep;
	double m_FreeFusionRotationStep;
	ViewPortType m_ViewPortType;
	bool m_FreeFusionStarted;
	bool m_ManualModeStarted;
	std::shared_ptr<IMultiplaViewCorrelationAdapter> m_IMultiplaViewCorrelationAdapter;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<parcast::IImageCorrelationTempCompositePackageCreator> m_ImageCorrelationTempPackageCreator;
	std::unique_ptr<parcast::IImageCorrelationSynchronizer> m_ImageCorrelationSynchronizer;
	std::shared_ptr<parcast::IImageCorrelationInitialTransformMatrixCreator>
		m_ImageCorrelationInitialTransformMatrixCreator;

	std::shared_ptr<ICorrelationGetAutomaticCorrelationMatrix> m_AutomaticCorrelation;
	std::unique_ptr<parcast::IImageCorrelationSettingReader> m_ImageCorrelationSettingReader;
	std::unique_ptr<parcast::IImageCorrelationTransformMatrixCalculator> m_ImageCorrelationTransformMatrixCalculator;
	std::shared_ptr<parcast::IImageCorrelationUiUpdater> m_ImageCorrelationUiUpdater;
	std::unique_ptr<parcast::IImageCorrelationViewingList> m_ImageCorrelationViewingList;
	std::unique_ptr<ICreateCorrelatedPackageList> m_CreateCorrelatedPackageList;
	std::shared_ptr<ImageCorrelationSetting> m_ImageCorrelationSetting;
	std::shared_ptr<ICorrelationShowVolumes>  m_CorrelationShowVolumes;
	std::shared_ptr<ICorrelationChangeOpacity> m_CorrelationChangeOpacity;
	std::shared_ptr<ICorrelationUpdateTransform> m_CorrelationUpdateTransform;
	std::shared_ptr<parcast::ICorrelationUpdateViewerLandmarks> m_UpdateViewerLandmarks;
	std::shared_ptr<ICorrelationSetRegistrationMatrix2Representators> m_RegistrationMatrix2;
	std::unique_ptr<parcast::ICorrelationShowImagesAndVolumes> m_CorrelationShowImagesAndVolumes;
	
};

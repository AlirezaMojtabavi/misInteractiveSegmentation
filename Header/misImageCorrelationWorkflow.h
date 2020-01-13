#pragma once
#include "misImageToImageLandmarkBasedRegistration.h"
#include "misMultiResCorrelation.h"
#include <misitkImageTypedef.h>
#include "misImageNormalizer.h"
#include "misImageCorrelationSetting.h"
#include "IImage.h"
#include "ICoordinateSystemCorrelationManager.h"

class  misImageCorrelationWorkflow
{
public:
	misImageCorrelationWorkflow();
	void ResetVariables();
	void StartCalculation();
	void Recalculate();
	misRegistrationMode GetRegistrationMode() const;
	void SetRegistrationMode(const misRegistrationMode& registrationMode) ;
	void DenyCorrelation();
	void ResetFreeFusionResault();
	void CacelImageCorrelation();
	void StopImageCorrelation();
	void SetFixedImage();
	void SwapImages();
	void FindInitialCorrelationTransform();
	vtkSmartPointer<vtkTransform> CreateInitialTransformMatrix();
	bool GetIsCalculateStarted() const;
	void SetIsCalculateStarted( bool started);
	void StopCorrelationProcedure();
	void CancelCorrelationPrecedure();
	void ResetCorrelationResult();
	void ChangeRegistrationMode();
	//m_FreeFusionStarted
	bool GetFreeFusionStarted() const;
	void SetFreeFusionStarted(bool freeFusionStarted);
	//m_LandmarkBasedFusion
	std::shared_ptr<misImageToImageLandmarkBasedRegistration> GetLandmarkBasedFusion() const;
	void SetLandmarkBasedFusion(const std::shared_ptr<misImageToImageLandmarkBasedRegistration>& landmarkoints);
	void StartCorrelation();
	void RequestOnAccept();
	double UpdateStatus(long long puls);
	void BuildPyramids();
	static void CalculatePyramidsInThread(void* pParams);
	void CalculatePyramids();
	void PrepareAndInsertPyramidToMap(std::shared_ptr<IImage> imageCorrelation);
	void CreatePermuteAndFlipAxes();
	void RequestOnCalculate();
	vtkSmartPointer<vtkMatrix4x4> GetAutomaticCorrelationMatrix();
	void DeletePyramidThread(void* pParams);
	void InitialState();
	//m_FreeFusionRotationStep
	void SetFreeFusionRotationStep(double step);
	double GetFreeFusionRotationStep() const;
	//m_FreeFusionTranslateStep
	void SetFreeFusionTranslateStep(double translation);
	double  GetFreeFusionTranslateStep() const;
	//m_StopCorrelation
	bool GetStopCorrelation() const;
	void SetStopCorrelation(bool stop);
	//m_MultiResCorrelation
	bool GetMultiResCorrelation() const;
	void SetMultiResCorrelation(bool reset);
	//m_ResetCorrelation
	bool GetResetCorrelation() const;
	void SetResetCorrelation(bool reset);

private:
	typedef itk::Image<PixelType, 3 > CorrelationImageType;
	typedef misPyramidCalculator< CorrelationImageType > PyramidCalculator;
	typedef PyramidCalculator::Pointer PyramidCalculatorPointer;

	typedef itk::RecursivePyramidFilter<CorrelationImageType, CorrelationImageType> ImagePyramidType;
	typedef CorrelationImageType::RegionType FixedImageRegionType;

	typedef misImageNormalizer<CorrelationImageType, CorrelationImageType> ImageNormalizerType;
	typedef ImageNormalizerType::Pointer ImageNormalizerPointer;

	struct PyramidAndRegion
	{
		ImagePyramidType::Pointer imagePyramid;
		vector<FixedImageRegionType> pyramidRegion;
	};

	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix;
	bool m_FreeFusionStarted;
	bool m_IsCalculateStarted;
	vector<levelInformation > m_levelInfo;
	int	m_NumberOfLevel;
	bool m_TransformMatrixModification;
	bool m_StopCorrelation;
	bool m_ResetCorrelation;
	bool m_IsManualRegistered;
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
	misCorrelationManualRegistrationStructure	m_RegistrationStrct;
	misMultiResCorrelation::Pointer m_MultiResCorrelation;
	misRegistrationMode m_RegistrationMode;		//for control the tab
	map<misUID, PyramidAndRegion> m_ImagePyramidAndRegionMap;
	unsigned int m_pastIteration;
	double m_FreeFusionTranslateStep;
	double m_FreeFusionRotationStep;
	ImageCorrelationSetting    m_ImageCorrelationSetting;
	std::shared_ptr<IImage> m_FixedImage;
	std::shared_ptr<IImage> m_MovingImage;
	misUID  m_FixedImageUID;
	misUID  m_MovingImageUID;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;


};

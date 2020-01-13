#pragma once
#include "ICorrelationSetRegistrationMatrix2Representators.h"
#include "misImageToImageLandmarkBasedRegistration.h"
#include "IImageCorrelationUiUpdater.h"
#include "ICorrelationUpdateTransform.h"

namespace parcast
{
class CorrelationSetRegistrationMatrix2Representators :
	public parcast::ICorrelationSetRegistrationMatrix2Representators
{
public:
	CorrelationSetRegistrationMatrix2Representators(std::shared_ptr<misImageToImageLandmarkBasedRegistration> ,
		std::shared_ptr<parcast::IImageCorrelationUiUpdater> m_ImageCorrelationUiUpdater,
		vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix, 
	vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix,
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix);
 
	void SetRegistrationMatrix2Representators(std::shared_ptr<CorrelationRegistrationState>) override;
private:
	std::shared_ptr<misImageToImageLandmarkBasedRegistration> m_LandmarkBasedFusion;
		std::shared_ptr<parcast::IImageCorrelationUiUpdater> m_ImageCorrelationUiUpdater;
vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
 

};

	
}

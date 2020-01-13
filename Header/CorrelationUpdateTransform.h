#pragma once
#include "ICorrelationUpdateTransform.h"
#include <IImage.h>
#include <misEnums.h>
#include "ICorrelationGetAutomaticCorrelationMatrix.h"
#include "misImageGeoProperties.h"

class CorrelationUpdateTransform :
	public ICorrelationUpdateTransform
{
public:
	CorrelationUpdateTransform(vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix, 
		std::shared_ptr<ICorrelationGetAutomaticCorrelationMatrix> m_AutomaticCorrelation, 
		vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix, vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix);
 private:
	void UpdateTransform(	std::shared_ptr<IImage> m_FixedImage,
		std::shared_ptr<IImage> m_MovingImage,
	misRegistrationMode registrationMode,
	bool& transformMatrixModification) override;
private:

	vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
	std::shared_ptr<ICorrelationGetAutomaticCorrelationMatrix> m_AutomaticCorrelation;
	vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix;
	vtkSmartPointer<vtkMatrix4x4> m_AutoCorrelationTransformMatrix;
};


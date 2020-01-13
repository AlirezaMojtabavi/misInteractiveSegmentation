#pragma once
#include "ICorrelationGetAutomaticCorrelationMatrix.h"
#include "misMultiResCorrelation.h"

class CorrelationGetAutomaticCorrelationMatrix :
	public ICorrelationGetAutomaticCorrelationMatrix
{
public:
	CorrelationGetAutomaticCorrelationMatrix(misMultiResCorrelation::Pointer, vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix);

	vtkSmartPointer<vtkMatrix4x4> GetAutomaticCorrelationMatrix(bool& m_TransformMatrixModification) override;
private:
		misMultiResCorrelation::Pointer m_MultiResCorrelation;
		vtkSmartPointer<vtkMatrix4x4> m_TransformMatrix;
		


};


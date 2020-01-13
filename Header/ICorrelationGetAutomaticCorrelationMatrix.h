#pragma once
class ICorrelationGetAutomaticCorrelationMatrix
{
public :
	virtual ~ICorrelationGetAutomaticCorrelationMatrix() = default;
	virtual vtkSmartPointer<vtkMatrix4x4> GetAutomaticCorrelationMatrix(bool& transformMatrixModification) = 0;
};

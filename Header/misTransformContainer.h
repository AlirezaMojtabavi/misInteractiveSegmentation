#pragma once
class vtkTransform;
//itkEventMacro( misTargetPointCapture, misEvent);
struct misTransformContainer 
{
	vtkTransform*  pTrans;
	misTransformContainer()
	{
		this->pTrans = 0;
	}
};
#include "StdAfx.h"
#include "misVTKMattoTgtMatConvertor.h"

misVTKMattoTgtMatConvertor::misVTKMattoTgtMatConvertor(void)
{
}


misVTKMattoTgtMatConvertor::~misVTKMattoTgtMatConvertor(void)
{
}




tgt::Matrix4d misVTKMattoTgtMatConvertor::operator()( vtkSmartPointer<vtkMatrix4x4> transform )
{

	tgt::Matrix4d transformMatrix = tgt::Matrix4d(transform->GetElement(0,0),transform->GetElement(0,1),
		transform->GetElement(0,2),transform->GetElement(0,3),transform->GetElement(1,0),
		transform->GetElement(1,1),transform->GetElement(1,2),transform->GetElement(1,3),
		transform->GetElement(2,0),transform->GetElement(2,1),transform->GetElement(2,2),
		transform->GetElement(2,3), 0.0, 0.0, 0.0, 1.0);

	return transformMatrix;

}




vtkSmartPointer<vtkMatrix4x4> misVTKMattoTgtMatConvertor::operator()( tgt::Matrix4d tgtMat )
{
	vtkSmartPointer<vtkMatrix4x4> transformMatrix=vtkSmartPointer<vtkMatrix4x4>::New();
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			transformMatrix->SetElement(i,j,tgtMat[i][j]);
		}
	}
	return transformMatrix;

}


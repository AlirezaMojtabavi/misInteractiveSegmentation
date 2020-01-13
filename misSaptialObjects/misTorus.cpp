#include "stdafx.h"
#include "misTorus.h"



void misTorus::TranslateTorus( double* position )
{
	m_TorusActor->SetPosition2(position);
}

void misTorus::CreateTorus( double CrossSectionRadius, double RingRadius, double zElement )
{
	vtkParametricTorus*    virtualTipTorus = vtkParametricTorus::New();
	virtualTipTorus->SetCrossSectionRadius(CrossSectionRadius); 
	virtualTipTorus->SetRingRadius (RingRadius); 
	virtualTipTorus->Modified();

	vtkSmartPointer<vtkActor2D> actor =
		vtkSmartPointer<vtkActor2D>::New();

	vtkParametricFunctionSource*  parametricFunctionSource = vtkParametricFunctionSource::New();
	parametricFunctionSource->SetParametricFunction(virtualTipTorus);


	vtkPolyData* torusPolyData = parametricFunctionSource->GetOutput();
	torusPolyData->Modified();

	transformMatrix->Identity();
	transformMatrix->SetElement(2,3,zElement);

	vtkTransform* trans = vtkTransform::New();
	trans->Identity();
	trans->SetMatrix(transformMatrix);
	trans->Modified();

	vtkTransformPolyDataFilter* polyTrans = vtkTransformPolyDataFilter::New();

	polyTrans->SetInputData(parametricFunctionSource->GetOutput());
	polyTrans->SetTransform(trans);

	vtkSmartPointer<vtkPolyDataMapper2D> torusMapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
	torusMapper->SetInputData(polyTrans->GetOutput());
	torusMapper->Modified();

	m_TorusActor->SetMapper(torusMapper);
	m_TorusActor->Modified();
	m_TorusActor->SetVisibility(true);
}

misTorus::misTorus( double CrossSectionRadius, double RingRadius, double zElement )
{
	m_TorusActor = vtkSmartPointer<vtkActor2D>::New();
	transformMatrix	= vtkMatrix4x4::New();
	CreateTorus(CrossSectionRadius, RingRadius, zElement);
}

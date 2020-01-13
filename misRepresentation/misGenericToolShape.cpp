#include "stdafx.h"
#include "misGenericToolShape.h"


vtkSmartPointer<vtkPolyData> misGenericToolShape::GenerateToolGeometry()
{
	const double height = 35;
	auto sphereModel = vtkSmartPointer<vtkSphereSource>::New();
	sphereModel->SetCenter(height / 2, 0, 0);
	sphereModel->SetRadius(0.5);
	sphereModel->SetThetaResolution(100);
	sphereModel->SetPhiResolution(100);
	sphereModel->Modified();
	auto coneModel = vtkSmartPointer<vtkConeSource>::New();
	coneModel->SetHeight(height);
	coneModel->SetRadius(height / 27);
	coneModel->SetResolution(20);
	coneModel->CappingOff();
	coneModel->Modified();
	auto appendPoly = vtkSmartPointer<vtkAppendPolyData>::New();
	appendPoly->AddInputConnection(sphereModel->GetOutputPort());
	appendPoly->AddInputConnection(coneModel->GetOutputPort());
	appendPoly->Update();
	auto primaryTransform = vtkSmartPointer<vtkTransform>::New();
	primaryTransform->Identity();
	primaryTransform->RotateY(-90);
	primaryTransform->Translate(-height / 2, 0, 0);
	primaryTransform->Update();
	auto polyDatFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	polyDatFilter->SetTransform(primaryTransform);
	polyDatFilter->SetInputConnection(appendPoly->GetOutputPort());
	polyDatFilter->Update();
	auto polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData->DeepCopy(polyDatFilter->GetOutput());
	return polyData;
}

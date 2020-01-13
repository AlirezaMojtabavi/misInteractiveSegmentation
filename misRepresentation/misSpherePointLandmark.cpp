#include "StdAfx.h"

#include "misSpherePointLandmark.h"

#include "misFollowerFixedArea.h"

misSpherePointLandmark::misSpherePointLandmark(bool disableDepth)
	:m_DisableDepth(disableDepth)
{
	GenerateGeometry();
}


void misSpherePointLandmark::GenerateGeometry()
{
	vtkSmartPointer<vtkSphereSource> pSphere = vtkSmartPointer<vtkSphereSource>::New();
	vtkSmartPointer<vtkPolyDataMapper>  pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	auto pActor= vtkSmartPointer<misFollowerFixedArea>::New();
	pActor->SetDisableDepth(m_DisableDepth);
	pSphere->SetRadius(1.5f);
	pSphere->Update();
	pMapper->SetInputData(pSphere->GetOutput());
	pActor->SetMapper(pMapper);
	m_Actors.push_back(pActor);
}

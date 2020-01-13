#include "stdafx.h"
#include "misSurfaceRepresentation.h"

#include "misFollowerFixedArea.h"

using std::string;



void  misSurfaceRepresentation::SetColor(float r,float g,float  b)
{
	for (int i = 0; i < this->m_Actors.size(); i++)
	{
		if (r < 0)
			r = 0;
		if (r > 1)
			r = 1;

		if (g < 0)
			g = 0;
		if (g > 1)
			g = 1;

		if (b < 0)
			b = 0;
		if (b > 1)
			b = 1;

		vtkActor* pActor = dynamic_cast<vtkActor*>(this->m_Actors[i].GetPointer());
		if (pActor)
			pActor->GetProperty()->SetColor(r, g, b);
	}
}


void misSurfaceRepresentation::SetOpacity( double opacity )
{
	for(int i=0; i < this->m_Actors.size(); i++)
	{
		vtkActor* pActor = dynamic_cast<vtkActor*>(this->m_Actors[i].GetPointer());
		if (pActor)
			pActor->GetProperty()->SetOpacity(opacity);
	}
}


//=====================================================================================
vtkActor* misSurfaceRepresentation::AddPolyData(vtkPolyData* polyData ,vtkProperty* property /*= 0*/)
{
	vtkPolyDataMapper*  pMapper = vtkPolyDataMapper::New();
	pMapper->SetInputData(polyData);
	pMapper->ScalarVisibilityOff();
	vtkActor* pActor = vtkActor::New();
	pActor->SetMapper(pMapper);
	if (property)
		pActor->SetProperty(property);
	this->m_Actors.push_back(pActor);
	pMapper->Delete();
	m_BoundingActorsUpdated = this->m_Actors.size();
	return  pActor;
}
//=====================================================================================
vtkActor* misSurfaceRepresentation::AddPolyData(vtkAlgorithmOutput* polyData, vtkProperty* property /*= 0*/)
{
	vtkPolyDataMapper*  pMapper = vtkPolyDataMapper::New();
	pMapper->SetInputConnection(polyData);
	pMapper->ScalarVisibilityOff();
	vtkActor* pActor = vtkActor::New();
	pActor->SetMapper(pMapper);
	if (property)
		pActor->SetProperty(property);
	this->m_Actors.push_back(pActor);
	pMapper->Delete();
	m_BoundingActorsUpdated = this->m_Actors.size();
	return  pActor;
}


std::shared_ptr<misSurfaceRepresentation> misSurfaceRepresentation::CreateInstance()
{
	auto pSurfcace = std::make_shared<misSurfaceRepresentation>("cloned");
	for (int i = 0; i < this->m_Actors.size(); i++)
	{
		vtkPolyData* pol = vtkPolyData::New();
		vtkActor* pActor = dynamic_cast<vtkActor*>(this->m_Actors[i].GetPointer());
		if (pActor)
		{
			vtkPolyData* temp = dynamic_cast<vtkPolyData*>(pActor->GetMapper()->GetInput());
			pol->DeepCopy(temp);
			pSurfcace->AddPolyData(pol, pActor->GetProperty());
		}
	}
	return pSurfcace;
}


void misSurfaceRepresentation::SetCamera(vtkCamera* pCamera)
{

	for(int i=0; i < this->m_Actors.size(); i++)
	{
		misFollowerFixedArea* pFollower = dynamic_cast<misFollowerFixedArea*>(this->m_Actors[i].GetPointer());
		if (pFollower)
			pFollower->SetCamera(pCamera);
	}


}

 
#include "stdafx.h"
#include "misImagePlaneInformationStrct.h"

misImagePlaneInformationStrct::misImagePlaneInformationStrct()
{
	this->m_showErased = false;
	this->m_ErasedObjectColor.red = 255;
	this->m_ErasedObjectColor.green = 0;
	this->m_ErasedObjectColor.blue = 0 ;
	this->m_ErasedObjectColor.alpha = 255;
	this->m_PlaneSpacing = new double[3];
	ZeroMemory(m_PlaneExtent,6*sizeof(int));
}

void misImagePlaneInformationStrct::Reset()
{
	this->m_TransformMatrix = nullptr;
}

void misImagePlaneInformationStrct::SetExtends( const int* extends )
{
	for (int i=0;i<6;i++)
	{
		m_PlaneExtent[i]=extends[i];
	}
}

const int* misImagePlaneInformationStrct::GetExtends() const
{
	return m_PlaneExtent;
}

parcast::PointD3  misImagePlaneInformationStrct::GetPlaneCenter()
{
	if (!m_pQuadActor)
		return{};
	double position[3];
	m_pQuadActor->GetPlaneCenter(position);
	return  parcast::PointD3(position);
}
void misImagePlaneInformationStrct::SetMapper(vtkMapper* mapper)
{
	const auto prevMapper = m_pQuadActor->GetMapper();
	if (prevMapper != mapper)
	{
		m_pQuadActor->SetMapper(mapper);
		mapper->Delete();
	}
}

void misImagePlaneInformationStrct::GeneratePlaneMesh()
{
	if(!m_pQuadActor)
		m_pQuadActor = vtkSmartPointer<misImageActor>::New();
}

vtkSmartPointer<misImageActor> misImagePlaneInformationStrct::GetActor()
{
	return m_pQuadActor;
}


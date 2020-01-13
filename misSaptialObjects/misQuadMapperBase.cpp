#include "StdAfx.h"
#include "misQuadMapperBase.h"

misQuadMapperBase::misQuadMapperBase(void)
{
	m_Coordinate1.SetPoint(0, 0, 0);
	m_Coordinate2.SetPoint(1, 0, 0);
	m_Coordinate3.SetPoint(1, 1, 0);
	m_Coordinate4.SetPoint(0, 1, 0);
	this->m_GroupCoordinateProperties.resize(2);

}



tgt::vec3 misQuadMapperBase::GetCenter()
{
	tgt::vec3  p1,p2,p3,p4;
	for (int i=0;i<3;i++)
	{
		p1[i]=m_P1[i];
		p2[i]=m_P2[i];
		p3[i]=m_P3[i];
		p4[i]=m_P4[i];
	}
	auto  vec1=(p2-p1)*0.5f;
	auto pt1=p1+vec1;
	auto  vec2=(p3-p1)*0.5f;
	auto pt2=p1+vec2;
	auto vecHalf1=pt2-p1;
	auto vecHalf2=pt1-p1;
	auto vec=vecHalf1+vecHalf2;
	auto  p=p1+vec;
	tgt::vec3   elem;
	elem[0]=p[0];
	elem[1]=p[1];
	elem[2]=p[2];
	return  elem;
}

void misQuadMapperBase::GeneratePlaneMesh(misTexturePropertyStruct prop)
{
	ImageBoundingProperty imageBoundingProperty;
	auto extent = prop.GetExtent();
	for (int i = 0; i < 6; i++)
	{
		imageBoundingProperty.Extent[i] = extent[i];
	}

	for (auto i = 0; i < 3; i++)
	{
		imageBoundingProperty.Spacing[i] = prop.Spacing[i];
	}
	
	this->m_CornerProperties->SetImageBounding(imageBoundingProperty);
}

void misQuadMapperBase::SetCornerProperties( std::shared_ptr<ICornerProperties> pCornerProp )
{
	if (pCornerProp)
		this->m_CornerProperties = pCornerProp;
}

double * misQuadMapperBase::GetBounds()
{
	if (!m_CornerProperties)
		return NULL;

	m_Bounds = this->m_CornerProperties->GetBounds();
	return m_Bounds;
}

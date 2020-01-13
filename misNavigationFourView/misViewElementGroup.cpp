#include "StdAfx.h"
#include "misViewElementGroup.h"
#include "misDirectionStringConevrtor.h"
#include "misTryCatchDeserializationMACRO.h"

misViewElementGroup::misViewElementGroup(int rowColumn, misViewerTypeDirection direction,
	PlaneVisibiltyMapType planeImageVisibility,	double distance)
	: m_NumberOfViewers(rowColumn * rowColumn), m_ViewerTypeDirection(direction), m_PlaneVisibility(planeImageVisibility), 
	m_Distance(distance)
{
	CreateChilds();
 

}

misViewElementGroup::misViewElementGroup()
{

}

void misViewElementGroup::CreateChilds()
{
	for (int i = 0; i < m_NumberOfViewers; i++)
	{
		double offset = i * m_Distance;
		misViewingWindowElement element(m_ViewerTypeDirection, m_PlaneVisibility, i, offset);
		m_Elements.push_back(element);
	}
	//Calculate view port
	int rowColumn = sqrt(m_NumberOfViewers);
	double windowWidth = 1.0 / double(rowColumn);
	int index = 0;
	// view port coordinates incrementing from bottom to top and left to right
	for (int i = 0; i < rowColumn; i++)
	{
		for (int j = 0; j < rowColumn; j++)
		{
			double posStartX = j * windowWidth;
			double posStartY = (rowColumn - 1 - i) * windowWidth;
			double posEndX = posStartX + windowWidth;
			double posEndY = posStartY + windowWidth;
			misViewPort port(tgt::Vector2d(posStartX, posStartY), tgt::Vector2d(posEndX, posEndY));
			m_Elements[index].SetViewPort(port);
			index++;
		}
	}
}

misViewElementGroup::~misViewElementGroup(void)
{
}

misViewPort misViewElementGroup::GetViewPort( int index ) const
{
	return m_Elements[index].GetViewPort();
}

misViewerTypeDirection misViewElementGroup::GetTypeOfViewer( ) const
{
	return m_ViewerTypeDirection;
}

PlaneVisibiltyMapType misViewElementGroup::GetPlaneVisibilityStatus() const
{
	return m_PlaneVisibility;
}

int misViewElementGroup::GetNumberOfViewer() const
{
	return m_NumberOfViewers;
}

const misViewingWindowElement& misViewElementGroup::GetViewer(int index) const
{
	return m_Elements[index];
}

PlaneVisibiltyMapType misViewElementGroup::CreateDefaultPlaneVisibilyMap()
{
	PlaneVisibiltyMapType planes;
	planes[FirstImage] = true;
	planes[SecondImage] = true;
	return planes;
}

void misViewElementGroup::serialize(XmlSerializer& s) const
{
	s.serialize("Position", m_Position);
	s.serialize("Size", m_Size);
	s.serialize("NumberOfWindows", m_NumberOfViewers);
	s.serialize("Distance", m_Distance);
	misDirectionStringConevrtor conevrtor;
	std::string direction = conevrtor.ConvertDirectionToString(m_ViewerTypeDirection);
	s.serialize("ViewerTypeDirection", direction);
	s.serialize("UpdateByVirtualTip", m_UpdateByVirtualTip);	
	s.serialize("IsOblique", m_IsObliq);
	s.serialize("ShowToolExtension", m_ShowToolExtension);

}

void misViewElementGroup::deserialize(XmlDeserializer& s)
{
	s.deserialize("Position", m_Position);
	s.deserialize("Size", m_Size);
	TRYCATCHDESERILIZE("NumberOfWindows", m_NumberOfViewers);
	TRYCATCHDESERILIZE("Distance", m_Distance);
	std::string viwerDirection;
	s.deserialize("ViewerTypeDirection", viwerDirection);
	TRYCATCHDESERILIZE("UpdateByVirtualTip", m_UpdateByVirtualTip);
	misDirectionStringConevrtor conevrtor;
	m_ViewerTypeDirection = conevrtor.ConvertStringToDirection(viwerDirection);
	TRYCATCHDESERILIZE("IsOblique", m_IsObliq);
	TRYCATCHDESERILIZE("ShowToolExtension", m_ShowToolExtension);
	TRYCATCHDESERILIZE("FirstImageVisibility", m_PlaneVisibility[FirstImage]);
	TRYCATCHDESERILIZE("SecondImageVisibility", m_PlaneVisibility[SecondImage]);
	CreateChilds();
} 

bool misViewElementGroup::IsUpdateByVirtualTip() const
{
	return m_UpdateByVirtualTip;
}


void misViewElementGroup::SetUpdateByVirtualTip(bool val)
{
	m_UpdateByVirtualTip = val;
}

bool misViewElementGroup::GetShowToolExtension() const
{
	return m_ShowToolExtension;
}

void misViewElementGroup::SetShowToolExtension(bool val)
{
	m_ShowToolExtension = val;
}

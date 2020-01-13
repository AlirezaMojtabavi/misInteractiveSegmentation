#include "StdAfx.h"
#include "misViewingWindowElement.h"

#include "misPlaneContrast.h"

misViewingWindowElement::~misViewingWindowElement(void)
{
}

misViewPort misViewingWindowElement::GetViewPort() const
{
	return m_ViewPort;
}

misViewingWindowElement::misViewingWindowElement( misViewerTypeDirection direction , 
	PlaneVisibiltyMapType imagePlaneVisibility, 	int index /*= 0*/, double offset /*=0*/ )
	: m_ViewerTypeDirection(direction), m_PlaneVisibility(imagePlaneVisibility), m_WindowIndex(index), m_Offset(offset)
{
}

misViewerTypeDirection misViewingWindowElement::GetTypeOfViewer(  ) const
{
	return m_ViewerTypeDirection;
}

PlaneVisibiltyMapType misViewingWindowElement::GetPlaneVisibilityStatus() const
{
	return m_PlaneVisibility;
}

void misViewingWindowElement::SetViewPort( const misViewPort& viewPort ) 
{
	m_ViewPort = viewPort;
}

double misViewingWindowElement::GetOffset() const
{
	return m_Offset;
}


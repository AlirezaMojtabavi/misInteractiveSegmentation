#include "StdAfx.h"
#include "misPlaneAndBoxConfiguration.h"

misPlaneAndBoxConfiguration::misPlaneAndBoxConfiguration( const misPlaneAndBoxConfiguration &planeAndBoxConfiguration ) 
	
{
	SetPlanePoint(planeAndBoxConfiguration.GetPlanePoint()); 
	SetPlaneOffset(planeAndBoxConfiguration.GetPlaneOffset());

	PointType tmpP1, tmpP2;
	planeAndBoxConfiguration.GetBoxBounds(tmpP1, tmpP2);
	SetBoxBounds(tmpP1, tmpP2);

}

misPlaneAndBoxConfiguration::misPlaneAndBoxConfiguration():m_PlaneOffset(0)
{

}

void misPlaneAndBoxConfiguration::SetBoxBounds( const PointType &vertex1, const PointType &vertex2 )
{
	m_Point1OfBoxBounds = vertex1;
	m_Ponit2OfBoxBounds = vertex2;
}

void misPlaneAndBoxConfiguration::GetBoxBounds( PointType& vertex1, PointType& vertex2 ) const
{
	vertex1 = m_Point1OfBoxBounds;
	vertex2 = m_Ponit2OfBoxBounds;
}

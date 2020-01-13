#include "stdafx.h"
#include "misZoomFinder.h"

unsigned int misZoomFinder::FindNextZoomPercentage( unsigned int zoomPercentage) const
{
	for(int i = 0; i < m_ZoomLookupTable.size() - 1; i++)
	{
		if(m_ZoomLookupTable[i] == zoomPercentage)
			return m_ZoomLookupTable[i+1];
	}
	return  1000;
}

unsigned int misZoomFinder::FindPreviousZoomPercentage( unsigned int zoomPercentage) const
{
	if (m_ZoomLookupTable[0] == zoomPercentage)
		return m_ZoomLookupTable[0];

	for(int i = 1; i < m_ZoomLookupTable.size(); i++)
	{
		if(m_ZoomLookupTable[i] == zoomPercentage)
			return m_ZoomLookupTable[i-1];
	}
	return 90;
}




#include "stdafx.h"
#include "misDistributionMap.h"

itk::EventObject* misDistributionMap::GetEventTypeid() const
{
	return m_Event;
}

misDistributionMap::misDistributionMap( itk::EventObject* pEvent )
{
	m_Event=pEvent;
	this->SetAllMapTo(false);
}

misDistributionMap::DistributionMap misDistributionMap::GetMap()
{
	return inerMap;
}

void misDistributionMap::InitializeInerMap( int numberOfElements )
{
	inerMap.clear();
	for (int i = 0 ; i < numberOfElements; i++)
	{
		std::vector<bool> inerVec;
		for (int j = 0 ; j < numberOfElements; j++)
		{
			inerVec.push_back(false);
		}
		inerMap.push_back(inerVec);
	}
	this->SetAllElemetsToDefault();
}

void misDistributionMap::SetAllMapTo( bool val )
{
	for (int i = 0; i < inerMap.size(); i++)
	{
		for (int j = 0; j < inerMap[i].size(); j++)
		{
			if (i == j)
				inerMap[i][j] = false;
			else
				inerMap[i][j] = val;
		}
	}
}

void misDistributionMap::SetElementTo( int i , int j , bool val )
{
	if (i <inerMap.size())
	{
		if (j < inerMap[i].size())
		{
			inerMap[i][j] = val;
			//inerMap[j][i] = val;
		}
		else
			_ASSERT( 0 == 1);
	}
	else
		_ASSERT( 0 == 1);
}

void misDistributionMap::SetAllElemetsToDefault()
{
	this->SetAllMapTo(true);
}

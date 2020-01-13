#pragma once

// this class provide a bidirectional graph N x N between any group of objects to process events from each other.
// in practice an N x N matrix defines relationships of objects to each other for an event.
class misDistributionMap
{
public:
	typedef std::vector<std::vector<bool>> DistributionMap;
private:
	
	DistributionMap inerMap;
	itk::EventObject*  m_Event;

public:
	itk::EventObject* GetEventTypeid() const;

	DistributionMap GetMap();

	misDistributionMap(itk::EventObject*  pEvent);

	void InitializeInerMap(int numberOfElements);

	void SetAllMapTo(bool val);

	void SetElementTo(int i , int j , bool val);

	void SetAllElemetsToDefault();
};

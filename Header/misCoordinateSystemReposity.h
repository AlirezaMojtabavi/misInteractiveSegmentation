#pragma once
#include "ICoordinateSystemReposity.h"

#include "ICoordinateSystem.h"
#include "boost/signals2.hpp"

// The misCoordinateSystemReposity implement ICoordinateSystemReposity and store a list of ICoordinateSystem and inform 
// subscribers when adding a new ICoordinateSystem
class misCoordinateSystemReposity : public ICoordinateSystemReposity 
{
public:
	misCoordinateSystemReposity(void);
	~misCoordinateSystemReposity(void);
	virtual void RemoveCoordinateSystem( const std::shared_ptr<ICoordinateSystem> coordinatesSystem );
	virtual void AddCoordinateSystem( const std::shared_ptr<ICoordinateSystem> coordinatesSystem );
	virtual void SubscribeAddingCoordinate( SubscriberType subscriber );
	virtual void SubscribeRemovingCoordinate( SubscriberType subscriber );

private:
	std::vector<std::shared_ptr<ICoordinateSystem>> m_CoordinatesSytems;
	boost::signals2::signal<SubscriberType> m_SubscriberSignalAdd;
	boost::signals2::signal<SubscriberType> m_SubscriberSignalRemove;
};


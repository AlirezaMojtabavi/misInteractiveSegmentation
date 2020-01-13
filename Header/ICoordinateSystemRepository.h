#pragma  once
#include "ICoordinateSystem.h"

#include "misStringTools.h"

// The class stores an IcoordinateSystem and informs any class that needs to observes. every ICoordinateSystem must be add to this
// repository -  for example Database adapter needs to know when arrived a new ICoordinateSystem
// to  update correlation results of previously read ICoordinateSystem UIDs
class  ICoordinateSystemRepository
{
public:
	// add ICoordinateSystem to internal containers
	virtual void AddCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinatesSystem) = 0;
	//remove ICoordinateSystem  from internal containers
	virtual void RemoveCoordinateSystem(std::shared_ptr<ICoordinateSystem> coordinatesSystem) = 0;
	// Find coordinate system with specified id
	virtual std::shared_ptr<ICoordinateSystem> GetCoordinateSystem(misUID coordinateSystemUID) const = 0;
	//Clear All Contents
	virtual void Clear() = 0;
	virtual std::vector<std::shared_ptr<ICoordinateSystem>> GetAllCoordinatesSystems() const= 0; 
};

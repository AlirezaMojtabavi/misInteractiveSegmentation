#pragma once

// The ICoordinateSystem class is abstract interface shared by concrete classes that can serve as a coordinate system. Classes 
// implementing this interface can be used with ICoordinateSystemCorrelationManager implementations which by default operate on 
// coordinate system objects (implementations of ICoordinateSystem).
class ICoordinateSystem
{
public: 
	virtual ~ICoordinateSystem() { }	// Default virtual destructor necessary for abstract classes.
	virtual std::string GetUID() const = 0; // return a unique identifier string 
	virtual void SetUID(const std::string& id) = 0; // set a unique identifier string 
};
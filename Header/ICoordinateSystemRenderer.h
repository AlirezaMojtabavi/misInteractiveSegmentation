#pragma once

#include "ICoordinateSystem.h"

// The ICoordinateSystemRenderer class renders a coordinate system and updates transform of coordinates system in rendering 
// scene related to specific reference coordinate system. It retrieves relative transforms from other sources such as an 
// external correlation manager ...
class ICoordinateSystemRenderer
{
public:
	// Performs prerendering preparations and sets transforms, shader parameters, ...
	virtual void Render() = 0;

	// Sets the coordinate system that will be rendered.
	virtual void SetCoordinateSystem( const std::string&  coordinateSytem ) = 0;
	
	// Set reference coordinate system relative to which the rendered coordinate's transform is calculated.
	virtual void SetRefrenceCoordinate( const  std::string&  coordinateSytem ) = 0;

	// Determines whether the Render() method performs the rendering operations or the coordinate system is not rendered at all.
	virtual void RenderingOn() = 0;
	virtual void RenderingOff() = 0;
	
	virtual void SetColor(float r, float g, float b ) = 0;
};
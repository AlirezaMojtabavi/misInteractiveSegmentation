#pragma once

#include "misROI.h"

// This class convert a vector of itk point to a texture which is represented it's ID.
// Author : Mohsen Rahimimoghaddam
// Date : May 2016
class IPointToTextureConvertor
{
public:

	// Set a vector of itk points which contains 3D points which will be converted to the texture
	virtual void SetPoints(const std::vector<itk::Point<double, 3>>&) = 0;

	// Returns ID of converted an OpenGL texture. 
	virtual GLuint GetTexture() const = 0;
	
	// Set image bounds - used for normalizing point coordinates within the range [0, 1]
	virtual void SetImageDimensions(const misROI& roi) = 0;

	virtual ~IPointToTextureConvertor() { };

};
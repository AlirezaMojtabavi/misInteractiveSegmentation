#pragma once

#include "misSurfaceRepresentation.h"

class misPointLandMark :
	public misSurfaceRepresentation
{
public:
	virtual void GenerateGeometry() = 0;
public:
	misPointLandMark(void);
	virtual ~misPointLandMark(void);
};


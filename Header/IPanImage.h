#pragma once
#include "misPlanarRepresentation.h"

class IPanImage
{
public:
	virtual void SetMainRepresentation(std::shared_ptr<misPlanarRepresentation>) = 0;
	virtual void Pan() = 0;
	virtual void SetInteractor(vtkRenderWindowInteractor*) = 0;

};

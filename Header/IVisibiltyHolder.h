#pragma once
#include "misPlaneContrast.h"

class IVisibiltyHolder
{
public:
	virtual ~IVisibiltyHolder() = default;
	virtual void SetVisibilty(misPlaneEnum layer, bool b) =0;
	virtual bool GetVisibilty(misPlaneEnum layer) = 0;

	
};

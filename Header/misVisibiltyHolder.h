#pragma once
#include "misPlaneContrast.h"
#include "IVisibiltyHolder.h"

class misVisibiltyHolder : public IVisibiltyHolder
{
public:
	misVisibiltyHolder(std::map<misPlaneEnum, bool> defaultVisibilty);
	~misVisibiltyHolder();
	void SetVisibilty(misPlaneEnum layer, bool b);
	bool GetVisibilty(misPlaneEnum layer);

private:
	std::map<misPlaneEnum, bool> defaultVisibilty;
	std::map<misPlaneEnum, bool> currentVisibilty;
};


#include "stdafx.h"
#include "misVisibiltyHolder.h"


misVisibiltyHolder::misVisibiltyHolder(std::map<misPlaneEnum, bool> defVisibilty)
	:defaultVisibilty(defVisibilty), currentVisibilty(defVisibilty)
{
}


misVisibiltyHolder::~misVisibiltyHolder()
{
}

void misVisibiltyHolder::SetVisibilty(misPlaneEnum layer, bool b)
{
	currentVisibilty[layer] = b&& defaultVisibilty[layer];
}

bool misVisibiltyHolder::GetVisibilty(misPlaneEnum layer)
{
	return currentVisibilty[layer];
}

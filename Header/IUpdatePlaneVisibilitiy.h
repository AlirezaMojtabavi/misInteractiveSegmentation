#pragma once
#include "misPlaneContrast.h"
#include "IMedicalImageViewer.h"

class IUpdatePlaneVisibilitiy
{
public:
	virtual ~IUpdatePlaneVisibilitiy() = default;
	virtual void UpdatePlaneVisibilities(const std::map<misPlaneEnum, bool>  imageVisibiltes,  std::map<misPlaneEnum, bool> pPlaneVisible) = 0;


};

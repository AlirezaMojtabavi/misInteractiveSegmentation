#pragma once
#include "IUpdatePlaneVisibilitiy.h"
#include "IVolumeSlicer.h"

class UpdatePlaneVisibilitiy : public IUpdatePlaneVisibilitiy
{
public:
	UpdatePlaneVisibilitiy(std::shared_ptr<IVolumeSlicer> volumeSlicer,
		std::shared_ptr<IVisibiltyHolder> visibiltyHolder);

	void UpdatePlaneVisibilities(const std::map<misPlaneEnum, bool>  imageVisibiltes,
		std::map<misPlaneEnum, bool> pPlaneVisible) final;
private:

	std::shared_ptr<IVolumeSlicer> m_2DViewer;
	std::shared_ptr<IVisibiltyHolder> m_VisibiltyHolder;
};

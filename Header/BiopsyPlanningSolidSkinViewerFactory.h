#pragma once
#include "IBiopsyPlanningSolidSkinViewer.h"
#include "BiopsyPlanningSolidSkinViewer.h"

namespace parcast
{
	class BiopsyPlanningSolidSkinViewerFactory
	{
	public:
		static  std::shared_ptr<IBiopsyPlanningSolidSkinViewer> Create(std::shared_ptr<INavigationViewersNView> groupViewer,
			std::shared_ptr<misVolumeCropping> volumeCropping,
			std::shared_ptr<IBiopsyPlanningUIUpdater> uIUpdater);
	};
}

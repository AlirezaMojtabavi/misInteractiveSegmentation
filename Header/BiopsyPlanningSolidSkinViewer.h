#pragma once
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"
#include "misVolumeCropping.h"
#include "IBiopsyPlanningUIUpdater.h"
#include "IBiopsyPlanningSolidSkinViewer.h"

namespace parcast
{
	class BiopsyPlanningSolidSkinViewer: public IBiopsyPlanningSolidSkinViewer
	{
	public:
		BiopsyPlanningSolidSkinViewer(std::shared_ptr<INavigationViewersNView> groupViewer,
			std::shared_ptr<misVolumeCropping> volumeCropping,
			std::shared_ptr<IBiopsyPlanningUIUpdater> uIUpdater);
		void Render(std::shared_ptr<ISimpleDataPackage> package, misCroppingDirectionInVR croppingDir = NoCut) override;

	private:
		void UpdateCroppingDirection(misCroppingDirectionInVR croppingDirection);
		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
		std::shared_ptr<misVolumeCropping> m_VolumeCropping;
		std::shared_ptr<IBiopsyPlanningUIUpdater> m_UIUpdater;
	};
}


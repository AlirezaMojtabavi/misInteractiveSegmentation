#pragma once
#include "IScrewViewer.h"
#include "misEnums.h"
#include "IInitializeScrewWidget.h"
#include "IRepresentation.h"
#include "misVolumeRendererContainer.h"

namespace parcast
{
	class ScrewViewerFactory
	{
	public:
		using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
		static std::shared_ptr<IScrewViewer> Create(enum::Dimention dimention,
		                                            std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
		                                            std::shared_ptr<ScrewListType> screwServiceList,
		                                            std::shared_ptr<ICornerProperties> cornerproperties,
		                                            misVolumeRendererContainer::Pointer parent);
	};
}

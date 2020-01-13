#pragma once

#include "IStaticTransformUpdater.h"

namespace parcast
{

	class StaticTransformUpdater : public IStaticTransformUpdater
	{
	public:

		StaticTransformUpdater(
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager);

		void Update(std::shared_ptr<ITrackingTool> subjectTool) override;

	private:
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
	};

}
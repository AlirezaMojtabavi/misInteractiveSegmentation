#pragma once
#include "ICoordinateSystem.h"
#include "ITrackingToolQuery.h"

namespace parcast
{
	class RegistrationCaptureLastPosition
	{
	public:
		RegistrationCaptureLastPosition(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >);
		void GetLastCapturedPosition(ICoordinateSystem* refernecCorinate, double outputPosition[3]);
		void SetTrackingToolQueruy(std::shared_ptr<ITrackingToolQuery>);
	private:
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;

	};
}
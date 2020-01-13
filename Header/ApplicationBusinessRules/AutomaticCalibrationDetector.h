#pragma once

#include "IAutomaticCalibrationDetector.h"

class ITrackingToolQuery;

namespace parcast
{
	class IClock;

	class AutomaticCalibrationDetector : public IAutomaticCalibrationDetector
	{
	public:
		AutomaticCalibrationDetector(
			std::shared_ptr<ITrackingToolQuery> toolQuery,
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
			std::shared_ptr<IClock> clock,
			double maximumDistanceToCalibratorPoint,
			double minimumTimeSecondIntervalBetweenRecalibration);

		void Update() override;

	private:
		std::shared_ptr<ITrackingToolQuery> m_ToolQuery;
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
		std::shared_ptr<IClock> m_Clock;
		double m_MaximumDistanceToCalibratorPoint;
		double m_Interval;
		double m_CallTime;
	};

}

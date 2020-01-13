#pragma once

#include "IBiopsyToolTransformCalculatorNav.h"
#include "IBiopsyToolTransformCalculatorTracker.h"

namespace parcast
{

	class IBiopsyToolDirFinder;

	class BiopsyToolTransformCalculator : public IBiopsyToolTransformCalculatorNav, public IBiopsyToolTransformCalculatorTracker
	{
	public:
		using ICorrelationManager_string = ICoordinateSystemCorrelationManager<std::string>;
		BiopsyToolTransformCalculator(std::shared_ptr<ICorrelationManager_string> correlationMgr, std::shared_ptr<IBiopsyToolDirFinder> dirFinder);
		void SetImageUid(const std::string& uid) override;
		void GetTransform(const std::pair<parcast::PointD3, parcast::PointD3>& points, double trans[4][4]) override;
		void SetTrackerUid(const std::string& uid) override;

	private:
		std::string m_ImageUid;
		std::string m_TrackerUid;
		std::shared_ptr<ICorrelationManager_string> m_Correlation;
		std::shared_ptr<IBiopsyToolDirFinder> m_BiopsyToolDirCalculator;
	};

}
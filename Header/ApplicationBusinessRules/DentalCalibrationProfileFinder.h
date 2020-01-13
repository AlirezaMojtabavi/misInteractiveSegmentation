#pragma once

#include "ICalibrationProfileFinder.h"

namespace parcast
{

	using ICorrelationManager_string = ICoordinateSystemCorrelationManager<std::string>;

	class DentalCalibrationProfileFinder : public ICalibrationProfileFinder
	{

	public:
		CalibrationProfile Get() const override;
		void SetUserType(const std::string& userType) override;
		void SetSubjectTrackingTool(std::shared_ptr<ITrackingTool> trackingTool) override;
		void AddCalibratedTool(const std::string& uid);
		void SetForceCompleteForDetach(bool forceComplete);

	private:
		std::shared_ptr<ITrackingTool> m_Tool;
		std::string m_UserType;
		std::set<std::string> m_CalibratedToolSet;
		bool m_ForceCompleteForDetach = false;
	};

}

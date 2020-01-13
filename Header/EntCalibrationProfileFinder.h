#pragma once
#include "ICalibrationProfileFinder.h"

namespace parcast
{

	class EntCalibrationProfileFinder : public ICalibrationProfileFinder
	{
	public:
		CalibrationProfile Get() const override;
		void SetUserType(const std::string& userType) override;
		void SetSubjectTrackingTool(std::shared_ptr<ITrackingTool> trackingTool) override;

	private:
		std::shared_ptr<ITrackingTool> m_TrackingTool;
		std::string m_UserType;
	};

}

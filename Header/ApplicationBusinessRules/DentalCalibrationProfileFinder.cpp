#include "stdafx.h"

#include "DentalCalibrationProfileFinder.h"

#include "misToolProperties.h"
#include "ITrackingTool.h"

using namespace parcast;

CalibrationProfile DentalCalibrationProfileFinder::Get() const
{
	if (m_UserType != "Admin" && m_Tool)
	{
		auto toolProp = m_Tool->GetToolProperties();

		const auto isFixed = !toolProp.HasApplicationFlag(misToolProperties::Detachable);
		const auto isCalibrated = m_CalibratedToolSet.find(toolProp.GetToolUID()) != m_CalibratedToolSet.end();

		if (isFixed || (!m_ForceCompleteForDetach && isCalibrated))
		{
			return CP_PARTIAL;
		}
	}

	return CP_COMPLETE;
}

void DentalCalibrationProfileFinder::SetUserType(const std::string& userType)
{
	m_UserType = userType;
}

void DentalCalibrationProfileFinder::SetSubjectTrackingTool(std::shared_ptr<ITrackingTool> trackingTool)
{
	m_Tool = trackingTool;
}

void DentalCalibrationProfileFinder::AddCalibratedTool(const std::string& uid)
{
	m_CalibratedToolSet.insert(uid);
}

void DentalCalibrationProfileFinder::SetForceCompleteForDetach(bool forceComplete)
{
	m_ForceCompleteForDetach = forceComplete;
}

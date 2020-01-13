#pragma once
class misTrackingStateReport;
struct RegistrationResultStr;
struct SurfaceRegistrationDataStrct;
struct mislandMarkPosAndStatusStr;

class ISurfaceRegistrationUIAdapter
{
public:
	virtual ~ISurfaceRegistrationUIAdapter()
	{
	}

	virtual void LandmarkRegistrationListUpdate(const std::vector<mislandMarkPosAndStatusStr>& landmarkList) = 0;
	virtual void UpdateSurfaceRegistrationDataInGUI(const SurfaceRegistrationDataStrct& surfaceRegData,
	                                                vtkPoints* capturePoints) = 0;
	virtual void UpdateSurfaceRegistrationErrorResult(const SurfaceRegistrationDataStrct& surfaceRegData) = 0;
	virtual void SetStatusMessage(const misTrackingStateReport& toolsStatus) = 0;
};

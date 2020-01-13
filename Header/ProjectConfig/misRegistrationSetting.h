#pragma once

#include "misProjectSettingMacro.h"
#include "misRegistrationEnums.h"
#include "misTimePassingForActionPropertiesStr.h"


struct  RegisterationSetting:public Serializable
{
	RegisterationSetting();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	// Initial number of landmark points presented to the user to be used in registration.
	int GetStartupNumberOfPointsForPointBasedRegistration() const;
	int GetMinimumPointsToAcceptSurfaceRegistration() const;
	double GetCameraVectorSize() const;
	double GetDelayBeforeLandmarkCaptureOffCalibration() const;

	int    TimeToKeepRegistrationEffect; // based on hour // Note : -1 keep the registration for ever,  used only  in debug time
	bool   LoggerEnabled;
	bool   ShowIsoSurface;
	bool   ExportIsoSurfaceToFile;
	bool   readDataFromFile;
	bool   AutoConnectOnLandRegSelection;
	int    minimumRequiredPointsForPointBasedRegistration;
	double MinimumAcceptedDistanceFromPreviousCapturedPoint;
	bool   AutoGoToTheNextPointInCapturing;
	bool   AutoGoToTheNextPointInSelection;
	double validNearestDistanceOfLankmarks; // mm
	bool   CheckNewLandmarkMaxErrorForAccepting; 
	bool   SkipNonCapturedLandmarkAutomatically;

	double DistanceOfShowinglankmarkError; // mm
	double BestErrorRange; // mm

	int    accteptableErrorForLeavelandmarkReg;
	bool   playAutoCapturingSoundInLandReg;

	bool   playAutoCapturingSoundInSurfReg;
	misLandmarkRegistarationPlaySoundStatus  PlayErrorInLandReg;
	bool   playDistanceSoundToSurfaceInSurfReg;

	misToolFixationPropertiesStr ToolFixationForAutomaticCaptureLandmark;
	misToolFixationPropertiesStr ToolFixationForAutomaticCaptureSurfaceLandmark;


	double MaxPermittedErrorForSurfaceRegistrationCapturingError; // internal check : max is 50 mm
	bool   UseAutomaticThresholdForSurfaceRegistrationCapturingError; // if true: check based on mean error up to max permitted
	double GetNearestLandmarkDistance() const { return m_NearestLandmarkDistance; }
	void SetNearestLandmarkDistance(double val) { m_NearestLandmarkDistance = val; }

private:
	int    m_MinimumPointsToAcceptSurfaceRegistration;
	int m_StartupNumberOfPointsForPointBasedRegistration;
	double m_CameraVectorSize;
	double m_DelayBeforeLandmarkCaptureOffCalibration;
	double m_NearestLandmarkDistance; // Minimum dstance allowed for registration a new point

};
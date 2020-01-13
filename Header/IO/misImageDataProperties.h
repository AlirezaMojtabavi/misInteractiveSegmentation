#pragma once
#include "misImageProperties.h"
#include "misStrctDicomHeaderInfo.h"
#include "misImageViewingProperties.h"

class misImageDataProperties
{
public:
	misImageDataProperties(void);


	void DeepCopy(misImageDataProperties* T);;
	void SetWindowParams(double center, double width);
	void SetDefaultThresholdForSkinViewing(double val);
	void SetDefaultThresholdForBoneViewing(double val);
	boost::optional<double> GetCurrentThresholdForSkinViewing() const;
	void SetCurrentThresholdForSkinViewing(double val);
	boost::optional<double> GetDefaultThresholdForSkinViewing() const;
	boost::optional<double> GetDefaultThresholdForBoneViewing() const;
	misImageViewingType GetViewingNameType() const;
	void SetViewingNameType(misImageViewingType val);
	misWindowLevelStr GetWindowlevel() const;
	void SetWindowlevel(misWindowLevelStr val);
	boost::optional<double> GetCurrentThresholdForBoneViewing() const;
	void SetCurrentThresholdForBoneViewing(double val);
	boost::optional<double> GetCurrentThresholdForTeethViewing() const;
	void SetCurrentThresholdForTeethViewing(double val);
	ImageColorTableType GetColorMapType() const;
	void SetColorMapType(ImageColorTableType val);
	misImageViewingProperties GetViewingProperties() const;
	void SetViewingProperties(misImageViewingProperties val);

	misImageingProperties     imagingProprties;
	misPatientProperties      patientProperties;
	misHardwareProperties     hardwareProperties;
	misSerieProperties        serieProperties;
	misStudyProperties        studyProperties;
	misImageProperties        imageProperties;
private:

	misImageViewingProperties m_ViewingProperties;
};


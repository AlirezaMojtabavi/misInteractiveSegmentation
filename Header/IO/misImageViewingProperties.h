#pragma once 
#include "misWindowLevelStr.h"
#include "misEnums.h"
#include <boost/optional.hpp>

class  misImageViewingProperties 
{
public:

	misImageViewingProperties();;
	void Reset(void);;

	boost::optional<double> GetDefaultThresholdForSkinViewing() const;
	boost::optional<double> GetDefaultThresholdForBoneViewing() const;
	void SetDefaultThresholdForSkinViewing(double val);
	void SetDefaultThresholdForBoneViewing(double val);
	boost::optional<double> GetCurrentThresholdForSkinViewing() const;
	void SetCurrentThresholdForSkinViewing(double val);
	boost::optional<double> GetCurrentThresholdForBoneViewing() const;
	void SetCurrentThresholdForBoneViewing(double val);
	boost::optional<double> GetCurrentThresholdForTeethViewing() const;
	void SetCurrentThresholdForTeethViewing(double val);
	boost::optional<double> GetCurrentThresholdForSkinFilledViewing() const;
	void SetCurrentThresholdForSkinFilledViewing(double val);
	misWindowLevelStr GetLevelWindow() const;
	void SetLevelWindow(misWindowLevelStr val);
	misImageViewingType GetViewingNameType() const;
	void SetViewingNameType(misImageViewingType val);
	ImageColorTableType GetColorMapType() const;
	void SetColorMapType(ImageColorTableType val);
	void SetWindowParams(double center, double width);
	misWindowLevelStr GetInitialLevelWindow() const;
	void SetInitialLevelWindow(misWindowLevelStr val);
private:

	misImageViewingType ViewingNameType = UnKnownViewingType;
	ImageColorTableType ColorMapType = UnkownColorTable;
	misWindowLevelStr m_InitialLevelWindow; // to be calculated from image mean and STD.
	misWindowLevelStr m_Windowlevel;

	boost::optional<double>  m_DefaultThresholdForSkinViewing;
	boost::optional<double> m_DefaultThresholdForBoneViewing;
	boost::optional<double> m_CurrentThresholdForSkinViewing;
	boost::optional<double> m_CurrentThresholdForBoneViewing;
	boost::optional<double> m_CurrentThresholdForTeethViewing;
	boost::optional<double> m_CurrentThresholdForSkinFilledViewing;
};

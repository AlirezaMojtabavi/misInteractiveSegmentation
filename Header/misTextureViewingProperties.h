#pragma  once

#include "misStrctColorData.h"

class misTextureViewingProperties
{
	//  MT represents MainTexture.
public:
	misTextureViewingProperties();

	int GetWindowLevelTransferFuncID() const;
	void SetWindowLevelTransferFuncID(int textureId);
	std::shared_ptr<TransFuncIntensity> GetColorMap() const;
	void SetColorMap(std::shared_ptr<TransFuncIntensity>);
	bool GetVisiblityOfColorMap() const;
	void SetVisiblityOfColorMap(bool val);
	bool GetVisiblityofSegmentedImage() const;
	void SetVisiblityofSegmentedImage(bool val);
	std::shared_ptr<TransFuncIntensity> GetSegmentedImageTransferFunc() const;
	void SetSegmentedImageTransferFunc(std::shared_ptr<TransFuncIntensity> val);
	void SetVisiblityofFmriImage(bool visible);
	bool GetVisiblityofFmriImage() const;
	float GetOpacityOfMT() const;
	void SetOpacityOfMT(float val);
	bool GetVisiblityOfMT() const;
	void SetVisiblityOfMT(bool val);
	void SetfMRIImageID(int fMRIID);
	int GetfMRIImageID();
	bool GetMainImageIsColored() const;
	void SetMainImageIsColored(bool val);
	int GetSegmentedImageID() const;
	void SetSegmentedImageID(int val);
	void SetColorValueOfMainTexture(const misDoubleColorStruct&);
	misDoubleColorStruct GetColorValueOfMainTexture()const;

	float CurrentWindowCenterOfMT;
	float CurrentWindowWidthOfMT;
	bool UseAlphaForMainBlending;
	bool UseColorForMT;
	int MainImageID;
	int FmriImageTransferFuncID;

private:

	misDoubleColorStruct m_ColorValueOfMainTexture;
	int m_SegmentedImageID;
	bool VisiblityofSegmentedImage;
	bool VisiblityOfColorMap;
	std::shared_ptr<TransFuncIntensity> m_ColorMap;
	bool mainImageIsColored;
	bool VisiblityofFmriImage;
	float m_OpacityOfMT;
	bool m_VisiblityOfMT;
	int m_fMRIID;
	std::shared_ptr<TransFuncIntensity> m_SegmentedImageTransferFunc;
	int m_WindowLevelTransferFuncID;
};

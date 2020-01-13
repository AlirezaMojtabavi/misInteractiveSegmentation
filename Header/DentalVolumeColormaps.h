#pragma once
#include "ITFIAddressMapper.h"
#include "ITFILoader.h"
#include "IVolumeRenderingColorMaps.h"
#include "misColorStruct.h"
class DentalVolumeColormaps : public IVolumeRenderingColorMaps
{
public:
	DentalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap);
	DentalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader);
	// Set Image acquisition modality (e.g. CT, MRI, PET, ...) please see misImageDataModality for complete list of modalities
	void SetImageModality(misImageDataModality imageModality) override;

	// Set Volume type (e.g. Skin, Bone, ...) please see misVolumeViewingTypes for complete list of modalities
	void SetObjectType(misVolumeViewingTypes volumeType) override;

	// Set Minimum/maximum threshold for representing the range of intensity for the specified object
	void SetObjectThreshold(double minThreshold) override;

	void SetObjectThresholdDefault(void) override;

	// Set the Color and Opacity of specified Object to the default value
	void SetObjectColorDefault(void) override;

	// Set/Get the Color and Opacity of specified Object 
	misColorStruct GetObjectColor(void) override;

	void SetObjectColor(const misColorStruct& objectColor) override {};

	misColorListTypedef GetVolumeColorMap(void) override;

	std::unique_ptr<IVolumeRenderingColorMaps> clone() override;

private:

	void  SetViewingThreshold(double minThreshold, double viewingRange);
	void  UpdateThresholds(void);
	void UpdateColorTFIList();

	misImageDataModality  m_ImageModality = NoData;
	double m_MinThreshold, m_MaxThreshold;
	double m_Range; // it used for calculating maxThreshold
	bool m_UsedDefaultThreshold = true;
 
	bool m_UseDefaultColor = true;
	std::shared_ptr<ITFILoader> m_TFILoader;
	std::shared_ptr<ITFIAddressMapper> m_TFIAddMap;
	misColorListTypedef   m_ColorList;
	misVolumeViewingTypes m_VolumeType = misVolumeViewingTypes::misTeethViewing;

};


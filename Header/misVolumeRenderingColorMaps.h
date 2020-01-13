#pragma once

#include "ITFILoader.h"
#include "ITFIAddressMapper.h"
#include "misColorStruct.h"
#include "misImageModalityEnum.h"
#include "misobjectProperitiesEnums.h"
#include "IVolumeRenderingColorMaps.h"
#include "IColorMapGenerator.h"
#include "misVolumeViewingTypes.h"


class misVolumeRenderingColorMaps : public IVolumeRenderingColorMaps
{
public:
	misVolumeRenderingColorMaps(std::shared_ptr<ITFIAddressMapper> tfiMap);
	misVolumeRenderingColorMaps(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader);
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
	void SetObjectColor(const misColorStruct& objectColor) override;
	misColorListTypedef GetVolumeColorMap(void) override;
	std::unique_ptr<IVolumeRenderingColorMaps> clone() override;

	double GetObjectThreshold();
	private:

	void SetViewingThreshold(double minThreshold, double viewingRange);
	void UpdateThresholds(void);

	void UpdateColorList(void);
	// These functions create or use the given color structure to represent a volume for each of the tissues type( Bone, Skin, ... )
	// in different modalities (MRI, CT, CBCT, ...)
	void UpdateCTList(void);
	void UpdateMRList(void);
	void UpdateCTMetalList(void);
	//void UpdateMRSkinTransparentList(void);
	void UpdateColorTFIList(misImageDataModality modality);
	// Create color map table for allviewing mode of MRI
	

	misVolumeViewingTypes m_VolumeType = misVolumeViewingTypes::misAllViewing;
	misImageDataModality m_ImageModality = NoData;
	double m_MinThreshold = 0.0;
	double m_MaxThreshold = 0.0;
	bool m_UsedDefaultThreshold = true;
	misColorStruct m_ObjectColor;
	bool m_UseDefaultColor = true;
	std::shared_ptr<ITFILoader> m_TFILoader;
	std::shared_ptr<ITFIAddressMapper> m_TFIAddMap;
	misColorListTypedef m_ColorList;
	std::shared_ptr<IColorMapGenerator> m_BoneCTColormap;
	std::shared_ptr<IColorMapGenerator> m_CTSkinFilledColorMap;
	std::shared_ptr<IColorMapGenerator> m_MRSkinFilledColorMap;
	std::shared_ptr<IColorMapGenerator> m_CTSkinTransparentColorMap;
	std::shared_ptr<IColorMapGenerator> m_MRSkinTransparentColorMap;
	std::shared_ptr<IColorMapGenerator> m_CTAllViewingColorMap;
	std::shared_ptr<IColorMapGenerator> m_MRAllViewingColorMap;
	std::shared_ptr<IColorMapGenerator> m_CTSinusViewingColorMap;
	std::shared_ptr<IColorMapGenerator> m_MRSinusViewingColorMap;

};

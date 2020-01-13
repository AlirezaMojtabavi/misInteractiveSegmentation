#pragma once
#include "ITFIAddressMapper.h"
#include "ITFILoader.h"
#include "IVolumeRenderingColorMaps.h"
#include "misColorStruct.h"
class misAnimalVolumeColormaps: public IVolumeRenderingColorMaps
{
public:
	misAnimalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap);
	misAnimalVolumeColormaps(std::shared_ptr<ITFIAddressMapper> tfiMap, std::shared_ptr<ITFILoader> TFILoader);
	~misAnimalVolumeColormaps();
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
	
private:
	void  SetObjectThreshold(double minThreshold, double range);

	void  SetViewingThreshold(double minThreshold, double viewingRange);
	void  UpdateThresholds(void);
	void  ResetObjectProperties(void);
	// Update min, max threshold for creating allViewing mode color map table 
	void UpdateThresholdForAllViewing(double& range);

	// These functions create or use the given color structure to represent a volume for each of the tissues type( Bone, Skin, ... )
	// in different modalities (MRI, CT, CBCT, ...)
	void UpdateCTSkinList(void);
	void UpdateCTBoneList(void);
	void UpdateCTList(void);
	void UpdateCTAllList(void);
	void UpdateMRSkinList(void);
	void UpdateColorTFIList();
	// to change color gradually
	misColorStruct ChangeColor(misColorStruct currentColor, int addRed, int addGreen, int addBlue);

	misImageDataModality  m_ImageModality;
	double                m_MinThreshold, m_MaxThreshold;
	double                m_Range; // it used for calculating maxThreshold
	bool                  m_UsedDefaultThreshold;
	misColorStruct        m_ObjectColor;
	bool                  m_UseDefaultColor;
	std::shared_ptr<ITFILoader> m_TFILoader;
	std::shared_ptr<ITFIAddressMapper> m_TFIAddMap;
	misColorListTypedef   m_ColorList;
	misVolumeViewingTypes m_VolumeType;

};


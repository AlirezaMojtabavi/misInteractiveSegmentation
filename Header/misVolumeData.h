#pragma once
#include "IVolumeData.h"


// The misVolumeData represent a volume rendering of 3D image 
// for rendering a volume a color map is needed
class misVolumeData : public IVolumeData
{
public:
	misVolumeData();

	// return all with default setting
	misDoubleColorListTypedef GetOpacityColorMap(misPresentationDimension presentationDim);

	std::string GetUID() const override;
	virtual void SetUID(const std::string& id);
	misCreateVariableWithProtectedSetGetMacro(ModificationFlag, bool);
	misCreateVariableWithSetGetMacro(Ambient, double);
	misCreateVariableWithSetGetMacro(Diffuse, double);
	misCreateVariableWithSetGetMacro(Specular, double);
	virtual void DeepCopy(IVolumeData *src);
	MisObjectType GetObjectType() { return this->m_ObjectType; }
	void SetRenderingType(mis3DModelRenderingType type);;
	mis3DModelRenderingType GetRenderingType();
	void Reset();
	void SetImage(std::shared_ptr<IImage> image);
	std::shared_ptr<IImage> GetIamge() const;
	void SetImageModality(misImageDataModality modality);
	misImageDataModality GetImageModality() const;
	void SetObjectName(misVolumeViewingTypes objectType, std::string name);
	std::string GetObjectName(misVolumeViewingTypes objectType);
	int GetObjectsNumber(void);
	bool IsExistObject(misVolumeViewingTypes objectType);
	void AddNewObject(misVolumeViewingTypes objectType);
	void DeleteObject(misVolumeViewingTypes objectType);
	void SetMinThreshold(misVolumeViewingTypes objectType, double minThreshold);
	void SetMinMaxThreshold(misVolumeViewingTypes objectType, double minThreshold, double maxThreshold);
	double GetMinThreshold(misVolumeViewingTypes objectType);
	void UsedDefaultThreshold(misVolumeViewingTypes objectType);
	void UsedDefaultThresholdForAll();
	void SetObjectColor(misVolumeViewingTypes objectType, misColorStruct ObjectColor);
	void UsedDefaultObjectColor(misVolumeViewingTypes objectType);
	misColorStruct GetObjectColor(misVolumeViewingTypes objectType);
	void SetViewableObjectsAll(double opacity = 0.5);
	void SetViewableObjectsDefault();
	misVolumeComponentPropTypdef GetColormaps();
	void SetColormaps(misVolumeComponentPropTypdef volumeComoponentPropertyList);
	misVolumeViewingTypes GetObjectType(misUID objectUID);
	misUID GetObjectUID(misVolumeViewingTypes objectType);

	void SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap);

	void SetAllComponentsVisibilityOFF();

	void SetComponentVisibilityAll();
	void ChangeComponentOpacity(misVolumeViewingTypes componentType, double opacity);
	misVolumeRangeColor GetObjectProperties(misVolumeViewingTypes objectType);

	bool m_ViewingModificationFlag;

	std::string GetParentImageUID() const;
	void SetParentImageUID(std::string val);
private:

	// convert m_VolumesProperties to m_OpacityColorMappingFinal for construction a transfer function 
	void ConvertVolumePropToColorKeys(misPresentationDimension presentationDim);
	void FillFinalColorMap(misColorListTypedef objectColorMap, double opacity);
	void CheckObjectUID(misVolumeRangeColor& volumeComponentProperties);
	void ResetProperties(void);

	int m_ScalarType;
	bool m_MisImageFlag;
	misImageDataModality m_ImageModality;
	MisObjectType m_ObjectType;
	mis3DModelRenderingType m_RenderingType;
	misApplicationSetting* m_AppSetting;
	// It maps different types of objects (e.g. skin, bone, metal, ...) to their color and other representation properties. 
	misVolumeComponentPropTypdef m_VolumesProperties;
	misDoubleColorListTypedef m_OpacityColorMappingFinal;
	// use this flag as a opacity, 0 i.e. invisible
	double m_ViewAllObjectsOpacity;
	bool m_ComponentHasBeenChanged;
	std::string m_DataObjectUID;
	std::shared_ptr<IImage> m_Image;
	std::string  m_ParentImageUID;
};

typedef std::vector<std::shared_ptr<IVolumeData>> VolumeDataListTypedef;

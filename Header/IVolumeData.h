#pragma once

#include "ICoordinateSystem.h"
#include "misEnums.h"
#include "misMacros.h"
#include "misVolumeViewingTypes.h"

class misApplicationSetting;
class IImage;
class mis3DModelObjectOpacityPropertiesStrct;

struct misDoubleColorStruct;
struct misColorStruct;
struct misVolumeRangeColor;

enum mis3DModelRenderingType;
enum misImageDataModality;


typedef  std::map<double, misDoubleColorStruct>	misDoubleColorListTypedef;
typedef std::map<misVolumeViewingTypes, misVolumeRangeColor>  misVolumeComponentPropTypdef;
typedef std::string misUID;
typedef std::map<misUID, mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityMap;
typedef  std::map<float, misColorStruct> misColorListTypedef;


class IVolumeData : public ICoordinateSystem
{
public:
	virtual ~IVolumeData() = default;
 	virtual misDoubleColorListTypedef GetOpacityColorMap(misPresentationDimension presentationDim) = 0;
	virtual void DeepCopy(IVolumeData *src) = 0;
	virtual MisObjectType GetObjectType() = 0;
	virtual void SetRenderingType(mis3DModelRenderingType type) = 0;
	virtual mis3DModelRenderingType GetRenderingType() = 0;
	virtual void Reset() = 0;
	virtual void SetImage(std::shared_ptr<IImage> image) = 0;
	virtual std::shared_ptr<IImage> GetIamge() const = 0;
	virtual void SetImageModality(misImageDataModality modality) = 0;
	virtual misImageDataModality GetImageModality()  const = 0;
	virtual void SetObjectName(misVolumeViewingTypes objectType, std::string name) = 0;
	virtual std::string GetObjectName(misVolumeViewingTypes objectType) = 0;
	virtual int GetObjectsNumber(void) = 0;
	virtual bool IsExistObject(misVolumeViewingTypes objectType) = 0;
	virtual void AddNewObject(misVolumeViewingTypes objectType) = 0;
	virtual void DeleteObject(misVolumeViewingTypes objectType) = 0;
	virtual void SetMinThreshold(misVolumeViewingTypes objectType, double minThreshold) = 0;
	virtual void SetMinMaxThreshold(misVolumeViewingTypes objectType, double minThreshold, double maxThreshold) = 0;
	virtual double GetMinThreshold(misVolumeViewingTypes objectType) = 0;
	virtual void UsedDefaultThreshold(misVolumeViewingTypes objectType) = 0;
	virtual void UsedDefaultThresholdForAll() = 0;
	virtual void SetObjectColor(misVolumeViewingTypes objectType, misColorStruct ObjectColor) = 0;
	virtual void UsedDefaultObjectColor(misVolumeViewingTypes objectType) = 0;
	virtual misColorStruct GetObjectColor(misVolumeViewingTypes objectType) = 0;
	virtual void SetViewableObjectsAll(double opacity = 0.5) = 0;
	virtual void SetViewableObjectsDefault() = 0;
	virtual misVolumeComponentPropTypdef GetColormaps() = 0;
	virtual void SetColormaps(misVolumeComponentPropTypdef volumeComoponentPropertyList) = 0;
	virtual misVolumeViewingTypes GetObjectType(misUID objectUID) = 0;
	virtual misUID GetObjectUID(misVolumeViewingTypes objectType) = 0;
	virtual void SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap) = 0;
	virtual void SetAllComponentsVisibilityOFF() = 0;
	virtual void SetComponentVisibilityAll() = 0;
	virtual void ChangeComponentOpacity(misVolumeViewingTypes componentType, double opacity) = 0;
	virtual misVolumeRangeColor GetObjectProperties(misVolumeViewingTypes objectType) = 0;
	virtual std::string GetParentImageUID() const = 0;
	virtual void SetParentImageUID(std::string val) = 0;
};

#pragma once
#include "misVolumeViewingTypes.h"
#include "IVolumeDataDependency.h"

class misVolumeDataDependensies;
class mis3DModelObjectOpacityPropertiesStrct;
class IImage;

enum mis3DModelTypes;

typedef std::string misUID;
typedef std::map<misUID, mis3DModelObjectOpacityPropertiesStrct> misObjectVisibilityMap;

// The misBoneSkineVolume class generate skin bone and composite them and generate  a volume dependency
class IBoneSkineVolume
{
public:
	virtual void SetImage(std::shared_ptr<IImage> image) = 0;
	virtual void SetMinThreshold(const mis3DModelTypes obJcetType, const double threshold) = 0;
	virtual std::shared_ptr<IVolumeDataDependency> GetVolumeData() const = 0;
	virtual misUID GetVolumeUID() const = 0;
	virtual misUID GetVolumeViewingTypeUID(const mis3DModelTypes obJcetType) = 0;
	virtual misObjectVisibilityMap GetVisibiltyMap() = 0;
	virtual void SetObjectName(misVolumeViewingTypes objectType, std::string name) = 0;
	virtual void UpdateVolumeRedeingSceneBasedOnNormalizedThreshold(mis3DModelTypes objectType,
		misVolumeViewingTypes ObjectVolumeViewing, double normalizedThreshold) = 0;
	virtual void UpdateHeadRestRenderingBasedOnNormalizedThreshold(mis3DModelTypes objectType,
		misVolumeViewingTypes ObjectVolumeViewing, double normalizedThreshold) = 0;
	virtual void AddToCoordinateSystem()  = 0;
	virtual void HideCurrenVolume() = 0;
	virtual void ShowAllVolume() = 0;
	virtual void SetColorMapTransferFunction(std::shared_ptr<TransFuncIntensity> transfunc) = 0;
	virtual double GetPreviosThreshold(misVolumeViewingTypes ObjectVolumeViewing)  = 0;
	virtual ~IBoneSkineVolume()
	{}
};

#pragma once

#include "misLandmarkenums.h"
#include "misObjectRangeStr.h"
#include "misobjectProperitiesEnums.h"
#include "IPackage3DDataRenderingAdapter.h"
#include "IViewingTypeColormapSelector.h"
#include "I3DModelTypeSelector.h"
#include "ILandmarkVolumeSelector.h"
#include "IDefualtVolumeThresholdFinder.h"
#include "IValidateVolumeThreshold.h"
#include "IVolumeUpdater.h"
#include "misVolumeViewingTypes.h"

// This class select colormap of volumes based on model Types(Skin/ Bone and ...) and Application Types

class IImage;
class IPackageDataRenderingAdapter;
class ISimpleDataPackage;
class misApplicationSetting;
class misVolumeDataDependensies;
class INavigationViewersNView;

class misSpineViewingTypeColormapSelector : public IViewingTypeColormapSelector
{
public:
	misSpineViewingTypeColormapSelector(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::unique_ptr<I3DModelTypeSelector> modelSelctor, std::unique_ptr<ILandmarkVolumeSelector> volumelSelector,
	                                    std::unique_ptr<IDefualtVolumeThresholdFinder> thresholdFinder,
	                                    std::unique_ptr<IValidateVolumeThreshold> validateThreshold,
		std::unique_ptr<IVolumeUpdater> volumeUpdater);
	void SelectVolumeType(misVolumeViewingTypes volumeType) override;
	void SetCurrentModelType(mis3DModelTypes val) override;
	void SetCurrentVolumeThreshold(double val) override;
	misVolumeViewingTypes GetCurrentVolumeType() const override;
	mis3DModelTypes GetCurrentModelType() const override;
	void ModifyCurrentSelectedLandmark(int landmarkIndex, misVolumeViewingTypes volumeType) override;
	double GetCurrentVolumeThreshold() const override;
	double GetCurrentThreshold() const override;
	boost::optional<misObjectRangeStr> GetValidObjectThresholdRange() const override;
	misLandmarkType GetLandmarkTypeOfCurrentVolume() const override;
	virtual void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage>) override;
	void ShowVolume() override;

private:
	
	void SetVolumeRenderingThresholdForImage(double normalizedThreshold, misVolumeViewingTypes volumeType) const;
	bool NormalizedVolumeThreshold();
	void UpdateVolumeDependency() ;

	misVolumeViewingTypes	m_CurrentVolumeType;
	mis3DModelTypes m_CurrentModelType;
	std::weak_ptr<IImage> m_CurrentImage;	
	std::shared_ptr<INavigationViewersNView>	m_GroupViewer;
	std::shared_ptr<IPackage3DDataRenderingAdapter> m_PackageViewer;
	std::weak_ptr<ISimpleDataPackage>  m_Package;
	double m_CurrentVolumeThreshold = -1;
	std::unique_ptr<I3DModelTypeSelector> m_ModelSelector;
	std::unique_ptr<ILandmarkVolumeSelector> m_VolumelSelector;
	std::unique_ptr<IDefualtVolumeThresholdFinder> m_ThresholdFinder;
	std::unique_ptr<IValidateVolumeThreshold> m_ValidateThreshold;
	std::unique_ptr<IVolumeUpdater> m_VolumeUpdater;
	std::shared_ptr<IVolumeDataDependency> m_Volume;
	bool m_ResetCameraSettings = false;
};


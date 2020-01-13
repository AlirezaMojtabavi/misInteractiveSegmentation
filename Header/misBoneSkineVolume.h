#pragma once
#include "IBoneSkineVolume.h"
#include "IVolumeDataDependency.h"

// The misBoneSkineVolume class generate skin bone and composite them and generate  a volume dependency
class misBoneSkineVolume : public IBoneSkineVolume
{
public:
	misBoneSkineVolume();
	void SetImage(std::shared_ptr<IImage> image) override;
	void SetMinThreshold(const mis3DModelTypes obJcetType, const double threshold) override;
	std::shared_ptr<IVolumeDataDependency> GetVolumeData() const override;
	misUID GetVolumeUID() const override;
	misUID GetVolumeViewingTypeUID(const mis3DModelTypes obJcetType) override;
	misObjectVisibilityMap GetVisibiltyMap()override;
	void SetObjectName(misVolumeViewingTypes objectType, std::string name) override;
	void AddToCoordinateSystem() override;
	void UpdateVolumeRedeingSceneBasedOnNormalizedThreshold(mis3DModelTypes objectType,
		misVolumeViewingTypes ObjectVolumeViewing, double normalizedThreshold) override;
	double GetPreviosThreshold(misVolumeViewingTypes ObjectVolumeViewing)  final;
	void UpdateHeadRestRenderingBasedOnNormalizedThreshold(mis3DModelTypes objectType,
		misVolumeViewingTypes ObjectVolumeViewing,
		double normalizedThreshold)override;
	void HideCurrenVolume() override;
	void ShowAllVolume()override;
	void SetColorMapTransferFunction(std::shared_ptr<TransFuncIntensity> transfunc) override;

private:

	void MergeVolumeDataRepresentation();
	misVolumeViewingTypes GetVolumeViewingtype(const mis3DModelTypes obJcetType) const;

	std::shared_ptr<IVolumeDataDependency> m_VolumeData;
	std::shared_ptr<IImage> m_Image;
	misObjectVisibilityMap	m_OriginalVolumeMap;
};
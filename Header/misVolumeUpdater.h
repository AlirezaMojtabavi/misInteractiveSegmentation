#pragma once
#include "IVolumeUpdater.h"
#include "ISimpleDataPackage.h"
#include "IPackageVolumeUpdater.h"
#include "IVolumeFactory.h"

class misVolumeUpdater : public IVolumeUpdater
{
public:
	misVolumeUpdater(std::shared_ptr<IVolumeFactory> volumeFactory);
	std::shared_ptr<IVolumeDataDependency> Update(double volumeThrshold, misVolumeViewingTypes volumeType,
	                                                std::shared_ptr<IImage> currentImage) override;
	void ClearVolumeThreshold() override;
private:
	boost::optional<double> m_VolumeThrshold;
	std::shared_ptr<IVolumeDataDependency> m_Volume;
	std::shared_ptr<IVolumeFactory> m_VolumeFactory;
};


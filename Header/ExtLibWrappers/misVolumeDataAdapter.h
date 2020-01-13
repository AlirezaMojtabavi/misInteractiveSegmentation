#pragma once

#include "IArrayBinaryCodec.h"
#include "IDatasetManager.h"
#include "IPackageVolumeDataAccess.h"
#include "IPackageVolumeVisibiltyRelDataAccess.h"
#include "IVolumeColormapDataAccess.h"
#include "IVolumeDataAccess.h"
#include "IVolumeDataAdapter.h"
#include "misVolumeData.h"
#include "IVolumeDataDependency.h"

namespace parcast
{

	class misVolumeDataAdapter : public IVolumeDataAdapter
	{
	public:
		misVolumeDataAdapter(
			IDatasetManager* datasetManager,
			std::shared_ptr<IVolumeDataAccess> VolumeDataAccess,
			std::shared_ptr<IVolumeColormapDataAccess> colormap,
			std::shared_ptr<IPackageVolumeDataAccess>pkgVolumeRelDataAccess, 
			std::shared_ptr<IPackageVolumeVisibiltyRelDataAccess> visibiltyDataAcces);

		void Save() override;
		void Load() override;

	private:
		VolumeData ConvertVolumeToVolumeData(std::shared_ptr<IVolumeData> Volume) const;
		PackageVolumeData ConvertVolumeDepToPkgRelData(
			std::shared_ptr<IVolumeDataDependency> VolumeDep, const std::string& packageUid) const;
		std::shared_ptr<misVolumeData> CreateVolumeFromVolumeData(VolumeData const& VolumeData) const;

		std::shared_ptr<IVolumeDataDependency> ConvertRelDataToVolumeDep(
			PackageVolumeData const& relData, std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IVolumeData> Volume);

		IDatasetManager* m_DatasetManager;
		std::shared_ptr<IVolumeDataAccess> m_VolumeDataAccess;
		std::shared_ptr<IVolumeColormapDataAccess> m_VolumeColormapDataAccess;
		std::shared_ptr<IPackageVolumeDataAccess> m_PkgVolumeRelDataAccess;
		std::shared_ptr<IPackageVolumeVisibiltyRelDataAccess> m_VisibilityDataAccess;

	};
}

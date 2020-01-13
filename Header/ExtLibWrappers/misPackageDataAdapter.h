#pragma once

#include "IPackageDataAdapter.h"
#include "LandmarkData.h"
#include "PackageImageRelationship.h"

class IDatasetManager;
class ISimpleDataPackage;
class ICompeleteImageDependencies;

struct misLandmarkPointStrct;

namespace  parcast
{

	class ILandmarkDataAccess;
	class IPackageDataAccess;
	class IPackageImageRelDataAccess;
	class IPanoramicDataAccess;
	class IPointListCodec;

	class misPackageDataAdapter : public IPackageDataAdapter
	{
	public:
		misPackageDataAdapter(IDatasetManager* datasetManager,
			std::shared_ptr<parcast::IPackageDataAccess> packageDataAccess,
			std::shared_ptr<parcast::IPackageImageRelDataAccess> packageImageRelDataAccess,
			std::shared_ptr<parcast::ILandmarkDataAccess> landmarkDataAccess,
			std::shared_ptr<parcast::IPanoramicDataAccess> panoramicDataAccess,
			std::shared_ptr<parcast::IPointListCodec> pointListCodec);
		~misPackageDataAdapter();

		virtual void SavePackages() override;
		virtual void LoadPackages() override;

	private:
		parcast::PackageImageRelationship CreatePackageImageDepData(const std::shared_ptr<ICompeleteImageDependencies>) const;
		parcast::LandmarkData CreateLandmarkData(const misLandmarkPointStrct& landmark, const std::string& packageUid) const;
		void SetPackageImageRelationship(const std::vector<PackageImageRelationship>& packageImageRels,
			std::shared_ptr<ISimpleDataPackage> package);
		void SetLandmarks(const std::vector<LandmarkData>& landmarksData, const std::shared_ptr<ISimpleDataPackage> package);
		void SavePackageData(std::string currentSolutionUid, std::vector<std::shared_ptr<ISimpleDataPackage>>::value_type const& package, std::string packageUid);
		void SavePackageImageRelData(std::vector<std::shared_ptr<ISimpleDataPackage>>::value_type const& package, std::string packageUid);
		void SaveLandmarkData(std::vector<std::shared_ptr<ISimpleDataPackage>>::value_type const& package, std::string packageUid);
		void SetPanoramic(std::shared_ptr<ISimpleDataPackage> package, std::vector<PackageImageRelationship> packageImageRelData);
		void SavePanoramicData(std::shared_ptr<ISimpleDataPackage> package) const;

		IDatasetManager* m_DatasetManager;
		std::shared_ptr<parcast::IPackageDataAccess> m_PackageDataAccess;
		std::shared_ptr<parcast::IPackageImageRelDataAccess> m_PackageImageRelDataAccess;
		std::shared_ptr<parcast::ILandmarkDataAccess> m_LandmarkDataAccess;
		std::shared_ptr<parcast::IPanoramicDataAccess> m_PanoramicDataAccess;
		std::shared_ptr<parcast::IPointListCodec> m_PointListCodec;
	};

}
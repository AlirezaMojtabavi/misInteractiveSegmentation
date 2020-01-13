#pragma once

#include "IPlanDataAdapter.h"
#include "PackageItemRelData.h"
#include "PlanData.h"
#include "IPackagePlanRel.h"

class IDatasetManager;
class ISimpleDataPackage;
class misVertebraScrewPlanData;

template < typename CST >
class ICoordinateSystemCorrelationManager;

namespace parcast
{

	class IPackageItemDataAccess;
	class IPackageItemRelDataAccess;
	class IPlanDataAccess;
	class IPlanTransformCalculator;

	class misPlanDataAdapter : public IPlanDataAdapter
	{
	public:
		misPlanDataAdapter(
			IDatasetManager* datasetManager,
			std::shared_ptr<IPlanDataAccess> planDataAccess,
			std::shared_ptr<IPackageItemDataAccess> packageItemDataAccess,
			std::shared_ptr<IPackageItemRelDataAccess> packageItemRelDataAccess,
			std::shared_ptr<IPlanTransformCalculator> planTransformCalculator);

		void Save() override;
		void Load() override;

	private:
		PlanData ConvertPlanToPlanData(std::weak_ptr<misVertebraScrewPlanData> plan) const;

		PackageItemRelData ConvertPlanDepToPkgRelData(
			std::shared_ptr<parcast::IPackagePlanRel> planDep, const std::string& packageUid) const;

		void CreateScrewPlanFromPlanData(
			std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, PlanData const& planData) const;

		void ConvertRelDataToPlanDep(
			PackageItemRelData const& relData, std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IPlan> plan);

		IDatasetManager* m_DatasetManager;
		std::shared_ptr<IPlanDataAccess> m_PlanDataAccess;
		std::shared_ptr<IPackageItemDataAccess> m_PkgItemDataAccess;
		std::shared_ptr<IPackageItemRelDataAccess> m_PkgItemRelDataAccess;
		std::shared_ptr<IPlanTransformCalculator> m_PlanTransCalculator;
	};

}

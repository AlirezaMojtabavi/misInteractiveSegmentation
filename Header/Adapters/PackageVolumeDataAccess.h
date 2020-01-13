#pragma once


#include "IDataBaseConnection.h"
#include "IPackageVolumeDataAccess.h"
#include "IPackageVolumeQueryBuilder.h"

namespace parcast
{

	class PackageVolumeDataAccess : public IPackageVolumeDataAccess
	{
	public:
		PackageVolumeDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IPackageVolumeQueryBuilder> queryBuilder);

		void Insert(const PackageVolumeData& data) override;
		std::vector<PackageVolumeData> GetByPackageUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IPackageVolumeQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}

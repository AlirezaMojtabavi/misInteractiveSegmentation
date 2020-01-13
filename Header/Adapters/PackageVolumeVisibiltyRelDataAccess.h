#pragma once
 
#include "IDataBaseConnection.h"
#include "IVolumeVisibiltyQueryBuilder.h"
#include "IPackageVolumeVisibiltyRelDataAccess.h"

namespace parcast
{

	class PackageVolumeVisibiltyRelDataAccess : public   IPackageVolumeVisibiltyRelDataAccess
	{
	public:
		PackageVolumeVisibiltyRelDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IVolumeVisibiltyQueryBuilder> queryBuilder);

		void Insert(const VolumeVisibility& data) override;
		std::vector<VolumeVisibility> GetByVolumeUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IVolumeVisibiltyQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}

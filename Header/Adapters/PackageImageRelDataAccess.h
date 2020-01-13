#pragma once

#include "IDataBaseConnection.h"
#include "IPackageImageRelDataAccess.h"
#include "IPackageImageRelQueryBuilder.h"

namespace parcast
{

	class PackageImageRelDataAccess : public IPackageImageRelDataAccess
	{
	public:
		PackageImageRelDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection, 
			std::shared_ptr<IPackageImageRelQueryBuilder> queryBuilder);

		virtual void InsertOrUpdate(const PackageImageRelationship& data) override;
		virtual std::vector<PackageImageRelationship> GetByPackageUid(const std::string& uid) override;
		virtual void DeleteByImageUid(const std::string& uid) override;

	private:
		void BindParameters(std::shared_ptr<IDataBaseCommand> dbCommand, const PackageImageRelationship& data);

		std::shared_ptr<IDataBaseConnection> m_DataBaseConnection;
		std::shared_ptr<IPackageImageRelQueryBuilder> m_QueryBuilder;
	};

}
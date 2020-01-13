#pragma once

#include "IDataBaseConnection.h"
#include "IPackageDataAccess.h"
#include "IPackageQueryBuilder.h"

namespace parcast
{

	class PackageDataAccess : public IPackageDataAccess
	{
	public:
		PackageDataAccess(
			std::shared_ptr<IDataBaseConnection> dbConnection, std::shared_ptr<IPackageQueryBuilder> dbQueryBuilder);

		virtual void InsertOrUpdate(const PackageData& inPackageData) override;
		virtual std::vector<PackageData> GetBySolutionUid(const std::string& solutionUid) override;

	private:
		void BindParameters(std::shared_ptr<IDataBaseCommand> dbCommand, const PackageData& data);
		
		std::shared_ptr<IDataBaseConnection> m_DataBaseConnection;
		std::shared_ptr<IPackageQueryBuilder> m_PackageQueryBuilder;
	};

}

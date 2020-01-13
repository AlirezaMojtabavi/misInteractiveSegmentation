#pragma once

#include "IDataBaseConnection.h"
#include "IImageContainedVisibilityQueryBuilder.h"
#include "IPackageImageContainedVisibilityDataAccess.h"

namespace parcast
{

	class PackageImageContainedVisibilityDataAccess : public   IPackageImageContainedVisibilityDataAccess
	{
	public:
		PackageImageContainedVisibilityDataAccess(std::shared_ptr<IDataBaseConnection> dbConnection,
			std::shared_ptr<IImageContainedVisibilityQueryBuilder> queryBuilder);

		void Insert(const ImageContainedVisibility& data) override;
		std::vector<ImageContainedVisibility> GetByImageContainedUid(const std::string& uid) const override;

	private:
		std::shared_ptr<IImageContainedVisibilityQueryBuilder> m_QueryBuilder;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
	};

}

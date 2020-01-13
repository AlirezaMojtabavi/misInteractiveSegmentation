#pragma once
#include "ILandmarkDataAccess.h"
#include "ConnectionGuard.h"
#include "IDataBaseConnection.h"
#include "ILandmarkQueryBuilder.h"
#include <memory>

namespace parcast
{
	class LandmarkDataAccess : public ILandmarkDataAccess
	{
	public:
		LandmarkDataAccess(std::shared_ptr<IDataBaseConnection> connection, std::shared_ptr<ILandmarkQueryBuilder> queryBuilder);
		virtual void DeleteByPackageUid(const std::string& uid) override;
		virtual void Insert(const LandmarkData& data) override;
		virtual std::vector<LandmarkData> GetByPackageUid(const std::string& uid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DataBaseConnection;
		std::shared_ptr<ILandmarkQueryBuilder> m_QueryBuilder;
	};
}

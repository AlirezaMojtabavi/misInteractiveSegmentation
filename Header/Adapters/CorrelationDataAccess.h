#pragma once

#include "ICorrelationDataAccess.h"
#include "ICorrelationQueryBuilder.h"
#include "IDataBaseConnection.h"

namespace parcast
{

	class CorrelationDataAccess : public ICorrelationDataAccess
	{
	public:
		CorrelationDataAccess(
			std::shared_ptr<IDataBaseConnection> dbConnection, std::shared_ptr<ICorrelationQueryBuilder> dbQueryBuilder);

		virtual void Insert(const std::vector<CorrelationData>& list) override;
		virtual std::vector<CorrelationData> GetBySolutionUid(const std::string& uid) override;
		virtual void DeleteBySolutionUid(const std::string& uid) override;
		virtual void DeleteByCoordSysUid(const std::string& uid) override;
		virtual void DeleteAll() override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DatabaseConnection;
		std::shared_ptr<ICorrelationQueryBuilder> m_QueryBuilder;
	};

}

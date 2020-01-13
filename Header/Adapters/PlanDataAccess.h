#pragma once

#include "IPlanDataAccess.h"

#include "IDataBaseConnection.h"
#include "IPlanQueryBuilder.h"

namespace parcast
{

	class PlanDataAccess : public IPlanDataAccess
	{
	public:
		PlanDataAccess(std::shared_ptr<IDataBaseConnection> connection, std::shared_ptr<IPlanQueryBuilder> queryBuilder);

		void Insert(const PlanData& data) override;
		std::vector<PlanData> GetBySolutionUid(const std::string& uid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IPlanQueryBuilder> m_QueryBuilder;
	};

}

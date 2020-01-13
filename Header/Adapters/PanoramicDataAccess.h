#pragma once
#include "IPanoramicDataAccess.h"
#include "IDataBaseConnection.h"
#include "IPanoramicQueryBuilder.h"

namespace  parcast
{
	class PanoramicDataAccess : public IPanoramicDataAccess
	{
	public:
		PanoramicDataAccess(std::shared_ptr<IDataBaseConnection> connection, std::shared_ptr<IPanoramicQueryBuilder> queryBuilder);
		virtual void InsertOrUpdate(const PanoramicData& panoramicData) override;
		virtual std::vector<PanoramicData> GetByImageUid(const std::string& imageUid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IPanoramicQueryBuilder> m_QueryBuilder;
	};

}

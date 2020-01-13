#pragma once

#include "ICoordinateSystemDataAccess.h"
#include "ICoordinateSystemQueryBuilder.h"
#include "IDataBaseConnection.h"

namespace parcast
{

	class CoordinateSystemDataAccess : public ICoordinateSystemDataAccess
	{
	public:
		CoordinateSystemDataAccess(
			std::shared_ptr<IDataBaseConnection> dbConnection, std::shared_ptr<ICoordinateSystemQueryBuilder> dbQueryBuilder);

		virtual void InsertIfNotExists(const std::string& coordinateSystemUid) override;
		virtual void Delete(const std::string& coordinateSystemUid) override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DatabaseConnection;
		std::shared_ptr<ICoordinateSystemQueryBuilder> m_QueryBuilder;
	};

}


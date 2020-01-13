#pragma once

#include "IDatabaseInitializer.h"
#include "IDataBaseConnection.h"

namespace parcast
{

	class DatabaseInitializer : public IDatabaseInitializer
	{
	public:
		explicit DatabaseInitializer(std::shared_ptr<IDataBaseConnection> dbConnection);

		virtual void AddQuerybuilder(std::shared_ptr<ITableQueryBuilder> queryBuilder) override;
		virtual void Initialize() const override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DatabaseConnection;
		std::vector<std::shared_ptr<ITableQueryBuilder>> m_TableQueryBuilderList;
	};

}



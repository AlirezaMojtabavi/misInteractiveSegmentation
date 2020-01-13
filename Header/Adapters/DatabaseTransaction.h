#pragma once

#include "IDataBaseConnection.h"
#include "IDatabaseTransactionQueryBuilder.h"
#include "IDataBaseTransaction.h"

namespace parcast
{

	class DatabaseTransaction : public IDataBaseTransaction
	{
	public:
		DatabaseTransaction(std::shared_ptr<IDataBaseConnection> databaseConnection,
			std::shared_ptr<IDatabaseTransactionQueryBuilder> queryBuilder);
		~DatabaseTransaction();
		void Commit() override;

	private:
		std::shared_ptr<IDataBaseConnection> m_DataBaseConnection;
		std::shared_ptr<IDatabaseTransactionQueryBuilder> m_QueryBuilder;
		bool m_Committed = false;
	};
}

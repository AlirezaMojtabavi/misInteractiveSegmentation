#pragma once

#include "DatabaseTransaction.h"
#include "IDataBaseConnection.h"
#include "IDatabaseTransaction.h"
#include "IDatabaseTransactionQueryBuilder.h"
#include "ITransactionFactory.h"

using namespace parcast;

class SqliteTransactionFactory : public ITransactionFactory
{
public:
	SqliteTransactionFactory(std::shared_ptr<parcast::IDatabaseTransactionQueryBuilder> queryBuilder);

	std::unique_ptr<parcast::IDataBaseTransaction> CreateTransaction(
		std::shared_ptr<parcast::IDataBaseConnection> connection) override;

private:
	std::shared_ptr<parcast::IDatabaseTransactionQueryBuilder> m_QueryBuilder;
};

#pragma once

#include "IDatabaseTransaction.h"
#include "IDataBaseConnection.h"

namespace parcast
{
	class ITransactionFactory
	{
	public:
		virtual std::unique_ptr<parcast::IDataBaseTransaction> CreateTransaction(
			std::shared_ptr<parcast::IDataBaseConnection> connection) = 0;
		virtual ~ITransactionFactory() { }
	};
}

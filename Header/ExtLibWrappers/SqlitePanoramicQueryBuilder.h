#pragma once
#include "IPanoramicQueryBuilder.h"
#include "IDataBaseCommandFactory.h"
#include <memory>

namespace parcast
{
	class SqlitePanoramicQueryBuilder : public IPanoramicQueryBuilder
	{
	public:
		explicit SqlitePanoramicQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);
		
		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByImageUidQuery() const override;
	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};
}

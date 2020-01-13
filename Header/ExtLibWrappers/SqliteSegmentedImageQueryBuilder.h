#pragma once

#include "IDataBaseCommandFactory.h"
#include "ISegmentedImageQueryBuilder.h"

namespace parcast
{

	class SqliteSegmentedImageQueryBuilder : public ISegmentedImageQueryBuilder
	{
	public:
		SqliteSegmentedImageQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<IDataBaseCommand> GetSelectByImageUidQuery() override;

		std::shared_ptr<parcast::IDataBaseCommand> GetSelectUidsBySolutionUidQuery() const override;
		
	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}
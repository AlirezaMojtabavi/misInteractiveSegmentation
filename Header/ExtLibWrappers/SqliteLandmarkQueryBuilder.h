#pragma once

#include "IDataBaseCommandFactory.h"
#include "ILandmarkQueryBuilder.h"

namespace parcast
{

	class SqliteLandmarkQueryBuilder : public ILandmarkQueryBuilder
	{
	public:
		SqliteLandmarkQueryBuilder(std::shared_ptr<parcast::IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByPackageUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const override;

	private:
		std::shared_ptr<parcast::IDataBaseCommandFactory> m_CommandFactory;
	};

}

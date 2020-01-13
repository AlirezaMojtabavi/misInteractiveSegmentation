#pragma once

#include "IDataBaseConnection.h"

namespace parcast
{

	class IDateTimeOperation;
	class ISqliteQueryResultFactory;

	class SqliteDataBaseConnection : public IDataBaseConnection
	{
	public:
		SqliteDataBaseConnection(
			const std::string & filePath, 
			std::shared_ptr<ISqliteQueryResultFactory> queryResultFactory,
			std::shared_ptr<IDateTimeOperation> dateTimeOps);
		~SqliteDataBaseConnection();

		virtual void Open() override;
		virtual bool IsOpen() const override;
		virtual void Close() override;
		virtual std::shared_ptr<IQueryResult> Exec(std::shared_ptr<const IDataBaseCommand> dbCommand) override;
		virtual void SetFilePath(const std::string& path) override;

	private:
		sqlite3_stmt* PrepareStatement(const std::string& queryStr);

		sqlite3 * m_DataBase;
		std::string m_DataBaseFileName;
		std::shared_ptr<ISqliteQueryResultFactory> m_QueryResultFactory;
		std::shared_ptr<IDateTimeOperation> m_DateTimeOps;
	};

}

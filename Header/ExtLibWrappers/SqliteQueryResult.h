#pragma once

#include "IDateTimeOperation.h"
#include "IArrayBinaryCodec.h"
#include "IQueryResult.h"

namespace parcast
{

	class SqliteQueryResult : public IQueryResult
	{
	public:
		SqliteQueryResult(sqlite3_stmt* sqliteStmt, const std::shared_ptr<IDateTimeOperation> dateTimeOps);
		~SqliteQueryResult();

		virtual void Next() override;
		virtual bool HasData() override;
		virtual std::string GetString(int colIndex) override;
		virtual long long int GetInt(int colIndex) override;
		virtual double GetDouble(int colIndex) override;
		virtual bool GetBool(int colIndex) override;
		virtual DateTime GetDateTime(int colIndex) override;
		virtual std::shared_ptr<ByteArray> GetBinary(int colIndex) override;

	private:
		void CheckStatus();

		sqlite3_stmt* m_SqliteStmt;
		int m_SqliteStatus;
		std::shared_ptr<IDateTimeOperation> m_DateTimeOps;
		void ThrowExceptionIfTableEmpty();
	};

}

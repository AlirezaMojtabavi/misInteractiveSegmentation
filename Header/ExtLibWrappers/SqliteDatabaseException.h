#pragma once

namespace parcast
{
	class SqliteDatabaseException : public std::exception
	{
	public:
		SqliteDatabaseException(const char* message);
		SqliteDatabaseException(const char* message, int resultCode);

		int ResultCode() const;

	private:
		int m_ResultCode;
	};
}

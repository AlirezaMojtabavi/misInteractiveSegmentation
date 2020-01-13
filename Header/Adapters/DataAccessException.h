#pragma once

namespace parcast
{
	class DataAccessException : public std::exception
	{
	public:
		DataAccessException(const char* message);
	};
}

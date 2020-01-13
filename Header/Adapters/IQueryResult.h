#pragma once

#include "DateTime.h"

namespace parcast
{

	typedef std::vector<std::uint8_t> ByteArray;

	class IQueryResult
	{
	public:
		virtual void Next() = 0;
		virtual bool HasData() = 0;
		virtual std::string GetString(int colIndex) = 0;
		virtual long long int GetInt(int colIndex) = 0;
		virtual double GetDouble(int colIndex) = 0;
		virtual bool GetBool(int colIndex) = 0;
		virtual DateTime GetDateTime(int colIndex) = 0;
		virtual std::shared_ptr<ByteArray> GetBinary(int colIndex) = 0;

		virtual ~IQueryResult() { }
	};

}

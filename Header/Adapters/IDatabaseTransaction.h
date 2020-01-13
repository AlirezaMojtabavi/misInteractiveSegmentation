#pragma once

#include "IDataBaseCommand.h"
#include "IQueryResult.h"

namespace parcast
{

	class IDataBaseTransaction
	{
	public:
		virtual void Commit() = 0;

		virtual ~IDataBaseTransaction() { }
	};

}
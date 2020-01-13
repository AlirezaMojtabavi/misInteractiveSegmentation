#pragma once

#include "IDataBaseCommand.h"

namespace parcast
{
	class IDataBaseCommandFactory
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> CreateCommand() = 0;

		virtual ~IDataBaseCommandFactory() { }
	};
}



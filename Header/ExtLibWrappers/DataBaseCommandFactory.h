#pragma once

#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class DataBaseCommandFactory : public IDataBaseCommandFactory
	{
	public:
		DataBaseCommandFactory();

		std::shared_ptr<IDataBaseCommand> CreateCommand() override;
	};

}



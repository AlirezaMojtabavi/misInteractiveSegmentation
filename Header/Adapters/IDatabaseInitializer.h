#pragma  once

#include "ITableQueryBuilder.h"

namespace parcast
{

	class IDatabaseInitializer
	{
	public:
		virtual void AddQuerybuilder(std::shared_ptr<ITableQueryBuilder> queryBuilder) = 0;
		virtual void Initialize() const = 0;

		virtual ~IDatabaseInitializer() = default;
	};

}
#pragma once
#include "misobjectProperitiesEnums.h"
 
namespace parcast
{
	class ISegmentedObjectNameGenerator
	{
	public:
		virtual std::string GetName(mis3DModelTypes type) = 0;
	};
}
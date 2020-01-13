#pragma once
#include "ISplitString.h"

namespace parcast
{
	template<typename T>
	class SplitString : public ISplitString<T>
	{
	public:
		using ValueType = T;

		std::vector<ValueType> GetNumbers(std::string const& inputString, char delimiter) const override
		{
			std::istringstream parseStream(inputString);
			auto valueStr = std::string();
			auto values = std::vector<ValueType>{};

			while (std::getline(parseStream, valueStr, delimiter)) {
				if (valueStr.empty())
					continue;
				auto value = ValueType();
				std::istringstream(valueStr) >> value;
				values.push_back(value);
			}

			return values;
		}
	};
}

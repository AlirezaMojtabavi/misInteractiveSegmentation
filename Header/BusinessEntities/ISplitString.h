#pragma once

namespace parcast
{

	template<typename T>
	class ISplitString
	{
	public:
		virtual ~ISplitString() = default;
		virtual std::vector<T> GetNumbers(const std::string& stringOfNumbers, char delimiter) const = 0;
	};

}

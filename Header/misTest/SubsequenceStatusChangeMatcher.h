#pragma once

namespace parcast
{

	class SubsequenceStatusChangeMatcher
	{
	public:
		SubsequenceStatusChangeMatcher(const std::string& statusString)
			: m_StatusString(statusString)
		{
		}

		bool operator()(std::string statusString, misResultMessageEnums resType, std::string resDesc)
		{
			return m_StatusString == statusString;
		}

	private:
		std::string m_StatusString;
	};

}
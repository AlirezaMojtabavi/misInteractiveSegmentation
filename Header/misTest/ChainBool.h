#pragma once

namespace parcast
{

	class ChainBool
	{
	public:
		ChainBool() = default;

		ChainBool(std::ostream& errorOutput, const std::string& chainName)
			: m_ErrorOutput(errorOutput),
			m_ChainName(chainName)
		{
		}

		operator bool()
		{
			return IsTrue();
		}

		ChainBool& Add(bool newBool)
		{
			m_Value = m_Value && newBool;
			++m_Length;
			if (!newBool)
				m_ErrorOutput << "ChainBool " << m_ChainName << " #" << m_Length << " turned false." << std::endl;
			return *this;
		}

		bool IsTrue()
		{
			return m_Value;
		}

	private:
		int m_Length = 0;
		bool m_Value = true;
		std::ostream& m_ErrorOutput = std::ostringstream();
		const std::string& m_ChainName = "UNNAMED";
	};

}
#pragma once

namespace parcast
{
	template <class ConnectionType>
	class ConnectionGuard
	{
	public:
		ConnectionGuard(std::shared_ptr<ConnectionType> connection)
			: m_Connection(connection)
		{
			if (!m_Connection->IsOpen())
				m_Connection->Open();
		}

		~ConnectionGuard()
		{
			if (m_Connection->IsOpen())
				m_Connection->Close();
		}
		
		void Close()
		{
			if(m_Connection->IsOpen())
				m_Connection->Close();
		}

	private:
		std::shared_ptr<ConnectionType> m_Connection;
	};
}

#pragma once

class PortException:public std::exception
{
};
class misFindPortByName
{
	std::vector<int> m_ports;
	std::vector<std::string> m_friendlyNames;

#pragma warning (suppress : 4290)	
	bool FindPorts() throw (PortException);

	GUID* FindGuid();

	bool IsNumeric(LPCSTR pszString, bool bIgnoreColon);
	bool IsNumeric(LPCWSTR pszString, BOOL bIgnoreColon);
public:
	int  GetPortByName(std::string  name);

	misFindPortByName(void);
	~misFindPortByName(void);
};

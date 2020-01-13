#include <string>
#include <vector>

class  WindowParam
{
public:
	int m_Index;
	WindowParam(std::string name,void* handle,int index)
	{
		m_name=name;
		m_handel=handle;
		m_Index=index;
	}
	std::string   m_name;
	void*    m_handel;
};

class  SubTabParam
{
public:
	std::string   name;
	std::vector<WindowParam> windows ;
};

class TabParam
{
public:
	std::string   name;
	std::vector<SubTabParam> m_subTabs ;
};

class Model
{
public:
	std::string   name;
	std::vector<TabParam> m_Tabbs ;
};
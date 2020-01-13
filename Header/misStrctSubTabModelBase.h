#pragma   once
#include <string>
#include "misWindowBase.h"
#include <list>

class misStrctSubTabModelBase
{
protected:
	std::string    m_ParentTabName;	 
	bool m_Active;

public:
	typedef std::list<misWindowBase*>  ListType;	
	ListType  childWindows;
	void Selected();
	void Unselected();
	bool Active() const { return m_Active; }
	void Active(bool val) { m_Active = val; }
	//##ModelId=4885AC7B0130
	int get_m_ID() const;

	//##ModelId=4885AC7B0138
	void set_m_ID(int left);

	//##ModelId=4885AC7B013A
	std::string get_m_Name() const;

	//##ModelId=4885AC7B013C
	void set_m_Name(std::string left);

	void	set_m_ParentTabName(std::string parentTabName);
	std::string	get_m_ParentTabName();

	//##ModelId=4885B14C02DE
	void* get_m_MainHandle() const;

	//##ModelId=4885B14C030D
	void set_m_MainHandle(void* left);

	bool GetWindow(std::string name,misWindowBase* window);

private:
	//##ModelId=4885AC7B00FB
	int m_ID;
	//##ModelId=4885AC7B0109
	std::string m_Name;
	void* m_MainHandle;


};


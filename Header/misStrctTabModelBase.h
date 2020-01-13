#pragma   once
#include "misStrctSubTabModelBase.h"
 

class misStrctTabModelBase
{

public:
	bool m_Selected;
	void Selected();
	void UnSelected();
	bool active;
	void  AddSubTab(misStrctSubTabModelBase*  subTab);
	int get_m_ID() const;

	//##ModelId=47D7E54F01D4
	void set_m_ID(int left);

	//##ModelId=47D7E54F0203
	std::string get_m_Name() const;

	//##ModelId=47D7E54F0223
	void set_m_Name(std::string left);
	//##ModelId=47D7E54F0290
	void set_m_SubTabs(std::list<misStrctSubTabModelBase*> left);

	//##ModelId=47D7E54F0271
	bool get_m_SubTab(std::string name,misStrctSubTabModelBase* group) const;
	//bool get_m_Group(int index,misGroupTab& group) const;
	//##ModelId=47D53044034B
	int m_ID;
	//##ModelId=47D53053036B
	std::string m_Name;
public:
	typedef std::list<misStrctSubTabModelBase*> ListType;
	ListType m_SubTabs;


};
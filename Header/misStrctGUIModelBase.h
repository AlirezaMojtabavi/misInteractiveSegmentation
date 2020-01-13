#pragma   once
#include <string>
#include "misStrctTabModelBase.h"

class misStrctGUIModelBase
{
public :
	void SetActiveTab(std::string name);
	//##ModelId=47D7E51B0167
	bool get_m_GUITab(std::string name,misStrctTabModelBase* tabModel) const;
	//bool get_m_GUITab(int index,misStrctTabModelBase& tabModel) const;
	misStrctTabModelBase* GetActiveTab() const { return  m_ActiveTab; }

	//##ModelId=47D7E51B0177
	void set_m_GUITabs(std::list<misStrctTabModelBase*> left);

	//##ModelId=47D7E51B01A5
	int get_m_VisibleTab() const;

	//##ModelId=47D7E51B01C5
	void set_m_VisibleTab(int left);
	void AddTab(misStrctTabModelBase* tab);
protected:

	int m_VisibleTab;//TODO:enum
	typedef   std::list<misStrctTabModelBase*>  ListType;
	ListType m_GUITabs;
	misStrctTabModelBase*  m_ActiveTab;



};
#include "stdafx.h"
#include "misStrctTabModel.h"

#include "ISubsequenceLayout.h"

using std::string; 

int misStrctTabModel::get_m_ID() const
{
    return m_ID;
}

void misStrctTabModel::set_m_ID(int left)
{
    m_ID = left;
}

string misStrctTabModel::get_m_Name() const
{
    return m_Name;
}

void misStrctTabModel::SetName(string left)
{
    m_Name = left;
}


std::shared_ptr<ISubsequenceLayout> misStrctTabModel::GetSubTab(const std::string& name) const
{
	auto found = std::find_if(m_SubTabs.begin(), m_SubTabs.end(), [&name](auto subtab)
	{
		if (subtab->GetName() == name)
			return true;
		return false;
	});
	if (found != m_SubTabs.end())
		return *found;
	return nullptr;
}




 
void misStrctTabModel::set_m_SubTabs(std::list<std::shared_ptr<ISubsequenceLayout>> left)
{
    m_SubTabs = left;
}

 

 int misStrctTabModel::get_m_VisibleSubTab() const
{
    return m_VisibleSubTab;
}


 void misStrctTabModel::set_m_VisibleSubTab(int  left)
{
    m_VisibleSubTab = left;
}



void misStrctTabModel::AddSubTab( std::shared_ptr<ISubsequenceLayout> group )
{
	this->m_SubTabs.push_back(group);
	group->SetParentTabName(this->get_m_Name());

}

misStrctTabModel::misStrctTabModel()
{
	this->active=false;
}

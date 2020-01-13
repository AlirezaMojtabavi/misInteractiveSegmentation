#include "stdafx.h"
#include "misStrctGUIModel.h"


#include "ISubsequenceLayout.h"

using std::list;
using std::string;

misStrctGUIModel::misStrctGUIModel()
{
}

void misStrctGUIModel::AddTab(misStrctTabModel  tab)
{
 
	this->m_GUITabs.push_front(tab); 
}

misStrctTabModel misStrctGUIModel::GetGUITab(string name) const
{
	auto found = std::find_if(m_GUITabs.cbegin(), m_GUITabs.cend(), [&](auto subtab)
	{
		if (name == subtab.get_m_Name())
			return true;
		return false;
	});
	if (found != m_GUITabs.end())
		return *found;
	return misStrctTabModel();
}

//====================================================================================

void misStrctGUIModel::set_m_GUITabs(list<misStrctTabModel> left)
{
    m_GUITabs = left;
}



int  misStrctGUIModel::get_m_VisibleTab() const
{
    return m_VisibleTab;
}



void misStrctGUIModel::set_m_VisibleTab(int  left)
{
    m_VisibleTab = left;
}




size_t misStrctGUIModel::GetTabCount()
{
	return m_GUITabs.size();
}

void misStrctGUIModel::SetActiveTab( string name )
{

	//SetActiveTab
	//============================================
	ListType::const_iterator   iter=this->m_GUITabs.begin();
	ListType::const_iterator   iterEnd=this->m_GUITabs.end();
	while (iter!=iterEnd)
	{

		string temp=iter->get_m_Name();
		if (temp==name)
		{
			this->m_ActiveTab=(*iter);
		}
		iter++;
	}
}

void* misStrctGUIModel::FinndWindowHandle( string name )
{
	for (auto tab : m_GUITabs)
	{
		for (auto subTab : tab.m_SubTabs)
		{
			auto childWindows = subTab->GetchildWindows();
			auto res = std::find_if(childWindows.begin(), childWindows.end(), [&](misWindowModel  model)->bool
			{
				if (model.GetName() == name)
					return  true;
				return  false;
			});
			if (res != childWindows.end())
				return res->GetHandle();
		}
	}
	return  nullptr;
}

 

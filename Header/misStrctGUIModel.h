#ifndef MISSTRCTGUIMODEL_H_HEADER_INCLUDED_B7E3A07C
#define MISSTRCTGUIMODEL_H_HEADER_INCLUDED_B7E3A07C

#include "..\misGUIModel\misGuiMdelMacroes.h"
#include "misStrctTabModel.h"

class misStrctGUIModel
{
private:

	misStrctTabModel  m_ActiveTab;
	misStrctTabModel GetActiveTab() const { return m_ActiveTab; }

public:
	typedef   std::list<misStrctTabModel>  ListType;
	ListType m_GUITabs;
	misStrctGUIModel();
	~misStrctGUIModel()
	{
	}
	void AddTab(misStrctTabModel tab);
	void SetActiveTab(std::string name);
	misStrctTabModel GetGUITab(std::string name) const;
	void set_m_GUITabs(std::list<misStrctTabModel> left);
	int get_m_VisibleTab() const;
	void set_m_VisibleTab(int left);
	size_t  GetTabCount();
	void*  FinndWindowHandle(std::string  name);

private:

	int m_VisibleTab;
};

#endif 

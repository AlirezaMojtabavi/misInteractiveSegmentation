#pragma   once

#ifndef MISSTRCTTABMODEL_H_HEADER_INCLUDED_B7E39069
#define MISSTRCTTABMODEL_H_HEADER_INCLUDED_B7E39069

#include "..\misGUIModel\misGuiMdelMacroes.h"

class ISubsequenceLayout;
//================================================================

//TODO:need  some modificaton
class misStrctTabModel
{
public:
	typedef std::list<std::shared_ptr<ISubsequenceLayout>> ListType;

	misStrctTabModel();

	void SetActiveSubTab(std::string name);
	void AddSubTab(std::shared_ptr<ISubsequenceLayout>  group);

	int get_m_ID() const;
	void set_m_ID(int left);

	std::string get_m_Name() const;
	void SetName(std::string left);

	std::shared_ptr<ISubsequenceLayout> GetSubTab(const std::string& name) const;

	void set_m_SubTabs(std::list<std::shared_ptr<ISubsequenceLayout>> left);

    int get_m_VisibleSubTab() const;
    void set_m_VisibleSubTab(int left);

	size_t GetGroupCount(){return this->m_SubTabs.size();}

	bool active;
	bool m_Selected;
    ListType m_SubTabs;

  private:
    int m_ID;
    std::string m_Name;
    int  m_VisibleSubTab;
};

#endif /* MISSTRCTTABMODEL_H_HEADER_INCLUDED_B7E39069 */

#pragma once

#include "CurrentSubSequenseStateStrct.h"

class subTabAbstractState
{
public:
	std::string   SubTabName;
	CurrentSubSequenseStateStrct subSequenceState;
	void SetSelected(bool value)
	{
		m_Selected = value;
	}
	void SetActivated(bool value)
	{
		m_Activated = value;
	}
	bool GetSelected()const
	{
		return m_Selected;
	}
	bool GetActivated()const
	{
		return m_Activated;
	}
private:
	bool m_Selected = false;
	bool m_Activated = false;
};
typedef std::vector<subTabAbstractState> subTabAbstractStateListTypdef;
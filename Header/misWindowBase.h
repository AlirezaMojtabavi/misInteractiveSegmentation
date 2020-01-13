#pragma once
#include <string>

class  misWindowBase
{
public:
	bool active;

	std::string m_ParentSubTabName;
	std::string m_ParentTabName;

	//##ModelId=4885ACA30280
	void set_m_Handle(void* left);
	void* get_m_Handle() const;
	std::string get_m_Name() const;
	void set_m_Name(std::string left);
	int GetWindowIndex() const;
	void SetWindowIndex(int val);
	void*  m_Handle;
	int m_WindowIndex;
	std::string m_Name;
};
